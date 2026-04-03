#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <windows.h>

int main() {
    //настройка кодировки консоли для корректного отображения кириллицы
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    //открытие файла для чтения
    std::ifstream file;
    file.open("text.txt");
    if (!file.is_open()) {
        std::cout << "Ошибка открытия файла.\n";
        return 1;
    }

    //чтение содержимого файла в строку
    std::string text;
    std::getline(file, text);

    //подсчет кол-ва вхождений каждого символа с помощью словаря
    std::map<char, int> frequencies;
    for (char c : text) {
        frequencies[c]++; //если символа нет, он создается, если есть — инкрементируется
    }
    file.close(); //закрытие файла после считывания

    //перенос данных из map в vector для сортировки по значениям
    std::vector<std::pair<char, int>> sorted_freq(frequencies.begin(), frequencies.end());

    //сортировка вектора по убыванию частоты (второй элемент пары)
    std::sort(sorted_freq.begin(), sorted_freq.end(),
        [](const auto& a, const auto& b) {
            return a.second > b.second; //лямбда-функция для сравнения частот
        }
    );

    //настройка формата вывода: фиксированная точка и 4 знака после запятой
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Общее количество букв (Nall): " << text.length() << "\n\n";

    std::cout << "Символ | Частота (p_x)\n";
    std::cout << "----------------------\n";

    //вычисление относительной частоты по формуле p = Nx / Nall и вывод таблицы
    for (auto const& pair : sorted_freq) {
        //приведение к double для корректного деления без потери дробной части
        double px = (double)pair.second / text.length();

        //обработка пробела для визуальной чистоты отчета
        if (pair.first == ' ') std::cout << "'пробел'";
        else std::cout << " '" << (char)pair.first << "'  ";

        std::cout << " | " << px << " (" << pair.second << " раз)\n";
    }
    return 0;
}
