#include <iostream>
#include <memory>
#include <vector>

#include "interface.h"
#include "puzzle.h"
#include "state.h"

int run_solver(options opts) {
    auto init_board = interface::read_board(std::cin);
    auto goal_board = interface::create_goal_board(init_board);

    puzzle sliding_puzzle(
        std::make_shared<state>(state(init_board)),
        std::make_shared<state>(state(goal_board))
    );

    auto moves = sliding_puzzle.solve(heuristic::manhattan);

    sliding_puzzle.display_path(moves, opts.verbose);
    if (opts.stats) sliding_puzzle.display_stats(moves);

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    auto opts = interface::process_cli(argc, argv);
    return run_solver(opts);
}
