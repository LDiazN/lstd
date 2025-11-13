# Ref Counted Pointer (`rc_ptr`)

A non-intrusive ref-counted smart pointer

This is also the default smart pointer, so you can use refer to it as `Ptr`

Note that since this is non-intrusive, dereferencing this pointer takes two indirections. One for the entry, another one for the actual data. 

You can find the full test suite [here](../../tests/rc_ptr.cpp)
