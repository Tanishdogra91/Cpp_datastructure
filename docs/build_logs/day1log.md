# Build Log

---

## Session 1

**Date:** 06 July 2026

**Duration:** 2:00 PM – 4:00 PM (2 Hours)

### Goal

Complete the initial software design of the Dynamic Array by defining the project objective, designing the Public API, and planning the Internal Representation.

### Problem Encountered

Initially, it was difficult to determine which functions should be part of the Public API and which should remain internal to the implementation. There was also some confusion between the concepts of the Public API and the Internal Representation.

### What I Tried

- Studied the expected functionality of a Dynamic Array.
- Categorized operations into object lifecycle, data modification, data access, and state inspection.
- Compared the responsibilities of the Public API and the Internal Representation.
- Planned the private data members (`data`, `size`, and `capacity`) required for the implementation.

### Outcome

Successfully completed the first draft of the design document, including the project objective, Public API, API design justification, and Internal Representation. The responsibilities of each public function and private data member were clearly documented.

---

## Session 2

**Date:** 06 July 2026

**Duration:** 4:00 PM – 6:25 PM (2 Hours 25 Minutes)

### Goal

Complete the remaining design documentation by finalizing the memory management strategy, Rule of Three, complexity analysis, design decisions, and supporting documentation.

### Problem Encountered

Faced difficulty in selecting the most appropriate resizing strategy and explaining the amortized time complexity of `append()`. Also spent time organizing the design document into a structured and readable format.

### What I Tried

- Compared different resizing strategies, including fixed increment, capacity doubling, and percentage-based growth.
- Studied how dynamic resizing affects time complexity.
- Documented the Rule of Three to ensure proper ownership of dynamically allocated memory.
- Justified each design decision by documenting the selected approach, alternatives considered, and reasons for rejection.
- Reviewed and refined the entire design document for consistency and readability.

### Outcome

Successfully completed the Dynamic Array design document. Finalized the memory management strategy, Rule of Three, complexity analysis, and design decisions. The project documentation is now complete and ready for the implementation phase.