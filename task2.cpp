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

    int n = 6; //заданная в условии длина ключа
    std::vector<int> p(n);
    //заполняем вектор начальной перестановкой {1, 2, 3, 4, 5, 6}
    iota(p.begin(), p.end(), 1);

    std::cout << "Перебор всех вариантов ключа:" << std::endl;

    //цикл перебора всех возможных перестановок (всего 6! = 720 вариантов)
    do {
        //пробуем расшифровать текст текущим вариантом ключа
        std::string attempt = decrypt(cipher_text, p);

        //выводим текущий ключ (перестановку)
        std::cout << "[";
        for (int x : p) std::cout << x;

        //выводим первые 50 символов результата для поиска осмысленного текста
        std::cout << "] " << attempt.substr(0, 50) << "..." << std::endl;

    } while (next_permutation(p.begin(), p.end())); //генерирует следующую уникальную перестановку

    file.close(); //закрываем файл после обработки
    return 0;
}
