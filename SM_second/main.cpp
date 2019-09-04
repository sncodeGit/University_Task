#include <iostream>
#include <string>
#include <stack>

// Проверка на соответствие языку введенной строки
// Возвращает позицию первого несоответствия языку
// Возвращает позицию после конца строки, если
// в строке не содержатся все необходимые символы,
// например: 110000111000
// При полном соответствии языку возвращает -1
int isLineRelevant(std::string &);

int main() {
	// Ввод строки
	std::string line;
	std::cout << "Enter string:" << std::endl;
	std::getline(std::cin, line);
	// Вывод результата
	int position = isLineRelevant(line);
	if (position == -1) std::cout << "The string belongs to the language" << std::endl;
	else std::cout << "Position of the first error: " << position << std::endl;
	// Пауза после окончания работы программы
	system("pause");
	return 0;
}

int isLineRelevant(std::string &e_line) {
	// Магазин автомата
	std::stack<char> machineShop;
	machineShop.push('A');
	machineShop.push('A');
	// Посимвольный разбор строки
	for (size_t i = 0, length = e_line.length(); i < length; i++)
		switch (e_line[i]) {
		case '1':
			// 1, идущая после 1^(n)0^(2n)1^(m)0^(2m)
			if (machineShop.empty()) return i;
			// Если в стеке осталась В, а пришла 1
			// это значит, что количество нулей не 
			// соответствует правилам языка
			if (machineShop.top() == 'B') return i;
			// Переход 1,A/ABB
			machineShop.pop();
			machineShop.push('B');
			machineShop.push('B');
			machineShop.push('A');
			break;
		case '0':
			// 0, идущий после 1^(n)0^(2n)1^(m)0^(2m)
			if (machineShop.empty()) return i;
			// Переход e,A/e, где е-эпсилон
			while (machineShop.top() == 'A') {
				machineShop.pop();
				// Если 0 стоит первым или нулей больше
				// чем ожидалось исходя из количества 1
				if (machineShop.empty()) return i;
			}
			// Переход 0,В/e, где е-эпсилон
			machineShop.pop();
			break;
		default:
			return i;
		}
	// Переход e,A/e, где е-эпсилон
	while (!machineShop.empty()) {
		if (machineShop.top() == 'B') return e_line.length();
		machineShop.pop();
	}
	// Строка соответствует языку
	return -1;
}
