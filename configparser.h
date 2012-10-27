
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

    
#line 207 "configparser.rl"

/*

*/

    
#line 96 "configparser.h"
static const int ConfigParser_start = 1;
static const int ConfigParser_first_final = 818;
static const int ConfigParser_error = 0;

static const int ConfigParser_en_one_species = 14;
static const int ConfigParser_en_main = 1;


#line 213 "configparser.rl"
    
#line 107 "configparser.h"
	{
	 state.cs = ConfigParser_start;
	 state.top = 0;
	}

#line 214 "configparser.rl"

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

        
#line 136 "configparser.h"
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
		case 13: goto st13;
		case 818: goto st818;
		case 819: goto st819;
		case 14: goto st14;
		case 15: goto st15;
		case 16: goto st16;
		case 17: goto st17;
		case 18: goto st18;
		case 19: goto st19;
		case 20: goto st20;
		case 21: goto st21;
		case 22: goto st22;
		case 820: goto st820;
		case 23: goto st23;
		case 24: goto st24;
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
		case 821: goto st821;
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
		case 822: goto st822;
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
		case 823: goto st823;
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
		case 115: goto tr2;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1;
	goto st0;
st0:
 state.cs = 0;
	goto _out;
tr2:
#line 199 "configparser.rl"
	{ spe = Species(); }
	goto st2;
tr1146:
#line 202 "configparser.rl"
	{ std::cout << "species done: " << std::endl; print_species(spe); }
#line 199 "configparser.rl"
	{ spe = Species(); }
	goto st2;
st2:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof2;
case 2:
#line 1005 "configparser.h"
	if ( (*( state.p)) == 112 )
		goto tr3;
	goto st0;
tr3:
#line 199 "configparser.rl"
	{ spe = Species(); }
	goto st3;
st3:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof3;
case 3:
#line 1017 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto tr4;
	goto st0;
tr4:
#line 199 "configparser.rl"
	{ spe = Species(); }
	goto st4;
st4:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof4;
case 4:
#line 1029 "configparser.h"
	if ( (*( state.p)) == 99 )
		goto tr5;
	goto st0;
tr5:
#line 199 "configparser.rl"
	{ spe = Species(); }
	goto st5;
st5:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof5;
case 5:
#line 1041 "configparser.h"
	if ( (*( state.p)) == 105 )
		goto tr6;
	goto st0;
tr6:
#line 199 "configparser.rl"
	{ spe = Species(); }
	goto st6;
st6:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof6;
case 6:
#line 1053 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto tr7;
	goto st0;
tr7:
#line 199 "configparser.rl"
	{ spe = Species(); }
	goto st7;
st7:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof7;
case 7:
#line 1065 "configparser.h"
	if ( (*( state.p)) == 115 )
		goto tr8;
	goto st0;
tr8:
#line 199 "configparser.rl"
	{ spe = Species(); }
	goto st8;
st8:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof8;
case 8:
#line 1077 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st9;
		case 32: goto st9;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st9;
	goto st0;
st9:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof9;
case 9:
	switch( (*( state.p)) ) {
		case 13: goto st9;
		case 32: goto st9;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr10;
	} else if ( (*( state.p)) >= 9 )
		goto st9;
	goto st0;
tr10:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st10;
tr12:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st10;
st10:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof10;
case 10:
#line 1119 "configparser.h"
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
#line 192 "configparser.rl"
	{ spe.level = ::atoi(state.match.c_str()); }
	goto st11;
st11:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof11;
case 11:
#line 1138 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st11;
		case 32: goto st11;
		case 95: goto tr14;
	}
	if ( (*( state.p)) < 48 ) {
		if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
			goto st11;
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
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st12;
tr16:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st12;
st12:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof12;
case 12:
#line 1176 "configparser.h"
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
#line 195 "configparser.rl"
	{ spe.tag = state.match; }
	goto st13;
st13:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof13;
case 13:
#line 1203 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st13;
		case 32: goto st13;
		case 123: goto tr19;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st13;
	goto st0;
tr17:
#line 195 "configparser.rl"
	{ spe.tag = state.match; }
#line 201 "configparser.rl"
	{{ state.stack[ state.top++] = 818; goto st14;}}
	goto st818;
tr19:
#line 201 "configparser.rl"
	{{ state.stack[ state.top++] = 818; goto st14;}}
	goto st818;
st818:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof818;
case 818:
#line 1226 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1145;
		case 32: goto tr1145;
		case 115: goto tr1146;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1145;
	goto st0;
tr1145:
#line 202 "configparser.rl"
	{ std::cout << "species done: " << std::endl; print_species(spe); }
	goto st819;
st819:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof819;
case 819:
#line 1243 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st819;
		case 32: goto st819;
		case 115: goto tr2;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st819;
	goto st0;
st14:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof14;
case 14:
	switch( (*( state.p)) ) {
		case 13: goto st14;
		case 32: goto st14;
		case 97: goto st15;
		case 99: goto st23;
		case 104: goto st716;
		case 105: goto st751;
		case 109: goto st769;
		case 110: goto st787;
		case 114: goto st793;
		case 115: goto st800;
		case 125: goto st806;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st14;
	goto st0;
st15:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof15;
case 15:
	if ( (*( state.p)) == 105 )
		goto st16;
	goto st0;
st16:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof16;
case 16:
	switch( (*( state.p)) ) {
		case 13: goto st17;
		case 32: goto st17;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st17;
	goto st0;
st17:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof17;
case 17:
	switch( (*( state.p)) ) {
		case 13: goto st17;
		case 32: goto st17;
		case 110: goto st18;
		case 115: goto st807;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st17;
	goto st0;
st18:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof18;
case 18:
	if ( (*( state.p)) == 111 )
		goto st19;
	goto st0;
st19:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof19;
case 19:
	if ( (*( state.p)) == 110 )
		goto st20;
	goto st0;
st20:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof20;
case 20:
	if ( (*( state.p)) == 101 )
		goto st21;
	goto st0;
st21:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof21;
case 21:
	switch( (*( state.p)) ) {
		case 13: goto tr37;
		case 32: goto tr37;
		case 59: goto tr38;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr37;
	goto st0;
tr37:
#line 150 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st22;
tr57:
#line 173 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
	goto st22;
tr83:
#line 178 "configparser.rl"
	{ spe.companion.back().chance = ::atof(state.match.c_str()); }
	goto st22;
tr270:
#line 163 "configparser.rl"
	{ spe.name = state.match; }
	goto st22;
tr499:
#line 130 "configparser.rl"
	{ add_color(spe.skin.fore, 4); }
	goto st22;
tr504:
#line 132 "configparser.rl"
	{ add_color(spe.skin.fore, 6); }
	goto st22;
tr510:
#line 128 "configparser.rl"
	{ add_color(spe.skin.fore, 2); }
	goto st22;
tr518:
#line 131 "configparser.rl"
	{ add_color(spe.skin.fore, 5); }
	goto st22;
tr522:
#line 127 "configparser.rl"
	{ add_color(spe.skin.fore, 1); }
	goto st22;
tr528:
#line 133 "configparser.rl"
	{ add_color(spe.skin.fore, 7); }
	goto st22;
tr535:
#line 129 "configparser.rl"
	{ add_color(spe.skin.fore, 3); }
	goto st22;
tr1021:
#line 162 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
	goto st22;
tr1040:
#line 146 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st22;
tr1046:
#line 144 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st22;
tr1056:
#line 147 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st22;
tr1062:
#line 143 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st22;
tr1066:
#line 145 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st22;
tr1080:
#line 154 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st22;
tr1087:
#line 155 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st22;
tr1098:
#line 158 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st22;
tr1104:
#line 159 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st22;
tr1110:
#line 160 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st22;
tr1123:
#line 169 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
	goto st22;
tr1131:
#line 186 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st22;
tr1143:
#line 151 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st22;
st22:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof22;
case 22:
#line 1440 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st22;
		case 32: goto st22;
		case 59: goto st820;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st22;
	goto st0;
tr38:
#line 150 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st820;
tr60:
#line 173 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
	goto st820;
tr86:
#line 178 "configparser.rl"
	{ spe.companion.back().chance = ::atof(state.match.c_str()); }
	goto st820;
tr271:
#line 163 "configparser.rl"
	{ spe.name = state.match; }
	goto st820;
tr500:
#line 130 "configparser.rl"
	{ add_color(spe.skin.fore, 4); }
	goto st820;
tr505:
#line 132 "configparser.rl"
	{ add_color(spe.skin.fore, 6); }
	goto st820;
tr511:
#line 128 "configparser.rl"
	{ add_color(spe.skin.fore, 2); }
	goto st820;
tr519:
#line 131 "configparser.rl"
	{ add_color(spe.skin.fore, 5); }
	goto st820;
tr523:
#line 127 "configparser.rl"
	{ add_color(spe.skin.fore, 1); }
	goto st820;
tr529:
#line 133 "configparser.rl"
	{ add_color(spe.skin.fore, 7); }
	goto st820;
tr536:
#line 129 "configparser.rl"
	{ add_color(spe.skin.fore, 3); }
	goto st820;
tr1023:
#line 162 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
	goto st820;
tr1041:
#line 146 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st820;
tr1047:
#line 144 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st820;
tr1057:
#line 147 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st820;
tr1063:
#line 143 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st820;
tr1067:
#line 145 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st820;
tr1081:
#line 154 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st820;
tr1088:
#line 155 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st820;
tr1099:
#line 158 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st820;
tr1105:
#line 159 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st820;
tr1111:
#line 160 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st820;
tr1125:
#line 169 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
	goto st820;
tr1132:
#line 186 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st820;
tr1144:
#line 151 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st820;
st820:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof820;
case 820:
#line 1553 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st14;
		case 32: goto st14;
		case 97: goto st15;
		case 99: goto st23;
		case 104: goto st716;
		case 105: goto st751;
		case 109: goto st769;
		case 110: goto st787;
		case 114: goto st793;
		case 115: goto st800;
		case 125: goto st806;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st14;
	goto st0;
st23:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof23;
case 23:
	switch( (*( state.p)) ) {
		case 108: goto st24;
		case 111: goto st40;
	}
	goto st0;
st24:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof24;
case 24:
	if ( (*( state.p)) == 117 )
		goto st25;
	goto st0;
st25:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof25;
case 25:
	if ( (*( state.p)) == 109 )
		goto st26;
	goto st0;
st26:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof26;
case 26:
	if ( (*( state.p)) == 112 )
		goto st27;
	goto st0;
st27:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof27;
case 27:
	if ( (*( state.p)) == 115 )
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
	if ( (*( state.p)) == 122 )
		goto st30;
	goto st0;
st30:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof30;
case 30:
	if ( (*( state.p)) == 101 )
		goto st31;
	goto st0;
st31:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof31;
case 31:
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
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr51;
	} else if ( (*( state.p)) >= 9 )
		goto st32;
	goto st0;
tr51:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st33;
tr54:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st33;
st33:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof33;
case 33:
#line 1673 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr52;
		case 32: goto tr52;
		case 46: goto st38;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr54;
	} else if ( (*( state.p)) >= 9 )
		goto tr52;
	goto st0;
tr52:
#line 172 "configparser.rl"
	{ spe.clumpsize.mean = ::atof(state.match.c_str()); }
	goto st34;
st34:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof34;
case 34:
#line 1693 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st34;
		case 32: goto st34;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr56;
	} else if ( (*( state.p)) >= 9 )
		goto st34;
	goto st0;
tr56:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st35;
tr59:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st35;
st35:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof35;
case 35:
#line 1724 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr57;
		case 32: goto tr57;
		case 46: goto st36;
		case 59: goto tr60;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr59;
	} else if ( (*( state.p)) >= 9 )
		goto tr57;
	goto st0;
st36:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof36;
case 36:
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto st37;
	goto st0;
st37:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof37;
case 37:
	switch( (*( state.p)) ) {
		case 13: goto tr57;
		case 32: goto tr57;
		case 59: goto tr60;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto st37;
	} else if ( (*( state.p)) >= 9 )
		goto tr57;
	goto st0;
st38:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof38;
case 38:
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto st39;
	goto st0;
st39:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof39;
case 39:
	switch( (*( state.p)) ) {
		case 13: goto tr52;
		case 32: goto tr52;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto st39;
	} else if ( (*( state.p)) >= 9 )
		goto tr52;
	goto st0;
st40:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof40;
case 40:
	switch( (*( state.p)) ) {
		case 109: goto st41;
		case 117: goto st711;
	}
	goto st0;
st41:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof41;
case 41:
	if ( (*( state.p)) == 112 )
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
	if ( (*( state.p)) == 105 )
		goto st45;
	goto st0;
st45:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof45;
case 45:
	if ( (*( state.p)) == 111 )
		goto st46;
	goto st0;
st46:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof46;
case 46:
	if ( (*( state.p)) == 110 )
		goto st47;
	goto st0;
st47:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof47;
case 47:
	switch( (*( state.p)) ) {
		case 13: goto tr71;
		case 32: goto tr71;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr71;
	goto st0;
tr71:
#line 176 "configparser.rl"
	{ spe.companion.push_back(Species::companion_t()); }
	goto st48;
st48:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof48;
case 48:
#line 1850 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st48;
		case 32: goto st48;
		case 34: goto st49;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st48;
	goto st0;
st49:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof49;
case 49:
	switch( (*( state.p)) ) {
		case 34: goto tr75;
		case 92: goto tr76;
	}
	goto tr74;
tr74:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st50;
tr77:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st50;
st50:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof50;
case 50:
#line 1888 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
	}
	goto tr77;
tr75:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st51;
st51:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof51;
case 51:
#line 1904 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr80;
		case 32: goto tr80;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr80;
	goto st0;
tr80:
#line 177 "configparser.rl"
	{ spe.companion.back().tag = state.match; }
	goto st52;
st52:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof52;
case 52:
#line 1920 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st52;
		case 32: goto st52;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr82;
	} else if ( (*( state.p)) >= 9 )
		goto st52;
	goto st0;
tr82:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st53;
tr85:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st53;
st53:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof53;
case 53:
#line 1951 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr83;
		case 32: goto tr83;
		case 46: goto st54;
		case 59: goto tr86;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr85;
	} else if ( (*( state.p)) >= 9 )
		goto tr83;
	goto st0;
st54:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof54;
case 54:
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto st55;
	goto st0;
st55:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof55;
case 55:
	switch( (*( state.p)) ) {
		case 13: goto tr83;
		case 32: goto tr83;
		case 59: goto tr86;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto st55;
	} else if ( (*( state.p)) >= 9 )
		goto tr83;
	goto st0;
tr76:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st56;
tr79:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st56;
st56:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof56;
case 56:
#line 2006 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr88;
		case 92: goto tr79;
	}
	goto tr77;
tr88:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st57;
st57:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof57;
case 57:
#line 2022 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr89;
		case 32: goto tr89;
		case 34: goto st51;
		case 92: goto tr79;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr89;
	goto tr77;
tr90:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st58;
tr89:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 177 "configparser.rl"
	{ spe.companion.back().tag = state.match; }
	goto st58;
tr162:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 177 "configparser.rl"
	{ spe.companion.back().tag = state.match; }
	goto st58;
st58:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof58;
case 58:
#line 2062 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr90;
		case 32: goto tr90;
		case 34: goto st51;
		case 92: goto tr79;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr91;
	} else if ( (*( state.p)) >= 9 )
		goto tr90;
	goto tr77;
tr94:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st59;
tr91:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st59;
st59:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof59;
case 59:
#line 2095 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr92;
		case 32: goto tr92;
		case 34: goto st51;
		case 46: goto tr93;
		case 59: goto tr95;
		case 92: goto tr79;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr94;
	} else if ( (*( state.p)) >= 9 )
		goto tr92;
	goto tr77;
tr96:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr92:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 178 "configparser.rl"
	{ spe.companion.back().chance = ::atof(state.match.c_str()); }
	goto st60;
