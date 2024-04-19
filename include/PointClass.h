#pragma once

class Point
{
public:
	Point();
	Point(int x, int y);
	~Point();
	int getX() const;
	int getY() const;
	void setX(int x);
	void setY(int y);
private:
	int x;
	int y;
};