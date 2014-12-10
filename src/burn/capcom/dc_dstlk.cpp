#include "cps.h"

STDINPUTINFOSPEC(Drv, CpsFsi);

static struct BurnRomInfo DstlkRomDesc[] = {
	{ "vame.03a",      0x80000, 0x004c9cff, 1 | BRF_ESS | BRF_PRG },
	{ "vame.04a",      0x80000, 0xae413ff2, 1 | BRF_ESS | BRF_PRG },
	{ "vame.05a",      0x80000, 0x60678756, 1 | BRF_ESS | BRF_PRG },
	{ "vame.06a",      0x80000, 0x912870b3, 1 | BRF_ESS | BRF_PRG },
	{ "vame.07a",      0x80000, 0xdabae3e8, 1 | BRF_ESS | BRF_PRG },
	{ "vame.08a",      0x80000, 0x2c6e3077, 1 | BRF_ESS | BRF_PRG },
	{ "vame.09a",      0x80000, 0xf16db74b, 1 | BRF_ESS | BRF_PRG },
	{ "vame.10a",      0x80000, 0x701e2147, 1 | BRF_ESS | BRF_PRG },

	{ "vam.13m",      0x400000, 0xc51baf99, 3 | BRF_GRA },
	{ "vam.15m",      0x400000, 0x3ce83c77, 3 | BRF_GRA },
	{ "vam.17m",      0x400000, 0x4f2408e0, 3 | BRF_GRA },
	{ "vam.19m",      0x400000, 0x9ff60250, 3 | BRF_GRA },
	{ "vam.14m",      0x100000, 0xbd87243c, 3 | BRF_GRA },
	{ "vam.16m",      0x100000, 0xafec855f, 3 | BRF_GRA },
	{ "vam.18m",      0x100000, 0x3a033625, 3 | BRF_GRA },
	{ "vam.20m",      0x100000, 0x2bff6a89, 3 | BRF_GRA },

	{ "vam.01",       0x020000, 0x64b685d5, 4 | BRF_ESS | BRF_PRG },
	{ "vam.02",       0x020000, 0xcf7c97c7, 4 | BRF_ESS | BRF_PRG },

	{ "vam.11m",      0x200000, 0x4a39deb2, 5 | BRF_SND },
	{ "vam.12m",      0x200000, 0x1a3e5c03, 5 | BRF_SND },

};


STD_ROM_PICK(Dstlk) STD_ROM_FN(Dstlk)

static struct BurnRomInfo DstlkuRomDesc[] = {
	{ "vamu.03b",      0x80000, 0x68a6343f, 1 | BRF_ESS | BRF_PRG },
	{ "vamu.04b",      0x80000, 0x58161453, 1 | BRF_ESS | BRF_PRG },
	{ "vamu.05b",      0x80000, 0xdfc038b8, 1 | BRF_ESS | BRF_PRG },
	{ "vamu.06b",      0x80000, 0xc3842c89, 1 | BRF_ESS | BRF_PRG },
	{ "vamu.07b",      0x80000, 0x25b60b6e, 1 | BRF_ESS | BRF_PRG },
	{ "vamu.08b",      0x80000, 0x2113c596, 1 | BRF_ESS | BRF_PRG },
	{ "vamu.09b",      0x80000, 0x2d1e9ae5, 1 | BRF_ESS | BRF_PRG },
	{ "vamu.10b",      0x80000, 0x81145622, 1 | BRF_ESS | BRF_PRG },

	{ "vam.13m",      0x400000, 0xc51baf99, 3 | BRF_GRA },
	{ "vam.15m",      0x400000, 0x3ce83c77, 3 | BRF_GRA },
	{ "vam.17m",      0x400000, 0x4f2408e0, 3 | BRF_GRA },
	{ "vam.19m",      0x400000, 0x9ff60250, 3 | BRF_GRA },
	{ "vam.14m",      0x100000, 0xbd87243c, 3 | BRF_GRA },
	{ "vam.16m",      0x100000, 0xafec855f, 3 | BRF_GRA },
	{ "vam.18m",      0x100000, 0x3a033625, 3 | BRF_GRA },
	{ "vam.20m",      0x100000, 0x2bff6a89, 3 | BRF_GRA },

	{ "vam.01",       0x020000, 0x64b685d5, 4 | BRF_ESS | BRF_PRG },
	{ "vam.02",       0x020000, 0xcf7c97c7, 4 | BRF_ESS | BRF_PRG },

