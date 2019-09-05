#ifndef M_MATRIX_HPP_INCLUDED
#define M_MATRIX_HPP_INCLUDED

struct matrixList {
	double data;
	size_t index;
	matrixList *next, *previous;
	matrixList(double Data, size_t Index) : data(Data), index(Index), next(nullptr), previous(nullptr) {}
	~matrixList() { delete next; }
};

void addElement(matrixList *&, matrixList *, double, size_t);

void removeElement(matrixList *&, matrixList *);

class m_matrix {
private:
	size_t height, width;
	matrixList **strings;
public:
	m_matrix(size_t Height, size_t Width) : height(Height), width(Width) {
		strings = new matrixList*[height];
		for (size_t i = 0; i < height; i++) strings[i] = nullptr;
	}
	~m_matrix() { delete strings; }
	bool setElement(size_t, size_t, double);
	double getElement(size_t, size_t);
	bool swapStrings(size_t, size_t);
	bool multiplyString(size_t, double);
	matrixList *stringLinearCombination(size_t, double, size_t, double);
	matrixList *getStringVector(size_t);
	matrixList *getColumnVector(size_t);
	void showMatrix(std::ostream &out = std::cout);
};

#endif // M_MATRIX_HPP_INCLUDED
