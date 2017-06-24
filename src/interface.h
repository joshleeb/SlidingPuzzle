#pragma once

#include <istream>
#include <vector>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

class options {
public:
    bool stats, verbose;

    options(bool stats, bool verbose);
};

namespace interface {
    options process_cli(int argc, char* argv[]);

    std::vector<int> read_board(std::istream& stream);
    std::vector<int> create_goal_board(std::vector<int> init_board);

    std::vector<std::string> get_tokens(std::istream& stream);
}
