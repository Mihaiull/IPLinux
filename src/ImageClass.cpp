#include "../include/ImageClass.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>
uint PIXELRANGE = 220;

Image::Image() {
	this->m_height = 0;
	this->m_width = 0;
	this->m_data = new char* [0];
}

Image::Image(unsigned int width, unsigned int height) {
	this->m_height = height;
	this->m_width = width;
	for (int i = 0; i < this->m_height; i++) {
		this->m_data[i] = new char[this->m_width];
		for (int j = 0; j < this->m_width; j++) {
			this->m_data[i][j] = 0;
		}
	}
}

Image::Image(const Image& img) {
	this->m_height = img.m_height;
	this->m_width = img.m_width;
	for (int i = 0; i < 10; i++) {
		this->m_data[i] = new char[img.m_height * img.m_width];
		memcpy(this->m_data[i], img.m_data[i], img.m_height);
	}
}

Image& Image::operator=(const Image& img) {
	if (this != &img) {
		this->m_height = img.m_height;
		this->m_width = img.m_width;
		for (int i = 0; i < 10; i++) {
			delete[] this->m_data[i];
			this->m_data[i] = new char[img.m_height * img.m_width];
			memcpy(this->m_data[i], img.m_data[i], static_cast<size_t>(img.m_height * img.m_width));
		}
	}
	return *this;
}

Image::~Image()
{
	Image::release();
}

void Image::release() {
	for (int i = 0; i < this->m_height; i++){
		delete[] this->m_data[i];
	}
}

Image Image::zeros(unsigned int width, unsigned int height) {
	Image img(width, height);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			img.setPixel(i, j, 0);
		}
	}
	return img;
}

Image Image::ones(unsigned int width, unsigned int height) {
	Image img(width, height);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			img.setPixel(i, j, 1);
		}
	}
	return img;
}



bool Image::getROI(Image& roiImg, Rectangle roiRect) {
	if (roiRect.getX() + roiRect.getWidth() > this->m_width || roiRect.getY() + roiRect.getHeight() > this->m_height) {
		return false;
	}
	roiImg.m_height = roiRect.getHeight();
	roiImg.m_width = roiRect.getWidth();
	for (int i = 0; i < roiImg.getHeight(); i++) {
		roiImg.m_data[i] = new char[roiImg.getWidth()];
	}

	for (int i = 0; i < roiRect.getHeight(); i++) {
		for (int j = 0; j < roiRect.getWidth(); j++) {
			roiImg.setPixel(i,j, this->m_data[i + roiRect.getY()][j + roiRect.getX()]);
		}
	}
	return true;
}

bool Image::getROI(Image& roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	if (x + width > this->m_width || y + height > this->m_height) {
		return false;
	}
	roiImg.m_height = height;
	roiImg.m_width = width;
	for (int i = 0; i < 10; i++) {
		roiImg.m_data[i] = new char[height * width];
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			roiImg.m_data[i][j] = this->m_data[i + y][j + x];
		}
	}
	return true;
}

bool Image::isEmpty() const {
	return this->m_height == 0 && this->m_width == 0 && this->m_data[0] == nullptr;
}

Size Image::size() const {
	Size size;
	size.setHeight(this->m_height);
	size.setWidth(this->m_width);
	return size;
}

unsigned int Image::getWidth() const {
	return this->m_width;
}
unsigned int Image::getHeight() const {
	return this->m_height;
}

// unsigned char& Image::at(unsigned int x, unsigned int y) {
// 	return this->m_data[x][y];
// }
// unsigned char& Image::at(Point pt) {
// 	return this->m_data[pt.getX()][pt.getY()];
// }

// unsigned char* Image::row(int y) {
// 	return this->m_data[y];
// }

bool Image::load(std::string imagePath) {
	std::string extension = imagePath.substr(imagePath.length() - 3);		
	if (extension != "pgm") {
	std::cerr << "Error: Invalid file extension!" << std::endl;
	return false;
	}

	std::ifstream file(imagePath);
	if (!file.is_open()) {
		std::cerr << "Error opening the file!" << std::endl;
		return false;
	}

	// Get the first line that must contain magic number
	std::string primalinie="";
	std::getline(file, primalinie);
	if (primalinie != "P5" && primalinie != "P2") {
		std::cerr << "Error: Invalid magic number!" << std::endl;
		return false;
	}

	// Ignore comments
	while (file.peek() == '#') {
		file.ignore(256, '\n');
	}

	// Get the size of the image
	std::stringstream ss;
	ss << file.rdbuf();
	ss>>m_width>>m_height;
	// Get the maximum value of the image
	unsigned int maxVal;
	ss >> maxVal;
	if(maxVal>255){
		std::cerr<<"Error: Invalid maximum value!"<<std::endl;
		return false;
	}
	
	m_data = new char* [m_height];
	for (uint i = 0; i < m_height; i++) {
		m_data[i] = new char[m_width];
		for (int j = 0; j < m_width; j++) {
			uint d;
			ss >> d;
			if (d > PIXELRANGE) {
				m_data[i][j] = static_cast<uint>(PIXELRANGE);
			}
			m_data[i][j] = d;
		}
	}
	file.close();
	return true;
}



