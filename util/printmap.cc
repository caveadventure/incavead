
#include <iostream>
#include <stdexcept>

#include "../strings_bank.h"
#include "../serialize.h"
#include "../common_types.h"
#include "../common.h"
#include "../random.h"
#include "../grid.h"

struct Feature {
    tag_t tag;
    grid::pt xy;
    unsigned int decay;
    unsigned int charges;
};

namespace serialize {

template <>
struct reader<Feature> {
    void read(Source& s, Feature& m) {
        serialize::read(s, m.tag);
        serialize::read(s, m.xy);
        serialize::read(s, m.decay);
        serialize::read(s, m.charges);
    }
};

};

int main(int argc, char** argv) {

    try {

        grid::Map grid;
        std::unordered_map<grid::pt,Feature>  feats;
        
        serialize::Source source(argv[1]);
        serialize::read(source, grid);
        serialize::read(source, feats);

        for (unsigned int y = 0; y < grid.h; ++y) {
            std::string z;
            for (unsigned int x = 0; x < grid.w; ++x) {

                if (feats.count(grid::pt(x, y)) != 0) {
                    z += '*';

                } else if (grid.is_lowlands(x, y)) {

                    if (grid.is_water(x, y)) {
                        z += 'O';
                    } else {
                        z += 'o';
                    }

                } else if (grid.is_walk(x, y)) {

                    if (grid.is_water(x, y)) {
                        z += '+';
                    } else {
                        z += '.';
                    }

                } else {
                    z += '#';
                }
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

