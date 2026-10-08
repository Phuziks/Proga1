#include "DynamicArray.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <typeinfo>

int main() {
    std::cout << "Задание 1: шаблонный класс и сеттер с проверкой для целых чисел" << std::endl;
    DynamicArray<int> ints(3);
    ints.set(0, 1);
    ints.set(1, 2);
    ints.set(2, 3);
    std::cout << "DynamicArray<int>: " << ints << std::endl;
    try {
        ints.set(0, 500);
    } catch (const std::invalid_argument& e) {
        std::cout << "int, set(0, 500): " << e.what() << std::endl;
    }
    try {
        ints.pushBack(-101);
    } catch (const std::invalid_argument& e) {
        std::cout << "int, pushBack(-101): " << e.what() << std::endl;
    }

    DynamicArray<double> doubles(3);
    doubles.set(0, 1.5);
    doubles.set(1, 500.25);
    doubles.set(2, -1000);
    std::cout << "DynamicArray<double> (проверки диапазона нет): " << doubles << std::endl;

    DynamicArray<std::string> strings(0);
    strings.pushBack("привет");
    strings.pushBack("мир");
    strings.set(1, "шаблоны");
    std::cout << "DynamicArray<std::string>: " << strings << std::endl;
    try {
        strings.get(5);
    } catch (const std::out_of_range& e) {
        std::cout << "string, get(5): " << e.what() << std::endl;
    }

    std::cout << std::endl << "Задание 2: оператор вывода <<" << std::endl;
    std::cout << "ints = " << ints << ", doubles = " << doubles << std::endl;
    std::cout << "print(): ";
    strings.print();

    std::cout << std::endl << "Задание 3: расстояние между массивами" << std::endl;
    DynamicArray<int> a(2);
    a.set(0, 0);
    a.set(1, 0);
    DynamicArray<int> b(2);
    b.set(0, 3);
    b.set(1, 4);
    std::cout << a << " и " << b << ": расстояние = " << a.distance(b) << std::endl;

    DynamicArray<double> c(3);
    c.set(0, 1.5);
    c.set(1, 500.25);
    c.set(2, -999);
    std::cout << doubles << " и " << c << ": расстояние = " << doubles.distance(c) << std::endl;

    try {
        ints.distance(a);
    } catch (const std::invalid_argument& e) {
        std::cout << "Разные размеры: " << e.what() << std::endl;
    }

    DynamicArray<std::string> words(2);
    words.set(0, "a");
    words.set(1, "b");
    try {
        strings.distance(words);
    } catch (const std::bad_typeid& e) {
        std::cout << "Строки: " << e.what() << std::endl;
    }

    return 0;
}
