#include "../include/PointClass.h"

Point::Point()
{
	this->x = 0;
	this->y = 0;
}

Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}

Point::~Point()
{
	delete this;
}

int Point::getX() const
{
	return this->x;
}

int Point::getY() const
{
	return this->y;
}

void Point::setX(int x)
{
	this->x = x;
}

void Point::setY(int y)
{
	this->y = y;
}
