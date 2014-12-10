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
  {"P1 Bomb"       , BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},
  {"P1 Shot (auto)", BIT_DIGITAL, CpsInp001+6, "p1 fire 3"},

  {"P2 Coin"       , BIT_DIGITAL, CpsInp020+5, "p2 coin"  },
  {"P2 Start"      , BIT_DIGITAL, CpsInp020+1, "p2 start" },
  {"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"    },
  {"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"  },
  {"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"  },
  {"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right" },
  {"P2 Shot"       , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
  {"P2 Bomb"       , BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},
  {"P2 Shot (auto)", BIT_DIGITAL, CpsInp000+6, "p2 fire 3"},

  {"Reset"         , BIT_DIGITAL, &CpsReset  , "reset"    },
  {"Diagnostic"    , BIT_DIGITAL, CpsInp021+1, "diag"     },
  {"Service"       , BIT_DIGITAL, CpsInp021+2, "service"  },
};

STDINPUTINFO(Drv);

static struct BurnRomInfo DimahooRomDesc[] = {
	{ "gmdu.03",       0x80000, 0x43BCB15F, 1 | BRF_ESS | BRF_PRG },
	{ "gmd.04",        0x80000, 0x37485567, 1 | BRF_ESS | BRF_PRG },
	{ "gmd.05",        0x80000, 0xDA269FFB, 1 | BRF_ESS | BRF_PRG },
	{ "gmd.06",        0x80000, 0x55B483C9, 1 | BRF_ESS | BRF_PRG },

	{ "gmd.13m",      0x400000, 0x80DD19F0, 3 | BRF_GRA },
	{ "gmd.15m",      0x400000, 0xDFD93A78, 3 | BRF_GRA },
	{ "gmd.17m",      0x400000, 0x16356520, 3 | BRF_GRA },
	{ "gmd.19m",      0x400000, 0xDFC33031, 3 | BRF_GRA },

	{ "gmd.01",       0x020000, 0x3F9BC985, 4 | BRF_ESS | BRF_PRG },
	{ "gmd.02",       0x020000, 0x3FD39DDE, 4 | BRF_ESS | BRF_PRG },

	{ "gmd.11m",      0x400000, 0x06A65542, 5 | BRF_SND },
	{ "gmd.12m",      0x400000, 0x50BC7A31, 5 | BRF_SND },
};


STD_ROM_PICK(Dimahoo) STD_ROM_FN(Dimahoo)

static struct BurnRomInfo gmdjRomDesc[] = {
	{ "gmdj.03",       0x80000, 0xCD6979E3, 1 | BRF_ESS | BRF_PRG },
	{ "gmd.04",        0x80000, 0x37485567, 1 | BRF_ESS | BRF_PRG },
	{ "gmd.05",        0x80000, 0xDA269FFB, 1 | BRF_ESS | BRF_PRG },
	{ "gmd.06",        0x80000, 0x55B483C9, 1 | BRF_ESS | BRF_PRG },

	{ "gmd.13m",      0x400000, 0x80DD19F0, 3 | BRF_GRA },
	{ "gmd.15m",      0x400000, 0xDFD93A78, 3 | BRF_GRA },
	{ "gmd.17m",      0x400000, 0x16356520, 3 | BRF_GRA },
	{ "gmd.19m",      0x400000, 0xDFC33031, 3 | BRF_GRA },

	{ "gmd.01",       0x020000, 0x3F9BC985, 4 | BRF_ESS | BRF_PRG },
	{ "gmd.02",       0x020000, 0x3FD39DDE, 4 | BRF_ESS | BRF_PRG },

	{ "gmd.11m",      0x400000, 0x06A65542, 5 | BRF_SND },
	{ "gmd.12m",      0x400000, 0x50BC7A31, 5 | BRF_SND },
};


STD_ROM_PICK(gmdj) STD_ROM_FN(gmdj)

struct BurnDriver BurnDrvCpsDimahoo = {
	"dimahoo", NULL, NULL, "2000",
	"Dimahoo (000121 USA)\0", NULL, "8ing / Raizing / Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_ORIENTATION_VERTICAL, 2, HARDWARE_CAPCOM_CPS2,
	NULL, DimahooRomInfo, DimahooRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,224,384,3,4
};

struct BurnDriver BurnDrvCpsGreatMahouDaiJ = {
	"gmahou", "dimahoo", NULL, "2000",
	"Great Mahou Daisakusen (000121 Japan)\0", NULL, "8ing / Raizing / Capcom", "CPS2",
	L"\u30B0\u30EC\u30FC\u30C8\u9B54\u6CD5\u5927\u4F5C\u6226 (Great Mahou Daisakusen 000121 Japan)\0", NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_ORIENTATION_VERTICAL, 2, HARDWARE_CAPCOM_CPS2,
	NULL, gmdjRomInfo, gmdjRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,224,384,3,4
};
