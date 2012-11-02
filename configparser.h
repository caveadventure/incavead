
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

inline void print_species(const Species& s) {
    std::cout << "  tag: " << s.tag << std::endl;
    std::cout << "  name: " << s.name << std::endl;
    std::cout << "  skin: " << s.skin.text << " " << (int)s.skin.fore << " " << (int)s.skin.back << std::endl;
    std::cout << "  level: " << s.level << std::endl;
    std::cout << "  count: " << s.count << std::endl;
    std::cout << "  habitat: " << (int)s.habitat << std::endl;
    std::cout << "  ai: " << (int)s.ai << std::endl;
    std::cout << "  idle_ai: " << (int)s.idle_ai << std::endl;
    std::cout << "  move: " << (int)s.move << std::endl;
    std::cout << "  range: " << s.range << std::endl;
    std::cout << "  clumpsize: " << s.clumpsize.mean << " " << s.clumpsize.deviation << std::endl;

    init_species_copy(s);
}

inline void print_design(const Design& d) {
    std::cout << "  tag: " << d.tag << std::endl;
    std::cout << "  name: " << d.name << std::endl;
    std::cout << "  skin: " << d.skin.text << " " << (int)d.skin.fore << " " << (int)d.skin.back << std::endl;
    std::cout << "  level: " << d.level << std::endl;
    std::cout << "  count: " << d.count << std::endl;
    std::cout << "  descr: " << d.descr << std::endl;
    std::cout << "  attack: " << d.attack << std::endl;
    std::cout << "  defense: " << d.defense << std::endl;

    init_design_copy(d);
}

inline void add_color(maudit::color& c, unsigned int i) {
    c = (maudit::color)((uint32_t)c + i);
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

    maudit::glyph skin;

    
#line 267 "configparser.rl"

/*

*/

    
#line 112 "configparser.h"
static const int ConfigParser_start = 1;
static const int ConfigParser_first_final = 1484;
static const int ConfigParser_error = 0;

static const int ConfigParser_en_one_species = 25;
static const int ConfigParser_en_one_design = 933;
static const int ConfigParser_en_main = 1;


#line 273 "configparser.rl"
    
#line 124 "configparser.h"
	{
	 state.cs = ConfigParser_start;
	 state.top = 0;
	}

#line 274 "configparser.rl"

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

        
#line 153 "configparser.h"
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
		case 1484: goto st1484;
		case 1485: goto st1485;
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
		case 1486: goto st1486;
		case 25: goto st25;
		case 26: goto st26;
		case 27: goto st27;
		case 28: goto st28;
		case 29: goto st29;
		case 30: goto st30;
		case 31: goto st31;
		case 32: goto st32;
		case 33: goto st33;
		case 1487: goto st1487;
		case 34: goto st34;
		case 35: goto st35;
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
		case 1488: goto st1488;
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
		case 1489: goto st1489;
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
		case 1490: goto st1490;
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
		case 1491: goto st1491;
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
		case 1492: goto st1492;
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
		case 1493: goto st1493;
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
		case 1494: goto st1494;
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
		case 1495: goto st1495;
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
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1;
	goto st0;
st0:
 state.cs = 0;
	goto _out;
tr2:
#line 257 "configparser.rl"
	{ des = Design(); }
	goto st2;
tr2171:
#line 260 "configparser.rl"
	{ std::cout << "design done: " << std::endl; print_design(des); }
#line 257 "configparser.rl"
	{ des = Design(); }
	goto st2;
tr2175:
#line 227 "configparser.rl"
	{ std::cout << "species done: " << std::endl; print_species(spe); }
#line 257 "configparser.rl"
	{ des = Design(); }
	goto st2;
st2:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof2;
case 2:
#line 1701 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto tr4;
	goto st0;
tr4:
#line 257 "configparser.rl"
	{ des = Design(); }
	goto st3;
st3:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof3;
case 3:
#line 1713 "configparser.h"
	if ( (*( state.p)) == 115 )
		goto tr5;
	goto st0;
tr5:
#line 257 "configparser.rl"
	{ des = Design(); }
	goto st4;
st4:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof4;
case 4:
#line 1725 "configparser.h"
	if ( (*( state.p)) == 105 )
		goto tr6;
	goto st0;
tr6:
#line 257 "configparser.rl"
	{ des = Design(); }
	goto st5;
st5:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof5;
case 5:
#line 1737 "configparser.h"
	if ( (*( state.p)) == 103 )
		goto tr7;
	goto st0;
tr7:
#line 257 "configparser.rl"
	{ des = Design(); }
	goto st6;
st6:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof6;
case 6:
#line 1749 "configparser.h"
	if ( (*( state.p)) == 110 )
		goto tr8;
	goto st0;
tr8:
#line 257 "configparser.rl"
	{ des = Design(); }
	goto st7;
st7:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof7;
case 7:
#line 1761 "configparser.h"
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
			goto tr10;
	} else if ( (*( state.p)) >= 9 )
		goto st8;
	goto st0;
tr10:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st9;
tr12:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st9;
st9:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof9;
case 9:
#line 1803 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr11;
		case 32: goto tr11;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr12;
	} else if ( (*( state.p)) >= 9 )
		goto tr11;
	goto st0;
tr11:
#line 250 "configparser.rl"
	{ des.level = ::atoi(state.match.c_str()); }
	goto st10;
st10:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof10;
case 10:
#line 1822 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st10;
		case 32: goto st10;
		case 95: goto tr14;
	}
	if ( (*( state.p)) < 48 ) {
		if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
			goto st10;
	} else if ( (*( state.p)) > 57 ) {
		if ( (*( state.p)) > 90 ) {
			if ( 97 <= (*( state.p)) && (*( state.p)) <= 122 )
				goto tr14;
		} else if ( (*( state.p)) >= 65 )
			goto tr14;
	} else
		goto tr14;
	goto st0;
tr14:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st11;
tr16:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st11;
st11:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof11;
case 11:
#line 1860 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr15;
		case 32: goto tr15;
		case 95: goto tr16;
		case 123: goto tr17;
	}
	if ( (*( state.p)) < 48 ) {
		if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
			goto tr15;
	} else if ( (*( state.p)) > 57 ) {
		if ( (*( state.p)) > 90 ) {
			if ( 97 <= (*( state.p)) && (*( state.p)) <= 122 )
				goto tr16;
		} else if ( (*( state.p)) >= 65 )
			goto tr16;
	} else
		goto tr16;
	goto st0;
tr15:
#line 253 "configparser.rl"
	{ des.tag = state.match; }
	goto st12;
st12:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof12;
case 12:
#line 1887 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st12;
		case 32: goto st12;
		case 123: goto tr19;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st12;
	goto st0;
tr17:
#line 253 "configparser.rl"
	{ des.tag = state.match; }
#line 259 "configparser.rl"
	{{ state.stack[ state.top++] = 1484; goto st933;}}
	goto st1484;
tr19:
#line 259 "configparser.rl"
	{{ state.stack[ state.top++] = 1484; goto st933;}}
	goto st1484;
st1484:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1484;
case 1484:
#line 1910 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr2170;
		case 32: goto tr2170;
		case 100: goto tr2171;
		case 115: goto tr2172;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2170;
	goto st0;
tr2170:
#line 260 "configparser.rl"
	{ std::cout << "design done: " << std::endl; print_design(des); }
	goto st1485;
tr2174:
#line 227 "configparser.rl"
	{ std::cout << "species done: " << std::endl; print_species(spe); }
	goto st1485;
st1485:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1485;
case 1485:
#line 1932 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st1485;
		case 32: goto st1485;
		case 100: goto tr2;
		case 115: goto tr3;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1485;
	goto st0;
tr3:
#line 224 "configparser.rl"
	{ spe = Species(); }
	goto st13;
tr2172:
#line 260 "configparser.rl"
	{ std::cout << "design done: " << std::endl; print_design(des); }
#line 224 "configparser.rl"
	{ spe = Species(); }
	goto st13;
tr2176:
#line 227 "configparser.rl"
	{ std::cout << "species done: " << std::endl; print_species(spe); }
#line 224 "configparser.rl"
	{ spe = Species(); }
	goto st13;
st13:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof13;
case 13:
#line 1962 "configparser.h"
	if ( (*( state.p)) == 112 )
		goto tr20;
	goto st0;
tr20:
#line 224 "configparser.rl"
	{ spe = Species(); }
	goto st14;
st14:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof14;
case 14:
#line 1974 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto tr21;
	goto st0;
tr21:
#line 224 "configparser.rl"
	{ spe = Species(); }
	goto st15;
st15:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof15;
case 15:
#line 1986 "configparser.h"
	if ( (*( state.p)) == 99 )
		goto tr22;
	goto st0;
tr22:
#line 224 "configparser.rl"
	{ spe = Species(); }
	goto st16;
st16:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof16;
case 16:
#line 1998 "configparser.h"
	if ( (*( state.p)) == 105 )
		goto tr23;
	goto st0;
tr23:
#line 224 "configparser.rl"
	{ spe = Species(); }
	goto st17;
st17:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof17;
case 17:
#line 2010 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto tr24;
	goto st0;
tr24:
#line 224 "configparser.rl"
	{ spe = Species(); }
	goto st18;
st18:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof18;
case 18:
#line 2022 "configparser.h"
	if ( (*( state.p)) == 115 )
		goto tr25;
	goto st0;
tr25:
#line 224 "configparser.rl"
	{ spe = Species(); }
	goto st19;
st19:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof19;
case 19:
#line 2034 "configparser.h"
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
			goto tr27;
	} else if ( (*( state.p)) >= 9 )
		goto st20;
	goto st0;
tr27:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st21;
tr29:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st21;
st21:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof21;
case 21:
#line 2076 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr28;
		case 32: goto tr28;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr29;
	} else if ( (*( state.p)) >= 9 )
		goto tr28;
	goto st0;
tr28:
#line 217 "configparser.rl"
	{ spe.level = ::atoi(state.match.c_str()); }
	goto st22;
st22:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof22;
case 22:
#line 2095 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st22;
		case 32: goto st22;
		case 95: goto tr31;
	}
	if ( (*( state.p)) < 48 ) {
		if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
			goto st22;
	} else if ( (*( state.p)) > 57 ) {
		if ( (*( state.p)) > 90 ) {
			if ( 97 <= (*( state.p)) && (*( state.p)) <= 122 )
				goto tr31;
		} else if ( (*( state.p)) >= 65 )
			goto tr31;
	} else
		goto tr31;
	goto st0;
tr31:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st23;
tr33:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st23;
st23:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof23;
case 23:
#line 2133 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr32;
		case 32: goto tr32;
		case 95: goto tr33;
		case 123: goto tr34;
	}
	if ( (*( state.p)) < 48 ) {
		if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
			goto tr32;
	} else if ( (*( state.p)) > 57 ) {
		if ( (*( state.p)) > 90 ) {
			if ( 97 <= (*( state.p)) && (*( state.p)) <= 122 )
				goto tr33;
		} else if ( (*( state.p)) >= 65 )
			goto tr33;
	} else
		goto tr33;
	goto st0;
tr32:
#line 220 "configparser.rl"
	{ spe.tag = state.match; }
	goto st24;
st24:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof24;
case 24:
#line 2160 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st24;
		case 32: goto st24;
		case 123: goto tr36;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st24;
	goto st0;
tr34:
#line 220 "configparser.rl"
	{ spe.tag = state.match; }
#line 226 "configparser.rl"
	{{ state.stack[ state.top++] = 1486; goto st25;}}
	goto st1486;
tr36:
#line 226 "configparser.rl"
	{{ state.stack[ state.top++] = 1486; goto st25;}}
	goto st1486;
st1486:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1486;
case 1486:
#line 2183 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr2174;
		case 32: goto tr2174;
		case 100: goto tr2175;
		case 115: goto tr2176;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2174;
	goto st0;
st25:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof25;
case 25:
	switch( (*( state.p)) ) {
		case 13: goto st25;
		case 32: goto st25;
		case 97: goto st26;
		case 99: goto st34;
		case 100: goto st811;
		case 104: goto st823;
		case 105: goto st858;
		case 109: goto st876;
		case 110: goto st894;
		case 114: goto st899;
		case 115: goto st906;
		case 125: goto st911;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st25;
	goto st0;
st26:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof26;
case 26:
	switch( (*( state.p)) ) {
		case 105: goto st27;
		case 116: goto st923;
	}
	goto st0;
st27:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof27;
case 27:
	switch( (*( state.p)) ) {
		case 13: goto st28;
		case 32: goto st28;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st28;
	goto st0;
st28:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof28;
case 28:
	switch( (*( state.p)) ) {
		case 13: goto st28;
		case 32: goto st28;
		case 110: goto st29;
		case 115: goto st912;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st28;
	goto st0;
st29:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof29;
case 29:
	if ( (*( state.p)) == 111 )
		goto st30;
	goto st0;
st30:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof30;
case 30:
	if ( (*( state.p)) == 110 )
		goto st31;
	goto st0;
st31:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof31;
case 31:
	if ( (*( state.p)) == 101 )
		goto st32;
	goto st0;
st32:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof32;
case 32:
	switch( (*( state.p)) ) {
		case 13: goto tr56;
		case 32: goto tr56;
		case 59: goto tr57;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr56;
	goto st0;
tr56:
#line 173 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st33;
tr79:
#line 198 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
	goto st33;
tr103:
#line 203 "configparser.rl"
	{ spe.companion.back().chance = ::atof(state.match.c_str()); }
	goto st33;
tr323:
#line 186 "configparser.rl"
	{ spe.name = state.match; }
	goto st33;
tr585:
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st33;
tr588:
#line 151 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st33;
tr593:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st33;
tr599:
#line 149 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st33;
tr607:
#line 152 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st33;
tr611:
#line 148 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st33;
tr617:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st33;
tr624:
#line 150 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st33;
tr1166:
#line 185 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
	goto st33;
tr1179:
#line 194 "configparser.rl"
	{ spe.defense = ::atof(state.match.c_str()); }
	goto st33;
tr1199:
#line 169 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st33;
tr1205:
#line 167 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st33;
tr1215:
#line 170 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st33;
tr1221:
#line 166 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st33;
tr1225:
#line 168 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st33;
tr1239:
#line 177 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st33;
tr1246:
#line 178 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st33;
tr1257:
#line 181 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st33;
tr1263:
#line 182 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st33;
tr1269:
#line 183 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st33;
tr1282:
#line 192 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
	goto st33;
tr1290:
#line 211 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st33;
tr1302:
#line 174 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st33;
tr1312:
#line 193 "configparser.rl"
	{ spe.attack = ::atof(state.match.c_str()); }
	goto st33;
st33:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof33;
case 33:
#line 2410 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st33;
		case 32: goto st33;
		case 59: goto st1487;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st33;
	goto st0;
tr57:
#line 173 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st1487;
tr81:
#line 198 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
	goto st1487;
tr105:
#line 203 "configparser.rl"
	{ spe.companion.back().chance = ::atof(state.match.c_str()); }
	goto st1487;
tr324:
#line 186 "configparser.rl"
	{ spe.name = state.match; }
	goto st1487;
tr586:
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st1487;
tr589:
#line 151 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st1487;
tr594:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st1487;
tr600:
#line 149 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st1487;
tr608:
#line 152 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st1487;
tr612:
#line 148 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st1487;
tr618:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st1487;
tr625:
#line 150 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st1487;
tr1168:
#line 185 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
	goto st1487;
tr1181:
#line 194 "configparser.rl"
	{ spe.defense = ::atof(state.match.c_str()); }
	goto st1487;
tr1200:
#line 169 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st1487;
tr1206:
#line 167 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st1487;
tr1216:
#line 170 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st1487;
tr1222:
#line 166 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st1487;
tr1226:
#line 168 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st1487;
tr1240:
#line 177 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st1487;
tr1247:
#line 178 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st1487;
tr1258:
#line 181 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st1487;
tr1264:
#line 182 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st1487;
tr1270:
#line 183 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st1487;
tr1284:
#line 192 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
	goto st1487;
tr1291:
#line 211 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st1487;
tr1303:
#line 174 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st1487;
tr1314:
#line 193 "configparser.rl"
	{ spe.attack = ::atof(state.match.c_str()); }
	goto st1487;
st1487:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1487;
case 1487:
#line 2549 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st25;
		case 32: goto st25;
		case 97: goto st26;
		case 99: goto st34;
		case 100: goto st811;
		case 104: goto st823;
		case 105: goto st858;
		case 109: goto st876;
		case 110: goto st894;
		case 114: goto st899;
		case 115: goto st906;
		case 125: goto st911;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st25;
	goto st0;
st34:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof34;
case 34:
	switch( (*( state.p)) ) {
		case 108: goto st35;
		case 111: goto st53;
	}
	goto st0;
st35:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof35;
case 35:
	if ( (*( state.p)) == 117 )
		goto st36;
	goto st0;
st36:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof36;
case 36:
	if ( (*( state.p)) == 109 )
		goto st37;
	goto st0;
st37:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof37;
case 37:
	if ( (*( state.p)) == 112 )
		goto st38;
	goto st0;
st38:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof38;
case 38:
	if ( (*( state.p)) == 115 )
		goto st39;
	goto st0;
st39:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof39;
case 39:
	if ( (*( state.p)) == 105 )
		goto st40;
	goto st0;
st40:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof40;
case 40:
	if ( (*( state.p)) == 122 )
		goto st41;
	goto st0;
st41:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof41;
case 41:
	if ( (*( state.p)) == 101 )
		goto st42;
	goto st0;
st42:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof42;
case 42:
	switch( (*( state.p)) ) {
		case 13: goto st43;
		case 32: goto st43;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st43;
	goto st0;
st43:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof43;
case 43:
	switch( (*( state.p)) ) {
		case 13: goto st43;
		case 32: goto st43;
		case 45: goto tr70;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr71;
	} else if ( (*( state.p)) >= 9 )
		goto st43;
	goto st0;
tr70:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st44;
st44:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof44;
case 44:
#line 2665 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr72;
	goto st0;
tr71:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st45;
tr72:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st45;
st45:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof45;
case 45:
#line 2689 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr73;
		case 32: goto tr73;
		case 46: goto tr74;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr72;
	} else if ( (*( state.p)) >= 9 )
		goto tr73;
	goto st0;
tr73:
#line 197 "configparser.rl"
	{ spe.clumpsize.mean = ::atof(state.match.c_str()); }
	goto st46;
st46:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof46;
case 46:
#line 2709 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st46;
		case 32: goto st46;
		case 45: goto tr76;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr77;
	} else if ( (*( state.p)) >= 9 )
		goto st46;
	goto st0;
tr76:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st47;
st47:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof47;
case 47:
#line 2735 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr78;
	goto st0;
tr77:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st48;
tr78:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st48;
st48:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof48;
case 48:
#line 2759 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr79;
		case 32: goto tr79;
		case 46: goto tr80;
		case 59: goto tr81;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr78;
	} else if ( (*( state.p)) >= 9 )
		goto tr79;
	goto st0;
tr80:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st49;
st49:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof49;
case 49:
#line 2782 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr82;
	goto st0;
tr82:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st50;
st50:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof50;
case 50:
#line 2796 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr79;
		case 32: goto tr79;
		case 59: goto tr81;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr82;
	} else if ( (*( state.p)) >= 9 )
		goto tr79;
	goto st0;
tr74:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st51;
st51:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof51;
case 51:
#line 2818 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr83;
	goto st0;
tr83:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st52;
st52:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof52;
case 52:
#line 2832 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr73;
		case 32: goto tr73;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr83;
	} else if ( (*( state.p)) >= 9 )
		goto tr73;
	goto st0;
st53:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof53;
case 53:
	switch( (*( state.p)) ) {
		case 109: goto st54;
		case 117: goto st806;
	}
	goto st0;
st54:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof54;
case 54:
	if ( (*( state.p)) == 112 )
		goto st55;
	goto st0;
st55:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof55;
case 55:
	if ( (*( state.p)) == 97 )
		goto st56;
	goto st0;
st56:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof56;
case 56:
	if ( (*( state.p)) == 110 )
		goto st57;
	goto st0;
st57:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof57;
case 57:
	if ( (*( state.p)) == 105 )
		goto st58;
	goto st0;
st58:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof58;
case 58:
	if ( (*( state.p)) == 111 )
		goto st59;
	goto st0;
st59:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof59;
case 59:
	if ( (*( state.p)) == 110 )
		goto st60;
	goto st0;
st60:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof60;
case 60:
	switch( (*( state.p)) ) {
		case 13: goto tr92;
		case 32: goto tr92;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr92;
	goto st0;
tr92:
#line 201 "configparser.rl"
	{ spe.companion.push_back(Species::companion_t()); }
	goto st61;
st61:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof61;
case 61:
#line 2913 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st61;
		case 32: goto st61;
		case 34: goto st62;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st61;
	goto st0;
tr95:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st62;
tr107:
#line 138 "configparser.rl"
	{ state.match += '\\'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st62;
tr111:
#line 136 "configparser.rl"
	{ state.match += '"'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st62;
tr1159:
#line 137 "configparser.rl"
	{ state.match += '\n'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st62;
st62:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof62;
case 62:
#line 2956 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
	}
	goto tr95;
tr96:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st63;
tr113:
#line 136 "configparser.rl"
	{ state.match += '"'; }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st63;
tr1160:
#line 137 "configparser.rl"
	{ state.match += '\n'; }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st63;
st63:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof63;
case 63:
#line 2988 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr98;
		case 32: goto tr98;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr98;
	goto st0;
tr98:
#line 202 "configparser.rl"
	{ spe.companion.back().tag = state.match; }
	goto st64;
st64:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof64;
case 64:
#line 3004 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st64;
		case 32: goto st64;
		case 45: goto tr100;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr101;
	} else if ( (*( state.p)) >= 9 )
		goto st64;
	goto st0;
tr100:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st65;
st65:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof65;
case 65:
#line 3030 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr102;
	goto st0;
tr101:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st66;
tr102:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st66;
st66:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof66;
case 66:
#line 3054 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr103;
		case 32: goto tr103;
		case 46: goto tr104;
		case 59: goto tr105;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr102;
	} else if ( (*( state.p)) >= 9 )
		goto tr103;
	goto st0;
tr104:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st67;
st67:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof67;
case 67:
#line 3077 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr106;
	goto st0;
tr106:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st68;
st68:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof68;
case 68:
#line 3091 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr103;
		case 32: goto tr103;
		case 59: goto tr105;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr106;
	} else if ( (*( state.p)) >= 9 )
		goto tr103;
	goto st0;
tr109:
#line 138 "configparser.rl"
	{ state.match += '\\'; }
	goto st69;
tr114:
#line 136 "configparser.rl"
	{ state.match += '"'; }
	goto st69;
tr1161:
#line 137 "configparser.rl"
	{ state.match += '\n'; }
	goto st69;
st69:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof69;
case 69:
#line 3119 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr108;
		case 92: goto tr109;
		case 110: goto tr110;
	}
	goto tr107;
tr108:
#line 138 "configparser.rl"
	{ state.match += '\\'; }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st70;
st70:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof70;
case 70:
#line 3138 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr112;
		case 32: goto tr112;
		case 34: goto tr113;
		case 92: goto tr114;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr112;
	goto tr111;
tr115:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st71;
tr112:
#line 136 "configparser.rl"
	{ state.match += '"'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 202 "configparser.rl"
	{ spe.companion.back().tag = state.match; }
	goto st71;
tr204:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 202 "configparser.rl"
	{ spe.companion.back().tag = state.match; }
	goto st71;
st71:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof71;
case 71:
#line 3176 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr115;
		case 32: goto tr115;
		case 34: goto tr96;
		case 45: goto tr116;
		case 92: goto st69;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr117;
	} else if ( (*( state.p)) >= 9 )
		goto tr115;
	goto tr95;
tr116:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st72;
st72:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof72;
case 72:
#line 3204 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr118;
	goto tr95;
tr118:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st73;
tr117:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st73;
st73:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof73;
case 73:
#line 3232 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr119;
		case 32: goto tr119;
		case 34: goto tr96;
		case 46: goto tr120;
		case 59: goto tr121;
		case 92: goto st69;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr118;
	} else if ( (*( state.p)) >= 9 )
		goto tr119;
	goto tr95;
tr122:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st74;
tr119:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 203 "configparser.rl"
	{ spe.companion.back().chance = ::atof(state.match.c_str()); }
	goto st74;
tr143:
#line 173 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st74;
tr155:
#line 174 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st74;
tr165:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 193 "configparser.rl"
	{ spe.attack = ::atof(state.match.c_str()); }
	goto st74;
tr188:
#line 198 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st74;
tr209:
#line 185 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st74;
tr222:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 194 "configparser.rl"
	{ spe.defense = ::atof(state.match.c_str()); }
	goto st74;
tr242:
#line 169 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st74;
tr248:
#line 167 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st74;
tr258:
#line 170 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st74;
tr264:
#line 166 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st74;
tr268:
#line 168 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st74;
tr282:
#line 177 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st74;
tr289:
#line 178 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st74;
tr300:
#line 181 "configparser.rl"
	{ spe.move = Species::move_t::any; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st74;
tr306:
#line 182 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st74;
tr312:
#line 183 "configparser.rl"
	{ spe.move = Species::move_t::water; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st74;
tr416:
#line 186 "configparser.rl"
	{ spe.name = state.match; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st74;
tr794:
#line 187 "configparser.rl"
	{ spe.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st74;
tr797:
#line 151 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st74;
tr802:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st74;
tr808:
#line 149 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st74;
tr816:
#line 152 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st74;
tr820:
#line 148 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st74;
tr826:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st74;
tr833:
#line 150 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st74;
tr1156:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 211 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st74;
tr1139:
#line 192 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st74;
st74:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof74;
case 74:
#line 3495 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr122;
		case 32: goto tr122;
		case 34: goto tr96;
		case 59: goto tr123;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr122;
	goto tr95;
tr123:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1488;
tr121:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 203 "configparser.rl"
	{ spe.companion.back().chance = ::atof(state.match.c_str()); }
	goto st1488;
tr144:
#line 173 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1488;
tr156:
#line 174 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1488;
tr167:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 193 "configparser.rl"
	{ spe.attack = ::atof(state.match.c_str()); }
	goto st1488;
tr190:
#line 198 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1488;
tr211:
#line 185 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1488;
tr224:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 194 "configparser.rl"
	{ spe.defense = ::atof(state.match.c_str()); }
	goto st1488;
tr243:
#line 169 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1488;
tr249:
#line 167 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1488;
tr259:
#line 170 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1488;
tr265:
#line 166 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1488;
tr269:
#line 168 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1488;
tr283:
#line 177 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1488;
tr290:
#line 178 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1488;
tr301:
#line 181 "configparser.rl"
	{ spe.move = Species::move_t::any; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1488;
tr307:
#line 182 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1488;
tr313:
#line 183 "configparser.rl"
	{ spe.move = Species::move_t::water; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1488;
tr417:
#line 186 "configparser.rl"
	{ spe.name = state.match; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1488;
tr795:
#line 187 "configparser.rl"
	{ spe.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1488;
tr798:
#line 151 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1488;
tr803:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1488;
tr809:
#line 149 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1488;
tr817:
#line 152 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1488;
tr821:
#line 148 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1488;
tr827:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1488;
tr834:
#line 150 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1488;
tr1157:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 211 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st1488;
tr1141:
#line 192 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1488;
st1488:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1488;
case 1488:
#line 3754 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr124;
		case 32: goto tr124;
		case 34: goto tr96;
		case 92: goto st69;
		case 97: goto tr125;
		case 99: goto tr126;
		case 100: goto tr127;
		case 104: goto tr128;
		case 105: goto tr129;
		case 109: goto tr130;
		case 110: goto tr131;
		case 114: goto tr132;
		case 115: goto tr133;
		case 125: goto tr134;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr124;
	goto tr95;
tr124:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st75;
st75:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof75;
case 75:
#line 3784 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr124;
		case 32: goto tr124;
		case 34: goto tr96;
		case 92: goto st69;
		case 97: goto tr125;
		case 99: goto tr126;
		case 100: goto tr127;
		case 104: goto tr128;
		case 105: goto tr129;
		case 109: goto tr130;
		case 110: goto tr131;
		case 114: goto tr132;
		case 115: goto tr133;
		case 125: goto tr134;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr124;
	goto tr95;
tr125:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st76;
st76:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof76;
case 76:
#line 3814 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 105: goto tr135;
		case 116: goto tr136;
	}
	goto tr95;
tr135:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st77;
st77:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof77;
case 77:
#line 3832 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr137;
		case 32: goto tr137;
		case 34: goto tr96;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr137;
	goto tr95;
tr137:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st78;
st78:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof78;
case 78:
#line 3852 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr137;
		case 32: goto tr137;
		case 34: goto tr96;
		case 92: goto st69;
		case 110: goto tr138;
		case 115: goto tr139;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr137;
	goto tr95;
tr138:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st79;
st79:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof79;
case 79:
#line 3874 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 111: goto tr140;
	}
	goto tr95;
tr140:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st80;
st80:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof80;
case 80:
#line 3891 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 110: goto tr141;
	}
	goto tr95;
tr141:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st81;
st81:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof81;
case 81:
#line 3908 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 101: goto tr142;
	}
	goto tr95;
tr142:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st82;
st82:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof82;
case 82:
#line 3925 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr143;
		case 32: goto tr143;
		case 34: goto tr96;
		case 59: goto tr144;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr143;
	goto tr95;
tr139:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st83;
st83:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof83;
case 83:
#line 3946 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 101: goto tr145;
	}
	goto tr95;
tr145:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st84;
st84:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof84;
case 84:
#line 3963 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 101: goto tr146;
	}
	goto tr95;
tr146:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st85;
st85:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof85;
case 85:
#line 3980 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 107: goto tr147;
	}
	goto tr95;
tr147:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st86;
st86:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof86;
case 86:
#line 3997 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 95: goto tr148;
	}
	goto tr95;
tr148:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st87;
st87:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof87;
case 87:
#line 4014 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 112: goto tr149;
	}
	goto tr95;
tr149:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st88;
st88:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof88;
case 88:
#line 4031 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 108: goto tr150;
	}
	goto tr95;
tr150:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st89;
st89:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof89;
case 89:
#line 4048 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 97: goto tr151;
	}
	goto tr95;
tr151:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st90;
st90:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof90;
case 90:
#line 4065 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 121: goto tr152;
	}
	goto tr95;
tr152:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st91;
st91:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof91;
case 91:
#line 4082 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 101: goto tr153;
	}
	goto tr95;
tr153:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st92;
st92:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof92;
case 92:
#line 4099 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 114: goto tr154;
	}
	goto tr95;
tr154:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st93;
st93:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof93;
case 93:
#line 4116 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr155;
		case 32: goto tr155;
		case 34: goto tr96;
		case 59: goto tr156;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr155;
	goto tr95;
tr136:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st94;
st94:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof94;
case 94:
#line 4137 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 116: goto tr157;
	}
	goto tr95;
tr157:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st95;
st95:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof95;
case 95:
#line 4154 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 97: goto tr158;
	}
	goto tr95;
tr158:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st96;
st96:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof96;
case 96:
#line 4171 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 99: goto tr159;
	}
	goto tr95;
tr159:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st97;
st97:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof97;
case 97:
#line 4188 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 107: goto tr160;
	}
	goto tr95;
tr160:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st98;
st98:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof98;
case 98:
#line 4205 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr161;
		case 32: goto tr161;
		case 34: goto tr96;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr161;
	goto tr95;
tr161:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st99;
st99:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof99;
case 99:
#line 4225 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr161;
		case 32: goto tr161;
		case 34: goto tr96;
		case 45: goto tr162;
		case 92: goto st69;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr163;
	} else if ( (*( state.p)) >= 9 )
		goto tr161;
	goto tr95;
tr162:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st100;
st100:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof100;
case 100:
#line 4253 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr164;
	goto tr95;
tr164:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st101;
tr163:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st101;
st101:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof101;
case 101:
#line 4281 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr165;
		case 32: goto tr165;
		case 34: goto tr96;
		case 46: goto tr166;
		case 59: goto tr167;
		case 92: goto st69;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr164;
	} else if ( (*( state.p)) >= 9 )
		goto tr165;
	goto tr95;
tr166:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st102;
st102:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof102;
case 102:
#line 4306 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr168;
	goto tr95;
tr168:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st103;
st103:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof103;
case 103:
#line 4324 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr165;
		case 32: goto tr165;
		case 34: goto tr96;
		case 59: goto tr167;
		case 92: goto st69;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr168;
	} else if ( (*( state.p)) >= 9 )
		goto tr165;
	goto tr95;
tr126:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st104;
st104:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof104;
case 104:
#line 4348 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 108: goto tr169;
		case 111: goto tr170;
	}
	goto tr95;
tr169:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st105;
st105:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof105;
case 105:
#line 4366 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 117: goto tr171;
	}
	goto tr95;
tr171:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st106;
st106:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof106;
case 106:
#line 4383 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 109: goto tr172;
	}
	goto tr95;
tr172:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st107;
st107:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof107;
case 107:
#line 4400 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 112: goto tr173;
	}
	goto tr95;
tr173:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st108;
st108:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof108;
case 108:
#line 4417 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 115: goto tr174;
	}
	goto tr95;
tr174:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st109;
st109:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof109;
case 109:
#line 4434 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 105: goto tr175;
	}
	goto tr95;
tr175:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st110;
st110:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof110;
case 110:
#line 4451 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 122: goto tr176;
	}
	goto tr95;
tr176:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st111;
st111:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof111;
case 111:
#line 4468 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 101: goto tr177;
	}
	goto tr95;
tr177:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st112;
st112:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof112;
case 112:
#line 4485 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr178;
		case 32: goto tr178;
		case 34: goto tr96;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr178;
	goto tr95;
tr178:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st113;
st113:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof113;
case 113:
#line 4505 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr178;
		case 32: goto tr178;
		case 34: goto tr96;
		case 45: goto tr179;
		case 92: goto st69;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr180;
	} else if ( (*( state.p)) >= 9 )
		goto tr178;
	goto tr95;
tr179:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st114;
st114:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof114;
case 114:
#line 4533 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr181;
	goto tr95;
tr180:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st115;
tr181:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st115;
st115:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof115;
case 115:
#line 4561 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr182;
		case 32: goto tr182;
		case 34: goto tr96;
		case 46: goto tr183;
		case 92: goto st69;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr181;
	} else if ( (*( state.p)) >= 9 )
		goto tr182;
	goto tr95;
tr184:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st116;
tr182:
#line 197 "configparser.rl"
	{ spe.clumpsize.mean = ::atof(state.match.c_str()); }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st116;
st116:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof116;
case 116:
#line 4593 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr184;
		case 32: goto tr184;
		case 34: goto tr96;
		case 45: goto tr185;
		case 92: goto st69;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr186;
	} else if ( (*( state.p)) >= 9 )
		goto tr184;
	goto tr95;
tr185:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st117;
st117:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof117;
case 117:
#line 4621 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr187;
	goto tr95;
tr186:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st118;
tr187:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st118;
st118:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof118;
case 118:
#line 4649 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr188;
		case 32: goto tr188;
		case 34: goto tr96;
		case 46: goto tr189;
		case 59: goto tr190;
		case 92: goto st69;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr187;
	} else if ( (*( state.p)) >= 9 )
		goto tr188;
	goto tr95;
tr189:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st119;
st119:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof119;
case 119:
#line 4674 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr191;
	goto tr95;
tr191:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st120;
st120:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof120;
case 120:
#line 4692 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr188;
		case 32: goto tr188;
		case 34: goto tr96;
		case 59: goto tr190;
		case 92: goto st69;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr191;
	} else if ( (*( state.p)) >= 9 )
		goto tr188;
	goto tr95;
tr183:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st121;
st121:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof121;
case 121:
#line 4716 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr192;
	goto tr95;
tr192:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st122;
st122:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof122;
case 122:
#line 4734 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr182;
		case 32: goto tr182;
		case 34: goto tr96;
		case 92: goto st69;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr192;
	} else if ( (*( state.p)) >= 9 )
		goto tr182;
	goto tr95;
tr170:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st123;
st123:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof123;
case 123:
#line 4757 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 109: goto tr193;
		case 117: goto tr194;
	}
	goto tr95;
