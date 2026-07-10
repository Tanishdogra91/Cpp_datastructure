# Journal Entry – Day 04

**Project:** Collections Library (C++)  
**Component:** DynamicArray & LinkedList  
**Phase:** Implementation Phase  
**Date:** 10 July 2026

---

# Introduction

Today, I transitioned from the design phase to the implementation phase of the **Collections Library**. The goal for the day was to implement two primary data structures: **DynamicArray** and **LinkedList**, ensuring manual memory management using `malloc()` and placement `new` was done correctly, and organizing the files such that declarations are in the headers (`.h`) and implementations are in the template implementation files (`.tpp`).

---

# DynamicArray Implementation (Morning Sessions)

During the morning shifts, I focused on developing the **DynamicArray** component. 

- **First Half**: I laid down the basic skeleton of the class, implemented the memory management hooks, and developed the first three core member functions:
  - Default Constructor (allocating raw memory)
  - Copy Constructor (copying elements deep copy)
  - Destructor (explicitly calling destructors on existing objects and freeing raw memory)
- **Second Half**: I expanded the implementation to include all other utility and modification methods:
  - Insertion and appending (`append`, `insert`)
  - Element retrieval and resizing (`get`, `resize`, `ensureCapacity`)
  - Modification and cleaning (`remove`, `clear`, assignment operator)

This completed the full functional implementation of the DynamicArray.

---

# LinkedList Implementation (Afternoon Session)

In the afternoon, I turned my attention to the **LinkedList** component. Following the singly-linked list design proposal, I implemented the class template along with the internal `Node` structure:

- Managed allocation of individual list nodes dynamically using `malloc()`.
- Implemented node insertion at different positions (`insertFront`, `insertBack`, `insertAt`).
- Implemented node deletion and memory cleanup (`deleteFront`, `deleteBack`, `deleteAt`).
- Created search, getter, and setter methods (`search`, `get`, `set`).
- Implemented the Rule of Three (Copy Constructor, Assignment Operator, and Destructor) to ensure proper deep copies and avoid dangling pointers or double frees.

---

# File Organization and IDE Enhancements

A significant portion of the development was focused on structuring template classes correctly for modern compilation and IDE parsing:
- Kept declarations in `.h` files under the `include/` directory.
- Kept implementation definitions in `.tpp` files under the `src/` directory.
- Implemented a mutual header guard pattern (`DYNAMICARRAY_TPP` and `LINKEDLIST_TPP`) to resolve recursive `#include` issues in IDE compilers (like Clangd), eliminating red squiggle parser warnings when viewing template implementation files standalone.

---

# Key Learnings

- **Template Structuring**: Learned the correct C++ practices for separating template declarations and implementations using `.h` and `.tpp` files.
- **Recursive Includes**: Discovered how cyclic dependencies happen during IDE standalone parses and how to solve them using compiler guards.
- **placement new**: Solidified understanding of separating raw memory allocation (`malloc`) from object construction (`placement new`) and destruction (`~T()`).