tr115:
#line 150 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr127:
#line 151 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr145:
#line 173 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr167:
#line 162 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr186:
#line 146 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr192:
#line 144 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr202:
#line 147 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr208:
#line 143 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr212:
#line 145 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr226:
#line 154 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr233:
#line 155 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr244:
#line 158 "configparser.rl"
	{ spe.move = Species::move_t::any; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr250:
#line 159 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr256:
#line 160 "configparser.rl"
	{ spe.move = Species::move_t::water; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr341:
#line 163 "configparser.rl"
	{ spe.name = state.match; }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr680:
#line 130 "configparser.rl"
	{ add_color(spe.skin.fore, 4); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr685:
#line 132 "configparser.rl"
	{ add_color(spe.skin.fore, 6); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr691:
#line 128 "configparser.rl"
	{ add_color(spe.skin.fore, 2); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr699:
#line 131 "configparser.rl"
	{ add_color(spe.skin.fore, 5); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr703:
#line 127 "configparser.rl"
	{ add_color(spe.skin.fore, 1); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr709:
#line 133 "configparser.rl"
	{ add_color(spe.skin.fore, 7); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr716:
#line 129 "configparser.rl"
	{ add_color(spe.skin.fore, 3); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr1014:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 186 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st60;
tr998:
#line 169 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
st60:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof60;
case 60:
#line 2324 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr96;
		case 32: goto tr96;
		case 34: goto st51;
		case 59: goto tr97;
		case 92: goto tr79;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr96;
	goto tr77;
tr97:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st821;
tr95:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 178 "configparser.rl"
	{ spe.companion.back().chance = ::atof(state.match.c_str()); }
	goto st821;
tr116:
#line 150 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st821;
tr128:
#line 151 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st821;
tr148:
#line 173 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st821;
tr169:
#line 162 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st821;
tr187:
#line 146 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st821;
tr193:
#line 144 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st821;
tr203:
#line 147 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st821;
tr209:
#line 143 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st821;
tr213:
#line 145 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st821;
tr227:
#line 154 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st821;
tr234:
#line 155 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st821;
tr245:
#line 158 "configparser.rl"
	{ spe.move = Species::move_t::any; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st821;
tr251:
#line 159 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st821;
tr257:
#line 160 "configparser.rl"
	{ spe.move = Species::move_t::water; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st821;
tr342:
#line 163 "configparser.rl"
	{ spe.name = state.match; }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st821;
tr681:
#line 130 "configparser.rl"
	{ add_color(spe.skin.fore, 4); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st821;
tr686:
#line 132 "configparser.rl"
	{ add_color(spe.skin.fore, 6); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st821;
tr692:
#line 128 "configparser.rl"
	{ add_color(spe.skin.fore, 2); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st821;
tr700:
#line 131 "configparser.rl"
	{ add_color(spe.skin.fore, 5); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st821;
tr704:
#line 127 "configparser.rl"
	{ add_color(spe.skin.fore, 1); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st821;
tr710:
#line 133 "configparser.rl"
	{ add_color(spe.skin.fore, 7); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st821;
tr717:
#line 129 "configparser.rl"
	{ add_color(spe.skin.fore, 3); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st821;
tr1015:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 186 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st821;
tr1000:
#line 169 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st821;
st821:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof821;
case 821:
#line 2549 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr98;
		case 32: goto tr98;
		case 34: goto st51;
		case 92: goto tr79;
		case 97: goto tr99;
		case 99: goto tr100;
		case 104: goto tr101;
		case 105: goto tr102;
		case 109: goto tr103;
		case 110: goto tr104;
		case 114: goto tr105;
		case 115: goto tr106;
		case 125: goto tr107;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr98;
	goto tr77;
tr98:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st61;
st61:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof61;
case 61:
#line 2578 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr98;
		case 32: goto tr98;
		case 34: goto st51;
		case 92: goto tr79;
		case 97: goto tr99;
		case 99: goto tr100;
		case 104: goto tr101;
		case 105: goto tr102;
		case 109: goto tr103;
		case 110: goto tr104;
		case 114: goto tr105;
		case 115: goto tr106;
		case 125: goto tr107;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr98;
	goto tr77;
tr99:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st62;
st62:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof62;
case 62:
#line 2607 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 105: goto tr108;
	}
	goto tr77;
tr108:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st63;
st63:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof63;
case 63:
#line 2624 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr109;
		case 32: goto tr109;
		case 34: goto st51;
		case 92: goto tr79;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr109;
	goto tr77;
tr109:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st64;
st64:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof64;
case 64:
#line 2644 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr109;
		case 32: goto tr109;
		case 34: goto st51;
		case 92: goto tr79;
		case 110: goto tr110;
		case 115: goto tr111;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr109;
	goto tr77;
tr110:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st65;
st65:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof65;
case 65:
#line 2666 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 111: goto tr112;
	}
	goto tr77;
tr112:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st66;
st66:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof66;
case 66:
#line 2683 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 110: goto tr113;
	}
	goto tr77;
tr113:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st67;
st67:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof67;
case 67:
#line 2700 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 101: goto tr114;
	}
	goto tr77;
tr114:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st68;
st68:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof68;
case 68:
#line 2717 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr115;
		case 32: goto tr115;
		case 34: goto st51;
		case 59: goto tr116;
		case 92: goto tr79;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr115;
	goto tr77;
tr111:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st69;
st69:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof69;
case 69:
#line 2738 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 101: goto tr117;
	}
	goto tr77;
tr117:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st70;
st70:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof70;
case 70:
#line 2755 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 101: goto tr118;
	}
	goto tr77;
tr118:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st71;
st71:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof71;
case 71:
#line 2772 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 107: goto tr119;
	}
	goto tr77;
tr119:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st72;
st72:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof72;
case 72:
#line 2789 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 95: goto tr120;
	}
	goto tr77;
tr120:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st73;
st73:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof73;
case 73:
#line 2806 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 112: goto tr121;
	}
	goto tr77;
tr121:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st74;
st74:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof74;
case 74:
#line 2823 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 108: goto tr122;
	}
	goto tr77;
tr122:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st75;
st75:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof75;
case 75:
#line 2840 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 97: goto tr123;
	}
	goto tr77;
tr123:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st76;
st76:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof76;
case 76:
#line 2857 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 121: goto tr124;
	}
	goto tr77;
tr124:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st77;
st77:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof77;
case 77:
#line 2874 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 101: goto tr125;
	}
	goto tr77;
tr125:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st78;
st78:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof78;
case 78:
#line 2891 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 114: goto tr126;
	}
	goto tr77;
tr126:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st79;
st79:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof79;
case 79:
#line 2908 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr127;
		case 32: goto tr127;
		case 34: goto st51;
		case 59: goto tr128;
		case 92: goto tr79;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr127;
	goto tr77;
tr100:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st80;
st80:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof80;
case 80:
#line 2929 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 108: goto tr129;
		case 111: goto tr130;
	}
	goto tr77;
tr129:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st81;
st81:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof81;
case 81:
#line 2947 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 117: goto tr131;
	}
	goto tr77;
tr131:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st82;
st82:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof82;
case 82:
#line 2964 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 109: goto tr132;
	}
	goto tr77;
tr132:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st83;
st83:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof83;
case 83:
#line 2981 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 112: goto tr133;
	}
	goto tr77;
tr133:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st84;
st84:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof84;
case 84:
#line 2998 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 115: goto tr134;
	}
	goto tr77;
tr134:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st85;
st85:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof85;
case 85:
#line 3015 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 105: goto tr135;
	}
	goto tr77;
tr135:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st86;
st86:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof86;
case 86:
#line 3032 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 122: goto tr136;
	}
	goto tr77;
tr136:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st87;
st87:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof87;
case 87:
#line 3049 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 101: goto tr137;
	}
	goto tr77;
tr137:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st88;
st88:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof88;
case 88:
#line 3066 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr138;
		case 32: goto tr138;
		case 34: goto st51;
		case 92: goto tr79;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr138;
	goto tr77;
tr138:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st89;
st89:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof89;
case 89:
#line 3086 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr138;
		case 32: goto tr138;
		case 34: goto st51;
		case 92: goto tr79;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr139;
	} else if ( (*( state.p)) >= 9 )
		goto tr138;
	goto tr77;
tr139:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st90;
tr142:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st90;
st90:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof90;
case 90:
#line 3119 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr140;
		case 32: goto tr140;
		case 34: goto st51;
		case 46: goto tr141;
		case 92: goto tr79;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr142;
	} else if ( (*( state.p)) >= 9 )
		goto tr140;
	goto tr77;
tr143:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st91;
tr140:
#line 172 "configparser.rl"
	{ spe.clumpsize.mean = ::atof(state.match.c_str()); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st91;
st91:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof91;
case 91:
#line 3151 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr143;
		case 32: goto tr143;
		case 34: goto st51;
		case 92: goto tr79;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr144;
	} else if ( (*( state.p)) >= 9 )
		goto tr143;
	goto tr77;
tr144:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st92;
tr147:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st92;
st92:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof92;
case 92:
#line 3184 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr145;
		case 32: goto tr145;
		case 34: goto st51;
		case 46: goto tr146;
		case 59: goto tr148;
		case 92: goto tr79;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr147;
	} else if ( (*( state.p)) >= 9 )
		goto tr145;
	goto tr77;
tr146:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st93;
st93:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof93;
case 93:
#line 3209 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr149;
	goto tr77;
tr149:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st94;
st94:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof94;
case 94:
#line 3227 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr145;
		case 32: goto tr145;
		case 34: goto st51;
		case 59: goto tr148;
		case 92: goto tr79;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr149;
	} else if ( (*( state.p)) >= 9 )
		goto tr145;
	goto tr77;
tr141:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st95;
st95:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof95;
case 95:
#line 3251 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr150;
	goto tr77;
tr150:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st96;
st96:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof96;
case 96:
#line 3269 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr140;
		case 32: goto tr140;
		case 34: goto st51;
		case 92: goto tr79;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr150;
	} else if ( (*( state.p)) >= 9 )
		goto tr140;
	goto tr77;
tr130:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st97;
st97:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof97;
case 97:
#line 3292 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 109: goto tr151;
		case 117: goto tr152;
	}
	goto tr77;
tr151:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st98;
st98:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof98;
case 98:
#line 3310 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 112: goto tr153;
	}
	goto tr77;
tr153:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st99;
st99:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof99;
case 99:
#line 3327 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 97: goto tr154;
	}
	goto tr77;
tr154:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st100;
st100:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof100;
case 100:
#line 3344 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 110: goto tr155;
	}
	goto tr77;
tr155:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st101;
st101:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof101;
case 101:
#line 3361 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 105: goto tr156;
	}
	goto tr77;
tr156:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st102;
st102:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof102;
case 102:
#line 3378 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 111: goto tr157;
	}
	goto tr77;
tr157:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st103;
st103:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof103;
case 103:
#line 3395 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 110: goto tr158;
	}
	goto tr77;
tr158:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st104;
st104:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof104;
case 104:
#line 3412 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr159;
		case 32: goto tr159;
		case 34: goto st51;
		case 92: goto tr79;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr159;
	goto tr77;
tr160:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st105;
tr159:
#line 176 "configparser.rl"
	{ spe.companion.push_back(Species::companion_t()); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st105;
st105:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof105;
case 105:
#line 3440 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr160;
		case 32: goto tr160;
		case 34: goto st106;
		case 92: goto tr79;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr160;
	goto tr77;
st106:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof106;
case 106:
	switch( (*( state.p)) ) {
		case 13: goto tr162;
		case 32: goto tr162;
		case 34: goto tr75;
		case 92: goto tr76;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr162;
	goto tr74;
tr152:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st107;
st107:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof107;
case 107:
#line 3473 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 110: goto tr163;
	}
	goto tr77;
tr163:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st108;
st108:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof108;
case 108:
#line 3490 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 116: goto tr164;
	}
	goto tr77;
tr164:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st109;
st109:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof109;
case 109:
#line 3507 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr165;
		case 32: goto tr165;
		case 34: goto st51;
		case 92: goto tr79;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr165;
	goto tr77;
tr165:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st110;
st110:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof110;
case 110:
#line 3527 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr165;
		case 32: goto tr165;
		case 34: goto st51;
		case 92: goto tr79;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr166;
	} else if ( (*( state.p)) >= 9 )
		goto tr165;
	goto tr77;
tr166:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st111;
tr168:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st111;
st111:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof111;
case 111:
#line 3560 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr167;
		case 32: goto tr167;
		case 34: goto st51;
		case 59: goto tr169;
		case 92: goto tr79;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr168;
	} else if ( (*( state.p)) >= 9 )
		goto tr167;
	goto tr77;
tr101:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st112;
st112:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof112;
case 112:
#line 3584 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 97: goto tr170;
	}
	goto tr77;
tr170:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st113;
st113:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof113;
case 113:
#line 3601 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 98: goto tr171;
	}
	goto tr77;
tr171:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st114;
st114:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof114;
case 114:
#line 3618 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 105: goto tr172;
	}
	goto tr77;
tr172:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st115;
st115:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof115;
case 115:
#line 3635 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 116: goto tr173;
	}
	goto tr77;
tr173:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st116;
st116:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof116;
case 116:
#line 3652 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 97: goto tr174;
	}
	goto tr77;
tr174:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st117;
st117:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof117;
case 117:
#line 3669 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 116: goto tr175;
	}
	goto tr77;
tr175:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st118;
st118:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof118;
case 118:
#line 3686 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr176;
		case 32: goto tr176;
		case 34: goto st51;
		case 92: goto tr79;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr176;
	goto tr77;
tr176:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st119;
st119:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof119;
case 119:
#line 3706 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr176;
		case 32: goto tr176;
		case 34: goto st51;
		case 92: goto tr79;
		case 99: goto tr177;
		case 102: goto tr178;
		case 115: goto tr179;
		case 119: goto tr180;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr176;
	goto tr77;
tr177:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st120;
st120:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof120;
case 120:
#line 3730 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 111: goto tr181;
	}
	goto tr77;
tr181:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st121;
st121:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof121;
case 121:
#line 3747 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 114: goto tr182;
	}
	goto tr77;
tr182:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st122;
st122:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof122;
case 122:
#line 3764 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 110: goto tr183;
	}
	goto tr77;
tr183:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st123;
st123:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof123;
case 123:
#line 3781 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 101: goto tr184;
	}
	goto tr77;
tr184:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st124;
st124:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof124;
case 124:
#line 3798 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 114: goto tr185;
	}
	goto tr77;
tr185:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st125;
st125:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof125;
case 125:
#line 3815 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr186;
		case 32: goto tr186;
		case 34: goto st51;
		case 59: goto tr187;
		case 92: goto tr79;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr186;
	goto tr77;
tr178:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st126;
st126:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof126;
case 126:
#line 3836 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 108: goto tr188;
	}
	goto tr77;
tr188:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st127;
st127:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof127;
case 127:
#line 3853 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 111: goto tr189;
	}
	goto tr77;
tr189:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st128;
st128:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof128;
case 128:
#line 3870 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 111: goto tr190;
	}
	goto tr77;
tr190:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st129;
st129:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof129;
case 129:
#line 3887 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 114: goto tr191;
	}
	goto tr77;
tr191:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st130;
st130:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof130;
case 130:
#line 3904 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr192;
		case 32: goto tr192;
		case 34: goto st51;
		case 59: goto tr193;
		case 92: goto tr79;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr192;
	goto tr77;
tr179:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st131;
st131:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof131;
case 131:
#line 3925 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 104: goto tr194;
	}
	goto tr77;
tr194:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st132;
st132:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof132;
case 132:
#line 3942 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 111: goto tr195;
	}
	goto tr77;
tr195:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st133;
st133:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof133;
case 133:
#line 3959 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 114: goto tr196;
	}
	goto tr77;
tr196:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st134;
st134:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof134;
case 134:
#line 3976 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 101: goto tr197;
	}
	goto tr77;
tr197:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st135;
st135:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof135;
case 135:
#line 3993 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 108: goto tr198;
	}
	goto tr77;
tr198:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st136;
st136:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof136;
case 136:
#line 4010 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 105: goto tr199;
	}
	goto tr77;
tr199:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st137;
st137:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof137;
case 137:
#line 4027 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 110: goto tr200;
	}
	goto tr77;
tr200:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st138;
st138:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof138;
case 138:
#line 4044 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 101: goto tr201;
	}
	goto tr77;
tr201:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st139;
st139:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof139;
case 139:
#line 4061 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr202;
		case 32: goto tr202;
		case 34: goto st51;
		case 59: goto tr203;
		case 92: goto tr79;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr202;
	goto tr77;
tr180:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st140;
st140:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof140;
case 140:
#line 4082 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 97: goto tr204;
	}
	goto tr77;
tr204:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st141;
st141:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof141;
case 141:
#line 4099 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 108: goto tr205;
		case 116: goto tr206;
	}
	goto tr77;
tr205:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st142;
st142:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof142;
case 142:
#line 4117 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 107: goto tr207;
	}
	goto tr77;
tr207:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st143;
st143:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof143;
case 143:
#line 4134 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr208;
		case 32: goto tr208;
		case 34: goto st51;
		case 59: goto tr209;
		case 92: goto tr79;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr208;
	goto tr77;
tr206:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st144;
st144:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof144;
case 144:
#line 4155 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 101: goto tr210;
	}
	goto tr77;
tr210:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st145;
st145:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof145;
case 145:
#line 4172 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 114: goto tr211;
	}
	goto tr77;
tr211:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st146;
st146:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof146;
case 146:
#line 4189 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr212;
		case 32: goto tr212;
		case 34: goto st51;
		case 59: goto tr213;
		case 92: goto tr79;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr212;
	goto tr77;
tr102:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st147;
st147:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof147;
case 147:
#line 4210 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 100: goto tr214;
	}
	goto tr77;
tr214:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st148;
st148:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof148;
case 148:
#line 4227 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 108: goto tr215;
	}
	goto tr77;
tr215:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st149;
st149:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof149;
case 149:
#line 4244 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 101: goto tr216;
	}
	goto tr77;
tr216:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st150;
st150:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof150;
case 150:
#line 4261 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 95: goto tr217;
	}
	goto tr77;
tr217:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st151;
st151:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof151;
case 151:
#line 4278 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 97: goto tr218;
	}
	goto tr77;
tr218:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st152;
st152:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof152;
case 152:
#line 4295 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 105: goto tr219;
	}
	goto tr77;
tr219:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st153;
st153:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof153;
case 153:
#line 4312 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr220;
		case 32: goto tr220;
		case 34: goto st51;
		case 92: goto tr79;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr220;
	goto tr77;
tr220:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st154;
st154:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof154;
case 154:
#line 4332 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr220;
		case 32: goto tr220;
		case 34: goto st51;
		case 92: goto tr79;
		case 110: goto tr221;
		case 114: goto tr222;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr220;
	goto tr77;
tr221:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st155;
st155:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof155;
case 155:
#line 4354 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 111: goto tr223;
	}
	goto tr77;
tr223:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st156;
st156:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof156;
case 156:
#line 4371 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 110: goto tr224;
	}
	goto tr77;
tr224:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st157;
st157:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof157;
case 157:
#line 4388 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 101: goto tr225;
	}
	goto tr77;
tr225:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st158;
st158:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof158;
case 158:
#line 4405 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr226;
		case 32: goto tr226;
		case 34: goto st51;
		case 59: goto tr227;
		case 92: goto tr79;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr226;
	goto tr77;
tr222:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st159;
st159:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof159;
case 159:
#line 4426 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 97: goto tr228;
	}
	goto tr77;
tr228:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st160;
st160:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof160;
case 160:
#line 4443 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 110: goto tr229;
	}
	goto tr77;
tr229:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st161;
st161:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof161;
case 161:
#line 4460 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 100: goto tr230;
	}
	goto tr77;
tr230:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st162;
st162:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof162;
case 162:
#line 4477 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 111: goto tr231;
	}
	goto tr77;
tr231:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st163;
st163:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof163;
case 163:
#line 4494 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 109: goto tr232;
	}
	goto tr77;
tr232:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st164;
st164:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof164;
case 164:
#line 4511 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr233;
		case 32: goto tr233;
		case 34: goto st51;
		case 59: goto tr234;
		case 92: goto tr79;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr233;
	goto tr77;
tr103:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st165;
st165:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof165;
case 165:
#line 4532 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 111: goto tr235;
	}
	goto tr77;
tr235:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st166;
st166:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof166;
case 166:
#line 4549 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 118: goto tr236;
	}
	goto tr77;
tr236:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st167;
st167:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof167;
case 167:
#line 4566 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 101: goto tr237;
	}
	goto tr77;
tr237:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st168;
st168:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof168;
case 168:
#line 4583 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr238;
		case 32: goto tr238;
		case 34: goto st51;
		case 92: goto tr79;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr238;
	goto tr77;