tr193:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st124;
st124:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof124;
case 124:
#line 4775 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 112: goto tr195;
	}
	goto tr95;
tr195:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st125;
st125:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof125;
case 125:
#line 4792 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 97: goto tr196;
	}
	goto tr95;
tr196:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st126;
st126:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof126;
case 126:
#line 4809 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 110: goto tr197;
	}
	goto tr95;
tr197:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st127;
st127:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof127;
case 127:
#line 4826 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 105: goto tr198;
	}
	goto tr95;
tr198:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st128;
st128:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof128;
case 128:
#line 4843 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 111: goto tr199;
	}
	goto tr95;
tr199:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st129;
st129:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof129;
case 129:
#line 4860 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 110: goto tr200;
	}
	goto tr95;
tr200:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st130;
st130:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof130;
case 130:
#line 4877 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr201;
		case 32: goto tr201;
		case 34: goto tr96;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr201;
	goto tr95;
tr202:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st131;
tr201:
#line 201 "configparser.rl"
	{ spe.companion.push_back(Species::companion_t()); }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st131;
st131:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof131;
case 131:
#line 4905 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr202;
		case 32: goto tr202;
		case 34: goto tr203;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr202;
	goto tr95;
tr203:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st132;
st132:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof132;
case 132:
#line 4925 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr204;
		case 32: goto tr204;
		case 34: goto tr96;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr204;
	goto tr95;
tr194:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st133;
st133:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof133;
case 133:
#line 4945 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 110: goto tr205;
	}
	goto tr95;
tr205:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st134;
st134:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof134;
case 134:
#line 4962 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 116: goto tr206;
	}
	goto tr95;
tr206:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st135;
st135:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof135;
case 135:
#line 4979 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr207;
		case 32: goto tr207;
		case 34: goto tr96;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr207;
	goto tr95;
tr207:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st136;
st136:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof136;
case 136:
#line 4999 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr207;
		case 32: goto tr207;
		case 34: goto tr96;
		case 92: goto st69;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr208;
	} else if ( (*( state.p)) >= 9 )
		goto tr207;
	goto tr95;
tr208:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st137;
tr210:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st137;
st137:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof137;
case 137:
#line 5032 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr209;
		case 32: goto tr209;
		case 34: goto tr96;
		case 59: goto tr211;
		case 92: goto st69;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr210;
	} else if ( (*( state.p)) >= 9 )
		goto tr209;
	goto tr95;
tr127:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st138;
st138:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof138;
case 138:
#line 5056 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 101: goto tr212;
	}
	goto tr95;
tr212:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st139;
st139:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof139;
case 139:
#line 5073 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 102: goto tr213;
	}
	goto tr95;
tr213:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st140;
st140:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof140;
case 140:
#line 5090 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 101: goto tr214;
	}
	goto tr95;
tr214:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st141;
st141:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof141;
case 141:
#line 5107 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 110: goto tr215;
	}
	goto tr95;
tr215:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st142;
st142:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof142;
case 142:
#line 5124 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 115: goto tr216;
	}
	goto tr95;
tr216:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st143;
st143:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof143;
case 143:
#line 5141 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 101: goto tr217;
	}
	goto tr95;
tr217:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st144;
st144:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof144;
case 144:
#line 5158 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr218;
		case 32: goto tr218;
		case 34: goto tr96;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr218;
	goto tr95;
tr218:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st145;
st145:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof145;
case 145:
#line 5178 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr218;
		case 32: goto tr218;
		case 34: goto tr96;
		case 45: goto tr219;
		case 92: goto st69;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr220;
	} else if ( (*( state.p)) >= 9 )
		goto tr218;
	goto tr95;
tr219:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st146;
st146:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof146;
case 146:
#line 5206 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr221;
	goto tr95;
tr221:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st147;
tr220:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st147;
st147:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof147;
case 147:
#line 5234 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr222;
		case 32: goto tr222;
		case 34: goto tr96;
		case 46: goto tr223;
		case 59: goto tr224;
		case 92: goto st69;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr221;
	} else if ( (*( state.p)) >= 9 )
		goto tr222;
	goto tr95;
tr223:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st148;
st148:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof148;
case 148:
#line 5259 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr225;
	goto tr95;
tr225:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st149;
st149:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof149;
case 149:
#line 5277 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr222;
		case 32: goto tr222;
		case 34: goto tr96;
		case 59: goto tr224;
		case 92: goto st69;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr225;
	} else if ( (*( state.p)) >= 9 )
		goto tr222;
	goto tr95;
tr128:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st150;
st150:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof150;
case 150:
#line 5301 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 97: goto tr226;
	}
	goto tr95;
tr226:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st151;
st151:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof151;
case 151:
#line 5318 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 98: goto tr227;
	}
	goto tr95;
tr227:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st152;
st152:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof152;
case 152:
#line 5335 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 105: goto tr228;
	}
	goto tr95;
tr228:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st153;
st153:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof153;
case 153:
#line 5352 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 116: goto tr229;
	}
	goto tr95;
tr229:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st154;
st154:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof154;
case 154:
#line 5369 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 97: goto tr230;
	}
	goto tr95;
tr230:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st155;
st155:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof155;
case 155:
#line 5386 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 116: goto tr231;
	}
	goto tr95;
tr231:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st156;
st156:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof156;
case 156:
#line 5403 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr232;
		case 32: goto tr232;
		case 34: goto tr96;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr232;
	goto tr95;
tr232:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st157;
st157:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof157;
case 157:
#line 5423 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr232;
		case 32: goto tr232;
		case 34: goto tr96;
		case 92: goto st69;
		case 99: goto tr233;
		case 102: goto tr234;
		case 115: goto tr235;
		case 119: goto tr236;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr232;
	goto tr95;
tr233:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st158;
st158:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof158;
case 158:
#line 5447 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 111: goto tr237;
	}
	goto tr95;
tr237:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st159;
st159:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof159;
case 159:
#line 5464 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 114: goto tr238;
	}
	goto tr95;
tr238:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st160;
st160:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof160;
case 160:
#line 5481 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 110: goto tr239;
	}
	goto tr95;
tr239:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st161;
st161:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof161;
case 161:
#line 5498 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 101: goto tr240;
	}
	goto tr95;
tr240:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st162;
st162:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof162;
case 162:
#line 5515 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 114: goto tr241;
	}
	goto tr95;
tr241:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st163;
st163:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof163;
case 163:
#line 5532 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr242;
		case 32: goto tr242;
		case 34: goto tr96;
		case 59: goto tr243;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr242;
	goto tr95;
tr234:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st164;
st164:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof164;
case 164:
#line 5553 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 108: goto tr244;
	}
	goto tr95;
tr244:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st165;
st165:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof165;
case 165:
#line 5570 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 111: goto tr245;
	}
	goto tr95;
tr245:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st166;
st166:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof166;
case 166:
#line 5587 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 111: goto tr246;
	}
	goto tr95;
tr246:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st167;
st167:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof167;
case 167:
#line 5604 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 114: goto tr247;
	}
	goto tr95;
tr247:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st168;
st168:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof168;
case 168:
#line 5621 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr248;
		case 32: goto tr248;
		case 34: goto tr96;
		case 59: goto tr249;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr248;
	goto tr95;
tr235:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st169;
st169:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof169;
case 169:
#line 5642 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 104: goto tr250;
	}
	goto tr95;
tr250:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st170;
st170:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof170;
case 170:
#line 5659 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 111: goto tr251;
	}
	goto tr95;
tr251:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st171;
st171:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof171;
case 171:
#line 5676 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 114: goto tr252;
	}
	goto tr95;
tr252:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st172;
st172:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof172;
case 172:
#line 5693 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 101: goto tr253;
	}
	goto tr95;
tr253:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st173;
st173:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof173;
case 173:
#line 5710 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 108: goto tr254;
	}
	goto tr95;
tr254:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st174;
st174:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof174;
case 174:
#line 5727 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 105: goto tr255;
	}
	goto tr95;
tr255:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st175;
st175:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof175;
case 175:
#line 5744 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 110: goto tr256;
	}
	goto tr95;
tr256:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st176;
st176:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof176;
case 176:
#line 5761 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 101: goto tr257;
	}
	goto tr95;
tr257:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st177;
st177:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof177;
case 177:
#line 5778 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr258;
		case 32: goto tr258;
		case 34: goto tr96;
		case 59: goto tr259;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr258;
	goto tr95;
tr236:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st178;
st178:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof178;
case 178:
#line 5799 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 97: goto tr260;
	}
	goto tr95;
tr260:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st179;
st179:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof179;
case 179:
#line 5816 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 108: goto tr261;
		case 116: goto tr262;
	}
	goto tr95;
tr261:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st180;
st180:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof180;
case 180:
#line 5834 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 107: goto tr263;
	}
	goto tr95;
tr263:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st181;
st181:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof181;
case 181:
#line 5851 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr264;
		case 32: goto tr264;
		case 34: goto tr96;
		case 59: goto tr265;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr264;
	goto tr95;
tr262:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st182;
st182:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof182;
case 182:
#line 5872 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 101: goto tr266;
	}
	goto tr95;
tr266:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st183;
st183:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof183;
case 183:
#line 5889 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 114: goto tr267;
	}
	goto tr95;
tr267:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st184;
st184:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof184;
case 184:
#line 5906 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr268;
		case 32: goto tr268;
		case 34: goto tr96;
		case 59: goto tr269;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr268;
	goto tr95;
tr129:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st185;
st185:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof185;
case 185:
#line 5927 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 100: goto tr270;
	}
	goto tr95;
tr270:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st186;
st186:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof186;
case 186:
#line 5944 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 108: goto tr271;
	}
	goto tr95;
tr271:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st187;
st187:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof187;
case 187:
#line 5961 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 101: goto tr272;
	}
	goto tr95;
tr272:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st188;
st188:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof188;
case 188:
#line 5978 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 95: goto tr273;
	}
	goto tr95;
tr273:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st189;
st189:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof189;
case 189:
#line 5995 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 97: goto tr274;
	}
	goto tr95;
tr274:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st190;
st190:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof190;
case 190:
#line 6012 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 105: goto tr275;
	}
	goto tr95;
tr275:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st191;
st191:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof191;
case 191:
#line 6029 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr276;
		case 32: goto tr276;
		case 34: goto tr96;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr276;
	goto tr95;
tr276:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st192;
st192:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof192;
case 192:
#line 6049 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr276;
		case 32: goto tr276;
		case 34: goto tr96;
		case 92: goto st69;
		case 110: goto tr277;
		case 114: goto tr278;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr276;
	goto tr95;
tr277:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st193;
st193:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof193;
case 193:
#line 6071 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 111: goto tr279;
	}
	goto tr95;
tr279:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st194;
st194:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof194;
case 194:
#line 6088 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 110: goto tr280;
	}
	goto tr95;
tr280:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st195;
st195:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof195;
case 195:
#line 6105 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 101: goto tr281;
	}
	goto tr95;
tr281:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st196;
st196:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof196;
case 196:
#line 6122 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr282;
		case 32: goto tr282;
		case 34: goto tr96;
		case 59: goto tr283;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr282;
	goto tr95;
tr278:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st197;
st197:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof197;
case 197:
#line 6143 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 97: goto tr284;
	}
	goto tr95;
tr284:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st198;
st198:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof198;
case 198:
#line 6160 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 110: goto tr285;
	}
	goto tr95;
tr285:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st199;
st199:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof199;
case 199:
#line 6177 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 100: goto tr286;
	}
	goto tr95;
tr286:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st200;
st200:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof200;
case 200:
#line 6194 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 111: goto tr287;
	}
	goto tr95;
tr287:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st201;
st201:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof201;
case 201:
#line 6211 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 109: goto tr288;
	}
	goto tr95;
tr288:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st202;
st202:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof202;
case 202:
#line 6228 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr289;
		case 32: goto tr289;
		case 34: goto tr96;
		case 59: goto tr290;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr289;
	goto tr95;
tr130:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st203;
st203:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof203;
case 203:
#line 6249 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 111: goto tr291;
	}
	goto tr95;
tr291:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st204;
st204:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof204;
case 204:
#line 6266 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 118: goto tr292;
	}
	goto tr95;
tr292:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st205;
st205:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof205;
case 205:
#line 6283 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 101: goto tr293;
	}
	goto tr95;
tr293:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st206;
st206:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof206;
case 206:
#line 6300 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr294;
		case 32: goto tr294;
		case 34: goto tr96;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr294;
	goto tr95;
tr294:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st207;
st207:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof207;
case 207:
#line 6320 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr294;
		case 32: goto tr294;
		case 34: goto tr96;
		case 92: goto st69;
		case 97: goto tr295;
		case 102: goto tr296;
		case 119: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr294;
	goto tr95;
tr295:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st208;
st208:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof208;
case 208:
#line 6343 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 110: goto tr298;
	}
	goto tr95;
tr298:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st209;
st209:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof209;
case 209:
#line 6360 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 121: goto tr299;
	}
	goto tr95;
tr299:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st210;
st210:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof210;
case 210:
#line 6377 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr300;
		case 32: goto tr300;
		case 34: goto tr96;
		case 59: goto tr301;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr300;
	goto tr95;
tr296:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st211;
st211:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof211;
case 211:
#line 6398 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 108: goto tr302;
	}
	goto tr95;
tr302:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st212;
st212:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof212;
case 212:
#line 6415 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 111: goto tr303;
	}
	goto tr95;
tr303:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st213;
st213:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof213;
case 213:
#line 6432 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 111: goto tr304;
	}
	goto tr95;
tr304:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st214;
st214:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof214;
case 214:
#line 6449 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 114: goto tr305;
	}
	goto tr95;
tr305:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st215;
st215:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof215;
case 215:
#line 6466 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr306;
		case 32: goto tr306;
		case 34: goto tr96;
		case 59: goto tr307;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr306;
	goto tr95;
tr297:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st216;
st216:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof216;
case 216:
#line 6487 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 97: goto tr308;
	}
	goto tr95;
tr308:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st217;
st217:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof217;
case 217:
#line 6504 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 116: goto tr309;
	}
	goto tr95;
tr309:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st218;
st218:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof218;
case 218:
#line 6521 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 101: goto tr310;
	}
	goto tr95;
tr310:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st219;
st219:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof219;
case 219:
#line 6538 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 114: goto tr311;
	}
	goto tr95;
tr311:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st220;
st220:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof220;
case 220:
#line 6555 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr312;
		case 32: goto tr312;
		case 34: goto tr96;
		case 59: goto tr313;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr312;
	goto tr95;
tr131:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st221;
st221:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof221;
case 221:
#line 6576 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 97: goto tr314;
	}
	goto tr95;
tr314:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st222;
st222:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof222;
case 222:
#line 6593 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 109: goto tr315;
	}
	goto tr95;
tr315:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st223;
st223:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof223;
case 223:
#line 6610 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 101: goto tr316;
	}
	goto tr95;
tr316:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st224;
st224:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof224;
case 224:
#line 6627 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr317;
		case 32: goto tr317;
		case 34: goto tr96;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr317;
	goto tr95;
tr317:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st225;
st225:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof225;
case 225:
#line 6647 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr317;
		case 32: goto tr317;
		case 34: goto tr318;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr317;
	goto tr95;
tr318:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st226;
st226:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof226;
case 226:
#line 6667 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr320;
		case 32: goto tr320;
		case 34: goto tr321;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr320;
	goto tr319;
tr319:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st227;
tr325:
#line 138 "configparser.rl"
	{ state.match += '\\'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st227;
tr329:
#line 136 "configparser.rl"
	{ state.match += '"'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st227;
tr1122:
#line 137 "configparser.rl"
	{ state.match += '\n'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st227;
st227:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof227;
case 227:
#line 6711 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
	}
	goto tr319;
tr321:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st228;
tr331:
#line 136 "configparser.rl"
	{ state.match += '"'; }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st228;
tr1123:
#line 137 "configparser.rl"
	{ state.match += '\n'; }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st228;
st228:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof228;
case 228:
#line 6743 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr323;
		case 32: goto tr323;
		case 59: goto tr324;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr323;
	goto st0;
tr327:
#line 138 "configparser.rl"
	{ state.match += '\\'; }
	goto st229;
tr333:
#line 136 "configparser.rl"
	{ state.match += '"'; }
	goto st229;
tr1124:
#line 137 "configparser.rl"
	{ state.match += '\n'; }
	goto st229;
st229:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof229;
case 229:
#line 6768 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr326;
		case 92: goto tr327;
		case 110: goto tr328;
	}
	goto tr325;
tr326:
#line 138 "configparser.rl"
	{ state.match += '\\'; }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st230;
st230:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof230;
case 230:
#line 6787 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr330;
		case 32: goto tr330;
		case 34: goto tr331;
		case 59: goto tr332;
		case 92: goto tr333;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr330;
	goto tr329;
tr334:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st231;
tr1129:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 203 "configparser.rl"
	{ spe.companion.back().chance = ::atof(state.match.c_str()); }
	goto st231;
tr377:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 193 "configparser.rl"
	{ spe.attack = ::atof(state.match.c_str()); }
	goto st231;
tr422:
#line 185 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st231;
tr435:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 194 "configparser.rl"
	{ spe.defense = ::atof(state.match.c_str()); }
	goto st231;
tr330:
#line 136 "configparser.rl"
	{ state.match += '"'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 186 "configparser.rl"
	{ spe.name = state.match; }
	goto st231;
tr355:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 173 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st231;
tr367:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 174 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st231;
tr400:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 198 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
	goto st231;
tr455:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 169 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st231;
tr461:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 167 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st231;
tr471:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 170 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st231;
tr477:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 166 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st231;
tr481:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 168 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st231;
tr495:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 177 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st231;
tr502:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 178 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st231;
tr513:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 181 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st231;
tr519:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 182 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st231;
tr525:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 183 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st231;
tr532:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 186 "configparser.rl"
	{ spe.name = state.match; }
	goto st231;
tr540:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 192 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
	goto st231;
tr994:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st231;
tr997:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 151 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st231;
tr1002:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 153 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st231;
tr1008:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 149 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st231;
tr1016:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 152 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st231;
tr1020:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 148 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st231;
tr1026:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 154 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st231;
tr1033:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 150 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st231;
tr1120:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 211 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st231;
st231:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof231;
case 231:
#line 7056 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr334;
		case 32: goto tr334;
		case 34: goto tr321;
		case 59: goto tr335;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr334;
	goto tr319;
tr335:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1489;
tr1131:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 203 "configparser.rl"
	{ spe.companion.back().chance = ::atof(state.match.c_str()); }
	goto st1489;
tr379:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 193 "configparser.rl"
	{ spe.attack = ::atof(state.match.c_str()); }
	goto st1489;
tr424:
#line 185 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1489;
tr437:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 194 "configparser.rl"
	{ spe.defense = ::atof(state.match.c_str()); }
	goto st1489;
tr332:
#line 136 "configparser.rl"
	{ state.match += '"'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 186 "configparser.rl"
	{ spe.name = state.match; }
	goto st1489;
tr356:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 173 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st1489;
tr368:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 174 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st1489;
tr402:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 198 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
	goto st1489;
tr456:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 169 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st1489;
tr462:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 167 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st1489;
tr472:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 170 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st1489;
tr478:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 166 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st1489;
tr482:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 168 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st1489;
tr496:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 177 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st1489;
tr503:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 178 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st1489;
tr514:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 181 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st1489;
tr520:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 182 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st1489;
tr526:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 183 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st1489;
tr533:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 186 "configparser.rl"
	{ spe.name = state.match; }
	goto st1489;
tr542:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 192 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
	goto st1489;
tr995:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st1489;
tr998:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 151 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st1489;
tr1003:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 153 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st1489;
tr1009:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 149 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st1489;
tr1017:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 152 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st1489;
tr1021:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 148 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st1489;
tr1027:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 154 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st1489;
tr1034:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 150 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st1489;
tr1121:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 211 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st1489;
st1489:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1489;
case 1489:
#line 7325 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr336;
		case 32: goto tr336;
		case 34: goto tr321;
		case 92: goto st229;
		case 97: goto tr337;
		case 99: goto tr338;
		case 100: goto tr339;
		case 104: goto tr340;
		case 105: goto tr341;
		case 109: goto tr342;
		case 110: goto tr343;
		case 114: goto tr344;
		case 115: goto tr345;
		case 125: goto tr346;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr336;
	goto tr319;
tr336:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st232;
st232:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof232;
case 232:
#line 7355 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr336;
		case 32: goto tr336;
		case 34: goto tr321;
		case 92: goto st229;
		case 97: goto tr337;
		case 99: goto tr338;
		case 100: goto tr339;
		case 104: goto tr340;
		case 105: goto tr341;
		case 109: goto tr342;
		case 110: goto tr343;
		case 114: goto tr344;
		case 115: goto tr345;
		case 125: goto tr346;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr336;
	goto tr319;
tr337:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st233;
st233:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof233;
case 233:
#line 7385 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 105: goto tr347;
		case 116: goto tr348;
	}
	goto tr319;
tr347:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st234;
st234:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof234;
case 234:
#line 7403 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr349;
		case 32: goto tr349;
		case 34: goto tr321;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr349;
	goto tr319;
tr349:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st235;
st235:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof235;
case 235:
#line 7423 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr349;
		case 32: goto tr349;
		case 34: goto tr321;
		case 92: goto st229;
		case 110: goto tr350;
		case 115: goto tr351;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr349;
	goto tr319;
tr350:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st236;
st236:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof236;
case 236:
#line 7445 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 111: goto tr352;
	}
	goto tr319;
tr352:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st237;
st237:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof237;
case 237:
#line 7462 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 110: goto tr353;
	}
	goto tr319;
tr353:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st238;
st238:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof238;
case 238:
#line 7479 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 101: goto tr354;
	}
	goto tr319;
tr354:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st239;
st239:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof239;
case 239:
#line 7496 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr355;
		case 32: goto tr355;
		case 34: goto tr321;
		case 59: goto tr356;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr355;
	goto tr319;
tr351:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st240;
st240:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof240;
case 240:
#line 7517 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 101: goto tr357;
	}
	goto tr319;
tr357:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st241;
st241:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof241;
case 241:
#line 7534 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 101: goto tr358;
	}
	goto tr319;
tr358:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st242;
st242:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof242;
case 242:
#line 7551 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 107: goto tr359;
	}
	goto tr319;
tr359:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st243;
st243:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof243;
case 243:
#line 7568 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 95: goto tr360;
	}
	goto tr319;
tr360:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st244;
st244:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof244;
case 244:
#line 7585 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 112: goto tr361;
	}
	goto tr319;
tr361:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st245;
st245:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof245;
case 245:
#line 7602 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 108: goto tr362;
	}
	goto tr319;
tr362:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st246;
st246:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof246;
case 246:
#line 7619 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 97: goto tr363;
	}
	goto tr319;
tr363:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st247;
st247:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof247;
case 247:
#line 7636 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 121: goto tr364;
	}
	goto tr319;
tr364:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st248;
st248:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof248;
case 248:
#line 7653 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 101: goto tr365;
	}
	goto tr319;
tr365:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st249;
st249:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof249;
case 249:
#line 7670 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 114: goto tr366;
	}
	goto tr319;
tr366:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st250;
st250:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof250;
case 250:
#line 7687 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr367;
		case 32: goto tr367;
		case 34: goto tr321;
		case 59: goto tr368;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr367;
	goto tr319;
tr348:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st251;
st251:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof251;
case 251:
#line 7708 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 116: goto tr369;
	}
	goto tr319;
tr369:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st252;
st252:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof252;
case 252:
#line 7725 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 97: goto tr370;
	}
	goto tr319;
tr370:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st253;
st253:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof253;
case 253:
#line 7742 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 99: goto tr371;
	}
	goto tr319;
tr371:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st254;
st254:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof254;
case 254:
#line 7759 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 107: goto tr372;
	}
	goto tr319;
tr372:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st255;
st255:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof255;
case 255:
#line 7776 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr373;
		case 32: goto tr373;
		case 34: goto tr321;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr373;
	goto tr319;
tr373:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st256;
st256:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof256;
case 256:
#line 7796 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr373;
		case 32: goto tr373;
		case 34: goto tr321;
		case 45: goto tr374;
		case 92: goto st229;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr375;
	} else if ( (*( state.p)) >= 9 )
		goto tr373;
	goto tr319;
tr374:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st257;
st257:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof257;
case 257:
#line 7824 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr376;
	goto tr319;
tr376:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st258;
tr375:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st258;
st258:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof258;
case 258:
#line 7852 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr377;
		case 32: goto tr377;
		case 34: goto tr321;
		case 46: goto tr378;
		case 59: goto tr379;
		case 92: goto st229;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr376;
	} else if ( (*( state.p)) >= 9 )
		goto tr377;
	goto tr319;
tr378:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st259;
st259:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof259;
case 259:
#line 7877 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr380;
	goto tr319;
tr380:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st260;
st260:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof260;
case 260:
#line 7895 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr377;
		case 32: goto tr377;
		case 34: goto tr321;
		case 59: goto tr379;
		case 92: goto st229;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr380;
	} else if ( (*( state.p)) >= 9 )
		goto tr377;
	goto tr319;
tr338:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st261;
st261:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof261;
case 261:
#line 7919 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 108: goto tr381;
		case 111: goto tr382;
	}
	goto tr319;
tr381:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st262;
st262:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof262;
case 262:
#line 7937 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 117: goto tr383;
	}
	goto tr319;
tr383:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st263;
st263:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof263;
case 263:
#line 7954 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 109: goto tr384;
	}
	goto tr319;
tr384:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st264;
st264:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof264;
case 264:
#line 7971 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 112: goto tr385;
	}
	goto tr319;
tr385:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st265;
st265:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof265;
case 265:
#line 7988 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 115: goto tr386;
	}
	goto tr319;
tr386:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st266;
st266:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof266;
case 266:
#line 8005 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 105: goto tr387;
	}
	goto tr319;
tr387:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st267;
st267:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof267;
case 267:
#line 8022 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 122: goto tr388;
	}
	goto tr319;
tr388:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st268;
st268:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof268;
case 268:
#line 8039 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 101: goto tr389;
	}
	goto tr319;
tr389:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st269;
st269:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof269;
case 269:
#line 8056 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr390;
		case 32: goto tr390;
		case 34: goto tr321;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr390;
	goto tr319;
tr390:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st270;
st270:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof270;
case 270:
#line 8076 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr390;
		case 32: goto tr390;
		case 34: goto tr321;
		case 45: goto tr391;
		case 92: goto st229;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr392;
	} else if ( (*( state.p)) >= 9 )
		goto tr390;
	goto tr319;
tr391:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st271;
st271:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof271;
case 271:
#line 8104 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr393;
	goto tr319;
tr393:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st272;
tr392:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st272;
st272:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof272;
case 272:
#line 8132 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr394;
		case 32: goto tr394;
		case 34: goto tr321;
		case 46: goto tr395;
		case 92: goto st229;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr393;
	} else if ( (*( state.p)) >= 9 )
		goto tr394;
	goto tr319;
tr396:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st273;
tr394:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 197 "configparser.rl"
	{ spe.clumpsize.mean = ::atof(state.match.c_str()); }
	goto st273;
st273:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof273;
case 273:
#line 8164 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr396;
		case 32: goto tr396;
		case 34: goto tr321;
		case 45: goto tr397;
		case 92: goto st229;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr398;
	} else if ( (*( state.p)) >= 9 )
		goto tr396;
	goto tr319;
tr397:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st274;
st274:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof274;
case 274:
#line 8192 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr399;
	goto tr319;
tr399:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st275;
tr398:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st275;
st275:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof275;
case 275:
#line 8220 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr400;
		case 32: goto tr400;
		case 34: goto tr321;
		case 46: goto tr401;
		case 59: goto tr402;
		case 92: goto st229;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr399;
	} else if ( (*( state.p)) >= 9 )
		goto tr400;
	goto tr319;
tr401:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st276;
st276:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof276;
case 276:
#line 8245 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr403;
	goto tr319;
tr403:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st277;
st277:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof277;
case 277:
#line 8263 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr400;
		case 32: goto tr400;
		case 34: goto tr321;
		case 59: goto tr402;
		case 92: goto st229;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr403;
	} else if ( (*( state.p)) >= 9 )
		goto tr400;
	goto tr319;
tr395:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st278;
st278:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof278;
case 278:
#line 8287 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr404;
	goto tr319;
tr404:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st279;
st279:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof279;
case 279:
#line 8305 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr394;
		case 32: goto tr394;
		case 34: goto tr321;
		case 92: goto st229;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr404;
	} else if ( (*( state.p)) >= 9 )
		goto tr394;
	goto tr319;
tr382:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st280;
st280:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof280;
case 280:
#line 8328 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 109: goto tr405;
		case 117: goto tr406;
	}
	goto tr319;
tr405:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st281;
st281:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof281;
case 281:
#line 8346 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 112: goto tr407;
	}
	goto tr319;
tr407:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st282;
st282:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof282;
case 282:
#line 8363 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 97: goto tr408;
	}
	goto tr319;
tr408:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st283;
st283:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof283;
case 283:
#line 8380 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 110: goto tr409;
	}
	goto tr319;
tr409:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st284;
st284:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof284;
case 284:
#line 8397 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 105: goto tr410;
	}
	goto tr319;
tr410:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st285;
st285:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof285;
case 285:
#line 8414 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 111: goto tr411;
	}
	goto tr319;
tr411:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st286;
st286:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof286;
case 286:
#line 8431 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 110: goto tr412;
	}
	goto tr319;
tr412:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st287;
st287:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof287;
case 287:
#line 8448 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr413;
		case 32: goto tr413;
		case 34: goto tr321;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr413;
	goto tr319;
tr414:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st288;
tr413:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 201 "configparser.rl"
	{ spe.companion.push_back(Species::companion_t()); }
	goto st288;
st288:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof288;
case 288:
#line 8476 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr414;
		case 32: goto tr414;
		case 34: goto tr415;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr414;
	goto tr319;
tr415:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st289;
st289:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof289;
case 289:
#line 8496 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr416;
		case 32: goto tr416;
		case 34: goto tr96;
		case 59: goto tr417;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr416;
	goto tr95;
tr406:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st290;
st290:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof290;
case 290:
#line 8517 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 110: goto tr418;
	}
	goto tr319;
tr418:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st291;
st291:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof291;
case 291:
#line 8534 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 116: goto tr419;
	}
	goto tr319;
tr419:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st292;
st292:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof292;
case 292:
#line 8551 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr420;
		case 32: goto tr420;
		case 34: goto tr321;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr420;
	goto tr319;
tr420:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st293;
st293:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof293;
case 293:
#line 8571 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr420;
		case 32: goto tr420;
		case 34: goto tr321;
		case 92: goto st229;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr421;
	} else if ( (*( state.p)) >= 9 )
		goto tr420;
	goto tr319;
tr421:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st294;
tr423:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st294;
st294:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof294;
case 294:
#line 8604 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr422;
		case 32: goto tr422;
		case 34: goto tr321;
		case 59: goto tr424;
		case 92: goto st229;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr423;
	} else if ( (*( state.p)) >= 9 )
		goto tr422;
	goto tr319;
tr339:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st295;
st295:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof295;
case 295:
#line 8628 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 101: goto tr425;
	}
	goto tr319;
tr425:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st296;
st296:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof296;
case 296:
#line 8645 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 102: goto tr426;
	}
	goto tr319;
tr426:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st297;
st297:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof297;
case 297:
#line 8662 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 101: goto tr427;
	}
	goto tr319;
tr427:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st298;
st298:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof298;
case 298:
#line 8679 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 110: goto tr428;
	}
	goto tr319;
tr428:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st299;
st299:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof299;
case 299:
#line 8696 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 115: goto tr429;
	}
	goto tr319;
tr429:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st300;
st300:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof300;
case 300:
#line 8713 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 101: goto tr430;
	}
	goto tr319;
tr430:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st301;
st301:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof301;
case 301:
#line 8730 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr431;
		case 32: goto tr431;
		case 34: goto tr321;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr431;
	goto tr319;
tr431:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st302;
st302:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof302;
case 302:
#line 8750 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr431;
		case 32: goto tr431;
		case 34: goto tr321;
		case 45: goto tr432;
		case 92: goto st229;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr433;
	} else if ( (*( state.p)) >= 9 )
		goto tr431;
	goto tr319;
tr432:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st303;
st303:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof303;
case 303:
#line 8778 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr434;
	goto tr319;
tr434:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st304;
tr433:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st304;
st304:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof304;
case 304:
#line 8806 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr435;
		case 32: goto tr435;
		case 34: goto tr321;
		case 46: goto tr436;
		case 59: goto tr437;
		case 92: goto st229;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr434;
	} else if ( (*( state.p)) >= 9 )
		goto tr435;
	goto tr319;
tr436:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st305;
st305:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof305;
case 305:
#line 8831 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr438;
	goto tr319;
tr438:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st306;
st306:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof306;
case 306:
#line 8849 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr435;
		case 32: goto tr435;
		case 34: goto tr321;
		case 59: goto tr437;
		case 92: goto st229;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr438;
	} else if ( (*( state.p)) >= 9 )
		goto tr435;
	goto tr319;
tr340:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st307;
st307:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof307;
case 307:
#line 8873 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 97: goto tr439;
	}
	goto tr319;
tr439:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st308;
st308:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof308;
case 308:
#line 8890 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 98: goto tr440;
	}
	goto tr319;
tr440:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st309;
st309:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof309;
case 309:
#line 8907 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 105: goto tr441;
	}
	goto tr319;
tr441:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st310;
st310:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof310;
case 310:
#line 8924 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 116: goto tr442;
	}
	goto tr319;
tr442:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st311;
st311:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof311;
case 311:
#line 8941 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 97: goto tr443;
	}
	goto tr319;
tr443:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st312;
st312:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof312;
case 312:
#line 8958 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 116: goto tr444;
	}
	goto tr319;
tr444:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st313;
st313:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof313;
case 313:
#line 8975 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr445;
		case 32: goto tr445;
		case 34: goto tr321;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr445;
	goto tr319;
tr445:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st314;
st314:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof314;
case 314:
#line 8995 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr445;
		case 32: goto tr445;
		case 34: goto tr321;
		case 92: goto st229;
		case 99: goto tr446;
		case 102: goto tr447;
		case 115: goto tr448;
		case 119: goto tr449;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr445;
	goto tr319;
tr446:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st315;
st315:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof315;
case 315:
#line 9019 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 111: goto tr450;
	}
	goto tr319;
tr450:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st316;
st316:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof316;
case 316:
#line 9036 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 114: goto tr451;
	}
	goto tr319;
tr451:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st317;
st317:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof317;
case 317:
#line 9053 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 110: goto tr452;
	}
	goto tr319;
tr452:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st318;
st318:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof318;
case 318:
#line 9070 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 101: goto tr453;
	}
	goto tr319;
tr453:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st319;
st319:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof319;
case 319:
#line 9087 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 114: goto tr454;
	}
	goto tr319;
tr454:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st320;
st320:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof320;
case 320:
#line 9104 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr455;
		case 32: goto tr455;
		case 34: goto tr321;
		case 59: goto tr456;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr455;
	goto tr319;
tr447:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st321;
st321:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof321;
case 321:
#line 9125 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 108: goto tr457;
	}
	goto tr319;
tr457:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st322;
st322:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof322;
case 322:
#line 9142 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 111: goto tr458;
	}
	goto tr319;
tr458:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st323;
st323:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof323;
case 323:
#line 9159 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 111: goto tr459;
	}
	goto tr319;
tr459:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st324;
st324:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof324;
case 324:
#line 9176 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 114: goto tr460;
	}
	goto tr319;
tr460:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st325;
st325:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof325;
case 325:
#line 9193 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr461;
		case 32: goto tr461;
		case 34: goto tr321;
		case 59: goto tr462;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr461;
	goto tr319;
tr448:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st326;
st326:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof326;
case 326:
#line 9214 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 104: goto tr463;
	}
	goto tr319;
tr463:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st327;
st327:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof327;
case 327:
#line 9231 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 111: goto tr464;
	}
	goto tr319;
tr464:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st328;
st328:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof328;
case 328:
#line 9248 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 114: goto tr465;
	}
	goto tr319;
