#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <utility>
#include <iostream>

class Parser {
public:
	// �����������. ��������� �������������� ������
	// �������� ����� searchSubstrings()
	Parser(std::string procString);
	// ����� ��������� ����������� �������� � ����� ������
	// � ������� "substring_pos: substring"
	// ��� substring_pos - ������� �������� + ������ ���������
	// �� ���� ������� ����� ������. �� ��������� - cout
	std::ostream &printRelevantSubsrings(std::ostream &out = std::cout);
	// �������� ���������� ����������� �������
	size_t getRelevantSubstringsNum();
private:
	// �������������� ������
	std::string procString_; 
	// ������ ������� �������� + � �������� + ����������� ��������
	std::vector<std::pair<size_t, size_t>> relevantSubstrings_;
	// ���������� ����������� ��������
	size_t relevantSubstringsNum_;
	
	// ����� ����������� ��������. ����������� � ������������
	void searchSubstrings();
	// ����� ������, �������� � ������
	// ���������� ���������� ��������� ������
	// � ��������-������ ���������� ������� ��������� ������
	size_t searchPluses(std::vector<size_t> &stringPluses);
	// �������� ��������� �� ����������� �������� �����
	// ��������� ������� ������� + (��������) � ������� + (��������)
	// ���������� ������������� ������ ��� ���
	bool checkSubstring(size_t firstPlus, size_t secondPlus);
};

#endif // PARSER_H