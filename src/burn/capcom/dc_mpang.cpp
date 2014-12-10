#include "cps.h"

static struct BurnInputInfo DrvInputList[] =
{
	{"P1 Coin"       , BIT_DIGITAL, CpsInp020+4, "p1 coin"},
	{"P1 Start"      , BIT_DIGITAL, CpsInp020+0, "p1 start"},
	{"P1 Up"         , BIT_DIGITAL, CpsInp001+3, "p1 up"},
	{"P1 Down"       , BIT_DIGITAL, CpsInp001+2, "p1 down"},
	{"P1 Left"       , BIT_DIGITAL, CpsInp001+1, "p1 left"},
	{"P1 Right"      , BIT_DIGITAL, CpsInp001+0, "p1 right"},
	{"P1 Shot1"      , BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},
	{"P1 Shot2"      , BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},

	{"P2 Coin"       , BIT_DIGITAL, CpsInp020+5, "p2 coin"},
	{"P2 Start"      , BIT_DIGITAL, CpsInp020+1, "p2 start"},
	{"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"},
	{"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"},
	{"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"},
	{"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right"},
	{"P2 Shot1"      , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
	{"P2 Shot2"      , BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},

	{"Reset"         , BIT_DIGITAL, &CpsReset  , "reset"},
	{"Diagnostic"    , BIT_DIGITAL, CpsInp021+1, "diag"},
	{"Service"       , BIT_DIGITAL, CpsInp021+2, "service"},
};

STDINPUTINFO(Drv);

static struct BurnRomInfo mpangRomDesc[] = {
	{ "mpn.03",       0x080000, 0x6e7ed03c,  1 | BRF_ESS | BRF_PRG },
	{ "mpn.04",       0x080000, 0xde079131,  1 | BRF_ESS | BRF_PRG },

	{ "mpn.13m",      0x200000, 0xc5f123dc, 3 | BRF_GRA },
	{ "mpn.15m",      0x200000, 0x8e033265, 3 | BRF_GRA },
	{ "mpn.17m",      0x200000, 0xcfcd73d2, 3 | BRF_GRA },
	{ "mpn.19m",      0x200000, 0x2db1ffbc, 3 | BRF_GRA },
	
	{ "mpn.01",       0x020000, 0x90C7ADB6,  4 | BRF_ESS | BRF_PRG },

	{ "mpn.q1",       0x100000, 0xd21c1f5a, 5 | BRF_SND },	
	{ "mpn.q2",       0x100000, 0xd22090b1, 5 | BRF_SND },	
	{ "mpn.q3",       0x100000, 0x60aa5ef2, 5 | BRF_SND },	
	{ "mpn.q4",       0x100000, 0x3a67d203, 5 | BRF_SND },	
};


STD_ROM_PICK(mpang) STD_ROM_FN(mpang)

static struct BurnRomInfo mpangjRomDesc[] = {
	{ "mpnj.03a",     0x080000, 0xBF597b1C,  1 | BRF_ESS | BRF_PRG },
	{ "mpnj.04a",     0x080000, 0xF4A3AB0F,  1 | BRF_ESS | BRF_PRG },

	{ "mpn-simm.01c", 0x200000, 0x388DB66B, 11 | BRF_GRA },
	{ "mpn-simm.01d", 0x200000, 0xAFF1B494, 11 | BRF_GRA },
	{ "mpn-simm.01a", 0x200000, 0xA9C4857B, 11 | BRF_GRA },
	{ "mpn-simm.01b", 0x200000, 0xF759DF22, 11 | BRF_GRA },
	{ "mpn-simm.03c", 0x200000, 0xDEC6B720, 11 | BRF_GRA },
	{ "mpn-simm.03d", 0x200000, 0xF8774C18, 11 | BRF_GRA },
	{ "mpn-simm.03a", 0x200000, 0xC2AEA4EC, 11 | BRF_GRA },
	{ "mpn-simm.03b", 0x200000, 0x84D6DC33, 11 | BRF_GRA },

	{ "mpn.01",       0x020000, 0x90C7ADB6,  4 | BRF_ESS | BRF_PRG },

	{ "mpn-simm.05a", 0x200000, 0x318A2E21, 13 | BRF_SND },
	{ "mpn-simm.05b", 0x200000, 0x5462F4E8, 13 | BRF_SND },
};


STD_ROM_PICK(mpangj) STD_ROM_FN(mpangj)

struct BurnDriver BurnDrvCpsMPang = {
	"mpang", NULL, NULL, "2000",
	"Mighty! Pang (001010 USA)\0", NULL, "Mitchell", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_CAPCOM_CPS2,
	NULL, mpangRomInfo, mpangRomName, DrvInputInfo, NULL,
	Cps2Init,CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsMPangj = {
	"mpangj", "mpang", NULL, "2000",
	"Mighty! Pang (001011 Japan)\0", NULL, "Mitchell", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_CAPCOM_CPS2 | HARDWARE_CAPCOM_CPS2_SIMM,
	NULL, mpangjRomInfo, mpangjRomName, DrvInputInfo, NULL,
	Cps2Init,CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
