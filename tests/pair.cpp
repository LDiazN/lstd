#include <catch2/catch_test_macros.hpp>
#include <lstd/utils/pair.hpp>


TEST_CASE("Pair construction", "[pair]") {
    auto p1 = lstd::Pair<int, int>();
    REQUIRE(p1.first == 0);
    REQUIRE(p1.second == 0);

    // Default construction uses default values
    auto p2 = lstd::Pair<int, int>(1,2);

    REQUIRE(p2.first == 1);
    REQUIRE(p2.second == 2);
}

TEST_CASE("Pair equality", "[vector]") {
    auto p1 = lstd::Pair<int, int>();



}