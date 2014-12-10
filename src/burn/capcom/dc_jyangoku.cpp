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

	{"Reset"         , BIT_DIGITAL, &CpsReset  , "reset"},
	{"Diagnostic"    , BIT_DIGITAL, CpsInp021+1, "diag"},
	{"Service"       , BIT_DIGITAL, CpsInp021+2, "service"},
};

STDINPUTINFO(Drv);

static struct BurnRomInfo jyangokuRomDesc[] = {
	{ "maj_j03.6a",   0x080000, 0x4614a3b2,  1 | BRF_ESS | BRF_PRG },

	{ "maj1_d.simm1", 0x200000, 0xba0fe27b, 11 | BRF_GRA },
	{ "maj1_c.simm1", 0x200000, 0x2cd141bf, 11 | BRF_GRA },
	{ "maj1_b.simm1", 0x200000, 0xe29e4c26, 11 | BRF_GRA },
	{ "maj1_a.simm1", 0x200000, 0x7f68b88a, 11 | BRF_GRA },
	{ "maj3_d.simm3", 0x200000, 0x3aaeb90b, 11 | BRF_GRA },
	{ "maj3_c.simm3", 0x200000, 0x97894cea, 11 | BRF_GRA },
	{ "maj3_b.simm3", 0x200000, 0xec737d9d, 11 | BRF_GRA },
	{ "maj3_a.simm3", 0x200000, 0xc23b6f22, 11 | BRF_GRA },
	
	{ "maj_01.1a",    0x020000, 0x1fe8c213,  4 | BRF_ESS | BRF_PRG },

	{ "maj5_a.simm5", 0x200000, 0x5ad9ee53, 15 | BRF_SND },	
	{ "maj5_b.simm5", 0x200000, 0xefb3dbfb, 15 | BRF_SND },	
};


STD_ROM_PICK(jyangoku) STD_ROM_FN(jyangoku)

struct BurnDriver BurnDrvCpsJyangoku = {
	"jyangoku", NULL, NULL, "1999",
	"Jyangokushi  -Haoh no Saihai- (990527 Japan)\0", NULL, "Mitchell", "CPS2",
	L"\u96C0\u570B\u5FD7 -\u8987\u738B\u306E\u91C7\u724C- (Jyangokushi 990527 Japan)\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_CAPCOM_CPS2 | HARDWARE_CAPCOM_CPS2_SIMM,
	NULL, jyangokuRomInfo, jyangokuRomName, DrvInputInfo, NULL,
	Cps2Init,CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
