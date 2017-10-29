/********************************************************************/
/**
* @LC	  2017/10/18
* @file   Application.h
* @Author Rubén Rodríguez Serrano (rubn2113@gmail.com)
* @date   2017/10/16
* @brief  This class is in charge of run the application
* @bug	  No known bugs.
*/
/********************************************************************/
#pragma once

/************************************************************************/
/* Includes												                */
/************************************************************************/
#include <map>
#include "InGame.h"
#include "MainMenu.h"
#include "Timer.h"

/************************************************************************/
/* Defines												                */
/************************************************************************/
#define MS_PER_UPDATE 1.0/60.0														/*!< Time per update in milliseconds */

/************************************************************************/
/* Application Class									                */
/************************************************************************/
class Application
{
	/************************************************************************/
	/* Constructor and Destructor Definitions				                */
	/************************************************************************/
public:
	Application();																	/*!< Standrad Constructor */
	virtual ~Application();															/*!< Standrad Destructor */

	/************************************************************************/
	/* Class functions										                */
	/************************************************************************/
public:
	void Run();																		/*!< Function that runs the application */

private:
	bool Initialize();																/*!< Initialize all data required by the application */
	bool InitModules();																/*!< Initialize all Modules */
	void Update(float _deltaTime);													/*!< Update all the systems */
	void Render();																	/*!< Main Render */
	void Destroy();																	/*!< Destroy all data occupied */
	void SetState(WindowState _state);												/*!< Sets the initial window */	

	/************************************************************************/
	/* Classs variables										                */
	/************************************************************************/
private:
	std::map<WindowState, BaseWindow*> m_windowMap;									/*!< Map of all windows */	
	BaseWindow* m_pActiveWindow;													/*!< Pointer to actual window */	
	MainMenu* m_mainMenuWindow;														/*!< Pointer to Main Menu window */	
	InGame* m_inGameWindow;															/*!< Pointer to In Game window */	
	Timer m_timer;																	/*!< Object of timer class to manage the time of the application */	
	float m_fLastTime;																/*!< Variable to store the last time of a cicle */	
	float m_fActualTime;															/*!< SVariable to store the actual time of a cicle */	
	float m_fDeltaTime;					 											/*!< Elapse time between las time and actual time */
	Point m_mousePos;																/*!< Object to store the mouse position */
};

