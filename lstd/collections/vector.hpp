#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <cstdlib>
#include <lstd/debug/assert.hpp>

namespace lstd {

template<typename T>
class BaseVector {
public:
  virtual ~BaseVector() = default;

  virtual size_t Size() const = 0;
  virtual size_t Capacity() const = 0;
  virtual T* RawPtr() = 0;
  virtual const T* RawPtr() const = 0;
  virtual void Reset() = 0;
  virtual void PushBack(T item) = 0;
  virtual void PopBack() = 0;
  // virtual void Pop(size_t index) = 0;


  virtual const T& operator[](size_t index) const = 0;
  virtual T& operator[](size_t index) = 0;
};

template<typename T>
class Vector : public BaseVector<T> {

  public:
  Vector(size_t initialCapacity = 8) : capacity(initialCapacity), size(0)
  {
    Assert(initialCapacity > 0, "Initial capacity should be always > 0 or resize breaks");
    data = static_cast<T*>(malloc(sizeof(T) * capacity));
  }

  Vector(const Vector& other) : capacity(other.capacity), size(other.size)
  {
    data = static_cast<T*>(malloc(sizeof(T) * capacity));

    // Placement new with copy constructor
    for (int i = 0; i < other.size; i++)
      new (data+i) T(other[i]);
  }

  ~Vector() override
  {
    Vector::Reset();
    free(data);
    data = nullptr;
  }

  size_t Size() const override
  {
    return size;
  }

  size_t Capacity() const override
  {
    return capacity;
  }

  T* RawPtr() override
  {
    return data;
  }

  const T* RawPtr() const override
  {
    return data;
  }

  void Reset() override
  {
    for(size_t i = 0; i < size; i++)
      data[i].~T();
  }

  void PushBack(T item) override
  {
    if (size == capacity)
      Resize();

    new (data + size) T(std::move(item));
    size++;
  }

  void PopBack() override
  {
    Assert(size > 0, "Vector is already empty");

    data[size - 1].~T();
    size--;
  }

  const T& operator[](size_t index) const override
  {
    Assert(index < size, "Index out of range");
    return data[index];
  }

  T& operator[](size_t index) override
  {
    Assert(index < size, "Index out of range");
    return data[index];
  }

private:
  size_t GetNewCapacity() const
  {
    // TODO find better regrow strategy
    return 2 * capacity;
  }

  /// Changes the capacity of this vector
  void Resize()
  {
      size_t newCapacity = GetNewCapacity();
      data = static_cast<T*>(realloc(data, sizeof(T) * newCapacity));
      capacity = newCapacity;
  }

protected:
  T* data = nullptr;
  size_t capacity = 0;
  size_t size = 0;
};

} // namespace lstd

#endif
