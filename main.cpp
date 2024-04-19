#include <iostream>
#include <string>
#include "include/ImageClass.h"
#include "include/SizeClass.h"
#include "include/PointClass.h"
#include "include/RectangleClass.h"
#include "include/UI.h"

using namespace std;

int main() {
	unsigned int option;
	cout<< "Welcome to the Image Processing Application!\n";
	printMenu();
	UI(1);
	while (cin >> option) {
		if (option == 0) {
			cout << "Ceaw Ceaw\n";
			break;
		}
		UI(option);
		printMenu();
	}
	return 0;
}