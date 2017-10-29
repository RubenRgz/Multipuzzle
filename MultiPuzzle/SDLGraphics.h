/********************************************************************/
/**
* @LC	  2017/10/18
* @file   SDLGraphics.h
* @Author Rubén Rodríguez Serrano (rubn2113@gmail.com)
* @date   2017/10/16
* @brief  Class in charge of manage SDL graphics
* @bug	  No known bugs.
*/
/********************************************************************/
#pragma once

/************************************************************************/
/* Includes												                */
/************************************************************************/
#include "Module.h"
#include <SDL.h>
#include <SDL_image.h>

/************************************************************************/
/* Global variables										                */
/************************************************************************/
const int SCREEN_WIDTH = 1024;															/*!< Screen width size */
const int SCREEN_HEIGHT = 768;															/*!< Screen height size */

/************************************************************************/
/* Application Class									                */
/************************************************************************/
class SDLGraphics : public Module<SDLGraphics>
{
	/************************************************************************/
	/* Constructor and Destructor Definitions				                */
	/************************************************************************/
public:
	SDLGraphics();																		/*!< Standrad Constructor */
	virtual ~SDLGraphics();																/*!< Standrad Destructor */
	
	/************************************************************************/
	/* Class functions										                */
	/************************************************************************/
public:
	void ClearBackBuffer();																/*!< Clear Back Buffer */
	void RenderPresent();																/*!< Render actual data */
	void Update();																		/*!< Update SDLGraphics info */
	SDL_Renderer* GetSDLRenderer();														/*!< Returna pointer to the SDL renderer object */

private:
	bool OnStartUp();																	/*!< Initialize the module */
	virtual void OnShutDown()override;													/*!< Free all resources */

	/************************************************************************/
	/* Classs variables										                */
	/************************************************************************/
private:
	SDL_Window* m_Window;																/*!< Actual window */
	SDL_Renderer* m_Renderer;															/*!< SDL renderer object */
	int m_MousePosX;																	/*!< Mouse pos X */
	int m_MousePosY;																	/*!< Mouse pos Y */
};

