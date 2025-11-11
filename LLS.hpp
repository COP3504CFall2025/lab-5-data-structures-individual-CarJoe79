#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <cstdlib>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS() {};

    // Insertion
    void push(const T& item) override {
        list.addHead(item);
    };

    // Deletion
    T pop() override {
        T item = list.getHead()->data;
        list.removeHead();
        return item;
    };

    // Access
    T peek() const override {
        return list.getHead()->data;
    };

    //Getters
    std::size_t getSize() const noexcept override {
        return list.getCount();
    };
};