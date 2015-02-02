
#include <thread>
#include <mutex>

#include <sstream>

#include <iostream>

#include <math.h>
//#include <stdlib.h>

#include "libmaudit/maudit.h"

#include "debug_benchmark.h"

#include "rcode.h"
#include "serialize.h"
#include "common_types.h"
#include "common.h"
#include "skins.h"

////

#include "damage.h"

#include "constants.h"
#include "terrain.h"
#include "designs.h"
#include "species.h"
#include "vaults.h"

#include "counters.h"

#include "terrain_bank.h"
#include "designs_bank.h"
#include "species_bank.h"
#include "vaults_bank.h"
#include "celauto_bank.h"

#include "levelskins.h"

#include "nlp.h"


#include "gamestate.h"

#include "mainloop_net.h"

#include "bones.h"
#include "uniques.h"
#include "permafeats.h"
#include "finance.h"


//#include "configparser.h"
namespace configparser {
extern void parse_config(const std::string& filename, tag_mem_t& tagmem);
}

#include "utilstuff.h"
#include "inventory.h"
#include "player.h"
#include "combat.h"
#include "monster_ai.h"

#include "vault_place.h"

#include "game.h"


void init_statics() {

    tag_mem_t tagmem;

    configparser::parse_config("species.cfg", tagmem);

    configparser::parse_config("designs.cfg", tagmem);

    configparser::parse_config("terrain.cfg", tagmem);

    configparser::parse_config("vaults.cfg", tagmem);

    configparser::parse_config("celauto.cfg", tagmem);

    configparser::parse_config("levelskins.cfg", tagmem);

    configparser::parse_config("constants.cfg", tagmem);

    configparser::parse_config("damage.cfg", tagmem);

    configparser::parse_config("howto.cfg", tagmem);

    ////
}


void client_mainloop(int client_fd, bool singleplayer, bool debug, size_t n_skin, bool fullwidth) {

    try {

        maudit::client_socket client(client_fd);

        typedef maudit::screen<maudit::client_socket> screen_t;

        screen_t screen(client);

        mainloop::Main<Game, GameState, GameOptions, screen_t> main(screen, debug, n_skin, fullwidth);

        main.mainloop(singleplayer);

    } catch (std::exception& e) {
        std::cerr << "Caught error: " << e.what() << std::endl;

    } catch (...) {
    }
}

void spectator_mainloop(int client_fd) {

    try {

        maudit::client_socket client(client_fd);

        typedef maudit::screen<maudit::client_socket> screen_t;

        screen_t screen(client);

        spectator::choose_and_watch(screen);

    } catch (std::exception& e) {
        std::cerr << "Caught error: " << e.what() << std::endl;

    } catch (...) {
    }
}

template <typename SOCKET>
void serverloop(SOCKET& sock, bool debug, size_t nskin, bool fullwidth) {

    while (1) {

        int client = sock.accept();

        std::thread thr(client_mainloop, client, false, debug, nskin, fullwidth);
        thr.detach();
    }
}

template <typename SOCKET>
void spectatorloop(SOCKET& sock) {

    while (1) {
        
        int client = sock.accept();

        std::thread thr(spectator_mainloop, client);
        thr.detach();
    }
}

void do_genmaps(int start, int end) {

    std::cout << "Generating a new set of maps. Please wait." << std::endl;

    GameState state;
    state.neigh.init(Game::GRID_W, Game::GRID_H);
    state.grid.init(Game::GRID_W, Game::GRID_H);

    for (int worldz = start; worldz <= end; ++worldz) {
        for (int worldx = -1; worldx <= 1; ++worldx) {
            for (int worldy = -1; worldy <= 1; ++worldy) {

                std::string filename;
                make_mapname(worldx, worldy, worldz, filename);

                /*
                uint64_t fixedseed = (((uint64_t)worldx) ^ 
                                      ((uint64_t)worldy << 16) ^
                                      ((uint64_t)worldz << 32)) + 1;

                std::cout << "=== Making map for: " << worldx << "," << worldy << "," << worldz << std::endl;
                make_map(worldx, worldy, worldz, state, fixedseed, filename,
                         [](const std::string& msg) { std::cout << msg << std::endl; });
                */
            }
        }
    }
}


int main(int argc, char** argv) {

    maudit::server_socket server(20020);

    init_statics();

    bones::bones().load(constants().max_bones);
    uniques::uniques().load();
    uniques::items().load();
    permafeats::features().load(constants().max_permafeats);
    finance::supply().load(constants().monetary_supply_base, constants().min_money_value);


    bool singleplayer = false;
    bool genmaps = false;
    bool debug = false;
    int graphics = 0;
    bool fullwidth = false;

    int genmaps_start = -9;
    int genmaps_end = 26;
    
    for (int argi = 1; argi < argc; ++argi) {

        std::string arg(argv[argi]);

        if (arg == "-s" || arg == "--singleplayer") {

            singleplayer = true;

        } else if (arg == "-g" || arg == "--generate") {

            genmaps = true;

        } else if (arg == "-d" || arg == "--debug") {
            
            debug = true;

        } else if (arg == "-u" || arg == "--unicode") {

            graphics = 1;

        } else if (arg == "-t" || arg == "--tiles") {

            graphics = 2;
            fullwidth = true;

        } else if (genmaps) {

            size_t n = arg.find(':');

            if (n != std::string::npos) {
                genmaps_start = std::stoi(arg.substr(0, n));
                genmaps_end = std::stoi(arg.substr(n+1));
            }
        }
    }

    if (genmaps) {
        do_genmaps(genmaps_start, genmaps_end);
        return 0;
    }

    if (singleplayer) {
        int client = server.accept();
        client_mainloop(client, true, false, graphics, fullwidth);

    } else {

        std::thread specl([&]() {
                
                maudit::server_socket specs(22222);
                spectatorloop(specs);
            });
        specl.detach();


        std::thread thru([&]() {

                maudit::server_socket serveru(20022);
                serverloop(serveru, debug, 1, false);
            });
        thru.detach();

        std::thread thrf([&]() {

                maudit::server_socket serverf(20028);
                serverloop(serverf, debug, 2, true);
            });
        thrf.detach();

        serverloop(server, debug, 0, false);

    }

    return 0;
}

