#include <catch2/catch_test_macros.hpp>
#include <lstd/vector.hpp>

TEST_CASE("Vector control test", "[vector]") {
    auto v = lstd::Vector();
    REQUIRE(v.Size() == 42);
}