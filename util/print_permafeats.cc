
#include <iostream>
#include <stdexcept>

#include "../serialize.h"
#include "../common_types.h"
#include "../permafeats.h"



int main(int argc, char** argv) {

    try {

        try {
            serialize::Source source("permafeats.dat");

            while (1) {
                try {
                    permafeats::key_t key;
                    permafeats::pt xy;
                    tag_t tag;

                    serialize::read(source, key);
                    serialize::read(source, xy);
                    serialize::read(source, tag);

                    bool walk = true;
                    bool water = false;

                    if (tag.null()) {
                        serialize::read(source, walk);
                        serialize::read(source, water);
                    }

                    std::cout << key.worldz << ":" << key.worldx << ":" << key.worldy 
                              << " " << xy.first << "," << xy.second
                              << " " << tag.v << " " << walk << " " << water << std::endl;

                } catch (std::exception& e) {
                    std::cout << "OOPS: " << e.what() << std::endl;
                    break;

                } catch (...) {
                    break;
                }
            }

        } catch (...) {
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

