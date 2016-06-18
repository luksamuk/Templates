namespace MyGame

open System
open System.Collections.Generic
open Microsoft.Xna.Framework
open Microsoft.Xna.Framework.Content
open Microsoft.Xna.Framework.Graphics
open Microsoft.Xna.Framework.Input
open Microsoft.Xna.Framework.Storage
open Microsoft.Xna.Framework.GamerServices

open MyGame.GameManager
open MyGame.Screens

type Game1() as this =
  inherit Game()

  let graphics = new GraphicsDeviceManager(this)
  do this.Content.RootDirectory <- "Content"

  override this.Initialize() =
    ScreenManager.GDM <- graphics
    graphics.PreferredBackBufferWidth  <- 1280
    graphics.PreferredBackBufferHeight <- 720
    ScreenManager.AddScreen(new LevelScreen())
    base.Initialize()

  override this.LoadContent() =
    ScreenManager.spriteBatch <- new SpriteBatch(this.GraphicsDevice)

  override this.UnloadContent() = ()

  override this.Update gameTime =
    if GamePad.GetState(PlayerIndex.One).Buttons.Back = ButtonState.Pressed
        || Keyboard.GetState().IsKeyDown(Keys.Escape)
      then this.Exit()
    ScreenManager.UpdateScreens gameTime
    base.Update(gameTime)

  override this.Draw gameTime =
    this.GraphicsDevice.Clear Color.CornflowerBlue
    ScreenManager.DrawScreens()
    base.Draw gameTime
