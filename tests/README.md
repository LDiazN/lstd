# Tests

This directory has all the tests for this project

Each data structure should have its dedicated test suite

The test suite is also the contract of the data structure, it should showcase all its intended use
cases

## Adding new tests:

1. Create a new file in this directory
2. Add the file to the `CMakeLists.txt` file in the root of this repository in the "Testing" section

## Test template:

```cpp
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Test title", "[tag]") {

}
```