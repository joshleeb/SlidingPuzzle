#pragma once

#include <memory>
#include <deque>

#include "state.h"

#define MOVEMENT_COST 1

typedef int (*astar_heuristic)(state& s1, state& s2);

namespace heuristic {
    int manhattan(state& s1, state& s2);
}

class puzzle {
    std::shared_ptr<state> init;
    std::shared_ptr<state> goal;

    // Count of nodes expanded in A* search.
    int expanded_nodes;

    // Construct the path from the A* search tree.
    std::deque<int> construct_path();

public:
    puzzle(std::shared_ptr<state> init, std::shared_ptr<state> goal);

    bool is_solvable();
    std::deque<int> solve(astar_heuristic heuristic);

    void display_path(std::deque<int> moves, bool is_verbose);
    void display_stats(std::deque<int> moves);

    int get_expanded_nodes();
};