tr465:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st329;
st329:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof329;
case 329:
#line 9265 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 101: goto tr466;
	}
	goto tr319;
tr466:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st330;
st330:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof330;
case 330:
#line 9282 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 108: goto tr467;
	}
	goto tr319;
tr467:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st331;
st331:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof331;
case 331:
#line 9299 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 105: goto tr468;
	}
	goto tr319;
tr468:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st332;
st332:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof332;
case 332:
#line 9316 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 110: goto tr469;
	}
	goto tr319;
tr469:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st333;
st333:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof333;
case 333:
#line 9333 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 101: goto tr470;
	}
	goto tr319;
tr470:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st334;
st334:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof334;
case 334:
#line 9350 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr471;
		case 32: goto tr471;
		case 34: goto tr321;
		case 59: goto tr472;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr471;
	goto tr319;
tr449:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st335;
st335:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof335;
case 335:
#line 9371 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 97: goto tr473;
	}
	goto tr319;
tr473:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st336;
st336:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof336;
case 336:
#line 9388 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 108: goto tr474;
		case 116: goto tr475;
	}
	goto tr319;
tr474:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st337;
st337:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof337;
case 337:
#line 9406 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 107: goto tr476;
	}
	goto tr319;
tr476:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st338;
st338:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof338;
case 338:
#line 9423 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr477;
		case 32: goto tr477;
		case 34: goto tr321;
		case 59: goto tr478;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr477;
	goto tr319;
tr475:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st339;
st339:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof339;
case 339:
#line 9444 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 101: goto tr479;
	}
	goto tr319;
tr479:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st340;
st340:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof340;
case 340:
#line 9461 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 114: goto tr480;
	}
	goto tr319;
tr480:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st341;
st341:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof341;
case 341:
#line 9478 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr481;
		case 32: goto tr481;
		case 34: goto tr321;
		case 59: goto tr482;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr481;
	goto tr319;
tr341:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st342;
st342:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof342;
case 342:
#line 9499 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 100: goto tr483;
	}
	goto tr319;
tr483:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st343;
st343:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof343;
case 343:
#line 9516 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 108: goto tr484;
	}
	goto tr319;
tr484:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st344;
st344:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof344;
case 344:
#line 9533 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 101: goto tr485;
	}
	goto tr319;
tr485:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st345;
st345:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof345;
case 345:
#line 9550 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 95: goto tr486;
	}
	goto tr319;
tr486:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st346;
st346:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof346;
case 346:
#line 9567 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 97: goto tr487;
	}
	goto tr319;
tr487:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st347;
st347:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof347;
case 347:
#line 9584 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 105: goto tr488;
	}
	goto tr319;
tr488:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st348;
st348:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof348;
case 348:
#line 9601 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr489;
		case 32: goto tr489;
		case 34: goto tr321;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr489;
	goto tr319;
tr489:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st349;
st349:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof349;
case 349:
#line 9621 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr489;
		case 32: goto tr489;
		case 34: goto tr321;
		case 92: goto st229;
		case 110: goto tr490;
		case 114: goto tr491;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr489;
	goto tr319;
tr490:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st350;
st350:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof350;
case 350:
#line 9643 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 111: goto tr492;
	}
	goto tr319;
tr492:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st351;
st351:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof351;
case 351:
#line 9660 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 110: goto tr493;
	}
	goto tr319;
tr493:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st352;
st352:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof352;
case 352:
#line 9677 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 101: goto tr494;
	}
	goto tr319;
tr494:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st353;
st353:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof353;
case 353:
#line 9694 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr495;
		case 32: goto tr495;
		case 34: goto tr321;
		case 59: goto tr496;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr495;
	goto tr319;
tr491:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st354;
st354:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof354;
case 354:
#line 9715 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 97: goto tr497;
	}
	goto tr319;
tr497:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st355;
st355:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof355;
case 355:
#line 9732 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 110: goto tr498;
	}
	goto tr319;
tr498:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st356;
st356:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof356;
case 356:
#line 9749 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 100: goto tr499;
	}
	goto tr319;
tr499:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st357;
st357:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof357;
case 357:
#line 9766 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 111: goto tr500;
	}
	goto tr319;
tr500:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st358;
st358:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof358;
case 358:
#line 9783 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 109: goto tr501;
	}
	goto tr319;
tr501:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st359;
st359:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof359;
case 359:
#line 9800 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr502;
		case 32: goto tr502;
		case 34: goto tr321;
		case 59: goto tr503;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr502;
	goto tr319;
tr342:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st360;
st360:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof360;
case 360:
#line 9821 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 111: goto tr504;
	}
	goto tr319;
tr504:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st361;
st361:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof361;
case 361:
#line 9838 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 118: goto tr505;
	}
	goto tr319;
tr505:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st362;
st362:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof362;
case 362:
#line 9855 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 101: goto tr506;
	}
	goto tr319;
tr506:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st363;
st363:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof363;
case 363:
#line 9872 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr507;
		case 32: goto tr507;
		case 34: goto tr321;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr507;
	goto tr319;
tr507:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st364;
st364:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof364;
case 364:
#line 9892 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr507;
		case 32: goto tr507;
		case 34: goto tr321;
		case 92: goto st229;
		case 97: goto tr508;
		case 102: goto tr509;
		case 119: goto tr510;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr507;
	goto tr319;
tr508:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st365;
st365:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof365;
case 365:
#line 9915 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 110: goto tr511;
	}
	goto tr319;
tr511:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st366;
st366:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof366;
case 366:
#line 9932 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 121: goto tr512;
	}
	goto tr319;
tr512:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st367;
st367:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof367;
case 367:
#line 9949 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr513;
		case 32: goto tr513;
		case 34: goto tr321;
		case 59: goto tr514;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr513;
	goto tr319;
tr509:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st368;
st368:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof368;
case 368:
#line 9970 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 108: goto tr515;
	}
	goto tr319;
tr515:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st369;
st369:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof369;
case 369:
#line 9987 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 111: goto tr516;
	}
	goto tr319;
tr516:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st370;
st370:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof370;
case 370:
#line 10004 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 111: goto tr517;
	}
	goto tr319;
tr517:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st371;
st371:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof371;
case 371:
#line 10021 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 114: goto tr518;
	}
	goto tr319;
tr518:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st372;
st372:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof372;
case 372:
#line 10038 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr519;
		case 32: goto tr519;
		case 34: goto tr321;
		case 59: goto tr520;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr519;
	goto tr319;
tr510:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st373;
st373:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof373;
case 373:
#line 10059 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 97: goto tr521;
	}
	goto tr319;
tr521:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st374;
st374:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof374;
case 374:
#line 10076 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 116: goto tr522;
	}
	goto tr319;
tr522:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st375;
st375:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof375;
case 375:
#line 10093 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 101: goto tr523;
	}
	goto tr319;
tr523:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st376;
st376:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof376;
case 376:
#line 10110 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 114: goto tr524;
	}
	goto tr319;
tr524:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st377;
st377:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof377;
case 377:
#line 10127 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr525;
		case 32: goto tr525;
		case 34: goto tr321;
		case 59: goto tr526;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr525;
	goto tr319;
tr343:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st378;
st378:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof378;
case 378:
#line 10148 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 97: goto tr527;
	}
	goto tr319;
tr527:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st379;
st379:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof379;
case 379:
#line 10165 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 109: goto tr528;
	}
	goto tr319;
tr528:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st380;
st380:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof380;
case 380:
#line 10182 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 101: goto tr529;
	}
	goto tr319;
tr529:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st381;
st381:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof381;
case 381:
#line 10199 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr530;
		case 32: goto tr530;
		case 34: goto tr321;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr530;
	goto tr319;
tr530:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st382;
st382:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof382;
case 382:
#line 10219 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr530;
		case 32: goto tr530;
		case 34: goto tr531;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr530;
	goto tr319;
tr531:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st383;
st383:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof383;
case 383:
#line 10239 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr532;
		case 32: goto tr532;
		case 34: goto tr321;
		case 59: goto tr533;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr532;
	goto tr319;
tr344:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st384;
st384:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof384;
case 384:
#line 10260 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 97: goto tr534;
	}
	goto tr319;
tr534:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st385;
st385:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof385;
case 385:
#line 10277 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 110: goto tr535;
	}
	goto tr319;
tr535:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st386;
st386:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof386;
case 386:
#line 10294 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 103: goto tr536;
	}
	goto tr319;
tr536:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st387;
st387:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof387;
case 387:
#line 10311 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 101: goto tr537;
	}
	goto tr319;
tr537:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st388;
st388:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof388;
case 388:
#line 10328 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr538;
		case 32: goto tr538;
		case 34: goto tr321;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr538;
	goto tr319;
tr538:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st389;
st389:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof389;
case 389:
#line 10348 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr538;
		case 32: goto tr538;
		case 34: goto tr321;
		case 92: goto st229;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr539;
	} else if ( (*( state.p)) >= 9 )
		goto tr538;
	goto tr319;
tr541:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st390;
tr539:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st390;
st390:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof390;
case 390:
#line 10381 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr540;
		case 32: goto tr540;
		case 34: goto tr321;
		case 59: goto tr542;
		case 92: goto st229;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr541;
	} else if ( (*( state.p)) >= 9 )
		goto tr540;
	goto tr319;
tr345:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st391;
st391:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof391;
case 391:
#line 10405 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 107: goto tr543;
	}
	goto tr319;
tr543:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st392;
st392:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof392;
case 392:
#line 10422 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 105: goto tr544;
	}
	goto tr319;
tr544:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st393;
st393:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof393;
case 393:
#line 10439 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 110: goto tr545;
	}
	goto tr319;
tr545:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st394;
st394:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof394;
case 394:
#line 10456 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr546;
		case 32: goto tr546;
		case 34: goto tr321;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr546;
	goto tr319;
tr546:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st395;
st395:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof395;
case 395:
#line 10476 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr546;
		case 32: goto tr546;
		case 34: goto tr547;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr546;
	goto tr319;
tr547:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st396;
st396:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof396;
case 396:
#line 10496 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr549;
		case 32: goto tr549;
		case 34: goto tr550;
		case 59: goto tr551;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr549;
	goto tr548;
tr548:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st397;
tr639:
#line 138 "configparser.rl"
	{ state.match += '\\'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st397;
tr643:
#line 136 "configparser.rl"
	{ state.match += '"'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st397;
tr1117:
#line 137 "configparser.rl"
	{ state.match += '\n'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st397;
st397:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof397;
case 397:
#line 10541 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
	}
	goto tr548;
tr550:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st398;
tr645:
#line 136 "configparser.rl"
	{ state.match += '"'; }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st398;
tr1118:
#line 137 "configparser.rl"
	{ state.match += '\n'; }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st398;
st398:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof398;
case 398:
#line 10573 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr553;
		case 32: goto tr553;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr553;
	goto st0;
tr553:
#line 161 "configparser.rl"
	{ skin.text = state.match; }
	goto st399;
st399:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof399;
case 399:
#line 10589 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st399;
		case 32: goto st399;
		case 98: goto st400;
		case 100: goto st445;
		case 110: goto st448;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st399;
	goto st0;
st400:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof400;
case 400:
	if ( (*( state.p)) == 114 )
		goto st401;
	goto st0;
st401:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof401;
case 401:
	if ( (*( state.p)) == 105 )
		goto st402;
	goto st0;
st402:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof402;
case 402:
	if ( (*( state.p)) == 103 )
		goto st403;
	goto st0;
st403:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof403;
case 403:
	if ( (*( state.p)) == 104 )
		goto st404;
	goto st0;
st404:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof404;
case 404:
	if ( (*( state.p)) == 116 )
		goto st405;
	goto st0;
st405:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof405;
case 405:
	switch( (*( state.p)) ) {
		case 13: goto tr563;
		case 32: goto tr563;
		case 95: goto tr564;
		case 98: goto tr565;
		case 99: goto tr566;
		case 103: goto tr567;
		case 109: goto tr568;
		case 114: goto tr569;
		case 119: goto tr570;
		case 121: goto tr571;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr563;
	goto st0;
tr563:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st406;
tr628:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st406;
st406:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof406;
case 406:
#line 10666 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st406;
		case 32: goto st406;
		case 98: goto st407;
		case 99: goto st414;
		case 103: goto st418;
		case 109: goto st423;
		case 114: goto st430;
		case 119: goto st433;
		case 121: goto st438;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st406;
	goto st0;
tr565:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st407;
tr630:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st407;
st407:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof407;
case 407:
#line 10693 "configparser.h"
	if ( (*( state.p)) == 108 )
		goto st408;
	goto st0;
st408:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof408;
case 408:
	switch( (*( state.p)) ) {
		case 97: goto st409;
		case 117: goto st412;
	}
	goto st0;
st409:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof409;
case 409:
	if ( (*( state.p)) == 99 )
		goto st410;
	goto st0;
st410:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof410;
case 410:
	if ( (*( state.p)) == 107 )
		goto st411;
	goto st0;
st411:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof411;
case 411:
	switch( (*( state.p)) ) {
		case 13: goto tr585;
		case 32: goto tr585;
		case 59: goto tr586;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr585;
	goto st0;
st412:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof412;
case 412:
	if ( (*( state.p)) == 101 )
		goto st413;
	goto st0;
st413:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof413;
case 413:
	switch( (*( state.p)) ) {
		case 13: goto tr588;
		case 32: goto tr588;
		case 59: goto tr589;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr588;
	goto st0;
tr566:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st414;
tr631:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st414;
st414:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof414;
case 414:
#line 10763 "configparser.h"
	if ( (*( state.p)) == 121 )
		goto st415;
	goto st0;
st415:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof415;
case 415:
	if ( (*( state.p)) == 97 )
		goto st416;
	goto st0;
st416:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof416;
case 416:
	if ( (*( state.p)) == 110 )
		goto st417;
	goto st0;
st417:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof417;
case 417:
	switch( (*( state.p)) ) {
		case 13: goto tr593;
		case 32: goto tr593;
		case 59: goto tr594;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr593;
	goto st0;
tr567:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st418;
tr632:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st418;
st418:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof418;
case 418:
#line 10805 "configparser.h"
	if ( (*( state.p)) == 114 )
		goto st419;
	goto st0;
st419:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof419;
case 419:
	if ( (*( state.p)) == 101 )
		goto st420;
	goto st0;
st420:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof420;
case 420:
	if ( (*( state.p)) == 101 )
		goto st421;
	goto st0;
st421:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof421;
case 421:
	if ( (*( state.p)) == 110 )
		goto st422;
	goto st0;
st422:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof422;
case 422:
	switch( (*( state.p)) ) {
		case 13: goto tr599;
		case 32: goto tr599;
		case 59: goto tr600;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr599;
	goto st0;
tr568:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st423;
tr633:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st423;
st423:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof423;
case 423:
#line 10854 "configparser.h"
	if ( (*( state.p)) == 97 )
		goto st424;
	goto st0;
st424:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof424;
case 424:
	if ( (*( state.p)) == 103 )
		goto st425;
	goto st0;
st425:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof425;
case 425:
	if ( (*( state.p)) == 101 )
		goto st426;
	goto st0;
st426:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof426;
case 426:
	if ( (*( state.p)) == 110 )
		goto st427;
	goto st0;
st427:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof427;
case 427:
	if ( (*( state.p)) == 116 )
		goto st428;
	goto st0;
st428:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof428;
case 428:
	if ( (*( state.p)) == 97 )
		goto st429;
	goto st0;
st429:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof429;
case 429:
	switch( (*( state.p)) ) {
		case 13: goto tr607;
		case 32: goto tr607;
		case 59: goto tr608;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr607;
	goto st0;
tr569:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st430;
tr634:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st430;
st430:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof430;
case 430:
#line 10917 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st431;
	goto st0;
st431:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof431;
case 431:
	if ( (*( state.p)) == 100 )
		goto st432;
	goto st0;
st432:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof432;
case 432:
	switch( (*( state.p)) ) {
		case 13: goto tr611;
		case 32: goto tr611;
		case 59: goto tr612;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr611;
	goto st0;
tr570:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st433;
tr635:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st433;
st433:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof433;
case 433:
#line 10952 "configparser.h"
	if ( (*( state.p)) == 104 )
		goto st434;
	goto st0;
st434:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof434;
case 434:
	if ( (*( state.p)) == 105 )
		goto st435;
	goto st0;
st435:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof435;
case 435:
	if ( (*( state.p)) == 116 )
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
		case 13: goto tr617;
		case 32: goto tr617;
		case 59: goto tr618;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr617;
	goto st0;
tr571:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st438;
tr636:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st438;
st438:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof438;
case 438:
#line 11001 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st439;
	goto st0;
st439:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof439;
case 439:
	if ( (*( state.p)) == 108 )
		goto st440;
	goto st0;
st440:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof440;
case 440:
	if ( (*( state.p)) == 108 )
		goto st441;
	goto st0;
st441:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof441;
case 441:
	if ( (*( state.p)) == 111 )
		goto st442;
	goto st0;
st442:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof442;
case 442:
	if ( (*( state.p)) == 119 )
		goto st443;
	goto st0;
st443:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof443;
case 443:
	switch( (*( state.p)) ) {
		case 13: goto tr624;
		case 32: goto tr624;
		case 59: goto tr625;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr624;
	goto st0;
tr564:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st444;
tr629:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st444;
st444:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof444;
case 444:
#line 11057 "configparser.h"
	switch( (*( state.p)) ) {
		case 98: goto st407;
		case 99: goto st414;
		case 103: goto st418;
		case 109: goto st423;
		case 114: goto st430;
		case 119: goto st433;
		case 121: goto st438;
	}
	goto st0;
st445:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof445;
case 445:
	if ( (*( state.p)) == 105 )
		goto st446;
	goto st0;
st446:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof446;
case 446:
	if ( (*( state.p)) == 109 )
		goto st447;
	goto st0;
st447:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof447;
case 447:
	switch( (*( state.p)) ) {
		case 13: goto tr628;
		case 32: goto tr628;
		case 95: goto tr629;
		case 98: goto tr630;
		case 99: goto tr631;
		case 103: goto tr632;
		case 109: goto tr633;
		case 114: goto tr634;
		case 119: goto tr635;
		case 121: goto tr636;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr628;
	goto st0;
st448:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof448;
case 448:
	if ( (*( state.p)) == 111 )
		goto st449;
	goto st0;
st449:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof449;
case 449:
	if ( (*( state.p)) == 110 )
		goto st450;
	goto st0;
st450:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof450;
case 450:
	if ( (*( state.p)) == 101 )
		goto st411;
	goto st0;
tr641:
#line 138 "configparser.rl"
	{ state.match += '\\'; }
	goto st451;
tr646:
#line 136 "configparser.rl"
	{ state.match += '"'; }
	goto st451;
tr1119:
#line 137 "configparser.rl"
	{ state.match += '\n'; }
	goto st451;
st451:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof451;
case 451:
#line 11138 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr640;
		case 92: goto tr641;
		case 110: goto tr642;
	}
	goto tr639;
tr640:
#line 138 "configparser.rl"
	{ state.match += '\\'; }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st452;
st452:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof452;
case 452:
#line 11157 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr644;
		case 32: goto tr644;
		case 34: goto tr645;
		case 92: goto tr646;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr644;
	goto tr643;
tr647:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st453;
tr644:
#line 136 "configparser.rl"
	{ state.match += '"'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 161 "configparser.rl"
	{ skin.text = state.match; }
	goto st453;
tr1062:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 161 "configparser.rl"
	{ skin.text = state.match; }
	goto st453;
st453:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof453;
case 453:
#line 11195 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr647;
		case 32: goto tr647;
		case 34: goto tr550;
		case 92: goto st451;
		case 98: goto tr648;
		case 100: goto tr649;
		case 110: goto tr650;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr647;
	goto tr548;
tr648:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st454;
st454:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof454;
case 454:
#line 11218 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 114: goto tr651;
	}
	goto tr548;
tr651:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st455;
st455:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof455;
case 455:
#line 11235 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 105: goto tr652;
	}
	goto tr548;
tr652:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st456;
st456:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof456;
case 456:
#line 11252 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 103: goto tr653;
	}
	goto tr548;
tr653:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st457;
st457:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof457;
case 457:
#line 11269 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 104: goto tr654;
	}
	goto tr548;
tr654:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st458;
st458:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof458;
case 458:
#line 11286 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 116: goto tr655;
	}
	goto tr548;
tr655:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st459;
st459:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof459;
case 459:
#line 11303 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr656;
		case 32: goto tr656;
		case 34: goto tr550;
		case 92: goto st451;
		case 95: goto tr657;
		case 98: goto tr658;
		case 99: goto tr659;
		case 103: goto tr660;
		case 109: goto tr661;
		case 114: goto tr662;
		case 119: goto tr663;
		case 121: goto tr664;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr656;
	goto tr548;
tr665:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st460;
tr656:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st460;
tr1106:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st460;
st460:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof460;
case 460:
#line 11347 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr665;
		case 32: goto tr665;
		case 34: goto tr550;
		case 92: goto st451;
		case 98: goto tr666;
		case 99: goto tr667;
		case 103: goto tr668;
		case 109: goto tr669;
		case 114: goto tr670;
		case 119: goto tr671;
		case 121: goto tr672;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr665;
	goto tr548;
tr666:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st461;
tr658:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st461;
tr1108:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st461;
st461:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof461;
case 461:
#line 11390 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 108: goto tr673;
	}
	goto tr548;
tr673:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st462;
st462:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof462;
case 462:
#line 11407 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 97: goto tr674;
		case 117: goto tr675;
	}
	goto tr548;
tr674:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st463;
st463:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof463;
case 463:
#line 11425 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 99: goto tr676;
	}
	goto tr548;
tr676:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st464;
st464:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof464;
case 464:
#line 11442 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 107: goto tr677;
	}
	goto tr548;
tr677:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st465;
st465:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof465;
case 465:
#line 11459 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr678;
		case 32: goto tr678;
		case 34: goto tr550;
		case 59: goto tr679;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr678;
	goto tr548;
tr680:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st466;
tr1152:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 203 "configparser.rl"
	{ spe.companion.back().chance = ::atof(state.match.c_str()); }
	goto st466;
tr723:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 193 "configparser.rl"
	{ spe.attack = ::atof(state.match.c_str()); }
	goto st466;
tr852:
#line 185 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st466;
tr865:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 194 "configparser.rl"
	{ spe.defense = ::atof(state.match.c_str()); }
	goto st466;
tr701:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 173 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st466;
tr713:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 174 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st466;
tr746:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 198 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
	goto st466;
tr549:
#line 186 "configparser.rl"
	{ spe.name = state.match; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st466;
tr885:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 169 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st466;
tr891:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 167 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st466;
tr901:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 170 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st466;
tr907:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 166 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st466;
tr911:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 168 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st466;
tr925:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 177 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st466;
tr932:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 178 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st466;
tr943:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 181 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st466;
tr949:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 182 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st466;
tr955:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 183 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st466;
tr1054:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 192 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
	goto st466;
tr678:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st466;
tr1066:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 151 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st466;
tr1071:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 153 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st466;
tr1077:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 149 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st466;
tr1085:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 152 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st466;
tr1089:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 148 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st466;
tr1095:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 154 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st466;
tr1102:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 150 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st466;
tr1063:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 211 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st466;
st466:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof466;
case 466:
#line 11718 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr680;
		case 32: goto tr680;
		case 34: goto tr550;
		case 59: goto tr681;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr680;
	goto tr548;
tr681:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1490;
tr1154:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 203 "configparser.rl"
	{ spe.companion.back().chance = ::atof(state.match.c_str()); }
	goto st1490;
tr725:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 193 "configparser.rl"
	{ spe.attack = ::atof(state.match.c_str()); }
	goto st1490;
tr854:
#line 185 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1490;
tr867:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 194 "configparser.rl"
	{ spe.defense = ::atof(state.match.c_str()); }
	goto st1490;
tr702:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 173 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st1490;
tr714:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 174 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st1490;
tr748:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 198 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
	goto st1490;
tr551:
#line 186 "configparser.rl"
	{ spe.name = state.match; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1490;
tr886:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 169 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st1490;
tr892:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 167 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st1490;
tr902:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 170 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st1490;
tr908:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 166 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st1490;
tr912:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 168 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st1490;
tr926:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 177 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st1490;
tr933:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 178 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st1490;
tr944:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 181 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st1490;
tr950:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 182 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st1490;
tr956:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 183 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st1490;
tr1056:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 192 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
	goto st1490;
tr679:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st1490;
tr1067:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 151 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st1490;
tr1072:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 153 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st1490;
tr1078:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 149 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st1490;
tr1086:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 152 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st1490;
tr1090:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 148 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st1490;
tr1096:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 154 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st1490;
tr1103:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 150 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 187 "configparser.rl"
	{ spe.skin = skin; }
	goto st1490;
tr1064:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 211 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st1490;
st1490:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1490;
case 1490:
#line 11977 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr682;
		case 32: goto tr682;
		case 34: goto tr550;
		case 92: goto st451;
		case 97: goto tr683;
		case 99: goto tr684;
		case 100: goto tr685;
		case 104: goto tr686;
		case 105: goto tr687;
		case 109: goto tr688;
		case 110: goto tr689;
		case 114: goto tr690;
		case 115: goto tr691;
		case 125: goto tr692;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr682;
	goto tr548;
tr682:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st467;
st467:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof467;
case 467:
#line 12007 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr682;
		case 32: goto tr682;
		case 34: goto tr550;
		case 92: goto st451;
		case 97: goto tr683;
		case 99: goto tr684;
		case 100: goto tr685;
		case 104: goto tr686;
		case 105: goto tr687;
		case 109: goto tr688;
		case 110: goto tr689;
		case 114: goto tr690;
		case 115: goto tr691;
		case 125: goto tr692;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr682;
	goto tr548;
tr683:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st468;
st468:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof468;
case 468:
#line 12037 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 105: goto tr693;
		case 116: goto tr694;
	}
	goto tr548;
tr693:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st469;
st469:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof469;
case 469:
#line 12055 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr695;
		case 32: goto tr695;
		case 34: goto tr550;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr695;
	goto tr548;
tr695:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st470;
st470:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof470;
case 470:
#line 12075 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr695;
		case 32: goto tr695;
		case 34: goto tr550;
		case 92: goto st451;
		case 110: goto tr696;
		case 115: goto tr697;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr695;
	goto tr548;
tr696:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st471;
st471:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof471;
case 471:
#line 12097 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 111: goto tr698;
	}
	goto tr548;
tr698:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st472;
st472:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof472;
case 472:
#line 12114 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 110: goto tr699;
	}
	goto tr548;
tr699:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st473;
st473:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof473;
case 473:
#line 12131 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 101: goto tr700;
	}
	goto tr548;
tr700:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st474;
st474:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof474;
case 474:
#line 12148 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr701;
		case 32: goto tr701;
		case 34: goto tr550;
		case 59: goto tr702;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr701;
	goto tr548;
tr697:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st475;
st475:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof475;
case 475:
#line 12169 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 101: goto tr703;
	}
	goto tr548;
tr703:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st476;
st476:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof476;
case 476:
#line 12186 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 101: goto tr704;
	}
	goto tr548;
tr704:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st477;
st477:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof477;
case 477:
#line 12203 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 107: goto tr705;
	}
	goto tr548;
tr705:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st478;
st478:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof478;
case 478:
#line 12220 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 95: goto tr706;
	}
	goto tr548;
tr706:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st479;
st479:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof479;
case 479:
#line 12237 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 112: goto tr707;
	}
	goto tr548;
tr707:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st480;
st480:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof480;
case 480:
#line 12254 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 108: goto tr708;
	}
	goto tr548;
tr708:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st481;
st481:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof481;
case 481:
#line 12271 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 97: goto tr709;
	}
	goto tr548;
tr709:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st482;
st482:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof482;
case 482:
#line 12288 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 121: goto tr710;
	}
	goto tr548;
tr710:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st483;
st483:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof483;
case 483:
#line 12305 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 101: goto tr711;
	}
	goto tr548;
tr711:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st484;
st484:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof484;
case 484:
#line 12322 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 114: goto tr712;
	}
	goto tr548;
tr712:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st485;
st485:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof485;
case 485:
#line 12339 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr713;
		case 32: goto tr713;
		case 34: goto tr550;
		case 59: goto tr714;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr713;
	goto tr548;
tr694:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st486;
st486:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof486;
case 486:
#line 12360 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 116: goto tr715;
	}
	goto tr548;
tr715:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st487;
st487:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof487;
case 487:
#line 12377 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 97: goto tr716;
	}
	goto tr548;
tr716:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st488;
st488:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof488;
case 488:
#line 12394 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 99: goto tr717;
	}
	goto tr548;
tr717:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st489;
st489:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof489;
case 489:
#line 12411 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 107: goto tr718;
	}
	goto tr548;
tr718:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st490;
st490:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof490;
case 490:
#line 12428 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr719;
		case 32: goto tr719;
		case 34: goto tr550;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr719;
	goto tr548;
tr719:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st491;
st491:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof491;
case 491:
#line 12448 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr719;
		case 32: goto tr719;
		case 34: goto tr550;
		case 45: goto tr720;
		case 92: goto st451;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr721;
	} else if ( (*( state.p)) >= 9 )
		goto tr719;
	goto tr548;
tr720:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st492;
st492:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof492;
case 492:
#line 12476 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr722;
	goto tr548;
tr722:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st493;
tr721:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st493;
st493:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof493;
case 493:
#line 12504 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr723;
		case 32: goto tr723;
		case 34: goto tr550;
		case 46: goto tr724;
		case 59: goto tr725;
		case 92: goto st451;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr722;
	} else if ( (*( state.p)) >= 9 )
		goto tr723;
	goto tr548;
tr724:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st494;
st494:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof494;
case 494:
#line 12529 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr726;
	goto tr548;
tr726:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st495;
st495:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof495;
case 495:
#line 12547 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr723;
		case 32: goto tr723;
		case 34: goto tr550;
		case 59: goto tr725;
		case 92: goto st451;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr726;
	} else if ( (*( state.p)) >= 9 )
		goto tr723;
	goto tr548;
tr684:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st496;
st496:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof496;
case 496:
#line 12571 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 108: goto tr727;
		case 111: goto tr728;
	}
	goto tr548;
tr727:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st497;
st497:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof497;
case 497:
#line 12589 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 117: goto tr729;
	}
	goto tr548;
tr729:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st498;
st498:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof498;
case 498:
#line 12606 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 109: goto tr730;
	}
	goto tr548;
tr730:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st499;
st499:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof499;
case 499:
#line 12623 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 112: goto tr731;
	}
	goto tr548;
tr731:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st500;
st500:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof500;
case 500:
#line 12640 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 115: goto tr732;
	}
	goto tr548;
tr732:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st501;
st501:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof501;
case 501:
#line 12657 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 105: goto tr733;
	}
	goto tr548;
tr733:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st502;
st502:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof502;
case 502:
#line 12674 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 122: goto tr734;
	}
	goto tr548;
tr734:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st503;
st503:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof503;
case 503:
#line 12691 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 101: goto tr735;
	}
	goto tr548;
tr735:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st504;
st504:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof504;
case 504:
#line 12708 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr736;
		case 32: goto tr736;
		case 34: goto tr550;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr736;
	goto tr548;
tr736:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st505;
st505:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof505;
case 505:
#line 12728 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr736;
		case 32: goto tr736;
		case 34: goto tr550;
		case 45: goto tr737;
		case 92: goto st451;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr738;
	} else if ( (*( state.p)) >= 9 )
		goto tr736;
	goto tr548;
tr737:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st506;
st506:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof506;
case 506:
#line 12756 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr739;
	goto tr548;
tr739:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st507;
tr738:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st507;
st507:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof507;
case 507:
#line 12784 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr740;
		case 32: goto tr740;
		case 34: goto tr550;
		case 46: goto tr741;
		case 92: goto st451;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr739;
	} else if ( (*( state.p)) >= 9 )
		goto tr740;
	goto tr548;
tr742:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st508;
tr740:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 197 "configparser.rl"
	{ spe.clumpsize.mean = ::atof(state.match.c_str()); }
	goto st508;
st508:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof508;
case 508:
#line 12816 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr742;
		case 32: goto tr742;
		case 34: goto tr550;
		case 45: goto tr743;
		case 92: goto st451;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr744;
	} else if ( (*( state.p)) >= 9 )
		goto tr742;
	goto tr548;
tr743:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st509;
st509:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof509;
case 509:
#line 12844 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr745;
	goto tr548;
tr745:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st510;
tr744:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st510;
st510:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof510;
case 510:
#line 12872 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr746;
		case 32: goto tr746;
		case 34: goto tr550;
		case 46: goto tr747;
		case 59: goto tr748;
		case 92: goto st451;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr745;
	} else if ( (*( state.p)) >= 9 )
		goto tr746;
	goto tr548;
tr747:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st511;
st511:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof511;
case 511:
#line 12897 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr749;
	goto tr548;
tr749:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st512;
st512:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof512;
case 512:
#line 12915 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr746;
		case 32: goto tr746;
		case 34: goto tr550;
		case 59: goto tr748;
		case 92: goto st451;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr749;
	} else if ( (*( state.p)) >= 9 )
		goto tr746;
	goto tr548;
tr741:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st513;
st513:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof513;
case 513:
#line 12939 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr750;
	goto tr548;
tr750:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st514;
st514:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof514;
case 514:
#line 12957 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr740;
		case 32: goto tr740;
		case 34: goto tr550;
		case 92: goto st451;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr750;
	} else if ( (*( state.p)) >= 9 )
		goto tr740;
	goto tr548;
tr728:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st515;
st515:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof515;
case 515:
#line 12980 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 109: goto tr751;
		case 117: goto tr752;
	}
	goto tr548;
tr751:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st516;
st516:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof516;
case 516:
#line 12998 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 112: goto tr753;
	}
	goto tr548;
tr753:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st517;
st517:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof517;
case 517:
#line 13015 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 97: goto tr754;
	}
	goto tr548;
tr754:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st518;
st518:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof518;
case 518:
#line 13032 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 110: goto tr755;
	}
	goto tr548;
tr755:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st519;
st519:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof519;
case 519:
#line 13049 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 105: goto tr756;
	}
	goto tr548;
tr756:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st520;
st520:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof520;
case 520:
#line 13066 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 111: goto tr757;
	}
	goto tr548;
tr757:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st521;
st521:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof521;
case 521:
#line 13083 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 110: goto tr758;
	}
	goto tr548;
tr758:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st522;
st522:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof522;
case 522:
#line 13100 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr759;
		case 32: goto tr759;
		case 34: goto tr550;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr759;
	goto tr548;
tr760:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st523;
tr759:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 201 "configparser.rl"
	{ spe.companion.push_back(Species::companion_t()); }
	goto st523;
st523:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof523;
case 523:
#line 13128 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr760;
		case 32: goto tr760;
		case 34: goto tr761;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr760;
	goto tr548;
tr761:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st524;
st524:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof524;
case 524:
#line 13148 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr762;
		case 32: goto tr762;
		case 34: goto tr96;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr762;
	goto tr95;
tr763:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st525;
tr762:
#line 161 "configparser.rl"
	{ skin.text = state.match; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st525;
st525:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof525;
case 525:
#line 13176 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr763;
		case 32: goto tr763;
		case 34: goto tr96;
		case 92: goto st69;
		case 98: goto tr764;
		case 100: goto tr765;
		case 110: goto tr766;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr763;
	goto tr95;
tr764:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st526;
st526:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof526;
case 526:
#line 13199 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 114: goto tr767;
	}
	goto tr95;
tr767:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st527;
st527:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof527;
case 527:
#line 13216 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 105: goto tr768;
	}
	goto tr95;
tr768:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st528;
st528:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof528;
case 528:
#line 13233 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 103: goto tr769;
	}
	goto tr95;
tr769:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st529;
st529:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof529;
case 529:
#line 13250 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 104: goto tr770;
	}
	goto tr95;
tr770:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st530;
st530:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof530;
case 530:
#line 13267 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 116: goto tr771;
	}
	goto tr95;
