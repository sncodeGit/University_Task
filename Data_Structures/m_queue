#ifndef M_QUEUE_HPP_INCLUDED
#define M_QUEUE_HPP_INCLUDED

struct queueIsEmpty {
};

template <typename T>
class m_queue {
private:
	struct queueElem {
		T data;
		queueElem *prev;
		queueElem(T e_data) : data(e_data), prev(nullptr) {}
	};
	queueElem *headElem, *lastElem;
public:
	m_queue() : headElem(nullptr), lastElem(nullptr) {}
	~m_queue();
	void addElem(T);
	T getElem();
	bool is_empty();
	void print(std::ostream &out = cout);
};

template <typename T>
m_queue<T>::~m_queue() {
	queueElem *delElem = nullptr;
	while (headElem != nullptr) {
		delElem = headElem;
		headElem = headElem->prev;
		delete delElem;
	}
}

template <typename T>
void m_queue<T>::addElem(T e_value) {
	if (lastElem == nullptr) {
		lastElem = new queueElem(e_value);
		headElem = lastElem;
	}
	else if (headElem == lastElem) {
		lastElem->prev = new queueElem(e_value);
		lastElem = lastElem->prev;
		headElem->prev = lastElem;
	}
	else {
		lastElem->prev = new queueElem(e_value);
		lastElem = lastElem->prev;
	}
}

template <typename T>
T m_queue<T>::getElem() {
	if (headElem == nullptr) throw queueIsEmpty();

	T value = headElem->data;
	queueElem *delElem = headElem;

	headElem = headElem->prev;
	if (headElem == nullptr) lastElem = nullptr;
	delete delElem;
	return value;
}

template <typename T>
bool m_queue<T>::is_empty() {
	if (headElem == nullptr) return true;
	else return false;
}

template <typename T>
void m_queue<T>::print(std::ostream &out) {
	for (queueElem *actElem = headElem; actElem != nullptr; actElem = actElem->prev)
		out << actElem->data << " | ";
}

#endif // M_QUEUE_HPP_INCLUDED
