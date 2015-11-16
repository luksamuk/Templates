CC       = g++
APP      = -o DX9SDL2.exe
DX9LINK += -ld3d9 -ld3dx9
SDLLINK  = -lmingw32 -lSDL2main -lSDL2
SUBSYSTEM = -mwindows

LINK = $(SDLLINK) $(DX9LINK)


all: dx9_sdl.cpp
	@echo Compiling...
	$(CC) dx9_sdl.cpp $(APP) $(LINK) $(SUBSYSTEM)
