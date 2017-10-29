/********************************************************************/
/**
* @LC	  2017/10/18
* @file   Texture.h
* @Author Rubén Rodríguez Serrano (rubn2113@gmail.com)
* @date   2017/10/16
* @brief  Class in charge to create a texture
* @bug	  No known bugs.
*/
/********************************************************************/
#pragma once

/************************************************************************/
/* Includes												                */
/************************************************************************/
#include <SDL_image.h>
#include <string>

/************************************************************************/
/* Texture Class										                */
/************************************************************************/
class Texture
{
	/************************************************************************/
	/* Constructor and Destructor Definitions				                */
	/************************************************************************/
public:
	Texture();																			 /*!< Standrad Constructor */
	virtual ~Texture();																	 /*!< Standrad Destructor */

	/************************************************************************/
	/* Class functions										                */
	/************************************************************************/
public:
	bool LoadFromFile(SDL_Renderer *pRenderer, std::string path);						/*! <Load an image from specific path  */
	void Free();																		/*! <Free the texture  */
	void SetColor(Uint8 red, Uint8 green, Uint8 blue);									/*! <Sets color  */
	void SetBlendMode(SDL_BlendMode blending);											/*!< Sets Blend Mode  */
	void SetAlpha(Uint8 alpha);															/*!< Sets Alpha  */
	void Render(int x,
              int y,
              SDL_Rect* srcArea = nullptr,
              int width = -1,
              int height = -1,
              double angle = 0.0, 
		          SDL_Point* center = nullptr,
              SDL_RendererFlip flip = SDL_FLIP_NONE);									/*!< Render a texture in the position assigned  */																												
	int GetWidth();																		/*!< Gets longitude  */
	int GetHeight();																	/*!< Gets height  */

	/************************************************************************/
	/* Class variables										                */
	/************************************************************************/
private:
	SDL_Renderer* m_Renderer;															/*!< Pointer to renderer to create the resource  */
	SDL_Texture* m_Texture;																/*!< Texture in hardware  */
	int m_Width;																		/*!< Longitude of the image  */
	int m_Height;																		/*!< Height of the image  */
};

