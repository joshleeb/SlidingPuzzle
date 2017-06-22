#include <iostream>
#include <memory>
#include <vector>

#include "interface.h"
#include "puzzle.h"
#include "state.h"

int main(int argc, char *argv[]) {
    auto init_board = interface::read_board(std::cin);
    auto goal_board = interface::create_goal_board(init_board);

    puzzle sliding_puzzle(
        std::make_shared<state>(state(init_board)),
        std::make_shared<state>(state(goal_board))
    );

    auto moves = sliding_puzzle.solve(heuristic::manhattan);

    for (const auto square : moves) {
        std::cout << square << " ";
    }
    std::cout << "\n";

    return EXIT_SUCCESS;
}
