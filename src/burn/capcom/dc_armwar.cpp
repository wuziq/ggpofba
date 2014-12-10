#include "cps.h"

static struct BurnInputInfo DrvInputList[] =
{
  {"P1 Coin"       , BIT_DIGITAL, CpsInp020+4, "p1 coin"  },
  {"P1 Start"      , BIT_DIGITAL, CpsInp020+0, "p1 start" },
  {"P1 Up"         , BIT_DIGITAL, CpsInp001+3, "p1 up"    },
  {"P1 Down"       , BIT_DIGITAL, CpsInp001+2, "p1 down"  },
  {"P1 Left"       , BIT_DIGITAL, CpsInp001+1, "p1 left"  },
  {"P1 Right"      , BIT_DIGITAL, CpsInp001+0, "p1 right" },
  {"P1 Attack"     , BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},
  {"P1 Jump"       , BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},
  {"P1 Shot"       , BIT_DIGITAL, CpsInp001+6, "p1 fire 3"},

  {"P2 Coin"       , BIT_DIGITAL, CpsInp020+5, "p2 coin"  },
  {"P2 Start"      , BIT_DIGITAL, CpsInp020+1, "p2 start" },
  {"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"    },
  {"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"  },
  {"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"  },
  {"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right" },
  {"P2 Attack"     , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
  {"P2 Jump"       , BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},
  {"P2 Shot"       , BIT_DIGITAL, CpsInp000+6, "p2 fire 3"},

  {"P3 Coin"       , BIT_DIGITAL, CpsInp020+6, "p3 coin"  },
  {"P3 Start"      , BIT_DIGITAL, CpsInp020+2, "p3 start" },
  {"P3 Up"         , BIT_DIGITAL, CpsInp011+3, "p3 up"    },
  {"P3 Down"       , BIT_DIGITAL, CpsInp011+2, "p3 down"  },
  {"P3 Left"       , BIT_DIGITAL, CpsInp011+1, "p3 left"  },
  {"P3 Right"      , BIT_DIGITAL, CpsInp011+0, "p3 right" },
  {"P3 Attack"     , BIT_DIGITAL, CpsInp011+4, "p3 fire 1"},
  {"P3 Jump"       , BIT_DIGITAL, CpsInp011+5, "p3 fire 2"},
  {"P3 Shot"       , BIT_DIGITAL, CpsInp011+6, "p3 fire 3"},

  {"Reset"         , BIT_DIGITAL, &CpsReset  , "reset"    },
  {"Diagnostic"    , BIT_DIGITAL, CpsInp021+1, "diag"     },
  {"Service"       , BIT_DIGITAL, CpsInp021+2, "service"  },
};

STDINPUTINFO(Drv);

static struct BurnRomInfo ArmwarRomDesc[] = {
	{ "pwge.03c",      0x80000, 0x31f74931, 1 | BRF_ESS | BRF_PRG },
	{ "pwge.04c",      0x80000, 0x16f34f5f, 1 | BRF_ESS | BRF_PRG },
	{ "pwge.05b",      0x80000, 0x4403ed08, 1 | BRF_ESS | BRF_PRG },
	{ "pwg.06",        0x80000, 0x87a60ce8, 1 | BRF_ESS | BRF_PRG },
	{ "pwg.07",        0x80000, 0xf7b148df, 1 | BRF_ESS | BRF_PRG },
	{ "pwg.08",        0x80000, 0xcc62823e, 1 | BRF_ESS | BRF_PRG },
	{ "pwg.09a",       0x80000, 0x4c26baee, 1 | BRF_ESS | BRF_PRG },
	{ "pwg.10",        0x80000, 0x07c4fb28, 1 | BRF_ESS | BRF_PRG },

	{ "pwg.13m",      0x400000, 0xae8fe08e, 3 | BRF_GRA },
	{ "pwg.15m",      0x400000, 0xdb560f58, 3 | BRF_GRA },
	{ "pwg.17m",      0x400000, 0xbc475b94, 3 | BRF_GRA },
	{ "pwg.19m",      0x400000, 0x07439ff7, 3 | BRF_GRA },
	{ "pwg.14m",      0x100000, 0xc3f9ba63, 3 | BRF_GRA },
	{ "pwg.16m",      0x100000, 0x815b0e7b, 3 | BRF_GRA },
	{ "pwg.18m",      0x100000, 0x0109c71b, 3 | BRF_GRA },
	{ "pwg.20m",      0x100000, 0xeb75ffbe, 3 | BRF_GRA },