//bool Image::load(std::string imagePath) {
//	std::string extension = imagePath.substr(imagePath.length() - 3);
//	if (extension != "pgm") {
//		std::cerr << "Error: Invalid file extension!" << std::endl;
//		return false;
//	}
//
//	std::ifstream file(imagePath);
//	if (!file.is_open()) {
//		std::cerr << "Error opening the file!" << std::endl;
//		return false;
//	}
//
//	// Get the first line that must contain magic number
//	std::string primalinie="";
//	std::getline(file, primalinie);
//	if (primalinie != "P5" && primalinie != "P2") {
//		std::cerr << "Error: Invalid magic number!" << std::endl;
//		return false;
//	}
//
//	// Ignore comments
//	while (file.peek() == '#') {
//		file.ignore(256, '\n');
//	}
//
//	// Get the size of the image
//	unsigned int width, height;
//	file >> width >> height;
//
//	// Get the maximum value of the image
//	unsigned int maxVal;
//	file >> maxVal;
//
//	this->m_data = new char* [height];
//	for (unsigned int i = 0; i < height; i++) {
//		this->m_data[i] = new char[width];
//		for (unsigned int j = 0; j < width; j++) {
//			// convert the value to an unsigned char
//			unsigned char d;
//			file >> d;
//			this->m_data[i][j] = d;
//		}
//	}
//	m_width = width;
//	m_height = height;
//
//	file.close();
//	return true;
//}

bool Image::save(std::string imagePath) const {
	std::string extension = imagePath.substr(imagePath.length() - 3);
	if (extension != "pgm") {
		std::cerr << "Error: Invalid file extension!" << std::endl;
		std::cerr << "Got: " << extension << " Expected: pgm" << std::endl;
		return false;
	}

	std::ofstream file(imagePath, std::ios::app);
	if (!file.is_open()) {
		std::cerr << "Error opening the file!" << std::endl;
		std::cerr << "The file may not exist or the path is invalid" << std::endl;
		std::cerr << "Please check the path and try again" << std::endl;
		std::cerr << "The path: " << imagePath << std::endl;
		return false;
	}

	// Write p5
	file << "P2" << std::endl;

	// Write a comment
	file << "# Image: " << imagePath << "  saved" << std::endl;

	// Write the size of the image
	file << this->m_width << " " << this->m_height << std::endl;

	// Write the maximum value of the image
	file << PIXELRANGE << std::endl;

	// Write the data
	for (unsigned int i = 0; i < m_height; i++) {
		for (unsigned int j = 0; j < m_width; j++) {
			if (m_data[i][j] > PIXELRANGE) {
				file << static_cast<uint>(PIXELRANGE) << " ";
			}
			else
				file << static_cast<uint>((m_data[i][j]))<<" ";
		}
		file << '\n';
	}
	std::cout << "Image saved successfully!" << std::endl;
	file.close();
	return true;
}

Image Image::operator+(const Image& img) {
	if (this->m_height != img.m_height || this->m_width != img.m_width) {
		throw std::invalid_argument("Images have different sizes");
	}
	Image result(this->m_width, this->m_height);
	for (int i = 0; i < this->m_height; i++) {
		for (int j = 0; j < this->m_width; j++) {
			result.m_data[i][j] = this->m_data[i][j] + img.m_data[i][j];
		}
	}
	return result;
}

Image Image::operator-(const Image& img) {
	if (this->m_height != img.m_height || this->m_width != img.m_width) {
		throw std::invalid_argument("Images have different sizes");
	}
	Image result(this->m_width, this->m_height);
	for (int i = 0; i < this->m_height; i++) {
		for (int j = 0; j < this->m_width; j++) {
			result.m_data[i][j] = this->m_data[i][j] - img.m_data[i][j];
		}
	}
	return result;
}

Image Image::operator*(double s) {
	Image result(this->m_width, this->m_height);
	for (int i = 0; i < this->m_height; i++) {
		for (int j = 0; j < this->m_width; j++) {
			result.m_data[i][j] = static_cast<unsigned char>(this->m_data[i][j] * s);
		}
	}
	return result;
}

std::ostream& operator<<(std::ostream& os, const Image& dt)
{
	os << "Image: " << dt.m_width << "x" << dt.m_height << std::endl;
	for (int i = 0; i < dt.m_height; i++) {
		for (int j = 0; j < dt.m_width; j++) {
			os << static_cast<int>(dt.m_data[i][j])<<" ";
		}
		os <<"\n";
	}
	return os;
}

// std::istream& operator>>(std::istream& is, Image& dt)
// {
// 	std::string line;
// 	std::getline(is, line);
// 	if (line != "P2") {
// 		return is;
// 	}
// 	std::getline(is, line);
// 	while (line[0] == '#') {
// 		std::getline(is, line);
// 	}
// 	std::string width, height;
// 	std::stringstream ss(line);
// 	ss >> width >> height;
// 	dt.m_width = std::stoi(width);
// 	dt.m_height = std::stoi(height);
// 	for (int i = 0; i < 10; i++) {
// 		dt.m_data[i] = new char[dt.m_height * dt.m_width];
// 	}
// 	std::getline(is, line);
// 	for (int i = 0; i < dt.m_height; i++) {
// 		for (int j = 0; j < dt.m_width; j++) {
// 			is >> dt.m_data[i][j];
// 		}
// 	}
// 	return is;
// }

void Image::setPixel(unsigned int x, unsigned int y, unsigned char value) {
	this->m_data[x][y] = value;
}

unsigned char Image::getPixel(unsigned int x, unsigned int y) const {
	return this->m_data[x][y];
}