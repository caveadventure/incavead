
#include <iostream>
#include <set>
#include <algorithm>
#include <stdexcept>

#include "../strings_bank.h"
#include "../highscore.h"


std::string quote(const std::string& s) {
    std::string ret;

    for (unsigned char c : s) {
        if (c == '\\') ret += "\\\\";
        else if (c == '"') ret += "\\\"";
        else if (c <= 31) ret += " ";
        else ret += c;
    }

    return ret;
}


void _process(size_t n, const bones::bone_t::fakeobj& name, const bones::bone_t::fakeobj& cause,
              unsigned int plev, int dlev, double worth, bool victory, size_t rcodes) {

    if (n != 0)
        std::cout << ",";

    auto _cause = cause;
    _cause.name = quote(_cause.name);

    auto _name = name;
    _name.name = quote(_name.name);

    std::cout << nlp::message("\n{\"dlev\": %d, \"plev\": %d, \"name\": \"%S\", \"cause\": \"%s\","
                              " \"worth\": %d, \"victory\": %s, \"rcodes\": %d}",
                              dlev+1, plev+1, _name, _cause, worth,
                              std::string(victory ? "true" : "false"), rcodes);
}

void split_name(const std::string& in, std::string& out, size_t& nach) {

    std::string::size_type achpos = in.find(" (");

    if (achpos == std::string::npos) {
        out = in;
        nach = 0;
        return;
    }

    out = in.substr(0, achpos);
    nach = 1;

    std::string tmp = in.substr(achpos);

    for (unsigned char cc : tmp) {
        if (cc == ',') {
            nach++;
        }
    }
}

struct bank_stats_t {

    enum OP_t {
        PURCHASE = 0,
        DEPOSIT = 1,
        WITHDRAWAL = 2
    };

    double base;

    std::set<tag_t> item_kinds_bought;
    size_t items_bought;
    double items_prices;

    std::map<unsigned int, double> accounts;
    double deposits;

    void load() {

        base = 0;
        item_kinds_bought.clear();
        items_bought = 0;
        items_prices = 0;
        accounts.clear();
        deposits = 0;

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

                        base += amount;
                        item_kinds_bought.insert(purchase);
                        items_bought += count;
                        items_prices += amount;
                        break;

                    case DEPOSIT:
                        // Deposits.
                        serialize::read(source, amount);
                        serialize::read(source, account);

                        base += amount;
                        accounts[account] += amount;
                        break;

                    case WITHDRAWAL:
                        // Withdrawals.
                        serialize::read(source, account);
                        
                        base -= accounts[account];
                        accounts.erase(account);
                        break;
                    }

                } catch (...) {
                    break;
                }
            }

        } catch (...) {
        }

        for (const auto& i : accounts) {
            deposits += i.second;
        }
    }

    void print() {

        std::cout << nlp::message("\n{\n"
                                  "\"base\": %d,\n"
                                  "\"purchases\": { \"num\": %d, \"kinds\": %d, \"cost\": %d },\n"
                                  "\"accounts\": { \"num\": %d, \"val\": %d }\n"
                                  "}\n",
                                  base, items_bought, item_kinds_bought.size(), items_prices,
                                  accounts.size(), deposits);
    }
};

struct other_stats_t {

    std::pair<std::string,size_t> cause_raw;
    std::pair<std::string,size_t> cause_plev;
    std::pair<std::string,size_t> cause_worth;

    double gdp1;
    double gdp2;
    double gdp3;

    double avg_plev;
    double avg_dlev;
    unsigned int median_plev;
    int median_dlev;

    size_t players;
    std::pair<std::string,size_t> most_active_player;
    std::pair<std::string,size_t> scummer;

    size_t ngames;

    std::pair< std::string, std::pair<double, std::string> > got_rich_quick;

    std::pair<std::string, size_t> most_achievements;

    std::string rare_cause;

    other_stats_t() : gdp1(0), gdp2(0), gdp3(0), avg_plev(0), avg_dlev(0), 
                      median_plev(0), median_dlev(0), players(0), ngames(0) {}

