#ifndef __COMMON_H
#define __COMMON_H

#include <functional>
#include <string>
#include <unordered_map>

struct tag_mem_t {
    std::unordered_map<unsigned int, std::string> memory;

    unsigned int convert(const std::string& v) {

        if (v.empty())
            return 0;

        unsigned int vh = std::hash<std::string>()(v); 

        if (vh == 0) {
            throw std::runtime_error("Hash failed for string value: " + v);
        }

        auto tmp = memory.find(vh);
        if (tmp != memory.end() && tmp->second != v) {
            throw std::runtime_error("Double hash for string value: " + v);
        }

        memory[vh] = v;
        return vh;
    }
};

struct tag_t {
    unsigned int v;

    tag_t() : v(0) {}

    tag_t(unsigned int _v) : v(_v) {
        if (v == 0) {
            throw std::runtime_error("Cannot initialize tag to zero");
        }
    }

    template <typename T>
    tag_t(const T& _v, tag_mem_t& tm) : v(tm.convert(_v)) {}

    bool operator==(const tag_t& other) const {
        return v == other.v;
    }

    bool operator!=(const tag_t& other) const {
        return v != other.v;
    }

    bool operator<(const tag_t& other) const {
        return v < other.v;
    }

    bool null() const {
        return (v == 0);
    }
};


namespace serialize {

template <>
struct reader<tag_t> {
    void read(Source& s, tag_t& t) {
        serialize::read(s, t.v);
    }
};

template <>
struct writer<tag_t> {
    void write(Sink& s, tag_t t) {
        serialize::write(s, t.v);
    }
};

}


#endif
