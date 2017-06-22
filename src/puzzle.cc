#include <deque>
#include <memory>
#include <set>

#include "puzzle.h"

// TODO: Remove function.
std::shared_ptr<state> XXXlowest_fcost(std::set<std::shared_ptr<state>> s) {
    std::shared_ptr<state> min_state = *s.begin();
    int min_fcost = min_state->get_fcost();

    for (const auto& st : s) {
        if (st->get_fcost() < min_fcost) {
            min_state = st; min_fcost = st->get_fcost();
        }
    }
    return min_state;
}

// TODO: Remove function.
std::shared_ptr<state> XXXfind_in_set(std::shared_ptr<state>f, std::set<std::shared_ptr<state>> s) {
    for (const auto& st : s) {
        if (*st == *f) return f;
    }
    return nullptr;
}

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

// TODO: Clean up.
std::deque<int> puzzle::solve(astar_heuristic heuristic) {
    std::shared_ptr<state> focus, next_focus;
    std::set<std::shared_ptr<state>> closed_states, open_states;
    std::vector<int> moves;
    int prospective_gcost;

    auto start = this->init;
    this->init->gcost = 0;
    this->init->hcost = heuristic(*this->init, *this->goal);

    open_states.insert(this->init);

    while (!open_states.empty()) {
        focus = XXXlowest_fcost(open_states);

        if (*focus == *this->goal) {
            this->goal->parent_move = focus->parent_move;
            this->goal->parent = focus->parent;;
            break;
        }

        open_states.erase(focus);
        closed_states.insert(focus);

        moves = focus->get_possible_moves();
        for (const auto square : moves) {
            next_focus = std::make_shared<state>(*focus);
            next_focus->move_square(square);

            if (XXXfind_in_set(next_focus, closed_states)) continue;
            if (!XXXfind_in_set(next_focus, open_states)) open_states.insert(next_focus);

            prospective_gcost = focus->gcost + MOVEMENT_COST;
            if (prospective_gcost < next_focus->gcost) continue;

            next_focus->parent_move = square;
            next_focus->parent = focus;
            next_focus->gcost = prospective_gcost;
            next_focus->hcost = heuristic(*next_focus, *this->goal);
        }
    }
    return this->construct_path();
}

int puzzle::get_expanded_nodes() {
    return this->expanded_nodes;
}

std::deque<int> puzzle::construct_path() {
    std::deque<int> search_path {};
    std::shared_ptr<state> focus = this->goal;

    while (focus && focus->parent_move != -1) {
        search_path.push_front(focus->parent_move);
        focus = focus->parent;
    }
    return search_path;
}