	{ "pwg.01",       0x020000, 0x18a5c0e4, 4 | BRF_ESS | BRF_PRG },
	{ "pwg.02",       0x020000, 0xc9dfffa6, 4 | BRF_ESS | BRF_PRG },

	{ "pwg.11m",      0x200000, 0xa78f7433, 5 | BRF_SND },
	{ "pwg.12m",      0x200000, 0x77438ed0, 5 | BRF_SND },
};


STD_ROM_PICK(Armwar) STD_ROM_FN(Armwar)

static struct BurnRomInfo Armwarr1RomDesc[] = {
	{ "pwge.03b",      0x80000, 0xe822e3e9, 1 | BRF_ESS | BRF_PRG },
	{ "pwge.04b",      0x80000, 0x4f89de39, 1 | BRF_ESS | BRF_PRG },
	{ "pwge.05a",      0x80000, 0x83df24e5, 1 | BRF_ESS | BRF_PRG },
	{ "pwg.06",        0x80000, 0x87a60ce8, 1 | BRF_ESS | BRF_PRG },
	{ "pwg.07",        0x80000, 0xf7b148df, 1 | BRF_ESS | BRF_PRG },
	{ "pwg.08",        0x80000, 0xcc62823e, 1 | BRF_ESS | BRF_PRG },
	{ "pwg.09",        0x80000, 0xddc85ca6, 1 | BRF_ESS | BRF_PRG },
	{ "pwg.10",        0x80000, 0x07c4fb28, 1 | BRF_ESS | BRF_PRG },

	{ "pwg.13m",      0x400000, 0xae8fe08e, 3 | BRF_GRA },
	{ "pwg.15m",      0x400000, 0xdb560f58, 3 | BRF_GRA },
	{ "pwg.17m",      0x400000, 0xbc475b94, 3 | BRF_GRA },
	{ "pwg.19m",      0x400000, 0x07439ff7, 3 | BRF_GRA },
	{ "pwg.14m",      0x100000, 0xc3f9ba63, 3 | BRF_GRA },
	{ "pwg.16m",      0x100000, 0x815b0e7b, 3 | BRF_GRA },
	{ "pwg.18m",      0x100000, 0x0109c71b, 3 | BRF_GRA },
	{ "pwg.20m",      0x100000, 0xeb75ffbe, 3 | BRF_GRA },

	{ "pwg.01",       0x020000, 0x18a5c0e4, 4 | BRF_ESS | BRF_PRG },
	{ "pwg.02",       0x020000, 0xc9dfffa6, 4 | BRF_ESS | BRF_PRG },

	{ "pwg.11m",      0x200000, 0xa78f7433, 5 | BRF_SND },
	{ "pwg.12m",      0x200000, 0x77438ed0, 5 | BRF_SND },
};


STD_ROM_PICK(Armwarr1) STD_ROM_FN(Armwarr1)

static struct BurnRomInfo ArmwaruRomDesc[] = {
	{ "pwgu.03b",      0x80000, 0x8b95497a, 1 | BRF_ESS | BRF_PRG },
	{ "pwgu.04b",      0x80000, 0x29eb5661, 1 | BRF_ESS | BRF_PRG },
	{ "pwgu.05b",      0x80000, 0xa54e9e44, 1 | BRF_ESS | BRF_PRG },
	{ "pwg.06",        0x80000, 0x87a60ce8, 1 | BRF_ESS | BRF_PRG },
	{ "pwg.07",        0x80000, 0xf7b148df, 1 | BRF_ESS | BRF_PRG },
	{ "pwg.08",        0x80000, 0xcc62823e, 1 | BRF_ESS | BRF_PRG },
	{ "pwg.09a",       0x80000, 0x4c26baee, 1 | BRF_ESS | BRF_PRG },
	{ "pwg.10",        0x80000, 0x07c4fb28, 1 | BRF_ESS | BRF_PRG },

	{ "pwg.13m",      0x400000, 0xae8fe08e, 3 | BRF_GRA },
	{ "pwg.15m",      0x400000, 0xdb560f58, 3 | BRF_GRA },
	{ "pwg.17m",      0x400000, 0xbc475b94, 3 | BRF_GRA },
	{ "pwg.19m",      0x400000, 0x07439ff7, 3 | BRF_GRA },
	{ "pwg.14m",      0x100000, 0xc3f9ba63, 3 | BRF_GRA },
	{ "pwg.16m",      0x100000, 0x815b0e7b, 3 | BRF_GRA },
	{ "pwg.18m",      0x100000, 0x0109c71b, 3 | BRF_GRA },
	{ "pwg.20m",      0x100000, 0xeb75ffbe, 3 | BRF_GRA },