tr771:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st531;
st531:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof531;
case 531:
#line 13284 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr772;
		case 32: goto tr772;
		case 34: goto tr96;
		case 92: goto st69;
		case 95: goto tr773;
		case 98: goto tr774;
		case 99: goto tr775;
		case 103: goto tr776;
		case 109: goto tr777;
		case 114: goto tr778;
		case 119: goto tr779;
		case 121: goto tr780;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr772;
	goto tr95;
tr781:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st532;
tr772:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st532;
tr837:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st532;
st532:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof532;
case 532:
#line 13328 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr781;
		case 32: goto tr781;
		case 34: goto tr96;
		case 92: goto st69;
		case 98: goto tr782;
		case 99: goto tr783;
		case 103: goto tr784;
		case 109: goto tr785;
		case 114: goto tr786;
		case 119: goto tr787;
		case 121: goto tr788;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr781;
	goto tr95;
tr782:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st533;
tr774:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st533;
tr839:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st533;
st533:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof533;
case 533:
#line 13371 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 108: goto tr789;
	}
	goto tr95;
tr789:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st534;
st534:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof534;
case 534:
#line 13388 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 97: goto tr790;
		case 117: goto tr791;
	}
	goto tr95;
tr790:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st535;
st535:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof535;
case 535:
#line 13406 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 99: goto tr792;
	}
	goto tr95;
tr792:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st536;
st536:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof536;
case 536:
#line 13423 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 107: goto tr793;
	}
	goto tr95;
tr793:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st537;
st537:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof537;
case 537:
#line 13440 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr794;
		case 32: goto tr794;
		case 34: goto tr96;
		case 59: goto tr795;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr794;
	goto tr95;
tr791:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st538;
st538:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof538;
case 538:
#line 13461 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 101: goto tr796;
	}
	goto tr95;
tr796:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st539;
st539:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof539;
case 539:
#line 13478 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr797;
		case 32: goto tr797;
		case 34: goto tr96;
		case 59: goto tr798;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr797;
	goto tr95;
tr783:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st540;
tr775:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st540;
tr840:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st540;
st540:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof540;
case 540:
#line 13515 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 121: goto tr799;
	}
	goto tr95;
tr799:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st541;
st541:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof541;
case 541:
#line 13532 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 97: goto tr800;
	}
	goto tr95;
tr800:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st542;
st542:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof542;
case 542:
#line 13549 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 110: goto tr801;
	}
	goto tr95;
tr801:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st543;
st543:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof543;
case 543:
#line 13566 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr802;
		case 32: goto tr802;
		case 34: goto tr96;
		case 59: goto tr803;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr802;
	goto tr95;
tr784:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st544;
tr776:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st544;
tr841:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st544;
st544:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof544;
case 544:
#line 13603 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 114: goto tr804;
	}
	goto tr95;
tr804:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st545;
st545:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof545;
case 545:
#line 13620 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 101: goto tr805;
	}
	goto tr95;
tr805:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st546;
st546:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof546;
case 546:
#line 13637 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 101: goto tr806;
	}
	goto tr95;
tr806:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st547;
st547:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof547;
case 547:
#line 13654 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 110: goto tr807;
	}
	goto tr95;
tr807:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st548;
st548:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof548;
case 548:
#line 13671 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr808;
		case 32: goto tr808;
		case 34: goto tr96;
		case 59: goto tr809;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr808;
	goto tr95;
tr785:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st549;
tr777:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st549;
tr842:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st549;
st549:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof549;
case 549:
#line 13708 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 97: goto tr810;
	}
	goto tr95;
tr810:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st550;
st550:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof550;
case 550:
#line 13725 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 103: goto tr811;
	}
	goto tr95;
tr811:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st551;
st551:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof551;
case 551:
#line 13742 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 101: goto tr812;
	}
	goto tr95;
tr812:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st552;
st552:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof552;
case 552:
#line 13759 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 110: goto tr813;
	}
	goto tr95;
tr813:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st553;
st553:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof553;
case 553:
#line 13776 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 116: goto tr814;
	}
	goto tr95;
tr814:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st554;
st554:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof554;
case 554:
#line 13793 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 97: goto tr815;
	}
	goto tr95;
tr815:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st555;
st555:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof555;
case 555:
#line 13810 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr816;
		case 32: goto tr816;
		case 34: goto tr96;
		case 59: goto tr817;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr816;
	goto tr95;
tr786:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st556;
tr778:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st556;
tr843:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st556;
st556:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof556;
case 556:
#line 13847 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 101: goto tr818;
	}
	goto tr95;
tr818:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st557;
st557:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof557;
case 557:
#line 13864 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 100: goto tr819;
	}
	goto tr95;
tr819:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st558;
st558:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof558;
case 558:
#line 13881 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr820;
		case 32: goto tr820;
		case 34: goto tr96;
		case 59: goto tr821;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr820;
	goto tr95;
tr787:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st559;
tr779:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st559;
tr844:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st559;
st559:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof559;
case 559:
#line 13918 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 104: goto tr822;
	}
	goto tr95;
tr822:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st560;
st560:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof560;
case 560:
#line 13935 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 105: goto tr823;
	}
	goto tr95;
tr823:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st561;
st561:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof561;
case 561:
#line 13952 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 116: goto tr824;
	}
	goto tr95;
tr824:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st562;
st562:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof562;
case 562:
#line 13969 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 101: goto tr825;
	}
	goto tr95;
tr825:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st563;
st563:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof563;
case 563:
#line 13986 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr826;
		case 32: goto tr826;
		case 34: goto tr96;
		case 59: goto tr827;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr826;
	goto tr95;
tr788:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st564;
tr780:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st564;
tr845:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st564;
st564:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof564;
case 564:
#line 14023 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 101: goto tr828;
	}
	goto tr95;
tr828:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st565;
st565:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof565;
case 565:
#line 14040 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 108: goto tr829;
	}
	goto tr95;
tr829:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st566;
st566:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof566;
case 566:
#line 14057 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 108: goto tr830;
	}
	goto tr95;
tr830:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st567;
st567:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof567;
case 567:
#line 14074 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 111: goto tr831;
	}
	goto tr95;
tr831:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st568;
st568:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof568;
case 568:
#line 14091 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 119: goto tr832;
	}
	goto tr95;
tr832:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st569;
st569:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof569;
case 569:
#line 14108 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr833;
		case 32: goto tr833;
		case 34: goto tr96;
		case 59: goto tr834;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr833;
	goto tr95;
tr773:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st570;
tr838:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st570;
st570:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof570;
case 570:
#line 14139 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 98: goto tr782;
		case 99: goto tr783;
		case 103: goto tr784;
		case 109: goto tr785;
		case 114: goto tr786;
		case 119: goto tr787;
		case 121: goto tr788;
	}
	goto tr95;
tr765:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st571;
st571:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof571;
case 571:
#line 14162 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 105: goto tr835;
	}
	goto tr95;
tr835:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st572;
st572:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof572;
case 572:
#line 14179 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 109: goto tr836;
	}
	goto tr95;
tr836:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st573;
st573:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof573;
case 573:
#line 14196 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr837;
		case 32: goto tr837;
		case 34: goto tr96;
		case 92: goto st69;
		case 95: goto tr838;
		case 98: goto tr839;
		case 99: goto tr840;
		case 103: goto tr841;
		case 109: goto tr842;
		case 114: goto tr843;
		case 119: goto tr844;
		case 121: goto tr845;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr837;
	goto tr95;
tr766:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st574;
st574:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof574;
case 574:
#line 14224 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 111: goto tr846;
	}
	goto tr95;
tr846:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st575;
st575:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof575;
case 575:
#line 14241 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 110: goto tr847;
	}
	goto tr95;
tr847:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st576;
st576:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof576;
case 576:
#line 14258 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 101: goto tr793;
	}
	goto tr95;
tr752:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st577;
st577:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof577;
case 577:
#line 14275 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 110: goto tr848;
	}
	goto tr548;
tr848:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st578;
st578:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof578;
case 578:
#line 14292 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 116: goto tr849;
	}
	goto tr548;
tr849:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st579;
st579:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof579;
case 579:
#line 14309 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr850;
		case 32: goto tr850;
		case 34: goto tr550;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr850;
	goto tr548;
tr850:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st580;
st580:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof580;
case 580:
#line 14329 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr850;
		case 32: goto tr850;
		case 34: goto tr550;
		case 92: goto st451;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr851;
	} else if ( (*( state.p)) >= 9 )
		goto tr850;
	goto tr548;
tr851:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st581;
tr853:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st581;
st581:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof581;
case 581:
#line 14362 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr852;
		case 32: goto tr852;
		case 34: goto tr550;
		case 59: goto tr854;
		case 92: goto st451;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr853;
	} else if ( (*( state.p)) >= 9 )
		goto tr852;
	goto tr548;
tr685:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st582;
st582:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof582;
case 582:
#line 14386 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 101: goto tr855;
	}
	goto tr548;
tr855:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st583;
st583:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof583;
case 583:
#line 14403 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 102: goto tr856;
	}
	goto tr548;
tr856:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st584;
st584:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof584;
case 584:
#line 14420 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 101: goto tr857;
	}
	goto tr548;
tr857:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st585;
st585:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof585;
case 585:
#line 14437 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 110: goto tr858;
	}
	goto tr548;
tr858:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st586;
st586:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof586;
case 586:
#line 14454 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 115: goto tr859;
	}
	goto tr548;
tr859:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st587;
st587:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof587;
case 587:
#line 14471 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 101: goto tr860;
	}
	goto tr548;
tr860:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st588;
st588:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof588;
case 588:
#line 14488 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr861;
		case 32: goto tr861;
		case 34: goto tr550;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr861;
	goto tr548;
tr861:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st589;
st589:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof589;
case 589:
#line 14508 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr861;
		case 32: goto tr861;
		case 34: goto tr550;
		case 45: goto tr862;
		case 92: goto st451;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr863;
	} else if ( (*( state.p)) >= 9 )
		goto tr861;
	goto tr548;
tr862:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st590;
st590:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof590;
case 590:
#line 14536 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr864;
	goto tr548;
tr864:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st591;
tr863:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st591;
st591:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof591;
case 591:
#line 14564 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr865;
		case 32: goto tr865;
		case 34: goto tr550;
		case 46: goto tr866;
		case 59: goto tr867;
		case 92: goto st451;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr864;
	} else if ( (*( state.p)) >= 9 )
		goto tr865;
	goto tr548;
tr866:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st592;
st592:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof592;
case 592:
#line 14589 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr868;
	goto tr548;
tr868:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st593;
st593:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof593;
case 593:
#line 14607 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr865;
		case 32: goto tr865;
		case 34: goto tr550;
		case 59: goto tr867;
		case 92: goto st451;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr868;
	} else if ( (*( state.p)) >= 9 )
		goto tr865;
	goto tr548;
tr686:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st594;
st594:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof594;
case 594:
#line 14631 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 97: goto tr869;
	}
	goto tr548;
tr869:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st595;
st595:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof595;
case 595:
#line 14648 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 98: goto tr870;
	}
	goto tr548;
tr870:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st596;
st596:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof596;
case 596:
#line 14665 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 105: goto tr871;
	}
	goto tr548;
tr871:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st597;
st597:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof597;
case 597:
#line 14682 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 116: goto tr872;
	}
	goto tr548;
tr872:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st598;
st598:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof598;
case 598:
#line 14699 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 97: goto tr873;
	}
	goto tr548;
tr873:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st599;
st599:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof599;
case 599:
#line 14716 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 116: goto tr874;
	}
	goto tr548;
tr874:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st600;
st600:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof600;
case 600:
#line 14733 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr875;
		case 32: goto tr875;
		case 34: goto tr550;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr875;
	goto tr548;
tr875:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st601;
st601:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof601;
case 601:
#line 14753 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr875;
		case 32: goto tr875;
		case 34: goto tr550;
		case 92: goto st451;
		case 99: goto tr876;
		case 102: goto tr877;
		case 115: goto tr878;
		case 119: goto tr879;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr875;
	goto tr548;
tr876:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st602;
st602:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof602;
case 602:
#line 14777 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 111: goto tr880;
	}
	goto tr548;
tr880:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st603;
st603:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof603;
case 603:
#line 14794 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 114: goto tr881;
	}
	goto tr548;
tr881:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st604;
st604:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof604;
case 604:
#line 14811 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 110: goto tr882;
	}
	goto tr548;
tr882:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st605;
st605:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof605;
case 605:
#line 14828 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 101: goto tr883;
	}
	goto tr548;
tr883:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st606;
st606:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof606;
case 606:
#line 14845 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 114: goto tr884;
	}
	goto tr548;
tr884:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st607;
st607:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof607;
case 607:
#line 14862 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr885;
		case 32: goto tr885;
		case 34: goto tr550;
		case 59: goto tr886;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr885;
	goto tr548;
tr877:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st608;
st608:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof608;
case 608:
#line 14883 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 108: goto tr887;
	}
	goto tr548;
tr887:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st609;
st609:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof609;
case 609:
#line 14900 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 111: goto tr888;
	}
	goto tr548;
tr888:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st610;
st610:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof610;
case 610:
#line 14917 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 111: goto tr889;
	}
	goto tr548;
tr889:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st611;
st611:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof611;
case 611:
#line 14934 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 114: goto tr890;
	}
	goto tr548;
tr890:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st612;
st612:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof612;
case 612:
#line 14951 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr891;
		case 32: goto tr891;
		case 34: goto tr550;
		case 59: goto tr892;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr891;
	goto tr548;
tr878:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st613;
st613:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof613;
case 613:
#line 14972 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 104: goto tr893;
	}
	goto tr548;
tr893:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st614;
st614:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof614;
case 614:
#line 14989 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 111: goto tr894;
	}
	goto tr548;
tr894:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st615;
st615:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof615;
case 615:
#line 15006 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 114: goto tr895;
	}
	goto tr548;
tr895:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st616;
st616:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof616;
case 616:
#line 15023 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 101: goto tr896;
	}
	goto tr548;
tr896:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st617;
st617:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof617;
case 617:
#line 15040 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 108: goto tr897;
	}
	goto tr548;
tr897:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st618;
st618:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof618;
case 618:
#line 15057 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 105: goto tr898;
	}
	goto tr548;
tr898:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st619;
st619:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof619;
case 619:
#line 15074 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 110: goto tr899;
	}
	goto tr548;
tr899:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st620;
st620:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof620;
case 620:
#line 15091 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 101: goto tr900;
	}
	goto tr548;
tr900:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st621;
st621:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof621;
case 621:
#line 15108 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr901;
		case 32: goto tr901;
		case 34: goto tr550;
		case 59: goto tr902;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr901;
	goto tr548;
tr879:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st622;
st622:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof622;
case 622:
#line 15129 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 97: goto tr903;
	}
	goto tr548;
tr903:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st623;
st623:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof623;
case 623:
#line 15146 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 108: goto tr904;
		case 116: goto tr905;
	}
	goto tr548;
tr904:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st624;
st624:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof624;
case 624:
#line 15164 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 107: goto tr906;
	}
	goto tr548;
tr906:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st625;
st625:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof625;
case 625:
#line 15181 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr907;
		case 32: goto tr907;
		case 34: goto tr550;
		case 59: goto tr908;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr907;
	goto tr548;
tr905:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st626;
st626:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof626;
case 626:
#line 15202 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 101: goto tr909;
	}
	goto tr548;
tr909:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st627;
st627:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof627;
case 627:
#line 15219 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 114: goto tr910;
	}
	goto tr548;
tr910:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st628;
st628:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof628;
case 628:
#line 15236 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr911;
		case 32: goto tr911;
		case 34: goto tr550;
		case 59: goto tr912;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr911;
	goto tr548;
tr687:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st629;
st629:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof629;
case 629:
#line 15257 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 100: goto tr913;
	}
	goto tr548;
tr913:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st630;
st630:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof630;
case 630:
#line 15274 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 108: goto tr914;
	}
	goto tr548;
tr914:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st631;
st631:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof631;
case 631:
#line 15291 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 101: goto tr915;
	}
	goto tr548;
tr915:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st632;
st632:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof632;
case 632:
#line 15308 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 95: goto tr916;
	}
	goto tr548;
tr916:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st633;
st633:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof633;
case 633:
#line 15325 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 97: goto tr917;
	}
	goto tr548;
tr917:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st634;
st634:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof634;
case 634:
#line 15342 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 105: goto tr918;
	}
	goto tr548;
tr918:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st635;
st635:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof635;
case 635:
#line 15359 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr919;
		case 32: goto tr919;
		case 34: goto tr550;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr919;
	goto tr548;
tr919:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st636;
st636:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof636;
case 636:
#line 15379 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr919;
		case 32: goto tr919;
		case 34: goto tr550;
		case 92: goto st451;
		case 110: goto tr920;
		case 114: goto tr921;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr919;
	goto tr548;
tr920:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st637;
st637:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof637;
case 637:
#line 15401 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 111: goto tr922;
	}
	goto tr548;
tr922:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st638;
st638:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof638;
case 638:
#line 15418 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 110: goto tr923;
	}
	goto tr548;
tr923:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st639;
st639:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof639;
case 639:
#line 15435 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 101: goto tr924;
	}
	goto tr548;
tr924:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st640;
st640:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof640;
case 640:
#line 15452 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr925;
		case 32: goto tr925;
		case 34: goto tr550;
		case 59: goto tr926;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr925;
	goto tr548;
tr921:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st641;
st641:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof641;
case 641:
#line 15473 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 97: goto tr927;
	}
	goto tr548;
tr927:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st642;
st642:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof642;
case 642:
#line 15490 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 110: goto tr928;
	}
	goto tr548;
tr928:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st643;
st643:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof643;
case 643:
#line 15507 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 100: goto tr929;
	}
	goto tr548;
tr929:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st644;
st644:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof644;
case 644:
#line 15524 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 111: goto tr930;
	}
	goto tr548;
tr930:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st645;
st645:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof645;
case 645:
#line 15541 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 109: goto tr931;
	}
	goto tr548;
tr931:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st646;
st646:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof646;
case 646:
#line 15558 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr932;
		case 32: goto tr932;
		case 34: goto tr550;
		case 59: goto tr933;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr932;
	goto tr548;
tr688:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st647;
st647:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof647;
case 647:
#line 15579 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 111: goto tr934;
	}
	goto tr548;
tr934:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st648;
st648:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof648;
case 648:
#line 15596 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 118: goto tr935;
	}
	goto tr548;
tr935:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st649;
st649:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof649;
case 649:
#line 15613 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 101: goto tr936;
	}
	goto tr548;
tr936:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st650;
st650:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof650;
case 650:
#line 15630 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr937;
		case 32: goto tr937;
		case 34: goto tr550;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr937;
	goto tr548;
tr937:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st651;
st651:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof651;
case 651:
#line 15650 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr937;
		case 32: goto tr937;
		case 34: goto tr550;
		case 92: goto st451;
		case 97: goto tr938;
		case 102: goto tr939;
		case 119: goto tr940;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr937;
	goto tr548;
tr938:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st652;
st652:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof652;
case 652:
#line 15673 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 110: goto tr941;
	}
	goto tr548;
tr941:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st653;
st653:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof653;
case 653:
#line 15690 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 121: goto tr942;
	}
	goto tr548;
tr942:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st654;
st654:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof654;
case 654:
#line 15707 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr943;
		case 32: goto tr943;
		case 34: goto tr550;
		case 59: goto tr944;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr943;
	goto tr548;
tr939:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st655;
st655:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof655;
case 655:
#line 15728 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 108: goto tr945;
	}
	goto tr548;
tr945:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st656;
st656:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof656;
case 656:
#line 15745 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 111: goto tr946;
	}
	goto tr548;
tr946:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st657;
st657:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof657;
case 657:
#line 15762 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 111: goto tr947;
	}
	goto tr548;
tr947:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st658;
st658:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof658;
case 658:
#line 15779 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 114: goto tr948;
	}
	goto tr548;
tr948:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st659;
st659:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof659;
case 659:
#line 15796 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr949;
		case 32: goto tr949;
		case 34: goto tr550;
		case 59: goto tr950;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr949;
	goto tr548;
tr940:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st660;
st660:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof660;
case 660:
#line 15817 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 97: goto tr951;
	}
	goto tr548;
tr951:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st661;
st661:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof661;
case 661:
#line 15834 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 116: goto tr952;
	}
	goto tr548;
tr952:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st662;
st662:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof662;
case 662:
#line 15851 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 101: goto tr953;
	}
	goto tr548;
tr953:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st663;
st663:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof663;
case 663:
#line 15868 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 114: goto tr954;
	}
	goto tr548;
tr954:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st664;
st664:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof664;
case 664:
#line 15885 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr955;
		case 32: goto tr955;
		case 34: goto tr550;
		case 59: goto tr956;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr955;
	goto tr548;
tr689:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st665;
st665:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof665;
case 665:
#line 15906 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 97: goto tr957;
	}
	goto tr548;
tr957:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st666;
st666:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof666;
case 666:
#line 15923 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 109: goto tr958;
	}
	goto tr548;
tr958:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st667;
st667:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof667;
case 667:
#line 15940 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 101: goto tr959;
	}
	goto tr548;
tr959:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st668;
st668:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof668;
case 668:
#line 15957 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr960;
		case 32: goto tr960;
		case 34: goto tr550;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr960;
	goto tr548;
tr960:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st669;
st669:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof669;
case 669:
#line 15977 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr960;
		case 32: goto tr960;
		case 34: goto tr961;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr960;
	goto tr548;
tr961:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st670;
st670:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof670;
case 670:
#line 15997 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr962;
		case 32: goto tr962;
		case 34: goto tr321;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr962;
	goto tr319;
tr963:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st671;
tr962:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 161 "configparser.rl"
	{ skin.text = state.match; }
	goto st671;
st671:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof671;
case 671:
#line 16025 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr963;
		case 32: goto tr963;
		case 34: goto tr321;
		case 92: goto st229;
		case 98: goto tr964;
		case 100: goto tr965;
		case 110: goto tr966;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr963;
	goto tr319;
tr964:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st672;
st672:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof672;
case 672:
#line 16048 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 114: goto tr967;
	}
	goto tr319;
tr967:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st673;
st673:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof673;
case 673:
#line 16065 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 105: goto tr968;
	}
	goto tr319;
tr968:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st674;
st674:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof674;
case 674:
#line 16082 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 103: goto tr969;
	}
	goto tr319;
tr969:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st675;
st675:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof675;
case 675:
#line 16099 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 104: goto tr970;
	}
	goto tr319;
tr970:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st676;
st676:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof676;
case 676:
#line 16116 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 116: goto tr971;
	}
	goto tr319;
tr971:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st677;
st677:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof677;
case 677:
#line 16133 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr972;
		case 32: goto tr972;
		case 34: goto tr321;
		case 92: goto st229;
		case 95: goto tr973;
		case 98: goto tr974;
		case 99: goto tr975;
		case 103: goto tr976;
		case 109: goto tr977;
		case 114: goto tr978;
		case 119: goto tr979;
		case 121: goto tr980;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr972;
	goto tr319;
tr981:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st678;
tr972:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st678;
tr1037:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st678;
st678:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof678;
case 678:
#line 16177 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr981;
		case 32: goto tr981;
		case 34: goto tr321;
		case 92: goto st229;
		case 98: goto tr982;
		case 99: goto tr983;
		case 103: goto tr984;
		case 109: goto tr985;
		case 114: goto tr986;
		case 119: goto tr987;
		case 121: goto tr988;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr981;
	goto tr319;
tr982:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st679;
tr974:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st679;
tr1039:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st679;
st679:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof679;
case 679:
#line 16220 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 108: goto tr989;
	}
	goto tr319;
tr989:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st680;
st680:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof680;
case 680:
#line 16237 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 97: goto tr990;
		case 117: goto tr991;
	}
	goto tr319;
tr990:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st681;
st681:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof681;
case 681:
#line 16255 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 99: goto tr992;
	}
	goto tr319;
tr992:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st682;
st682:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof682;
case 682:
#line 16272 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 107: goto tr993;
	}
	goto tr319;
tr993:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st683;
st683:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof683;
case 683:
#line 16289 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr994;
		case 32: goto tr994;
		case 34: goto tr321;
		case 59: goto tr995;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr994;
	goto tr319;
tr991:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st684;
st684:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof684;
case 684:
#line 16310 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 101: goto tr996;
	}
	goto tr319;
tr996:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st685;
st685:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof685;
case 685:
#line 16327 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr997;
		case 32: goto tr997;
		case 34: goto tr321;
		case 59: goto tr998;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr997;
	goto tr319;
tr983:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st686;
tr975:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st686;
tr1040:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st686;
st686:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof686;
case 686:
#line 16364 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 121: goto tr999;
	}
	goto tr319;
tr999:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st687;
st687:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof687;
case 687:
#line 16381 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 97: goto tr1000;
	}
	goto tr319;
tr1000:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st688;
st688:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof688;
case 688:
#line 16398 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 110: goto tr1001;
	}
	goto tr319;
tr1001:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st689;
st689:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof689;
case 689:
#line 16415 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1002;
		case 32: goto tr1002;
		case 34: goto tr321;
		case 59: goto tr1003;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1002;
	goto tr319;
tr984:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st690;
tr976:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st690;
tr1041:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st690;
st690:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof690;
case 690:
#line 16452 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 114: goto tr1004;
	}
	goto tr319;
tr1004:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st691;
st691:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof691;
case 691:
#line 16469 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 101: goto tr1005;
	}
	goto tr319;
tr1005:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st692;
st692:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof692;
case 692:
#line 16486 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 101: goto tr1006;
	}
	goto tr319;
tr1006:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st693;
st693:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof693;
case 693:
#line 16503 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 110: goto tr1007;
	}
	goto tr319;
tr1007:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st694;
st694:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof694;
case 694:
#line 16520 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1008;
		case 32: goto tr1008;
		case 34: goto tr321;
		case 59: goto tr1009;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1008;
	goto tr319;
tr985:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st695;
tr977:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st695;
tr1042:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st695;
st695:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof695;
case 695:
#line 16557 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 97: goto tr1010;
	}
	goto tr319;
tr1010:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st696;
st696:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof696;
case 696:
#line 16574 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 103: goto tr1011;
	}
	goto tr319;
tr1011:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st697;
st697:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof697;
case 697:
#line 16591 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 101: goto tr1012;
	}
	goto tr319;
tr1012:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st698;
st698:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof698;
case 698:
#line 16608 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 110: goto tr1013;
	}
	goto tr319;
tr1013:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st699;
st699:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof699;
case 699:
#line 16625 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 116: goto tr1014;
	}
	goto tr319;
tr1014:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st700;
st700:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof700;
case 700:
#line 16642 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 97: goto tr1015;
	}
	goto tr319;
tr1015:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st701;
st701:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof701;
case 701:
#line 16659 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1016;
		case 32: goto tr1016;
		case 34: goto tr321;
		case 59: goto tr1017;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1016;
	goto tr319;
tr986:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st702;
tr978:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st702;
tr1043:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st702;
st702:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof702;
case 702:
#line 16696 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 101: goto tr1018;
	}
	goto tr319;
tr1018:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st703;
st703:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof703;
case 703:
#line 16713 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 100: goto tr1019;
	}
	goto tr319;
tr1019:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st704;
st704:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof704;
case 704:
#line 16730 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1020;
		case 32: goto tr1020;
		case 34: goto tr321;
		case 59: goto tr1021;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1020;
	goto tr319;
tr987:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st705;
tr979:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st705;
tr1044:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st705;
st705:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof705;
case 705:
#line 16767 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 104: goto tr1022;
	}
	goto tr319;
tr1022:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st706;
st706:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof706;
case 706:
#line 16784 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 105: goto tr1023;
	}
	goto tr319;
tr1023:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st707;
st707:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof707;
case 707:
#line 16801 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 116: goto tr1024;
	}
	goto tr319;
tr1024:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st708;
st708:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof708;
case 708:
#line 16818 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 101: goto tr1025;
	}
	goto tr319;
tr1025:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st709;
st709:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof709;
case 709:
#line 16835 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1026;
		case 32: goto tr1026;
		case 34: goto tr321;
		case 59: goto tr1027;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1026;
	goto tr319;
tr988:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st710;
tr980:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st710;
tr1045:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st710;
st710:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof710;
case 710:
#line 16872 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 101: goto tr1028;
	}
	goto tr319;
tr1028:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st711;
st711:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof711;
case 711:
#line 16889 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 108: goto tr1029;
	}
	goto tr319;
tr1029:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st712;
st712:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof712;
case 712:
#line 16906 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 108: goto tr1030;
	}
	goto tr319;
tr1030:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st713;
st713:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof713;
case 713:
#line 16923 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 111: goto tr1031;
	}
	goto tr319;
tr1031:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st714;
st714:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof714;
case 714:
#line 16940 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 119: goto tr1032;
	}
	goto tr319;
tr1032:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st715;
st715:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof715;
case 715:
#line 16957 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1033;
		case 32: goto tr1033;
		case 34: goto tr321;
		case 59: goto tr1034;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1033;
	goto tr319;
tr973:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st716;
tr1038:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st716;
st716:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof716;
case 716:
#line 16988 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 98: goto tr982;
		case 99: goto tr983;
		case 103: goto tr984;
		case 109: goto tr985;
		case 114: goto tr986;
		case 119: goto tr987;
		case 121: goto tr988;
	}
	goto tr319;
tr965:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st717;
st717:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof717;
case 717:
#line 17011 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 105: goto tr1035;
	}
	goto tr319;
tr1035:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st718;
st718:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof718;
case 718:
#line 17028 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 109: goto tr1036;
	}
	goto tr319;
tr1036:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st719;
st719:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof719;
case 719:
#line 17045 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1037;
		case 32: goto tr1037;
		case 34: goto tr321;
		case 92: goto st229;
		case 95: goto tr1038;
		case 98: goto tr1039;
		case 99: goto tr1040;
		case 103: goto tr1041;
		case 109: goto tr1042;
		case 114: goto tr1043;
		case 119: goto tr1044;
		case 121: goto tr1045;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1037;
	goto tr319;
tr966:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st720;
st720:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof720;
case 720:
#line 17073 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 111: goto tr1046;
	}
	goto tr319;
tr1046:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st721;
st721:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof721;
case 721:
#line 17090 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 110: goto tr1047;
	}
	goto tr319;
tr1047:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st722;
st722:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof722;
case 722:
#line 17107 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
		case 101: goto tr993;
	}
	goto tr319;
tr690:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st723;
st723:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof723;
case 723:
#line 17124 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 97: goto tr1048;
	}
	goto tr548;
tr1048:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st724;
st724:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof724;
case 724:
#line 17141 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 110: goto tr1049;
	}
	goto tr548;
tr1049:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st725;
st725:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof725;
case 725:
#line 17158 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 103: goto tr1050;
	}
	goto tr548;
tr1050:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st726;
st726:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof726;
case 726:
#line 17175 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 101: goto tr1051;
	}
	goto tr548;
tr1051:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st727;
st727:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof727;
case 727:
#line 17192 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1052;
		case 32: goto tr1052;
		case 34: goto tr550;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1052;
	goto tr548;
tr1052:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st728;
st728:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof728;
case 728:
#line 17212 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1052;
		case 32: goto tr1052;
		case 34: goto tr550;
		case 92: goto st451;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1053;
	} else if ( (*( state.p)) >= 9 )
		goto tr1052;
	goto tr548;
tr1055:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st729;
tr1053:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st729;
st729:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof729;
case 729:
#line 17245 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1054;
		case 32: goto tr1054;
		case 34: goto tr550;
		case 59: goto tr1056;
		case 92: goto st451;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1055;
	} else if ( (*( state.p)) >= 9 )
		goto tr1054;
	goto tr548;
tr691:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st730;
st730:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof730;
case 730:
#line 17269 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 107: goto tr1057;
	}
	goto tr548;
tr1057:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st731;
st731:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof731;
case 731:
#line 17286 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 105: goto tr1058;
	}
	goto tr548;
tr1058:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st732;
st732:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof732;
case 732:
#line 17303 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 110: goto tr1059;
	}
	goto tr548;
tr1059:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st733;
st733:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof733;
case 733:
#line 17320 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1060;
		case 32: goto tr1060;
		case 34: goto tr550;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1060;
	goto tr548;
tr1060:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st734;
st734:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof734;
case 734:
#line 17340 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1060;
		case 32: goto tr1060;
		case 34: goto tr1061;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1060;
	goto tr548;
tr1061:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st735;
st735:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof735;
case 735:
#line 17360 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1062;
		case 32: goto tr1062;
		case 34: goto tr550;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1062;
	goto tr548;
tr692:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st736;
st736:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof736;
case 736:
#line 17380 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1063;
		case 32: goto tr1063;
		case 34: goto tr550;
		case 59: goto tr1064;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1063;
	goto tr548;
tr675:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st737;
st737:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof737;
case 737:
#line 17401 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 101: goto tr1065;
	}
	goto tr548;
tr1065:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st738;
st738:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof738;
case 738:
#line 17418 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1066;
		case 32: goto tr1066;
		case 34: goto tr550;
		case 59: goto tr1067;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1066;
	goto tr548;
tr667:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st739;
tr659:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st739;
tr1109:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st739;
st739:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof739;
case 739:
#line 17455 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 121: goto tr1068;
	}
	goto tr548;
tr1068:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st740;
st740:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof740;
case 740:
#line 17472 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 97: goto tr1069;
	}
	goto tr548;
tr1069:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st741;
st741:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof741;
case 741:
#line 17489 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 110: goto tr1070;
	}
	goto tr548;
tr1070:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st742;
st742:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof742;
case 742:
#line 17506 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1071;
		case 32: goto tr1071;
		case 34: goto tr550;
		case 59: goto tr1072;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1071;
	goto tr548;
tr668:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st743;
tr660:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st743;
tr1110:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st743;
st743:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof743;
case 743:
#line 17543 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 114: goto tr1073;
	}
	goto tr548;
tr1073:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st744;
st744:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof744;
case 744:
#line 17560 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 101: goto tr1074;
	}
	goto tr548;
tr1074:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st745;
st745:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof745;
case 745:
#line 17577 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 101: goto tr1075;
	}
	goto tr548;
tr1075:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st746;
st746:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof746;
case 746:
#line 17594 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 110: goto tr1076;
	}
	goto tr548;
tr1076:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st747;
st747:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof747;
case 747:
#line 17611 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1077;
		case 32: goto tr1077;
		case 34: goto tr550;
		case 59: goto tr1078;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1077;
	goto tr548;
tr669:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st748;
tr661:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st748;
tr1111:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st748;
st748:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof748;
case 748:
#line 17648 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 97: goto tr1079;
	}
	goto tr548;
tr1079:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st749;
st749:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof749;
case 749:
#line 17665 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 103: goto tr1080;
	}
	goto tr548;
tr1080:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st750;
st750:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof750;
case 750:
#line 17682 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 101: goto tr1081;
	}
	goto tr548;
tr1081:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st751;
st751:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof751;
case 751:
#line 17699 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 110: goto tr1082;
	}
	goto tr548;
tr1082:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st752;
st752:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof752;
case 752:
#line 17716 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 116: goto tr1083;
	}
	goto tr548;
tr1083:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st753;
st753:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof753;
case 753:
#line 17733 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 97: goto tr1084;
	}
	goto tr548;
tr1084:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st754;
st754:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof754;
case 754:
#line 17750 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1085;
		case 32: goto tr1085;
		case 34: goto tr550;
		case 59: goto tr1086;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1085;
	goto tr548;
tr670:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st755;
tr662:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st755;
tr1112:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st755;
st755:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof755;
case 755:
#line 17787 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 101: goto tr1087;
	}
	goto tr548;
tr1087:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st756;
st756:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof756;
case 756:
#line 17804 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 100: goto tr1088;
	}
	goto tr548;
tr1088:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st757;
st757:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof757;
case 757:
#line 17821 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1089;
		case 32: goto tr1089;
		case 34: goto tr550;
		case 59: goto tr1090;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1089;
	goto tr548;
tr671:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st758;
tr663:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st758;
tr1113:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st758;
st758:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof758;
case 758:
#line 17858 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 104: goto tr1091;
	}
	goto tr548;
tr1091:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st759;
st759:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof759;
case 759:
#line 17875 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 105: goto tr1092;
	}
	goto tr548;
tr1092:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st760;
st760:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof760;
case 760:
#line 17892 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 116: goto tr1093;
	}
	goto tr548;
