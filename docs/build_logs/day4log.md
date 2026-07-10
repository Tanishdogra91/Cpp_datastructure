# Day 04 Build Log

**Project:** Collections Library (C++)  
**Component:** DynamicArray & LinkedList  
**Phase:** Implementation Phase  
**Date:** 10 July 2026

---

# Shift 01 (09:45 AM – 11:30 AM)

## Goal

Begin the implementation phase of the `DynamicArray` template class by defining its class structure and implementing the first three core member functions.

## Work Completed

- Created `include/dynamicarray.h` for declarations and `src/dynamicarray.tpp` for definitions.
- Defined member variables (`data`, `currentSize`, `currentcapacity`).
- Developed the Default Constructor with raw memory allocation using `malloc()`.
- Developed the Copy Constructor performing deep copy using placement `new`.
- Developed the Destructor invoking element destructors explicitly and freeing memory using `free()`.

## Outcome

Successfully implemented the base skeleton and the first 3 functions of the DynamicArray template.

---

# Shift 02 (11:45 AM – 01:15 PM)

## Goal

Complete all remaining member functions of the `DynamicArray` template class and verify its functionality.

## Work Completed

- Implemented dynamic resizing helper methods (`resize` and `ensureCapacity`).
- Implemented item insertion and modification methods (`append`, `insert`, `remove`).
- Implemented utility methods (`get`, `size`, `capacity`, `isEmpty`, `clear`, `operator=`).
- Wrote basic verification cases in `main.cpp`.

## Outcome

Fully implemented the DynamicArray class and successfully compiled and executed the test driver.

---

# Shift 03 (02:00 PM – 04:00 PM)

## Goal

Implement the `LinkedList` template class and `Node` structure according to the Singly Linked List design proposal.

## Work Completed

- Defined the generic `Node` struct and the `LinkedList` class in `include/linkedlist.h`.
- Implemented construction and memory allocation logic in `src/linkedlist.tpp`.
- Developed insertion methods (`insertFront`, `insertBack`, `insertAt`).
- Developed deletion methods (`deleteFront`, `deleteBack`, `deleteAt`).
- Developed item search and mutation methods (`search`, `get`, `set`, `clear`, `print`).
- Developed copy operations (Copy Constructor and Assignment Operator) to support deep copying.
- Added LinkedList testing logic into `main.cpp`.

## Outcome

LinkedList is fully implemented, integrated with the test runner, and passes all basic operations.

---

# Shift 04 (04:00 PM – 06:25 PM)

## Goal

Clean up file organization, eliminate standalone template inclusion errors in the IDE, and verify final compilation.

## Work Completed

- Updated include paths inside `main.cpp` to resolve headers directly from the root workspace directory.
- Introduced mutual preprocessor guards (`DYNAMICARRAY_TPP` and `LINKEDLIST_TPP`) to resolve recursive compiler index loops when parsing `.tpp` files standalone.
- Ran tests directly using compiler shell commands to verify runtime accuracy.
- Removed temporary CMake build artifacts.

## Outcome

Cleaned up project files. Both template files now parse standalone in IDEs with zero errors, and compiling directly with `g++` works flawlessly.
