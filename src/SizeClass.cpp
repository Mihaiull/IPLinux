#include "../include/SizeClass.h"

Size::Size()
{
	this->width = 0;
	this->height = 0;
}

Size::Size(int width, int height)
{
	this->width = width;
	this->height = height;
}

int Size::getWidth() const
{
	return this->width;
}

int Size::getHeight() const
{
	return this->height;
}

void Size::setWidth(int width)
{
	this->width = width;
}

void Size::setHeight(int height)
{
	this->height = height;
}

Size& Size::operator=(const Size& size)
{
	this->width = size.width;
	this->height = size.height;
	return *this;
}

bool Size::operator==(const Size& size) const
{
	return this->width == size.width && this->height == size.height;
}

bool Size::operator!=(const Size& size) const
{
	return this->width != size.width || this->height != size.height;
}




