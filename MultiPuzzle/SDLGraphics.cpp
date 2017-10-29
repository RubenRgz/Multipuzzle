#include "SDLGraphics.h"
#include <iostream>
#include <functional>


SDLGraphics::SDLGraphics()
{
	Connect(std::bind(&SDLGraphics::OnStartUp, this));
	m_Window = NULL;
	m_Renderer = NULL;
}


SDLGraphics::~SDLGraphics()
{
}

bool SDLGraphics::OnStartUp()
{
	bool bExito = true;

	//SDL Init
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL No pudo inicializarse! SDL Error: %s\n", SDL_GetError());
		bExito = false;
	}
	else
	{
		//Activate Vertical Sync
		if (!SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1"))
		{
			printf("Warnig: VSync is not activated!");
		}

		//Texture filter lineal
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warnig: Texture filter lineal is not activated!");
		}

		//Create window
		m_Window = SDL_CreateWindow("MultiPuzzle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (m_Window == NULL)
		{
			printf("Can´t created window! SDL Error: %s\n", SDL_GetError());
			bExito = false;
		}
		else
		{
			//Create Render
			m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
			if (m_Renderer == NULL)
			{
				printf("Can´t create renderer! SDL Error: %s\n", SDL_GetError());
				bExito = false;
			}
			else
			{
				//Init color render
				SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Init PNG loader
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image can´t be initialized! SDL_image Error: %s\n", IMG_GetError());
					bExito = false;
				}
			}
		}
	}

	return bExito;
}

void SDLGraphics::OnShutDown()
{
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	m_Window = NULL;
	m_Renderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

void SDLGraphics::ClearBackBuffer()
{
	//Clear Screen
	SDL_SetRenderDrawColor(m_Renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(m_Renderer);
}

void SDLGraphics::RenderPresent()
{
	SDL_RenderPresent(m_Renderer);
}

void SDLGraphics::Update()
{
	SDL_GetMouseState(&m_MousePosX, &m_MousePosY);
}

SDL_Renderer * SDLGraphics::GetSDLRenderer()
{
	return m_Renderer;
}

