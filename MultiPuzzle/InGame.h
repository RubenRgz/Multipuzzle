/********************************************************************/
/**
* @LC	  2017/10/25
* @file   InGame.h
* @Author Rubén Rodríguez Serrano (rubn2113@gmail.com)
* @date   2017/10/16
* @brief  In Game Window
* @bug	  No known bugs.
*/
/********************************************************************/
#pragma once

/************************************************************************/
/* Includes												                */
/************************************************************************/
#include "BaseWindow.h"
#include "Texture.h"
#include <string.h>
#include <map>
#include <vector>
#include "Pieces.h"
#include "Board.h"
#include "Rect.h"


/************************************************************************/
/* Structs												                */
/************************************************************************/
enum BOARDS
{
	BOARD_1 = 0,
	BOARD_2,
	BOARD_3,
	BOARD_TOTALNUM
};



/************************************************************************/
/* InGame Class											                */
/************************************************************************/
class InGame :
	public BaseWindow
{
	/************************************************************************/
	/* Constructor and Destructor Definitions				                */
	/************************************************************************/
public:
	InGame();
	virtual ~InGame();

	/************************************************************************/
	/* Class functions										                */
	/************************************************************************/
public:
	virtual bool Initialize() override;											/*!< Initialize all window data */
	virtual void Update(float _deltaTime) override;								/*!< Updates the window */
	virtual void Render() override;												/*!< Renders window info*/
	virtual void Destroy() override;											/*!< Destroy all data of a window */
	virtual void ManageInputs(SDL_Event& pEvent) override;						/*!< Manage the window inputs */
	virtual void SetMousePos(Point _mousePos) override;							/*!< Sets the mouse position to all windows */
	virtual WindowState GetWindowChange() override;								/*!< Returns the next window state*/

private:
	bool LoadResources();														/*!< Load necessary resources */
	void SetActiveBoard(Board& _active);										/*!< Sets Active Board */
	void CopyInfoToBoard();														/*!< Copies piece info to board */
	void SwapBoard(int& _activeBoard);
	void CreatePieces();
	void DeletePenalty();														/*!< Delete the penalties in the board */
	void FallColumn(Point& _penaltyPos);										/*!< Fall the pieces above penalty erased */
	void UpdateScoreAndDeleteChances(int _num);

	/************************************************************************/
	/* Classs variables										                */
	/************************************************************************/
private:
	std::map<BLOCKCOLOR, MPColor> m_colorMap;									/*!< Map of all possible colors */
	std::vector<Board> m_vecBoards;
	Texture m_blockTexture;														/*!< Object to store a texture */
	Pieces m_pieces;															/*!< Object to create a piece */
	int m_iScore;																/*!< Variable to store the score */
	int m_iActiveBoard;															/*!< Variable to store the active board */
	Board* m_pActiveBoard;														/*!< Pointer to actual oard */
	Pieces m_nextPieces;														/*!< Object to create a piece (next piece to use) */
	bool m_bCreateNextPiece;													/*!< Boolean to check if a next piece is required */
	bool m_bCopyInfo;															/*!< Boolean to check if a copy of info pieces is necessary */
	Texture m_backGroundTexture;												/*!< Object to store the background texture */
	Rect m_backGround;															/*!< Rect of the texture */
	std::string m_strScore;														/*!< String that stores the score text to render */
	SDL_Color m_scoreColor;														/*!< Color of the score text  */
	int m_iLineMade;															/*!< Variable to store the lines made  */
	std::string m_strlinesMade;													/*!< String that stores the lines text to render */
	SDL_Color m_numLinesColor;													/*!< Color of the lines text  */
	std::vector<Penalty> m_vecPenalties;										/*!< Vector that stores penalties position of the boards*/
};

