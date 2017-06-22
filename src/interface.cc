#include <iostream>
#include <vector>
#include <string>

#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>

#include "interface.h"

const char* desc_text =
    "solver [OPTIONS...]\n"
    "Sliding puzzle solver.\n\n"
    "OPTIONS";

options::options(bool stats, bool verbose) {
    this->stats = stats;
    this->verbose = verbose;
}

options interface::process_cli(int argc, char* argv[]) {
    po::variables_map vm;
    po::options_description desc(desc_text);

    desc.add_options()
        ("help,h", po::bool_switch()->default_value(false), "Show this help")
        ("stats,s", po::bool_switch()->default_value(false), "Show search statistics")
        ("verbose,v", po::bool_switch()->default_value(false), "Show each state in solution path")
    ;

    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n\n";
        exit(EXIT_FAILURE);
    }

    if (vm["help"].as<bool>()) {
        std::cout << desc << "\n";
        exit(EXIT_SUCCESS);
    }
    return options(vm["stats"].as<bool>(), vm["verbose"].as<bool>());
}

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
