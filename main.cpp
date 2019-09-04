#include <iostream>
#include <string>
#include "Parser.h"

int main() {
	// Читаем введенную пользователем в консоль строку
	std::string procString = "";
	std::cout << "Enter string:" << std::endl;
	std::getline(std::cin, procString);
	// Создаём объект класса parser и выводим найденные подстроки
	// а также и количество
	Parser parser(procString);
	std::cout << "Found " << parser.getRelevantSubstringsNum() << " relevant substrings" << std::endl;
	parser.printRelevantSubsrings();
	// Пауза после вывода
	system("pause");
    return 0;
}