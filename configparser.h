
#line 1 "configparser.rl"
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

#include "maudit.h"
#include "species.h"
#include "species_bank.h"

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

inline void add_color(maudit::color& c, unsigned int i) {
    c = (maudit::color)((uint32_t)c + i);
}

inline int toint(const std::string& s) {
    return ::atoi(s.c_str());
}

inline double toreal(const std::string& s) {
    return ::atof(s.c_str());
}

void parse_config(const std::string& filename) {

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

    maudit::glyph skin;

    
#line 321 "configparser.rl"

/*

*/

    
#line 104 "configparser.h"
static const int ConfigParser_start = 1;
static const int ConfigParser_first_final = 588;
static const int ConfigParser_error = 0;

static const int ConfigParser_en_strchar_escape = 35;
static const int ConfigParser_en_one_species = 36;
static const int ConfigParser_en_one_design = 300;
static const int ConfigParser_en_one_terrain = 449;
static const int ConfigParser_en_main = 1;


#line 327 "configparser.rl"
    
#line 118 "configparser.h"
	{
	 state.cs = ConfigParser_start;
	 state.top = 0;
	}

#line 328 "configparser.rl"

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

        
#line 147 "configparser.h"
	{
	if ( ( state.p) == ( state.pe) )
		goto _test_eof;
	goto _resume;

_again:
	switch (  state.cs ) {
		case 1: goto st1;
		case 0: goto st0;
		case 2: goto st2;
		case 3: goto st3;
		case 4: goto st4;
		case 5: goto st5;
		case 6: goto st6;
		case 7: goto st7;
		case 8: goto st8;
		case 9: goto st9;
		case 10: goto st10;
		case 11: goto st11;
		case 12: goto st12;
		case 588: goto st588;
		case 589: goto st589;
		case 13: goto st13;
		case 14: goto st14;
		case 15: goto st15;
		case 16: goto st16;
		case 17: goto st17;
		case 18: goto st18;
		case 19: goto st19;
		case 20: goto st20;
		case 21: goto st21;
		case 22: goto st22;
		case 23: goto st23;
		case 24: goto st24;
		case 590: goto st590;
		case 25: goto st25;
		case 26: goto st26;
		case 27: goto st27;
		case 28: goto st28;
		case 29: goto st29;
		case 30: goto st30;
		case 31: goto st31;
		case 32: goto st32;
		case 33: goto st33;
		case 34: goto st34;
		case 591: goto st591;
		case 35: goto st35;
		case 592: goto st592;
		case 36: goto st36;
		case 37: goto st37;
		case 38: goto st38;
		case 39: goto st39;
		case 40: goto st40;
		case 41: goto st41;
		case 42: goto st42;
		case 43: goto st43;
		case 44: goto st44;
		case 45: goto st45;
		case 46: goto st46;
		case 47: goto st47;
		case 48: goto st48;
		case 49: goto st49;
		case 50: goto st50;
		case 51: goto st51;
		case 52: goto st52;
		case 53: goto st53;
		case 54: goto st54;
		case 593: goto st593;
		case 55: goto st55;
		case 56: goto st56;
		case 57: goto st57;
		case 58: goto st58;
		case 59: goto st59;
		case 60: goto st60;
		case 61: goto st61;
		case 62: goto st62;
		case 63: goto st63;
		case 64: goto st64;
		case 65: goto st65;
		case 66: goto st66;
		case 67: goto st67;
		case 68: goto st68;
		case 69: goto st69;
		case 70: goto st70;
		case 71: goto st71;
		case 72: goto st72;
		case 73: goto st73;
		case 74: goto st74;
		case 75: goto st75;
		case 76: goto st76;
		case 77: goto st77;
		case 78: goto st78;
		case 79: goto st79;
		case 80: goto st80;
		case 81: goto st81;
		case 82: goto st82;
		case 83: goto st83;
		case 84: goto st84;
		case 85: goto st85;
		case 86: goto st86;
		case 87: goto st87;
		case 88: goto st88;
		case 89: goto st89;
		case 90: goto st90;
		case 91: goto st91;
		case 92: goto st92;
		case 93: goto st93;
		case 94: goto st94;
		case 95: goto st95;
		case 96: goto st96;
		case 97: goto st97;
		case 98: goto st98;
		case 99: goto st99;
		case 100: goto st100;
		case 101: goto st101;
		case 102: goto st102;
		case 103: goto st103;
		case 104: goto st104;
		case 105: goto st105;
		case 106: goto st106;
		case 107: goto st107;
		case 108: goto st108;
		case 109: goto st109;
		case 110: goto st110;
		case 111: goto st111;
		case 112: goto st112;
		case 113: goto st113;
		case 114: goto st114;
		case 115: goto st115;
		case 116: goto st116;
		case 117: goto st117;
		case 118: goto st118;
		case 119: goto st119;
		case 120: goto st120;
		case 121: goto st121;
		case 122: goto st122;
		case 123: goto st123;
		case 124: goto st124;
		case 125: goto st125;
		case 126: goto st126;
		case 127: goto st127;
		case 128: goto st128;
		case 129: goto st129;
		case 130: goto st130;
		case 131: goto st131;
		case 132: goto st132;
		case 133: goto st133;
		case 134: goto st134;
		case 135: goto st135;
		case 136: goto st136;
		case 137: goto st137;
		case 138: goto st138;
		case 139: goto st139;
		case 140: goto st140;
		case 141: goto st141;
		case 142: goto st142;
		case 143: goto st143;
		case 144: goto st144;
		case 145: goto st145;
		case 146: goto st146;
		case 147: goto st147;
		case 148: goto st148;
		case 149: goto st149;
		case 150: goto st150;
		case 151: goto st151;
		case 152: goto st152;
		case 153: goto st153;
		case 154: goto st154;
		case 155: goto st155;
		case 156: goto st156;
		case 157: goto st157;
		case 158: goto st158;
		case 159: goto st159;
		case 160: goto st160;
		case 161: goto st161;
		case 162: goto st162;
		case 163: goto st163;
		case 164: goto st164;
		case 165: goto st165;
		case 166: goto st166;
		case 167: goto st167;
		case 168: goto st168;
		case 169: goto st169;
		case 170: goto st170;
		case 171: goto st171;
		case 172: goto st172;
		case 173: goto st173;
		case 174: goto st174;
		case 175: goto st175;
		case 176: goto st176;
		case 177: goto st177;
		case 178: goto st178;
		case 179: goto st179;
		case 180: goto st180;
		case 181: goto st181;
		case 182: goto st182;
		case 183: goto st183;
		case 184: goto st184;
		case 185: goto st185;
		case 186: goto st186;
		case 187: goto st187;
		case 188: goto st188;
		case 189: goto st189;
		case 190: goto st190;
		case 191: goto st191;
		case 192: goto st192;
		case 193: goto st193;
		case 194: goto st194;
		case 195: goto st195;
		case 196: goto st196;
		case 197: goto st197;
		case 198: goto st198;
		case 199: goto st199;
		case 200: goto st200;
		case 201: goto st201;
		case 202: goto st202;
		case 203: goto st203;
		case 204: goto st204;
		case 205: goto st205;
		case 206: goto st206;
		case 207: goto st207;
		case 208: goto st208;
		case 209: goto st209;
		case 210: goto st210;
		case 211: goto st211;
		case 212: goto st212;
		case 213: goto st213;
		case 214: goto st214;
		case 215: goto st215;
		case 216: goto st216;
		case 217: goto st217;
		case 218: goto st218;
		case 219: goto st219;
		case 220: goto st220;
		case 221: goto st221;
		case 222: goto st222;
		case 223: goto st223;
		case 224: goto st224;
		case 225: goto st225;
		case 226: goto st226;
		case 227: goto st227;
		case 228: goto st228;
		case 229: goto st229;
		case 230: goto st230;
		case 231: goto st231;
		case 232: goto st232;
		case 233: goto st233;
		case 234: goto st234;
		case 235: goto st235;
		case 236: goto st236;
		case 237: goto st237;
		case 238: goto st238;
		case 239: goto st239;
		case 240: goto st240;
		case 241: goto st241;
		case 242: goto st242;
		case 243: goto st243;
		case 244: goto st244;
		case 245: goto st245;
		case 246: goto st246;
		case 247: goto st247;
		case 248: goto st248;
		case 249: goto st249;
		case 250: goto st250;
		case 251: goto st251;
		case 252: goto st252;
		case 253: goto st253;
		case 254: goto st254;
		case 255: goto st255;
		case 256: goto st256;
		case 257: goto st257;
		case 258: goto st258;
		case 259: goto st259;
		case 260: goto st260;
		case 261: goto st261;
		case 262: goto st262;
		case 263: goto st263;
		case 264: goto st264;
		case 265: goto st265;
		case 266: goto st266;
		case 267: goto st267;
		case 268: goto st268;
		case 269: goto st269;
		case 270: goto st270;
		case 271: goto st271;
		case 272: goto st272;
		case 273: goto st273;
		case 274: goto st274;
		case 275: goto st275;
		case 276: goto st276;
		case 277: goto st277;
		case 278: goto st278;
		case 279: goto st279;
		case 280: goto st280;
		case 281: goto st281;
		case 282: goto st282;
		case 283: goto st283;
		case 284: goto st284;
		case 285: goto st285;
		case 286: goto st286;
		case 287: goto st287;
		case 288: goto st288;
		case 289: goto st289;
		case 290: goto st290;
		case 291: goto st291;
		case 292: goto st292;
		case 293: goto st293;
		case 294: goto st294;
		case 295: goto st295;
		case 296: goto st296;
		case 297: goto st297;
		case 298: goto st298;
		case 299: goto st299;
		case 300: goto st300;
		case 301: goto st301;
		case 302: goto st302;
		case 303: goto st303;
		case 304: goto st304;
		case 305: goto st305;
		case 306: goto st306;
		case 307: goto st307;
		case 308: goto st308;
		case 309: goto st309;
		case 310: goto st310;
		case 594: goto st594;
		case 311: goto st311;
		case 312: goto st312;
		case 313: goto st313;
		case 314: goto st314;
		case 315: goto st315;
		case 316: goto st316;
		case 317: goto st317;
		case 318: goto st318;
		case 319: goto st319;
		case 320: goto st320;
		case 321: goto st321;
		case 322: goto st322;
		case 323: goto st323;
		case 324: goto st324;
		case 325: goto st325;
		case 326: goto st326;
		case 327: goto st327;
		case 328: goto st328;
		case 329: goto st329;
		case 330: goto st330;
		case 331: goto st331;
		case 332: goto st332;
		case 333: goto st333;
		case 334: goto st334;
		case 335: goto st335;
		case 336: goto st336;
		case 337: goto st337;
		case 338: goto st338;
		case 339: goto st339;
		case 340: goto st340;
		case 341: goto st341;
		case 342: goto st342;
		case 343: goto st343;
		case 344: goto st344;
		case 345: goto st345;
		case 346: goto st346;
		case 347: goto st347;
		case 348: goto st348;
		case 349: goto st349;
		case 350: goto st350;
		case 351: goto st351;
		case 352: goto st352;
		case 353: goto st353;
		case 354: goto st354;
		case 355: goto st355;
		case 356: goto st356;
		case 357: goto st357;
		case 358: goto st358;
		case 359: goto st359;
		case 360: goto st360;
		case 361: goto st361;
		case 362: goto st362;
		case 363: goto st363;
		case 364: goto st364;
		case 365: goto st365;
		case 366: goto st366;
		case 367: goto st367;
		case 368: goto st368;
		case 369: goto st369;
		case 370: goto st370;
		case 371: goto st371;
		case 372: goto st372;
		case 373: goto st373;
		case 374: goto st374;
		case 375: goto st375;
		case 376: goto st376;
		case 377: goto st377;
		case 378: goto st378;
		case 379: goto st379;
		case 380: goto st380;
		case 381: goto st381;
		case 382: goto st382;
		case 383: goto st383;
		case 384: goto st384;
		case 385: goto st385;
		case 386: goto st386;
		case 387: goto st387;
		case 388: goto st388;
		case 389: goto st389;
		case 390: goto st390;
		case 391: goto st391;
		case 392: goto st392;
		case 393: goto st393;
		case 394: goto st394;
		case 395: goto st395;
		case 396: goto st396;
		case 397: goto st397;
		case 398: goto st398;
		case 399: goto st399;
		case 400: goto st400;
		case 401: goto st401;
		case 402: goto st402;
		case 403: goto st403;
		case 404: goto st404;
		case 405: goto st405;
		case 406: goto st406;
		case 407: goto st407;
		case 408: goto st408;
		case 409: goto st409;
		case 410: goto st410;
		case 411: goto st411;
		case 412: goto st412;
		case 413: goto st413;
		case 414: goto st414;
		case 415: goto st415;
		case 416: goto st416;
		case 417: goto st417;
		case 418: goto st418;
		case 419: goto st419;
		case 420: goto st420;
		case 421: goto st421;
		case 422: goto st422;
		case 423: goto st423;
		case 424: goto st424;
		case 425: goto st425;
		case 426: goto st426;
		case 427: goto st427;
		case 428: goto st428;
		case 429: goto st429;
		case 430: goto st430;
		case 431: goto st431;
		case 432: goto st432;
		case 433: goto st433;
		case 434: goto st434;
		case 435: goto st435;
		case 436: goto st436;
		case 437: goto st437;
		case 438: goto st438;
		case 439: goto st439;
		case 440: goto st440;
		case 441: goto st441;
		case 442: goto st442;
		case 443: goto st443;
		case 444: goto st444;
		case 445: goto st445;
		case 446: goto st446;
		case 447: goto st447;
		case 448: goto st448;
		case 449: goto st449;
		case 450: goto st450;
		case 451: goto st451;
		case 452: goto st452;
		case 453: goto st453;
		case 454: goto st454;
		case 455: goto st455;
		case 456: goto st456;
		case 457: goto st457;
		case 595: goto st595;
		case 458: goto st458;
		case 459: goto st459;
		case 460: goto st460;
		case 461: goto st461;
		case 462: goto st462;
		case 463: goto st463;
		case 464: goto st464;
		case 465: goto st465;
		case 466: goto st466;
		case 467: goto st467;
		case 468: goto st468;
		case 469: goto st469;
		case 470: goto st470;
		case 471: goto st471;
		case 472: goto st472;
		case 473: goto st473;
		case 474: goto st474;
		case 475: goto st475;
		case 476: goto st476;
		case 477: goto st477;
		case 478: goto st478;
		case 479: goto st479;
		case 480: goto st480;
		case 481: goto st481;
		case 482: goto st482;
		case 483: goto st483;
		case 484: goto st484;
		case 485: goto st485;
		case 486: goto st486;
		case 487: goto st487;
		case 488: goto st488;
		case 489: goto st489;
		case 490: goto st490;
		case 491: goto st491;
		case 492: goto st492;
		case 493: goto st493;
		case 494: goto st494;
		case 495: goto st495;
		case 496: goto st496;
		case 497: goto st497;
		case 498: goto st498;
		case 499: goto st499;
		case 500: goto st500;
		case 501: goto st501;
		case 502: goto st502;
		case 503: goto st503;
		case 504: goto st504;
		case 505: goto st505;
		case 506: goto st506;
		case 507: goto st507;
		case 508: goto st508;
		case 509: goto st509;
		case 510: goto st510;
		case 511: goto st511;
		case 512: goto st512;
		case 513: goto st513;
		case 514: goto st514;
		case 515: goto st515;
		case 516: goto st516;
		case 517: goto st517;
		case 518: goto st518;
		case 519: goto st519;
		case 520: goto st520;
		case 521: goto st521;
		case 522: goto st522;
		case 523: goto st523;
		case 524: goto st524;
		case 525: goto st525;
		case 526: goto st526;
		case 527: goto st527;
		case 528: goto st528;
		case 529: goto st529;
		case 530: goto st530;
		case 531: goto st531;
		case 532: goto st532;
		case 533: goto st533;
		case 534: goto st534;
		case 535: goto st535;
		case 536: goto st536;
		case 537: goto st537;
		case 538: goto st538;
		case 539: goto st539;
		case 540: goto st540;
		case 541: goto st541;
		case 542: goto st542;
		case 543: goto st543;
		case 544: goto st544;
		case 545: goto st545;
		case 546: goto st546;
		case 547: goto st547;
		case 548: goto st548;
		case 549: goto st549;
		case 550: goto st550;
		case 551: goto st551;
		case 552: goto st552;
		case 553: goto st553;
		case 554: goto st554;
		case 555: goto st555;
		case 556: goto st556;
		case 557: goto st557;
		case 558: goto st558;
		case 559: goto st559;
		case 560: goto st560;
		case 561: goto st561;
		case 562: goto st562;
		case 563: goto st563;
		case 564: goto st564;
		case 565: goto st565;
		case 566: goto st566;
		case 567: goto st567;
		case 568: goto st568;
		case 569: goto st569;
		case 570: goto st570;
		case 571: goto st571;
		case 572: goto st572;
		case 573: goto st573;
		case 574: goto st574;
		case 575: goto st575;
		case 576: goto st576;
		case 577: goto st577;
		case 578: goto st578;
		case 579: goto st579;
		case 580: goto st580;
		case 581: goto st581;
		case 582: goto st582;
		case 583: goto st583;
		case 584: goto st584;
		case 585: goto st585;
		case 586: goto st586;
		case 587: goto st587;
	default: break;
	}

	if ( ++( state.p) == ( state.pe) )
		goto _test_eof;
_resume:
	switch (  state.cs )
	{
st1:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1;
case 1:
	switch( (*( state.p)) ) {
		case 13: goto st1;
		case 32: goto st1;
		case 100: goto tr2;
		case 115: goto tr3;
		case 116: goto tr4;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1;
	goto st0;
st0:
 state.cs = 0;
	goto _out;
tr2:
#line 268 "configparser.rl"
	{ des = Design(); }
	goto st2;
tr846:
#line 271 "configparser.rl"
	{ init_design(des); }
#line 268 "configparser.rl"
	{ des = Design(); }
	goto st2;
tr851:
#line 233 "configparser.rl"
	{ init_species(spe); }
#line 268 "configparser.rl"
	{ des = Design(); }
	goto st2;
tr855:
#line 311 "configparser.rl"
	{ init_terrain(ter); }
#line 268 "configparser.rl"
	{ des = Design(); }
	goto st2;
st2:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof2;
case 2:
#line 802 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto tr5;
	goto st0;
tr5:
#line 268 "configparser.rl"
	{ des = Design(); }
	goto st3;
st3:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof3;
case 3:
#line 814 "configparser.h"
	if ( (*( state.p)) == 115 )
		goto tr6;
	goto st0;
tr6:
#line 268 "configparser.rl"
	{ des = Design(); }
	goto st4;
st4:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof4;
case 4:
#line 826 "configparser.h"
	if ( (*( state.p)) == 105 )
		goto tr7;
	goto st0;
tr7:
#line 268 "configparser.rl"
	{ des = Design(); }
	goto st5;
st5:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof5;
case 5:
#line 838 "configparser.h"
	if ( (*( state.p)) == 103 )
		goto tr8;
	goto st0;
tr8:
#line 268 "configparser.rl"
	{ des = Design(); }
	goto st6;
st6:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof6;
case 6:
#line 850 "configparser.h"
	if ( (*( state.p)) == 110 )
		goto tr9;
	goto st0;
tr9:
#line 268 "configparser.rl"
	{ des = Design(); }
	goto st7;
st7:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof7;
case 7:
#line 862 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st8;
		case 32: goto st8;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st8;
	goto st0;
st8:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof8;
case 8:
	switch( (*( state.p)) ) {
		case 13: goto st8;
		case 32: goto st8;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr11;
	} else if ( (*( state.p)) >= 9 )
		goto st8;
	goto st0;
tr11:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st9;
tr13:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st9;
st9:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof9;
case 9:
#line 904 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr12;
		case 32: goto tr12;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr13;
	} else if ( (*( state.p)) >= 9 )
		goto tr12;
	goto st0;
tr12:
#line 261 "configparser.rl"
	{ des.level = toint(state.match); }
	goto st10;
st10:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof10;
case 10:
#line 923 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st10;
		case 32: goto st10;
		case 95: goto tr15;
	}
	if ( (*( state.p)) < 48 ) {
		if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
			goto st10;
	} else if ( (*( state.p)) > 57 ) {
		if ( (*( state.p)) > 90 ) {
			if ( 97 <= (*( state.p)) && (*( state.p)) <= 122 )
				goto tr15;
		} else if ( (*( state.p)) >= 65 )
			goto tr15;
	} else
		goto tr15;
	goto st0;
tr15:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st11;
tr17:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st11;
st11:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof11;
case 11:
#line 961 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr16;
		case 32: goto tr16;
		case 95: goto tr17;
		case 123: goto tr18;
	}
	if ( (*( state.p)) < 48 ) {
		if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
			goto tr16;
	} else if ( (*( state.p)) > 57 ) {
		if ( (*( state.p)) > 90 ) {
			if ( 97 <= (*( state.p)) && (*( state.p)) <= 122 )
				goto tr17;
		} else if ( (*( state.p)) >= 65 )
			goto tr17;
	} else
		goto tr17;
	goto st0;
tr16:
#line 264 "configparser.rl"
	{ des.tag = state.match; }
	goto st12;
st12:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof12;
case 12:
#line 988 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st12;
		case 32: goto st12;
		case 123: goto tr20;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st12;
	goto st0;
tr18:
#line 264 "configparser.rl"
	{ des.tag = state.match; }
#line 270 "configparser.rl"
	{{ state.stack[ state.top++] = 588; goto st300;}}
	goto st588;
tr20:
#line 270 "configparser.rl"
	{{ state.stack[ state.top++] = 588; goto st300;}}
	goto st588;
st588:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof588;
case 588:
#line 1011 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr845;
		case 32: goto tr845;
		case 100: goto tr846;
		case 115: goto tr847;
		case 116: goto tr848;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr845;
	goto st0;
tr845:
#line 271 "configparser.rl"
	{ init_design(des); }
	goto st589;
tr850:
#line 233 "configparser.rl"
	{ init_species(spe); }
	goto st589;
tr854:
#line 311 "configparser.rl"
	{ init_terrain(ter); }
	goto st589;
st589:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof589;
case 589:
#line 1038 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st589;
		case 32: goto st589;
		case 100: goto tr2;
		case 115: goto tr3;
		case 116: goto tr4;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st589;
	goto st0;
tr3:
#line 230 "configparser.rl"
	{ spe = Species(); }
	goto st13;
tr847:
#line 271 "configparser.rl"
	{ init_design(des); }
#line 230 "configparser.rl"
	{ spe = Species(); }
	goto st13;
tr852:
#line 233 "configparser.rl"
	{ init_species(spe); }
#line 230 "configparser.rl"
	{ spe = Species(); }
	goto st13;
tr856:
#line 311 "configparser.rl"
	{ init_terrain(ter); }
#line 230 "configparser.rl"
	{ spe = Species(); }
	goto st13;
st13:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof13;
case 13:
#line 1075 "configparser.h"
	if ( (*( state.p)) == 112 )
		goto tr21;
	goto st0;
tr21:
#line 230 "configparser.rl"
	{ spe = Species(); }
	goto st14;
st14:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof14;
case 14:
#line 1087 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto tr22;
	goto st0;
tr22:
#line 230 "configparser.rl"
	{ spe = Species(); }
	goto st15;
st15:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof15;
case 15:
#line 1099 "configparser.h"
	if ( (*( state.p)) == 99 )
		goto tr23;
	goto st0;
tr23:
#line 230 "configparser.rl"
	{ spe = Species(); }
	goto st16;
st16:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof16;
case 16:
#line 1111 "configparser.h"
	if ( (*( state.p)) == 105 )
		goto tr24;
	goto st0;
tr24:
#line 230 "configparser.rl"
	{ spe = Species(); }
	goto st17;
st17:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof17;
case 17:
#line 1123 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto tr25;
	goto st0;
tr25:
#line 230 "configparser.rl"
	{ spe = Species(); }
	goto st18;
st18:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof18;
case 18:
#line 1135 "configparser.h"
	if ( (*( state.p)) == 115 )
		goto tr26;
	goto st0;
tr26:
#line 230 "configparser.rl"
	{ spe = Species(); }
	goto st19;
st19:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof19;
case 19:
#line 1147 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st20;
		case 32: goto st20;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st20;
	goto st0;
st20:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof20;
case 20:
	switch( (*( state.p)) ) {
		case 13: goto st20;
		case 32: goto st20;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr28;
	} else if ( (*( state.p)) >= 9 )
		goto st20;
	goto st0;
tr28:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st21;
tr30:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st21;
st21:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof21;
case 21:
#line 1189 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr29;
		case 32: goto tr29;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr30;
	} else if ( (*( state.p)) >= 9 )
		goto tr29;
	goto st0;