    void operator()(std::vector<highscore::Scores::order_t>& v) {

        if (v.size() == 0)
            return;

        std::reverse(v.begin(), v.end());

        ngames = v.size();

        typedef std::map< std::string, std::pair<unsigned int, std::pair<double,double> > > by_cause_t;
        by_cause_t by_cause;

        typedef std::map< std::string, std::pair<unsigned int, size_t> > by_players_t;
        by_players_t by_players;

        std::map<int, double> gdp_lev;

        std::string real_name;
        size_t num_aches;

        for (const auto& i : v) {

            auto& tmp = by_cause[i.bone.cause.name];
            tmp.first++;
            tmp.second.first += ::log(i.plev+1);
            tmp.second.second += ::log(i.worth+0.01);

            gdp1 += i.worth;
            gdp2 += i.bone.worth;

            avg_plev += i.plev;
            avg_dlev += i.dlev;

            split_name(i.bone.name.name, real_name, num_aches);

            auto& tmb = by_players[real_name];
            tmb.first++;
            tmb.second = std::max(tmb.second, i.scum_streak);

            if (i.plev == 0 && i.worth >= got_rich_quick.second.first) {
                got_rich_quick.first = i.bone.name.name;
                got_rich_quick.second.first = i.worth;
                got_rich_quick.second.second = i.bone.cause.name;
            }

            gdp_lev[i.dlev] += i.bone.worth;

            if (num_aches >= most_achievements.second) {
                most_achievements.first = i.bone.name.name;
                most_achievements.second = num_aches;
            }
        }

        for (const auto& i : gdp_lev) {
            if (i.second > 0) {
                gdp3 += i.second;
            }
        }

        avg_plev /= v.size();
        avg_dlev /= v.size();

        std::sort(v.begin(), v.end(), [](const highscore::Scores::order_t& a,
                                         const highscore::Scores::order_t& b) {
                      return a.plev < b.plev; });

        median_plev = v[v.size() / 2].plev;

        std::sort(v.begin(), v.end(), [](const highscore::Scores::order_t& a,
                                         const highscore::Scores::order_t& b) {
                      return a.dlev < b.dlev; });

        median_dlev = v[v.size() / 2].dlev;

        auto i = std::max_element(by_cause.begin(), by_cause.end(),
                                  [](const by_cause_t::value_type& a, const by_cause_t::value_type& b) {
                                      return (a.second.first < b.second.first); });

        cause_raw.first = i->first;
        cause_raw.second = i->second.first;

        i = std::max_element(by_cause.begin(), by_cause.end(),
                             [](const by_cause_t::value_type& a, const by_cause_t::value_type& b) {
                                 return (a.second.second.first < b.second.second.first); });

        cause_plev.first = i->first;
        cause_plev.second = i->second.first;

        i = std::max_element(by_cause.begin(), by_cause.end(),
                             [](const by_cause_t::value_type& a, const by_cause_t::value_type& b) {
                                 return (a.second.second.second < b.second.second.second); });

        cause_worth.first = i->first;
        cause_worth.second = i->second.first;

        i = std::min_element(by_cause.begin(), by_cause.end(),
                             [](const by_cause_t::value_type& a, const by_cause_t::value_type& b) {
                                 if (a.second.first < b.second.first) 
                                     return true;
                                 if (a.second.first == b.second.first && 
                                     a.second.second.second > b.second.second.second)
                                     return true;
                                 return false;
                             });

        rare_cause = i->first;

        players = by_players.size();

        auto j = std::max_element(by_players.begin(), by_players.end(),
                                  [](const by_players_t::value_type& a, const by_players_t::value_type& b) {
                                      return (a.second.first < b.second.first); });

        most_active_player.first = j->first;
        most_active_player.second = j->second.first;

        j = std::max_element(by_players.begin(), by_players.end(),
                             [](const by_players_t::value_type& a, const by_players_t::value_type& b) {
                                 return (a.second.second < b.second.second); });

        scummer.first = j->first;
        scummer.second = j->second.second;
    }