	{ "vam.11m",      0x200000, 0x4a39deb2, 5 | BRF_SND },
	{ "vam.12m",      0x200000, 0x1a3e5c03, 5 | BRF_SND },
};


STD_ROM_PICK(Dstlku) STD_ROM_FN(Dstlku)

static struct BurnRomInfo Dstlkur1RomDesc[] = {
	{ "vamu.03a",      0x80000, 0x628899f9, 1 | BRF_ESS | BRF_PRG },
	{ "vamu.04a",      0x80000, 0x696d9b25, 1 | BRF_ESS | BRF_PRG },
	{ "vamu.05a",      0x80000, 0x673ed50a, 1 | BRF_ESS | BRF_PRG },
	{ "vamu.06a",      0x80000, 0xf2377be7, 1 | BRF_ESS | BRF_PRG },
	{ "vamu.07a",      0x80000, 0xd8f498c4, 1 | BRF_ESS | BRF_PRG },
	{ "vamu.08a",      0x80000, 0xe6a8a1a0, 1 | BRF_ESS | BRF_PRG },
	{ "vamu.09a",      0x80000, 0x8dd55b24, 1 | BRF_ESS | BRF_PRG },
	{ "vamu.10a",      0x80000, 0xc1a3d9be, 1 | BRF_ESS | BRF_PRG },

	{ "vam.13m",      0x400000, 0xc51baf99, 3 | BRF_GRA },
	{ "vam.15m",      0x400000, 0x3ce83c77, 3 | BRF_GRA },
	{ "vam.17m",      0x400000, 0x4f2408e0, 3 | BRF_GRA },
	{ "vam.19m",      0x400000, 0x9ff60250, 3 | BRF_GRA },
	{ "vam.14m",      0x100000, 0xbd87243c, 3 | BRF_GRA },
	{ "vam.16m",      0x100000, 0xafec855f, 3 | BRF_GRA },
	{ "vam.18m",      0x100000, 0x3a033625, 3 | BRF_GRA },
	{ "vam.20m",      0x100000, 0x2bff6a89, 3 | BRF_GRA },

	{ "vam.01",       0x020000, 0x64b685d5, 4 | BRF_ESS | BRF_PRG },
	{ "vam.02",       0x020000, 0xcf7c97c7, 4 | BRF_ESS | BRF_PRG },

	{ "vam.11m",      0x200000, 0x4a39deb2, 5 | BRF_SND },
	{ "vam.12m",      0x200000, 0x1a3e5c03, 5 | BRF_SND },
};


STD_ROM_PICK(Dstlkur1) STD_ROM_FN(Dstlkur1)

static struct BurnRomInfo DstlkaRomDesc[] = {
	{ "vama.03a",      0x80000, 0x294e0bec, 1 | BRF_ESS | BRF_PRG },
	{ "vama.04a",      0x80000, 0xbc18e128, 1 | BRF_ESS | BRF_PRG },
	{ "vama.05a",      0x80000, 0xe709fa59, 1 | BRF_ESS | BRF_PRG },
	{ "vama.06a",      0x80000, 0x55e4d387, 1 | BRF_ESS | BRF_PRG },
	{ "vama.07a",      0x80000, 0x24e8f981, 1 | BRF_ESS | BRF_PRG },
	{ "vama.08a",      0x80000, 0x743f3a8e, 1 | BRF_ESS | BRF_PRG },
	{ "vama.09a",      0x80000, 0x67fa5573, 1 | BRF_ESS | BRF_PRG },
	{ "vama.10a",      0x80000, 0x5e03d747, 1 | BRF_ESS | BRF_PRG },

	{ "vam.13m",      0x400000, 0xc51baf99, 3 | BRF_GRA },
	{ "vam.15m",      0x400000, 0x3ce83c77, 3 | BRF_GRA },
	{ "vam.17m",      0x400000, 0x4f2408e0, 3 | BRF_GRA },
	{ "vam.19m",      0x400000, 0x9ff60250, 3 | BRF_GRA },
	{ "vam.14m",      0x100000, 0xbd87243c, 3 | BRF_GRA },
	{ "vam.16m",      0x100000, 0xafec855f, 3 | BRF_GRA },
	{ "vam.18m",      0x100000, 0x3a033625, 3 | BRF_GRA },
	{ "vam.20m",      0x100000, 0x2bff6a89, 3 | BRF_GRA },

