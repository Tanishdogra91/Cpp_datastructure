# Phase 0 – Linked List Design Proposal

**Project:** Collections Library (C++)  
**Component:** Linked List  
**Phase:** 0 – Design Proposal  
**Version:** 1.0

---

# Objective

The objective of designing the Linked List is to build a reusable, dynamically allocated linear data structure capable of efficiently storing and managing elements in heap memory. Unlike arrays, a Linked List does not require contiguous memory allocation and can grow dynamically by allocating individual nodes using **malloc()** during runtime and releasing them using **free()**.

This design focuses on understanding pointer manipulation, dynamic memory allocation, object ownership, node relationships, safe memory management, and efficient insertion and deletion operations while maintaining clean software architecture.

The Linked List will serve as the second core component of the Collections Library and will later support more advanced data structures such as HashMap using Separate Chaining.

---

# Section 1 – Public API

## Overview

The Linked List provides a sequential collection of dynamically allocated nodes connected through pointers. Each operation has been carefully selected to satisfy the project requirements while maintaining simplicity and extensibility.

---

## Proposed Public Interface

```cpp
template <typename T>
class LinkedList
{
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
```

---

# LinkedList API Design Documentation

This part explains each public API using a consistent format:

- **Return Type**
- **Parameters**
- **Explanation**
- **Time Complexity**
- **Why this design?**

---

# Constructor

## `LinkedList();`

### Return Type
**None**

A constructor does not have a return type because its purpose is to initialize a newly created object.

### Parameters
**None**

### Explanation
Creates an empty linked list by initializing the internal data members such as:

- `head = nullptr`
- `size = 0`

### Time Complexity
**O(1)**

### Why this design?
Every linked list should begin in a valid empty state so that insertions and other operations can be performed immediately.

---

# Destructor

## `~LinkedList();`

### Return Type
**None**

A destructor never returns a value.

### Parameters
**None**

### Explanation
Traverses the linked list and deallocates every dynamically allocated node before the object is destroyed.

### Time Complexity
**O(n)**

### Why this design?
Every node is stored in heap memory, so every allocated node must be freed to avoid memory leaks.

---

# Copy Constructor

## `LinkedList(const LinkedList<T>& other);`

### Return Type
**None**

Constructors never have a return type.

### Parameters

### `const LinkedList<T>& other`

| Part | Meaning |
|------|---------|
| `const` | Prevents modification of the source list |
| `LinkedList<T>` | Generic linked list type |
| `&` | Passes by reference to avoid copying the entire list |
| `other` | Source object that will be copied |

### Explanation
Creates a completely independent copy of another linked list by performing a **deep copy** of all nodes.

### Time Complexity
**O(n)**

### Why this design?
Passing by constant reference is efficient because it avoids unnecessary copying while ensuring the original object cannot be modified.

---

# Copy Assignment Operator

## `LinkedList<T>& operator=(const LinkedList<T>& other);`

### Return Type

### `LinkedList<T>&`

Returns a reference to the current object.

This enables assignment chaining such as:

```cpp
a = b = c;
```

without creating unnecessary temporary objects.

### Parameters

### `const LinkedList<T>& other`

| Part | Meaning |
|------|---------|
| `const` | Prevents modification of the source list |
| `&` | Avoids copying the complete object |
| `other` | Source linked list |

### Explanation
Deletes all existing nodes of the current object and creates a deep copy of another linked list.

Also checks for self-assignment:

```cpp
list = list;
```

### Time Complexity
**O(n)**

### Why this design?
Returning a reference follows standard C++ conventions and allows assignment chaining.

---

# insertFront

## `void insertFront(const T& value);`

### Return Type

### `void`

No value is returned because the function simply modifies the linked list.

### Parameters

### `const T& value`

| Part | Meaning |
|------|---------|
| `const` | Prevents modification of the input value |
| `T` | Supports any data type |
| `&` | Avoids copying large objects |
| `value` | Data to insert |

### Explanation
Creates a new node and inserts it at the beginning of the linked list.

### Time Complexity
**O(1)**

### Why this design?
Passing by constant reference improves performance and supports generic programming.

---

# insertBack

## `void insertBack(const T& value);`

### Return Type

### `void`

No value needs to be returned.

### Parameters

### `const T& value`

Same reasoning as `insertFront()`.

### Explanation
Creates a new node and inserts it at the end of the linked list.

### Time Complexity

- With tail pointer → **O(1)**
- Without tail pointer → **O(n)**

### Why this design?
Appending elements at the end is one of the most common linked list operations.

---

# insertAt

## `void insertAt(int index, const T& value);`

### Return Type

### `void`

No return value is required.

### Parameters

### `int index`

Specifies the position where the new node should be inserted.

### `const T& value`

The value that will be stored inside the new node.

