#include <catch2/catch_test_macros.hpp>
#include <lstd/utils/pair.hpp>
#include <map> // TODO replace with our own map
#include <unordered_map> // TODO replace with our own map


lstd::Pair<int,int> pii(int i, int j);
lstd::Pair<int,int> pii(int i);
lstd::Pair<int,int> pii();

TEST_CASE("Pair construction", "[pair]") {
    // Default construction uses default values
    auto p1 = lstd::Pair<int,int>();
    REQUIRE(p1.first == 0);
    REQUIRE(p1.second == 0);

    // Constructing with values assigns them properly
    auto p2 = lstd::Pair<int,int>(1,2);
    REQUIRE(p2.first == 1);
    REQUIRE(p2.second == 2);

    // When both types are the same, you can construct with a single arg
    auto p3 = lstd::Pair<int,int>(42);
    REQUIRE(p3.first == p3.second);
    REQUIRE(p3.first == 42);

    // Can create it with braces syntax
    lstd::Pair<int,int> p4 = {3,4};
}

TEST_CASE("Pair equality", "[pair]") {
    auto p1 = pii();
    auto p0 = pii(0);

    REQUIRE(p0 == p1);
    // You can use rvalues in left hand and right hand
    REQUIRE(p0 == lstd::Pair<int, int>());
    REQUIRE(lstd::Pair<int, int>() == p0);
    REQUIRE(lstd::Pair<int, int>() == lstd::Pair<int, int>());

    auto p2 = pii(1,2);
    REQUIRE(!(p2 == p0)); // both values difer
    REQUIRE(!(p2 == pii(1,3))); // one value difers
    REQUIRE(!(p2 == pii(3,2))); // one value difers

    // We also have inequality
    REQUIRE(p2 != p0);
    REQUIRE(!(p2 != p2));
}

TEST_CASE("Pair order", "[pair]") {
    REQUIRE( pii(0,0) < pii(0,1) );  // equal first, second is smaller
    REQUIRE( pii(0,0) < pii(1,0) );  // first is smaller
    REQUIRE( pii(0,1) < pii(1,0) );  // first is smaller (second irrelevant)

    REQUIRE( !(pii(0,1) < pii(0,0)) );  // equal first, second larger
    REQUIRE( !(pii(1,0) < pii(0,0)) );  // first larger
    REQUIRE( !(pii(1,1) < pii(1,0)) );  // equal first, second larger
    REQUIRE( !(pii(1,1) < pii(1,1)) );  // identical pairs

    REQUIRE(pii(0, 1) > pii(0, 0)); // equal first, second larger
    REQUIRE(pii(1, 0) > pii(0, 0)); // first larger
    REQUIRE(pii(1, 0) > pii(0, 1)); // first larger (second irrelevant)

    REQUIRE(!(pii(0, 0) > pii(0, 1))); // equal first, second smaller
    REQUIRE(!(pii(0, 0) > pii(1, 0))); // first smaller
    REQUIRE(!(pii(1, 0) > pii(1, 1))); // equal first, second smaller
    REQUIRE(!(pii(1, 1) > pii(1, 1))); // identical pairs
}

TEST_CASE("Pair works with map", "[pair]") {
    // Supports ordering, therefore supports map
    std::map<lstd::Pair<int,int>, int> m;
    m[{1,2}] = 42;
    m[{1,1}] = 24;
    m[{0,0}] = 69;

    REQUIRE(m[{0,0}] == 69);
    REQUIRE(m[{1,1}] == 24);
    REQUIRE(m[{1,2}] == 42);
    REQUIRE(m.find({0,1}) == m.end()); // not there

    // Keys should be ordered
    lstd::Pair<int,int> keys[3];
    int i = 0;
    for(auto const& p : m) {
        keys[i++] = p.first;
    }

    for(int i = 0; i < 2; i++)
        REQUIRE(keys[i] < keys[i+1]);
}

TEST_CASE("Pair works with unordered map", "[pair]") {
    // Supports equality, hashing. Therefore supports unordered_map
    std::unordered_map<lstd::Pair<int,int>, int> m;

    m[{1,2}] = 42;
    m[{1,3}] = 69;

    REQUIRE(m[{1,2}] == 42);
    REQUIRE(m[{1,3}] == 69);
    REQUIRE(m.find({0,0}) == m.end());
}

// Utility functions

lstd::Pair<int,int> pii(int i, int j) {
    return lstd::Pair<int,int>(i,j);
}

lstd::Pair<int,int> pii(int i) {
    return lstd::Pair<int,int>(i);
}

lstd::Pair<int,int> pii() {
    return lstd::Pair<int,int>();
}