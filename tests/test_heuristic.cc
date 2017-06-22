#include <catch/catch.hpp>

#include "../src/puzzle.h"
#include "../src/state.h"

SCENARIO("manhattan heuristic", "[heuristic]") {
    GIVEN("two different states") {
        state state1(std::vector<int> {1, 2, 3, 4, 5, 6, 7, 8, 0});
        state state2(std::vector<int> {8, 2, 4, 4, 3, 7, 6, 0, 1});

        THEN("should return manhattan heuristic") {
            REQUIRE(heuristic::manhattan(state1, state2) == 22);
        }
    }

    GIVEN("two identical states") {
        state new_state(std::vector<int> {1, 2, 3, 4, 5, 6, 7, 8, 0});

        THEN("should return zero") {
            REQUIRE(heuristic::manhattan(new_state, new_state) == 0);
        }
    }
}
