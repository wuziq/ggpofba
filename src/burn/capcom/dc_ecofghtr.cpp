#include "cps.h"

static struct BurnInputInfo DrvInputList[] =
{
  {"P1 Coin"       , BIT_DIGITAL, CpsInp020+4, "p1 coin"  },
  {"P1 Start"      , BIT_DIGITAL, CpsInp020+0, "p1 start" },
  {"P1 Up"         , BIT_DIGITAL, CpsInp001+3, "p1 up"    },
  {"P1 Down"       , BIT_DIGITAL, CpsInp001+2, "p1 down"  },
  {"P1 Left"       , BIT_DIGITAL, CpsInp001+1, "p1 left"  },
  {"P1 Right"      , BIT_DIGITAL, CpsInp001+0, "p1 right" },
  {"P1 Turn 1"     , BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},
  {"P1 Attack"     , BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},
  {"P1 Turn 2"     , BIT_DIGITAL, CpsInp001+6, "p1 fire 3"},

  {"P2 Coin"       , BIT_DIGITAL, CpsInp020+5, "p2 coin"  },
  {"P2 Start"      , BIT_DIGITAL, CpsInp020+1, "p2 start" },
  {"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"    },
  {"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"  },
  {"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"  },
  {"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right" },
  {"P2 Turn 1"     , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
  {"P2 Attack"     , BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},
  {"P2 Turn 2"     , BIT_DIGITAL, CpsInp000+6, "p2 fire 3"},

  {"Reset"         , BIT_DIGITAL, &CpsReset  , "reset"    },
  {"Diagnostic"    , BIT_DIGITAL, CpsInp021+1, "diag"     },
  {"Service"       , BIT_DIGITAL, CpsInp021+2, "service"  },
};

STDINPUTINFO(Drv);

static struct BurnRomInfo EcofghtrRomDesc[] = {
	{ "uece.03",       0x80000, 0xec2c1137, 1 | BRF_ESS | BRF_PRG },
	{ "uece.04",       0x80000, 0xb35f99db, 1 | BRF_ESS | BRF_PRG },
	{ "uece.05",       0x80000, 0xd9d42d31, 1 | BRF_ESS | BRF_PRG },
	{ "uece.06",       0x80000, 0x9d9771cf, 1 | BRF_ESS | BRF_PRG },

	{ "uec.13m",      0x200000, 0xdcaf1436, 3 | BRF_GRA },
	{ "uec.15m",      0x200000, 0x2807df41, 3 | BRF_GRA },
	{ "uec.17m",      0x200000, 0x8a708d02, 3 | BRF_GRA },
	{ "uec.19m",      0x200000, 0xde7be0ef, 3 | BRF_GRA },
	{ "uec.14m",      0x100000, 0x1a003558, 3 | BRF_GRA },
	{ "uec.16m",      0x100000, 0x4ff8a6f9, 3 | BRF_GRA },
	{ "uec.18m",      0x100000, 0xb167ae12, 3 | BRF_GRA },
	{ "uec.20m",      0x100000, 0x1064bdc2, 3 | BRF_GRA },

	{ "uec.01",       0x020000, 0xc235bd15, 4 | BRF_ESS | BRF_PRG },

	{ "uec.11m",      0x200000, 0x81b25d39, 5 | BRF_SND },
	{ "uec.12m",      0x200000, 0x27729e52, 5 | BRF_SND },
};


STD_ROM_PICK(Ecofghtr) STD_ROM_FN(Ecofghtr)

static struct BurnRomInfo EcofghtuRomDesc[] = {
	{ "uecu.03",       0x80000, 0x6792480c, 1 | BRF_ESS | BRF_PRG },
	{ "uecu.04",       0x80000, 0x95ce69d5, 1 | BRF_ESS | BRF_PRG },
	{ "uecu.05",       0x80000, 0x3a1e78ad, 1 | BRF_ESS | BRF_PRG },
	{ "uecu.06",       0x80000, 0xa3e2f3cc, 1 | BRF_ESS | BRF_PRG },

	{ "uec.13m",      0x200000, 0xdcaf1436, 3 | BRF_GRA },
	{ "uec.15m",      0x200000, 0x2807df41, 3 | BRF_GRA },
	{ "uec.17m",      0x200000, 0x8a708d02, 3 | BRF_GRA },
	{ "uec.19m",      0x200000, 0xde7be0ef, 3 | BRF_GRA },
	{ "uec.14m",      0x100000, 0x1a003558, 3 | BRF_GRA },
	{ "uec.16m",      0x100000, 0x4ff8a6f9, 3 | BRF_GRA },
	{ "uec.18m",      0x100000, 0xb167ae12, 3 | BRF_GRA },
	{ "uec.20m",      0x100000, 0x1064bdc2, 3 | BRF_GRA },