	{ "pwg.01",       0x020000, 0x18a5c0e4, 4 | BRF_ESS | BRF_PRG },
	{ "pwg.02",       0x020000, 0xc9dfffa6, 4 | BRF_ESS | BRF_PRG },

	{ "pwg.11m",      0x200000, 0xa78f7433, 5 | BRF_SND },
	{ "pwg.12m",      0x200000, 0x77438ed0, 5 | BRF_SND },
};


STD_ROM_PICK(Armwaru) STD_ROM_FN(Armwaru)

static struct BurnRomInfo PgearRomDesc[] = {
	{ "pwgj.03a",      0x80000, 0xc79c0c02, 1 | BRF_ESS | BRF_PRG },
	{ "pwgj.04a",      0x80000, 0x167c6ed8, 1 | BRF_ESS | BRF_PRG },
	{ "pwgj.05a",      0x80000, 0xa63fb400, 1 | BRF_ESS | BRF_PRG },
	{ "pwg.06",        0x80000, 0x87a60ce8, 1 | BRF_ESS | BRF_PRG },
	{ "pwg.07",        0x80000, 0xf7b148df, 1 | BRF_ESS | BRF_PRG },
	{ "pwg.08",        0x80000, 0xcc62823e, 1 | BRF_ESS | BRF_PRG },
	{ "pwg.09a",       0x80000, 0x4c26baee, 1 | BRF_ESS | BRF_PRG },
	{ "pwg.10",        0x80000, 0x07c4fb28, 1 | BRF_ESS | BRF_PRG },

	{ "pwg.13m",      0x400000, 0xae8fe08e, 3 | BRF_GRA },
	{ "pwg.15m",      0x400000, 0xdb560f58, 3 | BRF_GRA },
	{ "pwg.17m",      0x400000, 0xbc475b94, 3 | BRF_GRA },
	{ "pwg.19m",      0x400000, 0x07439ff7, 3 | BRF_GRA },
	{ "pwg.14m",      0x100000, 0xc3f9ba63, 3 | BRF_GRA },
	{ "pwg.16m",      0x100000, 0x815b0e7b, 3 | BRF_GRA },
	{ "pwg.18m",      0x100000, 0x0109c71b, 3 | BRF_GRA },
	{ "pwg.20m",      0x100000, 0xeb75ffbe, 3 | BRF_GRA },

	{ "pwg.01",       0x020000, 0x18a5c0e4, 4 | BRF_ESS | BRF_PRG },
	{ "pwg.02",       0x020000, 0xc9dfffa6, 4 | BRF_ESS | BRF_PRG },

	{ "pwg.11m",      0x200000, 0xa78f7433, 5 | BRF_SND },
	{ "pwg.12m",      0x200000, 0x77438ed0, 5 | BRF_SND },
};


STD_ROM_PICK(Pgear) STD_ROM_FN(Pgear)

static struct BurnRomInfo Pgearr1RomDesc[] = {
	{ "pwgj.03",       0x80000, 0xf264e74b, 1 | BRF_ESS | BRF_PRG },
	{ "pwgj.04",       0x80000, 0x23a84983, 1 | BRF_ESS | BRF_PRG },
	{ "pwgj.05",       0x80000, 0xbef58c62, 1 | BRF_ESS | BRF_PRG },
	{ "pwg.06",        0x80000, 0x87a60ce8, 1 | BRF_ESS | BRF_PRG },
	{ "pwg.07",        0x80000, 0xf7b148df, 1 | BRF_ESS | BRF_PRG },
	{ "pwg.08",        0x80000, 0xcc62823e, 1 | BRF_ESS | BRF_PRG },
	{ "pwg.09",        0x80000, 0xddc85ca6, 1 | BRF_ESS | BRF_PRG },
	{ "pwg.10",        0x80000, 0x07c4fb28, 1 | BRF_ESS | BRF_PRG },

	{ "pwg.13m",      0x400000, 0xae8fe08e, 3 | BRF_GRA },
	{ "pwg.15m",      0x400000, 0xdb560f58, 3 | BRF_GRA },
	{ "pwg.17m",      0x400000, 0xbc475b94, 3 | BRF_GRA },
	{ "pwg.19m",      0x400000, 0x07439ff7, 3 | BRF_GRA },
	{ "pwg.14m",      0x100000, 0xc3f9ba63, 3 | BRF_GRA },
	{ "pwg.16m",      0x100000, 0x815b0e7b, 3 | BRF_GRA },
	{ "pwg.18m",      0x100000, 0x0109c71b, 3 | BRF_GRA },
	{ "pwg.20m",      0x100000, 0xeb75ffbe, 3 | BRF_GRA },

