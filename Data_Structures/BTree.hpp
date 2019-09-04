#pragma once
#include <fstream>
#include "m_queue.hpp"

class IteratorIsNull{};

template <typename T>
class BTree;

template <typename T>
class treeIterator;

template <typename T>
class treeNode {
	T key;
	treeNode *left, *right, *parent;
public:
	treeNode(T e_key) : key(e_key), left(nullptr), right(nullptr), parent(nullptr) {}
	friend treeIterator<T>;
	friend BTree<T>;
};

template <typename T>
class treeIterator {
	treeNode<T> *elem;
	treeIterator(treeNode<T> *e_node) : elem(e_node) {}
public:
	treeIterator() : elem(nullptr) {}
	treeIterator(BTree<T> e_tree) : elem(e_tree.root) {}
	void setRoot(BTree<T> e_tree) { elem = e_tree.root; }
	T operator*() {
		if (elem == nullptr) throw IteratorIsNull();
		return elem->key;
	}
	treeIterator &moveLeft() {
		if (elem == nullptr) throw IteratorIsNull();
		elem = elem->left;
		return *this;
	}
	treeIterator &moveRight() {
		if (elem == nullptr) throw IteratorIsNull();
		elem = elem->right;
		return *this;
	}
	treeIterator &moveUp() {
		if (elem == nullptr) throw IteratorIsNull();
		elem = elem->parent;
		return *this;
	}
	treeIterator nextLeft() {
		if (elem == nullptr) throw IteratorIsNull();
		return treeIterator(elem->left);
	}
	treeIterator nextRight() {
		if (elem == nullptr) throw IteratorIsNull();
		return treeIterator(elem->right);
	}
	treeIterator nextUp() {
		if (elem == nullptr) throw IteratorIsNull();
		return treeIterator(elem->parent);
	}
	bool is_null() {
		if (elem == nullptr) return true;
		else return false;
	}
	friend BTree<T>;
};

template <typename T>
class BTree {
	treeNode<T> *root;
	void recDel(treeNode<T> *); // deleteSubtree() and deleteTree() subfunction
	treeNode<T> *recSearchElement(T, treeNode<T> *); // elementSearch() subfunction
	void recPrint(treeNode<T> *); // ascPrintTree() subfunction
	size_t recElementsNumber(treeNode<T> *e_node) {
		if (e_node == nullptr) return 0;
		else return recElementsNumber(e_node->left) + recElementsNumber(e_node->right) + 1;
	}
	size_t recLeavesNumber(treeNode<T> *e_node) {
		if (e_node == nullptr) return 0;
		else if ((e_node->left == nullptr) && (e_node->right == nullptr)) return 1;
		else return recLeavesNumber(e_node->left) + recLeavesNumber(e_node->right);
	}
	size_t recTreeHeight(treeNode<T> *e_node) {
		if (e_node == nullptr) return 0;
		size_t lHeight = recTreeHeight(e_node->left), rHeight = recTreeHeight(e_node->right);
		if (lHeight > rHeight) return lHeight + 1;
		else return rHeight + 1;
	}
	unsigned short maxLength(treeNode<T> *); // widePrintTree() subfunction
	unsigned short getLength(T); // getTreeHeight() and widePrintHeight() subfunction
public:
	BTree() : root(nullptr) {}
	BTree(T e_value) : root(new treeNode<T>(e_value)) {}
	void addElem(T);
	bool deleteSubtree(treeIterator<T>);
	bool deleteElem(treeIterator<T>);
	void deleteTree() { recDel(root); root = nullptr; }
	treeIterator<T> searchElement(T e_value) { return treeIterator<T>(recSearchElement(e_value, root)); } // For all trees
	bool ascPrintTree(); // Ascending
	bool widePrintTree();
	size_t getElementsNumber() { return recElementsNumber(root); }
	size_t getLeavesNumber() { return recLeavesNumber(root); }
	size_t getTreeHeight() { return recTreeHeight(root); }
	unsigned short getElementDegree(treeIterator<T>);
	size_t getElementLevel(treeIterator<T>);
	bool is_empty() {
		if (root == nullptr) return true;
		else return false;
	}
	friend treeIterator<T>;
};

template <typename T>
void BTree<T>::addElem(T e_value) {
	if (root == nullptr){
		root = new treeNode<T>(e_value);
		return;
	}

	treeNode<T> *actElem = root;
	while (true) {
		if (e_value <= actElem->key) {
			if (actElem->left == nullptr) {
				actElem->left = new treeNode<T>(e_value);
				actElem->left->parent = actElem;
				return;
			}
			actElem = actElem->left;
		}
		else {
			if (actElem->right == nullptr) {
				actElem->right = new treeNode<T>(e_value);
				actElem->right->parent = actElem;
				return;
			}
			actElem = actElem->right;
		}
	}
}

template <typename T>
bool BTree<T>::deleteSubtree(treeIterator<T> e_iter) {
	if (e_iter.elem == nullptr) return false;
	
	treeNode<T> *actElem = e_iter.elem;
	e_iter.moveUp();

	if (actElem->parent != nullptr) {
		if (actElem->key <= actElem->parent->key) actElem->parent->left = nullptr;
		else actElem->parent->right = nullptr;
	}
	else root = nullptr;

	recDel(actElem);
	return true;
}

