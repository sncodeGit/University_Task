#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <utility>
#include <iostream>

class Parser {
public:
	// Конструктор. Принимает обрабатываемую строку
	// Вызывает метод searchSubstrings()
	Parser(std::string procString);
	// Вывод найденных релевантных подстрок в поток вывода
	// в формате "substring_pos: substring"
	// где substring_pos - позиция префикса + данной подстроки
	// На вход подаётся поток вывода. По умолчанию - cout
	std::ostream &printRelevantSubsrings(std::ostream &out = std::cout);
	// Получить количество релевантных построк
	size_t getRelevantSubstringsNum();
private:
	// Обрабатываемая строка
	std::string procString_; 
	// Номера позиций префикса + и суффикса + релевантных подстрок
	std::vector<std::pair<size_t, size_t>> relevantSubstrings_;
	// Количество релевантных подстрок
	size_t relevantSubstringsNum_;
	
	// Поиск релевантных подстрок. Запускается в конструкторе
	void searchSubstrings();
	// Поиск плюсов, входящих в строку
	// Возвращает количество найденных плюсов
	// В аргумент-вектор записывает позиции найденных плюсов
	size_t searchPluses(std::vector<size_t> &stringPluses);
	// Проверка подстроки на соответсвие правилам языка
	// Принимаем позиции первого + (префикса) и второго + (суффикса)
	// Возвращаем соответствует строка или нет
	bool checkSubstring(size_t firstPlus, size_t secondPlus);
};

#endif // PARSER_H