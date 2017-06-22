#include <istream>
#include <vector>
#include <string>

#include <boost/algorithm/string.hpp>

#include "interface.h"

std::vector<int> interface::read_board(std::istream& stream) {
    std::vector<int> board {};

    for (const auto& token : interface::get_tokens(stream)) {
        board.push_back(stoi(token));
    }
    return board;
}

std::vector<int> interface::create_goal_board(std::vector<int> init_board) {
    std::vector<int> board {};

    for (size_t i = 1; i < init_board.size(); i++) {
        board.push_back(i);
    }
    board.push_back(0);

    return board;
}

std::vector<std::string> interface::get_tokens(std::istream& stream) {
    std::vector<std::string> tokens = {};
    std::string raw_board;

    getline(stream, raw_board);
    boost::split(tokens, raw_board, boost::is_any_of("\n\t "));

    return tokens;
}
