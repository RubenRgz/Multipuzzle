/********************************************************************/
/**
* @LC	  2017/10/19
* @file   Rect.h
* @Author Rubén Rodríguez Serrano (rubn2113@gmail.com)
* @date   2017/10/19
* @brief  Simple rect class
* @bug	  No known bugs.
*/
/********************************************************************/
#pragma once

/************************************************************************/
/* Rect Class											                */
/************************************************************************/
class Rect
{
	/************************************************************************/
	/* Declaracion de contructores y destructor                             */
	/************************************************************************/
public:
	explicit Rect(const int& _X = 0, const int& _Y = 0, 
				  const unsigned int& _Width = 0, const unsigned int& _Height = 0) :
				  X(_X), Y(_Y), m_Width(_Width), m_Height(_Height) {};							/*!< Constructor */
	
	Rect(const Rect& _Rect) { _Rect; };																	/*!< Copy Constructor */
	~Rect() {};																					/*!< Destructor */
	/************************************************************************/
	/* Classs variables										                */
	/************************************************************************/
public:
	int X;																						/*!< X Position */
	int Y;																						/*!< Y Position */
	unsigned int m_Width;																		/*!< Rect width */
	unsigned int m_Height;																		/*!< Rect height */

	/************************************************************************/
	/* Operator overloading		                                            */
	/************************************************************************/
public:
	bool operator ==	(const Rect& _Rect);													/*!< Rect comparations */
	bool operator !=	(const Rect& _Rect);													/*!< CRect comparations */
};
