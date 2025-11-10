
#include <catch2/catch_test_macros.hpp>
#include <lstd/memory/rc_ptr.hpp>

TEST_CASE("rc_ptr constructors", "[rc_ptr]") {
    struct P {
        int x,y;
        P(int _x, int _y) : x(_x), y(_y) {}
    };

    auto v1 = lstd::Ptr<P>(new P(1,2)); // take ownership of this ptr
    auto v2 = lstd::Ptr<P>(P(3,4)); // from reference
    auto v3 = lstd::Ptr<P>(v2); // create from another one
}