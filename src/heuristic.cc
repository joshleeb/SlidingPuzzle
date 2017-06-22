#include "puzzle.h"
#include "state.h"

int heuristic::manhattan(state &s1, state &s2) {
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

