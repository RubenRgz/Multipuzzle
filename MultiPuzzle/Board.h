/********************************************************************/
/**
* @LC	  2017/10/25
* @file   Board.h
* @Author Rubén Rodríguez Serrano (rubn2113@gmail.com)
* @date   2017/10/16
* @brief  This class manage the board
* @bug	  No known bugs.
*/
/********************************************************************/
#pragma once

/************************************************************************/
/* Includes												                */
/************************************************************************/
#include "Point.h"
#include "GameDefines.h"
#include "Texture.h"
#include <map>
#include "Pieces.h"
#include <list>
#include <vector>

/************************************************************************/
/* Defines												                */
/************************************************************************/	
#define BOARD_COLUMS 10																	/*!< Board max columns size */
#define BOARD_ROWS 20																	/*!< Board max rows size */

/************************************************************************/
/* Board Class											                */
/************************************************************************/
class Board
{
	/************************************************************************/
	/* Constructor and Destructor Definitions				                */
	/************************************************************************/
public:
	Board();																			/*!< Standrad Constructor */
	virtual ~Board();																	/*!< Standrad Destructor */

	/************************************************************************/
	/* Class functions										                */
	/************************************************************************/
public:
	void Create(BLOCKCOLOR& _color, Point& _position);									/*!< Creates a board */
	BLOCKCOLOR* GetBaseColor();															/*!< Returns base color board for logic game */
	Point* GetPos();																	/*!< Returns board screen position */
	void Update();																		/*!< Upfates board info */
	void Render(Texture& _texture, std::map<BLOCKCOLOR, MPColor>& _colorMap);			/*!< Render the blocks of a board */
	void Destroy();																		/*!< Destroy all data used */
	void SetPiece(Pieces& _piece);														/*!< Sets an actual piece reference */
	void PutPenalty(BLOCKCOLOR& _color, std::vector<Penalty>& _vecPenalties, 
					int& _activeBoatd);													/*!< Puts a penalty in the actual board */
	int  CheckInputCollisions();														/*!< Check input collision */
	void CheckLine();																	/*!< Checks if a line is made in the board */
	bool CheckGameOver();																/*!< Check Game Over */
	void ResetCounterLines();															/*!< Resets the counter of lines made */
	int* GetCounteLines();																/*!< Returns the num of lines made */

private:
	bool CheckGameCollisions();															/*!< Check game collisions */
	void DeleteLine(int _initRow);														/*!< Delete the complete lines */
	


	/************************************************************************/
	/* Classs variables										                */
	/************************************************************************/
public:
	int m_matrix[BOARD_ROWS][BOARD_COLUMS] = { 0 };										/*!< board matrix */
	bool m_bDeletedLines;																/*!< Boolean to check if there are a lines to delete */
	bool m_bIncorrectPieceColor;														/*!< Boolean to check if there is an incorrect piece in the board */
	bool m_bLeftBoardCollision;															/*!< Boolean to check if there is a left collision */
	bool m_bRightBoardCollision;														/*!< Boolean to check if there is a right collision */
	bool m_bBelowBoardCollision;														/*!< Boolean to check if there is a below board collision */
	bool m_bBelowCollision;																/*!< Boolean to check if there is a bleow piece collision */
	bool m_bTopCollision;																/*!< Boolean to check if there is a top collision */
	

private:
	Point m_position;																	/*!< Object to store board position */
	BLOCKCOLOR m_color;																	/*!< Enum to store board base color */									
	Pieces* m_pPiece;																	/*!< Pointer to actual Piece */
	int m_iLinesCounter;																/*!< Counter of lines made */
};

