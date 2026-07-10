#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <new>
#include <stdexcept>
#include <cstdlib>

template <typename T>
class Node {
public:
    T data;
    Node<T>* next;
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    int length;

public:
    // Constructor
    LinkedList();

    // Destructor
    ~LinkedList();

    // Rule of Three
    LinkedList(const LinkedList<T>& other);
    LinkedList<T>& operator=(const LinkedList<T>& other);

    // Insertion
    void insertFront(const T& value);
    void insertBack(const T& value);
    void insertAt(int index, const T& value);

    // Deletion
    void deleteFront();
    void deleteBack();
    void deleteAt(int index);

    // Search
    bool search(const T& value) const;

    // Access
    T get(int index) const;
    void set(int index, const T& value);

    // Utility
    bool isEmpty() const;
    int size() const;
    void clear();
    void print() const;
};

#include "../src/linkedlist.tpp"

#endif // LINKEDLIST_H
