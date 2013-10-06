#ifndef __CELAUTO_H
#define __CELAUTO_H

#include <map>
#include <string>
#include <memory>

#include "serialize.h"



/*
 *
 */

namespace celauto {

typedef std::pair<unsigned int, unsigned int> pt;

struct ca_element {
    tag_t tag;
    unsigned int age;
    unsigned int age_add;

    ca_element() : age(0), age_add(0) {}
    ca_element(tag_t t, unsigned int a) : tag(t), age(a), age_add(0) {}
};


struct CaMap {

    typedef std::map<pt, ca_element> camap_t;
    camap_t camap;

    std::unordered_map< pt, std::map<tag_t, size_t> > count_of_n;

    bool need_init_count;

    CaMap() : need_init_count(true) {}

    void init() {
        camap.clear();
        count_of_n.clear();
    }

    void clear() {
        init();
    }

    void seed(neighbors::Neighbors& neigh, const pt& xy, tag_t tag) {

        camap_t::iterator i = camap.find(xy);

        if (i != camap.end())
            return;

        camap[xy] = ca_element(tag, 0);

        const CelAuto& rul = celautos().get(tag);

        for (const auto& xy_ : neigh(xy)) {
            count_of_n[xy_][rul.tag]++;
        }
    }
    
    template <typename FUNC>
    void clear(neighbors::Neighbors& neigh, const pt& xy, FUNC funcoff) {

        camap_t::iterator i = camap.find(xy);

        if (i == camap.end())
            return;

        const CelAuto& rul = celautos().get(i->second.tag);

        for (const auto& xy_ : neigh(xy)) {

            size_t qq = count_of_n[xy_][rul.tag];
            if (qq == 0) {
                throw std::runtime_error("Sanity error in camap::clear");
            }
            
            count_of_n[xy_][rul.tag]--;
        }

        funcoff(xy.first, xy.second, rul);
        camap.erase(i);
    } 


    template <typename FUNC1, typename FUNC2, typename FUNC3>
    inline void step(neighbors::Neighbors& neigh_plain, FUNC1 cell_good, FUNC2 funcon, FUNC3 funcoff) {

        /// ///

        if (need_init_count) {

            for (const auto& i : camap) {
                const pt& xy = i.first;
                tag_t tag = i.second.tag;

                for (const auto& xy_ : neigh_plain(xy)) {
                    count_of_n[xy_][tag]++;
                }
            }

            need_init_count = false;
        }

        /// ///
    
        std::map<pt, tag_t> for_remove;
        std::map<pt, tag_t> for_add;
        std::set<pt> no_more_count_of_n;

        for (camap_t::iterator i = camap.begin(); i != camap.end(); ++i) {

            const pt& xy = i->first;
            const CelAuto& rul = celautos().get(i->second.tag);
            const unsigned int& age = i->second.age;
	    unsigned int& age_add = i->second.age_add;

	    age_add = 0;

            // Check if we are dead.
            if (age > 0) {

                if (age < rul.age - 1) {
                    age_add = 1;

                } else {
                    for_remove[xy] = rul.tag;
                }

            } else {
                // Check if we survive

                unsigned int n = count_of_n[xy][rul.tag];

                if (rul.survive.count(n) == 0) {
                    age_add = 1;
                }
            }
        }

        for (const auto& i : count_of_n) {

            const pt& xy = i.first;

            if (camap.count(xy) != 0)
                continue;

            bool need_delete = true;

            for (const auto& j : i.second) {

                size_t n = j.second;

                if (n == 0)
                    continue;

                need_delete = false;

                const CelAuto& rul = celautos().get(j.first);

                if (rul.born.count(n) != 0 &&
                    cell_good(xy.first, xy.second, rul)) {

                    for_add[xy] = rul.tag;
                    break;
                }
            }

            if (need_delete) {
                no_more_count_of_n.insert(xy);
            }
        }

        for (const auto& i : no_more_count_of_n) {
            count_of_n.erase(i);
        }

        for (const auto& i : for_add) {

            const pt& xy = i.first;
            const CelAuto& rul = celautos().get(i.second);

            camap[xy] = ca_element(rul.tag, 0);

            for (const auto& xy_ : neigh_plain(xy)) {
                count_of_n[xy_][rul.tag]++;
            }

            funcon(xy.first, xy.second, rul);
        }

        // Leave remains of dead cells.
        for (const auto& i : for_remove) {

            const pt& xy = i.first;
            const CelAuto& rul = celautos().get(i.second);

            camap.erase(xy);
        
            funcoff(xy.first, xy.second, rul);
        }

	for (camap_t::iterator i = camap.begin(); i != camap.end(); ++i) {

            const pt& xy = i->first;
            ca_element& cae = i->second;

            if (cae.age == 0 && cae.age_add > 0) {

                for (const auto& xy_ : neigh_plain(xy)) {

                    size_t qq = count_of_n[xy_][cae.tag];
                    if (qq == 0) {
                        throw std::runtime_error("Sanity error in camap");
                    }

                    count_of_n[xy_][cae.tag]--;
                }
            }

            cae.age += cae.age_add;
        }
    }

};

}

namespace serialize {

template <>
struct reader<celauto::CaMap> {
    void read(Source& s, celauto::CaMap& t) {

        size_t sz;
        serialize::read(s, sz);

        for (size_t i = 0; i < sz; ++i) {
            celauto::pt key;
            celauto::ca_element ca;

            serialize::read(s, key);
            serialize::read(s, ca.tag);
            serialize::read(s, ca.age);
            serialize::read(s, ca.age_add);

            t.camap[key] = ca;
        }

        t.need_init_count = true;
    }
};

template <>
struct writer<celauto::CaMap> {
    void write(Sink& s, const celauto::CaMap& m) {

        serialize::write(s, m.camap.size());
        for (const auto& t : m.camap) {
            serialize::write(s, t.first);
            serialize::write(s, t.second.tag);
            serialize::write(s, t.second.age);
            serialize::write(s, t.second.age_add);
        }
    }
};

}


#endif
