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

static struct BurnRomInfo Ssf2tRomDesc[] = {
	{ "sfxe.03c",      0x80000, 0x2fa1f396, 1 | BRF_ESS | BRF_PRG }, // 6, 68000 code (encrypted)
	{ "sfxe.04a",      0x80000, 0xd0bc29c6, 1 | BRF_ESS | BRF_PRG },
	{ "sfxe.05",       0x80000, 0x65222964, 1 | BRF_ESS | BRF_PRG },
	{ "sfxe.06a",      0x80000, 0x8fe9f531, 1 | BRF_ESS | BRF_PRG },
	{ "sfxe.07",       0x80000, 0x8a7d0cb6, 1 | BRF_ESS | BRF_PRG },
	{ "sfxe.08",       0x80000, 0x74c24062, 1 | BRF_ESS | BRF_PRG },
	{ "sfx.09",        0x80000, 0x642fae3f, 1 | BRF_ESS | BRF_PRG },

	{ "ssf.13m",      0x200000, 0xcf94d275, 3 | BRF_GRA },			 // 13
	{ "ssf.15m",      0x200000, 0x5eb703af, 3 | BRF_GRA },
	{ "ssf.17m",      0x200000, 0xffa60e0f, 3 | BRF_GRA },
	{ "ssf.19m",      0x200000, 0x34e825c5, 3 | BRF_GRA },
	{ "ssf.14m",      0x100000, 0xb7cc32e7, 3 | BRF_GRA },
	{ "ssf.16m",      0x100000, 0x8376ad18, 3 | BRF_GRA },
	{ "ssf.18m",      0x100000, 0xf5b1b336, 3 | BRF_GRA },
	{ "ssf.20m",      0x100000, 0x459d5c6b, 3 | BRF_GRA },
	{ "sfx.21m",      0x100000, 0xe32854af, 3 | BRF_GRA },
	{ "sfx.23m",      0x100000, 0x760f2927, 3 | BRF_GRA },
	{ "sfx.25m",      0x100000, 0x1ee90208, 3 | BRF_GRA },
	{ "sfx.27m",      0x100000, 0xf814400f, 3 | BRF_GRA },

	{ "sfx.01",       0x020000, 0xb47b8835, 4 | BRF_ESS | BRF_PRG }, // 25
	{ "sfx.02",       0x020000, 0x0022633f, 4 | BRF_ESS | BRF_PRG },

	{ "sfx.11m",      0x200000, 0x9bdbd476, 5 | BRF_SND },
	{ "sfx.12m",      0x200000, 0xa05e3aab, 5 | BRF_SND },
};


STD_ROM_PICK(Ssf2t) STD_ROM_FN(Ssf2t)

static struct BurnRomInfo Ssf2taRomDesc[] = {
	{ "sfxa.03c",      0x80000, 0x04b9ff34, 1 | BRF_ESS | BRF_PRG }, // 6, 68000 code (encrypted)
	{ "sfxa.04a",      0x80000, 0x16ea5f7a, 1 | BRF_ESS | BRF_PRG },
	{ "sfxa.05",       0x80000, 0x53d61f0c, 1 | BRF_ESS | BRF_PRG },
	{ "sfxa.06a",      0x80000, 0x066d09b5, 1 | BRF_ESS | BRF_PRG },
	{ "sfxa.07",       0x80000, 0xa428257b, 1 | BRF_ESS | BRF_PRG },
	{ "sfxa.08",       0x80000, 0x39be596c, 1 | BRF_ESS | BRF_PRG },
	{ "sfx.09",        0x80000, 0x642fae3f, 1 | BRF_ESS | BRF_PRG },

	{ "ssf.13m",      0x200000, 0xcf94d275, 3 | BRF_GRA },			 // 13
	{ "ssf.15m",      0x200000, 0x5eb703af, 3 | BRF_GRA },
	{ "ssf.17m",      0x200000, 0xffa60e0f, 3 | BRF_GRA },
	{ "ssf.19m",      0x200000, 0x34e825c5, 3 | BRF_GRA },
	{ "ssf.14m",      0x100000, 0xb7cc32e7, 3 | BRF_GRA },
	{ "ssf.16m",      0x100000, 0x8376ad18, 3 | BRF_GRA },
	{ "ssf.18m",      0x100000, 0xf5b1b336, 3 | BRF_GRA },
	{ "ssf.20m",      0x100000, 0x459d5c6b, 3 | BRF_GRA },
	{ "sfx.21m",      0x100000, 0xe32854af, 3 | BRF_GRA },
	{ "sfx.23m",      0x100000, 0x760f2927, 3 | BRF_GRA },
	{ "sfx.25m",      0x100000, 0x1ee90208, 3 | BRF_GRA },
	{ "sfx.27m",      0x100000, 0xf814400f, 3 | BRF_GRA },

	{ "sfx.01",       0x020000, 0xb47b8835, 4 | BRF_ESS | BRF_PRG }, // 25
	{ "sfx.02",       0x020000, 0x0022633f, 4 | BRF_ESS | BRF_PRG },

