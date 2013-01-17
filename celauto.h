#ifndef __CELAUTO_H
#define __CELAUTO_H

#include <set>
#include <map>
#include <string>
#include <memory>

#include "serialize.h"

struct CelAuto {
    std::string tag;

    std::set<unsigned int> survive;
    std::set<unsigned int> born;
    unsigned int age;

    std::string terrain;

    CelAuto() : age(0) {}

    CelAuto(const std::string& t, const std::string& s, const std::string& b, unsigned int a,
            const std::string& _terrain) : tag(t), terrain(_terrain) {

        for (char c : s) {
            survive.insert(c - '0');
        }

        for (char c : b) {
            born.insert(c - '0');
        }

        age = a;
    }
};

struct CelAutoBank {

    std::map<std::string,CelAuto> bank;

    template <typename... ARGS>
    void init(const std::string& tag, ARGS... args) {

        if (bank.count(tag) != 0) {
            throw std::runtime_error("Duplicate celauto tag: " + tag);
        }

        bank[tag] = CelAuto(tag, std::forward<ARGS>(args)...);
    }

    void copy(const CelAuto& ca) {

        if (bank.count(ca.tag) != 0) {
            throw std::runtime_error("Duplicate celauto tag: " + ca.tag);
        }

        bank[ca.tag] = ca;
    }

    const CelAuto& get(const std::string& tag) const {
        auto i = bank.find(tag);

        if (i == bank.end()) {
            throw std::runtime_error("Invalid celauto tag: " + tag);
        }

        return i->second;
    }
};


CelAutoBank& __celautos__() {
    static CelAutoBank ret;
    return ret;
}

const CelAutoBank celautos() {
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
    std::string tag;
    unsigned int age;
    unsigned int age_add;

    ca_element() : age(0), age_add(0) {}
    ca_element(const std::string& t, unsigned int a) : tag(t), age(a), age_add(0) {}
};


struct CaMap {

    typedef std::map<pt, ca_element> camap_t;
    camap_t camap;

    void init() {
        camap.clear();
    }

    void clear() {
        init();
    }

    /*
    bool get_state(const pt& xy, std::string& tag, unsigned int& age) {
        camap_t::iterator i = camap.find(xy);

        if (i != camap.end()) {
            tag = i->second.rul;
            age = i->second.age;
            return true;

        } else {
            return false;
        }
    }
    */

    void seed(unsigned int x, unsigned int y, const std::string& r) {
        camap[pt(x,y)] = ca_element(r, 0);
    }
    
    template <typename FUNC>
    void clear(const pt& xy, FUNC funcoff) {
        camap_t::iterator i = camap.find(xy);

        if (i != camap.end()) {
            funcoff(xy.first, xy.second, celautos().get(i->second.tag));
            camap.erase(i);
        }
    } 

    template <typename FUNC>
    unsigned int find_n(FUNC& neigh,
                        const pt& xy, 
                        const CelAuto& rul, camap_t* que = NULL) {

        unsigned int n = 0;

        for (const auto& xy_ : neigh(xy.first, xy.second, rul)) {

            camap_t::const_iterator i = camap.find(xy_);

            if (i != camap.end()) {
                if (i->second.tag == rul.tag && i->second.age == 0) {
                    n++;
                }

            } else if (que != NULL) {
                (*que)[xy_] = ca_element(rul.tag, 0);
            }
        }

        return n;
    }


    template <typename FUNC1, typename FUNC2, typename FUNC3>
    inline void step(FUNC1 neigh, FUNC2 funcon, FUNC3 funcoff) {
    
        camap_t remove;
        camap_t insert;

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
                    remove[xy] = i->second;
                }

            } else {
                // Check if we survive

                unsigned int n = find_n(neigh, xy, rul, &insert);

                if (rul.survive.count(n) == 0) {
                    age_add = 1;
                }
            }
        }

        camap_t born;
        
        // Check for newborn cells.
        for (camap_t::iterator i = insert.begin(); i != insert.end(); ++i) {

            const pt& xy = i->first;
            const CelAuto& rul = celautos().get(i->second.tag);

            unsigned int n = find_n(neigh, xy, rul);

            if (rul.born.count(n) != 0) {
                born[xy] = ca_element(rul.tag, 0);
            }
        }

        for (camap_t::iterator i = born.begin(); i != born.end(); ++i) {        

            const pt& xy = i->first;
            const CelAuto& rul = celautos().get(i->second.tag);

            camap[xy] = i->second;

            funcon(xy.first, xy.second, rul);
        }

        // Leave remains of dead cells.
        for (camap_t::iterator i = remove.begin(); i != remove.end(); ++i) {

            const pt& xy = i->first;
            const CelAuto& rul = celautos().get(i->second.tag);

            camap.erase(xy);
        
            funcoff(xy.first, xy.second, rul);
        }

	for (camap_t::iterator i = camap.begin(); i != camap.end(); ++i) {
	  i->second.age += i->second.age_add;
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
