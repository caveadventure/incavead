
#include <iostream>
#include <set>
#include <algorithm>
#include <stdexcept>

#include "../serialize.h"
#include "../common_types.h"
#include "../common.h"
#include "../bones.h"
#include "../nlp.h"

struct order_t {
    int dlev;
    unsigned int plev;
    double worth;
    bones::bone_t bone;

    bool victory;

    // HACK!

    order_t() : dlev(0), plev(0), worth(0), victory(false) {}
    order_t(int l, const bones::bone_t& b) : dlev(l), plev(b.level), worth(b.worth), bone(b), victory(b.cause.name == "VICTORY") {}
};

bool sort_plev(const order_t& a, const order_t& b) {
    if (a.victory > b.victory) return true;
    if (a.victory == b.victory && a.plev > b.plev) return true;
    if (a.victory == b.victory && a.plev == b.plev && a.dlev > b.dlev) return true;
    if (a.victory == b.victory && a.plev == b.plev && a.dlev == b.dlev && a.worth > b.worth) return true;
    return false;
}

bool sort_dlev_d(const order_t& a, const order_t& b) {
    if (a.victory > b.victory) return true;
    if (a.victory == b.victory && a.dlev > b.dlev) return true;
    if (a.victory == b.victory && a.dlev == b.dlev && a.plev > b.plev) return true;
    if (a.victory == b.victory && a.dlev == b.dlev && a.plev == b.plev && a.worth > b.worth) return true;
    return false;
}

bool sort_dlev_a(const order_t& a, const order_t& b) {
    if (a.victory > b.victory) return true;
    if (a.victory == b.victory && a.dlev < b.dlev) return true;
    if (a.victory == b.victory && a.dlev == b.dlev && a.plev > b.plev) return true;
    if (a.victory == b.victory && a.dlev == b.dlev && a.plev == b.plev && a.worth > b.worth) return true;
    return false;
}

bool sort_worth(const order_t& a, const order_t& b) {
    if (a.victory > b.victory) return true;
    if (a.victory == b.victory && a.worth > b.worth) return true;
    if (a.victory == b.victory && a.worth == b.worth && a.plev > b.plev) return true;
    if (a.victory == b.victory && a.worth == b.worth && a.plev == b.plev && a.dlev > b.dlev) return true;
    return false;
}


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

void _process(std::vector<order_t>& scores) {

    size_t n = 0;

    for (auto i = scores.begin(); i != scores.end() && n < 10; ++i, ++n) {

        if (i != scores.begin())
            std::cout << ",";

        bones::bone_t& bone = i->bone;

        if (bone.cause.name.empty())
            bone.cause.name = "unnatural causes";
        else
            bone.cause.name = quote(bone.cause.name);

        if (bone.name.name.empty())
            bone.name.name = "anonymous";
        else
            bone.name.name = quote(bone.name.name);

        std::cout << nlp::message("\n{\"dlev\": %d, \"plev\": %d, \"name\": \"%S\", \"cause\": \"%s\", \"worth\": %d, \"victory\": %s}",
                                  i->dlev+1, bone.level+1, bone.name, bone.cause, bone.worth, std::string(i->victory ? "true" : "false"));
    }
}

template <typename FUNC>
void process(std::vector<order_t>& scores, FUNC sorter) {

    std::sort(scores.begin(), scores.end(), sorter);
    _process(scores);
}

void process(std::vector<order_t>& scores) {

    std::reverse(scores.begin(), scores.end());
    _process(scores);
}



int main(int argc, char** argv) {

    try {

        std::vector<order_t> scores;

        try {
            serialize::Source source("bones.dat");

            while (1) {
                try {
                    bones::key_t key;
                    bones::pt xy;
                    bones::bone_t bone;

                    serialize::read(source, key);
                    serialize::read(source, xy);
                    serialize::read(source, bone);

                    scores.push_back(order_t(key.worldz, bone));

                } catch (...) {
                    break;
                }
            }

        } catch (...) {
        }


        std::cout << nlp::message("{\"num_games\": %d,\n", scores.size());
        std::cout << "\"highscores\": {";

        std::cout << "\"ts\": [";
        process(scores);
        std::cout << "]," << std::endl;

        std::cout << "\"plev\": [";
        process(scores, sort_plev);
        std::cout << "]," << std::endl;

        std::cout << "\"dlev_d\": [";
        process(scores, sort_dlev_d);
        std::cout << "]," << std::endl;

        std::cout << "\"dlev_a\": [";
        process(scores, sort_dlev_a);
        std::cout << "]," << std::endl;

        std::cout << "\"worth\": [";
        process(scores, sort_worth);
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

