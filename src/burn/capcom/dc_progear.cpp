#include "cps.h"

static struct BurnInputInfo DrvInputList[] =
{
	{"P1 Coin"       , BIT_DIGITAL, CpsInp020+4, "p1 coin"},
	{"P1 Start"      , BIT_DIGITAL, CpsInp020+0, "p1 start"},
	{"P1 Up"         , BIT_DIGITAL, CpsInp001+3, "p1 up"},
	{"P1 Down"       , BIT_DIGITAL, CpsInp001+2, "p1 down"},
	{"P1 Left"       , BIT_DIGITAL, CpsInp001+1, "p1 left"},
	{"P1 Right"      , BIT_DIGITAL, CpsInp001+0, "p1 right"},
	{"P1 Shot"       , BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},
	{"P1 Bomb"       , BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},
	{"P1 Auto"       , BIT_DIGITAL, CpsInp001+6, "p1 fire 3"},

	{"P2 Coin"       , BIT_DIGITAL, CpsInp020+5, "p2 coin"},
	{"P2 Start"      , BIT_DIGITAL, CpsInp020+1, "p2 start"},
	{"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"},
	{"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"},
	{"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"},
	{"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right"},
	{"P2 Shot"       , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
	{"P2 Bomb"       , BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},
	{"P2 Auto"       , BIT_DIGITAL, CpsInp000+6, "p2 fire 3"},

	{"Reset"         , BIT_DIGITAL, &CpsReset  , "reset"},
	{"Diagnostic"    , BIT_DIGITAL, CpsInp021+1, "diag"},
	{"Service"       , BIT_DIGITAL, CpsInp021+2, "service"},
};

STDINPUTINFO(Drv);

static struct BurnRomInfo progearRomDesc[] = {
	{ "pgau.03",      0x080000, 0x343A783E,  1 | BRF_ESS | BRF_PRG },
	{ "pgau.04",      0x080000, 0x16208D79,  1 | BRF_ESS | BRF_PRG },

	{ "pga-simm.01c",  0x200000, 0x452F98B0, 11 | BRF_GRA },
	{ "pga-simm.01d",  0x200000, 0x9E672092, 11 | BRF_GRA },
	{ "pga-simm.01a",  0x200000, 0xAE9DDAFE, 11 | BRF_GRA },
	{ "pga-simm.01b",  0x200000, 0x94D72D94, 11 | BRF_GRA },
	{ "pga-simm.03c",  0x200000, 0x48A1886D, 11 | BRF_GRA },
	{ "pga-simm.03d",  0x200000, 0x172D7E37, 11 | BRF_GRA },
	{ "pga-simm.03a",  0x200000, 0x9EE33D98, 11 | BRF_GRA },
	{ "pga-simm.03b",  0x200000, 0x848DEE32, 11 | BRF_GRA },

	{ "pga.01",       0x020000, 0xBDBFA992,  4 | BRF_ESS | BRF_PRG },

	{ "pga-simm.05a",  0x200000, 0xC0AAC80C, 13 | BRF_SND },
	{ "pga-simm.05b",  0x200000, 0x37A65D86, 13 | BRF_SND },
	{ "pga-simm.06a",  0x200000, 0xD3F1E934, 13 | BRF_SND },
	{ "pga-simm.06b",  0x200000, 0x8B39489A, 13 | BRF_SND },
};


STD_ROM_PICK(progear) STD_ROM_FN(progear)

static struct BurnRomInfo progearjRomDesc[] = {
	{ "pgaj.03",      0x080000, 0x06DBBA54,  1 | BRF_ESS | BRF_PRG },
	{ "pgaj.04",      0x080000, 0xA1F1F1BC,  1 | BRF_ESS | BRF_PRG },