### Explanation
Traverses the linked list until the specified index and inserts a new node.

### Time Complexity
**O(n)**

### Why this design?
Allows insertion at any valid position within the list.

---

# deleteFront

## `void deleteFront();`

### Return Type

### `void`

The function performs deletion and therefore returns nothing.

### Parameters
None

### Explanation
Removes the first node from the linked list.

### Time Complexity
**O(1)**

### Why this design?
Deleting the first node only requires updating the head pointer.

---

# deleteBack

## `void deleteBack();`

### Return Type

### `void`

### Parameters
None

### Explanation
Deletes the last node from the linked list.

### Time Complexity

- Singly Linked List → **O(n)**
- Doubly Linked List with tail pointer → **O(1)**

### Why this design?
Provides an interface for removing the last element of the list.

---

# deleteAt

## `void deleteAt(int index);`

### Return Type

### `void`

### Parameters

### `int index`

Represents the position of the node to be deleted.

### Explanation
Traverses to the specified position and removes that node from the linked list.

### Time Complexity
**O(n)**

### Why this design?
Allows deletion from any valid position.

---

# search

## `bool search(const T& value) const;`

### Return Type

### `bool`

Returns

- `true` → Element exists
- `false` → Element does not exist

### Parameters

### `const T& value`

The value that should be searched.

### Explanation
Traverses the linked list and compares every node with the given value.

### Time Complexity
**O(n)**

### Why this design?
A boolean value clearly indicates whether the element was found.

---

# get

## `T get(int index) const;`

### Return Type

### `T`

Returns a copy of the value stored at the specified index.

### Parameters

### `int index`

Position of the desired element.

### Explanation
Traverses the linked list until the specified index and returns the stored value.

If the index is invalid, an exception should be thrown.

### Time Complexity
**O(n)**

### Why this design?
Returning the value directly makes the API easy to use.

> **Alternative Design:**  
> Many standard libraries return `const T&` instead of `T` to avoid copying large objects.

---

# set

## `void set(int index, const T& value);`

### Return Type

### `void`

No value needs to be returned because the function only updates an existing node.

### Parameters

### `int index`

Specifies which node should be modified.

### `const T& value`

The new value that will replace the old value.

### Explanation
Updates the value stored at the specified position.

### Time Complexity
**O(n)**

### Why this design?
Separates data modification from data retrieval, making the interface easier to understand.

---

# isEmpty

## `bool isEmpty() const;`

### Return Type

### `bool`

Returns

- `true` → List contains no nodes
- `false` → List contains one or more nodes

### Parameters
None

### Explanation
Checks whether the linked list currently contains any elements.

### Time Complexity
**O(1)**

### Why this design?
A boolean return type naturally represents the empty or non-empty state of the list.

---

# size

## `int size() const;`

### Return Type

### `int`

Returns the total number of nodes in the linked list.

### Parameters
None

### Explanation
Returns the internally maintained node count.

### Time Complexity
**O(1)** (when a size member variable is maintained)

### Why this design?
Allows users to determine the length of the list instantly without traversing every node.

---

# clear

## `void clear();`

### Return Type

### `void`

### Parameters
None

### Explanation
Deletes every node from the linked list and resets the object to its initial empty state.

### Time Complexity
**O(n)**

### Why this design?
Allows the same linked list object to be reused instead of destroying and recreating it.

---

# print

## `void print() const;`

### Return Type

### `void`

Printing is a side effect, so no value needs to be returned.

### Parameters
None

### Explanation
Traverses the linked list and displays every stored element.

### Time Complexity
**O(n)**

### Why this design?
Provides a convenient debugging and visualization function.

---

# Summary of Return Types

| Return Type | Purpose | Example |
|-------------|---------|---------|
| `void` | Performs an operation without returning a value | `insertBack()`, `deleteFront()`, `clear()` |
| `bool` | Indicates success/failure or true/false | `search()`, `isEmpty()` |
| `int` | Returns a numeric result | `size()` |
| `T` | Returns a copy of the stored element | `get()` |
| `LinkedList<T>&` | Returns the current object for chaining | `operator=()` |

---

# Summary of Parameter Types

| Parameter Type | Why It Is Used | Example |
|----------------|----------------|---------|
| `const T&` | Avoids copying while preventing modification of the input value | `insertFront(const T& value)` |
| `int` | Represents an index or position within the list | `insertAt(int index, const T& value)` |
| `const LinkedList<T>&` | Efficiently accepts another linked list without copying it | Copy constructor, assignment operator |

---

# Summary of `const` Usage

| Syntax | Meaning | Example |
|--------|---------|---------|
| `const T&` | Read-only reference parameter | `insertBack(const T& value)` |
| `const LinkedList<T>&` | Read-only reference to another linked list | Copy constructor |
| `function() const` | Guarantees that the function will not modify the linked list object | `size() const`, `search() const`, `print() const` |

