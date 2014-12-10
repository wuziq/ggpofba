#include "cps.h"

#define A(a, b, c, d) {a, b, (unsigned char*)(c), d}

static struct BurnInputInfo DrvInputList[] =
{
	{"P1 Coin"       , BIT_DIGITAL, CpsInp020+4, "p1 coin"},
	{"P1 Start"      , BIT_DIGITAL, CpsInp020+0, "p1 start"},
	{"P1 Up"         , BIT_DIGITAL, CpsInp001+3, "p1 up"},
	{"P1 Down"       , BIT_DIGITAL, CpsInp001+2, "p1 down"},
	{"P1 Left"       , BIT_DIGITAL, CpsInp001+1, "p1 left"},
	{"P1 Right"      , BIT_DIGITAL, CpsInp001+0, "p1 right"},
	{"P1 Shot"       , BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},
	A("P1 Paddle"    , BIT_ANALOG_REL, &CpsInpPaddle1, "mouse x-axis"),

	{"P2 Coin"       , BIT_DIGITAL, CpsInp020+5, "p2 coin"},
	{"P2 Start"      , BIT_DIGITAL, CpsInp020+1, "p2 start"},
	{"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"},
	{"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"},
	{"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"},
	{"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right"},
	{"P2 Shot"       , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
	A("P2 Paddle"    , BIT_ANALOG_REL, &CpsInpPaddle2, "p2 z-axis"),

	{"Reset"         , BIT_DIGITAL, &CpsReset  , "reset"},
	{"Diagnostic"    , BIT_DIGITAL, CpsInp021+1, "diag"},
	{"Service"       , BIT_DIGITAL, CpsInp021+2, "service"},
};

#undef A

STDINPUTINFO(Drv);

static int DrvInit()
{
	Pzloop2 = 1;
	
	if (Cps2Init()) {
		return 1;
	}

	return 0;
}

static int DrvExit()
{
	Pzloop2 = 0;

	return CpsExit();
}

static struct BurnRomInfo pzloop2RomDesc[] = {
	{ "pl2e.03",      0x080000, 0x3b1285b2,  1 | BRF_ESS | BRF_PRG },
	{ "pl2e.04",      0x080000, 0x40a2d647,  1 | BRF_ESS | BRF_PRG },
	{ "pl2e.05",      0x080000, 0x0f11d818,  1 | BRF_ESS | BRF_PRG },
	{ "pl2e.06",      0x080000, 0x86fbbdf4,  1 | BRF_ESS | BRF_PRG },

	{ "pl2-simm.01c", 0x200000, 0x137b13a7, 11 | BRF_GRA },
	{ "pl2-simm.01d", 0x200000, 0xa2db1507, 11 | BRF_GRA },
	{ "pl2-simm.01a", 0x200000, 0x7e80ff8e, 11 | BRF_GRA },
	{ "pl2-simm.01b", 0x200000, 0xcd93e6ed, 11 | BRF_GRA },
	{ "pl2-simm.03c", 0x200000, 0x0f52bbca, 11 | BRF_GRA },
	{ "pl2-simm.03d", 0x200000, 0xa62712c3, 11 | BRF_GRA },
	{ "pl2-simm.03a", 0x200000, 0xb60c9f8e, 11 | BRF_GRA },
	{ "pl2-simm.03b", 0x200000, 0x83fef284, 11 | BRF_GRA },

	{ "pl2.01",       0x020000, 0x35697569,  4 | BRF_ESS | BRF_PRG },

	{ "pl2-simm.05a", 0x200000, 0x85d8fbe8, 13 | BRF_SND },
	{ "pl2-simm.05b", 0x200000, 0x1ed62584, 13 | BRF_SND },
};


STD_ROM_PICK(pzloop2) STD_ROM_FN(pzloop2)

static struct BurnRomInfo pzloop2jRomDesc[] = {
	{ "pl2j.03a",     0x080000, 0x0a751bd0,  1 | BRF_ESS | BRF_PRG },
	{ "pl2j.04a",     0x080000, 0xc3f72afe,  1 | BRF_ESS | BRF_PRG },
	{ "pl2j.05a",     0x080000, 0x6ea9dbfc,  1 | BRF_ESS | BRF_PRG },
	{ "pl2j.06a",     0x080000, 0x0f14848d,  1 | BRF_ESS | BRF_PRG },

	{ "pl2-simm.01c", 0x200000, 0x137b13a7, 11 | BRF_GRA },
	{ "pl2-simm.01d", 0x200000, 0xa2db1507, 11 | BRF_GRA },
	{ "pl2-simm.01a", 0x200000, 0x7e80ff8e, 11 | BRF_GRA },
	{ "pl2-simm.01b", 0x200000, 0xcd93e6ed, 11 | BRF_GRA },
	{ "pl2-simm.03c", 0x200000, 0x0f52bbca, 11 | BRF_GRA },
	{ "pl2-simm.03d", 0x200000, 0xa62712c3, 11 | BRF_GRA },
	{ "pl2-simm.03a", 0x200000, 0xb60c9f8e, 11 | BRF_GRA },
	{ "pl2-simm.03b", 0x200000, 0x83fef284, 11 | BRF_GRA },

	{ "pl2.01",       0x020000, 0x35697569,  4 | BRF_ESS | BRF_PRG },

	{ "pl2-simm.05a", 0x200000, 0x85d8fbe8, 13 | BRF_SND },
	{ "pl2-simm.05b", 0x200000, 0x1ed62584, 13 | BRF_SND },
};


STD_ROM_PICK(pzloop2j) STD_ROM_FN(pzloop2j)

struct BurnDriver BurnDrvCpsPzloop2 = {
	"pzloop2", NULL, NULL, "2001",
	"Puzz Loop 2 (010302 Euro)\0", NULL, "Mitchell, distritued by Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_CAPCOM_CPS2 | HARDWARE_CAPCOM_CPS2_SIMM,
	NULL, pzloop2RomInfo, pzloop2RomName, DrvInputInfo, NULL,
	DrvInit,DrvExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsPzloop2j = {
	"pzloop2j", "pzloop2", NULL, "2001",
	"Puzz Loop 2 (010205 Japan)\0", NULL, "Mitchell, distritued by Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_CAPCOM_CPS2 | HARDWARE_CAPCOM_CPS2_SIMM,
	NULL, pzloop2jRomInfo, pzloop2jRomName, DrvInputInfo, NULL,
	DrvInit,DrvExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
