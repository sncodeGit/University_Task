#ifndef M_STACK_HPP_INCLUDED
#define M_STACK_HPP_INCLUDED

struct stackIsEmpty {
};

template <typename T> 
class m_stack {
private:
	struct stackElem {
		stackElem *prev;
		T data;
		stackElem(T e_data) : data(e_data), prev(nullptr) {}
	};
	stackElem *headElem;
public:
	m_stack() : headElem(nullptr) {}
	~m_stack();
	void push(T);
	T pop();
	bool is_empty();
	void print(std::ostream &out = cout);
};

template <typename T>
m_stack<T>::~m_stack() {
	stackElem *delElem = nullptr;
	while(headElem != nullptr) {
		delElem = headElem;
		headElem = headElem->prev;
		delete delElem;
	}
}

template <typename T> 
void m_stack<T>::push(T e_data) {
	if (headElem == nullptr) headElem = new stackElem(e_data);
	else {
		stackElem *newElem = new stackElem(e_data);
		newElem->prev = headElem;
		headElem = newElem;
	}
}

template <typename T>
T m_stack<T>::pop() {
	if (headElem == nullptr) throw stackIsEmpty();

	T value = headElem->data;
	stackElem *delElem = headElem;

	headElem = headElem->prev;
	delete delElem;
	return value;
}

template <typename T>
bool m_stack<T>::is_empty() {
	if (headElem == nullptr) return true;
	else return false;
}

template <typename T>
void m_stack<T>::print(std::ostream &out) {
	for (stackElem *actElem = headElem; actElem != nullptr; actElem = actElem->prev)
		out << actElem->data << " | ";
}

#endif // M_STACK_HPP_INCLUDED
