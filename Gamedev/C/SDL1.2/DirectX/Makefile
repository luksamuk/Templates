CC       = g++
APP      = -o DX9SDL.exe
DX9LINK += -ld3d9 -ld3dx9
SDLLINK  = -lmingw32 -lSDLmain -lSDL
SUBSYSTEM = -mwindows

LINK = $(SDLLINK) $(DX9LINK)


all: dx9_sdl12.cpp
	@echo Compiling...
	$(CC) dx9_sdl12.cpp $(APP) $(LINK) $(SUBSYSTEM)