tr238:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st169;
st169:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof169;
case 169:
#line 4603 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr238;
		case 32: goto tr238;
		case 34: goto st51;
		case 92: goto tr79;
		case 97: goto tr239;
		case 102: goto tr240;
		case 119: goto tr241;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr238;
	goto tr77;
tr239:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st170;
st170:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof170;
case 170:
#line 4626 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 110: goto tr242;
	}
	goto tr77;
tr242:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st171;
st171:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof171;
case 171:
#line 4643 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 121: goto tr243;
	}
	goto tr77;
tr243:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st172;
st172:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof172;
case 172:
#line 4660 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr244;
		case 32: goto tr244;
		case 34: goto st51;
		case 59: goto tr245;
		case 92: goto tr79;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr244;
	goto tr77;
tr240:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st173;
st173:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof173;
case 173:
#line 4681 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 108: goto tr246;
	}
	goto tr77;
tr246:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st174;
st174:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof174;
case 174:
#line 4698 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 111: goto tr247;
	}
	goto tr77;
tr247:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st175;
st175:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof175;
case 175:
#line 4715 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 111: goto tr248;
	}
	goto tr77;
tr248:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st176;
st176:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof176;
case 176:
#line 4732 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 114: goto tr249;
	}
	goto tr77;
tr249:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st177;
st177:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof177;
case 177:
#line 4749 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr250;
		case 32: goto tr250;
		case 34: goto st51;
		case 59: goto tr251;
		case 92: goto tr79;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr250;
	goto tr77;
tr241:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st178;
st178:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof178;
case 178:
#line 4770 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 97: goto tr252;
	}
	goto tr77;
tr252:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st179;
st179:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof179;
case 179:
#line 4787 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 116: goto tr253;
	}
	goto tr77;
tr253:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st180;
st180:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof180;
case 180:
#line 4804 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 101: goto tr254;
	}
	goto tr77;
tr254:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st181;
st181:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof181;
case 181:
#line 4821 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 114: goto tr255;
	}
	goto tr77;
tr255:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st182;
st182:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof182;
case 182:
#line 4838 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr256;
		case 32: goto tr256;
		case 34: goto st51;
		case 59: goto tr257;
		case 92: goto tr79;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr256;
	goto tr77;
tr104:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st183;
st183:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof183;
case 183:
#line 4859 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 97: goto tr258;
	}
	goto tr77;
tr258:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st184;
st184:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof184;
case 184:
#line 4876 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 109: goto tr259;
	}
	goto tr77;
tr259:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st185;
st185:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof185;
case 185:
#line 4893 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 101: goto tr260;
	}
	goto tr77;
tr260:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st186;
st186:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof186;
case 186:
#line 4910 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr261;
		case 32: goto tr261;
		case 34: goto st51;
		case 92: goto tr79;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr261;
	goto tr77;
tr261:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st187;
st187:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof187;
case 187:
#line 4930 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr261;
		case 32: goto tr261;
		case 34: goto st188;
		case 92: goto tr79;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr261;
	goto tr77;
st188:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof188;
case 188:
	switch( (*( state.p)) ) {
		case 13: goto tr264;
		case 32: goto tr264;
		case 34: goto tr265;
		case 92: goto tr266;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr264;
	goto tr263;
tr263:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st189;
tr267:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st189;
st189:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof189;
case 189:
#line 4973 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
	}
	goto tr267;
tr265:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st190;
st190:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof190;
case 190:
#line 4989 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr270;
		case 32: goto tr270;
		case 59: goto tr271;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr270;
	goto st0;
tr266:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st191;
tr269:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st191;
st191:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof191;
case 191:
#line 5018 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr272;
		case 92: goto tr269;
	}
	goto tr267;
tr272:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st192;
st192:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof192;
case 192:
#line 5034 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr273;
		case 32: goto tr273;
		case 34: goto st190;
		case 59: goto tr274;
		case 92: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr273;
	goto tr267;
tr275:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st193;
tr987:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 178 "configparser.rl"
	{ spe.companion.back().chance = ::atof(state.match.c_str()); }
	goto st193;
tr347:
#line 162 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st193;
tr273:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 163 "configparser.rl"
	{ spe.name = state.match; }
	goto st193;
tr294:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 150 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st193;
tr306:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 151 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st193;
tr324:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 173 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
	goto st193;
tr366:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 146 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st193;
tr372:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 144 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st193;
tr382:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 147 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st193;
tr388:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 143 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st193;
tr392:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 145 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st193;
tr406:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 154 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st193;
tr413:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 155 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st193;
tr424:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st193;
tr430:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st193;
tr436:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 160 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st193;
tr443:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 163 "configparser.rl"
	{ spe.name = state.match; }
	goto st193;
tr451:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 169 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
	goto st193;
tr863:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 130 "configparser.rl"
	{ add_color(spe.skin.fore, 4); }
	goto st193;
tr868:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 132 "configparser.rl"
	{ add_color(spe.skin.fore, 6); }
	goto st193;
tr874:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 128 "configparser.rl"
	{ add_color(spe.skin.fore, 2); }
	goto st193;
tr882:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 131 "configparser.rl"
	{ add_color(spe.skin.fore, 5); }
	goto st193;
tr886:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 127 "configparser.rl"
	{ add_color(spe.skin.fore, 1); }
	goto st193;
tr892:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 133 "configparser.rl"
	{ add_color(spe.skin.fore, 7); }
	goto st193;
tr899:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 129 "configparser.rl"
	{ add_color(spe.skin.fore, 3); }
	goto st193;
tr983:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 186 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st193;
st193:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof193;
case 193:
#line 5267 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr275;
		case 32: goto tr275;
		case 34: goto st190;
		case 59: goto tr276;
		case 92: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr275;
	goto tr267;
tr276:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st822;
tr990:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 178 "configparser.rl"
	{ spe.companion.back().chance = ::atof(state.match.c_str()); }
	goto st822;
tr349:
#line 162 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st822;
tr274:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 163 "configparser.rl"
	{ spe.name = state.match; }
	goto st822;
tr295:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 150 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st822;
tr307:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 151 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st822;
tr327:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 173 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
	goto st822;
tr367:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 146 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st822;
tr373:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 144 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st822;
tr383:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 147 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st822;
tr389:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 143 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st822;
tr393:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 145 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st822;
tr407:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 154 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st822;
tr414:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 155 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st822;
tr425:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st822;
tr431:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st822;
tr437:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 160 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st822;
tr444:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 163 "configparser.rl"
	{ spe.name = state.match; }
	goto st822;
tr453:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 169 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
	goto st822;
tr864:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 130 "configparser.rl"
	{ add_color(spe.skin.fore, 4); }
	goto st822;
tr869:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 132 "configparser.rl"
	{ add_color(spe.skin.fore, 6); }
	goto st822;
tr875:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 128 "configparser.rl"
	{ add_color(spe.skin.fore, 2); }
	goto st822;
tr883:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 131 "configparser.rl"
	{ add_color(spe.skin.fore, 5); }
	goto st822;
tr887:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 127 "configparser.rl"
	{ add_color(spe.skin.fore, 1); }
	goto st822;
tr893:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 133 "configparser.rl"
	{ add_color(spe.skin.fore, 7); }
	goto st822;
tr900:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 129 "configparser.rl"
	{ add_color(spe.skin.fore, 3); }
	goto st822;
tr984:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 186 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st822;
st822:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof822;
case 822:
#line 5500 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr277;
		case 32: goto tr277;
		case 34: goto st190;
		case 92: goto tr269;
		case 97: goto tr278;
		case 99: goto tr279;
		case 104: goto tr280;
		case 105: goto tr281;
		case 109: goto tr282;
		case 110: goto tr283;
		case 114: goto tr284;
		case 115: goto tr285;
		case 125: goto tr286;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr277;
	goto tr267;
tr277:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st194;
st194:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof194;
case 194:
#line 5529 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr277;
		case 32: goto tr277;
		case 34: goto st190;
		case 92: goto tr269;
		case 97: goto tr278;
		case 99: goto tr279;
		case 104: goto tr280;
		case 105: goto tr281;
		case 109: goto tr282;
		case 110: goto tr283;
		case 114: goto tr284;
		case 115: goto tr285;
		case 125: goto tr286;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr277;
	goto tr267;
tr278:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st195;
st195:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof195;
case 195:
#line 5558 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 105: goto tr287;
	}
	goto tr267;
tr287:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st196;
st196:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof196;
case 196:
#line 5575 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr288;
		case 32: goto tr288;
		case 34: goto st190;
		case 92: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr288;
	goto tr267;
tr288:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st197;
st197:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof197;
case 197:
#line 5595 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr288;
		case 32: goto tr288;
		case 34: goto st190;
		case 92: goto tr269;
		case 110: goto tr289;
		case 115: goto tr290;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr288;
	goto tr267;
tr289:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st198;
st198:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof198;
case 198:
#line 5617 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 111: goto tr291;
	}
	goto tr267;
tr291:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st199;
st199:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof199;
case 199:
#line 5634 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 110: goto tr292;
	}
	goto tr267;
tr292:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st200;
st200:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof200;
case 200:
#line 5651 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 101: goto tr293;
	}
	goto tr267;
tr293:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st201;
st201:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof201;
case 201:
#line 5668 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr294;
		case 32: goto tr294;
		case 34: goto st190;
		case 59: goto tr295;
		case 92: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr294;
	goto tr267;
tr290:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st202;
st202:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof202;
case 202:
#line 5689 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 101: goto tr296;
	}
	goto tr267;
tr296:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st203;
st203:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof203;
case 203:
#line 5706 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 101: goto tr297;
	}
	goto tr267;
tr297:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st204;
st204:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof204;
case 204:
#line 5723 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 107: goto tr298;
	}
	goto tr267;
tr298:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st205;
st205:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof205;
case 205:
#line 5740 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 95: goto tr299;
	}
	goto tr267;
tr299:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st206;
st206:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof206;
case 206:
#line 5757 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 112: goto tr300;
	}
	goto tr267;
tr300:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st207;
st207:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof207;
case 207:
#line 5774 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 108: goto tr301;
	}
	goto tr267;
tr301:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st208;
st208:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof208;
case 208:
#line 5791 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 97: goto tr302;
	}
	goto tr267;
tr302:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st209;
st209:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof209;
case 209:
#line 5808 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 121: goto tr303;
	}
	goto tr267;
tr303:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st210;
st210:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof210;
case 210:
#line 5825 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 101: goto tr304;
	}
	goto tr267;
tr304:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st211;
st211:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof211;
case 211:
#line 5842 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 114: goto tr305;
	}
	goto tr267;
tr305:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st212;
st212:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof212;
case 212:
#line 5859 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr306;
		case 32: goto tr306;
		case 34: goto st190;
		case 59: goto tr307;
		case 92: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr306;
	goto tr267;
tr279:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st213;
st213:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof213;
case 213:
#line 5880 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 108: goto tr308;
		case 111: goto tr309;
	}
	goto tr267;
tr308:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st214;
st214:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof214;
case 214:
#line 5898 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 117: goto tr310;
	}
	goto tr267;
tr310:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st215;
st215:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof215;
case 215:
#line 5915 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 109: goto tr311;
	}
	goto tr267;
tr311:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st216;
st216:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof216;
case 216:
#line 5932 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 112: goto tr312;
	}
	goto tr267;
tr312:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st217;
st217:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof217;
case 217:
#line 5949 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 115: goto tr313;
	}
	goto tr267;
tr313:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st218;
st218:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof218;
case 218:
#line 5966 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 105: goto tr314;
	}
	goto tr267;
tr314:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st219;
st219:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof219;
case 219:
#line 5983 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 122: goto tr315;
	}
	goto tr267;
tr315:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st220;
st220:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof220;
case 220:
#line 6000 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 101: goto tr316;
	}
	goto tr267;
tr316:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st221;
st221:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof221;
case 221:
#line 6017 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr317;
		case 32: goto tr317;
		case 34: goto st190;
		case 92: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr317;
	goto tr267;
tr317:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st222;
st222:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof222;
case 222:
#line 6037 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr317;
		case 32: goto tr317;
		case 34: goto st190;
		case 92: goto tr269;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr318;
	} else if ( (*( state.p)) >= 9 )
		goto tr317;
	goto tr267;
tr321:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st223;
tr318:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st223;
st223:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof223;
case 223:
#line 6070 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr319;
		case 32: goto tr319;
		case 34: goto st190;
		case 46: goto tr320;
		case 92: goto tr269;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr321;
	} else if ( (*( state.p)) >= 9 )
		goto tr319;
	goto tr267;
tr322:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st224;
tr319:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 172 "configparser.rl"
	{ spe.clumpsize.mean = ::atof(state.match.c_str()); }
	goto st224;
st224:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof224;
case 224:
#line 6102 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr322;
		case 32: goto tr322;
		case 34: goto st190;
		case 92: goto tr269;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr323;
	} else if ( (*( state.p)) >= 9 )
		goto tr322;
	goto tr267;
tr326:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st225;
tr323:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st225;
st225:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof225;
case 225:
#line 6135 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr324;
		case 32: goto tr324;
		case 34: goto st190;
		case 46: goto tr325;
		case 59: goto tr327;
		case 92: goto tr269;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr326;
	} else if ( (*( state.p)) >= 9 )
		goto tr324;
	goto tr267;
tr325:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st226;
st226:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof226;
case 226:
#line 6160 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr328;
	goto tr267;
tr328:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st227;
st227:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof227;
case 227:
#line 6178 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr324;
		case 32: goto tr324;
		case 34: goto st190;
		case 59: goto tr327;
		case 92: goto tr269;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr328;
	} else if ( (*( state.p)) >= 9 )
		goto tr324;
	goto tr267;
tr320:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st228;
st228:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof228;
case 228:
#line 6202 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr329;
	goto tr267;
tr329:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st229;
st229:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof229;
case 229:
#line 6220 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr319;
		case 32: goto tr319;
		case 34: goto st190;
		case 92: goto tr269;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr329;
	} else if ( (*( state.p)) >= 9 )
		goto tr319;
	goto tr267;
tr309:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st230;
st230:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof230;
case 230:
#line 6243 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 109: goto tr330;
		case 117: goto tr331;
	}
	goto tr267;
tr330:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st231;
st231:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof231;
case 231:
#line 6261 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 112: goto tr332;
	}
	goto tr267;
tr332:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st232;
st232:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof232;
case 232:
#line 6278 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 97: goto tr333;
	}
	goto tr267;
tr333:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st233;
st233:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof233;
case 233:
#line 6295 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 110: goto tr334;
	}
	goto tr267;
tr334:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st234;
st234:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof234;
case 234:
#line 6312 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 105: goto tr335;
	}
	goto tr267;
tr335:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st235;
st235:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof235;
case 235:
#line 6329 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 111: goto tr336;
	}
	goto tr267;
tr336:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st236;
st236:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof236;
case 236:
#line 6346 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 110: goto tr337;
	}
	goto tr267;
tr337:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st237;
st237:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof237;
case 237:
#line 6363 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr338;
		case 32: goto tr338;
		case 34: goto st190;
		case 92: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr338;
	goto tr267;
tr339:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st238;
tr338:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 176 "configparser.rl"
	{ spe.companion.push_back(Species::companion_t()); }
	goto st238;
st238:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof238;
case 238:
#line 6391 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr339;
		case 32: goto tr339;
		case 34: goto st239;
		case 92: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr339;
	goto tr267;
st239:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof239;
case 239:
	switch( (*( state.p)) ) {
		case 13: goto tr341;
		case 32: goto tr341;
		case 34: goto tr75;
		case 59: goto tr342;
		case 92: goto tr76;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr341;
	goto tr74;
tr331:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st240;
st240:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof240;
case 240:
#line 6425 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 110: goto tr343;
	}
	goto tr267;
tr343:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st241;
st241:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof241;
case 241:
#line 6442 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 116: goto tr344;
	}
	goto tr267;
tr344:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st242;
st242:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof242;
case 242:
#line 6459 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr345;
		case 32: goto tr345;
		case 34: goto st190;
		case 92: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr345;
	goto tr267;
tr345:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st243;
st243:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof243;
case 243:
#line 6479 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr345;
		case 32: goto tr345;
		case 34: goto st190;
		case 92: goto tr269;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr346;
	} else if ( (*( state.p)) >= 9 )
		goto tr345;
	goto tr267;
tr346:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st244;
tr348:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st244;
st244:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof244;
case 244:
#line 6512 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr347;
		case 32: goto tr347;
		case 34: goto st190;
		case 59: goto tr349;
		case 92: goto tr269;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr348;
	} else if ( (*( state.p)) >= 9 )
		goto tr347;
	goto tr267;
tr280:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st245;
st245:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof245;
case 245:
#line 6536 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 97: goto tr350;
	}
	goto tr267;
tr350:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st246;
st246:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof246;
case 246:
#line 6553 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 98: goto tr351;
	}
	goto tr267;
tr351:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st247;
st247:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof247;
case 247:
#line 6570 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 105: goto tr352;
	}
	goto tr267;
tr352:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st248;
st248:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof248;
case 248:
#line 6587 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 116: goto tr353;
	}
	goto tr267;
tr353:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st249;
st249:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof249;
case 249:
#line 6604 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 97: goto tr354;
	}
	goto tr267;
tr354:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st250;
st250:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof250;
case 250:
#line 6621 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 116: goto tr355;
	}
	goto tr267;
tr355:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st251;
st251:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof251;
case 251:
#line 6638 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr356;
		case 32: goto tr356;
		case 34: goto st190;
		case 92: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr356;
	goto tr267;
tr356:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st252;
st252:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof252;
case 252:
#line 6658 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr356;
		case 32: goto tr356;
		case 34: goto st190;
		case 92: goto tr269;
		case 99: goto tr357;
		case 102: goto tr358;
		case 115: goto tr359;
		case 119: goto tr360;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr356;
	goto tr267;
tr357:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st253;
st253:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof253;
case 253:
#line 6682 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 111: goto tr361;
	}
	goto tr267;
tr361:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st254;
st254:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof254;
case 254:
#line 6699 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 114: goto tr362;
	}
	goto tr267;
tr362:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st255;
st255:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof255;
case 255:
#line 6716 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 110: goto tr363;
	}
	goto tr267;
tr363:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st256;
st256:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof256;
case 256:
#line 6733 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 101: goto tr364;
	}
	goto tr267;
tr364:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st257;
st257:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof257;
case 257:
#line 6750 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 114: goto tr365;
	}
	goto tr267;
