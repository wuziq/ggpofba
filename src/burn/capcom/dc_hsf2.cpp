#include "cps.h"

STDINPUTINFOSPEC(Drv, CpsFsi);

static int DrvInit()
{
	Ssf2t = 1;
	
	if (Cps2Init()) {
		return 1;
	}

	nCpsGfxScroll[3] = 0;

	return 0;
}

static int DrvExit()
{
	Ssf2t = 0;

	return CpsExit();
}

static struct BurnRomInfo hsf2RomDesc[] = {
	{ "hs2a.03",     0x080000, 0xd50a17e0, 1 | BRF_ESS | BRF_PRG },
	{ "hs2a.04",     0x080000, 0xa27f42de, 1 | BRF_ESS | BRF_PRG },
	{ "hs2.05",      0x080000, 0xdde34a35, 1 | BRF_ESS | BRF_PRG },
	{ "hs2.06",      0x080000, 0xf4e56dda, 1 | BRF_ESS | BRF_PRG },
	{ "hs2a.07",     0x080000, 0xee4420fc, 1 | BRF_ESS | BRF_PRG },
	{ "hs2.08",      0x080000, 0xc9441533, 1 | BRF_ESS | BRF_PRG },
	{ "hs2.09",      0x080000, 0x3fc638a8, 1 | BRF_ESS | BRF_PRG },
	{ "hs2.10",      0x080000, 0x20d0f9e4, 1 | BRF_ESS | BRF_PRG },

	{ "hs2.13m",     0x800000, 0xa6ecab17, 3 | BRF_GRA },
	{ "hs2.15m",     0x800000, 0x10a0ae4d, 3 | BRF_GRA },
	{ "hs2.17m",     0x800000, 0xadfa7726, 3 | BRF_GRA },
	{ "hs2.19m",     0x800000, 0xbb3ae322, 3 | BRF_GRA },

	{ "hs2.01",      0x020000, 0xc1a13786, 4 | BRF_ESS | BRF_PRG },
	{ "hs2.02",      0x020000, 0x2d8794aa, 4 | BRF_ESS | BRF_PRG },

	{ "hs2.11m",     0x800000, 0x0e15c359, 5 | BRF_SND },
};


STD_ROM_PICK(hsf2) STD_ROM_FN(hsf2)

static struct BurnRomInfo hsf2jRomDesc[] = {
	{ "hs2j.03",     0x080000, 0x00738f73, 1 | BRF_ESS | BRF_PRG },
	{ "hs2j.04",     0x080000, 0x40072c4a, 1 | BRF_ESS | BRF_PRG },
	{ "hs2.05",      0x080000, 0xdde34a35, 1 | BRF_ESS | BRF_PRG },
	{ "hs2.06",      0x080000, 0xf4e56dda, 1 | BRF_ESS | BRF_PRG },
	{ "hs2j.07",     0x080000, 0x09fe85b4, 1 | BRF_ESS | BRF_PRG },
	{ "hs2.08",      0x080000, 0xc9441533, 1 | BRF_ESS | BRF_PRG },
	{ "hs2.09",      0x080000, 0x3fc638a8, 1 | BRF_ESS | BRF_PRG },
	{ "hs2.10",      0x080000, 0x20d0f9e4, 1 | BRF_ESS | BRF_PRG },

	{ "hs2.13m" ,    0x800000, 0xa6ecab17, 3 | BRF_GRA },
	{ "hs2.15m",     0x800000, 0x10a0ae4d, 3 | BRF_GRA },
	{ "hs2.17m",     0x800000, 0xadfa7726, 3 | BRF_GRA },
	{ "hs2.19m",     0x800000, 0xbb3ae322, 3 | BRF_GRA },

	{ "hs2.01",      0x020000, 0xc1a13786, 4 | BRF_ESS | BRF_PRG },
	{ "hs2.02",      0x020000, 0x2d8794aa, 4 | BRF_ESS | BRF_PRG },

	{ "hs2.11m",     0x800000, 0x0e15c359, 5 | BRF_SND },
};


STD_ROM_PICK(hsf2j) STD_ROM_FN(hsf2j)

struct BurnDriver BurnDrvCpsHsf2 = {
	"hsf2", NULL, NULL, "2004",
	"Hyper Street Fighter 2: The Anniversary Edition (040202 Asia)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS2,
	NULL, hsf2RomInfo, hsf2RomName, DrvInputInfo, NULL,
	DrvInit, DrvExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsHsf2j = {
	"hsf2j", "hsf2", NULL, "2004",
	"Hyper Street Fighter 2: The Anniversary Edition (031222 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, hsf2jRomInfo, hsf2jRomName, DrvInputInfo, NULL,
	DrvInit, DrvExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
