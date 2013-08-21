
#include <iostream>
#include <set>
#include <algorithm>
#include <stdexcept>

#include "../serialize.h"
#include "../common.h"

#define __ITEMS_H

namespace items {

typedef std::pair<unsigned int, unsigned int> pt;

struct Item {
    tag_t tag;
    pt xy;
    unsigned int count;

    Item() : xy(0, 0), count(1) {}
};

}

namespace serialize {

template <>
struct reader<items::Item> {
    void read(Source& s, items::Item& m) {
        serialize::read(s, m.tag);
        serialize::read(s, m.xy);
        serialize::read(s, m.count);
    }
};

template <>
struct writer<items::Item> {
    void write(Sink& s, const items::Item& m) {
        serialize::write(s, m.tag);
        serialize::write(s, m.xy);
        serialize::write(s, m.count);
    }
};

}


#include "../uniques.h"
#include "../nlp.h"


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

        uniques::uniques().load();

        auto& u = uniques::uniques();

        std::cout << nlp::message("{\"series\": %d, \"ts\": %d, \"locations\": [", u.series, u.placetime);

        bool first = true;

        for (const auto& i : u.data) {
            for (const auto& j : i.second) {
                if (first) {
                    first = false;
                    std::cout << "\n";
                } else {
                    std::cout << ",\n";
                }

                std::cout << nlp::message("{\"dlev\": %d, \"dlev_offset\":[%d,%d], \"pt\": [%d,%d], \"count\": %d}",
                                          i.first.worldz, i.first.worldx, i.first.worldy, 
                                          j.xy.first, j.xy.second, j.count);
            }
        }

        std::cout << "]}" << std::endl;

    } catch (std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;

    } catch (...) {
        std::cerr << "Unknown fatal error." << std::endl;
        return 1;
    }

    return 0;
}

