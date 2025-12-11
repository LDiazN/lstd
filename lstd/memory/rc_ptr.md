# Ref Counted Pointer (`rc_ptr`)

A non-intrusive ref-counted smart pointer

This is also the default smart pointer, so you can use refer to it as `Ptr`

Note that since this is non-intrusive, dereferencing this pointer takes two indirections. One for the entry, another one for the actual data.

You can find the full test suite [here](../../tests/rc_ptr.cpp)

Note that this pointer does not support storing dynamically allocated arrays of objects:

```cpp
lstd::Ptr<P*> p(new P[3]); // Invalid, will trigger undefined behaviour on destruction
```

This is because it uses `delete` for destruction, so when the pointer is released it will run:

```cpp
delete ptr // instead of delete[] ptr
```

If you need to store an array, use a RAII container like a vector or an `std::array`
