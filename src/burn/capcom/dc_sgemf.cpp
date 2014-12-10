 #include "cps.h"

static struct BurnInputInfo DrvInputList[] =
{
  {"P1 Coin"       , BIT_DIGITAL, CpsInp020+4, "p1 coin"},
  {"P1 Start"      , BIT_DIGITAL, CpsInp020+0, "p1 start"},
  {"P1 Up"         , BIT_DIGITAL, CpsInp001+3, "p1 up"},
  {"P1 Down"       , BIT_DIGITAL, CpsInp001+2, "p1 down"},
  {"P1 Left"       , BIT_DIGITAL, CpsInp001+1, "p1 left"},
  {"P1 Right"      , BIT_DIGITAL, CpsInp001+0, "p1 right"},
  {"P1 Punch"      , BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},
  {"P1 Kick"       , BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},
  {"P1 Special"    , BIT_DIGITAL, CpsInp001+6, "p1 fire 3"},

  {"P2 Coin"       , BIT_DIGITAL, CpsInp020+5, "p2 coin"},
  {"P2 Start"      , BIT_DIGITAL, CpsInp020+1, "p2 start"},
  {"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"},
  {"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"},
  {"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"},
  {"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right"},
  {"P2 Punch"      , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
  {"P2 Kick"       , BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},
  {"P2 Special"    , BIT_DIGITAL, CpsInp000+6, "p2 fire 3"},

  {"Reset"         , BIT_DIGITAL, &CpsReset   , "reset"},
  {"Diagnostic"    , BIT_DIGITAL, CpsInp021+1, "diag"},
  {"Service"       , BIT_DIGITAL, CpsInp021+2, "service"},
};

STDINPUTINFO(Drv);

static struct BurnRomInfo SgemfRomDesc[] = {
	{ "pcfu.03",      0x080000, 0xac2e8566, 1 | BRF_ESS | BRF_PRG }, // 1
	{ "pcf.04",       0x080000, 0xf4314c96, 1 | BRF_ESS | BRF_PRG },
	{ "pcf.05",       0x080000, 0x215655f6, 1 | BRF_ESS | BRF_PRG },
	{ "pcf.06",       0x080000, 0xea6f13ea, 1 | BRF_ESS | BRF_PRG },
	{ "pcf.07",       0x080000, 0x5ac6d5ea, 1 | BRF_ESS | BRF_PRG },

	{ "pcf.13m",       0x400000, 0x22d72ab9, 3 | BRF_GRA },			 // 6
	{ "pcf.15m",       0x400000, 0x16a4813c, 3 | BRF_GRA },
	{ "pcf.17m",       0x400000, 0x1097e035, 3 | BRF_GRA },
	{ "pcf.19m",       0x400000, 0xd362d874, 3 | BRF_GRA },
	{ "pcf.14m",       0x100000, 0x0383897c, 3 | BRF_GRA },			 // 10
	{ "pcf.16m",       0x100000, 0x76f91084, 3 | BRF_GRA },
	{ "pcf.18m",       0x100000, 0x756c3754, 3 | BRF_GRA },
	{ "pcf.20m",       0x100000, 0x9ec9277d, 3 | BRF_GRA },

	{ "pcf.01",       0x020000, 0x254e5f33, 4 | BRF_ESS | BRF_PRG }, // 14
	{ "pcf.02",       0x020000, 0x6902f4f9, 4 | BRF_ESS | BRF_PRG },

	{ "pcf.11m",       0x400000, 0xa5dea005, 5 | BRF_SND },			 // 16
	{ "pcf.12m",       0x400000, 0x4ce235fe, 5 | BRF_SND },
};


STD_ROM_PICK(Sgemf) STD_ROM_FN(Sgemf)

static struct BurnRomInfo PfghtjRomDesc[] = {
	{ "pcfj.03",      0x080000, 0x681da43e, 1 | BRF_ESS | BRF_PRG }, // 1
	{ "pcf.04",       0x080000, 0xf4314c96, 1 | BRF_ESS | BRF_PRG },
	{ "pcf.05",       0x080000, 0x215655f6, 1 | BRF_ESS | BRF_PRG },
	{ "pcf.06",       0x080000, 0xea6f13ea, 1 | BRF_ESS | BRF_PRG },
	{ "pcf.07",       0x080000, 0x5ac6d5ea, 1 | BRF_ESS | BRF_PRG },

	{ "pcf.13m",       0x400000, 0x22d72ab9, 3 | BRF_GRA },			 // 6
	{ "pcf.15m",       0x400000, 0x16a4813c, 3 | BRF_GRA },
	{ "pcf.17m",       0x400000, 0x1097e035, 3 | BRF_GRA },
	{ "pcf.19m",       0x400000, 0xd362d874, 3 | BRF_GRA },
	{ "pcf.14m",       0x100000, 0x0383897c, 3 | BRF_GRA },			 // 10
	{ "pcf.16m",       0x100000, 0x76f91084, 3 | BRF_GRA },
	{ "pcf.18m",       0x100000, 0x756c3754, 3 | BRF_GRA },
	{ "pcf.20m",       0x100000, 0x9ec9277d, 3 | BRF_GRA },

