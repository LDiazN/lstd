#ifndef VECTOR_HPP
#define VECTOR_HPP

namespace lstd {

template<typename T>
class BaseVector {
public:
  virtual size_t Size() const = 0;
  virtual size_t Capacity() const = 0;
  virtual T* RawPtr() const = 0;
};
} // namespace lstd

#endif