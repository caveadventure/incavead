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

    // Iterator for start and end of token.
    char* ts;
    char* te;

    // Internal state and rollback variables.
    int cs, act;

    // Stack for ragel machine states.
    int stack[32];
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

    Vault::brush vbrush;

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

        skin = string %{ skin.text = state.match; skin.back = maudit::color::bright_black; } 
               ws1 color (ws1 'back' ws1 back_color)? ;

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
            'electric'      %{ dmgval.type = damage::type_t::electric; }      ;


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
            'none_nosleep'   %{ spe.ai = Species::ai_t::none_nosleep; }   ;

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
        species_skin        = 'skin'        ws1 skin       %{ spe.skin = skin; };
        species_habitat     = 'habitat'     ws1 habitat    ;
        species_ai          = 'ai'          ws1 ai         ;
        species_idle_ai     = 'idle_ai'     ws1 idle_ai    ;
        species_move        = 'move'        ws1 move       ;
        species_range       = 'range'       ws1 number     %{ spe.range = toint(state.match); } ;
        species_attack      = 'attack'      ws1 damage_val %{ spe.attacks.add(dmgval); } ;
        species_defense     = 'defense'     ws1 damage_val %{ spe.defenses.add(dmgval); } ;
        species_karma       = 'karma'       ws1 real       %{ spe.karma = toreal(state.match); };

        species_clumpsize = 'clumpsize' 
            ws1 real %{ spe.clumpsize.mean = toreal(state.match); } 
            ws1 real %{ spe.clumpsize.deviation = toreal(state.match); } 
        ;

        species_companion = 'companion' %{ spe.companion.push_back(Species::companion_t()); }
            ws1 real   %{ spe.companion.back().chance = toreal(state.match); }
            ws1 string %{ spe.companion.back().tag = tag_t(state.match, tagmem); }
            ;

        species_drop = 'drop' %{ spe.drop.push_back(Species::drop_t()); }
            ws1 string %{ spe.drop.back().tag = tag_t(state.match, tagmem); }
            ws1 real   %{ spe.drop.back().chance = toreal(state.match); }
            ;

        species_cast_cloud = 'cast_cloud' %{ spe.cast_cloud.push_back(Species::cloud_t()); }
            ws1 real   %{ spe.cast_cloud.back().chance = toreal(state.match); }
            ws1 string %{ spe.cast_cloud.back().terraintag = tag_t(state.match, tagmem); }
            ws1 number %{ spe.cast_cloud.back().radius = toint(state.match); }
            ws1 number %{ spe.cast_cloud.back().turns = toint(state.match); }
            ws1 string %{ spe.cast_cloud.back().name = state.match; }
            ;

        species_summon = 'summon' %{ spe.summon.push_back(Species::summon_t()); }
            ws1 real   %{ spe.summon.back().chance = toreal(state.match); }
            ws1 string %{ spe.summon.back().speciestag = tag_t(state.match, tagmem); }
            ws1 number %{ spe.summon.back().turns = toint(state.match); }
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

        species_one_data = 
            (species_count | species_name | species_skin | species_habitat | species_ai |
            species_idle_ai | species_move | species_range | species_clumpsize |
            species_companion | species_attack | species_defense | species_drop |
            species_cast_cloud | species_summon |
            species_animal | species_undead | species_magic | species_plant |
            species_robot |
            species_karma | species_blast |
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
        design_skin       = 'skin'       ws1 skin       %{ des.skin = skin; };
        design_slot       = 'slot'       ws1 string     %{ des.slot = state.match; } ;
        design_descr      = 'descr'      ws1 string     %{ des.descr = state.match; } ;
        design_attack     = 'attack'     ws1 damage_val %{ des.attacks.add(dmgval); } ;
        design_defense    = 'defense'    ws1 damage_val %{ des.defenses.add(dmgval); } ;
        design_stackrange = 'stackrange' ws1 number     %{ des.stackrange = toint(state.match); };
        design_heal       = 'heal'       ws1 real       %{ des.heal = toreal(state.match); };
        design_feed       = 'feed'       ws1 real       %{ des.feed = toreal(state.match); };
        design_usable     = 'usable'                    %{ des.usable = true; };
        design_melee      = 'melee'                     %{ des.melee = true; };
        design_throwrange = 'throwrange' ws1 number     %{ des.throwrange = toint(state.match); };
        design_lightradius = 'lightradius' ws1 number   %{ des.lightradius = toint(state.match); };
        design_digging    = 'digging' ws1 real          %{ des.digging = toreal(state.match); };

        design_blink      = 'blink' %{ des.flags.blink = true; };

        design_blast      = 'blast' 
            ws1 number %{ des.blastradius = toint(state.match); }
            ws1 number %{ des.blastrange = toint(state.match); }
            ;

        design_gencount = 'gencount' 
            ws1 real %{ des.gencount.mean = toreal(state.match); } 
            ws1 real %{ des.gencount.deviation = toreal(state.match); } 
        ;

        design_one_data = 
            (design_count | design_name | design_skin | design_slot | design_descr |
            design_attack | design_defense | design_stackrange | design_heal | design_usable |
            design_throwrange | design_blast | design_gencount | design_melee | design_feed |
            design_lightradius | design_digging | design_blink |
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
            'floor'   %{ ter.placement = Terrain::placement_t::floor; }     | 
            'water'   %{ ter.placement = Terrain::placement_t::water; }     | 
            'corner'  %{ ter.placement = Terrain::placement_t::corner; }    ;

        terrain_tunnel   = 'tunnel' 
            ws1 snumber %{ ter.tunnel_x = toint(state.match); }
            ws1 snumber %{ ter.tunnel_y = toint(state.match); } 
            ;

        terrain_count     = 'count'     ws1 number     %{ ter.count = toint(state.match); } ;
        terrain_name      = 'name'      ws1 string     %{ ter.name = state.match; } ;
        terrain_skin      = 'skin'      ws1 skin       %{ ter.skin = skin; };
        terrain_placement = 'placement' ws1 tplacement  ;
        terrain_stairs    = 'stairs'    ws1 number     %{ ter.stairs = toint(state.match); } ;
        terrain_viewblock = 'viewblock'                %{ ter.viewblock = true; } ;
        terrain_walkblock = 'walkblock'                %{ ter.walkblock = true; } ;
        terrain_decay     = 'decay'     ws1 number     %{ ter.decay = toint(state.match); } ;
        terrain_attack    = 'attack'    ws1 damage_val %{ ter.attacks.add(dmgval); } ;
        terrain_sticky    = 'sticky'                   %{ ter.sticky = true; } ;
        terrain_charges   = 'charges'   ws1 number     %{ ter.charges = toint(state.match); } ;
        
        terrain_is_lit    = 'is_lit' %{ ter.is_lit = true; } ;

        terrain_attack_level = 'attack_level' ws1 number %{ ter.attack_level = toint(state.match); } ;

        terrain_grant_spell = 'grant_spell'
            ws1 string %{ ter.grant_spell.ca_tag = tag_t(state.match, tagmem); } 
            ws1 real   %{ ter.grant_spell.karma_bound = toreal(state.match); }
            ws1 real   %{ ter.grant_spell.timeout = toreal(state.match); }
            ws1 string %{ ter.grant_spell.name = state.match; } ;

        terrain_one_data =
            (terrain_count | terrain_name | terrain_skin | terrain_placement |
            terrain_stairs | terrain_tunnel | terrain_viewblock | terrain_walkblock |
            terrain_decay | terrain_attack | terrain_attack_level | terrain_sticky |
            terrain_charges | terrain_grant_spell | terrain_is_lit |
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
            'floor'   %{ vau.placement = Vault::placement_t::floor; }     | 
            'water'   %{ vau.placement = Vault::placement_t::water; }     | 
            'corner'  %{ vau.placement = Vault::placement_t::corner; }    ;

        vault_count     = 'count'     ws1 number     %{ vau.count = toint(state.match); } ;
        vault_placement = 'placement' ws1 vplacement  ;

        vault_anchor    = 'anchor'    
            ws1 number %{ vau.ax = toint(state.match); } 
            ws1 number %{ vau.ay = toint(state.match); }
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

        vault_one_data =
            (vault_count | vault_placement | vault_anchor | vault_brush | vault_line |
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

        celauto_s = 's' ws1 ( [0-9] ${ cel.survive.insert(fc - '0'); } )+;

        celauto_b = 'b' ws1 ( [0-9] ${ cel.born.insert(fc - '0'); } )+;

        celauto_a = 'a' ws1 number %{ cel.age = toint(state.match); } ;

        celauto_terrain = 'terrain' ws1 string %{ cel.terrain = tag_t(state.match, tagmem); } ;

        celauto_is_walk   = 'is_walk'   %{ cel.is_walk = true; } ;
        celauto_make_walk = 'make_walk' %{ cel.make_walk = true; } ;

        celauto_karma_scale = 'karma_scale' ws1 real %{ cel.karma_scale = toreal(state.match); } ;
        celauto_karma_step  = 'karma_step'  ws1 real %{ cel.karma_step  = toreal(state.match); } ;

        celauto_seed = 'seed'      %{ cel.seed.push_back(std::make_pair(0,0)); }
                       ws1 snumber %{ cel.seed.back().first = toint(state.match); }
                       ws1 snumber %{ cel.seed.back().second = toint(state.match); }
                       ; 

        celauto_one_data =
            (celauto_s | celauto_b | celauto_a | celauto_terrain |
            celauto_is_walk | celauto_make_walk | celauto_karma_scale | 
            celauto_karma_step | celauto_seed | '}' 
            ${ fret; })
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

        levelskin_deep_water    = 'deep_water'    ws1 skin   %{ lev.deep_water = skin; };
        levelskin_shallow_water = 'shallow_water' ws1 skin   %{ lev.shallow_water = skin; };
        levelskin_wall          = 'wall'          ws1 skin   %{ lev.wall = skin; };
        levelskin_water_wall    = 'water_wall'    ws1 skin   %{ lev.water_wall = skin; };
        levelskin_floor1        = 'floor1'        ws1 skin   %{ lev.floor1 = skin; };
        levelskin_floor2        = 'floor2'        ws1 skin   %{ lev.floor2 = skin; };
        levelskin_floor3        = 'floor3'        ws1 skin   %{ lev.floor3 = skin; };
        levelskin_floor4        = 'floor4'        ws1 skin   %{ lev.floor4 = skin; };
        levelskin_floor5        = 'floor5'        ws1 skin   %{ lev.floor5 = skin; };
        levelskin_floor6        = 'floor6'        ws1 skin   %{ lev.floor6 = skin; };
        levelskin_floor7        = 'floor7'        ws1 skin   %{ lev.floor7 = skin; };
        levelskin_floor8        = 'floor8'        ws1 skin   %{ lev.floor8 = skin; };
        levelskin_lightradius   = 'lightradius'   ws1 number %{ lev.lightradius = toint(state.match); };
        levelskin_lightradius_max = 'lightradius_max' ws1 number %{ lev.lightradius_max = toint(state.match); };
        levelskin_exclusive     = 'exclusive'     %{ lev.exclusive = true; };

        levelskin_one_data =
            (levelskin_deep_water | levelskin_shallow_water | levelskin_wall | 
            levelskin_water_wall | levelskin_floor1 | levelskin_floor2 |
            levelskin_floor3 | levelskin_floor4 | levelskin_floor5 |
            levelskin_floor6 | levelskin_floor7 | levelskin_floor8 |
            levelskin_lightradius | levelskin_lightradius_max |
            levelskin_exclusive |
            '}' 
            ${ fret; })
            ;

        one_levelskin := (ws levelskin_one_data ws ';')+
            ;

        levelskin_level = number %{ lev.level = toint(state.match); } 
        ;

        levelskin =
            'levelskin' %{ lev = Levelskin(); }
            ws1 levelskin_level ws
            '{' ${fcall one_levelskin;}
            %{ init_levelskin_(lev); }
            ;

        ####

        constant_meat     = 'meat'     ws1 string  %{ __constants__().meat = tag_t(state.match, tagmem); };
        constant_bad_meat = 'bad_meat' ws1 string  %{ __constants__().bad_meat = tag_t(state.match, tagmem); };

        one_constant = constant_meat | constant_bad_meat;

        constant = 'constant' ws1 one_constant ws ';';

        ####

        entry = species | design | terrain | vault | celauto | levelskin | constant;
            
      main := (ws entry)+ ws ;
        
    }%%
/*

*/

    %% write data;
    %% write init;

    bool done = false;
    int have = 0;

    while (!done) {
        int space = sizeof(buf) - have;
        if (space == 0) {
            throw std::runtime_error("Token too big!");
        }

        state.p = buf + have;
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

        if (state.ts == 0) {
            have = 0;

        } else {
            have = state.pe - state.ts;
            ::memmove(buf, state.ts, have);
            state.te = buf + (state.te - state.ts);
            state.ts = buf;
        }
    }
}

}

#endif
