
#include <iostream>
#include <stdexcept>

#include "../serialize.h"
#include "../common_types.h"
#include "../common.h"
#include "../bones.h"
#include "../nlp.h"


void fix(bones::bone_t& bone) {

    size_t x = bone.cause.name.find("%#");

    if (x != std::string::npos) {
        bone.cause.name.replace(x, 2, "%(#)");
    }
}



int main(int argc, char** argv) {

    try {

        try {
            serialize::Source source("bones.dat");
            serialize::Sink sink("bones.dat.new");

            while (1) {
                try {
                    bones::key_t key;
                    bones::pt xy;
                    bones::bone_t bone;

                    serialize::read(source, key);
                    serialize::read(source, xy);
                    serialize::read(source, bone);

                    fix(bone);

                    serialize::write(sink, key);
                    serialize::write(sink, xy);
                    serialize::write(sink, bone);

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

