#include <istream>
#include <vector>

#include <catch/catch.hpp>

#include "../src/interface.h"

SCENARIO("reading board from stream", "[interface]") {
    GIVEN("a stream of board tokens") {
        std::istringstream string_stream("0 1 10");

        THEN("should get board") {
            auto tokens = interface::read_board(string_stream);

            std::vector<int> expected_tokens = {0, 1, 10};
            REQUIRE(tokens == expected_tokens);
        }
    }
}

SCENARIO("creating a goal board", "[interface]") {
    GIVEN("an initial board state") {
        std::vector<int> init_board {0, 8, 7, 6, 5, 4, 3, 2, 1};

        THEN("should create goal board of the same size") {
            auto goal_board = interface::create_goal_board(init_board);

            std::vector<int> expected_board = {1, 2, 3, 4, 5, 6, 7, 8, 0};
            REQUIRE(goal_board == expected_board);
        }
    }
}

SCENARIO("getting tokens from stream", "[interface]") {
    GIVEN("a stream of board tokens") {
        std::istringstream string_stream("0 1 10");

        THEN("should get tokens") {
            auto tokens = interface::get_tokens(string_stream);

            std::vector<std::string> expected_tokens = {"0", "1", "10"};
            REQUIRE(tokens == expected_tokens);
        }
    }
}