	{ "sfx.11m",      0x200000, 0x9bdbd476, 5 | BRF_SND },
	{ "sfx.12m",      0x200000, 0xa05e3aab, 5 | BRF_SND },
};


STD_ROM_PICK(Ssf2ta) STD_ROM_FN(Ssf2ta)

static struct BurnRomInfo Ssf2tuRomDesc[] = {
	{ "sfxu.03e",      0x80000, 0xd6ff689e, 1 | BRF_ESS | BRF_PRG }, // 6, 68000 code (encrypted)
	{ "sfxu.04a",      0x80000, 0x532b5ffd, 1 | BRF_ESS | BRF_PRG },
	{ "sfxu.05",       0x80000, 0xffa3c6de, 1 | BRF_ESS | BRF_PRG },
	{ "sfxu.06b",      0x80000, 0x83f9382b, 1 | BRF_ESS | BRF_PRG },
	{ "sfxu.07a",      0x80000, 0x6ab673e8, 1 | BRF_ESS | BRF_PRG },
	{ "sfxu.08",       0x80000, 0xb3c71810, 1 | BRF_ESS | BRF_PRG },
	{ "sfx.09",        0x80000, 0x642fae3f, 1 | BRF_ESS | BRF_PRG },

	{ "ssf.13m",      0x200000, 0xcf94d275, 3 | BRF_GRA },			 // 13
	{ "ssf.15m",      0x200000, 0x5eb703af, 3 | BRF_GRA },
	{ "ssf.17m",      0x200000, 0xffa60e0f, 3 | BRF_GRA },
	{ "ssf.19m",      0x200000, 0x34e825c5, 3 | BRF_GRA },
	{ "ssf.14m",      0x100000, 0xb7cc32e7, 3 | BRF_GRA },
	{ "ssf.16m",      0x100000, 0x8376ad18, 3 | BRF_GRA },
	{ "ssf.18m",      0x100000, 0xf5b1b336, 3 | BRF_GRA },
	{ "ssf.20m",      0x100000, 0x459d5c6b, 3 | BRF_GRA },
	{ "sfx.21m",      0x100000, 0xe32854af, 3 | BRF_GRA },
	{ "sfx.23m",      0x100000, 0x760f2927, 3 | BRF_GRA },
	{ "sfx.25m",      0x100000, 0x1ee90208, 3 | BRF_GRA },
	{ "sfx.27m",      0x100000, 0xf814400f, 3 | BRF_GRA },

	{ "sfx.01",       0x020000, 0xb47b8835, 4 | BRF_ESS | BRF_PRG }, // 25
	{ "sfx.02",       0x020000, 0x0022633f, 4 | BRF_ESS | BRF_PRG },

	{ "sfx.11m",      0x200000, 0x9bdbd476, 5 | BRF_SND },
	{ "sfx.12m",      0x200000, 0xa05e3aab, 5 | BRF_SND },
};


STD_ROM_PICK(Ssf2tu) STD_ROM_FN(Ssf2tu)

static struct BurnRomInfo Ssf2tur1RomDesc[] = {
	{ "sfxu.03c",      0x80000, 0x86e4a335, 1 | BRF_ESS | BRF_PRG }, // 6, 68000 code (encrypted)
	{ "sfxu.04a",      0x80000, 0x532b5ffd, 1 | BRF_ESS | BRF_PRG },
	{ "sfxu.05",       0x80000, 0xffa3c6de, 1 | BRF_ESS | BRF_PRG },
	{ "sfxu.06a",      0x80000, 0xe4c04c99, 1 | BRF_ESS | BRF_PRG },
	{ "sfxu.07",       0x80000, 0xd8199e41, 1 | BRF_ESS | BRF_PRG },
	{ "sfxu.08",       0x80000, 0xb3c71810, 1 | BRF_ESS | BRF_PRG },
	{ "sfx.09",        0x80000, 0x642fae3f, 1 | BRF_ESS | BRF_PRG },

	{ "ssf.13m",      0x200000, 0xcf94d275, 3 | BRF_GRA },			 // 13
	{ "ssf.15m",      0x200000, 0x5eb703af, 3 | BRF_GRA },
	{ "ssf.17m",      0x200000, 0xffa60e0f, 3 | BRF_GRA },
	{ "ssf.19m",      0x200000, 0x34e825c5, 3 | BRF_GRA },
	{ "ssf.14m",      0x100000, 0xb7cc32e7, 3 | BRF_GRA },
	{ "ssf.16m",      0x100000, 0x8376ad18, 3 | BRF_GRA },
	{ "ssf.18m",      0x100000, 0xf5b1b336, 3 | BRF_GRA },
	{ "ssf.20m",      0x100000, 0x459d5c6b, 3 | BRF_GRA },
	{ "sfx.21m",      0x100000, 0xe32854af, 3 | BRF_GRA },
	{ "sfx.23m",      0x100000, 0x760f2927, 3 | BRF_GRA },
	{ "sfx.25m",      0x100000, 0x1ee90208, 3 | BRF_GRA },
	{ "sfx.27m",      0x100000, 0xf814400f, 3 | BRF_GRA },

