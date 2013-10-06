
#include <iostream>
#include <stdexcept>

#include "../serialize.h"
#include "../common_types.h"
#include "../common.h"
#include "../random.h"
#include "../grid.h"


int main(int argc, char** argv) {

    try {

        grid::Map grid;
        serialize::Source source(argv[1]);
        serialize::read(source, grid);

        for (unsigned int y = 0; y < grid.h; ++y) {
            std::string z;
            for (unsigned int x = 0; x < grid.w; ++x) {

                if (grid.is_lowlands(x, y)) {

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

