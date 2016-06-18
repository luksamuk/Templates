namespace MyGame.GameManager

open System.Collections.Generic
open Microsoft.Xna.Framework
open Microsoft.Xna.Framework.Content
open Microsoft.Xna.Framework.Graphics

// Useful functions
module Util =
    // Keeps a value within a certain range.
    let clamp(value : unit byref, min, max) : unit =
        if   value < min then
            value <- min
        elif value > max then
            value <- max
        else value

    let rec factorial = function
        | n when n < 1 -> 1
        | n            -> n * factorial(n - 1)

// Screen Manager
module ScreenManager =
// Screen class
    [<AbstractClass>]
    type Screen() =
        // Fields
        let mutable active        = false
        let mutable contentloaded = false
        let mutable removeme      = false
        
        // Properties
        member this.Active
            with public get()     = active
            and  public set value = active <- value
        member this.ContentLoaded
            with public get()     = contentloaded
            and  public set value = contentloaded <- value
        member this.RemoveMe
            with public get()     = removeme
            and  public set value = removeme <- value
        
        // Methods
        abstract member Initialize: unit -> unit
        default this.Initialize() = 
            this.Active <- true

        abstract member LoadContent: unit -> unit
        default this.LoadContent() =
            this.ContentLoaded <- true

        abstract member UnloadContent: unit -> unit
        default this.UnloadContent() = 
            this.ContentLoaded <- false

        abstract member Update: GameTime -> unit
        abstract member Draw: SpriteBatch -> unit

    let mutable GSC = Unchecked.defaultof<GameServiceContainer>
    let mutable GDM = Unchecked.defaultof<GraphicsDeviceManager>
    let mutable spriteBatch = Unchecked.defaultof<SpriteBatch>
    
    let mutable private screenList        = new List<Screen>()
    let mutable private disposableScreens = new Stack<Screen>()
    let mutable private addedScreens      = new Stack<Screen>()

    let AddScreen scr =
        addedScreens.Push scr
   
    let UpdateScreens(gameTime : GameTime) =
        // Remove screens that are scheduled for removal
        while disposableScreens.Count <> 0 do
            disposableScreens.Peek().UnloadContent()
            ignore <| screenList.Remove(disposableScreens.Peek())
            ignore <| disposableScreens.Pop()
        // Add screens that are scheduled for addition
        while addedScreens.Count <> 0 do
            ignore <| addedScreens.Peek().Initialize()
            ignore <| addedScreens.Peek().LoadContent()
            ignore <| screenList.Add(addedScreens.Peek())
            ignore <| addedScreens.Pop()
        // Finally, update
        for scr in screenList do
            if scr.RemoveMe then
                disposableScreens.Push scr
            scr.Update gameTime
            
    let DrawScreens() =
        for scr in screenList do
            scr.Draw spriteBatch