tr365:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st258;
st258:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof258;
case 258:
#line 6767 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr366;
		case 32: goto tr366;
		case 34: goto st190;
		case 59: goto tr367;
		case 92: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr366;
	goto tr267;
tr358:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st259;
st259:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof259;
case 259:
#line 6788 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 108: goto tr368;
	}
	goto tr267;
tr368:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st260;
st260:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof260;
case 260:
#line 6805 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 111: goto tr369;
	}
	goto tr267;
tr369:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st261;
st261:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof261;
case 261:
#line 6822 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 111: goto tr370;
	}
	goto tr267;
tr370:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st262;
st262:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof262;
case 262:
#line 6839 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 114: goto tr371;
	}
	goto tr267;
tr371:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st263;
st263:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof263;
case 263:
#line 6856 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr372;
		case 32: goto tr372;
		case 34: goto st190;
		case 59: goto tr373;
		case 92: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr372;
	goto tr267;
tr359:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st264;
st264:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof264;
case 264:
#line 6877 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 104: goto tr374;
	}
	goto tr267;
tr374:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st265;
st265:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof265;
case 265:
#line 6894 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 111: goto tr375;
	}
	goto tr267;
tr375:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st266;
st266:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof266;
case 266:
#line 6911 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 114: goto tr376;
	}
	goto tr267;
tr376:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st267;
st267:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof267;
case 267:
#line 6928 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 101: goto tr377;
	}
	goto tr267;
tr377:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st268;
st268:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof268;
case 268:
#line 6945 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 108: goto tr378;
	}
	goto tr267;
tr378:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st269;
st269:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof269;
case 269:
#line 6962 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 105: goto tr379;
	}
	goto tr267;
tr379:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st270;
st270:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof270;
case 270:
#line 6979 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 110: goto tr380;
	}
	goto tr267;
tr380:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st271;
st271:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof271;
case 271:
#line 6996 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 101: goto tr381;
	}
	goto tr267;
tr381:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st272;
st272:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof272;
case 272:
#line 7013 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr382;
		case 32: goto tr382;
		case 34: goto st190;
		case 59: goto tr383;
		case 92: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr382;
	goto tr267;
tr360:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st273;
st273:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof273;
case 273:
#line 7034 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 97: goto tr384;
	}
	goto tr267;
tr384:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st274;
st274:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof274;
case 274:
#line 7051 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 108: goto tr385;
		case 116: goto tr386;
	}
	goto tr267;
tr385:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st275;
st275:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof275;
case 275:
#line 7069 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 107: goto tr387;
	}
	goto tr267;
tr387:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st276;
st276:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof276;
case 276:
#line 7086 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr388;
		case 32: goto tr388;
		case 34: goto st190;
		case 59: goto tr389;
		case 92: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr388;
	goto tr267;
tr386:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st277;
st277:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof277;
case 277:
#line 7107 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 101: goto tr390;
	}
	goto tr267;
tr390:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st278;
st278:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof278;
case 278:
#line 7124 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 114: goto tr391;
	}
	goto tr267;
tr391:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st279;
st279:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof279;
case 279:
#line 7141 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr392;
		case 32: goto tr392;
		case 34: goto st190;
		case 59: goto tr393;
		case 92: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr392;
	goto tr267;
tr281:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st280;
st280:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof280;
case 280:
#line 7162 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 100: goto tr394;
	}
	goto tr267;
tr394:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st281;
st281:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof281;
case 281:
#line 7179 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 108: goto tr395;
	}
	goto tr267;
tr395:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st282;
st282:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof282;
case 282:
#line 7196 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 101: goto tr396;
	}
	goto tr267;
tr396:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st283;
st283:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof283;
case 283:
#line 7213 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 95: goto tr397;
	}
	goto tr267;
tr397:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st284;
st284:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof284;
case 284:
#line 7230 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 97: goto tr398;
	}
	goto tr267;
tr398:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st285;
st285:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof285;
case 285:
#line 7247 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 105: goto tr399;
	}
	goto tr267;
tr399:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st286;
st286:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof286;
case 286:
#line 7264 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr400;
		case 32: goto tr400;
		case 34: goto st190;
		case 92: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr400;
	goto tr267;
tr400:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st287;
st287:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof287;
case 287:
#line 7284 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr400;
		case 32: goto tr400;
		case 34: goto st190;
		case 92: goto tr269;
		case 110: goto tr401;
		case 114: goto tr402;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr400;
	goto tr267;
tr401:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st288;
st288:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof288;
case 288:
#line 7306 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 111: goto tr403;
	}
	goto tr267;
tr403:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st289;
st289:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof289;
case 289:
#line 7323 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 110: goto tr404;
	}
	goto tr267;
tr404:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st290;
st290:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof290;
case 290:
#line 7340 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 101: goto tr405;
	}
	goto tr267;
tr405:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st291;
st291:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof291;
case 291:
#line 7357 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr406;
		case 32: goto tr406;
		case 34: goto st190;
		case 59: goto tr407;
		case 92: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr406;
	goto tr267;
tr402:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st292;
st292:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof292;
case 292:
#line 7378 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 97: goto tr408;
	}
	goto tr267;
tr408:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st293;
st293:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof293;
case 293:
#line 7395 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 110: goto tr409;
	}
	goto tr267;
tr409:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st294;
st294:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof294;
case 294:
#line 7412 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 100: goto tr410;
	}
	goto tr267;
tr410:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st295;
st295:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof295;
case 295:
#line 7429 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 111: goto tr411;
	}
	goto tr267;
tr411:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st296;
st296:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof296;
case 296:
#line 7446 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 109: goto tr412;
	}
	goto tr267;
tr412:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st297;
st297:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof297;
case 297:
#line 7463 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr413;
		case 32: goto tr413;
		case 34: goto st190;
		case 59: goto tr414;
		case 92: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr413;
	goto tr267;
tr282:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st298;
st298:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof298;
case 298:
#line 7484 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 111: goto tr415;
	}
	goto tr267;
tr415:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st299;
st299:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof299;
case 299:
#line 7501 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 118: goto tr416;
	}
	goto tr267;
tr416:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st300;
st300:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof300;
case 300:
#line 7518 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 101: goto tr417;
	}
	goto tr267;
tr417:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st301;
st301:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof301;
case 301:
#line 7535 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr418;
		case 32: goto tr418;
		case 34: goto st190;
		case 92: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr418;
	goto tr267;
tr418:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st302;
st302:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof302;
case 302:
#line 7555 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr418;
		case 32: goto tr418;
		case 34: goto st190;
		case 92: goto tr269;
		case 97: goto tr419;
		case 102: goto tr420;
		case 119: goto tr421;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr418;
	goto tr267;
tr419:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st303;
st303:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof303;
case 303:
#line 7578 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 110: goto tr422;
	}
	goto tr267;
tr422:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st304;
st304:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof304;
case 304:
#line 7595 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 121: goto tr423;
	}
	goto tr267;
tr423:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st305;
st305:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof305;
case 305:
#line 7612 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr424;
		case 32: goto tr424;
		case 34: goto st190;
		case 59: goto tr425;
		case 92: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr424;
	goto tr267;
tr420:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st306;
st306:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof306;
case 306:
#line 7633 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 108: goto tr426;
	}
	goto tr267;
tr426:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st307;
st307:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof307;
case 307:
#line 7650 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 111: goto tr427;
	}
	goto tr267;
tr427:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st308;
st308:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof308;
case 308:
#line 7667 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 111: goto tr428;
	}
	goto tr267;
tr428:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st309;
st309:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof309;
case 309:
#line 7684 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 114: goto tr429;
	}
	goto tr267;
tr429:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st310;
st310:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof310;
case 310:
#line 7701 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr430;
		case 32: goto tr430;
		case 34: goto st190;
		case 59: goto tr431;
		case 92: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr430;
	goto tr267;
tr421:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st311;
st311:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof311;
case 311:
#line 7722 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 97: goto tr432;
	}
	goto tr267;
tr432:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st312;
st312:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof312;
case 312:
#line 7739 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 116: goto tr433;
	}
	goto tr267;
tr433:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st313;
st313:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof313;
case 313:
#line 7756 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 101: goto tr434;
	}
	goto tr267;
tr434:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st314;
st314:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof314;
case 314:
#line 7773 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 114: goto tr435;
	}
	goto tr267;
tr435:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st315;
st315:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof315;
case 315:
#line 7790 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr436;
		case 32: goto tr436;
		case 34: goto st190;
		case 59: goto tr437;
		case 92: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr436;
	goto tr267;
tr283:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st316;
st316:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof316;
case 316:
#line 7811 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 97: goto tr438;
	}
	goto tr267;
tr438:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st317;
st317:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof317;
case 317:
#line 7828 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 109: goto tr439;
	}
	goto tr267;
tr439:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st318;
st318:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof318;
case 318:
#line 7845 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 101: goto tr440;
	}
	goto tr267;
tr440:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st319;
st319:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof319;
case 319:
#line 7862 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr441;
		case 32: goto tr441;
		case 34: goto st190;
		case 92: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr441;
	goto tr267;
tr441:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st320;
st320:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof320;
case 320:
#line 7882 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr441;
		case 32: goto tr441;
		case 34: goto st321;
		case 92: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr441;
	goto tr267;
st321:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof321;
case 321:
	switch( (*( state.p)) ) {
		case 13: goto tr443;
		case 32: goto tr443;
		case 34: goto tr265;
		case 59: goto tr444;
		case 92: goto tr266;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr443;
	goto tr263;
tr284:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st322;
st322:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof322;
case 322:
#line 7916 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 97: goto tr445;
	}
	goto tr267;
tr445:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st323;
st323:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof323;
case 323:
#line 7933 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 110: goto tr446;
	}
	goto tr267;
tr446:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st324;
st324:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof324;
case 324:
#line 7950 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 103: goto tr447;
	}
	goto tr267;
tr447:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st325;
st325:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof325;
case 325:
#line 7967 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 101: goto tr448;
	}
	goto tr267;
tr448:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st326;
st326:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof326;
case 326:
#line 7984 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr449;
		case 32: goto tr449;
		case 34: goto st190;
		case 92: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr449;
	goto tr267;
tr449:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st327;
st327:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof327;
case 327:
#line 8004 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr449;
		case 32: goto tr449;
		case 34: goto st190;
		case 92: goto tr269;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr450;
	} else if ( (*( state.p)) >= 9 )
		goto tr449;
	goto tr267;
tr452:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st328;
tr450:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st328;
st328:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof328;
case 328:
#line 8037 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr451;
		case 32: goto tr451;
		case 34: goto st190;
		case 59: goto tr453;
		case 92: goto tr269;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr452;
	} else if ( (*( state.p)) >= 9 )
		goto tr451;
	goto tr267;
tr285:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st329;
st329:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof329;
case 329:
#line 8061 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 107: goto tr454;
	}
	goto tr267;
tr454:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st330;
st330:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof330;
case 330:
#line 8078 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 105: goto tr455;
	}
	goto tr267;
tr455:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st331;
st331:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof331;
case 331:
#line 8095 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 110: goto tr456;
	}
	goto tr267;
tr456:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st332;
st332:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof332;
case 332:
#line 8112 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr457;
		case 32: goto tr457;
		case 34: goto st190;
		case 92: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr457;
	goto tr267;
tr457:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st333;
st333:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof333;
case 333:
#line 8132 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr457;
		case 32: goto tr457;
		case 34: goto st334;
		case 92: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr457;
	goto tr267;
st334:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof334;
case 334:
	switch( (*( state.p)) ) {
		case 13: goto tr460;
		case 32: goto tr460;
		case 34: goto tr461;
		case 59: goto tr462;
		case 92: goto tr463;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr460;
	goto tr459;
tr459:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st335;
tr464:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st335;
st335:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof335;
case 335:
#line 8176 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
	}
	goto tr464;
tr461:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st336;
st336:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof336;
case 336:
#line 8192 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr467;
		case 32: goto tr467;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr467;
	goto st0;
tr467:
#line 140 "configparser.rl"
	{ spe.skin.text = state.match; }
	goto st337;
st337:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof337;
case 337:
#line 8208 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st337;
		case 32: goto st337;
		case 98: goto st338;
		case 100: goto st382;
		case 110: goto st385;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st337;
	goto st0;
st338:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof338;
case 338:
	if ( (*( state.p)) == 114 )
		goto st339;
	goto st0;
st339:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof339;
case 339:
	if ( (*( state.p)) == 105 )
		goto st340;
	goto st0;
st340:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof340;
case 340:
	if ( (*( state.p)) == 103 )
		goto st341;
	goto st0;
st341:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof341;
case 341:
	if ( (*( state.p)) == 104 )
		goto st342;
	goto st0;
st342:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof342;
case 342:
	if ( (*( state.p)) == 116 )
		goto st343;
	goto st0;
st343:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof343;
case 343:
	switch( (*( state.p)) ) {
		case 13: goto tr477;
		case 32: goto tr477;
		case 95: goto tr478;
		case 98: goto tr479;
		case 99: goto tr480;
		case 103: goto tr481;
		case 109: goto tr482;
		case 114: goto tr483;
		case 119: goto tr484;
		case 121: goto tr485;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr477;
	goto st0;
tr477:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st344;
tr539:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st344;
st344:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof344;
case 344:
#line 8285 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st344;
		case 32: goto st344;
		case 98: goto st345;
		case 99: goto st351;
		case 103: goto st355;
		case 109: goto st360;
		case 114: goto st367;
		case 119: goto st370;
		case 121: goto st375;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st344;
	goto st0;
tr479:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st345;
tr541:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st345;
st345:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof345;
case 345:
#line 8312 "configparser.h"
	if ( (*( state.p)) == 108 )
		goto st346;
	goto st0;
st346:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof346;
case 346:
	switch( (*( state.p)) ) {
		case 97: goto st347;
		case 117: goto st349;
	}
	goto st0;
st347:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof347;
case 347:
	if ( (*( state.p)) == 99 )
		goto st348;
	goto st0;
st348:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof348;
case 348:
	if ( (*( state.p)) == 107 )
		goto st22;
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
	switch( (*( state.p)) ) {
		case 13: goto tr499;
		case 32: goto tr499;
		case 59: goto tr500;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr499;
	goto st0;
tr480:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st351;
tr542:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st351;
st351:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof351;
case 351:
#line 8370 "configparser.h"
	if ( (*( state.p)) == 121 )
		goto st352;
	goto st0;
st352:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof352;
case 352:
	if ( (*( state.p)) == 97 )
		goto st353;
	goto st0;
st353:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof353;
case 353:
	if ( (*( state.p)) == 110 )
		goto st354;
	goto st0;
st354:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof354;
case 354:
	switch( (*( state.p)) ) {
		case 13: goto tr504;
		case 32: goto tr504;
		case 59: goto tr505;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr504;
	goto st0;
tr481:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st355;
tr543:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st355;
st355:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof355;
case 355:
#line 8412 "configparser.h"
	if ( (*( state.p)) == 114 )
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
	if ( (*( state.p)) == 110 )
		goto st359;
	goto st0;
st359:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof359;
case 359:
	switch( (*( state.p)) ) {
		case 13: goto tr510;
		case 32: goto tr510;
		case 59: goto tr511;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr510;
	goto st0;
tr482:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st360;
tr544:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st360;
st360:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof360;
case 360:
#line 8461 "configparser.h"
	if ( (*( state.p)) == 97 )
		goto st361;
	goto st0;
st361:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof361;
case 361:
	if ( (*( state.p)) == 103 )
		goto st362;
	goto st0;
st362:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof362;
case 362:
	if ( (*( state.p)) == 101 )
		goto st363;
	goto st0;
st363:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof363;
case 363:
	if ( (*( state.p)) == 110 )
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
	if ( (*( state.p)) == 97 )
		goto st366;
	goto st0;
st366:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof366;
case 366:
	switch( (*( state.p)) ) {
		case 13: goto tr518;
		case 32: goto tr518;
		case 59: goto tr519;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr518;
	goto st0;
tr483:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st367;
tr545:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st367;
st367:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof367;
case 367:
#line 8524 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st368;
	goto st0;
st368:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof368;
case 368:
	if ( (*( state.p)) == 100 )
		goto st369;
	goto st0;
st369:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof369;
case 369:
	switch( (*( state.p)) ) {
		case 13: goto tr522;
		case 32: goto tr522;
		case 59: goto tr523;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr522;
	goto st0;
tr484:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st370;
tr546:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st370;
st370:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof370;
case 370:
#line 8559 "configparser.h"
	if ( (*( state.p)) == 104 )
		goto st371;
	goto st0;
st371:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof371;
case 371:
	if ( (*( state.p)) == 105 )
		goto st372;
	goto st0;
st372:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof372;
case 372:
	if ( (*( state.p)) == 116 )
		goto st373;
	goto st0;
st373:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof373;
case 373:
	if ( (*( state.p)) == 101 )
		goto st374;
	goto st0;
st374:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof374;
case 374:
	switch( (*( state.p)) ) {
		case 13: goto tr528;
		case 32: goto tr528;
		case 59: goto tr529;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr528;
	goto st0;
tr485:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st375;
tr547:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st375;
st375:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof375;
case 375:
#line 8608 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st376;
	goto st0;
st376:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof376;
case 376:
	if ( (*( state.p)) == 108 )
		goto st377;
	goto st0;
st377:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof377;
case 377:
	if ( (*( state.p)) == 108 )
		goto st378;
	goto st0;
st378:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof378;
case 378:
	if ( (*( state.p)) == 111 )
		goto st379;
	goto st0;
st379:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof379;
case 379:
	if ( (*( state.p)) == 119 )
		goto st380;
	goto st0;
st380:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof380;
case 380:
	switch( (*( state.p)) ) {
		case 13: goto tr535;
		case 32: goto tr535;
		case 59: goto tr536;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr535;
	goto st0;
tr478:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st381;
tr540:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st381;
st381:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof381;
case 381:
#line 8664 "configparser.h"
	switch( (*( state.p)) ) {
		case 98: goto st345;
		case 99: goto st351;
		case 103: goto st355;
		case 109: goto st360;
		case 114: goto st367;
		case 119: goto st370;
		case 121: goto st375;
	}
	goto st0;
st382:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof382;
case 382:
	if ( (*( state.p)) == 105 )
		goto st383;
	goto st0;
st383:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof383;
case 383:
	if ( (*( state.p)) == 109 )
		goto st384;
	goto st0;
st384:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof384;
case 384:
	switch( (*( state.p)) ) {
		case 13: goto tr539;
		case 32: goto tr539;
		case 95: goto tr540;
		case 98: goto tr541;
		case 99: goto tr542;
		case 103: goto tr543;
		case 109: goto tr544;
		case 114: goto tr545;
		case 119: goto tr546;
		case 121: goto tr547;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr539;
	goto st0;
st385:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof385;
case 385:
	if ( (*( state.p)) == 111 )
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
	if ( (*( state.p)) == 101 )
		goto st22;
	goto st0;
tr463:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st388;
tr466:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st388;
st388:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof388;
case 388:
#line 8749 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr550;
		case 92: goto tr466;
	}
	goto tr464;
tr550:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st389;
st389:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof389;
case 389:
#line 8765 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr551;
		case 32: goto tr551;
		case 34: goto st336;
		case 92: goto tr466;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr551;
	goto tr464;
tr552:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st390;
tr551:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 140 "configparser.rl"
	{ spe.skin.text = state.match; }
	goto st390;
tr928:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 140 "configparser.rl"
	{ spe.skin.text = state.match; }
	goto st390;
st390:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof390;
case 390:
#line 8805 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr552;
		case 32: goto tr552;
		case 34: goto st336;
		case 92: goto tr466;
		case 98: goto tr553;
		case 100: goto tr554;
		case 110: goto tr555;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr552;
	goto tr464;
tr553:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st391;
st391:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof391;
case 391:
#line 8828 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 114: goto tr556;
	}
	goto tr464;
tr556:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st392;
st392:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof392;
case 392:
#line 8845 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 105: goto tr557;
	}
	goto tr464;
tr557:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st393;
st393:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof393;
case 393:
#line 8862 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 103: goto tr558;
	}
	goto tr464;
tr558:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st394;
st394:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof394;
case 394:
#line 8879 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 104: goto tr559;
	}
	goto tr464;
tr559:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st395;
st395:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof395;
case 395:
#line 8896 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 116: goto tr560;
	}
	goto tr464;
tr560:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st396;
st396:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof396;
case 396:
#line 8913 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr561;
		case 32: goto tr561;
		case 34: goto st336;
		case 92: goto tr466;
		case 95: goto tr562;
		case 98: goto tr563;
		case 99: goto tr564;
		case 103: goto tr565;
		case 109: goto tr566;
		case 114: goto tr567;
		case 119: goto tr568;
		case 121: goto tr569;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr561;
	goto tr464;
tr570:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st397;
tr561:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st397;
tr972:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st397;
st397:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof397;
case 397:
#line 8957 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr570;
		case 32: goto tr570;
		case 34: goto st336;
		case 92: goto tr466;
		case 98: goto tr571;
		case 99: goto tr572;
		case 103: goto tr573;
		case 109: goto tr574;
		case 114: goto tr575;
		case 119: goto tr576;
		case 121: goto tr577;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr570;
	goto tr464;
tr571:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st398;
tr563:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st398;
tr974:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st398;
st398:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof398;
case 398:
#line 9000 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 108: goto tr578;
	}
	goto tr464;
tr578:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st399;
st399:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof399;
case 399:
#line 9017 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 97: goto tr579;
		case 117: goto tr580;
	}
	goto tr464;
tr579:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st400;
st400:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof400;
case 400:
#line 9035 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 99: goto tr581;
	}
	goto tr464;
