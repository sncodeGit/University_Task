#ifndef M_HTABLE_HPP_INCLUDED
#define M_HTABLE_HPP_INCLUDED

class IncorrectSymbol {
	char symb;
public:
	IncorrectSymbol(char e_symb) : symb(e_symb) {}
	char getSymb() { return symb; }
};

class m_HTable {
	size_t data[52];
	int hashFunc(char e_key) {
		if (e_key > 96) return e_key - 71;
		else return e_key - 65;
	}
public:
	m_HTable() { for (int i = 0; i < 52; i++) data[i] = 0; }
	void addElem(char e_key) { 
		if (!(((e_key >= 'a') && (e_key <= 'z')) || ((e_key >= 'A') && (e_key <= 'Z')))) throw IncorrectSymbol(e_key);
		data[hashFunc(e_key)]++; 
	}
	size_t getElem(char e_key) { 
		if (!(((e_key >= 'a') && (e_key <= 'z')) || ((e_key >= 'A') && (e_key <= 'Z')))) throw IncorrectSymbol(e_key);
		return data[hashFunc(e_key)]; 
	}
};

#endif // M_HTABLE_HPP_INCLUDED
