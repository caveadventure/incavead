
#include <thread>
#include <mutex>

#include <sstream>

#include <iostream>

#include "libmaudit/maudit.h"

#include "debug_benchmark.h"

#include "rcode.h"
#include "serialize.h"
#include "common_types.h"
#include "common.h"

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


//#include "configparser.h"
namespace configparser {
extern void parse_config(const std::string& filename, tag_mem_t& tagmem);
}

#include "utilstuff.h"
#include "inventory.h"
#include "inv_screens.h"
#include "player.h"
#include "look_screens.h"
#include "combat.h"
#include "apply.h"
#include "monster_ai.h"


#include "vault_place.h"


enum class screens_t : unsigned int {
    messages = 0,
    inventory,
    inv_item,
    floor_item,
    spells,
    help,
    tombstone
};

#include "inv_screens2.h"

#include "game.h"


void init_statics() {

    std::cout << "Tagmem" << std::endl;
    tag_mem_t tagmem;

    std::cout << "Parse species.cfg" << std::endl;
    configparser::parse_config("species.cfg", tagmem);

    std::cout << "Parse designs.cfg" << std::endl;
    configparser::parse_config("designs.cfg", tagmem);

    configparser::parse_config("terrain.cfg", tagmem);

    configparser::parse_config("vaults.cfg", tagmem);

    configparser::parse_config("celauto.cfg", tagmem);

    configparser::parse_config("levelskins.cfg", tagmem);

    configparser::parse_config("constants.cfg", tagmem);

    ////
}


void client_mainloop(int client_fd, bool singleplayer, bool debug) {

    try {

        std::cout << "Making client socket" << std::endl;
        maudit::client_socket client(client_fd);

        typedef maudit::screen<maudit::client_socket> screen_t;

        std::cout << "Making screen" << std::endl;
        screen_t screen(client);

        std::cout << "Making mainloop" << std::endl;
        mainloop::Main<Game, GameState, screen_t> main(screen, debug);

        std::cout << "Starting mainloop" << std::endl;
        main.mainloop(singleplayer);

    } catch (std::exception& e) {
        std::cerr << "Caught error: " << e.what() << std::endl;

    } catch (...) {
    }
}


void do_genmaps() {

    std::cout << "Generating a new set of maps. Please wait." << std::endl;

    GameState state;
    state.neigh.init(Game::GRID_W, Game::GRID_H);
    state.grid.init(Game::GRID_W, Game::GRID_H);

    for (int worldz = -4; worldz <= 15; ++worldz) {
        for (int worldx = -1; worldx <= 1; ++worldx) {
            for (int worldy = -1; worldy <= 1; ++worldy) {

                uint64_t gridseed;
                std::string filename;

                Game::make_mapname(worldx, worldy, worldz, gridseed, filename);

                std::cout << "=== Making map for: " << worldx << "," << worldy << "," << worldz << std::endl;
                Game::make_map(worldx, worldy, worldz, state, gridseed, filename,
                               [](const std::string& msg) { std::cout << msg << std::endl; });
            }
        }
    }
}


int main(int argc, char** argv) {

    std::cout << "Making server socket." << std::endl;

    maudit::server_socket server(20020);

    std::cout << "Server socket OK." << std::endl;
    std::cout << "Initting statics" << std::endl;

    init_statics();

    std::cout << "Loading bones" << std::endl;
    bones::bones().load();
    std::cout << "Loading uniques" << std::endl;
    uniques::uniques().load();
    std::cout << "Loading items" << std::endl;
    uniques::items().load();
    std::cout << "Loading features" << std::endl;
    permafeats::features().load();


    bool singleplayer = false;
    bool genmaps = false;
    bool debug = false;

    if (argc > 1) {

        std::string arg(argv[1]);

        if (arg == "-s" || arg == "--singleplayer") {

            singleplayer = true;

        } else if (arg == "-g" || arg == "--generate") {

            genmaps = true;

        } else if (arg == "-d" || arg == "--debug") {
            
            debug = true;
        }
    }

    if (genmaps) {
        do_genmaps();
        return 0;
    }

    if (singleplayer) {
        std::cout << "Accepting from server." << std::endl;
        int client = server.accept();
        client_mainloop(client, true, false);

    } else {

        while (1) {

            std::cout << "Accepting..." << std::endl;
            int client = server.accept();

            std::cout << "Making thread..." << std::endl;
            std::thread thr(client_mainloop, client, false, debug);
            thr.detach();
        }
    }

    return 0;
}