tr1093:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st761;
st761:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof761;
case 761:
#line 17909 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 101: goto tr1094;
	}
	goto tr548;
tr1094:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st762;
st762:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof762;
case 762:
#line 17926 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1095;
		case 32: goto tr1095;
		case 34: goto tr550;
		case 59: goto tr1096;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1095;
	goto tr548;
tr672:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st763;
tr664:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st763;
tr1114:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st763;
st763:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof763;
case 763:
#line 17963 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 101: goto tr1097;
	}
	goto tr548;
tr1097:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st764;
st764:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof764;
case 764:
#line 17980 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 108: goto tr1098;
	}
	goto tr548;
tr1098:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st765;
st765:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof765;
case 765:
#line 17997 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 108: goto tr1099;
	}
	goto tr548;
tr1099:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st766;
st766:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof766;
case 766:
#line 18014 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 111: goto tr1100;
	}
	goto tr548;
tr1100:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st767;
st767:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof767;
case 767:
#line 18031 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 119: goto tr1101;
	}
	goto tr548;
tr1101:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st768;
st768:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof768;
case 768:
#line 18048 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1102;
		case 32: goto tr1102;
		case 34: goto tr550;
		case 59: goto tr1103;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1102;
	goto tr548;
tr657:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st769;
tr1107:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st769;
st769:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof769;
case 769:
#line 18079 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 98: goto tr666;
		case 99: goto tr667;
		case 103: goto tr668;
		case 109: goto tr669;
		case 114: goto tr670;
		case 119: goto tr671;
		case 121: goto tr672;
	}
	goto tr548;
tr649:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st770;
st770:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof770;
case 770:
#line 18102 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 105: goto tr1104;
	}
	goto tr548;
tr1104:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st771;
st771:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof771;
case 771:
#line 18119 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 109: goto tr1105;
	}
	goto tr548;
tr1105:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st772;
st772:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof772;
case 772:
#line 18136 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1106;
		case 32: goto tr1106;
		case 34: goto tr550;
		case 92: goto st451;
		case 95: goto tr1107;
		case 98: goto tr1108;
		case 99: goto tr1109;
		case 103: goto tr1110;
		case 109: goto tr1111;
		case 114: goto tr1112;
		case 119: goto tr1113;
		case 121: goto tr1114;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1106;
	goto tr548;
tr650:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st773;
st773:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof773;
case 773:
#line 18164 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 111: goto tr1115;
	}
	goto tr548;
tr1115:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st774;
st774:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof774;
case 774:
#line 18181 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 110: goto tr1116;
	}
	goto tr548;
tr1116:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st775;
st775:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof775;
case 775:
#line 18198 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
		case 101: goto tr677;
	}
	goto tr548;
tr642:
#line 138 "configparser.rl"
	{ state.match += '\\'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st776;
st776:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof776;
case 776:
#line 18217 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1118;
		case 92: goto tr1119;
	}
	goto tr1117;
tr346:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st777;
st777:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof777;
case 777:
#line 18233 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1120;
		case 32: goto tr1120;
		case 34: goto tr321;
		case 59: goto tr1121;
		case 92: goto st229;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1120;
	goto tr319;
tr328:
#line 138 "configparser.rl"
	{ state.match += '\\'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st778;
st778:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof778;
case 778:
#line 18256 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1123;
		case 92: goto tr1124;
	}
	goto tr1122;
tr1125:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st779;
tr320:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 202 "configparser.rl"
	{ spe.companion.back().tag = state.match; }
	goto st779;
st779:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof779;
case 779:
#line 18280 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1125;
		case 32: goto tr1125;
		case 34: goto tr321;
		case 45: goto tr1126;
		case 92: goto st229;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1127;
	} else if ( (*( state.p)) >= 9 )
		goto tr1125;
	goto tr319;
tr1126:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st780;
st780:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof780;
case 780:
#line 18308 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr1128;
	goto tr319;
tr1128:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st781;
tr1127:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st781;
st781:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof781;
case 781:
#line 18336 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1129;
		case 32: goto tr1129;
		case 34: goto tr321;
		case 46: goto tr1130;
		case 59: goto tr1131;
		case 92: goto st229;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1128;
	} else if ( (*( state.p)) >= 9 )
		goto tr1129;
	goto tr319;
tr1130:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st782;
st782:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof782;
case 782:
#line 18361 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr321;
		case 92: goto st229;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr1132;
	goto tr319;
tr1132:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st783;
st783:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof783;
case 783:
#line 18379 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1129;
		case 32: goto tr1129;
		case 34: goto tr321;
		case 59: goto tr1131;
		case 92: goto st229;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1132;
	} else if ( (*( state.p)) >= 9 )
		goto tr1129;
	goto tr319;
tr132:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st784;
st784:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof784;
case 784:
#line 18403 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 97: goto tr1133;
	}
	goto tr95;
tr1133:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st785;
st785:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof785;
case 785:
#line 18420 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 110: goto tr1134;
	}
	goto tr95;
tr1134:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st786;
st786:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof786;
case 786:
#line 18437 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 103: goto tr1135;
	}
	goto tr95;
tr1135:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st787;
st787:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof787;
case 787:
#line 18454 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 101: goto tr1136;
	}
	goto tr95;
tr1136:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st788;
st788:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof788;
case 788:
#line 18471 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1137;
		case 32: goto tr1137;
		case 34: goto tr96;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1137;
	goto tr95;
tr1137:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st789;
st789:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof789;
case 789:
#line 18491 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1137;
		case 32: goto tr1137;
		case 34: goto tr96;
		case 92: goto st69;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1138;
	} else if ( (*( state.p)) >= 9 )
		goto tr1137;
	goto tr95;
tr1138:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st790;
tr1140:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st790;
st790:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof790;
case 790:
#line 18524 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1139;
		case 32: goto tr1139;
		case 34: goto tr96;
		case 59: goto tr1141;
		case 92: goto st69;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1140;
	} else if ( (*( state.p)) >= 9 )
		goto tr1139;
	goto tr95;
tr133:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st791;
st791:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof791;
case 791:
#line 18548 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 107: goto tr1142;
	}
	goto tr95;
tr1142:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st792;
st792:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof792;
case 792:
#line 18565 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 105: goto tr1143;
	}
	goto tr95;
tr1143:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st793;
st793:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof793;
case 793:
#line 18582 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
		case 110: goto tr1144;
	}
	goto tr95;
tr1144:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st794;
st794:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof794;
case 794:
#line 18599 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1145;
		case 32: goto tr1145;
		case 34: goto tr96;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1145;
	goto tr95;
tr1145:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st795;
st795:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof795;
case 795:
#line 18619 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1145;
		case 32: goto tr1145;
		case 34: goto tr1146;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1145;
	goto tr95;
tr1146:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st796;
st796:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof796;
case 796:
#line 18639 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1147;
		case 32: goto tr1147;
		case 34: goto tr550;
		case 92: goto st451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1147;
	goto tr548;
tr1148:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st797;
tr1147:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 202 "configparser.rl"
	{ spe.companion.back().tag = state.match; }
	goto st797;
st797:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof797;
case 797:
#line 18667 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1148;
		case 32: goto tr1148;
		case 34: goto tr550;
		case 45: goto tr1149;
		case 92: goto st451;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1150;
	} else if ( (*( state.p)) >= 9 )
		goto tr1148;
	goto tr548;
tr1149:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st798;
st798:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof798;
case 798:
#line 18695 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr1151;
	goto tr548;
tr1151:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st799;
tr1150:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st799;
st799:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof799;
case 799:
#line 18723 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1152;
		case 32: goto tr1152;
		case 34: goto tr550;
		case 46: goto tr1153;
		case 59: goto tr1154;
		case 92: goto st451;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1151;
	} else if ( (*( state.p)) >= 9 )
		goto tr1152;
	goto tr548;
tr1153:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st800;
st800:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof800;
case 800:
#line 18748 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto st451;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr1155;
	goto tr548;
tr1155:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st801;
st801:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof801;
case 801:
#line 18766 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1152;
		case 32: goto tr1152;
		case 34: goto tr550;
		case 59: goto tr1154;
		case 92: goto st451;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1155;
	} else if ( (*( state.p)) >= 9 )
		goto tr1152;
	goto tr548;
tr134:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st802;
st802:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof802;
case 802:
#line 18790 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1156;
		case 32: goto tr1156;
		case 34: goto tr96;
		case 59: goto tr1157;
		case 92: goto st69;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1156;
	goto tr95;
tr120:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st803;
st803:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof803;
case 803:
#line 18811 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr96;
		case 92: goto st69;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr1158;
	goto tr95;
tr1158:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st804;
st804:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof804;
case 804:
#line 18829 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr119;
		case 32: goto tr119;
		case 34: goto tr96;
		case 59: goto tr121;
		case 92: goto st69;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1158;
	} else if ( (*( state.p)) >= 9 )
		goto tr119;
	goto tr95;
tr110:
#line 138 "configparser.rl"
	{ state.match += '\\'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st805;
st805:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof805;
case 805:
#line 18855 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1160;
		case 92: goto tr1161;
	}
	goto tr1159;
st806:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof806;
case 806:
	if ( (*( state.p)) == 110 )
		goto st807;
	goto st0;
st807:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof807;
case 807:
	if ( (*( state.p)) == 116 )
		goto st808;
	goto st0;
st808:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof808;
case 808:
	switch( (*( state.p)) ) {
		case 13: goto st809;
		case 32: goto st809;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st809;
	goto st0;
st809:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof809;
case 809:
	switch( (*( state.p)) ) {
		case 13: goto st809;
		case 32: goto st809;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1165;
	} else if ( (*( state.p)) >= 9 )
		goto st809;
	goto st0;
tr1165:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st810;
tr1167:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st810;
st810:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof810;
case 810:
#line 18920 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1166;
		case 32: goto tr1166;
		case 59: goto tr1168;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1167;
	} else if ( (*( state.p)) >= 9 )
		goto tr1166;
	goto st0;
st811:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof811;
case 811:
	if ( (*( state.p)) == 101 )
		goto st812;
	goto st0;
st812:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof812;
case 812:
	if ( (*( state.p)) == 102 )
		goto st813;
	goto st0;
st813:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof813;
case 813:
	if ( (*( state.p)) == 101 )
		goto st814;
	goto st0;
st814:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof814;
case 814:
	if ( (*( state.p)) == 110 )
		goto st815;
	goto st0;
st815:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof815;
case 815:
	if ( (*( state.p)) == 115 )
		goto st816;
	goto st0;
st816:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof816;
case 816:
	if ( (*( state.p)) == 101 )
		goto st817;
	goto st0;
st817:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof817;
case 817:
	switch( (*( state.p)) ) {
		case 13: goto st818;
		case 32: goto st818;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st818;
	goto st0;
st818:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof818;
case 818:
	switch( (*( state.p)) ) {
		case 13: goto st818;
		case 32: goto st818;
		case 45: goto tr1176;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1177;
	} else if ( (*( state.p)) >= 9 )
		goto st818;
	goto st0;
tr1176:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st819;
st819:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof819;
case 819:
#line 19014 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr1178;
	goto st0;
tr1177:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st820;
tr1178:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st820;
st820:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof820;
case 820:
#line 19038 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1179;
		case 32: goto tr1179;
		case 46: goto tr1180;
		case 59: goto tr1181;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1178;
	} else if ( (*( state.p)) >= 9 )
		goto tr1179;
	goto st0;
tr1180:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st821;
st821:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof821;
case 821:
#line 19061 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr1182;
	goto st0;
tr1182:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st822;
st822:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof822;
case 822:
#line 19075 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1179;
		case 32: goto tr1179;
		case 59: goto tr1181;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1182;
	} else if ( (*( state.p)) >= 9 )
		goto tr1179;
	goto st0;
st823:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof823;
case 823:
	if ( (*( state.p)) == 97 )
		goto st824;
	goto st0;
st824:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof824;
case 824:
	if ( (*( state.p)) == 98 )
		goto st825;
	goto st0;
st825:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof825;
case 825:
	if ( (*( state.p)) == 105 )
		goto st826;
	goto st0;
st826:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof826;
case 826:
	if ( (*( state.p)) == 116 )
		goto st827;
	goto st0;
st827:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof827;
case 827:
	if ( (*( state.p)) == 97 )
		goto st828;
	goto st0;
st828:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof828;
case 828:
	if ( (*( state.p)) == 116 )
		goto st829;
	goto st0;
st829:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof829;
case 829:
	switch( (*( state.p)) ) {
		case 13: goto st830;
		case 32: goto st830;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st830;
	goto st0;
st830:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof830;
case 830:
	switch( (*( state.p)) ) {
		case 13: goto st830;
		case 32: goto st830;
		case 99: goto st831;
		case 102: goto st837;
		case 115: goto st842;
		case 119: goto st851;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st830;
	goto st0;
st831:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof831;
case 831:
	if ( (*( state.p)) == 111 )
		goto st832;
	goto st0;
st832:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof832;
case 832:
	if ( (*( state.p)) == 114 )
		goto st833;
	goto st0;
st833:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof833;
case 833:
	if ( (*( state.p)) == 110 )
		goto st834;
	goto st0;
st834:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof834;
case 834:
	if ( (*( state.p)) == 101 )
		goto st835;
	goto st0;
st835:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof835;
case 835:
	if ( (*( state.p)) == 114 )
		goto st836;
	goto st0;
st836:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof836;
case 836:
	switch( (*( state.p)) ) {
		case 13: goto tr1199;
		case 32: goto tr1199;
		case 59: goto tr1200;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1199;
	goto st0;
st837:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof837;
case 837:
	if ( (*( state.p)) == 108 )
		goto st838;
	goto st0;
st838:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof838;
case 838:
	if ( (*( state.p)) == 111 )
		goto st839;
	goto st0;
st839:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof839;
case 839:
	if ( (*( state.p)) == 111 )
		goto st840;
	goto st0;
st840:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof840;
case 840:
	if ( (*( state.p)) == 114 )
		goto st841;
	goto st0;
st841:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof841;
case 841:
	switch( (*( state.p)) ) {
		case 13: goto tr1205;
		case 32: goto tr1205;
		case 59: goto tr1206;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1205;
	goto st0;
st842:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof842;
case 842:
	if ( (*( state.p)) == 104 )
		goto st843;
	goto st0;
st843:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof843;
case 843:
	if ( (*( state.p)) == 111 )
		goto st844;
	goto st0;
st844:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof844;
case 844:
	if ( (*( state.p)) == 114 )
		goto st845;
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
	if ( (*( state.p)) == 108 )
		goto st847;
	goto st0;
st847:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof847;
case 847:
	if ( (*( state.p)) == 105 )
		goto st848;
	goto st0;
st848:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof848;
case 848:
	if ( (*( state.p)) == 110 )
		goto st849;
	goto st0;
st849:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof849;
case 849:
	if ( (*( state.p)) == 101 )
		goto st850;
	goto st0;
st850:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof850;
case 850:
	switch( (*( state.p)) ) {
		case 13: goto tr1215;
		case 32: goto tr1215;
		case 59: goto tr1216;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1215;
	goto st0;
st851:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof851;
case 851:
	if ( (*( state.p)) == 97 )
		goto st852;
	goto st0;
st852:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof852;
case 852:
	switch( (*( state.p)) ) {
		case 108: goto st853;
		case 116: goto st855;
	}
	goto st0;
st853:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof853;
case 853:
	if ( (*( state.p)) == 107 )
		goto st854;
	goto st0;
st854:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof854;
case 854:
	switch( (*( state.p)) ) {
		case 13: goto tr1221;
		case 32: goto tr1221;
		case 59: goto tr1222;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1221;
	goto st0;
st855:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof855;
case 855:
	if ( (*( state.p)) == 101 )
		goto st856;
	goto st0;
st856:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof856;
case 856:
	if ( (*( state.p)) == 114 )
		goto st857;
	goto st0;
st857:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof857;
case 857:
	switch( (*( state.p)) ) {
		case 13: goto tr1225;
		case 32: goto tr1225;
		case 59: goto tr1226;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1225;
	goto st0;
st858:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof858;
case 858:
	if ( (*( state.p)) == 100 )
		goto st859;
	goto st0;
st859:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof859;
case 859:
	if ( (*( state.p)) == 108 )
		goto st860;
	goto st0;
st860:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof860;
case 860:
	if ( (*( state.p)) == 101 )
		goto st861;
	goto st0;
st861:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof861;
case 861:
	if ( (*( state.p)) == 95 )
		goto st862;
	goto st0;
st862:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof862;
case 862:
	if ( (*( state.p)) == 97 )
		goto st863;
	goto st0;
st863:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof863;
case 863:
	if ( (*( state.p)) == 105 )
		goto st864;
	goto st0;
st864:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof864;
case 864:
	switch( (*( state.p)) ) {
		case 13: goto st865;
		case 32: goto st865;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st865;
	goto st0;
st865:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof865;
case 865:
	switch( (*( state.p)) ) {
		case 13: goto st865;
		case 32: goto st865;
		case 110: goto st866;
		case 114: goto st870;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st865;
	goto st0;
st866:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof866;
case 866:
	if ( (*( state.p)) == 111 )
		goto st867;
	goto st0;
st867:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof867;
case 867:
	if ( (*( state.p)) == 110 )
		goto st868;
	goto st0;
st868:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof868;
case 868:
	if ( (*( state.p)) == 101 )
		goto st869;
	goto st0;
st869:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof869;
case 869:
	switch( (*( state.p)) ) {
		case 13: goto tr1239;
		case 32: goto tr1239;
		case 59: goto tr1240;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1239;
	goto st0;
st870:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof870;
case 870:
	if ( (*( state.p)) == 97 )
		goto st871;
	goto st0;
st871:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof871;
case 871:
	if ( (*( state.p)) == 110 )
		goto st872;
	goto st0;
st872:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof872;
case 872:
	if ( (*( state.p)) == 100 )
		goto st873;
	goto st0;
st873:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof873;
case 873:
	if ( (*( state.p)) == 111 )
		goto st874;
	goto st0;
st874:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof874;
case 874:
	if ( (*( state.p)) == 109 )
		goto st875;
	goto st0;
st875:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof875;
case 875:
	switch( (*( state.p)) ) {
		case 13: goto tr1246;
		case 32: goto tr1246;
		case 59: goto tr1247;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1246;
	goto st0;
st876:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof876;
case 876:
	if ( (*( state.p)) == 111 )
		goto st877;
	goto st0;
st877:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof877;
case 877:
	if ( (*( state.p)) == 118 )
		goto st878;
	goto st0;
st878:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof878;
case 878:
	if ( (*( state.p)) == 101 )
		goto st879;
	goto st0;
st879:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof879;
case 879:
	switch( (*( state.p)) ) {
		case 13: goto st880;
		case 32: goto st880;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st880;
	goto st0;
st880:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof880;
case 880:
	switch( (*( state.p)) ) {
		case 13: goto st880;
		case 32: goto st880;
		case 97: goto st881;
		case 102: goto st884;
		case 119: goto st889;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st880;
	goto st0;
st881:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof881;
case 881:
	if ( (*( state.p)) == 110 )
		goto st882;
	goto st0;
st882:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof882;
case 882:
	if ( (*( state.p)) == 121 )
		goto st883;
	goto st0;
st883:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof883;
case 883:
	switch( (*( state.p)) ) {
		case 13: goto tr1257;
		case 32: goto tr1257;
		case 59: goto tr1258;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1257;
	goto st0;
st884:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof884;
case 884:
	if ( (*( state.p)) == 108 )
		goto st885;
	goto st0;
st885:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof885;
case 885:
	if ( (*( state.p)) == 111 )
		goto st886;
	goto st0;
st886:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof886;
case 886:
	if ( (*( state.p)) == 111 )
		goto st887;
	goto st0;
st887:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof887;
case 887:
	if ( (*( state.p)) == 114 )
		goto st888;
	goto st0;
st888:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof888;
case 888:
	switch( (*( state.p)) ) {
		case 13: goto tr1263;
		case 32: goto tr1263;
		case 59: goto tr1264;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1263;
	goto st0;
st889:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof889;
case 889:
	if ( (*( state.p)) == 97 )
		goto st890;
	goto st0;
st890:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof890;
case 890:
	if ( (*( state.p)) == 116 )
		goto st891;
	goto st0;
st891:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof891;
case 891:
	if ( (*( state.p)) == 101 )
		goto st892;
	goto st0;
st892:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof892;
case 892:
	if ( (*( state.p)) == 114 )
		goto st893;
	goto st0;
st893:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof893;
case 893:
	switch( (*( state.p)) ) {
		case 13: goto tr1269;
		case 32: goto tr1269;
		case 59: goto tr1270;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1269;
	goto st0;
st894:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof894;
case 894:
	if ( (*( state.p)) == 97 )
		goto st895;
	goto st0;
st895:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof895;
case 895:
	if ( (*( state.p)) == 109 )
		goto st896;
	goto st0;
st896:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof896;
case 896:
	if ( (*( state.p)) == 101 )
		goto st897;
	goto st0;
st897:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof897;
case 897:
	switch( (*( state.p)) ) {
		case 13: goto st898;
		case 32: goto st898;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st898;
	goto st0;
st898:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof898;
case 898:
	switch( (*( state.p)) ) {
		case 13: goto st898;
		case 32: goto st898;
		case 34: goto st227;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st898;
	goto st0;
st899:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof899;
case 899:
	if ( (*( state.p)) == 97 )
		goto st900;
	goto st0;
st900:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof900;
case 900:
	if ( (*( state.p)) == 110 )
		goto st901;
	goto st0;
st901:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof901;
case 901:
	if ( (*( state.p)) == 103 )
		goto st902;
	goto st0;
st902:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof902;
case 902:
	if ( (*( state.p)) == 101 )
		goto st903;
	goto st0;
st903:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof903;
case 903:
	switch( (*( state.p)) ) {
		case 13: goto st904;
		case 32: goto st904;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st904;
	goto st0;
st904:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof904;
case 904:
	switch( (*( state.p)) ) {
		case 13: goto st904;
		case 32: goto st904;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1281;
	} else if ( (*( state.p)) >= 9 )
		goto st904;
	goto st0;
tr1281:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st905;
tr1283:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st905;
st905:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof905;
case 905:
#line 19786 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1282;
		case 32: goto tr1282;
		case 59: goto tr1284;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1283;
	} else if ( (*( state.p)) >= 9 )
		goto tr1282;
	goto st0;
st906:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof906;
case 906:
	if ( (*( state.p)) == 107 )
		goto st907;
	goto st0;
st907:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof907;
case 907:
	if ( (*( state.p)) == 105 )
		goto st908;
	goto st0;
st908:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof908;
case 908:
	if ( (*( state.p)) == 110 )
		goto st909;
	goto st0;
st909:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof909;
case 909:
	switch( (*( state.p)) ) {
		case 13: goto st910;
		case 32: goto st910;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st910;
	goto st0;
st910:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof910;
case 910:
	switch( (*( state.p)) ) {
		case 13: goto st910;
		case 32: goto st910;
		case 34: goto st397;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st910;
	goto st0;
st911:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof911;
case 911:
	switch( (*( state.p)) ) {
		case 13: goto tr1290;
		case 32: goto tr1290;
		case 59: goto tr1291;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1290;
	goto st0;
st912:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof912;
case 912:
	if ( (*( state.p)) == 101 )
		goto st913;
	goto st0;
st913:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof913;
case 913:
	if ( (*( state.p)) == 101 )
		goto st914;
	goto st0;
st914:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof914;
case 914:
	if ( (*( state.p)) == 107 )
		goto st915;
	goto st0;
st915:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof915;
case 915:
	if ( (*( state.p)) == 95 )
		goto st916;
	goto st0;
st916:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof916;
case 916:
	if ( (*( state.p)) == 112 )
		goto st917;
	goto st0;
st917:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof917;
case 917:
	if ( (*( state.p)) == 108 )
		goto st918;
	goto st0;
st918:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof918;
case 918:
	if ( (*( state.p)) == 97 )
		goto st919;
	goto st0;
st919:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof919;
case 919:
	if ( (*( state.p)) == 121 )
		goto st920;
	goto st0;
st920:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof920;
case 920:
	if ( (*( state.p)) == 101 )
		goto st921;
	goto st0;
st921:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof921;
case 921:
	if ( (*( state.p)) == 114 )
		goto st922;
	goto st0;
st922:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof922;
case 922:
	switch( (*( state.p)) ) {
		case 13: goto tr1302;
		case 32: goto tr1302;
		case 59: goto tr1303;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1302;
	goto st0;
st923:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof923;
case 923:
	if ( (*( state.p)) == 116 )
		goto st924;
	goto st0;
st924:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof924;
case 924:
	if ( (*( state.p)) == 97 )
		goto st925;
	goto st0;
st925:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof925;
case 925:
	if ( (*( state.p)) == 99 )
		goto st926;
	goto st0;
st926:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof926;
case 926:
	if ( (*( state.p)) == 107 )
		goto st927;
	goto st0;
st927:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof927;
case 927:
	switch( (*( state.p)) ) {
		case 13: goto st928;
		case 32: goto st928;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st928;
	goto st0;
st928:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof928;
case 928:
	switch( (*( state.p)) ) {
		case 13: goto st928;
		case 32: goto st928;
		case 45: goto tr1309;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1310;
	} else if ( (*( state.p)) >= 9 )
		goto st928;
	goto st0;
tr1309:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st929;
st929:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof929;
case 929:
#line 20004 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr1311;
	goto st0;
tr1310:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st930;
tr1311:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st930;
st930:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof930;
case 930:
#line 20028 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1312;
		case 32: goto tr1312;
		case 46: goto tr1313;
		case 59: goto tr1314;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1311;
	} else if ( (*( state.p)) >= 9 )
		goto tr1312;
	goto st0;
tr1313:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st931;
st931:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof931;
case 931:
#line 20051 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr1315;
	goto st0;
tr1315:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st932;
st932:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof932;
case 932:
#line 20065 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1312;
		case 32: goto tr1312;
		case 59: goto tr1314;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1315;
	} else if ( (*( state.p)) >= 9 )
		goto tr1312;
	goto st0;
st933:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof933;
case 933:
	switch( (*( state.p)) ) {
		case 13: goto st933;
		case 32: goto st933;
		case 97: goto st934;
		case 99: goto st944;
		case 100: goto st951;
		case 110: goto st1467;
		case 115: goto st1472;
		case 125: goto st1481;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st933;
	goto st0;
st934:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof934;
case 934:
	if ( (*( state.p)) == 116 )
		goto st935;
	goto st0;
st935:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof935;
case 935:
	if ( (*( state.p)) == 116 )
		goto st936;
	goto st0;
st936:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof936;
case 936:
	if ( (*( state.p)) == 97 )
		goto st937;
	goto st0;
st937:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof937;
case 937:
	if ( (*( state.p)) == 99 )
		goto st938;
	goto st0;
st938:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof938;
case 938:
	if ( (*( state.p)) == 107 )
		goto st939;
	goto st0;
st939:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof939;
case 939:
	switch( (*( state.p)) ) {
		case 13: goto st940;
		case 32: goto st940;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st940;
	goto st0;
st940:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof940;
case 940:
	switch( (*( state.p)) ) {
		case 13: goto st940;
		case 32: goto st940;
		case 45: goto tr1329;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1330;
	} else if ( (*( state.p)) >= 9 )
		goto st940;
	goto st0;
tr1329:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st941;
st941:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof941;
case 941:
#line 20169 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr1331;
	goto st0;
tr1330:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st942;
tr1331:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st942;
st942:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof942;
case 942:
#line 20193 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1332;
		case 32: goto tr1332;
		case 46: goto tr1333;
		case 59: goto tr1334;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1331;
	} else if ( (*( state.p)) >= 9 )
		goto tr1332;
	goto st0;
tr1332:
#line 237 "configparser.rl"
	{ des.attack = ::atof(state.match.c_str()); }
	goto st943;
tr1343:
#line 232 "configparser.rl"
	{ des.count = ::atoi(state.match.c_str()); }
	goto st943;
tr1357:
#line 238 "configparser.rl"
	{ des.defense = ::atof(state.match.c_str()); }
	goto st943;
tr1368:
#line 236 "configparser.rl"
	{ des.descr = state.match; }
	goto st943;
tr1441:
#line 233 "configparser.rl"
	{ des.name = state.match; }
	goto st943;
tr1554:
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st943;
tr1557:
#line 151 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st943;
tr1562:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st943;
tr1568:
#line 149 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st943;
tr1576:
#line 152 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st943;
tr1580:
#line 148 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st943;
tr1586:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st943;
tr1593:
#line 150 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st943;
tr1891:
#line 235 "configparser.rl"
	{ des.slot = state.match; }
	goto st943;
tr2167:
#line 244 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st943;
st943:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof943;
case 943:
#line 20284 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st943;
		case 32: goto st943;
		case 59: goto st1491;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st943;
	goto st0;
tr1334:
#line 237 "configparser.rl"
	{ des.attack = ::atof(state.match.c_str()); }
	goto st1491;
tr1345:
#line 232 "configparser.rl"
	{ des.count = ::atoi(state.match.c_str()); }
	goto st1491;
tr1359:
#line 238 "configparser.rl"
	{ des.defense = ::atof(state.match.c_str()); }
	goto st1491;
tr1369:
#line 236 "configparser.rl"
	{ des.descr = state.match; }
	goto st1491;
tr1442:
#line 233 "configparser.rl"
	{ des.name = state.match; }
	goto st1491;
tr1555:
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1491;
tr1558:
#line 151 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1491;
tr1563:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1491;
tr1569:
#line 149 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1491;
tr1577:
#line 152 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1491;
tr1581:
#line 148 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1491;
tr1587:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1491;
tr1594:
#line 150 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1491;
tr1892:
#line 235 "configparser.rl"
	{ des.slot = state.match; }
	goto st1491;
tr2168:
#line 244 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st1491;
st1491:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1491;
case 1491:
#line 20371 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st933;
		case 32: goto st933;
		case 97: goto st934;
		case 99: goto st944;
		case 100: goto st951;
		case 110: goto st1467;
		case 115: goto st1472;
		case 125: goto st1481;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st933;
	goto st0;
st944:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof944;
case 944:
	if ( (*( state.p)) == 111 )
		goto st945;
	goto st0;
st945:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof945;
case 945:
	if ( (*( state.p)) == 117 )
		goto st946;
	goto st0;
st946:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof946;
case 946:
	if ( (*( state.p)) == 110 )
		goto st947;
	goto st0;
st947:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof947;
case 947:
	if ( (*( state.p)) == 116 )
		goto st948;
	goto st0;
st948:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof948;
case 948:
	switch( (*( state.p)) ) {
		case 13: goto st949;
		case 32: goto st949;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st949;
	goto st0;
st949:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof949;
case 949:
	switch( (*( state.p)) ) {
		case 13: goto st949;
		case 32: goto st949;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1342;
	} else if ( (*( state.p)) >= 9 )
		goto st949;
	goto st0;
tr1342:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st950;
tr1344:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st950;
st950:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof950;
case 950:
#line 20458 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1343;
		case 32: goto tr1343;
		case 59: goto tr1345;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1344;
	} else if ( (*( state.p)) >= 9 )
		goto tr1343;
	goto st0;
st951:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof951;
case 951:
	if ( (*( state.p)) == 101 )
		goto st952;
	goto st0;
st952:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof952;
case 952:
	switch( (*( state.p)) ) {
		case 102: goto st953;
		case 115: goto st963;
	}
	goto st0;
st953:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof953;
case 953:
	if ( (*( state.p)) == 101 )
		goto st954;
	goto st0;
st954:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof954;
case 954:
	if ( (*( state.p)) == 110 )
		goto st955;
	goto st0;
st955:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof955;
case 955:
	if ( (*( state.p)) == 115 )
		goto st956;
	goto st0;
st956:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof956;
case 956:
	if ( (*( state.p)) == 101 )
		goto st957;
	goto st0;
st957:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof957;
case 957:
	switch( (*( state.p)) ) {
		case 13: goto st958;
		case 32: goto st958;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st958;
	goto st0;
st958:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof958;
case 958:
	switch( (*( state.p)) ) {
		case 13: goto st958;
		case 32: goto st958;
		case 45: goto tr1354;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1355;
	} else if ( (*( state.p)) >= 9 )
		goto st958;
	goto st0;
tr1354:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st959;
st959:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof959;
case 959:
#line 20554 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr1356;
	goto st0;
tr1355:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st960;
tr1356:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st960;
st960:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof960;
case 960:
#line 20578 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1357;
		case 32: goto tr1357;
		case 46: goto tr1358;
		case 59: goto tr1359;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1356;
	} else if ( (*( state.p)) >= 9 )
		goto tr1357;
	goto st0;
tr1358:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st961;
st961:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof961;
case 961:
#line 20601 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr1360;
	goto st0;
tr1360:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st962;
st962:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof962;
case 962:
#line 20615 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1357;
		case 32: goto tr1357;
		case 59: goto tr1359;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1360;
	} else if ( (*( state.p)) >= 9 )
		goto tr1357;
	goto st0;
st963:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof963;
case 963:
	if ( (*( state.p)) == 99 )
		goto st964;
	goto st0;
st964:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof964;
case 964:
	if ( (*( state.p)) == 114 )
		goto st965;
	goto st0;
st965:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof965;
case 965:
	switch( (*( state.p)) ) {
		case 13: goto st966;
		case 32: goto st966;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st966;
	goto st0;
st966:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof966;
case 966:
	switch( (*( state.p)) ) {
		case 13: goto st966;
		case 32: goto st966;
		case 34: goto st967;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st966;
	goto st0;
tr1365:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st967;
tr1370:
#line 138 "configparser.rl"
	{ state.match += '\\'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st967;
tr1374:
#line 136 "configparser.rl"
	{ state.match += '"'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st967;
tr2149:
#line 137 "configparser.rl"
	{ state.match += '\n'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st967;
st967:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof967;
case 967:
#line 20698 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
	}
	goto tr1365;
tr1366:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st968;
tr1376:
#line 136 "configparser.rl"
	{ state.match += '"'; }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st968;
tr2150:
#line 137 "configparser.rl"
	{ state.match += '\n'; }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st968;
st968:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof968;
case 968:
#line 20730 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1368;
		case 32: goto tr1368;
		case 59: goto tr1369;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1368;
	goto st0;
tr1372:
#line 138 "configparser.rl"
	{ state.match += '\\'; }
	goto st969;
tr1378:
#line 136 "configparser.rl"
	{ state.match += '"'; }
	goto st969;
tr2151:
#line 137 "configparser.rl"
	{ state.match += '\n'; }
	goto st969;
st969:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof969;
case 969:
#line 20755 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1371;
		case 92: goto tr1372;
		case 110: goto tr1373;
	}
	goto tr1370;
tr1371:
#line 138 "configparser.rl"
	{ state.match += '\\'; }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st970;
st970:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof970;
case 970:
#line 20774 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1375;
		case 32: goto tr1375;
		case 34: goto tr1376;
		case 59: goto tr1377;
		case 92: goto tr1378;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1375;
	goto tr1374;
tr1379:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st971;
tr1375:
#line 136 "configparser.rl"
	{ state.match += '"'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 236 "configparser.rl"
	{ des.descr = state.match; }
	goto st971;
tr1397:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 237 "configparser.rl"
	{ des.attack = ::atof(state.match.c_str()); }
	goto st971;
tr1407:
#line 232 "configparser.rl"
	{ des.count = ::atoi(state.match.c_str()); }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st971;
tr1421:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 238 "configparser.rl"
	{ des.defense = ::atof(state.match.c_str()); }
	goto st971;
tr1429:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 236 "configparser.rl"
	{ des.descr = state.match; }
	goto st971;
tr1502:
#line 233 "configparser.rl"
	{ des.name = state.match; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st971;
tr1731:
#line 234 "configparser.rl"
	{ des.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st971;
tr1734:
#line 151 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st971;
tr1739:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st971;
tr1745:
#line 149 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st971;
tr1753:
#line 152 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st971;
tr1757:
#line 148 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st971;
tr1763:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st971;
tr1770:
#line 150 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st971;
tr1952:
#line 235 "configparser.rl"
	{ des.slot = state.match; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st971;
tr2147:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 244 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st971;
st971:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof971;
case 971:
#line 20939 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1379;
		case 32: goto tr1379;
		case 34: goto tr1366;
		case 59: goto tr1380;
		case 92: goto st969;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1379;
	goto tr1365;
tr1380:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1492;
tr1377:
#line 136 "configparser.rl"
	{ state.match += '"'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 236 "configparser.rl"
	{ des.descr = state.match; }
	goto st1492;
tr1399:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 237 "configparser.rl"
	{ des.attack = ::atof(state.match.c_str()); }
	goto st1492;
tr1409:
#line 232 "configparser.rl"
	{ des.count = ::atoi(state.match.c_str()); }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1492;
tr1423:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 238 "configparser.rl"
	{ des.defense = ::atof(state.match.c_str()); }
	goto st1492;
tr1430:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 236 "configparser.rl"
	{ des.descr = state.match; }
	goto st1492;
tr1503:
#line 233 "configparser.rl"
	{ des.name = state.match; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1492;
tr1732:
#line 234 "configparser.rl"
	{ des.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1492;
tr1735:
#line 151 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1492;
tr1740:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1492;
tr1746:
#line 149 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1492;
tr1754:
#line 152 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1492;
tr1758:
#line 148 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1492;
tr1764:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1492;
tr1771:
#line 150 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1492;
tr1953:
#line 235 "configparser.rl"
	{ des.slot = state.match; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1492;
tr2148:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 244 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st1492;
st1492:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1492;
case 1492:
#line 21104 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1381;
		case 32: goto tr1381;
		case 34: goto tr1366;
		case 92: goto st969;
		case 97: goto tr1382;
		case 99: goto tr1383;
		case 100: goto tr1384;
		case 110: goto tr1385;
		case 115: goto tr1386;
		case 125: goto tr1387;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1381;
	goto tr1365;
tr1381:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st972;
st972:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof972;
case 972:
#line 21130 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1381;
		case 32: goto tr1381;
		case 34: goto tr1366;
		case 92: goto st969;
		case 97: goto tr1382;
		case 99: goto tr1383;
		case 100: goto tr1384;
		case 110: goto tr1385;
		case 115: goto tr1386;
		case 125: goto tr1387;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1381;
	goto tr1365;
tr1382:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st973;
st973:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof973;
case 973:
#line 21156 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 116: goto tr1388;
	}
	goto tr1365;
tr1388:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st974;
st974:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof974;
case 974:
#line 21173 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 116: goto tr1389;
	}
	goto tr1365;
tr1389:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st975;
st975:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof975;
case 975:
#line 21190 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 97: goto tr1390;
	}
	goto tr1365;
tr1390:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st976;
st976:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof976;
case 976:
#line 21207 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 99: goto tr1391;
	}
	goto tr1365;
tr1391:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st977;
st977:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof977;
case 977:
#line 21224 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 107: goto tr1392;
	}
	goto tr1365;
tr1392:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st978;
st978:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof978;
case 978:
#line 21241 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1393;
		case 32: goto tr1393;
		case 34: goto tr1366;
		case 92: goto st969;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1393;
	goto tr1365;
tr1393:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st979;
st979:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof979;
case 979:
#line 21261 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1393;
		case 32: goto tr1393;
		case 34: goto tr1366;
		case 45: goto tr1394;
		case 92: goto st969;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1395;
	} else if ( (*( state.p)) >= 9 )
		goto tr1393;
	goto tr1365;
tr1394:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st980;
st980:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof980;
case 980:
#line 21289 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr1396;
	goto tr1365;
tr1396:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st981;
tr1395:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st981;
st981:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof981;
case 981:
#line 21317 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1397;
		case 32: goto tr1397;
		case 34: goto tr1366;
		case 46: goto tr1398;
		case 59: goto tr1399;
		case 92: goto st969;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1396;
	} else if ( (*( state.p)) >= 9 )
		goto tr1397;
	goto tr1365;
tr1398:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st982;
st982:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof982;
case 982:
#line 21342 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr1400;
	goto tr1365;
tr1400:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st983;
st983:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof983;
case 983:
#line 21360 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1397;
		case 32: goto tr1397;
		case 34: goto tr1366;
		case 59: goto tr1399;
		case 92: goto st969;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1400;
	} else if ( (*( state.p)) >= 9 )
		goto tr1397;
	goto tr1365;
tr1383:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st984;
st984:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof984;
case 984:
#line 21384 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 111: goto tr1401;
	}
	goto tr1365;
tr1401:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st985;
st985:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof985;
case 985:
#line 21401 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 117: goto tr1402;
	}
	goto tr1365;
tr1402:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st986;
st986:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof986;
case 986:
#line 21418 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 110: goto tr1403;
	}
	goto tr1365;
tr1403:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st987;
st987:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof987;
case 987:
#line 21435 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 116: goto tr1404;
	}
	goto tr1365;
tr1404:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st988;
st988:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof988;
case 988:
#line 21452 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1405;
		case 32: goto tr1405;
		case 34: goto tr1366;
		case 92: goto st969;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1405;
	goto tr1365;
tr1405:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st989;
st989:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof989;
case 989:
#line 21472 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1405;
		case 32: goto tr1405;
		case 34: goto tr1366;
		case 92: goto st969;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1406;
	} else if ( (*( state.p)) >= 9 )
		goto tr1405;
	goto tr1365;
tr1406:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st990;
tr1408:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st990;
st990:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof990;
case 990:
#line 21505 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1407;
		case 32: goto tr1407;
		case 34: goto tr1366;
		case 59: goto tr1409;
		case 92: goto st969;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1408;
	} else if ( (*( state.p)) >= 9 )
		goto tr1407;
	goto tr1365;
tr1384:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st991;
st991:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof991;
case 991:
#line 21529 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 101: goto tr1410;
	}
	goto tr1365;
tr1410:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st992;
st992:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof992;
case 992:
#line 21546 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 102: goto tr1411;
		case 115: goto tr1412;
	}
	goto tr1365;
tr1411:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st993;
st993:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof993;
case 993:
#line 21564 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 101: goto tr1413;
	}
	goto tr1365;
tr1413:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st994;
st994:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof994;
case 994:
#line 21581 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 110: goto tr1414;
	}
	goto tr1365;
tr1414:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st995;
st995:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof995;
case 995:
#line 21598 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 115: goto tr1415;
	}
	goto tr1365;
tr1415:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st996;
st996:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof996;
case 996:
#line 21615 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 101: goto tr1416;
	}
	goto tr1365;
tr1416:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st997;
st997:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof997;
case 997:
#line 21632 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1417;
		case 32: goto tr1417;
		case 34: goto tr1366;
		case 92: goto st969;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1417;
	goto tr1365;
tr1417:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st998;
st998:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof998;
case 998:
#line 21652 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1417;
		case 32: goto tr1417;
		case 34: goto tr1366;
		case 45: goto tr1418;
		case 92: goto st969;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1419;
	} else if ( (*( state.p)) >= 9 )
		goto tr1417;
	goto tr1365;
tr1418:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st999;
st999:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof999;
case 999:
#line 21680 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr1420;
	goto tr1365;
tr1420:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1000;
tr1419:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1000;
st1000:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1000;
case 1000:
#line 21708 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1421;
		case 32: goto tr1421;
		case 34: goto tr1366;
		case 46: goto tr1422;
		case 59: goto tr1423;
		case 92: goto st969;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1420;
	} else if ( (*( state.p)) >= 9 )
		goto tr1421;
	goto tr1365;
tr1422:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1001;
st1001:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1001;
case 1001:
#line 21733 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr1424;
	goto tr1365;
tr1424:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1002;
st1002:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1002;
case 1002:
#line 21751 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1421;
		case 32: goto tr1421;
		case 34: goto tr1366;
		case 59: goto tr1423;
		case 92: goto st969;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1424;
	} else if ( (*( state.p)) >= 9 )
		goto tr1421;
	goto tr1365;
tr1412:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1003;
st1003:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1003;
case 1003:
#line 21775 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 99: goto tr1425;
	}
	goto tr1365;
tr1425:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1004;
st1004:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1004;
case 1004:
#line 21792 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 114: goto tr1426;
	}
	goto tr1365;
tr1426:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1005;
st1005:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1005;
case 1005:
#line 21809 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1427;
		case 32: goto tr1427;
		case 34: goto tr1366;
		case 92: goto st969;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1427;
	goto tr1365;
tr1427:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1006;
st1006:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1006;
case 1006:
#line 21829 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1427;
		case 32: goto tr1427;
		case 34: goto tr1428;
		case 92: goto st969;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1427;
	goto tr1365;
tr1428:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1007;
st1007:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1007;
case 1007:
#line 21849 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1429;
		case 32: goto tr1429;
		case 34: goto tr1366;
		case 59: goto tr1430;
		case 92: goto st969;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1429;
	goto tr1365;
tr1385:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1008;
st1008:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1008;
case 1008:
#line 21870 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 97: goto tr1431;
	}
	goto tr1365;
tr1431:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1009;
st1009:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1009;
case 1009:
#line 21887 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 109: goto tr1432;
	}
	goto tr1365;
tr1432:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1010;
st1010:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1010;
case 1010:
#line 21904 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 101: goto tr1433;
	}
	goto tr1365;
tr1433:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1011;
st1011:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1011;
case 1011:
#line 21921 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1434;
		case 32: goto tr1434;
		case 34: goto tr1366;
		case 92: goto st969;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1434;
	goto tr1365;
tr1434:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1012;
st1012:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1012;
case 1012:
#line 21941 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1434;
		case 32: goto tr1434;
		case 34: goto tr1435;
		case 92: goto st969;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1434;
	goto tr1365;
tr1435:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1013;
st1013:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1013;
case 1013:
#line 21961 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1437;
		case 32: goto tr1437;
		case 34: goto tr1438;
		case 59: goto tr1439;
		case 92: goto st1016;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1437;
	goto tr1436;
tr1436:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1014;
tr1443:
#line 138 "configparser.rl"
	{ state.match += '\\'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1014;
tr1447:
#line 136 "configparser.rl"
	{ state.match += '"'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1014;
tr2130:
#line 137 "configparser.rl"
	{ state.match += '\n'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1014;
st1014:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1014;
case 1014:
#line 22006 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
	}
	goto tr1436;
tr1438:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1015;
tr1449:
#line 136 "configparser.rl"
	{ state.match += '"'; }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1015;
tr2131:
#line 137 "configparser.rl"
	{ state.match += '\n'; }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1015;
st1015:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1015;
case 1015:
#line 22038 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1441;
		case 32: goto tr1441;
		case 59: goto tr1442;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1441;
	goto st0;
tr1445:
#line 138 "configparser.rl"
	{ state.match += '\\'; }
	goto st1016;
tr1451:
#line 136 "configparser.rl"
	{ state.match += '"'; }
	goto st1016;
tr2132:
#line 137 "configparser.rl"
	{ state.match += '\n'; }
	goto st1016;
st1016:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1016;
case 1016:
#line 22063 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1444;
		case 92: goto tr1445;
		case 110: goto tr1446;
	}
	goto tr1443;
tr1444:
#line 138 "configparser.rl"
	{ state.match += '\\'; }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1017;
st1017:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1017;
case 1017:
#line 22082 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1448;
		case 32: goto tr1448;
		case 34: goto tr1449;
		case 59: goto tr1450;
		case 92: goto tr1451;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1448;
	goto tr1447;
tr1452:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1018;
tr1470:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 237 "configparser.rl"
	{ des.attack = ::atof(state.match.c_str()); }
	goto st1018;
tr1480:
#line 232 "configparser.rl"
	{ des.count = ::atoi(state.match.c_str()); }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1018;
tr1494:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 238 "configparser.rl"
	{ des.defense = ::atof(state.match.c_str()); }
	goto st1018;
tr1437:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 236 "configparser.rl"
	{ des.descr = state.match; }
	goto st1018;
tr1448:
#line 136 "configparser.rl"
	{ state.match += '"'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 233 "configparser.rl"
	{ des.name = state.match; }
	goto st1018;
tr1509:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 233 "configparser.rl"
	{ des.name = state.match; }
	goto st1018;
tr1822:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1018;
tr1825:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 151 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1018;
tr1830:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 153 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1018;
tr1836:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 149 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1018;
tr1844:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 152 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1018;
tr1848:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 148 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1018;
tr1854:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 154 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1018;
tr1861:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 150 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1018;
tr1959:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 235 "configparser.rl"
	{ des.slot = state.match; }
	goto st1018;
tr2128:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 244 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st1018;
st1018:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1018;
case 1018:
#line 22247 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1452;
		case 32: goto tr1452;
		case 34: goto tr1438;
		case 59: goto tr1453;
		case 92: goto st1016;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1452;
	goto tr1436;
tr1453:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1493;
tr1472:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 237 "configparser.rl"
	{ des.attack = ::atof(state.match.c_str()); }
	goto st1493;
tr1482:
#line 232 "configparser.rl"
	{ des.count = ::atoi(state.match.c_str()); }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1493;
tr1496:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 238 "configparser.rl"
	{ des.defense = ::atof(state.match.c_str()); }
	goto st1493;
tr1439:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 236 "configparser.rl"
	{ des.descr = state.match; }
	goto st1493;
tr1450:
#line 136 "configparser.rl"
	{ state.match += '"'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 233 "configparser.rl"
	{ des.name = state.match; }
	goto st1493;
tr1510:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 233 "configparser.rl"
	{ des.name = state.match; }
	goto st1493;
tr1823:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1493;
tr1826:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 151 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1493;
tr1831:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 153 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1493;
tr1837:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 149 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1493;
tr1845:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 152 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1493;
tr1849:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 148 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1493;
tr1855:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 154 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1493;
tr1862:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 150 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1493;
tr1960:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 235 "configparser.rl"
	{ des.slot = state.match; }
	goto st1493;
tr2129:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 244 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st1493;
st1493:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1493;
case 1493:
#line 22412 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1454;
		case 32: goto tr1454;
		case 34: goto tr1438;
		case 92: goto st1016;
		case 97: goto tr1455;
		case 99: goto tr1456;
		case 100: goto tr1457;
		case 110: goto tr1458;
		case 115: goto tr1459;
		case 125: goto tr1460;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1454;
	goto tr1436;
tr1454:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1019;
st1019:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1019;
case 1019:
#line 22438 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1454;
		case 32: goto tr1454;
		case 34: goto tr1438;
		case 92: goto st1016;
		case 97: goto tr1455;
		case 99: goto tr1456;
		case 100: goto tr1457;
		case 110: goto tr1458;
		case 115: goto tr1459;
		case 125: goto tr1460;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1454;
	goto tr1436;
tr1455:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1020;
st1020:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1020;
case 1020:
#line 22464 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 116: goto tr1461;
	}
	goto tr1436;
tr1461:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1021;
st1021:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1021;
case 1021:
#line 22481 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 116: goto tr1462;
	}
	goto tr1436;
tr1462:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1022;
st1022:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1022;
case 1022:
#line 22498 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 97: goto tr1463;
	}
	goto tr1436;
tr1463:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1023;
st1023:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1023;
case 1023:
#line 22515 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 99: goto tr1464;
	}
	goto tr1436;
tr1464:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1024;
st1024:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1024;
case 1024:
#line 22532 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 107: goto tr1465;
	}
	goto tr1436;
tr1465:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1025;
st1025:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1025;
case 1025:
#line 22549 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1466;
		case 32: goto tr1466;
		case 34: goto tr1438;
		case 92: goto st1016;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1466;
	goto tr1436;
tr1466:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1026;
st1026:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1026;
case 1026:
#line 22569 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1466;
		case 32: goto tr1466;
		case 34: goto tr1438;
		case 45: goto tr1467;
		case 92: goto st1016;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1468;
	} else if ( (*( state.p)) >= 9 )
		goto tr1466;
	goto tr1436;
tr1467:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1027;
st1027:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1027;
case 1027:
#line 22597 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr1469;
	goto tr1436;
tr1469:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1028;
tr1468:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1028;
st1028:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1028;
case 1028:
#line 22625 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1470;
		case 32: goto tr1470;
		case 34: goto tr1438;
		case 46: goto tr1471;
		case 59: goto tr1472;
		case 92: goto st1016;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1469;
	} else if ( (*( state.p)) >= 9 )
		goto tr1470;
	goto tr1436;
