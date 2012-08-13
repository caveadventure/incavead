#ifndef __CELAUTO_H
#define __CELAUTO_H

#include <set>
#include <map>
#include <string>
#include <memory>

#include "neighbors.h"

#include "serialize.h"



namespace celauto {

typedef std::pair<unsigned int, unsigned int> pt;

struct rule {
    size_t id;
    std::set<unsigned int> survive;
    std::set<unsigned int> born;
    unsigned int age;

    rule(size_t i, const std::string& s, const std::string& b, unsigned int a) : id(i) {

        for (char c : s) {
            survive.insert(c - '0');
        }

        for (char c : b) {
            born.insert(c - '0');
        }

        age = a;
    }
};

struct ca_element {
    std::shared_ptr<rule> rul;
    unsigned int age;
    unsigned int age_add;

    ca_element() : age(0), age_add(0) {}
    ca_element(std::shared_ptr<rule> r, unsigned int a) : rul(r), age(a), age_add(0) {}
};


struct CaMap {

    typedef std::map<pt, ca_element> camap_t;
    camap_t camap;


    std::map<size_t, std::shared_ptr<rule> > rules;

    std::shared_ptr<rule> get_rule(size_t i) {
        return rules[i];
    }

    void make_rule(size_t i, const std::string& s, const std::string& b, unsigned int a) {
        rules[i] = std::shared_ptr<rule>(new rule(i, s, b, a));
    }


    void init() {
        camap.clear();
    }

    void clear() {
        init();
    }

    void get_state(const pt& xy, size_t& id, unsigned int& age) {
        camap_t::iterator i = camap.find(xy);

        if (i != camap.end()) {
            id = i->second.rul->id;
            age = i->second.age;

        } else {
            id = 0;
            age = 0;
        }
    }

    void seed(const pt& xy, std::shared_ptr<rule> r) {
        camap[xy] = ca_element(r, 0);
    }
    
    template <typename FUNC>
    void clear(const pt& xy, FUNC funcoff) {
        camap_t::iterator i = camap.find(xy);

        if (i != camap.end()) {
            funcoff(xy.first, xy.second, i->second.rul->id);
            camap.erase(i);
        }
    } 

    unsigned int find_n(neighbors::Neighbors& neigh,
                        const pt& xy, 
                        const std::shared_ptr<rule>& rul, camap_t* que = NULL) {

        unsigned int n = 0;

        for (const auto& xy_ : neigh(xy)) {

            camap_t::const_iterator i = camap.find(xy_);

            if (i != camap.end()) {
                if (i->second.rul->id == rul->id && i->second.age == 0) {
                    n++;
                }

            } else if (que != NULL) {
                (*que)[xy_] = ca_element(rul, 0);
            }
        }

        return n;
    }


    template <typename FUNC>
    inline void step(neighbors::Neighbors& neigh, FUNC funcon, FUNC funcoff) {
    
        camap_t remove;
        camap_t insert;

        for (camap_t::iterator i = camap.begin(); i != camap.end(); ++i) {

            const pt& xy = i->first;
            std::shared_ptr<rule>& rul = i->second.rul;
            const unsigned int& age = i->second.age;
	    unsigned int& age_add = i->second.age_add;

	    age_add = 0;

            // Check if we are dead.
            if (age > 0) {

                if (age < rul->age - 1) {
                    age_add = 1;

                } else {
                    remove[xy] = i->second;
                }

            } else {
                // Check if we survive

                unsigned int n = find_n(neigh, xy, rul, &insert);

                if (rul->survive.count(n) == 0) {
                    age_add = 1;
                }
            }
        }

        camap_t born;
        
        // Check for newborn cells.
        for (camap_t::iterator i = insert.begin(); i != insert.end(); ++i) {

            const pt& xy = i->first;
            std::shared_ptr<rule>& rul = i->second.rul;

            unsigned int n = find_n(neigh, xy, rul);

            if (rul->born.count(n) != 0) {
                born[xy] = ca_element(rul, 0);
            }
        }

        for (camap_t::iterator i = born.begin(); i != born.end(); ++i) {        

            const pt& xy = i->first;
            std::shared_ptr<rule>& rul = i->second.rul;

            camap[xy] = i->second;

            funcon(xy.first, xy.second, rul->id);
        }

        // Leave remains of dead cells.
        for (camap_t::iterator i = remove.begin(); i != remove.end(); ++i) {

            const pt& xy = i->first;
            std::shared_ptr<rule>& rul = i->second.rul;

            camap.erase(xy);
        
            funcoff(xy.first, xy.second, rul->id);
        }

	for (camap_t::iterator i = camap.begin(); i != camap.end(); ++i) {
	  i->second.age += i->second.age_add;
	}

    }


    inline void write(serialize::Sink& s) {
        serialize::write(s, camap.size());
        for (const auto& t : camap) {
            serialize::write(s, t.first);
            serialize::write(s, t.second.rul->id);
            serialize::write(s, t.second.age);
            serialize::write(s, t.second.age_add);
        }
    }

    inline void read(serialize::Source& s) {
        size_t sz;
        serialize::read(s, sz);

        for (size_t i = 0; i < sz; ++i) {
            pt key;
            ca_element ca;
            size_t id;

            serialize::read(s, key);
            serialize::read(s, id);
            serialize::read(s, ca.age);
            serialize::read(s, ca.age_add);

            ca.rul = get_rule(id);

            camap[key] = ca;
        }
    }
};


}



#endif
