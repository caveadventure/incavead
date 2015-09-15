#ifndef __STRINGS_BANK_H
#define __STRINGS_BANK_H

#include <cstdint>
#include <stdexcept>
#include <unordered_map>

constexpr uint64_t fnv64a_hash(const char* s, size_t len) {
    return (*s == '\0' ?
            0xcbf29ce484222325ULL :
            (fnv64a_hash(s + 1, len - 1) ^ (uint64_t)(*s)) * 0x100000001b3ULL);
}


constexpr uint64_t operator"" _hash(const char* s, size_t len) {
    return fnv64a_hash(s, len);
}

struct StringsBank {

    std::unordered_map<uint64_t,std::string> bank;

    const std::string& get(uint64_t hash, const std::string& str) const {

        auto i = bank.find(hash);

        if (i == bank.end())
            return str;

        return i->second;
    }

    void set(uint64_t hash, const std::string& str) {

        auto i = bank.find(hash);

        if (i != bank.end())
            throw std::runtime_error("Duplicate strings bank hash for: '" + str + "'");

        bank[hash] = str;
    }
};

inline StringsBank& __strings__() {
    static StringsBank ret;
    return ret;
}

inline const StringsBank& strings() {
    return __strings__();
}

inline void init_strings_copy(uint64_t hash, const std::string& to) {
    __strings__().set(hash, to);
}

struct hash_and_string {
    uint64_t hash;
    const char* str;

    constexpr hash_and_string(uint64_t h, const char* s) : hash(h), str(s) {}

    operator std::string() const {
        return strings().get(hash, str);
    }
};

constexpr hash_and_string operator"" _m(const char* s, size_t len) {
    return hash_and_string(fnv64a_hash(s, len), s);
}

#endif
