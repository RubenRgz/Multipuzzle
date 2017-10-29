#include "Point.h"



Point::Point(const Point & _Point)
{
	X = _Point.X;
	Y = _Point.Y;
}

Point::~Point()
{
}

bool Point::operator==(const Point & _Point)
{
	if (X == _Point.X && Y == _Point.Y)
	{
		return true;
	}
	return false;
}

bool Point::operator!=(const Point & _Point)
{
	if (X != _Point.X || Y != _Point.Y)
	{
		return true;
	}
	return false;
}
