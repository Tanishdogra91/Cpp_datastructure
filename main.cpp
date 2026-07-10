#include "include/dynamicarray.h"
#include "include/linkedlist.h"
#include <iostream>

int main() {
  std::cout << "=== DynamicArray Demo ===" << std::endl;
  DynamicArray<int> arr;
  arr.append(1);
  arr.append(2);
  arr.append(3);

  std::cout << "Size: " << arr.size() << std::endl;
  std::cout << "Capacity: " << arr.capacity() << std::endl;

  for (int i = 0; i < arr.size(); ++i) {
    std::cout << "Element at index " << i << ": " << arr.get(i) << std::endl;
  }

  arr.remove(1);
  std::cout << "After removing element at index 1:" << std::endl;
  for (int i = 0; i < arr.size(); ++i) {
    std::cout << "Element at index " << i << ": " << arr.get(i) << std::endl;
  }

  std::cout << "Is array empty? " << (arr.isEmpty() ? "Yes" : "No")
            << std::endl;

  arr.insert(1, 5);
  std::cout << "After inserting 5 at index 1:" << std::endl;
  for (int i = 0; i < arr.size(); ++i) {
    std::cout << "Element at index " << i << ": " << arr.get(i) << std::endl;
  }

  std::cout << "\n=== LinkedList Demo ===" << std::endl;
  LinkedList<int> list;
  list.insertFront(10);
  list.insertBack(20);
  list.insertBack(30);
  list.insertAt(1, 15);

  std::cout << "Initial list: ";
  list.print();

  std::cout << "Size: " << list.size() << std::endl;
  std::cout << "Search 20: " << (list.search(20) ? "Found" : "Not Found") << std::endl;
  std::cout << "Search 100: " << (list.search(100) ? "Found" : "Not Found") << std::endl;

  list.deleteAt(1);
  std::cout << "After deleting at index 1: ";
  list.print();

  list.deleteFront();
  std::cout << "After deleting front: ";
  list.print();

  list.deleteBack();
  std::cout << "After deleting back: ";
  list.print();

  std::cout << "Is list empty? " << (list.isEmpty() ? "Yes" : "No") << std::endl;

  return 0;
}