tr581:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st401;
st401:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof401;
case 401:
#line 9052 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 107: goto tr582;
	}
	goto tr464;
tr582:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st402;
tr1009:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 178 "configparser.rl"
	{ spe.companion.back().chance = ::atof(state.match.c_str()); }
	goto st402;
tr735:
#line 162 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st402;
tr601:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 150 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st402;
tr613:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 151 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st402;
tr631:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 173 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
	goto st402;
tr460:
#line 163 "configparser.rl"
	{ spe.name = state.match; }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st402;
tr754:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 146 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st402;
tr760:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 144 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st402;
tr770:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 147 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st402;
tr776:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 143 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st402;
tr780:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 145 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st402;
tr794:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 154 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st402;
tr801:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 155 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st402;
tr812:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st402;
tr818:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st402;
tr824:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 160 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st402;
tr920:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 169 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
	goto st402;
tr932:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 130 "configparser.rl"
	{ add_color(spe.skin.fore, 4); }
	goto st402;
tr937:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 132 "configparser.rl"
	{ add_color(spe.skin.fore, 6); }
	goto st402;
tr943:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 128 "configparser.rl"
	{ add_color(spe.skin.fore, 2); }
	goto st402;
tr951:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 131 "configparser.rl"
	{ add_color(spe.skin.fore, 5); }
	goto st402;
tr955:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 127 "configparser.rl"
	{ add_color(spe.skin.fore, 1); }
	goto st402;
tr961:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 133 "configparser.rl"
	{ add_color(spe.skin.fore, 7); }
	goto st402;
tr968:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 129 "configparser.rl"
	{ add_color(spe.skin.fore, 3); }
	goto st402;
tr929:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 186 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st402;
st402:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof402;
case 402:
#line 9273 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr582;
		case 32: goto tr582;
		case 34: goto st336;
		case 59: goto tr583;
		case 92: goto tr466;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr582;
	goto tr464;
tr583:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st823;
tr1012:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 178 "configparser.rl"
	{ spe.companion.back().chance = ::atof(state.match.c_str()); }
	goto st823;
tr737:
#line 162 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st823;
tr602:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 150 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st823;
tr614:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 151 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st823;
tr634:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 173 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
	goto st823;
tr462:
#line 163 "configparser.rl"
	{ spe.name = state.match; }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st823;
tr755:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 146 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st823;
tr761:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 144 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st823;
tr771:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 147 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st823;
tr777:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 143 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st823;
tr781:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 145 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st823;
tr795:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 154 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st823;
tr802:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 155 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st823;
tr813:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st823;
tr819:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st823;
tr825:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 160 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st823;
tr922:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 169 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
	goto st823;
tr933:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 130 "configparser.rl"
	{ add_color(spe.skin.fore, 4); }
	goto st823;
tr938:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 132 "configparser.rl"
	{ add_color(spe.skin.fore, 6); }
	goto st823;
tr944:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 128 "configparser.rl"
	{ add_color(spe.skin.fore, 2); }
	goto st823;
tr952:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 131 "configparser.rl"
	{ add_color(spe.skin.fore, 5); }
	goto st823;
tr956:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 127 "configparser.rl"
	{ add_color(spe.skin.fore, 1); }
	goto st823;
tr962:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 133 "configparser.rl"
	{ add_color(spe.skin.fore, 7); }
	goto st823;
tr969:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 129 "configparser.rl"
	{ add_color(spe.skin.fore, 3); }
	goto st823;
tr930:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 186 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st823;
st823:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof823;
case 823:
#line 9498 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr584;
		case 32: goto tr584;
		case 34: goto st336;
		case 92: goto tr466;
		case 97: goto tr585;
		case 99: goto tr586;
		case 104: goto tr587;
		case 105: goto tr588;
		case 109: goto tr589;
		case 110: goto tr590;
		case 114: goto tr591;
		case 115: goto tr592;
		case 125: goto tr593;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr584;
	goto tr464;
tr584:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st403;
st403:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof403;
case 403:
#line 9527 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr584;
		case 32: goto tr584;
		case 34: goto st336;
		case 92: goto tr466;
		case 97: goto tr585;
		case 99: goto tr586;
		case 104: goto tr587;
		case 105: goto tr588;
		case 109: goto tr589;
		case 110: goto tr590;
		case 114: goto tr591;
		case 115: goto tr592;
		case 125: goto tr593;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr584;
	goto tr464;
tr585:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st404;
st404:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof404;
case 404:
#line 9556 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 105: goto tr594;
	}
	goto tr464;
tr594:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st405;
st405:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof405;
case 405:
#line 9573 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr595;
		case 32: goto tr595;
		case 34: goto st336;
		case 92: goto tr466;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr595;
	goto tr464;
tr595:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st406;
st406:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof406;
case 406:
#line 9593 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr595;
		case 32: goto tr595;
		case 34: goto st336;
		case 92: goto tr466;
		case 110: goto tr596;
		case 115: goto tr597;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr595;
	goto tr464;
tr596:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st407;
st407:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof407;
case 407:
#line 9615 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 111: goto tr598;
	}
	goto tr464;
tr598:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st408;
st408:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof408;
case 408:
#line 9632 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 110: goto tr599;
	}
	goto tr464;
tr599:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st409;
st409:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof409;
case 409:
#line 9649 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 101: goto tr600;
	}
	goto tr464;
tr600:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st410;
st410:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof410;
case 410:
#line 9666 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr601;
		case 32: goto tr601;
		case 34: goto st336;
		case 59: goto tr602;
		case 92: goto tr466;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr601;
	goto tr464;
tr597:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st411;
st411:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof411;
case 411:
#line 9687 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 101: goto tr603;
	}
	goto tr464;
tr603:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st412;
st412:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof412;
case 412:
#line 9704 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 101: goto tr604;
	}
	goto tr464;
tr604:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st413;
st413:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof413;
case 413:
#line 9721 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 107: goto tr605;
	}
	goto tr464;
tr605:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st414;
st414:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof414;
case 414:
#line 9738 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 95: goto tr606;
	}
	goto tr464;
tr606:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st415;
st415:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof415;
case 415:
#line 9755 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 112: goto tr607;
	}
	goto tr464;
tr607:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st416;
st416:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof416;
case 416:
#line 9772 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 108: goto tr608;
	}
	goto tr464;
tr608:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st417;
st417:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof417;
case 417:
#line 9789 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 97: goto tr609;
	}
	goto tr464;
tr609:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st418;
st418:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof418;
case 418:
#line 9806 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 121: goto tr610;
	}
	goto tr464;
tr610:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st419;
st419:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof419;
case 419:
#line 9823 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 101: goto tr611;
	}
	goto tr464;
tr611:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st420;
st420:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof420;
case 420:
#line 9840 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 114: goto tr612;
	}
	goto tr464;
tr612:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st421;
st421:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof421;
case 421:
#line 9857 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr613;
		case 32: goto tr613;
		case 34: goto st336;
		case 59: goto tr614;
		case 92: goto tr466;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr613;
	goto tr464;
tr586:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st422;
st422:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof422;
case 422:
#line 9878 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 108: goto tr615;
		case 111: goto tr616;
	}
	goto tr464;
tr615:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st423;
st423:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof423;
case 423:
#line 9896 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 117: goto tr617;
	}
	goto tr464;
tr617:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st424;
st424:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof424;
case 424:
#line 9913 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 109: goto tr618;
	}
	goto tr464;
tr618:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st425;
st425:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof425;
case 425:
#line 9930 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 112: goto tr619;
	}
	goto tr464;
tr619:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st426;
st426:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof426;
case 426:
#line 9947 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 115: goto tr620;
	}
	goto tr464;
tr620:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st427;
st427:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof427;
case 427:
#line 9964 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 105: goto tr621;
	}
	goto tr464;
tr621:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st428;
st428:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof428;
case 428:
#line 9981 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 122: goto tr622;
	}
	goto tr464;
tr622:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st429;
st429:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof429;
case 429:
#line 9998 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 101: goto tr623;
	}
	goto tr464;
tr623:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st430;
st430:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof430;
case 430:
#line 10015 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr624;
		case 32: goto tr624;
		case 34: goto st336;
		case 92: goto tr466;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr624;
	goto tr464;
tr624:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st431;
st431:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof431;
case 431:
#line 10035 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr624;
		case 32: goto tr624;
		case 34: goto st336;
		case 92: goto tr466;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr625;
	} else if ( (*( state.p)) >= 9 )
		goto tr624;
	goto tr464;
tr628:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st432;
tr625:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st432;
st432:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof432;
case 432:
#line 10068 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr626;
		case 32: goto tr626;
		case 34: goto st336;
		case 46: goto tr627;
		case 92: goto tr466;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr628;
	} else if ( (*( state.p)) >= 9 )
		goto tr626;
	goto tr464;
tr629:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st433;
tr626:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 172 "configparser.rl"
	{ spe.clumpsize.mean = ::atof(state.match.c_str()); }
	goto st433;
st433:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof433;
case 433:
#line 10100 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr629;
		case 32: goto tr629;
		case 34: goto st336;
		case 92: goto tr466;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr630;
	} else if ( (*( state.p)) >= 9 )
		goto tr629;
	goto tr464;
tr633:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st434;
tr630:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st434;
st434:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof434;
case 434:
#line 10133 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr631;
		case 32: goto tr631;
		case 34: goto st336;
		case 46: goto tr632;
		case 59: goto tr634;
		case 92: goto tr466;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr633;
	} else if ( (*( state.p)) >= 9 )
		goto tr631;
	goto tr464;
tr632:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st435;
st435:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof435;
case 435:
#line 10158 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr635;
	goto tr464;
tr635:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st436;
st436:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof436;
case 436:
#line 10176 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr631;
		case 32: goto tr631;
		case 34: goto st336;
		case 59: goto tr634;
		case 92: goto tr466;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr635;
	} else if ( (*( state.p)) >= 9 )
		goto tr631;
	goto tr464;
tr627:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st437;
st437:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof437;
case 437:
#line 10200 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr636;
	goto tr464;
tr636:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st438;
st438:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof438;
case 438:
#line 10218 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr626;
		case 32: goto tr626;
		case 34: goto st336;
		case 92: goto tr466;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr636;
	} else if ( (*( state.p)) >= 9 )
		goto tr626;
	goto tr464;
tr616:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st439;
st439:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof439;
case 439:
#line 10241 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 109: goto tr637;
		case 117: goto tr638;
	}
	goto tr464;
tr637:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st440;
st440:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof440;
case 440:
#line 10259 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 112: goto tr639;
	}
	goto tr464;
tr639:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st441;
st441:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof441;
case 441:
#line 10276 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 97: goto tr640;
	}
	goto tr464;
tr640:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st442;
st442:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof442;
case 442:
#line 10293 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 110: goto tr641;
	}
	goto tr464;
tr641:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st443;
st443:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof443;
case 443:
#line 10310 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 105: goto tr642;
	}
	goto tr464;
tr642:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st444;
st444:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof444;
case 444:
#line 10327 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 111: goto tr643;
	}
	goto tr464;
tr643:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st445;
st445:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof445;
case 445:
#line 10344 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 110: goto tr644;
	}
	goto tr464;
tr644:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st446;
st446:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof446;
case 446:
#line 10361 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr645;
		case 32: goto tr645;
		case 34: goto st336;
		case 92: goto tr466;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr645;
	goto tr464;
tr646:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st447;
tr645:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 176 "configparser.rl"
	{ spe.companion.push_back(Species::companion_t()); }
	goto st447;
st447:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof447;
case 447:
#line 10389 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr646;
		case 32: goto tr646;
		case 34: goto st448;
		case 92: goto tr466;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr646;
	goto tr464;
st448:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof448;
case 448:
	switch( (*( state.p)) ) {
		case 13: goto tr648;
		case 32: goto tr648;
		case 34: goto tr75;
		case 92: goto tr76;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr648;
	goto tr74;
tr649:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st449;
tr648:
#line 140 "configparser.rl"
	{ spe.skin.text = state.match; }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st449;
st449:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof449;
case 449:
#line 10434 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr649;
		case 32: goto tr649;
		case 34: goto st51;
		case 92: goto tr79;
		case 98: goto tr650;
		case 100: goto tr651;
		case 110: goto tr652;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr649;
	goto tr77;
tr650:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st450;
st450:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof450;
case 450:
#line 10457 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 114: goto tr653;
	}
	goto tr77;
tr653:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st451;
st451:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof451;
case 451:
#line 10474 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 105: goto tr654;
	}
	goto tr77;
tr654:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st452;
st452:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof452;
case 452:
#line 10491 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 103: goto tr655;
	}
	goto tr77;
tr655:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st453;
st453:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof453;
case 453:
#line 10508 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 104: goto tr656;
	}
	goto tr77;
tr656:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st454;
st454:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof454;
case 454:
#line 10525 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 116: goto tr657;
	}
	goto tr77;
tr657:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st455;
st455:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof455;
case 455:
#line 10542 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr658;
		case 32: goto tr658;
		case 34: goto st51;
		case 92: goto tr79;
		case 95: goto tr659;
		case 98: goto tr660;
		case 99: goto tr661;
		case 103: goto tr662;
		case 109: goto tr663;
		case 114: goto tr664;
		case 119: goto tr665;
		case 121: goto tr666;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr658;
	goto tr77;
tr667:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st456;
tr658:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st456;
tr720:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st456;
st456:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof456;
case 456:
#line 10586 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr667;
		case 32: goto tr667;
		case 34: goto st51;
		case 92: goto tr79;
		case 98: goto tr668;
		case 99: goto tr669;
		case 103: goto tr670;
		case 109: goto tr671;
		case 114: goto tr672;
		case 119: goto tr673;
		case 121: goto tr674;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr667;
	goto tr77;
tr668:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st457;
tr660:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st457;
tr722:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st457;
st457:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof457;
case 457:
#line 10629 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 108: goto tr675;
	}
	goto tr77;
tr675:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st458;
st458:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof458;
case 458:
#line 10646 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 97: goto tr676;
		case 117: goto tr677;
	}
	goto tr77;
tr676:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st459;
st459:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof459;
case 459:
#line 10664 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 99: goto tr678;
	}
	goto tr77;
tr678:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st460;
st460:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof460;
case 460:
#line 10681 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 107: goto tr96;
	}
	goto tr77;
tr677:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st461;
st461:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof461;
case 461:
#line 10698 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 101: goto tr679;
	}
	goto tr77;
tr679:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st462;
st462:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof462;
case 462:
#line 10715 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr680;
		case 32: goto tr680;
		case 34: goto st51;
		case 59: goto tr681;
		case 92: goto tr79;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr680;
	goto tr77;
tr669:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st463;
tr661:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st463;
tr723:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st463;
st463:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof463;
case 463:
#line 10752 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 121: goto tr682;
	}
	goto tr77;
tr682:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st464;
st464:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof464;
case 464:
#line 10769 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 97: goto tr683;
	}
	goto tr77;
tr683:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st465;
st465:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof465;
case 465:
#line 10786 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 110: goto tr684;
	}
	goto tr77;
tr684:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st466;
st466:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof466;
case 466:
#line 10803 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr685;
		case 32: goto tr685;
		case 34: goto st51;
		case 59: goto tr686;
		case 92: goto tr79;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr685;
	goto tr77;
