import std.stdio;
import core.thread;
import derelict.sdl2.sdl;
import derelict.sdl2.mixer;
import derelict.opengl3.gl;

SDL_Window* window;
SDL_GLContext glContext;

bool isgamerunning = true;

// Example vars
float POS_X,
      POS_Y;
float ANGLE;

const float speed  = 10.0f;
const float c_acc  = 5.0f;
const float half_size = 150.0f;


void main()
{
	DerelictSDL2.load();
	DerelictSDL2Mixer.load();
	DerelictGL.load();

	window = SDL_CreateWindow("OpenGL",
			 SDL_WINDOWPOS_CENTERED,
			 SDL_WINDOWPOS_CENTERED,
			 800, 600,
			 SDL_WINDOW_OPENGL);
	
	// GL Init
	glContext = SDL_GL_CreateContext(window);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
		glOrtho(0, 800, 600, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Example init
	POS_X = 400.0f;
	POS_Y = 300.0f;
	ANGLE = 0.0f;


	if(!window) {
		writefln("Error: %d", SDL_GetError());
		return;
	}

	while(isgamerunning)
	{
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					isgamerunning = false;
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							isgamerunning = false;
							break;
						default: break;
					}
				default: break;
			}
		}

		ANGLE += 1.0f;

		if(ANGLE > 360.0f) ANGLE -= 360.0f;
		else if(ANGLE < 0.0f) ANGLE += 360.0f;


		glClear(GL_COLOR_BUFFER_BIT);

		glPushMatrix();
				glTranslatef(POS_X, POS_Y, 0.0f);
				glRotatef(ANGLE, 0.0f, 0.0f, 1.0f);

				glBegin(GL_QUADS);
					glColor3f(1.0f, 1.0f, 1.0f);
					glVertex2f(-half_size, -half_size);
					glColor3f(1.0f, 0.0f, 0.0f);
					glVertex2f(half_size, -half_size);
					glColor3f(0.0f, 1.0f, 0.0f);
					glVertex2f(half_size, half_size);
					glColor3f(0.0f, 0.0f, 1.0f);
					glVertex2f(-half_size, half_size);
				glEnd();
			glPopMatrix();

			Thread.sleep(dur!("msecs")(50));

		SDL_GL_SwapWindow(window);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
}