	{ "pga-simm.01c", 0x200000, 0x452F98B0, 11 | BRF_GRA },
	{ "pga-simm.01d", 0x200000, 0x9E672092, 11 | BRF_GRA },
	{ "pga-simm.01a", 0x200000, 0xAE9DDAFE, 11 | BRF_GRA },
	{ "pga-simm.01b", 0x200000, 0x94D72D94, 11 | BRF_GRA },
	{ "pga-simm.03c", 0x200000, 0x48A1886D, 11 | BRF_GRA },
	{ "pga-simm.03d", 0x200000, 0x172D7E37, 11 | BRF_GRA },
	{ "pga-simm.03a", 0x200000, 0x9EE33D98, 11 | BRF_GRA },
	{ "pga-simm.03b", 0x200000, 0x848DEE32, 11 | BRF_GRA },

	{ "pga.01",       0x020000, 0xBDBFA992,  4 | BRF_ESS | BRF_PRG },

	{ "pga-simm.05a", 0x200000, 0xC0AAC80C, 13 | BRF_SND },
	{ "pga-simm.05b", 0x200000, 0x37A65D86, 13 | BRF_SND },
	{ "pga-simm.06a", 0x200000, 0xD3F1E934, 13 | BRF_SND },
	{ "pga-simm.06b", 0x200000, 0x8B39489A, 13 | BRF_SND },
};


STD_ROM_PICK(progearj) STD_ROM_FN(progearj)

static struct BurnRomInfo progearaRomDesc[] = {
	{ "pgaa.03",      0x080000, 0x25E6E2CE,  1 | BRF_ESS | BRF_PRG },
	{ "pgaa.04",      0x080000, 0x8104307E,  1 | BRF_ESS | BRF_PRG },

	{ "pga-simm.01c", 0x200000, 0x452F98B0, 11 | BRF_GRA },
	{ "pga-simm.01d", 0x200000, 0x9E672092, 11 | BRF_GRA },
	{ "pga-simm.01a", 0x200000, 0xAE9DDAFE, 11 | BRF_GRA },
	{ "pga-simm.01b", 0x200000, 0x94D72D94, 11 | BRF_GRA },
	{ "pga-simm.03c", 0x200000, 0x48A1886D, 11 | BRF_GRA },
	{ "pga-simm.03d", 0x200000, 0x172D7E37, 11 | BRF_GRA },
	{ "pga-simm.03a", 0x200000, 0x9EE33D98, 11 | BRF_GRA },
	{ "pga-simm.03b", 0x200000, 0x848DEE32, 11 | BRF_GRA },

	{ "pga.01",       0x020000, 0xBDBFA992,  4 | BRF_ESS | BRF_PRG },

	{ "pga-simm.05a", 0x200000, 0xC0AAC80C, 13 | BRF_SND },
	{ "pga-simm.05b", 0x200000, 0x37A65D86, 13 | BRF_SND },
	{ "pga-simm.06a", 0x200000, 0xD3F1E934, 13 | BRF_SND },
	{ "pga-simm.06b", 0x200000, 0x8B39489A, 13 | BRF_SND },
};


STD_ROM_PICK(progeara) STD_ROM_FN(progeara)

struct BurnDriver BurnDrvCpsProgear = {
	"progear", NULL, NULL, "2001",
	"Progear (010117 USA)\0", NULL, "Capcom / Cave", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_CAPCOM_CPS2 | HARDWARE_CAPCOM_CPS2_SIMM,
	NULL, progearRomInfo, progearRomName, DrvInputInfo, NULL,
	Cps2Init,CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsProgearj = {
	"progearj", "progear", NULL, "2001",
	"Progear No Arashi (010117 Japan)\0", NULL, "Capcom / Cave", "CPS2",
	L"\u30D7\u30ED\u30AE\u30A2\u306E\u5D50 (Progear No Arashi 010117 Japan)\0", NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_CAPCOM_CPS2 | HARDWARE_CAPCOM_CPS2_SIMM,
	NULL, progearjRomInfo, progearjRomName, DrvInputInfo, NULL,
	Cps2Init,CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsProgeara = {
	"progeara", "progear", NULL, "2001",
	"Progear (010117 Asia)\0", NULL, "Capcom / Cave", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_CAPCOM_CPS2 | HARDWARE_CAPCOM_CPS2_SIMM,
	NULL, progearaRomInfo, progearaRomName, DrvInputInfo, NULL,
	Cps2Init,CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
