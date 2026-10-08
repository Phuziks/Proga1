#include "DynamicArray.h"

#include <iostream>

int main() {
    std::cout << "Задание 1: конструктор, сеттер, геттер, вывод" << std::endl;
    DynamicArray a(5);
    std::cout << "Новый массив из 5 элементов: ";
    a.print();

    for (std::size_t i = 0; i < a.size(); ++i) {
        a.set(i, static_cast<int>(i) * 10);
    }
    std::cout << "После set: ";
    a.print();
    std::cout << "get(2) = " << a.get(2) << std::endl;

    std::cout << "Проверки сеттера и геттера:" << std::endl;
    a.set(10, 5);
    a.set(0, 101);
    a.set(0, -101);
    a.set(0, 100);
    a.set(1, -100);
    int wrong = a.get(99);
    std::cout << "get(99) вернул " << wrong << std::endl;
    std::cout << "Массив a: ";
    a.print();

    std::cout << std::endl << "Задание 2: конструктор копирования" << std::endl;
    DynamicArray copy(a);
    copy.set(0, 1);
    std::cout << "Изменили copy[0] = 1" << std::endl;
    std::cout << "a:    ";
    a.print();
    std::cout << "copy: ";
    copy.print();
    std::cout << "Оригинал не изменился — значит, копия глубокая." << std::endl;

    std::cout << std::endl << "Задание 3: добавление в конец" << std::endl;
    DynamicArray b(0);
    std::cout << "Пустой массив b: ";
    b.print();
    b.pushBack(7);
    b.pushBack(-3);
    b.pushBack(50);
    std::cout << "После pushBack(7), pushBack(-3), pushBack(50): ";
    b.print();
    b.pushBack(500);
    std::cout << "Размер b: " << b.size() << std::endl;

    std::cout << std::endl << "Задание 4: сложение и вычитание массивов" << std::endl;
    DynamicArray x(4);
    x.set(0, 1);
    x.set(1, 2);
    x.set(2, 3);
    x.set(3, 4);
    DynamicArray y(2);
    y.set(0, 10);
    y.set(1, 20);

    std::cout << "x = ";
    x.print();
    std::cout << "y = ";
    y.print();

    x.add(y);
    std::cout << "x.add(y) -> x = ";
    x.print();

    x.sub(y);
    std::cout << "x.sub(y) -> x = ";
    x.print();

    y.add(x);
    std::cout << "y.add(x) -> y = ";
    y.print();

    return 0;
}