# Section 2 – Internal Representation

## Selected Design

After evaluating multiple alternatives, the proposed implementation will use a **Singly Linked List**.

Reasons include:

- Lower memory consumption
- Simpler implementation
- Satisfies every project requirement
- Easier debugging
- Better for understanding pointers

---

## Memory Management Policy

All dynamic memory allocations in the Linked List will be performed using the C Standard Library functions **malloc()** and **free()**.

The C++ allocation operators **new** and **delete** will not be used. This ensures consistent manual memory management throughout the Collections Library and aligns with the implementation constraints of the project.

---

## Node Structure

```cpp
template <typename T>
class Node
{
public:

    T data;

    Node<T>* next;
};
```

Each node stores

- Data of type **T**
- Pointer to the next node

---

## Linked List Data Members

```cpp
template <typename T>
class LinkedList
{
private:

    Node<T>* head;

    int length;
};
```

---

## Memory Layout

**Diagram**

![Memory Diagram](./linkedlist_memorydiagram.png)

---

## Object Ownership

The Linked List object owns every node allocated during runtime.

Every node allocated using **malloc()** becomes the responsibility of the Linked List object and must be released exactly once using **free()**.

Responsibilities include

- Allocating nodes
- Connecting nodes
- Disconnecting nodes
- Destroying nodes
- Preventing memory leaks

---

## Destructor Strategy

Destructor algorithm

1. Start from head.
2. Save the pointer to the next node.
3. Release the current node using **free()**.
4. Move to the next node.
5. Continue until `nullptr`.
6. Reset head.
7. Reset length.

---

## Copy Strategy

The Linked List **will not share nodes**.

Instead,

every copied list receives its own independent nodes.

During copying,

- Allocate new nodes using **malloc()**
- Copy the stored data into the new nodes
- Rebuild the pointer links
- Maintain independent ownership

This prevents

- Double free
- Dangling pointers
- Shared ownership
- Memory corruption

---

# Section 3 – Complexity Analysis

| Operation | Best | Average | Worst | Reason |
|------------|------|----------|--------|--------|
| insertFront() | O(1) | O(1) | O(1) | Only updates head pointer |
| insertBack() | O(n) | O(n) | O(n) | Traverses entire list |
| insertAt() | O(1) | O(n) | O(n) | Best case when inserting at the beginning; otherwise traversal is required |
| deleteFront() | O(1) | O(1) | O(1) | Removes first node |
| deleteBack() | O(n) | O(n) | O(n) | Must locate previous node |
| deleteAt() | O(1) | O(n) | O(n) | Best case when deleting the first node; otherwise traversal is required |
| search() | O(1) | O(n) | O(n) | Best case when value is found at the head; otherwise sequential traversal |
| get() | O(1) | O(n) | O(n) | Best case for index 0; otherwise requires traversal |
| set() | O(1) | O(n) | O(n) | Best case for index 0; otherwise requires traversal |
| size() | O(1) | O(1) | O(1) | Maintained using length variable |
| isEmpty() | O(1) | O(1) | O(1) | Checks length |
| clear() | O(n) | O(n) | O(n) | Releases every allocated node | print() | O(n) | O(n) | O(n) | Visits every node to display all stored element in sequence |

---

# Section 4 – Design Decisions

## Decision 1

### Singly Linked List instead of Doubly Linked List

**Chosen because**

- Less memory usage
- One pointer per node
- Easier implementation
- Meets all assignment requirements

---

## Decision 2

### Maintain Length Variable

Maintaining an internal node count allows

- O(1) size()
- Easier boundary validation
- Better API performance

---

## Decision 3

### Dynamic Allocation

Every node will be allocated individually using

```cpp
malloc()
```

and released using

```cpp
free()
```

Using **malloc()** and **free()** provides explicit control over heap memory while reinforcing manual memory management concepts such as allocation, ownership, and deallocation. This strategy aligns with the implementation constraints of the project.

---

## Decision 4

### Deep Copy

Every Linked List object owns its own memory.

Copying creates

- New nodes allocated using **malloc()**
- Independent memory
- Independent ownership

This avoids

- Double free
- Dangling pointers
- Shared ownership

---

## Decision 5

### Error Handling

Boundary conditions will be checked before every indexed operation.

Invalid indices will not modify the data structure.

The final error handling strategy will be documented during implementation.

---

## Decision 6

### Generic Design Using Templates

The Linked List will be implemented as a template class rather than restricting it to a single data type.

Chosen because

- Increases reusability
- Stores any user-defined or primitive type
- Eliminates duplicate implementations for different data types
- Makes the Collections Library consistent with the Dynamic Array and future HashMap

---