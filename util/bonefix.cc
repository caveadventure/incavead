
#include <iostream>
#include <stdexcept>

#include "../serialize.h"
#include "../common_types.h"
#include "../common.h"
#include "../bones.h"
#include "../nlp.h"



int main(int argc, char** argv) {

    try {

        try {
            serialize::Source source("bones.dat");
            serialize::Sink sink("bones.dat.new");

            unsigned int q = 0;

            while (1) {
                try {
                    bones::key_t key;
                    bones::pt xy;
                    bones::bone_t bone;
                    bones::session_t sess;

                    serialize::read(source, key);
                    serialize::read(source, xy);
                    serialize::read(source, bone);

                    sess.address = ++q;

                    serialize::write(sink, key);
                    serialize::write(sink, xy);
                    serialize::write(sink, bone);
                    serialize::write(sink, sess);

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

