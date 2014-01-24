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

    damage::val_t dmgval;

    maudit::glyph skin;
    maudit::glyph skin_b;
    maudit::glyph skin_c;

#define SKINS skin, skin_b, skin_c
    
    Vault::brush vbrush;

    unsigned char shortcut_key;
    tag_t genus_tag;
    tag_t ach_tag;
    tag_t ail_tag;

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

        skin = string %{ skin.text = state.match; 
                         skin.back = maudit::color::bright_black; 
                         skin.fore = maudit::color::bright_white; } 
               (ws1 color)?
               ws
               ('back' ws1 back_color ws)? 
               %{ skin_b = skin; skin_c = skin; }
               (('|' ws string %{ skin_b.text = state.match; })
                ws
                ('|' ws string %{ skin_c.text = state.match; })?)?
               ;

        ####

        damage_type = 
            'physical'      %{ dmgval.type = damage::type_t::physical; }      |
            'sleep'         %{ dmgval.type = damage::type_t::sleep; }         |
            'poison'        %{ dmgval.type = damage::type_t::poison; }        |
            'turn_undead'   %{ dmgval.type = damage::type_t::turn_undead; }   |
            'cancellation'  %{ dmgval.type = damage::type_t::cancellation; }  |
            'scare_animal'  %{ dmgval.type = damage::type_t::scare_animal; }  |
            'psi'           %{ dmgval.type = damage::type_t::psi; }           |
            'eat_brain'     %{ dmgval.type = damage::type_t::eat_brain; }     |
            'drain'         %{ dmgval.type = damage::type_t::drain; }         |
            'make_meat'     %{ dmgval.type = damage::type_t::make_meat; }     |
            'scare'         %{ dmgval.type = damage::type_t::scare; }         |
            'vampiric'      %{ dmgval.type = damage::type_t::vampiric; }      |
            'heavenly_fire' %{ dmgval.type = damage::type_t::heavenly_fire; } |
            'hellish_fire'  %{ dmgval.type = damage::type_t::hellish_fire; }  |
            'electric'      %{ dmgval.type = damage::type_t::electric; }      |
            'sonic'         %{ dmgval.type = damage::type_t::sonic; }         |
            'magic'         %{ dmgval.type = damage::type_t::magic; }         |
            'hunger'        %{ dmgval.type = damage::type_t::hunger; }        |
            'unluck'        %{ dmgval.type = damage::type_t::unluck; }        |
            'blindness'     %{ dmgval.type = damage::type_t::blindness; }     ;


        damage_val = 
            damage_type 
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
            'none'           %{ spe.ai = Species::ai_t::none; }           |
            'seek_player'    %{ spe.ai = Species::ai_t::seek_player; }    |
            'random'         %{ spe.ai = Species::ai_t::random; }         |
            'inrange_random' %{ spe.ai = Species::ai_t::inrange_random; } |
            'seek_nosleep'   %{ spe.ai = Species::ai_t::seek_nosleep; }   |
            'none_nosleep'   %{ spe.ai = Species::ai_t::none_nosleep; }   |
            'suicide'        %{ spe.ai = Species::ai_t::suicide; }        ;

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
        species_habitat     = 'habitat'     ws1 habitat    ;
        species_ai          = 'ai'          ws1 ai         ;
        species_idle_ai     = 'idle_ai'     ws1 idle_ai    ;
        species_move        = 'move'        ws1 move       ;
        species_range       = 'range'       ws1 number     %{ spe.range = toint(state.match); } ;
        species_attack      = 'attack'      ws1 damage_val %{ spe.attacks.add(dmgval); } ;
        species_defense     = 'defense'     ws1 damage_val %{ spe.defenses.add(dmgval); } ;
        species_karma       = 'karma'       ws1 real       %{ spe.karma = toreal(state.match); } ;

        species_clumpsize = 'clumpsize' 
            ws1 real %{ spe.clumpsize.mean = toreal(state.match); } 
            ws1 real %{ spe.clumpsize.deviation = toreal(state.match); } 
        ;

        species_companion = 'companion' %{ spe.companion.push_back(Species::companion_t()); }
            ws1 real   %{ spe.companion.back().chance = toreal(state.match); }
            ws1 tag    %{ spe.companion.back().tag = tag_t(state.match, tagmem); }
            ;

        species_drop = 'drop' %{ spe.drop.push_back(Species::drop_t()); }
            ws1 tag    %{ spe.drop.back().tag = tag_t(state.match, tagmem); }
            ws1 real   %{ spe.drop.back().chance = toreal(state.match); }
            ;

        species_drop_random = 'drop_random' %{ spe.drop.push_back(Species::drop_t()); }
            ws1 number %{ spe.drop.back().level = toint(state.match); }
            ws1 real   %{ spe.drop.back().chance = toreal(state.match); }
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
            ;

        species_spawn = 'spawn' %{ spe.spawns.push_back(Species::spawn_t()); }
            ws1 real   %{ spe.spawns.back().chance = toreal(state.match); }
            ws1 number %{ spe.spawns.back().level = toint(state.match); }
            ws1 number %{ spe.spawns.back().turns = toint(state.match); }
            ;

        species_blast = 'blast' %{ spe.blast.push_back(Species::blast_t()); }
            ws1 real %{ spe.blast.back().chance = toreal(state.match); }
            ws1 number %{ spe.blast.back().radius = toint(state.match); }
            ws1 number %{ spe.blast.back().range = toint(state.match); }
            ws1 number %{ spe.blast.back().turns = toint(state.match); }
            (ws1 'attack' 
             ws1 damage_val 
             %{ spe.blast.back().attacks.add(dmgval); })+
            ;
        

        species_animal = 'animal' %{ spe.flags.animal = true; } ;
        species_undead = 'undead' %{ spe.flags.undead = true; } ;
        species_magic  = 'magic'  %{ spe.flags.magic = true; } ;
        species_plant  = 'plant'  %{ spe.flags.plant = true; } ;
        species_robot  = 'robot'  %{ spe.flags.robot = true; } ;

        species_terrain_immune = 'terrain_immune' %{ spe.flags.terrain_immune = true; } ;

        species_eyeless = 'eyeless' %{ spe.flags.eyeless = true; } ;

        species_trail = 'trail' 
            ws1 tag  %{ spe.trail.terrain = tag_t(state.match, tagmem); } 
            ws1 real %{ spe.trail.cost.mean = toreal(state.match); } 
            ws1 real %{ spe.trail.cost.deviation = toreal(state.match); }
            ;

        species_one_data = 
            (species_count | species_name | species_skin | species_habitat | species_ai |
            species_genus | species_idle_ai | species_move | species_range | species_clumpsize |
            species_companion | species_attack | species_defense | species_drop | species_drop_random |
            species_cast_cloud | species_summon | species_spawn |
            species_animal | species_undead | species_magic | species_plant |
            species_robot | species_terrain_immune | species_eyeless |
            species_karma | species_blast | species_true_level | species_trail |
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
        design_name       = 'name'       ws1 string     %{ des.name = state.match; } ;
        design_skin       = 'skin'       ws1 skin       %{ des.skin.set(SKINS); };
        design_slot       = 'slot'       ws1 tag        %{ des.slot = tag_t(state.match, tagmem); } ;
        design_descr      = 'descr'      ws1 string     %{ des.descr = state.match; } ;
        design_attack     = 'attack'     ws1 damage_val %{ des.attacks.add(dmgval); } ;
        design_defense    = 'defense'    ws1 damage_val %{ des.defenses.add(dmgval); } ;
        design_stackrange = 'stackrange' ws1 number     %{ des.stackrange = toint(state.match); };
        design_heal       = 'heal'       ws1 real       %{ des.heal = toreal(state.match); };
        design_feed       = 'feed'       ws1 real       %{ des.feed = toreal(state.match); };
        design_karma      = 'karma'      ws1 real       %{ des.karma = toreal(state.match); };
        design_usable     = 'usable'                    %{ des.usable = true; };
        design_melee      = 'melee'                     %{ des.melee = true; };
        design_throwrange = 'throwrange' ws1 number     %{ des.throwrange = toint(state.match); };
        design_lightradius = 'lightradius' ws1 number   %{ des.lightradius = toint(state.match); };
        design_digging    = 'digging' ws1 real          %{ des.digging = toreal(state.match); };
        design_descend    = 'descend' ws1 snumber       %{ des.descend = toint(state.match); };

        design_destructible = 'destructible' %{ des.destructible = true; };

        design_count_is_only_one = 'count_is_only_one' %{ des.count_is_only_one = true; };

        design_safe_descend = 'safe_descend' ws1 snumber %{ des.safe_descend = toint(state.match); };

        design_blink      = 'blink' %{ des.flags.blink = true; };
        design_dowsing    = 'dowsing' %{ des.flags.dowsing = true; };

        design_blast      = 'blast' 
            ws1 number %{ des.blast.radius = toint(state.match); }
            ws1 number %{ des.blast.range = toint(state.match); }
            ;

        design_cast_cloud = 'cast_cloud' 
            ws1 tag    %{ des.cast_cloud.terraintag = tag_t(state.match, tagmem); }
            ws1 number %{ des.cast_cloud.radius = toint(state.match); }
            ;

        design_gencount = 'gencount' 
            ws1 real %{ des.gencount.mean = toreal(state.match); } 
            ws1 real %{ des.gencount.deviation = toreal(state.match); } 
        ;

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

        design_luck = 'luck' %{ des.luck.push_back(Design::luck_t()); }
            ws1 real %{ des.luck.back().height = toreal(state.match); }
            ws1 real %{ des.luck.back().mean = toreal(state.match); }
            ws1 real %{ des.luck.back().deviation = toreal(state.match); }
            ;

        design_hunger = 'hunger' ws1 real %{ des.hunger = toreal(state.match); };

        design_other_hunger_multiplier = 'other_hunger_multiplier' 
            ws1 real %{ des.other_hunger_multiplier = toreal(state.match); };

        design_shield = 'shield' ws1 real %{ des.shield = toreal(state.match); };

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

        design_heal_blind = 'heal_blind' %{ des.heal_blind = true; };

        design_one_data = 
            (design_count | design_name | design_skin | design_slot | design_descr |
            design_attack | design_defense | design_stackrange | design_heal | design_usable | design_destructible |
            design_throwrange | design_blast | design_gencount | design_melee | design_feed | design_karma |
            design_lightradius | design_digging | design_descend | design_blink | design_cast_cloud |
            design_worth | design_safe_descend | design_is_lit | design_count_is_only_one |
            design_place_permafeat | design_place_permafloor | design_luck | design_hunger | 
            design_other_hunger_multiplier | design_dowsing |
            design_shield | design_enable_spells | design_grant_spell | design_count_is_rcode |
            design_random_spell | design_genocide | design_wish | design_magic_mapping |
            design_heal_blind |
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
        
        terrain_is_lit    = 'is_lit' %{ ter.is_lit = true; } ;
        terrain_air       = 'air'    %{ ter.air = true; };

        terrain_safebox   = 'safebox' %{ ter.safebox = true; };

        terrain_attack_level = 'attack_level' ws1 number %{ ter.attack_level = toint(state.match); } ;

        terrain_victory_item = 'victory_item' ws1 tag %{ ter.victory_item = tag_t(state.match, tagmem); } ;

        terrain_grant_spell = 'grant_spell'
            ws1 tag    %{ ter.grant_spell.ca_tag = tag_t(state.match, tagmem); } 
            ws1 real   %{ ter.grant_spell.karma_bound = toreal(state.match); }
            ws1 real   %{ ter.grant_spell.timeout = toreal(state.match); }
            ws1 string %{ ter.grant_spell.name = state.match; } ;

        terrain_protection_racket = 'protection_racket' 
            ws1 real   %{ ter.protection_racket.shield_bonus = toreal(state.match); }
            ws1 real   %{ ter.protection_racket.money_curse = toreal(state.match); } ;

        terrain_uncharge_flag = ('attack' %{ ter.uncharge.attack = true; } ) |
                                ('use'    %{ ter.uncharge.use = true; }    ) |
                                ('move'   %{ ter.uncharge.move = true; }   ) ;

        terrain_uncharge = 'uncharge' ws1 (ws terrain_uncharge_flag)* ;

        terrain_crafting = 'crafting' %{ ter.crafting.push_back(Terrain::craft_t()); }
            ws1 tag %{ ter.crafting.back().from = tag_t(state.match, tagmem); }
            ws1 tag %{ ter.crafting.back().to = tag_t(state.match, tagmem); }
            ;

        terrain_wish = 'wish' ws1 ('simple'  %{ ter.wishing = Terrain::SIMPLE_WISH;  } |
                                   'special' %{ ter.wishing = Terrain::SPECIAL_WISH; })
                       ;

        terrain_important = 'important' %{ ter.important = true; } ;

        terrain_view_radius = 'view_radius' ws1 number %{ ter.view_radius = toint(state.match); } ;

        terrain_one_data =
            (terrain_count | terrain_name | terrain_skin | terrain_placement | terrain_descr |
            terrain_stairs | terrain_tunnel | terrain_viewblock | terrain_walkblock |
            terrain_decay | terrain_attack | terrain_attack_level | terrain_sticky |
            terrain_charges | terrain_grant_spell | terrain_is_lit | terrain_air |
            terrain_victory_item | terrain_safebox | terrain_protection_racket |
            terrain_uncharge | terrain_crafting | terrain_wish | terrain_important |
            terrain_view_radius |
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

        vault_brush = 'brush' %{ vbrush = Vault::brush(); }
            ws1 ('blank' ${ vbrush.is_blank = true; } |
                 'floor' ${ vbrush.is_walk = true; vbrush.is_water = false;  } |
                 'water' ${ vbrush.is_walk = true; vbrush.is_water = true;   } |
                 'wall'  ${ vbrush.is_walk = false; vbrush.is_water = false; } |
                 'wwall' ${ vbrush.is_walk = false; vbrush.is_water = true;  })
            ws1 string   %{ vbrush.terrain = tag_t(state.match, tagmem); }
            ws1 string   %{ vbrush.design = tag_t(state.match, tagmem); }
            ws1 string   %{ vbrush.species = tag_t(state.match, tagmem); }
            ws1 '\'' any ${ vau.brushes[fc] = vbrush; } '\''
            ;

        vault_line = 'l' ws1 string %{ vau.pic.push_back(state.match); } ;

        vault_inherit = 'inherit' ws1 tag %{ vau.inherit = tag_t(state.match, tagmem); };

        vault_transpose = 'transpose' %{ vau.transpose = true; };

        vault_priority = 'priority' %{ vau.priority = 1; };

        vault_one_data =
            (vault_count | vault_placement | vault_anchor | vault_brush | vault_line |
            vault_inherit | vault_transpose | vault_priority | vault_set_player |
            '}'
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

        celauto_s = 's' ws1 ( [0-9] ${ cel.survive.insert(fc - '0'); } )*;

        celauto_b = 'b' ws1 ( [0-9] ${ cel.born.insert(fc - '0'); } )+;

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
        levelskin_damage        = 'damage'        ws1 real   %{ lev.damage = toreal(state.match); };
        levelskin_exclusive     = 'exclusive'     %{ lev.exclusive = true; };

        levelskin_no_phase_level = 'no_phase_level' %{ lev.no_phase_level = true; };

        levelskin_species_level = 'species_level' ws1 number %{ lev.species_level = toint(state.match); };
        levelskin_designs_level = 'designs_level' ws1 number %{ lev.designs_level = toint(state.match); };
        levelskin_vaults_level  = 'vaults_level'  ws1 number %{ lev.vaults_level  = toint(state.match); };

        levelskin_number_vaults = 'number_vaults' ws1 number %{ lev.number_vaults = toint(state.match); };

        levelskin_number_monsters = 'number_monsters' 
            ws1 real %{ lev.number_monsters.mean = toreal(state.match); }
            ws1 real %{ lev.number_monsters.deviation = toreal(state.match); }
            ;

        levelskin_number_items = 'number_items' 
            ws1 real %{ lev.number_items.mean = toreal(state.match); }
            ws1 real %{ lev.number_items.deviation = toreal(state.match); }
            ;

        levelskin_number_features = 'number_features' 
            ws1 real %{ lev.number_features.mean = toreal(state.match); }
            ws1 real %{ lev.number_features.deviation = toreal(state.match); }
            ;

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
        levelskin_flatten_walk_ng        = 'flatten_walk_ng'     ws1 number %{ lev.genparams.flatten_walk_ng = toint(state.match); };
        levelskin_flatten_water_ng       = 'flatten_water_ng'    ws1 number %{ lev.genparams.flatten_water_ng = toint(state.match); };
        levelskin_unflow_ng              = 'unflow_ng'           ws1 number %{ lev.genparams.unflow_ng = toint(state.match); };
        levelskin_karma_mean             = 'karma_mean'          ws1 real   %{ lev.genparams.karma_mean = toreal(state.match); };
        levelskin_karma_dev              = 'karma_dev'           ws1 real   %{ lev.genparams.karma_dev = toreal(state.match); };
        levelskin_nflatten               = 'nflatten'            ws1 number %{ lev.genparams.nflatten = toint(state.match); };
        levelskin_nunflow                = 'nunflow'             ws1 number %{ lev.genparams.nunflow = toint(state.match); };

        levelskin_one_data =
            (levelskin_deep_water | levelskin_shallow_water | levelskin_wall | 
            levelskin_water_wall | levelskin_floor1 | levelskin_floor2 |
            levelskin_floor3 | levelskin_floor4 | levelskin_floor5 |
            levelskin_floor6 | levelskin_floor7 | levelskin_floor8 |
            levelskin_lightradius | levelskin_lightradius_max | levelskin_damage |
            levelskin_exclusive | levelskin_no_phase_level |
            levelskin_species_level | levelskin_designs_level | levelskin_vaults_level |
            levelskin_number_vaults | levelskin_number_monsters | levelskin_number_items |
            levelskin_number_features | levelskin_name | levelskin_treasure_level |
            levelskin_flow_epsilon | levelskin_flow_n_freq | levelskin_flow_volume |
            levelskin_flow_erosion | levelskin_flow_renorm_freq | levelskin_flow_renorm_scale |
            levelskin_walk_threshold | levelskin_lowlands_threshold | levelskin_water_quantile_mean |
            levelskin_water_quantile_dev | levelskin_flatten_walk_ng | levelskin_flatten_water_ng |
            levelskin_unflow_ng | levelskin_karma_mean | levelskin_karma_dev |
            levelskin_nflatten | levelskin_nunflow |
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

        constant_hunger_rate       = 'hunger_rate'       
            ws1 real %{ __constants__().hunger_rate = toreal(state.match); };

        constant_starvation_damage = 'starvation_damage' 
            ws1 real %{ __constants__().starvation_damage = toreal(state.match); };

        constant_grave     = 'grave'     ws1 tag  %{ __constants__().grave = tag_t(state.match, tagmem); };
        constant_meat      = 'meat'      ws1 tag  %{ __constants__().meat = tag_t(state.match, tagmem); };
        constant_bad_meat  = 'bad_meat'  ws1 tag  %{ __constants__().bad_meat = tag_t(state.match, tagmem); };
        constant_money     = 'money'     ws1 tag  %{ __constants__().money = tag_t(state.match, tagmem); };
        constant_pit       = 'pit'       ws1 tag  %{ __constants__().pit = tag_t(state.match, tagmem); };
        constant_bad_grave = 'bad_grave' ws1 tag  %{ __constants__().bad_grave = tag_t(state.match, tagmem); };
        constant_ghost     = 'ghost'     ws1 tag  %{ __constants__().ghost = tag_t(state.match, tagmem); };

        constant_unique_item = 'unique_item' ws1 tag %{ __constants__().unique_item = tag_t(state.match, tagmem); };

        constant_uniques_timeout = 'uniques_timeout' ws1 number %{ __constants__().uniques_timeout = toint(state.match); };

        constant_player_skin = 'player_skin' ws1 skin %{ __constants__().player_skin.set(SKINS); } ;

        constant_health_shield_max = 'health_shield_max' 
            ws1 real %{ __constants__().health_shield_max = toreal(state.match); };

        constant_max_gold_per_grave = 'max_gold_per_grave'
            ws1 number %{ __constants__().max_gold_per_grave = toint(state.match); };

        constant_max_celauto_cells = 'max_celauto_cells'
            ws1 number %{ __constants__().max_celauto_cells = toint(state.match); };

        constant_slot = 'slot' %{ __constants__().slots.push_back(ConstantsBank::slot_t()); }
            ws1 tag      %{ __constants__().slots.back().slot = tag_t(state.match, tagmem); }
            ws1 '\'' any ${ __constants__().slots.back().letter = fc; } '\''
            ws1 string   %{ __constants__().slots.back().label = state.match; }
            ws1 string   %{ __constants__().slots.back().name = state.match; }
            ;

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

        constant_howto_text = 'howto_text' ws1 string %{ __constants__().howto_text = state.match; };

        constant_tombstone_text = 'tombstone_text' ws1 string %{ __constants__().tombstone_text = state.match; };

        constant_achievement_trigger_rate = 'achievement_trigger_rate' 
            ws1 number %{ __constants__().achievement_trigger_rate = toint(state.match); } ;

        constant_damage_to_sleepturns = 'damage_to_sleepturns' 
            ws1 snumber %{ __constants__().damage_to_sleepturns.scale = toint(state.match); }
            ws1 snumber %{ __constants__().damage_to_sleepturns.offset = toint(state.match); } ;

        constant_damage_to_scareturns = 'damage_to_scareturns' 
            ws1 snumber %{ __constants__().damage_to_scareturns.scale = toint(state.match); }
            ws1 snumber %{ __constants__().damage_to_scareturns.offset = toint(state.match); } ;

        constant_damage_to_blindturns = 'damage_to_blindturns' 
            ws1 snumber %{ __constants__().damage_to_blindturns.scale = toint(state.match); }
            ws1 snumber %{ __constants__().damage_to_blindturns.offset = toint(state.match); } ;

        constant_blindturns_to_radius = 'blindturns_to_radius' ws1 number %{ __constants__().blindturns_to_radius = toint(state.match); } ;

        constant_treasure_chance = 'treasure_chance' 
            ws1 real %{ __constants__().treasure_chance.mean = toreal(state.match); } 
            ws1 real %{ __constants__().treasure_chance.deviation = toreal(state.match); } 
        ;

        one_constant = constant_max_permafeats | constant_max_bones |
                       constant_hunger_rate | constant_starvation_damage |
                       constant_grave | constant_meat | constant_bad_meat | constant_money | constant_pit | 
                       constant_bad_grave | constant_ghost |
                       constant_slot | constant_player_skin |
                       constant_shortcut_messages | constant_shortcut_action | 
                       constant_genus | constant_unique_item | constant_uniques_timeout |
                       constant_health_shield_max | constant_max_gold_per_grave | constant_max_celauto_cells |
                       constant_howto_text | constant_tombstone_text | constant_achievement_trigger_rate | 
                       constant_damage_to_sleepturns | constant_damage_to_scareturns | constant_damage_to_blindturns |
                       constant_blindturns_to_radius | constant_treasure_chance
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

        ailment_attack = 'attack' ws1 damage_val %{ __constants__().ailments[ail_tag].attacks.add(dmgval); } ;

        ailment_attack_level = 'attack_level' ws1 number 
                               %{ __constants__().ailments[ail_tag].level = toint(state.match); } ;

        ailment_name = 'name' ws1 string 
                       %{ __constants__().ailments[ail_tag].name = state.match; } ;

        ailment_triggers = 'triggers' ws1 number 
                           %{ __constants__().ailments[ail_tag].triggers = toint(state.match); } ;

        ailment_line = 
            ailment_attack | ailment_attack_level | ailment_name | ailment_triggers 
            ;

        ailment = 'ailment' 
            ws1 tag    %{ ail_tag = tag_t(state.match, tagmem); }
            ws '{'
            ( ws ailment_line ws ';')+
            ws '}'
            ;

        ####

        entry = species | design | terrain | vault | celauto | levelskin | constant | 
                achievement | ailment | ui_syms;
            
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
        (void)ConfigParser_en_main;

        if (state.cs == ConfigParser_error) {
            throw std::runtime_error("Parse error. Unconsumed input: " + std::string(state.p, state.pe));
        }
    }
}

}

#undef SKINS

#endif
