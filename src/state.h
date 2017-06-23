#pragma once

#include <exception>
#include <memory>
#include <set>
#include <utility>
#include <vector>

#define BLANK 0

class state {
    std::vector<int> board;
    int board_width;

public:
    int gcost, hcost;

    int parent_move;
    std::shared_ptr<state> parent;

    state(std::vector<int> board);

    bool operator==(const state& s);
    bool operator!=(const state& s);

    int count_inversions();

    void move_square(int square);
    std::vector<int> get_possible_moves();

    void display();

    int get_fcost();

    int get_index(const int value);
    std::pair<int, int> get_location(const int value);

    int get_board_width();
    std::vector<int> get_board();
};

std::shared_ptr<state> get_lowest_fcost_state(
    std::set<std::shared_ptr<state>> state_set);
std::shared_ptr<state> find_state(std::shared_ptr<state> focus,
                                  std::set<std::shared_ptr<state>> state_set);
