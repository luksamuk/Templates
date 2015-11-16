// Link with mingw32, SDL2main, SDL2, d3d9, d3dx9.

#include <cstdio>
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <SDL2/SDL.h>

#define WINSIZE_x 800
#define WINSIZE_y 600
#define BUFSIZE_x WINSIZE_x
#define BUFSIZE_y WINSIZE_y
#define BUFSIZE_n 1
#define BUFSIZE_f 1000
#define ASPECTRATIO ((float)(WINSIZE_x/WINSIZE_y))

// Useful functions
bool initialize();
void load();
void update();
void draw();
void quit();


// A Direct3D vertex has 3 coordinates and a color associated with it
struct D3DVERTEX
{
	float fX, fY, fZ;
	DWORD dwColor;
};

// SDL variables
SDL_Window*             window;
SDL_Renderer*           renderer;
bool                    GameRunning = true;

// DirectX variables
LPDIRECT3D9             Direct3D_object;    // For creating a D3D device
LPDIRECT3DDEVICE9       Direct3D_device;    // Basic rendering object
D3DPRESENT_PARAMETERS   present_parameters; // Stores important attributes and
D3DXMATRIX              projection_matrix;  //  properties your D3D device will have
LPDIRECT3DVERTEXBUFFER9 tri_buffer = NULL;  // Data buffer which the D3D device can draw from
VOID*                   pData;              // Pointer to beginning of vertex buffer
// Actual data to be fed to vertex buffer
D3DVERTEX aTriangle[] = {{-2.0f,  1.0f, 10.0f, 0xFFFF0000},
		                 {-3.0f, -1.0f, 10.0f, 0xFF00FF00},
						 {-1.0f, -1.0f, 10.0f, 0xFF0000FF}};

int main(int argc, char** argv)
{
	if(!initialize()) return 1;
	load();
	while(GameRunning)
	{
		update();
		draw();
	}

	quit();

	return 0;
}

bool initialize()
{
	/* Initialization of SDL */
	// Create Window
	if(!(window = SDL_CreateWindow("DirectX 9 + SDL 2",
							SDL_WINDOWPOS_CENTERED,
							SDL_WINDOWPOS_CENTERED,
							WINSIZE_x, WINSIZE_y,
							SDL_WINDOW_RESIZABLE))) // Might have to change this flag
	{
		fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
		return false;
	}

	// Create Renderer
	if(!(renderer = SDL_CreateRenderer(window, -1, 0)))
	{
		fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
		return false;
	}

	/* Initialization of Direct3D */

	// Create Direct3D object
	Direct3D_object = Direct3DCreate9(D3D_SDK_VERSION);
	if(!Direct3D_object)
	{
		MessageBox(GetActiveWindow(), "Can't create D3D object.", "D3DERR", MB_OK);
		quit();
		return false;
	}

	// Direct3D Device Parameters
	ZeroMemory(&present_parameters, sizeof(present_parameters));
	present_parameters.Windowed               = true;
	present_parameters.SwapEffect             = D3DSWAPEFFECT_DISCARD;
	present_parameters.EnableAutoDepthStencil = true;
	present_parameters.AutoDepthStencilFormat = D3DFMT_D16;
	present_parameters.hDeviceWindow          = GetActiveWindow();
	present_parameters.BackBufferWidth        = BUFSIZE_x;
	present_parameters.BackBufferHeight       = BUFSIZE_y;
	present_parameters.BackBufferFormat       = D3DFMT_R5G6B5;
	present_parameters.MultiSampleType        = D3DMULTISAMPLE_NONE;

	// Create the Direct3D Device
	if(FAILED(Direct3D_object->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
								GetActiveWindow(), D3DCREATE_SOFTWARE_VERTEXPROCESSING,
								&present_parameters, &Direct3D_device)))
	{
		MessageBox(GetActiveWindow(), "Can't create D3D device.", "D3DERR", MB_OK);
		quit();
		return false;
	}

	// Setup projection matrix, lighting, culling, depth buffer and vertex format.
	// Matrix: Depth buffer set
	D3DXMatrixPerspectiveFovLH(&projection_matrix, D3DX_PI / 4.0f, ASPECTRATIO, BUFSIZE_n, BUFSIZE_f);
	Direct3D_device->SetTransform(D3DTS_PROJECTION, &projection_matrix);
	Direct3D_device->SetRenderState(D3DRS_AMBIENT, RGB(255, 255, 255));
	// Lighting: disabled
	Direct3D_device->SetRenderState(D3DRS_LIGHTING, false);
	// Backface culling: disabled
	Direct3D_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	// Vertex format
	Direct3D_device->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	Direct3D_device->SetFVF((D3DFVF_XYZ | D3DFVF_DIFFUSE));
	return true;
}

void load()
{
	/* LOADING PRIMITIVE DATA */

	// Create vertex buffer object
	// Tells device to only write and not read to buffer for optimization;
	// Specifies vertex format;
	// Pass a flag signaling to manage the data;
	// Pass address of object which will become vertex buffer.
	Direct3D_device->CreateVertexBuffer(sizeof(aTriangle), D3DUSAGE_WRITEONLY,
										(D3DFVF_XYZ | D3DFVF_DIFFUSE),
										D3DPOOL_MANAGED, &tri_buffer, NULL);
	// Set pData as the main pointer to the vertex buffer, then copy the vertex
	// data to the memory pointed by pData.
	tri_buffer->Lock(0, sizeof(pData), (void**)&pData, 0);
	memcpy(pData, aTriangle, sizeof(aTriangle));
	tri_buffer->Unlock();
}

void update()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
		case SDL_QUIT:
			GameRunning = false;
		case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_ESCAPE)
					GameRunning = false;
				break;
		default: break;
		}
	}
}

void draw()
{
	if(!Direct3D_device || !Direct3D_object) return;

	Direct3D_device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
					D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	Direct3D_device->BeginScene();

	// Draw everything here
	Direct3D_device->SetStreamSource(0, tri_buffer, 0, sizeof(D3DVERTEX));
	Direct3D_device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
	//
		
	Direct3D_device->EndScene();
	Direct3D_device->Present(NULL, NULL, NULL, NULL);
}

void quit()
{
	// Release Direct3D device and object
	Direct3D_device->Release();
	Direct3D_device = NULL;
	Direct3D_object->Release();
	Direct3D_object = NULL;

	// Finish SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
