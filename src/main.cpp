#include "DynamicArray.h"

#include <iostream>
#include <new>
#include <stdexcept>

int main() {
    std::cout << "Работа массива" << std::endl;
    DynamicArray a(5);
    for (std::size_t i = 0; i < a.size(); ++i) {
        a.set(i, static_cast<int>(i) * 10);
    }
    std::cout << "a = ";
    a.print();
    std::cout << "a.get(2) = " << a.get(2) << std::endl;

    DynamicArray copy(a);
    copy.pushBack(100);
    copy.add(a);
    std::cout << "copy после pushBack(100) и add(a) = ";
    copy.print();

    std::cout << std::endl << "std::out_of_range" << std::endl;
    try {
        a.get(10);
    } catch (const std::out_of_range& e) {
        std::cout << "get: " << e.what() << std::endl;
    }
    try {
        a.set(5, 1);
    } catch (const std::out_of_range& e) {
        std::cout << "set: " << e.what() << std::endl;
    }

    std::cout << std::endl << "std::invalid_argument" << std::endl;
    try {
        a.set(0, 101);
    } catch (const std::invalid_argument& e) {
        std::cout << "set: " << e.what() << std::endl;
    }
    try {
        a.pushBack(-150);
    } catch (const std::invalid_argument& e) {
        std::cout << "pushBack: " << e.what() << std::endl;
    }
    std::cout << "Массив a не изменился: ";
    a.print();

    std::cout << std::endl << "std::bad_alloc" << std::endl;
    try {
        DynamicArray huge(std::size_t(1) << 42);
        std::cout << "Память неожиданно выделилась, размер " << huge.size() << std::endl;
    } catch (const std::bad_alloc& e) {
        std::cout << "Не удалось выделить память: " << e.what() << std::endl;
    }

    std::cout << std::endl << "Несколько catch подряд" << std::endl;
    int values[] = {50, 200};
    for (int value : values) {
        try {
            a.set(0, value);
            std::cout << "a[0] = " << a.get(0) << std::endl;
        } catch (const std::out_of_range& e) {
            std::cout << "out_of_range: " << e.what() << std::endl;
        } catch (const std::invalid_argument& e) {
            std::cout << "invalid_argument: " << e.what() << std::endl;
        }
    }

    return 0;
}
