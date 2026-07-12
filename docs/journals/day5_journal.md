# Journal Entry – Day 05

**Project:** Collections Library (C++)  
**Component:** HashMap  
**Phase:** Implementation Phase  
**Date:** 11 July 2026

---

# Introduction

Today, I worked on the implementation phase of the **HashMap** component in the **Collections Library**. The goal was to build a robust, generic, open-chained (separate chaining) Hash Map from scratch, prioritizing raw memory management hooks (`std::malloc`, placement `new`, explicit destructor calls) and extensive hashing capabilities for diverse key types (including custom/user-defined and primitive types).

---

# HashMap Skeleton & Rule of Three (Morning Session)

During the morning session, I focused on the foundation of the hash map and the implementation of standard hashing specializations.

- **Primitive Key Hash Functors**:
  - Implemented a general hashing structure `DefaultHash` casting standard integer/arithmetic keys.
  - Wrote specialized hash templates for floating-point types (`float`, `double`, `long double`), hashing the raw memory byte streams directly using `std::memcpy` and XOR folding (or FNV-1a hashing for `long double`) to avoid loss of precision or incorrect comparisons.
  - Provided specializations for pointers `T*` and `std::nullptr_t` to maximize key support.
- **Custom Memory Management Helpers**:
  - Implemented `allocateBuckets` and `destroyBuckets` for managing the bucket array manually using `std::malloc` and `std::free`.
  - Wrote `createNode` and `destroyNode` helpers, separating memory allocation from constructor calls using placement `new`, and calling the node destructors (`~HashNode`) explicitly prior to freeing them.
- **Rule of Three**:
  - Implemented the **Copy Constructor** and **Copy Assignment Operator** to handle deep-copying of collision chains safely.
  - Utilized exception-safe allocation blocks and cleanup try-catch handlers to ensure that if node construction fails midway, any partially copied resources are cleared immediately to prevent memory leaks.

---

# HashMap Public Operations & Rehashing (Evening Session)

In the evening session, I expanded the API and added dynamic scaling capabilities to the hash map.

- **Core API Operations**:
  - Implemented `insert`, `get`, `remove`, and `contains`. 
  - Modeled the map collision resolution using separate chaining; lookup and insertion traverse bucket chains and compare keys using the `DefaultKeyEqual` functor (relying on `operator==`).
- **Dynamic Scaling & Rehashing**:
  - Implemented a rehashing threshold of `0.75` (max load factor).
  - Wrote a private `rehash()` function that allocates a new doubled bucket array and moves existing nodes across to their new destinations directly without creating/allocating new nodes, keeping memory operations highly efficient.
- **Compile-Time SFINAE Trait for Printing**:
  - Designed `details::is_streamable` to detect whether a type can be outputted using `std::ostream`.
  - Enabled `print()` to safely dump buckets and collision chains to `std::cout`, replacing any unstreamable keys or values with `<unstreamable>` at compile-time instead of failing compilation.
- **Verification Tests**:
  - Integrated testing logic in [main.cpp](file:///Users/tanishdogra/Cpp_datastructure/main.cpp) to cover constructors, copy/assignment functions, standard primitive key types, pointer/nullptr keys, load factor rehashing, and clean-up.

---

# Key Learnings

- **Bit-Level Hashing**: Learned the importance of using `std::memcpy` rather than direct casts when hashing floating-point types to obtain stable hash hashes from their underlying binary representations.
- **Exception Safety in Templates**: Solidified the practice of wrapping sequence iterations inside `try` blocks during template constructors so that dynamic allocation failures clean up successfully allocated resources before propagating the exception.
- **SFINAE and Modern template programming**: Used SFINAE (`std::enable_if`) to provide fallback behavior for container methods that output elements, ensuring templates can compile for both streamable and non-streamable structures.
