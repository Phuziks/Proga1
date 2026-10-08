#include "DynamicArray.h"

#include <iostream>
#include <stdexcept>
#include <string>

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

void DynamicArray::set(std::size_t index, int value) {
    checkIndex(index);
    checkValue(value);
    data_[index] = value;
}

int DynamicArray::get(std::size_t index) const {
    checkIndex(index);
    return data_[index];
}

void DynamicArray::pushBack(int value) {
    checkValue(value);

    int* newData = new int[size_ + 1];
    for (std::size_t i = 0; i < size_; ++i) {
        newData[i] = data_[i];
    }
    newData[size_] = value;

    delete[] data_;
    data_ = newData;
    ++size_;
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

void DynamicArray::checkIndex(std::size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("индекс " + std::to_string(index) +
                                " вне границ массива (размер " + std::to_string(size_) + ")");
    }
}

void DynamicArray::checkValue(int value) {
    if (value < MIN_VALUE || value > MAX_VALUE) {
        throw std::invalid_argument("значение " + std::to_string(value) + " вне промежутка [" +
                                    std::to_string(MIN_VALUE) + ", " +
                                    std::to_string(MAX_VALUE) + "]");
    }
}
