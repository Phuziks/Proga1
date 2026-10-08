#pragma once

#include <cstddef>

class DynamicArray {
public:
    static const int MIN_VALUE = -100;
    static const int MAX_VALUE = 100;

    explicit DynamicArray(std::size_t size);
    DynamicArray(const DynamicArray& other);
    DynamicArray& operator=(const DynamicArray& other) = delete;
    ~DynamicArray();

    std::size_t size() const;
    void print() const;

    bool set(std::size_t index, int value);
    int get(std::size_t index) const;

    bool pushBack(int value);

    void add(const DynamicArray& other);
    void sub(const DynamicArray& other);

private:
    int* data_;
    std::size_t size_;

    bool isIndexValid(std::size_t index) const;
    static bool isValueValid(int value);
};