	{ "uec.01",       0x020000, 0xc235bd15, 4 | BRF_ESS | BRF_PRG },

	{ "uec.11m",      0x200000, 0x81b25d39, 5 | BRF_SND },
	{ "uec.12m",      0x200000, 0x27729e52, 5 | BRF_SND },
};


STD_ROM_PICK(Ecofghtu) STD_ROM_FN(Ecofghtu)

static struct BurnRomInfo UecologyRomDesc[] = {
	{ "uecj.03",       0x80000, 0x94c40a4c, 1 | BRF_ESS | BRF_PRG },
	{ "uecj.04",       0x80000, 0x8d6e3a09, 1 | BRF_ESS | BRF_PRG },
	{ "uecj.05",       0x80000, 0x8604ecd7, 1 | BRF_ESS | BRF_PRG },
	{ "uecj.06",       0x80000, 0xb7e1d31f, 1 | BRF_ESS | BRF_PRG },

	{ "uec.13m",      0x200000, 0xdcaf1436, 3 | BRF_GRA },
	{ "uec.15m",      0x200000, 0x2807df41, 3 | BRF_GRA },
	{ "uec.17m",      0x200000, 0x8a708d02, 3 | BRF_GRA },
	{ "uec.19m",      0x200000, 0xde7be0ef, 3 | BRF_GRA },
	{ "uec.14m",      0x100000, 0x1a003558, 3 | BRF_GRA },
	{ "uec.16m",      0x100000, 0x4ff8a6f9, 3 | BRF_GRA },
	{ "uec.18m",      0x100000, 0xb167ae12, 3 | BRF_GRA },
	{ "uec.20m",      0x100000, 0x1064bdc2, 3 | BRF_GRA },

	{ "uec.01",       0x020000, 0xc235bd15, 4 | BRF_ESS | BRF_PRG },

	{ "uec.11m",      0x200000, 0x81b25d39, 5 | BRF_SND },
	{ "uec.12m",      0x200000, 0x27729e52, 5 | BRF_SND },
};


STD_ROM_PICK(Uecology) STD_ROM_FN(Uecology)

static struct BurnRomInfo EcofghtaRomDesc[] = {
	{ "ueca.03",       0x80000, 0xbd4589b1, 1 | BRF_ESS | BRF_PRG },
	{ "ueca.04",       0x80000, 0x1d134b7d, 1 | BRF_ESS | BRF_PRG },
	{ "ueca.05",       0x80000, 0x9c581fc7, 1 | BRF_ESS | BRF_PRG },
	{ "ueca.06",       0x80000, 0xc92a7c50, 1 | BRF_ESS | BRF_PRG },

	{ "uec.13m",      0x200000, 0xdcaf1436, 3 | BRF_GRA },
	{ "uec.15m",      0x200000, 0x2807df41, 3 | BRF_GRA },
	{ "uec.17m",      0x200000, 0x8a708d02, 3 | BRF_GRA },
	{ "uec.19m",      0x200000, 0xde7be0ef, 3 | BRF_GRA },
	{ "uec.14m",      0x100000, 0x1a003558, 3 | BRF_GRA },
	{ "uec.16m",      0x100000, 0x4ff8a6f9, 3 | BRF_GRA },
	{ "uec.18m",      0x100000, 0xb167ae12, 3 | BRF_GRA },
	{ "uec.20m",      0x100000, 0x1064bdc2, 3 | BRF_GRA },

	{ "uec.01",       0x020000, 0xc235bd15, 4 | BRF_ESS | BRF_PRG },

	{ "uec.11m",      0x200000, 0x81b25d39, 5 | BRF_SND },
	{ "uec.12m",      0x200000, 0x27729e52, 5 | BRF_SND },
};


STD_ROM_PICK(Ecofghta) STD_ROM_FN(Ecofghta)

struct BurnDriver BurnDrvCpsEcofghtr = {
	"ecofghtr", NULL, NULL, "1993",
	"Eco Fighters (931203 etc)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS2,
	NULL, EcofghtrRomInfo, EcofghtrRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsEcofghtu = {
	"ecofghtu", "ecofghtr", NULL, "1993",
	"Eco Fighters (931203 USA)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, EcofghtuRomInfo, EcofghtuRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsUecology = {
	"uecology", "ecofghtr", NULL, "1993",
	"Ultimate Ecology (931203 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, UecologyRomInfo, UecologyRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsEcofghta = {
	"ecofghta", "ecofghtr", NULL, "1993",
	"Eco Fighters (931203 Asia)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, EcofghtaRomInfo, EcofghtaRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
