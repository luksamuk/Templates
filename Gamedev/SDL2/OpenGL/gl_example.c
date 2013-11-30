#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

// Variáveis para o SDL...
SDL_Window* window;
SDL_Renderer* renderer;
SDL_GLContext glcontext;
int isgamerunning;

// Posição do quadrado...
float POS_X, POS_Y;
float ANGLE;

// Uma variável constante para ser a minha
// velocidade comum, outra para uma acel. centrípeta comum.
const float speed  = 10.0f;
const float c_acc  = 5.0f;
// Tamanho da METADE de um lado do quadrado.
const float half_size = 50.0f;

int main(int argc, char** argv)
{
	/* INICIALIZANDO O SDL 2.0 */
	// Inicialize a tela
	window = SDL_CreateWindow("OpenGL",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			800, 600,
			SDL_WINDOW_OPENGL);
	// Caso haja erro, encerre o programa mostrando o que aconteceu.
	if(!window)
	{
		printf("Error: %s\n", SDL_GetError());
		return 1;
	}
	// Inicialize o renderizador e verifique erros
	renderer = SDL_CreateRenderer(window, -1, 0);
	if(!renderer)
	{
		printf("Error: %s\n", SDL_GetError());
		return 2;
	}

	/* INICIALIZANDO O OPENGL */
	// Force o sistema a utilizar OpenGL e crie um contexto para tal
	// (se não especificado, no Windows, seria usado DirectX)
	glcontext = SDL_GL_CreateContext(window);

	// Faça com que a projeção seja um plano cartesiano de 800x600, com o
	// eixo Y crescente PARA BAIXO.
	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, 800, 600, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);

	// Defina a cor de vazio como preto, com alpha nulo.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);


	/* INICIALIZANDO DADOS GERAIS */
	// Defina a posição inicial como (100, 100)
	POS_X = POS_Y = 100.0f;
	// Defina ângulo inicial como 0 graus.
	ANGLE = 0.0f;
	// Defina que o jogo rodará.
	isgamerunning = 1;


	/* ROTINA DE REPETIÇÃO */
	while(isgamerunning)
	{
		// Primeiramente, vamos lidar com o input.
		SDL_Event event;
		// Execute enquanto houver algum evento de
		// interação na fila de interações do quadro
		// atual do jogo. 
		while(SDL_PollEvent(&event))
		{
			// Há vários tipos de eventos...
			switch(event.type)
			{
			// Se o programa recebeu um sinal de saída
			// (a janela foi fechada), então saia.
			case SDL_QUIT:
				isgamerunning = 0;
				break;
			// Se o usuário apertou uma tecla...
			case SDL_KEYDOWN:
				// ...há várias teclas...
				switch(event.key.keysym.sym)
				{
				// Se foi ESC, saia do programa.
				case SDLK_ESCAPE:
					isgamerunning = 0;
					break;
				// Se foi esquerda ou direita, aumente ou
				// diminua a posição X do quadrado a rigor!
				case SDLK_LEFT:
					POS_X -= speed;
					break;
				case SDLK_RIGHT:
					POS_X += speed;
					break;
				// Faça algo parecido para o eixo Y
				case SDLK_UP:
					POS_Y -= speed;
					break;
				case SDLK_DOWN:
					POS_Y += speed;
					break;

				// Q e E vão rotacionar o quadrado.
				case SDLK_q:
					ANGLE -= c_acc;
					break;
				case SDLK_e:
					ANGLE += c_acc;
					break;
				// Descarte os demais casos.
				default: break;
				} // Fim do segundo switch.
				break;
			// Descarte os demais casos.
			default: break;
			} // Fim do primeiro switch.
		} // Fim do loop de eventos.

		// O ângulo do quadrado deverá ficar sempre entre 0 e 360, para
		// evitar transtornos.
		if(ANGLE > 360.0f) ANGLE -= 360.0f;
		else if(ANGLE < 0.0f) ANGLE += 360.0f;


		/* DESENHANDO O QUADRADO NA TELA */
		// Apague o quadro anterior para nos livrar de rastros/lixo.
		// Esses rastros são chamados de "artifacts".
		glClear(GL_COLOR_BUFFER_BIT);

		// Evite que outras coisas já impressas na matrix
		// sejam alteradas, empilhando-a.
		glPushMatrix();
		// Mova a origem do plano para a posição do quadrado.
		glTranslatef(POS_X, POS_Y, 0.0f);
		// Rotacione o quadrado para o ângulo em que ele está.
		glRotatef(ANGLE, 0.0f, 0.0f, 1.0f);

		// Aplique a cor vermelha no quadrado
		glColor3f(1.0f, 0.0f, 0.0f);

		// Desenhe o quadrado, utilizando um QUAD: basicamente
		// um quadrado composto de dois triângulos. Isso facilita
		// texturização
		glBegin(GL_QUADS);
			// Vértices do quadrado.
			glVertex2f(-half_size, -half_size);
			glVertex2f(half_size, -half_size);
			glVertex2f(half_size, half_size);
			glVertex2f(-half_size, half_size);
		// Termine a inserção de vértices
		glEnd();
	// Retorne a matrix anterior para seu lugar e aplique as alterações
	glPopMatrix();

	// Por fim, faça com que as alterações sejam DE FATO desenhadas
	// na tela.
	SDL_GL_SwapWindow(window);

	} // Fim do while(isgamerunning)

	// Se o programa chegou até aqui, isso significa que devemos fechá-lo,
	// destruindo nossas janelas, contextos e etc.
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	// Fim do programa.
	return 0;
}
