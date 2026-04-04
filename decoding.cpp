#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <windows.h>
#include <fstream>

//функция для расшифровки текста по заданной перестановке (ключу)
std::string decrypt(std::string text, const std::vector<int>& p) {
	std::string result = "";
	int n = p.size(); //длина блока (ключа)

	//проходим по всему тексту шагами, равными длине блока
	for (size_t i = 0; i < text.length(); i += n) {
		//извлекаем очередной блок символов
		std::string block = text.substr(i, n);

		//если последний блок короче n, дополняем его пробелами (по условию)
		if (block.length() < n) block.append(n - block.length(), ' ');

		std::string decoded_block = block; //заготовка для расшифрованного блока
		for (int j = 0; j < n; ++j) {
			//переставляем символы обратно согласно текущему ключу p
			//вычитаем 1, так как в ключе нумерация с 1, а в массивах с 0
			decoded_block[p[j] - 1] = block[j];
		}
		result += decoded_block; //собираем расшифрованные блоки в единую строку
	}
	return result;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//открытие файла с зашифрованным текстом
	std::ifstream file;
	file.open("cipher.txt");
	if (!file.is_open()) {
		std::cerr << "Ошибка открытия файла.\n";
		return 1;
	}

	//чтение зашифрованного сообщения из файла
	std::string cipher_text;
	std::getline(file, cipher_text);

	std::vector<int> p{ 4, 6, 1, 2, 5, 3 }; //найденный ключ
	std::cout << "Расшифрованное сообщение:" << std::endl;
	std::string attempt = decrypt(cipher_text, p); //расшифровка

	//выводим ключ
	std::cout << "[";
	for (int x : p) std::cout << x;

	//выводим текст
	std::cout << "]\n" << attempt << std::endl;

	file.close(); //закрываем файл после обработки
	return 0;
}
