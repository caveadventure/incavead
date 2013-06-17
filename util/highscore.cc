
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

        bones::bones().load();

        std::vector<order_t> scores;

        for (const auto& i : bones::bones().data) {
            for (const auto& j : i.second) {

                scores.push_back(order_t(i.first.worldz, j.second));
            }
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

            std::cout << nlp::message("\n{\"dlev\": %d, \"plev\": %d, \"name\": \"%S\", \"cause\": \"%s\", \"worth\": %d}",
                                      i->dlev+1, bone.level+1, bone.name, bone.cause, bone.worth);
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

