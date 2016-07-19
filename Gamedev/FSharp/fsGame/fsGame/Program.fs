module Game

open System
open MyGame

[<EntryPoint>]
[<STAThread>]
let main argv = 
    use game = new Game1()
    game.Run()
    0