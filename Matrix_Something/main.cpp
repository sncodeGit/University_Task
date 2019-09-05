#include <iostream>
#include "m_matrix.hpp"

using namespace std;

void show_hint() {
	cout << endl << "To select an action, press one of the following keys:" << endl;
	cout << "1 - get element value, 2 - swap two rows, 3 - multiply matrix row," << endl;
	cout << "4 - Execute a linear combination of two rows, 5 - get vector row/column," << endl;
	cout << "6 - show matrix, 0 - exit" << endl;
	cout << "To call this prompt again, press '?'" << endl;
}

int main() {
	size_t height = 0, width = 0;
	char choice = 1;

	cout << "Welcome to the matrix tester!" << endl;
	cout << "Please, enter the heighst and the width of the matrix: ";
	cin >> height >> width;

	if ((height == 0) || (width == 0)) {
		cout << "Error" << endl << endl;
		system("pause");
		return 0;
	}

	m_matrix matrix(height, width);

	cout << "Please, enter the matrix:" << endl;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			double value;
			cout << "enter the element with a number " << i << "," << j << ": ";
			cin >> value;
			matrix.setElement(i, j, value);
		}
    
  show_hint();
	while (choice != '0') {
		cout << "Please, choose an action: ";
		cin >> choice;
		switch (choice) {
		case '1': {
			size_t e_height = 0, e_width;
			cout << "Please, enter the element index: ";
			cin >> e_height >> e_width;

			if ((e_height >= height) || (e_width >= width)) {
				cout << "Error!" << endl;
				break;
			}

			cout << "Value: " << matrix.getElement(e_height, e_width) << endl;
			break;
		}
		case '2': {
			size_t e_height1 = 0, e_height2 = 0;
			cout << "Please, enter the rows indexes: ";
			cin >> e_height1 >> e_height2;

			if ((e_height1 >= height) || (e_height2 >= height)) {
				cout << "Error!" << endl;
				break;
			}

			matrix.swapStrings(e_height1, e_height2);
			cout << "Complete!" << endl;
			break;
		}
		case '3': {
			double multiplier = 0;
			size_t e_height = 0;

			cout << "Please, enter the row number: ";
			cin >> e_height;

			if (e_height >= height) {
				cout << "Error!" << endl;
				break;
			}

			cout << "Please, enter the multiplier: ";
			cin >> multiplier;

			matrix.multiplyString(e_height, multiplier);
			cout << "Complete!" << endl;
			break;
		}
		case '4': {
			size_t e_height1 = 0, e_height2 = 0;
			double multiplier1 = 0, multiplier2 = 0;
			matrixList *vector = nullptr, *headElement = nullptr;

			cout << "Please, enter the rows indexes: ";
			cin >> e_height1 >> e_height2;
			
			if ((e_height1 >= height) || (e_height2 >= height)) {
				cout << "Error!" << endl;
				break;
			}

			cout << "Please, enter the multipliers: ";
			cin >> multiplier1 >> multiplier2;

			headElement = vector = matrix.stringLinearCombination(e_height1, multiplier1, e_height2, multiplier2);
			cout << "Vector:" << endl << "(";
			for (; vector->next != nullptr; vector = vector->next) cout << vector->data << ", ";
			cout << vector->data << ")" << endl;
			delete headElement;
			break;
		}
		case '5': {
			short i = 0;
			size_t index = 0;
			matrixList *vector = nullptr, *headElement = nullptr;

			cout << "Choose column(1) or rowns(2): ";
			cin >> i;

			if ((i != 1) && (i != 2)) {
				cout << "Error!" << endl;
				break;
			}

			cout << "Please, enter the index: ";
			cin >> index;

			if (((index >= width) && (i == 1)) || ((index >= height) && (i == 2))) {
				cout << "Error!" << endl;
				break;
			}

			if (i == 1) headElement = vector = matrix.getColumnVector(index);
			else headElement = vector = matrix.getStringVector(index);

			cout << "Vector:" << endl << "(";
			for (; vector->next != nullptr; vector = vector->next) cout << vector->data << ", ";
			cout << vector->data << ")" << endl;
			delete headElement;
			break;
		}
		case '6': {
			matrix.showMatrix(); 
			break;
		}
		case '?': {
      show_hint();
			break;
		}
		}
	}

	cout << endl;
	system("pause");
	return 0;
}
