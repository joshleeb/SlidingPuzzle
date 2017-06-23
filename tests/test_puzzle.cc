#include <memory>
#include <tuple>

#include <catch/catch.hpp>

#include "../src/puzzle.h"

#define INIT_BOARD \
    std::vector<int> { 1, 2, 3, 4, 0, 5, 6, 7, 8 }
#define GOAL_BOARD \
    std::vector<int> { 1, 2, 3, 4, 5, 6, 7, 8, 0 }

SCENARIO("setting up puzzle", "[puzzle]") {
    GIVEN("init and goal states") {
        state init_state(INIT_BOARD);
        state goal_state(GOAL_BOARD);

        THEN("should setup a new puzzle") {
            REQUIRE_NOTHROW(puzzle(std::make_shared<state>(init_state),
                                   std::make_shared<state>(goal_state)));
        }
    }
}

SCENARIO("checking solvability", "[puzzle]") {
    GIVEN("a board of odd width with an even number of inversions") {
        std::vector<int> board{1, 2, 3, 4, 5, 7, 6, 0, 8};
        state new_state(board);

        CHECK(new_state.count_inversions() % 2 == 0);

        THEN("should be solvable") {
            puzzle new_puzzle(std::make_shared<state>(new_state),
                              std::make_shared<state>(new_state));

            REQUIRE(new_puzzle.is_solvable());
        }
    }

    GIVEN("a board of odd width with an odd number of inversions") {
        std::vector<int> board{1, 2, 3, 4, 5, 6, 7, 0, 8};
        state new_state(board);

        CHECK_FALSE(new_state.count_inversions() % 2 == 0);

        THEN("should not be solvable") {
            puzzle new_puzzle(std::make_shared<state>(new_state),
                              std::make_shared<state>(new_state));

            REQUIRE_FALSE(new_puzzle.is_solvable());
        }
    }

    GIVEN("a board of even width with an even number of inversions") {
        WHEN("blank is on an even row from the bottom") {
            std::vector<int> board{1, 2,  3,  4,  5,  6,  7,  8,
                                   9, 10, 11, 12, 13, 15, 14, 0};
            state new_state(board);

            auto blank_row = std::get<1>(new_state.get_location(BLANK)) + 1;
            CHECK((new_state.get_board_width() - blank_row) % 2 == 0);
            CHECK(new_state.count_inversions() % 2 == 0);

            THEN("should not be solvable") {
                puzzle new_puzzle(std::make_shared<state>(new_state),
                                  std::make_shared<state>(new_state));

                REQUIRE_FALSE(new_puzzle.is_solvable());
            }
        }

        WHEN("blank is on an odd row from the bottom") {
            std::vector<int> board{12, 1, 10, 2,  7, 11, 4, 14,
                                   5,  0, 9,  15, 8, 13, 6, 3};
            state new_state(board);

            auto blank_row = std::get<1>(new_state.get_location(BLANK)) + 1;
            CHECK_FALSE((new_state.get_board_width() - blank_row) % 2 == 0);
            CHECK(new_state.count_inversions() % 2 == 0);

            THEN("should be solvable") {
                puzzle new_puzzle(std::make_shared<state>(new_state),
                                  std::make_shared<state>(new_state));

                REQUIRE(new_puzzle.is_solvable());
            }
        }
    }

    GIVEN("a board of even width with an odd number of inversions") {
        WHEN("blank is on an even row from the bottom") {
            std::vector<int> board{1, 2,  3,  4,  5,  6,  7,  8,
                                   9, 10, 11, 12, 13, 14, 15, 0};
            state new_state(board);

            auto blank_row = std::get<1>(new_state.get_location(BLANK)) + 1;
            CHECK((new_state.get_board_width() - blank_row) % 2 == 0);
            CHECK_FALSE(new_state.count_inversions() % 2 == 0);

            THEN("should be solvable") {
                puzzle new_puzzle(std::make_shared<state>(new_state),
                                  std::make_shared<state>(new_state));

                REQUIRE(new_puzzle.is_solvable());
            }
        }

        WHEN("blank is on an odd row from the bottom") {
            std::vector<int> board{1, 2,  3, 4,  5,  6,  7,  9,
                                   8, 11, 0, 12, 13, 14, 10, 15};
            state new_state(board);

            auto blank_row = std::get<1>(new_state.get_location(BLANK)) + 1;
            CHECK_FALSE((new_state.get_board_width() - blank_row) % 2 == 0);
            CHECK_FALSE(new_state.count_inversions() % 2 == 0);

            THEN("should not be solvable") {
                puzzle new_puzzle(std::make_shared<state>(new_state),
                                  std::make_shared<state>(new_state));

                REQUIRE_FALSE(new_puzzle.is_solvable());
            }
        }
    }
}

SCENARIO("solving the puzzle", "[puzzle]") {
    GIVEN("a puzzle") {
        state init_state(std::vector<int>{1, 2, 3, 4, 0, 5, 6, 7, 8});
        state goal_state(std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 0});
        puzzle new_puzzle(std::make_shared<state>(init_state),
                          std::make_shared<state>(goal_state));

        THEN("should return moves from init to goal") {
            auto moves = new_puzzle.solve(heuristic::manhattan);

            CHECK(init_state != goal_state);
            CHECK_FALSE(moves.empty());

            for (const auto& square : moves) {
                init_state.move_square(square);
            }
            REQUIRE(init_state == goal_state);
        }
    }

    GIVEN("a puzzle that is already complete") {
        puzzle new_puzzle(std::make_shared<state>(state(INIT_BOARD)),
                          std::make_shared<state>(state(INIT_BOARD)));

        THEN("should return no moves") {
            auto moves = new_puzzle.solve(heuristic::manhattan);
            REQUIRE(moves.empty());
        }
    }
}

SCENARIO("getting expanded nodes count", "[puzzle]") {
    GIVEN("a puzzle") {
        puzzle new_puzzle(std::make_shared<state>(state(INIT_BOARD)),
                          std::make_shared<state>(state(GOAL_BOARD)));

        THEN("should return the expanded nodes count") {
            REQUIRE(new_puzzle.get_expanded_nodes() == 0);
        }
    }
}

SCENARIO("get state with lowest f cost in set", "[state]") {}

SCENARIO("getting state with minimum f cost", "[state]") {
    GIVEN("states with various costs") {
        state state_a(std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8});
        state state_b(std::vector<int>{1, 0, 2, 3, 4, 5, 6, 7, 8});
        state state_c(std::vector<int>{1, 2, 0, 3, 4, 5, 6, 7, 8});

        state_a.gcost = 1;
        state_a.hcost = 4;
        state_b.gcost = 7;
        state_b.hcost = 2;
        state_c.gcost = 1;
        state_c.hcost = 2;

        std::set<std::shared_ptr<state>> state_set{
            std::make_shared<state>(state_a), std::make_shared<state>(state_b),
            std::make_shared<state>(state_c)};

        THEN("should return state with lowest f cost") {
            REQUIRE(state_c == *get_lowest_fcost_state(state_set));
        }
    }
}
