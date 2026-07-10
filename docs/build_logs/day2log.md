# Day 02 Build Log

**Project:** Collections Library (C++)  
**Component:** Linked List  
**Phase:** Design Proposal  
**Date:** 07 July 2026

---

# Shift 01 (09:45 AM – 11:30 AM)

## Goal

Begin the design proposal for the Linked List by understanding the project requirements, identifying the required operations, and deciding the overall architecture before implementation.

## Work Completed

- Carefully reviewed the Linked List requirements provided in the project handbook.
- Identified all mandatory operations expected from the data structure.
- Compared Linked Lists with Dynamic Arrays to understand their strengths and limitations.
- Listed the primary responsibilities of the Linked List class.
- Started drafting the public API that will be exposed to users.

## Problem Encountered

The first major architectural decision was choosing between implementing a **Singly Linked List** or a **Doubly Linked List**.

## What I Tried

Compared both implementations based on:

- Memory consumption
- Complexity of implementation
- Ease of traversal
- Insertion and deletion operations
- Suitability for current project requirements

## Outcome

Selected a **Singly Linked List** because it satisfies all project requirements while maintaining lower memory overhead and simpler implementation.

## Learning

Good software design begins by selecting the simplest architecture capable of fulfilling all functional requirements.

---

# Shift 02 (11:45 AM – 01:15 PM)

## Goal

Design the internal memory representation of the Linked List before writing any implementation.

## Work Completed

- Designed the internal `Node` structure.
- Determined the member variables required inside every node.
- Planned the private data members of the Linked List class.
- Designed the relationship between the head pointer and dynamically allocated nodes.
- Drew preliminary memory layout diagrams showing multiple nodes connected through pointers.
- Studied how traversal occurs using pointer references.

## Problem Encountered

Determining how dynamically allocated nodes should be owned and managed throughout the lifetime of the Linked List.

## What I Tried

Created multiple memory diagrams illustrating:

- Empty list
- Single node
- Multiple nodes
- Node traversal
- Object destruction

## Outcome

Finalized the ownership model where the Linked List object owns every dynamically allocated node, making the destructor responsible for releasing all allocated memory.

## Learning

Unlike Dynamic Arrays, a Linked List consists of multiple independent heap allocations connected through pointers rather than one contiguous memory block.

---

# Shift 03 (02:00 PM – 04:00 PM)

## Goal

Design the complete public interface and analyze the expected time complexity of every operation.

## Work Completed

- Drafted the complete public API.
- Listed all planned member functions.
- Defined parameters and return types.
- Prepared complexity analysis for every operation.
- Documented best-case, average-case, and worst-case complexities.
- Added explanations supporting every complexity estimate.
- Compared Linked List operations with equivalent Dynamic Array operations.

## Problem Encountered

Several operations involve both traversal and pointer manipulation, making complexity analysis more involved than initially expected.

## What I Tried

Analyzed every operation individually by separating:

- Traversal cost
- Pointer update cost
- Memory allocation cost

## Outcome

Completed a detailed complexity table explaining not only the Big-O notation but also the reasoning behind each complexity.

## Learning

The overall complexity of many Linked List operations is determined by traversal rather than pointer manipulation itself.

---

# Shift 04 (04:00 PM – 06:25 PM)

## Goal

Document the major design decisions and prepare the first complete draft of the Linked List Design Proposal.

## Work Completed

- Documented the justification for choosing a Singly Linked List.
- Planned the overall memory management strategy.
- Defined destructor responsibilities.
- Considered future implementation of the Rule of Three.
- Cross-checked API design with memory diagrams.
- Verified consistency between memory representation, complexity analysis, and public interface.
- Updated project documentation with all finalized design decisions.

## Problem Encountered

Maintaining consistency between every section of the design proposal while ensuring each design decision supported the others.

## What I Tried

Performed a complete design review by validating:

- Public API
- Memory diagrams
- Complexity table
- Ownership model
- Design decisions

## Outcome

Completed the first draft of the Linked List Design Proposal, establishing a clear blueprint for the implementation phase.

## Learning

A comprehensive design proposal significantly reduces implementation uncertainty by resolving architectural and memory management decisions before coding begins.

---

# End of Day Summary

## Objectives Achieved

- ✔ Reviewed Linked List project requirements
- ✔ Selected **Singly Linked List** architecture
- ✔ Designed internal Node structure
- ✔ Planned heap memory organization
- ✔ Designed the complete public API
- ✔ Completed complexity analysis with detailed explanations
- ✔ Defined memory ownership strategy
- ✔ Planned destructor responsibilities
- ✔ Considered Rule of Three requirements
- ✔ Completed the first draft of the Linked List Design Proposal

---

## Key Technical Takeaways

- A Linked List stores data as independently allocated nodes connected through pointers rather than contiguous memory.
- Selecting the appropriate data structure requires balancing simplicity, memory usage, and project requirements.
- Proper ownership of dynamically allocated nodes is essential for preventing memory leaks.
- Memory diagrams play a crucial role in understanding pointer relationships and object lifetime.
- Completing API design, memory representation, and complexity analysis before implementation provides a strong engineering foundation for future development.