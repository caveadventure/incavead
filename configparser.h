
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
    Levelskin lev;

    damage::val_t dmgval;

    maudit::glyph skin;

    
#line 406 "configparser.rl"

/*

*/

    
#line 111 "configparser.h"
static const int ConfigParser_start = 1;
static const int ConfigParser_first_final = 1518;
static const int ConfigParser_error = 0;

static const int ConfigParser_en_strchar_escape = 47;
static const int ConfigParser_en_one_species = 48;
static const int ConfigParser_en_one_design = 395;
static const int ConfigParser_en_one_terrain = 600;
static const int ConfigParser_en_one_levelskin = 795;
static const int ConfigParser_en_main = 1;


#line 412 "configparser.rl"
    
#line 126 "configparser.h"
	{
	 state.cs = ConfigParser_start;
	 state.top = 0;
	}

#line 413 "configparser.rl"

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

        
#line 155 "configparser.h"
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
		case 1518: goto st1518;
		case 1519: goto st1519;
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
		case 1520: goto st1520;
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
		case 35: goto st35;
		case 36: goto st36;
		case 1521: goto st1521;
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
		case 1522: goto st1522;
		case 47: goto st47;
		case 1523: goto st1523;
		case 48: goto st48;
		case 49: goto st49;
		case 50: goto st50;
		case 51: goto st51;
		case 52: goto st52;
		case 53: goto st53;
		case 54: goto st54;
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
		case 1524: goto st1524;
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
		case 1525: goto st1525;
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
		case 588: goto st588;
		case 589: goto st589;
		case 590: goto st590;
		case 591: goto st591;
		case 592: goto st592;
		case 593: goto st593;
		case 594: goto st594;
		case 595: goto st595;
		case 596: goto st596;
		case 597: goto st597;
		case 598: goto st598;
		case 599: goto st599;
		case 600: goto st600;
		case 601: goto st601;
		case 602: goto st602;
		case 603: goto st603;
		case 604: goto st604;
		case 605: goto st605;
		case 606: goto st606;
		case 607: goto st607;
		case 608: goto st608;
		case 609: goto st609;
		case 610: goto st610;
		case 611: goto st611;
		case 612: goto st612;
		case 613: goto st613;
		case 614: goto st614;
		case 615: goto st615;
		case 616: goto st616;
		case 617: goto st617;
		case 618: goto st618;
		case 619: goto st619;
		case 1526: goto st1526;
		case 620: goto st620;
		case 621: goto st621;
		case 622: goto st622;
		case 623: goto st623;
		case 624: goto st624;
		case 625: goto st625;
		case 626: goto st626;
		case 627: goto st627;
		case 628: goto st628;
		case 629: goto st629;
		case 630: goto st630;
		case 631: goto st631;
		case 632: goto st632;
		case 633: goto st633;
		case 634: goto st634;
		case 635: goto st635;
		case 636: goto st636;
		case 637: goto st637;
		case 638: goto st638;
		case 639: goto st639;
		case 640: goto st640;
		case 641: goto st641;
		case 642: goto st642;
		case 643: goto st643;
		case 644: goto st644;
		case 645: goto st645;
		case 646: goto st646;
		case 647: goto st647;
		case 648: goto st648;
		case 649: goto st649;
		case 650: goto st650;
		case 651: goto st651;
		case 652: goto st652;
		case 653: goto st653;
		case 654: goto st654;
		case 655: goto st655;
		case 656: goto st656;
		case 657: goto st657;
		case 658: goto st658;
		case 659: goto st659;
		case 660: goto st660;
		case 661: goto st661;
		case 662: goto st662;
		case 663: goto st663;
		case 664: goto st664;
		case 665: goto st665;
		case 666: goto st666;
		case 667: goto st667;
		case 668: goto st668;
		case 669: goto st669;
		case 670: goto st670;
		case 671: goto st671;
		case 672: goto st672;
		case 673: goto st673;
		case 674: goto st674;
		case 675: goto st675;
		case 676: goto st676;
		case 677: goto st677;
		case 678: goto st678;
		case 679: goto st679;
		case 680: goto st680;
		case 681: goto st681;
		case 682: goto st682;
		case 683: goto st683;
		case 684: goto st684;
		case 685: goto st685;
		case 686: goto st686;
		case 687: goto st687;
		case 688: goto st688;
		case 689: goto st689;
		case 690: goto st690;
		case 691: goto st691;
		case 692: goto st692;
		case 693: goto st693;
		case 694: goto st694;
		case 695: goto st695;
		case 696: goto st696;
		case 697: goto st697;
		case 698: goto st698;
		case 699: goto st699;
		case 700: goto st700;
		case 701: goto st701;
		case 702: goto st702;
		case 703: goto st703;
		case 704: goto st704;
		case 705: goto st705;
		case 706: goto st706;
		case 707: goto st707;
		case 708: goto st708;
		case 709: goto st709;
		case 710: goto st710;
		case 711: goto st711;
		case 712: goto st712;
		case 713: goto st713;
		case 714: goto st714;
		case 715: goto st715;
		case 716: goto st716;
		case 717: goto st717;
		case 718: goto st718;
		case 719: goto st719;
		case 720: goto st720;
		case 721: goto st721;
		case 722: goto st722;
		case 723: goto st723;
		case 724: goto st724;
		case 725: goto st725;
		case 726: goto st726;
		case 727: goto st727;
		case 728: goto st728;
		case 729: goto st729;
		case 730: goto st730;
		case 731: goto st731;
		case 732: goto st732;
		case 733: goto st733;
		case 734: goto st734;
		case 735: goto st735;
		case 736: goto st736;
		case 737: goto st737;
		case 738: goto st738;
		case 739: goto st739;
		case 740: goto st740;
		case 741: goto st741;
		case 742: goto st742;
		case 743: goto st743;
		case 744: goto st744;
		case 745: goto st745;
		case 746: goto st746;
		case 747: goto st747;
		case 748: goto st748;
		case 749: goto st749;
		case 750: goto st750;
		case 751: goto st751;
		case 752: goto st752;
		case 753: goto st753;
		case 754: goto st754;
		case 755: goto st755;
		case 756: goto st756;
		case 757: goto st757;
		case 758: goto st758;
		case 759: goto st759;
		case 760: goto st760;
		case 761: goto st761;
		case 762: goto st762;
		case 763: goto st763;
		case 764: goto st764;
		case 765: goto st765;
		case 766: goto st766;
		case 767: goto st767;
		case 768: goto st768;
		case 769: goto st769;
		case 770: goto st770;
		case 771: goto st771;
		case 772: goto st772;
		case 773: goto st773;
		case 774: goto st774;
		case 775: goto st775;
		case 776: goto st776;
		case 777: goto st777;
		case 778: goto st778;
		case 779: goto st779;
		case 780: goto st780;
		case 781: goto st781;
		case 782: goto st782;
		case 783: goto st783;
		case 784: goto st784;
		case 785: goto st785;
		case 786: goto st786;
		case 787: goto st787;
		case 788: goto st788;
		case 789: goto st789;
		case 790: goto st790;
		case 791: goto st791;
		case 792: goto st792;
		case 793: goto st793;
		case 794: goto st794;
		case 795: goto st795;
		case 796: goto st796;
		case 797: goto st797;
		case 798: goto st798;
		case 799: goto st799;
		case 800: goto st800;
		case 801: goto st801;
		case 802: goto st802;
		case 803: goto st803;
		case 804: goto st804;
		case 805: goto st805;
		case 806: goto st806;
		case 807: goto st807;
		case 808: goto st808;
		case 809: goto st809;
		case 810: goto st810;
		case 811: goto st811;
		case 812: goto st812;
		case 813: goto st813;
		case 814: goto st814;
		case 815: goto st815;
		case 816: goto st816;
		case 817: goto st817;
		case 818: goto st818;
		case 819: goto st819;
		case 820: goto st820;
		case 821: goto st821;
		case 822: goto st822;
		case 1527: goto st1527;
		case 823: goto st823;
		case 824: goto st824;
		case 825: goto st825;
		case 826: goto st826;
		case 827: goto st827;
		case 828: goto st828;
		case 829: goto st829;
		case 830: goto st830;
		case 831: goto st831;
		case 832: goto st832;
		case 833: goto st833;
		case 834: goto st834;
		case 835: goto st835;
		case 836: goto st836;
		case 837: goto st837;
		case 838: goto st838;
		case 839: goto st839;
		case 840: goto st840;
		case 841: goto st841;
		case 842: goto st842;
		case 843: goto st843;
		case 844: goto st844;
		case 845: goto st845;
		case 846: goto st846;
		case 847: goto st847;
		case 848: goto st848;
		case 849: goto st849;
		case 850: goto st850;
		case 851: goto st851;
		case 852: goto st852;
		case 853: goto st853;
		case 854: goto st854;
		case 855: goto st855;
		case 856: goto st856;
		case 857: goto st857;
		case 858: goto st858;
		case 859: goto st859;
		case 860: goto st860;
		case 861: goto st861;
		case 862: goto st862;
		case 863: goto st863;
		case 864: goto st864;
		case 865: goto st865;
		case 866: goto st866;
		case 867: goto st867;
		case 868: goto st868;
		case 869: goto st869;
		case 870: goto st870;
		case 871: goto st871;
		case 872: goto st872;
		case 873: goto st873;
		case 874: goto st874;
		case 875: goto st875;
		case 876: goto st876;
		case 877: goto st877;
		case 878: goto st878;
		case 879: goto st879;
		case 880: goto st880;
		case 881: goto st881;
		case 882: goto st882;
		case 883: goto st883;
		case 884: goto st884;
		case 885: goto st885;
		case 886: goto st886;
		case 887: goto st887;
		case 888: goto st888;
		case 889: goto st889;
		case 890: goto st890;
		case 891: goto st891;
		case 892: goto st892;
		case 893: goto st893;
		case 894: goto st894;
		case 895: goto st895;
		case 896: goto st896;
		case 897: goto st897;
		case 898: goto st898;
		case 899: goto st899;
		case 900: goto st900;
		case 901: goto st901;
		case 902: goto st902;
		case 903: goto st903;
		case 904: goto st904;
		case 905: goto st905;
		case 906: goto st906;
		case 907: goto st907;
		case 908: goto st908;
		case 909: goto st909;
		case 910: goto st910;
		case 911: goto st911;
		case 912: goto st912;
		case 913: goto st913;
		case 914: goto st914;
		case 915: goto st915;
		case 916: goto st916;
		case 917: goto st917;
		case 918: goto st918;
		case 919: goto st919;
		case 920: goto st920;
		case 921: goto st921;
		case 922: goto st922;
		case 923: goto st923;
		case 924: goto st924;
		case 925: goto st925;
		case 926: goto st926;
		case 927: goto st927;
		case 928: goto st928;
		case 929: goto st929;
		case 930: goto st930;
		case 931: goto st931;
		case 932: goto st932;
		case 933: goto st933;
		case 934: goto st934;
		case 935: goto st935;
		case 936: goto st936;
		case 937: goto st937;
		case 938: goto st938;
		case 939: goto st939;
		case 940: goto st940;
		case 941: goto st941;
		case 942: goto st942;
		case 943: goto st943;
		case 944: goto st944;
		case 945: goto st945;
		case 946: goto st946;
		case 947: goto st947;
		case 948: goto st948;
		case 949: goto st949;
		case 950: goto st950;
		case 951: goto st951;
		case 952: goto st952;
		case 953: goto st953;
		case 954: goto st954;
		case 955: goto st955;
		case 956: goto st956;
		case 957: goto st957;
		case 958: goto st958;
		case 959: goto st959;
		case 960: goto st960;
		case 961: goto st961;
		case 962: goto st962;
		case 963: goto st963;
		case 964: goto st964;
		case 965: goto st965;
		case 966: goto st966;
		case 967: goto st967;
		case 968: goto st968;
		case 969: goto st969;
		case 970: goto st970;
		case 971: goto st971;
		case 972: goto st972;
		case 973: goto st973;
		case 974: goto st974;
		case 975: goto st975;
		case 976: goto st976;
		case 977: goto st977;
		case 978: goto st978;
		case 979: goto st979;
		case 980: goto st980;
		case 981: goto st981;
		case 982: goto st982;
		case 983: goto st983;
		case 984: goto st984;
		case 985: goto st985;
		case 986: goto st986;
		case 987: goto st987;
		case 988: goto st988;
		case 989: goto st989;
		case 990: goto st990;
		case 991: goto st991;
		case 992: goto st992;
		case 993: goto st993;
		case 994: goto st994;
		case 995: goto st995;
		case 996: goto st996;
		case 997: goto st997;
		case 998: goto st998;
		case 999: goto st999;
		case 1000: goto st1000;
		case 1001: goto st1001;
		case 1002: goto st1002;
		case 1003: goto st1003;
		case 1004: goto st1004;
		case 1005: goto st1005;
		case 1006: goto st1006;
		case 1007: goto st1007;
		case 1008: goto st1008;
		case 1009: goto st1009;
		case 1010: goto st1010;
		case 1011: goto st1011;
		case 1012: goto st1012;
		case 1013: goto st1013;
		case 1014: goto st1014;
		case 1015: goto st1015;
		case 1016: goto st1016;
		case 1017: goto st1017;
		case 1018: goto st1018;
		case 1019: goto st1019;
		case 1020: goto st1020;
		case 1021: goto st1021;
		case 1022: goto st1022;
		case 1023: goto st1023;
		case 1024: goto st1024;
		case 1025: goto st1025;
		case 1026: goto st1026;
		case 1027: goto st1027;
		case 1028: goto st1028;
		case 1029: goto st1029;
		case 1030: goto st1030;
		case 1031: goto st1031;
		case 1032: goto st1032;
		case 1033: goto st1033;
		case 1034: goto st1034;
		case 1035: goto st1035;
		case 1036: goto st1036;
		case 1037: goto st1037;
		case 1038: goto st1038;
		case 1039: goto st1039;
		case 1040: goto st1040;
		case 1041: goto st1041;
		case 1042: goto st1042;
		case 1043: goto st1043;
		case 1044: goto st1044;
		case 1045: goto st1045;
		case 1046: goto st1046;
		case 1047: goto st1047;
		case 1048: goto st1048;
		case 1049: goto st1049;
		case 1050: goto st1050;
		case 1051: goto st1051;
		case 1052: goto st1052;
		case 1053: goto st1053;
		case 1054: goto st1054;
		case 1055: goto st1055;
		case 1056: goto st1056;
		case 1057: goto st1057;
		case 1058: goto st1058;
		case 1059: goto st1059;
		case 1060: goto st1060;
		case 1061: goto st1061;
		case 1062: goto st1062;
		case 1063: goto st1063;
		case 1064: goto st1064;
		case 1065: goto st1065;
		case 1066: goto st1066;
		case 1067: goto st1067;
		case 1068: goto st1068;
		case 1069: goto st1069;
		case 1070: goto st1070;
		case 1071: goto st1071;
		case 1072: goto st1072;
		case 1073: goto st1073;
		case 1074: goto st1074;
		case 1075: goto st1075;
		case 1076: goto st1076;
		case 1077: goto st1077;
		case 1078: goto st1078;
		case 1079: goto st1079;
		case 1080: goto st1080;
		case 1081: goto st1081;
		case 1082: goto st1082;
		case 1083: goto st1083;
		case 1084: goto st1084;
		case 1085: goto st1085;
		case 1086: goto st1086;
		case 1087: goto st1087;
		case 1088: goto st1088;
		case 1089: goto st1089;
		case 1090: goto st1090;
		case 1091: goto st1091;
		case 1092: goto st1092;
		case 1093: goto st1093;
		case 1094: goto st1094;
		case 1095: goto st1095;
		case 1096: goto st1096;
		case 1097: goto st1097;
		case 1098: goto st1098;
		case 1099: goto st1099;
		case 1100: goto st1100;
		case 1101: goto st1101;
		case 1102: goto st1102;
		case 1103: goto st1103;
		case 1104: goto st1104;
		case 1105: goto st1105;
		case 1106: goto st1106;
		case 1107: goto st1107;
		case 1108: goto st1108;
		case 1109: goto st1109;
		case 1110: goto st1110;
		case 1111: goto st1111;
		case 1112: goto st1112;
		case 1113: goto st1113;
		case 1114: goto st1114;
		case 1115: goto st1115;
		case 1116: goto st1116;
		case 1117: goto st1117;
		case 1118: goto st1118;
		case 1119: goto st1119;
		case 1120: goto st1120;
		case 1121: goto st1121;
		case 1122: goto st1122;
		case 1123: goto st1123;
		case 1124: goto st1124;
		case 1125: goto st1125;
		case 1126: goto st1126;
		case 1127: goto st1127;
		case 1128: goto st1128;
		case 1129: goto st1129;
		case 1130: goto st1130;
		case 1131: goto st1131;
		case 1132: goto st1132;
		case 1133: goto st1133;
		case 1134: goto st1134;
		case 1135: goto st1135;
		case 1136: goto st1136;
		case 1137: goto st1137;
		case 1138: goto st1138;
		case 1139: goto st1139;
		case 1140: goto st1140;
		case 1141: goto st1141;
		case 1142: goto st1142;
		case 1143: goto st1143;
		case 1144: goto st1144;
		case 1145: goto st1145;
		case 1146: goto st1146;
		case 1147: goto st1147;
		case 1148: goto st1148;
		case 1149: goto st1149;
		case 1150: goto st1150;
		case 1151: goto st1151;
		case 1152: goto st1152;
		case 1153: goto st1153;
		case 1154: goto st1154;
		case 1155: goto st1155;
		case 1156: goto st1156;
		case 1157: goto st1157;
		case 1158: goto st1158;
		case 1159: goto st1159;
		case 1160: goto st1160;
		case 1161: goto st1161;
		case 1162: goto st1162;
		case 1163: goto st1163;
		case 1164: goto st1164;
		case 1165: goto st1165;
		case 1166: goto st1166;
		case 1167: goto st1167;
		case 1168: goto st1168;
		case 1169: goto st1169;
		case 1170: goto st1170;
		case 1171: goto st1171;
		case 1172: goto st1172;
		case 1173: goto st1173;
		case 1174: goto st1174;
		case 1175: goto st1175;
		case 1176: goto st1176;
		case 1177: goto st1177;
		case 1178: goto st1178;
		case 1179: goto st1179;
		case 1180: goto st1180;
		case 1181: goto st1181;
		case 1182: goto st1182;
		case 1183: goto st1183;
		case 1184: goto st1184;
		case 1185: goto st1185;
		case 1186: goto st1186;
		case 1187: goto st1187;
		case 1188: goto st1188;
		case 1189: goto st1189;
		case 1190: goto st1190;
		case 1191: goto st1191;
		case 1192: goto st1192;
		case 1193: goto st1193;
		case 1194: goto st1194;
		case 1195: goto st1195;
		case 1196: goto st1196;
		case 1197: goto st1197;
		case 1198: goto st1198;
		case 1199: goto st1199;
		case 1200: goto st1200;
		case 1201: goto st1201;
		case 1202: goto st1202;
		case 1203: goto st1203;
		case 1204: goto st1204;
		case 1205: goto st1205;
		case 1206: goto st1206;
		case 1207: goto st1207;
		case 1208: goto st1208;
		case 1209: goto st1209;
		case 1210: goto st1210;
		case 1211: goto st1211;
		case 1212: goto st1212;
		case 1213: goto st1213;
		case 1214: goto st1214;
		case 1215: goto st1215;
		case 1216: goto st1216;
		case 1217: goto st1217;
		case 1218: goto st1218;
		case 1219: goto st1219;
		case 1220: goto st1220;
		case 1221: goto st1221;
		case 1222: goto st1222;
		case 1223: goto st1223;
		case 1224: goto st1224;
		case 1225: goto st1225;
		case 1226: goto st1226;
		case 1227: goto st1227;
		case 1228: goto st1228;
		case 1229: goto st1229;
		case 1230: goto st1230;
		case 1231: goto st1231;
		case 1232: goto st1232;
		case 1233: goto st1233;
		case 1234: goto st1234;
		case 1235: goto st1235;
		case 1236: goto st1236;
		case 1237: goto st1237;
		case 1238: goto st1238;
		case 1239: goto st1239;
		case 1240: goto st1240;
		case 1241: goto st1241;
		case 1242: goto st1242;
		case 1243: goto st1243;
		case 1244: goto st1244;
		case 1245: goto st1245;
		case 1246: goto st1246;
		case 1247: goto st1247;
		case 1248: goto st1248;
		case 1249: goto st1249;
		case 1250: goto st1250;
		case 1251: goto st1251;
		case 1252: goto st1252;
		case 1253: goto st1253;
		case 1254: goto st1254;
		case 1255: goto st1255;
		case 1256: goto st1256;
		case 1257: goto st1257;
		case 1258: goto st1258;
		case 1259: goto st1259;
		case 1260: goto st1260;
		case 1261: goto st1261;
		case 1262: goto st1262;
		case 1263: goto st1263;
		case 1264: goto st1264;
		case 1265: goto st1265;
		case 1266: goto st1266;
		case 1267: goto st1267;
		case 1268: goto st1268;
		case 1269: goto st1269;
		case 1270: goto st1270;
		case 1271: goto st1271;
		case 1272: goto st1272;
		case 1273: goto st1273;
		case 1274: goto st1274;
		case 1275: goto st1275;
		case 1276: goto st1276;
		case 1277: goto st1277;
		case 1278: goto st1278;
		case 1279: goto st1279;
		case 1280: goto st1280;
		case 1281: goto st1281;
		case 1282: goto st1282;
		case 1283: goto st1283;
		case 1284: goto st1284;
		case 1285: goto st1285;
		case 1286: goto st1286;
		case 1287: goto st1287;
		case 1288: goto st1288;
		case 1289: goto st1289;
		case 1290: goto st1290;
		case 1291: goto st1291;
		case 1292: goto st1292;
		case 1293: goto st1293;
		case 1294: goto st1294;
		case 1295: goto st1295;
		case 1296: goto st1296;
		case 1297: goto st1297;
		case 1298: goto st1298;
		case 1299: goto st1299;
		case 1300: goto st1300;
		case 1301: goto st1301;
		case 1302: goto st1302;
		case 1303: goto st1303;
		case 1304: goto st1304;
		case 1305: goto st1305;
		case 1306: goto st1306;
		case 1307: goto st1307;
		case 1308: goto st1308;
		case 1309: goto st1309;
		case 1310: goto st1310;
		case 1311: goto st1311;
		case 1312: goto st1312;
		case 1313: goto st1313;
		case 1314: goto st1314;
		case 1315: goto st1315;
		case 1316: goto st1316;
		case 1317: goto st1317;
		case 1318: goto st1318;
		case 1319: goto st1319;
		case 1320: goto st1320;
		case 1321: goto st1321;
		case 1322: goto st1322;
		case 1323: goto st1323;
		case 1324: goto st1324;
		case 1325: goto st1325;
		case 1326: goto st1326;
		case 1327: goto st1327;
		case 1328: goto st1328;
		case 1329: goto st1329;
		case 1330: goto st1330;
		case 1331: goto st1331;
		case 1332: goto st1332;
		case 1333: goto st1333;
		case 1334: goto st1334;
		case 1335: goto st1335;
		case 1336: goto st1336;
		case 1337: goto st1337;
		case 1338: goto st1338;
		case 1339: goto st1339;
		case 1340: goto st1340;
		case 1341: goto st1341;
		case 1342: goto st1342;
		case 1343: goto st1343;
		case 1344: goto st1344;
		case 1345: goto st1345;
		case 1346: goto st1346;
		case 1347: goto st1347;
		case 1348: goto st1348;
		case 1349: goto st1349;
		case 1350: goto st1350;
		case 1351: goto st1351;
		case 1352: goto st1352;
		case 1353: goto st1353;
		case 1354: goto st1354;
		case 1355: goto st1355;
		case 1356: goto st1356;
		case 1357: goto st1357;
		case 1358: goto st1358;
		case 1359: goto st1359;
		case 1360: goto st1360;
		case 1361: goto st1361;
		case 1362: goto st1362;
		case 1363: goto st1363;
		case 1364: goto st1364;
		case 1365: goto st1365;
		case 1366: goto st1366;
		case 1367: goto st1367;
		case 1368: goto st1368;
		case 1369: goto st1369;
		case 1370: goto st1370;
		case 1371: goto st1371;
		case 1372: goto st1372;
		case 1373: goto st1373;
		case 1374: goto st1374;
		case 1375: goto st1375;
		case 1376: goto st1376;
		case 1377: goto st1377;
		case 1378: goto st1378;
		case 1379: goto st1379;
		case 1380: goto st1380;
		case 1381: goto st1381;
		case 1382: goto st1382;
		case 1383: goto st1383;
		case 1384: goto st1384;
		case 1385: goto st1385;
		case 1386: goto st1386;
		case 1387: goto st1387;
		case 1388: goto st1388;
		case 1389: goto st1389;
		case 1390: goto st1390;
		case 1391: goto st1391;
		case 1392: goto st1392;
		case 1393: goto st1393;
		case 1394: goto st1394;
		case 1395: goto st1395;
		case 1396: goto st1396;
		case 1397: goto st1397;
		case 1398: goto st1398;
		case 1399: goto st1399;
		case 1400: goto st1400;
		case 1401: goto st1401;
		case 1402: goto st1402;
		case 1403: goto st1403;
		case 1404: goto st1404;
		case 1405: goto st1405;
		case 1406: goto st1406;
		case 1407: goto st1407;
		case 1408: goto st1408;
		case 1409: goto st1409;
		case 1410: goto st1410;
		case 1411: goto st1411;
		case 1412: goto st1412;
		case 1413: goto st1413;
		case 1414: goto st1414;
		case 1415: goto st1415;
		case 1416: goto st1416;
		case 1417: goto st1417;
		case 1418: goto st1418;
		case 1419: goto st1419;
		case 1420: goto st1420;
		case 1421: goto st1421;
		case 1422: goto st1422;
		case 1423: goto st1423;
		case 1424: goto st1424;
		case 1425: goto st1425;
		case 1426: goto st1426;
		case 1427: goto st1427;
		case 1428: goto st1428;
		case 1429: goto st1429;
		case 1430: goto st1430;
		case 1431: goto st1431;
		case 1432: goto st1432;
		case 1433: goto st1433;
		case 1434: goto st1434;
		case 1435: goto st1435;
		case 1436: goto st1436;
		case 1437: goto st1437;
		case 1438: goto st1438;
		case 1439: goto st1439;
		case 1440: goto st1440;
		case 1441: goto st1441;
		case 1442: goto st1442;
		case 1443: goto st1443;
		case 1444: goto st1444;
		case 1445: goto st1445;
		case 1446: goto st1446;
		case 1447: goto st1447;
		case 1448: goto st1448;
		case 1449: goto st1449;
		case 1450: goto st1450;
		case 1451: goto st1451;
		case 1452: goto st1452;
		case 1453: goto st1453;
		case 1454: goto st1454;
		case 1455: goto st1455;
		case 1456: goto st1456;
		case 1457: goto st1457;
		case 1458: goto st1458;
		case 1459: goto st1459;
		case 1460: goto st1460;
		case 1461: goto st1461;
		case 1462: goto st1462;
		case 1463: goto st1463;
		case 1464: goto st1464;
		case 1465: goto st1465;
		case 1466: goto st1466;
		case 1467: goto st1467;
		case 1468: goto st1468;
		case 1469: goto st1469;
		case 1470: goto st1470;
		case 1471: goto st1471;
		case 1472: goto st1472;
		case 1473: goto st1473;
		case 1474: goto st1474;
		case 1475: goto st1475;
		case 1476: goto st1476;
		case 1477: goto st1477;
		case 1478: goto st1478;
		case 1479: goto st1479;
		case 1480: goto st1480;
		case 1481: goto st1481;
		case 1482: goto st1482;
		case 1483: goto st1483;
		case 1484: goto st1484;
		case 1485: goto st1485;
		case 1486: goto st1486;
		case 1487: goto st1487;
		case 1488: goto st1488;
		case 1489: goto st1489;
		case 1490: goto st1490;
		case 1491: goto st1491;
		case 1492: goto st1492;
		case 1493: goto st1493;
		case 1494: goto st1494;
		case 1495: goto st1495;
		case 1496: goto st1496;
		case 1497: goto st1497;
		case 1498: goto st1498;
		case 1499: goto st1499;
		case 1500: goto st1500;
		case 1501: goto st1501;
		case 1502: goto st1502;
		case 1503: goto st1503;
		case 1504: goto st1504;
		case 1505: goto st1505;
		case 1506: goto st1506;
		case 1507: goto st1507;
		case 1508: goto st1508;
		case 1509: goto st1509;
		case 1510: goto st1510;
		case 1511: goto st1511;
		case 1512: goto st1512;
		case 1513: goto st1513;
		case 1514: goto st1514;
		case 1515: goto st1515;
		case 1516: goto st1516;
		case 1517: goto st1517;
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
		case 100: goto st2;
		case 108: goto st13;
		case 115: goto st25;
		case 116: goto st37;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1;
	goto st0;
st0:
 state.cs = 0;
	goto _out;
tr2275:
#line 309 "configparser.rl"
	{ init_design(des); }
	goto st2;
tr2281:
#line 396 "configparser.rl"
	{ init_levelskin_(lev); }
	goto st2;
tr2286:
#line 269 "configparser.rl"
	{ init_species(spe); }
	goto st2;
tr2291:
#line 357 "configparser.rl"
	{ init_terrain(ter); }
	goto st2;
st2:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof2;
case 2:
#line 1737 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st3;
	goto st0;
st3:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof3;
case 3:
	if ( (*( state.p)) == 115 )
		goto st4;
	goto st0;
st4:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof4;
case 4:
	if ( (*( state.p)) == 105 )
		goto st5;
	goto st0;
st5:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof5;
case 5:
	if ( (*( state.p)) == 103 )
		goto st6;
	goto st0;
st6:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof6;
case 6:
	if ( (*( state.p)) == 110 )
		goto st7;
	goto st0;
st7:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof7;
case 7:
	switch( (*( state.p)) ) {
		case 13: goto tr11;
		case 32: goto tr11;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr11;
	goto st0;
tr11:
#line 306 "configparser.rl"
	{ des = Design(); }
	goto st8;
st8:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof8;
case 8:
#line 1788 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st8;
		case 32: goto st8;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr13;
	} else if ( (*( state.p)) >= 9 )
		goto st8;
	goto st0;
tr13:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st9;
tr15:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st9;
st9:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof9;
case 9:
#line 1819 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr14;
		case 32: goto tr14;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr15;
	} else if ( (*( state.p)) >= 9 )
		goto tr14;
	goto st0;
tr14:
#line 299 "configparser.rl"
	{ des.level = toint(state.match); }
	goto st10;
st10:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof10;
case 10:
#line 1838 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st10;
		case 32: goto st10;
		case 95: goto tr17;
	}
	if ( (*( state.p)) < 48 ) {
		if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
			goto st10;
	} else if ( (*( state.p)) > 57 ) {
		if ( (*( state.p)) > 90 ) {
			if ( 97 <= (*( state.p)) && (*( state.p)) <= 122 )
				goto tr17;
		} else if ( (*( state.p)) >= 65 )
			goto tr17;
	} else
		goto tr17;
	goto st0;
tr17:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st11;
tr19:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st11;
st11:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof11;
case 11:
#line 1876 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr18;
		case 32: goto tr18;
		case 95: goto tr19;
		case 123: goto tr20;
	}
	if ( (*( state.p)) < 48 ) {
		if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
			goto tr18;
	} else if ( (*( state.p)) > 57 ) {
		if ( (*( state.p)) > 90 ) {
			if ( 97 <= (*( state.p)) && (*( state.p)) <= 122 )
				goto tr19;
		} else if ( (*( state.p)) >= 65 )
			goto tr19;
	} else
		goto tr19;
	goto st0;
tr18:
#line 302 "configparser.rl"
	{ des.tag = state.match; }
	goto st12;
st12:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof12;
case 12:
#line 1903 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st12;
		case 32: goto st12;
		case 123: goto tr22;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st12;
	goto st0;
tr20:
#line 302 "configparser.rl"
	{ des.tag = state.match; }
#line 308 "configparser.rl"
	{{ state.stack[ state.top++] = 1518; goto st395;}}
	goto st1518;
tr22:
#line 308 "configparser.rl"
	{{ state.stack[ state.top++] = 1518; goto st395;}}
	goto st1518;
st1518:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1518;
case 1518:
#line 1926 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr2274;
		case 32: goto tr2274;
		case 100: goto tr2275;
		case 108: goto tr2276;
		case 115: goto tr2277;
		case 116: goto tr2278;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2274;
	goto st0;
tr2274:
#line 309 "configparser.rl"
	{ init_design(des); }
	goto st1519;
tr2280:
#line 396 "configparser.rl"
	{ init_levelskin_(lev); }
	goto st1519;
tr2285:
#line 269 "configparser.rl"
	{ init_species(spe); }
	goto st1519;
tr2290:
#line 357 "configparser.rl"
	{ init_terrain(ter); }
	goto st1519;
st1519:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1519;
case 1519:
#line 1958 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st1519;
		case 32: goto st1519;
		case 100: goto st2;
		case 108: goto st13;
		case 115: goto st25;
		case 116: goto st37;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1519;
	goto st0;
tr2276:
#line 309 "configparser.rl"
	{ init_design(des); }
	goto st13;
tr2282:
#line 396 "configparser.rl"
	{ init_levelskin_(lev); }
	goto st13;
tr2287:
#line 269 "configparser.rl"
	{ init_species(spe); }
	goto st13;
tr2292:
#line 357 "configparser.rl"
	{ init_terrain(ter); }
	goto st13;
st13:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof13;
case 13:
#line 1990 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st14;
	goto st0;
st14:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof14;
case 14:
	if ( (*( state.p)) == 118 )
		goto st15;
	goto st0;
st15:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof15;
case 15:
	if ( (*( state.p)) == 101 )
		goto st16;
	goto st0;
st16:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof16;
case 16:
	if ( (*( state.p)) == 108 )
		goto st17;
	goto st0;
st17:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof17;
case 17:
	if ( (*( state.p)) == 115 )
		goto st18;
	goto st0;
st18:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof18;
case 18:
	if ( (*( state.p)) == 107 )
		goto st19;
	goto st0;
st19:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof19;
case 19:
	if ( (*( state.p)) == 105 )
		goto st20;
	goto st0;
st20:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof20;
case 20:
	if ( (*( state.p)) == 110 )
		goto st21;
	goto st0;
st21:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof21;
case 21:
	switch( (*( state.p)) ) {
		case 13: goto tr31;
		case 32: goto tr31;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr31;
	goto st0;
tr31:
#line 393 "configparser.rl"
	{ lev = Levelskin(); }
	goto st22;
st22:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof22;
case 22:
#line 2062 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st22;
		case 32: goto st22;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr33;
	} else if ( (*( state.p)) >= 9 )
		goto st22;
	goto st0;
tr33:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st23;
tr35:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st23;
st23:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof23;
case 23:
#line 2093 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr34;
		case 32: goto tr34;
		case 123: goto tr36;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr35;
	} else if ( (*( state.p)) >= 9 )
		goto tr34;
	goto st0;
tr34:
#line 389 "configparser.rl"
	{ lev.level = toint(state.match); }
	goto st24;
st24:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof24;
case 24:
#line 2113 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st24;
		case 32: goto st24;
		case 123: goto tr38;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st24;
	goto st0;
tr36:
#line 389 "configparser.rl"
	{ lev.level = toint(state.match); }
#line 395 "configparser.rl"
	{{ state.stack[ state.top++] = 1520; goto st795;}}
	goto st1520;
tr38:
#line 395 "configparser.rl"
	{{ state.stack[ state.top++] = 1520; goto st795;}}
	goto st1520;
st1520:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1520;
case 1520:
#line 2136 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr2280;
		case 32: goto tr2280;
		case 100: goto tr2281;
		case 108: goto tr2282;
		case 115: goto tr2283;
		case 116: goto tr2284;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2280;
	goto st0;
tr2277:
#line 309 "configparser.rl"
	{ init_design(des); }
	goto st25;
tr2283:
#line 396 "configparser.rl"
	{ init_levelskin_(lev); }
	goto st25;
tr2288:
#line 269 "configparser.rl"
	{ init_species(spe); }
	goto st25;
tr2293:
#line 357 "configparser.rl"
	{ init_terrain(ter); }
	goto st25;
st25:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof25;
case 25:
#line 2168 "configparser.h"
	if ( (*( state.p)) == 112 )
		goto st26;
	goto st0;
st26:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof26;
case 26:
	if ( (*( state.p)) == 101 )
		goto st27;
	goto st0;
st27:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof27;
case 27:
	if ( (*( state.p)) == 99 )
		goto st28;
	goto st0;
st28:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof28;
case 28:
	if ( (*( state.p)) == 105 )
		goto st29;
	goto st0;
st29:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof29;
case 29:
	if ( (*( state.p)) == 101 )
		goto st30;
	goto st0;
st30:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof30;
case 30:
	if ( (*( state.p)) == 115 )
		goto st31;
	goto st0;
st31:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof31;
case 31:
	switch( (*( state.p)) ) {
		case 13: goto tr45;
		case 32: goto tr45;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr45;
	goto st0;
tr45:
#line 266 "configparser.rl"
	{ spe = Species(); }
	goto st32;
st32:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof32;
case 32:
#line 2226 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st32;
		case 32: goto st32;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr47;
	} else if ( (*( state.p)) >= 9 )
		goto st32;
	goto st0;
tr47:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st33;
tr49:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st33;
st33:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof33;
case 33:
#line 2257 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr48;
		case 32: goto tr48;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr49;
	} else if ( (*( state.p)) >= 9 )
		goto tr48;
	goto st0;
tr48:
#line 259 "configparser.rl"
	{ spe.level = toint(state.match); }
	goto st34;
st34:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof34;
case 34:
#line 2276 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st34;
		case 32: goto st34;
		case 95: goto tr51;
	}
	if ( (*( state.p)) < 48 ) {
		if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
			goto st34;
	} else if ( (*( state.p)) > 57 ) {
		if ( (*( state.p)) > 90 ) {
			if ( 97 <= (*( state.p)) && (*( state.p)) <= 122 )
				goto tr51;
		} else if ( (*( state.p)) >= 65 )
			goto tr51;
	} else
		goto tr51;
	goto st0;
tr51:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st35;
tr53:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st35;
st35:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof35;
case 35:
#line 2314 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr52;
		case 32: goto tr52;
		case 95: goto tr53;
		case 123: goto tr54;
	}
	if ( (*( state.p)) < 48 ) {
		if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
			goto tr52;
	} else if ( (*( state.p)) > 57 ) {
		if ( (*( state.p)) > 90 ) {
			if ( 97 <= (*( state.p)) && (*( state.p)) <= 122 )
				goto tr53;
		} else if ( (*( state.p)) >= 65 )
			goto tr53;
	} else
		goto tr53;
	goto st0;
tr52:
#line 262 "configparser.rl"
	{ spe.tag = state.match; }
	goto st36;
st36:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof36;
case 36:
#line 2341 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st36;
		case 32: goto st36;
		case 123: goto tr56;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st36;
	goto st0;
tr54:
#line 262 "configparser.rl"
	{ spe.tag = state.match; }
#line 268 "configparser.rl"
	{{ state.stack[ state.top++] = 1521; goto st48;}}
	goto st1521;
tr56:
#line 268 "configparser.rl"
	{{ state.stack[ state.top++] = 1521; goto st48;}}
	goto st1521;
st1521:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1521;
case 1521:
#line 2364 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr2285;
		case 32: goto tr2285;
		case 100: goto tr2286;
		case 108: goto tr2287;
		case 115: goto tr2288;
		case 116: goto tr2289;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2285;
	goto st0;
tr2278:
#line 309 "configparser.rl"
	{ init_design(des); }
	goto st37;
tr2284:
#line 396 "configparser.rl"
	{ init_levelskin_(lev); }
	goto st37;
tr2289:
#line 269 "configparser.rl"
	{ init_species(spe); }
	goto st37;
tr2294:
#line 357 "configparser.rl"
	{ init_terrain(ter); }
	goto st37;
st37:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof37;
case 37:
#line 2396 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st38;
	goto st0;
st38:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof38;
case 38:
	if ( (*( state.p)) == 114 )
		goto st39;
	goto st0;
st39:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof39;
case 39:
	if ( (*( state.p)) == 114 )
		goto st40;
	goto st0;
st40:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof40;
case 40:
	if ( (*( state.p)) == 97 )
		goto st41;
	goto st0;
st41:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof41;
case 41:
	if ( (*( state.p)) == 105 )
		goto st42;
	goto st0;
st42:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof42;
case 42:
	if ( (*( state.p)) == 110 )
		goto st43;
	goto st0;
st43:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof43;
case 43:
	switch( (*( state.p)) ) {
		case 13: goto tr63;
		case 32: goto tr63;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr63;
	goto st0;
tr63:
#line 354 "configparser.rl"
	{ ter = Terrain(); }
	goto st44;
st44:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof44;
case 44:
#line 2454 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st44;
		case 32: goto st44;
		case 95: goto tr65;
	}
	if ( (*( state.p)) < 48 ) {
		if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
			goto st44;
	} else if ( (*( state.p)) > 57 ) {
		if ( (*( state.p)) > 90 ) {
			if ( 97 <= (*( state.p)) && (*( state.p)) <= 122 )
				goto tr65;
		} else if ( (*( state.p)) >= 65 )
			goto tr65;
	} else
		goto tr65;
	goto st0;
tr65:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st45;
tr67:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st45;
st45:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof45;
case 45:
#line 2492 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr66;
		case 32: goto tr66;
		case 95: goto tr67;
		case 123: goto tr68;
	}
	if ( (*( state.p)) < 48 ) {
		if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
			goto tr66;
	} else if ( (*( state.p)) > 57 ) {
		if ( (*( state.p)) > 90 ) {
			if ( 97 <= (*( state.p)) && (*( state.p)) <= 122 )
				goto tr67;
		} else if ( (*( state.p)) >= 65 )
			goto tr67;
	} else
		goto tr67;
	goto st0;
tr66:
#line 350 "configparser.rl"
	{ ter.tag = state.match; }
	goto st46;
st46:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof46;
case 46:
#line 2519 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st46;
		case 32: goto st46;
		case 123: goto tr70;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st46;
	goto st0;
tr68:
#line 350 "configparser.rl"
	{ ter.tag = state.match; }
#line 356 "configparser.rl"
	{{ state.stack[ state.top++] = 1522; goto st600;}}
	goto st1522;
tr70:
#line 356 "configparser.rl"
	{{ state.stack[ state.top++] = 1522; goto st600;}}
	goto st1522;
st1522:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1522;
case 1522:
#line 2542 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr2290;
		case 32: goto tr2290;
		case 100: goto tr2291;
		case 108: goto tr2292;
		case 115: goto tr2293;
		case 116: goto tr2294;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2290;
	goto st0;
st47:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof47;
case 47:
	switch( (*( state.p)) ) {
		case 34: goto tr71;
		case 92: goto tr72;
		case 110: goto tr73;
	}
	goto st0;
tr71:
#line 138 "configparser.rl"
	{ state.match += '"';  { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st1523;
tr72:
#line 140 "configparser.rl"
	{ state.match += '\\'; { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st1523;
tr73:
#line 139 "configparser.rl"
	{ state.match += '\n'; { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st1523;
st1523:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1523;
case 1523:
#line 2580 "configparser.h"
	goto st0;
st48:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof48;
case 48:
	switch( (*( state.p)) ) {
		case 13: goto st48;
		case 32: goto st48;
		case 97: goto st49;
		case 99: goto st67;
		case 100: goto st131;
		case 104: goto st173;
		case 105: goto st208;
		case 109: goto st226;
		case 110: goto st250;
		case 114: goto st257;
		case 115: goto st264;
		case 125: goto tr84;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st48;
	goto st0;
st49:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof49;
case 49:
	switch( (*( state.p)) ) {
		case 105: goto st50;
		case 116: goto st366;
	}
	goto st0;
st50:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof50;
case 50:
	switch( (*( state.p)) ) {
		case 13: goto st51;
		case 32: goto st51;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st51;
	goto st0;
st51:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof51;
case 51:
	switch( (*( state.p)) ) {
		case 13: goto st51;
		case 32: goto st51;
		case 105: goto st52;
		case 110: goto st338;
		case 114: goto st342;
		case 115: goto st348;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st51;
	goto st0;
st52:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof52;
case 52:
	if ( (*( state.p)) == 110 )
		goto st53;
	goto st0;
st53:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof53;
case 53:
	if ( (*( state.p)) == 114 )
		goto st54;
	goto st0;
st54:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof54;
case 54:
	if ( (*( state.p)) == 97 )
		goto st55;
	goto st0;
st55:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof55;
case 55:
	if ( (*( state.p)) == 110 )
		goto st56;
	goto st0;
st56:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof56;
case 56:
	if ( (*( state.p)) == 103 )
		goto st57;
	goto st0;
st57:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof57;
case 57:
	if ( (*( state.p)) == 101 )
		goto st58;
	goto st0;
st58:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof58;
case 58:
	if ( (*( state.p)) == 95 )
		goto st59;
	goto st0;
st59:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof59;
case 59:
	if ( (*( state.p)) == 114 )
		goto st60;
	goto st0;
st60:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof60;
case 60:
	if ( (*( state.p)) == 97 )
		goto st61;
	goto st0;
st61:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof61;
case 61:
	if ( (*( state.p)) == 110 )
		goto st62;
	goto st0;
st62:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof62;
case 62:
	if ( (*( state.p)) == 100 )
		goto st63;
	goto st0;
st63:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof63;
case 63:
	if ( (*( state.p)) == 111 )
		goto st64;
	goto st0;
st64:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof64;
case 64:
	if ( (*( state.p)) == 109 )
		goto st65;
	goto st0;
st65:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof65;
case 65:
	switch( (*( state.p)) ) {
		case 13: goto tr105;
		case 32: goto tr105;
		case 59: goto tr106;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr105;
	goto st0;
tr84:
#line 253 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st66;
tr105:
#line 194 "configparser.rl"
	{ spe.ai = Species::ai_t::inrange_random; }
	goto st66;
tr146:
#line 238 "configparser.rl"
	{ spe.cast_cloud.back().name = state.match; }
	goto st66;
tr166:
#line 220 "configparser.rl"
	{ spe.clumpsize.deviation = toreal(state.match); }
	goto st66;
tr190:
#line 225 "configparser.rl"
	{ spe.companion.back().chance = toreal(state.match); }
	goto st66;
tr198:
#line 207 "configparser.rl"
	{ spe.count = toint(state.match); }
	goto st66;
tr224:
#line 177 "configparser.rl"
	{ dmgval.val = toreal(state.match); }
#line 216 "configparser.rl"
	{ spe.defenses.add(dmgval); }
	goto st66;
tr251:
#line 230 "configparser.rl"
	{ spe.drop.back().chance = toreal(state.match); }
	goto st66;
tr271:
#line 187 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st66;
tr277:
#line 185 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st66;
tr287:
#line 188 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st66;
tr293:
#line 184 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st66;
tr297:
#line 186 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st66;
tr311:
#line 198 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st66;
tr318:
#line 199 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st66;
tr330:
#line 202 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st66;
tr337:
#line 205 "configparser.rl"
	{ spe.move = Species::move_t::corner; }
	goto st66;
tr343:
#line 203 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st66;
tr349:
#line 204 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st66;
tr359:
#line 208 "configparser.rl"
	{ spe.name = state.match; }
	goto st66;
tr367:
#line 214 "configparser.rl"
	{ spe.range = toint(state.match); }
	goto st66;
tr411:
#line 209 "configparser.rl"
	{ spe.skin = skin; }
	goto st66;
tr414:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 209 "configparser.rl"
	{ spe.skin = skin; }
	goto st66;
tr419:
#line 158 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 209 "configparser.rl"
	{ spe.skin = skin; }
	goto st66;
tr425:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 209 "configparser.rl"
	{ spe.skin = skin; }
	goto st66;
tr433:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 209 "configparser.rl"
	{ spe.skin = skin; }
	goto st66;
tr437:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 209 "configparser.rl"
	{ spe.skin = skin; }
	goto st66;
tr443:
#line 159 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 209 "configparser.rl"
	{ spe.skin = skin; }
	goto st66;
tr450:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 209 "configparser.rl"
	{ spe.skin = skin; }
	goto st66;
tr484:
#line 244 "configparser.rl"
	{ spe.summon.back().turns = toint(state.match); }
	goto st66;
tr491:
#line 191 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st66;
tr498:
#line 193 "configparser.rl"
	{ spe.ai = Species::ai_t::random; }
	goto st66;
tr512:
#line 195 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_nosleep; }
	goto st66;
tr519:
#line 192 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st66;
tr541:
#line 177 "configparser.rl"
	{ dmgval.val = toreal(state.match); }
#line 215 "configparser.rl"
	{ spe.attacks.add(dmgval); }
	goto st66;
st66:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof66;
case 66:
#line 2903 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st66;
		case 32: goto st66;
		case 59: goto st1524;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st66;
	goto st0;
tr106:
#line 194 "configparser.rl"
	{ spe.ai = Species::ai_t::inrange_random; }
	goto st1524;
tr147:
#line 238 "configparser.rl"
	{ spe.cast_cloud.back().name = state.match; }
	goto st1524;
tr168:
#line 220 "configparser.rl"
	{ spe.clumpsize.deviation = toreal(state.match); }
	goto st1524;
tr192:
#line 225 "configparser.rl"
	{ spe.companion.back().chance = toreal(state.match); }
	goto st1524;
tr200:
#line 207 "configparser.rl"
	{ spe.count = toint(state.match); }
	goto st1524;
tr226:
#line 177 "configparser.rl"
	{ dmgval.val = toreal(state.match); }
#line 216 "configparser.rl"
	{ spe.defenses.add(dmgval); }
	goto st1524;
tr253:
#line 230 "configparser.rl"
	{ spe.drop.back().chance = toreal(state.match); }
	goto st1524;
tr272:
#line 187 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st1524;
tr278:
#line 185 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st1524;
tr288:
#line 188 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st1524;
tr294:
#line 184 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st1524;
tr298:
#line 186 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st1524;
tr312:
#line 198 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st1524;
tr319:
#line 199 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st1524;
tr331:
#line 202 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st1524;
tr338:
#line 205 "configparser.rl"
	{ spe.move = Species::move_t::corner; }
	goto st1524;
tr344:
#line 203 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st1524;
tr350:
#line 204 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st1524;
tr360:
#line 208 "configparser.rl"
	{ spe.name = state.match; }
	goto st1524;
tr369:
#line 214 "configparser.rl"
	{ spe.range = toint(state.match); }
	goto st1524;
tr412:
#line 209 "configparser.rl"
	{ spe.skin = skin; }
	goto st1524;
tr415:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 209 "configparser.rl"
	{ spe.skin = skin; }
	goto st1524;
tr420:
#line 158 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 209 "configparser.rl"
	{ spe.skin = skin; }
	goto st1524;
tr426:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 209 "configparser.rl"
	{ spe.skin = skin; }
	goto st1524;
tr434:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 209 "configparser.rl"
	{ spe.skin = skin; }
	goto st1524;
tr438:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 209 "configparser.rl"
	{ spe.skin = skin; }
	goto st1524;
tr444:
#line 159 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 209 "configparser.rl"
	{ spe.skin = skin; }
	goto st1524;
tr451:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 209 "configparser.rl"
	{ spe.skin = skin; }
	goto st1524;
tr486:
#line 244 "configparser.rl"
	{ spe.summon.back().turns = toint(state.match); }
	goto st1524;
tr492:
#line 191 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st1524;
tr499:
#line 193 "configparser.rl"
	{ spe.ai = Species::ai_t::random; }
	goto st1524;
tr513:
#line 195 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_nosleep; }
	goto st1524;
tr520:
#line 192 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st1524;
tr543:
#line 177 "configparser.rl"
	{ dmgval.val = toreal(state.match); }
#line 215 "configparser.rl"
	{ spe.attacks.add(dmgval); }
	goto st1524;
st1524:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1524;
case 1524:
#line 3070 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st48;
		case 32: goto st48;
		case 97: goto st49;
		case 99: goto st67;
		case 100: goto st131;
		case 104: goto st173;
		case 105: goto st208;
		case 109: goto st226;
		case 110: goto st250;
		case 114: goto st257;
		case 115: goto st264;
		case 125: goto tr84;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st48;
	goto st0;
st67:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof67;
case 67:
	switch( (*( state.p)) ) {
		case 97: goto st68;
		case 108: goto st92;
		case 111: goto st110;
	}
	goto st0;
st68:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof68;
case 68:
	if ( (*( state.p)) == 115 )
		goto st69;
	goto st0;
st69:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof69;
case 69:
	if ( (*( state.p)) == 116 )
		goto st70;
	goto st0;
st70:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof70;
case 70:
	if ( (*( state.p)) == 95 )
		goto st71;
	goto st0;
st71:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof71;
case 71:
	if ( (*( state.p)) == 99 )
		goto st72;
	goto st0;
st72:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof72;
case 72:
	if ( (*( state.p)) == 108 )
		goto st73;
	goto st0;
st73:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof73;
case 73:
	if ( (*( state.p)) == 111 )
		goto st74;
	goto st0;
st74:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof74;
case 74:
	if ( (*( state.p)) == 117 )
		goto st75;
	goto st0;
st75:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof75;
case 75:
	if ( (*( state.p)) == 100 )
		goto st76;
	goto st0;
st76:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof76;
case 76:
	switch( (*( state.p)) ) {
		case 13: goto tr120;
		case 32: goto tr120;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr120;
	goto st0;
tr120:
#line 233 "configparser.rl"
	{ spe.cast_cloud.push_back(Species::cloud_t()); }
	goto st77;
st77:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof77;
case 77:
#line 3173 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st77;
		case 32: goto st77;
		case 45: goto tr122;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr123;
	} else if ( (*( state.p)) >= 9 )
		goto st77;
	goto st0;
tr122:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st78;
st78:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof78;
case 78:
#line 3199 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr124;
	goto st0;
tr123:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st79;
tr124:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st79;
st79:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof79;
case 79:
#line 3223 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr125;
		case 32: goto tr125;
		case 46: goto tr126;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr124;
	} else if ( (*( state.p)) >= 9 )
		goto tr125;
	goto st0;
tr125:
#line 234 "configparser.rl"
	{ spe.cast_cloud.back().chance = toreal(state.match); }
	goto st80;
st80:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof80;
case 80:
#line 3243 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st80;
		case 32: goto st80;
		case 34: goto tr128;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st80;
	goto st0;
tr129:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st81;
tr128:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
	goto st81;
tr131:
#line 144 "configparser.rl"
	{{ state.stack[ state.top++] = 81; goto st47;}}
	goto st81;
st81:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof81;
case 81:
#line 3272 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st82;
		case 92: goto tr131;
	}
	goto tr129;
st82:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof82;
case 82:
	switch( (*( state.p)) ) {
		case 13: goto tr132;
		case 32: goto tr132;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr132;
	goto st0;
tr132:
#line 235 "configparser.rl"
	{ spe.cast_cloud.back().terraintag = state.match; }
	goto st83;
st83:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof83;
case 83:
#line 3297 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st83;
		case 32: goto st83;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr134;
	} else if ( (*( state.p)) >= 9 )
		goto st83;
	goto st0;
tr134:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st84;
tr136:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st84;
st84:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof84;
case 84:
#line 3328 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr135;
		case 32: goto tr135;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr136;
	} else if ( (*( state.p)) >= 9 )
		goto tr135;
	goto st0;
tr135:
#line 236 "configparser.rl"
	{ spe.cast_cloud.back().radius = toint(state.match); }
	goto st85;
st85:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof85;
case 85:
#line 3347 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st85;
		case 32: goto st85;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr138;
	} else if ( (*( state.p)) >= 9 )
		goto st85;
	goto st0;
tr138:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st86;
tr140:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st86;
st86:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof86;
case 86:
#line 3378 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr139;
		case 32: goto tr139;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr140;
	} else if ( (*( state.p)) >= 9 )
		goto tr139;
	goto st0;
tr139:
#line 237 "configparser.rl"
	{ spe.cast_cloud.back().turns = toint(state.match); }
	goto st87;
st87:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof87;
case 87:
#line 3397 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st87;
		case 32: goto st87;
		case 34: goto tr142;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st87;
	goto st0;
tr143:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st88;
tr142:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
	goto st88;
tr145:
#line 144 "configparser.rl"
	{{ state.stack[ state.top++] = 88; goto st47;}}
	goto st88;
st88:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof88;
case 88:
#line 3426 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st89;
		case 92: goto tr145;
	}
	goto tr143;
st89:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof89;
case 89:
	switch( (*( state.p)) ) {
		case 13: goto tr146;
		case 32: goto tr146;
		case 59: goto tr147;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr146;
	goto st0;
tr126:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st90;
st90:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof90;
case 90:
#line 3454 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr148;
	goto st0;
tr148:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st91;
st91:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof91;
case 91:
#line 3468 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr125;
		case 32: goto tr125;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr148;
	} else if ( (*( state.p)) >= 9 )
		goto tr125;
	goto st0;
st92:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof92;
case 92:
	if ( (*( state.p)) == 117 )
		goto st93;
	goto st0;
st93:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof93;
case 93:
	if ( (*( state.p)) == 109 )
		goto st94;
	goto st0;
st94:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof94;
case 94:
	if ( (*( state.p)) == 112 )
		goto st95;
	goto st0;
st95:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof95;
case 95:
	if ( (*( state.p)) == 115 )
		goto st96;
	goto st0;
st96:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof96;
case 96:
	if ( (*( state.p)) == 105 )
		goto st97;
	goto st0;
st97:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof97;
case 97:
	if ( (*( state.p)) == 122 )
		goto st98;
	goto st0;
st98:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof98;
case 98:
	if ( (*( state.p)) == 101 )
		goto st99;
	goto st0;
st99:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof99;
case 99:
	switch( (*( state.p)) ) {
		case 13: goto st100;
		case 32: goto st100;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st100;
	goto st0;
st100:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof100;
case 100:
	switch( (*( state.p)) ) {
		case 13: goto st100;
		case 32: goto st100;
		case 45: goto tr157;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr158;
	} else if ( (*( state.p)) >= 9 )
		goto st100;
	goto st0;
tr157:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st101;
st101:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof101;
case 101:
#line 3568 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr159;
	goto st0;
tr158:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st102;
tr159:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st102;
st102:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof102;
case 102:
#line 3592 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr160;
		case 32: goto tr160;
		case 46: goto tr161;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr159;
	} else if ( (*( state.p)) >= 9 )
		goto tr160;
	goto st0;
tr160:
#line 219 "configparser.rl"
	{ spe.clumpsize.mean = toreal(state.match); }
	goto st103;
st103:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof103;
case 103:
#line 3612 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st103;
		case 32: goto st103;
		case 45: goto tr163;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr164;
	} else if ( (*( state.p)) >= 9 )
		goto st103;
	goto st0;
tr163:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st104;
st104:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof104;
case 104:
#line 3638 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr165;
	goto st0;
tr164:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st105;
tr165:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st105;
st105:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof105;
case 105:
#line 3662 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr166;
		case 32: goto tr166;
		case 46: goto tr167;
		case 59: goto tr168;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr165;
	} else if ( (*( state.p)) >= 9 )
		goto tr166;
	goto st0;
tr167:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st106;
st106:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof106;
case 106:
#line 3685 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr169;
	goto st0;
tr169:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st107;
st107:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof107;
case 107:
#line 3699 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr166;
		case 32: goto tr166;
		case 59: goto tr168;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr169;
	} else if ( (*( state.p)) >= 9 )
		goto tr166;
	goto st0;
tr161:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st108;
st108:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof108;
case 108:
#line 3721 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr170;
	goto st0;
tr170:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st109;
st109:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof109;
case 109:
#line 3735 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr160;
		case 32: goto tr160;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr170;
	} else if ( (*( state.p)) >= 9 )
		goto tr160;
	goto st0;
st110:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof110;
case 110:
	switch( (*( state.p)) ) {
		case 109: goto st111;
		case 117: goto st126;
	}
	goto st0;
st111:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof111;
case 111:
	if ( (*( state.p)) == 112 )
		goto st112;
	goto st0;
st112:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof112;
case 112:
	if ( (*( state.p)) == 97 )
		goto st113;
	goto st0;
st113:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof113;
case 113:
	if ( (*( state.p)) == 110 )
		goto st114;
	goto st0;
st114:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof114;
case 114:
	if ( (*( state.p)) == 105 )
		goto st115;
	goto st0;
st115:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof115;
case 115:
	if ( (*( state.p)) == 111 )
		goto st116;
	goto st0;
st116:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof116;
case 116:
	if ( (*( state.p)) == 110 )
		goto st117;
	goto st0;
st117:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof117;
case 117:
	switch( (*( state.p)) ) {
		case 13: goto tr179;
		case 32: goto tr179;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr179;
	goto st0;
tr179:
#line 223 "configparser.rl"
	{ spe.companion.push_back(Species::companion_t()); }
	goto st118;
st118:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof118;
case 118:
#line 3816 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st118;
		case 32: goto st118;
		case 34: goto tr181;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st118;
	goto st0;
tr182:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st119;
tr181:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
	goto st119;
tr184:
#line 144 "configparser.rl"
	{{ state.stack[ state.top++] = 119; goto st47;}}
	goto st119;
st119:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof119;
case 119:
#line 3845 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st120;
		case 92: goto tr184;
	}
	goto tr182;
st120:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof120;
case 120:
	switch( (*( state.p)) ) {
		case 13: goto tr185;
		case 32: goto tr185;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr185;
	goto st0;
tr185:
#line 224 "configparser.rl"
	{ spe.companion.back().tag = state.match; }
	goto st121;
st121:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof121;
case 121:
#line 3870 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st121;
		case 32: goto st121;
		case 45: goto tr187;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr188;
	} else if ( (*( state.p)) >= 9 )
		goto st121;
	goto st0;
tr187:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st122;
st122:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof122;
case 122:
#line 3896 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr189;
	goto st0;
tr188:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st123;
tr189:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st123;
st123:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof123;
case 123:
#line 3920 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr190;
		case 32: goto tr190;
		case 46: goto tr191;
		case 59: goto tr192;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr189;
	} else if ( (*( state.p)) >= 9 )
		goto tr190;
	goto st0;
tr191:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st124;
st124:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof124;
case 124:
#line 3943 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr193;
	goto st0;
tr193:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st125;
st125:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof125;
case 125:
#line 3957 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr190;
		case 32: goto tr190;
		case 59: goto tr192;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr193;
	} else if ( (*( state.p)) >= 9 )
		goto tr190;
	goto st0;
st126:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof126;
case 126:
	if ( (*( state.p)) == 110 )
		goto st127;
	goto st0;
st127:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof127;
case 127:
	if ( (*( state.p)) == 116 )
		goto st128;
	goto st0;
st128:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof128;
case 128:
	switch( (*( state.p)) ) {
		case 13: goto st129;
		case 32: goto st129;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st129;
	goto st0;
st129:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof129;
case 129:
	switch( (*( state.p)) ) {
		case 13: goto st129;
		case 32: goto st129;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr197;
	} else if ( (*( state.p)) >= 9 )
		goto st129;
	goto st0;
tr197:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st130;
tr199:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st130;
st130:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof130;
case 130:
#line 4028 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr198;
		case 32: goto tr198;
		case 59: goto tr200;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr199;
	} else if ( (*( state.p)) >= 9 )
		goto tr198;
	goto st0;
st131:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof131;
case 131:
	switch( (*( state.p)) ) {
		case 101: goto st132;
		case 114: goto st162;
	}
	goto st0;
st132:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof132;
case 132:
	if ( (*( state.p)) == 102 )
		goto st133;
	goto st0;
st133:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof133;
case 133:
	if ( (*( state.p)) == 101 )
		goto st134;
	goto st0;
st134:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof134;
case 134:
	if ( (*( state.p)) == 110 )
		goto st135;
	goto st0;
st135:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof135;
case 135:
	if ( (*( state.p)) == 115 )
		goto st136;
	goto st0;
st136:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof136;
case 136:
	if ( (*( state.p)) == 101 )
		goto st137;
	goto st0;
st137:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof137;
case 137:
	switch( (*( state.p)) ) {
		case 13: goto st138;
		case 32: goto st138;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st138;
	goto st0;
st138:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof138;
case 138:
	switch( (*( state.p)) ) {
		case 13: goto st138;
		case 32: goto st138;
		case 112: goto st139;
		case 115: goto st157;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st138;
	goto st0;
st139:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof139;
case 139:
	switch( (*( state.p)) ) {
		case 104: goto st140;
		case 111: goto st152;
	}
	goto st0;
st140:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof140;
case 140:
	if ( (*( state.p)) == 121 )
		goto st141;
	goto st0;
st141:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof141;
case 141:
	if ( (*( state.p)) == 115 )
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
	if ( (*( state.p)) == 99 )
		goto st144;
	goto st0;
st144:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof144;
case 144:
	if ( (*( state.p)) == 97 )
		goto st145;
	goto st0;
st145:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof145;
case 145:
	if ( (*( state.p)) == 108 )
		goto st146;
	goto st0;
st146:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof146;
case 146:
	switch( (*( state.p)) ) {
		case 13: goto tr219;
		case 32: goto tr219;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr219;
	goto st0;
tr219:
#line 171 "configparser.rl"
	{ dmgval.type = damage::type_t::physical; }
	goto st147;
tr232:
#line 173 "configparser.rl"
	{ dmgval.type = damage::type_t::poison; }
	goto st147;
tr237:
#line 172 "configparser.rl"
	{ dmgval.type = damage::type_t::sleep; }
	goto st147;
st147:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof147;
case 147:
#line 4186 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st147;
		case 32: goto st147;
		case 45: goto tr221;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr222;
	} else if ( (*( state.p)) >= 9 )
		goto st147;
	goto st0;
tr221:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st148;
st148:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof148;
case 148:
#line 4212 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr223;
	goto st0;
tr222:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st149;
tr223:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st149;
st149:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof149;
case 149:
#line 4236 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr224;
		case 32: goto tr224;
		case 46: goto tr225;
		case 59: goto tr226;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr223;
	} else if ( (*( state.p)) >= 9 )
		goto tr224;
	goto st0;
tr225:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st150;
st150:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof150;
case 150:
#line 4259 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr227;
	goto st0;
tr227:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st151;
st151:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof151;
case 151:
#line 4273 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr224;
		case 32: goto tr224;
		case 59: goto tr226;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr227;
	} else if ( (*( state.p)) >= 9 )
		goto tr224;
	goto st0;
st152:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof152;
case 152:
	if ( (*( state.p)) == 105 )
		goto st153;
	goto st0;
st153:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof153;
case 153:
	if ( (*( state.p)) == 115 )
		goto st154;
	goto st0;
st154:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof154;
case 154:
	if ( (*( state.p)) == 111 )
		goto st155;
	goto st0;
st155:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof155;
case 155:
	if ( (*( state.p)) == 110 )
		goto st156;
	goto st0;
st156:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof156;
case 156:
	switch( (*( state.p)) ) {
		case 13: goto tr232;
		case 32: goto tr232;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr232;
	goto st0;
st157:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof157;
case 157:
	if ( (*( state.p)) == 108 )
		goto st158;
	goto st0;
st158:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof158;
case 158:
	if ( (*( state.p)) == 101 )
		goto st159;
	goto st0;
st159:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof159;
case 159:
	if ( (*( state.p)) == 101 )
		goto st160;
	goto st0;
st160:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof160;
case 160:
	if ( (*( state.p)) == 112 )
		goto st161;
	goto st0;
st161:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof161;
case 161:
	switch( (*( state.p)) ) {
		case 13: goto tr237;
		case 32: goto tr237;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr237;
	goto st0;
st162:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof162;
case 162:
	if ( (*( state.p)) == 111 )
		goto st163;
	goto st0;
st163:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof163;
case 163:
	if ( (*( state.p)) == 112 )
		goto st164;
	goto st0;
st164:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof164;
case 164:
	switch( (*( state.p)) ) {
		case 13: goto tr240;
		case 32: goto tr240;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr240;
	goto st0;
tr240:
#line 228 "configparser.rl"
	{ spe.drop.push_back(Species::drop_t()); }
	goto st165;
st165:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof165;
case 165:
#line 4396 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st165;
		case 32: goto st165;
		case 34: goto tr242;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st165;
	goto st0;
tr243:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st166;
tr242:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
	goto st166;
tr245:
#line 144 "configparser.rl"
	{{ state.stack[ state.top++] = 166; goto st47;}}
	goto st166;
st166:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof166;
case 166:
#line 4425 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st167;
		case 92: goto tr245;
	}
	goto tr243;
st167:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof167;
case 167:
	switch( (*( state.p)) ) {
		case 13: goto tr246;
		case 32: goto tr246;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr246;
	goto st0;
tr246:
#line 229 "configparser.rl"
	{ spe.drop.back().tag = state.match; }
	goto st168;
st168:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof168;
case 168:
#line 4450 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st168;
		case 32: goto st168;
		case 45: goto tr248;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr249;
	} else if ( (*( state.p)) >= 9 )
		goto st168;
	goto st0;
tr248:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st169;
st169:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof169;
case 169:
#line 4476 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr250;
	goto st0;
tr249:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st170;
tr250:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st170;
st170:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof170;
case 170:
#line 4500 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr251;
		case 32: goto tr251;
		case 46: goto tr252;
		case 59: goto tr253;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr250;
	} else if ( (*( state.p)) >= 9 )
		goto tr251;
	goto st0;
tr252:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st171;
st171:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof171;
case 171:
#line 4523 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr254;
	goto st0;
tr254:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st172;
st172:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof172;
case 172:
#line 4537 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr251;
		case 32: goto tr251;
		case 59: goto tr253;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr254;
	} else if ( (*( state.p)) >= 9 )
		goto tr251;
	goto st0;
st173:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof173;
case 173:
	if ( (*( state.p)) == 97 )
		goto st174;
	goto st0;
st174:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof174;
case 174:
	if ( (*( state.p)) == 98 )
		goto st175;
	goto st0;
st175:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof175;
case 175:
	if ( (*( state.p)) == 105 )
		goto st176;
	goto st0;
st176:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof176;
case 176:
	if ( (*( state.p)) == 116 )
		goto st177;
	goto st0;
st177:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof177;
case 177:
	if ( (*( state.p)) == 97 )
		goto st178;
	goto st0;
st178:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof178;
case 178:
	if ( (*( state.p)) == 116 )
		goto st179;
	goto st0;
st179:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof179;
case 179:
	switch( (*( state.p)) ) {
		case 13: goto st180;
		case 32: goto st180;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st180;
	goto st0;
st180:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof180;
case 180:
	switch( (*( state.p)) ) {
		case 13: goto st180;
		case 32: goto st180;
		case 99: goto st181;
		case 102: goto st187;
		case 115: goto st192;
		case 119: goto st201;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st180;
	goto st0;
st181:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof181;
case 181:
	if ( (*( state.p)) == 111 )
		goto st182;
	goto st0;
st182:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof182;
case 182:
	if ( (*( state.p)) == 114 )
		goto st183;
	goto st0;
st183:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof183;
case 183:
	if ( (*( state.p)) == 110 )
		goto st184;
	goto st0;
st184:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof184;
case 184:
	if ( (*( state.p)) == 101 )
		goto st185;
	goto st0;
st185:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof185;
case 185:
	if ( (*( state.p)) == 114 )
		goto st186;
	goto st0;
st186:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof186;
case 186:
	switch( (*( state.p)) ) {
		case 13: goto tr271;
		case 32: goto tr271;
		case 59: goto tr272;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr271;
	goto st0;
st187:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof187;
case 187:
	if ( (*( state.p)) == 108 )
		goto st188;
	goto st0;
st188:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof188;
case 188:
	if ( (*( state.p)) == 111 )
		goto st189;
	goto st0;
st189:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof189;
case 189:
	if ( (*( state.p)) == 111 )
		goto st190;
	goto st0;
st190:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof190;
case 190:
	if ( (*( state.p)) == 114 )
		goto st191;
	goto st0;
st191:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof191;
case 191:
	switch( (*( state.p)) ) {
		case 13: goto tr277;
		case 32: goto tr277;
		case 59: goto tr278;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr277;
	goto st0;
st192:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof192;
case 192:
	if ( (*( state.p)) == 104 )
		goto st193;
	goto st0;
st193:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof193;
case 193:
	if ( (*( state.p)) == 111 )
		goto st194;
	goto st0;
st194:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof194;
case 194:
	if ( (*( state.p)) == 114 )
		goto st195;
	goto st0;
st195:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof195;
case 195:
	if ( (*( state.p)) == 101 )
		goto st196;
	goto st0;
st196:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof196;
case 196:
	if ( (*( state.p)) == 108 )
		goto st197;
	goto st0;
st197:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof197;
case 197:
	if ( (*( state.p)) == 105 )
		goto st198;
	goto st0;
st198:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof198;
case 198:
	if ( (*( state.p)) == 110 )
		goto st199;
	goto st0;
st199:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof199;
case 199:
	if ( (*( state.p)) == 101 )
		goto st200;
	goto st0;
st200:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof200;
case 200:
	switch( (*( state.p)) ) {
		case 13: goto tr287;
		case 32: goto tr287;
		case 59: goto tr288;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr287;
	goto st0;
st201:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof201;
case 201:
	if ( (*( state.p)) == 97 )
		goto st202;
	goto st0;
st202:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof202;
case 202:
	switch( (*( state.p)) ) {
		case 108: goto st203;
		case 116: goto st205;
	}
	goto st0;
st203:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof203;
case 203:
	if ( (*( state.p)) == 107 )
		goto st204;
	goto st0;
st204:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof204;
case 204:
	switch( (*( state.p)) ) {
		case 13: goto tr293;
		case 32: goto tr293;
		case 59: goto tr294;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr293;
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
	if ( (*( state.p)) == 114 )
		goto st207;
	goto st0;
st207:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof207;
case 207:
	switch( (*( state.p)) ) {
		case 13: goto tr297;
		case 32: goto tr297;
		case 59: goto tr298;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr297;
	goto st0;
st208:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof208;
case 208:
	if ( (*( state.p)) == 100 )
		goto st209;
	goto st0;
st209:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof209;
case 209:
	if ( (*( state.p)) == 108 )
		goto st210;
	goto st0;
st210:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof210;
case 210:
	if ( (*( state.p)) == 101 )
		goto st211;
	goto st0;
st211:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof211;
case 211:
	if ( (*( state.p)) == 95 )
		goto st212;
	goto st0;
st212:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof212;
case 212:
	if ( (*( state.p)) == 97 )
		goto st213;
	goto st0;
st213:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof213;
case 213:
	if ( (*( state.p)) == 105 )
		goto st214;
	goto st0;
st214:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof214;
case 214:
	switch( (*( state.p)) ) {
		case 13: goto st215;
		case 32: goto st215;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st215;
	goto st0;
st215:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof215;
case 215:
	switch( (*( state.p)) ) {
		case 13: goto st215;
		case 32: goto st215;
		case 110: goto st216;
		case 114: goto st220;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st215;
	goto st0;
st216:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof216;
case 216:
	if ( (*( state.p)) == 111 )
		goto st217;
	goto st0;
st217:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof217;
case 217:
	if ( (*( state.p)) == 110 )
		goto st218;
	goto st0;
st218:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof218;
case 218:
	if ( (*( state.p)) == 101 )
		goto st219;
	goto st0;
st219:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof219;
case 219:
	switch( (*( state.p)) ) {
		case 13: goto tr311;
		case 32: goto tr311;
		case 59: goto tr312;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr311;
	goto st0;
st220:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof220;
case 220:
	if ( (*( state.p)) == 97 )
		goto st221;
	goto st0;
st221:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof221;
case 221:
	if ( (*( state.p)) == 110 )
		goto st222;
	goto st0;
st222:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof222;
case 222:
	if ( (*( state.p)) == 100 )
		goto st223;
	goto st0;
st223:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof223;
case 223:
	if ( (*( state.p)) == 111 )
		goto st224;
	goto st0;
st224:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof224;
case 224:
	if ( (*( state.p)) == 109 )
		goto st225;
	goto st0;
st225:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof225;
case 225:
	switch( (*( state.p)) ) {
		case 13: goto tr318;
		case 32: goto tr318;
		case 59: goto tr319;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr318;
	goto st0;
st226:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof226;
case 226:
	if ( (*( state.p)) == 111 )
		goto st227;
	goto st0;
st227:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof227;
case 227:
	if ( (*( state.p)) == 118 )
		goto st228;
	goto st0;
st228:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof228;
case 228:
	if ( (*( state.p)) == 101 )
		goto st229;
	goto st0;
st229:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof229;
case 229:
	switch( (*( state.p)) ) {
		case 13: goto st230;
		case 32: goto st230;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st230;
	goto st0;
st230:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof230;
case 230:
	switch( (*( state.p)) ) {
		case 13: goto st230;
		case 32: goto st230;
		case 97: goto st231;
		case 99: goto st234;
		case 102: goto st240;
		case 119: goto st245;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st230;
	goto st0;
st231:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof231;
case 231:
	if ( (*( state.p)) == 110 )
		goto st232;
	goto st0;
st232:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof232;
case 232:
	if ( (*( state.p)) == 121 )
		goto st233;
	goto st0;
st233:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof233;
case 233:
	switch( (*( state.p)) ) {
		case 13: goto tr330;
		case 32: goto tr330;
		case 59: goto tr331;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr330;
	goto st0;
st234:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof234;
case 234:
	if ( (*( state.p)) == 111 )
		goto st235;
	goto st0;
st235:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof235;
case 235:
	if ( (*( state.p)) == 114 )
		goto st236;
	goto st0;
st236:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof236;
case 236:
	if ( (*( state.p)) == 110 )
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
	if ( (*( state.p)) == 114 )
		goto st239;
	goto st0;
st239:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof239;
case 239:
	switch( (*( state.p)) ) {
		case 13: goto tr337;
		case 32: goto tr337;
		case 59: goto tr338;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr337;
	goto st0;
st240:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof240;
case 240:
	if ( (*( state.p)) == 108 )
		goto st241;
	goto st0;
st241:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof241;
case 241:
	if ( (*( state.p)) == 111 )
		goto st242;
	goto st0;
st242:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof242;
case 242:
	if ( (*( state.p)) == 111 )
		goto st243;
	goto st0;
st243:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof243;
case 243:
	if ( (*( state.p)) == 114 )
		goto st244;
	goto st0;
st244:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof244;
case 244:
	switch( (*( state.p)) ) {
		case 13: goto tr343;
		case 32: goto tr343;
		case 59: goto tr344;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr343;
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
	if ( (*( state.p)) == 116 )
		goto st247;
	goto st0;
st247:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof247;
case 247:
	if ( (*( state.p)) == 101 )
		goto st248;
	goto st0;
st248:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof248;
case 248:
	if ( (*( state.p)) == 114 )
		goto st249;
	goto st0;
st249:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof249;
case 249:
	switch( (*( state.p)) ) {
		case 13: goto tr349;
		case 32: goto tr349;
		case 59: goto tr350;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr349;
	goto st0;
st250:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof250;
case 250:
	if ( (*( state.p)) == 97 )
		goto st251;
	goto st0;
st251:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof251;
case 251:
	if ( (*( state.p)) == 109 )
		goto st252;
	goto st0;
st252:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof252;
case 252:
	if ( (*( state.p)) == 101 )
		goto st253;
	goto st0;
st253:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof253;
case 253:
	switch( (*( state.p)) ) {
		case 13: goto st254;
		case 32: goto st254;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st254;
	goto st0;
st254:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof254;
case 254:
	switch( (*( state.p)) ) {
		case 13: goto st254;
		case 32: goto st254;
		case 34: goto tr355;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st254;
	goto st0;
tr356:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st255;
tr355:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
	goto st255;
tr358:
#line 144 "configparser.rl"
	{{ state.stack[ state.top++] = 255; goto st47;}}
	goto st255;
st255:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof255;
case 255:
#line 5243 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st256;
		case 92: goto tr358;
	}
	goto tr356;
st256:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof256;
case 256:
	switch( (*( state.p)) ) {
		case 13: goto tr359;
		case 32: goto tr359;
		case 59: goto tr360;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr359;
	goto st0;
st257:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof257;
case 257:
	if ( (*( state.p)) == 97 )
		goto st258;
	goto st0;
st258:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof258;
case 258:
	if ( (*( state.p)) == 110 )
		goto st259;
	goto st0;
st259:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof259;
case 259:
	if ( (*( state.p)) == 103 )
		goto st260;
	goto st0;
st260:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof260;
case 260:
	if ( (*( state.p)) == 101 )
		goto st261;
	goto st0;
st261:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof261;
case 261:
	switch( (*( state.p)) ) {
		case 13: goto st262;
		case 32: goto st262;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st262;
	goto st0;
st262:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof262;
case 262:
	switch( (*( state.p)) ) {
		case 13: goto st262;
		case 32: goto st262;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr366;
	} else if ( (*( state.p)) >= 9 )
		goto st262;
	goto st0;
tr366:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st263;
tr368:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st263;
st263:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof263;
case 263:
#line 5334 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr367;
		case 32: goto tr367;
		case 59: goto tr369;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr368;
	} else if ( (*( state.p)) >= 9 )
		goto tr367;
	goto st0;
st264:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof264;
case 264:
	switch( (*( state.p)) ) {
		case 107: goto st265;
		case 117: goto st323;
	}
	goto st0;
st265:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof265;
case 265:
	if ( (*( state.p)) == 105 )
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
	switch( (*( state.p)) ) {
		case 13: goto st268;
		case 32: goto st268;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st268;
	goto st0;
st268:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof268;
case 268:
	switch( (*( state.p)) ) {
		case 13: goto st268;
		case 32: goto st268;
		case 34: goto tr375;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st268;
	goto st0;
tr376:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st269;
tr375:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
	goto st269;
tr378:
#line 144 "configparser.rl"
	{{ state.stack[ state.top++] = 269; goto st47;}}
	goto st269;
st269:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof269;
case 269:
#line 5412 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st270;
		case 92: goto tr378;
	}
	goto tr376;
st270:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof270;
case 270:
	switch( (*( state.p)) ) {
		case 13: goto tr379;
		case 32: goto tr379;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr379;
	goto st0;
tr379:
#line 166 "configparser.rl"
	{ skin.text = state.match; }
	goto st271;
st271:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof271;
case 271:
#line 5437 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st271;
		case 32: goto st271;
		case 98: goto st272;
		case 100: goto st317;
		case 110: goto st320;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st271;
	goto st0;
st272:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof272;
case 272:
	if ( (*( state.p)) == 114 )
		goto st273;
	goto st0;
st273:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof273;
case 273:
	if ( (*( state.p)) == 105 )
		goto st274;
	goto st0;
st274:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof274;
case 274:
	if ( (*( state.p)) == 103 )
		goto st275;
	goto st0;
st275:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof275;
case 275:
	if ( (*( state.p)) == 104 )
		goto st276;
	goto st0;
st276:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof276;
case 276:
	if ( (*( state.p)) == 116 )
		goto st277;
	goto st0;
st277:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof277;
case 277:
	switch( (*( state.p)) ) {
		case 13: goto tr389;
		case 32: goto tr389;
		case 95: goto tr390;
		case 98: goto tr391;
		case 99: goto tr392;
		case 103: goto tr393;
		case 109: goto tr394;
		case 114: goto tr395;
		case 119: goto tr396;
		case 121: goto tr397;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr389;
	goto st0;
tr389:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st278;
tr454:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st278;
st278:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof278;
case 278:
#line 5514 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st278;
		case 32: goto st278;
		case 98: goto st279;
		case 99: goto st286;
		case 103: goto st290;
		case 109: goto st295;
		case 114: goto st302;
		case 119: goto st305;
		case 121: goto st310;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st278;
	goto st0;
tr391:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st279;
tr456:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st279;
st279:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof279;
case 279:
#line 5541 "configparser.h"
	if ( (*( state.p)) == 108 )
		goto st280;
	goto st0;
st280:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof280;
case 280:
	switch( (*( state.p)) ) {
		case 97: goto st281;
		case 117: goto st284;
	}
	goto st0;
st281:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof281;
case 281:
	if ( (*( state.p)) == 99 )
		goto st282;
	goto st0;
st282:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof282;
case 282:
	if ( (*( state.p)) == 107 )
		goto st283;
	goto st0;
st283:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof283;
case 283:
	switch( (*( state.p)) ) {
		case 13: goto tr411;
		case 32: goto tr411;
		case 59: goto tr412;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr411;
	goto st0;
st284:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof284;
case 284:
	if ( (*( state.p)) == 101 )
		goto st285;
	goto st0;
st285:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof285;
case 285:
	switch( (*( state.p)) ) {
		case 13: goto tr414;
		case 32: goto tr414;
		case 59: goto tr415;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr414;
	goto st0;
tr392:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st286;
tr457:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st286;
st286:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof286;
case 286:
#line 5611 "configparser.h"
	if ( (*( state.p)) == 121 )
		goto st287;
	goto st0;
st287:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof287;
case 287:
	if ( (*( state.p)) == 97 )
		goto st288;
	goto st0;
st288:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof288;
case 288:
	if ( (*( state.p)) == 110 )
		goto st289;
	goto st0;
st289:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof289;
case 289:
	switch( (*( state.p)) ) {
		case 13: goto tr419;
		case 32: goto tr419;
		case 59: goto tr420;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr419;
	goto st0;
tr393:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st290;
tr458:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st290;
st290:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof290;
case 290:
#line 5653 "configparser.h"
	if ( (*( state.p)) == 114 )
		goto st291;
	goto st0;
st291:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof291;
case 291:
	if ( (*( state.p)) == 101 )
		goto st292;
	goto st0;
st292:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof292;
case 292:
	if ( (*( state.p)) == 101 )
		goto st293;
	goto st0;
st293:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof293;
case 293:
	if ( (*( state.p)) == 110 )
		goto st294;
	goto st0;
st294:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof294;
case 294:
	switch( (*( state.p)) ) {
		case 13: goto tr425;
		case 32: goto tr425;
		case 59: goto tr426;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr425;
	goto st0;
tr394:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st295;
tr459:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st295;
st295:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof295;
case 295:
#line 5702 "configparser.h"
	if ( (*( state.p)) == 97 )
		goto st296;
	goto st0;
st296:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof296;
case 296:
	if ( (*( state.p)) == 103 )
		goto st297;
	goto st0;
st297:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof297;
case 297:
	if ( (*( state.p)) == 101 )
		goto st298;
	goto st0;
st298:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof298;
case 298:
	if ( (*( state.p)) == 110 )
		goto st299;
	goto st0;
st299:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof299;
case 299:
	if ( (*( state.p)) == 116 )
		goto st300;
	goto st0;
st300:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof300;
case 300:
	if ( (*( state.p)) == 97 )
		goto st301;
	goto st0;
st301:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof301;
case 301:
	switch( (*( state.p)) ) {
		case 13: goto tr433;
		case 32: goto tr433;
		case 59: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr433;
	goto st0;
tr395:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st302;
tr460:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st302;
st302:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof302;
case 302:
#line 5765 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st303;
	goto st0;
st303:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof303;
case 303:
	if ( (*( state.p)) == 100 )
		goto st304;
	goto st0;
st304:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof304;
case 304:
	switch( (*( state.p)) ) {
		case 13: goto tr437;
		case 32: goto tr437;
		case 59: goto tr438;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr437;
	goto st0;
tr396:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st305;
tr461:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st305;
st305:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof305;
case 305:
#line 5800 "configparser.h"
	if ( (*( state.p)) == 104 )
		goto st306;
	goto st0;
st306:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof306;
case 306:
	if ( (*( state.p)) == 105 )
		goto st307;
	goto st0;
st307:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof307;
case 307:
	if ( (*( state.p)) == 116 )
		goto st308;
	goto st0;
st308:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof308;
case 308:
	if ( (*( state.p)) == 101 )
		goto st309;
	goto st0;
st309:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof309;
case 309:
	switch( (*( state.p)) ) {
		case 13: goto tr443;
		case 32: goto tr443;
		case 59: goto tr444;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr443;
	goto st0;
tr397:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st310;
tr462:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st310;
st310:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof310;
case 310:
#line 5849 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st311;
	goto st0;
st311:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof311;
case 311:
	if ( (*( state.p)) == 108 )
		goto st312;
	goto st0;
st312:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof312;
case 312:
	if ( (*( state.p)) == 108 )
		goto st313;
	goto st0;
st313:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof313;
case 313:
	if ( (*( state.p)) == 111 )
		goto st314;
	goto st0;
st314:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof314;
case 314:
	if ( (*( state.p)) == 119 )
		goto st315;
	goto st0;
st315:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof315;
case 315:
	switch( (*( state.p)) ) {
		case 13: goto tr450;
		case 32: goto tr450;
		case 59: goto tr451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr450;
	goto st0;
tr390:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st316;
tr455:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st316;
st316:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof316;
case 316:
#line 5905 "configparser.h"
	switch( (*( state.p)) ) {
		case 98: goto st279;
		case 99: goto st286;
		case 103: goto st290;
		case 109: goto st295;
		case 114: goto st302;
		case 119: goto st305;
		case 121: goto st310;
	}
	goto st0;
st317:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof317;
case 317:
	if ( (*( state.p)) == 105 )
		goto st318;
	goto st0;
st318:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof318;
case 318:
	if ( (*( state.p)) == 109 )
		goto st319;
	goto st0;
st319:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof319;
case 319:
	switch( (*( state.p)) ) {
		case 13: goto tr454;
		case 32: goto tr454;
		case 95: goto tr455;
		case 98: goto tr456;
		case 99: goto tr457;
		case 103: goto tr458;
		case 109: goto tr459;
		case 114: goto tr460;
		case 119: goto tr461;
		case 121: goto tr462;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr454;
	goto st0;
st320:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof320;
case 320:
	if ( (*( state.p)) == 111 )
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
	if ( (*( state.p)) == 101 )
		goto st283;
	goto st0;
st323:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof323;
case 323:
	if ( (*( state.p)) == 109 )
		goto st324;
	goto st0;
st324:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof324;
case 324:
	if ( (*( state.p)) == 109 )
		goto st325;
	goto st0;
st325:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof325;
case 325:
	if ( (*( state.p)) == 111 )
		goto st326;
	goto st0;
st326:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof326;
case 326:
	if ( (*( state.p)) == 110 )
		goto st327;
	goto st0;
st327:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof327;
case 327:
	switch( (*( state.p)) ) {
		case 13: goto tr469;
		case 32: goto tr469;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr469;
	goto st0;
tr469:
#line 241 "configparser.rl"
	{ spe.summon.push_back(Species::summon_t()); }
	goto st328;
st328:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof328;
case 328:
#line 6017 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st328;
		case 32: goto st328;
		case 45: goto tr471;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr472;
	} else if ( (*( state.p)) >= 9 )
		goto st328;
	goto st0;
tr471:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st329;
st329:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof329;
case 329:
#line 6043 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr473;
	goto st0;
tr472:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st330;
tr473:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st330;
st330:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof330;
case 330:
#line 6067 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr474;
		case 32: goto tr474;
		case 46: goto tr475;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr473;
	} else if ( (*( state.p)) >= 9 )
		goto tr474;
	goto st0;
tr474:
#line 242 "configparser.rl"
	{ spe.summon.back().chance = toreal(state.match); }
	goto st331;
st331:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof331;
case 331:
#line 6087 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st331;
		case 32: goto st331;
		case 34: goto tr477;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st331;
	goto st0;
tr478:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st332;
tr477:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
	goto st332;
tr480:
#line 144 "configparser.rl"
	{{ state.stack[ state.top++] = 332; goto st47;}}
	goto st332;
st332:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof332;
case 332:
#line 6116 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st333;
		case 92: goto tr480;
	}
	goto tr478;
st333:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof333;
case 333:
	switch( (*( state.p)) ) {
		case 13: goto tr481;
		case 32: goto tr481;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr481;
	goto st0;
tr481:
#line 243 "configparser.rl"
	{ spe.summon.back().speciestag = state.match; }
	goto st334;
st334:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof334;
case 334:
#line 6141 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st334;
		case 32: goto st334;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr483;
	} else if ( (*( state.p)) >= 9 )
		goto st334;
	goto st0;
tr483:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st335;
tr485:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st335;
st335:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof335;
case 335:
#line 6172 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr484;
		case 32: goto tr484;
		case 59: goto tr486;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr485;
	} else if ( (*( state.p)) >= 9 )
		goto tr484;
	goto st0;
tr475:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st336;
st336:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof336;
case 336:
#line 6194 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr487;
	goto st0;
tr487:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st337;
st337:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof337;
case 337:
#line 6208 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr474;
		case 32: goto tr474;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr487;
	} else if ( (*( state.p)) >= 9 )
		goto tr474;
	goto st0;
st338:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof338;
case 338:
	if ( (*( state.p)) == 111 )
		goto st339;
	goto st0;
st339:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof339;
case 339:
	if ( (*( state.p)) == 110 )
		goto st340;
	goto st0;
st340:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof340;
case 340:
	if ( (*( state.p)) == 101 )
		goto st341;
	goto st0;
st341:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof341;
case 341:
	switch( (*( state.p)) ) {
		case 13: goto tr491;
		case 32: goto tr491;
		case 59: goto tr492;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr491;
	goto st0;
st342:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof342;
case 342:
	if ( (*( state.p)) == 97 )
		goto st343;
	goto st0;
st343:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof343;
case 343:
	if ( (*( state.p)) == 110 )
		goto st344;
	goto st0;
st344:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof344;
case 344:
	if ( (*( state.p)) == 100 )
		goto st345;
	goto st0;
st345:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof345;
case 345:
	if ( (*( state.p)) == 111 )
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
	switch( (*( state.p)) ) {
		case 13: goto tr498;
		case 32: goto tr498;
		case 59: goto tr499;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr498;
	goto st0;
st348:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof348;
case 348:
	if ( (*( state.p)) == 101 )
		goto st349;
	goto st0;
st349:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof349;
case 349:
	if ( (*( state.p)) == 101 )
		goto st350;
	goto st0;
st350:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof350;
case 350:
	if ( (*( state.p)) == 107 )
		goto st351;
	goto st0;
st351:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof351;
case 351:
	if ( (*( state.p)) == 95 )
		goto st352;
	goto st0;
st352:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof352;
case 352:
	switch( (*( state.p)) ) {
		case 110: goto st353;
		case 112: goto st360;
	}
	goto st0;
st353:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof353;
case 353:
	if ( (*( state.p)) == 111 )
		goto st354;
	goto st0;
st354:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof354;
case 354:
	if ( (*( state.p)) == 115 )
		goto st355;
	goto st0;
st355:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof355;
case 355:
	if ( (*( state.p)) == 108 )
		goto st356;
	goto st0;
st356:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof356;
case 356:
	if ( (*( state.p)) == 101 )
		goto st357;
	goto st0;
st357:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof357;
case 357:
	if ( (*( state.p)) == 101 )
		goto st358;
	goto st0;
st358:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof358;
case 358:
	if ( (*( state.p)) == 112 )
		goto st359;
	goto st0;
st359:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof359;
case 359:
	switch( (*( state.p)) ) {
		case 13: goto tr512;
		case 32: goto tr512;
		case 59: goto tr513;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr512;
	goto st0;
st360:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof360;
case 360:
	if ( (*( state.p)) == 108 )
		goto st361;
	goto st0;
st361:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof361;
case 361:
	if ( (*( state.p)) == 97 )
		goto st362;
	goto st0;
st362:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof362;
case 362:
	if ( (*( state.p)) == 121 )
		goto st363;
	goto st0;
st363:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof363;
case 363:
	if ( (*( state.p)) == 101 )
		goto st364;
	goto st0;
st364:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof364;
case 364:
	if ( (*( state.p)) == 114 )
		goto st365;
	goto st0;
st365:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof365;
case 365:
	switch( (*( state.p)) ) {
		case 13: goto tr519;
		case 32: goto tr519;
		case 59: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr519;
	goto st0;
st366:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof366;
case 366:
	if ( (*( state.p)) == 116 )
		goto st367;
	goto st0;
st367:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof367;
case 367:
	if ( (*( state.p)) == 97 )
		goto st368;
	goto st0;
st368:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof368;
case 368:
	if ( (*( state.p)) == 99 )
		goto st369;
	goto st0;
st369:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof369;
case 369:
	if ( (*( state.p)) == 107 )
		goto st370;
	goto st0;
st370:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof370;
case 370:
	switch( (*( state.p)) ) {
		case 13: goto st371;
		case 32: goto st371;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st371;
	goto st0;
st371:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof371;
case 371:
	switch( (*( state.p)) ) {
		case 13: goto st371;
		case 32: goto st371;
		case 112: goto st372;
		case 115: goto st390;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st371;
	goto st0;
st372:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof372;
case 372:
	switch( (*( state.p)) ) {
		case 104: goto st373;
		case 111: goto st385;
	}
	goto st0;
st373:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof373;
case 373:
	if ( (*( state.p)) == 121 )
		goto st374;
	goto st0;
st374:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof374;
case 374:
	if ( (*( state.p)) == 115 )
		goto st375;
	goto st0;
st375:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof375;
case 375:
	if ( (*( state.p)) == 105 )
		goto st376;
	goto st0;
st376:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof376;
case 376:
	if ( (*( state.p)) == 99 )
		goto st377;
	goto st0;
st377:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof377;
case 377:
	if ( (*( state.p)) == 97 )
		goto st378;
	goto st0;
st378:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof378;
case 378:
	if ( (*( state.p)) == 108 )
		goto st379;
	goto st0;
st379:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof379;
case 379:
	switch( (*( state.p)) ) {
		case 13: goto tr536;
		case 32: goto tr536;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr536;
	goto st0;
tr536:
#line 171 "configparser.rl"
	{ dmgval.type = damage::type_t::physical; }
	goto st380;
tr549:
#line 173 "configparser.rl"
	{ dmgval.type = damage::type_t::poison; }
	goto st380;
tr554:
#line 172 "configparser.rl"
	{ dmgval.type = damage::type_t::sleep; }
	goto st380;
st380:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof380;
case 380:
#line 6567 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st380;
		case 32: goto st380;
		case 45: goto tr538;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr539;
	} else if ( (*( state.p)) >= 9 )
		goto st380;
	goto st0;
tr538:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st381;
st381:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof381;
case 381:
#line 6593 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr540;
	goto st0;
tr539:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st382;
tr540:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st382;
st382:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof382;
case 382:
#line 6617 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr541;
		case 32: goto tr541;
		case 46: goto tr542;
		case 59: goto tr543;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr540;
	} else if ( (*( state.p)) >= 9 )
		goto tr541;
	goto st0;
tr542:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st383;
st383:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof383;
case 383:
#line 6640 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr544;
	goto st0;
tr544:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st384;
st384:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof384;
case 384:
#line 6654 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr541;
		case 32: goto tr541;
		case 59: goto tr543;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr544;
	} else if ( (*( state.p)) >= 9 )
		goto tr541;
	goto st0;
st385:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof385;
case 385:
	if ( (*( state.p)) == 105 )
		goto st386;
	goto st0;
st386:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof386;
case 386:
	if ( (*( state.p)) == 115 )
		goto st387;
	goto st0;
st387:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof387;
case 387:
	if ( (*( state.p)) == 111 )
		goto st388;
	goto st0;
st388:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof388;
case 388:
	if ( (*( state.p)) == 110 )
		goto st389;
	goto st0;
st389:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof389;
case 389:
	switch( (*( state.p)) ) {
		case 13: goto tr549;
		case 32: goto tr549;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr549;
	goto st0;
st390:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof390;
case 390:
	if ( (*( state.p)) == 108 )
		goto st391;
	goto st0;
st391:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof391;
case 391:
	if ( (*( state.p)) == 101 )
		goto st392;
	goto st0;
st392:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof392;
case 392:
	if ( (*( state.p)) == 101 )
		goto st393;
	goto st0;
st393:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof393;
case 393:
	if ( (*( state.p)) == 112 )
		goto st394;
	goto st0;
st394:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof394;
case 394:
	switch( (*( state.p)) ) {
		case 13: goto tr554;
		case 32: goto tr554;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr554;
	goto st0;
st395:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof395;
case 395:
	switch( (*( state.p)) ) {
		case 13: goto st395;
		case 32: goto st395;
		case 97: goto st396;
		case 99: goto st415;
		case 100: goto st422;
		case 104: goto st459;
		case 110: goto st468;
		case 112: goto st475;
		case 115: goto st494;
		case 116: goto st570;
		case 117: goto st582;
		case 125: goto tr565;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st395;
	goto st0;
st396:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof396;
case 396:
	if ( (*( state.p)) == 116 )
		goto st397;
	goto st0;
st397:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof397;
case 397:
	if ( (*( state.p)) == 116 )
		goto st398;
	goto st0;
st398:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof398;
case 398:
	if ( (*( state.p)) == 97 )
		goto st399;
	goto st0;
st399:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof399;
case 399:
	if ( (*( state.p)) == 99 )
		goto st400;
	goto st0;
st400:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof400;
case 400:
	if ( (*( state.p)) == 107 )
		goto st401;
	goto st0;
st401:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof401;
case 401:
	switch( (*( state.p)) ) {
		case 13: goto st402;
		case 32: goto st402;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st402;
	goto st0;
st402:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof402;
case 402:
	switch( (*( state.p)) ) {
		case 13: goto st402;
		case 32: goto st402;
		case 112: goto st403;
		case 115: goto st595;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st402;
	goto st0;
st403:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof403;
case 403:
	switch( (*( state.p)) ) {
		case 104: goto st404;
		case 111: goto st590;
	}
	goto st0;
st404:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof404;
case 404:
	if ( (*( state.p)) == 121 )
		goto st405;
	goto st0;
st405:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof405;
case 405:
	if ( (*( state.p)) == 115 )
		goto st406;
	goto st0;
st406:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof406;
case 406:
	if ( (*( state.p)) == 105 )
		goto st407;
	goto st0;
st407:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof407;
case 407:
	if ( (*( state.p)) == 99 )
		goto st408;
	goto st0;
st408:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof408;
case 408:
	if ( (*( state.p)) == 97 )
		goto st409;
	goto st0;
st409:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof409;
case 409:
	if ( (*( state.p)) == 108 )
		goto st410;
	goto st0;
st410:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof410;
case 410:
	switch( (*( state.p)) ) {
		case 13: goto tr582;
		case 32: goto tr582;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr582;
	goto st0;
tr582:
#line 171 "configparser.rl"
	{ dmgval.type = damage::type_t::physical; }
	goto st411;
tr833:
#line 173 "configparser.rl"
	{ dmgval.type = damage::type_t::poison; }
	goto st411;
tr838:
#line 172 "configparser.rl"
	{ dmgval.type = damage::type_t::sleep; }
	goto st411;
st411:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof411;
case 411:
#line 6902 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st411;
		case 32: goto st411;
		case 45: goto tr584;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr585;
	} else if ( (*( state.p)) >= 9 )
		goto st411;
	goto st0;
tr584:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st412;
st412:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof412;
case 412:
#line 6928 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr586;
	goto st0;
tr585:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st413;
tr586:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st413;
st413:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof413;
case 413:
#line 6952 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr587;
		case 32: goto tr587;
		case 46: goto tr588;
		case 59: goto tr589;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr586;
	} else if ( (*( state.p)) >= 9 )
		goto tr587;
	goto st0;
tr565:
#line 293 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st414;
tr587:
#line 177 "configparser.rl"
	{ dmgval.val = toreal(state.match); }
#line 279 "configparser.rl"
	{ des.attacks.add(dmgval); }
	goto st414;
tr598:
#line 274 "configparser.rl"
	{ des.count = toint(state.match); }
	goto st414;
tr624:
#line 177 "configparser.rl"
	{ dmgval.val = toreal(state.match); }
#line 280 "configparser.rl"
	{ des.defenses.add(dmgval); }
	goto st414;
tr645:
#line 278 "configparser.rl"
	{ des.descr = state.match; }
	goto st414;
tr654:
#line 282 "configparser.rl"
	{ des.heal = toreal(state.match); }
	goto st414;
tr666:
#line 275 "configparser.rl"
	{ des.name = state.match; }
	goto st414;
tr685:
#line 286 "configparser.rl"
	{ des.poison_defense = toreal(state.match); }
	goto st414;
tr731:
#line 276 "configparser.rl"
	{ des.skin = skin; }
	goto st414;
tr734:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 276 "configparser.rl"
	{ des.skin = skin; }
	goto st414;
tr739:
#line 158 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 276 "configparser.rl"
	{ des.skin = skin; }
	goto st414;
tr745:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 276 "configparser.rl"
	{ des.skin = skin; }
	goto st414;
tr753:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 276 "configparser.rl"
	{ des.skin = skin; }
	goto st414;
tr757:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 276 "configparser.rl"
	{ des.skin = skin; }
	goto st414;
tr763:
#line 159 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 276 "configparser.rl"
	{ des.skin = skin; }
	goto st414;
tr770:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 276 "configparser.rl"
	{ des.skin = skin; }
	goto st414;
tr792:
#line 277 "configparser.rl"
	{ des.slot = state.match; }
	goto st414;
tr804:
#line 281 "configparser.rl"
	{ des.stackrange = toint(state.match); }
	goto st414;
tr818:
#line 284 "configparser.rl"
	{ des.throwrange = toint(state.match); }
	goto st414;
tr826:
#line 283 "configparser.rl"
	{ des.usable = true; }
	goto st414;
st414:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof414;
case 414:
#line 7067 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st414;
		case 32: goto st414;
		case 59: goto st1525;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st414;
	goto st0;
tr589:
#line 177 "configparser.rl"
	{ dmgval.val = toreal(state.match); }
#line 279 "configparser.rl"
	{ des.attacks.add(dmgval); }
	goto st1525;
tr600:
#line 274 "configparser.rl"
	{ des.count = toint(state.match); }
	goto st1525;
tr626:
#line 177 "configparser.rl"
	{ dmgval.val = toreal(state.match); }
#line 280 "configparser.rl"
	{ des.defenses.add(dmgval); }
	goto st1525;
tr646:
#line 278 "configparser.rl"
	{ des.descr = state.match; }
	goto st1525;
tr656:
#line 282 "configparser.rl"
	{ des.heal = toreal(state.match); }
	goto st1525;
tr667:
#line 275 "configparser.rl"
	{ des.name = state.match; }
	goto st1525;
tr687:
#line 286 "configparser.rl"
	{ des.poison_defense = toreal(state.match); }
	goto st1525;
tr732:
#line 276 "configparser.rl"
	{ des.skin = skin; }
	goto st1525;
tr735:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 276 "configparser.rl"
	{ des.skin = skin; }
	goto st1525;
tr740:
#line 158 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 276 "configparser.rl"
	{ des.skin = skin; }
	goto st1525;
tr746:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 276 "configparser.rl"
	{ des.skin = skin; }
	goto st1525;
tr754:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 276 "configparser.rl"
	{ des.skin = skin; }
	goto st1525;
tr758:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 276 "configparser.rl"
	{ des.skin = skin; }
	goto st1525;
tr764:
#line 159 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 276 "configparser.rl"
	{ des.skin = skin; }
	goto st1525;
tr771:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 276 "configparser.rl"
	{ des.skin = skin; }
	goto st1525;
tr793:
#line 277 "configparser.rl"
	{ des.slot = state.match; }
	goto st1525;
tr806:
#line 281 "configparser.rl"
	{ des.stackrange = toint(state.match); }
	goto st1525;
tr820:
#line 284 "configparser.rl"
	{ des.throwrange = toint(state.match); }
	goto st1525;
tr827:
#line 283 "configparser.rl"
	{ des.usable = true; }
	goto st1525;
st1525:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1525;
case 1525:
#line 7174 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st395;
		case 32: goto st395;
		case 97: goto st396;
		case 99: goto st415;
		case 100: goto st422;
		case 104: goto st459;
		case 110: goto st468;
		case 112: goto st475;
		case 115: goto st494;
		case 116: goto st570;
		case 117: goto st582;
		case 125: goto tr565;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st395;
	goto st0;
st415:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof415;
case 415:
	if ( (*( state.p)) == 111 )
		goto st416;
	goto st0;
st416:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof416;
case 416:
	if ( (*( state.p)) == 117 )
		goto st417;
	goto st0;
st417:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof417;
case 417:
	if ( (*( state.p)) == 110 )
		goto st418;
	goto st0;
st418:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof418;
case 418:
	if ( (*( state.p)) == 116 )
		goto st419;
	goto st0;
st419:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof419;
case 419:
	switch( (*( state.p)) ) {
		case 13: goto st420;
		case 32: goto st420;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st420;
	goto st0;
st420:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof420;
case 420:
	switch( (*( state.p)) ) {
		case 13: goto st420;
		case 32: goto st420;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr597;
	} else if ( (*( state.p)) >= 9 )
		goto st420;
	goto st0;
tr597:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st421;
tr599:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st421;
st421:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof421;
case 421:
#line 7265 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr598;
		case 32: goto tr598;
		case 59: goto tr600;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr599;
	} else if ( (*( state.p)) >= 9 )
		goto tr598;
	goto st0;
st422:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof422;
case 422:
	if ( (*( state.p)) == 101 )
		goto st423;
	goto st0;
st423:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof423;
case 423:
	switch( (*( state.p)) ) {
		case 102: goto st424;
		case 115: goto st453;
	}
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
	if ( (*( state.p)) == 110 )
		goto st426;
	goto st0;
st426:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof426;
case 426:
	if ( (*( state.p)) == 115 )
		goto st427;
	goto st0;
st427:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof427;
case 427:
	if ( (*( state.p)) == 101 )
		goto st428;
	goto st0;
st428:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof428;
case 428:
	switch( (*( state.p)) ) {
		case 13: goto st429;
		case 32: goto st429;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st429;
	goto st0;
st429:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof429;
case 429:
	switch( (*( state.p)) ) {
		case 13: goto st429;
		case 32: goto st429;
		case 112: goto st430;
		case 115: goto st448;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st429;
	goto st0;
st430:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof430;
case 430:
	switch( (*( state.p)) ) {
		case 104: goto st431;
		case 111: goto st443;
	}
	goto st0;
st431:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof431;
case 431:
	if ( (*( state.p)) == 121 )
		goto st432;
	goto st0;
st432:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof432;
case 432:
	if ( (*( state.p)) == 115 )
		goto st433;
	goto st0;
st433:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof433;
case 433:
	if ( (*( state.p)) == 105 )
		goto st434;
	goto st0;
st434:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof434;
case 434:
	if ( (*( state.p)) == 99 )
		goto st435;
	goto st0;
st435:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof435;
case 435:
	if ( (*( state.p)) == 97 )
		goto st436;
	goto st0;
st436:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof436;
case 436:
	if ( (*( state.p)) == 108 )
		goto st437;
	goto st0;
st437:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof437;
case 437:
	switch( (*( state.p)) ) {
		case 13: goto tr619;
		case 32: goto tr619;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr619;
	goto st0;
tr619:
#line 171 "configparser.rl"
	{ dmgval.type = damage::type_t::physical; }
	goto st438;
tr632:
#line 173 "configparser.rl"
	{ dmgval.type = damage::type_t::poison; }
	goto st438;
tr637:
#line 172 "configparser.rl"
	{ dmgval.type = damage::type_t::sleep; }
	goto st438;
st438:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof438;
case 438:
#line 7423 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st438;
		case 32: goto st438;
		case 45: goto tr621;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr622;
	} else if ( (*( state.p)) >= 9 )
		goto st438;
	goto st0;
tr621:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st439;
st439:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof439;
case 439:
#line 7449 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr623;
	goto st0;
tr622:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st440;
tr623:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st440;
st440:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof440;
case 440:
#line 7473 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr624;
		case 32: goto tr624;
		case 46: goto tr625;
		case 59: goto tr626;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr623;
	} else if ( (*( state.p)) >= 9 )
		goto tr624;
	goto st0;
tr625:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st441;
st441:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof441;
case 441:
#line 7496 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr627;
	goto st0;
tr627:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st442;
st442:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof442;
case 442:
#line 7510 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr624;
		case 32: goto tr624;
		case 59: goto tr626;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr627;
	} else if ( (*( state.p)) >= 9 )
		goto tr624;
	goto st0;
st443:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof443;
case 443:
	if ( (*( state.p)) == 105 )
		goto st444;
	goto st0;
st444:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof444;
case 444:
	if ( (*( state.p)) == 115 )
		goto st445;
	goto st0;
st445:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof445;
case 445:
	if ( (*( state.p)) == 111 )
		goto st446;
	goto st0;
st446:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof446;
case 446:
	if ( (*( state.p)) == 110 )
		goto st447;
	goto st0;
st447:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof447;
case 447:
	switch( (*( state.p)) ) {
		case 13: goto tr632;
		case 32: goto tr632;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr632;
	goto st0;
st448:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof448;
case 448:
	if ( (*( state.p)) == 108 )
		goto st449;
	goto st0;
st449:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof449;
case 449:
	if ( (*( state.p)) == 101 )
		goto st450;
	goto st0;
st450:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof450;
case 450:
	if ( (*( state.p)) == 101 )
		goto st451;
	goto st0;
st451:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof451;
case 451:
	if ( (*( state.p)) == 112 )
		goto st452;
	goto st0;
st452:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof452;
case 452:
	switch( (*( state.p)) ) {
		case 13: goto tr637;
		case 32: goto tr637;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr637;
	goto st0;
st453:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof453;
case 453:
	if ( (*( state.p)) == 99 )
		goto st454;
	goto st0;
st454:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof454;
case 454:
	if ( (*( state.p)) == 114 )
		goto st455;
	goto st0;
st455:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof455;
case 455:
	switch( (*( state.p)) ) {
		case 13: goto st456;
		case 32: goto st456;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st456;
	goto st0;
st456:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof456;
case 456:
	switch( (*( state.p)) ) {
		case 13: goto st456;
		case 32: goto st456;
		case 34: goto tr641;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st456;
	goto st0;
tr642:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st457;
tr641:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
	goto st457;
tr644:
#line 144 "configparser.rl"
	{{ state.stack[ state.top++] = 457; goto st47;}}
	goto st457;
st457:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof457;
case 457:
#line 7657 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st458;
		case 92: goto tr644;
	}
	goto tr642;
st458:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof458;
case 458:
	switch( (*( state.p)) ) {
		case 13: goto tr645;
		case 32: goto tr645;
		case 59: goto tr646;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr645;
	goto st0;
st459:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof459;
case 459:
	if ( (*( state.p)) == 101 )
		goto st460;
	goto st0;
st460:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof460;
case 460:
	if ( (*( state.p)) == 97 )
		goto st461;
	goto st0;
st461:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof461;
case 461:
	if ( (*( state.p)) == 108 )
		goto st462;
	goto st0;
st462:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof462;
case 462:
	switch( (*( state.p)) ) {
		case 13: goto st463;
		case 32: goto st463;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st463;
	goto st0;
st463:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof463;
case 463:
	switch( (*( state.p)) ) {
		case 13: goto st463;
		case 32: goto st463;
		case 45: goto tr651;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr652;
	} else if ( (*( state.p)) >= 9 )
		goto st463;
	goto st0;
tr651:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st464;
st464:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof464;
case 464:
#line 7736 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr653;
	goto st0;
tr652:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st465;
tr653:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st465;
st465:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof465;
case 465:
#line 7760 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr654;
		case 32: goto tr654;
		case 46: goto tr655;
		case 59: goto tr656;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr653;
	} else if ( (*( state.p)) >= 9 )
		goto tr654;
	goto st0;
tr655:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st466;
st466:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof466;
case 466:
#line 7783 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr657;
	goto st0;
tr657:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st467;
st467:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof467;
case 467:
#line 7797 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr654;
		case 32: goto tr654;
		case 59: goto tr656;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr657;
	} else if ( (*( state.p)) >= 9 )
		goto tr654;
	goto st0;
st468:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof468;
case 468:
	if ( (*( state.p)) == 97 )
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
	switch( (*( state.p)) ) {
		case 13: goto st472;
		case 32: goto st472;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st472;
	goto st0;
st472:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof472;
case 472:
	switch( (*( state.p)) ) {
		case 13: goto st472;
		case 32: goto st472;
		case 34: goto tr662;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st472;
	goto st0;
tr663:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st473;
tr662:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
	goto st473;
tr665:
#line 144 "configparser.rl"
	{{ state.stack[ state.top++] = 473; goto st47;}}
	goto st473;
st473:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof473;
case 473:
#line 7873 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st474;
		case 92: goto tr665;
	}
	goto tr663;
st474:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof474;
case 474:
	switch( (*( state.p)) ) {
		case 13: goto tr666;
		case 32: goto tr666;
		case 59: goto tr667;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr666;
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
	if ( (*( state.p)) == 105 )
		goto st477;
	goto st0;
st477:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof477;
case 477:
	if ( (*( state.p)) == 115 )
		goto st478;
	goto st0;
st478:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof478;
case 478:
	if ( (*( state.p)) == 111 )
		goto st479;
	goto st0;
st479:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof479;
case 479:
	if ( (*( state.p)) == 110 )
		goto st480;
	goto st0;
st480:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof480;
case 480:
	if ( (*( state.p)) == 95 )
		goto st481;
	goto st0;
st481:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof481;
case 481:
	if ( (*( state.p)) == 100 )
		goto st482;
	goto st0;
st482:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof482;
case 482:
	if ( (*( state.p)) == 101 )
		goto st483;
	goto st0;
st483:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof483;
case 483:
	if ( (*( state.p)) == 102 )
		goto st484;
	goto st0;
st484:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof484;
case 484:
	if ( (*( state.p)) == 101 )
		goto st485;
	goto st0;
st485:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof485;
case 485:
	if ( (*( state.p)) == 110 )
		goto st486;
	goto st0;
st486:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof486;
case 486:
	if ( (*( state.p)) == 115 )
		goto st487;
	goto st0;
st487:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof487;
case 487:
	if ( (*( state.p)) == 101 )
		goto st488;
	goto st0;
st488:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof488;
case 488:
	switch( (*( state.p)) ) {
		case 13: goto st489;
		case 32: goto st489;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st489;
	goto st0;
st489:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof489;
case 489:
	switch( (*( state.p)) ) {
		case 13: goto st489;
		case 32: goto st489;
		case 45: goto tr682;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr683;
	} else if ( (*( state.p)) >= 9 )
		goto st489;
	goto st0;
tr682:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st490;
st490:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof490;
case 490:
#line 8022 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr684;
	goto st0;
tr683:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st491;
tr684:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st491;
st491:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof491;
case 491:
#line 8046 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr685;
		case 32: goto tr685;
		case 46: goto tr686;
		case 59: goto tr687;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr684;
	} else if ( (*( state.p)) >= 9 )
		goto tr685;
	goto st0;
tr686:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st492;
st492:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof492;
case 492:
#line 8069 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr688;
	goto st0;
tr688:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st493;
st493:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof493;
case 493:
#line 8083 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr685;
		case 32: goto tr685;
		case 59: goto tr687;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr688;
	} else if ( (*( state.p)) >= 9 )
		goto tr685;
	goto st0;
st494:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof494;
case 494:
	switch( (*( state.p)) ) {
		case 107: goto st495;
		case 108: goto st553;
		case 116: goto st559;
	}
	goto st0;
st495:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof495;
case 495:
	if ( (*( state.p)) == 105 )
		goto st496;
	goto st0;
st496:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof496;
case 496:
	if ( (*( state.p)) == 110 )
		goto st497;
	goto st0;
st497:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof497;
case 497:
	switch( (*( state.p)) ) {
		case 13: goto st498;
		case 32: goto st498;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st498;
	goto st0;
st498:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof498;
case 498:
	switch( (*( state.p)) ) {
		case 13: goto st498;
		case 32: goto st498;
		case 34: goto tr695;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st498;
	goto st0;
tr696:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st499;
tr695:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
	goto st499;
tr698:
#line 144 "configparser.rl"
	{{ state.stack[ state.top++] = 499; goto st47;}}
	goto st499;
st499:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof499;
case 499:
#line 8162 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st500;
		case 92: goto tr698;
	}
	goto tr696;
st500:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof500;
case 500:
	switch( (*( state.p)) ) {
		case 13: goto tr699;
		case 32: goto tr699;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr699;
	goto st0;
tr699:
#line 166 "configparser.rl"
	{ skin.text = state.match; }
	goto st501;
st501:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof501;
case 501:
#line 8187 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st501;
		case 32: goto st501;
		case 98: goto st502;
		case 100: goto st547;
		case 110: goto st550;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st501;
	goto st0;
st502:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof502;
case 502:
	if ( (*( state.p)) == 114 )
		goto st503;
	goto st0;
st503:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof503;
case 503:
	if ( (*( state.p)) == 105 )
		goto st504;
	goto st0;
st504:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof504;
case 504:
	if ( (*( state.p)) == 103 )
		goto st505;
	goto st0;
st505:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof505;
case 505:
	if ( (*( state.p)) == 104 )
		goto st506;
	goto st0;
st506:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof506;
case 506:
	if ( (*( state.p)) == 116 )
		goto st507;
	goto st0;
st507:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof507;
case 507:
	switch( (*( state.p)) ) {
		case 13: goto tr709;
		case 32: goto tr709;
		case 95: goto tr710;
		case 98: goto tr711;
		case 99: goto tr712;
		case 103: goto tr713;
		case 109: goto tr714;
		case 114: goto tr715;
		case 119: goto tr716;
		case 121: goto tr717;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr709;
	goto st0;
tr709:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st508;
tr774:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st508;
st508:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof508;
case 508:
#line 8264 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st508;
		case 32: goto st508;
		case 98: goto st509;
		case 99: goto st516;
		case 103: goto st520;
		case 109: goto st525;
		case 114: goto st532;
		case 119: goto st535;
		case 121: goto st540;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st508;
	goto st0;
tr711:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st509;
tr776:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st509;
st509:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof509;
case 509:
#line 8291 "configparser.h"
	if ( (*( state.p)) == 108 )
		goto st510;
	goto st0;
st510:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof510;
case 510:
	switch( (*( state.p)) ) {
		case 97: goto st511;
		case 117: goto st514;
	}
	goto st0;
st511:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof511;
case 511:
	if ( (*( state.p)) == 99 )
		goto st512;
	goto st0;
st512:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof512;
case 512:
	if ( (*( state.p)) == 107 )
		goto st513;
	goto st0;
st513:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof513;
case 513:
	switch( (*( state.p)) ) {
		case 13: goto tr731;
		case 32: goto tr731;
		case 59: goto tr732;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr731;
	goto st0;
st514:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof514;
case 514:
	if ( (*( state.p)) == 101 )
		goto st515;
	goto st0;
st515:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof515;
case 515:
	switch( (*( state.p)) ) {
		case 13: goto tr734;
		case 32: goto tr734;
		case 59: goto tr735;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr734;
	goto st0;
tr712:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st516;
tr777:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st516;
st516:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof516;
case 516:
#line 8361 "configparser.h"
	if ( (*( state.p)) == 121 )
		goto st517;
	goto st0;
st517:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof517;
case 517:
	if ( (*( state.p)) == 97 )
		goto st518;
	goto st0;
st518:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof518;
case 518:
	if ( (*( state.p)) == 110 )
		goto st519;
	goto st0;
st519:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof519;
case 519:
	switch( (*( state.p)) ) {
		case 13: goto tr739;
		case 32: goto tr739;
		case 59: goto tr740;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr739;
	goto st0;
tr713:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st520;
tr778:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st520;
st520:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof520;
case 520:
#line 8403 "configparser.h"
	if ( (*( state.p)) == 114 )
		goto st521;
	goto st0;
st521:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof521;
case 521:
	if ( (*( state.p)) == 101 )
		goto st522;
	goto st0;
st522:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof522;
case 522:
	if ( (*( state.p)) == 101 )
		goto st523;
	goto st0;
st523:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof523;
case 523:
	if ( (*( state.p)) == 110 )
		goto st524;
	goto st0;
st524:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof524;
case 524:
	switch( (*( state.p)) ) {
		case 13: goto tr745;
		case 32: goto tr745;
		case 59: goto tr746;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr745;
	goto st0;
tr714:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st525;
tr779:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st525;
st525:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof525;
case 525:
#line 8452 "configparser.h"
	if ( (*( state.p)) == 97 )
		goto st526;
	goto st0;
st526:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof526;
case 526:
	if ( (*( state.p)) == 103 )
		goto st527;
	goto st0;
st527:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof527;
case 527:
	if ( (*( state.p)) == 101 )
		goto st528;
	goto st0;
st528:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof528;
case 528:
	if ( (*( state.p)) == 110 )
		goto st529;
	goto st0;
st529:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof529;
case 529:
	if ( (*( state.p)) == 116 )
		goto st530;
	goto st0;
st530:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof530;
case 530:
	if ( (*( state.p)) == 97 )
		goto st531;
	goto st0;
st531:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof531;
case 531:
	switch( (*( state.p)) ) {
		case 13: goto tr753;
		case 32: goto tr753;
		case 59: goto tr754;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr753;
	goto st0;
tr715:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st532;
tr780:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st532;
st532:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof532;
case 532:
#line 8515 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st533;
	goto st0;
st533:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof533;
case 533:
	if ( (*( state.p)) == 100 )
		goto st534;
	goto st0;
st534:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof534;
case 534:
	switch( (*( state.p)) ) {
		case 13: goto tr757;
		case 32: goto tr757;
		case 59: goto tr758;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr757;
	goto st0;
tr716:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st535;
tr781:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st535;
st535:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof535;
case 535:
#line 8550 "configparser.h"
	if ( (*( state.p)) == 104 )
		goto st536;
	goto st0;
st536:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof536;
case 536:
	if ( (*( state.p)) == 105 )
		goto st537;
	goto st0;
st537:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof537;
case 537:
	if ( (*( state.p)) == 116 )
		goto st538;
	goto st0;
st538:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof538;
case 538:
	if ( (*( state.p)) == 101 )
		goto st539;
	goto st0;
st539:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof539;
case 539:
	switch( (*( state.p)) ) {
		case 13: goto tr763;
		case 32: goto tr763;
		case 59: goto tr764;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr763;
	goto st0;
tr717:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st540;
tr782:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st540;
st540:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof540;
case 540:
#line 8599 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st541;
	goto st0;
st541:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof541;
case 541:
	if ( (*( state.p)) == 108 )
		goto st542;
	goto st0;
st542:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof542;
case 542:
	if ( (*( state.p)) == 108 )
		goto st543;
	goto st0;
st543:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof543;
case 543:
	if ( (*( state.p)) == 111 )
		goto st544;
	goto st0;
st544:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof544;
case 544:
	if ( (*( state.p)) == 119 )
		goto st545;
	goto st0;
st545:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof545;
case 545:
	switch( (*( state.p)) ) {
		case 13: goto tr770;
		case 32: goto tr770;
		case 59: goto tr771;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr770;
	goto st0;
tr710:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st546;
tr775:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st546;
st546:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof546;
case 546:
#line 8655 "configparser.h"
	switch( (*( state.p)) ) {
		case 98: goto st509;
		case 99: goto st516;
		case 103: goto st520;
		case 109: goto st525;
		case 114: goto st532;
		case 119: goto st535;
		case 121: goto st540;
	}
	goto st0;
st547:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof547;
case 547:
	if ( (*( state.p)) == 105 )
		goto st548;
	goto st0;
st548:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof548;
case 548:
	if ( (*( state.p)) == 109 )
		goto st549;
	goto st0;
st549:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof549;
case 549:
	switch( (*( state.p)) ) {
		case 13: goto tr774;
		case 32: goto tr774;
		case 95: goto tr775;
		case 98: goto tr776;
		case 99: goto tr777;
		case 103: goto tr778;
		case 109: goto tr779;
		case 114: goto tr780;
		case 119: goto tr781;
		case 121: goto tr782;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr774;
	goto st0;
st550:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof550;
case 550:
	if ( (*( state.p)) == 111 )
		goto st551;
	goto st0;
st551:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof551;
case 551:
	if ( (*( state.p)) == 110 )
		goto st552;
	goto st0;
st552:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof552;
case 552:
	if ( (*( state.p)) == 101 )
		goto st513;
	goto st0;
st553:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof553;
case 553:
	if ( (*( state.p)) == 111 )
		goto st554;
	goto st0;
st554:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof554;
case 554:
	if ( (*( state.p)) == 116 )
		goto st555;
	goto st0;
st555:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof555;
case 555:
	switch( (*( state.p)) ) {
		case 13: goto st556;
		case 32: goto st556;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st556;
	goto st0;
st556:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof556;
case 556:
	switch( (*( state.p)) ) {
		case 13: goto st556;
		case 32: goto st556;
		case 34: goto tr788;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st556;
	goto st0;
tr789:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st557;
tr788:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
	goto st557;
tr791:
#line 144 "configparser.rl"
	{{ state.stack[ state.top++] = 557; goto st47;}}
	goto st557;
st557:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof557;
case 557:
#line 8777 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st558;
		case 92: goto tr791;
	}
	goto tr789;
st558:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof558;
case 558:
	switch( (*( state.p)) ) {
		case 13: goto tr792;
		case 32: goto tr792;
		case 59: goto tr793;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr792;
	goto st0;
st559:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof559;
case 559:
	if ( (*( state.p)) == 97 )
		goto st560;
	goto st0;
st560:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof560;
case 560:
	if ( (*( state.p)) == 99 )
		goto st561;
	goto st0;
st561:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof561;
case 561:
	if ( (*( state.p)) == 107 )
		goto st562;
	goto st0;
st562:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof562;
case 562:
	if ( (*( state.p)) == 114 )
		goto st563;
	goto st0;
st563:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof563;
case 563:
	if ( (*( state.p)) == 97 )
		goto st564;
	goto st0;
st564:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof564;
case 564:
	if ( (*( state.p)) == 110 )
		goto st565;
	goto st0;
st565:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof565;
case 565:
	if ( (*( state.p)) == 103 )
		goto st566;
	goto st0;
st566:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof566;
case 566:
	if ( (*( state.p)) == 101 )
		goto st567;
	goto st0;
st567:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof567;
case 567:
	switch( (*( state.p)) ) {
		case 13: goto st568;
		case 32: goto st568;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st568;
	goto st0;
st568:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof568;
case 568:
	switch( (*( state.p)) ) {
		case 13: goto st568;
		case 32: goto st568;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr803;
	} else if ( (*( state.p)) >= 9 )
		goto st568;
	goto st0;
tr803:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st569;
tr805:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st569;
st569:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof569;
case 569:
#line 8896 "configparser.h"
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
st570:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof570;
case 570:
	if ( (*( state.p)) == 104 )
		goto st571;
	goto st0;
st571:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof571;
case 571:
	if ( (*( state.p)) == 114 )
		goto st572;
	goto st0;
st572:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof572;
case 572:
	if ( (*( state.p)) == 111 )
		goto st573;
	goto st0;
st573:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof573;
case 573:
	if ( (*( state.p)) == 119 )
		goto st574;
	goto st0;
st574:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof574;
case 574:
	if ( (*( state.p)) == 114 )
		goto st575;
	goto st0;
st575:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof575;
case 575:
	if ( (*( state.p)) == 97 )
		goto st576;
	goto st0;
st576:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof576;
case 576:
	if ( (*( state.p)) == 110 )
		goto st577;
	goto st0;
st577:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof577;
case 577:
	if ( (*( state.p)) == 103 )
		goto st578;
	goto st0;
st578:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof578;
case 578:
	if ( (*( state.p)) == 101 )
		goto st579;
	goto st0;
st579:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof579;
case 579:
	switch( (*( state.p)) ) {
		case 13: goto st580;
		case 32: goto st580;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st580;
	goto st0;
st580:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof580;
case 580:
	switch( (*( state.p)) ) {
		case 13: goto st580;
		case 32: goto st580;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr817;
	} else if ( (*( state.p)) >= 9 )
		goto st580;
	goto st0;
tr817:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st581;
tr819:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st581;
st581:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof581;
case 581:
#line 9016 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr818;
		case 32: goto tr818;
		case 59: goto tr820;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr819;
	} else if ( (*( state.p)) >= 9 )
		goto tr818;
	goto st0;
st582:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof582;
case 582:
	if ( (*( state.p)) == 115 )
		goto st583;
	goto st0;
st583:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof583;
case 583:
	if ( (*( state.p)) == 97 )
		goto st584;
	goto st0;
st584:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof584;
case 584:
	if ( (*( state.p)) == 98 )
		goto st585;
	goto st0;
st585:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof585;
case 585:
	if ( (*( state.p)) == 108 )
		goto st586;
	goto st0;
st586:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof586;
case 586:
	if ( (*( state.p)) == 101 )
		goto st587;
	goto st0;
st587:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof587;
case 587:
	switch( (*( state.p)) ) {
		case 13: goto tr826;
		case 32: goto tr826;
		case 59: goto tr827;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr826;
	goto st0;
tr588:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st588;
st588:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof588;
case 588:
#line 9085 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr828;
	goto st0;
tr828:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st589;
st589:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof589;
case 589:
#line 9099 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr587;
		case 32: goto tr587;
		case 59: goto tr589;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr828;
	} else if ( (*( state.p)) >= 9 )
		goto tr587;
	goto st0;
st590:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof590;
case 590:
	if ( (*( state.p)) == 105 )
		goto st591;
	goto st0;
st591:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof591;
case 591:
	if ( (*( state.p)) == 115 )
		goto st592;
	goto st0;
st592:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof592;
case 592:
	if ( (*( state.p)) == 111 )
		goto st593;
	goto st0;
st593:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof593;
case 593:
	if ( (*( state.p)) == 110 )
		goto st594;
	goto st0;
st594:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof594;
case 594:
	switch( (*( state.p)) ) {
		case 13: goto tr833;
		case 32: goto tr833;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr833;
	goto st0;
st595:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof595;
case 595:
	if ( (*( state.p)) == 108 )
		goto st596;
	goto st0;
st596:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof596;
case 596:
	if ( (*( state.p)) == 101 )
		goto st597;
	goto st0;
st597:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof597;
case 597:
	if ( (*( state.p)) == 101 )
		goto st598;
	goto st0;
st598:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof598;
case 598:
	if ( (*( state.p)) == 112 )
		goto st599;
	goto st0;
st599:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof599;
case 599:
	switch( (*( state.p)) ) {
		case 13: goto tr838;
		case 32: goto tr838;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr838;
	goto st0;
st600:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof600;
case 600:
	switch( (*( state.p)) ) {
		case 13: goto st600;
		case 32: goto st600;
		case 97: goto st601;
		case 99: goto st620;
		case 100: goto st635;
		case 110: goto st642;
		case 112: goto st649;
		case 115: goto st675;
		case 116: goto st745;
		case 118: goto st757;
		case 119: goto st766;
		case 125: goto tr849;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st600;
	goto st0;
st601:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof601;
case 601:
	if ( (*( state.p)) == 116 )
		goto st602;
	goto st0;
st602:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof602;
case 602:
	if ( (*( state.p)) == 116 )
		goto st603;
	goto st0;
st603:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof603;
case 603:
	if ( (*( state.p)) == 97 )
		goto st604;
	goto st0;
st604:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof604;
case 604:
	if ( (*( state.p)) == 99 )
		goto st605;
	goto st0;
st605:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof605;
case 605:
	if ( (*( state.p)) == 107 )
		goto st606;
	goto st0;
st606:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof606;
case 606:
	switch( (*( state.p)) ) {
		case 13: goto st607;
		case 32: goto st607;
		case 95: goto st787;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st607;
	goto st0;
st607:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof607;
case 607:
	switch( (*( state.p)) ) {
		case 13: goto st607;
		case 32: goto st607;
		case 112: goto st608;
		case 115: goto st782;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st607;
	goto st0;
st608:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof608;
case 608:
	switch( (*( state.p)) ) {
		case 104: goto st609;
		case 111: goto st777;
	}
	goto st0;
st609:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof609;
case 609:
	if ( (*( state.p)) == 121 )
		goto st610;
	goto st0;
st610:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof610;
case 610:
	if ( (*( state.p)) == 115 )
		goto st611;
	goto st0;
st611:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof611;
case 611:
	if ( (*( state.p)) == 105 )
		goto st612;
	goto st0;
st612:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof612;
case 612:
	if ( (*( state.p)) == 99 )
		goto st613;
	goto st0;
st613:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof613;
case 613:
	if ( (*( state.p)) == 97 )
		goto st614;
	goto st0;
st614:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof614;
case 614:
	if ( (*( state.p)) == 108 )
		goto st615;
	goto st0;
st615:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof615;
case 615:
	switch( (*( state.p)) ) {
		case 13: goto tr867;
		case 32: goto tr867;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr867;
	goto st0;
tr867:
#line 171 "configparser.rl"
	{ dmgval.type = damage::type_t::physical; }
	goto st616;
tr1098:
#line 173 "configparser.rl"
	{ dmgval.type = damage::type_t::poison; }
	goto st616;
tr1103:
#line 172 "configparser.rl"
	{ dmgval.type = damage::type_t::sleep; }
	goto st616;
st616:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof616;
case 616:
#line 9348 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st616;
		case 32: goto st616;
		case 45: goto tr869;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr870;
	} else if ( (*( state.p)) >= 9 )
		goto st616;
	goto st0;
tr869:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st617;
st617:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof617;
case 617:
#line 9374 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr871;
	goto st0;
tr870:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st618;
tr871:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st618;
st618:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof618;
case 618:
#line 9398 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr872;
		case 32: goto tr872;
		case 46: goto tr873;
		case 59: goto tr874;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr871;
	} else if ( (*( state.p)) >= 9 )
		goto tr872;
	goto st0;
tr849:
#line 344 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st619;
tr872:
#line 177 "configparser.rl"
	{ dmgval.val = toreal(state.match); }
#line 332 "configparser.rl"
	{ ter.attacks.add(dmgval); }
	goto st619;
tr886:
#line 334 "configparser.rl"
	{ ter.charges = toint(state.match); }
	goto st619;
tr894:
#line 324 "configparser.rl"
	{ ter.count = toint(state.match); }
	goto st619;
tr903:
#line 331 "configparser.rl"
	{ ter.decay = toint(state.match); }
	goto st619;
tr914:
#line 325 "configparser.rl"
	{ ter.name = state.match; }
	goto st619;
tr933:
#line 317 "configparser.rl"
	{ ter.placement = Terrain::placement_t::corner; }
	goto st619;
tr939:
#line 315 "configparser.rl"
	{ ter.placement = Terrain::placement_t::floor; }
	goto st619;
tr945:
#line 316 "configparser.rl"
	{ ter.placement = Terrain::placement_t::water; }
	goto st619;
tr988:
#line 326 "configparser.rl"
	{ ter.skin = skin; }
	goto st619;
tr991:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 326 "configparser.rl"
	{ ter.skin = skin; }
	goto st619;
tr996:
#line 158 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 326 "configparser.rl"
	{ ter.skin = skin; }
	goto st619;
tr1002:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 326 "configparser.rl"
	{ ter.skin = skin; }
	goto st619;
tr1010:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 326 "configparser.rl"
	{ ter.skin = skin; }
	goto st619;
tr1014:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 326 "configparser.rl"
	{ ter.skin = skin; }
	goto st619;
tr1020:
#line 159 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 326 "configparser.rl"
	{ ter.skin = skin; }
	goto st619;
tr1027:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 326 "configparser.rl"
	{ ter.skin = skin; }
	goto st619;
tr1049:
#line 328 "configparser.rl"
	{ ter.stairs = toint(state.match); }
	goto st619;
tr1055:
#line 333 "configparser.rl"
	{ ter.sticky = true; }
	goto st619;
tr1071:
#line 321 "configparser.rl"
	{ ter.tunnel_y = toint(state.match); }
	goto st619;
tr1081:
#line 329 "configparser.rl"
	{ ter.viewblock = true; }
	goto st619;
tr1091:
#line 330 "configparser.rl"
	{ ter.walkblock = true; }
	goto st619;
tr1111:
#line 336 "configparser.rl"
	{ ter.attack_level = toint(state.match); }
	goto st619;
st619:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof619;
case 619:
#line 9523 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st619;
		case 32: goto st619;
		case 59: goto st1526;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st619;
	goto st0;
tr874:
#line 177 "configparser.rl"
	{ dmgval.val = toreal(state.match); }
#line 332 "configparser.rl"
	{ ter.attacks.add(dmgval); }
	goto st1526;
tr888:
#line 334 "configparser.rl"
	{ ter.charges = toint(state.match); }
	goto st1526;
tr896:
#line 324 "configparser.rl"
	{ ter.count = toint(state.match); }
	goto st1526;
tr905:
#line 331 "configparser.rl"
	{ ter.decay = toint(state.match); }
	goto st1526;
tr915:
#line 325 "configparser.rl"
	{ ter.name = state.match; }
	goto st1526;
tr934:
#line 317 "configparser.rl"
	{ ter.placement = Terrain::placement_t::corner; }
	goto st1526;
tr940:
#line 315 "configparser.rl"
	{ ter.placement = Terrain::placement_t::floor; }
	goto st1526;
tr946:
#line 316 "configparser.rl"
	{ ter.placement = Terrain::placement_t::water; }
	goto st1526;
tr989:
#line 326 "configparser.rl"
	{ ter.skin = skin; }
	goto st1526;
tr992:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 326 "configparser.rl"
	{ ter.skin = skin; }
	goto st1526;
tr997:
#line 158 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 326 "configparser.rl"
	{ ter.skin = skin; }
	goto st1526;
tr1003:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 326 "configparser.rl"
	{ ter.skin = skin; }
	goto st1526;
tr1011:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 326 "configparser.rl"
	{ ter.skin = skin; }
	goto st1526;
tr1015:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 326 "configparser.rl"
	{ ter.skin = skin; }
	goto st1526;
tr1021:
#line 159 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 326 "configparser.rl"
	{ ter.skin = skin; }
	goto st1526;
tr1028:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 326 "configparser.rl"
	{ ter.skin = skin; }
	goto st1526;
tr1051:
#line 328 "configparser.rl"
	{ ter.stairs = toint(state.match); }
	goto st1526;
tr1056:
#line 333 "configparser.rl"
	{ ter.sticky = true; }
	goto st1526;
tr1072:
#line 321 "configparser.rl"
	{ ter.tunnel_y = toint(state.match); }
	goto st1526;
tr1082:
#line 329 "configparser.rl"
	{ ter.viewblock = true; }
	goto st1526;
tr1092:
#line 330 "configparser.rl"
	{ ter.walkblock = true; }
	goto st1526;
tr1113:
#line 336 "configparser.rl"
	{ ter.attack_level = toint(state.match); }
	goto st1526;
st1526:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1526;
case 1526:
#line 9640 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st600;
		case 32: goto st600;
		case 97: goto st601;
		case 99: goto st620;
		case 100: goto st635;
		case 110: goto st642;
		case 112: goto st649;
		case 115: goto st675;
		case 116: goto st745;
		case 118: goto st757;
		case 119: goto st766;
		case 125: goto tr849;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st600;
	goto st0;
st620:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof620;
case 620:
	switch( (*( state.p)) ) {
		case 104: goto st621;
		case 111: goto st629;
	}
	goto st0;
st621:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof621;
case 621:
	if ( (*( state.p)) == 97 )
		goto st622;
	goto st0;
st622:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof622;
case 622:
	if ( (*( state.p)) == 114 )
		goto st623;
	goto st0;
st623:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof623;
case 623:
	if ( (*( state.p)) == 103 )
		goto st624;
	goto st0;
st624:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof624;
case 624:
	if ( (*( state.p)) == 101 )
		goto st625;
	goto st0;
st625:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof625;
case 625:
	if ( (*( state.p)) == 115 )
		goto st626;
	goto st0;
st626:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof626;
case 626:
	switch( (*( state.p)) ) {
		case 13: goto st627;
		case 32: goto st627;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st627;
	goto st0;
st627:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof627;
case 627:
	switch( (*( state.p)) ) {
		case 13: goto st627;
		case 32: goto st627;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr885;
	} else if ( (*( state.p)) >= 9 )
		goto st627;
	goto st0;
tr885:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st628;
tr887:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st628;
st628:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof628;
case 628:
#line 9747 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr886;
		case 32: goto tr886;
		case 59: goto tr888;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr887;
	} else if ( (*( state.p)) >= 9 )
		goto tr886;
	goto st0;
st629:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof629;
case 629:
	if ( (*( state.p)) == 117 )
		goto st630;
	goto st0;
st630:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof630;
case 630:
	if ( (*( state.p)) == 110 )
		goto st631;
	goto st0;
st631:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof631;
case 631:
	if ( (*( state.p)) == 116 )
		goto st632;
	goto st0;
st632:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof632;
case 632:
	switch( (*( state.p)) ) {
		case 13: goto st633;
		case 32: goto st633;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st633;
	goto st0;
st633:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof633;
case 633:
	switch( (*( state.p)) ) {
		case 13: goto st633;
		case 32: goto st633;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr893;
	} else if ( (*( state.p)) >= 9 )
		goto st633;
	goto st0;
tr893:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st634;
tr895:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st634;
st634:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof634;
case 634:
#line 9825 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr894;
		case 32: goto tr894;
		case 59: goto tr896;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr895;
	} else if ( (*( state.p)) >= 9 )
		goto tr894;
	goto st0;
st635:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof635;
case 635:
	if ( (*( state.p)) == 101 )
		goto st636;
	goto st0;
st636:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof636;
case 636:
	if ( (*( state.p)) == 99 )
		goto st637;
	goto st0;
st637:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof637;
case 637:
	if ( (*( state.p)) == 97 )
		goto st638;
	goto st0;
st638:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof638;
case 638:
	if ( (*( state.p)) == 121 )
		goto st639;
	goto st0;
st639:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof639;
case 639:
	switch( (*( state.p)) ) {
		case 13: goto st640;
		case 32: goto st640;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st640;
	goto st0;
st640:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof640;
case 640:
	switch( (*( state.p)) ) {
		case 13: goto st640;
		case 32: goto st640;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr902;
	} else if ( (*( state.p)) >= 9 )
		goto st640;
	goto st0;
tr902:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st641;
tr904:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st641;
st641:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof641;
case 641:
#line 9910 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr903;
		case 32: goto tr903;
		case 59: goto tr905;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr904;
	} else if ( (*( state.p)) >= 9 )
		goto tr903;
	goto st0;
st642:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof642;
case 642:
	if ( (*( state.p)) == 97 )
		goto st643;
	goto st0;
st643:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof643;
case 643:
	if ( (*( state.p)) == 109 )
		goto st644;
	goto st0;
st644:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof644;
case 644:
	if ( (*( state.p)) == 101 )
		goto st645;
	goto st0;
st645:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof645;
case 645:
	switch( (*( state.p)) ) {
		case 13: goto st646;
		case 32: goto st646;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st646;
	goto st0;
st646:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof646;
case 646:
	switch( (*( state.p)) ) {
		case 13: goto st646;
		case 32: goto st646;
		case 34: goto tr910;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st646;
	goto st0;
tr911:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st647;
tr910:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
	goto st647;
tr913:
#line 144 "configparser.rl"
	{{ state.stack[ state.top++] = 647; goto st47;}}
	goto st647;
st647:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof647;
case 647:
#line 9986 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st648;
		case 92: goto tr913;
	}
	goto tr911;
st648:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof648;
case 648:
	switch( (*( state.p)) ) {
		case 13: goto tr914;
		case 32: goto tr914;
		case 59: goto tr915;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr914;
	goto st0;
st649:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof649;
case 649:
	if ( (*( state.p)) == 108 )
		goto st650;
	goto st0;
st650:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof650;
case 650:
	if ( (*( state.p)) == 97 )
		goto st651;
	goto st0;
st651:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof651;
case 651:
	if ( (*( state.p)) == 99 )
		goto st652;
	goto st0;
st652:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof652;
case 652:
	if ( (*( state.p)) == 101 )
		goto st653;
	goto st0;
st653:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof653;
case 653:
	if ( (*( state.p)) == 109 )
		goto st654;
	goto st0;
st654:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof654;
case 654:
	if ( (*( state.p)) == 101 )
		goto st655;
	goto st0;
st655:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof655;
case 655:
	if ( (*( state.p)) == 110 )
		goto st656;
	goto st0;
st656:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof656;
case 656:
	if ( (*( state.p)) == 116 )
		goto st657;
	goto st0;
st657:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof657;
case 657:
	switch( (*( state.p)) ) {
		case 13: goto st658;
		case 32: goto st658;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st658;
	goto st0;
st658:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof658;
case 658:
	switch( (*( state.p)) ) {
		case 13: goto st658;
		case 32: goto st658;
		case 99: goto st659;
		case 102: goto st665;
		case 119: goto st670;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st658;
	goto st0;
st659:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof659;
case 659:
	if ( (*( state.p)) == 111 )
		goto st660;
	goto st0;
st660:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof660;
case 660:
	if ( (*( state.p)) == 114 )
		goto st661;
	goto st0;
st661:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof661;
case 661:
	if ( (*( state.p)) == 110 )
		goto st662;
	goto st0;
st662:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof662;
case 662:
	if ( (*( state.p)) == 101 )
		goto st663;
	goto st0;
st663:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof663;
case 663:
	if ( (*( state.p)) == 114 )
		goto st664;
	goto st0;
st664:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof664;
case 664:
	switch( (*( state.p)) ) {
		case 13: goto tr933;
		case 32: goto tr933;
		case 59: goto tr934;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr933;
	goto st0;
st665:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof665;
case 665:
	if ( (*( state.p)) == 108 )
		goto st666;
	goto st0;
st666:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof666;
case 666:
	if ( (*( state.p)) == 111 )
		goto st667;
	goto st0;
st667:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof667;
case 667:
	if ( (*( state.p)) == 111 )
		goto st668;
	goto st0;
st668:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof668;
case 668:
	if ( (*( state.p)) == 114 )
		goto st669;
	goto st0;
st669:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof669;
case 669:
	switch( (*( state.p)) ) {
		case 13: goto tr939;
		case 32: goto tr939;
		case 59: goto tr940;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr939;
	goto st0;
st670:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof670;
case 670:
	if ( (*( state.p)) == 97 )
		goto st671;
	goto st0;
st671:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof671;
case 671:
	if ( (*( state.p)) == 116 )
		goto st672;
	goto st0;
st672:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof672;
case 672:
	if ( (*( state.p)) == 101 )
		goto st673;
	goto st0;
st673:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof673;
case 673:
	if ( (*( state.p)) == 114 )
		goto st674;
	goto st0;
st674:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof674;
case 674:
	switch( (*( state.p)) ) {
		case 13: goto tr945;
		case 32: goto tr945;
		case 59: goto tr946;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr945;
	goto st0;
st675:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof675;
case 675:
	switch( (*( state.p)) ) {
		case 107: goto st676;
		case 116: goto st734;
	}
	goto st0;
st676:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof676;
case 676:
	if ( (*( state.p)) == 105 )
		goto st677;
	goto st0;
st677:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof677;
case 677:
	if ( (*( state.p)) == 110 )
		goto st678;
	goto st0;
st678:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof678;
case 678:
	switch( (*( state.p)) ) {
		case 13: goto st679;
		case 32: goto st679;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st679;
	goto st0;
st679:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof679;
case 679:
	switch( (*( state.p)) ) {
		case 13: goto st679;
		case 32: goto st679;
		case 34: goto tr952;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st679;
	goto st0;
tr953:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st680;
tr952:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
	goto st680;
tr955:
#line 144 "configparser.rl"
	{{ state.stack[ state.top++] = 680; goto st47;}}
	goto st680;
st680:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof680;
case 680:
#line 10278 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st681;
		case 92: goto tr955;
	}
	goto tr953;
st681:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof681;
case 681:
	switch( (*( state.p)) ) {
		case 13: goto tr956;
		case 32: goto tr956;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr956;
	goto st0;
tr956:
#line 166 "configparser.rl"
	{ skin.text = state.match; }
	goto st682;
st682:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof682;
case 682:
#line 10303 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st682;
		case 32: goto st682;
		case 98: goto st683;
		case 100: goto st728;
		case 110: goto st731;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st682;
	goto st0;
st683:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof683;
case 683:
	if ( (*( state.p)) == 114 )
		goto st684;
	goto st0;
st684:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof684;
case 684:
	if ( (*( state.p)) == 105 )
		goto st685;
	goto st0;
st685:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof685;
case 685:
	if ( (*( state.p)) == 103 )
		goto st686;
	goto st0;
st686:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof686;
case 686:
	if ( (*( state.p)) == 104 )
		goto st687;
	goto st0;
st687:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof687;
case 687:
	if ( (*( state.p)) == 116 )
		goto st688;
	goto st0;
st688:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof688;
case 688:
	switch( (*( state.p)) ) {
		case 13: goto tr966;
		case 32: goto tr966;
		case 95: goto tr967;
		case 98: goto tr968;
		case 99: goto tr969;
		case 103: goto tr970;
		case 109: goto tr971;
		case 114: goto tr972;
		case 119: goto tr973;
		case 121: goto tr974;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr966;
	goto st0;
tr966:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st689;
tr1031:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st689;
st689:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof689;
case 689:
#line 10380 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st689;
		case 32: goto st689;
		case 98: goto st690;
		case 99: goto st697;
		case 103: goto st701;
		case 109: goto st706;
		case 114: goto st713;
		case 119: goto st716;
		case 121: goto st721;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st689;
	goto st0;
tr968:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st690;
tr1033:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st690;
st690:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof690;
case 690:
#line 10407 "configparser.h"
	if ( (*( state.p)) == 108 )
		goto st691;
	goto st0;
st691:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof691;
case 691:
	switch( (*( state.p)) ) {
		case 97: goto st692;
		case 117: goto st695;
	}
	goto st0;
st692:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof692;
case 692:
	if ( (*( state.p)) == 99 )
		goto st693;
	goto st0;
st693:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof693;
case 693:
	if ( (*( state.p)) == 107 )
		goto st694;
	goto st0;
st694:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof694;
case 694:
	switch( (*( state.p)) ) {
		case 13: goto tr988;
		case 32: goto tr988;
		case 59: goto tr989;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr988;
	goto st0;
st695:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof695;
case 695:
	if ( (*( state.p)) == 101 )
		goto st696;
	goto st0;
st696:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof696;
case 696:
	switch( (*( state.p)) ) {
		case 13: goto tr991;
		case 32: goto tr991;
		case 59: goto tr992;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr991;
	goto st0;
tr969:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st697;
tr1034:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st697;
st697:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof697;
case 697:
#line 10477 "configparser.h"
	if ( (*( state.p)) == 121 )
		goto st698;
	goto st0;
st698:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof698;
case 698:
	if ( (*( state.p)) == 97 )
		goto st699;
	goto st0;
st699:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof699;
case 699:
	if ( (*( state.p)) == 110 )
		goto st700;
	goto st0;
st700:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof700;
case 700:
	switch( (*( state.p)) ) {
		case 13: goto tr996;
		case 32: goto tr996;
		case 59: goto tr997;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr996;
	goto st0;
tr970:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st701;
tr1035:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st701;
st701:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof701;
case 701:
#line 10519 "configparser.h"
	if ( (*( state.p)) == 114 )
		goto st702;
	goto st0;
st702:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof702;
case 702:
	if ( (*( state.p)) == 101 )
		goto st703;
	goto st0;
st703:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof703;
case 703:
	if ( (*( state.p)) == 101 )
		goto st704;
	goto st0;
st704:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof704;
case 704:
	if ( (*( state.p)) == 110 )
		goto st705;
	goto st0;
st705:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof705;
case 705:
	switch( (*( state.p)) ) {
		case 13: goto tr1002;
		case 32: goto tr1002;
		case 59: goto tr1003;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1002;
	goto st0;
tr971:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st706;
tr1036:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st706;
st706:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof706;
case 706:
#line 10568 "configparser.h"
	if ( (*( state.p)) == 97 )
		goto st707;
	goto st0;
st707:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof707;
case 707:
	if ( (*( state.p)) == 103 )
		goto st708;
	goto st0;
st708:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof708;
case 708:
	if ( (*( state.p)) == 101 )
		goto st709;
	goto st0;
st709:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof709;
case 709:
	if ( (*( state.p)) == 110 )
		goto st710;
	goto st0;
st710:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof710;
case 710:
	if ( (*( state.p)) == 116 )
		goto st711;
	goto st0;
st711:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof711;
case 711:
	if ( (*( state.p)) == 97 )
		goto st712;
	goto st0;
st712:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof712;
case 712:
	switch( (*( state.p)) ) {
		case 13: goto tr1010;
		case 32: goto tr1010;
		case 59: goto tr1011;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1010;
	goto st0;
tr972:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st713;
tr1037:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st713;
st713:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof713;
case 713:
#line 10631 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st714;
	goto st0;
st714:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof714;
case 714:
	if ( (*( state.p)) == 100 )
		goto st715;
	goto st0;
st715:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof715;
case 715:
	switch( (*( state.p)) ) {
		case 13: goto tr1014;
		case 32: goto tr1014;
		case 59: goto tr1015;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1014;
	goto st0;
tr973:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st716;
tr1038:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st716;
st716:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof716;
case 716:
#line 10666 "configparser.h"
	if ( (*( state.p)) == 104 )
		goto st717;
	goto st0;
st717:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof717;
case 717:
	if ( (*( state.p)) == 105 )
		goto st718;
	goto st0;
st718:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof718;
case 718:
	if ( (*( state.p)) == 116 )
		goto st719;
	goto st0;
st719:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof719;
case 719:
	if ( (*( state.p)) == 101 )
		goto st720;
	goto st0;
st720:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof720;
case 720:
	switch( (*( state.p)) ) {
		case 13: goto tr1020;
		case 32: goto tr1020;
		case 59: goto tr1021;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1020;
	goto st0;
tr974:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st721;
tr1039:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st721;
st721:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof721;
case 721:
#line 10715 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st722;
	goto st0;
st722:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof722;
case 722:
	if ( (*( state.p)) == 108 )
		goto st723;
	goto st0;
st723:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof723;
case 723:
	if ( (*( state.p)) == 108 )
		goto st724;
	goto st0;
st724:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof724;
case 724:
	if ( (*( state.p)) == 111 )
		goto st725;
	goto st0;
st725:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof725;
case 725:
	if ( (*( state.p)) == 119 )
		goto st726;
	goto st0;
st726:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof726;
case 726:
	switch( (*( state.p)) ) {
		case 13: goto tr1027;
		case 32: goto tr1027;
		case 59: goto tr1028;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1027;
	goto st0;
tr967:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st727;
tr1032:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st727;
st727:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof727;
case 727:
#line 10771 "configparser.h"
	switch( (*( state.p)) ) {
		case 98: goto st690;
		case 99: goto st697;
		case 103: goto st701;
		case 109: goto st706;
		case 114: goto st713;
		case 119: goto st716;
		case 121: goto st721;
	}
	goto st0;
st728:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof728;
case 728:
	if ( (*( state.p)) == 105 )
		goto st729;
	goto st0;
st729:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof729;
case 729:
	if ( (*( state.p)) == 109 )
		goto st730;
	goto st0;
st730:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof730;
case 730:
	switch( (*( state.p)) ) {
		case 13: goto tr1031;
		case 32: goto tr1031;
		case 95: goto tr1032;
		case 98: goto tr1033;
		case 99: goto tr1034;
		case 103: goto tr1035;
		case 109: goto tr1036;
		case 114: goto tr1037;
		case 119: goto tr1038;
		case 121: goto tr1039;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1031;
	goto st0;
st731:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof731;
case 731:
	if ( (*( state.p)) == 111 )
		goto st732;
	goto st0;
st732:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof732;
case 732:
	if ( (*( state.p)) == 110 )
		goto st733;
	goto st0;
st733:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof733;
case 733:
	if ( (*( state.p)) == 101 )
		goto st694;
	goto st0;
st734:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof734;
case 734:
	switch( (*( state.p)) ) {
		case 97: goto st735;
		case 105: goto st741;
	}
	goto st0;
st735:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof735;
case 735:
	if ( (*( state.p)) == 105 )
		goto st736;
	goto st0;
st736:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof736;
case 736:
	if ( (*( state.p)) == 114 )
		goto st737;
	goto st0;
st737:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof737;
case 737:
	if ( (*( state.p)) == 115 )
		goto st738;
	goto st0;
st738:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof738;
case 738:
	switch( (*( state.p)) ) {
		case 13: goto st739;
		case 32: goto st739;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st739;
	goto st0;
st739:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof739;
case 739:
	switch( (*( state.p)) ) {
		case 13: goto st739;
		case 32: goto st739;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1048;
	} else if ( (*( state.p)) >= 9 )
		goto st739;
	goto st0;
tr1048:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st740;
tr1050:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st740;
st740:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof740;
case 740:
#line 10911 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1049;
		case 32: goto tr1049;
		case 59: goto tr1051;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1050;
	} else if ( (*( state.p)) >= 9 )
		goto tr1049;
	goto st0;
st741:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof741;
case 741:
	if ( (*( state.p)) == 99 )
		goto st742;
	goto st0;
st742:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof742;
case 742:
	if ( (*( state.p)) == 107 )
		goto st743;
	goto st0;
st743:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof743;
case 743:
	if ( (*( state.p)) == 121 )
		goto st744;
	goto st0;
st744:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof744;
case 744:
	switch( (*( state.p)) ) {
		case 13: goto tr1055;
		case 32: goto tr1055;
		case 59: goto tr1056;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1055;
	goto st0;
st745:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof745;
case 745:
	if ( (*( state.p)) == 117 )
		goto st746;
	goto st0;
st746:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof746;
case 746:
	if ( (*( state.p)) == 110 )
		goto st747;
	goto st0;
st747:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof747;
case 747:
	if ( (*( state.p)) == 110 )
		goto st748;
	goto st0;
st748:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof748;
case 748:
	if ( (*( state.p)) == 101 )
		goto st749;
	goto st0;
st749:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof749;
case 749:
	if ( (*( state.p)) == 108 )
		goto st750;
	goto st0;
st750:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof750;
case 750:
	switch( (*( state.p)) ) {
		case 13: goto st751;
		case 32: goto st751;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st751;
	goto st0;
st751:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof751;
case 751:
	switch( (*( state.p)) ) {
		case 13: goto st751;
		case 32: goto st751;
		case 45: goto tr1063;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1064;
	} else if ( (*( state.p)) >= 9 )
		goto st751;
	goto st0;
tr1063:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st752;
st752:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof752;
case 752:
#line 11031 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr1065;
	goto st0;
tr1064:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st753;
tr1065:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st753;
st753:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof753;
case 753:
#line 11055 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1066;
		case 32: goto tr1066;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1065;
	} else if ( (*( state.p)) >= 9 )
		goto tr1066;
	goto st0;
tr1066:
#line 320 "configparser.rl"
	{ ter.tunnel_x = toint(state.match); }
	goto st754;
st754:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof754;
case 754:
#line 11074 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st754;
		case 32: goto st754;
		case 45: goto tr1068;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1069;
	} else if ( (*( state.p)) >= 9 )
		goto st754;
	goto st0;
tr1068:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st755;
st755:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof755;
case 755:
#line 11100 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr1070;
	goto st0;
tr1069:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st756;
tr1070:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st756;
st756:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof756;
case 756:
#line 11124 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1071;
		case 32: goto tr1071;
		case 59: goto tr1072;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1070;
	} else if ( (*( state.p)) >= 9 )
		goto tr1071;
	goto st0;
st757:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof757;
case 757:
	if ( (*( state.p)) == 105 )
		goto st758;
	goto st0;
st758:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof758;
case 758:
	if ( (*( state.p)) == 101 )
		goto st759;
	goto st0;
st759:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof759;
case 759:
	if ( (*( state.p)) == 119 )
		goto st760;
	goto st0;
st760:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof760;
case 760:
	if ( (*( state.p)) == 98 )
		goto st761;
	goto st0;
st761:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof761;
case 761:
	if ( (*( state.p)) == 108 )
		goto st762;
	goto st0;
st762:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof762;
case 762:
	if ( (*( state.p)) == 111 )
		goto st763;
	goto st0;
st763:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof763;
case 763:
	if ( (*( state.p)) == 99 )
		goto st764;
	goto st0;
st764:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof764;
case 764:
	if ( (*( state.p)) == 107 )
		goto st765;
	goto st0;
st765:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof765;
case 765:
	switch( (*( state.p)) ) {
		case 13: goto tr1081;
		case 32: goto tr1081;
		case 59: goto tr1082;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1081;
	goto st0;
st766:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof766;
case 766:
	if ( (*( state.p)) == 97 )
		goto st767;
	goto st0;
st767:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof767;
case 767:
	if ( (*( state.p)) == 108 )
		goto st768;
	goto st0;
st768:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof768;
case 768:
	if ( (*( state.p)) == 107 )
		goto st769;
	goto st0;
st769:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof769;
case 769:
	if ( (*( state.p)) == 98 )
		goto st770;
	goto st0;
st770:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof770;
case 770:
	if ( (*( state.p)) == 108 )
		goto st771;
	goto st0;
st771:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof771;
case 771:
	if ( (*( state.p)) == 111 )
		goto st772;
	goto st0;
st772:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof772;
case 772:
	if ( (*( state.p)) == 99 )
		goto st773;
	goto st0;
st773:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof773;
case 773:
	if ( (*( state.p)) == 107 )
		goto st774;
	goto st0;
st774:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof774;
case 774:
	switch( (*( state.p)) ) {
		case 13: goto tr1091;
		case 32: goto tr1091;
		case 59: goto tr1092;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1091;
	goto st0;
tr873:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st775;
st775:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof775;
case 775:
#line 11282 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr1093;
	goto st0;
tr1093:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st776;
st776:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof776;
case 776:
#line 11296 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr872;
		case 32: goto tr872;
		case 59: goto tr874;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1093;
	} else if ( (*( state.p)) >= 9 )
		goto tr872;
	goto st0;
st777:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof777;
case 777:
	if ( (*( state.p)) == 105 )
		goto st778;
	goto st0;
st778:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof778;
case 778:
	if ( (*( state.p)) == 115 )
		goto st779;
	goto st0;
st779:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof779;
case 779:
	if ( (*( state.p)) == 111 )
		goto st780;
	goto st0;
st780:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof780;
case 780:
	if ( (*( state.p)) == 110 )
		goto st781;
	goto st0;
st781:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof781;
case 781:
	switch( (*( state.p)) ) {
		case 13: goto tr1098;
		case 32: goto tr1098;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1098;
	goto st0;
st782:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof782;
case 782:
	if ( (*( state.p)) == 108 )
		goto st783;
	goto st0;
st783:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof783;
case 783:
	if ( (*( state.p)) == 101 )
		goto st784;
	goto st0;
st784:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof784;
case 784:
	if ( (*( state.p)) == 101 )
		goto st785;
	goto st0;
st785:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof785;
case 785:
	if ( (*( state.p)) == 112 )
		goto st786;
	goto st0;
st786:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof786;
case 786:
	switch( (*( state.p)) ) {
		case 13: goto tr1103;
		case 32: goto tr1103;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1103;
	goto st0;
st787:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof787;
case 787:
	if ( (*( state.p)) == 108 )
		goto st788;
	goto st0;
st788:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof788;
case 788:
	if ( (*( state.p)) == 101 )
		goto st789;
	goto st0;
st789:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof789;
case 789:
	if ( (*( state.p)) == 118 )
		goto st790;
	goto st0;
st790:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof790;
case 790:
	if ( (*( state.p)) == 101 )
		goto st791;
	goto st0;
st791:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof791;
case 791:
	if ( (*( state.p)) == 108 )
		goto st792;
	goto st0;
st792:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof792;
case 792:
	switch( (*( state.p)) ) {
		case 13: goto st793;
		case 32: goto st793;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st793;
	goto st0;
st793:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof793;
case 793:
	switch( (*( state.p)) ) {
		case 13: goto st793;
		case 32: goto st793;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1110;
	} else if ( (*( state.p)) >= 9 )
		goto st793;
	goto st0;
tr1110:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st794;
tr1112:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st794;
st794:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof794;
case 794:
#line 11466 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1111;
		case 32: goto tr1111;
		case 59: goto tr1113;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1112;
	} else if ( (*( state.p)) >= 9 )
		goto tr1111;
	goto st0;
st795:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof795;
case 795:
	switch( (*( state.p)) ) {
		case 13: goto st795;
		case 32: goto st795;
		case 100: goto st796;
		case 102: goto st823;
		case 108: goto st1276;
		case 115: goto st1289;
		case 119: goto st1357;
		case 125: goto tr1120;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st795;
	goto st0;
st796:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof796;
case 796:
	if ( (*( state.p)) == 101 )
		goto st797;
	goto st0;
st797:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof797;
case 797:
	if ( (*( state.p)) == 101 )
		goto st798;
	goto st0;
st798:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof798;
case 798:
	if ( (*( state.p)) == 112 )
		goto st799;
	goto st0;
st799:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof799;
case 799:
	if ( (*( state.p)) == 95 )
		goto st800;
	goto st0;
st800:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof800;
case 800:
	if ( (*( state.p)) == 119 )
		goto st801;
	goto st0;
st801:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof801;
case 801:
	if ( (*( state.p)) == 97 )
		goto st802;
	goto st0;
st802:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof802;
case 802:
	if ( (*( state.p)) == 116 )
		goto st803;
	goto st0;
st803:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof803;
case 803:
	if ( (*( state.p)) == 101 )
		goto st804;
	goto st0;
st804:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof804;
case 804:
	if ( (*( state.p)) == 114 )
		goto st805;
	goto st0;
st805:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof805;
case 805:
	switch( (*( state.p)) ) {
		case 13: goto st806;
		case 32: goto st806;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st806;
	goto st0;
st806:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof806;
case 806:
	switch( (*( state.p)) ) {
		case 13: goto st806;
		case 32: goto st806;
		case 34: goto tr1131;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st806;
	goto st0;
tr1132:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st807;
tr1131:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
	goto st807;
tr1134:
#line 144 "configparser.rl"
	{{ state.stack[ state.top++] = 807; goto st47;}}
	goto st807;
st807:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof807;
case 807:
#line 11601 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st808;
		case 92: goto tr1134;
	}
	goto tr1132;
st808:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof808;
case 808:
	switch( (*( state.p)) ) {
		case 13: goto tr1135;
		case 32: goto tr1135;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1135;
	goto st0;
tr1135:
#line 166 "configparser.rl"
	{ skin.text = state.match; }
	goto st809;
st809:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof809;
case 809:
#line 11626 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st809;
		case 32: goto st809;
		case 98: goto st810;
		case 100: goto st1512;
		case 110: goto st1515;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st809;
	goto st0;
st810:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof810;
case 810:
	if ( (*( state.p)) == 114 )
		goto st811;
	goto st0;
st811:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof811;
case 811:
	if ( (*( state.p)) == 105 )
		goto st812;
	goto st0;
st812:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof812;
case 812:
	if ( (*( state.p)) == 103 )
		goto st813;
	goto st0;
st813:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof813;
case 813:
	if ( (*( state.p)) == 104 )
		goto st814;
	goto st0;
st814:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof814;
case 814:
	if ( (*( state.p)) == 116 )
		goto st815;
	goto st0;
st815:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof815;
case 815:
	switch( (*( state.p)) ) {
		case 13: goto tr1145;
		case 32: goto tr1145;
		case 95: goto tr1146;
		case 98: goto tr1147;
		case 99: goto tr1148;
		case 103: goto tr1149;
		case 109: goto tr1150;
		case 114: goto tr1151;
		case 119: goto tr1152;
		case 121: goto tr1153;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1145;
	goto st0;
tr1145:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st816;
tr2263:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st816;
st816:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof816;
case 816:
#line 11703 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st816;
		case 32: goto st816;
		case 98: goto st817;
		case 99: goto st1481;
		case 103: goto st1485;
		case 109: goto st1490;
		case 114: goto st1497;
		case 119: goto st1500;
		case 121: goto st1505;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st816;
	goto st0;
tr1147:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st817;
tr2265:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st817;
st817:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof817;
case 817:
#line 11730 "configparser.h"
	if ( (*( state.p)) == 108 )
		goto st818;
	goto st0;
st818:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof818;
case 818:
	switch( (*( state.p)) ) {
		case 97: goto st819;
		case 117: goto st1479;
	}
	goto st0;
st819:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof819;
case 819:
	if ( (*( state.p)) == 99 )
		goto st820;
	goto st0;
st820:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof820;
case 820:
	if ( (*( state.p)) == 107 )
		goto st821;
	goto st0;
st821:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof821;
case 821:
	switch( (*( state.p)) ) {
		case 13: goto tr1167;
		case 32: goto tr1167;
		case 59: goto tr1168;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1167;
	goto st0;
tr1120:
#line 383 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st822;
tr1167:
#line 362 "configparser.rl"
	{ lev.deep_water = skin; }
	goto st822;
tr1220:
#line 366 "configparser.rl"
	{ lev.floor1 = skin; }
	goto st822;
tr1223:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 366 "configparser.rl"
	{ lev.floor1 = skin; }
	goto st822;
tr1228:
#line 158 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 366 "configparser.rl"
	{ lev.floor1 = skin; }
	goto st822;
tr1234:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 366 "configparser.rl"
	{ lev.floor1 = skin; }
	goto st822;
tr1242:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 366 "configparser.rl"
	{ lev.floor1 = skin; }
	goto st822;
tr1246:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 366 "configparser.rl"
	{ lev.floor1 = skin; }
	goto st822;
tr1252:
#line 159 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 366 "configparser.rl"
	{ lev.floor1 = skin; }
	goto st822;
tr1259:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 366 "configparser.rl"
	{ lev.floor1 = skin; }
	goto st822;
tr1311:
#line 367 "configparser.rl"
	{ lev.floor2 = skin; }
	goto st822;
tr1314:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 367 "configparser.rl"
	{ lev.floor2 = skin; }
	goto st822;
tr1319:
#line 158 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 367 "configparser.rl"
	{ lev.floor2 = skin; }
	goto st822;
tr1325:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 367 "configparser.rl"
	{ lev.floor2 = skin; }
	goto st822;
tr1333:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 367 "configparser.rl"
	{ lev.floor2 = skin; }
	goto st822;
tr1337:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 367 "configparser.rl"
	{ lev.floor2 = skin; }
	goto st822;
tr1343:
#line 159 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 367 "configparser.rl"
	{ lev.floor2 = skin; }
	goto st822;
tr1350:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 367 "configparser.rl"
	{ lev.floor2 = skin; }
	goto st822;
tr1402:
#line 368 "configparser.rl"
	{ lev.floor3 = skin; }
	goto st822;
tr1405:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 368 "configparser.rl"
	{ lev.floor3 = skin; }
	goto st822;
tr1410:
#line 158 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 368 "configparser.rl"
	{ lev.floor3 = skin; }
	goto st822;
tr1416:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 368 "configparser.rl"
	{ lev.floor3 = skin; }
	goto st822;
tr1424:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 368 "configparser.rl"
	{ lev.floor3 = skin; }
	goto st822;
tr1428:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 368 "configparser.rl"
	{ lev.floor3 = skin; }
	goto st822;
tr1434:
#line 159 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 368 "configparser.rl"
	{ lev.floor3 = skin; }
	goto st822;
tr1441:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 368 "configparser.rl"
	{ lev.floor3 = skin; }
	goto st822;
tr1493:
#line 369 "configparser.rl"
	{ lev.floor4 = skin; }
	goto st822;
tr1496:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 369 "configparser.rl"
	{ lev.floor4 = skin; }
	goto st822;
tr1501:
#line 158 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 369 "configparser.rl"
	{ lev.floor4 = skin; }
	goto st822;
tr1507:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 369 "configparser.rl"
	{ lev.floor4 = skin; }
	goto st822;
tr1515:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 369 "configparser.rl"
	{ lev.floor4 = skin; }
	goto st822;
tr1519:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 369 "configparser.rl"
	{ lev.floor4 = skin; }
	goto st822;
tr1525:
#line 159 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 369 "configparser.rl"
	{ lev.floor4 = skin; }
	goto st822;
tr1532:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 369 "configparser.rl"
	{ lev.floor4 = skin; }
	goto st822;
tr1584:
#line 370 "configparser.rl"
	{ lev.floor5 = skin; }
	goto st822;
tr1587:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 370 "configparser.rl"
	{ lev.floor5 = skin; }
	goto st822;
tr1592:
#line 158 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 370 "configparser.rl"
	{ lev.floor5 = skin; }
	goto st822;
tr1598:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 370 "configparser.rl"
	{ lev.floor5 = skin; }
	goto st822;
tr1606:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 370 "configparser.rl"
	{ lev.floor5 = skin; }
	goto st822;
tr1610:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 370 "configparser.rl"
	{ lev.floor5 = skin; }
	goto st822;
tr1616:
#line 159 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 370 "configparser.rl"
	{ lev.floor5 = skin; }
	goto st822;
tr1623:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 370 "configparser.rl"
	{ lev.floor5 = skin; }
	goto st822;
tr1675:
#line 371 "configparser.rl"
	{ lev.floor6 = skin; }
	goto st822;
tr1678:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 371 "configparser.rl"
	{ lev.floor6 = skin; }
	goto st822;
tr1683:
#line 158 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 371 "configparser.rl"
	{ lev.floor6 = skin; }
	goto st822;
tr1689:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 371 "configparser.rl"
	{ lev.floor6 = skin; }
	goto st822;
tr1697:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 371 "configparser.rl"
	{ lev.floor6 = skin; }
	goto st822;
tr1701:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 371 "configparser.rl"
	{ lev.floor6 = skin; }
	goto st822;
tr1707:
#line 159 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 371 "configparser.rl"
	{ lev.floor6 = skin; }
	goto st822;
tr1714:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 371 "configparser.rl"
	{ lev.floor6 = skin; }
	goto st822;
tr1766:
#line 372 "configparser.rl"
	{ lev.floor7 = skin; }
	goto st822;
tr1769:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 372 "configparser.rl"
	{ lev.floor7 = skin; }
	goto st822;
tr1774:
#line 158 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 372 "configparser.rl"
	{ lev.floor7 = skin; }
	goto st822;
tr1780:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 372 "configparser.rl"
	{ lev.floor7 = skin; }
	goto st822;
tr1788:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 372 "configparser.rl"
	{ lev.floor7 = skin; }
	goto st822;
tr1792:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 372 "configparser.rl"
	{ lev.floor7 = skin; }
	goto st822;
tr1798:
#line 159 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 372 "configparser.rl"
	{ lev.floor7 = skin; }
	goto st822;
tr1805:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 372 "configparser.rl"
	{ lev.floor7 = skin; }
	goto st822;
tr1857:
#line 373 "configparser.rl"
	{ lev.floor8 = skin; }
	goto st822;
tr1860:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 373 "configparser.rl"
	{ lev.floor8 = skin; }
	goto st822;
tr1865:
#line 158 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 373 "configparser.rl"
	{ lev.floor8 = skin; }
	goto st822;
tr1871:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 373 "configparser.rl"
	{ lev.floor8 = skin; }
	goto st822;
tr1879:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 373 "configparser.rl"
	{ lev.floor8 = skin; }
	goto st822;
tr1883:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 373 "configparser.rl"
	{ lev.floor8 = skin; }
	goto st822;
tr1889:
#line 159 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 373 "configparser.rl"
	{ lev.floor8 = skin; }
	goto st822;
tr1896:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 373 "configparser.rl"
	{ lev.floor8 = skin; }
	goto st822;
tr1923:
#line 374 "configparser.rl"
	{ lev.lightradius = toint(state.match); }
	goto st822;
tr1975:
#line 363 "configparser.rl"
	{ lev.shallow_water = skin; }
	goto st822;
tr1978:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 363 "configparser.rl"
	{ lev.shallow_water = skin; }
	goto st822;
tr1983:
#line 158 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 363 "configparser.rl"
	{ lev.shallow_water = skin; }
	goto st822;
tr1989:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 363 "configparser.rl"
	{ lev.shallow_water = skin; }
	goto st822;
tr1997:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 363 "configparser.rl"
	{ lev.shallow_water = skin; }
	goto st822;
tr2001:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 363 "configparser.rl"
	{ lev.shallow_water = skin; }
	goto st822;
tr2007:
#line 159 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 363 "configparser.rl"
	{ lev.shallow_water = skin; }
	goto st822;
tr2014:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 363 "configparser.rl"
	{ lev.shallow_water = skin; }
	goto st822;
tr2070:
#line 364 "configparser.rl"
	{ lev.wall = skin; }
	goto st822;
tr2073:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 364 "configparser.rl"
	{ lev.wall = skin; }
	goto st822;
tr2078:
#line 158 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 364 "configparser.rl"
	{ lev.wall = skin; }
	goto st822;
tr2084:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 364 "configparser.rl"
	{ lev.wall = skin; }
	goto st822;
tr2092:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 364 "configparser.rl"
	{ lev.wall = skin; }
	goto st822;
tr2096:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 364 "configparser.rl"
	{ lev.wall = skin; }
	goto st822;
tr2102:
#line 159 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 364 "configparser.rl"
	{ lev.wall = skin; }
	goto st822;
tr2109:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 364 "configparser.rl"
	{ lev.wall = skin; }
	goto st822;
tr2168:
#line 365 "configparser.rl"
	{ lev.water_wall = skin; }
	goto st822;
tr2171:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 365 "configparser.rl"
	{ lev.water_wall = skin; }
	goto st822;
tr2176:
#line 158 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 365 "configparser.rl"
	{ lev.water_wall = skin; }
	goto st822;
tr2182:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 365 "configparser.rl"
	{ lev.water_wall = skin; }
	goto st822;
tr2190:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 365 "configparser.rl"
	{ lev.water_wall = skin; }
	goto st822;
tr2194:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 365 "configparser.rl"
	{ lev.water_wall = skin; }
	goto st822;
tr2200:
#line 159 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 365 "configparser.rl"
	{ lev.water_wall = skin; }
	goto st822;
tr2207:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 365 "configparser.rl"
	{ lev.water_wall = skin; }
	goto st822;
tr2223:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 362 "configparser.rl"
	{ lev.deep_water = skin; }
	goto st822;
tr2228:
#line 158 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 362 "configparser.rl"
	{ lev.deep_water = skin; }
	goto st822;
tr2234:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 362 "configparser.rl"
	{ lev.deep_water = skin; }
	goto st822;
tr2242:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 362 "configparser.rl"
	{ lev.deep_water = skin; }
	goto st822;
tr2246:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 362 "configparser.rl"
	{ lev.deep_water = skin; }
	goto st822;
tr2252:
#line 159 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 362 "configparser.rl"
	{ lev.deep_water = skin; }
	goto st822;
tr2259:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 362 "configparser.rl"
	{ lev.deep_water = skin; }
	goto st822;
st822:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof822;
case 822:
#line 12333 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st822;
		case 32: goto st822;
		case 59: goto st1527;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st822;
	goto st0;
tr1168:
#line 362 "configparser.rl"
	{ lev.deep_water = skin; }
	goto st1527;
tr1221:
#line 366 "configparser.rl"
	{ lev.floor1 = skin; }
	goto st1527;
tr1224:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 366 "configparser.rl"
	{ lev.floor1 = skin; }
	goto st1527;
tr1229:
#line 158 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 366 "configparser.rl"
	{ lev.floor1 = skin; }
	goto st1527;
tr1235:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 366 "configparser.rl"
	{ lev.floor1 = skin; }
	goto st1527;
tr1243:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 366 "configparser.rl"
	{ lev.floor1 = skin; }
	goto st1527;
tr1247:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 366 "configparser.rl"
	{ lev.floor1 = skin; }
	goto st1527;
tr1253:
#line 159 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 366 "configparser.rl"
	{ lev.floor1 = skin; }
	goto st1527;
tr1260:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 366 "configparser.rl"
	{ lev.floor1 = skin; }
	goto st1527;
tr1312:
#line 367 "configparser.rl"
	{ lev.floor2 = skin; }
	goto st1527;
tr1315:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 367 "configparser.rl"
	{ lev.floor2 = skin; }
	goto st1527;
tr1320:
#line 158 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 367 "configparser.rl"
	{ lev.floor2 = skin; }
	goto st1527;
tr1326:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 367 "configparser.rl"
	{ lev.floor2 = skin; }
	goto st1527;
tr1334:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 367 "configparser.rl"
	{ lev.floor2 = skin; }
	goto st1527;
tr1338:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 367 "configparser.rl"
	{ lev.floor2 = skin; }
	goto st1527;
tr1344:
#line 159 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 367 "configparser.rl"
	{ lev.floor2 = skin; }
	goto st1527;
tr1351:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 367 "configparser.rl"
	{ lev.floor2 = skin; }
	goto st1527;
tr1403:
#line 368 "configparser.rl"
	{ lev.floor3 = skin; }
	goto st1527;
tr1406:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 368 "configparser.rl"
	{ lev.floor3 = skin; }
	goto st1527;
tr1411:
#line 158 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 368 "configparser.rl"
	{ lev.floor3 = skin; }
	goto st1527;
tr1417:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 368 "configparser.rl"
	{ lev.floor3 = skin; }
	goto st1527;
tr1425:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 368 "configparser.rl"
	{ lev.floor3 = skin; }
	goto st1527;
tr1429:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 368 "configparser.rl"
	{ lev.floor3 = skin; }
	goto st1527;
tr1435:
#line 159 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 368 "configparser.rl"
	{ lev.floor3 = skin; }
	goto st1527;
tr1442:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 368 "configparser.rl"
	{ lev.floor3 = skin; }
	goto st1527;
tr1494:
#line 369 "configparser.rl"
	{ lev.floor4 = skin; }
	goto st1527;
tr1497:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 369 "configparser.rl"
	{ lev.floor4 = skin; }
	goto st1527;
tr1502:
#line 158 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 369 "configparser.rl"
	{ lev.floor4 = skin; }
	goto st1527;
tr1508:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 369 "configparser.rl"
	{ lev.floor4 = skin; }
	goto st1527;
tr1516:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 369 "configparser.rl"
	{ lev.floor4 = skin; }
	goto st1527;
tr1520:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 369 "configparser.rl"
	{ lev.floor4 = skin; }
	goto st1527;
tr1526:
#line 159 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 369 "configparser.rl"
	{ lev.floor4 = skin; }
	goto st1527;
tr1533:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 369 "configparser.rl"
	{ lev.floor4 = skin; }
	goto st1527;
tr1585:
#line 370 "configparser.rl"
	{ lev.floor5 = skin; }
	goto st1527;
tr1588:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 370 "configparser.rl"
	{ lev.floor5 = skin; }
	goto st1527;
tr1593:
#line 158 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 370 "configparser.rl"
	{ lev.floor5 = skin; }
	goto st1527;
tr1599:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 370 "configparser.rl"
	{ lev.floor5 = skin; }
	goto st1527;
tr1607:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 370 "configparser.rl"
	{ lev.floor5 = skin; }
	goto st1527;
tr1611:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 370 "configparser.rl"
	{ lev.floor5 = skin; }
	goto st1527;
tr1617:
#line 159 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 370 "configparser.rl"
	{ lev.floor5 = skin; }
	goto st1527;
tr1624:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 370 "configparser.rl"
	{ lev.floor5 = skin; }
	goto st1527;
tr1676:
#line 371 "configparser.rl"
	{ lev.floor6 = skin; }
	goto st1527;
tr1679:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 371 "configparser.rl"
	{ lev.floor6 = skin; }
	goto st1527;
tr1684:
#line 158 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 371 "configparser.rl"
	{ lev.floor6 = skin; }
	goto st1527;
tr1690:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 371 "configparser.rl"
	{ lev.floor6 = skin; }
	goto st1527;
tr1698:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 371 "configparser.rl"
	{ lev.floor6 = skin; }
	goto st1527;
tr1702:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 371 "configparser.rl"
	{ lev.floor6 = skin; }
	goto st1527;
tr1708:
#line 159 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 371 "configparser.rl"
	{ lev.floor6 = skin; }
	goto st1527;
tr1715:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 371 "configparser.rl"
	{ lev.floor6 = skin; }
	goto st1527;
tr1767:
#line 372 "configparser.rl"
	{ lev.floor7 = skin; }
	goto st1527;
tr1770:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 372 "configparser.rl"
	{ lev.floor7 = skin; }
	goto st1527;
tr1775:
#line 158 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 372 "configparser.rl"
	{ lev.floor7 = skin; }
	goto st1527;
tr1781:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 372 "configparser.rl"
	{ lev.floor7 = skin; }
	goto st1527;
tr1789:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 372 "configparser.rl"
	{ lev.floor7 = skin; }
	goto st1527;
tr1793:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 372 "configparser.rl"
	{ lev.floor7 = skin; }
	goto st1527;
tr1799:
#line 159 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 372 "configparser.rl"
	{ lev.floor7 = skin; }
	goto st1527;
tr1806:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 372 "configparser.rl"
	{ lev.floor7 = skin; }
	goto st1527;
tr1858:
#line 373 "configparser.rl"
	{ lev.floor8 = skin; }
	goto st1527;
tr1861:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 373 "configparser.rl"
	{ lev.floor8 = skin; }
	goto st1527;
tr1866:
#line 158 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 373 "configparser.rl"
	{ lev.floor8 = skin; }
	goto st1527;
tr1872:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 373 "configparser.rl"
	{ lev.floor8 = skin; }
	goto st1527;
tr1880:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 373 "configparser.rl"
	{ lev.floor8 = skin; }
	goto st1527;
tr1884:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 373 "configparser.rl"
	{ lev.floor8 = skin; }
	goto st1527;
tr1890:
#line 159 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 373 "configparser.rl"
	{ lev.floor8 = skin; }
	goto st1527;
tr1897:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 373 "configparser.rl"
	{ lev.floor8 = skin; }
	goto st1527;
tr1925:
#line 374 "configparser.rl"
	{ lev.lightradius = toint(state.match); }
	goto st1527;
tr1976:
#line 363 "configparser.rl"
	{ lev.shallow_water = skin; }
	goto st1527;
tr1979:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 363 "configparser.rl"
	{ lev.shallow_water = skin; }
	goto st1527;
tr1984:
#line 158 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 363 "configparser.rl"
	{ lev.shallow_water = skin; }
	goto st1527;
tr1990:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 363 "configparser.rl"
	{ lev.shallow_water = skin; }
	goto st1527;
tr1998:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 363 "configparser.rl"
	{ lev.shallow_water = skin; }
	goto st1527;
tr2002:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 363 "configparser.rl"
	{ lev.shallow_water = skin; }
	goto st1527;
tr2008:
#line 159 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 363 "configparser.rl"
	{ lev.shallow_water = skin; }
	goto st1527;
tr2015:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 363 "configparser.rl"
	{ lev.shallow_water = skin; }
	goto st1527;
tr2071:
#line 364 "configparser.rl"
	{ lev.wall = skin; }
	goto st1527;
tr2074:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 364 "configparser.rl"
	{ lev.wall = skin; }
	goto st1527;
tr2079:
#line 158 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 364 "configparser.rl"
	{ lev.wall = skin; }
	goto st1527;
tr2085:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 364 "configparser.rl"
	{ lev.wall = skin; }
	goto st1527;
tr2093:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 364 "configparser.rl"
	{ lev.wall = skin; }
	goto st1527;
tr2097:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 364 "configparser.rl"
	{ lev.wall = skin; }
	goto st1527;
tr2103:
#line 159 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 364 "configparser.rl"
	{ lev.wall = skin; }
	goto st1527;
tr2110:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 364 "configparser.rl"
	{ lev.wall = skin; }
	goto st1527;
tr2169:
#line 365 "configparser.rl"
	{ lev.water_wall = skin; }
	goto st1527;
tr2172:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 365 "configparser.rl"
	{ lev.water_wall = skin; }
	goto st1527;
tr2177:
#line 158 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 365 "configparser.rl"
	{ lev.water_wall = skin; }
	goto st1527;
tr2183:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 365 "configparser.rl"
	{ lev.water_wall = skin; }
	goto st1527;
tr2191:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 365 "configparser.rl"
	{ lev.water_wall = skin; }
	goto st1527;
tr2195:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 365 "configparser.rl"
	{ lev.water_wall = skin; }
	goto st1527;
tr2201:
#line 159 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 365 "configparser.rl"
	{ lev.water_wall = skin; }
	goto st1527;
tr2208:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 365 "configparser.rl"
	{ lev.water_wall = skin; }
	goto st1527;
tr2224:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 362 "configparser.rl"
	{ lev.deep_water = skin; }
	goto st1527;
tr2229:
#line 158 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 362 "configparser.rl"
	{ lev.deep_water = skin; }
	goto st1527;
tr2235:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 362 "configparser.rl"
	{ lev.deep_water = skin; }
	goto st1527;
tr2243:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 362 "configparser.rl"
	{ lev.deep_water = skin; }
	goto st1527;
tr2247:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 362 "configparser.rl"
	{ lev.deep_water = skin; }
	goto st1527;
tr2253:
#line 159 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 362 "configparser.rl"
	{ lev.deep_water = skin; }
	goto st1527;
tr2260:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 362 "configparser.rl"
	{ lev.deep_water = skin; }
	goto st1527;
st1527:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1527;
case 1527:
#line 12902 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st795;
		case 32: goto st795;
		case 100: goto st796;
		case 102: goto st823;
		case 108: goto st1276;
		case 115: goto st1289;
		case 119: goto st1357;
		case 125: goto tr1120;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st795;
	goto st0;
st823:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof823;
case 823:
	if ( (*( state.p)) == 108 )
		goto st824;
	goto st0;
st824:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof824;
case 824:
	if ( (*( state.p)) == 111 )
		goto st825;
	goto st0;
st825:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof825;
case 825:
	if ( (*( state.p)) == 111 )
		goto st826;
	goto st0;
st826:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof826;
case 826:
	if ( (*( state.p)) == 114 )
		goto st827;
	goto st0;
st827:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof827;
case 827:
	switch( (*( state.p)) ) {
		case 49: goto st828;
		case 50: goto st884;
		case 51: goto st940;
		case 52: goto st996;
		case 53: goto st1052;
		case 54: goto st1108;
		case 55: goto st1164;
		case 56: goto st1220;
	}
	goto st0;
st828:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof828;
case 828:
	switch( (*( state.p)) ) {
		case 13: goto st829;
		case 32: goto st829;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st829;
	goto st0;
st829:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof829;
case 829:
	switch( (*( state.p)) ) {
		case 13: goto st829;
		case 32: goto st829;
		case 34: goto tr1184;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st829;
	goto st0;
tr1185:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st830;
tr1184:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
	goto st830;
tr1187:
#line 144 "configparser.rl"
	{{ state.stack[ state.top++] = 830; goto st47;}}
	goto st830;
st830:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof830;
case 830:
#line 13002 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st831;
		case 92: goto tr1187;
	}
	goto tr1185;
st831:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof831;
case 831:
	switch( (*( state.p)) ) {
		case 13: goto tr1188;
		case 32: goto tr1188;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1188;
	goto st0;
tr1188:
#line 166 "configparser.rl"
	{ skin.text = state.match; }
	goto st832;
st832:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof832;
case 832:
#line 13027 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st832;
		case 32: goto st832;
		case 98: goto st833;
		case 100: goto st878;
		case 110: goto st881;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st832;
	goto st0;
st833:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof833;
case 833:
	if ( (*( state.p)) == 114 )
		goto st834;
	goto st0;
st834:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof834;
case 834:
	if ( (*( state.p)) == 105 )
		goto st835;
	goto st0;
st835:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof835;
case 835:
	if ( (*( state.p)) == 103 )
		goto st836;
	goto st0;
st836:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof836;
case 836:
	if ( (*( state.p)) == 104 )
		goto st837;
	goto st0;
st837:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof837;
case 837:
	if ( (*( state.p)) == 116 )
		goto st838;
	goto st0;
st838:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof838;
case 838:
	switch( (*( state.p)) ) {
		case 13: goto tr1198;
		case 32: goto tr1198;
		case 95: goto tr1199;
		case 98: goto tr1200;
		case 99: goto tr1201;
		case 103: goto tr1202;
		case 109: goto tr1203;
		case 114: goto tr1204;
		case 119: goto tr1205;
		case 121: goto tr1206;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1198;
	goto st0;
tr1198:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st839;
tr1263:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st839;
st839:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof839;
case 839:
#line 13104 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st839;
		case 32: goto st839;
		case 98: goto st840;
		case 99: goto st847;
		case 103: goto st851;
		case 109: goto st856;
		case 114: goto st863;
		case 119: goto st866;
		case 121: goto st871;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st839;
	goto st0;
tr1200:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st840;
tr1265:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st840;
st840:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof840;
case 840:
#line 13131 "configparser.h"
	if ( (*( state.p)) == 108 )
		goto st841;
	goto st0;
st841:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof841;
case 841:
	switch( (*( state.p)) ) {
		case 97: goto st842;
		case 117: goto st845;
	}
	goto st0;
st842:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof842;
case 842:
	if ( (*( state.p)) == 99 )
		goto st843;
	goto st0;
st843:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof843;
case 843:
	if ( (*( state.p)) == 107 )
		goto st844;
	goto st0;
st844:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof844;
case 844:
	switch( (*( state.p)) ) {
		case 13: goto tr1220;
		case 32: goto tr1220;
		case 59: goto tr1221;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1220;
	goto st0;
st845:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof845;
case 845:
	if ( (*( state.p)) == 101 )
		goto st846;
	goto st0;
st846:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof846;
case 846:
	switch( (*( state.p)) ) {
		case 13: goto tr1223;
		case 32: goto tr1223;
		case 59: goto tr1224;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1223;
	goto st0;
tr1201:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st847;
tr1266:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st847;
st847:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof847;
case 847:
#line 13201 "configparser.h"
	if ( (*( state.p)) == 121 )
		goto st848;
	goto st0;
st848:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof848;
case 848:
	if ( (*( state.p)) == 97 )
		goto st849;
	goto st0;
st849:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof849;
case 849:
	if ( (*( state.p)) == 110 )
		goto st850;
	goto st0;
st850:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof850;
case 850:
	switch( (*( state.p)) ) {
		case 13: goto tr1228;
		case 32: goto tr1228;
		case 59: goto tr1229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1228;
	goto st0;
tr1202:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st851;
tr1267:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st851;
st851:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof851;
case 851:
#line 13243 "configparser.h"
	if ( (*( state.p)) == 114 )
		goto st852;
	goto st0;
st852:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof852;
case 852:
	if ( (*( state.p)) == 101 )
		goto st853;
	goto st0;
st853:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof853;
case 853:
	if ( (*( state.p)) == 101 )
		goto st854;
	goto st0;
st854:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof854;
case 854:
	if ( (*( state.p)) == 110 )
		goto st855;
	goto st0;
st855:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof855;
case 855:
	switch( (*( state.p)) ) {
		case 13: goto tr1234;
		case 32: goto tr1234;
		case 59: goto tr1235;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1234;
	goto st0;
tr1203:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st856;
tr1268:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st856;
st856:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof856;
case 856:
#line 13292 "configparser.h"
	if ( (*( state.p)) == 97 )
		goto st857;
	goto st0;
st857:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof857;
case 857:
	if ( (*( state.p)) == 103 )
		goto st858;
	goto st0;
st858:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof858;
case 858:
	if ( (*( state.p)) == 101 )
		goto st859;
	goto st0;
st859:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof859;
case 859:
	if ( (*( state.p)) == 110 )
		goto st860;
	goto st0;
st860:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof860;
case 860:
	if ( (*( state.p)) == 116 )
		goto st861;
	goto st0;
st861:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof861;
case 861:
	if ( (*( state.p)) == 97 )
		goto st862;
	goto st0;
st862:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof862;
case 862:
	switch( (*( state.p)) ) {
		case 13: goto tr1242;
		case 32: goto tr1242;
		case 59: goto tr1243;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1242;
	goto st0;
tr1204:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st863;
tr1269:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st863;
st863:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof863;
case 863:
#line 13355 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st864;
	goto st0;
st864:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof864;
case 864:
	if ( (*( state.p)) == 100 )
		goto st865;
	goto st0;
st865:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof865;
case 865:
	switch( (*( state.p)) ) {
		case 13: goto tr1246;
		case 32: goto tr1246;
		case 59: goto tr1247;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1246;
	goto st0;
tr1205:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st866;
tr1270:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st866;
st866:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof866;
case 866:
#line 13390 "configparser.h"
	if ( (*( state.p)) == 104 )
		goto st867;
	goto st0;
st867:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof867;
case 867:
	if ( (*( state.p)) == 105 )
		goto st868;
	goto st0;
st868:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof868;
case 868:
	if ( (*( state.p)) == 116 )
		goto st869;
	goto st0;
st869:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof869;
case 869:
	if ( (*( state.p)) == 101 )
		goto st870;
	goto st0;
st870:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof870;
case 870:
	switch( (*( state.p)) ) {
		case 13: goto tr1252;
		case 32: goto tr1252;
		case 59: goto tr1253;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1252;
	goto st0;
tr1206:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st871;
tr1271:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st871;
st871:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof871;
case 871:
#line 13439 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st872;
	goto st0;
st872:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof872;
case 872:
	if ( (*( state.p)) == 108 )
		goto st873;
	goto st0;
st873:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof873;
case 873:
	if ( (*( state.p)) == 108 )
		goto st874;
	goto st0;
st874:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof874;
case 874:
	if ( (*( state.p)) == 111 )
		goto st875;
	goto st0;
st875:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof875;
case 875:
	if ( (*( state.p)) == 119 )
		goto st876;
	goto st0;
st876:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof876;
case 876:
	switch( (*( state.p)) ) {
		case 13: goto tr1259;
		case 32: goto tr1259;
		case 59: goto tr1260;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1259;
	goto st0;
tr1199:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st877;
tr1264:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st877;
st877:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof877;
case 877:
#line 13495 "configparser.h"
	switch( (*( state.p)) ) {
		case 98: goto st840;
		case 99: goto st847;
		case 103: goto st851;
		case 109: goto st856;
		case 114: goto st863;
		case 119: goto st866;
		case 121: goto st871;
	}
	goto st0;
st878:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof878;
case 878:
	if ( (*( state.p)) == 105 )
		goto st879;
	goto st0;
st879:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof879;
case 879:
	if ( (*( state.p)) == 109 )
		goto st880;
	goto st0;
st880:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof880;
case 880:
	switch( (*( state.p)) ) {
		case 13: goto tr1263;
		case 32: goto tr1263;
		case 95: goto tr1264;
		case 98: goto tr1265;
		case 99: goto tr1266;
		case 103: goto tr1267;
		case 109: goto tr1268;
		case 114: goto tr1269;
		case 119: goto tr1270;
		case 121: goto tr1271;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1263;
	goto st0;
st881:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof881;
case 881:
	if ( (*( state.p)) == 111 )
		goto st882;
	goto st0;
st882:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof882;
case 882:
	if ( (*( state.p)) == 110 )
		goto st883;
	goto st0;
st883:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof883;
case 883:
	if ( (*( state.p)) == 101 )
		goto st844;
	goto st0;
st884:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof884;
case 884:
	switch( (*( state.p)) ) {
		case 13: goto st885;
		case 32: goto st885;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st885;
	goto st0;
st885:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof885;
case 885:
	switch( (*( state.p)) ) {
		case 13: goto st885;
		case 32: goto st885;
		case 34: goto tr1275;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st885;
	goto st0;
tr1276:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st886;
tr1275:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
	goto st886;
tr1278:
#line 144 "configparser.rl"
	{{ state.stack[ state.top++] = 886; goto st47;}}
	goto st886;
st886:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof886;
case 886:
#line 13603 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st887;
		case 92: goto tr1278;
	}
	goto tr1276;
st887:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof887;
case 887:
	switch( (*( state.p)) ) {
		case 13: goto tr1279;
		case 32: goto tr1279;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1279;
	goto st0;
tr1279:
#line 166 "configparser.rl"
	{ skin.text = state.match; }
	goto st888;
st888:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof888;
case 888:
#line 13628 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st888;
		case 32: goto st888;
		case 98: goto st889;
		case 100: goto st934;
		case 110: goto st937;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st888;
	goto st0;
st889:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof889;
case 889:
	if ( (*( state.p)) == 114 )
		goto st890;
	goto st0;
st890:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof890;
case 890:
	if ( (*( state.p)) == 105 )
		goto st891;
	goto st0;
st891:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof891;
case 891:
	if ( (*( state.p)) == 103 )
		goto st892;
	goto st0;
st892:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof892;
case 892:
	if ( (*( state.p)) == 104 )
		goto st893;
	goto st0;
st893:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof893;
case 893:
	if ( (*( state.p)) == 116 )
		goto st894;
	goto st0;
st894:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof894;
case 894:
	switch( (*( state.p)) ) {
		case 13: goto tr1289;
		case 32: goto tr1289;
		case 95: goto tr1290;
		case 98: goto tr1291;
		case 99: goto tr1292;
		case 103: goto tr1293;
		case 109: goto tr1294;
		case 114: goto tr1295;
		case 119: goto tr1296;
		case 121: goto tr1297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1289;
	goto st0;
tr1289:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st895;
tr1354:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st895;
st895:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof895;
case 895:
#line 13705 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st895;
		case 32: goto st895;
		case 98: goto st896;
		case 99: goto st903;
		case 103: goto st907;
		case 109: goto st912;
		case 114: goto st919;
		case 119: goto st922;
		case 121: goto st927;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st895;
	goto st0;
tr1291:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st896;
tr1356:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st896;
st896:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof896;
case 896:
#line 13732 "configparser.h"
	if ( (*( state.p)) == 108 )
		goto st897;
	goto st0;
st897:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof897;
case 897:
	switch( (*( state.p)) ) {
		case 97: goto st898;
		case 117: goto st901;
	}
	goto st0;
st898:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof898;
case 898:
	if ( (*( state.p)) == 99 )
		goto st899;
	goto st0;
st899:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof899;
case 899:
	if ( (*( state.p)) == 107 )
		goto st900;
	goto st0;
st900:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof900;
case 900:
	switch( (*( state.p)) ) {
		case 13: goto tr1311;
		case 32: goto tr1311;
		case 59: goto tr1312;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1311;
	goto st0;
st901:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof901;
case 901:
	if ( (*( state.p)) == 101 )
		goto st902;
	goto st0;
st902:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof902;
case 902:
	switch( (*( state.p)) ) {
		case 13: goto tr1314;
		case 32: goto tr1314;
		case 59: goto tr1315;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1314;
	goto st0;
tr1292:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st903;
tr1357:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st903;
st903:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof903;
case 903:
#line 13802 "configparser.h"
	if ( (*( state.p)) == 121 )
		goto st904;
	goto st0;
st904:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof904;
case 904:
	if ( (*( state.p)) == 97 )
		goto st905;
	goto st0;
st905:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof905;
case 905:
	if ( (*( state.p)) == 110 )
		goto st906;
	goto st0;
st906:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof906;
case 906:
	switch( (*( state.p)) ) {
		case 13: goto tr1319;
		case 32: goto tr1319;
		case 59: goto tr1320;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1319;
	goto st0;
tr1293:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st907;
tr1358:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st907;
st907:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof907;
case 907:
#line 13844 "configparser.h"
	if ( (*( state.p)) == 114 )
		goto st908;
	goto st0;
st908:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof908;
case 908:
	if ( (*( state.p)) == 101 )
		goto st909;
	goto st0;
st909:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof909;
case 909:
	if ( (*( state.p)) == 101 )
		goto st910;
	goto st0;
st910:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof910;
case 910:
	if ( (*( state.p)) == 110 )
		goto st911;
	goto st0;
st911:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof911;
case 911:
	switch( (*( state.p)) ) {
		case 13: goto tr1325;
		case 32: goto tr1325;
		case 59: goto tr1326;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1325;
	goto st0;
tr1294:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st912;
tr1359:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st912;
st912:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof912;
case 912:
#line 13893 "configparser.h"
	if ( (*( state.p)) == 97 )
		goto st913;
	goto st0;
st913:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof913;
case 913:
	if ( (*( state.p)) == 103 )
		goto st914;
	goto st0;
st914:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof914;
case 914:
	if ( (*( state.p)) == 101 )
		goto st915;
	goto st0;
st915:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof915;
case 915:
	if ( (*( state.p)) == 110 )
		goto st916;
	goto st0;
st916:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof916;
case 916:
	if ( (*( state.p)) == 116 )
		goto st917;
	goto st0;
st917:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof917;
case 917:
	if ( (*( state.p)) == 97 )
		goto st918;
	goto st0;
st918:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof918;
case 918:
	switch( (*( state.p)) ) {
		case 13: goto tr1333;
		case 32: goto tr1333;
		case 59: goto tr1334;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1333;
	goto st0;
tr1295:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st919;
tr1360:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st919;
st919:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof919;
case 919:
#line 13956 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st920;
	goto st0;
st920:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof920;
case 920:
	if ( (*( state.p)) == 100 )
		goto st921;
	goto st0;
st921:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof921;
case 921:
	switch( (*( state.p)) ) {
		case 13: goto tr1337;
		case 32: goto tr1337;
		case 59: goto tr1338;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1337;
	goto st0;
tr1296:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st922;
tr1361:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st922;
st922:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof922;
case 922:
#line 13991 "configparser.h"
	if ( (*( state.p)) == 104 )
		goto st923;
	goto st0;
st923:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof923;
case 923:
	if ( (*( state.p)) == 105 )
		goto st924;
	goto st0;
st924:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof924;
case 924:
	if ( (*( state.p)) == 116 )
		goto st925;
	goto st0;
st925:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof925;
case 925:
	if ( (*( state.p)) == 101 )
		goto st926;
	goto st0;
st926:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof926;
case 926:
	switch( (*( state.p)) ) {
		case 13: goto tr1343;
		case 32: goto tr1343;
		case 59: goto tr1344;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1343;
	goto st0;
tr1297:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st927;
tr1362:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st927;
st927:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof927;
case 927:
#line 14040 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st928;
	goto st0;
st928:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof928;
case 928:
	if ( (*( state.p)) == 108 )
		goto st929;
	goto st0;
st929:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof929;
case 929:
	if ( (*( state.p)) == 108 )
		goto st930;
	goto st0;
st930:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof930;
case 930:
	if ( (*( state.p)) == 111 )
		goto st931;
	goto st0;
st931:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof931;
case 931:
	if ( (*( state.p)) == 119 )
		goto st932;
	goto st0;
st932:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof932;
case 932:
	switch( (*( state.p)) ) {
		case 13: goto tr1350;
		case 32: goto tr1350;
		case 59: goto tr1351;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1350;
	goto st0;
tr1290:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st933;
tr1355:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st933;
st933:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof933;
case 933:
#line 14096 "configparser.h"
	switch( (*( state.p)) ) {
		case 98: goto st896;
		case 99: goto st903;
		case 103: goto st907;
		case 109: goto st912;
		case 114: goto st919;
		case 119: goto st922;
		case 121: goto st927;
	}
	goto st0;
st934:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof934;
case 934:
	if ( (*( state.p)) == 105 )
		goto st935;
	goto st0;
st935:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof935;
case 935:
	if ( (*( state.p)) == 109 )
		goto st936;
	goto st0;
st936:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof936;
case 936:
	switch( (*( state.p)) ) {
		case 13: goto tr1354;
		case 32: goto tr1354;
		case 95: goto tr1355;
		case 98: goto tr1356;
		case 99: goto tr1357;
		case 103: goto tr1358;
		case 109: goto tr1359;
		case 114: goto tr1360;
		case 119: goto tr1361;
		case 121: goto tr1362;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1354;
	goto st0;
st937:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof937;
case 937:
	if ( (*( state.p)) == 111 )
		goto st938;
	goto st0;
st938:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof938;
case 938:
	if ( (*( state.p)) == 110 )
		goto st939;
	goto st0;
st939:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof939;
case 939:
	if ( (*( state.p)) == 101 )
		goto st900;
	goto st0;
st940:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof940;
case 940:
	switch( (*( state.p)) ) {
		case 13: goto st941;
		case 32: goto st941;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st941;
	goto st0;
st941:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof941;
case 941:
	switch( (*( state.p)) ) {
		case 13: goto st941;
		case 32: goto st941;
		case 34: goto tr1366;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st941;
	goto st0;
tr1367:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st942;
tr1366:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
	goto st942;
tr1369:
#line 144 "configparser.rl"
	{{ state.stack[ state.top++] = 942; goto st47;}}
	goto st942;
st942:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof942;
case 942:
#line 14204 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st943;
		case 92: goto tr1369;
	}
	goto tr1367;
st943:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof943;
case 943:
	switch( (*( state.p)) ) {
		case 13: goto tr1370;
		case 32: goto tr1370;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1370;
	goto st0;
tr1370:
#line 166 "configparser.rl"
	{ skin.text = state.match; }
	goto st944;
st944:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof944;
case 944:
#line 14229 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st944;
		case 32: goto st944;
		case 98: goto st945;
		case 100: goto st990;
		case 110: goto st993;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st944;
	goto st0;
st945:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof945;
case 945:
	if ( (*( state.p)) == 114 )
		goto st946;
	goto st0;
st946:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof946;
case 946:
	if ( (*( state.p)) == 105 )
		goto st947;
	goto st0;
st947:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof947;
case 947:
	if ( (*( state.p)) == 103 )
		goto st948;
	goto st0;
st948:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof948;
case 948:
	if ( (*( state.p)) == 104 )
		goto st949;
	goto st0;
st949:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof949;
case 949:
	if ( (*( state.p)) == 116 )
		goto st950;
	goto st0;
st950:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof950;
case 950:
	switch( (*( state.p)) ) {
		case 13: goto tr1380;
		case 32: goto tr1380;
		case 95: goto tr1381;
		case 98: goto tr1382;
		case 99: goto tr1383;
		case 103: goto tr1384;
		case 109: goto tr1385;
		case 114: goto tr1386;
		case 119: goto tr1387;
		case 121: goto tr1388;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1380;
	goto st0;
tr1380:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st951;
tr1445:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st951;
st951:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof951;
case 951:
#line 14306 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st951;
		case 32: goto st951;
		case 98: goto st952;
		case 99: goto st959;
		case 103: goto st963;
		case 109: goto st968;
		case 114: goto st975;
		case 119: goto st978;
		case 121: goto st983;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st951;
	goto st0;
tr1382:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st952;
tr1447:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st952;
st952:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof952;
case 952:
#line 14333 "configparser.h"
	if ( (*( state.p)) == 108 )
		goto st953;
	goto st0;
st953:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof953;
case 953:
	switch( (*( state.p)) ) {
		case 97: goto st954;
		case 117: goto st957;
	}
	goto st0;
st954:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof954;
case 954:
	if ( (*( state.p)) == 99 )
		goto st955;
	goto st0;
st955:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof955;
case 955:
	if ( (*( state.p)) == 107 )
		goto st956;
	goto st0;
st956:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof956;
case 956:
	switch( (*( state.p)) ) {
		case 13: goto tr1402;
		case 32: goto tr1402;
		case 59: goto tr1403;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1402;
	goto st0;
st957:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof957;
case 957:
	if ( (*( state.p)) == 101 )
		goto st958;
	goto st0;
st958:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof958;
case 958:
	switch( (*( state.p)) ) {
		case 13: goto tr1405;
		case 32: goto tr1405;
		case 59: goto tr1406;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1405;
	goto st0;
tr1383:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st959;
tr1448:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st959;
st959:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof959;
case 959:
#line 14403 "configparser.h"
	if ( (*( state.p)) == 121 )
		goto st960;
	goto st0;
st960:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof960;
case 960:
	if ( (*( state.p)) == 97 )
		goto st961;
	goto st0;
st961:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof961;
case 961:
	if ( (*( state.p)) == 110 )
		goto st962;
	goto st0;
st962:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof962;
case 962:
	switch( (*( state.p)) ) {
		case 13: goto tr1410;
		case 32: goto tr1410;
		case 59: goto tr1411;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1410;
	goto st0;
tr1384:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st963;
tr1449:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st963;
st963:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof963;
case 963:
#line 14445 "configparser.h"
	if ( (*( state.p)) == 114 )
		goto st964;
	goto st0;
st964:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof964;
case 964:
	if ( (*( state.p)) == 101 )
		goto st965;
	goto st0;
st965:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof965;
case 965:
	if ( (*( state.p)) == 101 )
		goto st966;
	goto st0;
st966:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof966;
case 966:
	if ( (*( state.p)) == 110 )
		goto st967;
	goto st0;
st967:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof967;
case 967:
	switch( (*( state.p)) ) {
		case 13: goto tr1416;
		case 32: goto tr1416;
		case 59: goto tr1417;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1416;
	goto st0;
tr1385:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st968;
tr1450:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st968;
st968:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof968;
case 968:
#line 14494 "configparser.h"
	if ( (*( state.p)) == 97 )
		goto st969;
	goto st0;
st969:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof969;
case 969:
	if ( (*( state.p)) == 103 )
		goto st970;
	goto st0;
st970:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof970;
case 970:
	if ( (*( state.p)) == 101 )
		goto st971;
	goto st0;
st971:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof971;
case 971:
	if ( (*( state.p)) == 110 )
		goto st972;
	goto st0;
st972:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof972;
case 972:
	if ( (*( state.p)) == 116 )
		goto st973;
	goto st0;
st973:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof973;
case 973:
	if ( (*( state.p)) == 97 )
		goto st974;
	goto st0;
st974:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof974;
case 974:
	switch( (*( state.p)) ) {
		case 13: goto tr1424;
		case 32: goto tr1424;
		case 59: goto tr1425;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1424;
	goto st0;
tr1386:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st975;
tr1451:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st975;
st975:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof975;
case 975:
#line 14557 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st976;
	goto st0;
st976:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof976;
case 976:
	if ( (*( state.p)) == 100 )
		goto st977;
	goto st0;
st977:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof977;
case 977:
	switch( (*( state.p)) ) {
		case 13: goto tr1428;
		case 32: goto tr1428;
		case 59: goto tr1429;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1428;
	goto st0;
tr1387:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st978;
tr1452:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st978;
st978:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof978;
case 978:
#line 14592 "configparser.h"
	if ( (*( state.p)) == 104 )
		goto st979;
	goto st0;
st979:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof979;
case 979:
	if ( (*( state.p)) == 105 )
		goto st980;
	goto st0;
st980:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof980;
case 980:
	if ( (*( state.p)) == 116 )
		goto st981;
	goto st0;
st981:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof981;
case 981:
	if ( (*( state.p)) == 101 )
		goto st982;
	goto st0;
st982:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof982;
case 982:
	switch( (*( state.p)) ) {
		case 13: goto tr1434;
		case 32: goto tr1434;
		case 59: goto tr1435;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1434;
	goto st0;
tr1388:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st983;
tr1453:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st983;
st983:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof983;
case 983:
#line 14641 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st984;
	goto st0;
st984:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof984;
case 984:
	if ( (*( state.p)) == 108 )
		goto st985;
	goto st0;
st985:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof985;
case 985:
	if ( (*( state.p)) == 108 )
		goto st986;
	goto st0;
st986:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof986;
case 986:
	if ( (*( state.p)) == 111 )
		goto st987;
	goto st0;
st987:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof987;
case 987:
	if ( (*( state.p)) == 119 )
		goto st988;
	goto st0;
st988:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof988;
case 988:
	switch( (*( state.p)) ) {
		case 13: goto tr1441;
		case 32: goto tr1441;
		case 59: goto tr1442;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1441;
	goto st0;
tr1381:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st989;
tr1446:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st989;
st989:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof989;
case 989:
#line 14697 "configparser.h"
	switch( (*( state.p)) ) {
		case 98: goto st952;
		case 99: goto st959;
		case 103: goto st963;
		case 109: goto st968;
		case 114: goto st975;
		case 119: goto st978;
		case 121: goto st983;
	}
	goto st0;
st990:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof990;
case 990:
	if ( (*( state.p)) == 105 )
		goto st991;
	goto st0;
st991:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof991;
case 991:
	if ( (*( state.p)) == 109 )
		goto st992;
	goto st0;
st992:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof992;
case 992:
	switch( (*( state.p)) ) {
		case 13: goto tr1445;
		case 32: goto tr1445;
		case 95: goto tr1446;
		case 98: goto tr1447;
		case 99: goto tr1448;
		case 103: goto tr1449;
		case 109: goto tr1450;
		case 114: goto tr1451;
		case 119: goto tr1452;
		case 121: goto tr1453;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1445;
	goto st0;
st993:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof993;
case 993:
	if ( (*( state.p)) == 111 )
		goto st994;
	goto st0;
st994:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof994;
case 994:
	if ( (*( state.p)) == 110 )
		goto st995;
	goto st0;
st995:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof995;
case 995:
	if ( (*( state.p)) == 101 )
		goto st956;
	goto st0;
st996:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof996;
case 996:
	switch( (*( state.p)) ) {
		case 13: goto st997;
		case 32: goto st997;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st997;
	goto st0;
st997:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof997;
case 997:
	switch( (*( state.p)) ) {
		case 13: goto st997;
		case 32: goto st997;
		case 34: goto tr1457;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st997;
	goto st0;
tr1458:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st998;
tr1457:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
	goto st998;
tr1460:
#line 144 "configparser.rl"
	{{ state.stack[ state.top++] = 998; goto st47;}}
	goto st998;
st998:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof998;
case 998:
#line 14805 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st999;
		case 92: goto tr1460;
	}
	goto tr1458;
st999:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof999;
case 999:
	switch( (*( state.p)) ) {
		case 13: goto tr1461;
		case 32: goto tr1461;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1461;
	goto st0;
tr1461:
#line 166 "configparser.rl"
	{ skin.text = state.match; }
	goto st1000;
st1000:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1000;
case 1000:
#line 14830 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st1000;
		case 32: goto st1000;
		case 98: goto st1001;
		case 100: goto st1046;
		case 110: goto st1049;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1000;
	goto st0;
st1001:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1001;
case 1001:
	if ( (*( state.p)) == 114 )
		goto st1002;
	goto st0;
st1002:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1002;
case 1002:
	if ( (*( state.p)) == 105 )
		goto st1003;
	goto st0;
st1003:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1003;
case 1003:
	if ( (*( state.p)) == 103 )
		goto st1004;
	goto st0;
st1004:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1004;
case 1004:
	if ( (*( state.p)) == 104 )
		goto st1005;
	goto st0;
st1005:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1005;
case 1005:
	if ( (*( state.p)) == 116 )
		goto st1006;
	goto st0;
st1006:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1006;
case 1006:
	switch( (*( state.p)) ) {
		case 13: goto tr1471;
		case 32: goto tr1471;
		case 95: goto tr1472;
		case 98: goto tr1473;
		case 99: goto tr1474;
		case 103: goto tr1475;
		case 109: goto tr1476;
		case 114: goto tr1477;
		case 119: goto tr1478;
		case 121: goto tr1479;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1471;
	goto st0;
tr1471:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1007;
tr1536:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1007;
st1007:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1007;
case 1007:
#line 14907 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st1007;
		case 32: goto st1007;
		case 98: goto st1008;
		case 99: goto st1015;
		case 103: goto st1019;
		case 109: goto st1024;
		case 114: goto st1031;
		case 119: goto st1034;
		case 121: goto st1039;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1007;
	goto st0;
tr1473:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1008;
tr1538:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1008;
st1008:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1008;
case 1008:
#line 14934 "configparser.h"
	if ( (*( state.p)) == 108 )
		goto st1009;
	goto st0;
st1009:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1009;
case 1009:
	switch( (*( state.p)) ) {
		case 97: goto st1010;
		case 117: goto st1013;
	}
	goto st0;
st1010:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1010;
case 1010:
	if ( (*( state.p)) == 99 )
		goto st1011;
	goto st0;
st1011:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1011;
case 1011:
	if ( (*( state.p)) == 107 )
		goto st1012;
	goto st0;
st1012:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1012;
case 1012:
	switch( (*( state.p)) ) {
		case 13: goto tr1493;
		case 32: goto tr1493;
		case 59: goto tr1494;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1493;
	goto st0;
st1013:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1013;
case 1013:
	if ( (*( state.p)) == 101 )
		goto st1014;
	goto st0;
st1014:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1014;
case 1014:
	switch( (*( state.p)) ) {
		case 13: goto tr1496;
		case 32: goto tr1496;
		case 59: goto tr1497;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1496;
	goto st0;
tr1474:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1015;
tr1539:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1015;
st1015:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1015;
case 1015:
#line 15004 "configparser.h"
	if ( (*( state.p)) == 121 )
		goto st1016;
	goto st0;
st1016:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1016;
case 1016:
	if ( (*( state.p)) == 97 )
		goto st1017;
	goto st0;
st1017:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1017;
case 1017:
	if ( (*( state.p)) == 110 )
		goto st1018;
	goto st0;
st1018:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1018;
case 1018:
	switch( (*( state.p)) ) {
		case 13: goto tr1501;
		case 32: goto tr1501;
		case 59: goto tr1502;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1501;
	goto st0;
tr1475:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1019;
tr1540:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1019;
st1019:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1019;
case 1019:
#line 15046 "configparser.h"
	if ( (*( state.p)) == 114 )
		goto st1020;
	goto st0;
st1020:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1020;
case 1020:
	if ( (*( state.p)) == 101 )
		goto st1021;
	goto st0;
st1021:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1021;
case 1021:
	if ( (*( state.p)) == 101 )
		goto st1022;
	goto st0;
st1022:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1022;
case 1022:
	if ( (*( state.p)) == 110 )
		goto st1023;
	goto st0;
st1023:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1023;
case 1023:
	switch( (*( state.p)) ) {
		case 13: goto tr1507;
		case 32: goto tr1507;
		case 59: goto tr1508;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1507;
	goto st0;
tr1476:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1024;
tr1541:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1024;
st1024:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1024;
case 1024:
#line 15095 "configparser.h"
	if ( (*( state.p)) == 97 )
		goto st1025;
	goto st0;
st1025:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1025;
case 1025:
	if ( (*( state.p)) == 103 )
		goto st1026;
	goto st0;
st1026:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1026;
case 1026:
	if ( (*( state.p)) == 101 )
		goto st1027;
	goto st0;
st1027:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1027;
case 1027:
	if ( (*( state.p)) == 110 )
		goto st1028;
	goto st0;
st1028:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1028;
case 1028:
	if ( (*( state.p)) == 116 )
		goto st1029;
	goto st0;
st1029:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1029;
case 1029:
	if ( (*( state.p)) == 97 )
		goto st1030;
	goto st0;
st1030:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1030;
case 1030:
	switch( (*( state.p)) ) {
		case 13: goto tr1515;
		case 32: goto tr1515;
		case 59: goto tr1516;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1515;
	goto st0;
tr1477:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1031;
tr1542:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1031;
st1031:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1031;
case 1031:
#line 15158 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st1032;
	goto st0;
st1032:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1032;
case 1032:
	if ( (*( state.p)) == 100 )
		goto st1033;
	goto st0;
st1033:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1033;
case 1033:
	switch( (*( state.p)) ) {
		case 13: goto tr1519;
		case 32: goto tr1519;
		case 59: goto tr1520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1519;
	goto st0;
tr1478:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1034;
tr1543:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1034;
st1034:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1034;
case 1034:
#line 15193 "configparser.h"
	if ( (*( state.p)) == 104 )
		goto st1035;
	goto st0;
st1035:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1035;
case 1035:
	if ( (*( state.p)) == 105 )
		goto st1036;
	goto st0;
st1036:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1036;
case 1036:
	if ( (*( state.p)) == 116 )
		goto st1037;
	goto st0;
st1037:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1037;
case 1037:
	if ( (*( state.p)) == 101 )
		goto st1038;
	goto st0;
st1038:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1038;
case 1038:
	switch( (*( state.p)) ) {
		case 13: goto tr1525;
		case 32: goto tr1525;
		case 59: goto tr1526;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1525;
	goto st0;
tr1479:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1039;
tr1544:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1039;
st1039:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1039;
case 1039:
#line 15242 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st1040;
	goto st0;
st1040:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1040;
case 1040:
	if ( (*( state.p)) == 108 )
		goto st1041;
	goto st0;
st1041:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1041;
case 1041:
	if ( (*( state.p)) == 108 )
		goto st1042;
	goto st0;
st1042:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1042;
case 1042:
	if ( (*( state.p)) == 111 )
		goto st1043;
	goto st0;
st1043:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1043;
case 1043:
	if ( (*( state.p)) == 119 )
		goto st1044;
	goto st0;
st1044:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1044;
case 1044:
	switch( (*( state.p)) ) {
		case 13: goto tr1532;
		case 32: goto tr1532;
		case 59: goto tr1533;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1532;
	goto st0;
tr1472:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1045;
tr1537:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1045;
st1045:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1045;
case 1045:
#line 15298 "configparser.h"
	switch( (*( state.p)) ) {
		case 98: goto st1008;
		case 99: goto st1015;
		case 103: goto st1019;
		case 109: goto st1024;
		case 114: goto st1031;
		case 119: goto st1034;
		case 121: goto st1039;
	}
	goto st0;
st1046:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1046;
case 1046:
	if ( (*( state.p)) == 105 )
		goto st1047;
	goto st0;
st1047:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1047;
case 1047:
	if ( (*( state.p)) == 109 )
		goto st1048;
	goto st0;
st1048:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1048;
case 1048:
	switch( (*( state.p)) ) {
		case 13: goto tr1536;
		case 32: goto tr1536;
		case 95: goto tr1537;
		case 98: goto tr1538;
		case 99: goto tr1539;
		case 103: goto tr1540;
		case 109: goto tr1541;
		case 114: goto tr1542;
		case 119: goto tr1543;
		case 121: goto tr1544;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1536;
	goto st0;
st1049:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1049;
case 1049:
	if ( (*( state.p)) == 111 )
		goto st1050;
	goto st0;
st1050:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1050;
case 1050:
	if ( (*( state.p)) == 110 )
		goto st1051;
	goto st0;
st1051:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1051;
case 1051:
	if ( (*( state.p)) == 101 )
		goto st1012;
	goto st0;
st1052:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1052;
case 1052:
	switch( (*( state.p)) ) {
		case 13: goto st1053;
		case 32: goto st1053;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1053;
	goto st0;
st1053:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1053;
case 1053:
	switch( (*( state.p)) ) {
		case 13: goto st1053;
		case 32: goto st1053;
		case 34: goto tr1548;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1053;
	goto st0;
tr1549:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1054;
tr1548:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1054;
tr1551:
#line 144 "configparser.rl"
	{{ state.stack[ state.top++] = 1054; goto st47;}}
	goto st1054;
st1054:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1054;
case 1054:
#line 15406 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st1055;
		case 92: goto tr1551;
	}
	goto tr1549;
st1055:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1055;
case 1055:
	switch( (*( state.p)) ) {
		case 13: goto tr1552;
		case 32: goto tr1552;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1552;
	goto st0;
tr1552:
#line 166 "configparser.rl"
	{ skin.text = state.match; }
	goto st1056;
st1056:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1056;
case 1056:
#line 15431 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st1056;
		case 32: goto st1056;
		case 98: goto st1057;
		case 100: goto st1102;
		case 110: goto st1105;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1056;
	goto st0;
st1057:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1057;
case 1057:
	if ( (*( state.p)) == 114 )
		goto st1058;
	goto st0;
st1058:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1058;
case 1058:
	if ( (*( state.p)) == 105 )
		goto st1059;
	goto st0;
st1059:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1059;
case 1059:
	if ( (*( state.p)) == 103 )
		goto st1060;
	goto st0;
st1060:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1060;
case 1060:
	if ( (*( state.p)) == 104 )
		goto st1061;
	goto st0;
st1061:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1061;
case 1061:
	if ( (*( state.p)) == 116 )
		goto st1062;
	goto st0;
st1062:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1062;
case 1062:
	switch( (*( state.p)) ) {
		case 13: goto tr1562;
		case 32: goto tr1562;
		case 95: goto tr1563;
		case 98: goto tr1564;
		case 99: goto tr1565;
		case 103: goto tr1566;
		case 109: goto tr1567;
		case 114: goto tr1568;
		case 119: goto tr1569;
		case 121: goto tr1570;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1562;
	goto st0;
tr1562:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1063;
tr1627:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1063;
st1063:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1063;
case 1063:
#line 15508 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st1063;
		case 32: goto st1063;
		case 98: goto st1064;
		case 99: goto st1071;
		case 103: goto st1075;
		case 109: goto st1080;
		case 114: goto st1087;
		case 119: goto st1090;
		case 121: goto st1095;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1063;
	goto st0;
tr1564:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1064;
tr1629:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1064;
st1064:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1064;
case 1064:
#line 15535 "configparser.h"
	if ( (*( state.p)) == 108 )
		goto st1065;
	goto st0;
st1065:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1065;
case 1065:
	switch( (*( state.p)) ) {
		case 97: goto st1066;
		case 117: goto st1069;
	}
	goto st0;
st1066:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1066;
case 1066:
	if ( (*( state.p)) == 99 )
		goto st1067;
	goto st0;
st1067:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1067;
case 1067:
	if ( (*( state.p)) == 107 )
		goto st1068;
	goto st0;
st1068:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1068;
case 1068:
	switch( (*( state.p)) ) {
		case 13: goto tr1584;
		case 32: goto tr1584;
		case 59: goto tr1585;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1584;
	goto st0;
st1069:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1069;
case 1069:
	if ( (*( state.p)) == 101 )
		goto st1070;
	goto st0;
st1070:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1070;
case 1070:
	switch( (*( state.p)) ) {
		case 13: goto tr1587;
		case 32: goto tr1587;
		case 59: goto tr1588;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1587;
	goto st0;
tr1565:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1071;
tr1630:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1071;
st1071:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1071;
case 1071:
#line 15605 "configparser.h"
	if ( (*( state.p)) == 121 )
		goto st1072;
	goto st0;
st1072:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1072;
case 1072:
	if ( (*( state.p)) == 97 )
		goto st1073;
	goto st0;
st1073:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1073;
case 1073:
	if ( (*( state.p)) == 110 )
		goto st1074;
	goto st0;
st1074:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1074;
case 1074:
	switch( (*( state.p)) ) {
		case 13: goto tr1592;
		case 32: goto tr1592;
		case 59: goto tr1593;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1592;
	goto st0;
tr1566:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1075;
tr1631:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1075;
st1075:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1075;
case 1075:
#line 15647 "configparser.h"
	if ( (*( state.p)) == 114 )
		goto st1076;
	goto st0;
st1076:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1076;
case 1076:
	if ( (*( state.p)) == 101 )
		goto st1077;
	goto st0;
st1077:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1077;
case 1077:
	if ( (*( state.p)) == 101 )
		goto st1078;
	goto st0;
st1078:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1078;
case 1078:
	if ( (*( state.p)) == 110 )
		goto st1079;
	goto st0;
st1079:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1079;
case 1079:
	switch( (*( state.p)) ) {
		case 13: goto tr1598;
		case 32: goto tr1598;
		case 59: goto tr1599;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1598;
	goto st0;
tr1567:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1080;
tr1632:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1080;
st1080:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1080;
case 1080:
#line 15696 "configparser.h"
	if ( (*( state.p)) == 97 )
		goto st1081;
	goto st0;
st1081:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1081;
case 1081:
	if ( (*( state.p)) == 103 )
		goto st1082;
	goto st0;
st1082:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1082;
case 1082:
	if ( (*( state.p)) == 101 )
		goto st1083;
	goto st0;
st1083:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1083;
case 1083:
	if ( (*( state.p)) == 110 )
		goto st1084;
	goto st0;
st1084:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1084;
case 1084:
	if ( (*( state.p)) == 116 )
		goto st1085;
	goto st0;
st1085:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1085;
case 1085:
	if ( (*( state.p)) == 97 )
		goto st1086;
	goto st0;
st1086:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1086;
case 1086:
	switch( (*( state.p)) ) {
		case 13: goto tr1606;
		case 32: goto tr1606;
		case 59: goto tr1607;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1606;
	goto st0;
tr1568:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1087;
tr1633:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1087;
st1087:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1087;
case 1087:
#line 15759 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st1088;
	goto st0;
st1088:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1088;
case 1088:
	if ( (*( state.p)) == 100 )
		goto st1089;
	goto st0;
st1089:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1089;
case 1089:
	switch( (*( state.p)) ) {
		case 13: goto tr1610;
		case 32: goto tr1610;
		case 59: goto tr1611;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1610;
	goto st0;
tr1569:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1090;
tr1634:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1090;
st1090:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1090;
case 1090:
#line 15794 "configparser.h"
	if ( (*( state.p)) == 104 )
		goto st1091;
	goto st0;
st1091:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1091;
case 1091:
	if ( (*( state.p)) == 105 )
		goto st1092;
	goto st0;
st1092:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1092;
case 1092:
	if ( (*( state.p)) == 116 )
		goto st1093;
	goto st0;
st1093:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1093;
case 1093:
	if ( (*( state.p)) == 101 )
		goto st1094;
	goto st0;
st1094:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1094;
case 1094:
	switch( (*( state.p)) ) {
		case 13: goto tr1616;
		case 32: goto tr1616;
		case 59: goto tr1617;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1616;
	goto st0;
tr1570:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1095;
tr1635:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1095;
st1095:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1095;
case 1095:
#line 15843 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st1096;
	goto st0;
st1096:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1096;
case 1096:
	if ( (*( state.p)) == 108 )
		goto st1097;
	goto st0;
st1097:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1097;
case 1097:
	if ( (*( state.p)) == 108 )
		goto st1098;
	goto st0;
st1098:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1098;
case 1098:
	if ( (*( state.p)) == 111 )
		goto st1099;
	goto st0;
st1099:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1099;
case 1099:
	if ( (*( state.p)) == 119 )
		goto st1100;
	goto st0;
st1100:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1100;
case 1100:
	switch( (*( state.p)) ) {
		case 13: goto tr1623;
		case 32: goto tr1623;
		case 59: goto tr1624;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1623;
	goto st0;
tr1563:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1101;
tr1628:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1101;
st1101:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1101;
case 1101:
#line 15899 "configparser.h"
	switch( (*( state.p)) ) {
		case 98: goto st1064;
		case 99: goto st1071;
		case 103: goto st1075;
		case 109: goto st1080;
		case 114: goto st1087;
		case 119: goto st1090;
		case 121: goto st1095;
	}
	goto st0;
st1102:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1102;
case 1102:
	if ( (*( state.p)) == 105 )
		goto st1103;
	goto st0;
st1103:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1103;
case 1103:
	if ( (*( state.p)) == 109 )
		goto st1104;
	goto st0;
st1104:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1104;
case 1104:
	switch( (*( state.p)) ) {
		case 13: goto tr1627;
		case 32: goto tr1627;
		case 95: goto tr1628;
		case 98: goto tr1629;
		case 99: goto tr1630;
		case 103: goto tr1631;
		case 109: goto tr1632;
		case 114: goto tr1633;
		case 119: goto tr1634;
		case 121: goto tr1635;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1627;
	goto st0;
st1105:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1105;
case 1105:
	if ( (*( state.p)) == 111 )
		goto st1106;
	goto st0;
st1106:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1106;
case 1106:
	if ( (*( state.p)) == 110 )
		goto st1107;
	goto st0;
st1107:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1107;
case 1107:
	if ( (*( state.p)) == 101 )
		goto st1068;
	goto st0;
st1108:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1108;
case 1108:
	switch( (*( state.p)) ) {
		case 13: goto st1109;
		case 32: goto st1109;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1109;
	goto st0;
st1109:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1109;
case 1109:
	switch( (*( state.p)) ) {
		case 13: goto st1109;
		case 32: goto st1109;
		case 34: goto tr1639;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1109;
	goto st0;
tr1640:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1110;
tr1639:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1110;
tr1642:
#line 144 "configparser.rl"
	{{ state.stack[ state.top++] = 1110; goto st47;}}
	goto st1110;
st1110:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1110;
case 1110:
#line 16007 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st1111;
		case 92: goto tr1642;
	}
	goto tr1640;
st1111:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1111;
case 1111:
	switch( (*( state.p)) ) {
		case 13: goto tr1643;
		case 32: goto tr1643;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1643;
	goto st0;
tr1643:
#line 166 "configparser.rl"
	{ skin.text = state.match; }
	goto st1112;
st1112:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1112;
case 1112:
#line 16032 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st1112;
		case 32: goto st1112;
		case 98: goto st1113;
		case 100: goto st1158;
		case 110: goto st1161;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1112;
	goto st0;
st1113:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1113;
case 1113:
	if ( (*( state.p)) == 114 )
		goto st1114;
	goto st0;
st1114:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1114;
case 1114:
	if ( (*( state.p)) == 105 )
		goto st1115;
	goto st0;
st1115:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1115;
case 1115:
	if ( (*( state.p)) == 103 )
		goto st1116;
	goto st0;
st1116:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1116;
case 1116:
	if ( (*( state.p)) == 104 )
		goto st1117;
	goto st0;
st1117:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1117;
case 1117:
	if ( (*( state.p)) == 116 )
		goto st1118;
	goto st0;
st1118:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1118;
case 1118:
	switch( (*( state.p)) ) {
		case 13: goto tr1653;
		case 32: goto tr1653;
		case 95: goto tr1654;
		case 98: goto tr1655;
		case 99: goto tr1656;
		case 103: goto tr1657;
		case 109: goto tr1658;
		case 114: goto tr1659;
		case 119: goto tr1660;
		case 121: goto tr1661;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1653;
	goto st0;
tr1653:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1119;
tr1718:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1119;
st1119:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1119;
case 1119:
#line 16109 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st1119;
		case 32: goto st1119;
		case 98: goto st1120;
		case 99: goto st1127;
		case 103: goto st1131;
		case 109: goto st1136;
		case 114: goto st1143;
		case 119: goto st1146;
		case 121: goto st1151;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1119;
	goto st0;
tr1655:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1120;
tr1720:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1120;
st1120:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1120;
case 1120:
#line 16136 "configparser.h"
	if ( (*( state.p)) == 108 )
		goto st1121;
	goto st0;
st1121:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1121;
case 1121:
	switch( (*( state.p)) ) {
		case 97: goto st1122;
		case 117: goto st1125;
	}
	goto st0;
st1122:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1122;
case 1122:
	if ( (*( state.p)) == 99 )
		goto st1123;
	goto st0;
st1123:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1123;
case 1123:
	if ( (*( state.p)) == 107 )
		goto st1124;
	goto st0;
st1124:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1124;
case 1124:
	switch( (*( state.p)) ) {
		case 13: goto tr1675;
		case 32: goto tr1675;
		case 59: goto tr1676;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1675;
	goto st0;
st1125:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1125;
case 1125:
	if ( (*( state.p)) == 101 )
		goto st1126;
	goto st0;
st1126:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1126;
case 1126:
	switch( (*( state.p)) ) {
		case 13: goto tr1678;
		case 32: goto tr1678;
		case 59: goto tr1679;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1678;
	goto st0;
tr1656:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1127;
tr1721:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1127;
st1127:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1127;
case 1127:
#line 16206 "configparser.h"
	if ( (*( state.p)) == 121 )
		goto st1128;
	goto st0;
st1128:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1128;
case 1128:
	if ( (*( state.p)) == 97 )
		goto st1129;
	goto st0;
st1129:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1129;
case 1129:
	if ( (*( state.p)) == 110 )
		goto st1130;
	goto st0;
st1130:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1130;
case 1130:
	switch( (*( state.p)) ) {
		case 13: goto tr1683;
		case 32: goto tr1683;
		case 59: goto tr1684;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1683;
	goto st0;
tr1657:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1131;
tr1722:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1131;
st1131:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1131;
case 1131:
#line 16248 "configparser.h"
	if ( (*( state.p)) == 114 )
		goto st1132;
	goto st0;
st1132:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1132;
case 1132:
	if ( (*( state.p)) == 101 )
		goto st1133;
	goto st0;
st1133:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1133;
case 1133:
	if ( (*( state.p)) == 101 )
		goto st1134;
	goto st0;
st1134:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1134;
case 1134:
	if ( (*( state.p)) == 110 )
		goto st1135;
	goto st0;
st1135:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1135;
case 1135:
	switch( (*( state.p)) ) {
		case 13: goto tr1689;
		case 32: goto tr1689;
		case 59: goto tr1690;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1689;
	goto st0;
tr1658:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1136;
tr1723:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1136;
st1136:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1136;
case 1136:
#line 16297 "configparser.h"
	if ( (*( state.p)) == 97 )
		goto st1137;
	goto st0;
st1137:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1137;
case 1137:
	if ( (*( state.p)) == 103 )
		goto st1138;
	goto st0;
st1138:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1138;
case 1138:
	if ( (*( state.p)) == 101 )
		goto st1139;
	goto st0;
st1139:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1139;
case 1139:
	if ( (*( state.p)) == 110 )
		goto st1140;
	goto st0;
st1140:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1140;
case 1140:
	if ( (*( state.p)) == 116 )
		goto st1141;
	goto st0;
st1141:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1141;
case 1141:
	if ( (*( state.p)) == 97 )
		goto st1142;
	goto st0;
st1142:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1142;
case 1142:
	switch( (*( state.p)) ) {
		case 13: goto tr1697;
		case 32: goto tr1697;
		case 59: goto tr1698;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1697;
	goto st0;
tr1659:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1143;
tr1724:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1143;
st1143:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1143;
case 1143:
#line 16360 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st1144;
	goto st0;
st1144:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1144;
case 1144:
	if ( (*( state.p)) == 100 )
		goto st1145;
	goto st0;
st1145:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1145;
case 1145:
	switch( (*( state.p)) ) {
		case 13: goto tr1701;
		case 32: goto tr1701;
		case 59: goto tr1702;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1701;
	goto st0;
tr1660:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1146;
tr1725:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1146;
st1146:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1146;
case 1146:
#line 16395 "configparser.h"
	if ( (*( state.p)) == 104 )
		goto st1147;
	goto st0;
st1147:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1147;
case 1147:
	if ( (*( state.p)) == 105 )
		goto st1148;
	goto st0;
st1148:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1148;
case 1148:
	if ( (*( state.p)) == 116 )
		goto st1149;
	goto st0;
st1149:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1149;
case 1149:
	if ( (*( state.p)) == 101 )
		goto st1150;
	goto st0;
st1150:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1150;
case 1150:
	switch( (*( state.p)) ) {
		case 13: goto tr1707;
		case 32: goto tr1707;
		case 59: goto tr1708;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1707;
	goto st0;
tr1661:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1151;
tr1726:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1151;
st1151:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1151;
case 1151:
#line 16444 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st1152;
	goto st0;
st1152:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1152;
case 1152:
	if ( (*( state.p)) == 108 )
		goto st1153;
	goto st0;
st1153:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1153;
case 1153:
	if ( (*( state.p)) == 108 )
		goto st1154;
	goto st0;
st1154:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1154;
case 1154:
	if ( (*( state.p)) == 111 )
		goto st1155;
	goto st0;
st1155:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1155;
case 1155:
	if ( (*( state.p)) == 119 )
		goto st1156;
	goto st0;
st1156:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1156;
case 1156:
	switch( (*( state.p)) ) {
		case 13: goto tr1714;
		case 32: goto tr1714;
		case 59: goto tr1715;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1714;
	goto st0;
tr1654:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1157;
tr1719:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1157;
st1157:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1157;
case 1157:
#line 16500 "configparser.h"
	switch( (*( state.p)) ) {
		case 98: goto st1120;
		case 99: goto st1127;
		case 103: goto st1131;
		case 109: goto st1136;
		case 114: goto st1143;
		case 119: goto st1146;
		case 121: goto st1151;
	}
	goto st0;
st1158:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1158;
case 1158:
	if ( (*( state.p)) == 105 )
		goto st1159;
	goto st0;
st1159:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1159;
case 1159:
	if ( (*( state.p)) == 109 )
		goto st1160;
	goto st0;
st1160:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1160;
case 1160:
	switch( (*( state.p)) ) {
		case 13: goto tr1718;
		case 32: goto tr1718;
		case 95: goto tr1719;
		case 98: goto tr1720;
		case 99: goto tr1721;
		case 103: goto tr1722;
		case 109: goto tr1723;
		case 114: goto tr1724;
		case 119: goto tr1725;
		case 121: goto tr1726;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1718;
	goto st0;
st1161:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1161;
case 1161:
	if ( (*( state.p)) == 111 )
		goto st1162;
	goto st0;
st1162:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1162;
case 1162:
	if ( (*( state.p)) == 110 )
		goto st1163;
	goto st0;
st1163:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1163;
case 1163:
	if ( (*( state.p)) == 101 )
		goto st1124;
	goto st0;
st1164:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1164;
case 1164:
	switch( (*( state.p)) ) {
		case 13: goto st1165;
		case 32: goto st1165;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1165;
	goto st0;
st1165:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1165;
case 1165:
	switch( (*( state.p)) ) {
		case 13: goto st1165;
		case 32: goto st1165;
		case 34: goto tr1730;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1165;
	goto st0;
tr1731:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1166;
tr1730:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1166;
tr1733:
#line 144 "configparser.rl"
	{{ state.stack[ state.top++] = 1166; goto st47;}}
	goto st1166;
st1166:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1166;
case 1166:
#line 16608 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st1167;
		case 92: goto tr1733;
	}
	goto tr1731;
st1167:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1167;
case 1167:
	switch( (*( state.p)) ) {
		case 13: goto tr1734;
		case 32: goto tr1734;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1734;
	goto st0;
tr1734:
#line 166 "configparser.rl"
	{ skin.text = state.match; }
	goto st1168;
st1168:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1168;
case 1168:
#line 16633 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st1168;
		case 32: goto st1168;
		case 98: goto st1169;
		case 100: goto st1214;
		case 110: goto st1217;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1168;
	goto st0;
st1169:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1169;
case 1169:
	if ( (*( state.p)) == 114 )
		goto st1170;
	goto st0;
st1170:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1170;
case 1170:
	if ( (*( state.p)) == 105 )
		goto st1171;
	goto st0;
st1171:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1171;
case 1171:
	if ( (*( state.p)) == 103 )
		goto st1172;
	goto st0;
st1172:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1172;
case 1172:
	if ( (*( state.p)) == 104 )
		goto st1173;
	goto st0;
st1173:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1173;
case 1173:
	if ( (*( state.p)) == 116 )
		goto st1174;
	goto st0;
st1174:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1174;
case 1174:
	switch( (*( state.p)) ) {
		case 13: goto tr1744;
		case 32: goto tr1744;
		case 95: goto tr1745;
		case 98: goto tr1746;
		case 99: goto tr1747;
		case 103: goto tr1748;
		case 109: goto tr1749;
		case 114: goto tr1750;
		case 119: goto tr1751;
		case 121: goto tr1752;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1744;
	goto st0;
tr1744:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1175;
tr1809:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1175;
st1175:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1175;
case 1175:
#line 16710 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st1175;
		case 32: goto st1175;
		case 98: goto st1176;
		case 99: goto st1183;
		case 103: goto st1187;
		case 109: goto st1192;
		case 114: goto st1199;
		case 119: goto st1202;
		case 121: goto st1207;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1175;
	goto st0;
tr1746:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1176;
tr1811:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1176;
st1176:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1176;
case 1176:
#line 16737 "configparser.h"
	if ( (*( state.p)) == 108 )
		goto st1177;
	goto st0;
st1177:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1177;
case 1177:
	switch( (*( state.p)) ) {
		case 97: goto st1178;
		case 117: goto st1181;
	}
	goto st0;
st1178:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1178;
case 1178:
	if ( (*( state.p)) == 99 )
		goto st1179;
	goto st0;
st1179:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1179;
case 1179:
	if ( (*( state.p)) == 107 )
		goto st1180;
	goto st0;
st1180:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1180;
case 1180:
	switch( (*( state.p)) ) {
		case 13: goto tr1766;
		case 32: goto tr1766;
		case 59: goto tr1767;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1766;
	goto st0;
st1181:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1181;
case 1181:
	if ( (*( state.p)) == 101 )
		goto st1182;
	goto st0;
st1182:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1182;
case 1182:
	switch( (*( state.p)) ) {
		case 13: goto tr1769;
		case 32: goto tr1769;
		case 59: goto tr1770;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1769;
	goto st0;
tr1747:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1183;
tr1812:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1183;
st1183:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1183;
case 1183:
#line 16807 "configparser.h"
	if ( (*( state.p)) == 121 )
		goto st1184;
	goto st0;
st1184:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1184;
case 1184:
	if ( (*( state.p)) == 97 )
		goto st1185;
	goto st0;
st1185:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1185;
case 1185:
	if ( (*( state.p)) == 110 )
		goto st1186;
	goto st0;
st1186:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1186;
case 1186:
	switch( (*( state.p)) ) {
		case 13: goto tr1774;
		case 32: goto tr1774;
		case 59: goto tr1775;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1774;
	goto st0;
tr1748:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1187;
tr1813:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1187;
st1187:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1187;
case 1187:
#line 16849 "configparser.h"
	if ( (*( state.p)) == 114 )
		goto st1188;
	goto st0;
st1188:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1188;
case 1188:
	if ( (*( state.p)) == 101 )
		goto st1189;
	goto st0;
st1189:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1189;
case 1189:
	if ( (*( state.p)) == 101 )
		goto st1190;
	goto st0;
st1190:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1190;
case 1190:
	if ( (*( state.p)) == 110 )
		goto st1191;
	goto st0;
st1191:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1191;
case 1191:
	switch( (*( state.p)) ) {
		case 13: goto tr1780;
		case 32: goto tr1780;
		case 59: goto tr1781;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1780;
	goto st0;
tr1749:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1192;
tr1814:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1192;
st1192:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1192;
case 1192:
#line 16898 "configparser.h"
	if ( (*( state.p)) == 97 )
		goto st1193;
	goto st0;
st1193:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1193;
case 1193:
	if ( (*( state.p)) == 103 )
		goto st1194;
	goto st0;
st1194:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1194;
case 1194:
	if ( (*( state.p)) == 101 )
		goto st1195;
	goto st0;
st1195:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1195;
case 1195:
	if ( (*( state.p)) == 110 )
		goto st1196;
	goto st0;
st1196:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1196;
case 1196:
	if ( (*( state.p)) == 116 )
		goto st1197;
	goto st0;
st1197:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1197;
case 1197:
	if ( (*( state.p)) == 97 )
		goto st1198;
	goto st0;
st1198:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1198;
case 1198:
	switch( (*( state.p)) ) {
		case 13: goto tr1788;
		case 32: goto tr1788;
		case 59: goto tr1789;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1788;
	goto st0;
tr1750:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1199;
tr1815:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1199;
st1199:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1199;
case 1199:
#line 16961 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st1200;
	goto st0;
st1200:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1200;
case 1200:
	if ( (*( state.p)) == 100 )
		goto st1201;
	goto st0;
st1201:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1201;
case 1201:
	switch( (*( state.p)) ) {
		case 13: goto tr1792;
		case 32: goto tr1792;
		case 59: goto tr1793;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1792;
	goto st0;
tr1751:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1202;
tr1816:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1202;
st1202:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1202;
case 1202:
#line 16996 "configparser.h"
	if ( (*( state.p)) == 104 )
		goto st1203;
	goto st0;
st1203:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1203;
case 1203:
	if ( (*( state.p)) == 105 )
		goto st1204;
	goto st0;
st1204:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1204;
case 1204:
	if ( (*( state.p)) == 116 )
		goto st1205;
	goto st0;
st1205:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1205;
case 1205:
	if ( (*( state.p)) == 101 )
		goto st1206;
	goto st0;
st1206:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1206;
case 1206:
	switch( (*( state.p)) ) {
		case 13: goto tr1798;
		case 32: goto tr1798;
		case 59: goto tr1799;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1798;
	goto st0;
tr1752:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1207;
tr1817:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1207;
st1207:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1207;
case 1207:
#line 17045 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st1208;
	goto st0;
st1208:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1208;
case 1208:
	if ( (*( state.p)) == 108 )
		goto st1209;
	goto st0;
st1209:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1209;
case 1209:
	if ( (*( state.p)) == 108 )
		goto st1210;
	goto st0;
st1210:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1210;
case 1210:
	if ( (*( state.p)) == 111 )
		goto st1211;
	goto st0;
st1211:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1211;
case 1211:
	if ( (*( state.p)) == 119 )
		goto st1212;
	goto st0;
st1212:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1212;
case 1212:
	switch( (*( state.p)) ) {
		case 13: goto tr1805;
		case 32: goto tr1805;
		case 59: goto tr1806;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1805;
	goto st0;
tr1745:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1213;
tr1810:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1213;
st1213:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1213;
case 1213:
#line 17101 "configparser.h"
	switch( (*( state.p)) ) {
		case 98: goto st1176;
		case 99: goto st1183;
		case 103: goto st1187;
		case 109: goto st1192;
		case 114: goto st1199;
		case 119: goto st1202;
		case 121: goto st1207;
	}
	goto st0;
st1214:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1214;
case 1214:
	if ( (*( state.p)) == 105 )
		goto st1215;
	goto st0;
st1215:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1215;
case 1215:
	if ( (*( state.p)) == 109 )
		goto st1216;
	goto st0;
st1216:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1216;
case 1216:
	switch( (*( state.p)) ) {
		case 13: goto tr1809;
		case 32: goto tr1809;
		case 95: goto tr1810;
		case 98: goto tr1811;
		case 99: goto tr1812;
		case 103: goto tr1813;
		case 109: goto tr1814;
		case 114: goto tr1815;
		case 119: goto tr1816;
		case 121: goto tr1817;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1809;
	goto st0;
st1217:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1217;
case 1217:
	if ( (*( state.p)) == 111 )
		goto st1218;
	goto st0;
st1218:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1218;
case 1218:
	if ( (*( state.p)) == 110 )
		goto st1219;
	goto st0;
st1219:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1219;
case 1219:
	if ( (*( state.p)) == 101 )
		goto st1180;
	goto st0;
st1220:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1220;
case 1220:
	switch( (*( state.p)) ) {
		case 13: goto st1221;
		case 32: goto st1221;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1221;
	goto st0;
st1221:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1221;
case 1221:
	switch( (*( state.p)) ) {
		case 13: goto st1221;
		case 32: goto st1221;
		case 34: goto tr1821;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1221;
	goto st0;
tr1822:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1222;
tr1821:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1222;
tr1824:
#line 144 "configparser.rl"
	{{ state.stack[ state.top++] = 1222; goto st47;}}
	goto st1222;
st1222:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1222;
case 1222:
#line 17209 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st1223;
		case 92: goto tr1824;
	}
	goto tr1822;
st1223:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1223;
case 1223:
	switch( (*( state.p)) ) {
		case 13: goto tr1825;
		case 32: goto tr1825;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1825;
	goto st0;
tr1825:
#line 166 "configparser.rl"
	{ skin.text = state.match; }
	goto st1224;
st1224:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1224;
case 1224:
#line 17234 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st1224;
		case 32: goto st1224;
		case 98: goto st1225;
		case 100: goto st1270;
		case 110: goto st1273;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1224;
	goto st0;
st1225:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1225;
case 1225:
	if ( (*( state.p)) == 114 )
		goto st1226;
	goto st0;
st1226:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1226;
case 1226:
	if ( (*( state.p)) == 105 )
		goto st1227;
	goto st0;
st1227:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1227;
case 1227:
	if ( (*( state.p)) == 103 )
		goto st1228;
	goto st0;
st1228:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1228;
case 1228:
	if ( (*( state.p)) == 104 )
		goto st1229;
	goto st0;
st1229:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1229;
case 1229:
	if ( (*( state.p)) == 116 )
		goto st1230;
	goto st0;
st1230:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1230;
case 1230:
	switch( (*( state.p)) ) {
		case 13: goto tr1835;
		case 32: goto tr1835;
		case 95: goto tr1836;
		case 98: goto tr1837;
		case 99: goto tr1838;
		case 103: goto tr1839;
		case 109: goto tr1840;
		case 114: goto tr1841;
		case 119: goto tr1842;
		case 121: goto tr1843;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1835;
	goto st0;
tr1835:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1231;
tr1900:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1231;
st1231:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1231;
case 1231:
#line 17311 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st1231;
		case 32: goto st1231;
		case 98: goto st1232;
		case 99: goto st1239;
		case 103: goto st1243;
		case 109: goto st1248;
		case 114: goto st1255;
		case 119: goto st1258;
		case 121: goto st1263;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1231;
	goto st0;
tr1837:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1232;
tr1902:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1232;
st1232:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1232;
case 1232:
#line 17338 "configparser.h"
	if ( (*( state.p)) == 108 )
		goto st1233;
	goto st0;
st1233:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1233;
case 1233:
	switch( (*( state.p)) ) {
		case 97: goto st1234;
		case 117: goto st1237;
	}
	goto st0;
st1234:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1234;
case 1234:
	if ( (*( state.p)) == 99 )
		goto st1235;
	goto st0;
st1235:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1235;
case 1235:
	if ( (*( state.p)) == 107 )
		goto st1236;
	goto st0;
st1236:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1236;
case 1236:
	switch( (*( state.p)) ) {
		case 13: goto tr1857;
		case 32: goto tr1857;
		case 59: goto tr1858;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1857;
	goto st0;
st1237:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1237;
case 1237:
	if ( (*( state.p)) == 101 )
		goto st1238;
	goto st0;
st1238:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1238;
case 1238:
	switch( (*( state.p)) ) {
		case 13: goto tr1860;
		case 32: goto tr1860;
		case 59: goto tr1861;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1860;
	goto st0;
tr1838:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1239;
tr1903:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1239;
st1239:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1239;
case 1239:
#line 17408 "configparser.h"
	if ( (*( state.p)) == 121 )
		goto st1240;
	goto st0;
st1240:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1240;
case 1240:
	if ( (*( state.p)) == 97 )
		goto st1241;
	goto st0;
st1241:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1241;
case 1241:
	if ( (*( state.p)) == 110 )
		goto st1242;
	goto st0;
st1242:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1242;
case 1242:
	switch( (*( state.p)) ) {
		case 13: goto tr1865;
		case 32: goto tr1865;
		case 59: goto tr1866;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1865;
	goto st0;
tr1839:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1243;
tr1904:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1243;
st1243:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1243;
case 1243:
#line 17450 "configparser.h"
	if ( (*( state.p)) == 114 )
		goto st1244;
	goto st0;
st1244:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1244;
case 1244:
	if ( (*( state.p)) == 101 )
		goto st1245;
	goto st0;
st1245:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1245;
case 1245:
	if ( (*( state.p)) == 101 )
		goto st1246;
	goto st0;
st1246:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1246;
case 1246:
	if ( (*( state.p)) == 110 )
		goto st1247;
	goto st0;
st1247:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1247;
case 1247:
	switch( (*( state.p)) ) {
		case 13: goto tr1871;
		case 32: goto tr1871;
		case 59: goto tr1872;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1871;
	goto st0;
tr1840:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1248;
tr1905:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1248;
st1248:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1248;
case 1248:
#line 17499 "configparser.h"
	if ( (*( state.p)) == 97 )
		goto st1249;
	goto st0;
st1249:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1249;
case 1249:
	if ( (*( state.p)) == 103 )
		goto st1250;
	goto st0;
st1250:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1250;
case 1250:
	if ( (*( state.p)) == 101 )
		goto st1251;
	goto st0;
st1251:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1251;
case 1251:
	if ( (*( state.p)) == 110 )
		goto st1252;
	goto st0;
st1252:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1252;
case 1252:
	if ( (*( state.p)) == 116 )
		goto st1253;
	goto st0;
st1253:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1253;
case 1253:
	if ( (*( state.p)) == 97 )
		goto st1254;
	goto st0;
st1254:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1254;
case 1254:
	switch( (*( state.p)) ) {
		case 13: goto tr1879;
		case 32: goto tr1879;
		case 59: goto tr1880;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1879;
	goto st0;
tr1841:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1255;
tr1906:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1255;
st1255:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1255;
case 1255:
#line 17562 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st1256;
	goto st0;
st1256:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1256;
case 1256:
	if ( (*( state.p)) == 100 )
		goto st1257;
	goto st0;
st1257:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1257;
case 1257:
	switch( (*( state.p)) ) {
		case 13: goto tr1883;
		case 32: goto tr1883;
		case 59: goto tr1884;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1883;
	goto st0;
tr1842:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1258;
tr1907:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1258;
st1258:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1258;
case 1258:
#line 17597 "configparser.h"
	if ( (*( state.p)) == 104 )
		goto st1259;
	goto st0;
st1259:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1259;
case 1259:
	if ( (*( state.p)) == 105 )
		goto st1260;
	goto st0;
st1260:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1260;
case 1260:
	if ( (*( state.p)) == 116 )
		goto st1261;
	goto st0;
st1261:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1261;
case 1261:
	if ( (*( state.p)) == 101 )
		goto st1262;
	goto st0;
st1262:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1262;
case 1262:
	switch( (*( state.p)) ) {
		case 13: goto tr1889;
		case 32: goto tr1889;
		case 59: goto tr1890;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1889;
	goto st0;
tr1843:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1263;
tr1908:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1263;
st1263:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1263;
case 1263:
#line 17646 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st1264;
	goto st0;
st1264:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1264;
case 1264:
	if ( (*( state.p)) == 108 )
		goto st1265;
	goto st0;
st1265:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1265;
case 1265:
	if ( (*( state.p)) == 108 )
		goto st1266;
	goto st0;
st1266:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1266;
case 1266:
	if ( (*( state.p)) == 111 )
		goto st1267;
	goto st0;
st1267:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1267;
case 1267:
	if ( (*( state.p)) == 119 )
		goto st1268;
	goto st0;
st1268:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1268;
case 1268:
	switch( (*( state.p)) ) {
		case 13: goto tr1896;
		case 32: goto tr1896;
		case 59: goto tr1897;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1896;
	goto st0;
tr1836:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1269;
tr1901:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1269;
st1269:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1269;
case 1269:
#line 17702 "configparser.h"
	switch( (*( state.p)) ) {
		case 98: goto st1232;
		case 99: goto st1239;
		case 103: goto st1243;
		case 109: goto st1248;
		case 114: goto st1255;
		case 119: goto st1258;
		case 121: goto st1263;
	}
	goto st0;
st1270:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1270;
case 1270:
	if ( (*( state.p)) == 105 )
		goto st1271;
	goto st0;
st1271:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1271;
case 1271:
	if ( (*( state.p)) == 109 )
		goto st1272;
	goto st0;
st1272:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1272;
case 1272:
	switch( (*( state.p)) ) {
		case 13: goto tr1900;
		case 32: goto tr1900;
		case 95: goto tr1901;
		case 98: goto tr1902;
		case 99: goto tr1903;
		case 103: goto tr1904;
		case 109: goto tr1905;
		case 114: goto tr1906;
		case 119: goto tr1907;
		case 121: goto tr1908;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1900;
	goto st0;
st1273:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1273;
case 1273:
	if ( (*( state.p)) == 111 )
		goto st1274;
	goto st0;
st1274:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1274;
case 1274:
	if ( (*( state.p)) == 110 )
		goto st1275;
	goto st0;
st1275:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1275;
case 1275:
	if ( (*( state.p)) == 101 )
		goto st1236;
	goto st0;
st1276:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1276;
case 1276:
	if ( (*( state.p)) == 105 )
		goto st1277;
	goto st0;
st1277:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1277;
case 1277:
	if ( (*( state.p)) == 103 )
		goto st1278;
	goto st0;
st1278:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1278;
case 1278:
	if ( (*( state.p)) == 104 )
		goto st1279;
	goto st0;
st1279:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1279;
case 1279:
	if ( (*( state.p)) == 116 )
		goto st1280;
	goto st0;
st1280:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1280;
case 1280:
	if ( (*( state.p)) == 114 )
		goto st1281;
	goto st0;
st1281:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1281;
case 1281:
	if ( (*( state.p)) == 97 )
		goto st1282;
	goto st0;
st1282:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1282;
case 1282:
	if ( (*( state.p)) == 100 )
		goto st1283;
	goto st0;
st1283:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1283;
case 1283:
	if ( (*( state.p)) == 105 )
		goto st1284;
	goto st0;
st1284:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1284;
case 1284:
	if ( (*( state.p)) == 117 )
		goto st1285;
	goto st0;
st1285:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1285;
case 1285:
	if ( (*( state.p)) == 115 )
		goto st1286;
	goto st0;
st1286:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1286;
case 1286:
	switch( (*( state.p)) ) {
		case 13: goto st1287;
		case 32: goto st1287;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1287;
	goto st0;
st1287:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1287;
case 1287:
	switch( (*( state.p)) ) {
		case 13: goto st1287;
		case 32: goto st1287;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1922;
	} else if ( (*( state.p)) >= 9 )
		goto st1287;
	goto st0;
tr1922:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1288;
tr1924:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1288;
st1288:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1288;
case 1288:
#line 17882 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1923;
		case 32: goto tr1923;
		case 59: goto tr1925;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1924;
	} else if ( (*( state.p)) >= 9 )
		goto tr1923;
	goto st0;
st1289:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1289;
case 1289:
	if ( (*( state.p)) == 104 )
		goto st1290;
	goto st0;
st1290:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1290;
case 1290:
	if ( (*( state.p)) == 97 )
		goto st1291;
	goto st0;
st1291:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1291;
case 1291:
	if ( (*( state.p)) == 108 )
		goto st1292;
	goto st0;
st1292:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1292;
case 1292:
	if ( (*( state.p)) == 108 )
		goto st1293;
	goto st0;
st1293:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1293;
case 1293:
	if ( (*( state.p)) == 111 )
		goto st1294;
	goto st0;
st1294:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1294;
case 1294:
	if ( (*( state.p)) == 119 )
		goto st1295;
	goto st0;
st1295:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1295;
case 1295:
	if ( (*( state.p)) == 95 )
		goto st1296;
	goto st0;
st1296:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1296;
case 1296:
	if ( (*( state.p)) == 119 )
		goto st1297;
	goto st0;
st1297:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1297;
case 1297:
	if ( (*( state.p)) == 97 )
		goto st1298;
	goto st0;
st1298:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1298;
case 1298:
	if ( (*( state.p)) == 116 )
		goto st1299;
	goto st0;
st1299:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1299;
case 1299:
	if ( (*( state.p)) == 101 )
		goto st1300;
	goto st0;
st1300:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1300;
case 1300:
	if ( (*( state.p)) == 114 )
		goto st1301;
	goto st0;
st1301:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1301;
case 1301:
	switch( (*( state.p)) ) {
		case 13: goto st1302;
		case 32: goto st1302;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1302;
	goto st0;
st1302:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1302;
case 1302:
	switch( (*( state.p)) ) {
		case 13: goto st1302;
		case 32: goto st1302;
		case 34: goto tr1939;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1302;
	goto st0;
tr1940:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1303;
tr1939:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1303;
tr1942:
#line 144 "configparser.rl"
	{{ state.stack[ state.top++] = 1303; goto st47;}}
	goto st1303;
st1303:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1303;
case 1303:
#line 18021 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st1304;
		case 92: goto tr1942;
	}
	goto tr1940;
st1304:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1304;
case 1304:
	switch( (*( state.p)) ) {
		case 13: goto tr1943;
		case 32: goto tr1943;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1943;
	goto st0;
tr1943:
#line 166 "configparser.rl"
	{ skin.text = state.match; }
	goto st1305;
st1305:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1305;
case 1305:
#line 18046 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st1305;
		case 32: goto st1305;
		case 98: goto st1306;
		case 100: goto st1351;
		case 110: goto st1354;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1305;
	goto st0;
st1306:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1306;
case 1306:
	if ( (*( state.p)) == 114 )
		goto st1307;
	goto st0;
st1307:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1307;
case 1307:
	if ( (*( state.p)) == 105 )
		goto st1308;
	goto st0;
st1308:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1308;
case 1308:
	if ( (*( state.p)) == 103 )
		goto st1309;
	goto st0;
st1309:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1309;
case 1309:
	if ( (*( state.p)) == 104 )
		goto st1310;
	goto st0;
st1310:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1310;
case 1310:
	if ( (*( state.p)) == 116 )
		goto st1311;
	goto st0;
st1311:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1311;
case 1311:
	switch( (*( state.p)) ) {
		case 13: goto tr1953;
		case 32: goto tr1953;
		case 95: goto tr1954;
		case 98: goto tr1955;
		case 99: goto tr1956;
		case 103: goto tr1957;
		case 109: goto tr1958;
		case 114: goto tr1959;
		case 119: goto tr1960;
		case 121: goto tr1961;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1953;
	goto st0;
tr1953:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1312;
tr2018:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1312;
st1312:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1312;
case 1312:
#line 18123 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st1312;
		case 32: goto st1312;
		case 98: goto st1313;
		case 99: goto st1320;
		case 103: goto st1324;
		case 109: goto st1329;
		case 114: goto st1336;
		case 119: goto st1339;
		case 121: goto st1344;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1312;
	goto st0;
tr1955:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1313;
tr2020:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1313;
st1313:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1313;
case 1313:
#line 18150 "configparser.h"
	if ( (*( state.p)) == 108 )
		goto st1314;
	goto st0;
st1314:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1314;
case 1314:
	switch( (*( state.p)) ) {
		case 97: goto st1315;
		case 117: goto st1318;
	}
	goto st0;
st1315:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1315;
case 1315:
	if ( (*( state.p)) == 99 )
		goto st1316;
	goto st0;
st1316:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1316;
case 1316:
	if ( (*( state.p)) == 107 )
		goto st1317;
	goto st0;
st1317:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1317;
case 1317:
	switch( (*( state.p)) ) {
		case 13: goto tr1975;
		case 32: goto tr1975;
		case 59: goto tr1976;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1975;
	goto st0;
st1318:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1318;
case 1318:
	if ( (*( state.p)) == 101 )
		goto st1319;
	goto st0;
st1319:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1319;
case 1319:
	switch( (*( state.p)) ) {
		case 13: goto tr1978;
		case 32: goto tr1978;
		case 59: goto tr1979;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1978;
	goto st0;
tr1956:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1320;
tr2021:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1320;
st1320:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1320;
case 1320:
#line 18220 "configparser.h"
	if ( (*( state.p)) == 121 )
		goto st1321;
	goto st0;
st1321:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1321;
case 1321:
	if ( (*( state.p)) == 97 )
		goto st1322;
	goto st0;
st1322:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1322;
case 1322:
	if ( (*( state.p)) == 110 )
		goto st1323;
	goto st0;
st1323:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1323;
case 1323:
	switch( (*( state.p)) ) {
		case 13: goto tr1983;
		case 32: goto tr1983;
		case 59: goto tr1984;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1983;
	goto st0;
tr1957:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1324;
tr2022:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1324;
st1324:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1324;
case 1324:
#line 18262 "configparser.h"
	if ( (*( state.p)) == 114 )
		goto st1325;
	goto st0;
st1325:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1325;
case 1325:
	if ( (*( state.p)) == 101 )
		goto st1326;
	goto st0;
st1326:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1326;
case 1326:
	if ( (*( state.p)) == 101 )
		goto st1327;
	goto st0;
st1327:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1327;
case 1327:
	if ( (*( state.p)) == 110 )
		goto st1328;
	goto st0;
st1328:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1328;
case 1328:
	switch( (*( state.p)) ) {
		case 13: goto tr1989;
		case 32: goto tr1989;
		case 59: goto tr1990;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1989;
	goto st0;
tr1958:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1329;
tr2023:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1329;
st1329:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1329;
case 1329:
#line 18311 "configparser.h"
	if ( (*( state.p)) == 97 )
		goto st1330;
	goto st0;
st1330:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1330;
case 1330:
	if ( (*( state.p)) == 103 )
		goto st1331;
	goto st0;
st1331:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1331;
case 1331:
	if ( (*( state.p)) == 101 )
		goto st1332;
	goto st0;
st1332:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1332;
case 1332:
	if ( (*( state.p)) == 110 )
		goto st1333;
	goto st0;
st1333:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1333;
case 1333:
	if ( (*( state.p)) == 116 )
		goto st1334;
	goto st0;
st1334:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1334;
case 1334:
	if ( (*( state.p)) == 97 )
		goto st1335;
	goto st0;
st1335:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1335;
case 1335:
	switch( (*( state.p)) ) {
		case 13: goto tr1997;
		case 32: goto tr1997;
		case 59: goto tr1998;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1997;
	goto st0;
tr1959:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1336;
tr2024:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1336;
st1336:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1336;
case 1336:
#line 18374 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st1337;
	goto st0;
st1337:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1337;
case 1337:
	if ( (*( state.p)) == 100 )
		goto st1338;
	goto st0;
st1338:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1338;
case 1338:
	switch( (*( state.p)) ) {
		case 13: goto tr2001;
		case 32: goto tr2001;
		case 59: goto tr2002;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2001;
	goto st0;
tr1960:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1339;
tr2025:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1339;
st1339:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1339;
case 1339:
#line 18409 "configparser.h"
	if ( (*( state.p)) == 104 )
		goto st1340;
	goto st0;
st1340:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1340;
case 1340:
	if ( (*( state.p)) == 105 )
		goto st1341;
	goto st0;
st1341:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1341;
case 1341:
	if ( (*( state.p)) == 116 )
		goto st1342;
	goto st0;
st1342:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1342;
case 1342:
	if ( (*( state.p)) == 101 )
		goto st1343;
	goto st0;
st1343:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1343;
case 1343:
	switch( (*( state.p)) ) {
		case 13: goto tr2007;
		case 32: goto tr2007;
		case 59: goto tr2008;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2007;
	goto st0;
tr1961:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1344;
tr2026:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1344;
st1344:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1344;
case 1344:
#line 18458 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st1345;
	goto st0;
st1345:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1345;
case 1345:
	if ( (*( state.p)) == 108 )
		goto st1346;
	goto st0;
st1346:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1346;
case 1346:
	if ( (*( state.p)) == 108 )
		goto st1347;
	goto st0;
st1347:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1347;
case 1347:
	if ( (*( state.p)) == 111 )
		goto st1348;
	goto st0;
st1348:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1348;
case 1348:
	if ( (*( state.p)) == 119 )
		goto st1349;
	goto st0;
st1349:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1349;
case 1349:
	switch( (*( state.p)) ) {
		case 13: goto tr2014;
		case 32: goto tr2014;
		case 59: goto tr2015;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2014;
	goto st0;
tr1954:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1350;
tr2019:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1350;
st1350:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1350;
case 1350:
#line 18514 "configparser.h"
	switch( (*( state.p)) ) {
		case 98: goto st1313;
		case 99: goto st1320;
		case 103: goto st1324;
		case 109: goto st1329;
		case 114: goto st1336;
		case 119: goto st1339;
		case 121: goto st1344;
	}
	goto st0;
st1351:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1351;
case 1351:
	if ( (*( state.p)) == 105 )
		goto st1352;
	goto st0;
st1352:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1352;
case 1352:
	if ( (*( state.p)) == 109 )
		goto st1353;
	goto st0;
st1353:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1353;
case 1353:
	switch( (*( state.p)) ) {
		case 13: goto tr2018;
		case 32: goto tr2018;
		case 95: goto tr2019;
		case 98: goto tr2020;
		case 99: goto tr2021;
		case 103: goto tr2022;
		case 109: goto tr2023;
		case 114: goto tr2024;
		case 119: goto tr2025;
		case 121: goto tr2026;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2018;
	goto st0;
st1354:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1354;
case 1354:
	if ( (*( state.p)) == 111 )
		goto st1355;
	goto st0;
st1355:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1355;
case 1355:
	if ( (*( state.p)) == 110 )
		goto st1356;
	goto st0;
st1356:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1356;
case 1356:
	if ( (*( state.p)) == 101 )
		goto st1317;
	goto st0;
st1357:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1357;
case 1357:
	if ( (*( state.p)) == 97 )
		goto st1358;
	goto st0;
st1358:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1358;
case 1358:
	switch( (*( state.p)) ) {
		case 108: goto st1359;
		case 116: goto st1416;
	}
	goto st0;
st1359:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1359;
case 1359:
	if ( (*( state.p)) == 108 )
		goto st1360;
	goto st0;
st1360:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1360;
case 1360:
	switch( (*( state.p)) ) {
		case 13: goto st1361;
		case 32: goto st1361;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1361;
	goto st0;
st1361:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1361;
case 1361:
	switch( (*( state.p)) ) {
		case 13: goto st1361;
		case 32: goto st1361;
		case 34: goto tr2034;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1361;
	goto st0;
tr2035:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1362;
tr2034:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1362;
tr2037:
#line 144 "configparser.rl"
	{{ state.stack[ state.top++] = 1362; goto st47;}}
	goto st1362;
st1362:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1362;
case 1362:
#line 18645 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st1363;
		case 92: goto tr2037;
	}
	goto tr2035;
st1363:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1363;
case 1363:
	switch( (*( state.p)) ) {
		case 13: goto tr2038;
		case 32: goto tr2038;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2038;
	goto st0;
tr2038:
#line 166 "configparser.rl"
	{ skin.text = state.match; }
	goto st1364;
st1364:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1364;
case 1364:
#line 18670 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st1364;
		case 32: goto st1364;
		case 98: goto st1365;
		case 100: goto st1410;
		case 110: goto st1413;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1364;
	goto st0;
st1365:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1365;
case 1365:
	if ( (*( state.p)) == 114 )
		goto st1366;
	goto st0;
st1366:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1366;
case 1366:
	if ( (*( state.p)) == 105 )
		goto st1367;
	goto st0;
st1367:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1367;
case 1367:
	if ( (*( state.p)) == 103 )
		goto st1368;
	goto st0;
st1368:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1368;
case 1368:
	if ( (*( state.p)) == 104 )
		goto st1369;
	goto st0;
st1369:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1369;
case 1369:
	if ( (*( state.p)) == 116 )
		goto st1370;
	goto st0;
st1370:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1370;
case 1370:
	switch( (*( state.p)) ) {
		case 13: goto tr2048;
		case 32: goto tr2048;
		case 95: goto tr2049;
		case 98: goto tr2050;
		case 99: goto tr2051;
		case 103: goto tr2052;
		case 109: goto tr2053;
		case 114: goto tr2054;
		case 119: goto tr2055;
		case 121: goto tr2056;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2048;
	goto st0;
tr2048:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1371;
tr2113:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1371;
st1371:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1371;
case 1371:
#line 18747 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st1371;
		case 32: goto st1371;
		case 98: goto st1372;
		case 99: goto st1379;
		case 103: goto st1383;
		case 109: goto st1388;
		case 114: goto st1395;
		case 119: goto st1398;
		case 121: goto st1403;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1371;
	goto st0;
tr2050:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1372;
tr2115:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1372;
st1372:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1372;
case 1372:
#line 18774 "configparser.h"
	if ( (*( state.p)) == 108 )
		goto st1373;
	goto st0;
st1373:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1373;
case 1373:
	switch( (*( state.p)) ) {
		case 97: goto st1374;
		case 117: goto st1377;
	}
	goto st0;
st1374:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1374;
case 1374:
	if ( (*( state.p)) == 99 )
		goto st1375;
	goto st0;
st1375:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1375;
case 1375:
	if ( (*( state.p)) == 107 )
		goto st1376;
	goto st0;
st1376:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1376;
case 1376:
	switch( (*( state.p)) ) {
		case 13: goto tr2070;
		case 32: goto tr2070;
		case 59: goto tr2071;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2070;
	goto st0;
st1377:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1377;
case 1377:
	if ( (*( state.p)) == 101 )
		goto st1378;
	goto st0;
st1378:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1378;
case 1378:
	switch( (*( state.p)) ) {
		case 13: goto tr2073;
		case 32: goto tr2073;
		case 59: goto tr2074;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2073;
	goto st0;
tr2051:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1379;
tr2116:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1379;
st1379:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1379;
case 1379:
#line 18844 "configparser.h"
	if ( (*( state.p)) == 121 )
		goto st1380;
	goto st0;
st1380:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1380;
case 1380:
	if ( (*( state.p)) == 97 )
		goto st1381;
	goto st0;
st1381:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1381;
case 1381:
	if ( (*( state.p)) == 110 )
		goto st1382;
	goto st0;
st1382:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1382;
case 1382:
	switch( (*( state.p)) ) {
		case 13: goto tr2078;
		case 32: goto tr2078;
		case 59: goto tr2079;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2078;
	goto st0;
tr2052:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1383;
tr2117:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1383;
st1383:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1383;
case 1383:
#line 18886 "configparser.h"
	if ( (*( state.p)) == 114 )
		goto st1384;
	goto st0;
st1384:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1384;
case 1384:
	if ( (*( state.p)) == 101 )
		goto st1385;
	goto st0;
st1385:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1385;
case 1385:
	if ( (*( state.p)) == 101 )
		goto st1386;
	goto st0;
st1386:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1386;
case 1386:
	if ( (*( state.p)) == 110 )
		goto st1387;
	goto st0;
st1387:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1387;
case 1387:
	switch( (*( state.p)) ) {
		case 13: goto tr2084;
		case 32: goto tr2084;
		case 59: goto tr2085;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2084;
	goto st0;
tr2053:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1388;
tr2118:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1388;
st1388:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1388;
case 1388:
#line 18935 "configparser.h"
	if ( (*( state.p)) == 97 )
		goto st1389;
	goto st0;
st1389:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1389;
case 1389:
	if ( (*( state.p)) == 103 )
		goto st1390;
	goto st0;
st1390:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1390;
case 1390:
	if ( (*( state.p)) == 101 )
		goto st1391;
	goto st0;
st1391:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1391;
case 1391:
	if ( (*( state.p)) == 110 )
		goto st1392;
	goto st0;
st1392:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1392;
case 1392:
	if ( (*( state.p)) == 116 )
		goto st1393;
	goto st0;
st1393:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1393;
case 1393:
	if ( (*( state.p)) == 97 )
		goto st1394;
	goto st0;
st1394:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1394;
case 1394:
	switch( (*( state.p)) ) {
		case 13: goto tr2092;
		case 32: goto tr2092;
		case 59: goto tr2093;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2092;
	goto st0;
tr2054:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1395;
tr2119:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1395;
st1395:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1395;
case 1395:
#line 18998 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st1396;
	goto st0;
st1396:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1396;
case 1396:
	if ( (*( state.p)) == 100 )
		goto st1397;
	goto st0;
st1397:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1397;
case 1397:
	switch( (*( state.p)) ) {
		case 13: goto tr2096;
		case 32: goto tr2096;
		case 59: goto tr2097;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2096;
	goto st0;
tr2055:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1398;
tr2120:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1398;
st1398:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1398;
case 1398:
#line 19033 "configparser.h"
	if ( (*( state.p)) == 104 )
		goto st1399;
	goto st0;
st1399:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1399;
case 1399:
	if ( (*( state.p)) == 105 )
		goto st1400;
	goto st0;
st1400:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1400;
case 1400:
	if ( (*( state.p)) == 116 )
		goto st1401;
	goto st0;
st1401:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1401;
case 1401:
	if ( (*( state.p)) == 101 )
		goto st1402;
	goto st0;
st1402:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1402;
case 1402:
	switch( (*( state.p)) ) {
		case 13: goto tr2102;
		case 32: goto tr2102;
		case 59: goto tr2103;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2102;
	goto st0;
tr2056:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1403;
tr2121:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1403;
st1403:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1403;
case 1403:
#line 19082 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st1404;
	goto st0;
st1404:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1404;
case 1404:
	if ( (*( state.p)) == 108 )
		goto st1405;
	goto st0;
st1405:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1405;
case 1405:
	if ( (*( state.p)) == 108 )
		goto st1406;
	goto st0;
st1406:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1406;
case 1406:
	if ( (*( state.p)) == 111 )
		goto st1407;
	goto st0;
st1407:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1407;
case 1407:
	if ( (*( state.p)) == 119 )
		goto st1408;
	goto st0;
st1408:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1408;
case 1408:
	switch( (*( state.p)) ) {
		case 13: goto tr2109;
		case 32: goto tr2109;
		case 59: goto tr2110;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2109;
	goto st0;
tr2049:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1409;
tr2114:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1409;
st1409:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1409;
case 1409:
#line 19138 "configparser.h"
	switch( (*( state.p)) ) {
		case 98: goto st1372;
		case 99: goto st1379;
		case 103: goto st1383;
		case 109: goto st1388;
		case 114: goto st1395;
		case 119: goto st1398;
		case 121: goto st1403;
	}
	goto st0;
st1410:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1410;
case 1410:
	if ( (*( state.p)) == 105 )
		goto st1411;
	goto st0;
st1411:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1411;
case 1411:
	if ( (*( state.p)) == 109 )
		goto st1412;
	goto st0;
st1412:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1412;
case 1412:
	switch( (*( state.p)) ) {
		case 13: goto tr2113;
		case 32: goto tr2113;
		case 95: goto tr2114;
		case 98: goto tr2115;
		case 99: goto tr2116;
		case 103: goto tr2117;
		case 109: goto tr2118;
		case 114: goto tr2119;
		case 119: goto tr2120;
		case 121: goto tr2121;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2113;
	goto st0;
st1413:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1413;
case 1413:
	if ( (*( state.p)) == 111 )
		goto st1414;
	goto st0;
st1414:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1414;
case 1414:
	if ( (*( state.p)) == 110 )
		goto st1415;
	goto st0;
st1415:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1415;
case 1415:
	if ( (*( state.p)) == 101 )
		goto st1376;
	goto st0;
st1416:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1416;
case 1416:
	if ( (*( state.p)) == 101 )
		goto st1417;
	goto st0;
st1417:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1417;
case 1417:
	if ( (*( state.p)) == 114 )
		goto st1418;
	goto st0;
st1418:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1418;
case 1418:
	if ( (*( state.p)) == 95 )
		goto st1419;
	goto st0;
st1419:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1419;
case 1419:
	if ( (*( state.p)) == 119 )
		goto st1420;
	goto st0;
st1420:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1420;
case 1420:
	if ( (*( state.p)) == 97 )
		goto st1421;
	goto st0;
st1421:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1421;
case 1421:
	if ( (*( state.p)) == 108 )
		goto st1422;
	goto st0;
st1422:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1422;
case 1422:
	if ( (*( state.p)) == 108 )
		goto st1423;
	goto st0;
st1423:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1423;
case 1423:
	switch( (*( state.p)) ) {
		case 13: goto st1424;
		case 32: goto st1424;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1424;
	goto st0;
st1424:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1424;
case 1424:
	switch( (*( state.p)) ) {
		case 13: goto st1424;
		case 32: goto st1424;
		case 34: goto tr2132;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1424;
	goto st0;
tr2133:
#line 113 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1425;
tr2132:
#line 109 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1425;
tr2135:
#line 144 "configparser.rl"
	{{ state.stack[ state.top++] = 1425; goto st47;}}
	goto st1425;
st1425:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1425;
case 1425:
#line 19295 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st1426;
		case 92: goto tr2135;
	}
	goto tr2133;
st1426:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1426;
case 1426:
	switch( (*( state.p)) ) {
		case 13: goto tr2136;
		case 32: goto tr2136;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2136;
	goto st0;
tr2136:
#line 166 "configparser.rl"
	{ skin.text = state.match; }
	goto st1427;
st1427:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1427;
case 1427:
#line 19320 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st1427;
		case 32: goto st1427;
		case 98: goto st1428;
		case 100: goto st1473;
		case 110: goto st1476;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1427;
	goto st0;
st1428:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1428;
case 1428:
	if ( (*( state.p)) == 114 )
		goto st1429;
	goto st0;
st1429:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1429;
case 1429:
	if ( (*( state.p)) == 105 )
		goto st1430;
	goto st0;
st1430:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1430;
case 1430:
	if ( (*( state.p)) == 103 )
		goto st1431;
	goto st0;
st1431:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1431;
case 1431:
	if ( (*( state.p)) == 104 )
		goto st1432;
	goto st0;
st1432:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1432;
case 1432:
	if ( (*( state.p)) == 116 )
		goto st1433;
	goto st0;
st1433:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1433;
case 1433:
	switch( (*( state.p)) ) {
		case 13: goto tr2146;
		case 32: goto tr2146;
		case 95: goto tr2147;
		case 98: goto tr2148;
		case 99: goto tr2149;
		case 103: goto tr2150;
		case 109: goto tr2151;
		case 114: goto tr2152;
		case 119: goto tr2153;
		case 121: goto tr2154;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2146;
	goto st0;
tr2146:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1434;
tr2211:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1434;
st1434:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1434;
case 1434:
#line 19397 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st1434;
		case 32: goto st1434;
		case 98: goto st1435;
		case 99: goto st1442;
		case 103: goto st1446;
		case 109: goto st1451;
		case 114: goto st1458;
		case 119: goto st1461;
		case 121: goto st1466;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1434;
	goto st0;
tr2148:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1435;
tr2213:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1435;
st1435:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1435;
case 1435:
#line 19424 "configparser.h"
	if ( (*( state.p)) == 108 )
		goto st1436;
	goto st0;
st1436:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1436;
case 1436:
	switch( (*( state.p)) ) {
		case 97: goto st1437;
		case 117: goto st1440;
	}
	goto st0;
st1437:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1437;
case 1437:
	if ( (*( state.p)) == 99 )
		goto st1438;
	goto st0;
st1438:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1438;
case 1438:
	if ( (*( state.p)) == 107 )
		goto st1439;
	goto st0;
st1439:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1439;
case 1439:
	switch( (*( state.p)) ) {
		case 13: goto tr2168;
		case 32: goto tr2168;
		case 59: goto tr2169;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2168;
	goto st0;
st1440:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1440;
case 1440:
	if ( (*( state.p)) == 101 )
		goto st1441;
	goto st0;
st1441:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1441;
case 1441:
	switch( (*( state.p)) ) {
		case 13: goto tr2171;
		case 32: goto tr2171;
		case 59: goto tr2172;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2171;
	goto st0;
tr2149:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1442;
tr2214:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1442;
st1442:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1442;
case 1442:
#line 19494 "configparser.h"
	if ( (*( state.p)) == 121 )
		goto st1443;
	goto st0;
st1443:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1443;
case 1443:
	if ( (*( state.p)) == 97 )
		goto st1444;
	goto st0;
st1444:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1444;
case 1444:
	if ( (*( state.p)) == 110 )
		goto st1445;
	goto st0;
st1445:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1445;
case 1445:
	switch( (*( state.p)) ) {
		case 13: goto tr2176;
		case 32: goto tr2176;
		case 59: goto tr2177;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2176;
	goto st0;
tr2150:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1446;
tr2215:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1446;
st1446:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1446;
case 1446:
#line 19536 "configparser.h"
	if ( (*( state.p)) == 114 )
		goto st1447;
	goto st0;
st1447:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1447;
case 1447:
	if ( (*( state.p)) == 101 )
		goto st1448;
	goto st0;
st1448:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1448;
case 1448:
	if ( (*( state.p)) == 101 )
		goto st1449;
	goto st0;
st1449:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1449;
case 1449:
	if ( (*( state.p)) == 110 )
		goto st1450;
	goto st0;
st1450:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1450;
case 1450:
	switch( (*( state.p)) ) {
		case 13: goto tr2182;
		case 32: goto tr2182;
		case 59: goto tr2183;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2182;
	goto st0;
tr2151:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1451;
tr2216:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1451;
st1451:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1451;
case 1451:
#line 19585 "configparser.h"
	if ( (*( state.p)) == 97 )
		goto st1452;
	goto st0;
st1452:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1452;
case 1452:
	if ( (*( state.p)) == 103 )
		goto st1453;
	goto st0;
st1453:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1453;
case 1453:
	if ( (*( state.p)) == 101 )
		goto st1454;
	goto st0;
st1454:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1454;
case 1454:
	if ( (*( state.p)) == 110 )
		goto st1455;
	goto st0;
st1455:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1455;
case 1455:
	if ( (*( state.p)) == 116 )
		goto st1456;
	goto st0;
st1456:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1456;
case 1456:
	if ( (*( state.p)) == 97 )
		goto st1457;
	goto st0;
st1457:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1457;
case 1457:
	switch( (*( state.p)) ) {
		case 13: goto tr2190;
		case 32: goto tr2190;
		case 59: goto tr2191;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2190;
	goto st0;
tr2152:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1458;
tr2217:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1458;
st1458:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1458;
case 1458:
#line 19648 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st1459;
	goto st0;
st1459:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1459;
case 1459:
	if ( (*( state.p)) == 100 )
		goto st1460;
	goto st0;
st1460:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1460;
case 1460:
	switch( (*( state.p)) ) {
		case 13: goto tr2194;
		case 32: goto tr2194;
		case 59: goto tr2195;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2194;
	goto st0;
tr2153:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1461;
tr2218:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1461;
st1461:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1461;
case 1461:
#line 19683 "configparser.h"
	if ( (*( state.p)) == 104 )
		goto st1462;
	goto st0;
st1462:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1462;
case 1462:
	if ( (*( state.p)) == 105 )
		goto st1463;
	goto st0;
st1463:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1463;
case 1463:
	if ( (*( state.p)) == 116 )
		goto st1464;
	goto st0;
st1464:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1464;
case 1464:
	if ( (*( state.p)) == 101 )
		goto st1465;
	goto st0;
st1465:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1465;
case 1465:
	switch( (*( state.p)) ) {
		case 13: goto tr2200;
		case 32: goto tr2200;
		case 59: goto tr2201;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2200;
	goto st0;
tr2154:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1466;
tr2219:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1466;
st1466:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1466;
case 1466:
#line 19732 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st1467;
	goto st0;
st1467:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1467;
case 1467:
	if ( (*( state.p)) == 108 )
		goto st1468;
	goto st0;
st1468:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1468;
case 1468:
	if ( (*( state.p)) == 108 )
		goto st1469;
	goto st0;
st1469:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1469;
case 1469:
	if ( (*( state.p)) == 111 )
		goto st1470;
	goto st0;
st1470:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1470;
case 1470:
	if ( (*( state.p)) == 119 )
		goto st1471;
	goto st0;
st1471:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1471;
case 1471:
	switch( (*( state.p)) ) {
		case 13: goto tr2207;
		case 32: goto tr2207;
		case 59: goto tr2208;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2207;
	goto st0;
tr2147:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1472;
tr2212:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1472;
st1472:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1472;
case 1472:
#line 19788 "configparser.h"
	switch( (*( state.p)) ) {
		case 98: goto st1435;
		case 99: goto st1442;
		case 103: goto st1446;
		case 109: goto st1451;
		case 114: goto st1458;
		case 119: goto st1461;
		case 121: goto st1466;
	}
	goto st0;
st1473:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1473;
case 1473:
	if ( (*( state.p)) == 105 )
		goto st1474;
	goto st0;
st1474:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1474;
case 1474:
	if ( (*( state.p)) == 109 )
		goto st1475;
	goto st0;
st1475:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1475;
case 1475:
	switch( (*( state.p)) ) {
		case 13: goto tr2211;
		case 32: goto tr2211;
		case 95: goto tr2212;
		case 98: goto tr2213;
		case 99: goto tr2214;
		case 103: goto tr2215;
		case 109: goto tr2216;
		case 114: goto tr2217;
		case 119: goto tr2218;
		case 121: goto tr2219;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2211;
	goto st0;
st1476:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1476;
case 1476:
	if ( (*( state.p)) == 111 )
		goto st1477;
	goto st0;
st1477:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1477;
case 1477:
	if ( (*( state.p)) == 110 )
		goto st1478;
	goto st0;
st1478:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1478;
case 1478:
	if ( (*( state.p)) == 101 )
		goto st1439;
	goto st0;
st1479:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1479;
case 1479:
	if ( (*( state.p)) == 101 )
		goto st1480;
	goto st0;
st1480:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1480;
case 1480:
	switch( (*( state.p)) ) {
		case 13: goto tr2223;
		case 32: goto tr2223;
		case 59: goto tr2224;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2223;
	goto st0;
tr1148:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1481;
tr2266:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1481;
st1481:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1481;
case 1481:
#line 19884 "configparser.h"
	if ( (*( state.p)) == 121 )
		goto st1482;
	goto st0;
st1482:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1482;
case 1482:
	if ( (*( state.p)) == 97 )
		goto st1483;
	goto st0;
st1483:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1483;
case 1483:
	if ( (*( state.p)) == 110 )
		goto st1484;
	goto st0;
st1484:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1484;
case 1484:
	switch( (*( state.p)) ) {
		case 13: goto tr2228;
		case 32: goto tr2228;
		case 59: goto tr2229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2228;
	goto st0;
tr1149:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1485;
tr2267:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1485;
st1485:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1485;
case 1485:
#line 19926 "configparser.h"
	if ( (*( state.p)) == 114 )
		goto st1486;
	goto st0;
st1486:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1486;
case 1486:
	if ( (*( state.p)) == 101 )
		goto st1487;
	goto st0;
st1487:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1487;
case 1487:
	if ( (*( state.p)) == 101 )
		goto st1488;
	goto st0;
st1488:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1488;
case 1488:
	if ( (*( state.p)) == 110 )
		goto st1489;
	goto st0;
st1489:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1489;
case 1489:
	switch( (*( state.p)) ) {
		case 13: goto tr2234;
		case 32: goto tr2234;
		case 59: goto tr2235;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2234;
	goto st0;
tr1150:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1490;
tr2268:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1490;
st1490:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1490;
case 1490:
#line 19975 "configparser.h"
	if ( (*( state.p)) == 97 )
		goto st1491;
	goto st0;
st1491:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1491;
case 1491:
	if ( (*( state.p)) == 103 )
		goto st1492;
	goto st0;
st1492:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1492;
case 1492:
	if ( (*( state.p)) == 101 )
		goto st1493;
	goto st0;
st1493:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1493;
case 1493:
	if ( (*( state.p)) == 110 )
		goto st1494;
	goto st0;
st1494:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1494;
case 1494:
	if ( (*( state.p)) == 116 )
		goto st1495;
	goto st0;
st1495:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1495;
case 1495:
	if ( (*( state.p)) == 97 )
		goto st1496;
	goto st0;
st1496:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1496;
case 1496:
	switch( (*( state.p)) ) {
		case 13: goto tr2242;
		case 32: goto tr2242;
		case 59: goto tr2243;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2242;
	goto st0;
tr1151:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1497;
tr2269:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1497;
st1497:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1497;
case 1497:
#line 20038 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st1498;
	goto st0;
st1498:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1498;
case 1498:
	if ( (*( state.p)) == 100 )
		goto st1499;
	goto st0;
st1499:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1499;
case 1499:
	switch( (*( state.p)) ) {
		case 13: goto tr2246;
		case 32: goto tr2246;
		case 59: goto tr2247;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2246;
	goto st0;
tr1152:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1500;
tr2270:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1500;
st1500:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1500;
case 1500:
#line 20073 "configparser.h"
	if ( (*( state.p)) == 104 )
		goto st1501;
	goto st0;
st1501:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1501;
case 1501:
	if ( (*( state.p)) == 105 )
		goto st1502;
	goto st0;
st1502:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1502;
case 1502:
	if ( (*( state.p)) == 116 )
		goto st1503;
	goto st0;
st1503:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1503;
case 1503:
	if ( (*( state.p)) == 101 )
		goto st1504;
	goto st0;
st1504:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1504;
case 1504:
	switch( (*( state.p)) ) {
		case 13: goto tr2252;
		case 32: goto tr2252;
		case 59: goto tr2253;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2252;
	goto st0;
tr1153:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1505;
tr2271:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1505;
st1505:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1505;
case 1505:
#line 20122 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st1506;
	goto st0;
st1506:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1506;
case 1506:
	if ( (*( state.p)) == 108 )
		goto st1507;
	goto st0;
st1507:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1507;
case 1507:
	if ( (*( state.p)) == 108 )
		goto st1508;
	goto st0;
st1508:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1508;
case 1508:
	if ( (*( state.p)) == 111 )
		goto st1509;
	goto st0;
st1509:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1509;
case 1509:
	if ( (*( state.p)) == 119 )
		goto st1510;
	goto st0;
st1510:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1510;
case 1510:
	switch( (*( state.p)) ) {
		case 13: goto tr2259;
		case 32: goto tr2259;
		case 59: goto tr2260;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2259;
	goto st0;
tr1146:
#line 164 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1511;
tr2264:
#line 163 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1511;
st1511:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1511;
case 1511:
#line 20178 "configparser.h"
	switch( (*( state.p)) ) {
		case 98: goto st817;
		case 99: goto st1481;
		case 103: goto st1485;
		case 109: goto st1490;
		case 114: goto st1497;
		case 119: goto st1500;
		case 121: goto st1505;
	}
	goto st0;
st1512:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1512;
case 1512:
	if ( (*( state.p)) == 105 )
		goto st1513;
	goto st0;
st1513:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1513;
case 1513:
	if ( (*( state.p)) == 109 )
		goto st1514;
	goto st0;
st1514:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1514;
case 1514:
	switch( (*( state.p)) ) {
		case 13: goto tr2263;
		case 32: goto tr2263;
		case 95: goto tr2264;
		case 98: goto tr2265;
		case 99: goto tr2266;
		case 103: goto tr2267;
		case 109: goto tr2268;
		case 114: goto tr2269;
		case 119: goto tr2270;
		case 121: goto tr2271;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2263;
	goto st0;
st1515:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1515;
case 1515:
	if ( (*( state.p)) == 111 )
		goto st1516;
	goto st0;
st1516:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1516;
case 1516:
	if ( (*( state.p)) == 110 )
		goto st1517;
	goto st0;
st1517:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1517;
case 1517:
	if ( (*( state.p)) == 101 )
		goto st821;
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
	_test_eof1518:  state.cs = 1518; goto _test_eof; 
	_test_eof1519:  state.cs = 1519; goto _test_eof; 
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
	_test_eof1520:  state.cs = 1520; goto _test_eof; 
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
	_test_eof35:  state.cs = 35; goto _test_eof; 
	_test_eof36:  state.cs = 36; goto _test_eof; 
	_test_eof1521:  state.cs = 1521; goto _test_eof; 
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
	_test_eof1522:  state.cs = 1522; goto _test_eof; 
	_test_eof47:  state.cs = 47; goto _test_eof; 
	_test_eof1523:  state.cs = 1523; goto _test_eof; 
	_test_eof48:  state.cs = 48; goto _test_eof; 
	_test_eof49:  state.cs = 49; goto _test_eof; 
	_test_eof50:  state.cs = 50; goto _test_eof; 
	_test_eof51:  state.cs = 51; goto _test_eof; 
	_test_eof52:  state.cs = 52; goto _test_eof; 
	_test_eof53:  state.cs = 53; goto _test_eof; 
	_test_eof54:  state.cs = 54; goto _test_eof; 
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
	_test_eof1524:  state.cs = 1524; goto _test_eof; 
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
	_test_eof1525:  state.cs = 1525; goto _test_eof; 
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
	_test_eof588:  state.cs = 588; goto _test_eof; 
	_test_eof589:  state.cs = 589; goto _test_eof; 
	_test_eof590:  state.cs = 590; goto _test_eof; 
	_test_eof591:  state.cs = 591; goto _test_eof; 
	_test_eof592:  state.cs = 592; goto _test_eof; 
	_test_eof593:  state.cs = 593; goto _test_eof; 
	_test_eof594:  state.cs = 594; goto _test_eof; 
	_test_eof595:  state.cs = 595; goto _test_eof; 
	_test_eof596:  state.cs = 596; goto _test_eof; 
	_test_eof597:  state.cs = 597; goto _test_eof; 
	_test_eof598:  state.cs = 598; goto _test_eof; 
	_test_eof599:  state.cs = 599; goto _test_eof; 
	_test_eof600:  state.cs = 600; goto _test_eof; 
	_test_eof601:  state.cs = 601; goto _test_eof; 
	_test_eof602:  state.cs = 602; goto _test_eof; 
	_test_eof603:  state.cs = 603; goto _test_eof; 
	_test_eof604:  state.cs = 604; goto _test_eof; 
	_test_eof605:  state.cs = 605; goto _test_eof; 
	_test_eof606:  state.cs = 606; goto _test_eof; 
	_test_eof607:  state.cs = 607; goto _test_eof; 
	_test_eof608:  state.cs = 608; goto _test_eof; 
	_test_eof609:  state.cs = 609; goto _test_eof; 
	_test_eof610:  state.cs = 610; goto _test_eof; 
	_test_eof611:  state.cs = 611; goto _test_eof; 
	_test_eof612:  state.cs = 612; goto _test_eof; 
	_test_eof613:  state.cs = 613; goto _test_eof; 
	_test_eof614:  state.cs = 614; goto _test_eof; 
	_test_eof615:  state.cs = 615; goto _test_eof; 
	_test_eof616:  state.cs = 616; goto _test_eof; 
	_test_eof617:  state.cs = 617; goto _test_eof; 
	_test_eof618:  state.cs = 618; goto _test_eof; 
	_test_eof619:  state.cs = 619; goto _test_eof; 
	_test_eof1526:  state.cs = 1526; goto _test_eof; 
	_test_eof620:  state.cs = 620; goto _test_eof; 
	_test_eof621:  state.cs = 621; goto _test_eof; 
	_test_eof622:  state.cs = 622; goto _test_eof; 
	_test_eof623:  state.cs = 623; goto _test_eof; 
	_test_eof624:  state.cs = 624; goto _test_eof; 
	_test_eof625:  state.cs = 625; goto _test_eof; 
	_test_eof626:  state.cs = 626; goto _test_eof; 
	_test_eof627:  state.cs = 627; goto _test_eof; 
	_test_eof628:  state.cs = 628; goto _test_eof; 
	_test_eof629:  state.cs = 629; goto _test_eof; 
	_test_eof630:  state.cs = 630; goto _test_eof; 
	_test_eof631:  state.cs = 631; goto _test_eof; 
	_test_eof632:  state.cs = 632; goto _test_eof; 
	_test_eof633:  state.cs = 633; goto _test_eof; 
	_test_eof634:  state.cs = 634; goto _test_eof; 
	_test_eof635:  state.cs = 635; goto _test_eof; 
	_test_eof636:  state.cs = 636; goto _test_eof; 
	_test_eof637:  state.cs = 637; goto _test_eof; 
	_test_eof638:  state.cs = 638; goto _test_eof; 
	_test_eof639:  state.cs = 639; goto _test_eof; 
	_test_eof640:  state.cs = 640; goto _test_eof; 
	_test_eof641:  state.cs = 641; goto _test_eof; 
	_test_eof642:  state.cs = 642; goto _test_eof; 
	_test_eof643:  state.cs = 643; goto _test_eof; 
	_test_eof644:  state.cs = 644; goto _test_eof; 
	_test_eof645:  state.cs = 645; goto _test_eof; 
	_test_eof646:  state.cs = 646; goto _test_eof; 
	_test_eof647:  state.cs = 647; goto _test_eof; 
	_test_eof648:  state.cs = 648; goto _test_eof; 
	_test_eof649:  state.cs = 649; goto _test_eof; 
	_test_eof650:  state.cs = 650; goto _test_eof; 
	_test_eof651:  state.cs = 651; goto _test_eof; 
	_test_eof652:  state.cs = 652; goto _test_eof; 
	_test_eof653:  state.cs = 653; goto _test_eof; 
	_test_eof654:  state.cs = 654; goto _test_eof; 
	_test_eof655:  state.cs = 655; goto _test_eof; 
	_test_eof656:  state.cs = 656; goto _test_eof; 
	_test_eof657:  state.cs = 657; goto _test_eof; 
	_test_eof658:  state.cs = 658; goto _test_eof; 
	_test_eof659:  state.cs = 659; goto _test_eof; 
	_test_eof660:  state.cs = 660; goto _test_eof; 
	_test_eof661:  state.cs = 661; goto _test_eof; 
	_test_eof662:  state.cs = 662; goto _test_eof; 
	_test_eof663:  state.cs = 663; goto _test_eof; 
	_test_eof664:  state.cs = 664; goto _test_eof; 
	_test_eof665:  state.cs = 665; goto _test_eof; 
	_test_eof666:  state.cs = 666; goto _test_eof; 
	_test_eof667:  state.cs = 667; goto _test_eof; 
	_test_eof668:  state.cs = 668; goto _test_eof; 
	_test_eof669:  state.cs = 669; goto _test_eof; 
	_test_eof670:  state.cs = 670; goto _test_eof; 
	_test_eof671:  state.cs = 671; goto _test_eof; 
	_test_eof672:  state.cs = 672; goto _test_eof; 
	_test_eof673:  state.cs = 673; goto _test_eof; 
	_test_eof674:  state.cs = 674; goto _test_eof; 
	_test_eof675:  state.cs = 675; goto _test_eof; 
	_test_eof676:  state.cs = 676; goto _test_eof; 
	_test_eof677:  state.cs = 677; goto _test_eof; 
	_test_eof678:  state.cs = 678; goto _test_eof; 
	_test_eof679:  state.cs = 679; goto _test_eof; 
	_test_eof680:  state.cs = 680; goto _test_eof; 
	_test_eof681:  state.cs = 681; goto _test_eof; 
	_test_eof682:  state.cs = 682; goto _test_eof; 
	_test_eof683:  state.cs = 683; goto _test_eof; 
	_test_eof684:  state.cs = 684; goto _test_eof; 
	_test_eof685:  state.cs = 685; goto _test_eof; 
	_test_eof686:  state.cs = 686; goto _test_eof; 
	_test_eof687:  state.cs = 687; goto _test_eof; 
	_test_eof688:  state.cs = 688; goto _test_eof; 
	_test_eof689:  state.cs = 689; goto _test_eof; 
	_test_eof690:  state.cs = 690; goto _test_eof; 
	_test_eof691:  state.cs = 691; goto _test_eof; 
	_test_eof692:  state.cs = 692; goto _test_eof; 
	_test_eof693:  state.cs = 693; goto _test_eof; 
	_test_eof694:  state.cs = 694; goto _test_eof; 
	_test_eof695:  state.cs = 695; goto _test_eof; 
	_test_eof696:  state.cs = 696; goto _test_eof; 
	_test_eof697:  state.cs = 697; goto _test_eof; 
	_test_eof698:  state.cs = 698; goto _test_eof; 
	_test_eof699:  state.cs = 699; goto _test_eof; 
	_test_eof700:  state.cs = 700; goto _test_eof; 
	_test_eof701:  state.cs = 701; goto _test_eof; 
	_test_eof702:  state.cs = 702; goto _test_eof; 
	_test_eof703:  state.cs = 703; goto _test_eof; 
	_test_eof704:  state.cs = 704; goto _test_eof; 
	_test_eof705:  state.cs = 705; goto _test_eof; 
	_test_eof706:  state.cs = 706; goto _test_eof; 
	_test_eof707:  state.cs = 707; goto _test_eof; 
	_test_eof708:  state.cs = 708; goto _test_eof; 
	_test_eof709:  state.cs = 709; goto _test_eof; 
	_test_eof710:  state.cs = 710; goto _test_eof; 
	_test_eof711:  state.cs = 711; goto _test_eof; 
	_test_eof712:  state.cs = 712; goto _test_eof; 
	_test_eof713:  state.cs = 713; goto _test_eof; 
	_test_eof714:  state.cs = 714; goto _test_eof; 
	_test_eof715:  state.cs = 715; goto _test_eof; 
	_test_eof716:  state.cs = 716; goto _test_eof; 
	_test_eof717:  state.cs = 717; goto _test_eof; 
	_test_eof718:  state.cs = 718; goto _test_eof; 
	_test_eof719:  state.cs = 719; goto _test_eof; 
	_test_eof720:  state.cs = 720; goto _test_eof; 
	_test_eof721:  state.cs = 721; goto _test_eof; 
	_test_eof722:  state.cs = 722; goto _test_eof; 
	_test_eof723:  state.cs = 723; goto _test_eof; 
	_test_eof724:  state.cs = 724; goto _test_eof; 
	_test_eof725:  state.cs = 725; goto _test_eof; 
	_test_eof726:  state.cs = 726; goto _test_eof; 
	_test_eof727:  state.cs = 727; goto _test_eof; 
	_test_eof728:  state.cs = 728; goto _test_eof; 
	_test_eof729:  state.cs = 729; goto _test_eof; 
	_test_eof730:  state.cs = 730; goto _test_eof; 
	_test_eof731:  state.cs = 731; goto _test_eof; 
	_test_eof732:  state.cs = 732; goto _test_eof; 
	_test_eof733:  state.cs = 733; goto _test_eof; 
	_test_eof734:  state.cs = 734; goto _test_eof; 
	_test_eof735:  state.cs = 735; goto _test_eof; 
	_test_eof736:  state.cs = 736; goto _test_eof; 
	_test_eof737:  state.cs = 737; goto _test_eof; 
	_test_eof738:  state.cs = 738; goto _test_eof; 
	_test_eof739:  state.cs = 739; goto _test_eof; 
	_test_eof740:  state.cs = 740; goto _test_eof; 
	_test_eof741:  state.cs = 741; goto _test_eof; 
	_test_eof742:  state.cs = 742; goto _test_eof; 
	_test_eof743:  state.cs = 743; goto _test_eof; 
	_test_eof744:  state.cs = 744; goto _test_eof; 
	_test_eof745:  state.cs = 745; goto _test_eof; 
	_test_eof746:  state.cs = 746; goto _test_eof; 
	_test_eof747:  state.cs = 747; goto _test_eof; 
	_test_eof748:  state.cs = 748; goto _test_eof; 
	_test_eof749:  state.cs = 749; goto _test_eof; 
	_test_eof750:  state.cs = 750; goto _test_eof; 
	_test_eof751:  state.cs = 751; goto _test_eof; 
	_test_eof752:  state.cs = 752; goto _test_eof; 
	_test_eof753:  state.cs = 753; goto _test_eof; 
	_test_eof754:  state.cs = 754; goto _test_eof; 
	_test_eof755:  state.cs = 755; goto _test_eof; 
	_test_eof756:  state.cs = 756; goto _test_eof; 
	_test_eof757:  state.cs = 757; goto _test_eof; 
	_test_eof758:  state.cs = 758; goto _test_eof; 
	_test_eof759:  state.cs = 759; goto _test_eof; 
	_test_eof760:  state.cs = 760; goto _test_eof; 
	_test_eof761:  state.cs = 761; goto _test_eof; 
	_test_eof762:  state.cs = 762; goto _test_eof; 
	_test_eof763:  state.cs = 763; goto _test_eof; 
	_test_eof764:  state.cs = 764; goto _test_eof; 
	_test_eof765:  state.cs = 765; goto _test_eof; 
	_test_eof766:  state.cs = 766; goto _test_eof; 
	_test_eof767:  state.cs = 767; goto _test_eof; 
	_test_eof768:  state.cs = 768; goto _test_eof; 
	_test_eof769:  state.cs = 769; goto _test_eof; 
	_test_eof770:  state.cs = 770; goto _test_eof; 
	_test_eof771:  state.cs = 771; goto _test_eof; 
	_test_eof772:  state.cs = 772; goto _test_eof; 
	_test_eof773:  state.cs = 773; goto _test_eof; 
	_test_eof774:  state.cs = 774; goto _test_eof; 
	_test_eof775:  state.cs = 775; goto _test_eof; 
	_test_eof776:  state.cs = 776; goto _test_eof; 
	_test_eof777:  state.cs = 777; goto _test_eof; 
	_test_eof778:  state.cs = 778; goto _test_eof; 
	_test_eof779:  state.cs = 779; goto _test_eof; 
	_test_eof780:  state.cs = 780; goto _test_eof; 
	_test_eof781:  state.cs = 781; goto _test_eof; 
	_test_eof782:  state.cs = 782; goto _test_eof; 
	_test_eof783:  state.cs = 783; goto _test_eof; 
	_test_eof784:  state.cs = 784; goto _test_eof; 
	_test_eof785:  state.cs = 785; goto _test_eof; 
	_test_eof786:  state.cs = 786; goto _test_eof; 
	_test_eof787:  state.cs = 787; goto _test_eof; 
	_test_eof788:  state.cs = 788; goto _test_eof; 
	_test_eof789:  state.cs = 789; goto _test_eof; 
	_test_eof790:  state.cs = 790; goto _test_eof; 
	_test_eof791:  state.cs = 791; goto _test_eof; 
	_test_eof792:  state.cs = 792; goto _test_eof; 
	_test_eof793:  state.cs = 793; goto _test_eof; 
	_test_eof794:  state.cs = 794; goto _test_eof; 
	_test_eof795:  state.cs = 795; goto _test_eof; 
	_test_eof796:  state.cs = 796; goto _test_eof; 
	_test_eof797:  state.cs = 797; goto _test_eof; 
	_test_eof798:  state.cs = 798; goto _test_eof; 
	_test_eof799:  state.cs = 799; goto _test_eof; 
	_test_eof800:  state.cs = 800; goto _test_eof; 
	_test_eof801:  state.cs = 801; goto _test_eof; 
	_test_eof802:  state.cs = 802; goto _test_eof; 
	_test_eof803:  state.cs = 803; goto _test_eof; 
	_test_eof804:  state.cs = 804; goto _test_eof; 
	_test_eof805:  state.cs = 805; goto _test_eof; 
	_test_eof806:  state.cs = 806; goto _test_eof; 
	_test_eof807:  state.cs = 807; goto _test_eof; 
	_test_eof808:  state.cs = 808; goto _test_eof; 
	_test_eof809:  state.cs = 809; goto _test_eof; 
	_test_eof810:  state.cs = 810; goto _test_eof; 
	_test_eof811:  state.cs = 811; goto _test_eof; 
	_test_eof812:  state.cs = 812; goto _test_eof; 
	_test_eof813:  state.cs = 813; goto _test_eof; 
	_test_eof814:  state.cs = 814; goto _test_eof; 
	_test_eof815:  state.cs = 815; goto _test_eof; 
	_test_eof816:  state.cs = 816; goto _test_eof; 
	_test_eof817:  state.cs = 817; goto _test_eof; 
	_test_eof818:  state.cs = 818; goto _test_eof; 
	_test_eof819:  state.cs = 819; goto _test_eof; 
	_test_eof820:  state.cs = 820; goto _test_eof; 
	_test_eof821:  state.cs = 821; goto _test_eof; 
	_test_eof822:  state.cs = 822; goto _test_eof; 
	_test_eof1527:  state.cs = 1527; goto _test_eof; 
	_test_eof823:  state.cs = 823; goto _test_eof; 
	_test_eof824:  state.cs = 824; goto _test_eof; 
	_test_eof825:  state.cs = 825; goto _test_eof; 
	_test_eof826:  state.cs = 826; goto _test_eof; 
	_test_eof827:  state.cs = 827; goto _test_eof; 
	_test_eof828:  state.cs = 828; goto _test_eof; 
	_test_eof829:  state.cs = 829; goto _test_eof; 
	_test_eof830:  state.cs = 830; goto _test_eof; 
	_test_eof831:  state.cs = 831; goto _test_eof; 
	_test_eof832:  state.cs = 832; goto _test_eof; 
	_test_eof833:  state.cs = 833; goto _test_eof; 
	_test_eof834:  state.cs = 834; goto _test_eof; 
	_test_eof835:  state.cs = 835; goto _test_eof; 
	_test_eof836:  state.cs = 836; goto _test_eof; 
	_test_eof837:  state.cs = 837; goto _test_eof; 
	_test_eof838:  state.cs = 838; goto _test_eof; 
	_test_eof839:  state.cs = 839; goto _test_eof; 
	_test_eof840:  state.cs = 840; goto _test_eof; 
	_test_eof841:  state.cs = 841; goto _test_eof; 
	_test_eof842:  state.cs = 842; goto _test_eof; 
	_test_eof843:  state.cs = 843; goto _test_eof; 
	_test_eof844:  state.cs = 844; goto _test_eof; 
	_test_eof845:  state.cs = 845; goto _test_eof; 
	_test_eof846:  state.cs = 846; goto _test_eof; 
	_test_eof847:  state.cs = 847; goto _test_eof; 
	_test_eof848:  state.cs = 848; goto _test_eof; 
	_test_eof849:  state.cs = 849; goto _test_eof; 
	_test_eof850:  state.cs = 850; goto _test_eof; 
	_test_eof851:  state.cs = 851; goto _test_eof; 
	_test_eof852:  state.cs = 852; goto _test_eof; 
	_test_eof853:  state.cs = 853; goto _test_eof; 
	_test_eof854:  state.cs = 854; goto _test_eof; 
	_test_eof855:  state.cs = 855; goto _test_eof; 
	_test_eof856:  state.cs = 856; goto _test_eof; 
	_test_eof857:  state.cs = 857; goto _test_eof; 
	_test_eof858:  state.cs = 858; goto _test_eof; 
	_test_eof859:  state.cs = 859; goto _test_eof; 
	_test_eof860:  state.cs = 860; goto _test_eof; 
	_test_eof861:  state.cs = 861; goto _test_eof; 
	_test_eof862:  state.cs = 862; goto _test_eof; 
	_test_eof863:  state.cs = 863; goto _test_eof; 
	_test_eof864:  state.cs = 864; goto _test_eof; 
	_test_eof865:  state.cs = 865; goto _test_eof; 
	_test_eof866:  state.cs = 866; goto _test_eof; 
	_test_eof867:  state.cs = 867; goto _test_eof; 
	_test_eof868:  state.cs = 868; goto _test_eof; 
	_test_eof869:  state.cs = 869; goto _test_eof; 
	_test_eof870:  state.cs = 870; goto _test_eof; 
	_test_eof871:  state.cs = 871; goto _test_eof; 
	_test_eof872:  state.cs = 872; goto _test_eof; 
	_test_eof873:  state.cs = 873; goto _test_eof; 
	_test_eof874:  state.cs = 874; goto _test_eof; 
	_test_eof875:  state.cs = 875; goto _test_eof; 
	_test_eof876:  state.cs = 876; goto _test_eof; 
	_test_eof877:  state.cs = 877; goto _test_eof; 
	_test_eof878:  state.cs = 878; goto _test_eof; 
	_test_eof879:  state.cs = 879; goto _test_eof; 
	_test_eof880:  state.cs = 880; goto _test_eof; 
	_test_eof881:  state.cs = 881; goto _test_eof; 
	_test_eof882:  state.cs = 882; goto _test_eof; 
	_test_eof883:  state.cs = 883; goto _test_eof; 
	_test_eof884:  state.cs = 884; goto _test_eof; 
	_test_eof885:  state.cs = 885; goto _test_eof; 
	_test_eof886:  state.cs = 886; goto _test_eof; 
	_test_eof887:  state.cs = 887; goto _test_eof; 
	_test_eof888:  state.cs = 888; goto _test_eof; 
	_test_eof889:  state.cs = 889; goto _test_eof; 
	_test_eof890:  state.cs = 890; goto _test_eof; 
	_test_eof891:  state.cs = 891; goto _test_eof; 
	_test_eof892:  state.cs = 892; goto _test_eof; 
	_test_eof893:  state.cs = 893; goto _test_eof; 
	_test_eof894:  state.cs = 894; goto _test_eof; 
	_test_eof895:  state.cs = 895; goto _test_eof; 
	_test_eof896:  state.cs = 896; goto _test_eof; 
	_test_eof897:  state.cs = 897; goto _test_eof; 
	_test_eof898:  state.cs = 898; goto _test_eof; 
	_test_eof899:  state.cs = 899; goto _test_eof; 
	_test_eof900:  state.cs = 900; goto _test_eof; 
	_test_eof901:  state.cs = 901; goto _test_eof; 
	_test_eof902:  state.cs = 902; goto _test_eof; 
	_test_eof903:  state.cs = 903; goto _test_eof; 
	_test_eof904:  state.cs = 904; goto _test_eof; 
	_test_eof905:  state.cs = 905; goto _test_eof; 
	_test_eof906:  state.cs = 906; goto _test_eof; 
	_test_eof907:  state.cs = 907; goto _test_eof; 
	_test_eof908:  state.cs = 908; goto _test_eof; 
	_test_eof909:  state.cs = 909; goto _test_eof; 
	_test_eof910:  state.cs = 910; goto _test_eof; 
	_test_eof911:  state.cs = 911; goto _test_eof; 
	_test_eof912:  state.cs = 912; goto _test_eof; 
	_test_eof913:  state.cs = 913; goto _test_eof; 
	_test_eof914:  state.cs = 914; goto _test_eof; 
	_test_eof915:  state.cs = 915; goto _test_eof; 
	_test_eof916:  state.cs = 916; goto _test_eof; 
	_test_eof917:  state.cs = 917; goto _test_eof; 
	_test_eof918:  state.cs = 918; goto _test_eof; 
	_test_eof919:  state.cs = 919; goto _test_eof; 
	_test_eof920:  state.cs = 920; goto _test_eof; 
	_test_eof921:  state.cs = 921; goto _test_eof; 
	_test_eof922:  state.cs = 922; goto _test_eof; 
	_test_eof923:  state.cs = 923; goto _test_eof; 
	_test_eof924:  state.cs = 924; goto _test_eof; 
	_test_eof925:  state.cs = 925; goto _test_eof; 
	_test_eof926:  state.cs = 926; goto _test_eof; 
	_test_eof927:  state.cs = 927; goto _test_eof; 
	_test_eof928:  state.cs = 928; goto _test_eof; 
	_test_eof929:  state.cs = 929; goto _test_eof; 
	_test_eof930:  state.cs = 930; goto _test_eof; 
	_test_eof931:  state.cs = 931; goto _test_eof; 
	_test_eof932:  state.cs = 932; goto _test_eof; 
	_test_eof933:  state.cs = 933; goto _test_eof; 
	_test_eof934:  state.cs = 934; goto _test_eof; 
	_test_eof935:  state.cs = 935; goto _test_eof; 
	_test_eof936:  state.cs = 936; goto _test_eof; 
	_test_eof937:  state.cs = 937; goto _test_eof; 
	_test_eof938:  state.cs = 938; goto _test_eof; 
	_test_eof939:  state.cs = 939; goto _test_eof; 
	_test_eof940:  state.cs = 940; goto _test_eof; 
	_test_eof941:  state.cs = 941; goto _test_eof; 
	_test_eof942:  state.cs = 942; goto _test_eof; 
	_test_eof943:  state.cs = 943; goto _test_eof; 
	_test_eof944:  state.cs = 944; goto _test_eof; 
	_test_eof945:  state.cs = 945; goto _test_eof; 
	_test_eof946:  state.cs = 946; goto _test_eof; 
	_test_eof947:  state.cs = 947; goto _test_eof; 
	_test_eof948:  state.cs = 948; goto _test_eof; 
	_test_eof949:  state.cs = 949; goto _test_eof; 
	_test_eof950:  state.cs = 950; goto _test_eof; 
	_test_eof951:  state.cs = 951; goto _test_eof; 
	_test_eof952:  state.cs = 952; goto _test_eof; 
	_test_eof953:  state.cs = 953; goto _test_eof; 
	_test_eof954:  state.cs = 954; goto _test_eof; 
	_test_eof955:  state.cs = 955; goto _test_eof; 
	_test_eof956:  state.cs = 956; goto _test_eof; 
	_test_eof957:  state.cs = 957; goto _test_eof; 
	_test_eof958:  state.cs = 958; goto _test_eof; 
	_test_eof959:  state.cs = 959; goto _test_eof; 
	_test_eof960:  state.cs = 960; goto _test_eof; 
	_test_eof961:  state.cs = 961; goto _test_eof; 
	_test_eof962:  state.cs = 962; goto _test_eof; 
	_test_eof963:  state.cs = 963; goto _test_eof; 
	_test_eof964:  state.cs = 964; goto _test_eof; 
	_test_eof965:  state.cs = 965; goto _test_eof; 
	_test_eof966:  state.cs = 966; goto _test_eof; 
	_test_eof967:  state.cs = 967; goto _test_eof; 
	_test_eof968:  state.cs = 968; goto _test_eof; 
	_test_eof969:  state.cs = 969; goto _test_eof; 
	_test_eof970:  state.cs = 970; goto _test_eof; 
	_test_eof971:  state.cs = 971; goto _test_eof; 
	_test_eof972:  state.cs = 972; goto _test_eof; 
	_test_eof973:  state.cs = 973; goto _test_eof; 
	_test_eof974:  state.cs = 974; goto _test_eof; 
	_test_eof975:  state.cs = 975; goto _test_eof; 
	_test_eof976:  state.cs = 976; goto _test_eof; 
	_test_eof977:  state.cs = 977; goto _test_eof; 
	_test_eof978:  state.cs = 978; goto _test_eof; 
	_test_eof979:  state.cs = 979; goto _test_eof; 
	_test_eof980:  state.cs = 980; goto _test_eof; 
	_test_eof981:  state.cs = 981; goto _test_eof; 
	_test_eof982:  state.cs = 982; goto _test_eof; 
	_test_eof983:  state.cs = 983; goto _test_eof; 
	_test_eof984:  state.cs = 984; goto _test_eof; 
	_test_eof985:  state.cs = 985; goto _test_eof; 
	_test_eof986:  state.cs = 986; goto _test_eof; 
	_test_eof987:  state.cs = 987; goto _test_eof; 
	_test_eof988:  state.cs = 988; goto _test_eof; 
	_test_eof989:  state.cs = 989; goto _test_eof; 
	_test_eof990:  state.cs = 990; goto _test_eof; 
	_test_eof991:  state.cs = 991; goto _test_eof; 
	_test_eof992:  state.cs = 992; goto _test_eof; 
	_test_eof993:  state.cs = 993; goto _test_eof; 
	_test_eof994:  state.cs = 994; goto _test_eof; 
	_test_eof995:  state.cs = 995; goto _test_eof; 
	_test_eof996:  state.cs = 996; goto _test_eof; 
	_test_eof997:  state.cs = 997; goto _test_eof; 
	_test_eof998:  state.cs = 998; goto _test_eof; 
	_test_eof999:  state.cs = 999; goto _test_eof; 
	_test_eof1000:  state.cs = 1000; goto _test_eof; 
	_test_eof1001:  state.cs = 1001; goto _test_eof; 
	_test_eof1002:  state.cs = 1002; goto _test_eof; 
	_test_eof1003:  state.cs = 1003; goto _test_eof; 
	_test_eof1004:  state.cs = 1004; goto _test_eof; 
	_test_eof1005:  state.cs = 1005; goto _test_eof; 
	_test_eof1006:  state.cs = 1006; goto _test_eof; 
	_test_eof1007:  state.cs = 1007; goto _test_eof; 
	_test_eof1008:  state.cs = 1008; goto _test_eof; 
	_test_eof1009:  state.cs = 1009; goto _test_eof; 
	_test_eof1010:  state.cs = 1010; goto _test_eof; 
	_test_eof1011:  state.cs = 1011; goto _test_eof; 
	_test_eof1012:  state.cs = 1012; goto _test_eof; 
	_test_eof1013:  state.cs = 1013; goto _test_eof; 
	_test_eof1014:  state.cs = 1014; goto _test_eof; 
	_test_eof1015:  state.cs = 1015; goto _test_eof; 
	_test_eof1016:  state.cs = 1016; goto _test_eof; 
	_test_eof1017:  state.cs = 1017; goto _test_eof; 
	_test_eof1018:  state.cs = 1018; goto _test_eof; 
	_test_eof1019:  state.cs = 1019; goto _test_eof; 
	_test_eof1020:  state.cs = 1020; goto _test_eof; 
	_test_eof1021:  state.cs = 1021; goto _test_eof; 
	_test_eof1022:  state.cs = 1022; goto _test_eof; 
	_test_eof1023:  state.cs = 1023; goto _test_eof; 
	_test_eof1024:  state.cs = 1024; goto _test_eof; 
	_test_eof1025:  state.cs = 1025; goto _test_eof; 
	_test_eof1026:  state.cs = 1026; goto _test_eof; 
	_test_eof1027:  state.cs = 1027; goto _test_eof; 
	_test_eof1028:  state.cs = 1028; goto _test_eof; 
	_test_eof1029:  state.cs = 1029; goto _test_eof; 
	_test_eof1030:  state.cs = 1030; goto _test_eof; 
	_test_eof1031:  state.cs = 1031; goto _test_eof; 
	_test_eof1032:  state.cs = 1032; goto _test_eof; 
	_test_eof1033:  state.cs = 1033; goto _test_eof; 
	_test_eof1034:  state.cs = 1034; goto _test_eof; 
	_test_eof1035:  state.cs = 1035; goto _test_eof; 
	_test_eof1036:  state.cs = 1036; goto _test_eof; 
	_test_eof1037:  state.cs = 1037; goto _test_eof; 
	_test_eof1038:  state.cs = 1038; goto _test_eof; 
	_test_eof1039:  state.cs = 1039; goto _test_eof; 
	_test_eof1040:  state.cs = 1040; goto _test_eof; 
	_test_eof1041:  state.cs = 1041; goto _test_eof; 
	_test_eof1042:  state.cs = 1042; goto _test_eof; 
	_test_eof1043:  state.cs = 1043; goto _test_eof; 
	_test_eof1044:  state.cs = 1044; goto _test_eof; 
	_test_eof1045:  state.cs = 1045; goto _test_eof; 
	_test_eof1046:  state.cs = 1046; goto _test_eof; 
	_test_eof1047:  state.cs = 1047; goto _test_eof; 
	_test_eof1048:  state.cs = 1048; goto _test_eof; 
	_test_eof1049:  state.cs = 1049; goto _test_eof; 
	_test_eof1050:  state.cs = 1050; goto _test_eof; 
	_test_eof1051:  state.cs = 1051; goto _test_eof; 
	_test_eof1052:  state.cs = 1052; goto _test_eof; 
	_test_eof1053:  state.cs = 1053; goto _test_eof; 
	_test_eof1054:  state.cs = 1054; goto _test_eof; 
	_test_eof1055:  state.cs = 1055; goto _test_eof; 
	_test_eof1056:  state.cs = 1056; goto _test_eof; 
	_test_eof1057:  state.cs = 1057; goto _test_eof; 
	_test_eof1058:  state.cs = 1058; goto _test_eof; 
	_test_eof1059:  state.cs = 1059; goto _test_eof; 
	_test_eof1060:  state.cs = 1060; goto _test_eof; 
	_test_eof1061:  state.cs = 1061; goto _test_eof; 
	_test_eof1062:  state.cs = 1062; goto _test_eof; 
	_test_eof1063:  state.cs = 1063; goto _test_eof; 
	_test_eof1064:  state.cs = 1064; goto _test_eof; 
	_test_eof1065:  state.cs = 1065; goto _test_eof; 
	_test_eof1066:  state.cs = 1066; goto _test_eof; 
	_test_eof1067:  state.cs = 1067; goto _test_eof; 
	_test_eof1068:  state.cs = 1068; goto _test_eof; 
	_test_eof1069:  state.cs = 1069; goto _test_eof; 
	_test_eof1070:  state.cs = 1070; goto _test_eof; 
	_test_eof1071:  state.cs = 1071; goto _test_eof; 
	_test_eof1072:  state.cs = 1072; goto _test_eof; 
	_test_eof1073:  state.cs = 1073; goto _test_eof; 
	_test_eof1074:  state.cs = 1074; goto _test_eof; 
	_test_eof1075:  state.cs = 1075; goto _test_eof; 
	_test_eof1076:  state.cs = 1076; goto _test_eof; 
	_test_eof1077:  state.cs = 1077; goto _test_eof; 
	_test_eof1078:  state.cs = 1078; goto _test_eof; 
	_test_eof1079:  state.cs = 1079; goto _test_eof; 
	_test_eof1080:  state.cs = 1080; goto _test_eof; 
	_test_eof1081:  state.cs = 1081; goto _test_eof; 
	_test_eof1082:  state.cs = 1082; goto _test_eof; 
	_test_eof1083:  state.cs = 1083; goto _test_eof; 
	_test_eof1084:  state.cs = 1084; goto _test_eof; 
	_test_eof1085:  state.cs = 1085; goto _test_eof; 
	_test_eof1086:  state.cs = 1086; goto _test_eof; 
	_test_eof1087:  state.cs = 1087; goto _test_eof; 
	_test_eof1088:  state.cs = 1088; goto _test_eof; 
	_test_eof1089:  state.cs = 1089; goto _test_eof; 
	_test_eof1090:  state.cs = 1090; goto _test_eof; 
	_test_eof1091:  state.cs = 1091; goto _test_eof; 
	_test_eof1092:  state.cs = 1092; goto _test_eof; 
	_test_eof1093:  state.cs = 1093; goto _test_eof; 
	_test_eof1094:  state.cs = 1094; goto _test_eof; 
	_test_eof1095:  state.cs = 1095; goto _test_eof; 
	_test_eof1096:  state.cs = 1096; goto _test_eof; 
	_test_eof1097:  state.cs = 1097; goto _test_eof; 
	_test_eof1098:  state.cs = 1098; goto _test_eof; 
	_test_eof1099:  state.cs = 1099; goto _test_eof; 
	_test_eof1100:  state.cs = 1100; goto _test_eof; 
	_test_eof1101:  state.cs = 1101; goto _test_eof; 
	_test_eof1102:  state.cs = 1102; goto _test_eof; 
	_test_eof1103:  state.cs = 1103; goto _test_eof; 
	_test_eof1104:  state.cs = 1104; goto _test_eof; 
	_test_eof1105:  state.cs = 1105; goto _test_eof; 
	_test_eof1106:  state.cs = 1106; goto _test_eof; 
	_test_eof1107:  state.cs = 1107; goto _test_eof; 
	_test_eof1108:  state.cs = 1108; goto _test_eof; 
	_test_eof1109:  state.cs = 1109; goto _test_eof; 
	_test_eof1110:  state.cs = 1110; goto _test_eof; 
	_test_eof1111:  state.cs = 1111; goto _test_eof; 
	_test_eof1112:  state.cs = 1112; goto _test_eof; 
	_test_eof1113:  state.cs = 1113; goto _test_eof; 
	_test_eof1114:  state.cs = 1114; goto _test_eof; 
	_test_eof1115:  state.cs = 1115; goto _test_eof; 
	_test_eof1116:  state.cs = 1116; goto _test_eof; 
	_test_eof1117:  state.cs = 1117; goto _test_eof; 
	_test_eof1118:  state.cs = 1118; goto _test_eof; 
	_test_eof1119:  state.cs = 1119; goto _test_eof; 
	_test_eof1120:  state.cs = 1120; goto _test_eof; 
	_test_eof1121:  state.cs = 1121; goto _test_eof; 
	_test_eof1122:  state.cs = 1122; goto _test_eof; 
	_test_eof1123:  state.cs = 1123; goto _test_eof; 
	_test_eof1124:  state.cs = 1124; goto _test_eof; 
	_test_eof1125:  state.cs = 1125; goto _test_eof; 
	_test_eof1126:  state.cs = 1126; goto _test_eof; 
	_test_eof1127:  state.cs = 1127; goto _test_eof; 
	_test_eof1128:  state.cs = 1128; goto _test_eof; 
	_test_eof1129:  state.cs = 1129; goto _test_eof; 
	_test_eof1130:  state.cs = 1130; goto _test_eof; 
	_test_eof1131:  state.cs = 1131; goto _test_eof; 
	_test_eof1132:  state.cs = 1132; goto _test_eof; 
	_test_eof1133:  state.cs = 1133; goto _test_eof; 
	_test_eof1134:  state.cs = 1134; goto _test_eof; 
	_test_eof1135:  state.cs = 1135; goto _test_eof; 
	_test_eof1136:  state.cs = 1136; goto _test_eof; 
	_test_eof1137:  state.cs = 1137; goto _test_eof; 
	_test_eof1138:  state.cs = 1138; goto _test_eof; 
	_test_eof1139:  state.cs = 1139; goto _test_eof; 
	_test_eof1140:  state.cs = 1140; goto _test_eof; 
	_test_eof1141:  state.cs = 1141; goto _test_eof; 
	_test_eof1142:  state.cs = 1142; goto _test_eof; 
	_test_eof1143:  state.cs = 1143; goto _test_eof; 
	_test_eof1144:  state.cs = 1144; goto _test_eof; 
	_test_eof1145:  state.cs = 1145; goto _test_eof; 
	_test_eof1146:  state.cs = 1146; goto _test_eof; 
	_test_eof1147:  state.cs = 1147; goto _test_eof; 
	_test_eof1148:  state.cs = 1148; goto _test_eof; 
	_test_eof1149:  state.cs = 1149; goto _test_eof; 
	_test_eof1150:  state.cs = 1150; goto _test_eof; 
	_test_eof1151:  state.cs = 1151; goto _test_eof; 
	_test_eof1152:  state.cs = 1152; goto _test_eof; 
	_test_eof1153:  state.cs = 1153; goto _test_eof; 
	_test_eof1154:  state.cs = 1154; goto _test_eof; 
	_test_eof1155:  state.cs = 1155; goto _test_eof; 
	_test_eof1156:  state.cs = 1156; goto _test_eof; 
	_test_eof1157:  state.cs = 1157; goto _test_eof; 
	_test_eof1158:  state.cs = 1158; goto _test_eof; 
	_test_eof1159:  state.cs = 1159; goto _test_eof; 
	_test_eof1160:  state.cs = 1160; goto _test_eof; 
	_test_eof1161:  state.cs = 1161; goto _test_eof; 
	_test_eof1162:  state.cs = 1162; goto _test_eof; 
	_test_eof1163:  state.cs = 1163; goto _test_eof; 
	_test_eof1164:  state.cs = 1164; goto _test_eof; 
	_test_eof1165:  state.cs = 1165; goto _test_eof; 
	_test_eof1166:  state.cs = 1166; goto _test_eof; 
	_test_eof1167:  state.cs = 1167; goto _test_eof; 
	_test_eof1168:  state.cs = 1168; goto _test_eof; 
	_test_eof1169:  state.cs = 1169; goto _test_eof; 
	_test_eof1170:  state.cs = 1170; goto _test_eof; 
	_test_eof1171:  state.cs = 1171; goto _test_eof; 
	_test_eof1172:  state.cs = 1172; goto _test_eof; 
	_test_eof1173:  state.cs = 1173; goto _test_eof; 
	_test_eof1174:  state.cs = 1174; goto _test_eof; 
	_test_eof1175:  state.cs = 1175; goto _test_eof; 
	_test_eof1176:  state.cs = 1176; goto _test_eof; 
	_test_eof1177:  state.cs = 1177; goto _test_eof; 
	_test_eof1178:  state.cs = 1178; goto _test_eof; 
	_test_eof1179:  state.cs = 1179; goto _test_eof; 
	_test_eof1180:  state.cs = 1180; goto _test_eof; 
	_test_eof1181:  state.cs = 1181; goto _test_eof; 
	_test_eof1182:  state.cs = 1182; goto _test_eof; 
	_test_eof1183:  state.cs = 1183; goto _test_eof; 
	_test_eof1184:  state.cs = 1184; goto _test_eof; 
	_test_eof1185:  state.cs = 1185; goto _test_eof; 
	_test_eof1186:  state.cs = 1186; goto _test_eof; 
	_test_eof1187:  state.cs = 1187; goto _test_eof; 
	_test_eof1188:  state.cs = 1188; goto _test_eof; 
	_test_eof1189:  state.cs = 1189; goto _test_eof; 
	_test_eof1190:  state.cs = 1190; goto _test_eof; 
	_test_eof1191:  state.cs = 1191; goto _test_eof; 
	_test_eof1192:  state.cs = 1192; goto _test_eof; 
	_test_eof1193:  state.cs = 1193; goto _test_eof; 
	_test_eof1194:  state.cs = 1194; goto _test_eof; 
	_test_eof1195:  state.cs = 1195; goto _test_eof; 
	_test_eof1196:  state.cs = 1196; goto _test_eof; 
	_test_eof1197:  state.cs = 1197; goto _test_eof; 
	_test_eof1198:  state.cs = 1198; goto _test_eof; 
	_test_eof1199:  state.cs = 1199; goto _test_eof; 
	_test_eof1200:  state.cs = 1200; goto _test_eof; 
	_test_eof1201:  state.cs = 1201; goto _test_eof; 
	_test_eof1202:  state.cs = 1202; goto _test_eof; 
	_test_eof1203:  state.cs = 1203; goto _test_eof; 
	_test_eof1204:  state.cs = 1204; goto _test_eof; 
	_test_eof1205:  state.cs = 1205; goto _test_eof; 
	_test_eof1206:  state.cs = 1206; goto _test_eof; 
	_test_eof1207:  state.cs = 1207; goto _test_eof; 
	_test_eof1208:  state.cs = 1208; goto _test_eof; 
	_test_eof1209:  state.cs = 1209; goto _test_eof; 
	_test_eof1210:  state.cs = 1210; goto _test_eof; 
	_test_eof1211:  state.cs = 1211; goto _test_eof; 
	_test_eof1212:  state.cs = 1212; goto _test_eof; 
	_test_eof1213:  state.cs = 1213; goto _test_eof; 
	_test_eof1214:  state.cs = 1214; goto _test_eof; 
	_test_eof1215:  state.cs = 1215; goto _test_eof; 
	_test_eof1216:  state.cs = 1216; goto _test_eof; 
	_test_eof1217:  state.cs = 1217; goto _test_eof; 
	_test_eof1218:  state.cs = 1218; goto _test_eof; 
	_test_eof1219:  state.cs = 1219; goto _test_eof; 
	_test_eof1220:  state.cs = 1220; goto _test_eof; 
	_test_eof1221:  state.cs = 1221; goto _test_eof; 
	_test_eof1222:  state.cs = 1222; goto _test_eof; 
	_test_eof1223:  state.cs = 1223; goto _test_eof; 
	_test_eof1224:  state.cs = 1224; goto _test_eof; 
	_test_eof1225:  state.cs = 1225; goto _test_eof; 
	_test_eof1226:  state.cs = 1226; goto _test_eof; 
	_test_eof1227:  state.cs = 1227; goto _test_eof; 
	_test_eof1228:  state.cs = 1228; goto _test_eof; 
	_test_eof1229:  state.cs = 1229; goto _test_eof; 
	_test_eof1230:  state.cs = 1230; goto _test_eof; 
	_test_eof1231:  state.cs = 1231; goto _test_eof; 
	_test_eof1232:  state.cs = 1232; goto _test_eof; 
	_test_eof1233:  state.cs = 1233; goto _test_eof; 
	_test_eof1234:  state.cs = 1234; goto _test_eof; 
	_test_eof1235:  state.cs = 1235; goto _test_eof; 
	_test_eof1236:  state.cs = 1236; goto _test_eof; 
	_test_eof1237:  state.cs = 1237; goto _test_eof; 
	_test_eof1238:  state.cs = 1238; goto _test_eof; 
	_test_eof1239:  state.cs = 1239; goto _test_eof; 
	_test_eof1240:  state.cs = 1240; goto _test_eof; 
	_test_eof1241:  state.cs = 1241; goto _test_eof; 
	_test_eof1242:  state.cs = 1242; goto _test_eof; 
	_test_eof1243:  state.cs = 1243; goto _test_eof; 
	_test_eof1244:  state.cs = 1244; goto _test_eof; 
	_test_eof1245:  state.cs = 1245; goto _test_eof; 
	_test_eof1246:  state.cs = 1246; goto _test_eof; 
	_test_eof1247:  state.cs = 1247; goto _test_eof; 
	_test_eof1248:  state.cs = 1248; goto _test_eof; 
	_test_eof1249:  state.cs = 1249; goto _test_eof; 
	_test_eof1250:  state.cs = 1250; goto _test_eof; 
	_test_eof1251:  state.cs = 1251; goto _test_eof; 
	_test_eof1252:  state.cs = 1252; goto _test_eof; 
	_test_eof1253:  state.cs = 1253; goto _test_eof; 
	_test_eof1254:  state.cs = 1254; goto _test_eof; 
	_test_eof1255:  state.cs = 1255; goto _test_eof; 
	_test_eof1256:  state.cs = 1256; goto _test_eof; 
	_test_eof1257:  state.cs = 1257; goto _test_eof; 
	_test_eof1258:  state.cs = 1258; goto _test_eof; 
	_test_eof1259:  state.cs = 1259; goto _test_eof; 
	_test_eof1260:  state.cs = 1260; goto _test_eof; 
	_test_eof1261:  state.cs = 1261; goto _test_eof; 
	_test_eof1262:  state.cs = 1262; goto _test_eof; 
	_test_eof1263:  state.cs = 1263; goto _test_eof; 
	_test_eof1264:  state.cs = 1264; goto _test_eof; 
	_test_eof1265:  state.cs = 1265; goto _test_eof; 
	_test_eof1266:  state.cs = 1266; goto _test_eof; 
	_test_eof1267:  state.cs = 1267; goto _test_eof; 
	_test_eof1268:  state.cs = 1268; goto _test_eof; 
	_test_eof1269:  state.cs = 1269; goto _test_eof; 
	_test_eof1270:  state.cs = 1270; goto _test_eof; 
	_test_eof1271:  state.cs = 1271; goto _test_eof; 
	_test_eof1272:  state.cs = 1272; goto _test_eof; 
	_test_eof1273:  state.cs = 1273; goto _test_eof; 
	_test_eof1274:  state.cs = 1274; goto _test_eof; 
	_test_eof1275:  state.cs = 1275; goto _test_eof; 
	_test_eof1276:  state.cs = 1276; goto _test_eof; 
	_test_eof1277:  state.cs = 1277; goto _test_eof; 
	_test_eof1278:  state.cs = 1278; goto _test_eof; 
	_test_eof1279:  state.cs = 1279; goto _test_eof; 
	_test_eof1280:  state.cs = 1280; goto _test_eof; 
	_test_eof1281:  state.cs = 1281; goto _test_eof; 
	_test_eof1282:  state.cs = 1282; goto _test_eof; 
	_test_eof1283:  state.cs = 1283; goto _test_eof; 
	_test_eof1284:  state.cs = 1284; goto _test_eof; 
	_test_eof1285:  state.cs = 1285; goto _test_eof; 
	_test_eof1286:  state.cs = 1286; goto _test_eof; 
	_test_eof1287:  state.cs = 1287; goto _test_eof; 
	_test_eof1288:  state.cs = 1288; goto _test_eof; 
	_test_eof1289:  state.cs = 1289; goto _test_eof; 
	_test_eof1290:  state.cs = 1290; goto _test_eof; 
	_test_eof1291:  state.cs = 1291; goto _test_eof; 
	_test_eof1292:  state.cs = 1292; goto _test_eof; 
	_test_eof1293:  state.cs = 1293; goto _test_eof; 
	_test_eof1294:  state.cs = 1294; goto _test_eof; 
	_test_eof1295:  state.cs = 1295; goto _test_eof; 
	_test_eof1296:  state.cs = 1296; goto _test_eof; 
	_test_eof1297:  state.cs = 1297; goto _test_eof; 
	_test_eof1298:  state.cs = 1298; goto _test_eof; 
	_test_eof1299:  state.cs = 1299; goto _test_eof; 
	_test_eof1300:  state.cs = 1300; goto _test_eof; 
	_test_eof1301:  state.cs = 1301; goto _test_eof; 
	_test_eof1302:  state.cs = 1302; goto _test_eof; 
	_test_eof1303:  state.cs = 1303; goto _test_eof; 
	_test_eof1304:  state.cs = 1304; goto _test_eof; 
	_test_eof1305:  state.cs = 1305; goto _test_eof; 
	_test_eof1306:  state.cs = 1306; goto _test_eof; 
	_test_eof1307:  state.cs = 1307; goto _test_eof; 
	_test_eof1308:  state.cs = 1308; goto _test_eof; 
	_test_eof1309:  state.cs = 1309; goto _test_eof; 
	_test_eof1310:  state.cs = 1310; goto _test_eof; 
	_test_eof1311:  state.cs = 1311; goto _test_eof; 
	_test_eof1312:  state.cs = 1312; goto _test_eof; 
	_test_eof1313:  state.cs = 1313; goto _test_eof; 
	_test_eof1314:  state.cs = 1314; goto _test_eof; 
	_test_eof1315:  state.cs = 1315; goto _test_eof; 
	_test_eof1316:  state.cs = 1316; goto _test_eof; 
	_test_eof1317:  state.cs = 1317; goto _test_eof; 
	_test_eof1318:  state.cs = 1318; goto _test_eof; 
	_test_eof1319:  state.cs = 1319; goto _test_eof; 
	_test_eof1320:  state.cs = 1320; goto _test_eof; 
	_test_eof1321:  state.cs = 1321; goto _test_eof; 
	_test_eof1322:  state.cs = 1322; goto _test_eof; 
	_test_eof1323:  state.cs = 1323; goto _test_eof; 
	_test_eof1324:  state.cs = 1324; goto _test_eof; 
	_test_eof1325:  state.cs = 1325; goto _test_eof; 
	_test_eof1326:  state.cs = 1326; goto _test_eof; 
	_test_eof1327:  state.cs = 1327; goto _test_eof; 
	_test_eof1328:  state.cs = 1328; goto _test_eof; 
	_test_eof1329:  state.cs = 1329; goto _test_eof; 
	_test_eof1330:  state.cs = 1330; goto _test_eof; 
	_test_eof1331:  state.cs = 1331; goto _test_eof; 
	_test_eof1332:  state.cs = 1332; goto _test_eof; 
	_test_eof1333:  state.cs = 1333; goto _test_eof; 
	_test_eof1334:  state.cs = 1334; goto _test_eof; 
	_test_eof1335:  state.cs = 1335; goto _test_eof; 
	_test_eof1336:  state.cs = 1336; goto _test_eof; 
	_test_eof1337:  state.cs = 1337; goto _test_eof; 
	_test_eof1338:  state.cs = 1338; goto _test_eof; 
	_test_eof1339:  state.cs = 1339; goto _test_eof; 
	_test_eof1340:  state.cs = 1340; goto _test_eof; 
	_test_eof1341:  state.cs = 1341; goto _test_eof; 
	_test_eof1342:  state.cs = 1342; goto _test_eof; 
	_test_eof1343:  state.cs = 1343; goto _test_eof; 
	_test_eof1344:  state.cs = 1344; goto _test_eof; 
	_test_eof1345:  state.cs = 1345; goto _test_eof; 
	_test_eof1346:  state.cs = 1346; goto _test_eof; 
	_test_eof1347:  state.cs = 1347; goto _test_eof; 
	_test_eof1348:  state.cs = 1348; goto _test_eof; 
	_test_eof1349:  state.cs = 1349; goto _test_eof; 
	_test_eof1350:  state.cs = 1350; goto _test_eof; 
	_test_eof1351:  state.cs = 1351; goto _test_eof; 
	_test_eof1352:  state.cs = 1352; goto _test_eof; 
	_test_eof1353:  state.cs = 1353; goto _test_eof; 
	_test_eof1354:  state.cs = 1354; goto _test_eof; 
	_test_eof1355:  state.cs = 1355; goto _test_eof; 
	_test_eof1356:  state.cs = 1356; goto _test_eof; 
	_test_eof1357:  state.cs = 1357; goto _test_eof; 
	_test_eof1358:  state.cs = 1358; goto _test_eof; 
	_test_eof1359:  state.cs = 1359; goto _test_eof; 
	_test_eof1360:  state.cs = 1360; goto _test_eof; 
	_test_eof1361:  state.cs = 1361; goto _test_eof; 
	_test_eof1362:  state.cs = 1362; goto _test_eof; 
	_test_eof1363:  state.cs = 1363; goto _test_eof; 
	_test_eof1364:  state.cs = 1364; goto _test_eof; 
	_test_eof1365:  state.cs = 1365; goto _test_eof; 
	_test_eof1366:  state.cs = 1366; goto _test_eof; 
	_test_eof1367:  state.cs = 1367; goto _test_eof; 
	_test_eof1368:  state.cs = 1368; goto _test_eof; 
	_test_eof1369:  state.cs = 1369; goto _test_eof; 
	_test_eof1370:  state.cs = 1370; goto _test_eof; 
	_test_eof1371:  state.cs = 1371; goto _test_eof; 
	_test_eof1372:  state.cs = 1372; goto _test_eof; 
	_test_eof1373:  state.cs = 1373; goto _test_eof; 
	_test_eof1374:  state.cs = 1374; goto _test_eof; 
	_test_eof1375:  state.cs = 1375; goto _test_eof; 
	_test_eof1376:  state.cs = 1376; goto _test_eof; 
	_test_eof1377:  state.cs = 1377; goto _test_eof; 
	_test_eof1378:  state.cs = 1378; goto _test_eof; 
	_test_eof1379:  state.cs = 1379; goto _test_eof; 
	_test_eof1380:  state.cs = 1380; goto _test_eof; 
	_test_eof1381:  state.cs = 1381; goto _test_eof; 
	_test_eof1382:  state.cs = 1382; goto _test_eof; 
	_test_eof1383:  state.cs = 1383; goto _test_eof; 
	_test_eof1384:  state.cs = 1384; goto _test_eof; 
	_test_eof1385:  state.cs = 1385; goto _test_eof; 
	_test_eof1386:  state.cs = 1386; goto _test_eof; 
	_test_eof1387:  state.cs = 1387; goto _test_eof; 
	_test_eof1388:  state.cs = 1388; goto _test_eof; 
	_test_eof1389:  state.cs = 1389; goto _test_eof; 
	_test_eof1390:  state.cs = 1390; goto _test_eof; 
	_test_eof1391:  state.cs = 1391; goto _test_eof; 
	_test_eof1392:  state.cs = 1392; goto _test_eof; 
	_test_eof1393:  state.cs = 1393; goto _test_eof; 
	_test_eof1394:  state.cs = 1394; goto _test_eof; 
	_test_eof1395:  state.cs = 1395; goto _test_eof; 
	_test_eof1396:  state.cs = 1396; goto _test_eof; 
	_test_eof1397:  state.cs = 1397; goto _test_eof; 
	_test_eof1398:  state.cs = 1398; goto _test_eof; 
	_test_eof1399:  state.cs = 1399; goto _test_eof; 
	_test_eof1400:  state.cs = 1400; goto _test_eof; 
	_test_eof1401:  state.cs = 1401; goto _test_eof; 
	_test_eof1402:  state.cs = 1402; goto _test_eof; 
	_test_eof1403:  state.cs = 1403; goto _test_eof; 
	_test_eof1404:  state.cs = 1404; goto _test_eof; 
	_test_eof1405:  state.cs = 1405; goto _test_eof; 
	_test_eof1406:  state.cs = 1406; goto _test_eof; 
	_test_eof1407:  state.cs = 1407; goto _test_eof; 
	_test_eof1408:  state.cs = 1408; goto _test_eof; 
	_test_eof1409:  state.cs = 1409; goto _test_eof; 
	_test_eof1410:  state.cs = 1410; goto _test_eof; 
	_test_eof1411:  state.cs = 1411; goto _test_eof; 
	_test_eof1412:  state.cs = 1412; goto _test_eof; 
	_test_eof1413:  state.cs = 1413; goto _test_eof; 
	_test_eof1414:  state.cs = 1414; goto _test_eof; 
	_test_eof1415:  state.cs = 1415; goto _test_eof; 
	_test_eof1416:  state.cs = 1416; goto _test_eof; 
	_test_eof1417:  state.cs = 1417; goto _test_eof; 
	_test_eof1418:  state.cs = 1418; goto _test_eof; 
	_test_eof1419:  state.cs = 1419; goto _test_eof; 
	_test_eof1420:  state.cs = 1420; goto _test_eof; 
	_test_eof1421:  state.cs = 1421; goto _test_eof; 
	_test_eof1422:  state.cs = 1422; goto _test_eof; 
	_test_eof1423:  state.cs = 1423; goto _test_eof; 
	_test_eof1424:  state.cs = 1424; goto _test_eof; 
	_test_eof1425:  state.cs = 1425; goto _test_eof; 
	_test_eof1426:  state.cs = 1426; goto _test_eof; 
	_test_eof1427:  state.cs = 1427; goto _test_eof; 
	_test_eof1428:  state.cs = 1428; goto _test_eof; 
	_test_eof1429:  state.cs = 1429; goto _test_eof; 
	_test_eof1430:  state.cs = 1430; goto _test_eof; 
	_test_eof1431:  state.cs = 1431; goto _test_eof; 
	_test_eof1432:  state.cs = 1432; goto _test_eof; 
	_test_eof1433:  state.cs = 1433; goto _test_eof; 
	_test_eof1434:  state.cs = 1434; goto _test_eof; 
	_test_eof1435:  state.cs = 1435; goto _test_eof; 
	_test_eof1436:  state.cs = 1436; goto _test_eof; 
	_test_eof1437:  state.cs = 1437; goto _test_eof; 
	_test_eof1438:  state.cs = 1438; goto _test_eof; 
	_test_eof1439:  state.cs = 1439; goto _test_eof; 
	_test_eof1440:  state.cs = 1440; goto _test_eof; 
	_test_eof1441:  state.cs = 1441; goto _test_eof; 
	_test_eof1442:  state.cs = 1442; goto _test_eof; 
	_test_eof1443:  state.cs = 1443; goto _test_eof; 
	_test_eof1444:  state.cs = 1444; goto _test_eof; 
	_test_eof1445:  state.cs = 1445; goto _test_eof; 
	_test_eof1446:  state.cs = 1446; goto _test_eof; 
	_test_eof1447:  state.cs = 1447; goto _test_eof; 
	_test_eof1448:  state.cs = 1448; goto _test_eof; 
	_test_eof1449:  state.cs = 1449; goto _test_eof; 
	_test_eof1450:  state.cs = 1450; goto _test_eof; 
	_test_eof1451:  state.cs = 1451; goto _test_eof; 
	_test_eof1452:  state.cs = 1452; goto _test_eof; 
	_test_eof1453:  state.cs = 1453; goto _test_eof; 
	_test_eof1454:  state.cs = 1454; goto _test_eof; 
	_test_eof1455:  state.cs = 1455; goto _test_eof; 
	_test_eof1456:  state.cs = 1456; goto _test_eof; 
	_test_eof1457:  state.cs = 1457; goto _test_eof; 
	_test_eof1458:  state.cs = 1458; goto _test_eof; 
	_test_eof1459:  state.cs = 1459; goto _test_eof; 
	_test_eof1460:  state.cs = 1460; goto _test_eof; 
	_test_eof1461:  state.cs = 1461; goto _test_eof; 
	_test_eof1462:  state.cs = 1462; goto _test_eof; 
	_test_eof1463:  state.cs = 1463; goto _test_eof; 
	_test_eof1464:  state.cs = 1464; goto _test_eof; 
	_test_eof1465:  state.cs = 1465; goto _test_eof; 
	_test_eof1466:  state.cs = 1466; goto _test_eof; 
	_test_eof1467:  state.cs = 1467; goto _test_eof; 
	_test_eof1468:  state.cs = 1468; goto _test_eof; 
	_test_eof1469:  state.cs = 1469; goto _test_eof; 
	_test_eof1470:  state.cs = 1470; goto _test_eof; 
	_test_eof1471:  state.cs = 1471; goto _test_eof; 
	_test_eof1472:  state.cs = 1472; goto _test_eof; 
	_test_eof1473:  state.cs = 1473; goto _test_eof; 
	_test_eof1474:  state.cs = 1474; goto _test_eof; 
	_test_eof1475:  state.cs = 1475; goto _test_eof; 
	_test_eof1476:  state.cs = 1476; goto _test_eof; 
	_test_eof1477:  state.cs = 1477; goto _test_eof; 
	_test_eof1478:  state.cs = 1478; goto _test_eof; 
	_test_eof1479:  state.cs = 1479; goto _test_eof; 
	_test_eof1480:  state.cs = 1480; goto _test_eof; 
	_test_eof1481:  state.cs = 1481; goto _test_eof; 
	_test_eof1482:  state.cs = 1482; goto _test_eof; 
	_test_eof1483:  state.cs = 1483; goto _test_eof; 
	_test_eof1484:  state.cs = 1484; goto _test_eof; 
	_test_eof1485:  state.cs = 1485; goto _test_eof; 
	_test_eof1486:  state.cs = 1486; goto _test_eof; 
	_test_eof1487:  state.cs = 1487; goto _test_eof; 
	_test_eof1488:  state.cs = 1488; goto _test_eof; 
	_test_eof1489:  state.cs = 1489; goto _test_eof; 
	_test_eof1490:  state.cs = 1490; goto _test_eof; 
	_test_eof1491:  state.cs = 1491; goto _test_eof; 
	_test_eof1492:  state.cs = 1492; goto _test_eof; 
	_test_eof1493:  state.cs = 1493; goto _test_eof; 
	_test_eof1494:  state.cs = 1494; goto _test_eof; 
	_test_eof1495:  state.cs = 1495; goto _test_eof; 
	_test_eof1496:  state.cs = 1496; goto _test_eof; 
	_test_eof1497:  state.cs = 1497; goto _test_eof; 
	_test_eof1498:  state.cs = 1498; goto _test_eof; 
	_test_eof1499:  state.cs = 1499; goto _test_eof; 
	_test_eof1500:  state.cs = 1500; goto _test_eof; 
	_test_eof1501:  state.cs = 1501; goto _test_eof; 
	_test_eof1502:  state.cs = 1502; goto _test_eof; 
	_test_eof1503:  state.cs = 1503; goto _test_eof; 
	_test_eof1504:  state.cs = 1504; goto _test_eof; 
	_test_eof1505:  state.cs = 1505; goto _test_eof; 
	_test_eof1506:  state.cs = 1506; goto _test_eof; 
	_test_eof1507:  state.cs = 1507; goto _test_eof; 
	_test_eof1508:  state.cs = 1508; goto _test_eof; 
	_test_eof1509:  state.cs = 1509; goto _test_eof; 
	_test_eof1510:  state.cs = 1510; goto _test_eof; 
	_test_eof1511:  state.cs = 1511; goto _test_eof; 
	_test_eof1512:  state.cs = 1512; goto _test_eof; 
	_test_eof1513:  state.cs = 1513; goto _test_eof; 
	_test_eof1514:  state.cs = 1514; goto _test_eof; 
	_test_eof1515:  state.cs = 1515; goto _test_eof; 
	_test_eof1516:  state.cs = 1516; goto _test_eof; 
	_test_eof1517:  state.cs = 1517; goto _test_eof; 

	_test_eof: {}
	if ( ( state.p) == ( state.eof) )
	{
	switch (  state.cs ) {
	case 1521: 
#line 269 "configparser.rl"
	{ init_species(spe); }
	break;
	case 1518: 
#line 309 "configparser.rl"
	{ init_design(des); }
	break;
	case 1522: 
#line 357 "configparser.rl"
	{ init_terrain(ter); }
	break;
	case 1520: 
#line 396 "configparser.rl"
	{ init_levelskin_(lev); }
	break;
#line 21792 "configparser.h"
	}
	}

	_out: {}
	}

#line 435 "configparser.rl"

        // Avoid spurious gcc warnings.
        (void)ConfigParser_first_final;
        (void)ConfigParser_en_strchar_escape;
        (void)ConfigParser_en_one_species;
        (void)ConfigParser_en_one_design;
        (void)ConfigParser_en_one_terrain;
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
