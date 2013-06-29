
#include <iostream>
#include <set>
#include <algorithm>

#include "../serialize.h"
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

    bool operator<(const order_t& a) const {
        if (victory > a.victory) return true;
        if (victory == a.victory && plev > a.plev) return true;
        if (victory == a.victory && plev == a.plev && dlev > a.dlev) return true;
        if (victory == a.victory && plev == a.plev && dlev == a.dlev && worth > a.worth) return true;
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

        std::sort(scores.begin(), scores.end());

        if (scores.size() > 10) {
            scores.resize(10);
        }

        std::cout << "[";

        for (auto i = scores.begin(); i != scores.end(); ++i) {

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

        std::cout << std::endl << "]" << std::endl;

    } catch (std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;

    } catch (...) {
        std::cerr << "Unknown fatal error." << std::endl;
        return 1;
    }

    return 0;
}

