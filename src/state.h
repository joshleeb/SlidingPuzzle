#pragma once

#include <exception>
#include <memory>
#include <tuple>
#include <vector>

#define BLANK 0

class state {
    std::vector<int> board;
    int board_width;

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
    int get_board_width();
};
