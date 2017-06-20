#pragma once

#include <exception>
#include <memory>
#include <set>
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

    int count_inversions();

    void move_square(int square);
    std::vector<int> get_possible_moves();

    int get_fcost();

    int get_index(const int value);
    std::tuple<int, int> get_location(const int value);

    int get_board_width();
    std::vector<int> get_board();
};

struct fcost_state_ptr_cmp {
    bool operator()(std::shared_ptr<state> left, std::shared_ptr<state> right);
};
