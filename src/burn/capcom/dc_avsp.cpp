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
  {"P1 Attack"     , BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},
  {"P1 Jump"       , BIT_DIGITAL, CpsInp001+6, "p1 fire 3"},

  {"P2 Coin"       , BIT_DIGITAL, CpsInp020+5, "p2 coin"  },
  {"P2 Start"      , BIT_DIGITAL, CpsInp020+1, "p2 start" },
  {"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"    },
  {"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"  },
  {"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"  },
  {"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right" },
  {"P2 Shot"       , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
  {"P2 Attack"     , BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},
  {"P2 Jump"       , BIT_DIGITAL, CpsInp000+6, "p2 fire 3"},

  {"P3 Coin"       , BIT_DIGITAL, CpsInp020+6, "p3 coin"  },
  {"P3 Start"      , BIT_DIGITAL, CpsInp020+2, "p3 start" },
  {"P3 Up"         , BIT_DIGITAL, CpsInp011+3, "p3 up"    },
  {"P3 Down"       , BIT_DIGITAL, CpsInp011+2, "p3 down"  },
  {"P3 Left"       , BIT_DIGITAL, CpsInp011+1, "p3 left"  },
  {"P3 Right"      , BIT_DIGITAL, CpsInp011+0, "p3 right" },
  {"P3 Shot"       , BIT_DIGITAL, CpsInp011+4, "p3 fire 1"},
  {"P3 Attack"     , BIT_DIGITAL, CpsInp011+5, "p3 fire 2"},
  {"P3 Jump"       , BIT_DIGITAL, CpsInp011+6, "p3 fire 3"},

  {"Reset"         , BIT_DIGITAL, &CpsReset  , "reset"    },
  {"Diagnostic"    , BIT_DIGITAL, CpsInp021+1, "diag"     },
  {"Service"       , BIT_DIGITAL, CpsInp021+2, "service"  },
};

STDINPUTINFO(Drv);

static struct BurnRomInfo AvspRomDesc[] = {
	{ "avpe.03d",      0x80000, 0x774334a9, 1 | BRF_ESS | BRF_PRG },
	{ "avpe.04d",      0x80000, 0x7fa83769, 1 | BRF_ESS | BRF_PRG },
	{ "avp.05d",       0x80000, 0xfbfb5d7a, 1 | BRF_ESS | BRF_PRG },
	{ "avp.06",        0x80000, 0x190b817f, 1 | BRF_ESS | BRF_PRG },

	{ "avp.13m",      0x200000, 0x8f8b5ae4, 3 | BRF_GRA },
	{ "avp.15m",      0x200000, 0xb00280df, 3 | BRF_GRA },
	{ "avp.17m",      0x200000, 0x94403195, 3 | BRF_GRA },
	{ "avp.19m",      0x200000, 0xe1981245, 3 | BRF_GRA },
	{ "avp.14m",      0x200000, 0xebba093e, 3 | BRF_GRA },
	{ "avp.16m",      0x200000, 0xfb228297, 3 | BRF_GRA },
	{ "avp.18m",      0x200000, 0x34fb7232, 3 | BRF_GRA },
	{ "avp.20m",      0x200000, 0xf90baa21, 3 | BRF_GRA },

	{ "avp.01",       0x020000, 0x2d3b4220, 4 | BRF_ESS | BRF_PRG },
	{ "avp.11m",      0x200000, 0x83499817, 5 | BRF_SND },
	{ "avp.12m",      0x200000, 0xf4110d49, 5 | BRF_SND },
};


STD_ROM_PICK(Avsp) STD_ROM_FN(Avsp)

static struct BurnRomInfo AvspuRomDesc[] = {
	{ "avpu.03d",      0x80000, 0x42757950, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "avpu.04d",      0x80000, 0x5abcdee6, 1 | BRF_ESS | BRF_PRG },
	{ "avp.05d",       0x80000, 0xfbfb5d7a, 1 | BRF_ESS | BRF_PRG },
	{ "avp.06",        0x80000, 0x190b817f, 1 | BRF_ESS | BRF_PRG },

	{ "avp.13m",      0x200000, 0x8f8b5ae4, 3 | BRF_GRA },
	{ "avp.15m",      0x200000, 0xb00280df, 3 | BRF_GRA },
	{ "avp.17m",      0x200000, 0x94403195, 3 | BRF_GRA },
	{ "avp.19m",      0x200000, 0xe1981245, 3 | BRF_GRA },
	{ "avp.14m",      0x200000, 0xebba093e, 3 | BRF_GRA },
	{ "avp.16m",      0x200000, 0xfb228297, 3 | BRF_GRA },
	{ "avp.18m",      0x200000, 0x34fb7232, 3 | BRF_GRA },
	{ "avp.20m",      0x200000, 0xf90baa21, 3 | BRF_GRA },

	{ "avp.01",       0x020000, 0x2d3b4220, 4 | BRF_ESS | BRF_PRG },
	{ "avp.11m",      0x200000, 0x83499817, 5 | BRF_SND },
	{ "avp.12m",      0x200000, 0xf4110d49, 5 | BRF_SND },
};


STD_ROM_PICK(Avspu) STD_ROM_FN(Avspu)

static struct BurnRomInfo AvspjRomDesc[] = {
	{ "avpj.03d",      0x80000, 0x49799119, 1 | BRF_ESS | BRF_PRG },
	{ "avpj.04d",      0x80000, 0x8cd2bba8, 1 | BRF_ESS | BRF_PRG },
	{ "avp.05d",       0x80000, 0xfbfb5d7a, 1 | BRF_ESS | BRF_PRG },
	{ "avp.06",        0x80000, 0x190b817f, 1 | BRF_ESS | BRF_PRG },

