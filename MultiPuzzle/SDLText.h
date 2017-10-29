/********************************************************************/
/**
* @LC	  2017/10/25
* @file   SDLText.h
* @Author Rubén Rodríguez Serrano (rubn2113@gmail.com)
* @date   2017/10/21
* @brief  Main Menu Window
* @bug	  No known bugs.
*/
/********************************************************************/
#pragma once

/************************************************************************/
/* Includes												                */
/************************************************************************/
#include <SDL_ttf.h>
#include "Module.h"
#include <string>

/************************************************************************/
/* Structures											                */
/************************************************************************/
struct FontData																									/*!< Data to init the font */
{
	char* _pathFontFile;
	int _fontSize;

	FontData()
	{
		_pathFontFile = "c:/windows/fonts/arialbd.ttf";
		_fontSize = 24;
	}
};

/************************************************************************/
/* SDL Text												                */
/************************************************************************/
class SDLText : public Module<SDLText, const FontData&>
{
	/************************************************************************/
	/* Constructor and Destructor Definitions				                */
	/************************************************************************/
public:
	SDLText();
	virtual ~SDLText();

	/************************************************************************/
	/* Class functions										                */
	/************************************************************************/
private:
	bool OnStartUp(const FontData& _fontData);																	/*!< Initialize the module */
	virtual void OnShutDown()override;																			/*!< Free all resources */
	bool LoadFont(const char& _pathFontFile, int _fontSize);													/*!< Load selected font */

public:
	void RenderSolidText(std::string& _text, SDL_Color& _textColor, int _x,										/*!< Render a solid text */
						int _y, SDL_Renderer& _renderer);
	void RenderShadedText(std::string& _text, SDL_Color& _backgroundColor, SDL_Color& _textColor, int _x,		/*!< Render a shaded text */
		int _y, SDL_Renderer& _renderer);
	void RenderBlendedText(std::string& _text, SDL_Color& _textColor, int _x,									/*!< Render a blended text */
		int _y, SDL_Renderer& _renderer);

	/************************************************************************/
	/* Classs variables										                */
	/************************************************************************/
private:
	TTF_Font* m_font;																							/*!< Pointer to font data */
	SDL_Surface* m_surfaceMessage;																				/*!< Pointer to surface */
	SDL_Texture* m_message;																						/*!< Pointer to texture message */
	SDL_Rect m_messageRect;																						/*!< Rect of the texture message */
};

