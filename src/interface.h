#include <iostream>
#include <vector>

namespace interface {
    std::vector<int> read_board(std::istream& stream);
    std::vector<int> create_goal_board(std::vector<int> init_board);

    std::vector<std::string> get_tokens(std::istream& stream);
}

