#include <catch2/catch_test_macros.hpp>
#include <lstd/memory/box_ptr.hpp>
#include <lstd/debug/assert.hpp>
#include "utils.hpp"

using P = Point;
lstd::BoxPtr<P> bp(int x, int y);
lstd::BoxPtr<Counter> bc(int *count);

TEST_CASE("BoxPtr Construction", "[box_ptr]") {
    lstd::BoxPtr<P> b1(new P{1,2});
    lstd::BoxPtr<P> b2;
    lstd::BoxPtr<P> b3(bp(3,4));

    REQUIRE(b1.RawPtr() != nullptr);
    REQUIRE(b2.RawPtr() == nullptr);
    REQUIRE(b3.RawPtr() != nullptr);
}

TEST_CASE("BoxPtr Eq", "[box_ptr]") {
    lstd::BoxPtr<P> b1;
    lstd::BoxPtr<P> b2 = nullptr;
    lstd::BoxPtr<P> b3(new P{1,2});
    lstd::BoxPtr<P> b4(new P{1,2});

    // Can compare to nullptr
    REQUIRE(b1 == nullptr);
    REQUIRE(b1 == b2);
    REQUIRE(b3 != nullptr);
    REQUIRE(b3 != b1);

    // The values are equal but the pointers are not
    REQUIRE(b4 != b3);

    // You can clean the reference
    b4 = nullptr;
    REQUIRE(b4 == nullptr);
}

TEST_CASE("BoxPtr Assign", "[box_ptr]") {
    int count = 0;

    lstd::BoxPtr<Counter> b1(new Counter(&count));
    REQUIRE(count == 1);

    lstd::BoxPtr<Counter> b2(new Counter(&count));
    REQUIRE(count == 2);

    // Prev one should be destroyed, new one should take it's place
    b1 = bc(&count);
    REQUIRE(count == 2);

    // Assigning null should deallocate the counter
    b2 = nullptr;
    REQUIRE(count == 1);

    // Assign to dereferenced value
    auto b3 = bp(1,2);
    *b3 = P{3,4};

    REQUIRE(b3->x == 3);
    REQUIRE(b3->y == 4);

    const P& p = *b3;
}

TEST_CASE("BoxPtr dereference", "[box_ptr]") {
    lstd::BoxPtr<int> b1(new int(42));
    lstd::BoxPtr<P> b2 = bp(1,2);
    lstd::BoxPtr<P> b3;

    REQUIRE(*b1 == 42);
    REQUIRE(b2->x == 1);
    REQUIRE(b2->y == 2);

    // Dereferencing null throws exception on development mode
    REQUIRE_THROWS_AS(*b3, lstd::AssertionError);
}

lstd::BoxPtr<P> bp(int x, int y) {
    return lstd::BoxPtr<P>(new P{x,y});
}

lstd::BoxPtr<Counter> bc(int *count) {
    return lstd::BoxPtr<Counter>(new Counter(count));
}