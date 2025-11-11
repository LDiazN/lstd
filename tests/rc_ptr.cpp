
#include <catch2/catch_test_macros.hpp>
#include <lstd/memory/rc_ptr.hpp>

struct P {
    int x,y;
};

TEST_CASE("rc_ptr constructors", "[rc_ptr]") {
    auto v1 = lstd::Ptr<P>(new P{1,2}); // take ownership of this ptr
    auto v2 = lstd::Ptr<P>(P{3,4}); // from reference
    auto v3 = lstd::Ptr<P>(v2); // create from another one
    auto v4 = lstd::Ptr<P>(); // Create null ptr

    REQUIRE(v1.Count() == 1);
    REQUIRE(v2.Count() == 2);
    REQUIRE(v3.Count() == 2);
    REQUIRE(v4.Count() == 0);
}

TEST_CASE("rc_ptr equality", "[rc_ptr]") {

    auto v1 = lstd::Ptr<P>(); 
    auto p = new P{1,2};
    auto v2 = lstd::Ptr<P>(p); 
    auto v3 = lstd::Ptr<P>(v2);

    REQUIRE(v1 == nullptr); // null == null
    REQUIRE(v2 != nullptr); // p != null
    REQUIRE(v2 == p); // p == p
    REQUIRE(v2 == v3); // p == p
    REQUIRE(v2 != v1); // p != null
}

TEST_CASE("rc_ptr deref", "[rc_ptr]") {
    auto v = lstd::Ptr<P>(new P{1,2});

    REQUIRE((*v).x == 1);
    REQUIRE((*v).y == 2);

    lstd::Ptr<P> v1(v);

    REQUIRE((*v1).x == 1);
    REQUIRE((*v1).y == 2);
    REQUIRE(v1->y == 2); // arrow syntax should also be available
}

TEST_CASE("rc_ptr assign", "[rc_ptr]") {
    auto v = lstd::Ptr<P>(new P{1,2});
    // Start null and assign existent value
    lstd::Ptr<P> v1;
    REQUIRE(v1 == nullptr);

    v1 = v;
    REQUIRE(v1->x == v->x);

    // Start with something and assign value
    lstd::Ptr<P> v2(new P{3,4});
    v2 = v1;
    REQUIRE(v1->x == v2->x);
    REQUIRE(v2.Count() == 3); // 3 references to (1,2)

    // Assign null to previous value
    v2 = nullptr;
    REQUIRE(v2 == nullptr);
    REQUIRE(v1.Count() == 2);

    // Assign null to null does nothing
    lstd::Ptr<P> v3;
    v3 = nullptr;

    // Assign to yourself should not increase ref count
    lstd::Ptr<P> v4(new P{5,6});
    v4 = v4;
    REQUIRE(v4.Count() == 1);

    // Transitive self-assign
    lstd::Ptr<P> v5(new P{7,8});
    lstd::Ptr<P> v6(v5);
    v5 = v6;
    REQUIRE(v5.Count() == 2);
}
