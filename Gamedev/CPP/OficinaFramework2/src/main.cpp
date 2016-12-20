#include <oficina2/oficina.hpp>
#include "GameScreen.hpp"

int main(int argc, char** argv)
{
    oficina::ofInit();
    oficina::ofSetWindowSize(1280, 720);
    oficina::ofMapDefaultsP1();
    oficina::ofCanvasManager::add(new GameScreen);
    oficina::ofGameLoop();
    oficina::ofQuit();
	return 0;
}