tr670:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st467;
tr662:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st467;
tr724:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st467;
st467:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof467;
case 467:
#line 10840 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 114: goto tr687;
	}
	goto tr77;
tr687:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st468;
st468:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof468;
case 468:
#line 10857 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 101: goto tr688;
	}
	goto tr77;
tr688:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st469;
st469:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof469;
case 469:
#line 10874 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 101: goto tr689;
	}
	goto tr77;
tr689:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st470;
st470:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof470;
case 470:
#line 10891 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 110: goto tr690;
	}
	goto tr77;
tr690:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st471;
st471:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof471;
case 471:
#line 10908 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr691;
		case 32: goto tr691;
		case 34: goto st51;
		case 59: goto tr692;
		case 92: goto tr79;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr691;
	goto tr77;
tr671:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st472;
tr663:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st472;
tr725:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st472;
st472:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof472;
case 472:
#line 10945 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 97: goto tr693;
	}
	goto tr77;
tr693:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st473;
st473:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof473;
case 473:
#line 10962 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 103: goto tr694;
	}
	goto tr77;
tr694:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st474;
st474:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof474;
case 474:
#line 10979 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 101: goto tr695;
	}
	goto tr77;
tr695:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st475;
st475:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof475;
case 475:
#line 10996 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 110: goto tr696;
	}
	goto tr77;
tr696:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st476;
st476:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof476;
case 476:
#line 11013 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 116: goto tr697;
	}
	goto tr77;
tr697:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st477;
st477:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof477;
case 477:
#line 11030 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 97: goto tr698;
	}
	goto tr77;
tr698:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st478;
st478:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof478;
case 478:
#line 11047 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr699;
		case 32: goto tr699;
		case 34: goto st51;
		case 59: goto tr700;
		case 92: goto tr79;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr699;
	goto tr77;
tr672:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st479;
tr664:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st479;
tr726:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st479;
st479:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof479;
case 479:
#line 11084 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 101: goto tr701;
	}
	goto tr77;
tr701:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st480;
st480:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof480;
case 480:
#line 11101 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 100: goto tr702;
	}
	goto tr77;
tr702:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st481;
st481:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof481;
case 481:
#line 11118 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr703;
		case 32: goto tr703;
		case 34: goto st51;
		case 59: goto tr704;
		case 92: goto tr79;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr703;
	goto tr77;
tr673:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st482;
tr665:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st482;
tr727:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st482;
st482:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof482;
case 482:
#line 11155 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 104: goto tr705;
	}
	goto tr77;
tr705:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st483;
st483:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof483;
case 483:
#line 11172 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 105: goto tr706;
	}
	goto tr77;
tr706:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st484;
st484:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof484;
case 484:
#line 11189 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 116: goto tr707;
	}
	goto tr77;
tr707:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st485;
st485:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof485;
case 485:
#line 11206 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 101: goto tr708;
	}
	goto tr77;
tr708:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st486;
st486:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof486;
case 486:
#line 11223 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr709;
		case 32: goto tr709;
		case 34: goto st51;
		case 59: goto tr710;
		case 92: goto tr79;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr709;
	goto tr77;
tr674:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st487;
tr666:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st487;
tr728:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st487;
st487:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof487;
case 487:
#line 11260 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 101: goto tr711;
	}
	goto tr77;
tr711:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st488;
st488:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof488;
case 488:
#line 11277 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 108: goto tr712;
	}
	goto tr77;
tr712:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st489;
st489:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof489;
case 489:
#line 11294 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 108: goto tr713;
	}
	goto tr77;
tr713:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st490;
st490:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof490;
case 490:
#line 11311 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 111: goto tr714;
	}
	goto tr77;
tr714:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st491;
st491:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof491;
case 491:
#line 11328 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 119: goto tr715;
	}
	goto tr77;
tr715:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st492;
st492:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof492;
case 492:
#line 11345 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr716;
		case 32: goto tr716;
		case 34: goto st51;
		case 59: goto tr717;
		case 92: goto tr79;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr716;
	goto tr77;
tr659:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st493;
tr721:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st493;
st493:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof493;
case 493:
#line 11376 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 98: goto tr668;
		case 99: goto tr669;
		case 103: goto tr670;
		case 109: goto tr671;
		case 114: goto tr672;
		case 119: goto tr673;
		case 121: goto tr674;
	}
	goto tr77;
tr651:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st494;
st494:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof494;
case 494:
#line 11399 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 105: goto tr718;
	}
	goto tr77;
tr718:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st495;
st495:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof495;
case 495:
#line 11416 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 109: goto tr719;
	}
	goto tr77;
tr719:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st496;
st496:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof496;
case 496:
#line 11433 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr720;
		case 32: goto tr720;
		case 34: goto st51;
		case 92: goto tr79;
		case 95: goto tr721;
		case 98: goto tr722;
		case 99: goto tr723;
		case 103: goto tr724;
		case 109: goto tr725;
		case 114: goto tr726;
		case 119: goto tr727;
		case 121: goto tr728;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr720;
	goto tr77;
tr652:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st497;
st497:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof497;
case 497:
#line 11461 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 111: goto tr729;
	}
	goto tr77;
tr729:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st498;
st498:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof498;
case 498:
#line 11478 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 110: goto tr730;
	}
	goto tr77;
tr730:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st499;
st499:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof499;
case 499:
#line 11495 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 101: goto tr96;
	}
	goto tr77;
tr638:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st500;
st500:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof500;
case 500:
#line 11512 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 110: goto tr731;
	}
	goto tr464;
tr731:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st501;
st501:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof501;
case 501:
#line 11529 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 116: goto tr732;
	}
	goto tr464;
tr732:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st502;
st502:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof502;
case 502:
#line 11546 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr733;
		case 32: goto tr733;
		case 34: goto st336;
		case 92: goto tr466;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr733;
	goto tr464;
tr733:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st503;
st503:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof503;
case 503:
#line 11566 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr733;
		case 32: goto tr733;
		case 34: goto st336;
		case 92: goto tr466;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr734;
	} else if ( (*( state.p)) >= 9 )
		goto tr733;
	goto tr464;
tr734:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st504;
tr736:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st504;
st504:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof504;
case 504:
#line 11599 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr735;
		case 32: goto tr735;
		case 34: goto st336;
		case 59: goto tr737;
		case 92: goto tr466;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr736;
	} else if ( (*( state.p)) >= 9 )
		goto tr735;
	goto tr464;
tr587:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st505;
st505:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof505;
case 505:
#line 11623 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 97: goto tr738;
	}
	goto tr464;
tr738:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st506;
st506:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof506;
case 506:
#line 11640 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 98: goto tr739;
	}
	goto tr464;
tr739:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st507;
st507:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof507;
case 507:
#line 11657 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 105: goto tr740;
	}
	goto tr464;
tr740:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st508;
st508:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof508;
case 508:
#line 11674 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 116: goto tr741;
	}
	goto tr464;
tr741:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st509;
st509:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof509;
case 509:
#line 11691 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 97: goto tr742;
	}
	goto tr464;
tr742:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st510;
st510:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof510;
case 510:
#line 11708 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 116: goto tr743;
	}
	goto tr464;
tr743:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st511;
st511:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof511;
case 511:
#line 11725 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr744;
		case 32: goto tr744;
		case 34: goto st336;
		case 92: goto tr466;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr744;
	goto tr464;
tr744:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st512;
st512:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof512;
case 512:
#line 11745 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr744;
		case 32: goto tr744;
		case 34: goto st336;
		case 92: goto tr466;
		case 99: goto tr745;
		case 102: goto tr746;
		case 115: goto tr747;
		case 119: goto tr748;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr744;
	goto tr464;
tr745:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st513;
st513:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof513;
case 513:
#line 11769 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 111: goto tr749;
	}
	goto tr464;
tr749:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st514;
st514:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof514;
case 514:
#line 11786 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 114: goto tr750;
	}
	goto tr464;
tr750:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st515;
st515:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof515;
case 515:
#line 11803 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 110: goto tr751;
	}
	goto tr464;
tr751:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st516;
st516:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof516;
case 516:
#line 11820 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 101: goto tr752;
	}
	goto tr464;
tr752:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st517;
st517:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof517;
case 517:
#line 11837 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 114: goto tr753;
	}
	goto tr464;
tr753:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st518;
st518:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof518;
case 518:
#line 11854 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr754;
		case 32: goto tr754;
		case 34: goto st336;
		case 59: goto tr755;
		case 92: goto tr466;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr754;
	goto tr464;
tr746:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st519;
st519:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof519;
case 519:
#line 11875 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 108: goto tr756;
	}
	goto tr464;
tr756:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st520;
st520:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof520;
case 520:
#line 11892 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 111: goto tr757;
	}
	goto tr464;
tr757:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st521;
st521:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof521;
case 521:
#line 11909 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 111: goto tr758;
	}
	goto tr464;
tr758:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st522;
st522:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof522;
case 522:
#line 11926 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 114: goto tr759;
	}
	goto tr464;
tr759:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st523;
st523:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof523;
case 523:
#line 11943 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr760;
		case 32: goto tr760;
		case 34: goto st336;
		case 59: goto tr761;
		case 92: goto tr466;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr760;
	goto tr464;
tr747:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st524;
st524:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof524;
case 524:
#line 11964 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 104: goto tr762;
	}
	goto tr464;
tr762:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st525;
st525:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof525;
case 525:
#line 11981 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 111: goto tr763;
	}
	goto tr464;
tr763:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st526;
st526:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof526;
case 526:
#line 11998 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 114: goto tr764;
	}
	goto tr464;
tr764:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st527;
st527:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof527;
case 527:
#line 12015 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 101: goto tr765;
	}
	goto tr464;
tr765:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st528;
st528:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof528;
case 528:
#line 12032 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 108: goto tr766;
	}
	goto tr464;
tr766:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st529;
st529:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof529;
case 529:
#line 12049 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 105: goto tr767;
	}
	goto tr464;
tr767:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st530;
st530:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof530;
case 530:
#line 12066 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 110: goto tr768;
	}
	goto tr464;
tr768:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st531;
st531:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof531;
case 531:
#line 12083 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 101: goto tr769;
	}
	goto tr464;
tr769:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st532;
st532:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof532;
case 532:
#line 12100 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr770;
		case 32: goto tr770;
		case 34: goto st336;
		case 59: goto tr771;
		case 92: goto tr466;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr770;
	goto tr464;
tr748:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st533;
st533:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof533;
case 533:
#line 12121 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 97: goto tr772;
	}
	goto tr464;
tr772:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st534;
st534:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof534;
case 534:
#line 12138 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 108: goto tr773;
		case 116: goto tr774;
	}
	goto tr464;
tr773:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st535;
st535:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof535;
case 535:
#line 12156 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 107: goto tr775;
	}
	goto tr464;
tr775:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st536;
st536:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof536;
case 536:
#line 12173 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr776;
		case 32: goto tr776;
		case 34: goto st336;
		case 59: goto tr777;
		case 92: goto tr466;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr776;
	goto tr464;
tr774:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st537;
st537:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof537;
case 537:
#line 12194 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 101: goto tr778;
	}
	goto tr464;
tr778:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st538;
st538:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof538;
case 538:
#line 12211 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 114: goto tr779;
	}
	goto tr464;
tr779:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st539;
st539:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof539;
case 539:
#line 12228 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr780;
		case 32: goto tr780;
		case 34: goto st336;
		case 59: goto tr781;
		case 92: goto tr466;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr780;
	goto tr464;
tr588:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st540;
st540:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof540;
case 540:
#line 12249 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 100: goto tr782;
	}
	goto tr464;
tr782:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st541;
st541:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof541;
case 541:
#line 12266 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 108: goto tr783;
	}
	goto tr464;
tr783:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st542;
st542:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof542;
case 542:
#line 12283 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 101: goto tr784;
	}
	goto tr464;
tr784:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st543;
st543:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof543;
case 543:
#line 12300 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 95: goto tr785;
	}
	goto tr464;
tr785:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st544;
st544:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof544;
case 544:
#line 12317 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 97: goto tr786;
	}
	goto tr464;
tr786:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st545;
st545:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof545;
case 545:
#line 12334 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 105: goto tr787;
	}
	goto tr464;
tr787:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st546;
st546:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof546;
case 546:
#line 12351 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr788;
		case 32: goto tr788;
		case 34: goto st336;
		case 92: goto tr466;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr788;
	goto tr464;
tr788:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st547;
st547:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof547;
case 547:
#line 12371 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr788;
		case 32: goto tr788;
		case 34: goto st336;
		case 92: goto tr466;
		case 110: goto tr789;
		case 114: goto tr790;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr788;
	goto tr464;
tr789:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st548;
st548:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof548;
case 548:
#line 12393 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 111: goto tr791;
	}
	goto tr464;
tr791:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st549;
st549:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof549;
case 549:
#line 12410 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 110: goto tr792;
	}
	goto tr464;
tr792:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st550;
st550:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof550;
case 550:
#line 12427 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 101: goto tr793;
	}
	goto tr464;
tr793:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st551;
st551:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof551;
case 551:
#line 12444 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr794;
		case 32: goto tr794;
		case 34: goto st336;
		case 59: goto tr795;
		case 92: goto tr466;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr794;
	goto tr464;
tr790:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st552;
st552:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof552;
case 552:
#line 12465 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 97: goto tr796;
	}
	goto tr464;
tr796:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st553;
st553:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof553;
case 553:
#line 12482 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 110: goto tr797;
	}
	goto tr464;
tr797:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st554;
st554:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof554;
case 554:
#line 12499 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 100: goto tr798;
	}
	goto tr464;
tr798:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st555;
st555:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof555;
case 555:
#line 12516 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 111: goto tr799;
	}
	goto tr464;
tr799:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st556;
st556:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof556;
case 556:
#line 12533 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 109: goto tr800;
	}
	goto tr464;
tr800:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st557;
st557:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof557;
case 557:
#line 12550 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr801;
		case 32: goto tr801;
		case 34: goto st336;
		case 59: goto tr802;
		case 92: goto tr466;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr801;
	goto tr464;
tr589:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st558;
st558:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof558;
case 558:
#line 12571 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 111: goto tr803;
	}
	goto tr464;
tr803:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st559;
st559:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof559;
case 559:
#line 12588 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 118: goto tr804;
	}
	goto tr464;
tr804:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st560;
st560:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof560;
case 560:
#line 12605 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 101: goto tr805;
	}
	goto tr464;
tr805:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st561;
st561:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof561;
case 561:
#line 12622 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr806;
		case 32: goto tr806;
		case 34: goto st336;
		case 92: goto tr466;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr806;
	goto tr464;
tr806:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st562;
st562:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof562;
case 562:
#line 12642 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr806;
		case 32: goto tr806;
		case 34: goto st336;
		case 92: goto tr466;
		case 97: goto tr807;
		case 102: goto tr808;
		case 119: goto tr809;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr806;
	goto tr464;
tr807:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st563;
st563:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof563;
case 563:
#line 12665 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 110: goto tr810;
	}
	goto tr464;
tr810:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st564;
st564:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof564;
case 564:
#line 12682 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 121: goto tr811;
	}
	goto tr464;
tr811:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st565;
st565:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof565;
case 565:
#line 12699 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr812;
		case 32: goto tr812;
		case 34: goto st336;
		case 59: goto tr813;
		case 92: goto tr466;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr812;
	goto tr464;
tr808:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st566;
st566:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof566;
case 566:
#line 12720 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 108: goto tr814;
	}
	goto tr464;
tr814:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st567;
st567:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof567;
case 567:
#line 12737 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 111: goto tr815;
	}
	goto tr464;
tr815:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st568;
st568:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof568;
case 568:
#line 12754 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 111: goto tr816;
	}
	goto tr464;
tr816:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st569;
st569:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof569;
case 569:
#line 12771 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 114: goto tr817;
	}
	goto tr464;
tr817:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st570;
st570:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof570;
case 570:
#line 12788 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr818;
		case 32: goto tr818;
		case 34: goto st336;
		case 59: goto tr819;
		case 92: goto tr466;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr818;
	goto tr464;
tr809:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st571;
st571:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof571;
case 571:
#line 12809 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 97: goto tr820;
	}
	goto tr464;
tr820:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st572;
st572:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof572;
case 572:
#line 12826 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 116: goto tr821;
	}
	goto tr464;
tr821:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st573;
st573:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof573;
case 573:
#line 12843 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 101: goto tr822;
	}
	goto tr464;
tr822:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st574;
st574:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof574;
case 574:
#line 12860 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 114: goto tr823;
	}
	goto tr464;
tr823:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st575;
st575:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof575;
case 575:
#line 12877 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr824;
		case 32: goto tr824;
		case 34: goto st336;
		case 59: goto tr825;
		case 92: goto tr466;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr824;
	goto tr464;
tr590:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st576;
st576:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof576;
case 576:
#line 12898 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 97: goto tr826;
	}
	goto tr464;
tr826:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st577;
st577:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof577;
case 577:
#line 12915 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 109: goto tr827;
	}
	goto tr464;
tr827:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st578;
st578:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof578;
case 578:
#line 12932 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 101: goto tr828;
	}
	goto tr464;
tr828:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st579;
st579:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof579;
case 579:
#line 12949 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr829;
		case 32: goto tr829;
		case 34: goto st336;
		case 92: goto tr466;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr829;
	goto tr464;
tr829:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st580;
st580:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof580;
case 580:
#line 12969 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr829;
		case 32: goto tr829;
		case 34: goto st581;
		case 92: goto tr466;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr829;
	goto tr464;
st581:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof581;
case 581:
	switch( (*( state.p)) ) {
		case 13: goto tr831;
		case 32: goto tr831;
		case 34: goto tr265;
		case 92: goto tr266;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr831;
	goto tr263;
tr832:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st582;
tr831:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 140 "configparser.rl"
	{ spe.skin.text = state.match; }
	goto st582;
st582:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof582;
case 582:
#line 13014 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr832;
		case 32: goto tr832;
		case 34: goto st190;
		case 92: goto tr269;
		case 98: goto tr833;
		case 100: goto tr834;
		case 110: goto tr835;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr832;
	goto tr267;
tr833:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st583;
st583:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof583;
case 583:
#line 13037 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 114: goto tr836;
	}
	goto tr267;
tr836:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st584;
st584:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof584;
case 584:
#line 13054 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 105: goto tr837;
	}
	goto tr267;
