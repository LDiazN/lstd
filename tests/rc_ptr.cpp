
#include <catch2/catch_test_macros.hpp>
#include <lstd/memory/rc_ptr.hpp>

struct P {
    int x,y;
    P(int _x, int _y) : x(_x), y(_y) {}
};

TEST_CASE("rc_ptr constructors", "[rc_ptr]") {
    auto v1 = lstd::Ptr<P>(new P(1,2)); // take ownership of this ptr
    auto v2 = lstd::Ptr<P>(P(3,4)); // from reference
    auto v3 = lstd::Ptr<P>(v2); // create from another one
    auto v4 = lstd::Ptr<P>(); // Create null ptr

    REQUIRE(v1.Count() == 1);
    REQUIRE(v2.Count() == 2);
    REQUIRE(v3.Count() == 2);
    REQUIRE(v4.Count() == 0);
}

TEST_CASE("rc_ptr equality", "[rc_ptr]") {

    auto v1 = lstd::Ptr<P>(); 
    auto p = new P(1,2);
    auto v2 = lstd::Ptr<P>(p); 
    auto v3 = lstd::Ptr<P>(v2);

    REQUIRE(v1 == nullptr); // null == null
    REQUIRE(v2 != nullptr); // p != null
    REQUIRE(v2 == p); // p == p
    REQUIRE(v2 == v3); // p == p
    REQUIRE(v2 != v1); // p != null
}