	{ "pwg.01",       0x020000, 0x18a5c0e4, 4 | BRF_ESS | BRF_PRG },
	{ "pwg.02",       0x020000, 0xc9dfffa6, 4 | BRF_ESS | BRF_PRG },

	{ "pwg.11m",      0x200000, 0xa78f7433, 5 | BRF_SND },
	{ "pwg.12m",      0x200000, 0x77438ed0, 5 | BRF_SND },
};


STD_ROM_PICK(Pgearr1) STD_ROM_FN(Pgearr1)

static struct BurnRomInfo ArmwaraRomDesc[] = {
	{ "pwga.03a",      0x80000, 0x8d474ab1, 1 | BRF_ESS | BRF_PRG },
	{ "pwga.04a",      0x80000, 0x81b5aec7, 1 | BRF_ESS | BRF_PRG },
	{ "pwga.05a",      0x80000, 0x2618e819, 1 | BRF_ESS | BRF_PRG },
	{ "pwg.06",        0x80000, 0x87a60ce8, 1 | BRF_ESS | BRF_PRG },
	{ "pwg.07",        0x80000, 0xf7b148df, 1 | BRF_ESS | BRF_PRG },
	{ "pwg.08",        0x80000, 0xcc62823e, 1 | BRF_ESS | BRF_PRG },
	{ "pwg.09",        0x80000, 0xddc85ca6, 1 | BRF_ESS | BRF_PRG },
	{ "pwg.10",        0x80000, 0x07c4fb28, 1 | BRF_ESS | BRF_PRG },

	{ "pwg.13m",      0x400000, 0xae8fe08e, 3 | BRF_GRA },
	{ "pwg.15m",      0x400000, 0xdb560f58, 3 | BRF_GRA },
	{ "pwg.17m",      0x400000, 0xbc475b94, 3 | BRF_GRA },
	{ "pwg.19m",      0x400000, 0x07439ff7, 3 | BRF_GRA },
	{ "pwg.14m",      0x100000, 0xc3f9ba63, 3 | BRF_GRA },
	{ "pwg.16m",      0x100000, 0x815b0e7b, 3 | BRF_GRA },
	{ "pwg.18m",      0x100000, 0x0109c71b, 3 | BRF_GRA },
	{ "pwg.20m",      0x100000, 0xeb75ffbe, 3 | BRF_GRA },

	{ "pwg.01",       0x020000, 0x18a5c0e4, 4 | BRF_ESS | BRF_PRG },
	{ "pwg.02",       0x020000, 0xc9dfffa6, 4 | BRF_ESS | BRF_PRG },

	{ "pwg.11m",      0x200000, 0xa78f7433, 5 | BRF_SND },
	{ "pwg.12m",      0x200000, 0x77438ed0, 5 | BRF_SND },
};


STD_ROM_PICK(Armwara) STD_ROM_FN(Armwara)

struct BurnDriver BurnDrvCpsArmwar = {
	"armwar", NULL, NULL, "1994",
	"Armored Warriors (941024 Europe)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,3,HARDWARE_CAPCOM_CPS2,
	NULL, ArmwarRomInfo, ArmwarRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsArmwarr1 = {
	"armwarr1", "armwar", NULL, "1994",
	"Armored Warriors (941011 Europe)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,3,HARDWARE_CAPCOM_CPS2,
	NULL, Armwarr1RomInfo, Armwarr1RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsArmwaru = {
	"armwaru", "armwar", NULL, "1994",
	"Armored Warriors (941024 USA)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,3,HARDWARE_CAPCOM_CPS2,
	NULL, ArmwaruRomInfo, ArmwaruRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsPgear = {
	"pgear", "armwar", NULL, "1994",
	"Powered Gear - strategic variant armor equipment (941024 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,3,HARDWARE_CAPCOM_CPS2,
	NULL, PgearRomInfo, PgearRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsPgearr1 = {
	"pgearr1", "armwar", NULL, "1994",
	"Powered Gear - strategic variant armor equipment (940916 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,3,HARDWARE_CAPCOM_CPS2,
	NULL, Pgearr1RomInfo, Pgearr1RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsArmwara = {
	"armwara", "armwar", NULL, "1994",
	"Armored Warriors (940920 Asia)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,3,HARDWARE_CAPCOM_CPS2,
	NULL, ArmwaraRomInfo, ArmwaraRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
