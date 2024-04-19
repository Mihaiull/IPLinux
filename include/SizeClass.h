#pragma once

class Size {
public:
	Size();
	Size(int width, int height);
	int getWidth() const;
	int getHeight() const;
	void setWidth(int width);
	void setHeight(int height);
	Size& operator=(const Size& size);
	bool operator==(const Size& size) const;
	bool operator!=(const Size& size) const;
private:
	int width;
	int height;
};