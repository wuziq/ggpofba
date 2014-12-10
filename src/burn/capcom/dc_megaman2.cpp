#include "cps.h"

static struct BurnInputInfo DrvInputList[] =
{
	{"P1 Coin"       , BIT_DIGITAL, CpsInp020 + 4, "p1 coin"   },
	{"P1 Start"      , BIT_DIGITAL, CpsInp020 + 0, "p1 start"  },
	{"P1 Up"         , BIT_DIGITAL, CpsInp001 + 3, "p1 up"     },
	{"P1 Down"       , BIT_DIGITAL, CpsInp001 + 2, "p1 down"   },
	{"P1 Left"       , BIT_DIGITAL, CpsInp001 + 1, "p1 left"   },
	{"P1 Right"      , BIT_DIGITAL, CpsInp001 + 0, "p1 right"  },
	{"P1 Attack"     , BIT_DIGITAL, CpsInp001 + 4, "p1 fire 1" },
	{"P1 Jump"       , BIT_DIGITAL, CpsInp001 + 5, "p1 fire 2" },
	{"P1 Select"     , BIT_DIGITAL, CpsInp001 + 6, "p1 fire 3" },

	{"P2 Coin"       , BIT_DIGITAL, CpsInp020 + 5, "p2 coin"   },
	{"P2 Start"      , BIT_DIGITAL, CpsInp020 + 1, "p2 start"  },
	{"P2 Up"         , BIT_DIGITAL, CpsInp000 + 3, "p2 up"     },
	{"P2 Down"       , BIT_DIGITAL, CpsInp000 + 2, "p2 down"   },
	{"P2 Left"       , BIT_DIGITAL, CpsInp000 + 1, "p2 left"   },
	{"P2 Right"      , BIT_DIGITAL, CpsInp000 + 0, "p2 right"  },
	{"P2 Attack"     , BIT_DIGITAL, CpsInp000 + 4, "p2 fire 1" },
	{"P2 Jump"       , BIT_DIGITAL, CpsInp000 + 5, "p2 fire 2" },
	{"P2 Select"     , BIT_DIGITAL, CpsInp000 + 6, "p2 fire 3" },

	{"Reset"         , BIT_DIGITAL, &CpsReset    , "reset"     },
	{"Diagnostic"    , BIT_DIGITAL, CpsInp021 + 1, "diag"      },
	{"Service"       , BIT_DIGITAL, CpsInp021 + 2, "service"   },
};

STDINPUTINFO(Drv);

static struct BurnRomInfo Megaman2RomDesc[] = {
	{ "rm2u.03",      0x080000, 0x8ffc2cd1, 1 | BRF_ESS | BRF_PRG },
	{ "rm2u.04",      0x080000, 0xbb30083a, 1 | BRF_ESS | BRF_PRG },
	{ "rm2.05",       0x080000, 0x02ee9efc, 1 | BRF_ESS | BRF_PRG },

	{ "rm2.14m",      0x200000, 0x9b1f00b4, 3 | BRF_GRA },
	{ "rm2.16m",      0x200000, 0xc2bb0c24, 3 | BRF_GRA },
	{ "rm2.18m",      0x200000, 0x12257251, 3 | BRF_GRA },
	{ "rm2.20m",      0x200000, 0xf9b6e786, 3 | BRF_GRA },

	{ "rm2.01a",      0x020000, 0xd18e7859, 4 | BRF_ESS | BRF_PRG },
	{ "rm2.02",       0x020000, 0xc463ece0, 4 | BRF_ESS | BRF_PRG },

	{ "rm2.11m",      0x200000, 0x2106174d, 5 | BRF_SND },
	{ "rm2.12m",      0x200000, 0x546c1636, 5 | BRF_SND },
};


STD_ROM_PICK(Megaman2) STD_ROM_FN(Megaman2)

static struct BurnRomInfo Megamn2aRomDesc[] = {
	{ "rm2a.03",      0x080000, 0x2b330ca7, 1 | BRF_ESS | BRF_PRG },
	{ "rm2a.04",      0x080000, 0x8b47942b, 1 | BRF_ESS | BRF_PRG },
	{ "rm2.05",       0x080000, 0x02ee9efc, 1 | BRF_ESS | BRF_PRG },

	{ "rm2.14m",      0x200000, 0x9b1f00b4, 3 | BRF_GRA },
	{ "rm2.16m",      0x200000, 0xc2bb0c24, 3 | BRF_GRA },
	{ "rm2.18m",      0x200000, 0x12257251, 3 | BRF_GRA },
	{ "rm2.20m",      0x200000, 0xf9b6e786, 3 | BRF_GRA },

	{ "rm2.01a",      0x020000, 0xd18e7859, 4 | BRF_ESS | BRF_PRG },
	{ "rm2.02",       0x020000, 0xc463ece0, 4 | BRF_ESS | BRF_PRG },

	{ "rm2.11m",      0x200000, 0x2106174d, 5 | BRF_SND },
	{ "rm2.12m",      0x200000, 0x546c1636, 5 | BRF_SND },
};


STD_ROM_PICK(Megamn2a) STD_ROM_FN(Megamn2a)

static struct BurnRomInfo Rckman2jRomDesc[] = {
	{ "rm2j.03",      0x080000, 0xdbaa1437, 1 | BRF_ESS | BRF_PRG },
	{ "rm2j.04",      0x080000, 0xcf5ba612, 1 | BRF_ESS | BRF_PRG },
	{ "rm2.05",       0x080000, 0x02ee9efc, 1 | BRF_ESS | BRF_PRG },

	{ "rm2.14m",      0x200000, 0x9b1f00b4, 3 | BRF_GRA },
	{ "rm2.16m",      0x200000, 0xc2bb0c24, 3 | BRF_GRA },
	{ "rm2.18m",      0x200000, 0x12257251, 3 | BRF_GRA },
	{ "rm2.20m",      0x200000, 0xf9b6e786, 3 | BRF_GRA },

	{ "rm2.01a",      0x020000, 0xd18e7859, 4 | BRF_ESS | BRF_PRG },
	{ "rm2.02",       0x020000, 0xc463ece0, 4 | BRF_ESS | BRF_PRG },

	{ "rm2.11m",      0x200000, 0x2106174d, 5 | BRF_SND },
	{ "rm2.12m",      0x200000, 0x546c1636, 5 | BRF_SND },
};


STD_ROM_PICK(Rckman2j) STD_ROM_FN(Rckman2j)

struct BurnDriver BurnDrvCpsMegaman2 = {
	"megaman2", NULL, NULL, "1996",
	"Mega Man 2 - the power fighters (960708 USA)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_CAPCOM_CPS2,
	NULL, Megaman2RomInfo, Megaman2RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit, Cps2Frame, CpsRedraw, CpsAreaScan,
	&CpsRecalcPal ,384, 224, 4, 3
};

struct BurnDriver BurnDrvCpsMegamn2a = {
	"megamn2a", "megaman2", NULL, "1996",
	"Mega Man 2 - the power fighters (960708 Asia)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_CAPCOM_CPS2,
	NULL, Megamn2aRomInfo, Megamn2aRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit, Cps2Frame, CpsRedraw, CpsAreaScan,
	&CpsRecalcPal ,384, 224, 4, 3
};

struct BurnDriver BurnDrvCpsRckman2j = {
	"rckman2j", "megaman2", NULL, "1996",
	"Rockman 2 - the power fighters (960708 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_CAPCOM_CPS2,
	NULL, Rckman2jRomInfo, Rckman2jRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit, Cps2Frame, CpsRedraw, CpsAreaScan,
	&CpsRecalcPal, 384, 224, 4, 3
};
