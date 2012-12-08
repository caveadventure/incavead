#ifndef __COUNTERS_H
#define __COUNTERS_H

#include <string>
#include <map>

#include "random.h"

namespace counters {

struct Counts {

    std::map< unsigned int, std::map<std::string, unsigned int> > data;

    void init(const std::string& tag, unsigned int level, unsigned int maxc) {

        if (maxc > 0) {
            data[level][tag] = maxc;
        }
    }

    std::map<std::string, unsigned int> take(rnd::Generator& rng, unsigned int level, unsigned int n = 1) {

        std::map<std::string, unsigned int> ret;

        std::cout << "+++ " << level << " " << data.size() << std::endl;

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
                std::cout << "||| " << level << " : " << i.first << "," << i.second << std::endl;
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

    void replace(unsigned int level, const std::string& tag, unsigned int n = 1) {
        if (n > 0) {
            data[level][tag] += n;
        }
    }

    bool has(unsigned int level, const std::string& tag) {
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
