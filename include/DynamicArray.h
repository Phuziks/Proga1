#pragma once

#include <cmath>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <typeinfo>

template <typename T>
class DynamicArray {
public:
    static const int MIN_VALUE = -100;
    static const int MAX_VALUE = 100;

    class Reference {
    public:
        Reference(DynamicArray& arr, std::size_t index) : index_(index), arr(arr) {

        }
        Reference& operator=(const T& value) {
            arr.set(index_, value);
            return *this;

        }
        operator T&() const {
            return arr.get(index_);
        }
    private:
        DynamicArray& arr;
        std::size_t index_;
    };

    explicit DynamicArray(std::size_t size)
        : data_(new T[size]()), size_(size) {
    }

    DynamicArray(const DynamicArray& other)
        : data_(new T[other.size_]), size_(other.size_) {
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    DynamicArray& operator=(const DynamicArray& other) = delete;

    ~DynamicArray() {
        delete[] data_;
    }

    std::size_t size() const {
        return size_;
    }

    void print() const {
        std::cout << *this << std::endl;
    }

    void set(std::size_t index, const T& value) {
        checkIndex(index);
        checkValue(value);
        data_[index] = value;
    }

    T get(std::size_t index) const {
        checkIndex(index);
        return data_[index];
    }

    void pushBack(const T& value) {
        checkValue(value);

        T* newData = new T[size_ + 1];
        for (std::size_t i = 0; i < size_; ++i) {
            newData[i] = data_[i];
        }
        newData[size_] = value;

        delete[] data_;
        data_ = newData;
        ++size_;
    }

    void add(const DynamicArray& other) {
        for (std::size_t i = 0; i < size_; ++i) {
            T otherValue = (i < other.size_) ? other.data_[i] : T();
            data_[i] = data_[i] + otherValue;
        }
    }

    void sub(const DynamicArray& other) {
        for (std::size_t i = 0; i < size_; ++i) {
            T otherValue = (i < other.size_) ? other.data_[i] : T();
            data_[i] = data_[i] - otherValue;
        }
    }

    double distance(const DynamicArray& other) const {
        if constexpr (!std::is_arithmetic_v<T>) {
            throw std::bad_typeid();
        } else {
            if (size_ != other.size_) {
                throw std::invalid_argument("размеры массивов не совпадают: " +
                                            std::to_string(size_) + " и " +
                                            std::to_string(other.size_));
            }
            double sum = 0;
            for (std::size_t i = 0; i < size_; ++i) {
                double diff = static_cast<double>(data_[i]) - static_cast<double>(other.data_[i]);
                sum += diff * diff;
            }
            return std::sqrt(sum);
        }
    }

    friend std::ostream& operator<<(std::ostream& out, const DynamicArray& array) {
        out << "[";
        for (std::size_t i = 0; i < array.size_; ++i) {
            if (i > 0) {
                out << ", ";
            }
            out << array.data_[i];
        }
        out << "]";
        return out;
    }

    Reference operator[](std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("out of range");
        }
        return Reference(*this, index);
    }

    bool operator==(DynamicArray& other) {
        if (size_ != other.size_) {
            return false;
        }
        for (std::size_t i = 0; i < size_; ++i) {
            if (data_[i] != other.data_[i]) {
                return false;
            }
        }
        return true;
    }

    DynamicArray& operator+=(const DynamicArray& other) {
        add(other);
        return *this;
    }

    DynamicArray& operator-=(const DynamicArray& other) {
        sub(other);
        return *this;
    }

    DynamicArray& operator+=(const T& value) {
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = data_[i] + value;
        }
        return *this;
    }

    DynamicArray& operator-=(const T& value) {
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = data_[i] - value;
        }
        return *this;
    }

    T* begin() { return data_; }
    T* end()   { return data_ + size_; }

    const T* begin() const { return data_; }
    const T* end()   const { return data_ + size_; }

    bool operator!=(DynamicArray& other) {
        return !(*this == other);
    }

private:
    T* data_;
    std::size_t size_;

    void checkIndex(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("индекс " + std::to_string(index) +
                                    " вне границ массива (размер " + std::to_string(size_) + ")");
        }
    }

    static void checkValue(const T& value) {
        if constexpr (std::is_integral_v<T>) {
            if (value < MIN_VALUE || value > MAX_VALUE) {
                throw std::invalid_argument("значение " + std::to_string(value) +
                                            " вне промежутка [" + std::to_string(MIN_VALUE) +
                                            ", " + std::to_string(MAX_VALUE) + "]");
            }
        }
    }
};
