
#include <iostream>
#include <stdexcept>

#include "../serialize.h"
#include "../common_types.h"
#include "../common.h"
#include "../bones.h"
#include "../nlp.h"



int main(int argc, char** argv) {

    try {

        std::unordered_map<bones::key_t,double> money;

        try {
            serialize::Source source("bones.dat");

            while (1) {
                try {
                    bones::key_t key;
                    bones::pt xy;
                    bones::bone_t bone;
                    bones::session_t sess;

                    serialize::read(source, key);
                    serialize::read(source, xy);
                    serialize::read(source, bone);
                    serialize::read(source, sess);

                    if (bone.cause.name == "VICTORY")
                        continue;

                    money[key] += bone.worth;

                } catch (...) {
                    std::cout << "oops" << std::endl;
                    break;
                }
            }

            std::unordered_map<bones::key_t,double> money2;

            for (const auto& i : money) {
                std::cout << i.first.worldx << "," << i.first.worldy << ":" << i.first.worldz << " = " << i.second << std::endl;
                money2[bones::key_t(i.first.worldx, i.first.worldy, 0)] += i.second;
            }

            std::cout << "----" << std::endl;

            for (const auto& i : money2) {
                std::cout << i.first.worldx << "," << i.first.worldy << " = " << i.second << std::endl;
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