tr1471:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1029;
st1029:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1029;
case 1029:
#line 22650 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr1473;
	goto tr1436;
tr1473:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1030;
st1030:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1030;
case 1030:
#line 22668 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1470;
		case 32: goto tr1470;
		case 34: goto tr1438;
		case 59: goto tr1472;
		case 92: goto st1016;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1473;
	} else if ( (*( state.p)) >= 9 )
		goto tr1470;
	goto tr1436;
tr1456:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1031;
st1031:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1031;
case 1031:
#line 22692 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 111: goto tr1474;
	}
	goto tr1436;
tr1474:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1032;
st1032:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1032;
case 1032:
#line 22709 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 117: goto tr1475;
	}
	goto tr1436;
tr1475:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1033;
st1033:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1033;
case 1033:
#line 22726 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 110: goto tr1476;
	}
	goto tr1436;
tr1476:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1034;
st1034:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1034;
case 1034:
#line 22743 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 116: goto tr1477;
	}
	goto tr1436;
tr1477:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1035;
st1035:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1035;
case 1035:
#line 22760 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1478;
		case 32: goto tr1478;
		case 34: goto tr1438;
		case 92: goto st1016;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1478;
	goto tr1436;
tr1478:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1036;
st1036:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1036;
case 1036:
#line 22780 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1478;
		case 32: goto tr1478;
		case 34: goto tr1438;
		case 92: goto st1016;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1479;
	} else if ( (*( state.p)) >= 9 )
		goto tr1478;
	goto tr1436;
tr1479:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1037;
tr1481:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1037;
st1037:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1037;
case 1037:
#line 22813 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1480;
		case 32: goto tr1480;
		case 34: goto tr1438;
		case 59: goto tr1482;
		case 92: goto st1016;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1481;
	} else if ( (*( state.p)) >= 9 )
		goto tr1480;
	goto tr1436;
tr1457:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1038;
st1038:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1038;
case 1038:
#line 22837 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 101: goto tr1483;
	}
	goto tr1436;
tr1483:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1039;
st1039:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1039;
case 1039:
#line 22854 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 102: goto tr1484;
		case 115: goto tr1485;
	}
	goto tr1436;
tr1484:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1040;
st1040:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1040;
case 1040:
#line 22872 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 101: goto tr1486;
	}
	goto tr1436;
tr1486:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1041;
st1041:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1041;
case 1041:
#line 22889 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 110: goto tr1487;
	}
	goto tr1436;
tr1487:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1042;
st1042:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1042;
case 1042:
#line 22906 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 115: goto tr1488;
	}
	goto tr1436;
tr1488:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1043;
st1043:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1043;
case 1043:
#line 22923 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 101: goto tr1489;
	}
	goto tr1436;
tr1489:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1044;
st1044:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1044;
case 1044:
#line 22940 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1490;
		case 32: goto tr1490;
		case 34: goto tr1438;
		case 92: goto st1016;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1490;
	goto tr1436;
tr1490:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1045;
st1045:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1045;
case 1045:
#line 22960 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1490;
		case 32: goto tr1490;
		case 34: goto tr1438;
		case 45: goto tr1491;
		case 92: goto st1016;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1492;
	} else if ( (*( state.p)) >= 9 )
		goto tr1490;
	goto tr1436;
tr1491:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1046;
st1046:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1046;
case 1046:
#line 22988 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr1493;
	goto tr1436;
tr1493:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1047;
tr1492:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1047;
st1047:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1047;
case 1047:
#line 23016 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1494;
		case 32: goto tr1494;
		case 34: goto tr1438;
		case 46: goto tr1495;
		case 59: goto tr1496;
		case 92: goto st1016;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1493;
	} else if ( (*( state.p)) >= 9 )
		goto tr1494;
	goto tr1436;
tr1495:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1048;
st1048:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1048;
case 1048:
#line 23041 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr1497;
	goto tr1436;
tr1497:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1049;
st1049:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1049;
case 1049:
#line 23059 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1494;
		case 32: goto tr1494;
		case 34: goto tr1438;
		case 59: goto tr1496;
		case 92: goto st1016;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1497;
	} else if ( (*( state.p)) >= 9 )
		goto tr1494;
	goto tr1436;
tr1485:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1050;
st1050:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1050;
case 1050:
#line 23083 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 99: goto tr1498;
	}
	goto tr1436;
tr1498:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1051;
st1051:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1051;
case 1051:
#line 23100 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 114: goto tr1499;
	}
	goto tr1436;
tr1499:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1052;
st1052:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1052;
case 1052:
#line 23117 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1500;
		case 32: goto tr1500;
		case 34: goto tr1438;
		case 92: goto st1016;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1500;
	goto tr1436;
tr1500:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1053;
st1053:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1053;
case 1053:
#line 23137 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1500;
		case 32: goto tr1500;
		case 34: goto tr1501;
		case 92: goto st1016;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1500;
	goto tr1436;
tr1501:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1054;
st1054:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1054;
case 1054:
#line 23157 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1502;
		case 32: goto tr1502;
		case 34: goto tr1366;
		case 59: goto tr1503;
		case 92: goto st969;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1502;
	goto tr1365;
tr1458:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1055;
st1055:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1055;
case 1055:
#line 23178 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 97: goto tr1504;
	}
	goto tr1436;
tr1504:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1056;
st1056:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1056;
case 1056:
#line 23195 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 109: goto tr1505;
	}
	goto tr1436;
tr1505:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1057;
st1057:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1057;
case 1057:
#line 23212 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 101: goto tr1506;
	}
	goto tr1436;
tr1506:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1058;
st1058:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1058;
case 1058:
#line 23229 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1507;
		case 32: goto tr1507;
		case 34: goto tr1438;
		case 92: goto st1016;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1507;
	goto tr1436;
tr1507:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1059;
st1059:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1059;
case 1059:
#line 23249 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1507;
		case 32: goto tr1507;
		case 34: goto tr1508;
		case 92: goto st1016;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1507;
	goto tr1436;
tr1508:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1060;
st1060:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1060;
case 1060:
#line 23269 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1509;
		case 32: goto tr1509;
		case 34: goto tr1438;
		case 59: goto tr1510;
		case 92: goto st1016;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1509;
	goto tr1436;
tr1459:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1061;
st1061:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1061;
case 1061:
#line 23290 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 107: goto tr1511;
		case 108: goto tr1512;
	}
	goto tr1436;
tr1511:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1062;
st1062:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1062;
case 1062:
#line 23308 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 105: goto tr1513;
	}
	goto tr1436;
tr1513:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1063;
st1063:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1063;
case 1063:
#line 23325 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 110: goto tr1514;
	}
	goto tr1436;
tr1514:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1064;
st1064:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1064;
case 1064:
#line 23342 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1515;
		case 32: goto tr1515;
		case 34: goto tr1438;
		case 92: goto st1016;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1515;
	goto tr1436;
tr1515:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1065;
st1065:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1065;
case 1065:
#line 23362 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1515;
		case 32: goto tr1515;
		case 34: goto tr1516;
		case 92: goto st1016;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1515;
	goto tr1436;
tr1516:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1066;
st1066:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1066;
case 1066:
#line 23382 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1518;
		case 32: goto tr1518;
		case 34: goto tr1519;
		case 59: goto tr1520;
		case 92: goto st1121;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1518;
	goto tr1517;
tr1517:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1067;
tr1608:
#line 138 "configparser.rl"
	{ state.match += '\\'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1067;
tr1612:
#line 136 "configparser.rl"
	{ state.match += '"'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1067;
tr2119:
#line 137 "configparser.rl"
	{ state.match += '\n'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1067;
st1067:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1067;
case 1067:
#line 23427 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
	}
	goto tr1517;
tr1519:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1068;
tr1614:
#line 136 "configparser.rl"
	{ state.match += '"'; }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1068;
tr2120:
#line 137 "configparser.rl"
	{ state.match += '\n'; }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1068;
st1068:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1068;
case 1068:
#line 23459 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1522;
		case 32: goto tr1522;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1522;
	goto st0;
tr1522:
#line 161 "configparser.rl"
	{ skin.text = state.match; }
	goto st1069;
st1069:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1069;
case 1069:
#line 23475 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st1069;
		case 32: goto st1069;
		case 98: goto st1070;
		case 100: goto st1115;
		case 110: goto st1118;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1069;
	goto st0;
st1070:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1070;
case 1070:
	if ( (*( state.p)) == 114 )
		goto st1071;
	goto st0;
st1071:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1071;
case 1071:
	if ( (*( state.p)) == 105 )
		goto st1072;
	goto st0;
st1072:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1072;
case 1072:
	if ( (*( state.p)) == 103 )
		goto st1073;
	goto st0;
st1073:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1073;
case 1073:
	if ( (*( state.p)) == 104 )
		goto st1074;
	goto st0;
st1074:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1074;
case 1074:
	if ( (*( state.p)) == 116 )
		goto st1075;
	goto st0;
st1075:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1075;
case 1075:
	switch( (*( state.p)) ) {
		case 13: goto tr1532;
		case 32: goto tr1532;
		case 95: goto tr1533;
		case 98: goto tr1534;
		case 99: goto tr1535;
		case 103: goto tr1536;
		case 109: goto tr1537;
		case 114: goto tr1538;
		case 119: goto tr1539;
		case 121: goto tr1540;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1532;
	goto st0;
tr1532:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1076;
tr1597:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1076;
st1076:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1076;
case 1076:
#line 23552 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st1076;
		case 32: goto st1076;
		case 98: goto st1077;
		case 99: goto st1084;
		case 103: goto st1088;
		case 109: goto st1093;
		case 114: goto st1100;
		case 119: goto st1103;
		case 121: goto st1108;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1076;
	goto st0;
tr1534:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1077;
tr1599:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1077;
st1077:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1077;
case 1077:
#line 23579 "configparser.h"
	if ( (*( state.p)) == 108 )
		goto st1078;
	goto st0;
st1078:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1078;
case 1078:
	switch( (*( state.p)) ) {
		case 97: goto st1079;
		case 117: goto st1082;
	}
	goto st0;
st1079:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1079;
case 1079:
	if ( (*( state.p)) == 99 )
		goto st1080;
	goto st0;
st1080:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1080;
case 1080:
	if ( (*( state.p)) == 107 )
		goto st1081;
	goto st0;
st1081:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1081;
case 1081:
	switch( (*( state.p)) ) {
		case 13: goto tr1554;
		case 32: goto tr1554;
		case 59: goto tr1555;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1554;
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
	switch( (*( state.p)) ) {
		case 13: goto tr1557;
		case 32: goto tr1557;
		case 59: goto tr1558;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1557;
	goto st0;
tr1535:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1084;
tr1600:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1084;
st1084:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1084;
case 1084:
#line 23649 "configparser.h"
	if ( (*( state.p)) == 121 )
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
	if ( (*( state.p)) == 110 )
		goto st1087;
	goto st0;
st1087:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1087;
case 1087:
	switch( (*( state.p)) ) {
		case 13: goto tr1562;
		case 32: goto tr1562;
		case 59: goto tr1563;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1562;
	goto st0;
tr1536:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1088;
tr1601:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1088;
st1088:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1088;
case 1088:
#line 23691 "configparser.h"
	if ( (*( state.p)) == 114 )
		goto st1089;
	goto st0;
st1089:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1089;
case 1089:
	if ( (*( state.p)) == 101 )
		goto st1090;
	goto st0;
st1090:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1090;
case 1090:
	if ( (*( state.p)) == 101 )
		goto st1091;
	goto st0;
st1091:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1091;
case 1091:
	if ( (*( state.p)) == 110 )
		goto st1092;
	goto st0;
st1092:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1092;
case 1092:
	switch( (*( state.p)) ) {
		case 13: goto tr1568;
		case 32: goto tr1568;
		case 59: goto tr1569;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1568;
	goto st0;
tr1537:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1093;
tr1602:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1093;
st1093:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1093;
case 1093:
#line 23740 "configparser.h"
	if ( (*( state.p)) == 97 )
		goto st1094;
	goto st0;
st1094:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1094;
case 1094:
	if ( (*( state.p)) == 103 )
		goto st1095;
	goto st0;
st1095:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1095;
case 1095:
	if ( (*( state.p)) == 101 )
		goto st1096;
	goto st0;
st1096:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1096;
case 1096:
	if ( (*( state.p)) == 110 )
		goto st1097;
	goto st0;
st1097:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1097;
case 1097:
	if ( (*( state.p)) == 116 )
		goto st1098;
	goto st0;
st1098:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1098;
case 1098:
	if ( (*( state.p)) == 97 )
		goto st1099;
	goto st0;
st1099:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1099;
case 1099:
	switch( (*( state.p)) ) {
		case 13: goto tr1576;
		case 32: goto tr1576;
		case 59: goto tr1577;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1576;
	goto st0;
tr1538:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1100;
tr1603:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1100;
st1100:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1100;
case 1100:
#line 23803 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st1101;
	goto st0;
st1101:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1101;
case 1101:
	if ( (*( state.p)) == 100 )
		goto st1102;
	goto st0;
st1102:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1102;
case 1102:
	switch( (*( state.p)) ) {
		case 13: goto tr1580;
		case 32: goto tr1580;
		case 59: goto tr1581;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1580;
	goto st0;
tr1539:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1103;
tr1604:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1103;
st1103:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1103;
case 1103:
#line 23838 "configparser.h"
	if ( (*( state.p)) == 104 )
		goto st1104;
	goto st0;
st1104:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1104;
case 1104:
	if ( (*( state.p)) == 105 )
		goto st1105;
	goto st0;
st1105:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1105;
case 1105:
	if ( (*( state.p)) == 116 )
		goto st1106;
	goto st0;
st1106:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1106;
case 1106:
	if ( (*( state.p)) == 101 )
		goto st1107;
	goto st0;
st1107:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1107;
case 1107:
	switch( (*( state.p)) ) {
		case 13: goto tr1586;
		case 32: goto tr1586;
		case 59: goto tr1587;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1586;
	goto st0;
tr1540:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1108;
tr1605:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1108;
st1108:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1108;
case 1108:
#line 23887 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st1109;
	goto st0;
st1109:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1109;
case 1109:
	if ( (*( state.p)) == 108 )
		goto st1110;
	goto st0;
st1110:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1110;
case 1110:
	if ( (*( state.p)) == 108 )
		goto st1111;
	goto st0;
st1111:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1111;
case 1111:
	if ( (*( state.p)) == 111 )
		goto st1112;
	goto st0;
st1112:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1112;
case 1112:
	if ( (*( state.p)) == 119 )
		goto st1113;
	goto st0;
st1113:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1113;
case 1113:
	switch( (*( state.p)) ) {
		case 13: goto tr1593;
		case 32: goto tr1593;
		case 59: goto tr1594;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1593;
	goto st0;
tr1533:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1114;
tr1598:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1114;
st1114:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1114;
case 1114:
#line 23943 "configparser.h"
	switch( (*( state.p)) ) {
		case 98: goto st1077;
		case 99: goto st1084;
		case 103: goto st1088;
		case 109: goto st1093;
		case 114: goto st1100;
		case 119: goto st1103;
		case 121: goto st1108;
	}
	goto st0;
st1115:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1115;
case 1115:
	if ( (*( state.p)) == 105 )
		goto st1116;
	goto st0;
st1116:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1116;
case 1116:
	if ( (*( state.p)) == 109 )
		goto st1117;
	goto st0;
st1117:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1117;
case 1117:
	switch( (*( state.p)) ) {
		case 13: goto tr1597;
		case 32: goto tr1597;
		case 95: goto tr1598;
		case 98: goto tr1599;
		case 99: goto tr1600;
		case 103: goto tr1601;
		case 109: goto tr1602;
		case 114: goto tr1603;
		case 119: goto tr1604;
		case 121: goto tr1605;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1597;
	goto st0;
st1118:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1118;
case 1118:
	if ( (*( state.p)) == 111 )
		goto st1119;
	goto st0;
st1119:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1119;
case 1119:
	if ( (*( state.p)) == 110 )
		goto st1120;
	goto st0;
st1120:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1120;
case 1120:
	if ( (*( state.p)) == 101 )
		goto st1081;
	goto st0;
tr1610:
#line 138 "configparser.rl"
	{ state.match += '\\'; }
	goto st1121;
tr1615:
#line 136 "configparser.rl"
	{ state.match += '"'; }
	goto st1121;
tr2121:
#line 137 "configparser.rl"
	{ state.match += '\n'; }
	goto st1121;
st1121:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1121;
case 1121:
#line 24024 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1609;
		case 92: goto tr1610;
		case 110: goto tr1611;
	}
	goto tr1608;
tr1609:
#line 138 "configparser.rl"
	{ state.match += '\\'; }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1122;
st1122:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1122;
case 1122:
#line 24043 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1613;
		case 32: goto tr1613;
		case 34: goto tr1614;
		case 92: goto tr1615;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1613;
	goto tr1612;
tr1616:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1123;
tr1613:
#line 136 "configparser.rl"
	{ state.match += '"'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 161 "configparser.rl"
	{ skin.text = state.match; }
	goto st1123;
tr1882:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 161 "configparser.rl"
	{ skin.text = state.match; }
	goto st1123;
st1123:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1123;
case 1123:
#line 24081 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1616;
		case 32: goto tr1616;
		case 34: goto tr1519;
		case 92: goto st1121;
		case 98: goto tr1617;
		case 100: goto tr1618;
		case 110: goto tr1619;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1616;
	goto tr1517;
tr1617:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1124;
st1124:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1124;
case 1124:
#line 24104 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 114: goto tr1620;
	}
	goto tr1517;
tr1620:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1125;
st1125:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1125;
case 1125:
#line 24121 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 105: goto tr1621;
	}
	goto tr1517;
tr1621:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1126;
st1126:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1126;
case 1126:
#line 24138 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 103: goto tr1622;
	}
	goto tr1517;
tr1622:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1127;
st1127:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1127;
case 1127:
#line 24155 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 104: goto tr1623;
	}
	goto tr1517;
tr1623:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1128;
st1128:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1128;
case 1128:
#line 24172 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 116: goto tr1624;
	}
	goto tr1517;
tr1624:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1129;
st1129:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1129;
case 1129:
#line 24189 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1625;
		case 32: goto tr1625;
		case 34: goto tr1519;
		case 92: goto st1121;
		case 95: goto tr1626;
		case 98: goto tr1627;
		case 99: goto tr1628;
		case 103: goto tr1629;
		case 109: goto tr1630;
		case 114: goto tr1631;
		case 119: goto tr1632;
		case 121: goto tr1633;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1625;
	goto tr1517;
tr1634:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1130;
tr1625:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1130;
tr2108:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1130;
st1130:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1130;
case 1130:
#line 24233 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1634;
		case 32: goto tr1634;
		case 34: goto tr1519;
		case 92: goto st1121;
		case 98: goto tr1635;
		case 99: goto tr1636;
		case 103: goto tr1637;
		case 109: goto tr1638;
		case 114: goto tr1639;
		case 119: goto tr1640;
		case 121: goto tr1641;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1634;
	goto tr1517;
tr1635:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1131;
tr1627:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1131;
tr2110:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1131;
st1131:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1131;
case 1131:
#line 24276 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 108: goto tr1642;
	}
	goto tr1517;
tr1642:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1132;
st1132:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1132;
case 1132:
#line 24293 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 97: goto tr1643;
		case 117: goto tr1644;
	}
	goto tr1517;
tr1643:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1133;
st1133:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1133;
case 1133:
#line 24311 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 99: goto tr1645;
	}
	goto tr1517;
tr1645:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1134;
st1134:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1134;
case 1134:
#line 24328 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 107: goto tr1646;
	}
	goto tr1517;
tr1646:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1135;
st1135:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1135;
case 1135:
#line 24345 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1647;
		case 32: goto tr1647;
		case 34: goto tr1519;
		case 59: goto tr1648;
		case 92: goto st1121;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1647;
	goto tr1517;
tr1649:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1136;
tr1667:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 237 "configparser.rl"
	{ des.attack = ::atof(state.match.c_str()); }
	goto st1136;
tr1677:
#line 232 "configparser.rl"
	{ des.count = ::atoi(state.match.c_str()); }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1136;
tr1691:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 238 "configparser.rl"
	{ des.defense = ::atof(state.match.c_str()); }
	goto st1136;
tr2139:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 236 "configparser.rl"
	{ des.descr = state.match; }
	goto st1136;
tr1518:
#line 233 "configparser.rl"
	{ des.name = state.match; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1136;
tr1647:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1136;
tr2068:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 151 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1136;
tr2073:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 153 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1136;
tr2079:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 149 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1136;
tr2087:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 152 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1136;
tr2091:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 148 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1136;
tr2097:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 154 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1136;
tr2104:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 150 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1136;
tr1967:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 235 "configparser.rl"
	{ des.slot = state.match; }
	goto st1136;
tr2065:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 244 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st1136;
st1136:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1136;
case 1136:
#line 24500 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1649;
		case 32: goto tr1649;
		case 34: goto tr1519;
		case 59: goto tr1650;
		case 92: goto st1121;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1649;
	goto tr1517;
tr1650:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1494;
tr1669:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 237 "configparser.rl"
	{ des.attack = ::atof(state.match.c_str()); }
	goto st1494;
tr1679:
#line 232 "configparser.rl"
	{ des.count = ::atoi(state.match.c_str()); }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1494;
tr1693:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 238 "configparser.rl"
	{ des.defense = ::atof(state.match.c_str()); }
	goto st1494;
tr2140:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 236 "configparser.rl"
	{ des.descr = state.match; }
	goto st1494;
tr1520:
#line 233 "configparser.rl"
	{ des.name = state.match; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1494;
tr1648:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1494;
tr2069:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 151 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1494;
tr2074:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 153 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1494;
tr2080:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 149 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1494;
tr2088:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 152 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1494;
tr2092:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 148 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1494;
tr2098:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 154 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1494;
tr2105:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 150 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
	goto st1494;
tr1968:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 235 "configparser.rl"
	{ des.slot = state.match; }
	goto st1494;
tr2066:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 244 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st1494;
st1494:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1494;
case 1494:
#line 24655 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1651;
		case 32: goto tr1651;
		case 34: goto tr1519;
		case 92: goto st1121;
		case 97: goto tr1652;
		case 99: goto tr1653;
		case 100: goto tr1654;
		case 110: goto tr1655;
		case 115: goto tr1656;
		case 125: goto tr1657;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1651;
	goto tr1517;
tr1651:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1137;
st1137:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1137;
case 1137:
#line 24681 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1651;
		case 32: goto tr1651;
		case 34: goto tr1519;
		case 92: goto st1121;
		case 97: goto tr1652;
		case 99: goto tr1653;
		case 100: goto tr1654;
		case 110: goto tr1655;
		case 115: goto tr1656;
		case 125: goto tr1657;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1651;
	goto tr1517;
tr1652:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1138;
st1138:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1138;
case 1138:
#line 24707 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 116: goto tr1658;
	}
	goto tr1517;
tr1658:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1139;
st1139:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1139;
case 1139:
#line 24724 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 116: goto tr1659;
	}
	goto tr1517;
tr1659:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1140;
st1140:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1140;
case 1140:
#line 24741 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 97: goto tr1660;
	}
	goto tr1517;
tr1660:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1141;
st1141:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1141;
case 1141:
#line 24758 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 99: goto tr1661;
	}
	goto tr1517;
tr1661:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1142;
st1142:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1142;
case 1142:
#line 24775 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 107: goto tr1662;
	}
	goto tr1517;
