#include "include/dynamicarray.h"
#include "include/linkedlist.h"
#include "include/hashmap.h"
#include <iostream>
#include <string>
#include <cassert>

// User-defined Key type
struct CustomKey {
    int id;
    std::string name;

    bool operator==(const CustomKey& other) const {
        return id == other.id && name == other.name;
    }
};

// Custom Hash functor for CustomKey
struct CustomKeyHash {
    std::size_t operator()(const CustomKey& k) const {
        return std::hash<int>{}(k.id) ^ (std::hash<std::string>{}(k.name) << 1);
    }
};

// User-defined Value type with tracking for construction/destruction
struct CustomValue {
    std::string val;
    static int constructorCount;
    static int destructorCount;

    CustomValue() : val("") { constructorCount++; }
    CustomValue(const std::string& v) : val(v) { constructorCount++; }
    CustomValue(const CustomValue& other) : val(other.val) { constructorCount++; }
    ~CustomValue() { destructorCount++; }
};

int CustomValue::constructorCount = 0;
int CustomValue::destructorCount = 0;

// Simple hash functor for std::string
struct StringHash {
    std::size_t operator()(const std::string& s) const {
        std::size_t hash = 0;
        for (char c : s) {
            hash = hash * 31 + c;
        }
        return hash;
    }
};

int main() {
  std::cout << "=== DynamicArray Code ===" << std::endl;
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

  std::cout << "\n=== LinkedList Code ===" << std::endl;
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

  std::cout << "\n=== HashMap Code ===" << std::endl;
  
  std::cout << "--- Testing Constructors & Rule of Three ---" << std::endl;
  {
      HashMap<std::string, int, StringHash> map1(8);
      std::cout << "Successfully constructed map1 (capacity 8)." << std::endl;
      
      HashMap<std::string, int, StringHash> map2 = map1; // Copy constructor
      std::cout << "Successfully copy-constructed map2 from map1." << std::endl;
      
      HashMap<std::string, int, StringHash> map3;
      map3 = map2; // Copy assignment operator
      std::cout << "Successfully copy-assigned map3 from map2." << std::endl;
  }
  std::cout << "Successfully destructed all maps." << std::endl;

  std::cout << "\n--- Testing with User-defined Types ---" << std::endl;
  {
      HashMap<CustomKey, CustomValue, CustomKeyHash> customMap1(4);
      std::cout << "Successfully constructed customMap1." << std::endl;
      
      HashMap<CustomKey, CustomValue, CustomKeyHash> customMap2(customMap1);
      std::cout << "Successfully copy-constructed customMap2." << std::endl;
  }
  std::cout << "Successfully destructed all custom maps." << std::endl;

  return 0;
}