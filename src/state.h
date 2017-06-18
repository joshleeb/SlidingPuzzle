#pragma once

#include <vector>
#include <memory>
#include <tuple>

#define BLANK 0

class state {
    std::vector<int> board;

    public:
    int gcost, hcost;
    std::shared_ptr<state> parent;

    state(std::vector<int> board);

    bool operator ==(const state &s);

    void move_square(int square);
    std::vector<int> get_possible_moves();

    int get_index(const int value);
    std::tuple<int, int> get_location(const int value);

    int get_fcost();
};
