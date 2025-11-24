#include <catch2/catch_test_macros.hpp>
#include <lstd/memory/box_ptr.hpp>
#include "utils.hpp"

using P = Point;
lstd::BoxPtr<P> bp(int x, int y);
lstd::BoxPtr<Counter> bc(int *count);

TEST_CASE("BoxPtr Construction", "[box_ptr]") {
    lstd::BoxPtr<P> b2;
    lstd::BoxPtr<P> b1(new P{1,2});
    lstd::BoxPtr<P> b3(bp(3,4));

    REQUIRE(b1.RawPtr() != nullptr);
    REQUIRE(b2.RawPtr() == nullptr);
    REQUIRE(b3.RawPtr() != nullptr);
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
}


lstd::BoxPtr<P> bp(int x, int y) {
    return lstd::BoxPtr<P>(new P{x,y});
}

lstd::BoxPtr<Counter> bc(int *count) {
    return lstd::BoxPtr<Counter>(new Counter(count));
}