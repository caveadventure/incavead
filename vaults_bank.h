#ifndef __VAULTS_BANK
#define __VAULTS_BANK

#include <string>
#include <unordered_map>

struct VaultsBank {

    std::unordered_map<tag_t,Vault> bank;
    counters::Counts counts;
    counters::Counts random_counts;

    void copy(const Vault& s) {

        if (bank.count(s.tag) != 0) {
            throw std::runtime_error("Duplicate vaults tag");
        }

        bank[s.tag] = s;

        if (s.randomized) {

            random_counts.init(s.tag, s.level, s.count);

        } else {
            counts.init(s.tag, s.level, s.count);
        }
    }

    const Vault& get(tag_t tag) const {
        auto i = bank.find(tag);

        if (i == bank.end()) {
            throw std::runtime_error("Invalid vaults tag");
        }

        return i->second;
    }
};

inline VaultsBank& __vaults__() {
    static VaultsBank ret;
    return ret;
}

inline const VaultsBank& vaults() {
    return __vaults__();
}

inline void init_vault_copy(const Vault& s) {
    __vaults__().copy(s);
}

#endif