	{ "vam.01",       0x020000, 0x64b685d5, 4 | BRF_ESS | BRF_PRG },
	{ "vam.02",       0x020000, 0xcf7c97c7, 4 | BRF_ESS | BRF_PRG },

	{ "vam.11m",      0x200000, 0x4a39deb2, 5 | BRF_SND },
	{ "vam.12m",      0x200000, 0x1a3e5c03, 5 | BRF_SND },
};


STD_ROM_PICK(Dstlka) STD_ROM_FN(Dstlka)

static struct BurnRomInfo VampjRomDesc[] = {
	{ "vamj.03a",      0x80000, 0xf55d3722, 1 | BRF_ESS | BRF_PRG },
	{ "vamj.04b",      0x80000, 0x4d9c43c4, 1 | BRF_ESS | BRF_PRG },
	{ "vamj.05a",      0x80000, 0x6c497e92, 1 | BRF_ESS | BRF_PRG },
	{ "vamj.06a",      0x80000, 0xf1bbecb6, 1 | BRF_ESS | BRF_PRG },
	{ "vamj.07a",      0x80000, 0x1067ad84, 1 | BRF_ESS | BRF_PRG },
	{ "vamj.08a",      0x80000, 0x4b89f41f, 1 | BRF_ESS | BRF_PRG },
	{ "vamj.09a",      0x80000, 0xfc0a4aac, 1 | BRF_ESS | BRF_PRG },
	{ "vamj.10a",      0x80000, 0x9270c26b, 1 | BRF_ESS | BRF_PRG },

	{ "vam.13m",      0x400000, 0xc51baf99, 3 | BRF_GRA },
	{ "vam.15m",      0x400000, 0x3ce83c77, 3 | BRF_GRA },
	{ "vam.17m",      0x400000, 0x4f2408e0, 3 | BRF_GRA },
	{ "vam.19m",      0x400000, 0x9ff60250, 3 | BRF_GRA },
	{ "vam.14m",      0x100000, 0xbd87243c, 3 | BRF_GRA },
	{ "vam.16m",      0x100000, 0xafec855f, 3 | BRF_GRA },
	{ "vam.18m",      0x100000, 0x3a033625, 3 | BRF_GRA },
	{ "vam.20m",      0x100000, 0x2bff6a89, 3 | BRF_GRA },

	{ "vam.01",       0x020000, 0x64b685d5, 4 | BRF_ESS | BRF_PRG },
	{ "vam.02",       0x020000, 0xcf7c97c7, 4 | BRF_ESS | BRF_PRG },

	{ "vam.11m",      0x200000, 0x4a39deb2, 5 | BRF_SND },
	{ "vam.12m",      0x200000, 0x1a3e5c03, 5 | BRF_SND },

};


STD_ROM_PICK(Vampj) STD_ROM_FN(Vampj)

static struct BurnRomInfo VampjaRomDesc[] = {
	{ "vamj.03a",      0x80000, 0xf55d3722, 1 | BRF_ESS | BRF_PRG },
	{ "vamj.04a",      0x80000, 0xfdcbdae3, 1 | BRF_ESS | BRF_PRG },
	{ "vamj.05a",      0x80000, 0x6c497e92, 1 | BRF_ESS | BRF_PRG },
	{ "vamj.06a",      0x80000, 0xf1bbecb6, 1 | BRF_ESS | BRF_PRG },
	{ "vamj.07a",      0x80000, 0x1067ad84, 1 | BRF_ESS | BRF_PRG },
	{ "vamj.08a",      0x80000, 0x4b89f41f, 1 | BRF_ESS | BRF_PRG },
	{ "vamj.09a",      0x80000, 0xfc0a4aac, 1 | BRF_ESS | BRF_PRG },
	{ "vamj.10a",      0x80000, 0x9270c26b, 1 | BRF_ESS | BRF_PRG },

	{ "vam.13m",      0x400000, 0xc51baf99, 3 | BRF_GRA },
	{ "vam.15m",      0x400000, 0x3ce83c77, 3 | BRF_GRA },
	{ "vam.17m",      0x400000, 0x4f2408e0, 3 | BRF_GRA },
	{ "vam.19m",      0x400000, 0x9ff60250, 3 | BRF_GRA },
	{ "vam.14m",      0x100000, 0xbd87243c, 3 | BRF_GRA },
	{ "vam.16m",      0x100000, 0xafec855f, 3 | BRF_GRA },
	{ "vam.18m",      0x100000, 0x3a033625, 3 | BRF_GRA },
	{ "vam.20m",      0x100000, 0x2bff6a89, 3 | BRF_GRA },

