#ifndef __CELAUTO_H
#define __CELAUTO_H

#include <set>
#include <map>
#include <string>
#include <memory>

#include "serialize.h"

struct CelAuto {
    tag_t tag;

    std::set<unsigned int> survive;
    std::set<unsigned int> born;
    unsigned int age;

    tag_t terrain;

    bool is_walk;
    bool make_walk;
    double karma_scale;
    double karma_step;

    std::vector< std::pair<int,int> > seed;

    CelAuto() : age(0), is_walk(false), make_walk(false), karma_scale(1.0), karma_step(1.0) {}

};

struct CelAutoBank {

    std::map<tag_t,CelAuto> bank;

    template <typename... ARGS>
    void init(tag_t tag, ARGS... args) {

        if (bank.count(tag) != 0) {
            throw std::runtime_error("Duplicate celauto tag");
        }

        bank[tag] = CelAuto(tag, std::forward<ARGS>(args)...);
    }

    void copy(const CelAuto& ca) {

        if (bank.count(ca.tag) != 0) {
            throw std::runtime_error("Duplicate celauto tag");
        }

        bank[ca.tag] = ca;
    }

    const CelAuto& get(tag_t tag) const {
        auto i = bank.find(tag);

        if (i == bank.end()) {
            throw std::runtime_error("Invalid celauto tag");
        }

        return i->second;
    }
};


CelAutoBank& __celautos__() {
    static CelAutoBank ret;
    return ret;
}

const CelAutoBank& celautos() {
    return __celautos__();
}

template <typename... ARGS>
void init_celauto(ARGS... args) {
    __celautos__().init(std::forward<ARGS>(args)...);
}

void init_celauto_copy(const CelAuto& ca) {
    __celautos__().copy(ca);
}


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
                std::cout << "[] " << xy_.first << " " << xy_.second << std::endl;
                throw std::runtime_error("Sanity error in camap::clear");
            }
            
            count_of_n[xy_][rul.tag]--;
        }

        funcoff(xy.first, xy.second, rul);
        camap.erase(i);
    } 


    template <typename FUNC1, typename FUNC2, typename FUNC3>
    inline void step(neighbors::Neighbors& neigh_plain, FUNC1 neigh, FUNC2 funcon, FUNC3 funcoff) {

        std::cout << "[[ " << camap.size() << std::endl;
        bm _zz("celauto::step()");

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
        std::map<pt, tag_t> edges_for_new;

        {
            bm _z1("iter1");

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

                for (const auto& xy_ : neigh(xy.first, xy.second, rul)) {
                    if (camap.count(xy_) == 0) {
                        edges_for_new[xy_] = rul.tag;
                    }
                }
            }
        }
        }

        {
            bm _z2("iter2");
        
        // Check for newborn cells.
        for (const auto& i : edges_for_new) {

            const pt& xy = i.first;
            const CelAuto& rul = celautos().get(i.second);

            unsigned int n = count_of_n[xy][rul.tag];

            //std::cout << "++ " << xy.first << "," << xy.second << " " << n << std::endl;

            if (rul.born.count(n) != 0) {

                camap[xy] = ca_element(rul.tag, 0);

                for (const auto& xy_ : neigh_plain(xy)) {
                    count_of_n[xy_][rul.tag]++;
                }

                funcon(xy.first, xy.second, rul);
            }
        }

        }

        {
            bm _z4("iter4");

        // Leave remains of dead cells.
        for (const auto& i : for_remove) {

            const pt& xy = i.first;
            const CelAuto& rul = celautos().get(i.second);

            camap.erase(xy);
        
            funcoff(xy.first, xy.second, rul);
        }

        }

        {
            bm _z5("iter5");

	for (camap_t::iterator i = camap.begin(); i != camap.end(); ++i) {

            const pt& xy = i->first;
            ca_element& cae = i->second;

            if (cae.age == 0 && cae.age_add > 0) {

                for (const auto& xy_ : neigh_plain(xy)) {

                    size_t qq = count_of_n[xy_][cae.tag];
                    if (qq == 0) {
                        //std::cout << "[] " << xy_.first << " " << xy_.second << std::endl;
                        throw std::runtime_error("Sanity error in camap");
                    }

                    count_of_n[xy_][cae.tag]--;
                }
            }

            cae.age += cae.age_add;
        }
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
