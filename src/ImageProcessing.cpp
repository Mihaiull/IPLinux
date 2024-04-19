#include "../include/ImageProcessing.h"
#include "../include/ImageClass.h"
#include "../include/SizeClass.h"
#include "../include/PointClass.h"
#include "../include/RectangleClass.h"
#include <iostream>
#include <cmath>
#define CRT_SECURE_NO_WARNINGS

using namespace std; //pentru ca dintr-un motiv sau altul la momentul scrierii codului am uitat ca input-u si outputu se face in ui si l-am facut direct in functii sunt un geniu ce pot sa zic


void ImageProcessing::process(const Image& src, Image& dst)
{
		cout << "Processing image..." << endl;
		cout << "Source image size: " << src.size().getWidth() << "x" << src.size().getHeight() << endl;
		cout<<"You should not be here!"<<endl;
}

void Brightness::process(const Image& src, Image& dst)
{
	cout << "Applying brightness filter..." << endl;
	cout << "Source image size: " << src.size().getWidth() << "x" << src.size().getHeight() << endl;
	float alpha = 0.0, beta = 0.0;
	cout<< "Enter alpha and beta values: ";
	cin >> alpha;
	cin >> beta;
	for (int i = 0; i < src.size().getHeight(); i++)
	{
		for (int j = 0; j < src.size().getWidth(); j++)
		{
			dst.setPixel(i, j, alpha * src.getPixel(i, j) + beta);
		}
	}
}

//Does not work as intended, but it does some really cool shit
// void Brightness::process(const Image& src, Image& dst)
// {
// 	cout << "Applying brightness filter..." << endl;
// 	cout << "Source image size: " << src.size().getWidth() << "x" << src.size().getHeight() << endl;
// 	float alpha = 0.0, beta = 0.0;
// 	cout<< "Enter alpha and beta values: ";
// 	cin >> alpha;
// 	cin >> beta;
// 	for (int i = 0; i < src.size().getHeight(); i++)
// 	{
// 		for (int j = 0; j < src.size().getWidth(); j++)
// 		{
// 			dst.setPixel(i, j, alpha * src.getPixel(i, j) + beta);
// 		}
// 	}
// }

void GammaCorrection::process(const Image& src, Image& dst)
{
	float gamma = 0.0;
	cout << "Enter gamma value: ";
	//gamma should be between 
	cin >> gamma;
	cout << "Applying gamma correction filter..." << endl;
	for (int i = 0; i < src.size().getHeight(); i++)
	{
		for (int j = 0; j < src.size().getWidth(); j++)
		{
			uint corrected;
			corrected = pow(src.getPixel(i, j), gamma);
			dst.setPixel(i, j, corrected);
		}
	}
}

void ImageConvolution::setKernel(int value)
{
	switch (value)
	{
	case 1: //identity
	{
		kernel[0][0] = 0; kernel[0][1] = 0; kernel[0][2] = 0;
		kernel[1][0] = 0; kernel[1][1] = 1; kernel[1][2] = 0;
		kernel[2][0] = 0; kernel[2][1] = 0; kernel[2][2] = 0;
		this->option = 0;
		break;
	}
	case 2: //mean blur
	{
		kernel[0][0] = 1; kernel[0][1] = 1; kernel[0][2] = 1;
		kernel[1][0] = 1; kernel[1][1] = 1; kernel[1][2] = 1;
		kernel[2][0] = 1; kernel[2][1] = 1;	kernel[2][2] = 1;
		this->option= 1;
		break;
	}
	case 3: //3x3 gaussean blur
	{
		kernel[0][0] = 1; kernel[0][1] = 2; kernel[0][2] = 1;
		kernel[1][0] = 2; kernel[1][1] = 4; kernel[1][2] = 2;
		kernel[2][0] = 1; kernel[2][1] = 2; kernel[2][2] = 1;
		this->option= 2;
		break;
	}
	case 4: //horizontal sobel
	{
		kernel[0][0] = 1; kernel[0][1] = 2; kernel[0][2] = 1;
		kernel[1][0] = 0; kernel[1][1] = 0; kernel[1][2] = 0;
		kernel[2][0] = -1; kernel[2][1] = -2; kernel[2][2] = -1;
		this->option= 0;
		break;
	}
	case 5: //vertical sobel
	{
		kernel[0][0] = 1; kernel[0][1] = 0; kernel[0][2] = -1;
		kernel[1][0] = 2; kernel[1][1] = 0; kernel[1][2] = -2;
		kernel[2][0] = 1; kernel[2][1] = 0; kernel[2][2] = -1;
		this->option= 0;
		break;
	}
	default:
	{
		cout << "Invalid option!" << endl;
		break;
	}
	}

}


