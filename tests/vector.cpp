#include <catch2/catch_test_macros.hpp>
#include <lstd/collections/vector.hpp>
#include "utils.hpp"

TEST_CASE("vector construction", "[vector]") {
  auto v1 = lstd::Vector<Point>();
  REQUIRE(v1.Size() == 0);

  auto v2 = lstd::Vector<Point>(42);
  REQUIRE(v2.Capacity() == 42);
  REQUIRE(v2.Capacity() != v1.Capacity());

  // Test copy constructor
  int counter = 0;
  lstd::Vector<Counter> v3;
  v3.PushBack(Counter(&counter));
  v3.PushBack(Counter(&counter));
  v3.PushBack(Counter(&counter));
  REQUIRE(counter == 3);

  // Creates a deep copy of v3
  lstd::Vector<Counter> v3Copy(v3);
  REQUIRE(v3.RawPtr() != v3Copy.RawPtr()); // different memory segments
  REQUIRE(counter == 6);

  // Releasing a vector should properly release internal resources
  v3.Reset();
  REQUIRE(counter == 3);
  REQUIRE(v3.Size() == 0);
  REQUIRE(v3Copy.Size() == 3);
}

TEST_CASE("vector push back", "[vector]")
{
  auto v = lstd::Vector<Point>();
  REQUIRE(v.Size() == 0);

  v.PushBack({1,2});
  REQUIRE(v.Size() == 1);
  REQUIRE(v[0].x == 1);
  REQUIRE(v[0].y == 2);

  // Push back should resize a vector
  auto v1 = lstd::Vector<Point>(1);
  REQUIRE(v1.Capacity() == 1);

  v1.PushBack({4,2});
  REQUIRE(v1.Size() == 1);
  REQUIRE(v1.Capacity() == 1); // don't resize if you have enough space

  v1.PushBack({6,9});
  REQUIRE(v1.Capacity() > 1); // Resize should be triggered by now

  // Test correct resource release
  int counter = 0;
  {
    auto v2 = lstd::Vector<Counter>();
    v2.PushBack(Counter{&counter});
    v2.PushBack(Counter{&counter});
    v2.PushBack(Counter{&counter});
    REQUIRE(counter == 3);
  }
  REQUIRE(counter == 0);

  // Test that resize is not creating new resources and forgetting to release the previous ones
  counter = 0;
  {
    auto v3 = lstd::Vector<Counter>(1);
    v3.PushBack(Counter(&counter)); // Not resize

    REQUIRE(counter == 1);

    v3.PushBack(Counter(&counter)); // Resize
    v3.PushBack(Counter(&counter));
    REQUIRE(counter == 3);
  }
  REQUIRE(counter == 0);

  // Test move construction
  counter = 0;
  {
    lstd::Vector<Counter> v4(lstd::Vector<Counter>(4, Counter(&counter)));
    REQUIRE(counter == 4);
  }
  REQUIRE(counter == 0);
}

TEST_CASE("vector index operator", "[vector]")
{
  auto v = lstd::Vector<Point>();
  v.PushBack({1,2});
  REQUIRE(v[0].x == 1);
  REQUIRE(v[0].y == 2);
}
