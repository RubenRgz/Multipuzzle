/********************************************************************/
/**
* @LC	  2017/10/25
* @file   GameDefines.h
* @Author Rubén Rodríguez Serrano (rubn2113@gmail.com)
* @date   2017/10/16
* @brief  This class contains definitions that all clases related with the game needs
* @bug	  No known bugs.
*/
/********************************************************************/
#pragma once

/************************************************************************/
/* Defines												                */
/************************************************************************/
#define BLOCK_SIZE 20																			/*!< Size of block to render */
#define PIECE_COLUMS 5																			/*!< Piece max columns size */
#define PIECE_ROWS 5																			/*!< Piece max rows size */
#define INIT_WORLD_PIECE_POSX 2
#define INIT_WORLD_PIECE_POSY -1


/************************************************************************/
/* Enums												                */
/************************************************************************/
enum BLOCKCOLOR																					/*!< All available colors in the game */
{
	BC_NONE = 0,
	BC_RED,
	BC_BLUE,
	BC_GREEN,
	BC_TOTALNUM
};

enum PIECETYPE																					/*!< All kind of pieces */
{
	PT_SQUARE = 0,
	PT_LINE,
	PT_L,
	PT_L_MIRRORED,
	PT_N,
	PT_N_MIRRORED,
	PT_T,
	PT_TOTALNUM
};

/************************************************************************/
/* Structures											                */
/************************************************************************/
struct MPColor																					/*!< Struct to store colors from the blocks */
{
	int r, g, b;

	MPColor(int x = 0, int y = 0, int z = 0) : r(x), g(y), b(z) {}
};

struct Penalty																					/*!< Info of a penalty */
{
	Point pos;
	int board;
};