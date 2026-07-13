# Journal Entry – Day 06

**Project:** Collections Library (C++)  
**Component:** HashMap (Pointer Safety & Hashing)  
**Phase:** Refactoring & Redis Lite Planning  
**Date:** 13 July 2026

---

# Introduction

Today, I focused on addressing crucial pointer safety and deep value comparison issues when utilizing user-defined pointer types (such as `int*` or custom data pointers) as keys in the `HashMap`. The primary goal was to prevent address-based duplication of identical underlying data, handle address conflicts gracefully through parameterized behaviors, and compile-proof the hash/equality code using STL-free template metaprogramming. In the evening, we completed verification testing and designed the conceptual blueprint for a **Redis Lite** database engine powered by this custom `HashMap`.

---

# Hashing User-Defined/Pointer Keys & Debugging (Morning Session)

During the morning session, we faced several functional issues and compilation errors while testing `HashMap` with pointer-based keys:

- **The Pointer Equality vs. Value Equality Bug**:
  - Initially, inserting pointer keys (`T*`) into the `HashMap` hashed the pointer's *memory address* (`std::hash<T*>{}(key)`) and compared keys via raw address comparison.
  - Consequently, if two different pointers pointed to the same data (e.g., `int a = 10; int a2 = 10;`), they were treated as distinct keys. This resulted in duplicate keys residing on the same collision chain and broke data consistency.
  - Additionally, querying with a temporary pointer pointing to the same data failed to retrieve the associated value.
- **The Compilation Failure with Direct Dereferencing**:
  - Attempting to solve this by dereferencing keys directly within the standard templates (e.g., doing `*key1 == *key2` inside `DefaultKeyEqual`) broke compilation for primitive/non-pointer key types (like `int` or `double`), because the dereference operator `*` is invalid on non-pointer types.
  - This required a clean, compile-time type-dispatch mechanism to separate pointer dereferencing from direct comparisons.
- **Null Pointer Dereference Risks**:
  - Dereferencing pointer keys blindly introduced potential segmentation faults if a pointer was `nullptr`.
- **Debugging setup with AddressSanitizer (ASan)**:
  - To trace pointer lifetimes, prevent memory leaks, and detect invalid reads/writes, we integrated AddressSanitizer compilation flags (`-fsanitize=address -fno-omit-frame-pointer`) directly into [CMakeLists.txt](file:///Users/tanishdogra/Cpp_datastructure/CMakeLists.txt). This ensured any memory mismanagement was flagged immediately during runtime checks.

---

# Resolution & Redis Lite Concept Design (Evening Session)

In the evening session, we solved these structural and compilation issues, implemented conflict resolution policies, and brainstormed the integration with Redis Lite.

- **STL-Free Type Traits & Compile-Time Dispatch**:
  - Implemented a custom trait struct `IsPointer<T>` to identify pointer types at compile-time without relying on `<type_traits>`'s `std::is_pointer`.
  - Created `EqualHelper` and `HashHelper` template structs. By partial specialization on `IsPointer<T>::value`, we decoupled the implementation:
    - **Non-Pointer types**: Directly hash and compare by value.
    - **Pointer types**: Safely hash and compare the *pointed-to values* after checking for `nullptr` (treating `nullptr` as a unique fallback returning `0`).
- **Flexible Address Conflict Behaviors**:
  - Defined the `AddressConflictBehavior` enum containing:
    - `OVERWRITE`: Updates the value and redirects the key pointer to the newly inserted pointer.
    - `ERROR_RETURN`: Fails the insertion and returns `false` if the underlying data matches but the address is different.
  - Updated the signature of `insert()` to return `bool` indicating successful insertion or conflict error.
- **Redis Lite Conceptualization**:
  - Brainstormed how the `HashMap` will act as the core storage engine for our upcoming **Redis Lite** project.
  - **Key structures**: Since Redis key-value pairs are typically text-based, the keys will be string-based (using a custom heap-allocated string type or standard string).
  - **Values**: Since Redis supports multiple datatypes (Strings, Lists, Hashes, Sets), the value in our `HashMap` will wrap a variant or custom base object using polymorphism (e.g., `RedisObject`) to represent the specific type.
  - **Memory Hooks & TTL**: The custom memory allocator will keep track of allocations, while the `HashMap` will support checking expiration timestamps (TTL) to evict expired items, keeping the memory footprint minimal.

---

# Key Learnings

- **Address-Agnostic vs. Address-Aware Hashing**: Learned that when using pointer types as keys, we must clearly define if we intend to hash the address itself (pointer identity) or the dereferenced content (value identity). Value identity requires robust dereferencing wrappers and `nullptr` checks.
- **SFINAE / Template Dispatch**: Metaprogramming with trait specializations is the correct C++ approach to write generic container logic that behaves differently for pointers vs. references, preventing illegal expressions from compilation failures.
- **AddressSanitizer (ASan)**: Enabling ASan in CMake is an invaluable practice for debugging templates with placement `new` and manual destructors, exposing errors immediately on execution.
