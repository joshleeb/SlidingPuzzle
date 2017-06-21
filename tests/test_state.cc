#include <cmath>
#include <memory>
#include <set>
#include <stdexcept>
#include <tuple>
#include <vector>

#include <catch/catch.hpp>

#include "../src/state.h"

#define DEFAULT_BOARD std::vector<int> {1, 2, 3, 4, 5, 6, 7, 8, 0}

SCENARIO("setting up state", "[state]") {
    GIVEN("a valid board") {
        auto board = DEFAULT_BOARD;

        THEN("should setup a new state") {
            REQUIRE_NOTHROW(state(board));

            state new_state(board);

            REQUIRE(new_state.gcost == std::numeric_limits<int>::max());
            REQUIRE(new_state.hcost == std::numeric_limits<int>::max());
            REQUIRE(new_state.parent_move == -1);
            REQUIRE(new_state.get_board_width() == 3);
        }
    }

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

SCENARIO("comparing equality of states", "[state]") {
    GIVEN("states with equal boards") {
        THEN("should be equal") {
            state state_a(DEFAULT_BOARD);
            state state_b(DEFAULT_BOARD);

            REQUIRE(state_a == state_b);
        }
    }

    GIVEN("states with unequal boards") {
        THEN("should not be equal") {
            state state_a(std::vector<int> {1, 2, 3, 4, 5, 6, 7, 8, 0});
            state state_b(std::vector<int> {0, 8, 7, 6, 5, 4, 3, 2, 1});

            REQUIRE_FALSE(state_a == state_b);
        }
    }
}

SCENARIO("comparing inequality of states", "[state]") {
    GIVEN("states with equal boards") {
        THEN("should be equal") {
            state state_a(DEFAULT_BOARD);
            state state_b(DEFAULT_BOARD);

            REQUIRE_FALSE(state_a != state_b);
        }
    }

    GIVEN("states with unequal boards") {
        THEN("should not be equal") {
            state state_a(std::vector<int> {1, 2, 3, 4, 5, 6, 7, 8, 0});
            state state_b(std::vector<int> {0, 8, 7, 6, 5, 4, 3, 2, 1});

            REQUIRE(state_a != state_b);
        }
    }
}

SCENARIO("counting inversions", "[state]") {
    GIVEN("a state with no inversions") {
        state new_state(std::vector<int> {0, 1, 2, 3, 4, 5, 6, 7, 8});

        THEN("should return 0") {
            REQUIRE(new_state.count_inversions() == 0);
        }
    }

    GIVEN("a state with inversions") {
        state new_state(std::vector<int> {0, 2, 3, 1, 4, 5, 6, 7, 8});

        THEN("should return number of inversions") {
            REQUIRE(new_state.count_inversions() == 2);
        }
    }
}

SCENARIO("moving squares", "[state]") {
    GIVEN("a state") {
        state new_state(DEFAULT_BOARD);

        WHEN("a square is moved") {
            THEN("should move the blank square") {
                new_state.move_square(8);

                std::vector<int> expected_board {1, 2, 3, 4, 5, 6, 7, 0, 8};
                REQUIRE(new_state.get_board() == expected_board);
            }
        }
    }
}

SCENARIO("getting possible moves", "[state]") {
    GIVEN("a state with blank in bottom right corner") {
        state new_state(std::vector<int> {1, 2, 3, 4, 5, 6, 7, 8, 0});

        THEN("should return possible moves") {
            std::vector<int> expected_moves {8, 6};
            REQUIRE_THAT(new_state.get_possible_moves(), Catch::Contains(expected_moves));
        }
    }

    GIVEN("a state with blank in top left corner") {
        state new_state(std::vector<int> {0, 1, 2, 3, 4, 5, 6, 7, 8});

        THEN("should return possible moves") {
            std::vector<int> expected_moves {1, 3};
            REQUIRE_THAT(new_state.get_possible_moves(), Catch::Contains(expected_moves));
        }
    }

    GIVEN("a state with blank in the center") {
        state new_state(std::vector<int> {1, 2, 3, 4, 0, 5, 6, 7, 8});

        THEN("should return possible moves") {
            std::vector<int> expected_moves {2, 4, 5, 7};
            REQUIRE_THAT(new_state.get_possible_moves(), Catch::Contains(expected_moves));
        }
    }
}

SCENARIO("getting f cost", "[state]") {
    GIVEN("a state") {
        state new_state(DEFAULT_BOARD);

        WHEN("g cost is not max and h cost is not max") {
            new_state.gcost = 1;
            new_state.hcost = 2;

            THEN("should return sum") {
                REQUIRE(new_state.get_fcost() == 3);
            }
        }

        WHEN("g cost is max") {
            new_state.gcost = std::numeric_limits<int>::max();
            new_state.hcost = 1;

            THEN("should return max") {
                REQUIRE(new_state.get_fcost() == std::numeric_limits<int>::max());
            }
        }

        WHEN("h cost is max") {
            new_state.gcost = 1;
            new_state.hcost = std::numeric_limits<int>::max();

            THEN("should return max") {
                REQUIRE(new_state.get_fcost() == std::numeric_limits<int>::max());
            }
        }
    }
}

SCENARIO("getting index of square", "[state]") {
    GIVEN("a state") {
        state new_state(DEFAULT_BOARD);

        WHEN("searching for an existing square") {
            THEN("should return index of the square") {
                REQUIRE(new_state.get_index(2) == 1);
            }
        }

        WHEN("searching for a non-existing square") {
            THEN("should return -1 index") {
                REQUIRE(new_state.get_index(9) == -1);
            }
        }
    }
}

SCENARIO("getting location of square", "[state]") {
    GIVEN("a state") {
        state new_state(std::vector<int> {0, 1, 2, 3, 4, 5, 6, 7, 8});

        THEN("should return location of the square") {
            int square = 0;

            std::tuple<int, int> expected_location_a {0, 1};
            REQUIRE(new_state.get_location(3) == expected_location_a);

            std::tuple<int, int> expected_location_b {1, 1};
            REQUIRE(new_state.get_location(4) == expected_location_b);
        }
    }
}

SCENARIO("getting board width", "[state]") {
    GIVEN("a state") {
        state new_state(DEFAULT_BOARD);

        THEN("should return the board") {
            auto board_size = DEFAULT_BOARD.size();
            REQUIRE(new_state.get_board_width() == std::sqrt(board_size));
        }
    }
}

SCENARIO("getting board", "[state]") {
    GIVEN("a state") {
        state new_state(DEFAULT_BOARD);

        THEN("should return the board") {
            auto expected_board = DEFAULT_BOARD;
            REQUIRE(new_state.get_board() == expected_board);
        }
    }
}

SCENARIO("getting states with minimum and maximum f cost", "[state]") {
    GIVEN("states with various costs") {
        state state_a(std::vector<int> {0, 1, 2, 3, 4, 5, 6, 7, 8});
        state state_b(std::vector<int> {1, 0, 2, 3, 4, 5, 6, 7, 8});
        state state_c(std::vector<int> {1, 2, 0, 3, 4, 5, 6, 7, 8});

        state_a.gcost = 1; state_a.hcost = 4;
        state_b.gcost = 7; state_b.hcost = 2;
        state_c.gcost = 1; state_c.hcost = 2;

        WHEN("using set with f cost comparitor") {
            std::set<std::shared_ptr<state>, fcost_state_ptr_cmp> states_set {
                std::make_shared<state>(state_a),
                std::make_shared<state>(state_b),
                std::make_shared<state>(state_c)
            };

            THEN("should begin with min f cost state") {
                REQUIRE(state_c == **states_set.begin());
            }

            THEN("should end with max f cost state") {
                REQUIRE(state_b == **states_set.rbegin());
            }
        }
    }
}
