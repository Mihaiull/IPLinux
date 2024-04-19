#include "../include/RectangleClass.h"

Rectangle::Rectangle() {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
}

Rectangle::Rectangle(int x, int y, int width, int height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

Rectangle::~Rectangle() {
	delete this;
}

int Rectangle::getX() {
	return this->x;
}

int Rectangle::getY() {
	return this->y;
}

int Rectangle::getWidth() {
	return this->width;
}

int Rectangle::getHeight() {
	return this->height;
}

void Rectangle::setX(int x) {
	this->x = x;
}

void Rectangle::setY(int y) {
	this->y = y;
}

void Rectangle::setWidth(int width) {
	this->width = width;
}

void Rectangle::setHeight(int height) {
	this->height = height;
}



