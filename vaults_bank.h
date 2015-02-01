#ifndef __VAULTS_BANK
#define __VAULTS_BANK

#include <string>
#include <unordered_map>

struct VaultsBank {

    std::unordered_map<tag_t,Vault> bank;
    counters::Counts fixed_counts;
    counters::Counts semirandom_counts;
    counters::Counts random_counts;

    void copy(const Vault& s) {

        if (bank.count(s.tag) != 0) {
            throw std::runtime_error("Duplicate vaults tag");
        }

        bank[s.tag] = s;

        switch (s.type) {
        case Vault::type_t::FIXED:
            fixed_counts.init(s.tag, s.level, s.count);
            break;
        case Vault::type_t::SEMIRANDOM:
            semirandom_counts.init(s.tag, s.level, s.count);
            break;
        case Vault::type_t::RANDOM:
            random_counts.init(s.tag, s.level, s.count);
            break;
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