tr29:
#line 223 "configparser.rl"
	{ spe.level = toint(state.match); }
	goto st22;
st22:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof22;
case 22:
#line 1208 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st22;
		case 32: goto st22;
		case 95: goto tr32;
	}
	if ( (*( state.p)) < 48 ) {
		if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
			goto st22;
	} else if ( (*( state.p)) > 57 ) {
		if ( (*( state.p)) > 90 ) {
			if ( 97 <= (*( state.p)) && (*( state.p)) <= 122 )
				goto tr32;
		} else if ( (*( state.p)) >= 65 )
			goto tr32;
	} else
		goto tr32;
	goto st0;
tr32:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st23;
tr34:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st23;
st23:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof23;
case 23:
#line 1246 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr33;
		case 32: goto tr33;
		case 95: goto tr34;
		case 123: goto tr35;
	}
	if ( (*( state.p)) < 48 ) {
		if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
			goto tr33;
	} else if ( (*( state.p)) > 57 ) {
		if ( (*( state.p)) > 90 ) {
			if ( 97 <= (*( state.p)) && (*( state.p)) <= 122 )
				goto tr34;
		} else if ( (*( state.p)) >= 65 )
			goto tr34;
	} else
		goto tr34;
	goto st0;
tr33:
#line 226 "configparser.rl"
	{ spe.tag = state.match; }
	goto st24;
st24:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof24;
case 24:
#line 1273 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st24;
		case 32: goto st24;
		case 123: goto tr37;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st24;
	goto st0;
tr35:
#line 226 "configparser.rl"
	{ spe.tag = state.match; }
#line 232 "configparser.rl"
	{{ state.stack[ state.top++] = 590; goto st36;}}
	goto st590;
tr37:
#line 232 "configparser.rl"
	{{ state.stack[ state.top++] = 590; goto st36;}}
	goto st590;
st590:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof590;
case 590:
#line 1296 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr850;
		case 32: goto tr850;
		case 100: goto tr851;
		case 115: goto tr852;
		case 116: goto tr853;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr850;
	goto st0;
tr4:
#line 308 "configparser.rl"
	{ ter = Terrain(); }
	goto st25;
tr848:
#line 271 "configparser.rl"
	{ init_design(des); }
#line 308 "configparser.rl"
	{ ter = Terrain(); }
	goto st25;
tr853:
#line 233 "configparser.rl"
	{ init_species(spe); }
#line 308 "configparser.rl"
	{ ter = Terrain(); }
	goto st25;
tr857:
#line 311 "configparser.rl"
	{ init_terrain(ter); }
#line 308 "configparser.rl"
	{ ter = Terrain(); }
	goto st25;
st25:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof25;
case 25:
#line 1333 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto tr38;
	goto st0;
tr38:
#line 308 "configparser.rl"
	{ ter = Terrain(); }
	goto st26;
st26:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof26;
case 26:
#line 1345 "configparser.h"
	if ( (*( state.p)) == 114 )
		goto tr39;
	goto st0;
tr39:
#line 308 "configparser.rl"
	{ ter = Terrain(); }
	goto st27;
st27:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof27;
case 27:
#line 1357 "configparser.h"
	if ( (*( state.p)) == 114 )
		goto tr40;
	goto st0;
tr40:
#line 308 "configparser.rl"
	{ ter = Terrain(); }
	goto st28;
st28:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof28;
case 28:
#line 1369 "configparser.h"
	if ( (*( state.p)) == 97 )
		goto tr41;
	goto st0;
tr41:
#line 308 "configparser.rl"
	{ ter = Terrain(); }
	goto st29;
st29:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof29;
case 29:
#line 1381 "configparser.h"
	if ( (*( state.p)) == 105 )
		goto tr42;
	goto st0;
tr42:
#line 308 "configparser.rl"
	{ ter = Terrain(); }
	goto st30;
st30:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof30;
case 30:
#line 1393 "configparser.h"
	if ( (*( state.p)) == 110 )
		goto tr43;
	goto st0;
tr43:
#line 308 "configparser.rl"
	{ ter = Terrain(); }
	goto st31;
st31:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof31;
case 31:
#line 1405 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st32;
		case 32: goto st32;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st32;
	goto st0;
st32:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof32;
case 32:
	switch( (*( state.p)) ) {
		case 13: goto st32;
		case 32: goto st32;
		case 95: goto tr45;
	}
	if ( (*( state.p)) < 48 ) {
		if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
			goto st32;
	} else if ( (*( state.p)) > 57 ) {
		if ( (*( state.p)) > 90 ) {
			if ( 97 <= (*( state.p)) && (*( state.p)) <= 122 )
				goto tr45;
		} else if ( (*( state.p)) >= 65 )
			goto tr45;
	} else
		goto tr45;
	goto st0;
tr45:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st33;
tr47:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st33;
st33:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof33;
case 33:
#line 1454 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr46;
		case 32: goto tr46;
		case 95: goto tr47;
		case 123: goto tr48;
	}
	if ( (*( state.p)) < 48 ) {
		if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
			goto tr46;
	} else if ( (*( state.p)) > 57 ) {
		if ( (*( state.p)) > 90 ) {
			if ( 97 <= (*( state.p)) && (*( state.p)) <= 122 )
				goto tr47;
		} else if ( (*( state.p)) >= 65 )
			goto tr47;
	} else
		goto tr47;
	goto st0;
tr46:
#line 304 "configparser.rl"
	{ ter.tag = state.match; }
	goto st34;
st34:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof34;
case 34:
#line 1481 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st34;
		case 32: goto st34;
		case 123: goto tr50;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st34;
	goto st0;
tr48:
#line 304 "configparser.rl"
	{ ter.tag = state.match; }
#line 310 "configparser.rl"
	{{ state.stack[ state.top++] = 591; goto st449;}}
	goto st591;
tr50:
#line 310 "configparser.rl"
	{{ state.stack[ state.top++] = 591; goto st449;}}
	goto st591;
st591:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof591;
case 591:
#line 1504 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr854;
		case 32: goto tr854;
		case 100: goto tr855;
		case 115: goto tr856;
		case 116: goto tr857;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr854;
	goto st0;
st35:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof35;
case 35:
	switch( (*( state.p)) ) {
		case 34: goto tr51;
		case 92: goto tr52;
		case 110: goto tr53;
	}
	goto st0;
