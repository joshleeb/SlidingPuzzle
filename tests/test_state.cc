#include <stdexcept>
#include <vector>

#include <catch/catch.hpp>

#include "../src/state.h"

SCENARIO("valid state", "[state]") {
    GIVEN("a valid board") {
        std::vector<int> board {1, 2, 3, 4, 5, 6, 7, 8, 0};

        THEN("should setup a new state") {
            state new_state(board);

            REQUIRE(new_state.gcost == std::numeric_limits<int>::max());
            REQUIRE(new_state.hcost == std::numeric_limits<int>::max());
            REQUIRE(new_state.parent == nullptr);
            REQUIRE(new_state.get_board_width() == 3);
        }
    }
}

SCENARIO("invalid state", "[!throws][state]") {
    GIVEN("a board that is too small") {
        std::vector<int> board {1, 2, 3, 0};

        THEN("should throw an invalid argument exception") {
            REQUIRE_THROWS_AS(state(board), std::invalid_argument);
        }
    }

    GIVEN("a board that isn't a square") {
        std::vector<int> board {1, 2, 3, 4, 0};

        THEN("should throw an invalid argument exception") {
            REQUIRE_THROWS_AS(state(board), std::invalid_argument);
        }
    }

    GIVEN("a board without an blank space") {
        std::vector<int> board {1, 2, 3, 4, 5, 6, 7, 8, 9};

        THEN("should throw an invalid argument exception") {
            REQUIRE_THROWS_AS(state(board), std::invalid_argument);
        }
    }
}
