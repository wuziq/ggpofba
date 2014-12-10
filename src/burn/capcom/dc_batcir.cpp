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

 {"P2 Coin"       , BIT_DIGITAL, CpsInp020+5, "p2 coin"  },
 {"P2 Start"      , BIT_DIGITAL, CpsInp020+1, "p2 start" },
 {"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"    },
 {"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"  },
 {"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"  },
 {"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right" },
 {"P2 Attack"     , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
 {"P2 Jump"       , BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},

 {"P3 Coin"       , BIT_DIGITAL, CpsInp020+6, "p3 coin"  },
 {"P3 Start"      , BIT_DIGITAL, CpsInp020+2, "p3 start" },
 {"P3 Up"         , BIT_DIGITAL, CpsInp011+3, "p3 up"    },
 {"P3 Down"       , BIT_DIGITAL, CpsInp011+2, "p3 down"  },
 {"P3 Left"       , BIT_DIGITAL, CpsInp011+1, "p3 left"  },
 {"P3 Right"      , BIT_DIGITAL, CpsInp011+0, "p3 right" },
 {"P3 Attack"     , BIT_DIGITAL, CpsInp011+4, "p3 fire 1"},
 {"P3 Jump"       , BIT_DIGITAL, CpsInp011+5, "p3 fire 2"},

 {"P4 Coin"       , BIT_DIGITAL, CpsInp020+7, "p4 coin"  },
 {"P4 Start"      , BIT_DIGITAL, CpsInp020+3, "p4 start" },
 {"P4 Up"         , BIT_DIGITAL, CpsInp010+3, "p4 up"    },
 {"P4 Down"       , BIT_DIGITAL, CpsInp010+2, "p4 down"  },
 {"P4 Left"       , BIT_DIGITAL, CpsInp010+1, "p4 left"  },
 {"P4 Right"      , BIT_DIGITAL, CpsInp010+0, "p4 right" },
 {"P4 Attack"     , BIT_DIGITAL, CpsInp010+4, "p4 fire 1"},
 {"P4 Jump"       , BIT_DIGITAL, CpsInp010+5, "p4 fire 2"},

 {"Reset"         , BIT_DIGITAL, &CpsReset,   "reset"    },
 {"Diagnostic"    , BIT_DIGITAL, CpsInp021+1, "diag"     },
 {"Service"       , BIT_DIGITAL, CpsInp021+2, "service"  },
};

STDINPUTINFO(Drv);

static struct BurnRomInfo BatcirRomDesc[] = {
	{ "btce.03",       0x80000, 0xbc60484b, 1 | BRF_ESS | BRF_PRG },
	{ "btce.04",       0x80000, 0x457d55f6, 1 | BRF_ESS | BRF_PRG },
	{ "btce.05",       0x80000, 0xe86560d7, 1 | BRF_ESS | BRF_PRG },
	{ "btce.06",       0x80000, 0xf778e61b, 1 | BRF_ESS | BRF_PRG },
	{ "btc.07",        0x80000, 0x7322d5db, 1 | BRF_ESS | BRF_PRG },
	{ "btc.08",        0x80000, 0x6aac85ab, 1 | BRF_ESS | BRF_PRG },
	{ "btc.09",        0x80000, 0x1203db08, 1 | BRF_ESS | BRF_PRG },

	{ "btc.13m",      0x400000, 0xdc705bad, 3 | BRF_GRA },
	{ "btc.15m",      0x400000, 0xe5779a3c, 3 | BRF_GRA },
	{ "btc.17m",      0x400000, 0xb33f4112, 3 | BRF_GRA },
	{ "btc.19m",      0x400000, 0xa6fcdb7e, 3 | BRF_GRA },

	{ "btc.01",       0x020000, 0x1e194310, 4 | BRF_ESS | BRF_PRG },
	{ "btc.02",       0x020000, 0x01aeb8e6, 4 | BRF_ESS | BRF_PRG },

	{ "btc.11m",      0x200000, 0xc27f2229, 5 | BRF_SND },
	{ "btc.12m",      0x200000, 0x418a2e33, 5 | BRF_SND },
};


STD_ROM_PICK(Batcir) STD_ROM_FN(Batcir)