tr1662:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1143;
st1143:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1143;
case 1143:
#line 24792 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1663;
		case 32: goto tr1663;
		case 34: goto tr1519;
		case 92: goto st1121;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1663;
	goto tr1517;
tr1663:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1144;
st1144:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1144;
case 1144:
#line 24812 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1663;
		case 32: goto tr1663;
		case 34: goto tr1519;
		case 45: goto tr1664;
		case 92: goto st1121;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1665;
	} else if ( (*( state.p)) >= 9 )
		goto tr1663;
	goto tr1517;
tr1664:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1145;
st1145:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1145;
case 1145:
#line 24840 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr1666;
	goto tr1517;
tr1666:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1146;
tr1665:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1146;
st1146:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1146;
case 1146:
#line 24868 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1667;
		case 32: goto tr1667;
		case 34: goto tr1519;
		case 46: goto tr1668;
		case 59: goto tr1669;
		case 92: goto st1121;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1666;
	} else if ( (*( state.p)) >= 9 )
		goto tr1667;
	goto tr1517;
tr1668:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1147;
st1147:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1147;
case 1147:
#line 24893 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr1670;
	goto tr1517;
tr1670:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1148;
st1148:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1148;
case 1148:
#line 24911 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1667;
		case 32: goto tr1667;
		case 34: goto tr1519;
		case 59: goto tr1669;
		case 92: goto st1121;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1670;
	} else if ( (*( state.p)) >= 9 )
		goto tr1667;
	goto tr1517;
tr1653:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1149;
st1149:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1149;
case 1149:
#line 24935 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 111: goto tr1671;
	}
	goto tr1517;
tr1671:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1150;
st1150:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1150;
case 1150:
#line 24952 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 117: goto tr1672;
	}
	goto tr1517;
tr1672:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1151;
st1151:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1151;
case 1151:
#line 24969 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 110: goto tr1673;
	}
	goto tr1517;
tr1673:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1152;
st1152:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1152;
case 1152:
#line 24986 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 116: goto tr1674;
	}
	goto tr1517;
tr1674:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1153;
st1153:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1153;
case 1153:
#line 25003 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1675;
		case 32: goto tr1675;
		case 34: goto tr1519;
		case 92: goto st1121;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1675;
	goto tr1517;
tr1675:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1154;
st1154:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1154;
case 1154:
#line 25023 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1675;
		case 32: goto tr1675;
		case 34: goto tr1519;
		case 92: goto st1121;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1676;
	} else if ( (*( state.p)) >= 9 )
		goto tr1675;
	goto tr1517;
tr1676:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1155;
tr1678:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1155;
st1155:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1155;
case 1155:
#line 25056 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1677;
		case 32: goto tr1677;
		case 34: goto tr1519;
		case 59: goto tr1679;
		case 92: goto st1121;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1678;
	} else if ( (*( state.p)) >= 9 )
		goto tr1677;
	goto tr1517;
tr1654:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1156;
st1156:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1156;
case 1156:
#line 25080 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 101: goto tr1680;
	}
	goto tr1517;
tr1680:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1157;
st1157:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1157;
case 1157:
#line 25097 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 102: goto tr1681;
		case 115: goto tr1682;
	}
	goto tr1517;
tr1681:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1158;
st1158:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1158;
case 1158:
#line 25115 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 101: goto tr1683;
	}
	goto tr1517;
tr1683:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1159;
st1159:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1159;
case 1159:
#line 25132 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 110: goto tr1684;
	}
	goto tr1517;
tr1684:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1160;
st1160:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1160;
case 1160:
#line 25149 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 115: goto tr1685;
	}
	goto tr1517;
tr1685:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1161;
st1161:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1161;
case 1161:
#line 25166 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 101: goto tr1686;
	}
	goto tr1517;
tr1686:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1162;
st1162:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1162;
case 1162:
#line 25183 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1687;
		case 32: goto tr1687;
		case 34: goto tr1519;
		case 92: goto st1121;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1687;
	goto tr1517;
tr1687:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1163;
st1163:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1163;
case 1163:
#line 25203 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1687;
		case 32: goto tr1687;
		case 34: goto tr1519;
		case 45: goto tr1688;
		case 92: goto st1121;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1689;
	} else if ( (*( state.p)) >= 9 )
		goto tr1687;
	goto tr1517;
tr1688:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1164;
st1164:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1164;
case 1164:
#line 25231 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr1690;
	goto tr1517;
tr1690:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1165;
tr1689:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1165;
st1165:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1165;
case 1165:
#line 25259 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1691;
		case 32: goto tr1691;
		case 34: goto tr1519;
		case 46: goto tr1692;
		case 59: goto tr1693;
		case 92: goto st1121;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1690;
	} else if ( (*( state.p)) >= 9 )
		goto tr1691;
	goto tr1517;
tr1692:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1166;
st1166:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1166;
case 1166:
#line 25284 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr1694;
	goto tr1517;
tr1694:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1167;
st1167:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1167;
case 1167:
#line 25302 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1691;
		case 32: goto tr1691;
		case 34: goto tr1519;
		case 59: goto tr1693;
		case 92: goto st1121;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1694;
	} else if ( (*( state.p)) >= 9 )
		goto tr1691;
	goto tr1517;
tr1682:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1168;
st1168:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1168;
case 1168:
#line 25326 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 99: goto tr1695;
	}
	goto tr1517;
tr1695:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1169;
st1169:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1169;
case 1169:
#line 25343 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 114: goto tr1696;
	}
	goto tr1517;
tr1696:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1170;
st1170:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1170;
case 1170:
#line 25360 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1697;
		case 32: goto tr1697;
		case 34: goto tr1519;
		case 92: goto st1121;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1697;
	goto tr1517;
tr1697:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1171;
st1171:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1171;
case 1171:
#line 25380 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1697;
		case 32: goto tr1697;
		case 34: goto tr1698;
		case 92: goto st1121;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1697;
	goto tr1517;
tr1698:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1172;
st1172:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1172;
case 1172:
#line 25400 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1699;
		case 32: goto tr1699;
		case 34: goto tr1366;
		case 92: goto st969;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1699;
	goto tr1365;
tr1700:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1173;
tr1699:
#line 161 "configparser.rl"
	{ skin.text = state.match; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1173;
st1173:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1173;
case 1173:
#line 25428 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1700;
		case 32: goto tr1700;
		case 34: goto tr1366;
		case 92: goto st969;
		case 98: goto tr1701;
		case 100: goto tr1702;
		case 110: goto tr1703;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1700;
	goto tr1365;
tr1701:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1174;
st1174:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1174;
case 1174:
#line 25451 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 114: goto tr1704;
	}
	goto tr1365;
tr1704:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1175;
st1175:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1175;
case 1175:
#line 25468 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 105: goto tr1705;
	}
	goto tr1365;
tr1705:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1176;
st1176:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1176;
case 1176:
#line 25485 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 103: goto tr1706;
	}
	goto tr1365;
tr1706:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1177;
st1177:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1177;
case 1177:
#line 25502 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 104: goto tr1707;
	}
	goto tr1365;
tr1707:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1178;
st1178:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1178;
case 1178:
#line 25519 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 116: goto tr1708;
	}
	goto tr1365;
tr1708:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1179;
st1179:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1179;
case 1179:
#line 25536 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1709;
		case 32: goto tr1709;
		case 34: goto tr1366;
		case 92: goto st969;
		case 95: goto tr1710;
		case 98: goto tr1711;
		case 99: goto tr1712;
		case 103: goto tr1713;
		case 109: goto tr1714;
		case 114: goto tr1715;
		case 119: goto tr1716;
		case 121: goto tr1717;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1709;
	goto tr1365;
tr1718:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1180;
tr1709:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1180;
tr1774:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1180;
st1180:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1180;
case 1180:
#line 25580 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1718;
		case 32: goto tr1718;
		case 34: goto tr1366;
		case 92: goto st969;
		case 98: goto tr1719;
		case 99: goto tr1720;
		case 103: goto tr1721;
		case 109: goto tr1722;
		case 114: goto tr1723;
		case 119: goto tr1724;
		case 121: goto tr1725;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1718;
	goto tr1365;
tr1719:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1181;
tr1711:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1181;
tr1776:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1181;
st1181:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1181;
case 1181:
#line 25623 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 108: goto tr1726;
	}
	goto tr1365;
tr1726:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1182;
st1182:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1182;
case 1182:
#line 25640 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 97: goto tr1727;
		case 117: goto tr1728;
	}
	goto tr1365;
tr1727:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1183;
st1183:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1183;
case 1183:
#line 25658 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 99: goto tr1729;
	}
	goto tr1365;
tr1729:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1184;
st1184:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1184;
case 1184:
#line 25675 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 107: goto tr1730;
	}
	goto tr1365;
tr1730:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1185;
st1185:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1185;
case 1185:
#line 25692 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1731;
		case 32: goto tr1731;
		case 34: goto tr1366;
		case 59: goto tr1732;
		case 92: goto st969;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1731;
	goto tr1365;
tr1728:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1186;
st1186:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1186;
case 1186:
#line 25713 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 101: goto tr1733;
	}
	goto tr1365;
tr1733:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1187;
st1187:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1187;
case 1187:
#line 25730 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1734;
		case 32: goto tr1734;
		case 34: goto tr1366;
		case 59: goto tr1735;
		case 92: goto st969;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1734;
	goto tr1365;
tr1720:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1188;
tr1712:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1188;
tr1777:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1188;
st1188:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1188;
case 1188:
#line 25767 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 121: goto tr1736;
	}
	goto tr1365;
tr1736:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1189;
st1189:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1189;
case 1189:
#line 25784 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 97: goto tr1737;
	}
	goto tr1365;
tr1737:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1190;
st1190:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1190;
case 1190:
#line 25801 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 110: goto tr1738;
	}
	goto tr1365;
tr1738:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1191;
st1191:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1191;
case 1191:
#line 25818 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1739;
		case 32: goto tr1739;
		case 34: goto tr1366;
		case 59: goto tr1740;
		case 92: goto st969;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1739;
	goto tr1365;
tr1721:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1192;
tr1713:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1192;
tr1778:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1192;
st1192:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1192;
case 1192:
#line 25855 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 114: goto tr1741;
	}
	goto tr1365;
tr1741:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1193;
st1193:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1193;
case 1193:
#line 25872 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 101: goto tr1742;
	}
	goto tr1365;
tr1742:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1194;
st1194:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1194;
case 1194:
#line 25889 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 101: goto tr1743;
	}
	goto tr1365;
tr1743:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1195;
st1195:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1195;
case 1195:
#line 25906 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 110: goto tr1744;
	}
	goto tr1365;
tr1744:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1196;
st1196:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1196;
case 1196:
#line 25923 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1745;
		case 32: goto tr1745;
		case 34: goto tr1366;
		case 59: goto tr1746;
		case 92: goto st969;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1745;
	goto tr1365;
tr1722:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1197;
tr1714:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1197;
tr1779:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1197;
st1197:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1197;
case 1197:
#line 25960 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 97: goto tr1747;
	}
	goto tr1365;
tr1747:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1198;
st1198:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1198;
case 1198:
#line 25977 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 103: goto tr1748;
	}
	goto tr1365;
tr1748:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1199;
st1199:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1199;
case 1199:
#line 25994 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 101: goto tr1749;
	}
	goto tr1365;
tr1749:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1200;
st1200:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1200;
case 1200:
#line 26011 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 110: goto tr1750;
	}
	goto tr1365;
tr1750:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1201;
st1201:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1201;
case 1201:
#line 26028 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 116: goto tr1751;
	}
	goto tr1365;
tr1751:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1202;
st1202:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1202;
case 1202:
#line 26045 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 97: goto tr1752;
	}
	goto tr1365;
tr1752:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1203;
st1203:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1203;
case 1203:
#line 26062 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1753;
		case 32: goto tr1753;
		case 34: goto tr1366;
		case 59: goto tr1754;
		case 92: goto st969;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1753;
	goto tr1365;
tr1723:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1204;
tr1715:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1204;
tr1780:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1204;
st1204:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1204;
case 1204:
#line 26099 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 101: goto tr1755;
	}
	goto tr1365;
tr1755:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1205;
st1205:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1205;
case 1205:
#line 26116 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 100: goto tr1756;
	}
	goto tr1365;
tr1756:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1206;
st1206:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1206;
case 1206:
#line 26133 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1757;
		case 32: goto tr1757;
		case 34: goto tr1366;
		case 59: goto tr1758;
		case 92: goto st969;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1757;
	goto tr1365;
tr1724:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1207;
tr1716:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1207;
tr1781:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1207;
st1207:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1207;
case 1207:
#line 26170 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 104: goto tr1759;
	}
	goto tr1365;
tr1759:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1208;
st1208:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1208;
case 1208:
#line 26187 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 105: goto tr1760;
	}
	goto tr1365;
tr1760:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1209;
st1209:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1209;
case 1209:
#line 26204 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 116: goto tr1761;
	}
	goto tr1365;
tr1761:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1210;
st1210:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1210;
case 1210:
#line 26221 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 101: goto tr1762;
	}
	goto tr1365;
tr1762:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1211;
st1211:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1211;
case 1211:
#line 26238 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1763;
		case 32: goto tr1763;
		case 34: goto tr1366;
		case 59: goto tr1764;
		case 92: goto st969;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1763;
	goto tr1365;
tr1725:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1212;
tr1717:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1212;
tr1782:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1212;
st1212:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1212;
case 1212:
#line 26275 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 101: goto tr1765;
	}
	goto tr1365;
tr1765:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1213;
st1213:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1213;
case 1213:
#line 26292 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 108: goto tr1766;
	}
	goto tr1365;
tr1766:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1214;
st1214:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1214;
case 1214:
#line 26309 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 108: goto tr1767;
	}
	goto tr1365;
tr1767:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1215;
st1215:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1215;
case 1215:
#line 26326 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 111: goto tr1768;
	}
	goto tr1365;
tr1768:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1216;
st1216:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1216;
case 1216:
#line 26343 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 119: goto tr1769;
	}
	goto tr1365;
tr1769:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1217;
st1217:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1217;
case 1217:
#line 26360 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1770;
		case 32: goto tr1770;
		case 34: goto tr1366;
		case 59: goto tr1771;
		case 92: goto st969;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1770;
	goto tr1365;
tr1710:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1218;
tr1775:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1218;
st1218:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1218;
case 1218:
#line 26391 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 98: goto tr1719;
		case 99: goto tr1720;
		case 103: goto tr1721;
		case 109: goto tr1722;
		case 114: goto tr1723;
		case 119: goto tr1724;
		case 121: goto tr1725;
	}
	goto tr1365;
tr1702:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1219;
st1219:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1219;
case 1219:
#line 26414 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 105: goto tr1772;
	}
	goto tr1365;
tr1772:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1220;
st1220:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1220;
case 1220:
#line 26431 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 109: goto tr1773;
	}
	goto tr1365;
tr1773:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1221;
st1221:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1221;
case 1221:
#line 26448 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1774;
		case 32: goto tr1774;
		case 34: goto tr1366;
		case 92: goto st969;
		case 95: goto tr1775;
		case 98: goto tr1776;
		case 99: goto tr1777;
		case 103: goto tr1778;
		case 109: goto tr1779;
		case 114: goto tr1780;
		case 119: goto tr1781;
		case 121: goto tr1782;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1774;
	goto tr1365;
tr1703:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1222;
st1222:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1222;
case 1222:
#line 26476 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 111: goto tr1783;
	}
	goto tr1365;
tr1783:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1223;
st1223:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1223;
case 1223:
#line 26493 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 110: goto tr1784;
	}
	goto tr1365;
tr1784:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1224;
st1224:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1224;
case 1224:
#line 26510 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 101: goto tr1730;
	}
	goto tr1365;
tr1655:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1225;
st1225:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1225;
case 1225:
#line 26527 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 97: goto tr1785;
	}
	goto tr1517;
tr1785:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1226;
st1226:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1226;
case 1226:
#line 26544 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 109: goto tr1786;
	}
	goto tr1517;
tr1786:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1227;
st1227:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1227;
case 1227:
#line 26561 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 101: goto tr1787;
	}
	goto tr1517;
tr1787:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1228;
st1228:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1228;
case 1228:
#line 26578 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1788;
		case 32: goto tr1788;
		case 34: goto tr1519;
		case 92: goto st1121;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1788;
	goto tr1517;
tr1788:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1229;
st1229:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1229;
case 1229:
#line 26598 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1788;
		case 32: goto tr1788;
		case 34: goto tr1789;
		case 92: goto st1121;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1788;
	goto tr1517;
tr1789:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1230;
st1230:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1230;
case 1230:
#line 26618 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1790;
		case 32: goto tr1790;
		case 34: goto tr1438;
		case 92: goto st1016;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1790;
	goto tr1436;
tr1791:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1231;
tr1790:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 161 "configparser.rl"
	{ skin.text = state.match; }
	goto st1231;
st1231:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1231;
case 1231:
#line 26646 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1791;
		case 32: goto tr1791;
		case 34: goto tr1438;
		case 92: goto st1016;
		case 98: goto tr1792;
		case 100: goto tr1793;
		case 110: goto tr1794;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1791;
	goto tr1436;
tr1792:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1232;
st1232:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1232;
case 1232:
#line 26669 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 114: goto tr1795;
	}
	goto tr1436;
tr1795:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1233;
st1233:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1233;
case 1233:
#line 26686 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 105: goto tr1796;
	}
	goto tr1436;
tr1796:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1234;
st1234:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1234;
case 1234:
#line 26703 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 103: goto tr1797;
	}
	goto tr1436;
tr1797:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1235;
st1235:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1235;
case 1235:
#line 26720 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 104: goto tr1798;
	}
	goto tr1436;
tr1798:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1236;
st1236:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1236;
case 1236:
#line 26737 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 116: goto tr1799;
	}
	goto tr1436;
tr1799:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1237;
st1237:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1237;
case 1237:
#line 26754 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1800;
		case 32: goto tr1800;
		case 34: goto tr1438;
		case 92: goto st1016;
		case 95: goto tr1801;
		case 98: goto tr1802;
		case 99: goto tr1803;
		case 103: goto tr1804;
		case 109: goto tr1805;
		case 114: goto tr1806;
		case 119: goto tr1807;
		case 121: goto tr1808;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1800;
	goto tr1436;
tr1809:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1238;
tr1800:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1238;
tr1865:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1238;
st1238:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1238;
case 1238:
#line 26798 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1809;
		case 32: goto tr1809;
		case 34: goto tr1438;
		case 92: goto st1016;
		case 98: goto tr1810;
		case 99: goto tr1811;
		case 103: goto tr1812;
		case 109: goto tr1813;
		case 114: goto tr1814;
		case 119: goto tr1815;
		case 121: goto tr1816;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1809;
	goto tr1436;
tr1810:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1239;
tr1802:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1239;
tr1867:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1239;
st1239:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1239;
case 1239:
#line 26841 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 108: goto tr1817;
	}
	goto tr1436;
tr1817:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1240;
st1240:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1240;
case 1240:
#line 26858 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 97: goto tr1818;
		case 117: goto tr1819;
	}
	goto tr1436;
tr1818:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1241;
st1241:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1241;
case 1241:
#line 26876 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 99: goto tr1820;
	}
	goto tr1436;
tr1820:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1242;
st1242:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1242;
case 1242:
#line 26893 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 107: goto tr1821;
	}
	goto tr1436;
tr1821:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1243;
st1243:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1243;
case 1243:
#line 26910 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1822;
		case 32: goto tr1822;
		case 34: goto tr1438;
		case 59: goto tr1823;
		case 92: goto st1016;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1822;
	goto tr1436;
tr1819:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1244;
st1244:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1244;
case 1244:
#line 26931 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 101: goto tr1824;
	}
	goto tr1436;
tr1824:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1245;
st1245:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1245;
case 1245:
#line 26948 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1825;
		case 32: goto tr1825;
		case 34: goto tr1438;
		case 59: goto tr1826;
		case 92: goto st1016;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1825;
	goto tr1436;
tr1811:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1246;
tr1803:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1246;
tr1868:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1246;
st1246:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1246;
case 1246:
#line 26985 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 121: goto tr1827;
	}
	goto tr1436;
tr1827:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1247;
st1247:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1247;
case 1247:
#line 27002 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 97: goto tr1828;
	}
	goto tr1436;
tr1828:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1248;
st1248:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1248;
case 1248:
#line 27019 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 110: goto tr1829;
	}
	goto tr1436;
tr1829:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1249;
st1249:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1249;
case 1249:
#line 27036 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1830;
		case 32: goto tr1830;
		case 34: goto tr1438;
		case 59: goto tr1831;
		case 92: goto st1016;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1830;
	goto tr1436;
tr1812:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1250;
tr1804:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1250;
tr1869:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1250;
st1250:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1250;
case 1250:
#line 27073 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 114: goto tr1832;
	}
	goto tr1436;
tr1832:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1251;
st1251:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1251;
case 1251:
#line 27090 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 101: goto tr1833;
	}
	goto tr1436;
tr1833:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1252;
st1252:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1252;
case 1252:
#line 27107 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 101: goto tr1834;
	}
	goto tr1436;
tr1834:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1253;
st1253:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1253;
case 1253:
#line 27124 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 110: goto tr1835;
	}
	goto tr1436;
tr1835:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1254;
st1254:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1254;
case 1254:
#line 27141 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1836;
		case 32: goto tr1836;
		case 34: goto tr1438;
		case 59: goto tr1837;
		case 92: goto st1016;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1836;
	goto tr1436;
tr1813:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1255;
tr1805:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1255;
tr1870:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1255;
st1255:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1255;
case 1255:
#line 27178 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 97: goto tr1838;
	}
	goto tr1436;
tr1838:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1256;
st1256:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1256;
case 1256:
#line 27195 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 103: goto tr1839;
	}
	goto tr1436;
tr1839:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1257;
st1257:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1257;
case 1257:
#line 27212 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 101: goto tr1840;
	}
	goto tr1436;
tr1840:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1258;
st1258:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1258;
case 1258:
#line 27229 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 110: goto tr1841;
	}
	goto tr1436;
tr1841:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1259;
st1259:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1259;
case 1259:
#line 27246 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 116: goto tr1842;
	}
	goto tr1436;
tr1842:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1260;
st1260:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1260;
case 1260:
#line 27263 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 97: goto tr1843;
	}
	goto tr1436;
tr1843:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1261;
st1261:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1261;
case 1261:
#line 27280 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1844;
		case 32: goto tr1844;
		case 34: goto tr1438;
		case 59: goto tr1845;
		case 92: goto st1016;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1844;
	goto tr1436;
tr1814:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1262;
tr1806:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1262;
tr1871:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1262;
st1262:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1262;
case 1262:
#line 27317 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 101: goto tr1846;
	}
	goto tr1436;
tr1846:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1263;
st1263:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1263;
case 1263:
#line 27334 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 100: goto tr1847;
	}
	goto tr1436;
tr1847:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1264;
st1264:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1264;
case 1264:
#line 27351 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1848;
		case 32: goto tr1848;
		case 34: goto tr1438;
		case 59: goto tr1849;
		case 92: goto st1016;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1848;
	goto tr1436;
tr1815:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1265;
tr1807:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1265;
tr1872:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1265;
st1265:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1265;
case 1265:
#line 27388 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 104: goto tr1850;
	}
	goto tr1436;
tr1850:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1266;
st1266:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1266;
case 1266:
#line 27405 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 105: goto tr1851;
	}
	goto tr1436;
tr1851:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1267;
st1267:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1267;
case 1267:
#line 27422 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 116: goto tr1852;
	}
	goto tr1436;
tr1852:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1268;
st1268:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1268;
case 1268:
#line 27439 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 101: goto tr1853;
	}
	goto tr1436;
tr1853:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1269;
st1269:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1269;
case 1269:
#line 27456 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1854;
		case 32: goto tr1854;
		case 34: goto tr1438;
		case 59: goto tr1855;
		case 92: goto st1016;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1854;
	goto tr1436;
tr1816:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1270;
tr1808:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1270;
tr1873:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1270;
st1270:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1270;
case 1270:
#line 27493 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 101: goto tr1856;
	}
	goto tr1436;
tr1856:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1271;
st1271:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1271;
case 1271:
#line 27510 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 108: goto tr1857;
	}
	goto tr1436;
tr1857:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1272;
st1272:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1272;
case 1272:
#line 27527 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 108: goto tr1858;
	}
	goto tr1436;
tr1858:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1273;
st1273:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1273;
case 1273:
#line 27544 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 111: goto tr1859;
	}
	goto tr1436;
tr1859:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1274;
st1274:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1274;
case 1274:
#line 27561 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 119: goto tr1860;
	}
	goto tr1436;
tr1860:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1275;
st1275:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1275;
case 1275:
#line 27578 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1861;
		case 32: goto tr1861;
		case 34: goto tr1438;
		case 59: goto tr1862;
		case 92: goto st1016;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1861;
	goto tr1436;
tr1801:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1276;
tr1866:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1276;
st1276:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1276;
case 1276:
#line 27609 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 98: goto tr1810;
		case 99: goto tr1811;
		case 103: goto tr1812;
		case 109: goto tr1813;
		case 114: goto tr1814;
		case 119: goto tr1815;
		case 121: goto tr1816;
	}
	goto tr1436;
tr1793:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1277;
st1277:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1277;
case 1277:
#line 27632 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 105: goto tr1863;
	}
	goto tr1436;
tr1863:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1278;
st1278:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1278;
case 1278:
#line 27649 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 109: goto tr1864;
	}
	goto tr1436;
tr1864:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1279;
st1279:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1279;
case 1279:
#line 27666 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1865;
		case 32: goto tr1865;
		case 34: goto tr1438;
		case 92: goto st1016;
		case 95: goto tr1866;
		case 98: goto tr1867;
		case 99: goto tr1868;
		case 103: goto tr1869;
		case 109: goto tr1870;
		case 114: goto tr1871;
		case 119: goto tr1872;
		case 121: goto tr1873;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1865;
	goto tr1436;
tr1794:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1280;
st1280:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1280;
case 1280:
#line 27694 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 111: goto tr1874;
	}
	goto tr1436;
tr1874:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1281;
st1281:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1281;
case 1281:
#line 27711 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 110: goto tr1875;
	}
	goto tr1436;
tr1875:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1282;
st1282:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1282;
case 1282:
#line 27728 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 101: goto tr1821;
	}
	goto tr1436;
tr1656:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1283;
st1283:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1283;
case 1283:
#line 27745 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 107: goto tr1876;
		case 108: goto tr1877;
	}
	goto tr1517;
tr1876:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1284;
st1284:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1284;
case 1284:
#line 27763 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 105: goto tr1878;
	}
	goto tr1517;
tr1878:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1285;
st1285:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1285;
case 1285:
#line 27780 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 110: goto tr1879;
	}
	goto tr1517;
tr1879:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1286;
st1286:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1286;
case 1286:
#line 27797 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1880;
		case 32: goto tr1880;
		case 34: goto tr1519;
		case 92: goto st1121;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1880;
	goto tr1517;
tr1880:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1287;
st1287:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1287;
case 1287:
#line 27817 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1880;
		case 32: goto tr1880;
		case 34: goto tr1881;
		case 92: goto st1121;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1880;
	goto tr1517;
tr1881:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1288;
st1288:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1288;
case 1288:
#line 27837 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1882;
		case 32: goto tr1882;
		case 34: goto tr1519;
		case 92: goto st1121;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1882;
	goto tr1517;
tr1877:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1289;
st1289:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1289;
case 1289:
#line 27857 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 111: goto tr1883;
	}
	goto tr1517;
tr1883:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1290;
st1290:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1290;
case 1290:
#line 27874 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 116: goto tr1884;
	}
	goto tr1517;
tr1884:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1291;
st1291:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1291;
case 1291:
#line 27891 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1885;
		case 32: goto tr1885;
		case 34: goto tr1519;
		case 92: goto st1121;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1885;
	goto tr1517;
tr1885:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1292;
st1292:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1292;
case 1292:
#line 27911 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1885;
		case 32: goto tr1885;
		case 34: goto tr1886;
		case 92: goto st1121;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1885;
	goto tr1517;
tr1886:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1293;
st1293:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1293;
case 1293:
#line 27931 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1888;
		case 32: goto tr1888;
		case 34: goto tr1889;
		case 92: goto st1296;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1888;
	goto tr1887;
tr1887:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1294;
tr1893:
#line 138 "configparser.rl"
	{ state.match += '\\'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1294;
tr1897:
#line 136 "configparser.rl"
	{ state.match += '"'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1294;
tr1977:
#line 137 "configparser.rl"
	{ state.match += '\n'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1294;
st1294:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1294;
case 1294:
#line 27975 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
	}
	goto tr1887;
tr1889:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1295;
tr1899:
#line 136 "configparser.rl"
	{ state.match += '"'; }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1295;
tr1978:
#line 137 "configparser.rl"
	{ state.match += '\n'; }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1295;
st1295:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1295;
case 1295:
#line 28007 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1891;
		case 32: goto tr1891;
		case 59: goto tr1892;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1891;
	goto st0;
tr1895:
#line 138 "configparser.rl"
	{ state.match += '\\'; }
	goto st1296;
tr1901:
#line 136 "configparser.rl"
	{ state.match += '"'; }
	goto st1296;
tr1979:
#line 137 "configparser.rl"
	{ state.match += '\n'; }
	goto st1296;
st1296:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1296;
case 1296:
#line 28032 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1894;
		case 92: goto tr1895;
		case 110: goto tr1896;
	}
	goto tr1893;
tr1894:
#line 138 "configparser.rl"
	{ state.match += '\\'; }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1297;
st1297:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1297;
case 1297:
#line 28051 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1898;
		case 32: goto tr1898;
		case 34: goto tr1899;
		case 59: goto tr1900;
		case 92: goto tr1901;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1898;
	goto tr1897;
tr1902:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1298;
tr1920:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 237 "configparser.rl"
	{ des.attack = ::atof(state.match.c_str()); }
	goto st1298;
tr1930:
#line 232 "configparser.rl"
	{ des.count = ::atoi(state.match.c_str()); }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1298;
tr1944:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 238 "configparser.rl"
	{ des.defense = ::atof(state.match.c_str()); }
	goto st1298;
tr2145:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 236 "configparser.rl"
	{ des.descr = state.match; }
	goto st1298;
tr2126:
#line 233 "configparser.rl"
	{ des.name = state.match; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1298;
tr2011:
#line 234 "configparser.rl"
	{ des.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1298;
tr2014:
#line 151 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1298;
tr2019:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1298;
tr2025:
#line 149 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1298;
tr2033:
#line 152 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1298;
tr2037:
#line 148 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1298;
tr2043:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1298;
tr2050:
#line 150 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1298;
tr1898:
#line 136 "configparser.rl"
	{ state.match += '"'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 235 "configparser.rl"
	{ des.slot = state.match; }
	goto st1298;
tr1973:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 235 "configparser.rl"
	{ des.slot = state.match; }
	goto st1298;
tr1975:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 244 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st1298;
st1298:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1298;
case 1298:
#line 28216 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1902;
		case 32: goto tr1902;
		case 34: goto tr1889;
		case 59: goto tr1903;
		case 92: goto st1296;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1902;
	goto tr1887;
tr1903:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1495;
tr1922:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 237 "configparser.rl"
	{ des.attack = ::atof(state.match.c_str()); }
	goto st1495;
tr1932:
#line 232 "configparser.rl"
	{ des.count = ::atoi(state.match.c_str()); }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1495;
tr1946:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 238 "configparser.rl"
	{ des.defense = ::atof(state.match.c_str()); }
	goto st1495;
tr2146:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 236 "configparser.rl"
	{ des.descr = state.match; }
	goto st1495;
tr2127:
#line 233 "configparser.rl"
	{ des.name = state.match; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1495;
tr2012:
#line 234 "configparser.rl"
	{ des.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1495;
tr2015:
#line 151 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1495;
tr2020:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1495;
tr2026:
#line 149 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1495;
tr2034:
#line 152 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1495;
tr2038:
#line 148 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1495;
tr2044:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1495;
tr2051:
#line 150 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 234 "configparser.rl"
	{ des.skin = skin; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1495;
tr1900:
#line 136 "configparser.rl"
	{ state.match += '"'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 235 "configparser.rl"
	{ des.slot = state.match; }
	goto st1495;
tr1974:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 235 "configparser.rl"
	{ des.slot = state.match; }
	goto st1495;
tr1976:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 244 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st1495;
st1495:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1495;
case 1495:
#line 28381 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1904;
		case 32: goto tr1904;
		case 34: goto tr1889;
		case 92: goto st1296;
		case 97: goto tr1905;
		case 99: goto tr1906;
		case 100: goto tr1907;
		case 110: goto tr1908;
		case 115: goto tr1909;
		case 125: goto tr1910;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1904;
	goto tr1887;
tr1904:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1299;
st1299:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1299;
case 1299:
#line 28407 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1904;
		case 32: goto tr1904;
		case 34: goto tr1889;
		case 92: goto st1296;
		case 97: goto tr1905;
		case 99: goto tr1906;
		case 100: goto tr1907;
		case 110: goto tr1908;
		case 115: goto tr1909;
		case 125: goto tr1910;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1904;
	goto tr1887;
tr1905:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1300;
st1300:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1300;
case 1300:
#line 28433 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 116: goto tr1911;
	}
	goto tr1887;
tr1911:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1301;
st1301:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1301;
case 1301:
#line 28450 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 116: goto tr1912;
	}
	goto tr1887;
tr1912:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1302;
st1302:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1302;
case 1302:
#line 28467 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 97: goto tr1913;
	}
	goto tr1887;
tr1913:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1303;
st1303:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1303;
case 1303:
#line 28484 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 99: goto tr1914;
	}
	goto tr1887;
tr1914:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1304;
st1304:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1304;
case 1304:
#line 28501 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 107: goto tr1915;
	}
	goto tr1887;
tr1915:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1305;
st1305:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1305;
case 1305:
#line 28518 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1916;
		case 32: goto tr1916;
		case 34: goto tr1889;
		case 92: goto st1296;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1916;
	goto tr1887;
tr1916:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1306;
st1306:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1306;
case 1306:
#line 28538 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1916;
		case 32: goto tr1916;
		case 34: goto tr1889;
		case 45: goto tr1917;
		case 92: goto st1296;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1918;
	} else if ( (*( state.p)) >= 9 )
		goto tr1916;
	goto tr1887;
tr1917:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1307;
st1307:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1307;
case 1307:
#line 28566 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr1919;
	goto tr1887;
tr1919:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1308;
tr1918:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1308;
st1308:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1308;
case 1308:
#line 28594 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1920;
		case 32: goto tr1920;
		case 34: goto tr1889;
		case 46: goto tr1921;
		case 59: goto tr1922;
		case 92: goto st1296;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1919;
	} else if ( (*( state.p)) >= 9 )
		goto tr1920;
	goto tr1887;
tr1921:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1309;
st1309:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1309;
case 1309:
#line 28619 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr1923;
	goto tr1887;
tr1923:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1310;
st1310:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1310;
case 1310:
#line 28637 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1920;
		case 32: goto tr1920;
		case 34: goto tr1889;
		case 59: goto tr1922;
		case 92: goto st1296;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1923;
	} else if ( (*( state.p)) >= 9 )
		goto tr1920;
	goto tr1887;