tr837:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st585;
st585:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof585;
case 585:
#line 13071 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 103: goto tr838;
	}
	goto tr267;
tr838:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st586;
st586:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof586;
case 586:
#line 13088 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 104: goto tr839;
	}
	goto tr267;
tr839:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st587;
st587:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof587;
case 587:
#line 13105 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 116: goto tr840;
	}
	goto tr267;
tr840:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st588;
st588:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof588;
case 588:
#line 13122 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr841;
		case 32: goto tr841;
		case 34: goto st190;
		case 92: goto tr269;
		case 95: goto tr842;
		case 98: goto tr843;
		case 99: goto tr844;
		case 103: goto tr845;
		case 109: goto tr846;
		case 114: goto tr847;
		case 119: goto tr848;
		case 121: goto tr849;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr841;
	goto tr267;
tr850:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st589;
tr841:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st589;
tr903:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st589;
st589:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof589;
case 589:
#line 13166 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr850;
		case 32: goto tr850;
		case 34: goto st190;
		case 92: goto tr269;
		case 98: goto tr851;
		case 99: goto tr852;
		case 103: goto tr853;
		case 109: goto tr854;
		case 114: goto tr855;
		case 119: goto tr856;
		case 121: goto tr857;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr850;
	goto tr267;
tr851:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st590;
tr843:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st590;
tr905:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st590;
st590:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof590;
case 590:
#line 13209 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 108: goto tr858;
	}
	goto tr267;
tr858:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st591;
st591:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof591;
case 591:
#line 13226 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 97: goto tr859;
		case 117: goto tr860;
	}
	goto tr267;
tr859:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st592;
st592:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof592;
case 592:
#line 13244 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 99: goto tr861;
	}
	goto tr267;
tr861:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st593;
st593:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof593;
case 593:
#line 13261 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 107: goto tr275;
	}
	goto tr267;
tr860:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st594;
st594:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof594;
case 594:
#line 13278 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 101: goto tr862;
	}
	goto tr267;
tr862:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st595;
st595:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof595;
case 595:
#line 13295 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr863;
		case 32: goto tr863;
		case 34: goto st190;
		case 59: goto tr864;
		case 92: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr863;
	goto tr267;
tr852:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st596;
tr844:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st596;
tr906:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st596;
st596:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof596;
case 596:
#line 13332 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 121: goto tr865;
	}
	goto tr267;
tr865:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st597;
st597:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof597;
case 597:
#line 13349 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 97: goto tr866;
	}
	goto tr267;
tr866:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st598;
st598:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof598;
case 598:
#line 13366 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 110: goto tr867;
	}
	goto tr267;
tr867:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st599;
st599:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof599;
case 599:
#line 13383 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr868;
		case 32: goto tr868;
		case 34: goto st190;
		case 59: goto tr869;
		case 92: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr868;
	goto tr267;
tr853:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st600;
tr845:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st600;
tr907:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st600;
st600:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof600;
case 600:
#line 13420 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 114: goto tr870;
	}
	goto tr267;
tr870:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st601;
st601:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof601;
case 601:
#line 13437 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 101: goto tr871;
	}
	goto tr267;
tr871:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st602;
st602:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof602;
case 602:
#line 13454 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 101: goto tr872;
	}
	goto tr267;
tr872:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st603;
st603:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof603;
case 603:
#line 13471 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 110: goto tr873;
	}
	goto tr267;
tr873:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st604;
st604:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof604;
case 604:
#line 13488 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr874;
		case 32: goto tr874;
		case 34: goto st190;
		case 59: goto tr875;
		case 92: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr874;
	goto tr267;
tr854:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st605;
tr846:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st605;
tr908:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st605;
st605:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof605;
case 605:
#line 13525 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 97: goto tr876;
	}
	goto tr267;
tr876:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st606;
st606:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof606;
case 606:
#line 13542 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 103: goto tr877;
	}
	goto tr267;
tr877:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st607;
st607:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof607;
case 607:
#line 13559 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 101: goto tr878;
	}
	goto tr267;
tr878:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st608;
st608:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof608;
case 608:
#line 13576 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 110: goto tr879;
	}
	goto tr267;
tr879:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st609;
st609:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof609;
case 609:
#line 13593 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 116: goto tr880;
	}
	goto tr267;
tr880:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st610;
st610:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof610;
case 610:
#line 13610 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 97: goto tr881;
	}
	goto tr267;
tr881:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st611;
st611:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof611;
case 611:
#line 13627 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr882;
		case 32: goto tr882;
		case 34: goto st190;
		case 59: goto tr883;
		case 92: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr882;
	goto tr267;
tr855:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st612;
tr847:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st612;
tr909:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st612;
st612:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof612;
case 612:
#line 13664 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 101: goto tr884;
	}
	goto tr267;
tr884:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st613;
st613:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof613;
case 613:
#line 13681 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 100: goto tr885;
	}
	goto tr267;
tr885:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st614;
st614:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof614;
case 614:
#line 13698 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr886;
		case 32: goto tr886;
		case 34: goto st190;
		case 59: goto tr887;
		case 92: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr886;
	goto tr267;
tr856:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st615;
tr848:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st615;
tr910:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st615;
st615:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof615;
case 615:
#line 13735 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 104: goto tr888;
	}
	goto tr267;
tr888:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st616;
st616:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof616;
case 616:
#line 13752 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 105: goto tr889;
	}
	goto tr267;
tr889:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st617;
st617:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof617;
case 617:
#line 13769 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 116: goto tr890;
	}
	goto tr267;
tr890:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st618;
st618:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof618;
case 618:
#line 13786 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 101: goto tr891;
	}
	goto tr267;
tr891:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st619;
st619:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof619;
case 619:
#line 13803 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr892;
		case 32: goto tr892;
		case 34: goto st190;
		case 59: goto tr893;
		case 92: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr892;
	goto tr267;
tr857:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st620;
tr849:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st620;
tr911:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st620;
st620:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof620;
case 620:
#line 13840 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 101: goto tr894;
	}
	goto tr267;
tr894:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st621;
st621:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof621;
case 621:
#line 13857 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 108: goto tr895;
	}
	goto tr267;
tr895:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st622;
st622:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof622;
case 622:
#line 13874 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 108: goto tr896;
	}
	goto tr267;
tr896:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st623;
st623:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof623;
case 623:
#line 13891 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 111: goto tr897;
	}
	goto tr267;
tr897:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st624;
st624:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof624;
case 624:
#line 13908 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 119: goto tr898;
	}
	goto tr267;
tr898:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st625;
st625:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof625;
case 625:
#line 13925 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr899;
		case 32: goto tr899;
		case 34: goto st190;
		case 59: goto tr900;
		case 92: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr899;
	goto tr267;
tr842:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st626;
tr904:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st626;
st626:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof626;
case 626:
#line 13956 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 98: goto tr851;
		case 99: goto tr852;
		case 103: goto tr853;
		case 109: goto tr854;
		case 114: goto tr855;
		case 119: goto tr856;
		case 121: goto tr857;
	}
	goto tr267;
tr834:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st627;
st627:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof627;
case 627:
#line 13979 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 105: goto tr901;
	}
	goto tr267;
tr901:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st628;
st628:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof628;
case 628:
#line 13996 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 109: goto tr902;
	}
	goto tr267;
tr902:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st629;
st629:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof629;
case 629:
#line 14013 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr903;
		case 32: goto tr903;
		case 34: goto st190;
		case 92: goto tr269;
		case 95: goto tr904;
		case 98: goto tr905;
		case 99: goto tr906;
		case 103: goto tr907;
		case 109: goto tr908;
		case 114: goto tr909;
		case 119: goto tr910;
		case 121: goto tr911;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr903;
	goto tr267;
tr835:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st630;
st630:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof630;
case 630:
#line 14041 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 111: goto tr912;
	}
	goto tr267;
tr912:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st631;
st631:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof631;
case 631:
#line 14058 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 110: goto tr913;
	}
	goto tr267;
tr913:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st632;
st632:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof632;
case 632:
#line 14075 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
		case 101: goto tr275;
	}
	goto tr267;
tr591:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st633;
st633:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof633;
case 633:
#line 14092 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 97: goto tr914;
	}
	goto tr464;
tr914:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st634;
st634:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof634;
case 634:
#line 14109 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 110: goto tr915;
	}
	goto tr464;
tr915:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st635;
st635:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof635;
case 635:
#line 14126 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 103: goto tr916;
	}
	goto tr464;
tr916:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st636;
st636:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof636;
case 636:
#line 14143 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 101: goto tr917;
	}
	goto tr464;
tr917:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st637;
st637:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof637;
case 637:
#line 14160 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr918;
		case 32: goto tr918;
		case 34: goto st336;
		case 92: goto tr466;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr918;
	goto tr464;
tr918:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st638;
st638:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof638;
case 638:
#line 14180 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr918;
		case 32: goto tr918;
		case 34: goto st336;
		case 92: goto tr466;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr919;
	} else if ( (*( state.p)) >= 9 )
		goto tr918;
	goto tr464;
tr921:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st639;
tr919:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st639;
st639:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof639;
case 639:
#line 14213 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr920;
		case 32: goto tr920;
		case 34: goto st336;
		case 59: goto tr922;
		case 92: goto tr466;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr921;
	} else if ( (*( state.p)) >= 9 )
		goto tr920;
	goto tr464;
tr592:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st640;
st640:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof640;
case 640:
#line 14237 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 107: goto tr923;
	}
	goto tr464;
tr923:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st641;
st641:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof641;
case 641:
#line 14254 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 105: goto tr924;
	}
	goto tr464;
tr924:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st642;
st642:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof642;
case 642:
#line 14271 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 110: goto tr925;
	}
	goto tr464;
tr925:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st643;
st643:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof643;
case 643:
#line 14288 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr926;
		case 32: goto tr926;
		case 34: goto st336;
		case 92: goto tr466;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr926;
	goto tr464;
tr926:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st644;
st644:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof644;
case 644:
#line 14308 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr926;
		case 32: goto tr926;
		case 34: goto st645;
		case 92: goto tr466;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr926;
	goto tr464;
st645:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof645;
case 645:
	switch( (*( state.p)) ) {
		case 13: goto tr928;
		case 32: goto tr928;
		case 34: goto tr461;
		case 92: goto tr463;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr928;
	goto tr459;
tr593:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st646;
st646:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof646;
case 646:
#line 14341 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr929;
		case 32: goto tr929;
		case 34: goto st336;
		case 59: goto tr930;
		case 92: goto tr466;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr929;
	goto tr464;
tr580:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st647;
st647:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof647;
case 647:
#line 14362 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 101: goto tr931;
	}
	goto tr464;
tr931:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st648;
st648:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof648;
case 648:
#line 14379 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr932;
		case 32: goto tr932;
		case 34: goto st336;
		case 59: goto tr933;
		case 92: goto tr466;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr932;
	goto tr464;
tr572:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st649;
tr564:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st649;
tr975:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st649;
st649:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof649;
case 649:
#line 14416 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 121: goto tr934;
	}
	goto tr464;
tr934:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st650;
st650:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof650;
case 650:
#line 14433 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 97: goto tr935;
	}
	goto tr464;
tr935:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st651;
st651:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof651;
case 651:
#line 14450 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 110: goto tr936;
	}
	goto tr464;
tr936:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st652;
st652:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof652;
case 652:
#line 14467 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr937;
		case 32: goto tr937;
		case 34: goto st336;
		case 59: goto tr938;
		case 92: goto tr466;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr937;
	goto tr464;
tr573:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st653;
tr565:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st653;
tr976:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st653;
st653:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof653;
case 653:
#line 14504 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 114: goto tr939;
	}
	goto tr464;
tr939:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st654;
st654:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof654;
case 654:
#line 14521 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 101: goto tr940;
	}
	goto tr464;
tr940:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st655;
st655:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof655;
case 655:
#line 14538 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 101: goto tr941;
	}
	goto tr464;
tr941:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st656;
st656:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof656;
case 656:
#line 14555 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 110: goto tr942;
	}
	goto tr464;
tr942:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st657;
st657:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof657;
case 657:
#line 14572 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr943;
		case 32: goto tr943;
		case 34: goto st336;
		case 59: goto tr944;
		case 92: goto tr466;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr943;
	goto tr464;
tr574:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st658;
tr566:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st658;
tr977:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st658;
st658:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof658;
case 658:
#line 14609 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 97: goto tr945;
	}
	goto tr464;
tr945:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st659;
st659:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof659;
case 659:
#line 14626 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 103: goto tr946;
	}
	goto tr464;
tr946:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st660;
st660:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof660;
case 660:
#line 14643 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 101: goto tr947;
	}
	goto tr464;
tr947:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st661;
st661:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof661;
case 661:
#line 14660 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 110: goto tr948;
	}
	goto tr464;
tr948:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st662;
st662:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof662;
case 662:
#line 14677 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 116: goto tr949;
	}
	goto tr464;
tr949:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st663;
st663:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof663;
case 663:
#line 14694 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 97: goto tr950;
	}
	goto tr464;
tr950:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st664;
st664:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof664;
case 664:
#line 14711 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr951;
		case 32: goto tr951;
		case 34: goto st336;
		case 59: goto tr952;
		case 92: goto tr466;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr951;
	goto tr464;
tr575:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st665;
tr567:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st665;
tr978:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st665;
st665:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof665;
case 665:
#line 14748 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 101: goto tr953;
	}
	goto tr464;
tr953:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st666;
st666:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof666;
case 666:
#line 14765 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 100: goto tr954;
	}
	goto tr464;
tr954:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st667;
st667:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof667;
case 667:
#line 14782 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr955;
		case 32: goto tr955;
		case 34: goto st336;
		case 59: goto tr956;
		case 92: goto tr466;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr955;
	goto tr464;
tr576:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st668;
tr568:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st668;
tr979:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st668;
st668:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof668;
case 668:
#line 14819 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 104: goto tr957;
	}
	goto tr464;
tr957:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st669;
st669:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof669;
case 669:
#line 14836 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 105: goto tr958;
	}
	goto tr464;
tr958:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st670;
st670:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof670;
case 670:
#line 14853 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 116: goto tr959;
	}
	goto tr464;
tr959:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st671;
st671:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof671;
case 671:
#line 14870 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 101: goto tr960;
	}
	goto tr464;
tr960:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st672;
st672:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof672;
case 672:
#line 14887 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr961;
		case 32: goto tr961;
		case 34: goto st336;
		case 59: goto tr962;
		case 92: goto tr466;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr961;
	goto tr464;
tr577:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st673;
tr569:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st673;
tr980:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st673;
st673:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof673;
case 673:
#line 14924 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 101: goto tr963;
	}
	goto tr464;
tr963:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st674;
st674:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof674;
case 674:
#line 14941 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 108: goto tr964;
	}
	goto tr464;
tr964:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st675;
st675:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof675;
case 675:
#line 14958 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 108: goto tr965;
	}
	goto tr464;
tr965:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st676;
st676:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof676;
case 676:
#line 14975 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 111: goto tr966;
	}
	goto tr464;
tr966:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st677;
st677:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof677;
case 677:
#line 14992 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 119: goto tr967;
	}
	goto tr464;
tr967:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st678;
st678:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof678;
case 678:
#line 15009 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr968;
		case 32: goto tr968;
		case 34: goto st336;
		case 59: goto tr969;
		case 92: goto tr466;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr968;
	goto tr464;
tr562:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st679;
tr973:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st679;
st679:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof679;
case 679:
#line 15040 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 98: goto tr571;
		case 99: goto tr572;
		case 103: goto tr573;
		case 109: goto tr574;
		case 114: goto tr575;
		case 119: goto tr576;
		case 121: goto tr577;
	}
	goto tr464;
tr554:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st680;
st680:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof680;
case 680:
#line 15063 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 105: goto tr970;
	}
	goto tr464;
tr970:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st681;
st681:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof681;
case 681:
#line 15080 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 109: goto tr971;
	}
	goto tr464;
tr971:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st682;
st682:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof682;
case 682:
#line 15097 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr972;
		case 32: goto tr972;
		case 34: goto st336;
		case 92: goto tr466;
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
	goto tr464;
tr555:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st683;
st683:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof683;
case 683:
#line 15125 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 111: goto tr981;
	}
	goto tr464;
tr981:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st684;
st684:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof684;
case 684:
#line 15142 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 110: goto tr982;
	}
	goto tr464;
tr982:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st685;
st685:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof685;
case 685:
#line 15159 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
		case 101: goto tr582;
	}
	goto tr464;
tr286:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st686;
st686:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof686;
case 686:
#line 15176 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr983;
		case 32: goto tr983;
		case 34: goto st190;
		case 59: goto tr984;
		case 92: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr983;
	goto tr267;
tr985:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st687;
tr264:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 177 "configparser.rl"
	{ spe.companion.back().tag = state.match; }
	goto st687;
st687:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof687;
case 687:
#line 15209 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr985;
		case 32: goto tr985;
		case 34: goto st190;
		case 92: goto tr269;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr986;
	} else if ( (*( state.p)) >= 9 )
		goto tr985;
	goto tr267;
tr989:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st688;
tr986:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st688;
st688:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof688;
case 688:
#line 15242 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr987;
		case 32: goto tr987;
		case 34: goto st190;
		case 46: goto tr988;
		case 59: goto tr990;
		case 92: goto tr269;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr989;
	} else if ( (*( state.p)) >= 9 )
		goto tr987;
	goto tr267;
tr988:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st689;
st689:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof689;
case 689:
#line 15267 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st190;
		case 92: goto tr269;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr991;
	goto tr267;
tr991:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st690;
st690:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof690;
case 690:
#line 15285 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr987;
		case 32: goto tr987;
		case 34: goto st190;
		case 59: goto tr990;
		case 92: goto tr269;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr991;
	} else if ( (*( state.p)) >= 9 )
		goto tr987;
	goto tr267;
tr105:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st691;
st691:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof691;
case 691:
#line 15309 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 97: goto tr992;
	}
	goto tr77;
tr992:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st692;
st692:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof692;
case 692:
#line 15326 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 110: goto tr993;
	}
	goto tr77;
tr993:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st693;
st693:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof693;
case 693:
#line 15343 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 103: goto tr994;
	}
	goto tr77;
tr994:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st694;
st694:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof694;
case 694:
#line 15360 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 101: goto tr995;
	}
	goto tr77;
tr995:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st695;
st695:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof695;
case 695:
#line 15377 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr996;
		case 32: goto tr996;
		case 34: goto st51;
		case 92: goto tr79;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr996;
	goto tr77;
