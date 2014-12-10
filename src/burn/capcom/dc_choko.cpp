#include "cps.h"

static struct BurnInputInfo DrvInputList[] =
{
	{"P1 Coin"       , BIT_DIGITAL, CpsInp020+4, "p1 coin"},
	{"P1 Start"      , BIT_DIGITAL, CpsInp020+0, "p1 start"},
	{"P1 Up"         , BIT_DIGITAL, CpsInp001+3, "p1 up"},
	{"P1 Down"       , BIT_DIGITAL, CpsInp001+2, "p1 down"},
	{"P1 Left"       , BIT_DIGITAL, CpsInp001+1, "p1 left"},
	{"P1 Right"      , BIT_DIGITAL, CpsInp001+0, "p1 right"},
	{"P1 Shot1"      , BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},
	{"P1 Shot2"      , BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},
	{"P1 Shot3"      , BIT_DIGITAL, CpsInp001+6, "p1 fire 3"},

	{"P2 Coin"       , BIT_DIGITAL, CpsInp020+5, "p2 coin"},

	{"Reset"         , BIT_DIGITAL, &CpsReset  , "reset"},
	{"Diagnostic"    , BIT_DIGITAL, CpsInp021+1, "diag"},
	{"Service"       , BIT_DIGITAL, CpsInp021+2, "service"},
};

STDINPUTINFO(Drv);

static struct BurnRomInfo chokoRomDesc[] = {
	{ "tkoj.03",       0x080000, 0x11f5452f,  1 | BRF_ESS | BRF_PRG },
	{ "tkoj.04",       0x080000, 0x68655378,  1 | BRF_ESS | BRF_PRG },

	{ "tkoj1_d.simm1", 0x200000, 0x6933377d, 11 | BRF_GRA },
	{ "tkoj1_c.simm1", 0x200000, 0x7f668950, 11 | BRF_GRA },
	{ "tkoj1_b.simm1", 0x200000, 0xcfb68ca9, 11 | BRF_GRA },
	{ "tkoj1_a.simm1", 0x200000, 0x437e21c5, 11 | BRF_GRA },
	{ "tkoj3_d.simm3", 0x200000, 0xa9e32b57, 11 | BRF_GRA },
	{ "tkoj3_c.simm3", 0x200000, 0xb7ab9338, 11 | BRF_GRA },
	{ "tkoj3_b.simm3", 0x200000, 0x4d3f919a, 11 | BRF_GRA },
	{ "tkoj3_a.simm3", 0x200000, 0xcfef17ab, 11 | BRF_GRA },
	
	{ "tko.01",        0x020000, 0x6eda50c2,  4 | BRF_ESS | BRF_PRG },

	{ "tkoj5_a.simm5", 0x200000, 0xab45d509, 15 | BRF_SND },	
	{ "tkoj5_b.simm5", 0x200000, 0xfa905c3d, 15 | BRF_SND },	
};


STD_ROM_PICK(choko) STD_ROM_FN(choko)

struct BurnDriver BurnDrvCpsChoko = {
	"choko", NULL, NULL, "2001",
	"Choko (010820 Japan)\0", NULL, "Mitchell", "CPS2",
	L"\u9577\u6C5F (Choko 010820 Japan)\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_CAPCOM_CPS2 | HARDWARE_CAPCOM_CPS2_SIMM,
	NULL, chokoRomInfo, chokoRomName, DrvInputInfo, NULL,
	Cps2Init,CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
