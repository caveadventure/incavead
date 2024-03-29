#ifndef __LEVELSKINS_H
#define __LEVELSKINS_H

struct Levelskin {

    skins deep_water;
    skins shallow_water;
    skins wall;
    skins water_wall;
    skins floor1;
    skins floor2;
    skins floor3;
    skins floor4;
    skins floor5;
    skins floor6;
    skins floor7;
    skins floor8;

    unsigned int lightradius;
    unsigned int lightradius_max;

    tag_t ailment;

    int level;

    bool exclusive_monsters;
    bool exclusive_items;

    bool no_phase_level;

    int species_level;
    int designs_level;
    int vaults_level;

    unsigned int number_fixed_vaults;
    unsigned int number_semirandom_vaults;
    unsigned int number_random_vaults;

    mean_deviation_t number_monsters;
    mean_deviation_t number_items;
    mean_deviation_t number_features;

    std::string name;

    bool has_treasure;
    double treasure_level;

    struct mapgen_params_t {
        double flow_epsilon;
        unsigned int flow_n_freq;
        double flow_volume;
        double flow_erosion;
        unsigned int flow_renorm_freq;
        double flow_renorm_scale; 
        double walk_threshold;
        unsigned int lowlands_threshold;
        double water_quantile_mean;
        double water_quantile_dev;
        unsigned int flatten_walk_ng;
        unsigned int flatten_water_ng;
        unsigned int unflow_ng;
        double karma_mean;
        double karma_dev;
        int nflatten_walk;
        int nflatten_water;
        int nunflow;

        mapgen_params_t() : 
            flow_epsilon(1e-5), 
            flow_n_freq(20), 
            flow_volume(50.0), 
            flow_erosion(1), 
            flow_renorm_freq(500), 
            flow_renorm_scale(15),
            walk_threshold(0),
            lowlands_threshold(1), 
            water_quantile_mean(5.0), 
            water_quantile_dev(1.0),
            flatten_walk_ng(0x1FF & ~0x1F), // Bitmask of 5,6,7,8
            flatten_water_ng(0x1FF & ~0x7), // Bitmask of 3,4,5,6,7,8
            unflow_ng(0x1F), // Bitmask of 0,1,2,3,4
            karma_mean(0.0),
            karma_dev(0.2),
            nflatten_walk(-1),
            nflatten_water(-1),
            nunflow(-1)
            {}
    };


    mapgen_params_t genparams;

    Levelskin() : lightradius(8), lightradius_max(8), level(0), exclusive_monsters(false), 
                  exclusive_items(false), no_phase_level(false), 
                  species_level(-1), designs_level(-1), vaults_level(-1),
                  number_fixed_vaults(100), number_semirandom_vaults(0), number_random_vaults(0),
                  number_monsters(250.0, 20.0), 
                  number_items(300.0, 50.0),
                  number_features(160.0, 30.0),
                  has_treasure(false), treasure_level(0)
        {}


    unsigned int get_species_level(int worldz) const {
        return (species_level >= 0 ? species_level : std::max(worldz, 0));
    }

    unsigned int get_designs_level(int worldz) const {
        return (designs_level >= 0 ? designs_level : std::max(worldz, 0));
    }

    unsigned int get_vaults_level(int worldz) const {
        return (vaults_level  >= 0 ? vaults_level  : std::max(worldz, 0));
    }
};

struct Levelskins {

    std::map<int,Levelskin> skins;

    const Levelskin& get(int level) const {

        if (skins.size() == 0)
            throw std::runtime_error("sanity error: no levelskins defined");

        auto i = skins.upper_bound(level);

        if (i == skins.begin()) {
            return i->second;

        } else {
            --i;
            return i->second;
        }
    }

    void set(const Levelskin& skin) {
        skins[skin.level] = skin;
    }
};


inline Levelskins& __levelskins__() {
    static Levelskins ret;
    return ret;
}

inline const Levelskins& levelskins() {
    return __levelskins__();
}

inline void init_levelskin(const Levelskin& skin) {
    __levelskins__().set(skin);
}


#endif