tr996:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st696;
st696:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof696;
case 696:
#line 15397 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr996;
		case 32: goto tr996;
		case 34: goto st51;
		case 92: goto tr79;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr997;
	} else if ( (*( state.p)) >= 9 )
		goto tr996;
	goto tr77;
tr997:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st697;
tr999:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st697;
st697:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof697;
case 697:
#line 15430 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr998;
		case 32: goto tr998;
		case 34: goto st51;
		case 59: goto tr1000;
		case 92: goto tr79;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr999;
	} else if ( (*( state.p)) >= 9 )
		goto tr998;
	goto tr77;
tr106:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st698;
st698:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof698;
case 698:
#line 15454 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 107: goto tr1001;
	}
	goto tr77;
tr1001:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st699;
st699:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof699;
case 699:
#line 15471 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 105: goto tr1002;
	}
	goto tr77;
tr1002:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st700;
st700:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof700;
case 700:
#line 15488 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
		case 110: goto tr1003;
	}
	goto tr77;
tr1003:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st701;
st701:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof701;
case 701:
#line 15505 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1004;
		case 32: goto tr1004;
		case 34: goto st51;
		case 92: goto tr79;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1004;
	goto tr77;
tr1004:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st702;
st702:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof702;
case 702:
#line 15525 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1004;
		case 32: goto tr1004;
		case 34: goto st703;
		case 92: goto tr79;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1004;
	goto tr77;
st703:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof703;
case 703:
	switch( (*( state.p)) ) {
		case 13: goto tr1006;
		case 32: goto tr1006;
		case 34: goto tr461;
		case 92: goto tr463;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1006;
	goto tr459;
tr1007:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st704;
tr1006:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 177 "configparser.rl"
	{ spe.companion.back().tag = state.match; }
	goto st704;
st704:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof704;
case 704:
#line 15570 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1007;
		case 32: goto tr1007;
		case 34: goto st336;
		case 92: goto tr466;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1008;
	} else if ( (*( state.p)) >= 9 )
		goto tr1007;
	goto tr464;
tr1011:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st705;
tr1008:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st705;
st705:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof705;
case 705:
#line 15603 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1009;
		case 32: goto tr1009;
		case 34: goto st336;
		case 46: goto tr1010;
		case 59: goto tr1012;
		case 92: goto tr466;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1011;
	} else if ( (*( state.p)) >= 9 )
		goto tr1009;
	goto tr464;
tr1010:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st706;
st706:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof706;
case 706:
#line 15628 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st336;
		case 92: goto tr466;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr1013;
	goto tr464;
tr1013:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st707;
st707:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof707;
case 707:
#line 15646 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1009;
		case 32: goto tr1009;
		case 34: goto st336;
		case 59: goto tr1012;
		case 92: goto tr466;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1013;
	} else if ( (*( state.p)) >= 9 )
		goto tr1009;
	goto tr464;
tr107:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st708;
st708:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof708;
case 708:
#line 15670 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1014;
		case 32: goto tr1014;
		case 34: goto st51;
		case 59: goto tr1015;
		case 92: goto tr79;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1014;
	goto tr77;
tr93:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st709;
st709:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof709;
case 709:
#line 15691 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr79;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr1016;
	goto tr77;
tr1016:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st710;
st710:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof710;
case 710:
#line 15709 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr92;
		case 32: goto tr92;
		case 34: goto st51;
		case 59: goto tr95;
		case 92: goto tr79;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1016;
	} else if ( (*( state.p)) >= 9 )
		goto tr92;
	goto tr77;
st711:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof711;
case 711:
	if ( (*( state.p)) == 110 )
		goto st712;
	goto st0;
st712:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof712;
case 712:
	if ( (*( state.p)) == 116 )
		goto st713;
	goto st0;
st713:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof713;
case 713:
	switch( (*( state.p)) ) {
		case 13: goto st714;
		case 32: goto st714;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st714;
	goto st0;
st714:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof714;
case 714:
	switch( (*( state.p)) ) {
		case 13: goto st714;
		case 32: goto st714;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1020;
	} else if ( (*( state.p)) >= 9 )
		goto st714;
	goto st0;
tr1020:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st715;
tr1022:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st715;
st715:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof715;
case 715:
#line 15782 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1021;
		case 32: goto tr1021;
		case 59: goto tr1023;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1022;
	} else if ( (*( state.p)) >= 9 )
		goto tr1021;
	goto st0;
st716:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof716;
case 716:
	if ( (*( state.p)) == 97 )
		goto st717;
	goto st0;
st717:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof717;
case 717:
	if ( (*( state.p)) == 98 )
		goto st718;
	goto st0;
st718:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof718;
case 718:
	if ( (*( state.p)) == 105 )
		goto st719;
	goto st0;
st719:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof719;
case 719:
	if ( (*( state.p)) == 116 )
		goto st720;
	goto st0;
st720:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof720;
case 720:
	if ( (*( state.p)) == 97 )
		goto st721;
	goto st0;
st721:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof721;
case 721:
	if ( (*( state.p)) == 116 )
		goto st722;
	goto st0;
st722:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof722;
case 722:
	switch( (*( state.p)) ) {
		case 13: goto st723;
		case 32: goto st723;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st723;
	goto st0;
st723:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof723;
case 723:
	switch( (*( state.p)) ) {
		case 13: goto st723;
		case 32: goto st723;
		case 99: goto st724;
		case 102: goto st730;
		case 115: goto st735;
		case 119: goto st744;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st723;
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
	if ( (*( state.p)) == 114 )
		goto st726;
	goto st0;
st726:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof726;
case 726:
	if ( (*( state.p)) == 110 )
		goto st727;
	goto st0;
st727:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof727;
case 727:
	if ( (*( state.p)) == 101 )
		goto st728;
	goto st0;
st728:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof728;
case 728:
	if ( (*( state.p)) == 114 )
		goto st729;
	goto st0;
st729:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof729;
case 729:
	switch( (*( state.p)) ) {
		case 13: goto tr1040;
		case 32: goto tr1040;
		case 59: goto tr1041;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1040;
	goto st0;
st730:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof730;
case 730:
	if ( (*( state.p)) == 108 )
		goto st731;
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
	if ( (*( state.p)) == 111 )
		goto st733;
	goto st0;
st733:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof733;
case 733:
	if ( (*( state.p)) == 114 )
		goto st734;
	goto st0;
st734:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof734;
case 734:
	switch( (*( state.p)) ) {
		case 13: goto tr1046;
		case 32: goto tr1046;
		case 59: goto tr1047;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1046;
	goto st0;
st735:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof735;
case 735:
	if ( (*( state.p)) == 104 )
		goto st736;
	goto st0;
st736:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof736;
case 736:
	if ( (*( state.p)) == 111 )
		goto st737;
	goto st0;
st737:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof737;
case 737:
	if ( (*( state.p)) == 114 )
		goto st738;
	goto st0;
st738:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof738;
case 738:
	if ( (*( state.p)) == 101 )
		goto st739;
	goto st0;
st739:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof739;
case 739:
	if ( (*( state.p)) == 108 )
		goto st740;
	goto st0;
st740:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof740;
case 740:
	if ( (*( state.p)) == 105 )
		goto st741;
	goto st0;
st741:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof741;
case 741:
	if ( (*( state.p)) == 110 )
		goto st742;
	goto st0;
st742:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof742;
case 742:
	if ( (*( state.p)) == 101 )
		goto st743;
	goto st0;
st743:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof743;
case 743:
	switch( (*( state.p)) ) {
		case 13: goto tr1056;
		case 32: goto tr1056;
		case 59: goto tr1057;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1056;
	goto st0;
st744:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof744;
case 744:
	if ( (*( state.p)) == 97 )
		goto st745;
	goto st0;
st745:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof745;
case 745:
	switch( (*( state.p)) ) {
		case 108: goto st746;
		case 116: goto st748;
	}
	goto st0;
st746:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof746;
case 746:
	if ( (*( state.p)) == 107 )
		goto st747;
	goto st0;
st747:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof747;
case 747:
	switch( (*( state.p)) ) {
		case 13: goto tr1062;
		case 32: goto tr1062;
		case 59: goto tr1063;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1062;
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
	if ( (*( state.p)) == 114 )
		goto st750;
	goto st0;
st750:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof750;
case 750:
	switch( (*( state.p)) ) {
		case 13: goto tr1066;
		case 32: goto tr1066;
		case 59: goto tr1067;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1066;
	goto st0;
st751:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof751;
case 751:
	if ( (*( state.p)) == 100 )
		goto st752;
	goto st0;
st752:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof752;
case 752:
	if ( (*( state.p)) == 108 )
		goto st753;
	goto st0;
st753:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof753;
case 753:
	if ( (*( state.p)) == 101 )
		goto st754;
	goto st0;
st754:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof754;
case 754:
	if ( (*( state.p)) == 95 )
		goto st755;
	goto st0;
st755:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof755;
case 755:
	if ( (*( state.p)) == 97 )
		goto st756;
	goto st0;
st756:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof756;
case 756:
	if ( (*( state.p)) == 105 )
		goto st757;
	goto st0;
st757:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof757;
case 757:
	switch( (*( state.p)) ) {
		case 13: goto st758;
		case 32: goto st758;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st758;
	goto st0;
st758:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof758;
case 758:
	switch( (*( state.p)) ) {
		case 13: goto st758;
		case 32: goto st758;
		case 110: goto st759;
		case 114: goto st763;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st758;
	goto st0;
st759:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof759;
case 759:
	if ( (*( state.p)) == 111 )
		goto st760;
	goto st0;
st760:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof760;
case 760:
	if ( (*( state.p)) == 110 )
		goto st761;
	goto st0;
st761:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof761;
case 761:
	if ( (*( state.p)) == 101 )
		goto st762;
	goto st0;
st762:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof762;
case 762:
	switch( (*( state.p)) ) {
		case 13: goto tr1080;
		case 32: goto tr1080;
		case 59: goto tr1081;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1080;
	goto st0;
st763:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof763;
case 763:
	if ( (*( state.p)) == 97 )
		goto st764;
	goto st0;
st764:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof764;
case 764:
	if ( (*( state.p)) == 110 )
		goto st765;
	goto st0;
st765:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof765;
case 765:
	if ( (*( state.p)) == 100 )
		goto st766;
	goto st0;
st766:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof766;
case 766:
	if ( (*( state.p)) == 111 )
		goto st767;
	goto st0;
st767:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof767;
case 767:
	if ( (*( state.p)) == 109 )
		goto st768;
	goto st0;
st768:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof768;
case 768:
	switch( (*( state.p)) ) {
		case 13: goto tr1087;
		case 32: goto tr1087;
		case 59: goto tr1088;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1087;
	goto st0;
st769:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof769;
case 769:
	if ( (*( state.p)) == 111 )
		goto st770;
	goto st0;
st770:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof770;
case 770:
	if ( (*( state.p)) == 118 )
		goto st771;
	goto st0;
st771:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof771;
case 771:
	if ( (*( state.p)) == 101 )
		goto st772;
	goto st0;
st772:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof772;
case 772:
	switch( (*( state.p)) ) {
		case 13: goto st773;
		case 32: goto st773;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st773;
	goto st0;
st773:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof773;
case 773:
	switch( (*( state.p)) ) {
		case 13: goto st773;
		case 32: goto st773;
		case 97: goto st774;
		case 102: goto st777;
		case 119: goto st782;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st773;
	goto st0;
st774:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof774;
case 774:
	if ( (*( state.p)) == 110 )
		goto st775;
	goto st0;
st775:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof775;
case 775:
	if ( (*( state.p)) == 121 )
		goto st776;
	goto st0;
st776:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof776;
case 776:
	switch( (*( state.p)) ) {
		case 13: goto tr1098;
		case 32: goto tr1098;
		case 59: goto tr1099;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1098;
	goto st0;
st777:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof777;
case 777:
	if ( (*( state.p)) == 108 )
		goto st778;
	goto st0;
st778:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof778;
case 778:
	if ( (*( state.p)) == 111 )
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
	if ( (*( state.p)) == 114 )
		goto st781;
	goto st0;
st781:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof781;
case 781:
	switch( (*( state.p)) ) {
		case 13: goto tr1104;
		case 32: goto tr1104;
		case 59: goto tr1105;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1104;
	goto st0;
st782:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof782;
case 782:
	if ( (*( state.p)) == 97 )
		goto st783;
	goto st0;
st783:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof783;
case 783:
	if ( (*( state.p)) == 116 )
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
	if ( (*( state.p)) == 114 )
		goto st786;
	goto st0;
st786:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof786;
case 786:
	switch( (*( state.p)) ) {
		case 13: goto tr1110;
		case 32: goto tr1110;
		case 59: goto tr1111;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1110;
	goto st0;
st787:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof787;
case 787:
	if ( (*( state.p)) == 97 )
		goto st788;
	goto st0;
st788:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof788;
case 788:
	if ( (*( state.p)) == 109 )
		goto st789;
	goto st0;
st789:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof789;
case 789:
	if ( (*( state.p)) == 101 )
		goto st790;
	goto st0;
st790:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof790;
case 790:
	switch( (*( state.p)) ) {
		case 13: goto st791;
		case 32: goto st791;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st791;
	goto st0;
st791:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof791;
case 791:
	switch( (*( state.p)) ) {
		case 13: goto st791;
		case 32: goto st791;
		case 34: goto st792;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st791;
	goto st0;
st792:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof792;
case 792:
	switch( (*( state.p)) ) {
		case 34: goto tr265;
		case 92: goto tr266;
	}
	goto tr263;
st793:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof793;
case 793:
	if ( (*( state.p)) == 97 )
		goto st794;
	goto st0;
st794:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof794;
case 794:
	if ( (*( state.p)) == 110 )
		goto st795;
	goto st0;
st795:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof795;
case 795:
	if ( (*( state.p)) == 103 )
		goto st796;
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
	switch( (*( state.p)) ) {
		case 13: goto st798;
		case 32: goto st798;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st798;
	goto st0;
st798:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof798;
case 798:
	switch( (*( state.p)) ) {
		case 13: goto st798;
		case 32: goto st798;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1122;
	} else if ( (*( state.p)) >= 9 )
		goto st798;
	goto st0;
tr1122:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st799;
tr1124:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st799;
st799:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof799;
case 799:
#line 16502 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1123;
		case 32: goto tr1123;
		case 59: goto tr1125;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1124;
	} else if ( (*( state.p)) >= 9 )
		goto tr1123;
	goto st0;
st800:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof800;
case 800:
	if ( (*( state.p)) == 107 )
		goto st801;
	goto st0;
st801:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof801;
case 801:
	if ( (*( state.p)) == 105 )
		goto st802;
	goto st0;
st802:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof802;
case 802:
	if ( (*( state.p)) == 110 )
		goto st803;
	goto st0;
st803:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof803;
case 803:
	switch( (*( state.p)) ) {
		case 13: goto st804;
		case 32: goto st804;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st804;
	goto st0;
st804:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof804;
case 804:
	switch( (*( state.p)) ) {
		case 13: goto st804;
		case 32: goto st804;
		case 34: goto st805;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st804;
	goto st0;
st805:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof805;
case 805:
	switch( (*( state.p)) ) {
		case 34: goto tr461;
		case 92: goto tr463;
	}
	goto tr459;
st806:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof806;
case 806:
	switch( (*( state.p)) ) {
		case 13: goto tr1131;
		case 32: goto tr1131;
		case 59: goto tr1132;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1131;
	goto st0;
st807:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof807;
case 807:
	if ( (*( state.p)) == 101 )
		goto st808;
	goto st0;
st808:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof808;
case 808:
	if ( (*( state.p)) == 101 )
		goto st809;
	goto st0;
st809:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof809;
case 809:
	if ( (*( state.p)) == 107 )
		goto st810;
	goto st0;
st810:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof810;
case 810:
	if ( (*( state.p)) == 95 )
		goto st811;
	goto st0;
st811:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof811;
case 811:
	if ( (*( state.p)) == 112 )
		goto st812;
	goto st0;
st812:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof812;
case 812:
	if ( (*( state.p)) == 108 )
		goto st813;
	goto st0;
st813:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof813;
case 813:
	if ( (*( state.p)) == 97 )
		goto st814;
	goto st0;
st814:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof814;
case 814:
	if ( (*( state.p)) == 121 )
		goto st815;
	goto st0;
st815:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof815;
case 815:
	if ( (*( state.p)) == 101 )
		goto st816;
	goto st0;
st816:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof816;
case 816:
	if ( (*( state.p)) == 114 )
		goto st817;
	goto st0;
st817:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof817;
case 817:
	switch( (*( state.p)) ) {
		case 13: goto tr1143;
		case 32: goto tr1143;
		case 59: goto tr1144;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1143;
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
	_test_eof13:  state.cs = 13; goto _test_eof; 
	_test_eof818:  state.cs = 818; goto _test_eof; 
	_test_eof819:  state.cs = 819; goto _test_eof; 
	_test_eof14:  state.cs = 14; goto _test_eof; 
	_test_eof15:  state.cs = 15; goto _test_eof; 
	_test_eof16:  state.cs = 16; goto _test_eof; 
	_test_eof17:  state.cs = 17; goto _test_eof; 
	_test_eof18:  state.cs = 18; goto _test_eof; 
	_test_eof19:  state.cs = 19; goto _test_eof; 
	_test_eof20:  state.cs = 20; goto _test_eof; 
	_test_eof21:  state.cs = 21; goto _test_eof; 
	_test_eof22:  state.cs = 22; goto _test_eof; 
	_test_eof820:  state.cs = 820; goto _test_eof; 
	_test_eof23:  state.cs = 23; goto _test_eof; 
	_test_eof24:  state.cs = 24; goto _test_eof; 
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
	_test_eof821:  state.cs = 821; goto _test_eof; 
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
	_test_eof822:  state.cs = 822; goto _test_eof; 
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
	_test_eof823:  state.cs = 823; goto _test_eof; 
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

	_test_eof: {}
	if ( ( state.p) == ( state.eof) )
	{
	switch (  state.cs ) {
	case 818: 
#line 202 "configparser.rl"
	{ std::cout << "species done: " << std::endl; print_species(spe); }
	break;
#line 17494 "configparser.h"
	}
	}

	_out: {}
	}

#line 236 "configparser.rl"

        if (state.cs == ConfigParser_error) {
            throw std::runtime_error("Parse error.");
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
