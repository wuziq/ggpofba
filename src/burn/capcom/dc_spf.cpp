#include "cps.h"

static struct BurnInputInfo DrvInputList[] =
{
  {"P1 Coin"       , BIT_DIGITAL, CpsInp020+4, "p1 coin"},
  {"P1 Start"      , BIT_DIGITAL, CpsInp020+0, "p1 start"},
  {"P1 Up"         , BIT_DIGITAL, CpsInp001+3, "p1 up"},
  {"P1 Down"       , BIT_DIGITAL, CpsInp001+2, "p1 down"},
  {"P1 Left"       , BIT_DIGITAL, CpsInp001+1, "p1 left"},
  {"P1 Right"      , BIT_DIGITAL, CpsInp001+0, "p1 right"},
  {"P1 Rotate Left" , BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},
  {"P1 Rotate Right", BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},

  {"P2 Coin"       , BIT_DIGITAL, CpsInp020+5, "p2 coin"},
  {"P2 Start"      , BIT_DIGITAL, CpsInp020+1, "p2 start"},
  {"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"},
  {"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"},
  {"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"},
  {"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right"},
  {"P2 Rotate Left", BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
  {"P2 Rotate Right", BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},

  {"Reset"         , BIT_DIGITAL, &CpsReset   , "reset"},
  {"Diagnostic"    , BIT_DIGITAL, CpsInp021+1, "diag"},
  {"Service"       , BIT_DIGITAL, CpsInp021+2, "service"},
};

STDINPUTINFO(Drv);

static struct BurnRomInfo Spf2tRomDesc[] = {
	{ "pzfu.03a",      0x80000, 0x346e62ef, 1 | BRF_ESS | BRF_PRG },
	{ "pzf.04",        0x80000, 0xb80649e2, 1 | BRF_ESS | BRF_PRG },

	{ "pzf.14m",      0x100000, 0x2d4881cb, 3 | BRF_GRA },			 // 3
	{ "pzf.16m",      0x100000, 0x4b0fd1be, 3 | BRF_GRA },
	{ "pzf.18m",      0x100000, 0xe43aac33, 3 | BRF_GRA },
	{ "pzf.20m",      0x100000, 0x7f536ff1, 3 | BRF_GRA },

	{ "pzf.01",       0x020000, 0x600fb2a3, 4 | BRF_ESS | BRF_PRG }, // 7
	{ "pzf.02",       0x020000, 0x496076e0, 4 | BRF_ESS | BRF_PRG },

	{ "pzf.11m",      0x200000, 0x78442743, 5 | BRF_SND },
	{ "pzf.12m",      0x200000, 0x399d2c7b, 5 | BRF_SND },
};


STD_ROM_PICK(Spf2t) STD_ROM_FN(Spf2t)

static struct BurnRomInfo Spf2taRomDesc[] = {
	{ "pzfa.03",       0x80000, 0x3cecfa78, 1 | BRF_ESS | BRF_PRG },
	{ "pzf.04",        0x80000, 0xb80649e2, 1 | BRF_ESS | BRF_PRG },

	{ "pzf.14m",      0x100000, 0x2d4881cb, 3 | BRF_GRA },			 // 3
	{ "pzf.16m",      0x100000, 0x4b0fd1be, 3 | BRF_GRA },
	{ "pzf.18m",      0x100000, 0xe43aac33, 3 | BRF_GRA },
	{ "pzf.20m",      0x100000, 0x7f536ff1, 3 | BRF_GRA },

	{ "pzf.01",       0x020000, 0x600fb2a3, 4 | BRF_ESS | BRF_PRG }, // 7
	{ "pzf.02",       0x020000, 0x496076e0, 4 | BRF_ESS | BRF_PRG },

	{ "pzf.11m",      0x200000, 0x78442743, 5 | BRF_SND },
	{ "pzf.12m",      0x200000, 0x399d2c7b, 5 | BRF_SND },
};


STD_ROM_PICK(Spf2ta) STD_ROM_FN(Spf2ta)

static struct BurnRomInfo Spf2xjRomDesc[] = {
	{ "pzfj.03a",      0x80000, 0x2070554a, 1 | BRF_ESS | BRF_PRG },
	{ "pzf.04",        0x80000, 0xb80649e2, 1 | BRF_ESS | BRF_PRG },

	{ "pzf.14m",      0x100000, 0x2d4881cb, 3 | BRF_GRA },			 // 3
	{ "pzf.16m",      0x100000, 0x4b0fd1be, 3 | BRF_GRA },
	{ "pzf.18m",      0x100000, 0xe43aac33, 3 | BRF_GRA },
	{ "pzf.20m",      0x100000, 0x7f536ff1, 3 | BRF_GRA },

	{ "pzf.01",       0x020000, 0x600fb2a3, 4 | BRF_ESS | BRF_PRG }, // 7
	{ "pzf.02",       0x020000, 0x496076e0, 4 | BRF_ESS | BRF_PRG },

	{ "pzf.11m",      0x200000, 0x78442743, 5 | BRF_SND },
	{ "pzf.12m",      0x200000, 0x399d2c7b, 5 | BRF_SND },
};


STD_ROM_PICK(Spf2xj) STD_ROM_FN(Spf2xj)

struct BurnDriver BurnDrvCpsSpf2t = {
	"spf2t", NULL, NULL, "1996",
	"Super Puzzle Fighter II Turbo (Super Puzzle Fighter 2 Turbo 960620 USA)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS2,
	NULL, Spf2tRomInfo, Spf2tRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSpf2xj = {
	"spf2xj", "spf2t", NULL, "1996",
	"Super Puzzle Fighter II X (Super Puzzle Fighter 2 X 960531 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Spf2xjRomInfo, Spf2xjRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSpf2ta = {
	"spf2ta", "spf2t", NULL, "1996",
	"Super Puzzle Fighter II Turbo (Super Puzzle Fighter 2 Turbo 960529 Asia)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Spf2taRomInfo, Spf2taRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
