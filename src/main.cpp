#include "../include/DynamicArray.h"

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
        return strings.distance(words);
    } catch (const std::bad_typeid& e) {
        std::cout << "Строки: " << e.what() << std::endl;
    }

        std::cout << std::endl << "Задание 4: operator[] через Reference" << std::endl;
    DynamicArray<int> ref(3);
    ref[0] = 10;
    ref[1] = 20;
    ref[2] = 30;
    std::cout << "после присваивания через []: " << ref << std::endl;


    // проверка границ
    try {
        ref[10] = 5;
    } catch (const std::out_of_range& e) {
        std::cout << "ref[10]: " << e.what() << std::endl;
    }

    // проверка диапазона значений через set (Reference вызывает set)
    try {
        ref[0] = 500;
    } catch (const std::invalid_argument& e) {
        std::cout << "ref[0] = 500: " << e.what() << std::endl;
    }

    std::cout << std::endl << "Задание 5: итераторы begin()/end()" << std::endl;
    DynamicArray<int> iterable(4);
    iterable.set(0, 1);
    iterable.set(1, 2);
    iterable.set(2, 3);
    iterable.set(3, 4);

    std::cout << "for (const auto& x : iterable): ";
    for (const auto& v : iterable) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    // изменяемый обход
    for (auto& v : iterable) {
        v = v * 2;
    }
    std::cout << "после удвоения через for (auto&): " << iterable << std::endl;

    // const-версия begin()/end()
    const DynamicArray<int>& constRef = iterable;
    std::cout << "const-обход: ";
    for (const auto& v : constRef) {
        std::cout << v << " ";
    }
    std::cout << std::endl;



    std::cout << std::endl << "Задание 6: == и !=" << std::endl;
    DynamicArray<int> eq1(3);
    eq1.set(0, 1); eq1.set(1, 2); eq1.set(2, 3);
    DynamicArray<int> eq2(3);
    eq2.set(0, 1); eq2.set(1, 2); eq2.set(2, 3);


    std::cout << "eq1 == eq2: " << (eq1 == eq2) << std::endl;

    std::cout << std::endl << "Задание 7: += и -= с массивом" << std::endl;
    DynamicArray<int> acc1(3);
    acc1.set(0, 1); acc1.set(1, 2); acc1.set(2, 3);
    DynamicArray<int> acc2(3);
    acc2.set(0, 10); acc2.set(1, 20); acc2.set(2, 30);

    std::cout << "acc1 = " << acc1 << std::endl;
    acc1 += acc2;
    std::cout << "acc1 += acc2 -> " << acc1 << std::endl;
    acc1 -= acc2;
    std::cout << "acc1 -= acc2 -> " << acc1 << std::endl;

    // += с массивом другого размера (недостающие = T())
    DynamicArray<int> small(2);
    small.set(0, 100); small.set(1, 100);
    DynamicArray<int> big(4);
    big.set(0, 1); big.set(1, 1); big.set(2, 1); big.set(3, 1);
    big += small;
    std::cout << "big(4) += small(2) -> " << big << std::endl;

    std::cout << std::endl << "Задание 8: += и -= со скаляром" << std::endl;
    DynamicArray<int> scal(3);
    scal.set(0, 1); scal.set(1, 2); scal.set(2, 3);
    std::cout << "scal = " << scal << std::endl;
    scal += 10;
    std::cout << "scal += 10 -> " << scal << std::endl;
    scal -= 5;
    std::cout << "scal -= 5  -> " << scal << std::endl;

    return 0;
}