	{ "pcf.01",       0x020000, 0x254e5f33, 4 | BRF_ESS | BRF_PRG }, // 14
	{ "pcf.02",       0x020000, 0x6902f4f9, 4 | BRF_ESS | BRF_PRG },

	{ "pcf.11m",       0x400000, 0xa5dea005, 5 | BRF_SND },			 // 16
	{ "pcf.12m",       0x400000, 0x4ce235fe, 5 | BRF_SND },
};


STD_ROM_PICK(Pfghtj) STD_ROM_FN(Pfghtj)

static struct BurnRomInfo SgemfaRomDesc[] = {
	{ "pcfa.03",      0x080000, 0xe17c089a, 1 | BRF_ESS | BRF_PRG }, // 1
	{ "pcf.04",       0x080000, 0xf4314c96, 1 | BRF_ESS | BRF_PRG },
	{ "pcf.05",       0x080000, 0x215655f6, 1 | BRF_ESS | BRF_PRG },
	{ "pcf.06",       0x080000, 0xea6f13ea, 1 | BRF_ESS | BRF_PRG },
	{ "pcf.07",       0x080000, 0x5ac6d5ea, 1 | BRF_ESS | BRF_PRG },

	{ "pcf.13m",       0x400000, 0x22d72ab9, 3 | BRF_GRA },			 // 6
	{ "pcf.15m",       0x400000, 0x16a4813c, 3 | BRF_GRA },
	{ "pcf.17m",       0x400000, 0x1097e035, 3 | BRF_GRA },
	{ "pcf.19m",       0x400000, 0xd362d874, 3 | BRF_GRA },
	{ "pcf.14m",       0x100000, 0x0383897c, 3 | BRF_GRA },			 // 10
	{ "pcf.16m",       0x100000, 0x76f91084, 3 | BRF_GRA },
	{ "pcf.18m",       0x100000, 0x756c3754, 3 | BRF_GRA },
	{ "pcf.20m",       0x100000, 0x9ec9277d, 3 | BRF_GRA },

	{ "pcf.01",       0x020000, 0x254e5f33, 4 | BRF_ESS | BRF_PRG }, // 14
	{ "pcf.02",       0x020000, 0x6902f4f9, 4 | BRF_ESS | BRF_PRG },

	{ "pcf.11m",       0x400000, 0xa5dea005, 5 | BRF_SND },			 // 16
	{ "pcf.12m",       0x400000, 0x4ce235fe, 5 | BRF_SND },
};


STD_ROM_PICK(Sgemfa) STD_ROM_FN(Sgemfa)

static struct BurnRomInfo SgemfhRomDesc[] = {
	{ "pcfh.03",      0x080000, 0xe9103347, 1 | BRF_ESS | BRF_PRG }, // 1
	{ "pcf.04",       0x080000, 0xf4314c96, 1 | BRF_ESS | BRF_PRG },
	{ "pcf.05",       0x080000, 0x215655f6, 1 | BRF_ESS | BRF_PRG },
	{ "pcf.06",       0x080000, 0xea6f13ea, 1 | BRF_ESS | BRF_PRG },
	{ "pcf.07",       0x080000, 0x5ac6d5ea, 1 | BRF_ESS | BRF_PRG },

	{ "pcf.13m",       0x400000, 0x22d72ab9, 3 | BRF_GRA },			 // 6
	{ "pcf.15m",       0x400000, 0x16a4813c, 3 | BRF_GRA },
	{ "pcf.17m",       0x400000, 0x1097e035, 3 | BRF_GRA },
	{ "pcf.19m",       0x400000, 0xd362d874, 3 | BRF_GRA },
	{ "pcf.14m",       0x100000, 0x0383897c, 3 | BRF_GRA },			 // 10
	{ "pcf.16m",       0x100000, 0x76f91084, 3 | BRF_GRA },
	{ "pcf.18m",       0x100000, 0x756c3754, 3 | BRF_GRA },
	{ "pcf.20m",       0x100000, 0x9ec9277d, 3 | BRF_GRA },

	{ "pcf.01",       0x020000, 0x254e5f33, 4 | BRF_ESS | BRF_PRG }, // 14
	{ "pcf.02",       0x020000, 0x6902f4f9, 4 | BRF_ESS | BRF_PRG },

	{ "pcf.11m",       0x400000, 0xa5dea005, 5 | BRF_SND },			 // 16
	{ "pcf.12m",       0x400000, 0x4ce235fe, 5 | BRF_SND },
};


STD_ROM_PICK(Sgemfh) STD_ROM_FN(Sgemfh)

struct BurnDriver BurnDrvCpsSgemf = {
	"sgemf", NULL, NULL, "1997",
	"Super Gem Fighter Mini Mix (970904 USA)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS2,
	NULL, SgemfRomInfo, SgemfRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsPfghtj = {
	"pfghtj", "sgemf", NULL, "1997",
	"Pocket Fighter (970904 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, PfghtjRomInfo, PfghtjRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSgemfa = {
	"sgemfa", "sgemf", NULL, "1997",
	"Super Gem Fighter Mini Mix (970904 Asia)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, SgemfaRomInfo, SgemfaRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSgemfh = {
	"sgemfh", "sgemf", NULL, "1997",
	"Super Gem Fighter Mini Mix (970904 Hispanic)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, SgemfhRomInfo, SgemfhRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