	{ "sfx.01",       0x020000, 0xb47b8835, 4 | BRF_ESS | BRF_PRG }, // 25
	{ "sfx.02",       0x020000, 0x0022633f, 4 | BRF_ESS | BRF_PRG },

	{ "sfx.11m",      0x200000, 0x9bdbd476, 5 | BRF_SND },
	{ "sfx.12m",      0x200000, 0xa05e3aab, 5 | BRF_SND },
};


STD_ROM_PICK(Ssf2tur1) STD_ROM_FN(Ssf2tur1)

static struct BurnRomInfo Ssf2xjRomDesc[] = {
	{ "sfxj.03c",      0x80000, 0xa7417b79, 1 | BRF_ESS | BRF_PRG }, // 6, 68000 code (encrypted)
	{ "sfxj.04a",      0x80000, 0xaf7767b4, 1 | BRF_ESS | BRF_PRG },
	{ "sfxj.05",       0x80000, 0xf4ff18f5, 1 | BRF_ESS | BRF_PRG },
	{ "sfxj.06a",      0x80000, 0x260d0370, 1 | BRF_ESS | BRF_PRG },
	{ "sfxj.07",       0x80000, 0x1324d02a, 1 | BRF_ESS | BRF_PRG },
	{ "sfxj.08",       0x80000, 0x2de76f10, 1 | BRF_ESS | BRF_PRG },
	{ "sfx.09",        0x80000, 0x642fae3f, 1 | BRF_ESS | BRF_PRG },

	{ "ssf.13m",      0x200000, 0xcf94d275, 3 | BRF_GRA },			 // 13
	{ "ssf.15m",      0x200000, 0x5eb703af, 3 | BRF_GRA },
	{ "ssf.17m",      0x200000, 0xffa60e0f, 3 | BRF_GRA },
	{ "ssf.19m",      0x200000, 0x34e825c5, 3 | BRF_GRA },
	{ "ssf.14m",      0x100000, 0xb7cc32e7, 3 | BRF_GRA },
	{ "ssf.16m",      0x100000, 0x8376ad18, 3 | BRF_GRA },
	{ "ssf.18m",      0x100000, 0xf5b1b336, 3 | BRF_GRA },
	{ "ssf.20m",      0x100000, 0x459d5c6b, 3 | BRF_GRA },
	{ "sfx.21m",      0x100000, 0xe32854af, 3 | BRF_GRA },
	{ "sfx.23m",      0x100000, 0x760f2927, 3 | BRF_GRA },
	{ "sfx.25m",      0x100000, 0x1ee90208, 3 | BRF_GRA },
	{ "sfx.27m",      0x100000, 0xf814400f, 3 | BRF_GRA },

	{ "sfx.01",       0x020000, 0xb47b8835, 4 | BRF_ESS | BRF_PRG }, // 25
	{ "sfx.02",       0x020000, 0x0022633f, 4 | BRF_ESS | BRF_PRG },

	{ "sfx.11m",      0x200000, 0x9bdbd476, 5 | BRF_SND },
	{ "sfx.12m",      0x200000, 0xa05e3aab, 5 | BRF_SND },
};


STD_ROM_PICK(Ssf2xj) STD_ROM_FN(Ssf2xj)

struct BurnDriver BurnDrvCpsSsf2t = {
	"ssf2t", "ssf2", NULL, "1994",
	"Super Street Fighter II Turbo (super street fighter 2 X 940223 etc)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS2,
	NULL, Ssf2tRomInfo, Ssf2tRomName, DrvInputInfo, NULL,
	DrvInit, DrvExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSsf2ta = {
	"ssf2ta", "ssf2t", NULL, "1994",
	"Super Street Fighter II Turbo (super street fighter 2 X 940223 Asia)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Ssf2taRomInfo, Ssf2taRomName, DrvInputInfo, NULL,
	DrvInit, DrvExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSsf2tu = {
	"ssf2tu", "ssf2t", NULL, "1994",
	"Super Street Fighter II Turbo (super street fighter 2 X 940323 USA)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Ssf2tuRomInfo, Ssf2tuRomName, DrvInputInfo, NULL,
	DrvInit, DrvExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSsf2tur1 = {
	"ssf2tur1", "ssf2t", NULL, "1994",
	"Super Street Fighter II Turbo (super street fighter 2 X 940223 USA)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Ssf2tur1RomInfo, Ssf2tur1RomName, DrvInputInfo, NULL,
	DrvInit, DrvExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSsf2xj = {
	"ssf2xj", "ssf2t", NULL, "1994",
	"Super Street Fighter II X - grand master challenge (super street fighter 2 X 940223 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Ssf2xjRomInfo, Ssf2xjRomName, DrvInputInfo, NULL,
	DrvInit, DrvExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
