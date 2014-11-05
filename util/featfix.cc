
#include <iostream>
#include <stdexcept>

#include "../serialize.h"
#include "../common_types.h"
#include "../common.h"
#include "../permafeats.h"


int main(int argc, char** argv) {

    try {
        serialize::Source source(argv[1]);
        serialize::Sink sink(argv[2]);
        
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

                serialize::write(sink, key);
                serialize::write(sink, xy);
                serialize::write(sink, tag);

                if (tag.null()) {
                    serialize::write(sink, walk);
                    serialize::write(sink, water);
                }

                std::string message;
                serialize::write(sink, message);

            } catch (...) {
                break;
            }
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

