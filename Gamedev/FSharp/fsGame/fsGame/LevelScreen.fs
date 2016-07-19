namespace MyGame.Screens

open System
open System.Numerics
open MyGame.GameManager
open Microsoft.Xna.Framework
open Microsoft.Xna.Framework.Graphics

type LevelScreen() =
    inherit ScreenManager.Screen()

    let texture =
        new Texture2D(ScreenManager.GDM.GraphicsDevice,
                      1, 1, false, SurfaceFormat.Color)

    member this.fibonacci =
        Seq.unfold
            (fun (current, next) -> Some(current, (next, current + next)))
            (BigInteger 1, BigInteger 1)

    member this.points x = [
        for i = 0 to x do
            let seqitem = Seq.item i this.fibonacci
            let angle = ((float i) * (Math.PI / 2.0))
            let x =
                (float seqitem) * (Math.Cos angle) +
                (float ScreenManager.GDM.PreferredBackBufferWidth / 2.0)
            let y =
                (float seqitem) * (Math.Sin angle) +
                (float ScreenManager.GDM.PreferredBackBufferHeight / 2.0)
            yield (x, y)
    ]

    override this.Initialize() =
        base.Initialize()

    override this.LoadContent() =
        texture.SetData<Color>([| Color.White |])
        base.LoadContent()

    override this.Update gameTime = ()

    member this.DrawLine (spriteBatch : SpriteBatch, startline : Vector2, endline : Vector2) =
        let edge: Vector2 = endline - startline
        let angle = Math.Atan2(float edge.Y, float edge.X)

        spriteBatch.Draw(texture,
            new Rectangle(int startline.X, int startline.Y, int (edge.Length()), 2),
            System.Nullable(),
            Color.Red,
            float32 angle,
            Vector2.Zero,
            SpriteEffects.None,
            0.0f)

    override this.Draw spriteBatch =
        spriteBatch.Begin()
        let mutable startsAt =
            new Vector2((float32 ScreenManager.GDM.PreferredBackBufferWidth / 2.0f),
                        (float32 ScreenManager.GDM.PreferredBackBufferHeight / 2.0f))
        for point in this.points 20 do
            let endsAt = new Vector2(float32 (fst point), float32 (snd point))
            this.DrawLine(spriteBatch, startsAt, endsAt)
            startsAt <- endsAt
        spriteBatch.End()