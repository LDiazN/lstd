#ifndef VECTOR_HPP
#define VECTOR_HPP

namespace lstd {

template<typename T>
class BaseVector {
public:
  virtual size_t Size() const = 0;
  virtual size_t Capacity() const = 0;
  virtual T* RawPtr() = 0;
  virtual const T* RawPtr() const = 0;
  virtual void Reset() = 0;
  virtual void PushBack(const T& item) = 0;
  virtual void PopBack() = 0;
  virtual void Pop(size_t index) = 0;

  virtual ~BaseVector() = 0;

  virtual const T& operator[](size_t index) const = 0;
  virtual T& operator[](size_t index) = 0;
};

template<typename T>
class Vector : public BaseVector<T> {

  public:
  Vector(size_t initialCapacity = 8) : capacity(initialCapacity), size(0)
  {
    data = malloc(sizeof(T) * capacity);
  }

  Vector(const Vector& other) : capacity(other.capacity), size(other.size)
  {
    data = malloc(sizeof(T) * capacity);

    // Placement new with copy constructor
    for (int i = 0; i < other.size; i++)
      new (data+i) T(other[i]);
  }

  ~Vector() override
  {
    for(size_t i = 0; i < size; i++)
      data[i].~T();

    free(data);
  }

protected:
  T* data = nullptr;
  size_t capacity = 0;
  size_t size = 0;
};

} // namespace lstd

#endif
