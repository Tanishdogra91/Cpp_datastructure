# Day 06 Build Log

**Project:** Collections Library (C++)  
**Component:** HashMap (Pointer Safety & Hashing)  
**Phase:** Refactoring & Redis Lite Planning  
**Date:** 13 July 2026

---

# Shift 01 (10:00 AM – 01:30 PM)

## Goal

Adapt the `HashMap` implementation to support user-defined pointer keys safely and fix hashing/comparison behavior where identical data stored at different memory addresses resulted in duplicate keys or retrieval failures.

## Work Completed

- Identified a critical bug in pointer-based keys (e.g. `int*` or custom data pointers) where hashing and comparison were based on the pointer's *address* instead of the *underlying data*.
- Attempted to dereference pointers directly in `DefaultKeyEqual` and `DefaultHash`, which triggered compilation errors because the compiler tried to instantiate dereferencing operators on non-pointer types like `int`.
- Modified [CMakeLists.txt](file:///Users/tanishdogra/Cpp_datastructure/CMakeLists.txt) to enable AddressSanitizer (ASan) options (`-fsanitize=address -fno-omit-frame-pointer`) to monitor memory safety and detect access violations or leaks during pointer validation tests.
- Formulated the design for address conflict policies, specifying how the map should react when encountering two different pointer instances pointing to equivalent data values.

## Outcome

Encountered compilation errors and duplicate entries in collision chains. Concluded that a compile-time template-dispatch pattern using custom type traits was required to inspect pointer keys by value rather than address.

---

# Shift 02 (02:30 PM – 06:00 PM)

## Goal

Implement pointer traits, deep comparison helpers, configurable conflict behaviors, update `HashMap` methods, rewrite verification tests, and research/design Redis Lite concepts.

## Work Completed

- Created an STL-free trait struct `IsPointer<T>` to determine pointer types at compile-time.
- Implemented class templates `EqualHelper` and `HashHelper` inside [hashmap.h](file:///Users/tanishdogra/Cpp_datastructure/include/hashmap.h):
  - Specializations resolve non-pointers by direct value comparison and standard hashing.
  - Specializations resolve pointer keys (`T*`) by safely dereferencing values (`*key`), while checking for `nullptr` (which hashes to `0` and fails comparisons with non-null pointer instances).
- Defined the `AddressConflictBehavior` enum containing `OVERWRITE` (overwrite value and key pointer) and `ERROR_RETURN` (return `false` on conflicting address insert).
- Updated constructor of `HashMap` to take the conflict behavior, and modified `insert()` in [hashmap.tpp](file:///Users/tanishdogra/Cpp_datastructure/src/hashmap.tpp) to return `bool`:
  - If a key matches under the value-equality functor:
    - If pointers have identical addresses: Standard overwrite (returns `true`).
    - If pointers have different addresses but match value: Inspect behavior. If `ERROR_RETURN`, insertion fails and returns `false`. If `OVERWRITE`, values are overwritten and the stored key pointer updates to the new address.
- Updated unit test drivers in [main.cpp](file:///Users/tanishdogra/Cpp_datastructure/main.cpp):
  - Added assert statements checking `insert()` return values.
  - Added test case verifying different addresses with same values under `OVERWRITE` mode.
  - Added test case verifying `ERROR_RETURN` mode correctly returns `false` on conflict and preserves original associations.
- Successfully built and ran the test binary under AddressSanitizer with zero errors or leaks.
- Researched **Redis Lite** design:
  - Planned to use the custom `HashMap` with string keys as the database core.
  - Understood requirement for variant values (`RedisObject`) supporting multiple data types (Strings, Lists, Hashes).
  - Drafted concepts for a REPL CLI parsing command arguments and handling TTL-based item expiration checks.

## Outcome

The `HashMap` handles pointer keys securely without duplicates, compilation failures, or memory corruption. Tests pass with ASan, and the architectural concept for the Redis Lite key-value store is established.