    void print() {

        bones::bone_t::fakeobj cause_raw_name(quote(cause_raw.first));
        bones::bone_t::fakeobj cause_plev_name(quote(cause_plev.first));
        bones::bone_t::fakeobj cause_worth_name(quote(cause_worth.first));
        bones::bone_t::fakeobj rare_cause_name(quote(rare_cause));

        most_active_player.first = quote(most_active_player.first);
        scummer.first = quote(scummer.first);
        most_achievements.first = quote(most_achievements.first);
        got_rich_quick.first = quote(got_rich_quick.first);

        bones::bone_t::fakeobj cause_g_r_q(quote(got_rich_quick.second.second));

        std::cout << nlp::message("\n{\n"
                                  "\"games\": %d,\n"
                                  "\"kills_raw\": { \"cause\": \"%s\", \"kills\": %d },\n"
                                  "\"kills_plev\": { \"cause\": \"%s\", \"kills\": %d },\n"
                                  "\"kills_worth\": { \"cause\": \"%s\", \"kills\": %d },\n"
                                  "\"kills_rare\": \"%s\",\n"
                                  "\"gdp\": { \"a\": %d, \"b\": %d, \"c\": %d },\n"
                                  "\"plev\": { \"avg\": %d, \"median\": %d },\n"
                                  "\"dlev\": { \"avg\": %d, \"median\": %d },\n"
                                  "\"players\": %d,\n"
                                  "\"most_active\": { \"name\": \"%S\", \"games\": %d },\n"
                                  "\"scummer\": { \"name\": \"%S\", \"streak\": %d },\n"
                                  "\"most_achievements\": { \"name\": \"%S\", \"number\": %d },\n"
                                  "\"got_rich_quick\": { \"name\": \"%S\", \"worth\": %d, \"cause\": \"%s\" }\n"
                                  "}\n",
                                  ngames,
                                  cause_raw_name, cause_raw.second, 
                                  cause_plev_name, cause_plev.second,
                                  cause_worth_name, cause_worth.second,
                                  rare_cause_name,
                                  gdp1, gdp2, gdp3,
                                  avg_plev+1, median_plev+1,
                                  avg_dlev+1, median_dlev+1,
                                  players,
                                  most_active_player.first, most_active_player.second,
                                  scummer.first, scummer.second,
                                  most_achievements.first, most_achievements.second,
                                  got_rich_quick.first, got_rich_quick.second.first, cause_g_r_q);
    }
};


int main(int argc, char** argv) {

    try {

        highscore::Scores scores;

        auto scores_saved = scores.scores;

        std::cout << nlp::message("{\"num_games\": %d,\n", scores.scores.size());
        std::cout << "\"highscores\": {";

        scores.by_ts();
        std::cout << "\"victors\": [";
        scores.process(_process, 1, 5);
        std::cout << "]," << std::endl;

        std::cout << "\"ts\": [";
        scores.process(_process, 0);
        std::cout << "]," << std::endl;

        scores.by_plev();
        std::cout << "\"plev\": [";
        scores.process(_process, 0);
        std::cout << "]," << std::endl;

        scores.by_dlev_d();
        std::cout << "\"dlev_d\": [";
        scores.process(_process, 0);
        std::cout << "]," << std::endl;

        scores.by_dlev_a();
        std::cout << "\"dlev_a\": [";
        scores.process(_process, 0);
        std::cout << "]," << std::endl;

        scores.by_worth();
        std::cout << "\"worth\": [";
        scores.process(_process, 0);
        std::cout << "]" << std::endl;

        std::cout << "}," << std::endl; 

        other_stats_t other;
        other(scores_saved);

        std::cout << "\"stats\": ";
        other.print();

        bank_stats_t money;
        money.load();

        std::cout << ",\"money\": ";
        money.print();

        std::cout << "}" << std::endl;


    } catch (std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;

    } catch (...) {
        std::cerr << "Unknown fatal error." << std::endl;
        return 1;
    }

    return 0;
}

