#include "cps.h"

static struct BurnInputInfo DrvInputList[] =
{
  {"P1 Coin"       , BIT_DIGITAL, CpsInp020+4, "p1 coin"  },
  {"P1 Start"      , BIT_DIGITAL, CpsInp020+0, "p1 start" },
  {"P1 Up"         , BIT_DIGITAL, CpsInp001+3, "p1 up"    },
  {"P1 Down"       , BIT_DIGITAL, CpsInp001+2, "p1 down"  },
  {"P1 Left"       , BIT_DIGITAL, CpsInp001+1, "p1 left"  },
  {"P1 Right"      , BIT_DIGITAL, CpsInp001+0, "p1 right" },
  {"P1 Shot"       , BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},

  {"P2 Coin"       , BIT_DIGITAL, CpsInp020+5, "p2 coin"  },
  {"P2 Start"      , BIT_DIGITAL, CpsInp020+1, "p2 start" },
  {"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"    },
  {"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"  },
  {"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"  },
  {"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right" },
  {"P2 Shot"       , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},

  {"Reset"         , BIT_DIGITAL, &CpsReset  , "reset"    },
  {"Diagnostic"    , BIT_DIGITAL, CpsInp021+1, "diag"     },
  {"Service"       , BIT_DIGITAL, CpsInp021+2, "service"  },
};

STDINPUTINFO(Drv);

static struct BurnRomInfo mmatrixRomDesc[] = {
	{ "mmxu.03",       0x80000, 0xAB65b599, 1 | BRF_ESS | BRF_PRG },
	{ "mmxu.04",       0x80000, 0x0135FC6C, 1 | BRF_ESS | BRF_PRG },
	{ "mmxu.05",       0x80000, 0xF1FD2B84, 1 | BRF_ESS | BRF_PRG },

	{ "mmx.13m",      0x400000, 0x04748718, 3 | BRF_GRA },
	{ "mmx.15m",      0x400000, 0x38074F44, 3 | BRF_GRA },
	{ "mmx.17m",      0x400000, 0xE4635E35, 3 | BRF_GRA },
	{ "mmx.19m",      0x400000, 0x4400A3F2, 3 | BRF_GRA },
	{ "mmx.14m",      0x400000, 0xD52BF491, 3 | BRF_GRA },
	{ "mmx.16m",      0x400000, 0x23F70780, 3 | BRF_GRA },
	{ "mmx.18m",      0x400000, 0x2562C9D5, 3 | BRF_GRA },
	{ "mmx.20m",      0x400000, 0x583A9687, 3 | BRF_GRA },

	{ "mmx.01",       0x020000, 0xC57E8171, 4 | BRF_ESS | BRF_PRG },

	{ "mmx.11m",      0x400000, 0x4180B39F, 5 | BRF_SND },
	{ "mmx.12m",      0x400000, 0x95E22A59, 5 | BRF_SND },
};


STD_ROM_PICK(mmatrix) STD_ROM_FN(mmatrix)

static struct BurnRomInfo mmatrixjRomDesc[] = {
	{ "mmxj.03",       0x80000, 0x1D5DE213, 1 | BRF_ESS | BRF_PRG },
	{ "mmxj.04",       0x80000, 0xD943A339, 1 | BRF_ESS | BRF_PRG },
	{ "mmxj.05",       0x80000, 0x0C8B4ABB, 1 | BRF_ESS | BRF_PRG },

	{ "mmx.13m",      0x400000, 0x04748718, 3 | BRF_GRA },
	{ "mmx.15m",      0x400000, 0x38074F44, 3 | BRF_GRA },
	{ "mmx.17m",      0x400000, 0xE4635E35, 3 | BRF_GRA },
	{ "mmx.19m",      0x400000, 0x4400A3F2, 3 | BRF_GRA },
	{ "mmx.14m",      0x400000, 0xD52BF491, 3 | BRF_GRA },
	{ "mmx.16m",      0x400000, 0x23F70780, 3 | BRF_GRA },
	{ "mmx.18m",      0x400000, 0x2562C9D5, 3 | BRF_GRA },
	{ "mmx.20m",      0x400000, 0x583A9687, 3 | BRF_GRA },

	{ "mmx.01",       0x020000, 0xC57E8171, 4 | BRF_ESS | BRF_PRG },

	{ "mmx.11m",      0x400000, 0x4180B39F, 5 | BRF_SND },
	{ "mmx.12m",      0x400000, 0x95E22A59, 5 | BRF_SND },
};


STD_ROM_PICK(mmatrixj) STD_ROM_FN(mmatrixj)

struct BurnDriver BurnDrvCpsMarsMatrix = {
	"mmatrix", NULL, NULL, "2000",
	"Mars Matrix (000412 USA)\0", NULL, "Capcom / Takumi", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_CAPCOM_CPS2,
	NULL, mmatrixRomInfo, mmatrixRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsMarsMatrixJ = {
	"mmatrixj", "mmatrix", NULL, "2000",
	"Mars Matrix (000412 Japan)\0", NULL, "Capcom / Takumi", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_CAPCOM_CPS2,
	NULL, mmatrixjRomInfo, mmatrixjRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
