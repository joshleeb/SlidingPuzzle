#include <utility>

#include "puzzle.h"
#include "state.h"

int heuristic::manhattan(state& s1, state& s2) {
    int delta = 0;
    std::pair<int, int> s1_loc, s2_loc;

    for (size_t i = 0; i < s1.get_board().size(); i++) {
        s1_loc = s1.get_location(i);
        s2_loc = s2.get_location(i);

        delta += std::abs(s1_loc.first - s2_loc.first) +
                 std::abs(s1_loc.second - s2_loc.second);
    }

    return delta;
}
