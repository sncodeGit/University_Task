#ifndef M_DEQUE_HPP_INCLUDED
#define M_DEQUE_HPP_INCLUDED

struct dequeIsEmpty {
	bool right;
	dequeIsEmpty(bool e_value) : right(e_value) {}
};

template <typename T>
class m_deque {
private:
	struct dequeElem {
		T data;
		dequeElem *next, *prev;
		dequeElem(T e_data) : data(e_data), next(nullptr), prev(nullptr) {}
	};
	dequeElem *rightElem, *leftElem;
public:
	m_deque() : rightElem(nullptr), leftElem(nullptr) {}
	~m_deque();
	m_deque(const m_deque &obj);
	void addToLeft(T);
	void addToRight(T);
	T getFromLeft();
	T getFromRight();
	size_t searchElem(T);
	bool is_empty();
	void print(std::ostream &out = cout);
};

template <typename T>
m_deque<T>::~m_deque() {
	dequeElem *delElem = nullptr;
	while (leftElem != nullptr) {
		delElem = leftElem;
		leftElem = leftElem->next;
		delete delElem;
	}
}

template <typename T>
m_deque<T>::m_deque(const m_deque<T> &obj) {
	if (obj.leftElem == nullptr) return;

	dequeElem *actElem = obj.leftElem;
	leftElem = new dequeElem(actElem->data);
	rightElem = leftElem;
	actElem = actElem->next;

	dequeElem *prevElem = rightElem;
	while (actElem != nullptr) {
		rightElem->next = new dequeElem(actElem->data);
		prevElem = rightElem;
		rightElem = rightElem->next;
		rightElem->prev = actElem;
		actElem = actElem->next;
	}
}

template <typename T>
void m_deque<T>::addToLeft(T e_value) {
	if (leftElem == nullptr) {
		leftElem = new dequeElem(e_value);
		rightElem = leftElem;
		return;
	}

	leftElem->prev = new dequeElem(e_value);
	leftElem->prev->next = leftElem;
	leftElem = leftElem->prev;
}

template <typename T>
void m_deque<T>::addToRight(T e_value) {
	if (rightElem == nullptr) {
		rightElem = new dequeElem(e_value);
		leftElem = rightElem;
		return;
	}

	rightElem->next = new dequeElem(e_value);
	rightElem->next->prev = rightElem;
	rightElem = rightElem->next;
}

template <typename T>
T m_deque<T>::getFromLeft() {
	if (leftElem == nullptr) throw dequeIsEmpty(false);

	T value = leftElem->data;
	dequeElem *delElem = leftElem;
	
	leftElem = leftElem->next;
	if (leftElem == nullptr) rightElem = nullptr;
	if (leftElem != nullptr) leftElem->prev = nullptr;
	delete delElem;
	return value;
}

template <typename T>
T m_deque<T>::getFromRight() {
	if (rightElem == nullptr) throw dequeIsEmpty(true);

	T value = rightElem->data;
	dequeElem *delElem = rightElem;

	rightElem = rightElem->prev;
	if (rightElem == nullptr) leftElem = nullptr;
	if (rightElem != nullptr) rightElem->next = nullptr;
	delete delElem;
	return value;
}

template <typename T>
size_t m_deque<T>::searchElem(T e_value) {
	size_t count = 0;
	for (dequeElem *actElem = leftElem; actElem != nullptr; actElem = actElem->next)
		if (actElem->data == e_value) count++;
	return count;
}

template <typename T>
bool m_deque<T>::is_empty() {
	if (leftElem == nullptr) return true;
	else return false;
}

template <typename T>
void m_deque<T>::print(std::ostream &out) {
	for (dequeElem *actElem = leftElem; actElem != nullptr; actElem = actElem->next)
		out << actElem->data << " | ";
}

#endif // M_DEQUE_HPP_INCLUDED
