# vector.h

A resizable contiguous container, equivalent to `std::vector`

## Operations

Let `n`  the current amount of elements in the vector, `T` the stored type: 

- **Indexing**: Access any element in the array by index. Time complexity: `O(1)`.  
- **Push Back**: Add an element at the end of the vector. Time complexity: `O(1)` in most cases, `O(n)` when resize is needed to increase capacity (worst case).
- **Pop Back**: Remove an element from the end of the vector. Time complexity: `O(1)`.
- **Pop**: Remove an element at any position in the array. Following elements will be moved one position earlier, using the move assign operator. Time complexity: `O(n)`.
- **Reset**: Resets the content of the vector, preserving it's original capacity. Elements in the vector will be destroyed. Time complexity: `O(n * Complexity(~T))`

Note that two types of vectors (with the same API) are provided:

- `Vector` Which is equivalent to `std::vector` and provides the standard behaviour of a vector.
- `OVector` (optimistic vector) Behaves the same as a normal vector but it starts with a compile-time defined starting **capacity** and storing elements within the vector itself, rather than in a different memory segment, assuming that no resize will be necessary most of the times.
  - If a resize is necessary, the content will be moved to a different memory segment in the heap with higher capacity and it will become a normal `Vector` going forward.
  - This vector provides better data locality and it's useful when the amount of elements to store will (likely) be small and well known beforehand  
