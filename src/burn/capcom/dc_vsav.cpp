#include "cps.h"

STDINPUTINFOSPEC(Drv, CpsFsi);

static struct BurnRomInfo VsavRomDesc[] = {
	{ "vm3e.03d",      0x80000, 0xf5962a8c, 1 | BRF_ESS | BRF_PRG },
	{ "vm3e.04d",      0x80000, 0x21b40ea2, 1 | BRF_ESS | BRF_PRG },
	{ "vm3.05a",       0x80000, 0x4118e00f, 1 | BRF_ESS | BRF_PRG },
	{ "vm3.06a",       0x80000, 0x2f4fd3a9, 1 | BRF_ESS | BRF_PRG },
	{ "vm3.07b",       0x80000, 0xcbda91b8, 1 | BRF_ESS | BRF_PRG },
	{ "vm3.08a",       0x80000, 0x6ca47259, 1 | BRF_ESS | BRF_PRG },
	{ "vm3.09b",       0x80000, 0xf4a339e3, 1 | BRF_ESS | BRF_PRG },
	{ "vm3.10b",       0x80000, 0xfffbb5b8, 1 | BRF_ESS | BRF_PRG },

	{ "vm3.13m",      0x400000, 0xfd8a11eb, 3 | BRF_GRA },
	{ "vm3.15m",      0x400000, 0xdd1e7d4e, 3 | BRF_GRA },
	{ "vm3.17m",      0x400000, 0x6b89445e, 3 | BRF_GRA },
	{ "vm3.19m",      0x400000, 0x3830fdc7, 3 | BRF_GRA },
	{ "vm3.14m",      0x400000, 0xc1a28e6c, 3 | BRF_GRA },
	{ "vm3.16m",      0x400000, 0x194a7304, 3 | BRF_GRA },
	{ "vm3.18m",      0x400000, 0xdf9a9f47, 3 | BRF_GRA },
	{ "vm3.20m",      0x400000, 0xc22fc3d9, 3 | BRF_GRA },

	{ "vm3.01",       0x020000, 0xf778769b, 4 | BRF_ESS | BRF_PRG },
	{ "vm3.02",       0x020000, 0xcc09faa1, 4 | BRF_ESS | BRF_PRG },

	{ "vm3.11m",      0x400000, 0xe80e956e, 5 | BRF_SND },
	{ "vm3.12m",      0x400000, 0x9cd71557, 5 | BRF_SND },
};


STD_ROM_PICK(Vsav) STD_ROM_FN(Vsav)

static struct BurnRomInfo VsavuRomDesc[] = {
	{ "vm3u.03d",      0x80000, 0x1f295274, 1 | BRF_ESS | BRF_PRG },
	{ "vm3u.04d",      0x80000, 0xc46adf81, 1 | BRF_ESS | BRF_PRG },
	{ "vm3.05a",       0x80000, 0x4118e00f, 1 | BRF_ESS | BRF_PRG },
	{ "vm3.06a",       0x80000, 0x2f4fd3a9, 1 | BRF_ESS | BRF_PRG },
	{ "vm3.07b",       0x80000, 0xcbda91b8, 1 | BRF_ESS | BRF_PRG },
	{ "vm3.08a",       0x80000, 0x6ca47259, 1 | BRF_ESS | BRF_PRG },
	{ "vm3.09b",       0x80000, 0xf4a339e3, 1 | BRF_ESS | BRF_PRG },
	{ "vm3.10b",       0x80000, 0xfffbb5b8, 1 | BRF_ESS | BRF_PRG },

	{ "vm3.13m",      0x400000, 0xfd8a11eb, 3 | BRF_GRA },
	{ "vm3.15m",      0x400000, 0xdd1e7d4e, 3 | BRF_GRA },
	{ "vm3.17m",      0x400000, 0x6b89445e, 3 | BRF_GRA },
	{ "vm3.19m",      0x400000, 0x3830fdc7, 3 | BRF_GRA },
	{ "vm3.14m",      0x400000, 0xc1a28e6c, 3 | BRF_GRA },
	{ "vm3.16m",      0x400000, 0x194a7304, 3 | BRF_GRA },
	{ "vm3.18m",      0x400000, 0xdf9a9f47, 3 | BRF_GRA },
	{ "vm3.20m",      0x400000, 0xc22fc3d9, 3 | BRF_GRA },

