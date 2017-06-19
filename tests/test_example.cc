#include <catch/catch.hpp>

TEST_CASE("Equality of 1") {
    REQUIRE(1 == 1);
}

TEST_CASE("Inequality of 1") {
    REQUIRE(1 != 2);
}
