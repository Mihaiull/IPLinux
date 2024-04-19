#include "../include/ImageClass.h"
#include "../include/ImageProcessing.h"
#include <iostream>
#include "../include/UI.h"

using std::cout;
using std::cin;

void printMenu() {
	cout << "1.Load Image\n2.Save Image\n3.Change Brightness\n4.Change Gamma\n5.Image Convolution Module\n6.Drawing Module\nYour option: ";
}

void imageConvolutionMenu() {
	cout << " 1.Choose Kernel\n 2.Apply Kernel\n 3.Go back\nYour option: ";
}

void imageConvolutionKernelMenu() {
	cout << " Choose one of the following:\n 1.3x3 Identity\n 2.Mean Blur\n 3.3x3 Edge Detection\n 4.3x3 Gaussian Blur\n 5.Horizontal Sobel\n 6.Vertical Sobel\nYour Option: ";
}

void DrawingMenu() {
	cout << " 1.Draw Line\n 2.Draw Circle\n 3.Draw Rectangle\n 4.Go back\nYour Option: ";
}

Image img = Image();

void UI(unsigned int option) {

	switch(option) {
		case 1:
		{
			//cout<<"Enter the path of the image file: ";
			string path;
			//cin>>path;
			path = "samples/load/sample.pgm";
			img.load(path);
			cout<<"Image loaded successfully!\n";
			cout<<"Image size: "<<img.size().getWidth()<<"x"<<img.size().getHeight()<<'\n';
			break;
		}
		case 2:
		{
			cout<<"Enter the path of the image file: ";
			string path;
			cin>>path;
			img.save(path);
			break;
		}
		case 3:
		{
			Brightness b;
			b.process(img, img);
			break;
		}
		case 4:
		{
			GammaCorrection g;
			g.process(img, img);
			break;
		}
		case 5:
		{
			ImageConvolution ic;
			imageConvolutionMenu();
			int option2;
			cin>>option2;
			switch (option2) {
				case 1:
				{
					imageConvolutionKernelMenu();
					unsigned int option;
					cin>>option;
					ic.setKernel(option);
					break;
				}
				case 2:
				{
					ic.process(img, img);
					break;
				}
				case 3:
				{
					break;
				}
			}
			break;
		}
		case 6:
		{
			DrawingModule dm;
			DrawingMenu();
			int option3;
			cin>>option3;
			switch (option3) {
				case 1:
				{
					int startx, starty, endx, endy;
					cout<<"Enter the start point(x,y): ";
					cin>>startx>>starty;
					Point start(startx, starty);
					cout<<"Enter the end point(x,y): ";
					cin>>endx>>endy;
					Point end(endx, endy);
					dm.drawLine(img, start, end, 255);
					break;
				}
				case 2:
				{
					int x, y, radius;
					cout<<"Enter the center of the circle(x,y): ";
					cin >> x >> y;
					cout<<"Enter the radius of the circle(x,y): ";
					cin>>radius;
					Point center(x, y);
					dm.drawCircle(img, center, radius, 0);
					break;
				}
				case 3:
				{
					int topx, topy, bottomx, bottomy;
					cout<<"Enter the top left point of the rectangle(x,y): ";
					cin>>topx>>topy;
					Point topLeft(topx, topy);
					cout<<"Enter the bottom right point of the rectangle(x,y): ";
					cin>>bottomx>>bottomy;
					Point bottomRight(bottomx, bottomy);
					dm.drawRectangle(img, topLeft, bottomRight, 255);
					break;
				}
				case 4:
				{
					break;
				}
			}
			break;
		}
	}
}