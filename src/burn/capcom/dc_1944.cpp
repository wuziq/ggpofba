#include "cps.h"

static struct BurnInputInfo DrvInputList[] = {
	{"P1 Coin"       , BIT_DIGITAL, CpsInp020+4, "p1 coin"},
	{"P1 Start"      , BIT_DIGITAL, CpsInp020+0, "p1 start"},
	{"P1 Up"         , BIT_DIGITAL, CpsInp001+3, "p1 up"},
	{"P1 Down"       , BIT_DIGITAL, CpsInp001+2, "p1 down"},
	{"P1 Left"       , BIT_DIGITAL, CpsInp001+1, "p1 left"},
	{"P1 Right"      , BIT_DIGITAL, CpsInp001+0, "p1 right"},
	{"P1 Shot"       , BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},
	{"P1 Bomb"       , BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},

	{"P2 Coin"       , BIT_DIGITAL, CpsInp020+5, "p2 coin"},
	{"P2 Start"      , BIT_DIGITAL, CpsInp020+1, "p2 start"},
	{"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"},
	{"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"},
	{"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"},
	{"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right"},
	{"P2 Shot"       , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
	{"P2 Bomb"       , BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},

	{"Reset"         , BIT_DIGITAL, &CpsReset  , "reset"},
	{"Diagnostic"    , BIT_DIGITAL, CpsInp021+1, "diag"},
	{"Service"       , BIT_DIGITAL, CpsInp021+2, "service"},
};

STDINPUTINFO(Drv);

static struct BurnRomInfo nffRomDesc[] = {
	{ "nffu.03",      0x080000, 0x9693CF8F, 1 | BRF_ESS | BRF_PRG },
	{ "nff.04",       0x080000, 0xDBA1C66E, 1 | BRF_ESS | BRF_PRG },
	{ "nffu.05",      0x080000, 0xEA813EB7, 1 | BRF_ESS | BRF_PRG },

	{ "nff.13m",      0x400000, 0xC9FCA741, 3 | BRF_GRA },
	{ "nff.15m",      0x400000, 0xF809D898, 3 | BRF_GRA },
	{ "nff.17m",      0x400000, 0x15BA4507, 3 | BRF_GRA },
	{ "nff.19m",      0x400000, 0x3DD41B8C, 3 | BRF_GRA },
	{ "nff.14m",      0x100000, 0x3FE3A54B, 3 | BRF_GRA },
	{ "nff.16m",      0x100000, 0x565CD231, 3 | BRF_GRA },
	{ "nff.18m",      0x100000, 0x63CA5988, 3 | BRF_GRA },
	{ "nff.20m",      0x100000, 0x21EB8F3B, 3 | BRF_GRA },

	{ "nff.01",       0x020000, 0xD2E44318, 4 | BRF_ESS | BRF_PRG },

	{ "nff.11m",      0x400000, 0x243E4E05, 5 | BRF_SND },
	{ "nff.12m",      0x400000, 0x4FCF1600, 5 | BRF_SND },
};


STD_ROM_PICK(nff) STD_ROM_FN(nff)

static struct BurnRomInfo nffjRomDesc[] = {
	{ "nffj.03",      0x080000, 0x247521EF, 1 | BRF_ESS | BRF_PRG },
	{ "nff.04",       0x080000, 0xDBA1C66E, 1 | BRF_ESS | BRF_PRG },
	{ "nffj.05",      0x080000, 0x7F20C2EF, 1 | BRF_ESS | BRF_PRG },

	{ "nff.13m",      0x400000, 0xC9FCA741, 3 | BRF_GRA },
	{ "nff.15m",      0x400000, 0xF809D898, 3 | BRF_GRA },
	{ "nff.17m",      0x400000, 0x15BA4507, 3 | BRF_GRA },
	{ "nff.19m",      0x400000, 0x3DD41B8C, 3 | BRF_GRA },
	{ "nff.14m",      0x100000, 0x3FE3A54B, 3 | BRF_GRA },
	{ "nff.16m",      0x100000, 0x565CD231, 3 | BRF_GRA },
	{ "nff.18m",      0x100000, 0x63CA5988, 3 | BRF_GRA },
	{ "nff.20m",      0x100000, 0x21EB8F3B, 3 | BRF_GRA },

	{ "nff.01",       0x020000, 0xD2E44318, 4 | BRF_ESS | BRF_PRG },

	{ "nff.11m",      0x400000, 0x243E4E05, 5 | BRF_SND },
	{ "nff.12m",      0x400000, 0x4FCF1600, 5 | BRF_SND },
};


STD_ROM_PICK(nffj) STD_ROM_FN(nffj)

struct BurnDriver BurnDrvCps1944 = {
	"1944", NULL, NULL, "2000",
	"1944 - the loop master (000620 USA)\0", NULL, "Capcom / 8ing / Raizing", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_CAPCOM_CPS2,
	NULL, nffRomInfo, nffRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit, Cps2Frame, CpsRedraw, CpsAreaScan,
	&CpsRecalcPal, 384, 224, 4, 3
};

struct BurnDriver BurnDrvCps1944j = {
	"1944j", "1944", NULL, "2000",
	"1944 - the loop master (000620 Japan)\0", NULL, "Capcom / 8ing / Raizing", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_CAPCOM_CPS2,
	NULL, nffjRomInfo, nffjRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit, Cps2Frame, CpsRedraw, CpsAreaScan,
	&CpsRecalcPal, 384, 224, 4, 3
};
