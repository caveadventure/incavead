#ifndef __CONFIGPARSER_H
#define __CONFIGPARSER_H

// This file needs to be preprocessed with the 'ragel' tool.
// Run it like this:
//
//   ragel -G2 configparser.rl -o configparser.h
//

#include <string>
#include <stdexcept>
#include <iostream>

#include <string.h>
#include <stdio.h>


namespace configparser {

struct ragel_state {

    /** Ragel scanner cruft. **/

    // Iterators for start and end of buffer data.
    char* p;
    char* pe;

    // Iterator for 'end of file'.
    char* eof;

    // Internal state and rollback variables.
    int cs, act;

    // Stack for ragel machine states.
    int stack[256];
    int top;

    // Not part of ragel's variables; this is a buffer to hold the current match.
    std::string match;
};

inline void init_species(const Species& s) {
    init_species_copy(s);
}

inline void init_design(const Design& d) {
    init_design_copy(d);
}

inline void init_terrain(const Terrain& t) {
    init_terrain_copy(t);
}

inline void init_vault(const Vault& v) {
    init_vault_copy(v);
}

inline void init_celauto(const CelAuto& c) {
    init_celauto_copy(c);
}

inline void init_levelskin_(const Levelskin& l) {
    init_levelskin(l);
}

inline void init_damage(const Damage& d) {
    init_damage_copy(d);
}

inline void init_stat(const Stat& s) {
    init_stat_copy(s);
}

inline void init_count(const Count& s) {
    init_count_copy(s);
}

inline void add_color(maudit::color& c, unsigned int i) {
    c = (maudit::color)((uint32_t)c + i);
}

inline int toint(const std::string& s) {
    return ::atoi(s.c_str());
}

inline double toreal(const std::string& s) {
    return ::atof(s.c_str());
}


void parse_config(const std::string& filename, tag_mem_t& tagmem) {

    /** File reading cruft. **/

    char buf[4096];

    FILE* fn = ::fopen(filename.c_str(), "r");

    if (fn == NULL) {
        throw std::runtime_error("Could not open: \"" + filename + "\"");
    }

    ragel_state state;

    Species spe;
    Design des;
    Terrain ter;
    Vault vau;
    CelAuto cel;
    Levelskin lev;
    Damage dam;
    Stat sta;
    Count cou;
    ConstantsBank::ailment_t ail;

    damage::val_t dmgval;

    mean_deviation_t meandev;

    maudit::glyph skin;
    maudit::glyph skin_b;
    maudit::glyph skin_c;

    size_t bitmask_v;

#define SKINS skin, skin_b, skin_c
    
    Vault::brush vbrush;

    unsigned char shortcut_key;
    tag_t genus_tag;
    tag_t flavor_tag;
    tag_t ach_tag;
    tag_t ail_tag;
    tag_t tmp_tag;
    unsigned int starsign_n;
    uint64_t hash;

    ui_symbols_t* ui_syms = NULL;

    %%{

        machine ConfigParser;

        access state.;
        variable p state.p;
        variable pe state.pe;
        variable eof state.eof;

        action start {
            state.match.clear();
        }

        action push {
            state.match += fc;
        }

        onews = [ \t\r\n];
        ws = onews*;
        ws1 = onews+;
        sep = '_' | ws;

        number = [0-9]+ 
            >start $push;

        snumber = ('-'? [0-9]+)
            >start $push;

        real = (('-'?) (([0-9]+ '\.' [0-9]+) | ([0-9]+)))
            >start $push;

        tag = [a-zA-Z0-9_]+ 
            >start $push;

        #/* 34 is the double quote character, the only reason for writing it like this is to make Emacs happy */
        quote = 34;

        strchar_escape := 
            ( ('"'   ${ state.match += '"';  fret; }) |
              ('n'   ${ state.match += '\n'; fret; }) |
              ('1'   ${ state.match += '\1'; fret; }) |
              ('2'   ${ state.match += '\2'; fret; }) |
              ('3'   ${ state.match += '\3'; fret; }) |
              ('\\'  ${ state.match += '\\'; fret; }) )
            ;

        strchar = ( (^ (quote | '\\') $push ) |
                    ('\\'             ${fcall strchar_escape;} ) );

        strdata = strchar*;

        string = '"' >start strdata '"';

        mean_dev = real %{ meandev.mean = toreal(state.match); } ws '|' ws
                   real %{ meandev.deviation = toreal(state.match); };

        colorname = 
            'black'   | 
            'red'     %{ add_color(skin.fore, 1); } | 
            'green'   %{ add_color(skin.fore, 2); } | 
            'yellow'  %{ add_color(skin.fore, 3); } | 
            'blue'    %{ add_color(skin.fore, 4); } | 
            'magenta' %{ add_color(skin.fore, 5); } | 
            'cyan'    %{ add_color(skin.fore, 6); } | 
            'white'   %{ add_color(skin.fore, 7); } ;

        color = 
            ('none'   %{ skin.fore = maudit::color::none; } ) | 
            ('dim'    %{ skin.fore = maudit::color::dim_black; }    sep colorname) | 
            ('bright' %{ skin.fore = maudit::color::bright_black; } sep colorname) ;

        back_color =
            'none'    %{ skin.back = maudit::color::none; }           |
            'black'   %{ skin.back = maudit::color::bright_black; }   | 
            'red'     %{ skin.back = maudit::color::bright_red; }     | 
            'green'   %{ skin.back = maudit::color::bright_green; }   | 
            'yellow'  %{ skin.back = maudit::color::bright_yellow; }  | 
            'blue'    %{ skin.back = maudit::color::bright_blue; }    | 
            'magenta' %{ skin.back = maudit::color::bright_magenta; } | 
            'cyan'    %{ skin.back = maudit::color::bright_cyan; }    | 
            'white'   %{ skin.back = maudit::color::bright_white; }   ;

        skin = string %{ skin.set_text(state.match); 
                         skin.back = maudit::color::bright_black; 
                         skin.fore = maudit::color::bright_white;
                         skin.underline = false; } 
               ws
               (color ws)?
               ('back' ws1 back_color ws)? 
               ('underline' %{ skin.underline = true; } ws)?
               %{ skin_b = skin; skin_c = skin; }
               (('|' ws string %{ skin_b.set_text(state.match); })
                ws
                ('|' ws string %{ skin_c.set_text(state.match); })?)?
               ;

        bitmask = '' %{ bitmask_v = 0; }
                  ( number %{ bitmask_v |= (1 << toint(state.match)); } ws)* ;

        ####

        damage_val = 
            tag %{ dmgval.type = tag_t(state.match, tagmem); } 
            ws1 real %{ dmgval.val = toreal(state.match); }
            ;


        ####

        habitat = 
            'walk'              %{ spe.habitat = Species::habitat_t::walk; }              | 
            'floor'             %{ spe.habitat = Species::habitat_t::floor; }             | 
            'water'             %{ spe.habitat = Species::habitat_t::water; }             | 
            'corner'            %{ spe.habitat = Species::habitat_t::corner; }            | 
            'shoreline'         %{ spe.habitat = Species::habitat_t::shoreline; }         ; 

        ai = 
            'none'             %{ spe.ai = Species::ai_t::none; }             |
            'seek'             %{ spe.ai = Species::ai_t::seek; }             |
            'random'           %{ spe.ai = Species::ai_t::random; }           |
            'seek_awake'       %{ spe.ai = Species::ai_t::seek_awake; }       |
            'magic_none'       %{ spe.ai = Species::ai_t::magic_none; }       |
            'magic_none_awake' %{ spe.ai = Species::ai_t::magic_none_awake; } |
            'suicide'          %{ spe.ai = Species::ai_t::suicide; }          |
            'magic_random'     %{ spe.ai = Species::ai_t::magic_random; }     ;

        idle_ai = 
            'none'   %{ spe.idle_ai = Species::idle_ai_t::none; }   |
            'random' %{ spe.idle_ai = Species::idle_ai_t::random; } ;

        move = 
            'walk'      %{ spe.move = Species::move_t::walk; }      | 
            'floor'     %{ spe.move = Species::move_t::floor; }     | 
            'water'     %{ spe.move = Species::move_t::water; }     |
            'corner'    %{ spe.move = Species::move_t::corner; }    |
            'shoreline' %{ spe.move = Species::move_t::shoreline; } ;

        species_count       = 'count'       ws1 number     %{ spe.count = toint(state.match); } ;
        species_name        = 'name'        ws1 string     %{ spe.name = state.match; } ;
        species_skin        = 'skin'        ws1 skin       %{ spe.skin.set(SKINS); } ;
        species_true_level  = 'true_level'  ws1 number     %{ spe.true_level = toint(state.match); } ;
        species_genus       = 'genus'       ws1 tag        %{ spe.genus = tag_t(state.match, tagmem); } ;
        species_descr       = 'descr'       ws1 string     %{ spe.descr = state.match; } ;
        species_habitat     = 'habitat'     ws1 habitat    ;
        species_ai          = 'ai'          ws1 ai         ;
        species_idle_ai     = 'idle_ai'     ws1 idle_ai    ;
        species_move        = 'move'        ws1 move       ;
        species_range       = 'range'       ws1 number     %{ spe.range = toint(state.match); } ;
        species_attack      = 'attack'      ws1 damage_val %{ spe.attacks.add(dmgval); } ;
        species_defense     = 'defense'     ws1 damage_val %{ spe.defenses.add(dmgval); } ;

        species_stat = 'stat'
            ws1 tag  %{ tmp_tag = tag_t(state.match, tagmem); }
            ws1 real %{ spe.stats.stats[tmp_tag].val = toreal(state.match); } ;

        species_digging = 'digging' ws1 real %{ spe.digging = toreal(state.match); } ;

        species_clumpsize = 'clumpsize' ws1 mean_dev %{ spe.clumpsize = meandev; };

        species_companion = 'companion' %{ spe.companion.push_back(Species::companion_t()); }
            ws1 real   %{ spe.companion.back().chance = toreal(state.match); }
            ws1 tag    %{ spe.companion.back().tag = tag_t(state.match, tagmem); }
            ;

        species_drop = 'drop' %{ spe.drop.push_back(Species::drop_t()); }
            ws1 tag    %{ spe.drop.back().tag = tag_t(state.match, tagmem); }
            ws1 real   %{ spe.drop.back().chance = toreal(state.match); }
            ( ws1 tag  %{ spe.drop.back().damage_type = tag_t(state.match, tagmem); } )?
            ;

        species_drop_random = 'drop_random' %{ spe.drop.push_back(Species::drop_t()); }
            ws1 number %{ spe.drop.back().level = toint(state.match); }
            ws1 real   %{ spe.drop.back().chance = toreal(state.match); }
            ( ws1 tag  %{ spe.drop.back().damage_type = tag_t(state.match, tagmem); } )?
            ;

        species_cast_cloud = 'cast_cloud' %{ spe.cast_cloud.push_back(Species::cloud_t()); }
            ws1 real   %{ spe.cast_cloud.back().chance = toreal(state.match); }
            ws1 tag    %{ spe.cast_cloud.back().terraintag = tag_t(state.match, tagmem); }
            ws1 number %{ spe.cast_cloud.back().radius = toint(state.match); }
            ws1 number %{ spe.cast_cloud.back().turns = toint(state.match); }
            ws1 string %{ spe.cast_cloud.back().name = state.match; }
            ;

        species_summon = 'summon' %{ spe.summon.push_back(Species::summon_t()); }
            ws1 real   %{ spe.summon.back().chance = toreal(state.match); }
            ws1 tag    %{ spe.summon.back().speciestag = tag_t(state.match, tagmem); }
            ws1 number %{ spe.summon.back().turns = toint(state.match); }
            ws1 string %{ spe.summon.back().msg = state.match; }
            ;

        species_death_summon = 'death_summon' ws1 tag %{ spe.death_summon = tag_t(state.match, tagmem); } ;

        species_spawn = 'spawn' %{ spe.spawns.push_back(Species::spawn_t()); }
            ws1 real   %{ spe.spawns.back().chance = toreal(state.match); }
            ws1 number %{ spe.spawns.back().level = toint(state.match); }
            ws1 number %{ spe.spawns.back().turns = toint(state.match); }
            ws1 string %{ spe.spawns.back().msg = state.match; }
            ;

        species_blast = 'blast' %{ spe.blast.push_back(Species::blast_t()); }
            ws1 real %{ spe.blast.back().chance = toreal(state.match); }
            ws1 number %{ spe.blast.back().radius = toint(state.match); }
            ws1 number %{ spe.blast.back().range = toint(state.match); }
            ws1 number %{ spe.blast.back().turns = toint(state.match); }
            ws1 string %{ spe.blast.back().name = state.match; }
            (ws1 'attack' 
             ws1 damage_val 
             %{ spe.blast.back().attacks.add(dmgval); })+
            ;
        

        species_animal = 'animal' %{ spe.flags.animal = true; } ;
        species_undead = 'undead' %{ spe.flags.undead = true; } ;
        species_magic  = 'magic'  %{ spe.flags.magic = true; } ;
        species_plant  = 'plant'  %{ spe.flags.plant = true; } ;
        species_robot  = 'robot'  %{ spe.flags.robot = true; } ;
        species_cosmic = 'cosmic' %{ spe.flags.cosmic = true; } ;
        species_player = 'player' %{ spe.flags.player = true; } ;

        species_stealthy = 'stealthy' %{ spe.flags.stealthy = true; } ;

        species_terrain_immune = 'terrain_immune' %{ spe.flags.terrain_immune = true; } ;

        species_eyeless = 'eyeless' %{ spe.flags.eyeless = true; } ;

        species_trail = 'trail' 
            ws1 tag  %{ spe.trail.terrain = tag_t(state.match, tagmem); }
            ws1 tag  %{ spe.trail.stat = tag_t(state.match, tagmem); }
            ws1 mean_dev %{ spe.trail.cost = meandev; } 
            ;

        species_steal = 'steal' ws1 tag %{ spe.steal = tag_t(state.match, tagmem); } ;

        species_morph = 'morph' 
            ws1 tag  %{ spe.morph.species = tag_t(state.match, tagmem); }
            ws1 real %{ spe.morph.chance = toreal(state.match); }
            ;

        species_inc_stat = 'inc_stat'
            ws1 tag  %{ tmp_tag = tag_t(state.match, tagmem); }
            ws1 real %{ spe.inc_stat[tmp_tag] += toreal(state.match); };

        species_ally = 'ally' ws1 tag %{ spe.ally = tag_t(state.match, tagmem); };

        species_magic_cost = 'magic_cost'
            ws1 tag  %{ spe.magic_cost.stat = tag_t(state.match, tagmem); }
            ws1 real %{ spe.magic_cost.cost = toreal(state.match); };

        species_one_data = 
            (species_count | species_name | species_skin | species_habitat | species_ai |
            species_genus | species_descr | species_idle_ai | species_move | species_range | species_clumpsize |
            species_companion | species_attack | species_defense | species_drop | species_drop_random |
            species_cast_cloud | species_summon | species_death_summon | species_spawn | 
            species_animal | species_undead | species_magic | species_plant | species_magic_cost |
            species_robot | species_cosmic | species_terrain_immune | species_eyeless | species_player |
            species_stat | species_blast | species_true_level | species_trail | species_steal |
            species_morph | species_inc_stat | species_ally | species_stealthy | species_digging |
            '}'
            ${ fret; })
            ;

        one_species :=  (ws species_one_data ws ';')+
            ;

        species_level = number %{ spe.level = toint(state.match); }
        ;

        species_tag   = tag    %{ spe.tag = tag_t(state.match, tagmem); }
        ;

        species = 
            'species' %{ spe = Species(); }
            ws1 species_level ws1 species_tag ws
            '{' ${fcall one_species;} 
            %{ init_species(spe); }
            ;

        ####

        design_count      = 'count'      ws1 number     %{ des.count = toint(state.match); } ;
        design_bonus_a    = 'bonus_a'    ws1 number     %{ des.bonus_a_count = toint(state.match); } ;
        design_bonus_b    = 'bonus_b'    ws1 number     %{ des.bonus_b_count = toint(state.match); } ;
        design_name       = 'name'       ws1 string     %{ des.name = state.match; } ;
        design_skin       = 'skin'       ws1 skin       %{ des.skin.set(SKINS); };
        design_slot       = 'slot'       ws1 tag        %{ des.slot = tag_t(state.match, tagmem); } ;
        design_descr      = 'descr'      ws1 string     %{ des.descr = state.match; } ;
        design_attack     = 'attack'     ws1 damage_val %{ des.attacks.add(dmgval); } ;
        design_defense    = 'defense'    ws1 damage_val %{ des.defenses.add(dmgval); } ;
        design_stackrange = 'stackrange' ws1 number     %{ des.stackrange = toint(state.match); };
        design_usable     = 'usable'                    %{ des.usable = true; };
        design_melee      = 'melee'                     %{ des.melee = true; };
        design_throwrange = 'throwrange' ws1 number     %{ des.throwrange = toint(state.match); };
        design_lightradius = 'lightradius' ws1 number   %{ des.lightradius = toint(state.match); };
        design_digging    = 'digging' ws1 real          %{ des.digging = toreal(state.match); };
        design_descend    = 'descend' ws1 snumber       %{ des.descend = toint(state.match); };

        design_inc_stat = 'inc_stat' %{ des.inc_stat.push_back(Design::inc_stat_t()); }
            ws1 tag  %{ des.inc_stat.back().stat = tag_t(state.match, tagmem); }
            ws1 real %{ des.inc_stat.back().val = toreal(state.match); }
            (ws1 string %{ des.inc_stat.back().msg = state.match; })?
            ;

        design_inc_count = 'inc_count' %{ des.inc_count.push_back(Design::inc_count_t()); }
            ws1 tag %{ des.inc_count.back().stat = tag_t(state.match, tagmem); }
            ws1 snumber %{ des.inc_count.back().val = toint(state.match); }
            (ws1 string %{ des.inc_count.back().msg_a = state.match; }
             ws1 string %{ des.inc_count.back().msg_b = state.match; })?
             ;

        design_zero_stat = 'zero_stat' %{ des.zero_stat.push_back(Design::zero_stat_t()); }
            ws1 tag %{ des.zero_stat.back().stat = tag_t(state.match, tagmem); }
            (ws1 string %{ des.zero_stat.back().msg = state.match; })?
            ;

        design_use_for_free = 'use_for_free' %{ des.use_for_free = true; };
        design_destructible = 'destructible' %{ des.destructible = true; };

        design_count_is_only_one = 'count_is_only_one' %{ des.count_is_only_one = true; };

        design_safe_descend = 'safe_descend' ws1 snumber %{ des.safe_descend = toint(state.match); };

        design_blink      = 'blink' %{ des.flags.blink = true; };
        design_dowsing    = 'dowsing' %{ des.flags.dowsing = true; };

        design_blast      = 'blast' 
            ws1 number %{ des.blast.radius = toint(state.match); }
            ws1 number %{ des.blast.range = toint(state.match); }
            ;

        design_attack_level = 'attack_level' ws1 number %{ des.attack_level = toint(state.match); };

        design_cast_cloud = 'cast_cloud' 
            ws1 tag    %{ des.cast_cloud.terraintag = tag_t(state.match, tagmem); }
            ws1 number %{ des.cast_cloud.radius = toint(state.match); }
            ws1 number %{ des.cast_cloud.range = toint(state.match); }
            ;

        design_gencount = 'gencount' ws1 mean_dev %{ des.gencount = meandev; };

        design_worth = 'worth' ws1 real %{ des.worth = toreal(state.match); };

        design_is_lit = 'is_lit' %{ des.is_lit = true; };

        design_place_permafeat = 'place_permafeat' 
            ws1 tag %{ des.place_permafeat.feat = tag_t(state.match, tagmem); };

        design_place_permafloor_flag = 
            ('+walk' %{ des.place_permafeat.walk = 1; } ) |
            ('-walk' %{ des.place_permafeat.walk = 0; } ) |
            ('+water' %{ des.place_permafeat.water = 1; } ) |
            ('-water' %{ des.place_permafeat.water = 0; } );

        design_place_permafloor = 'place_permafloor'
            ws1 (ws design_place_permafloor_flag)*;

        design_tickstat_moon = 'tickstat_moon' %{ des.tickstat_moon.push_back(Design::tickstat_moon_t()); }
            ws1 tag  %{ des.tickstat_moon.back().stat = tag_t(state.match, tagmem); }
            ws1 real %{ des.tickstat_moon.back().height = toreal(state.match); }
            ws1 mean_dev %{ des.tickstat_moon.back().v = meandev; }
            ;

        design_tickstat = 'tickstat' %{ des.tickstat.push_back(Design::tickstat_t()); }
            ws1 tag %{ des.tickstat.back().stat = tag_t(state.match, tagmem); }
            ws1 real %{ des.tickstat.back().add = toreal(state.match); }
            ws1 real %{ des.tickstat.back().mul = toreal(state.match); }
            (ws1 'apply_count' %{ des.tickstat.back().apply_count = true; })?
            ;

        design_enable_spells = 'enable_spells' %{ des.flags.enable_spells = true; };
        design_random_spell  = 'random_spell'  %{ des.flags.random_spell = true; };

        design_grant_spell = 'grant_spell' %{ des.spells.push_back(Design::spell_t()); }
            ws1 tag    %{ des.spells.back().ca_tag = tag_t(state.match, tagmem); } 
            ws1 string %{ des.spells.back().name = state.match; } 
            ;

        design_count_is_rcode = 'count_is_rcode' 
            %{ des.count_is_rcode = true; des.count_is_only_one = true; }
            ;

        design_genocide = 'genocide' ws1 tag %{ des.genocide = tag_t(state.match, tagmem); };

        design_wish = 'wish' ws1 ('simple'  %{ des.wishing = Design::SIMPLE_WISH;  } |
                                  'special' %{ des.wishing = Design::SPECIAL_WISH; })
                       ;

        design_magic_mapping = 'magic_mapping' %{ des.magic_mapping = true; };

        design_heal_ailments  = 'heal_ailments'  %{ des.heal_ailments = true; };
        design_heal_polymorph = 'heal_polymorph' %{ des.heal_polymorph = true; };

        design_action_name = 'action_name' ws1 string %{ des.action_name = state.match; };

        design_flavor = 'flavor' ws1 tag %{ des.flavor = tag_t(state.match, tagmem); };

        design_take_summon = 'take_summon' 
            ws1 tag %{ des.take_summon.species = tag_t(state.match, tagmem); }
            ws1 number %{ des.take_summon.needs_count = toint(state.match); }
            ;

        design_forbid_wish = 'forbid_wish' %{ des.forbid_wish = true; };
        design_forbid_buy  = 'forbid_buy'  %{ des.forbid_buy = true; };

        design_change_count = 'change_count' ws1 snumber %{ des.change_count = toint(state.match); };

        design_starsign = 'starsign' 
            ws1 number %{ des.starsign.day = toint(state.match); }
            ws1 number %{ des.starsign.sign = toint(state.match); }
            ;

        design_summon = 'summon' 
            ws1 tag    %{ des.summon.species = tag_t(state.match, tagmem); }
            ws1 number %{ des.summon.count = toint(state.match); }
            ;

        design_polymorph = 'polymorph' 
            ws1 tag      %{ des.polymorph.species = tag_t(state.match, tagmem); }
            ws1 mean_dev %{ des.polymorph.turns = meandev; }
            ws1 string   %{ des.polymorph.msg = state.match; }
            ;

        design_fast = 'fast'
            ws1 number   %{ des.fast.slice = toint(state.match); }
            ws1 mean_dev %{ des.fast.turns = meandev; }
            ;

        design_monster_raised = 'monster_raised' ws1 tag %{ des.monster_raised = tag_t(state.match, tagmem); };
        design_raise_monsters = 'raise_monsters' ws1 tag %{ des.raise_monsters = tag_t(state.match, tagmem); };

        design_charm      = 'charm' 
            ws1 number %{ des.charm.range = toint(state.match); }
            ws1 string %{ des.charm.msg = state.match; }
            ;

        design_label_spot = 'label_spot' %{ des.label_spot = true; };

        design_lucky_free_apply = 'lucky_free_apply'
            ws1 tag  %{ des.lucky_free_apply.stat = tag_t(state.match, tagmem); }
            ws1 real %{ des.lucky_free_apply.factor = toreal(state.match); }
            ws1 real %{ des.lucky_free_apply.threshold = toreal(state.match); }
            ;

        design_one_data = 
            (design_count | design_bonus_a | design_bonus_b | design_name | design_skin | design_slot | design_descr | 
            design_attack | design_defense | design_stackrange | design_usable | design_destructible |
            design_throwrange | design_blast | design_attack_level | design_gencount | design_melee | 
            design_tickstat_moon | design_lightradius | design_digging | design_descend | design_blink | 
            design_cast_cloud | design_worth | design_safe_descend | design_is_lit | design_count_is_only_one |
            design_place_permafeat | design_place_permafloor | design_tickstat |
            design_dowsing | design_use_for_free |
            design_enable_spells | design_grant_spell | design_count_is_rcode |
            design_random_spell | design_genocide | design_wish | design_magic_mapping |
            design_action_name | design_flavor | design_take_summon |
            design_heal_ailments | design_heal_polymorph | design_forbid_buy |
            design_forbid_wish | design_change_count | design_inc_stat | design_inc_count | design_zero_stat |
            design_starsign | design_summon | design_polymorph | design_fast | design_lucky_free_apply |
            design_monster_raised | design_raise_monsters | design_charm | design_label_spot |
            '}'
            ${ fret; })
            ;
            
        one_design :=  (ws design_one_data ws ';')+
            ;

        design_level = number %{ des.level = toint(state.match); }
        ;

        design_tag   = tag    %{ des.tag = tag_t(state.match, tagmem); }
        ;

        design =
            'design' %{ des = Design(); }
            ws1 design_level ws1 design_tag ws
            '{' ${fcall one_design;}
            %{ init_design(des); }
            ;

        ####

        tplacement = 
            'floor'     %{ ter.placement = Terrain::placement_t::floor; }     | 
            'water'     %{ ter.placement = Terrain::placement_t::water; }     | 
            'corner'    %{ ter.placement = Terrain::placement_t::corner; }    |
            'shoreline' %{ ter.placement = Terrain::placement_t::shoreline; } |
            'lowlands'  %{ ter.placement = Terrain::placement_t::lowlands; }  ;

        terrain_tunnel   = 'tunnel' 
            ws1 snumber %{ ter.tunnel_x = toint(state.match); }
            ws1 snumber %{ ter.tunnel_y = toint(state.match); } 
            ;

        terrain_count     = 'count'     ws1 number     %{ ter.count = toint(state.match); } ;
        terrain_name      = 'name'      ws1 string     %{ ter.name = state.match; } ;
        terrain_descr     = 'descr'     ws1 string     %{ ter.descr = state.match; } ;
        terrain_skin      = 'skin'      ws1 skin       %{ ter.skin.set(SKINS); };
        terrain_placement = 'placement' ws1 tplacement  ;
        terrain_stairs    = 'stairs'    ws1 snumber    %{ ter.stairs = toint(state.match); } ;
        terrain_viewblock = 'viewblock'                %{ ter.viewblock = true; } ;
        terrain_walkblock = 'walkblock'                %{ ter.walkblock = true; } ;
        terrain_decay     = 'decay'     ws1 number     %{ ter.decay = toint(state.match); } ;
        terrain_attack    = 'attack'    ws1 damage_val %{ ter.attacks.add(dmgval); } ;
        terrain_sticky    = 'sticky'                   %{ ter.sticky = true; } ;
        terrain_charges   = 'charges'   ws1 number     %{ ter.charges = toint(state.match); } ;
        
        terrain_is_lit         = 'is_lit'         %{ ter.is_lit = true; } ;
        terrain_is_lightsource = 'is_lightsource' %{ ter.is_lightsource = true; } ;
        terrain_air            = 'air'            %{ ter.air = true; };

        terrain_safebox   = 'safebox' %{ ter.safebox = true; };

        terrain_attack_level = 'attack_level' ws1 number %{ ter.attack_level = toint(state.match); } ;

        terrain_victory_item = 'victory_item' ws1 tag %{ ter.victory_item = tag_t(state.match, tagmem); } ;

        terrain_grant_spell = 'grant_spell'
            ws1 tag    %{ ter.grant_spell.stat = tag_t(state.match, tagmem); }
            ws1 real   %{ ter.grant_spell.stat_min = toreal(state.match); }
            ws1 real   %{ ter.grant_spell.stat_max = toreal(state.match); }
            ws1 tag    %{ ter.grant_spell.ca_tag = tag_t(state.match, tagmem); } 
            ws1 real   %{ ter.grant_spell.timeout = toreal(state.match); }
            ws1 string %{ ter.grant_spell.name = state.match; } ;

        terrain_banking = 'banking' 
            ws1 real   %{ ter.banking.buy_margin = toreal(state.match); }
            ws1 real   %{ ter.banking.sell_margin = toreal(state.match); }
            ws1 tag    %{ ter.banking.bonus_stat = tag_t(state.match, tagmem); }
            ws1 real   %{ ter.banking.stat_bonus = toreal(state.match); }
            ws1 real   %{ ter.banking.money_curse = toreal(state.match); } 
            ws1 real   %{ ter.banking.gives_change = toreal(state.match); }
            ;

        terrain_uncharge_flag = ('attack' %{ ter.uncharge.attack = true; } ) |
                                ('use'    %{ ter.uncharge.use = true; }    ) |
                                ('move'   %{ ter.uncharge.move = true; }   ) |
                                ('bump'   %{ ter.uncharge.bump = true; }   ) |
                                ('sensor' %{ ter.uncharge.sensor = true; } ) ;

        terrain_uncharge = 'uncharge' ws1 (ws terrain_uncharge_flag)* ;

        terrain_crafting = 'crafting' %{ ter.crafting.push_back(Terrain::craft_t()); }
            ws1 tag     %{ ter.crafting.back().from = tag_t(state.match, tagmem); }
            ws1 tag     %{ ter.crafting.back().to = tag_t(state.match, tagmem); }
            ws1 string  %{ ter.crafting.back().msg = state.match; }
            ;

        terrain_wish = 'wish' ws1 ('simple'  %{ ter.wishing = Terrain::SIMPLE_WISH;  } |
                                   'special' %{ ter.wishing = Terrain::SPECIAL_WISH; })
                       ;

        terrain_important = 'important' %{ ter.important = true; } ;

        terrain_view_radius = 'view_radius' ws1 number %{ ter.view_radius = toint(state.match); } ;

        terrain_sensor_toggle = 'sensor_toggle' 
            ws1 tag %{ tmp_tag = tag_t(state.match, tagmem); }
            ws1 tag %{ ter.sensor_toggle[tmp_tag] = tag_t(state.match, tagmem); }
            ;

        terrain_inc_stat = 'inc_stat' %{ ter.inc_stat.push_back(Terrain::inc_stat_t()); }
            ws1 tag  %{ ter.inc_stat.back().stat = tag_t(state.match, tagmem); }
            ws1 real %{ ter.inc_stat.back().val = toreal(state.match); }
            (ws1 string %{ ter.inc_stat.back().msg = state.match; })?
            ;

        terrain_preserve = 'preserve' %{ ter.preserve = true; } ;

        terrain_message = 'message' ws1 string %{ ter.message = state.match; } ;

        terrain_player_attack = 'player_attack' %{ ter.player_attack = true; } ;

        terrain_one_data =
            (terrain_count | terrain_name | terrain_skin | terrain_placement | terrain_descr |
            terrain_stairs | terrain_tunnel | terrain_viewblock | terrain_walkblock |
            terrain_decay | terrain_attack | terrain_attack_level | terrain_sticky |
            terrain_charges | terrain_grant_spell | terrain_is_lit | terrain_is_lightsource | terrain_air |
            terrain_victory_item | terrain_safebox | terrain_banking | terrain_player_attack |
            terrain_uncharge | terrain_crafting | terrain_wish | terrain_important | terrain_inc_stat |
            terrain_view_radius | terrain_sensor_toggle | terrain_preserve | terrain_message |
            '}' 
            ${ fret; })
            ;

        one_terrain := (ws terrain_one_data ws ';')+
            ;

        terrain_tag = tag %{ ter.tag = tag_t(state.match, tagmem); }
        ;

        terrain = 
            'terrain' %{ ter = Terrain(); }
            ws1 terrain_tag ws
            '{' ${fcall one_terrain;}
            %{ init_terrain(ter); }
            ;

        ####

        vplacement = 
            'floor'     %{ vau.placement = Vault::placement_t::floor; }     | 
            'water'     %{ vau.placement = Vault::placement_t::water; }     | 
            'corner'    %{ vau.placement = Vault::placement_t::corner; }    |
            'shoreline' %{ vau.placement = Vault::placement_t::shoreline; } |
            'lowlands'  %{ vau.placement = Vault::placement_t::lowlands; }  |
            'packing'   %{ vau.placement = Vault::placement_t::packing; }   ;

        vault_count     = 'count'     ws1 number     %{ vau.count = toint(state.match); } ;
        vault_placement = 'placement' ws1 vplacement  ;

        vault_anchor    = 'anchor'    
            ws1 number %{ vau.ax = toint(state.match); } 
            ws1 number %{ vau.ay = toint(state.match); }
            ;

        vault_set_player = 'set_player'    
            ws1 number %{ vau.px = toint(state.match); } 
            ws1 number %{ vau.py = toint(state.match); }
            ;      

        vault_brush_terrain = 
            ('-' %{ vbrush.terrain = tag_t(); } |
             tag %{ vbrush.terrain = tag_t(state.match, tagmem); });

        vault_brush_design = 
            ('-'         %{ vbrush.design.type = Vault::brush::design_t::type_t::NONE; } |
             'specific'  %{ vbrush.design.type = Vault::brush::design_t::type_t::SPECIFIC; }
               ws '(' ws tag %{ vbrush.design.tag = tag_t(state.match, tagmem); } ws ')' |
             'level'     %{ vbrush.design.type = Vault::brush::design_t::type_t::LEVEL; }
               ws '(' ws number %{ vbrush.design.level = toint(state.match); } ws ')'    |
             'level_any' %{ vbrush.design.type = Vault::brush::design_t::type_t::LEVEL_ANY; }
               ws '(' ws number %{ vbrush.design.level = toint(state.match); } ws ')');

        vault_brush_species =
            ('-'        %{ vbrush.species.type = Vault::brush::species_t::type_t::NONE; }  |
             'specific' %{ vbrush.species.type = Vault::brush::species_t::type_t::SPECIFIC; }
               ws '(' ws tag %{ vbrush.species.tag = tag_t(state.match, tagmem); } ws ')'  |
             'level'    %{ vbrush.species.type = Vault::brush::species_t::type_t::LEVEL; }
               ws '(' ws number %{ vbrush.species.level = toint(state.match); } ws ')'     |
             'genus'    %{ vbrush.species.type = Vault::brush::species_t::type_t::GENUS; } 
               ws '(' ws tag     %{ vbrush.species.tag = tag_t(state.match, tagmem); }
                      ws1 number %{ vbrush.species.level = toint(state.match); } ws ')');

        vault_brush = 'brush' %{ vbrush = Vault::brush(); }
            ws1 ('blank' ${ vbrush.is_blank = true; } |
                 'floor' ${ vbrush.is_walk = true; vbrush.is_water = false;  } |
                 'water' ${ vbrush.is_walk = true; vbrush.is_water = true;   } |
                 'wall'  ${ vbrush.is_walk = false; vbrush.is_water = false; } |
                 'wwall' ${ vbrush.is_walk = false; vbrush.is_water = true;  })
            ws1 vault_brush_terrain
            ws1 vault_brush_design
            ws1 vault_brush_species
            ws1 '\'' any ${ vau.brushes[fc] = vbrush; } '\''
            ;

        vault_line = 'l' ws1 string %{ vau.pic.push_back(state.match); } ;

        vault_cloud = 'cloud' ws1 number %{ vau.cloud.n = toint(state.match); }
                      ws1 mean_dev %{ vau.cloud.distrib = meandev; }
                      (ws1 '\'' any ${ vau.cloud.brushes.push_back(fc); } '\''
                       ws1 real %{ vau.cloud.chances.push_back(toreal(state.match)); } )+
                      ;

        vbplacement = 
            'floor'     %{ vau.blob.placement = Vault::placement_t::floor; }     | 
            'water'     %{ vau.blob.placement = Vault::placement_t::water; }     | 
            'corner'    %{ vau.blob.placement = Vault::placement_t::corner; }    |
            'shoreline' %{ vau.blob.placement = Vault::placement_t::shoreline; } |
            'lowlands'  %{ vau.blob.placement = Vault::placement_t::lowlands; }  ;

        vault_blob = 'blob' ws1 number %{ vau.blob.n = toint(state.match); }
                      ws1 vbplacement
                      ws1 '\'' any ${ vau.blob.brush = fc; } '\''
                      ;

        vault_river = 'river' ws1 number %{ vau.river.n = toint(state.match); }
                      ws1 mean_dev %{ vau.river.angle = meandev; }
                      ws1 mean_dev %{ vau.river.width = meandev; }
                      ws1 number %{ vau.river.splitchance = toint(state.match); }
                      ws1 '\'' any ${ vau.river.brush = fc; } '\''
                      ;

        vault_room = 'room'
                     ws1 number %{ vau.room.w1 = toint(state.match); }
                     ws1 number %{ vau.room.w2 = toint(state.match); }
                     ws1 number %{ vau.room.h1 = toint(state.match); }
                     ws1 number %{ vau.room.h2 = toint(state.match); }
                     ws1 '\'' any ${ vau.room.brush = fc; } '\''
                     ;

        vault_tunnel = 'tunnel' %{ vau.tunnel.enabled = true; }
                       ws1 '\'' any ${ vau.tunnel.plain_brush = fc; } '\''
                       ws1 '\'' any ${ vau.tunnel.b_brush = fc; } '\''
                       ws1 '\'' any ${ vau.tunnel.a_brush = fc; } '\''
                       ;

        vault_inherit = 'inherit' ws1 tag %{ vau.inherit = tag_t(state.match, tagmem); };

        vault_transpose = 'transpose' %{ vau.transpose = true; };

        vault_priority = 'priority' ws1 number %{ vau.priority = toint(state.match); };
      
        vault_use_species_counts = 'use_monster_counts' %{ vau.use_species_counts = true; };

        vault_width  = 'width'  ws1 number %{ vau.w = toint(state.match); };
        vault_height = 'height' ws1 number %{ vau.h = toint(state.match); };

        vault_fixed = 'fixed' %{ vau.type = Vault::type_t::FIXED; };
        vault_semirandom = 'semirandom' %{ vau.type = Vault::type_t::SEMIRANDOM; };
        vault_random = 'random' %{ vau.type = Vault::type_t::RANDOM; };

        vault_one_data =
            (vault_count | vault_placement | vault_anchor | vault_brush | vault_line |
            vault_inherit | vault_transpose | vault_priority | vault_set_player |
            vault_use_species_counts | vault_fixed | vault_semirandom | vault_random |
            vault_cloud | vault_width | vault_height | vault_blob | vault_river |
            vault_room | vault_tunnel | '}'
             ${ fret; })
            ;

        one_vault := (ws vault_one_data ws ';')+
            ;

        vault_level = number %{ vau.level = toint(state.match); }
        ;

        vault_tag = tag %{ vau.tag = tag_t(state.match, tagmem); }
        ;

        vault = 
            'vault' %{ vau = Vault(); }
            ws1 vault_level ws1 vault_tag ws
            '{' ${fcall one_vault;}
            %{ vau.postprocess(); init_vault(vau); }
            ;

        ####

        celauto_s = 's' ws1 bitmask %{ cel.survive = bitmask_v; };

        celauto_b = 'b' ws1 bitmask %{ cel.born = bitmask_v; };

        celauto_a = 'a' ws1 number %{ cel.age = toint(state.match); } ;

        celauto_terrain = 'terrain' ws1 tag %{ cel.terrain = tag_t(state.match, tagmem); } ;

        celauto_is_walk   = 'is_walk'   %{ cel.is_walk = true; } ;
        celauto_make_walk = 'make_walk' %{ cel.make_walk = true; } ;

        celauto_karma_scale = 'karma_scale' ws1 real %{ cel.karma_scale = toreal(state.match); } ;
        celauto_karma_step  = 'karma_step'  ws1 real %{ cel.karma_step  = toreal(state.match); } ;

        celauto_seed = 'seed'      %{ cel.seed.push_back(std::make_pair(0,0)); }
                       ws1 snumber %{ cel.seed.back().first = toint(state.match); }
                       ws1 snumber %{ cel.seed.back().second = toint(state.match); }
                       ; 

        celauto_debug_name = 'debug_name' ws1 string %{ cel.debug_name = state.match; } ;

        celauto_one_data =
            (celauto_s | celauto_b | celauto_a | celauto_terrain |
            celauto_is_walk | celauto_make_walk | celauto_karma_scale | 
            celauto_karma_step | celauto_seed | celauto_debug_name |
            '}' ${ fret; })
            ;

        one_celauto := (ws celauto_one_data ws ';')+
            ;

        celauto_tag = tag %{ cel.tag = tag_t(state.match, tagmem); }
        ;

        celauto = 
            'celauto' %{ cel = CelAuto(); }
            ws1 celauto_tag ws
            '{' ${fcall one_celauto;}
            %{ init_celauto(cel); }
            ;

        ####

        levelskin_deep_water    = 'deep_water'    ws1 skin   %{ lev.deep_water.set(SKINS); };
        levelskin_shallow_water = 'shallow_water' ws1 skin   %{ lev.shallow_water.set(SKINS); };
        levelskin_wall          = 'wall'          ws1 skin   %{ lev.wall.set(SKINS); };
        levelskin_water_wall    = 'water_wall'    ws1 skin   %{ lev.water_wall.set(SKINS); };
        levelskin_floor1        = 'floor1'        ws1 skin   %{ lev.floor1.set(SKINS); };
        levelskin_floor2        = 'floor2'        ws1 skin   %{ lev.floor2.set(SKINS); };
        levelskin_floor3        = 'floor3'        ws1 skin   %{ lev.floor3.set(SKINS); };
        levelskin_floor4        = 'floor4'        ws1 skin   %{ lev.floor4.set(SKINS); };
        levelskin_floor5        = 'floor5'        ws1 skin   %{ lev.floor5.set(SKINS); };
        levelskin_floor6        = 'floor6'        ws1 skin   %{ lev.floor6.set(SKINS); };
        levelskin_floor7        = 'floor7'        ws1 skin   %{ lev.floor7.set(SKINS); };
        levelskin_floor8        = 'floor8'        ws1 skin   %{ lev.floor8.set(SKINS); };
        levelskin_lightradius   = 'lightradius'   ws1 number %{ lev.lightradius = toint(state.match); };
        levelskin_lightradius_max = 'lightradius_max' ws1 number %{ lev.lightradius_max = toint(state.match); };
        levelskin_ailment       = 'ailment'       ws1 tag    %{ lev.ailment = tag_t(state.match, tagmem); };

        levelskin_exclusive_monsters = 'exclusive_monsters' %{ lev.exclusive_monsters = true; };
        levelskin_exclusive_items    = 'exclusive_items'    %{ lev.exclusive_items = true; };

        levelskin_no_phase_level = 'no_phase_level' %{ lev.no_phase_level = true; };

        levelskin_species_level = 'species_level' ws1 number %{ lev.species_level = toint(state.match); };
        levelskin_designs_level = 'designs_level' ws1 number %{ lev.designs_level = toint(state.match); };
        levelskin_vaults_level  = 'vaults_level'  ws1 number %{ lev.vaults_level  = toint(state.match); };

        levelskin_number_fixed_vaults = 'number_fixed_vaults' ws1 number
            %{ lev.number_fixed_vaults = toint(state.match); };

        levelskin_number_semirandom_vaults = 'number_semirandom_vaults' ws1 number 
            %{ lev.number_semirandom_vaults = toint(state.match); };

        levelskin_number_random_vaults = 'number_random_vaults' ws1 number 
            %{ lev.number_random_vaults = toint(state.match); };

        levelskin_number_monsters = 'number_monsters' ws1 mean_dev %{ lev.number_monsters = meandev; };

        levelskin_number_items = 'number_items' ws1 mean_dev %{ lev.number_items = meandev; };

        levelskin_number_features = 'number_features' ws1 mean_dev %{ lev.number_features = meandev; };

        levelskin_name          = 'name'          ws1 string %{ lev.name = state.match; };

        levelskin_treasure_level = 'treasure_level' ws1 real %{ lev.has_treasure = true; lev.treasure_level = toreal(state.match); };

        levelskin_flow_epsilon           = 'flow_epsilon'        ws1 real   %{ lev.genparams.flow_epsilon = toreal(state.match); };
        levelskin_flow_n_freq            = 'flow_n_freq'         ws1 number %{ lev.genparams.flow_n_freq = toint(state.match); };
        levelskin_flow_volume            = 'flow_volume'         ws1 real   %{ lev.genparams.flow_volume = toreal(state.match); };
        levelskin_flow_erosion           = 'flow_erosion'        ws1 real   %{ lev.genparams.flow_erosion = toreal(state.match); };
        levelskin_flow_renorm_freq       = 'flow_renorm_freq'    ws1 number %{ lev.genparams.flow_renorm_freq = toint(state.match); };
        levelskin_flow_renorm_scale      = 'flow_renorm_scale'   ws1 real   %{ lev.genparams.flow_renorm_scale = toreal(state.match); }; 
        levelskin_walk_threshold         = 'walk_threshold'      ws1 real   %{ lev.genparams.walk_threshold = toreal(state.match); };
        levelskin_lowlands_threshold     = 'lowlands_threshold'  ws1 number %{ lev.genparams.lowlands_threshold = toint(state.match); };
        levelskin_water_quantile_mean    = 'water_quantile_mean' ws1 real   %{ lev.genparams.water_quantile_mean = toreal(state.match); };
        levelskin_water_quantile_dev     = 'water_quantile_dev'  ws1 real   %{ lev.genparams.water_quantile_dev = toreal(state.match); };
        levelskin_flatten_walk_ng        = 'flatten_walk_ng'     ws1 bitmask %{ lev.genparams.flatten_walk_ng = bitmask_v; };
        levelskin_flatten_water_ng       = 'flatten_water_ng'    ws1 bitmask %{ lev.genparams.flatten_water_ng = bitmask_v; };
        levelskin_unflow_ng              = 'unflow_ng'           ws1 bitmask %{ lev.genparams.unflow_ng = bitmask_v; };
        levelskin_karma_mean             = 'karma_mean'          ws1 real   %{ lev.genparams.karma_mean = toreal(state.match); };
        levelskin_karma_dev              = 'karma_dev'           ws1 real   %{ lev.genparams.karma_dev = toreal(state.match); };
        levelskin_nflatten_walk          = 'nflatten_walk'       ws1 number %{ lev.genparams.nflatten_walk = toint(state.match); };
        levelskin_nflatten_water         = 'nflatten_water'      ws1 number %{ lev.genparams.nflatten_water = toint(state.match); };
        levelskin_nunflow                = 'nunflow'             ws1 number %{ lev.genparams.nunflow = toint(state.match); };

        levelskin_one_data =
            (levelskin_deep_water | levelskin_shallow_water | levelskin_wall | 
            levelskin_water_wall | levelskin_floor1 | levelskin_floor2 |
            levelskin_floor3 | levelskin_floor4 | levelskin_floor5 |
            levelskin_floor6 | levelskin_floor7 | levelskin_floor8 |
            levelskin_lightradius | levelskin_lightradius_max | levelskin_ailment |
            levelskin_exclusive_monsters | levelskin_exclusive_items | levelskin_no_phase_level |
            levelskin_species_level | levelskin_designs_level | levelskin_vaults_level |
            levelskin_number_fixed_vaults | levelskin_number_semirandom_vaults | levelskin_number_random_vaults |
            levelskin_number_monsters | 
            levelskin_number_items | levelskin_number_features | levelskin_name | levelskin_treasure_level |
            levelskin_flow_epsilon | levelskin_flow_n_freq | levelskin_flow_volume |
            levelskin_flow_erosion | levelskin_flow_renorm_freq | levelskin_flow_renorm_scale |
            levelskin_walk_threshold | levelskin_lowlands_threshold | levelskin_water_quantile_mean |
            levelskin_water_quantile_dev | levelskin_flatten_walk_ng | levelskin_flatten_water_ng |
            levelskin_unflow_ng | levelskin_karma_mean | levelskin_karma_dev |
            levelskin_nflatten_walk | levelskin_nflatten_water | levelskin_nunflow |
            '}' 
            ${ fret; })
            ;

        one_levelskin := (ws levelskin_one_data ws ';')+
            ;

        levelskin_level = snumber %{ lev.level = toint(state.match); } 
        ;

        levelskin =
            'levelskin' %{ lev = Levelskin(); }
            ws1 levelskin_level ws
            '{' ${fcall one_levelskin;}
            %{ init_levelskin_(lev); }
            ;

        ####

        constant_max_permafeats = 'max_permafeats' ws1 number %{ __constants__().max_permafeats = toint(state.match); };
        constant_max_bones      = 'max_bones'      ws1 number %{ __constants__().max_bones = toint(state.match); };

        constant_starvation_damage = 'starvation_damage' 
            ws1 real %{ __constants__().starvation_damage = toreal(state.match); };

        constant_grave     = 'grave'     ws1 tag  %{ __constants__().grave = tag_t(state.match, tagmem); };
        constant_pit       = 'pit'       ws1 tag  %{ __constants__().pit = tag_t(state.match, tagmem); };
        constant_bad_grave = 'bad_grave' ws1 tag  %{ __constants__().bad_grave = tag_t(state.match, tagmem); };
        constant_ghost     = 'ghost'     ws1 tag  %{ __constants__().ghost = tag_t(state.match, tagmem); };

        constant_money     = 'money'     
             (ws1 tag  %{ __constants__().money.insert(tag_t(state.match, tagmem)); } )+ ;

        constant_unique_item = 'unique_item' ws1 tag %{ __constants__().unique_item = tag_t(state.match, tagmem); };

        constant_uniques_timeout = 'uniques_timeout' ws1 number %{ __constants__().uniques_timeout = toint(state.match); };

        constant_player_species = 'player_species' ws1 tag %{ __constants__().player_species = tag_t(state.match, tagmem); } ;

        constant_min_money_value = 'min_money_value'
            ws1 real %{ __constants__().min_money_value = toreal(state.match); };

        constant_max_celauto_cells = 'max_celauto_cells'
            ws1 number %{ __constants__().max_celauto_cells = toint(state.match); };

        constant_slot = 'slot' %{ __constants__().slots.push_back(ConstantsBank::slot_t()); }
            ws1 tag      %{ __constants__().slots.back().slot = tag_t(state.match, tagmem); }
            ws1 '\'' any ${ __constants__().slots.back().letter = fc; } '\''
            ws1 string   %{ __constants__().slots.back().label = state.match; }
            ws1 string   %{ __constants__().slots.back().name = state.match; }
            ;

        constant_money_slot = 'money_slot' ws1 tag %{ __constants__().money_slot = tag_t(state.match, tagmem); };

        constant_shortcut_messages = 'shortcut' ws1 'messages'
            ws1 '\'' any ${ shortcut_key = fc; } '\''
            ws1 string %{ __constants__().shortcuts[shortcut_key].help_message = state.match; }
            ws1 string %{ __constants__().shortcuts[shortcut_key].fail_message = state.match; }
            ;

        constant_shortcut_action = 'shortcut' ws1 'action'
            ws1 '\'' any ${ shortcut_key = fc; } '\''
            ws1 tag      ${ __constants__().shortcuts[shortcut_key].slot_keypress.
                                            push_back(std::make_pair(tag_t(state.match, tagmem), 0)); } 
            ws1 '\'' any ${ __constants__().shortcuts[shortcut_key].slot_keypress.back().second = fc; } '\''
            ;

        constant_genus = 'genus' (
            ws1 tag %{ genus_tag = tag_t(state.match, tagmem); }
            ws1 string %{ __constants__().genus_names[genus_tag] = state.match; }
            )+
            ;

        constant_flavor = 'flavor' (
            ws1 tag %{ flavor_tag = tag_t(state.match, tagmem); }
            ws1 real %{ __constants__().flavor_moon_frequency[flavor_tag].height = toreal(state.match); }
            ws1 mean_dev %{ __constants__().flavor_moon_frequency[flavor_tag].curve = meandev; }
            )+
            ;

        constant_achievement_trigger_rate = 'achievement_trigger_rate' 
            ws1 number %{ __constants__().achievement_trigger_rate = toint(state.match); } ;

        constant_treasure_chance = 'treasure_chance'
            ws1 mean_dev %{ __constants__().treasure_chance = meandev; } 
        ;

        constant_max_ailments = 'max_ailments' ws1 number %{ __constants__().max_ailments = toint(state.match); };

        constant_monetary_supply_base = 'monetary_supply_base'
            ws1 real %{ __constants__().monetary_supply_base = toreal(state.match); }
        ;

        constant_player_level_cap = 'player_level_cap' 
            ws1 number %{ __constants__().player_level_cap = toint(state.match); }
        ;

        constant_bonus_a_items = 'bonus_a_items' 
            ws1 mean_dev %{ __constants__().bonus_a_items = meandev; } 
        ;

        constant_bonus_b_items = 'bonus_b_items' 
            ws1 mean_dev %{ __constants__().bonus_b_items = meandev; } 
        ;

        constant_starsigns = 'starsigns'
            ws1 number %{ __constants__().starsigns.zero = toint(state.match); }
            ws1 number %{ __constants__().starsigns.nday = toint(state.match); }
            ws1 number %{ __constants__().starsigns.nsign = toint(state.match); }
            ( ws1 number %{ starsign_n = toint(state.match); }
              ws1 string %{ __constants__().starsigns.names[starsign_n] = state.match; } )+
            ;

        constant_ai_radius = 'ai_radius' ws1 number %{ __constants__().ai_radius = toint(state.match); };

        constant_hud_stats_order = 'hud_stats' (
            ws1 tag %{ __constants__().hud_stats_order.push_back(tag_t(state.match, tagmem)); }
            )+ ;

        constant_hud_counts_order = 'hud_counts' (
            ws1 tag %{ __constants__().hud_counts_order.push_back(tag_t(state.match, tagmem)); }
            )+ ;

        constant_luck_stat = 'luck_stat'
            ws1 tag  %{ __constants__().luck.stat = tag_t(state.match, tagmem); }
            ws1 real %{ __constants__().luck.factor = toreal(state.match); }
            ws1 real %{ __constants__().luck.threshold = toreal(state.match); }
            ;

        constant_rest_count = 'rest_count' ws1 tag %{ __constants__().rest_count = tag_t(state.match, tagmem); };
        constant_digging_count = 'digging_count' ws1 tag %{ __constants__().digging_count = tag_t(state.match, tagmem); };

        one_constant = constant_max_permafeats | constant_max_bones |
                       constant_starvation_damage |
                       constant_grave | constant_money | constant_pit | 
                       constant_bad_grave | constant_ghost | constant_rest_count |
                       constant_slot | constant_player_species |
                       constant_shortcut_messages | constant_shortcut_action | 
                       constant_genus | constant_flavor | constant_unique_item | constant_uniques_timeout |
                       constant_min_money_value | constant_max_celauto_cells |
                       constant_achievement_trigger_rate | 
                       constant_treasure_chance | constant_digging_count |
                       constant_monetary_supply_base | constant_money_slot | constant_player_level_cap |
                       constant_bonus_a_items | constant_bonus_b_items | constant_max_ailments | constant_luck_stat |
                       constant_starsigns | constant_ai_radius | constant_hud_stats_order | constant_hud_counts_order
                       ;

        constant = 'constant' ws1 one_constant ws ';';

        ####

        ui_syms_circle  = 'circle'  ws1 skin %{ ui_syms->circle.set(SKINS); };
        ui_syms_fill    = 'fill'    ws1 skin %{ ui_syms->fill.set(SKINS); };
        ui_syms_line    = 'line'    ws1 skin %{ ui_syms->line.set(SKINS); };
        ui_syms_box_v   = 'box_v'   ws1 skin %{ ui_syms->box_v.set(SKINS); };
        ui_syms_box_h   = 'box_h'   ws1 skin %{ ui_syms->box_h.set(SKINS); };
        ui_syms_box_rd  = 'box_rd'  ws1 skin %{ ui_syms->box_rd.set(SKINS); };
        ui_syms_box_ru  = 'box_ru'  ws1 skin %{ ui_syms->box_ru.set(SKINS); };
        ui_syms_box_ld  = 'box_ld'  ws1 skin %{ ui_syms->box_ld.set(SKINS); };
        ui_syms_box_lu  = 'box_lu'  ws1 skin %{ ui_syms->box_lu.set(SKINS); };
        ui_syms_arrow_l = 'arrow_l' ws1 skin %{ ui_syms->arrow_l.set(SKINS); };
        ui_syms_arrow_r = 'arrow_r' ws1 skin %{ ui_syms->arrow_r.set(SKINS); };
        ui_syms_arrow_u = 'arrow_u' ws1 skin %{ ui_syms->arrow_u.set(SKINS); };
        ui_syms_arrow_d = 'arrow_d' ws1 skin %{ ui_syms->arrow_d.set(SKINS); };
        ui_syms_wspace  = 'wspace'  ws1 skin %{ ui_syms->wspace.set(SKINS); };

        ui_syms_one_sym = ui_syms_circle | ui_syms_fill | ui_syms_line | ui_syms_box_v | ui_syms_box_h |
                          ui_syms_box_rd | ui_syms_box_ru | ui_syms_box_ld | ui_syms_box_lu | 
                          ui_syms_arrow_l | ui_syms_arrow_r | ui_syms_arrow_u | ui_syms_arrow_d |
                          ui_syms_wspace;

        ui_syms = 'ui_syms' ws
            %{ __constants__().ui_symbols.push_back(ui_symbols_t()); 
               ui_syms = &(__constants__().ui_symbols.back()); }
            '{'
            ( ws ui_syms_one_sym ws ';')+
            ws '}'
            ;

        ####

        achievement_genus = 'genus' ws1 tag 
                            %{ __constants__().achievements[ach_tag].genus = tag_t(state.match, tagmem); } ;

        achievement_kills = 'kills' ws1 number 
                            %{ __constants__().achievements[ach_tag].kills = toint(state.match); } ;

        achievement_priority = 'priority' ws1 number 
                            %{ __constants__().achievements[ach_tag].priority = toint(state.match); } ;

        achievement_label = 'label' ws1 string 
                            %{ __constants__().achievements[ach_tag].label = state.match; } ;

        achievement_summon = 'summon' ws1 tag 
                            %{ __constants__().achievements[ach_tag].summon = tag_t(state.match, tagmem); } ;

        achievement_line = 
            achievement_genus | achievement_kills | achievement_priority | achievement_label |
            achievement_summon
            ;

        achievement = 'achievement' 
            ws1 tag    %{ ach_tag = tag_t(state.match, tagmem); }
            ws '{'
            ( ws achievement_line ws ';')+
            ws '}'
            ;

        ####

        ailment_attack = 'attack' ws1 damage_val %{ ail.attacks.add(dmgval); } ;

        ailment_attack_level = 'attack_level' ws1 number  %{ ail.level = toint(state.match); } ;

        ailment_name = 'name' ws1 string %{ ail.name = state.match; } ;

        ailment_triggers = 'triggers' ws1 number %{ ail.triggers = toint(state.match); } ;

        ailment_oneshot = 'oneshot' %{ ail.oneshot = true; } ;

        ailment_inc_stat = 'inc_stat'
            ws1 tag  %{ tmp_tag = tag_t(state.match, tagmem); }
            ws1 real %{ ail.inc_stat[tmp_tag] += toreal(state.match); };

        ailment_line = 
            ailment_attack | ailment_attack_level | ailment_name | ailment_triggers | ailment_oneshot |
            ailment_inc_stat ;

        ailment = 'ailment' 
            ws1 tag    %{ ail_tag = tag_t(state.match, tagmem); ail = ConstantsBank::ailment_t(); }
            ws '{'
            ( ws ailment_line ws ';')+
            ws '}' %{ __constants__().ailments[ail_tag] = ail; }
            ;

        ####

        damage_name = 'name' ws1 string %{ dam.name = state.match; } ;

        damage_inc_counts = 'inc_count' %{ dam.inc_counts.resize(dam.inc_counts.size() + 1); }
            ws1 tag %{ dam.inc_counts.back().first = tag_t(state.match, tagmem); }
            ws1 snumber %{ dam.inc_counts.back().second.scale = toint(state.match); }
            ws1 snumber %{ dam.inc_counts.back().second.offset = toint(state.match); }
            ;

        damage_dec_stat = 'dec_stat' ws1 tag %{ dam.dec_stats.push_back(tag_t(state.match, tagmem)); };

        damage_inc_stat = 'inc_stat' ws1 tag %{ dam.inc_stats.push_back(tag_t(state.match, tagmem)); };

        damage_transfer_stat = 'transfer_stat' ws1 tag %{ dam.transfer_stats.push_back(tag_t(state.match, tagmem)); };

        damage_threshold = 'threshold' ws1 real %{ dam.threshold = toreal(state.match); } ;

        damage_levelup_threshold = 'levelup_threshold' ws1 real %{ dam.levelup_threshold = toreal(state.match); };

        damage_visible_damage = 'visible_damage' %{ dam.visible_damage = true; };

        damage_karmic_scale = 'karmic_scale' %{ dam.karmic_scale.resize(dam.karmic_scale.size() + 1); }
            ws1 tag  %{ dam.karmic_scale.back().first = tag_t(state.match, tagmem); }
            ws1 real %{ dam.karmic_scale.back().second = toreal(state.match); }
            ;

        damage_polymorph    = 'polymorph' ws1 tag %{ dam.polymorph = tag_t(state.match, tagmem); } ;        

        damage_player_poly = 'player_poly' 
            ws1 snumber %{ dam.player_poly.scale = toint(state.match); }
            ws1 snumber %{ dam.player_poly.offset = toint(state.match); } ;

        damage_infect = 'infect'
            ws1 tag %{ dam.infect.first = tag_t(state.match, tagmem); }
            ws1 tag %{ dam.infect.second = tag_t(state.match, tagmem); } ;

        damage_ally   = 'ally'   ws1 tag %{ dam.ally = tag_t(state.match, tagmem); };

        damage_eyeless = 'eyeless' ws (('+' %{ dam.flags.eyeless.v = 1; }) | ('-' %{ dam.flags.eyeless.v = 0; }));
        damage_undead  = 'undead'  ws (('+' %{ dam.flags.undead.v = 1; })  | ('-' %{ dam.flags.undead.v = 0; }));
        damage_animal  = 'animal'  ws (('+' %{ dam.flags.animal.v = 1; })  | ('-' %{ dam.flags.animal.v = 0; }));
        damage_plant   = 'plant'   ws (('+' %{ dam.flags.plant.v = 1; })   | ('-' %{ dam.flags.plant.v = 0; }));
        damage_robot   = 'robot'   ws (('+' %{ dam.flags.robot.v = 1; })   | ('-' %{ dam.flags.robot.v = 0; }));
        damage_cosmic  = 'cosmic'  ws (('+' %{ dam.flags.cosmic.v = 1; })  | ('-' %{ dam.flags.cosmic.v = 0; }));
        damage_magic   = 'magic'   ws (('+' %{ dam.flags.magic.v = 1; })   | ('-' %{ dam.flags.magic.v = 0; }));
        damage_player  = 'player'  ws (('+' %{ dam.flags.player.v = 1; })  | ('-' %{ dam.flags.player.v = 0; }));

        damage_melee_msg = 
            'melee_msg' ws1 string %{ dam.melee_msg.str = state.match; }
            (ws '!' %{ dam.melee_msg.important = true; })?
            ;

        damage_env_msg = 
            'env_msg' ws1 string %{ dam.env_msg.str = state.match; }
            (ws '!' %{ dam.env_msg.important = true; })?
            ;

        damage_one_data =
            (damage_name | damage_inc_counts | damage_dec_stat | damage_inc_stat | damage_transfer_stat |
            damage_threshold | damage_levelup_threshold | damage_visible_damage | damage_karmic_scale |
            damage_polymorph | damage_player_poly | damage_infect | damage_ally |
            damage_eyeless | damage_undead | damage_animal | damage_plant | damage_player |
            damage_robot | damage_magic | damage_melee_msg | damage_env_msg | 
            damage_cosmic | 
            '}' ${ fret; })
            ;

        one_damage := (ws damage_one_data ws ';')+
            ;

        damage_tag = tag %{ dam.tag = tag_t(state.match, tagmem); }
        ;

        damage = 
            'damage' %{ dam = Damage(); }
            ws1 damage_tag ws
            '{' ${fcall one_damage;}
            %{ init_damage(dam); }
            ;

        ####

        stat_label = 'label'
            ws1 string %{ sta.label.label = state.match; }
            ws1 skin   %{ sta.label.lskin.set(SKINS); } ;

        stat_mark = 'mark'
            ws1 skin %{ sta.label.pskin.set(SKINS); }
            (ws1 skin %{ sta.label.nskin.set(SKINS); sta.progressbar = false; })?
            (ws1 'reversed' %{ sta.reversed = true; })?;

        stat_limits = 'limits'
            ws1 real %{ sta.min = toreal(state.match); }
            ws1 real %{ sta.max = toreal(state.match); } ;

        stat_critical = 'critical' %{ sta.critical = true; } ;
        stat_hidden = 'hidden' %{ sta.hidden = true; } ;

        stat_chain_pos = 'chain_pos' ws1 tag %{ sta.chain_pos = tag_t(state.match, tagmem); } ;
        stat_chain_neg = 'chain_neg' ws1 tag %{ sta.chain_neg = tag_t(state.match, tagmem); } ;

        stat_monster_hit_msg = 'monster_hit_msg' ws1 string %{ sta.monster_hit_msg = state.match; };

        stat_status_min_msg = 'status_min_msg' ws1 string %{ sta.status_min_msg = state.match; };

        stat_ailment = 'ailment' ws1 tag %{ sta.ailment = tag_t(state.match, tagmem); } ;

        stat_one_data =
            (stat_label | stat_mark | stat_limits | stat_critical | stat_hidden | stat_status_min_msg |
            stat_chain_pos | stat_chain_neg | stat_monster_hit_msg | stat_ailment |
            '}' ${ fret; })
            ;

        one_stat := (ws stat_one_data ws ';')+
            ;

        stat_tag = tag %{ sta.tag = tag_t(state.match, tagmem); }
        ;

        stat = 
            'stat' %{ sta = Stat(); }
            ws1 stat_tag ws
            '{' ${fcall one_stat;}
            %{ init_stat(sta); }
            ;

        ####

        count_label = 'label'
            ws1 string %{ cou.label.label = state.match; }
            ws1 skin   %{ cou.label.lskin.set(SKINS); } ;

        count_mark = 'mark'
            ws1 skin %{ cou.label.pskin.set(SKINS); }
            ws1 skin %{ cou.label.nskin.set(SKINS); } ;

        count_max = 'max' ws1 number %{ cou.cmax = toint(state.match); } ;

        count_hidden = 'hidden' %{ cou.hidden = true; } ;

        count_monster_hit_msg = 'monster_hit_msg' ws1 string %{ cou.monster_hit_msg = state.match; };

        count_status_msg = 'status_msg' ws1 string %{ cou.status_msg = state.match; };

        count_blind = 'blind' %{ cou.blind = true; };
        count_stun  = 'stun'  %{ cou.stun = true; };
        count_fear  = 'fear'  %{ cou.fear = true; };
        count_sleep = 'sleep' %{ cou.sleep = true; };

        count_cancellable = 'cancellable' %{ cou.cancellable = true; };

        count_ailment = 'ailment' ws1 tag %{ cou.ailment = tag_t(state.match, tagmem); } ;

        count_one_data =
            (count_label | count_mark | count_max | count_hidden |
            count_monster_hit_msg | count_status_msg | count_ailment |
            count_blind | count_stun | count_fear | count_sleep | count_cancellable |
            '}' ${ fret; })
            ;

        one_count := (ws count_one_data ws ';')+
            ;

        count_tag = tag %{ cou.tag = tag_t(state.match, tagmem); }
        ;

        count = 
            'count' %{ cou = Count(); }
            ws1 count_tag ws
            '{' ${fcall one_count;}
            %{ init_count(cou); }
            ;

        ###

        pc_include = 'include' ws1 string %{ parse_config(state.match, tagmem); } ws ';';

        pc_string = 'string'
            ws1 string %{ hash = fnv64a_hash(state.match.c_str(), state.match.size()); }
            ws1 string %{ init_strings_copy(hash, state.match); }
            ws ';';

        ###

        entry = species | design | terrain | vault | celauto | levelskin | constant | 
                achievement | ailment | ui_syms | damage | stat | count | pc_include |
                pc_string;
            
      main := (ws entry)+ ws ;
        
    }%%
/*

*/

    %% write data;
    %% write init;

    bool done = false;

    while (!done) {
        int space = sizeof(buf) ;

        state.p = buf;
        int len = ::fread(state.p, 1, space, fn);
        
        state.pe = state.p + len;
        state.eof = 0;
        
        if (len == 0) {
            state.eof = state.pe;
            done = true;
        }

        %% write exec;

        // Avoid spurious gcc warnings.
        (void)ConfigParser_first_final;
        (void)ConfigParser_en_strchar_escape;
        (void)ConfigParser_en_one_species;
        (void)ConfigParser_en_one_design;
        (void)ConfigParser_en_one_terrain;
        (void)ConfigParser_en_one_vault;
        (void)ConfigParser_en_one_celauto;
        (void)ConfigParser_en_one_levelskin;
        (void)ConfigParser_en_one_damage;
        (void)ConfigParser_en_one_stat;
        (void)ConfigParser_en_one_count;
        (void)ConfigParser_en_main;

        if (state.cs == ConfigParser_error) {
            throw std::runtime_error("Parse error. Unconsumed input: " + std::string(state.p, state.pe));
        }
    }
}

}

#undef SKINS

#endif
