#include "cps.h"

STDINPUTINFOSPEC(Drv, CpsFsi);

static struct BurnRomInfo Vsav2RomDesc[] = {
	{ "vs2j.03",       0x80000, 0x89fd86b4, 1 | BRF_ESS | BRF_PRG },
	{ "vs2j.04",       0x80000, 0x107c091b, 1 | BRF_ESS | BRF_PRG },
	{ "vs2j.05",       0x80000, 0x61979638, 1 | BRF_ESS | BRF_PRG },
	{ "vs2j.06",       0x80000, 0xf37c5bc2, 1 | BRF_ESS | BRF_PRG },
	{ "vs2j.07",       0x80000, 0x8f885809, 1 | BRF_ESS | BRF_PRG },
	{ "vs2j.08",       0x80000, 0x2018c120, 1 | BRF_ESS | BRF_PRG },
	{ "vs2j.09",       0x80000, 0xfac3c217, 1 | BRF_ESS | BRF_PRG },
	{ "vs2j.10",       0x80000, 0xeb490213, 1 | BRF_ESS | BRF_PRG },

	{ "vs2.13m",      0x400000, 0x5c852f52, 3 | BRF_GRA },
	{ "vs2.15m",      0x400000, 0xa20f58af, 3 | BRF_GRA },
	{ "vs2.17m",      0x400000, 0x39db59ad, 3 | BRF_GRA },
	{ "vs2.19m",      0x400000, 0x00c763a7, 3 | BRF_GRA },
	{ "vs2.14m",      0x400000, 0xcd09bd63, 3 | BRF_GRA },
	{ "vs2.16m",      0x400000, 0xe0182c15, 3 | BRF_GRA },
	{ "vs2.18m",      0x400000, 0x778dc4f6, 3 | BRF_GRA },
	{ "vs2.20m",      0x400000, 0x605d9d1d, 3 | BRF_GRA },

	{ "vs2.01",       0x020000, 0x35190139, 4 | BRF_ESS | BRF_PRG },
	{ "vs2.02",       0x020000, 0xc32dba09, 4 | BRF_ESS | BRF_PRG },

	{ "vs2.11m",      0x400000, 0xd67e47b7, 5 | BRF_SND },
	{ "vs2.12m",      0x400000, 0x6d020a14, 5 | BRF_SND },
};


STD_ROM_PICK(Vsav2) STD_ROM_FN(Vsav2)

struct BurnDriver BurnDrvCpsVsav2 = {
	"vsav2", NULL, NULL, "1997",
	"Vampire Savior 2 - the lord of vampire (970913 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS2,
	NULL, Vsav2RomInfo, Vsav2RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
