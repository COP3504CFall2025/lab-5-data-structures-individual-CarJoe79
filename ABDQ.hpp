#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ() {
        capacity_ = 4;
        data_ = new T[capacity_];
        front_ = 0;
        back_ = 0;
        size_ = 0;
    };
    explicit ABDQ(std::size_t capacity) {
        capacity_ = capacity;
        data_ = new T[capacity_];
        front_ = 0;
        back_ = 0;
        size_ = 0;
    };
    ABDQ(const ABDQ& other) {
        capacity_ = other.capacity_;
        front_ = other.front_;
        back_ = other.back_;
        size_ = other.size_;
        data_ = new T[capacity_];

        for (size_t i = 0; i < other.capacity_; i++) this->data_[i] = other.data_[i];
    };
    ABDQ(ABDQ&& other) noexcept {
        capacity_ = other.capacity_;
        data_ = other.data_;
        front_ = other.front_;
        back_ = other.back_;
        size_ = other.size_;

        other.data_ = nullptr;
        other.capacity_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        other.size_ = 0;
    };
    ABDQ& operator=(const ABDQ& other) {
        if (this == &other) return *this;

        delete[] data_;

        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        data_ = new T[capacity_];

        for (size_t i = 0; i < other.capacity_; i++) this->data_[i] = other.data_[i];
        return *this;
    };
    ABDQ& operator=(ABDQ&& other) noexcept {
        if (this == &other) return *this;

        delete[] data_;

        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        data_ = other.data_;

        other.capacity_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        other.size_ = 0;
        other.data_ = nullptr;

        return *this;
    };
    ~ABDQ() {
        delete[] data_;

        data_ = nullptr;
        capacity_ = 0;
        size_ = 0;
        front_ = 0;
        back_ = 0;
    };

    // Insertion
    void pushFront(const T& item) override {
        if (size_ == capacity_) {
            capacity_ *= SCALE_FACTOR;
            T* new_array_ = new T[capacity_];

            for (size_t i = 0; i < size_; i++) new_array_[i] = data_[i];

            delete[] data_;

            data_ = new_array_;
        }

        if (size_ != 0) {
            back_++;
            for (int i = size_; i > 0; i--) data_[i] = data_[i - 1];
        }

        data_[0] = item;

        size_++;
    };
    void pushBack(const T& item) override {
        if (size_ == capacity_) {
            capacity_ *= SCALE_FACTOR;
            T* new_array_ = new T[capacity_];

            for (size_t i = 0; i < size_; i++) new_array_[i] = data_[i];

            delete[] data_;

            data_ = new_array_;
        }
        if (size_ != 0) {
            data_[size_] = item;
            back_++;
        }
        else data_[0] = item;
        size_++;
    };

    // Deletion
    T popFront() override {
        if (size_ == 0) throw std::runtime_error("");
        T value = data_[0];
        size_--;
        back_--;
        for (size_t i = 0; i < size_; i++) data_[i] = data_[i + 1];
        if (size_ <= capacity_ / 4) {
            capacity_ /= SCALE_FACTOR;
            T* new_array_ = new T[capacity_];

            for (size_t i = 0; i < size_; i++) new_array_[i] = data_[i];

            delete[] data_;

            data_ = new_array_;
        }
        return value;
    };
    T popBack() override {
        if (size_ == 0) throw std::runtime_error("");
        T value = data_[0];
        data_[back_] = value;
        size_--;
        back_--;
        if (size_ <= capacity_ / 4) {
            capacity_ /= SCALE_FACTOR;
            T* new_array_ = new T[capacity_];

            for (size_t i = 0; i < size_; i++) new_array_[i] = data_[i];

            delete[] data_;

            data_ = new_array_;
        }
        return value;
    };

    // Access
    const T& front() const override {return data_[front_];};
    const T& back() const override {return data_[back_];};

    // Getters
    std::size_t getSize() const noexcept override {return size_;};
};
