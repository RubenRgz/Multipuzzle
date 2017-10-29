/********************************************************************/
/**
* @LC	  2017/10/18
* @file   Point.h
* @Author Rubén Rodríguez Serrano (rubn2113@gmail.com)
* @date   2017/10/16
* @brief  It´s a simple point in 2D
* @bug	  No known bugs.
*/
/********************************************************************/
#pragma once

/************************************************************************/
/* Point Class											                */
/************************************************************************/
class Point
{
public:
	explicit Point(const int& _X = 0, const int& _Y = 0) :
		X(_X), Y(_Y) {};														/*!< Constructor with variables */
	Point(const Point& _Point);													/*!< Constructor with Point */
	~Point();																	/*!< Destructor */

												
public:
	int X;																		/*!< X value of the point */
	int Y;																		/*!< Y value of the point */

/************************************************************************/
/* Operator overloading                                                 */
/************************************************************************/
public:
	bool operator ==	(const Point& _Point);
	bool operator !=	(const Point& _Point);
};


