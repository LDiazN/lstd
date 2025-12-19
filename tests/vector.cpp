#include <catch2/catch_test_macros.hpp>
#include <lstd/collections/vector.hpp>
#include "utils.hpp"

TEST_CASE("vector construction", "[vector]") {
  auto v1 = lstd::Vector<Point>();
  REQUIRE(v1.Size() == 0);

  auto v2 = lstd::Vector<Point>(42);
  REQUIRE(v2.Capacity() == 42);
  REQUIRE(v2.Capacity() != v1.Capacity());
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
}

TEST_CASE("vector index operator", "[vector]")
{
  auto v = lstd::Vector<Point>();
  v.PushBack({1,2});
  REQUIRE(v[0].x == 1);
  REQUIRE(v[0].y == 2);
}
