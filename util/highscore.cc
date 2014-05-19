
#include <iostream>
#include <set>
#include <algorithm>
#include <stdexcept>

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

    other_stats_t() : gdp1(0), gdp2(0), gdp3(0), avg_plev(0), avg_dlev(0), 
                      median_plev(0), median_dlev(0), players(0), ngames(0) {}

    void operator()(const std::vector<highscore::Scores::order_t>& v) {

        if (v.size() == 0)
            return;

        ngames = v.size();

        typedef std::map< std::string, std::pair<unsigned int, std::pair<double,double> > > by_cause_t;
        by_cause_t by_cause;

        typedef std::map< std::string, std::pair<unsigned int, size_t> > by_players_t;
        by_players_t by_players;

        std::map<int, double> gdp_lev;

        for (const auto& i : v) {

            auto& tmp = by_cause[i.bone.cause.name];
            tmp.first++;
            tmp.second.first += ::log(i.plev+1);
            tmp.second.second += ::log(i.worth+0.01);

            gdp1 += i.worth;
            gdp2 += i.bone.worth;

            avg_plev += i.plev;
            avg_dlev += i.dlev;

            auto& tmb = by_players[i.bone.name.name];
            tmb.first++;
            tmb.second = std::max(tmb.second, i.scum_streak);

            if (i.plev == 0 && i.worth >= got_rich_quick.second.first) {
                got_rich_quick.first = i.bone.name.name;
                got_rich_quick.second.first = i.worth;
                got_rich_quick.second.second = i.bone.cause.name;
            }

            gdp_lev[i.dlev] += i.bone.worth;
        }

        for (const auto& i : gdp_lev) {
            if (i.second > 0) {
                gdp3 += i.second;
            }
        }

        avg_plev /= v.size();
        avg_dlev /= v.size();

        auto v_copy = v;

        std::sort(v_copy.begin(), v_copy.end(), [](const highscore::Scores::order_t& a,
                                                   const highscore::Scores::order_t& b) {
                      return a.plev < b.plev; });

        median_plev = v[v.size() / 2].plev;

        std::sort(v_copy.begin(), v_copy.end(), [](const highscore::Scores::order_t& a,
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

        most_active_player.first = quote(most_active_player.first);
        scummer.first = quote(scummer.first);
        got_rich_quick.first = quote(got_rich_quick.first);

        bones::bone_t::fakeobj cause_g_r_q(quote(got_rich_quick.second.second));

        std::cout << nlp::message("\n{\n"
                                  "\"games\": %d,\n"
                                  "\"kills_raw\": { \"cause\": \"%s\", \"kills\": %d },\n"
                                  "\"kills_plev\": { \"cause\": \"%s\", \"kills\": %d },\n"
                                  "\"kills_worth\": { \"cause\": \"%s\", \"kills\": %d },\n"
                                  "\"gdp\": { \"a\": %d, \"b\": %d, \"c\": %d },\n"
                                  "\"plev\": { \"avg\": %d, \"median\": %d },\n"
                                  "\"dlev\": { \"avg\": %d, \"median\": %d },\n"
                                  "\"players\": %d,\n"
                                  "\"most_active\": { \"name\": \"%S\", \"games\": %d },\n"
                                  "\"scummer\": { \"name\": \"%S\", \"streak\": %d },\n"
                                  "\"got_rich_quick\": { \"name\": \"%S\", \"worth\": %d, \"cause\": \"%s\" }\n"
                                  "}\n",
                                  ngames,
                                  cause_raw_name, cause_raw.second, 
                                  cause_plev_name, cause_plev.second,
                                  cause_worth_name, cause_worth.second,
                                  gdp1, gdp2, gdp3,
                                  avg_plev+1, median_plev+1,
                                  avg_dlev, median_dlev,
                                  players,
                                  most_active_player.first, most_active_player.second,
                                  scummer.first, scummer.second,
                                  got_rich_quick.first, got_rich_quick.second.first, cause_g_r_q);
    }
};


int main(int argc, char** argv) {

    try {

        highscore::Scores scores;

        std::cout << nlp::message("{\"num_games\": %d,\n", scores.scores.size());
        std::cout << "\"highscores\": {";

        std::cout << "\"ts\": [";
        scores.by_ts(_process);
        std::cout << "]," << std::endl;

        std::cout << "\"plev\": [";
        scores.by_plev(_process);
        std::cout << "]," << std::endl;

        std::cout << "\"dlev_d\": [";
        scores.by_dlev_d(_process);
        std::cout << "]," << std::endl;

        std::cout << "\"dlev_a\": [";
        scores.by_dlev_a(_process);
        std::cout << "]," << std::endl;

        std::cout << "\"worth\": [";
        scores.by_worth(_process);
        std::cout << "]" << std::endl;

        std::cout << "}," << std::endl; 

        other_stats_t other;
        other(scores.scores);

        std::cout << "\"stats\": ";
        other.print();

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

