#ifndef LINKEDLIST_TPP
#define LINKEDLIST_TPP

#ifndef LINKEDLIST_H
#include "../include/linkedlist.h"
#endif

// Constructor
template <typename T> LinkedList<T>::LinkedList() {
  head = nullptr;
  length = 0;
}

// Destructor
template <typename T> LinkedList<T>::~LinkedList() { clear(); }

// Copy Constructor
template <typename T> LinkedList<T>::LinkedList(const LinkedList<T> &other) {
  head = nullptr;
  length = 0;
  if (other.head == nullptr) {
    return;
  }

  Node<T> *current = other.head;
  Node<T> *tail = nullptr;
  while (current != nullptr) {
    Node<T> *newNode = static_cast<Node<T> *>(std::malloc(sizeof(Node<T>)));
    if (newNode == nullptr) {
      clear();
      throw std::bad_alloc();
    }
    new (newNode) Node<T>{current->data, nullptr};

    if (head == nullptr) {
      head = newNode;
    } else {
      tail->next = newNode;
    }
    tail = newNode;
    length++;
    current = current->next;
  }
}

// Assignment Operator
template <typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &other) {
  if (this == &other) {
    return *this;
  }
  clear();
  if (other.head == nullptr) {
    return *this;
  }

  Node<T> *current = other.head;
  Node<T> *tail = nullptr;
  while (current != nullptr) {
    Node<T> *newNode = static_cast<Node<T> *>(std::malloc(sizeof(Node<T>)));
    if (newNode == nullptr) {
      clear();
      throw std::bad_alloc();
    }
    new (newNode) Node<T>{current->data, nullptr};

    if (head == nullptr) {
      head = newNode;
    } else {
      tail->next = newNode;
    }
    tail = newNode;
    length++;
    current = current->next;
  }
  return *this;
}

// Insertion at the front
template <typename T> void LinkedList<T>::insertFront(const T &value) {
  Node<T> *newNode = static_cast<Node<T> *>(std::malloc(sizeof(Node<T>)));
  if (newNode == nullptr) {
    throw std::bad_alloc();
  }
  new (newNode) Node<T>{value, head};
  head = newNode;
  length++;
}

// Insertion at the back
template <typename T> void LinkedList<T>::insertBack(const T &value) {
  Node<T> *newNode = static_cast<Node<T> *>(std::malloc(sizeof(Node<T>)));
  if (newNode == nullptr) {
    throw std::bad_alloc();
  }
  new (newNode) Node<T>{value, nullptr};

  if (head == nullptr) {
    head = newNode;
  } else {
    Node<T> *current = head;
    while (current->next != nullptr) {
      current = current->next;
    }
    current->next = newNode;
  }
  length++;
}

// Insertion at a specific index
template <typename T> void LinkedList<T>::insertAt(int index, const T &value) {
  if (index < 0 || index > length) {
    throw std::out_of_range("Index out of range");
  }
  if (index == 0) {
    insertFront(value);
  } else {
    Node<T> *newNode = static_cast<Node<T> *>(std::malloc(sizeof(Node<T>)));
    if (newNode == nullptr) {
      throw std::bad_alloc();
    }
    new (newNode) Node<T>{value, nullptr};

    Node<T> *current = head;
    for (int i = 0; i < index - 1; ++i) {
      current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
    length++;
  }
}

// Deletion from the front
template <typename T> void LinkedList<T>::deleteFront() {
  if (head == nullptr) {
    throw std::out_of_range("List is empty");
  }
  Node<T> *temp = head;
  head = head->next;
  temp->~Node<T>();
  std::free(temp);
  length--;
}

// Deletion from the back
template <typename T> void LinkedList<T>::deleteBack() {
  if (head == nullptr) {
    throw std::out_of_range("List is empty");
  }
  if (head->next == nullptr) {
    head->~Node<T>();
    std::free(head);
    head = nullptr;
  } else {
    Node<T> *current = head;
    while (current->next->next != nullptr) {
      current = current->next;
    }
    Node<T> *temp = current->next;
    current->next = nullptr;
    temp->~Node<T>();
    std::free(temp);
  }
  length--;
}

// Deletion at a specific index
template <typename T> void LinkedList<T>::deleteAt(int index) {
  if (index < 0 || index >= length) {
    throw std::out_of_range("Index out of range");
  }
  if (index == 0) {
    deleteFront();
  } else {
    Node<T> *current = head;
    for (int i = 0; i < index - 1; ++i) {
      current = current->next;
    }
    Node<T> *temp = current->next;
    current->next = temp->next;
    temp->~Node<T>();
    std::free(temp);
    length--;
  }
}

// Search for a value
template <typename T> bool LinkedList<T>::search(const T &value) const {
  Node<T> *current = head;
  while (current != nullptr) {
    if (current->data == value) {
      return true;
    }
    current = current->next;
  }
  return false;
}

// Get value at an index
template <typename T> T LinkedList<T>::get(int index) const {
  if (index < 0 || index >= length) {
    throw std::out_of_range("Index out of range");
  }
  Node<T> *current = head;
  for (int i = 0; i < index; ++i) {
    current = current->next;
  }
  return current->data;
}

// Set value at an index
template <typename T> void LinkedList<T>::set(int index, const T &value) {
  if (index < 0 || index >= length) {
    throw std::out_of_range("Index out of range");
  }
  Node<T> *current = head;
  for (int i = 0; i < index; ++i) {
    current = current->next;
  }
  current->data = value;
}

// Check if list is empty
template <typename T> bool LinkedList<T>::isEmpty() const {
  return length == 0;
}

// Get size of list
template <typename T> int LinkedList<T>::size() const { return length; }

// Clear the list
template <typename T> void LinkedList<T>::clear() {
  Node<T> *current = head;
  while (current != nullptr) {
    Node<T> *temp = current;
    current = current->next;
    temp->~Node<T>();
    std::free(temp);
  }
  head = nullptr;
  length = 0;
}

// Print the list
template <typename T> void LinkedList<T>::print() const {
  Node<T> *current = head;
  while (current != nullptr) {
    std::cout << current->data << " -> ";
    current = current->next;
  }
  std::cout << "nullptr" << std::endl;
}

#endif // LINKEDLIST_TPP
