#include <oficina2/oficina.hpp>

int main(int argc, char** argv)
{
    oficina::ofInit();
    oficina::ofSetWindowSize(1280, 720);
    oficina::ofMapDefaultsP1();
    oficina::ofGameLoop();
    oficina::ofQuit();
	return 0;
}
