#ifndef __COUNTERS_H
#define __COUNTERS_H

#include <string>
#include <map>

#include "random.h"

namespace counters {

struct Counts {

    std::map< unsigned int, std::map<std::string, unsigned int> > data;

    void init(const std::string& tag, unsigned int level, unsigned int maxc) {
        data[level][tag] = maxc;
    }

    std::map<std::string, unsigned int> take(rnd::Generator& rng, unsigned int level, unsigned int n = 1) {

        std::map<std::string, unsigned int> ret;

        while (level >= 0 && n > 0) {

            if (data.count(level) == 0) {

                if (level == 0) {
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

            unsigned int takecount = take(level, i->first, n);

            n -= takecount;
            ret[i->first] += takecount;
        }

        return ret;
    }

    unsigned int take(unsigned int level, const std::string& tag, unsigned int n = 1) {

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

    unsigned int take(const std::string& tag, unsigned int n = 1) {

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


    inline void write(serialize::Sink& s) {
        serialize::write(s, data);
    }

    inline void read(serialize::Source& s) {
        serialize::read(s, data);
    }

};

}

#endif