tr51:
#line 131 "configparser.rl"
	{ state.match += '"';  { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st592;
tr52:
#line 133 "configparser.rl"
	{ state.match += '\\'; { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st592;
tr53:
#line 132 "configparser.rl"
	{ state.match += '\n'; { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st592;
st592:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof592;
case 592:
#line 1541 "configparser.h"
	goto st0;
st36:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof36;
case 36:
	switch( (*( state.p)) ) {
		case 13: goto st36;
		case 32: goto st36;
		case 97: goto st37;
		case 99: goto st55;
		case 100: goto st95;
		case 104: goto st118;
		case 105: goto st153;
		case 109: goto st171;
		case 110: goto st195;
		case 114: goto st202;
		case 115: goto st209;
		case 125: goto st268;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st36;
	goto st0;
st37:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof37;
case 37:
	switch( (*( state.p)) ) {
		case 105: goto st38;
		case 116: goto st290;
	}
	goto st0;
st38:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof38;
case 38:
	switch( (*( state.p)) ) {
		case 13: goto st39;
		case 32: goto st39;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st39;
	goto st0;
st39:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof39;
case 39:
	switch( (*( state.p)) ) {
		case 13: goto st39;
		case 32: goto st39;
		case 105: goto st40;
		case 110: goto st269;
		case 114: goto st273;
		case 115: goto st279;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st39;
	goto st0;
st40:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof40;
case 40:
	if ( (*( state.p)) == 110 )
		goto st41;
	goto st0;
st41:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof41;
case 41:
	if ( (*( state.p)) == 114 )
		goto st42;
	goto st0;
st42:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof42;
case 42:
	if ( (*( state.p)) == 97 )
		goto st43;
	goto st0;
st43:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof43;
case 43:
	if ( (*( state.p)) == 110 )
		goto st44;
	goto st0;
st44:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof44;
case 44:
	if ( (*( state.p)) == 103 )
		goto st45;
	goto st0;
st45:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof45;
case 45:
	if ( (*( state.p)) == 101 )
		goto st46;
	goto st0;
st46:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof46;
case 46:
	if ( (*( state.p)) == 95 )
		goto st47;
	goto st0;
st47:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof47;
case 47:
	if ( (*( state.p)) == 114 )
		goto st48;
	goto st0;
st48:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof48;
case 48:
	if ( (*( state.p)) == 97 )
		goto st49;
	goto st0;
st49:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof49;
case 49:
	if ( (*( state.p)) == 110 )
		goto st50;
	goto st0;
st50:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof50;
case 50:
	if ( (*( state.p)) == 100 )
		goto st51;
	goto st0;
st51:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof51;
case 51:
	if ( (*( state.p)) == 111 )
		goto st52;
	goto st0;
st52:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof52;
case 52:
	if ( (*( state.p)) == 109 )
		goto st53;
	goto st0;
st53:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof53;
case 53:
	switch( (*( state.p)) ) {
		case 13: goto tr85;
		case 32: goto tr85;
		case 59: goto tr86;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr85;
	goto st0;
tr85:
#line 174 "configparser.rl"
	{ spe.ai = Species::ai_t::inrange_random; }
	goto st54;
tr108:
#line 199 "configparser.rl"
	{ spe.clumpsize.deviation = toreal(state.match); }
	goto st54;
tr132:
#line 204 "configparser.rl"
	{ spe.companion.back().chance = toreal(state.match); }
	goto st54;
tr140:
#line 186 "configparser.rl"
	{ spe.count = toint(state.match); }
	goto st54;
tr154:
#line 195 "configparser.rl"
	{ spe.defense = toreal(state.match); }
	goto st54;
tr171:
#line 209 "configparser.rl"
	{ spe.drop.back().chance = toreal(state.match); }
	goto st54;
tr191:
#line 167 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st54;
tr197:
#line 165 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st54;
tr207:
#line 168 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st54;
tr213:
#line 164 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st54;
tr217:
#line 166 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st54;
tr231:
#line 177 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st54;
tr238:
#line 178 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st54;
tr250:
#line 181 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st54;
tr257:
#line 184 "configparser.rl"
	{ spe.move = Species::move_t::corner; }
	goto st54;
tr263:
#line 182 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st54;
tr269:
#line 183 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st54;
tr279:
#line 187 "configparser.rl"
	{ spe.name = state.match; }
	goto st54;
tr287:
#line 193 "configparser.rl"
	{ spe.range = toint(state.match); }
	goto st54;
tr330:
#line 188 "configparser.rl"
	{ spe.skin = skin; }
	goto st54;
tr333:
#line 149 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 188 "configparser.rl"
	{ spe.skin = skin; }
	goto st54;
tr338:
#line 151 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 188 "configparser.rl"
	{ spe.skin = skin; }
	goto st54;
tr344:
#line 147 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 188 "configparser.rl"
	{ spe.skin = skin; }
	goto st54;
tr352:
#line 150 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 188 "configparser.rl"
	{ spe.skin = skin; }
	goto st54;
tr356:
#line 146 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 188 "configparser.rl"
	{ spe.skin = skin; }
	goto st54;
tr362:
#line 152 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 188 "configparser.rl"
	{ spe.skin = skin; }
	goto st54;
tr369:
#line 148 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 188 "configparser.rl"
	{ spe.skin = skin; }
	goto st54;
tr384:
#line 217 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st54;
tr389:
#line 171 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st54;
tr396:
#line 173 "configparser.rl"
	{ spe.ai = Species::ai_t::random; }
	goto st54;
tr408:
#line 172 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st54;
tr418:
#line 194 "configparser.rl"
	{ spe.attack = toreal(state.match); }
	goto st54;
st54:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof54;
case 54:
#line 1848 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st54;
		case 32: goto st54;
		case 59: goto st593;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st54;
	goto st0;
tr86:
#line 174 "configparser.rl"
	{ spe.ai = Species::ai_t::inrange_random; }
	goto st593;
tr110:
#line 199 "configparser.rl"
	{ spe.clumpsize.deviation = toreal(state.match); }
	goto st593;
tr134:
#line 204 "configparser.rl"
	{ spe.companion.back().chance = toreal(state.match); }
	goto st593;
tr142:
#line 186 "configparser.rl"
	{ spe.count = toint(state.match); }
	goto st593;
tr156:
#line 195 "configparser.rl"
	{ spe.defense = toreal(state.match); }
	goto st593;
tr173:
#line 209 "configparser.rl"
	{ spe.drop.back().chance = toreal(state.match); }
	goto st593;
tr192:
#line 167 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st593;
tr198:
#line 165 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st593;
tr208:
#line 168 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st593;
tr214:
#line 164 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st593;
tr218:
#line 166 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st593;
tr232:
#line 177 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st593;
tr239:
#line 178 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st593;
tr251:
#line 181 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st593;
tr258:
#line 184 "configparser.rl"
	{ spe.move = Species::move_t::corner; }
	goto st593;
tr264:
#line 182 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st593;
tr270:
#line 183 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st593;
tr280:
#line 187 "configparser.rl"
	{ spe.name = state.match; }
	goto st593;
tr289:
#line 193 "configparser.rl"
	{ spe.range = toint(state.match); }
	goto st593;
tr331:
#line 188 "configparser.rl"
	{ spe.skin = skin; }
	goto st593;
tr334:
#line 149 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 188 "configparser.rl"
	{ spe.skin = skin; }
	goto st593;
tr339:
#line 151 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 188 "configparser.rl"
	{ spe.skin = skin; }
	goto st593;
tr345:
#line 147 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 188 "configparser.rl"
	{ spe.skin = skin; }
	goto st593;
tr353:
#line 150 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 188 "configparser.rl"
	{ spe.skin = skin; }
	goto st593;
tr357:
#line 146 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 188 "configparser.rl"
	{ spe.skin = skin; }
	goto st593;
tr363:
#line 152 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 188 "configparser.rl"
	{ spe.skin = skin; }
	goto st593;
tr370:
#line 148 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 188 "configparser.rl"
	{ spe.skin = skin; }
	goto st593;
tr385:
#line 217 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st593;
tr390:
#line 171 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st593;
tr397:
#line 173 "configparser.rl"
	{ spe.ai = Species::ai_t::random; }
	goto st593;
tr409:
#line 172 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st593;
tr420:
#line 194 "configparser.rl"
	{ spe.attack = toreal(state.match); }
	goto st593;
st593:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof593;
case 593:
#line 2003 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st36;
		case 32: goto st36;
		case 97: goto st37;
		case 99: goto st55;
		case 100: goto st95;
		case 104: goto st118;
		case 105: goto st153;
		case 109: goto st171;
		case 110: goto st195;
		case 114: goto st202;
		case 115: goto st209;
		case 125: goto st268;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st36;
	goto st0;
st55:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof55;
case 55:
	switch( (*( state.p)) ) {
		case 108: goto st56;
		case 111: goto st74;
	}
	goto st0;
st56:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof56;
case 56:
	if ( (*( state.p)) == 117 )
		goto st57;
	goto st0;
st57:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof57;
case 57:
	if ( (*( state.p)) == 109 )
		goto st58;
	goto st0;
st58:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof58;
case 58:
	if ( (*( state.p)) == 112 )
		goto st59;
	goto st0;
st59:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof59;
case 59:
	if ( (*( state.p)) == 115 )
		goto st60;
	goto st0;
st60:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof60;
case 60:
	if ( (*( state.p)) == 105 )
		goto st61;
	goto st0;
st61:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof61;
case 61:
	if ( (*( state.p)) == 122 )
		goto st62;
	goto st0;
st62:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof62;
case 62:
	if ( (*( state.p)) == 101 )
		goto st63;
	goto st0;
st63:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof63;
case 63:
	switch( (*( state.p)) ) {
		case 13: goto st64;
		case 32: goto st64;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st64;
	goto st0;
st64:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof64;
case 64:
	switch( (*( state.p)) ) {
		case 13: goto st64;
		case 32: goto st64;
		case 45: goto tr99;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr100;
	} else if ( (*( state.p)) >= 9 )
		goto st64;
	goto st0;
tr99:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st65;
st65:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof65;
case 65:
#line 2119 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr101;
	goto st0;
tr100:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st66;
tr101:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st66;
st66:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof66;
case 66:
#line 2143 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr102;
		case 32: goto tr102;
		case 46: goto tr103;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr101;
	} else if ( (*( state.p)) >= 9 )
		goto tr102;
	goto st0;
tr102:
#line 198 "configparser.rl"
	{ spe.clumpsize.mean = toreal(state.match); }
	goto st67;
st67:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof67;
case 67:
#line 2163 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st67;
		case 32: goto st67;
		case 45: goto tr105;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr106;
	} else if ( (*( state.p)) >= 9 )
		goto st67;
	goto st0;
tr105:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st68;
st68:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof68;
case 68:
#line 2189 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr107;
	goto st0;
tr106:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st69;
tr107:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st69;
st69:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof69;
case 69:
#line 2213 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr108;
		case 32: goto tr108;
		case 46: goto tr109;
		case 59: goto tr110;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr107;
	} else if ( (*( state.p)) >= 9 )
		goto tr108;
	goto st0;
tr109:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st70;
st70:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof70;
case 70:
#line 2236 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr111;
	goto st0;
tr111:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st71;
st71:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof71;
case 71:
#line 2250 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr108;
		case 32: goto tr108;
		case 59: goto tr110;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr111;
	} else if ( (*( state.p)) >= 9 )
		goto tr108;
	goto st0;
tr103:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st72;
st72:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof72;
case 72:
#line 2272 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr112;
	goto st0;
tr112:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st73;
st73:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof73;
case 73:
#line 2286 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr102;
		case 32: goto tr102;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr112;
	} else if ( (*( state.p)) >= 9 )
		goto tr102;
	goto st0;
st74:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof74;
case 74:
	switch( (*( state.p)) ) {
		case 109: goto st75;
		case 117: goto st90;
	}
	goto st0;
st75:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof75;
case 75:
	if ( (*( state.p)) == 112 )
		goto st76;
	goto st0;
st76:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof76;
case 76:
	if ( (*( state.p)) == 97 )
		goto st77;
	goto st0;
st77:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof77;
case 77:
	if ( (*( state.p)) == 110 )
		goto st78;
	goto st0;
st78:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof78;
case 78:
	if ( (*( state.p)) == 105 )
		goto st79;
	goto st0;
st79:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof79;
case 79:
	if ( (*( state.p)) == 111 )
		goto st80;
	goto st0;
st80:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof80;
case 80:
	if ( (*( state.p)) == 110 )
		goto st81;
	goto st0;
st81:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof81;
case 81:
	switch( (*( state.p)) ) {
		case 13: goto tr121;
		case 32: goto tr121;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr121;
	goto st0;
tr121:
#line 202 "configparser.rl"
	{ spe.companion.push_back(Species::companion_t()); }
	goto st82;
st82:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof82;
case 82:
#line 2367 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st82;
		case 32: goto st82;
		case 34: goto tr123;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st82;
	goto st0;
tr124:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st83;
tr123:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
	goto st83;
tr126:
#line 137 "configparser.rl"
	{{ state.stack[ state.top++] = 83; goto st35;}}
	goto st83;
st83:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof83;
case 83:
#line 2396 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st84;
		case 92: goto tr126;
	}
	goto tr124;
st84:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof84;
case 84:
	switch( (*( state.p)) ) {
		case 13: goto tr127;
		case 32: goto tr127;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr127;
	goto st0;
tr127:
#line 203 "configparser.rl"
	{ spe.companion.back().tag = state.match; }
	goto st85;
st85:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof85;
case 85:
#line 2421 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st85;
		case 32: goto st85;
		case 45: goto tr129;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr130;
	} else if ( (*( state.p)) >= 9 )
		goto st85;
	goto st0;
tr129:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st86;
st86:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof86;
case 86:
#line 2447 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr131;
	goto st0;
tr130:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st87;
tr131:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st87;
st87:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof87;
case 87:
#line 2471 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr132;
		case 32: goto tr132;
		case 46: goto tr133;
		case 59: goto tr134;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr131;
	} else if ( (*( state.p)) >= 9 )
		goto tr132;
	goto st0;
tr133:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st88;
st88:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof88;
case 88:
#line 2494 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr135;
	goto st0;
tr135:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st89;
st89:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof89;
case 89:
#line 2508 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr132;
		case 32: goto tr132;
		case 59: goto tr134;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr135;
	} else if ( (*( state.p)) >= 9 )
		goto tr132;
	goto st0;
st90:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof90;
case 90:
	if ( (*( state.p)) == 110 )
		goto st91;
	goto st0;
st91:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof91;
case 91:
	if ( (*( state.p)) == 116 )
		goto st92;
	goto st0;
st92:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof92;
case 92:
	switch( (*( state.p)) ) {
		case 13: goto st93;
		case 32: goto st93;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st93;
	goto st0;
st93:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof93;
case 93:
	switch( (*( state.p)) ) {
		case 13: goto st93;
		case 32: goto st93;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr139;
	} else if ( (*( state.p)) >= 9 )
		goto st93;
	goto st0;
tr139:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st94;
tr141:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st94;
st94:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof94;
case 94:
#line 2579 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr140;
		case 32: goto tr140;
		case 59: goto tr142;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr141;
	} else if ( (*( state.p)) >= 9 )
		goto tr140;
	goto st0;
st95:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof95;
case 95:
	switch( (*( state.p)) ) {
		case 101: goto st96;
		case 114: goto st107;
	}
	goto st0;
st96:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof96;
case 96:
	if ( (*( state.p)) == 102 )
		goto st97;
	goto st0;
st97:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof97;
case 97:
	if ( (*( state.p)) == 101 )
		goto st98;
	goto st0;
st98:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof98;
case 98:
	if ( (*( state.p)) == 110 )
		goto st99;
	goto st0;
st99:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof99;
case 99:
	if ( (*( state.p)) == 115 )
		goto st100;
	goto st0;
st100:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof100;
case 100:
	if ( (*( state.p)) == 101 )
		goto st101;
	goto st0;
st101:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof101;
case 101:
	switch( (*( state.p)) ) {
		case 13: goto st102;
		case 32: goto st102;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st102;
	goto st0;
st102:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof102;
case 102:
	switch( (*( state.p)) ) {
		case 13: goto st102;
		case 32: goto st102;
		case 45: goto tr151;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr152;
	} else if ( (*( state.p)) >= 9 )
		goto st102;
	goto st0;
tr151:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st103;
st103:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof103;
case 103:
#line 2675 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr153;
	goto st0;
tr152:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st104;
tr153:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st104;
st104:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof104;
case 104:
#line 2699 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr154;
		case 32: goto tr154;
		case 46: goto tr155;
		case 59: goto tr156;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr153;
	} else if ( (*( state.p)) >= 9 )
		goto tr154;
	goto st0;
tr155:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st105;
st105:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof105;
case 105:
#line 2722 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr157;
	goto st0;
tr157:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st106;
st106:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof106;
case 106:
#line 2736 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr154;
		case 32: goto tr154;
		case 59: goto tr156;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr157;
	} else if ( (*( state.p)) >= 9 )
		goto tr154;
	goto st0;
st107:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof107;
case 107:
	if ( (*( state.p)) == 111 )
		goto st108;
	goto st0;
st108:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof108;
case 108:
	if ( (*( state.p)) == 112 )
		goto st109;
	goto st0;
st109:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof109;
case 109:
	switch( (*( state.p)) ) {
		case 13: goto tr160;
		case 32: goto tr160;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr160;
	goto st0;
tr160:
#line 207 "configparser.rl"
	{ spe.drop.push_back(Species::drop_t()); }
	goto st110;
st110:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof110;
case 110:
#line 2781 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st110;
		case 32: goto st110;
		case 34: goto tr162;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st110;
	goto st0;
tr163:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st111;
tr162:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
	goto st111;
tr165:
#line 137 "configparser.rl"
	{{ state.stack[ state.top++] = 111; goto st35;}}
	goto st111;
st111:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof111;
case 111:
#line 2810 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st112;
		case 92: goto tr165;
	}
	goto tr163;
st112:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof112;
case 112:
	switch( (*( state.p)) ) {
		case 13: goto tr166;
		case 32: goto tr166;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr166;
	goto st0;
tr166:
#line 208 "configparser.rl"
	{ spe.drop.back().tag = state.match; }
	goto st113;
st113:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof113;
case 113:
#line 2835 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st113;
		case 32: goto st113;
		case 45: goto tr168;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr169;
	} else if ( (*( state.p)) >= 9 )
		goto st113;
	goto st0;
tr168:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st114;
st114:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof114;
case 114:
#line 2861 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr170;
	goto st0;
tr169:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st115;
tr170:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st115;
st115:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof115;
case 115:
#line 2885 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr171;
		case 32: goto tr171;
		case 46: goto tr172;
		case 59: goto tr173;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr170;
	} else if ( (*( state.p)) >= 9 )
		goto tr171;
	goto st0;
tr172:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st116;
st116:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof116;
case 116:
#line 2908 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr174;
	goto st0;
tr174:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st117;
st117:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof117;
case 117:
#line 2922 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr171;
		case 32: goto tr171;
		case 59: goto tr173;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr174;
	} else if ( (*( state.p)) >= 9 )
		goto tr171;
	goto st0;
st118:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof118;
case 118:
	if ( (*( state.p)) == 97 )
		goto st119;
	goto st0;
st119:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof119;
case 119:
	if ( (*( state.p)) == 98 )
		goto st120;
	goto st0;
st120:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof120;
case 120:
	if ( (*( state.p)) == 105 )
		goto st121;
	goto st0;
st121:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof121;
case 121:
	if ( (*( state.p)) == 116 )
		goto st122;
	goto st0;
st122:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof122;
case 122:
	if ( (*( state.p)) == 97 )
		goto st123;
	goto st0;
st123:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof123;
case 123:
	if ( (*( state.p)) == 116 )
		goto st124;
	goto st0;
st124:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof124;
case 124:
	switch( (*( state.p)) ) {
		case 13: goto st125;
		case 32: goto st125;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st125;
	goto st0;
st125:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof125;
case 125:
	switch( (*( state.p)) ) {
		case 13: goto st125;
		case 32: goto st125;
		case 99: goto st126;
		case 102: goto st132;
		case 115: goto st137;
		case 119: goto st146;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st125;
	goto st0;
st126:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof126;
case 126:
	if ( (*( state.p)) == 111 )
		goto st127;
	goto st0;
st127:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof127;
case 127:
	if ( (*( state.p)) == 114 )
		goto st128;
	goto st0;
st128:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof128;
case 128:
	if ( (*( state.p)) == 110 )
		goto st129;
	goto st0;
st129:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof129;
case 129:
	if ( (*( state.p)) == 101 )
		goto st130;
	goto st0;
st130:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof130;
case 130:
	if ( (*( state.p)) == 114 )
		goto st131;
	goto st0;
st131:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof131;
case 131:
	switch( (*( state.p)) ) {
		case 13: goto tr191;
		case 32: goto tr191;
		case 59: goto tr192;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr191;
	goto st0;
st132:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof132;
case 132:
	if ( (*( state.p)) == 108 )
		goto st133;
	goto st0;
st133:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof133;
case 133:
	if ( (*( state.p)) == 111 )
		goto st134;
	goto st0;
st134:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof134;
case 134:
	if ( (*( state.p)) == 111 )
		goto st135;
	goto st0;
st135:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof135;
case 135:
	if ( (*( state.p)) == 114 )
		goto st136;
	goto st0;
st136:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof136;
case 136:
	switch( (*( state.p)) ) {
		case 13: goto tr197;
		case 32: goto tr197;
		case 59: goto tr198;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr197;
	goto st0;
st137:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof137;
case 137:
	if ( (*( state.p)) == 104 )
		goto st138;
	goto st0;
st138:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof138;
case 138:
	if ( (*( state.p)) == 111 )
		goto st139;
	goto st0;
st139:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof139;
case 139:
	if ( (*( state.p)) == 114 )
		goto st140;
	goto st0;
st140:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof140;
case 140:
	if ( (*( state.p)) == 101 )
		goto st141;
	goto st0;
st141:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof141;
case 141:
	if ( (*( state.p)) == 108 )
		goto st142;
	goto st0;
st142:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof142;
case 142:
	if ( (*( state.p)) == 105 )
		goto st143;
	goto st0;
st143:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof143;
case 143:
	if ( (*( state.p)) == 110 )
		goto st144;
	goto st0;
st144:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof144;
case 144:
	if ( (*( state.p)) == 101 )
		goto st145;
	goto st0;
st145:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof145;
case 145:
	switch( (*( state.p)) ) {
		case 13: goto tr207;
		case 32: goto tr207;
		case 59: goto tr208;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr207;
	goto st0;
st146:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof146;
case 146:
	if ( (*( state.p)) == 97 )
		goto st147;
	goto st0;
st147:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof147;
case 147:
	switch( (*( state.p)) ) {
		case 108: goto st148;
		case 116: goto st150;
	}
	goto st0;
st148:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof148;
case 148:
	if ( (*( state.p)) == 107 )
		goto st149;
	goto st0;
st149:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof149;
case 149:
	switch( (*( state.p)) ) {
		case 13: goto tr213;
		case 32: goto tr213;
		case 59: goto tr214;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr213;
	goto st0;
st150:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof150;
case 150:
	if ( (*( state.p)) == 101 )
		goto st151;
	goto st0;
st151:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof151;
case 151:
	if ( (*( state.p)) == 114 )
		goto st152;
	goto st0;
st152:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof152;
case 152:
	switch( (*( state.p)) ) {
		case 13: goto tr217;
		case 32: goto tr217;
		case 59: goto tr218;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr217;
	goto st0;
st153:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof153;
case 153:
	if ( (*( state.p)) == 100 )
		goto st154;
	goto st0;
st154:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof154;
case 154:
	if ( (*( state.p)) == 108 )
		goto st155;
	goto st0;
st155:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof155;
case 155:
	if ( (*( state.p)) == 101 )
		goto st156;
	goto st0;
st156:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof156;
case 156:
	if ( (*( state.p)) == 95 )
		goto st157;
	goto st0;
st157:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof157;
case 157:
	if ( (*( state.p)) == 97 )
		goto st158;
	goto st0;
st158:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof158;
case 158:
	if ( (*( state.p)) == 105 )
		goto st159;
	goto st0;
st159:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof159;
case 159:
	switch( (*( state.p)) ) {
		case 13: goto st160;
		case 32: goto st160;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st160;
	goto st0;
st160:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof160;
case 160:
	switch( (*( state.p)) ) {
		case 13: goto st160;
		case 32: goto st160;
		case 110: goto st161;
		case 114: goto st165;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st160;
	goto st0;
st161:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof161;
case 161:
	if ( (*( state.p)) == 111 )
		goto st162;
	goto st0;
st162:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof162;
case 162:
	if ( (*( state.p)) == 110 )
		goto st163;
	goto st0;
st163:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof163;
case 163:
	if ( (*( state.p)) == 101 )
		goto st164;
	goto st0;
st164:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof164;
case 164:
	switch( (*( state.p)) ) {
		case 13: goto tr231;
		case 32: goto tr231;
		case 59: goto tr232;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr231;
	goto st0;
st165:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof165;
case 165:
	if ( (*( state.p)) == 97 )
		goto st166;
	goto st0;
st166:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof166;
case 166:
	if ( (*( state.p)) == 110 )
		goto st167;
	goto st0;
st167:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof167;
case 167:
	if ( (*( state.p)) == 100 )
		goto st168;
	goto st0;
st168:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof168;
case 168:
	if ( (*( state.p)) == 111 )
		goto st169;
	goto st0;
st169:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof169;
case 169:
	if ( (*( state.p)) == 109 )
		goto st170;
	goto st0;
st170:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof170;
case 170:
	switch( (*( state.p)) ) {
		case 13: goto tr238;
		case 32: goto tr238;
		case 59: goto tr239;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr238;
	goto st0;
st171:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof171;
case 171:
	if ( (*( state.p)) == 111 )
		goto st172;
	goto st0;
st172:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof172;
case 172:
	if ( (*( state.p)) == 118 )
		goto st173;
	goto st0;
st173:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof173;
case 173:
	if ( (*( state.p)) == 101 )
		goto st174;
	goto st0;
st174:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof174;
case 174:
	switch( (*( state.p)) ) {
		case 13: goto st175;
		case 32: goto st175;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st175;
	goto st0;
st175:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof175;
case 175:
	switch( (*( state.p)) ) {
		case 13: goto st175;
		case 32: goto st175;
		case 97: goto st176;
		case 99: goto st179;
		case 102: goto st185;
		case 119: goto st190;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st175;
	goto st0;
st176:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof176;
case 176:
	if ( (*( state.p)) == 110 )
		goto st177;
	goto st0;
st177:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof177;
case 177:
	if ( (*( state.p)) == 121 )
		goto st178;
	goto st0;
st178:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof178;
case 178:
	switch( (*( state.p)) ) {
		case 13: goto tr250;
		case 32: goto tr250;
		case 59: goto tr251;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr250;
	goto st0;
st179:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof179;
case 179:
	if ( (*( state.p)) == 111 )
		goto st180;
	goto st0;
st180:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof180;
case 180:
	if ( (*( state.p)) == 114 )
		goto st181;
	goto st0;
st181:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof181;
case 181:
	if ( (*( state.p)) == 110 )
		goto st182;
	goto st0;
st182:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof182;
case 182:
	if ( (*( state.p)) == 101 )
		goto st183;
	goto st0;
st183:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof183;
case 183:
	if ( (*( state.p)) == 114 )
		goto st184;
	goto st0;
st184:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof184;
case 184:
	switch( (*( state.p)) ) {
		case 13: goto tr257;
		case 32: goto tr257;
		case 59: goto tr258;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr257;
	goto st0;
st185:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof185;
case 185:
	if ( (*( state.p)) == 108 )
		goto st186;
	goto st0;
st186:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof186;
case 186:
	if ( (*( state.p)) == 111 )
		goto st187;
	goto st0;
st187:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof187;
case 187:
	if ( (*( state.p)) == 111 )
		goto st188;
	goto st0;
st188:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof188;
case 188:
	if ( (*( state.p)) == 114 )
		goto st189;
	goto st0;
st189:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof189;
case 189:
	switch( (*( state.p)) ) {
		case 13: goto tr263;
		case 32: goto tr263;
		case 59: goto tr264;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr263;
	goto st0;
st190:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof190;
case 190:
	if ( (*( state.p)) == 97 )
		goto st191;
	goto st0;
st191:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof191;
case 191:
	if ( (*( state.p)) == 116 )
		goto st192;
	goto st0;
st192:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof192;
case 192:
	if ( (*( state.p)) == 101 )
		goto st193;
	goto st0;
st193:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof193;
case 193:
	if ( (*( state.p)) == 114 )
		goto st194;
	goto st0;
st194:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof194;
case 194:
	switch( (*( state.p)) ) {
		case 13: goto tr269;
		case 32: goto tr269;
		case 59: goto tr270;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr269;
	goto st0;
st195:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof195;
case 195:
	if ( (*( state.p)) == 97 )
		goto st196;
	goto st0;
st196:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof196;
case 196:
	if ( (*( state.p)) == 109 )
		goto st197;
	goto st0;
st197:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof197;
case 197:
	if ( (*( state.p)) == 101 )
		goto st198;
	goto st0;
st198:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof198;
case 198:
	switch( (*( state.p)) ) {
		case 13: goto st199;
		case 32: goto st199;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st199;
	goto st0;
st199:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof199;
case 199:
	switch( (*( state.p)) ) {
		case 13: goto st199;
		case 32: goto st199;
		case 34: goto tr275;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st199;
	goto st0;
tr276:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st200;
tr275:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
	goto st200;
tr278:
#line 137 "configparser.rl"
	{{ state.stack[ state.top++] = 200; goto st35;}}
	goto st200;
st200:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof200;
case 200:
#line 3628 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st201;
		case 92: goto tr278;
	}
	goto tr276;
st201:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof201;
case 201:
	switch( (*( state.p)) ) {
		case 13: goto tr279;
		case 32: goto tr279;
		case 59: goto tr280;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr279;
	goto st0;
st202:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof202;
case 202:
	if ( (*( state.p)) == 97 )
		goto st203;
	goto st0;
st203:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof203;
case 203:
	if ( (*( state.p)) == 110 )
		goto st204;
	goto st0;
st204:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof204;
case 204:
	if ( (*( state.p)) == 103 )
		goto st205;
	goto st0;
st205:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof205;
case 205:
	if ( (*( state.p)) == 101 )
		goto st206;
	goto st0;
st206:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof206;
case 206:
	switch( (*( state.p)) ) {
		case 13: goto st207;
		case 32: goto st207;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st207;
	goto st0;
st207:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof207;
case 207:
	switch( (*( state.p)) ) {
		case 13: goto st207;
		case 32: goto st207;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr286;
	} else if ( (*( state.p)) >= 9 )
		goto st207;
	goto st0;
tr286:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st208;
tr288:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st208;
st208:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof208;
case 208:
#line 3719 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr287;
		case 32: goto tr287;
		case 59: goto tr289;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr288;
	} else if ( (*( state.p)) >= 9 )
		goto tr287;
	goto st0;
st209:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof209;
case 209:
	if ( (*( state.p)) == 107 )
		goto st210;
	goto st0;
st210:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof210;
case 210:
	if ( (*( state.p)) == 105 )
		goto st211;
	goto st0;
st211:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof211;
case 211:
	if ( (*( state.p)) == 110 )
		goto st212;
	goto st0;
st212:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof212;
case 212:
	switch( (*( state.p)) ) {
		case 13: goto st213;
		case 32: goto st213;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st213;
	goto st0;
st213:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof213;
case 213:
	switch( (*( state.p)) ) {
		case 13: goto st213;
		case 32: goto st213;
		case 34: goto tr294;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st213;
	goto st0;
tr295:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st214;
tr294:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
	goto st214;
tr297:
#line 137 "configparser.rl"
	{{ state.stack[ state.top++] = 214; goto st35;}}
	goto st214;
st214:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof214;
case 214:
#line 3795 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st215;
		case 92: goto tr297;
	}
	goto tr295;
st215:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof215;
case 215:
	switch( (*( state.p)) ) {
		case 13: goto tr298;
		case 32: goto tr298;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr298;
	goto st0;
tr298:
#line 159 "configparser.rl"
	{ skin.text = state.match; }
	goto st216;
st216:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof216;
case 216:
#line 3820 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st216;
		case 32: goto st216;
		case 98: goto st217;
		case 100: goto st262;
		case 110: goto st265;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st216;
	goto st0;
st217:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof217;
case 217:
	if ( (*( state.p)) == 114 )
		goto st218;
	goto st0;
st218:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof218;
case 218:
	if ( (*( state.p)) == 105 )
		goto st219;
	goto st0;
st219:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof219;
case 219:
	if ( (*( state.p)) == 103 )
		goto st220;
	goto st0;
st220:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof220;
case 220:
	if ( (*( state.p)) == 104 )
		goto st221;
	goto st0;
st221:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof221;
case 221:
	if ( (*( state.p)) == 116 )
		goto st222;
	goto st0;
st222:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof222;
case 222:
	switch( (*( state.p)) ) {
		case 13: goto tr308;
		case 32: goto tr308;
		case 95: goto tr309;
		case 98: goto tr310;
		case 99: goto tr311;
		case 103: goto tr312;
		case 109: goto tr313;
		case 114: goto tr314;
		case 119: goto tr315;
		case 121: goto tr316;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr308;
	goto st0;
tr308:
#line 157 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st223;
tr373:
#line 156 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st223;
st223:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof223;
case 223:
#line 3897 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st223;
		case 32: goto st223;
		case 98: goto st224;
		case 99: goto st231;
		case 103: goto st235;
		case 109: goto st240;
		case 114: goto st247;
		case 119: goto st250;
		case 121: goto st255;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st223;
	goto st0;
tr310:
#line 157 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st224;
tr375:
#line 156 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st224;
st224:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof224;
case 224:
#line 3924 "configparser.h"
	if ( (*( state.p)) == 108 )
		goto st225;
	goto st0;
st225:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof225;
case 225:
	switch( (*( state.p)) ) {
		case 97: goto st226;
		case 117: goto st229;
	}
	goto st0;
st226:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof226;
case 226:
	if ( (*( state.p)) == 99 )
		goto st227;
	goto st0;
st227:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof227;
case 227:
	if ( (*( state.p)) == 107 )
		goto st228;
	goto st0;
st228:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof228;
case 228:
	switch( (*( state.p)) ) {
		case 13: goto tr330;
		case 32: goto tr330;
		case 59: goto tr331;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr330;
	goto st0;
st229:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof229;
case 229:
	if ( (*( state.p)) == 101 )
		goto st230;
	goto st0;
st230:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof230;
case 230:
	switch( (*( state.p)) ) {
		case 13: goto tr333;
		case 32: goto tr333;
		case 59: goto tr334;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr333;
	goto st0;
tr311:
#line 157 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st231;
tr376:
#line 156 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st231;
st231:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof231;
case 231:
#line 3994 "configparser.h"
	if ( (*( state.p)) == 121 )
		goto st232;
	goto st0;
st232:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof232;
case 232:
	if ( (*( state.p)) == 97 )
		goto st233;
	goto st0;
st233:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof233;
case 233:
	if ( (*( state.p)) == 110 )
		goto st234;
	goto st0;
st234:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof234;
case 234:
	switch( (*( state.p)) ) {
		case 13: goto tr338;
		case 32: goto tr338;
		case 59: goto tr339;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr338;
	goto st0;
tr312:
#line 157 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st235;
tr377:
#line 156 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st235;
st235:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof235;
case 235:
#line 4036 "configparser.h"
	if ( (*( state.p)) == 114 )
		goto st236;
	goto st0;
st236:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof236;
case 236:
	if ( (*( state.p)) == 101 )
		goto st237;
	goto st0;
st237:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof237;
case 237:
	if ( (*( state.p)) == 101 )
		goto st238;
	goto st0;
st238:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof238;
case 238:
	if ( (*( state.p)) == 110 )
		goto st239;
	goto st0;
st239:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof239;
case 239:
	switch( (*( state.p)) ) {
		case 13: goto tr344;
		case 32: goto tr344;
		case 59: goto tr345;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr344;
	goto st0;
tr313:
#line 157 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st240;
tr378:
#line 156 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st240;
st240:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof240;
case 240:
#line 4085 "configparser.h"
	if ( (*( state.p)) == 97 )
		goto st241;
	goto st0;
st241:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof241;
case 241:
	if ( (*( state.p)) == 103 )
		goto st242;
	goto st0;
st242:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof242;
case 242:
	if ( (*( state.p)) == 101 )
		goto st243;
	goto st0;
st243:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof243;
case 243:
	if ( (*( state.p)) == 110 )
		goto st244;
	goto st0;
st244:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof244;
case 244:
	if ( (*( state.p)) == 116 )
		goto st245;
	goto st0;
st245:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof245;
case 245:
	if ( (*( state.p)) == 97 )
		goto st246;
	goto st0;
st246:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof246;
case 246:
	switch( (*( state.p)) ) {
		case 13: goto tr352;
		case 32: goto tr352;
		case 59: goto tr353;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr352;
	goto st0;
tr314:
#line 157 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st247;
tr379:
#line 156 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st247;
st247:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof247;
case 247:
#line 4148 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st248;
	goto st0;
st248:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof248;
case 248:
	if ( (*( state.p)) == 100 )
		goto st249;
	goto st0;
st249:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof249;
case 249:
	switch( (*( state.p)) ) {
		case 13: goto tr356;
		case 32: goto tr356;
		case 59: goto tr357;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr356;
	goto st0;
tr315:
#line 157 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st250;
tr380:
#line 156 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st250;
st250:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof250;
case 250:
#line 4183 "configparser.h"
	if ( (*( state.p)) == 104 )
		goto st251;
	goto st0;
st251:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof251;
case 251:
	if ( (*( state.p)) == 105 )
		goto st252;
	goto st0;
st252:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof252;
case 252:
	if ( (*( state.p)) == 116 )
		goto st253;
	goto st0;
st253:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof253;
case 253:
	if ( (*( state.p)) == 101 )
		goto st254;
	goto st0;
st254:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof254;
case 254:
	switch( (*( state.p)) ) {
		case 13: goto tr362;
		case 32: goto tr362;
		case 59: goto tr363;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr362;
	goto st0;
tr316:
#line 157 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st255;
tr381:
#line 156 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st255;
st255:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof255;
case 255:
#line 4232 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st256;
	goto st0;
st256:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof256;
case 256:
	if ( (*( state.p)) == 108 )
		goto st257;
	goto st0;
st257:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof257;
case 257:
	if ( (*( state.p)) == 108 )
		goto st258;
	goto st0;
st258:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof258;
case 258:
	if ( (*( state.p)) == 111 )
		goto st259;
	goto st0;
st259:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof259;
case 259:
	if ( (*( state.p)) == 119 )
		goto st260;
	goto st0;
st260:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof260;
case 260:
	switch( (*( state.p)) ) {
		case 13: goto tr369;
		case 32: goto tr369;
		case 59: goto tr370;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr369;
	goto st0;
tr309:
#line 157 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st261;
tr374:
#line 156 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st261;
st261:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof261;
case 261:
#line 4288 "configparser.h"
	switch( (*( state.p)) ) {
		case 98: goto st224;
		case 99: goto st231;
		case 103: goto st235;
		case 109: goto st240;
		case 114: goto st247;
		case 119: goto st250;
		case 121: goto st255;
	}
	goto st0;
st262:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof262;
case 262:
	if ( (*( state.p)) == 105 )
		goto st263;
	goto st0;
st263:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof263;
case 263:
	if ( (*( state.p)) == 109 )
		goto st264;
	goto st0;
st264:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof264;
case 264:
	switch( (*( state.p)) ) {
		case 13: goto tr373;
		case 32: goto tr373;
		case 95: goto tr374;
		case 98: goto tr375;
		case 99: goto tr376;
		case 103: goto tr377;
		case 109: goto tr378;
		case 114: goto tr379;
		case 119: goto tr380;
		case 121: goto tr381;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr373;
	goto st0;
st265:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof265;
case 265:
	if ( (*( state.p)) == 111 )
		goto st266;
	goto st0;
st266:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof266;
case 266:
	if ( (*( state.p)) == 110 )
		goto st267;
	goto st0;
st267:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof267;
case 267:
	if ( (*( state.p)) == 101 )
		goto st228;
	goto st0;
st268:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof268;
case 268:
	switch( (*( state.p)) ) {
		case 13: goto tr384;
		case 32: goto tr384;
		case 59: goto tr385;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr384;
	goto st0;
st269:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof269;
case 269:
	if ( (*( state.p)) == 111 )
		goto st270;
	goto st0;
st270:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof270;
case 270:
	if ( (*( state.p)) == 110 )
		goto st271;
	goto st0;
st271:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof271;
case 271:
	if ( (*( state.p)) == 101 )
		goto st272;
	goto st0;
st272:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof272;
case 272:
	switch( (*( state.p)) ) {
		case 13: goto tr389;
		case 32: goto tr389;
		case 59: goto tr390;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr389;
	goto st0;
st273:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof273;
case 273:
	if ( (*( state.p)) == 97 )
		goto st274;
	goto st0;
st274:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof274;
case 274:
	if ( (*( state.p)) == 110 )
		goto st275;
	goto st0;
st275:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof275;
case 275:
	if ( (*( state.p)) == 100 )
		goto st276;
	goto st0;
st276:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof276;
case 276:
	if ( (*( state.p)) == 111 )
		goto st277;
	goto st0;
st277:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof277;
case 277:
	if ( (*( state.p)) == 109 )
		goto st278;
	goto st0;
st278:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof278;
case 278:
	switch( (*( state.p)) ) {
		case 13: goto tr396;
		case 32: goto tr396;
		case 59: goto tr397;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr396;
	goto st0;
st279:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof279;
case 279:
	if ( (*( state.p)) == 101 )
		goto st280;
	goto st0;
st280:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof280;
case 280:
	if ( (*( state.p)) == 101 )
		goto st281;
	goto st0;
st281:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof281;
case 281:
	if ( (*( state.p)) == 107 )
		goto st282;
	goto st0;
st282:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof282;
case 282:
	if ( (*( state.p)) == 95 )
		goto st283;
	goto st0;
st283:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof283;
case 283:
	if ( (*( state.p)) == 112 )
		goto st284;
	goto st0;
st284:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof284;
case 284:
	if ( (*( state.p)) == 108 )
		goto st285;
	goto st0;
st285:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof285;
case 285:
	if ( (*( state.p)) == 97 )
		goto st286;
	goto st0;
st286:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof286;
case 286:
	if ( (*( state.p)) == 121 )
		goto st287;
	goto st0;
st287:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof287;
case 287:
	if ( (*( state.p)) == 101 )
		goto st288;
	goto st0;
st288:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof288;
case 288:
	if ( (*( state.p)) == 114 )
		goto st289;
	goto st0;
st289:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof289;
case 289:
	switch( (*( state.p)) ) {
		case 13: goto tr408;
		case 32: goto tr408;
		case 59: goto tr409;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr408;
	goto st0;
st290:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof290;
case 290:
	if ( (*( state.p)) == 116 )
		goto st291;
	goto st0;
st291:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof291;
case 291:
	if ( (*( state.p)) == 97 )
		goto st292;
	goto st0;
st292:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof292;
case 292:
	if ( (*( state.p)) == 99 )
		goto st293;
	goto st0;
st293:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof293;
case 293:
	if ( (*( state.p)) == 107 )
		goto st294;
	goto st0;
st294:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof294;
case 294:
	switch( (*( state.p)) ) {
		case 13: goto st295;
		case 32: goto st295;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st295;
	goto st0;
st295:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof295;
case 295:
	switch( (*( state.p)) ) {
		case 13: goto st295;
		case 32: goto st295;
		case 45: goto tr415;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr416;
	} else if ( (*( state.p)) >= 9 )
		goto st295;
	goto st0;
tr415:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st296;
st296:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof296;
case 296:
#line 4595 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr417;
	goto st0;
tr416:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st297;
tr417:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st297;
st297:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof297;
case 297:
#line 4619 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr418;
		case 32: goto tr418;
		case 46: goto tr419;
		case 59: goto tr420;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr417;
	} else if ( (*( state.p)) >= 9 )
		goto tr418;
	goto st0;
tr419:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st298;
st298:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof298;
case 298:
#line 4642 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr421;
	goto st0;
tr421:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st299;
st299:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof299;
case 299:
#line 4656 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr418;
		case 32: goto tr418;
		case 59: goto tr420;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr421;
	} else if ( (*( state.p)) >= 9 )
		goto tr418;
	goto st0;
st300:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof300;
case 300:
	switch( (*( state.p)) ) {
		case 13: goto st300;
		case 32: goto st300;
		case 97: goto st301;
		case 99: goto st311;
		case 100: goto st318;
		case 104: goto st336;
		case 110: goto st345;
		case 115: goto st352;
		case 116: goto st428;
		case 117: goto st440;
		case 125: goto st446;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st300;
	goto st0;
st301:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof301;
case 301:
	if ( (*( state.p)) == 116 )
		goto st302;
	goto st0;
st302:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof302;
case 302:
	if ( (*( state.p)) == 116 )
		goto st303;
	goto st0;
st303:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof303;
case 303:
	if ( (*( state.p)) == 97 )
		goto st304;
	goto st0;
st304:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof304;
case 304:
	if ( (*( state.p)) == 99 )
		goto st305;
	goto st0;
st305:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof305;
case 305:
	if ( (*( state.p)) == 107 )
		goto st306;
	goto st0;
st306:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof306;
case 306:
	switch( (*( state.p)) ) {
		case 13: goto st307;
		case 32: goto st307;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st307;
	goto st0;
st307:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof307;
case 307:
	switch( (*( state.p)) ) {
		case 13: goto st307;
		case 32: goto st307;
		case 45: goto tr438;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr439;
	} else if ( (*( state.p)) >= 9 )
		goto st307;
	goto st0;
tr438:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st308;
st308:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof308;
case 308:
#line 4763 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr440;
	goto st0;
tr439:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st309;
tr440:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st309;
st309:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof309;
case 309:
#line 4787 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr441;
		case 32: goto tr441;
		case 46: goto tr442;
		case 59: goto tr443;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr440;
	} else if ( (*( state.p)) >= 9 )
		goto tr441;
	goto st0;
tr441:
#line 243 "configparser.rl"
	{ des.attack = toreal(state.match); }
	goto st310;
tr452:
#line 238 "configparser.rl"
	{ des.count = toint(state.match); }
	goto st310;
tr466:
#line 244 "configparser.rl"
	{ des.defense = toreal(state.match); }
	goto st310;
tr477:
#line 242 "configparser.rl"
	{ des.descr = state.match; }
	goto st310;
tr486:
#line 246 "configparser.rl"
	{ des.heal = toreal(state.match); }
	goto st310;
tr498:
#line 239 "configparser.rl"
	{ des.name = state.match; }
	goto st310;
tr542:
#line 240 "configparser.rl"
	{ des.skin = skin; }
	goto st310;
tr545:
#line 149 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 240 "configparser.rl"
	{ des.skin = skin; }
	goto st310;
tr550:
#line 151 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 240 "configparser.rl"
	{ des.skin = skin; }
	goto st310;
tr556:
#line 147 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 240 "configparser.rl"
	{ des.skin = skin; }
	goto st310;
tr564:
#line 150 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 240 "configparser.rl"
	{ des.skin = skin; }
	goto st310;
tr568:
#line 146 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 240 "configparser.rl"
	{ des.skin = skin; }
	goto st310;
tr574:
#line 152 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 240 "configparser.rl"
	{ des.skin = skin; }
	goto st310;
tr581:
#line 148 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 240 "configparser.rl"
	{ des.skin = skin; }
	goto st310;
tr603:
#line 241 "configparser.rl"
	{ des.slot = state.match; }
	goto st310;
tr615:
#line 245 "configparser.rl"
	{ des.stackrange = toint(state.match); }
	goto st310;
tr629:
#line 248 "configparser.rl"
	{ des.throwrange = toint(state.match); }
	goto st310;
tr637:
#line 247 "configparser.rl"
	{ des.usable = true; }
	goto st310;
tr639:
#line 255 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st310;
st310:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof310;
case 310:
#line 4894 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st310;
		case 32: goto st310;
		case 59: goto st594;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st310;
	goto st0;
tr443:
#line 243 "configparser.rl"
	{ des.attack = toreal(state.match); }
	goto st594;
tr454:
#line 238 "configparser.rl"
	{ des.count = toint(state.match); }
	goto st594;
tr468:
#line 244 "configparser.rl"
	{ des.defense = toreal(state.match); }
	goto st594;
tr478:
#line 242 "configparser.rl"
	{ des.descr = state.match; }
	goto st594;
tr488:
#line 246 "configparser.rl"
	{ des.heal = toreal(state.match); }
	goto st594;
tr499:
#line 239 "configparser.rl"
	{ des.name = state.match; }
	goto st594;
tr543:
#line 240 "configparser.rl"
	{ des.skin = skin; }
	goto st594;
tr546:
#line 149 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 240 "configparser.rl"
	{ des.skin = skin; }
	goto st594;
tr551:
#line 151 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 240 "configparser.rl"
	{ des.skin = skin; }
	goto st594;
tr557:
#line 147 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 240 "configparser.rl"
	{ des.skin = skin; }
	goto st594;
tr565:
#line 150 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 240 "configparser.rl"
	{ des.skin = skin; }
	goto st594;
tr569:
#line 146 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 240 "configparser.rl"
	{ des.skin = skin; }
	goto st594;
tr575:
#line 152 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 240 "configparser.rl"
	{ des.skin = skin; }
	goto st594;
tr582:
#line 148 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 240 "configparser.rl"
	{ des.skin = skin; }
	goto st594;
tr604:
#line 241 "configparser.rl"
	{ des.slot = state.match; }
	goto st594;
tr617:
#line 245 "configparser.rl"
	{ des.stackrange = toint(state.match); }
	goto st594;
tr631:
#line 248 "configparser.rl"
	{ des.throwrange = toint(state.match); }
	goto st594;
tr638:
#line 247 "configparser.rl"
	{ des.usable = true; }
	goto st594;
tr640:
#line 255 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st594;
st594:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof594;
case 594:
#line 4997 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st300;
		case 32: goto st300;
		case 97: goto st301;
		case 99: goto st311;
		case 100: goto st318;
		case 104: goto st336;
		case 110: goto st345;
		case 115: goto st352;
		case 116: goto st428;
		case 117: goto st440;
		case 125: goto st446;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st300;
	goto st0;
st311:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof311;
case 311:
	if ( (*( state.p)) == 111 )
		goto st312;
	goto st0;
st312:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof312;
case 312:
	if ( (*( state.p)) == 117 )
		goto st313;
	goto st0;
st313:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof313;
case 313:
	if ( (*( state.p)) == 110 )
		goto st314;
	goto st0;
st314:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof314;
case 314:
	if ( (*( state.p)) == 116 )
		goto st315;
	goto st0;
st315:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof315;
case 315:
	switch( (*( state.p)) ) {
		case 13: goto st316;
		case 32: goto st316;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st316;
	goto st0;
st316:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof316;
case 316:
	switch( (*( state.p)) ) {
		case 13: goto st316;
		case 32: goto st316;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr451;
	} else if ( (*( state.p)) >= 9 )
		goto st316;
	goto st0;
tr451:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st317;
tr453:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st317;
st317:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof317;
case 317:
#line 5087 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr452;
		case 32: goto tr452;
		case 59: goto tr454;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr453;
	} else if ( (*( state.p)) >= 9 )
		goto tr452;
	goto st0;
st318:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof318;
case 318:
	if ( (*( state.p)) == 101 )
		goto st319;
	goto st0;
st319:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof319;
case 319:
	switch( (*( state.p)) ) {
		case 102: goto st320;
		case 115: goto st330;
	}
	goto st0;
st320:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof320;
case 320:
	if ( (*( state.p)) == 101 )
		goto st321;
	goto st0;
st321:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof321;
case 321:
	if ( (*( state.p)) == 110 )
		goto st322;
	goto st0;
st322:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof322;
case 322:
	if ( (*( state.p)) == 115 )
		goto st323;
	goto st0;
st323:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof323;
case 323:
	if ( (*( state.p)) == 101 )
		goto st324;
	goto st0;
st324:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof324;
case 324:
	switch( (*( state.p)) ) {
		case 13: goto st325;
		case 32: goto st325;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st325;
	goto st0;
st325:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof325;
case 325:
	switch( (*( state.p)) ) {
		case 13: goto st325;
		case 32: goto st325;
		case 45: goto tr463;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr464;
	} else if ( (*( state.p)) >= 9 )
		goto st325;
	goto st0;
tr463:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st326;
st326:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof326;
case 326:
#line 5183 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr465;
	goto st0;
tr464:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st327;
tr465:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st327;
st327:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof327;
case 327:
#line 5207 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr466;
		case 32: goto tr466;
		case 46: goto tr467;
		case 59: goto tr468;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr465;
	} else if ( (*( state.p)) >= 9 )
		goto tr466;
	goto st0;
tr467:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st328;
st328:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof328;
case 328:
#line 5230 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr469;
	goto st0;
tr469:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st329;
st329:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof329;
case 329:
#line 5244 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr466;
		case 32: goto tr466;
		case 59: goto tr468;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr469;
	} else if ( (*( state.p)) >= 9 )
		goto tr466;
	goto st0;
st330:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof330;
case 330:
	if ( (*( state.p)) == 99 )
		goto st331;
	goto st0;
st331:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof331;
case 331:
	if ( (*( state.p)) == 114 )
		goto st332;
	goto st0;
st332:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof332;
case 332:
	switch( (*( state.p)) ) {
		case 13: goto st333;
		case 32: goto st333;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st333;
	goto st0;
st333:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof333;
case 333:
	switch( (*( state.p)) ) {
		case 13: goto st333;
		case 32: goto st333;
		case 34: goto tr473;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st333;
	goto st0;
tr474:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st334;
tr473:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
	goto st334;
tr476:
#line 137 "configparser.rl"
	{{ state.stack[ state.top++] = 334; goto st35;}}
	goto st334;
st334:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof334;
case 334:
#line 5313 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st335;
		case 92: goto tr476;
	}
	goto tr474;
st335:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof335;
case 335:
	switch( (*( state.p)) ) {
		case 13: goto tr477;
		case 32: goto tr477;
		case 59: goto tr478;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr477;
	goto st0;
st336:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof336;
case 336:
	if ( (*( state.p)) == 101 )
		goto st337;
	goto st0;
st337:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof337;
case 337:
	if ( (*( state.p)) == 97 )
		goto st338;
	goto st0;
st338:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof338;
case 338:
	if ( (*( state.p)) == 108 )
		goto st339;
	goto st0;
st339:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof339;
case 339:
	switch( (*( state.p)) ) {
		case 13: goto st340;
		case 32: goto st340;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st340;
	goto st0;
st340:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof340;
case 340:
	switch( (*( state.p)) ) {
		case 13: goto st340;
		case 32: goto st340;
		case 45: goto tr483;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr484;
	} else if ( (*( state.p)) >= 9 )
		goto st340;
	goto st0;
tr483:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st341;
st341:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof341;
case 341:
#line 5392 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr485;
	goto st0;
tr484:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st342;
tr485:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st342;
st342:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof342;
case 342:
#line 5416 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr486;
		case 32: goto tr486;
		case 46: goto tr487;
		case 59: goto tr488;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr485;
	} else if ( (*( state.p)) >= 9 )
		goto tr486;
	goto st0;
tr487:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st343;
st343:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof343;
case 343:
#line 5439 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr489;
	goto st0;
tr489:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st344;
st344:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof344;
case 344:
#line 5453 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr486;
		case 32: goto tr486;
		case 59: goto tr488;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr489;
	} else if ( (*( state.p)) >= 9 )
		goto tr486;
	goto st0;
st345:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof345;
case 345:
	if ( (*( state.p)) == 97 )
		goto st346;
	goto st0;
st346:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof346;
case 346:
	if ( (*( state.p)) == 109 )
		goto st347;
	goto st0;
st347:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof347;
case 347:
	if ( (*( state.p)) == 101 )
		goto st348;
	goto st0;
st348:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof348;
case 348:
	switch( (*( state.p)) ) {
		case 13: goto st349;
		case 32: goto st349;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st349;
	goto st0;
st349:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof349;
case 349:
	switch( (*( state.p)) ) {
		case 13: goto st349;
		case 32: goto st349;
		case 34: goto tr494;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st349;
	goto st0;
tr495:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st350;
tr494:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
	goto st350;
tr497:
#line 137 "configparser.rl"
	{{ state.stack[ state.top++] = 350; goto st35;}}
	goto st350;
st350:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof350;
case 350:
#line 5529 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st351;
		case 92: goto tr497;
	}
	goto tr495;
st351:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof351;
case 351:
	switch( (*( state.p)) ) {
		case 13: goto tr498;
		case 32: goto tr498;
		case 59: goto tr499;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr498;
	goto st0;
st352:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof352;
case 352:
	switch( (*( state.p)) ) {
		case 107: goto st353;
		case 108: goto st411;
		case 116: goto st417;
	}
	goto st0;
st353:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof353;
case 353:
	if ( (*( state.p)) == 105 )
		goto st354;
	goto st0;
st354:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof354;
case 354:
	if ( (*( state.p)) == 110 )
		goto st355;
	goto st0;
st355:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof355;
case 355:
	switch( (*( state.p)) ) {
		case 13: goto st356;
		case 32: goto st356;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st356;
	goto st0;
st356:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof356;
case 356:
	switch( (*( state.p)) ) {
		case 13: goto st356;
		case 32: goto st356;
		case 34: goto tr506;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st356;
	goto st0;
tr507:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st357;
tr506:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
	goto st357;
tr509:
#line 137 "configparser.rl"
	{{ state.stack[ state.top++] = 357; goto st35;}}
	goto st357;
st357:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof357;
case 357:
#line 5614 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st358;
		case 92: goto tr509;
	}
	goto tr507;
st358:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof358;
case 358:
	switch( (*( state.p)) ) {
		case 13: goto tr510;
		case 32: goto tr510;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr510;
	goto st0;
tr510:
#line 159 "configparser.rl"
	{ skin.text = state.match; }
	goto st359;
st359:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof359;
case 359:
#line 5639 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st359;
		case 32: goto st359;
		case 98: goto st360;
		case 100: goto st405;
		case 110: goto st408;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st359;
	goto st0;
st360:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof360;
case 360:
	if ( (*( state.p)) == 114 )
		goto st361;
	goto st0;
st361:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof361;
case 361:
	if ( (*( state.p)) == 105 )
		goto st362;
	goto st0;
st362:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof362;
case 362:
	if ( (*( state.p)) == 103 )
		goto st363;
	goto st0;
st363:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof363;
case 363:
	if ( (*( state.p)) == 104 )
		goto st364;
	goto st0;
st364:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof364;
case 364:
	if ( (*( state.p)) == 116 )
		goto st365;
	goto st0;
st365:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof365;
case 365:
	switch( (*( state.p)) ) {
		case 13: goto tr520;
		case 32: goto tr520;
		case 95: goto tr521;
		case 98: goto tr522;
		case 99: goto tr523;
		case 103: goto tr524;
		case 109: goto tr525;
		case 114: goto tr526;
		case 119: goto tr527;
		case 121: goto tr528;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr520;
	goto st0;
tr520:
#line 157 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st366;
tr585:
#line 156 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st366;
st366:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof366;
case 366:
#line 5716 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st366;
		case 32: goto st366;
		case 98: goto st367;
		case 99: goto st374;
		case 103: goto st378;
		case 109: goto st383;
		case 114: goto st390;
		case 119: goto st393;
		case 121: goto st398;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st366;
	goto st0;
tr522:
#line 157 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st367;
tr587:
#line 156 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st367;
st367:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof367;
case 367:
#line 5743 "configparser.h"
	if ( (*( state.p)) == 108 )
		goto st368;
	goto st0;
st368:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof368;
case 368:
	switch( (*( state.p)) ) {
		case 97: goto st369;
		case 117: goto st372;
	}
	goto st0;
st369:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof369;
case 369:
	if ( (*( state.p)) == 99 )
		goto st370;
	goto st0;
st370:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof370;
case 370:
	if ( (*( state.p)) == 107 )
		goto st371;
	goto st0;
st371:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof371;
case 371:
	switch( (*( state.p)) ) {
		case 13: goto tr542;
		case 32: goto tr542;
		case 59: goto tr543;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr542;
	goto st0;
st372:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof372;
case 372:
	if ( (*( state.p)) == 101 )
		goto st373;
	goto st0;
st373:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof373;
case 373:
	switch( (*( state.p)) ) {
		case 13: goto tr545;
		case 32: goto tr545;
		case 59: goto tr546;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr545;
	goto st0;
tr523:
#line 157 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st374;
tr588:
#line 156 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st374;
st374:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof374;
case 374:
#line 5813 "configparser.h"
	if ( (*( state.p)) == 121 )
		goto st375;
	goto st0;
st375:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof375;
case 375:
	if ( (*( state.p)) == 97 )
		goto st376;
	goto st0;
st376:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof376;
case 376:
	if ( (*( state.p)) == 110 )
		goto st377;
	goto st0;
st377:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof377;
case 377:
	switch( (*( state.p)) ) {
		case 13: goto tr550;
		case 32: goto tr550;
		case 59: goto tr551;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr550;
	goto st0;
tr524:
#line 157 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st378;
tr589:
#line 156 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st378;
st378:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof378;
case 378:
#line 5855 "configparser.h"
	if ( (*( state.p)) == 114 )
		goto st379;
	goto st0;
st379:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof379;
case 379:
	if ( (*( state.p)) == 101 )
		goto st380;
	goto st0;
st380:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof380;
case 380:
	if ( (*( state.p)) == 101 )
		goto st381;
	goto st0;
st381:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof381;
case 381:
	if ( (*( state.p)) == 110 )
		goto st382;
	goto st0;
st382:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof382;
case 382:
	switch( (*( state.p)) ) {
		case 13: goto tr556;
		case 32: goto tr556;
		case 59: goto tr557;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr556;
	goto st0;
tr525:
#line 157 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st383;
tr590:
#line 156 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st383;
st383:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof383;
case 383:
#line 5904 "configparser.h"
	if ( (*( state.p)) == 97 )
		goto st384;
	goto st0;
st384:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof384;
case 384:
	if ( (*( state.p)) == 103 )
		goto st385;
	goto st0;
st385:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof385;
case 385:
	if ( (*( state.p)) == 101 )
		goto st386;
	goto st0;
st386:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof386;
case 386:
	if ( (*( state.p)) == 110 )
		goto st387;
	goto st0;
st387:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof387;
case 387:
	if ( (*( state.p)) == 116 )
		goto st388;
	goto st0;
st388:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof388;
case 388:
	if ( (*( state.p)) == 97 )
		goto st389;
	goto st0;
st389:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof389;
case 389:
	switch( (*( state.p)) ) {
		case 13: goto tr564;
		case 32: goto tr564;
		case 59: goto tr565;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr564;
	goto st0;
tr526:
#line 157 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st390;
tr591:
#line 156 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st390;
st390:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof390;
case 390:
#line 5967 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st391;
	goto st0;
st391:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof391;
case 391:
	if ( (*( state.p)) == 100 )
		goto st392;
	goto st0;
st392:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof392;
case 392:
	switch( (*( state.p)) ) {
		case 13: goto tr568;
		case 32: goto tr568;
		case 59: goto tr569;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr568;
	goto st0;
tr527:
#line 157 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st393;
tr592:
#line 156 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st393;
st393:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof393;
case 393:
#line 6002 "configparser.h"
	if ( (*( state.p)) == 104 )
		goto st394;
	goto st0;
st394:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof394;
case 394:
	if ( (*( state.p)) == 105 )
		goto st395;
	goto st0;
st395:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof395;
case 395:
	if ( (*( state.p)) == 116 )
		goto st396;
	goto st0;
st396:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof396;
case 396:
	if ( (*( state.p)) == 101 )
		goto st397;
	goto st0;
st397:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof397;
case 397:
	switch( (*( state.p)) ) {
		case 13: goto tr574;
		case 32: goto tr574;
		case 59: goto tr575;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr574;
	goto st0;
tr528:
#line 157 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st398;
tr593:
#line 156 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st398;
st398:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof398;
case 398:
#line 6051 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st399;
	goto st0;
st399:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof399;
case 399:
	if ( (*( state.p)) == 108 )
		goto st400;
	goto st0;
st400:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof400;
case 400:
	if ( (*( state.p)) == 108 )
		goto st401;
	goto st0;
st401:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof401;
case 401:
	if ( (*( state.p)) == 111 )
		goto st402;
	goto st0;
st402:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof402;
case 402:
	if ( (*( state.p)) == 119 )
		goto st403;
	goto st0;
st403:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof403;
case 403:
	switch( (*( state.p)) ) {
		case 13: goto tr581;
		case 32: goto tr581;
		case 59: goto tr582;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr581;
	goto st0;
tr521:
#line 157 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st404;
tr586:
#line 156 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st404;
st404:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof404;
case 404:
#line 6107 "configparser.h"
	switch( (*( state.p)) ) {
		case 98: goto st367;
		case 99: goto st374;
		case 103: goto st378;
		case 109: goto st383;
		case 114: goto st390;
		case 119: goto st393;
		case 121: goto st398;
	}
	goto st0;
st405:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof405;
case 405:
	if ( (*( state.p)) == 105 )
		goto st406;
	goto st0;
st406:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof406;
case 406:
	if ( (*( state.p)) == 109 )
		goto st407;
	goto st0;
st407:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof407;
case 407:
	switch( (*( state.p)) ) {
		case 13: goto tr585;
		case 32: goto tr585;
		case 95: goto tr586;
		case 98: goto tr587;
		case 99: goto tr588;
		case 103: goto tr589;
		case 109: goto tr590;
		case 114: goto tr591;
		case 119: goto tr592;
		case 121: goto tr593;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr585;
	goto st0;
st408:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof408;
case 408:
	if ( (*( state.p)) == 111 )
		goto st409;
	goto st0;
st409:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof409;
case 409:
	if ( (*( state.p)) == 110 )
		goto st410;
	goto st0;
st410:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof410;
case 410:
	if ( (*( state.p)) == 101 )
		goto st371;
	goto st0;
st411:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof411;
case 411:
	if ( (*( state.p)) == 111 )
		goto st412;
	goto st0;
st412:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof412;
case 412:
	if ( (*( state.p)) == 116 )
		goto st413;
	goto st0;
st413:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof413;
case 413:
	switch( (*( state.p)) ) {
		case 13: goto st414;
		case 32: goto st414;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st414;
	goto st0;
st414:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof414;
case 414:
	switch( (*( state.p)) ) {
		case 13: goto st414;
		case 32: goto st414;
		case 34: goto tr599;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st414;
	goto st0;
tr600:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st415;
tr599:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
	goto st415;
tr602:
#line 137 "configparser.rl"
	{{ state.stack[ state.top++] = 415; goto st35;}}
	goto st415;
st415:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof415;
case 415:
#line 6229 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st416;
		case 92: goto tr602;
	}
	goto tr600;
st416:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof416;
case 416:
	switch( (*( state.p)) ) {
		case 13: goto tr603;
		case 32: goto tr603;
		case 59: goto tr604;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr603;
	goto st0;
st417:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof417;
case 417:
	if ( (*( state.p)) == 97 )
		goto st418;
	goto st0;
st418:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof418;
case 418:
	if ( (*( state.p)) == 99 )
		goto st419;
	goto st0;
st419:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof419;
case 419:
	if ( (*( state.p)) == 107 )
		goto st420;
	goto st0;
st420:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof420;
case 420:
	if ( (*( state.p)) == 114 )
		goto st421;
	goto st0;
st421:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof421;
case 421:
	if ( (*( state.p)) == 97 )
		goto st422;
	goto st0;
st422:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof422;
case 422:
	if ( (*( state.p)) == 110 )
		goto st423;
	goto st0;
st423:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof423;
case 423:
	if ( (*( state.p)) == 103 )
		goto st424;
	goto st0;
st424:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof424;
case 424:
	if ( (*( state.p)) == 101 )
		goto st425;
	goto st0;
st425:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof425;
case 425:
	switch( (*( state.p)) ) {
		case 13: goto st426;
		case 32: goto st426;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st426;
	goto st0;
st426:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof426;
case 426:
	switch( (*( state.p)) ) {
		case 13: goto st426;
		case 32: goto st426;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr614;
	} else if ( (*( state.p)) >= 9 )
		goto st426;
	goto st0;
tr614:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st427;
tr616:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st427;
st427:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof427;
case 427:
#line 6348 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr615;
		case 32: goto tr615;
		case 59: goto tr617;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr616;
	} else if ( (*( state.p)) >= 9 )
		goto tr615;
	goto st0;
st428:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof428;
case 428:
	if ( (*( state.p)) == 104 )
		goto st429;
	goto st0;
st429:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof429;
case 429:
	if ( (*( state.p)) == 114 )
		goto st430;
	goto st0;
st430:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof430;
case 430:
	if ( (*( state.p)) == 111 )
		goto st431;
	goto st0;
st431:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof431;
case 431:
	if ( (*( state.p)) == 119 )
		goto st432;
	goto st0;
st432:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof432;
case 432:
	if ( (*( state.p)) == 114 )
		goto st433;
	goto st0;
st433:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof433;
case 433:
	if ( (*( state.p)) == 97 )
		goto st434;
	goto st0;
st434:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof434;
case 434:
	if ( (*( state.p)) == 110 )
		goto st435;
	goto st0;
st435:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof435;
case 435:
	if ( (*( state.p)) == 103 )
		goto st436;
	goto st0;
st436:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof436;
case 436:
	if ( (*( state.p)) == 101 )
		goto st437;
	goto st0;
st437:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof437;
case 437:
	switch( (*( state.p)) ) {
		case 13: goto st438;
		case 32: goto st438;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st438;
	goto st0;
st438:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof438;
case 438:
	switch( (*( state.p)) ) {
		case 13: goto st438;
		case 32: goto st438;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr628;
	} else if ( (*( state.p)) >= 9 )
		goto st438;
	goto st0;
tr628:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st439;
tr630:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st439;
st439:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof439;
case 439:
#line 6468 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr629;
		case 32: goto tr629;
		case 59: goto tr631;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr630;
	} else if ( (*( state.p)) >= 9 )
		goto tr629;
	goto st0;
st440:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof440;
case 440:
	if ( (*( state.p)) == 115 )
		goto st441;
	goto st0;
st441:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof441;
case 441:
	if ( (*( state.p)) == 97 )
		goto st442;
	goto st0;
st442:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof442;
case 442:
	if ( (*( state.p)) == 98 )
		goto st443;
	goto st0;
st443:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof443;
case 443:
	if ( (*( state.p)) == 108 )
		goto st444;
	goto st0;
st444:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof444;
case 444:
	if ( (*( state.p)) == 101 )
		goto st445;
	goto st0;
st445:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof445;
case 445:
	switch( (*( state.p)) ) {
		case 13: goto tr637;
		case 32: goto tr637;
		case 59: goto tr638;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr637;
	goto st0;
st446:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof446;
case 446:
	switch( (*( state.p)) ) {
		case 13: goto tr639;
		case 32: goto tr639;
		case 59: goto tr640;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr639;
	goto st0;
tr442:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st447;
st447:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof447;
case 447:
#line 6549 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr641;
	goto st0;
tr641:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st448;
st448:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof448;
case 448:
#line 6563 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr441;
		case 32: goto tr441;
		case 59: goto tr443;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr641;
	} else if ( (*( state.p)) >= 9 )
		goto tr441;
	goto st0;
st449:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof449;
case 449:
	switch( (*( state.p)) ) {
		case 13: goto st449;
		case 32: goto st449;
		case 99: goto st450;
		case 110: goto st458;
		case 112: goto st465;
		case 115: goto st491;
		case 116: goto st557;
		case 118: goto st569;
		case 119: goto st578;
		case 125: goto st587;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st449;
	goto st0;
st450:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof450;
case 450:
	if ( (*( state.p)) == 111 )
		goto st451;
	goto st0;
st451:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof451;
case 451:
	if ( (*( state.p)) == 117 )
		goto st452;
	goto st0;
st452:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof452;
case 452:
	if ( (*( state.p)) == 110 )
		goto st453;
	goto st0;
st453:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof453;
case 453:
	if ( (*( state.p)) == 116 )
		goto st454;
	goto st0;
st454:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof454;
case 454:
	switch( (*( state.p)) ) {
		case 13: goto st455;
		case 32: goto st455;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st455;
	goto st0;
st455:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof455;
case 455:
	switch( (*( state.p)) ) {
		case 13: goto st455;
		case 32: goto st455;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr656;
	} else if ( (*( state.p)) >= 9 )
		goto st455;
	goto st0;
tr656:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st456;
tr658:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st456;
st456:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof456;
case 456:
#line 6667 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr657;
		case 32: goto tr657;
		case 59: goto tr659;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr658;
	} else if ( (*( state.p)) >= 9 )
		goto tr657;
	goto st0;
tr657:
#line 286 "configparser.rl"
	{ ter.count = toint(state.match); }
	goto st457;
tr670:
#line 287 "configparser.rl"
	{ ter.name = state.match; }
	goto st457;
tr689:
#line 279 "configparser.rl"
	{ ter.placement = Terrain::placement_t::corner; }
	goto st457;
tr695:
#line 277 "configparser.rl"
	{ ter.placement = Terrain::placement_t::floor; }
	goto st457;
tr701:
#line 278 "configparser.rl"
	{ ter.placement = Terrain::placement_t::water; }
	goto st457;
tr744:
#line 288 "configparser.rl"
	{ ter.skin = skin; }
	goto st457;
tr747:
#line 149 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 288 "configparser.rl"
	{ ter.skin = skin; }
	goto st457;
tr752:
#line 151 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 288 "configparser.rl"
	{ ter.skin = skin; }
	goto st457;
tr758:
#line 147 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 288 "configparser.rl"
	{ ter.skin = skin; }
	goto st457;
tr766:
#line 150 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 288 "configparser.rl"
	{ ter.skin = skin; }
	goto st457;
tr770:
#line 146 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 288 "configparser.rl"
	{ ter.skin = skin; }
	goto st457;
tr776:
#line 152 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 288 "configparser.rl"
	{ ter.skin = skin; }
	goto st457;
tr783:
#line 148 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 288 "configparser.rl"
	{ ter.skin = skin; }
	goto st457;
tr804:
#line 290 "configparser.rl"
	{ ter.stairs = toint(state.match); }
	goto st457;
tr821:
#line 283 "configparser.rl"
	{ ter.tunnel_y = toint(state.match); }
	goto st457;
tr831:
#line 291 "configparser.rl"
	{ ter.viewblock = true; }
	goto st457;
tr841:
#line 292 "configparser.rl"
	{ ter.walkblock = true; }
	goto st457;
tr843:
#line 298 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st457;
st457:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof457;
case 457:
#line 6769 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st457;
		case 32: goto st457;
		case 59: goto st595;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st457;
	goto st0;
tr659:
#line 286 "configparser.rl"
	{ ter.count = toint(state.match); }
	goto st595;
tr671:
#line 287 "configparser.rl"
	{ ter.name = state.match; }
	goto st595;
tr690:
#line 279 "configparser.rl"
	{ ter.placement = Terrain::placement_t::corner; }
	goto st595;
tr696:
#line 277 "configparser.rl"
	{ ter.placement = Terrain::placement_t::floor; }
	goto st595;
tr702:
#line 278 "configparser.rl"
	{ ter.placement = Terrain::placement_t::water; }
	goto st595;
tr745:
#line 288 "configparser.rl"
	{ ter.skin = skin; }
	goto st595;
tr748:
#line 149 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 288 "configparser.rl"
	{ ter.skin = skin; }
	goto st595;
tr753:
#line 151 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 288 "configparser.rl"
	{ ter.skin = skin; }
	goto st595;
tr759:
#line 147 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 288 "configparser.rl"
	{ ter.skin = skin; }
	goto st595;
tr767:
#line 150 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 288 "configparser.rl"
	{ ter.skin = skin; }
	goto st595;
tr771:
#line 146 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 288 "configparser.rl"
	{ ter.skin = skin; }
	goto st595;
tr777:
#line 152 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 288 "configparser.rl"
	{ ter.skin = skin; }
	goto st595;
tr784:
#line 148 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 288 "configparser.rl"
	{ ter.skin = skin; }
	goto st595;
tr806:
#line 290 "configparser.rl"
	{ ter.stairs = toint(state.match); }
	goto st595;
tr822:
#line 283 "configparser.rl"
	{ ter.tunnel_y = toint(state.match); }
	goto st595;
tr832:
#line 291 "configparser.rl"
	{ ter.viewblock = true; }
	goto st595;
tr842:
#line 292 "configparser.rl"
	{ ter.walkblock = true; }
	goto st595;
tr844:
#line 298 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st595;
st595:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof595;
case 595:
#line 6868 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st449;
		case 32: goto st449;
		case 99: goto st450;
		case 110: goto st458;
		case 112: goto st465;
		case 115: goto st491;
		case 116: goto st557;
		case 118: goto st569;
		case 119: goto st578;
		case 125: goto st587;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st449;
	goto st0;
st458:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof458;
case 458:
	if ( (*( state.p)) == 97 )
		goto st459;
	goto st0;
st459:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof459;
case 459:
	if ( (*( state.p)) == 109 )
		goto st460;
	goto st0;
st460:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof460;
case 460:
	if ( (*( state.p)) == 101 )
		goto st461;
	goto st0;
st461:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof461;
case 461:
	switch( (*( state.p)) ) {
		case 13: goto st462;
		case 32: goto st462;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st462;
	goto st0;
st462:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof462;
case 462:
	switch( (*( state.p)) ) {
		case 13: goto st462;
		case 32: goto st462;
		case 34: goto tr666;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st462;
	goto st0;
tr667:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st463;
tr666:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
	goto st463;
tr669:
#line 137 "configparser.rl"
	{{ state.stack[ state.top++] = 463; goto st35;}}
	goto st463;
st463:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof463;
case 463:
#line 6948 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st464;
		case 92: goto tr669;
	}
	goto tr667;
st464:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof464;
case 464:
	switch( (*( state.p)) ) {
		case 13: goto tr670;
		case 32: goto tr670;
		case 59: goto tr671;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr670;
	goto st0;
st465:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof465;
case 465:
	if ( (*( state.p)) == 108 )
		goto st466;
	goto st0;
st466:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof466;
case 466:
	if ( (*( state.p)) == 97 )
		goto st467;
	goto st0;
st467:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof467;
case 467:
	if ( (*( state.p)) == 99 )
		goto st468;
	goto st0;
st468:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof468;
case 468:
	if ( (*( state.p)) == 101 )
		goto st469;
	goto st0;
st469:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof469;
case 469:
	if ( (*( state.p)) == 109 )
		goto st470;
	goto st0;
st470:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof470;
case 470:
	if ( (*( state.p)) == 101 )
		goto st471;
	goto st0;
st471:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof471;
case 471:
	if ( (*( state.p)) == 110 )
		goto st472;
	goto st0;
st472:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof472;
case 472:
	if ( (*( state.p)) == 116 )
		goto st473;
	goto st0;
st473:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof473;
case 473:
	switch( (*( state.p)) ) {
		case 13: goto st474;
		case 32: goto st474;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st474;
	goto st0;
st474:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof474;
case 474:
	switch( (*( state.p)) ) {
		case 13: goto st474;
		case 32: goto st474;
		case 99: goto st475;
		case 102: goto st481;
		case 119: goto st486;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st474;
	goto st0;
st475:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof475;
case 475:
	if ( (*( state.p)) == 111 )
		goto st476;
	goto st0;
st476:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof476;
case 476:
	if ( (*( state.p)) == 114 )
		goto st477;
	goto st0;
st477:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof477;
case 477:
	if ( (*( state.p)) == 110 )
		goto st478;
	goto st0;
st478:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof478;
case 478:
	if ( (*( state.p)) == 101 )
		goto st479;
	goto st0;
st479:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof479;
case 479:
	if ( (*( state.p)) == 114 )
		goto st480;
	goto st0;
st480:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof480;
case 480:
	switch( (*( state.p)) ) {
		case 13: goto tr689;
		case 32: goto tr689;
		case 59: goto tr690;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr689;
	goto st0;
st481:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof481;
case 481:
	if ( (*( state.p)) == 108 )
		goto st482;
	goto st0;
st482:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof482;
case 482:
	if ( (*( state.p)) == 111 )
		goto st483;
	goto st0;
st483:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof483;
case 483:
	if ( (*( state.p)) == 111 )
		goto st484;
	goto st0;
st484:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof484;
case 484:
	if ( (*( state.p)) == 114 )
		goto st485;
	goto st0;
st485:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof485;
case 485:
	switch( (*( state.p)) ) {
		case 13: goto tr695;
		case 32: goto tr695;
		case 59: goto tr696;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr695;
	goto st0;
st486:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof486;
case 486:
	if ( (*( state.p)) == 97 )
		goto st487;
	goto st0;
st487:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof487;
case 487:
	if ( (*( state.p)) == 116 )
		goto st488;
	goto st0;
st488:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof488;
case 488:
	if ( (*( state.p)) == 101 )
		goto st489;
	goto st0;
st489:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof489;
case 489:
	if ( (*( state.p)) == 114 )
		goto st490;
	goto st0;
st490:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof490;
case 490:
	switch( (*( state.p)) ) {
		case 13: goto tr701;
		case 32: goto tr701;
		case 59: goto tr702;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr701;
	goto st0;
st491:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof491;
case 491:
	switch( (*( state.p)) ) {
		case 107: goto st492;
		case 116: goto st550;
	}
	goto st0;
st492:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof492;
case 492:
	if ( (*( state.p)) == 105 )
		goto st493;
	goto st0;
st493:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof493;
case 493:
	if ( (*( state.p)) == 110 )
		goto st494;
	goto st0;
st494:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof494;
case 494:
	switch( (*( state.p)) ) {
		case 13: goto st495;
		case 32: goto st495;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st495;
	goto st0;
st495:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof495;
case 495:
	switch( (*( state.p)) ) {
		case 13: goto st495;
		case 32: goto st495;
		case 34: goto tr708;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st495;
	goto st0;
tr709:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st496;
tr708:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
	goto st496;
tr711:
#line 137 "configparser.rl"
	{{ state.stack[ state.top++] = 496; goto st35;}}
	goto st496;
st496:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof496;
case 496:
#line 7240 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st497;
		case 92: goto tr711;
	}
	goto tr709;
st497:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof497;
case 497:
	switch( (*( state.p)) ) {
		case 13: goto tr712;
		case 32: goto tr712;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr712;
	goto st0;
tr712:
#line 159 "configparser.rl"
	{ skin.text = state.match; }
	goto st498;
st498:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof498;
case 498:
#line 7265 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st498;
		case 32: goto st498;
		case 98: goto st499;
		case 100: goto st544;
		case 110: goto st547;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st498;
	goto st0;
st499:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof499;
case 499:
	if ( (*( state.p)) == 114 )
		goto st500;
	goto st0;
st500:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof500;
case 500:
	if ( (*( state.p)) == 105 )
		goto st501;
	goto st0;
st501:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof501;
case 501:
	if ( (*( state.p)) == 103 )
		goto st502;
	goto st0;
st502:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof502;
case 502:
	if ( (*( state.p)) == 104 )
		goto st503;
	goto st0;
st503:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof503;
case 503:
	if ( (*( state.p)) == 116 )
		goto st504;
	goto st0;
st504:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof504;
case 504:
	switch( (*( state.p)) ) {
		case 13: goto tr722;
		case 32: goto tr722;
		case 95: goto tr723;
		case 98: goto tr724;
		case 99: goto tr725;
		case 103: goto tr726;
		case 109: goto tr727;
		case 114: goto tr728;
		case 119: goto tr729;
		case 121: goto tr730;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr722;
	goto st0;
tr722:
#line 157 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st505;
tr787:
#line 156 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st505;
st505:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof505;
case 505:
#line 7342 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st505;
		case 32: goto st505;
		case 98: goto st506;
		case 99: goto st513;
		case 103: goto st517;
		case 109: goto st522;
		case 114: goto st529;
		case 119: goto st532;
		case 121: goto st537;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st505;
	goto st0;
tr724:
#line 157 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st506;
tr789:
#line 156 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st506;
st506:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof506;
case 506:
#line 7369 "configparser.h"
	if ( (*( state.p)) == 108 )
		goto st507;
	goto st0;
st507:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof507;
case 507:
	switch( (*( state.p)) ) {
		case 97: goto st508;
		case 117: goto st511;
	}
	goto st0;
st508:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof508;
case 508:
	if ( (*( state.p)) == 99 )
		goto st509;
	goto st0;
st509:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof509;
case 509:
	if ( (*( state.p)) == 107 )
		goto st510;
	goto st0;
st510:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof510;
case 510:
	switch( (*( state.p)) ) {
		case 13: goto tr744;
		case 32: goto tr744;
		case 59: goto tr745;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr744;
	goto st0;
st511:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof511;
case 511:
	if ( (*( state.p)) == 101 )
		goto st512;
	goto st0;
st512:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof512;
case 512:
	switch( (*( state.p)) ) {
		case 13: goto tr747;
		case 32: goto tr747;
		case 59: goto tr748;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr747;
	goto st0;
tr725:
#line 157 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st513;
tr790:
#line 156 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st513;
st513:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof513;
case 513:
#line 7439 "configparser.h"
	if ( (*( state.p)) == 121 )
		goto st514;
	goto st0;
st514:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof514;
case 514:
	if ( (*( state.p)) == 97 )
		goto st515;
	goto st0;
st515:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof515;
case 515:
	if ( (*( state.p)) == 110 )
		goto st516;
	goto st0;
st516:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof516;
case 516:
	switch( (*( state.p)) ) {
		case 13: goto tr752;
		case 32: goto tr752;
		case 59: goto tr753;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr752;
	goto st0;
tr726:
#line 157 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st517;
tr791:
#line 156 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st517;
st517:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof517;
case 517:
#line 7481 "configparser.h"
	if ( (*( state.p)) == 114 )
		goto st518;
	goto st0;
st518:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof518;
case 518:
	if ( (*( state.p)) == 101 )
		goto st519;
	goto st0;
st519:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof519;
case 519:
	if ( (*( state.p)) == 101 )
		goto st520;
	goto st0;
st520:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof520;
case 520:
	if ( (*( state.p)) == 110 )
		goto st521;
	goto st0;
st521:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof521;
case 521:
	switch( (*( state.p)) ) {
		case 13: goto tr758;
		case 32: goto tr758;
		case 59: goto tr759;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr758;
	goto st0;
tr727:
#line 157 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st522;
tr792:
#line 156 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st522;
st522:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof522;
case 522:
#line 7530 "configparser.h"
	if ( (*( state.p)) == 97 )
		goto st523;
	goto st0;
st523:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof523;
case 523:
	if ( (*( state.p)) == 103 )
		goto st524;
	goto st0;
st524:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof524;
case 524:
	if ( (*( state.p)) == 101 )
		goto st525;
	goto st0;
st525:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof525;
case 525:
	if ( (*( state.p)) == 110 )
		goto st526;
	goto st0;
st526:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof526;
case 526:
	if ( (*( state.p)) == 116 )
		goto st527;
	goto st0;
st527:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof527;
case 527:
	if ( (*( state.p)) == 97 )
		goto st528;
	goto st0;
st528:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof528;
case 528:
	switch( (*( state.p)) ) {
		case 13: goto tr766;
		case 32: goto tr766;
		case 59: goto tr767;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr766;
	goto st0;
tr728:
#line 157 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st529;
tr793:
#line 156 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st529;
st529:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof529;
case 529:
#line 7593 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st530;
	goto st0;
st530:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof530;
case 530:
	if ( (*( state.p)) == 100 )
		goto st531;
	goto st0;
st531:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof531;
case 531:
	switch( (*( state.p)) ) {
		case 13: goto tr770;
		case 32: goto tr770;
		case 59: goto tr771;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr770;
	goto st0;
tr729:
#line 157 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st532;
tr794:
#line 156 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st532;
st532:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof532;
case 532:
#line 7628 "configparser.h"
	if ( (*( state.p)) == 104 )
		goto st533;
	goto st0;
st533:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof533;
case 533:
	if ( (*( state.p)) == 105 )
		goto st534;
	goto st0;
st534:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof534;
case 534:
	if ( (*( state.p)) == 116 )
		goto st535;
	goto st0;
st535:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof535;
case 535:
	if ( (*( state.p)) == 101 )
		goto st536;
	goto st0;
st536:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof536;
case 536:
	switch( (*( state.p)) ) {
		case 13: goto tr776;
		case 32: goto tr776;
		case 59: goto tr777;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr776;
	goto st0;
tr730:
#line 157 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st537;
tr795:
#line 156 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st537;
st537:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof537;
case 537:
#line 7677 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st538;
	goto st0;
st538:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof538;
case 538:
	if ( (*( state.p)) == 108 )
		goto st539;
	goto st0;
st539:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof539;
case 539:
	if ( (*( state.p)) == 108 )
		goto st540;
	goto st0;
st540:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof540;
case 540:
	if ( (*( state.p)) == 111 )
		goto st541;
	goto st0;
st541:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof541;
case 541:
	if ( (*( state.p)) == 119 )
		goto st542;
	goto st0;
st542:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof542;
case 542:
	switch( (*( state.p)) ) {
		case 13: goto tr783;
		case 32: goto tr783;
		case 59: goto tr784;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr783;
	goto st0;
tr723:
#line 157 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st543;
tr788:
#line 156 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st543;
st543:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof543;
case 543:
#line 7733 "configparser.h"
	switch( (*( state.p)) ) {
		case 98: goto st506;
		case 99: goto st513;
		case 103: goto st517;
		case 109: goto st522;
		case 114: goto st529;
		case 119: goto st532;
		case 121: goto st537;
	}
	goto st0;
st544:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof544;
case 544:
	if ( (*( state.p)) == 105 )
		goto st545;
	goto st0;
st545:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof545;
case 545:
	if ( (*( state.p)) == 109 )
		goto st546;
	goto st0;
st546:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof546;
case 546:
	switch( (*( state.p)) ) {
		case 13: goto tr787;
		case 32: goto tr787;
		case 95: goto tr788;
		case 98: goto tr789;
		case 99: goto tr790;
		case 103: goto tr791;
		case 109: goto tr792;
		case 114: goto tr793;
		case 119: goto tr794;
		case 121: goto tr795;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr787;
	goto st0;
st547:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof547;
case 547:
	if ( (*( state.p)) == 111 )
		goto st548;
	goto st0;
st548:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof548;
case 548:
	if ( (*( state.p)) == 110 )
		goto st549;
	goto st0;
st549:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof549;
case 549:
	if ( (*( state.p)) == 101 )
		goto st510;
	goto st0;
st550:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof550;
case 550:
	if ( (*( state.p)) == 97 )
		goto st551;
	goto st0;
st551:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof551;
case 551:
	if ( (*( state.p)) == 105 )
		goto st552;
	goto st0;
st552:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof552;
case 552:
	if ( (*( state.p)) == 114 )
		goto st553;
	goto st0;
st553:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof553;
case 553:
	if ( (*( state.p)) == 115 )
		goto st554;
	goto st0;
st554:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof554;
case 554:
	switch( (*( state.p)) ) {
		case 13: goto st555;
		case 32: goto st555;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st555;
	goto st0;
st555:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof555;
case 555:
	switch( (*( state.p)) ) {
		case 13: goto st555;
		case 32: goto st555;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr803;
	} else if ( (*( state.p)) >= 9 )
		goto st555;
	goto st0;
tr803:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st556;
tr805:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st556;
st556:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof556;
case 556:
#line 7871 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr804;
		case 32: goto tr804;
		case 59: goto tr806;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr805;
	} else if ( (*( state.p)) >= 9 )
		goto tr804;
	goto st0;
st557:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof557;
case 557:
	if ( (*( state.p)) == 117 )
		goto st558;
	goto st0;
st558:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof558;
case 558:
	if ( (*( state.p)) == 110 )
		goto st559;
	goto st0;
st559:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof559;
case 559:
	if ( (*( state.p)) == 110 )
		goto st560;
	goto st0;
st560:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof560;
case 560:
	if ( (*( state.p)) == 101 )
		goto st561;
	goto st0;
st561:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof561;
case 561:
	if ( (*( state.p)) == 108 )
		goto st562;
	goto st0;
st562:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof562;
case 562:
	switch( (*( state.p)) ) {
		case 13: goto st563;
		case 32: goto st563;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st563;
	goto st0;
st563:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof563;
case 563:
	switch( (*( state.p)) ) {
		case 13: goto st563;
		case 32: goto st563;
		case 45: goto tr813;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr814;
	} else if ( (*( state.p)) >= 9 )
		goto st563;
	goto st0;
tr813:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st564;
st564:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof564;
case 564:
#line 7958 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr815;
	goto st0;
tr814:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st565;
tr815:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st565;
st565:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof565;
case 565:
#line 7982 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr816;
		case 32: goto tr816;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr815;
	} else if ( (*( state.p)) >= 9 )
		goto tr816;
	goto st0;
tr816:
#line 282 "configparser.rl"
	{ ter.tunnel_x = toint(state.match); }
	goto st566;
st566:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof566;
case 566:
#line 8001 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st566;
		case 32: goto st566;
		case 45: goto tr818;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr819;
	} else if ( (*( state.p)) >= 9 )
		goto st566;
	goto st0;
tr818:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st567;
st567:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof567;
case 567:
#line 8027 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr820;
	goto st0;
tr819:
#line 102 "configparser.rl"
	{
            state.match.clear();
        }
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st568;
tr820:
#line 106 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st568;
st568:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof568;
case 568:
#line 8051 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr821;
		case 32: goto tr821;
		case 59: goto tr822;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr820;
	} else if ( (*( state.p)) >= 9 )
		goto tr821;
	goto st0;
st569:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof569;
case 569:
	if ( (*( state.p)) == 105 )
		goto st570;
	goto st0;
st570:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof570;
case 570:
	if ( (*( state.p)) == 101 )
		goto st571;
	goto st0;
st571:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof571;
case 571:
	if ( (*( state.p)) == 119 )
		goto st572;
	goto st0;
st572:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof572;
case 572:
	if ( (*( state.p)) == 98 )
		goto st573;
	goto st0;
st573:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof573;
case 573:
	if ( (*( state.p)) == 108 )
		goto st574;
	goto st0;
st574:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof574;
case 574:
	if ( (*( state.p)) == 111 )
		goto st575;
	goto st0;
st575:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof575;
case 575:
	if ( (*( state.p)) == 99 )
		goto st576;
	goto st0;
st576:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof576;
case 576:
	if ( (*( state.p)) == 107 )
		goto st577;
	goto st0;
st577:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof577;
case 577:
	switch( (*( state.p)) ) {
		case 13: goto tr831;
		case 32: goto tr831;
		case 59: goto tr832;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr831;
	goto st0;
st578:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof578;
case 578:
	if ( (*( state.p)) == 97 )
		goto st579;
	goto st0;
st579:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof579;
case 579:
	if ( (*( state.p)) == 108 )
		goto st580;
	goto st0;
st580:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof580;
case 580:
	if ( (*( state.p)) == 107 )
		goto st581;
	goto st0;
st581:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof581;
case 581:
	if ( (*( state.p)) == 98 )
		goto st582;
	goto st0;
st582:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof582;
case 582:
	if ( (*( state.p)) == 108 )
		goto st583;
	goto st0;
st583:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof583;
case 583:
	if ( (*( state.p)) == 111 )
		goto st584;
	goto st0;
st584:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof584;
case 584:
	if ( (*( state.p)) == 99 )
		goto st585;
	goto st0;
st585:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof585;
case 585:
	if ( (*( state.p)) == 107 )
		goto st586;
	goto st0;
st586:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof586;
case 586:
	switch( (*( state.p)) ) {
		case 13: goto tr841;
		case 32: goto tr841;
		case 59: goto tr842;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr841;
	goto st0;
st587:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof587;
case 587:
	switch( (*( state.p)) ) {
		case 13: goto tr843;
		case 32: goto tr843;
		case 59: goto tr844;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr843;
	goto st0;
	}
	_test_eof1:  state.cs = 1; goto _test_eof; 
	_test_eof2:  state.cs = 2; goto _test_eof; 
	_test_eof3:  state.cs = 3; goto _test_eof; 
	_test_eof4:  state.cs = 4; goto _test_eof; 
	_test_eof5:  state.cs = 5; goto _test_eof; 
	_test_eof6:  state.cs = 6; goto _test_eof; 
	_test_eof7:  state.cs = 7; goto _test_eof; 
	_test_eof8:  state.cs = 8; goto _test_eof; 
	_test_eof9:  state.cs = 9; goto _test_eof; 
	_test_eof10:  state.cs = 10; goto _test_eof; 
	_test_eof11:  state.cs = 11; goto _test_eof; 
	_test_eof12:  state.cs = 12; goto _test_eof; 
	_test_eof588:  state.cs = 588; goto _test_eof; 
	_test_eof589:  state.cs = 589; goto _test_eof; 
	_test_eof13:  state.cs = 13; goto _test_eof; 
	_test_eof14:  state.cs = 14; goto _test_eof; 
	_test_eof15:  state.cs = 15; goto _test_eof; 
	_test_eof16:  state.cs = 16; goto _test_eof; 
	_test_eof17:  state.cs = 17; goto _test_eof; 
	_test_eof18:  state.cs = 18; goto _test_eof; 
	_test_eof19:  state.cs = 19; goto _test_eof; 
	_test_eof20:  state.cs = 20; goto _test_eof; 
	_test_eof21:  state.cs = 21; goto _test_eof; 
	_test_eof22:  state.cs = 22; goto _test_eof; 
	_test_eof23:  state.cs = 23; goto _test_eof; 
	_test_eof24:  state.cs = 24; goto _test_eof; 
	_test_eof590:  state.cs = 590; goto _test_eof; 
	_test_eof25:  state.cs = 25; goto _test_eof; 
	_test_eof26:  state.cs = 26; goto _test_eof; 
	_test_eof27:  state.cs = 27; goto _test_eof; 
	_test_eof28:  state.cs = 28; goto _test_eof; 
	_test_eof29:  state.cs = 29; goto _test_eof; 
	_test_eof30:  state.cs = 30; goto _test_eof; 
	_test_eof31:  state.cs = 31; goto _test_eof; 
	_test_eof32:  state.cs = 32; goto _test_eof; 
	_test_eof33:  state.cs = 33; goto _test_eof; 
	_test_eof34:  state.cs = 34; goto _test_eof; 
	_test_eof591:  state.cs = 591; goto _test_eof; 
	_test_eof35:  state.cs = 35; goto _test_eof; 
	_test_eof592:  state.cs = 592; goto _test_eof; 
	_test_eof36:  state.cs = 36; goto _test_eof; 
	_test_eof37:  state.cs = 37; goto _test_eof; 
	_test_eof38:  state.cs = 38; goto _test_eof; 
	_test_eof39:  state.cs = 39; goto _test_eof; 
	_test_eof40:  state.cs = 40; goto _test_eof; 
	_test_eof41:  state.cs = 41; goto _test_eof; 
	_test_eof42:  state.cs = 42; goto _test_eof; 
	_test_eof43:  state.cs = 43; goto _test_eof; 
	_test_eof44:  state.cs = 44; goto _test_eof; 
	_test_eof45:  state.cs = 45; goto _test_eof; 
	_test_eof46:  state.cs = 46; goto _test_eof; 
	_test_eof47:  state.cs = 47; goto _test_eof; 
	_test_eof48:  state.cs = 48; goto _test_eof; 
	_test_eof49:  state.cs = 49; goto _test_eof; 
	_test_eof50:  state.cs = 50; goto _test_eof; 
	_test_eof51:  state.cs = 51; goto _test_eof; 
	_test_eof52:  state.cs = 52; goto _test_eof; 
	_test_eof53:  state.cs = 53; goto _test_eof; 
	_test_eof54:  state.cs = 54; goto _test_eof; 
	_test_eof593:  state.cs = 593; goto _test_eof; 
	_test_eof55:  state.cs = 55; goto _test_eof; 
	_test_eof56:  state.cs = 56; goto _test_eof; 
	_test_eof57:  state.cs = 57; goto _test_eof; 
	_test_eof58:  state.cs = 58; goto _test_eof; 
	_test_eof59:  state.cs = 59; goto _test_eof; 
	_test_eof60:  state.cs = 60; goto _test_eof; 
	_test_eof61:  state.cs = 61; goto _test_eof; 
	_test_eof62:  state.cs = 62; goto _test_eof; 
	_test_eof63:  state.cs = 63; goto _test_eof; 
	_test_eof64:  state.cs = 64; goto _test_eof; 
	_test_eof65:  state.cs = 65; goto _test_eof; 
	_test_eof66:  state.cs = 66; goto _test_eof; 
	_test_eof67:  state.cs = 67; goto _test_eof; 
	_test_eof68:  state.cs = 68; goto _test_eof; 
	_test_eof69:  state.cs = 69; goto _test_eof; 
	_test_eof70:  state.cs = 70; goto _test_eof; 
	_test_eof71:  state.cs = 71; goto _test_eof; 
	_test_eof72:  state.cs = 72; goto _test_eof; 
	_test_eof73:  state.cs = 73; goto _test_eof; 
	_test_eof74:  state.cs = 74; goto _test_eof; 
	_test_eof75:  state.cs = 75; goto _test_eof; 
	_test_eof76:  state.cs = 76; goto _test_eof; 
	_test_eof77:  state.cs = 77; goto _test_eof; 
	_test_eof78:  state.cs = 78; goto _test_eof; 
	_test_eof79:  state.cs = 79; goto _test_eof; 
	_test_eof80:  state.cs = 80; goto _test_eof; 
	_test_eof81:  state.cs = 81; goto _test_eof; 
	_test_eof82:  state.cs = 82; goto _test_eof; 
	_test_eof83:  state.cs = 83; goto _test_eof; 
	_test_eof84:  state.cs = 84; goto _test_eof; 
	_test_eof85:  state.cs = 85; goto _test_eof; 
	_test_eof86:  state.cs = 86; goto _test_eof; 
	_test_eof87:  state.cs = 87; goto _test_eof; 
	_test_eof88:  state.cs = 88; goto _test_eof; 
	_test_eof89:  state.cs = 89; goto _test_eof; 
	_test_eof90:  state.cs = 90; goto _test_eof; 
	_test_eof91:  state.cs = 91; goto _test_eof; 
	_test_eof92:  state.cs = 92; goto _test_eof; 
	_test_eof93:  state.cs = 93; goto _test_eof; 
	_test_eof94:  state.cs = 94; goto _test_eof; 
	_test_eof95:  state.cs = 95; goto _test_eof; 
	_test_eof96:  state.cs = 96; goto _test_eof; 
	_test_eof97:  state.cs = 97; goto _test_eof; 
	_test_eof98:  state.cs = 98; goto _test_eof; 
	_test_eof99:  state.cs = 99; goto _test_eof; 
	_test_eof100:  state.cs = 100; goto _test_eof; 
	_test_eof101:  state.cs = 101; goto _test_eof; 
	_test_eof102:  state.cs = 102; goto _test_eof; 
	_test_eof103:  state.cs = 103; goto _test_eof; 
	_test_eof104:  state.cs = 104; goto _test_eof; 
	_test_eof105:  state.cs = 105; goto _test_eof; 
	_test_eof106:  state.cs = 106; goto _test_eof; 
	_test_eof107:  state.cs = 107; goto _test_eof; 
	_test_eof108:  state.cs = 108; goto _test_eof; 
	_test_eof109:  state.cs = 109; goto _test_eof; 
	_test_eof110:  state.cs = 110; goto _test_eof; 
	_test_eof111:  state.cs = 111; goto _test_eof; 
	_test_eof112:  state.cs = 112; goto _test_eof; 
	_test_eof113:  state.cs = 113; goto _test_eof; 
	_test_eof114:  state.cs = 114; goto _test_eof; 
	_test_eof115:  state.cs = 115; goto _test_eof; 
	_test_eof116:  state.cs = 116; goto _test_eof; 
	_test_eof117:  state.cs = 117; goto _test_eof; 
	_test_eof118:  state.cs = 118; goto _test_eof; 
	_test_eof119:  state.cs = 119; goto _test_eof; 
	_test_eof120:  state.cs = 120; goto _test_eof; 
	_test_eof121:  state.cs = 121; goto _test_eof; 
	_test_eof122:  state.cs = 122; goto _test_eof; 
	_test_eof123:  state.cs = 123; goto _test_eof; 
	_test_eof124:  state.cs = 124; goto _test_eof; 
	_test_eof125:  state.cs = 125; goto _test_eof; 
	_test_eof126:  state.cs = 126; goto _test_eof; 
	_test_eof127:  state.cs = 127; goto _test_eof; 
	_test_eof128:  state.cs = 128; goto _test_eof; 
	_test_eof129:  state.cs = 129; goto _test_eof; 
	_test_eof130:  state.cs = 130; goto _test_eof; 
	_test_eof131:  state.cs = 131; goto _test_eof; 
	_test_eof132:  state.cs = 132; goto _test_eof; 
	_test_eof133:  state.cs = 133; goto _test_eof; 
	_test_eof134:  state.cs = 134; goto _test_eof; 
	_test_eof135:  state.cs = 135; goto _test_eof; 
	_test_eof136:  state.cs = 136; goto _test_eof; 
	_test_eof137:  state.cs = 137; goto _test_eof; 
	_test_eof138:  state.cs = 138; goto _test_eof; 
	_test_eof139:  state.cs = 139; goto _test_eof; 
	_test_eof140:  state.cs = 140; goto _test_eof; 
	_test_eof141:  state.cs = 141; goto _test_eof; 
	_test_eof142:  state.cs = 142; goto _test_eof; 
	_test_eof143:  state.cs = 143; goto _test_eof; 
	_test_eof144:  state.cs = 144; goto _test_eof; 
	_test_eof145:  state.cs = 145; goto _test_eof; 
	_test_eof146:  state.cs = 146; goto _test_eof; 
	_test_eof147:  state.cs = 147; goto _test_eof; 
	_test_eof148:  state.cs = 148; goto _test_eof; 
	_test_eof149:  state.cs = 149; goto _test_eof; 
	_test_eof150:  state.cs = 150; goto _test_eof; 
	_test_eof151:  state.cs = 151; goto _test_eof; 
	_test_eof152:  state.cs = 152; goto _test_eof; 
	_test_eof153:  state.cs = 153; goto _test_eof; 
	_test_eof154:  state.cs = 154; goto _test_eof; 
	_test_eof155:  state.cs = 155; goto _test_eof; 
	_test_eof156:  state.cs = 156; goto _test_eof; 
	_test_eof157:  state.cs = 157; goto _test_eof; 
	_test_eof158:  state.cs = 158; goto _test_eof; 
	_test_eof159:  state.cs = 159; goto _test_eof; 
	_test_eof160:  state.cs = 160; goto _test_eof; 
	_test_eof161:  state.cs = 161; goto _test_eof; 
	_test_eof162:  state.cs = 162; goto _test_eof; 
	_test_eof163:  state.cs = 163; goto _test_eof; 
	_test_eof164:  state.cs = 164; goto _test_eof; 
	_test_eof165:  state.cs = 165; goto _test_eof; 
	_test_eof166:  state.cs = 166; goto _test_eof; 
	_test_eof167:  state.cs = 167; goto _test_eof; 
	_test_eof168:  state.cs = 168; goto _test_eof; 
	_test_eof169:  state.cs = 169; goto _test_eof; 
	_test_eof170:  state.cs = 170; goto _test_eof; 
	_test_eof171:  state.cs = 171; goto _test_eof; 
	_test_eof172:  state.cs = 172; goto _test_eof; 
	_test_eof173:  state.cs = 173; goto _test_eof; 
	_test_eof174:  state.cs = 174; goto _test_eof; 
	_test_eof175:  state.cs = 175; goto _test_eof; 
	_test_eof176:  state.cs = 176; goto _test_eof; 
	_test_eof177:  state.cs = 177; goto _test_eof; 
	_test_eof178:  state.cs = 178; goto _test_eof; 
	_test_eof179:  state.cs = 179; goto _test_eof; 
	_test_eof180:  state.cs = 180; goto _test_eof; 
	_test_eof181:  state.cs = 181; goto _test_eof; 
	_test_eof182:  state.cs = 182; goto _test_eof; 
	_test_eof183:  state.cs = 183; goto _test_eof; 
	_test_eof184:  state.cs = 184; goto _test_eof; 
	_test_eof185:  state.cs = 185; goto _test_eof; 
	_test_eof186:  state.cs = 186; goto _test_eof; 
	_test_eof187:  state.cs = 187; goto _test_eof; 
	_test_eof188:  state.cs = 188; goto _test_eof; 
	_test_eof189:  state.cs = 189; goto _test_eof; 
	_test_eof190:  state.cs = 190; goto _test_eof; 
	_test_eof191:  state.cs = 191; goto _test_eof; 
	_test_eof192:  state.cs = 192; goto _test_eof; 
	_test_eof193:  state.cs = 193; goto _test_eof; 
	_test_eof194:  state.cs = 194; goto _test_eof; 
	_test_eof195:  state.cs = 195; goto _test_eof; 
	_test_eof196:  state.cs = 196; goto _test_eof; 
	_test_eof197:  state.cs = 197; goto _test_eof; 
	_test_eof198:  state.cs = 198; goto _test_eof; 
	_test_eof199:  state.cs = 199; goto _test_eof; 
	_test_eof200:  state.cs = 200; goto _test_eof; 
	_test_eof201:  state.cs = 201; goto _test_eof; 
	_test_eof202:  state.cs = 202; goto _test_eof; 
	_test_eof203:  state.cs = 203; goto _test_eof; 
	_test_eof204:  state.cs = 204; goto _test_eof; 
	_test_eof205:  state.cs = 205; goto _test_eof; 
	_test_eof206:  state.cs = 206; goto _test_eof; 
	_test_eof207:  state.cs = 207; goto _test_eof; 
	_test_eof208:  state.cs = 208; goto _test_eof; 
	_test_eof209:  state.cs = 209; goto _test_eof; 
	_test_eof210:  state.cs = 210; goto _test_eof; 
	_test_eof211:  state.cs = 211; goto _test_eof; 
	_test_eof212:  state.cs = 212; goto _test_eof; 
	_test_eof213:  state.cs = 213; goto _test_eof; 
	_test_eof214:  state.cs = 214; goto _test_eof; 
	_test_eof215:  state.cs = 215; goto _test_eof; 
	_test_eof216:  state.cs = 216; goto _test_eof; 
	_test_eof217:  state.cs = 217; goto _test_eof; 
	_test_eof218:  state.cs = 218; goto _test_eof; 
	_test_eof219:  state.cs = 219; goto _test_eof; 
	_test_eof220:  state.cs = 220; goto _test_eof; 
	_test_eof221:  state.cs = 221; goto _test_eof; 
	_test_eof222:  state.cs = 222; goto _test_eof; 
	_test_eof223:  state.cs = 223; goto _test_eof; 
	_test_eof224:  state.cs = 224; goto _test_eof; 
	_test_eof225:  state.cs = 225; goto _test_eof; 
	_test_eof226:  state.cs = 226; goto _test_eof; 
	_test_eof227:  state.cs = 227; goto _test_eof; 
	_test_eof228:  state.cs = 228; goto _test_eof; 
	_test_eof229:  state.cs = 229; goto _test_eof; 
	_test_eof230:  state.cs = 230; goto _test_eof; 
	_test_eof231:  state.cs = 231; goto _test_eof; 
	_test_eof232:  state.cs = 232; goto _test_eof; 
	_test_eof233:  state.cs = 233; goto _test_eof; 
	_test_eof234:  state.cs = 234; goto _test_eof; 
	_test_eof235:  state.cs = 235; goto _test_eof; 
	_test_eof236:  state.cs = 236; goto _test_eof; 
	_test_eof237:  state.cs = 237; goto _test_eof; 
	_test_eof238:  state.cs = 238; goto _test_eof; 
	_test_eof239:  state.cs = 239; goto _test_eof; 
	_test_eof240:  state.cs = 240; goto _test_eof; 
	_test_eof241:  state.cs = 241; goto _test_eof; 
	_test_eof242:  state.cs = 242; goto _test_eof; 
	_test_eof243:  state.cs = 243; goto _test_eof; 
	_test_eof244:  state.cs = 244; goto _test_eof; 
	_test_eof245:  state.cs = 245; goto _test_eof; 
	_test_eof246:  state.cs = 246; goto _test_eof; 
	_test_eof247:  state.cs = 247; goto _test_eof; 
	_test_eof248:  state.cs = 248; goto _test_eof; 
	_test_eof249:  state.cs = 249; goto _test_eof; 
	_test_eof250:  state.cs = 250; goto _test_eof; 
	_test_eof251:  state.cs = 251; goto _test_eof; 
	_test_eof252:  state.cs = 252; goto _test_eof; 
	_test_eof253:  state.cs = 253; goto _test_eof; 
	_test_eof254:  state.cs = 254; goto _test_eof; 
	_test_eof255:  state.cs = 255; goto _test_eof; 
	_test_eof256:  state.cs = 256; goto _test_eof; 
	_test_eof257:  state.cs = 257; goto _test_eof; 
	_test_eof258:  state.cs = 258; goto _test_eof; 
	_test_eof259:  state.cs = 259; goto _test_eof; 
	_test_eof260:  state.cs = 260; goto _test_eof; 
	_test_eof261:  state.cs = 261; goto _test_eof; 
	_test_eof262:  state.cs = 262; goto _test_eof; 
	_test_eof263:  state.cs = 263; goto _test_eof; 
	_test_eof264:  state.cs = 264; goto _test_eof; 
	_test_eof265:  state.cs = 265; goto _test_eof; 
	_test_eof266:  state.cs = 266; goto _test_eof; 
	_test_eof267:  state.cs = 267; goto _test_eof; 
	_test_eof268:  state.cs = 268; goto _test_eof; 
	_test_eof269:  state.cs = 269; goto _test_eof; 
	_test_eof270:  state.cs = 270; goto _test_eof; 
	_test_eof271:  state.cs = 271; goto _test_eof; 
	_test_eof272:  state.cs = 272; goto _test_eof; 
	_test_eof273:  state.cs = 273; goto _test_eof; 
	_test_eof274:  state.cs = 274; goto _test_eof; 
	_test_eof275:  state.cs = 275; goto _test_eof; 
	_test_eof276:  state.cs = 276; goto _test_eof; 
	_test_eof277:  state.cs = 277; goto _test_eof; 
	_test_eof278:  state.cs = 278; goto _test_eof; 
	_test_eof279:  state.cs = 279; goto _test_eof; 
	_test_eof280:  state.cs = 280; goto _test_eof; 
	_test_eof281:  state.cs = 281; goto _test_eof; 
	_test_eof282:  state.cs = 282; goto _test_eof; 
	_test_eof283:  state.cs = 283; goto _test_eof; 
	_test_eof284:  state.cs = 284; goto _test_eof; 
	_test_eof285:  state.cs = 285; goto _test_eof; 
	_test_eof286:  state.cs = 286; goto _test_eof; 
	_test_eof287:  state.cs = 287; goto _test_eof; 
	_test_eof288:  state.cs = 288; goto _test_eof; 
	_test_eof289:  state.cs = 289; goto _test_eof; 
	_test_eof290:  state.cs = 290; goto _test_eof; 
	_test_eof291:  state.cs = 291; goto _test_eof; 
	_test_eof292:  state.cs = 292; goto _test_eof; 
	_test_eof293:  state.cs = 293; goto _test_eof; 
	_test_eof294:  state.cs = 294; goto _test_eof; 
	_test_eof295:  state.cs = 295; goto _test_eof; 
	_test_eof296:  state.cs = 296; goto _test_eof; 
	_test_eof297:  state.cs = 297; goto _test_eof; 
	_test_eof298:  state.cs = 298; goto _test_eof; 
	_test_eof299:  state.cs = 299; goto _test_eof; 
	_test_eof300:  state.cs = 300; goto _test_eof; 
	_test_eof301:  state.cs = 301; goto _test_eof; 
	_test_eof302:  state.cs = 302; goto _test_eof; 
	_test_eof303:  state.cs = 303; goto _test_eof; 
	_test_eof304:  state.cs = 304; goto _test_eof; 
	_test_eof305:  state.cs = 305; goto _test_eof; 
	_test_eof306:  state.cs = 306; goto _test_eof; 
	_test_eof307:  state.cs = 307; goto _test_eof; 
	_test_eof308:  state.cs = 308; goto _test_eof; 
	_test_eof309:  state.cs = 309; goto _test_eof; 
	_test_eof310:  state.cs = 310; goto _test_eof; 
	_test_eof594:  state.cs = 594; goto _test_eof; 
	_test_eof311:  state.cs = 311; goto _test_eof; 
	_test_eof312:  state.cs = 312; goto _test_eof; 
	_test_eof313:  state.cs = 313; goto _test_eof; 
	_test_eof314:  state.cs = 314; goto _test_eof; 
	_test_eof315:  state.cs = 315; goto _test_eof; 
	_test_eof316:  state.cs = 316; goto _test_eof; 
	_test_eof317:  state.cs = 317; goto _test_eof; 
	_test_eof318:  state.cs = 318; goto _test_eof; 
	_test_eof319:  state.cs = 319; goto _test_eof; 
	_test_eof320:  state.cs = 320; goto _test_eof; 
	_test_eof321:  state.cs = 321; goto _test_eof; 
	_test_eof322:  state.cs = 322; goto _test_eof; 
	_test_eof323:  state.cs = 323; goto _test_eof; 
	_test_eof324:  state.cs = 324; goto _test_eof; 
	_test_eof325:  state.cs = 325; goto _test_eof; 
	_test_eof326:  state.cs = 326; goto _test_eof; 
	_test_eof327:  state.cs = 327; goto _test_eof; 
	_test_eof328:  state.cs = 328; goto _test_eof; 
	_test_eof329:  state.cs = 329; goto _test_eof; 
	_test_eof330:  state.cs = 330; goto _test_eof; 
	_test_eof331:  state.cs = 331; goto _test_eof; 
	_test_eof332:  state.cs = 332; goto _test_eof; 
	_test_eof333:  state.cs = 333; goto _test_eof; 
	_test_eof334:  state.cs = 334; goto _test_eof; 
	_test_eof335:  state.cs = 335; goto _test_eof; 
	_test_eof336:  state.cs = 336; goto _test_eof; 
	_test_eof337:  state.cs = 337; goto _test_eof; 
	_test_eof338:  state.cs = 338; goto _test_eof; 
	_test_eof339:  state.cs = 339; goto _test_eof; 
	_test_eof340:  state.cs = 340; goto _test_eof; 
	_test_eof341:  state.cs = 341; goto _test_eof; 
	_test_eof342:  state.cs = 342; goto _test_eof; 
	_test_eof343:  state.cs = 343; goto _test_eof; 
	_test_eof344:  state.cs = 344; goto _test_eof; 
	_test_eof345:  state.cs = 345; goto _test_eof; 
	_test_eof346:  state.cs = 346; goto _test_eof; 
	_test_eof347:  state.cs = 347; goto _test_eof; 
	_test_eof348:  state.cs = 348; goto _test_eof; 
	_test_eof349:  state.cs = 349; goto _test_eof; 
	_test_eof350:  state.cs = 350; goto _test_eof; 
	_test_eof351:  state.cs = 351; goto _test_eof; 
	_test_eof352:  state.cs = 352; goto _test_eof; 
	_test_eof353:  state.cs = 353; goto _test_eof; 
	_test_eof354:  state.cs = 354; goto _test_eof; 
	_test_eof355:  state.cs = 355; goto _test_eof; 
	_test_eof356:  state.cs = 356; goto _test_eof; 
	_test_eof357:  state.cs = 357; goto _test_eof; 
	_test_eof358:  state.cs = 358; goto _test_eof; 
	_test_eof359:  state.cs = 359; goto _test_eof; 
	_test_eof360:  state.cs = 360; goto _test_eof; 
	_test_eof361:  state.cs = 361; goto _test_eof; 
	_test_eof362:  state.cs = 362; goto _test_eof; 
	_test_eof363:  state.cs = 363; goto _test_eof; 
	_test_eof364:  state.cs = 364; goto _test_eof; 
	_test_eof365:  state.cs = 365; goto _test_eof; 
	_test_eof366:  state.cs = 366; goto _test_eof; 
	_test_eof367:  state.cs = 367; goto _test_eof; 
	_test_eof368:  state.cs = 368; goto _test_eof; 
	_test_eof369:  state.cs = 369; goto _test_eof; 
	_test_eof370:  state.cs = 370; goto _test_eof; 
	_test_eof371:  state.cs = 371; goto _test_eof; 
	_test_eof372:  state.cs = 372; goto _test_eof; 
	_test_eof373:  state.cs = 373; goto _test_eof; 
	_test_eof374:  state.cs = 374; goto _test_eof; 
	_test_eof375:  state.cs = 375; goto _test_eof; 
	_test_eof376:  state.cs = 376; goto _test_eof; 
	_test_eof377:  state.cs = 377; goto _test_eof; 
	_test_eof378:  state.cs = 378; goto _test_eof; 
	_test_eof379:  state.cs = 379; goto _test_eof; 
	_test_eof380:  state.cs = 380; goto _test_eof; 
	_test_eof381:  state.cs = 381; goto _test_eof; 
	_test_eof382:  state.cs = 382; goto _test_eof; 
	_test_eof383:  state.cs = 383; goto _test_eof; 
	_test_eof384:  state.cs = 384; goto _test_eof; 
	_test_eof385:  state.cs = 385; goto _test_eof; 
	_test_eof386:  state.cs = 386; goto _test_eof; 
	_test_eof387:  state.cs = 387; goto _test_eof; 
	_test_eof388:  state.cs = 388; goto _test_eof; 
	_test_eof389:  state.cs = 389; goto _test_eof; 
	_test_eof390:  state.cs = 390; goto _test_eof; 
	_test_eof391:  state.cs = 391; goto _test_eof; 
	_test_eof392:  state.cs = 392; goto _test_eof; 
	_test_eof393:  state.cs = 393; goto _test_eof; 
	_test_eof394:  state.cs = 394; goto _test_eof; 
	_test_eof395:  state.cs = 395; goto _test_eof; 
	_test_eof396:  state.cs = 396; goto _test_eof; 
	_test_eof397:  state.cs = 397; goto _test_eof; 
	_test_eof398:  state.cs = 398; goto _test_eof; 
	_test_eof399:  state.cs = 399; goto _test_eof; 
	_test_eof400:  state.cs = 400; goto _test_eof; 
	_test_eof401:  state.cs = 401; goto _test_eof; 
	_test_eof402:  state.cs = 402; goto _test_eof; 
	_test_eof403:  state.cs = 403; goto _test_eof; 
	_test_eof404:  state.cs = 404; goto _test_eof; 
	_test_eof405:  state.cs = 405; goto _test_eof; 
	_test_eof406:  state.cs = 406; goto _test_eof; 
	_test_eof407:  state.cs = 407; goto _test_eof; 
	_test_eof408:  state.cs = 408; goto _test_eof; 
	_test_eof409:  state.cs = 409; goto _test_eof; 
	_test_eof410:  state.cs = 410; goto _test_eof; 
	_test_eof411:  state.cs = 411; goto _test_eof; 
	_test_eof412:  state.cs = 412; goto _test_eof; 
	_test_eof413:  state.cs = 413; goto _test_eof; 
	_test_eof414:  state.cs = 414; goto _test_eof; 
	_test_eof415:  state.cs = 415; goto _test_eof; 
	_test_eof416:  state.cs = 416; goto _test_eof; 
	_test_eof417:  state.cs = 417; goto _test_eof; 
	_test_eof418:  state.cs = 418; goto _test_eof; 
	_test_eof419:  state.cs = 419; goto _test_eof; 
	_test_eof420:  state.cs = 420; goto _test_eof; 
	_test_eof421:  state.cs = 421; goto _test_eof; 
	_test_eof422:  state.cs = 422; goto _test_eof; 
	_test_eof423:  state.cs = 423; goto _test_eof; 
	_test_eof424:  state.cs = 424; goto _test_eof; 
	_test_eof425:  state.cs = 425; goto _test_eof; 
	_test_eof426:  state.cs = 426; goto _test_eof; 
	_test_eof427:  state.cs = 427; goto _test_eof; 
	_test_eof428:  state.cs = 428; goto _test_eof; 
	_test_eof429:  state.cs = 429; goto _test_eof; 
	_test_eof430:  state.cs = 430; goto _test_eof; 
	_test_eof431:  state.cs = 431; goto _test_eof; 
	_test_eof432:  state.cs = 432; goto _test_eof; 
	_test_eof433:  state.cs = 433; goto _test_eof; 
	_test_eof434:  state.cs = 434; goto _test_eof; 
	_test_eof435:  state.cs = 435; goto _test_eof; 
	_test_eof436:  state.cs = 436; goto _test_eof; 
	_test_eof437:  state.cs = 437; goto _test_eof; 
	_test_eof438:  state.cs = 438; goto _test_eof; 
	_test_eof439:  state.cs = 439; goto _test_eof; 
	_test_eof440:  state.cs = 440; goto _test_eof; 
	_test_eof441:  state.cs = 441; goto _test_eof; 
	_test_eof442:  state.cs = 442; goto _test_eof; 
	_test_eof443:  state.cs = 443; goto _test_eof; 
	_test_eof444:  state.cs = 444; goto _test_eof; 
	_test_eof445:  state.cs = 445; goto _test_eof; 
	_test_eof446:  state.cs = 446; goto _test_eof; 
	_test_eof447:  state.cs = 447; goto _test_eof; 
	_test_eof448:  state.cs = 448; goto _test_eof; 
	_test_eof449:  state.cs = 449; goto _test_eof; 
	_test_eof450:  state.cs = 450; goto _test_eof; 
	_test_eof451:  state.cs = 451; goto _test_eof; 
	_test_eof452:  state.cs = 452; goto _test_eof; 
	_test_eof453:  state.cs = 453; goto _test_eof; 
	_test_eof454:  state.cs = 454; goto _test_eof; 
	_test_eof455:  state.cs = 455; goto _test_eof; 
	_test_eof456:  state.cs = 456; goto _test_eof; 
	_test_eof457:  state.cs = 457; goto _test_eof; 
	_test_eof595:  state.cs = 595; goto _test_eof; 
	_test_eof458:  state.cs = 458; goto _test_eof; 
	_test_eof459:  state.cs = 459; goto _test_eof; 
	_test_eof460:  state.cs = 460; goto _test_eof; 
	_test_eof461:  state.cs = 461; goto _test_eof; 
	_test_eof462:  state.cs = 462; goto _test_eof; 
	_test_eof463:  state.cs = 463; goto _test_eof; 
	_test_eof464:  state.cs = 464; goto _test_eof; 
	_test_eof465:  state.cs = 465; goto _test_eof; 
	_test_eof466:  state.cs = 466; goto _test_eof; 
	_test_eof467:  state.cs = 467; goto _test_eof; 
	_test_eof468:  state.cs = 468; goto _test_eof; 
	_test_eof469:  state.cs = 469; goto _test_eof; 
	_test_eof470:  state.cs = 470; goto _test_eof; 
	_test_eof471:  state.cs = 471; goto _test_eof; 
	_test_eof472:  state.cs = 472; goto _test_eof; 
	_test_eof473:  state.cs = 473; goto _test_eof; 
	_test_eof474:  state.cs = 474; goto _test_eof; 
	_test_eof475:  state.cs = 475; goto _test_eof; 
	_test_eof476:  state.cs = 476; goto _test_eof; 
	_test_eof477:  state.cs = 477; goto _test_eof; 
	_test_eof478:  state.cs = 478; goto _test_eof; 
	_test_eof479:  state.cs = 479; goto _test_eof; 
	_test_eof480:  state.cs = 480; goto _test_eof; 
	_test_eof481:  state.cs = 481; goto _test_eof; 
	_test_eof482:  state.cs = 482; goto _test_eof; 
	_test_eof483:  state.cs = 483; goto _test_eof; 
	_test_eof484:  state.cs = 484; goto _test_eof; 
	_test_eof485:  state.cs = 485; goto _test_eof; 
	_test_eof486:  state.cs = 486; goto _test_eof; 
	_test_eof487:  state.cs = 487; goto _test_eof; 
	_test_eof488:  state.cs = 488; goto _test_eof; 
	_test_eof489:  state.cs = 489; goto _test_eof; 
	_test_eof490:  state.cs = 490; goto _test_eof; 
	_test_eof491:  state.cs = 491; goto _test_eof; 
	_test_eof492:  state.cs = 492; goto _test_eof; 
	_test_eof493:  state.cs = 493; goto _test_eof; 
	_test_eof494:  state.cs = 494; goto _test_eof; 
	_test_eof495:  state.cs = 495; goto _test_eof; 
	_test_eof496:  state.cs = 496; goto _test_eof; 
	_test_eof497:  state.cs = 497; goto _test_eof; 
	_test_eof498:  state.cs = 498; goto _test_eof; 
	_test_eof499:  state.cs = 499; goto _test_eof; 
	_test_eof500:  state.cs = 500; goto _test_eof; 
	_test_eof501:  state.cs = 501; goto _test_eof; 
	_test_eof502:  state.cs = 502; goto _test_eof; 
	_test_eof503:  state.cs = 503; goto _test_eof; 
	_test_eof504:  state.cs = 504; goto _test_eof; 
	_test_eof505:  state.cs = 505; goto _test_eof; 
	_test_eof506:  state.cs = 506; goto _test_eof; 
	_test_eof507:  state.cs = 507; goto _test_eof; 
	_test_eof508:  state.cs = 508; goto _test_eof; 
	_test_eof509:  state.cs = 509; goto _test_eof; 
	_test_eof510:  state.cs = 510; goto _test_eof; 
	_test_eof511:  state.cs = 511; goto _test_eof; 
	_test_eof512:  state.cs = 512; goto _test_eof; 
	_test_eof513:  state.cs = 513; goto _test_eof; 
	_test_eof514:  state.cs = 514; goto _test_eof; 
	_test_eof515:  state.cs = 515; goto _test_eof; 
	_test_eof516:  state.cs = 516; goto _test_eof; 
	_test_eof517:  state.cs = 517; goto _test_eof; 
	_test_eof518:  state.cs = 518; goto _test_eof; 
	_test_eof519:  state.cs = 519; goto _test_eof; 
	_test_eof520:  state.cs = 520; goto _test_eof; 
	_test_eof521:  state.cs = 521; goto _test_eof; 
	_test_eof522:  state.cs = 522; goto _test_eof; 
	_test_eof523:  state.cs = 523; goto _test_eof; 
	_test_eof524:  state.cs = 524; goto _test_eof; 
	_test_eof525:  state.cs = 525; goto _test_eof; 
	_test_eof526:  state.cs = 526; goto _test_eof; 
	_test_eof527:  state.cs = 527; goto _test_eof; 
	_test_eof528:  state.cs = 528; goto _test_eof; 
	_test_eof529:  state.cs = 529; goto _test_eof; 
	_test_eof530:  state.cs = 530; goto _test_eof; 
	_test_eof531:  state.cs = 531; goto _test_eof; 
	_test_eof532:  state.cs = 532; goto _test_eof; 
	_test_eof533:  state.cs = 533; goto _test_eof; 
	_test_eof534:  state.cs = 534; goto _test_eof; 
	_test_eof535:  state.cs = 535; goto _test_eof; 
	_test_eof536:  state.cs = 536; goto _test_eof; 
	_test_eof537:  state.cs = 537; goto _test_eof; 
	_test_eof538:  state.cs = 538; goto _test_eof; 
	_test_eof539:  state.cs = 539; goto _test_eof; 
	_test_eof540:  state.cs = 540; goto _test_eof; 
	_test_eof541:  state.cs = 541; goto _test_eof; 
	_test_eof542:  state.cs = 542; goto _test_eof; 
	_test_eof543:  state.cs = 543; goto _test_eof; 
	_test_eof544:  state.cs = 544; goto _test_eof; 
	_test_eof545:  state.cs = 545; goto _test_eof; 
	_test_eof546:  state.cs = 546; goto _test_eof; 
	_test_eof547:  state.cs = 547; goto _test_eof; 
	_test_eof548:  state.cs = 548; goto _test_eof; 
	_test_eof549:  state.cs = 549; goto _test_eof; 
	_test_eof550:  state.cs = 550; goto _test_eof; 
	_test_eof551:  state.cs = 551; goto _test_eof; 
	_test_eof552:  state.cs = 552; goto _test_eof; 
	_test_eof553:  state.cs = 553; goto _test_eof; 
	_test_eof554:  state.cs = 554; goto _test_eof; 
	_test_eof555:  state.cs = 555; goto _test_eof; 
	_test_eof556:  state.cs = 556; goto _test_eof; 
	_test_eof557:  state.cs = 557; goto _test_eof; 
	_test_eof558:  state.cs = 558; goto _test_eof; 
	_test_eof559:  state.cs = 559; goto _test_eof; 
	_test_eof560:  state.cs = 560; goto _test_eof; 
	_test_eof561:  state.cs = 561; goto _test_eof; 
	_test_eof562:  state.cs = 562; goto _test_eof; 
	_test_eof563:  state.cs = 563; goto _test_eof; 
	_test_eof564:  state.cs = 564; goto _test_eof; 
	_test_eof565:  state.cs = 565; goto _test_eof; 
	_test_eof566:  state.cs = 566; goto _test_eof; 
	_test_eof567:  state.cs = 567; goto _test_eof; 
	_test_eof568:  state.cs = 568; goto _test_eof; 
	_test_eof569:  state.cs = 569; goto _test_eof; 
	_test_eof570:  state.cs = 570; goto _test_eof; 
	_test_eof571:  state.cs = 571; goto _test_eof; 
	_test_eof572:  state.cs = 572; goto _test_eof; 
	_test_eof573:  state.cs = 573; goto _test_eof; 
	_test_eof574:  state.cs = 574; goto _test_eof; 
	_test_eof575:  state.cs = 575; goto _test_eof; 
	_test_eof576:  state.cs = 576; goto _test_eof; 
	_test_eof577:  state.cs = 577; goto _test_eof; 
	_test_eof578:  state.cs = 578; goto _test_eof; 
	_test_eof579:  state.cs = 579; goto _test_eof; 
	_test_eof580:  state.cs = 580; goto _test_eof; 
	_test_eof581:  state.cs = 581; goto _test_eof; 
	_test_eof582:  state.cs = 582; goto _test_eof; 
	_test_eof583:  state.cs = 583; goto _test_eof; 
	_test_eof584:  state.cs = 584; goto _test_eof; 
	_test_eof585:  state.cs = 585; goto _test_eof; 
	_test_eof586:  state.cs = 586; goto _test_eof; 
	_test_eof587:  state.cs = 587; goto _test_eof; 

	_test_eof: {}
	if ( ( state.p) == ( state.eof) )
	{
	switch (  state.cs ) {
	case 590: 
#line 233 "configparser.rl"
	{ init_species(spe); }
	break;
	case 588: 
#line 271 "configparser.rl"
	{ init_design(des); }
	break;
	case 591: 
#line 311 "configparser.rl"
	{ init_terrain(ter); }
	break;
#line 8824 "configparser.h"
	}
	}

	_out: {}
	}

#line 350 "configparser.rl"

        // Avoid spurious gcc warnings.
        (void)ConfigParser_first_final;
        (void)ConfigParser_en_strchar_escape;
        (void)ConfigParser_en_one_species;
        (void)ConfigParser_en_one_design;
        (void)ConfigParser_en_one_terrain;
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
