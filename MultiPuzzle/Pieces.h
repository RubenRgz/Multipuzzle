/********************************************************************/
/**
* @LC	  2017/10/25
* @file   Pieces.h
* @Author Rubén Rodríguez Serrano (rubn2113@gmail.com)
* @date   2017/10/16
* @brief  This class manage the pieces
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

/************************************************************************/
/* Enums												                */
/************************************************************************/
enum POSORIENTATION																				/*!< Piece orientation */
{
	PO_0 = 0,
	PO_1,
	PO_2,
	PO_3,
	PO_TOTALNUM
};


/************************************************************************/
/* Piece Class											                */
/************************************************************************/
class Pieces
{
	/************************************************************************/
	/* Constructor and Destructor Definitions				                */
	/************************************************************************/
public:	
	Pieces();																					/*!< Standrad Constructor */
	virtual ~Pieces();																			/*!< Standrad Destructor */

	/************************************************************************/
	/* Class functions										                */
	/************************************************************************/
public:
	void Create(PIECETYPE& _type, BLOCKCOLOR& _color, Point& _initPos, Point& _worldPos);		/*!< Creates a piece */
	void RotateLeft();																			/*!< Rotate a piece to the left */
	void RotateRight();																			/*!< Rotate a piece to the right */
	bool IsCreated();																			/*!< Query if the piece has been created */
	void Update();																				/*!< Updates all piece data */
	void Render(Texture& _texture, std::map<BLOCKCOLOR, MPColor>& _colorMap);					/*!< Render the blocks of a piece */
	void Destroy();																				/*!< Destroy all data used */
	BLOCKCOLOR* GetColor();																		/*!< Returns the piece color */
	PIECETYPE* GetType();																		/*!< Returns type piece*/
	bool IsActive();																			/*!< Query if a piece is active */
	void SetIsActive(bool _active);																/*!< Sets the actual piece as active */
	void SetWorldPos(Point& _boardPos, Point& _movementPice);

	/************************************************************************/
	/* Classs variables										                */
	/************************************************************************/
public:
	int m_matrix[PIECE_ROWS][PIECE_COLUMS] = { 0 };												/*!< Piece matrix */
	Point m_position;																			/*!< Piece position */
	
private:
	BLOCKCOLOR m_color;																			/*!< Enum to store piece color */
	PIECETYPE m_type;																			/*!< Enum to store piece type */
	static int m_rotatePos;																		/*!< Variable to know what rotation continues */
	bool m_bIsCreated;																			/*!< Boolean to know if a piece has been created */
	bool m_bActive;																				/*!< Boolean to check if a piece is active */
};

