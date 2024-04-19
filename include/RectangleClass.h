#pragma once

class Rectangle
{
public:
	Rectangle();
	Rectangle(int x, int y, int width, int height);
	~Rectangle();
	int getX();
	int getY();
	int getWidth();
	int getHeight();
	void setX(int x);
	void setY(int y);
	void setWidth(int width);
	void setHeight(int height);

private:
	int x;
	int y;
	int width;
	int height;

};