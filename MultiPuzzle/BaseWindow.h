/********************************************************************/
/**
* @LC	  2017/10/18
* @file   BaseWindow.h
* @Author Rubén Rodríguez Serrano (rubn2113@gmail.com)
* @date   2017/10/16
* @brief  Virtual window class to manage the inherite windows
* @bug	  No known bugs.
*/
/********************************************************************/
#pragma once

/************************************************************************/
/* Includes												                */
/************************************************************************/
#include <SDL_events.h>
#include "Point.h"

/************************************************************************/
/* Enums												                */
/************************************************************************/
enum WindowState																			/*!< Windows in the application */
{
	WS_NONE = 0,
	WS_MAINMENU,
	WS_INGAME,
	WS_TOTALNUM
};

/************************************************************************/
/* Base Window Class									                */
/************************************************************************/
class BaseWindow
{
	/************************************************************************/
	/* Constructor and Destructor Definitions				                */
	/************************************************************************/
public:
	BaseWindow() {};
	virtual ~BaseWindow() {};

	/************************************************************************/
	/* Class functions										                */
	/************************************************************************/
public:
	virtual bool Initialize() { return true; };												/*!< Initialize all window data */
	virtual void Update(float _deltaTime) { _deltaTime; };									/*!< Updates the window */
    virtual void Render() {};																/*!< Renders window info*/
	virtual void Destroy() {};																/*!< Destroy all data of a window */
	virtual void ManageInputs(SDL_Event& pEvent) { pEvent; };										/*!< Manage the window inputs */
	virtual void SetMousePos(Point _mousePos) {};											/*!< Sets the mouse position to all windows */
	virtual WindowState GetWindowChange() { return WindowState(); };						/*!< Returns the next window state */

	bool m_bChangeWindow;																	/*!< Boolean to check if is need a window change */
};

