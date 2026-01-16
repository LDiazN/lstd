#include "vector.hpp"
using namespace lstd;

size_t lstd::closest2Pow(size_t v) {
  // TODO there most be a bit trick to do this faster
  size_t result = 1;
  while (result < v)
    result *= 2;

  return result;
}
