#ifndef __LEVELSKINS_H
#define __LEVELSKINS_H

struct Levelskin {

    maudit::glyph deep_water;
    maudit::glyph shallow_water;
    maudit::glyph wall;
    maudit::glyph water_wall;
    maudit::glyph floor1;
    maudit::glyph floor2;
    maudit::glyph floor3;
    maudit::glyph floor4;
    maudit::glyph floor5;
    maudit::glyph floor6;
    maudit::glyph floor7;
    maudit::glyph floor8;

    unsigned int lightradius;
    unsigned int lightradius_max;

    unsigned int level;

    bool exclusive;

    struct mapgen_params_t {
        double flow_epsilon;
        unsigned int flow_n_freq;
        double flow_volume;
        double flow_erosion;
        unsigned int flow_renorm_freq;
        double flow_renorm_scale; 
        double walk_threshold;
        unsigned int lowlands_quantile;
        double water_quantile_mean;
        double water_quantile_dev;
        unsigned int flatten_walk_ng;
        unsigned int flatten_water_ng;
        unsigned int unflow_ng;
        double karma_mean;
        double karma_dev;
        int nflatten;
        int nunflow;

        mapgen_params_t() : 
            flow_epsilon(1e-5), 
            flow_n_freq(20), 
            flow_volume(50.0), 
            flow_erosion(1), 
            flow_renorm_freq(500), 
            flow_renorm_scale(15),
            walk_threshold(0),
            lowlands_quantile(4), 
            water_quantile_mean(5.0), 
            water_quantile_dev(1.0),
            flatten_walk_ng(5),
            flatten_water_ng(3),
            unflow_ng(5),
            karma_mean(0.0),
            karma_dev(0.2),
            nflatten(-1),
            nunflow(-1)
            {}
    };


    mapgen_params_t genparams;

    Levelskin() : lightradius(8), lightradius_max(8), level(0), exclusive(false) {}
};

struct Levelskins {
    std::map<unsigned int,Levelskin> skins;

    const Levelskin& get(unsigned int level) const {

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


Levelskins& __levelskins__() {
    static Levelskins ret;
    return ret;
}

const Levelskins& levelskins() {
    return __levelskins__();
}

void init_levelskin(const Levelskin& skin) {
    __levelskins__().set(skin);
}


#endif

