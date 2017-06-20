#include <memory>
#include <deque>

#include "puzzle.h"

puzzle::puzzle(std::shared_ptr<state> init, std::shared_ptr<state> goal) {
    this->init = init;
    this->goal = goal;

    this->expanded_nodes = 0;
}

bool puzzle::is_solvable() {
    int inversions = this->init->count_inversions();

    // If the board width is odd, then the puzzle is solvable if the number of inversions is even.
    if (this->init->get_board_width() % 2 != 0) return inversions % 2 == 0;

    auto blank_loc = this->init->get_location(BLANK);
    int row_from_bottom = (this->init->get_board_width() - 1) - std::get<1>(blank_loc);

    // If the board width is even, then the puzzle solvable if one of the following holds:
    //  + The blank is on an even row counting from the bottom and the number if inversions is odd.
    //  + The blank is on an odd row counting from the bottom and the number if inversions is even.
    return row_from_bottom % 2 == 0 != inversions % 2 == 0;
}

// std::deque<state> puzzle::solve(astar_heuristic h) {
//     (void) h;
//     return this->construct_path();
// }

int puzzle::get_expanded_nodes() {
    return this->expanded_nodes;
}

// std::deque<state> puzzle::construct_path() {
//     return std::deque<state>();
// }
