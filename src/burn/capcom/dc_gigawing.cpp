#include "cps.h"

static struct BurnInputInfo DrvInputList[] =
{
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

static struct BurnRomInfo GigawingRomDesc[] = {
	{ "ggwu.03",       0x80000, 0xac725eb2, 1 | BRF_ESS | BRF_PRG },
	{ "ggwu.04",       0x80000, 0x392f4118, 1 | BRF_ESS | BRF_PRG },
	{ "ggwu.05",       0x80000, 0x3239d642, 1 | BRF_ESS | BRF_PRG },

	{ "ggw.13m",      0x400000, 0x105530a4, 3 | BRF_GRA },
	{ "ggw.15m",      0x400000, 0x9e774ab9, 3 | BRF_GRA },
	{ "ggw.17m",      0x400000, 0x466e0ba4, 3 | BRF_GRA },
	{ "ggw.19m",      0x400000, 0x840c8dea, 3 | BRF_GRA },

	{ "ggw.01",       0x020000, 0x4c6351d5, 4 | BRF_ESS | BRF_PRG },

	{ "ggw.11m",      0x400000, 0xe172acf5, 5 | BRF_SND },
	{ "ggw.12m",      0x400000, 0x4bee4e8f, 5 | BRF_SND },
};


STD_ROM_PICK(Gigawing) STD_ROM_FN(Gigawing)

static struct BurnRomInfo GwingjRomDesc[] = {
	{ "ggwj.03a",      0x80000, 0xfdd23b91, 1 | BRF_ESS | BRF_PRG },
	{ "ggwj.04a",      0x80000, 0x8c6e093c, 1 | BRF_ESS | BRF_PRG },
	{ "ggwj.05a",      0x80000, 0x43811454, 1 | BRF_ESS | BRF_PRG },

	{ "ggw.13m",      0x400000, 0x105530a4, 3 | BRF_GRA },
	{ "ggw.15m",      0x400000, 0x9e774ab9, 3 | BRF_GRA },
	{ "ggw.17m",      0x400000, 0x466e0ba4, 3 | BRF_GRA },
	{ "ggw.19m",      0x400000, 0x840c8dea, 3 | BRF_GRA },

	{ "ggw.01",       0x020000, 0x4c6351d5, 4 | BRF_ESS | BRF_PRG },

	{ "ggw.11m",      0x400000, 0xe172acf5, 5 | BRF_SND },
	{ "ggw.12m",      0x400000, 0x4bee4e8f, 5 | BRF_SND },
};


STD_ROM_PICK(Gwingj) STD_ROM_FN(Gwingj)

static struct BurnRomInfo GwingaRomDesc[] = {
	{ "ggwa.03a",      0x80000, 0x116f8837, 1 | BRF_ESS | BRF_PRG },
	{ "ggwa.04a",      0x80000, 0xe6e3f0c4, 1 | BRF_ESS | BRF_PRG },
	{ "ggwa.05a",      0x80000, 0x465e8ac9, 1 | BRF_ESS | BRF_PRG },

	{ "ggw.13m",      0x400000, 0x105530a4, 3 | BRF_GRA },
	{ "ggw.15m",      0x400000, 0x9e774ab9, 3 | BRF_GRA },
	{ "ggw.17m",      0x400000, 0x466e0ba4, 3 | BRF_GRA },
	{ "ggw.19m",      0x400000, 0x840c8dea, 3 | BRF_GRA },

	{ "ggw.01",       0x020000, 0x4c6351d5, 4 | BRF_ESS | BRF_PRG },

	{ "ggw.11m",      0x400000, 0xe172acf5, 5 | BRF_SND },
	{ "ggw.12m",      0x400000, 0x4bee4e8f, 5 | BRF_SND },
};


STD_ROM_PICK(Gwinga) STD_ROM_FN(Gwinga)

struct BurnDriver BurnDrvCpsGigawing = {
	"gigawing", NULL, NULL, "1999",
	"Giga Wing (990222 USA)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_CAPCOM_CPS2,
	NULL, GigawingRomInfo, GigawingRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsGwingj = {
	"gwingj", "gigawing", NULL, "1999",
	"Giga Wing (990223 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_CAPCOM_CPS2,
	NULL, GwingjRomInfo, GwingjRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsGwinga = {
	"gwinga", "gigawing", NULL, "1999",
	"Giga Wing (990222 Asia)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_CAPCOM_CPS2,
	NULL, GwingaRomInfo, GwingaRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
