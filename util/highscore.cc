
#include <iostream>
#include <set>
#include <algorithm>
#include <stdexcept>

#include "../highscore.h"


std::string quote(const std::string& s) {
    std::string ret;

    for (unsigned char c : s) {
        if (c == '\\') ret += "\\\\";
        else if (c == '"') ret += "\\\"";
        else if (c <= 31) ret += " ";
        else ret += c;
    }

    return ret;
}


void _process(size_t n, const bones::bone_t::fakeobj& name, const bones::bone_t::fakeobj& cause,
              unsigned int plev, int dlev, double worth, bool victory) {

    if (n != 0)
        std::cout << ",";

    auto _cause = cause;
    _cause.name = quote(_cause.name);

    auto _name = name;
    _name.name = quote(_name.name);

    std::cout << nlp::message("\n{\"dlev\": %d, \"plev\": %d, \"name\": \"%S\", \"cause\": \"%s\", \"worth\": %d, \"victory\": %s}",
                              dlev+1, plev+1, _name, _cause, worth,
                              std::string(victory ? "true" : "false"));
}


int main(int argc, char** argv) {

    try {

        highscore::Scores scores;

        std::cout << nlp::message("{\"num_games\": %d,\n", scores.scores.size());
        std::cout << "\"highscores\": {";

        std::cout << "\"ts\": [";
        scores.by_ts(_process);
        std::cout << "]," << std::endl;

        std::cout << "\"plev\": [";
        scores.by_plev(_process);
        std::cout << "]," << std::endl;

        std::cout << "\"dlev_d\": [";
        scores.by_dlev_d(_process);
        std::cout << "]," << std::endl;

        std::cout << "\"dlev_a\": [";
        scores.by_dlev_a(_process);
        std::cout << "]," << std::endl;

        std::cout << "\"worth\": [";
        scores.by_worth(_process);
        std::cout << "]" << std::endl;

        std::cout << "}}" << std::endl;

    } catch (std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;

    } catch (...) {
        std::cerr << "Unknown fatal error." << std::endl;
        return 1;
    }

    return 0;
}

