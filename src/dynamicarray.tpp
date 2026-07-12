#ifndef DYNAMICARRAY_TPP
#define DYNAMICARRAY_TPP

#ifndef DYNAMICARRAY_H
#include "../include/dynamicarray.h"
#endif

template <typename T> DynamicArray<T>::DynamicArray() {
  currentSize = 0;
  currentcapacity = 1;
  data = static_cast<T *>(std::malloc(currentcapacity * sizeof(T)));
  if (data == nullptr) {
    throw std::bad_alloc();
  }
}

// Copy constructor
template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &other) {
  currentSize = other.currentSize;
  currentcapacity = other.currentcapacity;
  data = static_cast<T *>(std::malloc(currentcapacity * sizeof(T)));
  if (data == nullptr) {
    throw std::bad_alloc();
  }
  for (int i = 0; i < currentSize; ++i) {
    new (data + i) T(other.data[i]);
  }
}

// Destructor
template <typename T> DynamicArray<T>::~DynamicArray() {
  for (int i = 0; i < currentSize; ++i) {
    data[i].~T();
  }
  std::free(data);
}

// Private method to resize the array
template <typename T> void DynamicArray<T>::resize(int newCapacity) {
  T *newData = static_cast<T *>(std::malloc(newCapacity * sizeof(T)));
  if (newData == nullptr) {
    throw std::bad_alloc();
  }
  for (int i = 0; i < currentSize; ++i) {
    new (newData + i) T(data[i]);
    data[i].~T();
  }
  std::free(data);
  data = newData;
  currentcapacity = newCapacity;
}

// Private method to ensure capacity
template <typename T> void DynamicArray<T>::ensureCapacity() {
  if (currentSize >= currentcapacity) {
    resize(currentcapacity * 2);
  }
}

// append method to add an element to the end of the array
template <typename T> void DynamicArray<T>::append(const T &element) {
  ensureCapacity();
  new (data + currentSize) T(element);
  ++currentSize;
}

// remove method to remove an element at a specific index
template <typename T> void DynamicArray<T>::remove(int index) {
  if (index < 0 || index >= currentSize) {
    throw std::out_of_range("Index out of range");
  }
  data[index].~T();
  for (int i = index; i < currentSize - 1; ++i) {
    new (data + i) T(data[i + 1]);
    data[i + 1].~T();
  }
  --currentSize;
}

// get method to retrieve an element at a specific index
template <typename T> T& DynamicArray<T>::get(int index) {
  if (index < 0 || index >= currentSize) {
    throw std::out_of_range("Index out of range");
  }
  return data[index];
}

template <typename T> const T& DynamicArray<T>::get(int index) const {
  if (index < 0 || index >= currentSize) {
    throw std::out_of_range("Index out of range");
  }
  return data[index];
}

// insert method to insert an element at a specific index
template <typename T>
void DynamicArray<T>::insert(int index, const T &element) {
  if (index < 0 || index > currentSize) {
    throw std::out_of_range("Index out of range");
  }
  ensureCapacity();
  for (int i = currentSize; i > index; --i) {
    new (data + i) T(data[i - 1]);
    data[i - 1].~T();
  }
  new (data + index) T(element);
  ++currentSize;
}

template <typename T> void DynamicArray<T>::clear() {
  for (int i = 0; i < currentSize; ++i) {
    data[i].~T();
  }
  currentSize = 0;
}

// copy assignment operator
template <typename T>
DynamicArray<T> &DynamicArray<T>::operator=(const DynamicArray<T> &other) {
  if (this == &other) {
    return *this;
  }

  for (int i = 0; i < currentSize; ++i) {
    data[i].~T();
  }

  if (currentcapacity < other.currentcapacity) {
    std::free(data);
    data = static_cast<T *>(std::malloc(other.currentcapacity * sizeof(T)));
    if (data == nullptr) {
      throw std::bad_alloc();
    }
    currentcapacity = other.currentcapacity;
  }

  currentSize = other.currentSize;
  for (int i = 0; i < currentSize; ++i) {
    new (data + i) T(other.data[i]);
  }

  return *this;
}

// size method to get the current size of the array
template <typename T> int DynamicArray<T>::size() const { return currentSize; }

// capacity method to get the current capacity of the array
template <typename T> int DynamicArray<T>::capacity() const {
  return currentcapacity;
}

// isEmpty method to check if the array is empty
template <typename T> bool DynamicArray<T>::isEmpty() const {
  return currentSize == 0;
}

#endif // DYNAMICARRAY_TPP
