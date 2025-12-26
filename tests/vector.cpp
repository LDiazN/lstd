#include "utils.hpp"
#include <catch2/catch_test_macros.hpp>
#include <lstd/collections/vector.hpp>

#include "lstd/memory/rc_ptr.hpp"

TEST_CASE("vector construction", "[vector]")
{
  auto v1 = lstd::Vector<Point>();
  REQUIRE(v1.Size() == 0);

  auto v2 = lstd::Vector<Point>(42);
  // Capacity doesn't need to be exactly 42,
  // but at the least 42 elements should be ensured
  REQUIRE(v2.Capacity() >= 42);
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

TEST_CASE("vector assign", "[vector]") {
  lstd::Vector<int> v1;
  v1.PushBack(1);
  v1.PushBack(2);
  v1.PushBack(3);

  lstd::Vector<int> v2;
  v2.PushBack(4);
  v2.PushBack(5);
  v2 = v1;

  REQUIRE(v2.Size() == v1.Size());
  REQUIRE(v2.RawPtr() !=
          v1.RawPtr()); // copy constructor should allocate new data

  REQUIRE(v2[0] == v1[0]);
  REQUIRE(v2[1] == v1[1]);
  REQUIRE(v2[2] == v1[2]);

  // Changing v2 should NOT change v1
  v2[0] = 69;
  REQUIRE(v2[0] != v1[0]);

  // rvalue assign
  v2 = lstd::Vector<int>(4, 42);
  REQUIRE(v2.Size() == 4);
  REQUIRE(v2[0] == 42);
  REQUIRE(v2[1] == 42);
  REQUIRE(v2[2] == 42);
  REQUIRE(v2[3] == 42);

  // Check that assign is releasing resources
  int counter = 0;
  {
    lstd::Vector<Counter> v3(3, Counter(&counter));
    REQUIRE(counter == 3);

    // Should release all counters
    v3 = lstd::Vector<Counter>();
    REQUIRE(counter == 0);
  }

  // Check that you properly handle self assign
  counter = 0;
  lstd::Vector<Counter> v4(1, Counter(&counter));
  // ReSharper disable once CppIdenticalOperandsInBinaryExpression
  v4 = v4; // NOLINT(clang-diagnostic-self-assign-overloaded)

  REQUIRE(counter == 1);
  REQUIRE(v4.Size() == 1);
  v4[0]; // should not fail

  v4 = std::move(v4); // NOLINT(clang-diagnostic-self-move)
  REQUIRE(counter == 1);
  REQUIRE(v4.Size() == 1);
  v4[0];
}

TEST_CASE("vector push back", "[vector]") {
  auto v = lstd::Vector<Point>();
  REQUIRE(v.Size() == 0);

  v.PushBack({1, 2});
  REQUIRE(v.Size() == 1);
  REQUIRE(v[0].x == 1);
  REQUIRE(v[0].y == 2);

  // Push back should resize a vector
  auto v1 = lstd::Vector<Point>(1);
  REQUIRE(v1.Capacity() == 1);

  v1.PushBack({4, 2});
  REQUIRE(v1.Size() == 1);
  REQUIRE(v1.Capacity() == 1); // don't resize if you have enough space

  v1.PushBack({6, 9});
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

  // Test that resize is not creating new resources and forgetting to release
  // the previous ones
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

TEST_CASE("vector pop back", "[vector]") {
  int counter = 0;
  lstd::Vector<Counter> v1(3, Counter(&counter));
  REQUIRE(counter == 3);

  // Pop back should release resources for the last element
  v1.PopBack();
  REQUIRE(counter == 2);
  REQUIRE(v1.Size() == 2);

  // You can pop until it's empty
  v1.PopBack();
  v1.PopBack();
  REQUIRE(counter == 0);
  REQUIRE(v1.Size() == 0);

  // Poping again will throw an error on debug
  REQUIRE_THROWS(v1.PopBack());
}

lstd::Vector<size_t> toN(size_t n);
TEST_CASE("vector pop", "[vector]") {
  lstd::Vector<size_t> v1 = toN(8);
  v1.Pop(7); // Pop last one
  REQUIRE(v1.Size() == 7);

  v1.Pop(2);
  REQUIRE(v1.Size() == 6);
  REQUIRE(v1[2] == 3);

  // We can pop until it's empty
  v1.Pop(0);
  v1.Pop(0);
  v1.Pop(0);
  v1.Pop(0);
  v1.Pop(0);
  v1.Pop(0);

  REQUIRE(v1.Size() == 0);

  // Poping again raises an error on debug
  REQUIRE_THROWS(v1.Pop(0));

  // Check that popping is releasing resources properly
  int counter = 0;
  lstd::Vector<Counter> v2(4, Counter(&counter));
  REQUIRE(counter == 4);
  v2.Pop(1);
  REQUIRE(counter == 3);
  v2.Pop(2);
  REQUIRE(counter == 2);
}

TEST_CASE("vector index operator", "[vector]") {
  auto v = lstd::Vector<Point>();
  v.PushBack({1, 2});
  REQUIRE(v[0].x == 1);
  REQUIRE(v[0].y == 2);

  REQUIRE_THROWS(v[1]);
}

// -- < Optimistic Vector > -----------------
TEST_CASE("optimistic vector construction", "[vector]") {
  lstd::OVector<int, 16> v; // Default construction
  REQUIRE(v.Size() == 0);
  REQUIRE(v.Capacity() == 16); // same as template param

  int counter = 0;
  {
    lstd::OVector<Counter, 8> v1(4, Counter(&counter));
    REQUIRE(counter == 4);

    // copies > optimistic capacity
    lstd::OVector<Counter, 8> v2(12, Counter(&counter));
    REQUIRE(counter == 16); // 4 + 12

    // Create a copy from other vector
    lstd::OVector<Counter, 8> v3(
        v1); // NOLINT(performance-unnecessary-copy-initialization)
    REQUIRE(counter == 20);

    // Move constructor
    lstd::OVector<Counter, 8> v4(
        lstd::OVector<Counter, 8>(4, Counter(&counter)));
  }

  REQUIRE(counter == 0);
}

TEST_CASE("optimistic vector assign", "[vector]") {
  int counter = 0;
  {
    lstd::OVector<Counter, 8> v1(4, Counter(&counter));
    REQUIRE(counter == 4);

    lstd::OVector<Counter, 8> v2(2, Counter(&counter));
    REQUIRE(counter == 6);

    // Copy assign
    v2 = v1;
    REQUIRE(counter == 8);

    // Move assign
    v2 = lstd::OVector<Counter, 8>(8, Counter(&counter));
    REQUIRE(counter == 12);

    // Assign from a vector with external memory
    lstd::OVector<Counter, 8> v3(12, Counter(&counter));

    // Copy assign again
    v2 = v3;
    REQUIRE(counter == 28);
  }
  REQUIRE(counter == 0);
}

TEST_CASE("optimistic vector push", "[vector]") {
  lstd::OVector<int, 4> v1;
  v1.PushBack(42);
  REQUIRE(v1.Size() == 1);
  REQUIRE(v1[0] == 42);

  // More pushes should trigger a resize to external mem
  for (int i = 1; i < 5; i++) {
    v1.PushBack(i);
    REQUIRE(v1.Size() == i + 1);
    REQUIRE(v1[i] == i);
  }
  REQUIRE(v1.Capacity() > 4);

  // Triggering a resize should not leave dangling pointers
  int counter = 0;
  {
    lstd::OVector<Counter, 2> v2;
    v2.PushBack(Counter(&counter));
    v2.PushBack(Counter(&counter));
    v2.PushBack(Counter(&counter));
    v2.PushBack(Counter(&counter));
    REQUIRE(counter == 4);
  }
  REQUIRE(counter == 0);
}

TEST_CASE("optimistic vector pop", "[vector]") {
  int counter = 0;
  {
    lstd::OVector<Counter, 4> v;
    REQUIRE_THROWS(v.PopBack());
    REQUIRE_THROWS(v.Pop(0));

    v.PushBack(Counter(&counter));
    REQUIRE(v.Size() == 1);
    v.PopBack();
    REQUIRE(v.Size() == 0);
    v.PushBack(Counter(&counter));
    v.PushBack(Counter(&counter));
    v.Pop(0);
    REQUIRE(v.Size() == 1);
  }
  REQUIRE(counter == 0);

  lstd::OVector<int, 16> v1;
  for (int i = 0; i < 8; i++)
    v1.PushBack(i);

  REQUIRE(v1[1] == 1);
  v1.Pop(1);
  REQUIRE(v1[1] == 2);
}

TEST_CASE("optimistic vector indexing", "[vector]") {
  lstd::OVector<int, 16> v1;
  // Index out of range
  REQUIRE_THROWS(v1[0]);
  v1.PushBack(1);
  v1.PushBack(2);
  v1.PushBack(3);

  REQUIRE(v1[0] == 1);
  REQUIRE(v1[1] == 2);
  REQUIRE(v1[2] == 3);

  // You can replace an element inside the array
  int counter = 0;
  {
    lstd::OVector<Counter, 4> v2(2, Counter(&counter));
    REQUIRE(counter == 2);
    v2[1] = Counter(nullptr);
    REQUIRE(counter == 1);
  }
  REQUIRE(counter == 0);

  // You can get a const reference
  {
    const lstd::OVector<Counter, 4> v2(2, Counter(&counter));
    REQUIRE(counter == 2);
    const Counter &c = v2[0];
    REQUIRE(c.counter == &counter);
  }
  REQUIRE(counter == 0);
}

TEST_CASE("optimistic vector reset", "[vector]") {
  int counter1 = 0;
  int counter2 = 0;
  {
    lstd::OVector<Counter, 4> v1(3, Counter(&counter1));
    REQUIRE(counter1 == 3);
    v1.Reset();
    REQUIRE(counter1 == 0);
    v1.PushBack(Counter(&counter2));
    REQUIRE(counter2 == 1);
  }
  REQUIRE(counter1 == 0);
  REQUIRE(counter2 == 0);
}

TEST_CASE("optimistic vector with pointers", "[vector]")
{
  int counter = 0;
  {
    lstd::OVector<lstd::Ptr<Counter>, 4> v1(3, lstd::Ptr<Counter>(new Counter(&counter)));

    // all three entries point to the same counter object
    REQUIRE(counter == 1);

    // You can deref pointers inside the vector
    REQUIRE(v1[0]->Count() == 1);
    REQUIRE(v1[1]->Count() == 1);
    REQUIRE(v1[2]->Count() == 1);
  }
  REQUIRE(counter == 0);
}

// -- < Utils > -----------------------------
lstd::Vector<size_t> toN(size_t n) {
  lstd::Vector<size_t> v(n, 0);
  for (size_t i = 0; i < n; i++)
    v[i] = i;

  return v;
}
