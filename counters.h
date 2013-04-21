#ifndef __COUNTERS_H
#define __COUNTERS_H

#include <string>
#include <map>

#include "random.h"

namespace counters {

struct Counts {

    std::map< unsigned int, std::map<tag_t, unsigned int> > data;

    /*
    void print() {
        std::cout << "====" << std::endl;
        for (const auto& i : data) {
            for (const auto& j : i.second) {
                std::cout << i.first << " '" << j.first << "' " << j.second << std::endl;
            }
        }
        std::cout << "-==-" << std::endl;
    }
    */

    void init(tag_t tag, unsigned int level, unsigned int maxc) {

        if (maxc > 0) {
            data[level][tag] = maxc;
        }
    }

    std::map<tag_t, unsigned int> take(rnd::Generator& rng, unsigned int level, unsigned int n = 1, bool exclusive = false) {

        std::map<tag_t, unsigned int> ret;

        while (level >= 0 && n > 0) {

            if (data.count(level) == 0) {

                if (level == 0 || exclusive) {
                    return ret;

                } else {
                    --level;
                    continue;
                }
            }


            std::vector<double> weights;

            for (const auto& i : data[level]) {
                weights.push_back(i.second);
            }

            std::discrete_distribution<unsigned int> d(weights.begin(), weights.end());
 
            unsigned int ntag = d(rng.gen);
           
            auto i = data[level].begin();

            while (ntag > 0) {
                ++i;
                --ntag;
            }

            tag_t tag = i->first;
            unsigned int takecount = take(level, tag, n);

            n -= takecount;
            ret[tag] += takecount;
        }

        return ret;
    }

    unsigned int take(unsigned int level, tag_t tag, unsigned int n = 1) {

        auto levi = data.find(level);

        if (levi == data.end()) {
            return 0;
        }

        auto tagi = levi->second.find(tag);

        if (tagi == levi->second.end()) {
            return 0;
        }

        unsigned int& totn = tagi->second;

        if (n < totn) {
            totn -= n;
            return n;

        } else {
            unsigned int ret = totn;

            levi->second.erase(tagi);

            if (levi->second.size() == 0) {
                data.erase(levi);
            }

            return ret;
        }
    }

    unsigned int take(tag_t tag, unsigned int n = 1) {

        unsigned int ret = 0;

        if (data.size() == 0) {
            return ret;
        }

        unsigned int maxlevel = data.rbegin()->first;

        for (unsigned int lev = 0; lev <= maxlevel; ++lev) {

            unsigned int takecount = take(lev, tag, n);

            n -= takecount;
            ret += takecount;

            if (n == 0) {
                break;
            }
        }

        return ret;
    }

    void replace(unsigned int level, tag_t tag, unsigned int n = 1) {
        if (n > 0) {
            data[level][tag] += n;
        }
    }

    bool has(unsigned int level, tag_t tag) {
        auto i = data.find(level);

        if (i == data.end()) return false;

        auto j = i->second.find(tag);

        if (j == i->second.end()) return false;

        if (j->second < 1) return false;

        return true;
    }

};

}

namespace serialize {

template <>
struct reader<counters::Counts> {
    void read(Source& s, counters::Counts& t) {
        serialize::read(s, t.data);
    }
};

template <>
struct writer<counters::Counts> {
    void write(Sink& s, const counters::Counts& t) {
        serialize::write(s, t.data);
    }
};

}


#endif