template <typename T>
void BTree<T>::recDel(treeNode<T> *e_node) {
	if (e_node == nullptr) return;

	recDel(e_node->left);
	recDel(e_node->right);

	delete e_node;
}

template <typename T>
bool BTree<T>::deleteElem(treeIterator<T> e_iter) {
	treeNode<T> *elem = e_iter.elem;
	if (elem == nullptr) return false;

	if ((elem->right == nullptr) && (elem->left == nullptr)) {
		if (elem->parent == nullptr) root = nullptr;
		if (elem->key <= elem->parent->key) elem->parent->left = nullptr;
		else elem->parent->right = nullptr;
		e_iter.moveUp();
	}
	else if (elem->right == nullptr) {
		elem->left->parent = elem->parent;
		if (elem->parent == nullptr) root = elem->left;
		else {
			if (elem->key <= elem->parent->key) elem->parent->left = elem->left;
			else elem->parent->right = elem->left;
		}
		e_iter.elem = elem->left;
	}
	else if (elem->left == nullptr) {
		elem->right->parent = elem->parent;
		if (elem->parent == nullptr) root = elem->right;
		else {
			if (elem->key <= elem->parent->key) elem->parent->left = elem->right;
			else elem->parent->right = elem->right;
		}
		e_iter.elem = elem->right;
	}
	else {
		treeNode<T> *extremeElem = elem->left;
		while (extremeElem->right != nullptr) extremeElem = extremeElem->right;

		if (extremeElem->left != nullptr) extremeElem->left->parent = extremeElem->parent;
		if (extremeElem->key <= extremeElem->parent->key) extremeElem->parent->left = extremeElem->left;
		else extremeElem->parent->right = extremeElem->left;

		extremeElem->parent = elem->parent;
		if (elem->parent == nullptr) root = extremeElem;
		else {
			if (elem->key <= elem->parent->key) elem->parent->left = extremeElem;
			else elem->parent->right = extremeElem;
		}

		extremeElem->right = elem->right;
		extremeElem->left = elem->left;

		e_iter.elem = extremeElem;
	}

	delete elem;
	return true;
}

template <typename T>
treeNode<T> *BTree<T>::recSearchElement(T e_key, treeNode<T> *e_node) {
	if (e_node == nullptr) return nullptr;

	if (e_node->key == e_key) return e_node;

	treeNode<T> *lSearchRes = recSearchElement(e_key, e_node->left);
	if (lSearchRes != nullptr) return lSearchRes;
	return recSearchElement(e_key, e_node->right);
}

template <typename T>
bool BTree<T>::ascPrintTree() {
	if (root == nullptr) return false;
	recPrint(root);
	return true;
}

template <typename T>
void BTree<T>::recPrint(treeNode<T> *e_node) {
	if (e_node == nullptr) return;

	recPrint(e_node->left);
	cout << e_node->key << " ";
	recPrint(e_node->right);
}

template <typename T>
bool BTree<T>::widePrintTree() {
	if (root == nullptr) return false;

	ofstream fout("PRINT_TREE.txt");
	if (!fout.is_open()) return false;

	unsigned short len = maxLength(root);
	size_t height = getTreeHeight(), i = 1;
	treeNode<T> *elem = nullptr; 

	m_queue<treeNode<T> *> queue;
	queue.addElem(root);
	for (size_t j = 1; j < height; j++) i *= 2;

	for (size_t j = 1; i != 0; i /= 2, j *= 2) {
		for (size_t m = 0; m < j; m++) {
			elem = queue.getElem();
			for (size_t l = 1; l < i; l++)
				for (size_t f = 0; f < len; f++) fout << " ";
			if (elem == nullptr) {
				for (size_t f = 0; f < len; f++) fout << " ";
				queue.addElem(nullptr);
				queue.addElem(nullptr);
			}
			else {
				fout << elem->key;
				for (size_t f = getLength(elem->key); f < len; f++) fout << " ";
				queue.addElem(elem->left);
				queue.addElem(elem->right);
			}
			for (size_t l = 0; l < i; l++)
				for (size_t f = 0; f < len; f++) fout << " ";
		}
		fout << endl << endl;
	}

	fout.close();
	return true;
}

template <typename T>
unsigned short BTree<T>::maxLength(treeNode<T> *e_node) {
	if (e_node == nullptr) return 0;

	short length = getLength(e_node->key), lLength = maxLength(e_node->left), rLength = maxLength(e_node->right);

	if ((length >= lLength) && (length >= rLength)) return length;
	else if ((lLength >= length) && (lLength >= rLength)) return lLength;
	else return rLength;
}

template <typename T>
unsigned short BTree<T>::getLength(T e_value) {
	unsigned short length = 0;
	
	if (e_value < 0) length++;
	do {
		e_value /= 10;
		length++;
	} while (e_value != 0);
	return length;
}

template <typename T>
unsigned short BTree<T>::getElementDegree(treeIterator<T> e_iter) {
	unsigned short degree = 0;
	if (e_iter.elem->left != nullptr) degree++;
	if (e_iter.elem->right != nullptr) degree++;
	return degree;
}

template <typename T>
size_t BTree<T>::getElementLevel(treeIterator<T> e_iter) {
	size_t level = 0;
	treeNode<T> *actElem = e_iter.elem->parent;

	for (; actElem != nullptr; level++) actElem = actElem->parent;

	return level;
}