	{ "vam.01",       0x020000, 0x64b685d5, 4 | BRF_ESS | BRF_PRG },
	{ "vam.02",       0x020000, 0xcf7c97c7, 4 | BRF_ESS | BRF_PRG },

	{ "vam.11m",      0x200000, 0x4a39deb2, 5 | BRF_SND },
	{ "vam.12m",      0x200000, 0x1a3e5c03, 5 | BRF_SND },
};


STD_ROM_PICK(Vampja) STD_ROM_FN(Vampja)

static struct BurnRomInfo Vampjr1RomDesc[] = {
	{ "vamj.03",       0x80000, 0x8895bf77, 1 | BRF_ESS | BRF_PRG },
	{ "vamj.04",       0x80000, 0x5027db3d, 1 | BRF_ESS | BRF_PRG },
	{ "vamj.05",       0x80000, 0x97c66fdb, 1 | BRF_ESS | BRF_PRG },
	{ "vamj.06",       0x80000, 0x9b4c3426, 1 | BRF_ESS | BRF_PRG },
	{ "vamj.07",       0x80000, 0x303bc4fd, 1 | BRF_ESS | BRF_PRG },
	{ "vamj.08",       0x80000, 0x3dea3646, 1 | BRF_ESS | BRF_PRG },
	{ "vamj.09",       0x80000, 0xc119a827, 1 | BRF_ESS | BRF_PRG },
	{ "vamj.10",       0x80000, 0x46593b79, 1 | BRF_ESS | BRF_PRG },

	{ "vam.13m",      0x400000, 0xc51baf99, 3 | BRF_GRA },
	{ "vam.15m",      0x400000, 0x3ce83c77, 3 | BRF_GRA },
	{ "vam.17m",      0x400000, 0x4f2408e0, 3 | BRF_GRA },
	{ "vam.19m",      0x400000, 0x9ff60250, 3 | BRF_GRA },
	{ "vam.14m",      0x100000, 0xbd87243c, 3 | BRF_GRA },
	{ "vam.16m",      0x100000, 0xafec855f, 3 | BRF_GRA },
	{ "vam.18m",      0x100000, 0x3a033625, 3 | BRF_GRA },
	{ "vam.20m",      0x100000, 0x2bff6a89, 3 | BRF_GRA },

	{ "vam.01",       0x020000, 0x64b685d5, 4 | BRF_ESS | BRF_PRG },
	{ "vam.02",       0x020000, 0xcf7c97c7, 4 | BRF_ESS | BRF_PRG },

	{ "vam.11m",      0x200000, 0x4a39deb2, 5 | BRF_SND },
	{ "vam.12m",      0x200000, 0x1a3e5c03, 5 | BRF_SND },
};


STD_ROM_PICK(Vampjr1) STD_ROM_FN(Vampjr1)

struct BurnDriver BurnDrvCpsDstlk = {
	"dstlk", NULL, NULL, "1994",
	"Darkstalkers - the night warriors (940705 Euro)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS2,
	NULL, DstlkRomInfo, DstlkRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsDstlku = {
	"dstlku", "dstlk", NULL, "1994",
	"Darkstalkers - the night warriors (940818 USA)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, DstlkuRomInfo, DstlkuRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsDstlkur1 = {
	"dstlkur1", "dstlk", NULL, "1994",
	"Darkstalkers - the night warriors (940705 USA)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Dstlkur1RomInfo, Dstlkur1RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsDstlka = {
	"dstlka", "dstlk", NULL, "1994",
	"Darkstalkers - the night warriors (940705 Asia)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, DstlkaRomInfo, DstlkaRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsVampj = {
	"vampj", "dstlk", NULL, "1994",
	"Vampire - the night warriors (940705 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, VampjRomInfo, VampjRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsVampja = {
	"vampja", "dstlk", NULL, "1994",
	"Vampire - the night warriors (940705 Japan, alt)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, VampjaRomInfo, VampjaRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsVampjr1 = {
	"vampjr1", "dstlk", NULL, "1994",
	"Vampire - the night warriors (940630 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Vampjr1RomInfo, Vampjr1RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