tr1906:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1311;
st1311:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1311;
case 1311:
#line 28661 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 111: goto tr1924;
	}
	goto tr1887;
tr1924:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1312;
st1312:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1312;
case 1312:
#line 28678 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 117: goto tr1925;
	}
	goto tr1887;
tr1925:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1313;
st1313:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1313;
case 1313:
#line 28695 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 110: goto tr1926;
	}
	goto tr1887;
tr1926:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1314;
st1314:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1314;
case 1314:
#line 28712 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 116: goto tr1927;
	}
	goto tr1887;
tr1927:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1315;
st1315:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1315;
case 1315:
#line 28729 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1928;
		case 32: goto tr1928;
		case 34: goto tr1889;
		case 92: goto st1296;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1928;
	goto tr1887;
tr1928:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1316;
st1316:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1316;
case 1316:
#line 28749 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1928;
		case 32: goto tr1928;
		case 34: goto tr1889;
		case 92: goto st1296;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1929;
	} else if ( (*( state.p)) >= 9 )
		goto tr1928;
	goto tr1887;
tr1929:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1317;
tr1931:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1317;
st1317:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1317;
case 1317:
#line 28782 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1930;
		case 32: goto tr1930;
		case 34: goto tr1889;
		case 59: goto tr1932;
		case 92: goto st1296;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1931;
	} else if ( (*( state.p)) >= 9 )
		goto tr1930;
	goto tr1887;
tr1907:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1318;
st1318:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1318;
case 1318:
#line 28806 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 101: goto tr1933;
	}
	goto tr1887;
tr1933:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1319;
st1319:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1319;
case 1319:
#line 28823 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 102: goto tr1934;
		case 115: goto tr1935;
	}
	goto tr1887;
tr1934:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1320;
st1320:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1320;
case 1320:
#line 28841 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 101: goto tr1936;
	}
	goto tr1887;
tr1936:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1321;
st1321:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1321;
case 1321:
#line 28858 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 110: goto tr1937;
	}
	goto tr1887;
tr1937:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1322;
st1322:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1322;
case 1322:
#line 28875 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 115: goto tr1938;
	}
	goto tr1887;
tr1938:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1323;
st1323:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1323;
case 1323:
#line 28892 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 101: goto tr1939;
	}
	goto tr1887;
tr1939:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1324;
st1324:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1324;
case 1324:
#line 28909 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1940;
		case 32: goto tr1940;
		case 34: goto tr1889;
		case 92: goto st1296;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1940;
	goto tr1887;
tr1940:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1325;
st1325:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1325;
case 1325:
#line 28929 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1940;
		case 32: goto tr1940;
		case 34: goto tr1889;
		case 45: goto tr1941;
		case 92: goto st1296;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1942;
	} else if ( (*( state.p)) >= 9 )
		goto tr1940;
	goto tr1887;
tr1941:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1326;
st1326:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1326;
case 1326:
#line 28957 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr1943;
	goto tr1887;
tr1943:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1327;
tr1942:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1327;
st1327:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1327;
case 1327:
#line 28985 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1944;
		case 32: goto tr1944;
		case 34: goto tr1889;
		case 46: goto tr1945;
		case 59: goto tr1946;
		case 92: goto st1296;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1943;
	} else if ( (*( state.p)) >= 9 )
		goto tr1944;
	goto tr1887;
tr1945:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1328;
st1328:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1328;
case 1328:
#line 29010 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr1947;
	goto tr1887;
tr1947:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1329;
st1329:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1329;
case 1329:
#line 29028 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1944;
		case 32: goto tr1944;
		case 34: goto tr1889;
		case 59: goto tr1946;
		case 92: goto st1296;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1947;
	} else if ( (*( state.p)) >= 9 )
		goto tr1944;
	goto tr1887;
tr1935:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1330;
st1330:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1330;
case 1330:
#line 29052 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 99: goto tr1948;
	}
	goto tr1887;
tr1948:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1331;
st1331:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1331;
case 1331:
#line 29069 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 114: goto tr1949;
	}
	goto tr1887;
tr1949:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1332;
st1332:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1332;
case 1332:
#line 29086 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1950;
		case 32: goto tr1950;
		case 34: goto tr1889;
		case 92: goto st1296;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1950;
	goto tr1887;
tr1950:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1333;
st1333:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1333;
case 1333:
#line 29106 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1950;
		case 32: goto tr1950;
		case 34: goto tr1951;
		case 92: goto st1296;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1950;
	goto tr1887;
tr1951:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1334;
st1334:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1334;
case 1334:
#line 29126 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1952;
		case 32: goto tr1952;
		case 34: goto tr1366;
		case 59: goto tr1953;
		case 92: goto st969;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1952;
	goto tr1365;
tr1908:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1335;
st1335:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1335;
case 1335:
#line 29147 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 97: goto tr1954;
	}
	goto tr1887;
tr1954:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1336;
st1336:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1336;
case 1336:
#line 29164 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 109: goto tr1955;
	}
	goto tr1887;
tr1955:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1337;
st1337:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1337;
case 1337:
#line 29181 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 101: goto tr1956;
	}
	goto tr1887;
tr1956:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1338;
st1338:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1338;
case 1338:
#line 29198 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1957;
		case 32: goto tr1957;
		case 34: goto tr1889;
		case 92: goto st1296;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1957;
	goto tr1887;
tr1957:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1339;
st1339:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1339;
case 1339:
#line 29218 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1957;
		case 32: goto tr1957;
		case 34: goto tr1958;
		case 92: goto st1296;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1957;
	goto tr1887;
tr1958:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1340;
st1340:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1340;
case 1340:
#line 29238 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1959;
		case 32: goto tr1959;
		case 34: goto tr1438;
		case 59: goto tr1960;
		case 92: goto st1016;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1959;
	goto tr1436;
tr1909:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1341;
st1341:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1341;
case 1341:
#line 29259 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 107: goto tr1961;
		case 108: goto tr1962;
	}
	goto tr1887;
tr1961:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1342;
st1342:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1342;
case 1342:
#line 29277 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 105: goto tr1963;
	}
	goto tr1887;
tr1963:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1343;
st1343:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1343;
case 1343:
#line 29294 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 110: goto tr1964;
	}
	goto tr1887;
tr1964:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1344;
st1344:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1344;
case 1344:
#line 29311 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1965;
		case 32: goto tr1965;
		case 34: goto tr1889;
		case 92: goto st1296;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1965;
	goto tr1887;
tr1965:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1345;
st1345:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1345;
case 1345:
#line 29331 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1965;
		case 32: goto tr1965;
		case 34: goto tr1966;
		case 92: goto st1296;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1965;
	goto tr1887;
tr1966:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1346;
st1346:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1346;
case 1346:
#line 29351 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1967;
		case 32: goto tr1967;
		case 34: goto tr1519;
		case 59: goto tr1968;
		case 92: goto st1121;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1967;
	goto tr1517;
tr1962:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1347;
st1347:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1347;
case 1347:
#line 29372 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 111: goto tr1969;
	}
	goto tr1887;
tr1969:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1348;
st1348:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1348;
case 1348:
#line 29389 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 116: goto tr1970;
	}
	goto tr1887;
tr1970:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1349;
st1349:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1349;
case 1349:
#line 29406 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1971;
		case 32: goto tr1971;
		case 34: goto tr1889;
		case 92: goto st1296;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1971;
	goto tr1887;
tr1971:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1350;
st1350:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1350;
case 1350:
#line 29426 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1971;
		case 32: goto tr1971;
		case 34: goto tr1972;
		case 92: goto st1296;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1971;
	goto tr1887;
tr1972:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1351;
st1351:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1351;
case 1351:
#line 29446 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1973;
		case 32: goto tr1973;
		case 34: goto tr1889;
		case 59: goto tr1974;
		case 92: goto st1296;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1973;
	goto tr1887;
tr1910:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1352;
st1352:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1352;
case 1352:
#line 29467 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1975;
		case 32: goto tr1975;
		case 34: goto tr1889;
		case 59: goto tr1976;
		case 92: goto st1296;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1975;
	goto tr1887;
tr1896:
#line 138 "configparser.rl"
	{ state.match += '\\'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1353;
st1353:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1353;
case 1353:
#line 29490 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1978;
		case 92: goto tr1979;
	}
	goto tr1977;
tr1980:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1354;
tr1888:
#line 161 "configparser.rl"
	{ skin.text = state.match; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1354;
st1354:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1354;
case 1354:
#line 29514 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1980;
		case 32: goto tr1980;
		case 34: goto tr1889;
		case 92: goto st1296;
		case 98: goto tr1981;
		case 100: goto tr1982;
		case 110: goto tr1983;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1980;
	goto tr1887;
tr1981:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1355;
st1355:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1355;
case 1355:
#line 29537 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 114: goto tr1984;
	}
	goto tr1887;
tr1984:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1356;
st1356:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1356;
case 1356:
#line 29554 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 105: goto tr1985;
	}
	goto tr1887;
tr1985:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1357;
st1357:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1357;
case 1357:
#line 29571 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 103: goto tr1986;
	}
	goto tr1887;
tr1986:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1358;
st1358:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1358;
case 1358:
#line 29588 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 104: goto tr1987;
	}
	goto tr1887;
tr1987:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1359;
st1359:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1359;
case 1359:
#line 29605 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 116: goto tr1988;
	}
	goto tr1887;
tr1988:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1360;
st1360:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1360;
case 1360:
#line 29622 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1989;
		case 32: goto tr1989;
		case 34: goto tr1889;
		case 92: goto st1296;
		case 95: goto tr1990;
		case 98: goto tr1991;
		case 99: goto tr1992;
		case 103: goto tr1993;
		case 109: goto tr1994;
		case 114: goto tr1995;
		case 119: goto tr1996;
		case 121: goto tr1997;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1989;
	goto tr1887;
tr1998:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1361;
tr1989:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1361;
tr2054:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1361;
st1361:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1361;
case 1361:
#line 29666 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1998;
		case 32: goto tr1998;
		case 34: goto tr1889;
		case 92: goto st1296;
		case 98: goto tr1999;
		case 99: goto tr2000;
		case 103: goto tr2001;
		case 109: goto tr2002;
		case 114: goto tr2003;
		case 119: goto tr2004;
		case 121: goto tr2005;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1998;
	goto tr1887;
tr1999:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1362;
tr1991:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1362;
tr2056:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1362;
st1362:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1362;
case 1362:
#line 29709 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 108: goto tr2006;
	}
	goto tr1887;
tr2006:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1363;
st1363:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1363;
case 1363:
#line 29726 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 97: goto tr2007;
		case 117: goto tr2008;
	}
	goto tr1887;
tr2007:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1364;
st1364:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1364;
case 1364:
#line 29744 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 99: goto tr2009;
	}
	goto tr1887;
tr2009:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1365;
st1365:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1365;
case 1365:
#line 29761 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 107: goto tr2010;
	}
	goto tr1887;
tr2010:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1366;
st1366:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1366;
case 1366:
#line 29778 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr2011;
		case 32: goto tr2011;
		case 34: goto tr1889;
		case 59: goto tr2012;
		case 92: goto st1296;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2011;
	goto tr1887;
tr2008:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1367;
st1367:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1367;
case 1367:
#line 29799 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 101: goto tr2013;
	}
	goto tr1887;
tr2013:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1368;
st1368:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1368;
case 1368:
#line 29816 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr2014;
		case 32: goto tr2014;
		case 34: goto tr1889;
		case 59: goto tr2015;
		case 92: goto st1296;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2014;
	goto tr1887;
tr2000:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1369;
tr1992:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1369;
tr2057:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1369;
st1369:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1369;
case 1369:
#line 29853 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 121: goto tr2016;
	}
	goto tr1887;
tr2016:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1370;
st1370:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1370;
case 1370:
#line 29870 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 97: goto tr2017;
	}
	goto tr1887;
tr2017:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1371;
st1371:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1371;
case 1371:
#line 29887 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 110: goto tr2018;
	}
	goto tr1887;
tr2018:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1372;
st1372:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1372;
case 1372:
#line 29904 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr2019;
		case 32: goto tr2019;
		case 34: goto tr1889;
		case 59: goto tr2020;
		case 92: goto st1296;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2019;
	goto tr1887;
tr2001:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1373;
tr1993:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1373;
tr2058:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1373;
st1373:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1373;
case 1373:
#line 29941 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 114: goto tr2021;
	}
	goto tr1887;
tr2021:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1374;
st1374:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1374;
case 1374:
#line 29958 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 101: goto tr2022;
	}
	goto tr1887;
tr2022:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1375;
st1375:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1375;
case 1375:
#line 29975 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 101: goto tr2023;
	}
	goto tr1887;
tr2023:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1376;
st1376:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1376;
case 1376:
#line 29992 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 110: goto tr2024;
	}
	goto tr1887;
tr2024:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1377;
st1377:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1377;
case 1377:
#line 30009 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr2025;
		case 32: goto tr2025;
		case 34: goto tr1889;
		case 59: goto tr2026;
		case 92: goto st1296;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2025;
	goto tr1887;
tr2002:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1378;
tr1994:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1378;
tr2059:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1378;
st1378:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1378;
case 1378:
#line 30046 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 97: goto tr2027;
	}
	goto tr1887;
tr2027:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1379;
st1379:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1379;
case 1379:
#line 30063 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 103: goto tr2028;
	}
	goto tr1887;
tr2028:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1380;
st1380:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1380;
case 1380:
#line 30080 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 101: goto tr2029;
	}
	goto tr1887;
tr2029:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1381;
st1381:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1381;
case 1381:
#line 30097 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 110: goto tr2030;
	}
	goto tr1887;
tr2030:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1382;
st1382:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1382;
case 1382:
#line 30114 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 116: goto tr2031;
	}
	goto tr1887;
tr2031:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1383;
st1383:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1383;
case 1383:
#line 30131 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 97: goto tr2032;
	}
	goto tr1887;
tr2032:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1384;
st1384:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1384;
case 1384:
#line 30148 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr2033;
		case 32: goto tr2033;
		case 34: goto tr1889;
		case 59: goto tr2034;
		case 92: goto st1296;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2033;
	goto tr1887;
tr2003:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1385;
tr1995:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1385;
tr2060:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1385;
st1385:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1385;
case 1385:
#line 30185 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 101: goto tr2035;
	}
	goto tr1887;
tr2035:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1386;
st1386:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1386;
case 1386:
#line 30202 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 100: goto tr2036;
	}
	goto tr1887;
tr2036:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1387;
st1387:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1387;
case 1387:
#line 30219 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr2037;
		case 32: goto tr2037;
		case 34: goto tr1889;
		case 59: goto tr2038;
		case 92: goto st1296;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2037;
	goto tr1887;
tr2004:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1388;
tr1996:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1388;
tr2061:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1388;
st1388:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1388;
case 1388:
#line 30256 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 104: goto tr2039;
	}
	goto tr1887;
tr2039:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1389;
st1389:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1389;
case 1389:
#line 30273 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 105: goto tr2040;
	}
	goto tr1887;
tr2040:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1390;
st1390:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1390;
case 1390:
#line 30290 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 116: goto tr2041;
	}
	goto tr1887;
tr2041:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1391;
st1391:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1391;
case 1391:
#line 30307 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 101: goto tr2042;
	}
	goto tr1887;
tr2042:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1392;
st1392:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1392;
case 1392:
#line 30324 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr2043;
		case 32: goto tr2043;
		case 34: goto tr1889;
		case 59: goto tr2044;
		case 92: goto st1296;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2043;
	goto tr1887;
tr2005:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1393;
tr1997:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1393;
tr2062:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1393;
st1393:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1393;
case 1393:
#line 30361 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 101: goto tr2045;
	}
	goto tr1887;
tr2045:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1394;
st1394:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1394;
case 1394:
#line 30378 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 108: goto tr2046;
	}
	goto tr1887;
tr2046:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1395;
st1395:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1395;
case 1395:
#line 30395 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 108: goto tr2047;
	}
	goto tr1887;
tr2047:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1396;
st1396:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1396;
case 1396:
#line 30412 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 111: goto tr2048;
	}
	goto tr1887;
tr2048:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1397;
st1397:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1397;
case 1397:
#line 30429 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 119: goto tr2049;
	}
	goto tr1887;
tr2049:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1398;
st1398:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1398;
case 1398:
#line 30446 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr2050;
		case 32: goto tr2050;
		case 34: goto tr1889;
		case 59: goto tr2051;
		case 92: goto st1296;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2050;
	goto tr1887;
tr1990:
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1399;
tr2055:
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1399;
st1399:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1399;
case 1399:
#line 30477 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 98: goto tr1999;
		case 99: goto tr2000;
		case 103: goto tr2001;
		case 109: goto tr2002;
		case 114: goto tr2003;
		case 119: goto tr2004;
		case 121: goto tr2005;
	}
	goto tr1887;
tr1982:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1400;
st1400:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1400;
case 1400:
#line 30500 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 105: goto tr2052;
	}
	goto tr1887;
tr2052:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1401;
st1401:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1401;
case 1401:
#line 30517 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 109: goto tr2053;
	}
	goto tr1887;
tr2053:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1402;
st1402:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1402;
case 1402:
#line 30534 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr2054;
		case 32: goto tr2054;
		case 34: goto tr1889;
		case 92: goto st1296;
		case 95: goto tr2055;
		case 98: goto tr2056;
		case 99: goto tr2057;
		case 103: goto tr2058;
		case 109: goto tr2059;
		case 114: goto tr2060;
		case 119: goto tr2061;
		case 121: goto tr2062;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2054;
	goto tr1887;
tr1983:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1403;
st1403:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1403;
case 1403:
#line 30562 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 111: goto tr2063;
	}
	goto tr1887;
tr2063:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1404;
st1404:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1404;
case 1404:
#line 30579 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 110: goto tr2064;
	}
	goto tr1887;
tr2064:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1405;
st1405:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1405;
case 1405:
#line 30596 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1889;
		case 92: goto st1296;
		case 101: goto tr2010;
	}
	goto tr1887;
tr1657:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1406;
st1406:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1406;
case 1406:
#line 30613 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr2065;
		case 32: goto tr2065;
		case 34: goto tr1519;
		case 59: goto tr2066;
		case 92: goto st1121;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2065;
	goto tr1517;
tr1644:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1407;
st1407:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1407;
case 1407:
#line 30634 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 101: goto tr2067;
	}
	goto tr1517;
tr2067:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1408;
st1408:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1408;
case 1408:
#line 30651 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr2068;
		case 32: goto tr2068;
		case 34: goto tr1519;
		case 59: goto tr2069;
		case 92: goto st1121;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2068;
	goto tr1517;
tr1636:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1409;
tr1628:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1409;
tr2111:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1409;
st1409:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1409;
case 1409:
#line 30688 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 121: goto tr2070;
	}
	goto tr1517;
tr2070:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1410;
st1410:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1410;
case 1410:
#line 30705 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 97: goto tr2071;
	}
	goto tr1517;
tr2071:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1411;
st1411:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1411;
case 1411:
#line 30722 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 110: goto tr2072;
	}
	goto tr1517;
tr2072:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1412;
st1412:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1412;
case 1412:
#line 30739 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr2073;
		case 32: goto tr2073;
		case 34: goto tr1519;
		case 59: goto tr2074;
		case 92: goto st1121;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2073;
	goto tr1517;
tr1637:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1413;
tr1629:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1413;
tr2112:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1413;
st1413:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1413;
case 1413:
#line 30776 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 114: goto tr2075;
	}
	goto tr1517;
tr2075:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1414;
st1414:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1414;
case 1414:
#line 30793 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 101: goto tr2076;
	}
	goto tr1517;
tr2076:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1415;
st1415:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1415;
case 1415:
#line 30810 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 101: goto tr2077;
	}
	goto tr1517;
tr2077:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1416;
st1416:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1416;
case 1416:
#line 30827 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 110: goto tr2078;
	}
	goto tr1517;
tr2078:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1417;
st1417:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1417;
case 1417:
#line 30844 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr2079;
		case 32: goto tr2079;
		case 34: goto tr1519;
		case 59: goto tr2080;
		case 92: goto st1121;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2079;
	goto tr1517;
tr1638:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1418;
tr1630:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1418;
tr2113:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1418;
st1418:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1418;
case 1418:
#line 30881 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 97: goto tr2081;
	}
	goto tr1517;
tr2081:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1419;
st1419:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1419;
case 1419:
#line 30898 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 103: goto tr2082;
	}
	goto tr1517;
tr2082:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1420;
st1420:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1420;
case 1420:
#line 30915 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 101: goto tr2083;
	}
	goto tr1517;
tr2083:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1421;
st1421:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1421;
case 1421:
#line 30932 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 110: goto tr2084;
	}
	goto tr1517;
tr2084:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1422;
st1422:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1422;
case 1422:
#line 30949 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 116: goto tr2085;
	}
	goto tr1517;
tr2085:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1423;
st1423:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1423;
case 1423:
#line 30966 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 97: goto tr2086;
	}
	goto tr1517;
tr2086:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1424;
st1424:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1424;
case 1424:
#line 30983 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr2087;
		case 32: goto tr2087;
		case 34: goto tr1519;
		case 59: goto tr2088;
		case 92: goto st1121;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2087;
	goto tr1517;
tr1639:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1425;
tr1631:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1425;
tr2114:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1425;
st1425:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1425;
case 1425:
#line 31020 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 101: goto tr2089;
	}
	goto tr1517;
tr2089:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1426;
st1426:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1426;
case 1426:
#line 31037 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 100: goto tr2090;
	}
	goto tr1517;
tr2090:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1427;
st1427:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1427;
case 1427:
#line 31054 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr2091;
		case 32: goto tr2091;
		case 34: goto tr1519;
		case 59: goto tr2092;
		case 92: goto st1121;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2091;
	goto tr1517;
tr1640:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1428;
tr1632:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1428;
tr2115:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1428;
st1428:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1428;
case 1428:
#line 31091 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 104: goto tr2093;
	}
	goto tr1517;
tr2093:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1429;
st1429:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1429;
case 1429:
#line 31108 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 105: goto tr2094;
	}
	goto tr1517;
tr2094:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1430;
st1430:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1430;
case 1430:
#line 31125 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 116: goto tr2095;
	}
	goto tr1517;
tr2095:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1431;
st1431:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1431;
case 1431:
#line 31142 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 101: goto tr2096;
	}
	goto tr1517;
tr2096:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1432;
st1432:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1432;
case 1432:
#line 31159 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr2097;
		case 32: goto tr2097;
		case 34: goto tr1519;
		case 59: goto tr2098;
		case 92: goto st1121;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2097;
	goto tr1517;
tr1641:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1433;
tr1633:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1433;
tr2116:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1433;
st1433:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1433;
case 1433:
#line 31196 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 101: goto tr2099;
	}
	goto tr1517;
tr2099:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1434;
st1434:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1434;
case 1434:
#line 31213 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 108: goto tr2100;
	}
	goto tr1517;
tr2100:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1435;
st1435:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1435;
case 1435:
#line 31230 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 108: goto tr2101;
	}
	goto tr1517;
tr2101:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1436;
st1436:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1436;
case 1436:
#line 31247 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 111: goto tr2102;
	}
	goto tr1517;
tr2102:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1437;
st1437:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1437;
case 1437:
#line 31264 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 119: goto tr2103;
	}
	goto tr1517;
tr2103:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1438;
st1438:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1438;
case 1438:
#line 31281 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr2104;
		case 32: goto tr2104;
		case 34: goto tr1519;
		case 59: goto tr2105;
		case 92: goto st1121;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2104;
	goto tr1517;
tr1626:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st1439;
tr2109:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st1439;
st1439:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1439;
case 1439:
#line 31312 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 98: goto tr1635;
		case 99: goto tr1636;
		case 103: goto tr1637;
		case 109: goto tr1638;
		case 114: goto tr1639;
		case 119: goto tr1640;
		case 121: goto tr1641;
	}
	goto tr1517;
tr1618:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1440;
st1440:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1440;
case 1440:
#line 31335 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 105: goto tr2106;
	}
	goto tr1517;
tr2106:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1441;
st1441:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1441;
case 1441:
#line 31352 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 109: goto tr2107;
	}
	goto tr1517;
tr2107:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1442;
st1442:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1442;
case 1442:
#line 31369 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr2108;
		case 32: goto tr2108;
		case 34: goto tr1519;
		case 92: goto st1121;
		case 95: goto tr2109;
		case 98: goto tr2110;
		case 99: goto tr2111;
		case 103: goto tr2112;
		case 109: goto tr2113;
		case 114: goto tr2114;
		case 119: goto tr2115;
		case 121: goto tr2116;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2108;
	goto tr1517;
tr1619:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1443;
st1443:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1443;
case 1443:
#line 31397 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 111: goto tr2117;
	}
	goto tr1517;
tr2117:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1444;
st1444:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1444;
case 1444:
#line 31414 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 110: goto tr2118;
	}
	goto tr1517;
tr2118:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1445;
st1445:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1445;
case 1445:
#line 31431 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1519;
		case 92: goto st1121;
		case 101: goto tr1646;
	}
	goto tr1517;
tr1611:
#line 138 "configparser.rl"
	{ state.match += '\\'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1446;
st1446:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1446;
case 1446:
#line 31450 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr2120;
		case 92: goto tr2121;
	}
	goto tr2119;
tr1512:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1447;
st1447:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1447;
case 1447:
#line 31466 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 111: goto tr2122;
	}
	goto tr1436;
tr2122:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1448;
st1448:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1448;
case 1448:
#line 31483 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1438;
		case 92: goto st1016;
		case 116: goto tr2123;
	}
	goto tr1436;
tr2123:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1449;
st1449:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1449;
case 1449:
#line 31500 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr2124;
		case 32: goto tr2124;
		case 34: goto tr1438;
		case 92: goto st1016;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2124;
	goto tr1436;
tr2124:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1450;
st1450:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1450;
case 1450:
#line 31520 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr2124;
		case 32: goto tr2124;
		case 34: goto tr2125;
		case 92: goto st1016;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2124;
	goto tr1436;
tr2125:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1451;
st1451:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1451;
case 1451:
#line 31540 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr2126;
		case 32: goto tr2126;
		case 34: goto tr1889;
		case 59: goto tr2127;
		case 92: goto st1296;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2126;
	goto tr1887;
tr1460:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1452;
st1452:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1452;
case 1452:
#line 31561 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr2128;
		case 32: goto tr2128;
		case 34: goto tr1438;
		case 59: goto tr2129;
		case 92: goto st1016;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2128;
	goto tr1436;
tr1446:
#line 138 "configparser.rl"
	{ state.match += '\\'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1453;
st1453:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1453;
case 1453:
#line 31584 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr2131;
		case 92: goto tr2132;
	}
	goto tr2130;
tr1386:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1454;
st1454:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1454;
case 1454:
#line 31600 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 107: goto tr2133;
		case 108: goto tr2134;
	}
	goto tr1365;
tr2133:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1455;
st1455:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1455;
case 1455:
#line 31618 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 105: goto tr2135;
	}
	goto tr1365;
tr2135:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1456;
st1456:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1456;
case 1456:
#line 31635 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 110: goto tr2136;
	}
	goto tr1365;
tr2136:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1457;
st1457:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1457;
case 1457:
#line 31652 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr2137;
		case 32: goto tr2137;
		case 34: goto tr1366;
		case 92: goto st969;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2137;
	goto tr1365;
tr2137:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1458;
st1458:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1458;
case 1458:
#line 31672 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr2137;
		case 32: goto tr2137;
		case 34: goto tr2138;
		case 92: goto st969;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2137;
	goto tr1365;
tr2138:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1459;
st1459:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1459;
case 1459:
#line 31692 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr2139;
		case 32: goto tr2139;
		case 34: goto tr1519;
		case 59: goto tr2140;
		case 92: goto st1121;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2139;
	goto tr1517;
tr2134:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1460;
st1460:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1460;
case 1460:
#line 31713 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 111: goto tr2141;
	}
	goto tr1365;
tr2141:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1461;
st1461:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1461;
case 1461:
#line 31730 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr1366;
		case 92: goto st969;
		case 116: goto tr2142;
	}
	goto tr1365;
tr2142:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1462;
st1462:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1462;
case 1462:
#line 31747 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr2143;
		case 32: goto tr2143;
		case 34: goto tr1366;
		case 92: goto st969;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2143;
	goto tr1365;
tr2143:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1463;
st1463:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1463;
case 1463:
#line 31767 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr2143;
		case 32: goto tr2143;
		case 34: goto tr2144;
		case 92: goto st969;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2143;
	goto tr1365;
tr2144:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st1464;
st1464:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1464;
case 1464:
#line 31787 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr2145;
		case 32: goto tr2145;
		case 34: goto tr1889;
		case 59: goto tr2146;
		case 92: goto st1296;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2145;
	goto tr1887;
tr1387:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1465;
st1465:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1465;
case 1465:
#line 31808 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr2147;
		case 32: goto tr2147;
		case 34: goto tr1366;
		case 59: goto tr2148;
		case 92: goto st969;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2147;
	goto tr1365;
tr1373:
#line 138 "configparser.rl"
	{ state.match += '\\'; }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1466;
st1466:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1466;
case 1466:
#line 31831 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr2150;
		case 92: goto tr2151;
	}
	goto tr2149;
st1467:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1467;
case 1467:
	if ( (*( state.p)) == 97 )
		goto st1468;
	goto st0;
st1468:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1468;
case 1468:
	if ( (*( state.p)) == 109 )
		goto st1469;
	goto st0;
st1469:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1469;
case 1469:
	if ( (*( state.p)) == 101 )
		goto st1470;
	goto st0;
st1470:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1470;
case 1470:
	switch( (*( state.p)) ) {
		case 13: goto st1471;
		case 32: goto st1471;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1471;
	goto st0;
st1471:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1471;
case 1471:
	switch( (*( state.p)) ) {
		case 13: goto st1471;
		case 32: goto st1471;
		case 34: goto st1014;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1471;
	goto st0;
st1472:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1472;
case 1472:
	switch( (*( state.p)) ) {
		case 107: goto st1473;
		case 108: goto st1477;
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
	if ( (*( state.p)) == 110 )
		goto st1475;
	goto st0;
st1475:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1475;
case 1475:
	switch( (*( state.p)) ) {
		case 13: goto st1476;
		case 32: goto st1476;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1476;
	goto st0;
st1476:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1476;
case 1476:
	switch( (*( state.p)) ) {
		case 13: goto st1476;
		case 32: goto st1476;
		case 34: goto st1067;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1476;
	goto st0;
st1477:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1477;
case 1477:
	if ( (*( state.p)) == 111 )
		goto st1478;
	goto st0;
st1478:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1478;
case 1478:
	if ( (*( state.p)) == 116 )
		goto st1479;
	goto st0;
st1479:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1479;
case 1479:
	switch( (*( state.p)) ) {
		case 13: goto st1480;
		case 32: goto st1480;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1480;
	goto st0;
st1480:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1480;
case 1480:
	switch( (*( state.p)) ) {
		case 13: goto st1480;
		case 32: goto st1480;
		case 34: goto st1294;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1480;
	goto st0;
st1481:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1481;
case 1481:
	switch( (*( state.p)) ) {
		case 13: goto tr2167;
		case 32: goto tr2167;
		case 59: goto tr2168;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr2167;
	goto st0;
tr1333:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1482;
st1482:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1482;
case 1482:
#line 31986 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr2169;
	goto st0;
tr2169:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st1483;
st1483:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1483;
case 1483:
#line 32000 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1332;
		case 32: goto tr1332;
		case 59: goto tr1334;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr2169;
	} else if ( (*( state.p)) >= 9 )
		goto tr1332;
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
	_test_eof1484:  state.cs = 1484; goto _test_eof; 
	_test_eof1485:  state.cs = 1485; goto _test_eof; 
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
	_test_eof1486:  state.cs = 1486; goto _test_eof; 
	_test_eof25:  state.cs = 25; goto _test_eof; 
	_test_eof26:  state.cs = 26; goto _test_eof; 
	_test_eof27:  state.cs = 27; goto _test_eof; 
	_test_eof28:  state.cs = 28; goto _test_eof; 
	_test_eof29:  state.cs = 29; goto _test_eof; 
	_test_eof30:  state.cs = 30; goto _test_eof; 
	_test_eof31:  state.cs = 31; goto _test_eof; 
	_test_eof32:  state.cs = 32; goto _test_eof; 
	_test_eof33:  state.cs = 33; goto _test_eof; 
	_test_eof1487:  state.cs = 1487; goto _test_eof; 
	_test_eof34:  state.cs = 34; goto _test_eof; 
	_test_eof35:  state.cs = 35; goto _test_eof; 
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
	_test_eof1488:  state.cs = 1488; goto _test_eof; 
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
	_test_eof1489:  state.cs = 1489; goto _test_eof; 
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
	_test_eof1490:  state.cs = 1490; goto _test_eof; 
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
	_test_eof1491:  state.cs = 1491; goto _test_eof; 
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
	_test_eof1492:  state.cs = 1492; goto _test_eof; 
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
	_test_eof1493:  state.cs = 1493; goto _test_eof; 
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
	_test_eof1494:  state.cs = 1494; goto _test_eof; 
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
	_test_eof1495:  state.cs = 1495; goto _test_eof; 
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

	_test_eof: {}
	if ( ( state.p) == ( state.eof) )
	{
	switch (  state.cs ) {
	case 1486: 
#line 227 "configparser.rl"
	{ std::cout << "species done: " << std::endl; print_species(spe); }
	break;
	case 1484: 
#line 260 "configparser.rl"
	{ std::cout << "design done: " << std::endl; print_design(des); }
	break;
#line 33521 "configparser.h"
	}
	}

	_out: {}
	}

#line 296 "configparser.rl"

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