void ImageConvolution::process(const Image & src, Image & dst)
{
	cout << "Applying image convolution filter..." << endl;
	cout << "Source image size: " << src.size().getWidth() << "x" << src.size().getHeight() << endl;
	for (int i = 0; i < src.size().getHeight(); i++)
	{
		for (int j = 0; j < src.size().getWidth(); j++)
		{
			double sum = 0;
			for (int k = 0; k < 3; k++)
			{
				for (int l = 0; l < 3; l++)
				{
					uint height, width;
					//take your meds before reading this next part
					if(i+k < src.size().getHeight())
						height = i + k;
					else if (i+k == src.size().getHeight())
						height = src.size().getHeight() - 1;
					else if (i+k-1 == src.size().getHeight())
						height = src.size().getHeight() - 2;
					else if (i+k-2 == src.size().getHeight())
						height = src.size().getHeight() - 3;

					if(j+l < src.size().getWidth())
						width = j + l;
					else if (j+l == src.size().getWidth())
						width = src.size().getWidth() - 1;
					else if (j+l-1 == src.size().getWidth())
						width = src.size().getWidth() - 2;
					else if (j+l-2 == src.size().getWidth())
						width = src.size().getWidth() - 3;
					
					switch(this->option)
					{
						case 1:
						{
							sum += 1/9.0*(src.getPixel(height, width) * kernel[k][l]);
							break;
						}
						case 2:
						{
							sum+= 1/16.0*(src.getPixel(height, width) * kernel[k][l]);
							break;
						}
						case 0:
						{
							sum+= src.getPixel(height, width) * kernel[k][l];
							break;
						}
					}
					
				}
			}
			dst.setPixel(i, j, sum);
		}
	}
}

void DrawingModule::setColor(int option)
{
	switch (option)
	{
	case 1:
	{
		cout << "Color: Black" << endl;
		break;
	}
	case 2:
	{
		cout << "Color: White" << endl;
		break;
	}
	default:
	{
		cout << "Invalid option!" << endl;
		break;
	}
	}
}

void DrawingModule::drawCircle(Image& img, Point center, int radius, unsigned char color) const
{
	cout << "Drawing circle..." << endl;
	cout << "Center: (" << center.getX() << ", " << center.getY() << ")" << endl;
	cout << "Radius: " << radius << endl;
	cout << "Color: " << static_cast<int>(color) << endl;
	if (radius <= 0)
	{
		cout << "Invalid radius!" << endl;
		return;
	}
	for (int i = 0; i < img.size().getHeight(); i++)
	{
		for (int j = 0; j < img.size().getWidth(); j++)
		{
			if ((i - center.getX()) * (i - center.getX()) + (j - center.getY()) * (j - center.getY()) <= radius * radius) //didn't have cmath included
			{
				img.setPixel(i, j, color);
			}
		}
	}
}

void DrawingModule::drawLine(Image& img, Point start, Point end, unsigned char color) const
{
	cout << "Drawing line..." << endl;
	cout << "Start: (" << start.getX() << ", " << start.getY() << ")" << endl;
	cout << "End: (" << end.getX() << ", " << end.getY() << ")" << endl;
	cout << "Color: " << static_cast<int>(color) << endl;
	if (start.getX() == end.getX() && start.getY() == end.getY())
	{
		cout << "Invalid line!" << endl;
		return;
	}
	int dx = end.getX() - start.getX();
	int dy = end.getY() - start.getY();
	if (abs(dx) > abs(dy))
	{
		if (start.getX() > end.getX())
		{
			swap(start, end);
		}
		for (int i = start.getX(); i <= end.getX(); i++)
		{
			int j = start.getY() + dy * (i - start.getX()) / dx;
			img.setPixel(i, j, color);
		}
	}
	else
	{
		if (start.getY() > end.getY())
		{
			swap(start, end);
		}
		for (int j = start.getY(); j <= end.getY(); j++)
		{
			int i = start.getX() + dx * (j - start.getY()) / dy;
			img.setPixel(i, j, color);
		}
	}
}

void DrawingModule::drawRectangle(Image& img, Rectangle rect, unsigned char color) const
{
	cout << "Drawing rectangle..." << endl;
	cout << "Top-left: (" << rect.getX() << ", " << rect.getY() << ")" << endl;
	cout << "Bottom-right: (" << rect.getX() + rect.getWidth() << ", " << rect.getY() + rect.getHeight() << ")" << endl;
	cout << "Color: " << static_cast<int>(color) << endl;
	if (rect.getWidth() <= 0 || rect.getHeight() <= 0)
	{
		cout << "Invalid rectangle!" << endl;
		return;
	}
	for (int i = rect.getX(); i < rect.getX() + rect.getWidth(); i++)
	{
		img.setPixel(i, rect.getY(), color);
		img.setPixel(i, rect.getY() + rect.getHeight() - 1, color);
	}
	for (int j = rect.getY(); j < rect.getY() + rect.getHeight(); j++)
	{
		img.setPixel(rect.getX(), j, color);
		img.setPixel(rect.getX() + rect.getWidth() - 1, j, color);
	}
}

void DrawingModule::drawRectangle(Image& img, Point topLeft, Point bottomRight, unsigned char color) const
{
	cout << "Drawing rectangle..." << endl;
	cout << "Top-left: (" << topLeft.getX() << ", " << topLeft.getY() << ")" << endl;
	cout << "Bottom-right: (" << bottomRight.getX() << ", " << bottomRight.getY() << ")" << endl;
	cout << "Color: " << static_cast<int>(color) << endl;
	if (topLeft.getX() >= bottomRight.getX() || topLeft.getY() >= bottomRight.getY())
	{
		cout << "Invalid rectangle!" << endl;
		return;
	}
	for (int i = topLeft.getX(); i <= bottomRight.getX(); i++)
	{
		img.setPixel(i, topLeft.getY(), color);
		img.setPixel(i, bottomRight.getY(), color);
	}
	for (int j = topLeft.getY(); j <= bottomRight.getY(); j++)
	{
		img.setPixel(topLeft.getX(), j, color);
		img.setPixel(bottomRight.getX(), j, color);
	}
}