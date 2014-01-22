#ifndef __COUNTERS_H
#define __COUNTERS_H

#include <string>
#include <map>

#include "random.h"

namespace counters {

struct Counts {

    std::map< unsigned int, std::map<tag_t, unsigned int> > data;

    void init(tag_t tag, unsigned int level, unsigned int maxc) {

        if (maxc > 0) {
            data[level][tag] = maxc;
        }
    }

    template <typename FUNC>
    std::map<tag_t, unsigned int> take(rnd::Generator& rng, unsigned int level, unsigned int n, bool exclusive, FUNC filter) {

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

                if (filter(i.first)) {
                    weights.push_back(i.second);
                }
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


    std::map<tag_t, unsigned int> take(rnd::Generator& rng, unsigned int level, 
                                       unsigned int n = 1, bool exclusive = false) {

        return take(rng, level, n, exclusive, [](tag_t) { return true; });
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

    template <typename FUNC>
    void wipe(FUNC f) {

        for (auto i = data.begin(); i != data.end(); ) {

            for (auto j = i->second.begin(); j != i->second.end(); ) {

                if (f(j->first)) {
                    j = i->second.erase(j);
                } else {
                    ++j;
                }
            }

            if (i->second.empty()) {
                i = data.erase(i);
            } else {
                ++i;
            }
        }
    }

};

}


#endif