	{ "vm3.01",       0x020000, 0xf778769b, 4 | BRF_ESS | BRF_PRG },
	{ "vm3.02",       0x020000, 0xcc09faa1, 4 | BRF_ESS | BRF_PRG },

	{ "vm3.11m",      0x400000, 0xe80e956e, 5 | BRF_SND },
	{ "vm3.12m",      0x400000, 0x9cd71557, 5 | BRF_SND },
};


STD_ROM_PICK(Vsavu) STD_ROM_FN(Vsavu)

static struct BurnRomInfo VsavjRomDesc[] = {
	{ "vm3j.03d",      0x80000, 0x2a2e74a4, 1 | BRF_ESS | BRF_PRG },
	{ "vm3j.04d",      0x80000, 0x1c2427bc, 1 | BRF_ESS | BRF_PRG },
	{ "vm3j.05a",      0x80000, 0x95ce88d5, 1 | BRF_ESS | BRF_PRG },
	{ "vm3j.06b",      0x80000, 0x2c4297e0, 1 | BRF_ESS | BRF_PRG },
	{ "vm3j.07b",      0x80000, 0xa38aaae7, 1 | BRF_ESS | BRF_PRG },
	{ "vm3j.08a",      0x80000, 0x5773e5c9, 1 | BRF_ESS | BRF_PRG },
	{ "vm3j.09b",      0x80000, 0xd064f8b9, 1 | BRF_ESS | BRF_PRG },
	{ "vm3j.10b",      0x80000, 0x434518e9, 1 | BRF_ESS | BRF_PRG },

	{ "vm3.13m",      0x400000, 0xfd8a11eb, 3 | BRF_GRA },
	{ "vm3.15m",      0x400000, 0xdd1e7d4e, 3 | BRF_GRA },
	{ "vm3.17m",      0x400000, 0x6b89445e, 3 | BRF_GRA },
	{ "vm3.19m",      0x400000, 0x3830fdc7, 3 | BRF_GRA },
	{ "vm3.14m",      0x400000, 0xc1a28e6c, 3 | BRF_GRA },
	{ "vm3.16m",      0x400000, 0x194a7304, 3 | BRF_GRA },
	{ "vm3.18m",      0x400000, 0xdf9a9f47, 3 | BRF_GRA },
	{ "vm3.20m",      0x400000, 0xc22fc3d9, 3 | BRF_GRA },

	{ "vm3.01",       0x020000, 0xf778769b, 4 | BRF_ESS | BRF_PRG },
	{ "vm3.02",       0x020000, 0xcc09faa1, 4 | BRF_ESS | BRF_PRG },

	{ "vm3.11m",      0x400000, 0xe80e956e, 5 | BRF_SND },
	{ "vm3.12m",      0x400000, 0x9cd71557, 5 | BRF_SND },
};


STD_ROM_PICK(Vsavj) STD_ROM_FN(Vsavj)

static struct BurnRomInfo VsavaRomDesc[] = {
	{ "vm3a.03d",      0x80000, 0x44c1198f, 1 | BRF_ESS | BRF_PRG },
	{ "vm3a.04d",      0x80000, 0x2218b781, 1 | BRF_ESS | BRF_PRG },
	{ "vm3.05a",       0x80000, 0x4118e00f, 1 | BRF_ESS | BRF_PRG },
	{ "vm3.06a",       0x80000, 0x2f4fd3a9, 1 | BRF_ESS | BRF_PRG },
	{ "vm3.07b",       0x80000, 0xcbda91b8, 1 | BRF_ESS | BRF_PRG },
	{ "vm3.08a",       0x80000, 0x6ca47259, 1 | BRF_ESS | BRF_PRG },
	{ "vm3.09b",       0x80000, 0xf4a339e3, 1 | BRF_ESS | BRF_PRG },
	{ "vm3.10b",       0x80000, 0xfffbb5b8, 1 | BRF_ESS | BRF_PRG },

