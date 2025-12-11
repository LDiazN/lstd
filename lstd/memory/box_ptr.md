# BoxPtr<T>

A `unique_ptr`-like pointer, for unique ownership of a pointer

Note that this pointer does not support storing dynamically allocated arrays of objects:

```cpp
lstd::BoxPtr<P*> p(new P[3]); // Invalid, will trigger undefined behaviour on destruction
```

This is because it uses `delete` for destruction, so when the pointer is released it will run:

```cpp
delete ptr // instead of delete[] ptr
```

If you need to store an array, use a RAII container like a vector or an `std::array`

