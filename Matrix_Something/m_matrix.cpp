#include <iostream>
#include "m_matrix.hpp"

void addElement(matrixList *&headElement, matrixList *activeElement, double enterValue, size_t enterIndex) {
	matrixList *element = new matrixList(enterValue, enterIndex);
	
	if (headElement == activeElement) {
		headElement->previous = element;
		element->next = headElement;
		headElement = element;
		return;
	}

	if (activeElement == nullptr) {
		matrixList *lastElement = headElement;
		for (; lastElement->next != nullptr; lastElement = lastElement->next);
		lastElement->next = element;
		element->previous = lastElement;
		return;
	}

	element->next = activeElement;
	element->previous = activeElement->previous;
	activeElement->previous = element;
	element->previous->next = element;
}

void removeElement(matrixList *&headElement, matrixList *activeElement) {
	if (headElement == activeElement) {
		headElement = headElement->next;
		if (headElement != nullptr) headElement->previous = nullptr;
		activeElement->next = nullptr;
		delete activeElement;
		return;
	}

	activeElement->previous->next = activeElement->next;
	if (activeElement->next != nullptr) activeElement->next->previous = activeElement->previous;
	activeElement->next = nullptr;
	activeElement->previous = nullptr;
	delete activeElement;
}

bool m_matrix::setElement(size_t e_height, size_t e_width, double e_data) {
	if ((e_height >= height) || (e_width >= width)) return false;

	if (strings[e_height] == nullptr) {
		if (e_data != 0) strings[e_height] = new matrixList(e_data, e_width);
		return true;
	}

	matrixList *activeElement = strings[e_height];
	for (; activeElement != nullptr; activeElement = activeElement->next)
		if (activeElement->index == e_width) {
			if (e_data == 0) removeElement(strings[e_height], activeElement);
			else activeElement->data = e_data;
			return true;
		}
		else if (activeElement->index > e_width) {
			if (e_data != 0) addElement(strings[e_height], activeElement, e_data, e_width);
			return true;
		}
		else if (activeElement->next == nullptr) {
			if (e_data != 0) addElement(strings[e_height], nullptr, e_data, e_width);
			return true;
		}
}

double m_matrix::getElement(size_t e_height, size_t e_width) {
	if ((e_height >= height) || (e_width >= width)) return 0;
	for (matrixList *activeElement = strings[e_height]; activeElement != nullptr; activeElement = activeElement->next)
		if (activeElement->index == e_width) return activeElement->data;
	return 0;
}

bool m_matrix::swapStrings(size_t e_height1, size_t e_height2) {
	if ((e_height1 >= height) || (e_height2 >= height)) return false;
	matrixList *string = strings[e_height1];
	strings[e_height1] = strings[e_height2];
	strings[e_height2] = string;
	return true;
}

bool m_matrix::multiplyString(size_t e_height, double e_num) {
	if (e_height >= height) return false;
	
	if (e_num == 0) {
		while (strings[e_height] != nullptr)
			removeElement(strings[e_height], strings[e_height]);
		return true;
	}
	
	for (matrixList *string = strings[e_height]; string != nullptr; string = string->next)
		string->data *= e_num;
	return true;
}

matrixList *m_matrix::stringLinearCombination(size_t e_height1, double e_num1, size_t e_height2, double e_num2) {
	if ((e_height1 >= height) || (e_height2 >= height)) return nullptr;

	matrixList *headElement = new matrixList(getElement(e_height1, 0) * e_num1 + getElement(e_height2, 0) * e_num2, 0);
	for (size_t i = 1; i < width; i++)
		addElement(headElement, nullptr, getElement(e_height1, i) * e_num1 + getElement(e_height2, i) * e_num2, 0);
	return headElement;
}

matrixList *m_matrix::getStringVector(size_t e_height) {
	if (e_height >= height) return nullptr;
	matrixList *headElement = new matrixList(getElement(e_height, 0), 0);
	for (size_t i = 1; i < width; i++) addElement(headElement, nullptr, this->getElement(e_height, i), 0);
	return headElement;
}

matrixList *m_matrix::getColumnVector(size_t e_width) {
	if (e_width >= width) return nullptr;
	matrixList *headElement = new matrixList(getElement(0, e_width), 0);
	for (size_t i = 1; i < height; i++) addElement(headElement, nullptr, this->getElement(i, e_width), 0);
	return headElement;
}

void m_matrix::showMatrix(std::ostream &out) {
	for (size_t i = 0; i < height; i++) {
		matrixList *activeString = strings[i];
		out << "String " << i << ": ";
		for (size_t j = 0; j < width; j++)
			if ((activeString != nullptr) && (activeString->index == j)) {
				out << activeString->data << " | ";
				activeString = activeString->next;
			}
			else out << 0 << " | ";
		out << "\n";
	}
}
