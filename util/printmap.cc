
#include <iostream>
#include <set>
#include <algorithm>

#include "serialize.h"
#include "common.h"
#include "bones.h"
#include "nlp.h"
#include "grid.h"

struct order_t {
    int dlev;
    unsigned int plev;
    double worth;
    bones::bone_t bone;

    order_t() : dlev(0), plev(0), worth(0) {}
    order_t(int l, const bones::bone_t& b) : dlev(l), plev(b.level), worth(b.worth), bone(b) {}

    bool operator<(const order_t& a) const {
        if (plev > a.plev) return true;
        if (plev == a.plev && dlev > a.dlev) return true;
        if (plev == a.plev && dlev == a.dlev && worth > a.worth) return true;
        return false;
    }
};

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

int main(int argc, char** argv) {

    try {

        rnd::Generator rng;
        uint64_t seed1 = 0xFFFF000000000000;
        uint64_t seed2 = 0x0000000000100000;
        rng.init(seed1);
        std::cout << rng.gauss(0.0, 1.0) << std::endl;
        rng.init(seed2);
        std::cout << rng.gauss(0.0, 1.0) << std::endl;

        grid::Map grid;
        serialize::Source source(argv[1]);
        serialize::read(source, grid);

        for (unsigned int y = 0; y < grid.h; ++y) {
            std::string z;
            for (unsigned int x = 0; x < grid.w; ++x) {
                z += (grid.is_walk(x, y) ? '.' : '#');
            }
            std::cout << z << std::endl;
        }

    } catch (std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;

    } catch (...) {
        std::cerr << "Unknown fatal error." << std::endl;
        return 1;
    }

    return 0;
}

