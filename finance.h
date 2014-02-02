#ifndef __FINANCE_H
#define __FINANCE_H

#include <mutex>

#include "common.h"

namespace finance {

struct Supply {

private:

    double max_base;
    double base;
    double min_base;

    std::unordered_map<tag_t, unsigned int> purchases;

    std::unordered_map<unsigned int, double> accounts;

    std::mutex mutex;

    void check_valid() {

        // Oops, the markets crashed. Lol.
        if (base < min_base) {

            serialize::Sink sink("finance.dat");

            base = max_base;
            purchases.clear();
            accounts.clear();
        }
    }

    enum OP_t {
        PURCHASE = 0,
        DEPOSIT = 1,
        WITHDRAWAL = 2
    };

public:


    Supply() : max_base(1e6), base(max_base), min_base(0.01) {}

    void load(double b = 1e6, double m = 0.01) {

        max_base = b;
        base = max_base;
        min_base = m;

        try {
            serialize::Source source("finance.dat");

            while (1) {
                try {
                    int type;
                    double amount;
                    tag_t purchase;
                    unsigned int count;
                    unsigned int account;

                    serialize::read(source, type);

                    switch (type) {
                    case PURCHASE:
                        // Purchases.
                        serialize::read(source, amount);
                        serialize::read(source, purchase);
                        serialize::read(source, count);

                        base -= amount;
                        purchases[purchase] += count;
                        break;

                    case DEPOSIT:
                        // Deposits.
                        serialize::read(source, amount);
                        serialize::read(source, account);

                        base -= amount;
                        accounts[account] += amount;
                        break;

                    case WITHDRAWAL:
                        // Withdrawals.
                        serialize::read(source, account);
                        
                        base += accounts[account];
                        accounts.erase(account);
                        break;
                    }

                } catch (...) {
                    break;
                }
            }

        } catch (...) {
        }

        check_valid();
    }

    double get_base() {
        std::unique_lock<std::mutex> l(mutex);

        return base;
    }

    double get_rate() {
        std::unique_lock<std::mutex> l(mutex);

        return max_base / base;
    }

    template <typename DESIGN>
    double get_price(const DESIGN& d, bool fixed = false) {

        std::unique_lock<std::mutex> l(mutex);

        double deflation = base / max_base;
        double price = d.worth * deflation;

        if (fixed) {
            return price;
        }

        auto c = purchases.find(d.tag);

        if (c == purchases.end()) {
            return price;
        }

        unsigned int count = d.count;

        if (c->second >= count) {
            // These items are sold out.
            return -1;
        }

        double scarcity = (double)count / (double)(count - c->second);

        return scarcity * price;
    }

    void purchase(tag_t d, double cost, unsigned int count = 1) {

        std::unique_lock<std::mutex> l(mutex);

        purchases[d] += count;
        base -= cost;

        {
            serialize::Sink sink("finance.dat", true);
            serialize::write(sink, (int)PURCHASE);
            serialize::write(sink, cost);
            serialize::write(sink, d);
            serialize::write(sink, count);
        }

        check_valid();
    }

    double deposit(unsigned int account, double amount) {

        std::unique_lock<std::mutex> l(mutex);

        double& balance = accounts[account];
        balance += amount;
        base -= amount;

        {
            serialize::Sink sink("finance.dat", true);
            serialize::write(sink, (int)DEPOSIT);
            serialize::write(sink, amount);
            serialize::write(sink, account);
        }

        check_valid();

        return balance;
    }

    double withdraw(unsigned int account) {

        std::unique_lock<std::mutex> l(mutex);

        auto i = accounts.find(account);

        if (i == accounts.end()) {
            return 0;
        }

        double ret = i->second;
        accounts.erase(i);
        base += ret;

        {
            serialize::Sink sink("finance.dat", true);
            serialize::write(sink, (int)WITHDRAWAL);
            serialize::write(sink, account);
        }

        check_valid();

        return ret;
    }
};


Supply& supply() {
    static Supply ret;
    return ret;
}

}


#endif
