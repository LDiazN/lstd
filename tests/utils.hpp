#ifndef UTILS_HPP
#define UTILS_HPP

/// This class will count how many instances of itself there are alive.
/// Useful for pointer implementations
struct Counter {
  int *counter = nullptr;
  Counter(int *_counter = nullptr) : counter(_counter) {
    if (counter != nullptr)
      (*counter)++;
  }
  ~Counter() {
    if (counter != nullptr)
      (*counter)--;
    counter = nullptr;
  }

  Counter(const Counter &other) : counter(other.counter) {
    if (counter != nullptr)
      (*counter)++;
  }

  Counter(Counter &&other) : counter(other.counter) { other.counter = nullptr; }

  Counter &operator=(const Counter &other) {
    if (&other == this)
      return *this;

    if (counter != nullptr)
      (*counter)--;

    counter = other.counter;
    if (counter != nullptr)
      (*counter)++;

    return *this;
  }

  Counter &operator=(Counter &&other) {
    if (&other == this)
      return *this;

    if (counter != nullptr)
      (*counter)--;

    counter = other.counter;
    other.counter = nullptr;

    return *this;
  }

  int Count() const { return counter == nullptr ? 0 : *counter; }
};

struct Point {
  int x, y;
};

#endif
