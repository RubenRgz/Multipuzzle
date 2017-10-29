#include "Texture.h"


Texture::Texture(void)
{
	//Init variables
	m_Renderer = NULL;
	m_Texture = NULL;
	m_Width = 0;
	m_Height = 0;
}

Texture::~Texture(void)
{
	Free();
}

bool Texture::LoadFromFile(SDL_Renderer *pRenderer, std::string path)
{
	//Free any information before
	Free();

	m_Renderer = pRenderer;	

	SDL_Texture* newTexture = NULL;

	//Load image
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Fail loading surface");
	}
	else
	{
		//Set image format
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture
		newTexture = SDL_CreateTextureFromSurface(m_Renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Fail creating texture");
		}
		else
		{
			//Dimensions
			m_Width = loadedSurface->w;
			m_Height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	m_Texture = newTexture;
	return m_Texture != NULL;
}

void Texture::Free()
{
	//Destroy image
	if (m_Texture != NULL)
	{
		SDL_DestroyTexture(m_Texture);
		m_Texture = NULL;
		m_Width = 0;
		m_Height = 0;
	}

	//Destroy Renderer reference
	m_Renderer = NULL;
}

void Texture::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(m_Texture, red, green, blue);
}

void Texture::SetBlendMode(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(m_Texture, blending);
}

void Texture::SetAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(m_Texture, alpha);
}

void Texture::Render(int x, int y, SDL_Rect* srcArea, int width, int height, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
  SDL_Rect selectQuad = { selectQuad.x = 0, selectQuad.y = 0, selectQuad.w = m_Width, selectQuad.h = m_Height };
  SDL_Rect renderQuad = { x, y, m_Width, m_Height };

  if (srcArea != nullptr)
  {
    selectQuad.x = srcArea->x;
    selectQuad.y = srcArea->y;
    selectQuad.w = srcArea->w;
    selectQuad.h = srcArea->h;
  }

  if (width > -1)
  {
    renderQuad.w = width;
  }

  if (height > -1)
  {
    renderQuad.h = height;
  }

	//Draw to the screen
	SDL_RenderCopyEx(m_Renderer, m_Texture, &selectQuad, &renderQuad, angle, center, flip);
}

int Texture::GetWidth()
{
	return m_Width;
}

int Texture::GetHeight()
{
	return m_Height;
}
