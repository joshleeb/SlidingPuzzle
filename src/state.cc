#include <algorithm>
#include <cmath>
#include <iterator>
#include <memory>
#include <set>
#include <stdexcept>
#include <tuple>
#include <vector>

#include "state.h"


// A board is represented as a vector such as vector(1, 2, 3, 4) represents the board where the top
// row is (1, 2) and the bottom row is (3, 4).
state::state(std::vector<int> board) {
    this->board = board;
    this->board_width = (int) std::sqrt(board.size());

    if (board.size() <= 4) {
        throw std::invalid_argument("board is too small");
    }
    if (std::pow(this->board_width, 2) != board.size()) {
        throw std::invalid_argument("board is not a square");
    }
    if (std::find(board.begin(), board.end(), 0) == board.end()) {
        throw std::invalid_argument("board doesn't contain a blank space");
    }

    this->gcost = std::numeric_limits<int>::max();
    this->hcost = std::numeric_limits<int>::max();
}

bool state::operator ==(const state &s) {
    return this->board == s.board;
}

int state::count_inversions() {
    int inversions = 0;
    for (size_t i = 0; i < this->board.size(); i++) {
        for (size_t j = i + 1; j < this->board.size(); j++) {
            if (this->get_index(i) > this->get_index(j)) {
                inversions++;
            }
        }
    }

    return inversions;
}

void state::move_square(int square) {
    auto square_index = this->get_index(square);
    auto blank_index = this->get_index(BLANK);

    this->board[blank_index] = square;
    this->board[square_index] = BLANK;
}

std::vector<int> state::get_possible_moves() {
    auto moves = std::vector<int>();

    int blank_index = this->get_index(BLANK);
    int up_index = blank_index + this->board_width;

    // Up from blank.
    if (up_index >= 0 && (size_t) blank_index + this->board_width < this->board.size()) {
        moves.push_back(this->board[blank_index + this->board_width]);
    }

    // Down from blank.
    if (blank_index - this->board_width >= 0) {
        moves.push_back(this->board[blank_index - this->board_width]);
    }

    // Left from blank.
    if (blank_index % this->board_width > 0) {
        moves.push_back(this->board[blank_index - 1]);
    }

    // Right from blank.
    if (blank_index % this->board_width < this->board_width - 1) {
        moves.push_back(this->board[blank_index + 1]);
    }

    return moves;
}

int state::get_index(const int value) {
    auto it = std::find(this->board.begin(), this->board.end(), value);

    if (it == this->board.end()) return -1;
    return std::distance(this->board.begin(), it);
}

std::tuple<int, int> state::get_location(const int value) {
    auto index = this->get_index(value);

    return std::make_tuple(
        index % this->board_width,  // x-coordinate
        std::floor(index / this->board_width)   // y-coordinate
    );
}

int state::get_fcost() {
    if (this->gcost == std::numeric_limits<int>::max()) return this->gcost;
    if (this->hcost == std::numeric_limits<int>::max()) return this->hcost;
    return this->gcost + this->hcost;
}

int state::get_board_width() {
    return this->board_width;
}

std::vector<int> state::get_board() {
    return this->board;
}

bool fcost_state_ptr_cmp::operator()(std::shared_ptr<state> left, std::shared_ptr<state> right) {
    return left->get_fcost() < right->get_fcost();
}
