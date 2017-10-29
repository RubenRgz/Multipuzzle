/********************************************************************/
/**
* @LC	  2017/10/21
* @file   MainMenu.h
* @Author Rubén Rodríguez Serrano (rubn2113@gmail.com)
* @date   2017/10/16
* @brief  Main Menu Window
* @bug	  No known bugs.
*/
/********************************************************************/
#pragma once

/************************************************************************/
/* Includes												                */
/************************************************************************/
#include "BaseWindow.h"
#include "Texture.h"
#include "Point.h"
#include "Rect.h"

/************************************************************************/
/* Main Menu Class										                */
/************************************************************************/
class MainMenu :
	public BaseWindow
{
	/************************************************************************/
	/* Constructor and Destructor Definitions				                */
	/************************************************************************/
public:
	MainMenu();
	virtual ~MainMenu();

	/************************************************************************/
	/* Class functions										                */
	/************************************************************************/
public:
	virtual bool Initialize() override;											  /*!< Initialize all window data */
	virtual void Update(float _deltaTime) override;								  /*!< Updates the window */
	virtual void Render() override;												  /*!< Renders window info*/
	virtual void Destroy() override;											  /*!< Destroy all data of a window */
	virtual void ManageInputs(SDL_Event& pEvent) override;						  /*!< Manage the window inputs */
	virtual void SetMousePos(Point _mousePos) override;							  /*!< Sets the mouse position */
	virtual WindowState GetWindowChange() override;								  /*!< Returns the next window state */
	bool LoadResources();														  /*!< Load all necessary data */

private:
	Texture m_playButtonTexture;												/*!< Object to store a texture */
	Texture m_backGroundTexture;												/*!< Object to store a texture */
	Texture m_inputsTexture;													/*!< Object to store a texture */
	Point m_mousePos;															/*!< Mouse position */
	Rect m_playButton;															/*!< Rect of a texture */
	Rect m_backGround;															/*!< Rect of a texture */
	Rect m_inputs;																/*!< Rect of a texture */
	SDL_Color m_titleTextColor;													/*!< Color of title text */
	std::string m_strGameTitle;													/*!< String to store the title text */
	Point m_titlePos;															/*!< Position of the title in the screen */

private:
	bool CheckPointRectCollision(Rect& _rect, Point& _point);					/*!< Query if there are a point-rect collision */
};

