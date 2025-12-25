#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <cstdlib>
#include <lstd/debug/assert.hpp>
#include <sstream>

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
  virtual void Pop(size_t index) = 0;

  virtual const T& operator[](size_t index) const = 0;
  virtual T& operator[](size_t index) = 0;
};

  size_t closest2Pow(size_t v);

template<typename T>
class Vector : public BaseVector<T> {

  public:
  Vector(size_t initialCapacity = 8) : capacity(closest2Pow(initialCapacity)), size(0)
  {
    Assert(initialCapacity > 0, "Initial capacity should be always > 0 or resize breaks");
    data = Allocate(capacity);
  }

  Vector(size_t copies, const T& defaultValue) : capacity(8), size(copies)
  {
    capacity = closest2Pow(copies);

    data = Allocate(capacity);
    for (size_t i = 0; i < size; i++)
      new (data + i) T(defaultValue);
  }

  Vector(const Vector& other) : capacity(other.capacity), size(other.size)
  {
    data = Allocate(capacity);

    // Placement new with copy constructor
    for (size_t i = 0; i < other.size; i++)
      new (data+i) T(other[i]);
  }

  Vector(Vector&& other) noexcept : data(other.data), capacity(other.capacity), size(other.size)
  {
    other.Clear();
  }

  ~Vector() override
  {
    Vector::Reset();
    free(data);
    data = nullptr;
  }

  Vector& operator=(const Vector& other)
  {
    if (&other == this)
      return *this;

    // Defer to the move assign
    *this = Vector(other);

    return *this;
  }

  Vector& operator=(Vector&& other) noexcept
  {
    if (&other == this)
      return *this;

    // Destroy current vector
    Vector::Reset();
    free(data);

    // Swap from copy
    capacity = other.capacity;
    size = other.size;
    data = other.data;

    other.Clear();

    return *this;
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
    size = 0;
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

  void Pop(size_t index) override
  {
    Assert(index < size, "Position to pop out of range");

    // Move all elements one position earlier
    for (size_t i = index; i < size - 1; i++)
      data[i] = std::move(data[i+1]);

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

  /// Nullifies the vector, setting everything to zero
  void Clear() noexcept
  {
    data = nullptr;
    capacity = size = 0;
  }

  /// Changes the capacity of this vector
  void Resize()
  {
      size_t newCapacity = GetNewCapacity();
      data = static_cast<T*>(realloc(data, sizeof(T) * newCapacity));
      capacity = newCapacity;
  }

  static T* Allocate(size_t count)
  {
    return static_cast<T*>(malloc(sizeof(T) * count));
  }

protected:
  T* data = nullptr;
  size_t capacity = 0;
  size_t size = 0;
};

  template <typename T>
  class OVector : public BaseVector<T>
  {

  };

} // namespace lstd

#endif