	{ "avp.13m",      0x200000, 0x8f8b5ae4, 3 | BRF_GRA },
	{ "avp.15m",      0x200000, 0xb00280df, 3 | BRF_GRA },
	{ "avp.17m",      0x200000, 0x94403195, 3 | BRF_GRA },
	{ "avp.19m",      0x200000, 0xe1981245, 3 | BRF_GRA },
	{ "avp.14m",      0x200000, 0xebba093e, 3 | BRF_GRA },
	{ "avp.16m",      0x200000, 0xfb228297, 3 | BRF_GRA },
	{ "avp.18m",      0x200000, 0x34fb7232, 3 | BRF_GRA },
	{ "avp.20m",      0x200000, 0xf90baa21, 3 | BRF_GRA },

	{ "avp.01",       0x020000, 0x2d3b4220, 4 | BRF_ESS | BRF_PRG },
	{ "avp.11m",      0x200000, 0x83499817, 5 | BRF_SND },
	{ "avp.12m",      0x200000, 0xf4110d49, 5 | BRF_SND },
};


STD_ROM_PICK(Avspj) STD_ROM_FN(Avspj)

static struct BurnRomInfo AvspaRomDesc[] = {
	{ "avpa.03d",      0x80000, 0x6c1c1858, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "avpa.04d",      0x80000, 0x94f50b0c, 1 | BRF_ESS | BRF_PRG },
	{ "avp.05d",       0x80000, 0xfbfb5d7a, 1 | BRF_ESS | BRF_PRG },
	{ "avp.06",        0x80000, 0x190b817f, 1 | BRF_ESS | BRF_PRG },

	{ "avp.13m",      0x200000, 0x8f8b5ae4, 3 | BRF_GRA },
	{ "avp.15m",      0x200000, 0xb00280df, 3 | BRF_GRA },
	{ "avp.17m",      0x200000, 0x94403195, 3 | BRF_GRA },
	{ "avp.19m",      0x200000, 0xe1981245, 3 | BRF_GRA },
	{ "avp.14m",      0x200000, 0xebba093e, 3 | BRF_GRA },
	{ "avp.16m",      0x200000, 0xfb228297, 3 | BRF_GRA },
	{ "avp.18m",      0x200000, 0x34fb7232, 3 | BRF_GRA },
	{ "avp.20m",      0x200000, 0xf90baa21, 3 | BRF_GRA },

	{ "avp.01",       0x020000, 0x2d3b4220, 4 | BRF_ESS | BRF_PRG },
	{ "avp.11m",      0x200000, 0x83499817, 5 | BRF_SND },
	{ "avp.12m",      0x200000, 0xf4110d49, 5 | BRF_SND },
};


STD_ROM_PICK(Avspa) STD_ROM_FN(Avspa)

static struct BurnRomInfo AvsphRomDesc[] = {
	{ "avph.03d",      0x80000, 0x3e440447, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "avph.04d",      0x80000, 0xaf6fc82f, 1 | BRF_ESS | BRF_PRG },
	{ "avp.05d",       0x80000, 0xfbfb5d7a, 1 | BRF_ESS | BRF_PRG },
	{ "avp.06",        0x80000, 0x190b817f, 1 | BRF_ESS | BRF_PRG },
	
	{ "avp.13m",      0x200000, 0x8f8b5ae4, 3 | BRF_GRA },
	{ "avp.15m",      0x200000, 0xb00280df, 3 | BRF_GRA },
	{ "avp.17m",      0x200000, 0x94403195, 3 | BRF_GRA },
	{ "avp.19m",      0x200000, 0xe1981245, 3 | BRF_GRA },
	{ "avp.14m",      0x200000, 0xebba093e, 3 | BRF_GRA },
	{ "avp.16m",      0x200000, 0xfb228297, 3 | BRF_GRA },
	{ "avp.18m",      0x200000, 0x34fb7232, 3 | BRF_GRA },
	{ "avp.20m",      0x200000, 0xf90baa21, 3 | BRF_GRA },

	{ "avp.01",       0x020000, 0x2d3b4220, 4 | BRF_ESS | BRF_PRG },
	{ "avp.11m",      0x200000, 0x83499817, 5 | BRF_SND },
	{ "avp.12m",      0x200000, 0xf4110d49, 5 | BRF_SND },
};


STD_ROM_PICK(Avsph) STD_ROM_FN(Avsph)

struct BurnDriver BurnDrvCpsAvsp = {
	"avsp", NULL, NULL, "1994",
	"Alien vs Predator (940520 Euro)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING ,3,HARDWARE_CAPCOM_CPS2,
	NULL, AvspRomInfo, AvspRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsAvspu = {
	"avspu", "avsp", NULL, "1994",
	"Alien vs Predator (940520 USA)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,3,HARDWARE_CAPCOM_CPS2,
	NULL, AvspuRomInfo, AvspuRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsAvspj = {
	"avspj", "avsp", NULL, "1994",
	"Alien vs Predator (940520 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,3,HARDWARE_CAPCOM_CPS2,
	NULL, AvspjRomInfo, AvspjRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsAvspa = {
	"avspa", "avsp", NULL, "1994",
	"Alien vs Predator (940520 Asia)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 3,HARDWARE_CAPCOM_CPS2,
	NULL, AvspaRomInfo, AvspaRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsAvsph = {
	"avsph", "avsp", NULL, "1994",
	"Alien vs Predator (940520 Hispanic)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 3,HARDWARE_CAPCOM_CPS2,
	NULL, AvsphRomInfo, AvsphRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