	{ "vm3.13m",      0x400000, 0xfd8a11eb, 3 | BRF_GRA },
	{ "vm3.15m",      0x400000, 0xdd1e7d4e, 3 | BRF_GRA },
	{ "vm3.17m",      0x400000, 0x6b89445e, 3 | BRF_GRA },
	{ "vm3.19m",      0x400000, 0x3830fdc7, 3 | BRF_GRA },
	{ "vm3.14m",      0x400000, 0xc1a28e6c, 3 | BRF_GRA },
	{ "vm3.16m",      0x400000, 0x194a7304, 3 | BRF_GRA },
	{ "vm3.18m",      0x400000, 0xdf9a9f47, 3 | BRF_GRA },
	{ "vm3.20m",      0x400000, 0xc22fc3d9, 3 | BRF_GRA },

	{ "vm3.01",       0x020000, 0xf778769b, 4 | BRF_ESS | BRF_PRG },
	{ "vm3.02",       0x020000, 0xcc09faa1, 4 | BRF_ESS | BRF_PRG },

	{ "vm3.11m",      0x400000, 0xe80e956e, 5 | BRF_SND },
	{ "vm3.12m",      0x400000, 0x9cd71557, 5 | BRF_SND },
};


STD_ROM_PICK(Vsava) STD_ROM_FN(Vsava)

static struct BurnRomInfo VsavhRomDesc[] = {
	{ "vm3h.03a",      0x80000, 0x7cc62df8, 1 | BRF_ESS | BRF_PRG },
	{ "vm3h.04d",      0x80000, 0xd716f3b5, 1 | BRF_ESS | BRF_PRG },
	{ "vm3.05a",       0x80000, 0x4118e00f, 1 | BRF_ESS | BRF_PRG },
	{ "vm3.06a",       0x80000, 0x2f4fd3a9, 1 | BRF_ESS | BRF_PRG },
	{ "vm3.07b",       0x80000, 0xcbda91b8, 1 | BRF_ESS | BRF_PRG },
	{ "vm3.08a",       0x80000, 0x6ca47259, 1 | BRF_ESS | BRF_PRG },
	{ "vm3.09b",       0x80000, 0xf4a339e3, 1 | BRF_ESS | BRF_PRG },
	{ "vm3.10b",       0x80000, 0xfffbb5b8, 1 | BRF_ESS | BRF_PRG },

	{ "vm3.13m",      0x400000, 0xfd8a11eb, 3 | BRF_GRA },
	{ "vm3.15m",      0x400000, 0xdd1e7d4e, 3 | BRF_GRA },
	{ "vm3.17m",      0x400000, 0x6b89445e, 3 | BRF_GRA },
	{ "vm3.19m",      0x400000, 0x3830fdc7, 3 | BRF_GRA },
	{ "vm3.14m",      0x400000, 0xc1a28e6c, 3 | BRF_GRA },
	{ "vm3.16m",      0x400000, 0x194a7304, 3 | BRF_GRA },
	{ "vm3.18m",      0x400000, 0xdf9a9f47, 3 | BRF_GRA },
	{ "vm3.20m",      0x400000, 0xc22fc3d9, 3 | BRF_GRA },

	{ "vm3.01",       0x020000, 0xf778769b, 4 | BRF_ESS | BRF_PRG },
	{ "vm3.02",       0x020000, 0xcc09faa1, 4 | BRF_ESS | BRF_PRG },

	{ "vm3.11m",      0x400000, 0xe80e956e, 5 | BRF_SND },
	{ "vm3.12m",      0x400000, 0x9cd71557, 5 | BRF_SND },
};


STD_ROM_PICK(Vsavh) STD_ROM_FN(Vsavh)

struct BurnDriver BurnDrvCpsVsav = {
	"vsav", NULL, NULL, "1997",
	"Vampire Savior - the lord of vampire (970519 Euro)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS2,
	NULL, VsavRomInfo, VsavRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsVsavu = {
	"vsavu", "vsav", NULL, "1997",
	"Vampire Savior - the lord of vampire (970519 USA)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, VsavuRomInfo, VsavuRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsVsavj = {
	"vsavj", "vsav", NULL, "1997",
	"Vampire Savior - the lord of vampire (970519 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, VsavjRomInfo, VsavjRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsVsava = {
	"vsava", "vsav", NULL, "1997",
	"Vampire Savior - the lord of vampire (970519 Asia)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, VsavaRomInfo, VsavaRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsVsavh = {
	"vsavh", "vsav", NULL, "1997",
	"Vampire Savior - the lord of vampire (970519 Hispanic)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, VsavhRomInfo, VsavhRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
