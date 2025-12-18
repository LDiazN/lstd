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
  virtual void PushBack() = 0;
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

  ~Vector() override
  {
    for(size_t i = 0; i < size; i++)
      data[i].~T();

    free(data);
  }

  private:


  private:
  T* data;
  size_t capacity;
  size_t size;
};

} // namespace lstd

#endif