static struct BurnRomInfo BatciraRomDesc[] = {
	{ "btca.03",       0x80000, 0x1ad20d87, 1 | BRF_ESS | BRF_PRG },
	{ "btca.04",       0x80000, 0x2b3f4dbe, 1 | BRF_ESS | BRF_PRG },
	{ "btca.05",       0x80000, 0x8238a3d9, 1 | BRF_ESS | BRF_PRG },
	{ "btca.06",       0x80000, 0x446c7c02, 1 | BRF_ESS | BRF_PRG },
	{ "btc.07",        0x80000, 0x7322d5db, 1 | BRF_ESS | BRF_PRG },
	{ "btc.08",        0x80000, 0x6aac85ab, 1 | BRF_ESS | BRF_PRG },
	{ "btc.09",        0x80000, 0x1203db08, 1 | BRF_ESS | BRF_PRG },

	{ "btc.13m",      0x400000, 0xdc705bad, 3 | BRF_GRA },
	{ "btc.15m",      0x400000, 0xe5779a3c, 3 | BRF_GRA },
	{ "btc.17m",      0x400000, 0xb33f4112, 3 | BRF_GRA },
	{ "btc.19m",      0x400000, 0xa6fcdb7e, 3 | BRF_GRA },

	{ "btc.01",       0x020000, 0x1e194310, 4 | BRF_ESS | BRF_PRG },
	{ "btc.02",       0x020000, 0x01aeb8e6, 4 | BRF_ESS | BRF_PRG },

	{ "btc.11m",      0x200000, 0xc27f2229, 5 | BRF_SND },
	{ "btc.12m",      0x200000, 0x418a2e33, 5 | BRF_SND },
};


STD_ROM_PICK(Batcira) STD_ROM_FN(Batcira)

static struct BurnRomInfo BatcirjRomDesc[] = {
	{ "btcj.03",       0x80000, 0x6b7e168d, 1 | BRF_ESS | BRF_PRG },
	{ "btcj.04",       0x80000, 0x46ba3467, 1 | BRF_ESS | BRF_PRG },
	{ "btcj.05",       0x80000, 0x0e23a859, 1 | BRF_ESS | BRF_PRG },
	{ "btcj.06",       0x80000, 0xa853b59c, 1 | BRF_ESS | BRF_PRG },
	{ "btc.07",        0x80000, 0x7322d5db, 1 | BRF_ESS | BRF_PRG },
	{ "btc.08",        0x80000, 0x6aac85ab, 1 | BRF_ESS | BRF_PRG },
	{ "btc.09",        0x80000, 0x1203db08, 1 | BRF_ESS | BRF_PRG },

	{ "btc.13m",      0x400000, 0xdc705bad, 3 | BRF_GRA },
	{ "btc.15m",      0x400000, 0xe5779a3c, 3 | BRF_GRA },
	{ "btc.17m",      0x400000, 0xb33f4112, 3 | BRF_GRA },
	{ "btc.19m",      0x400000, 0xa6fcdb7e, 3 | BRF_GRA },

	{ "btc.01",       0x020000, 0x1e194310, 4 | BRF_ESS | BRF_PRG },
	{ "btc.02",       0x020000, 0x01aeb8e6, 4 | BRF_ESS | BRF_PRG },

	{ "btc.11m",      0x200000, 0xc27f2229, 5 | BRF_SND },
	{ "btc.12m",      0x200000, 0x418a2e33, 5 | BRF_SND },
};


STD_ROM_PICK(Batcirj) STD_ROM_FN(Batcirj)

struct BurnDriver BurnDrvCpsBatcir = {
	"batcir", NULL, NULL, "1997",
	"Battle Circuit (970319 Euro)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,4,HARDWARE_CAPCOM_CPS2,
	NULL, BatcirRomInfo, BatcirRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsBatcira = {
	"batcira", "batcir", NULL, "1997",
	"Battle Circuit (970319 Asia)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,4,HARDWARE_CAPCOM_CPS2,
	NULL, BatciraRomInfo, BatciraRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsBatcirj = {
	"batcirj", "batcir", NULL, "1997",
	"Battle Circuit (970319 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,4,HARDWARE_CAPCOM_CPS2,
	NULL, BatcirjRomInfo, BatcirjRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
