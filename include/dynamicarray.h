#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <iostream>
#include <new>
#include <stdexcept>
#include <cstdlib>

template<typename T>
class DynamicArray {
private:
    T* data;
    int currentSize;
    int currentcapacity;

    void resize(int newCapacity);
    void ensureCapacity();
public:
    DynamicArray();
    DynamicArray(const DynamicArray& other);
    DynamicArray& operator=(const DynamicArray& other);
    ~DynamicArray();
    void append(const T& element);
    void remove(int index);
    void insert(int index, const T& element);
    T get(int index) const;
    int size() const;
    int capacity() const;
    bool isEmpty() const;
    void clear();
};

#include "../src/dynamicarray.tpp"

#endif // DYNAMICARRAY_H
