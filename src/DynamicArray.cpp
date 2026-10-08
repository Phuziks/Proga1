#include "DynamicArray.h"

#include <iostream>

DynamicArray::DynamicArray(std::size_t size)
    : data_(new int[size]()), size_(size) {
}

DynamicArray::DynamicArray(const DynamicArray& other)
    : data_(new int[other.size_]), size_(other.size_) {
    for (std::size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
}

DynamicArray::~DynamicArray() {
    delete[] data_;
}

std::size_t DynamicArray::size() const {
    return size_;
}

void DynamicArray::print() const {
    std::cout << "[";
    for (std::size_t i = 0; i < size_; ++i) {
        if (i > 0) {
            std::cout << ", ";
        }
        std::cout << data_[i];
    }
    std::cout << "]" << std::endl;
}

bool DynamicArray::set(std::size_t index, int value) {
    if (!isIndexValid(index)) {
        std::cerr << "Ошибка set: индекс " << index << " вне границ массива (размер "
                  << size_ << ")" << std::endl;
        return false;
    }
    if (!isValueValid(value)) {
        std::cerr << "Ошибка set: значение " << value << " вне промежутка ["
                  << MIN_VALUE << ", " << MAX_VALUE << "]" << std::endl;
        return false;
    }
    data_[index] = value;
    return true;
}

int DynamicArray::get(std::size_t index) const {
    if (!isIndexValid(index)) {
        std::cerr << "Ошибка get: индекс " << index << " вне границ массива (размер "
                  << size_ << ")" << std::endl;
        return 0;
    }
    return data_[index];
}

bool DynamicArray::pushBack(int value) {
    if (!isValueValid(value)) {
        std::cerr << "Ошибка pushBack: значение " << value << " вне промежутка ["
                  << MIN_VALUE << ", " << MAX_VALUE << "]" << std::endl;
        return false;
    }
    int* newData = new int[size_ + 1];
    for (std::size_t i = 0; i < size_; ++i) {
        newData[i] = data_[i];
    }
    newData[size_] = value;

    delete[] data_;
    data_ = newData;
    ++size_;
    return true;
}

void DynamicArray::add(const DynamicArray& other) {
    for (std::size_t i = 0; i < size_; ++i) {
        int otherValue = (i < other.size_) ? other.data_[i] : 0;
        data_[i] += otherValue;
    }
}

void DynamicArray::sub(const DynamicArray& other) {
    for (std::size_t i = 0; i < size_; ++i) {
        int otherValue = (i < other.size_) ? other.data_[i] : 0;
        data_[i] -= otherValue;
    }
}

bool DynamicArray::isIndexValid(std::size_t index) const {
    return index < size_;
}

bool DynamicArray::isValueValid(int value) {
    return value >= MIN_VALUE && value <= MAX_VALUE;
}
