#include <iostream>
#include <memory>
#include <vector>

#include "interface.h"
#include "puzzle.h"
#include "state.h"

int manhattan(state &s1, state &s2) {
    int delta = 0;
    std::tuple<int, int> s1_loc, s2_loc;

    for (size_t i = 0; i < s1.get_board().size(); i++) {
        s1_loc = s1.get_location(i);
        s2_loc = s2.get_location(i);

        delta += std::abs(std::get<0>(s1_loc) - std::get<0>(s2_loc))
            + std::abs(std::get<1>(s1_loc) - std::get<1>(s2_loc));
    }

    return delta;
}

int main(int argc, char *argv[]) {
    auto init_board = interface::read_board(std::cin);
    auto goal_board = interface::create_goal_board(init_board);

    puzzle sliding_puzzle(
        std::make_shared<state>(state(init_board)),
        std::make_shared<state>(state(goal_board))
    );

    auto moves = sliding_puzzle.solve(manhattan);

    for (const auto square : moves) {
        std::cout << square << " ";
    }
    std::cout << "\n";

    return EXIT_SUCCESS;
}
