#include "cps.h"

STDINPUTINFOSPEC(Drv, CpsFsi);

static struct BurnRomInfo Vhunt2RomDesc[] = {
	{ "vh2j.03a",     0x080000, 0x9ae8f186, 1 | BRF_ESS | BRF_PRG },
	{ "vh2j.04a",     0x080000, 0xe2fabf53, 1 | BRF_ESS | BRF_PRG },
	{ "vh2j.05",      0x080000, 0xde34f624, 1 | BRF_ESS | BRF_PRG },
	{ "vh2j.06",      0x080000, 0x6a3b9897, 1 | BRF_ESS | BRF_PRG },
	{ "vh2j.07",      0x080000, 0xb021c029, 1 | BRF_ESS | BRF_PRG },
	{ "vh2j.08",      0x080000, 0xac873dff, 1 | BRF_ESS | BRF_PRG },
	{ "vh2j.09",      0x080000, 0xeaefce9c, 1 | BRF_ESS | BRF_PRG },
	{ "vh2j.10",      0x080000, 0x11730952, 1 | BRF_ESS | BRF_PRG },

	{ "vh2.13m",      0x400000, 0x3b02ddaa, 3 | BRF_GRA },
	{ "vh2.15m",      0x400000, 0x4e40de66, 3 | BRF_GRA },
	{ "vh2.17m",      0x400000, 0xb31d00c9, 3 | BRF_GRA },
	{ "vh2.19m",      0x400000, 0x149be3ab, 3 | BRF_GRA },
	{ "vh2.14m",      0x400000, 0xcd09bd63, 3 | BRF_GRA },
	{ "vh2.16m",      0x400000, 0xe0182c15, 3 | BRF_GRA },
	{ "vh2.18m",      0x400000, 0x778dc4f6, 3 | BRF_GRA },
	{ "vh2.20m",      0x400000, 0x605d9d1d, 3 | BRF_GRA },

	{ "vh2.01",       0x020000, 0x67b9f779, 4 | BRF_ESS | BRF_PRG },
	{ "vh2.02",       0x020000, 0xaaf15fcb, 4 | BRF_ESS | BRF_PRG },

	{ "vh2.11m",      0x400000, 0x38922efd, 5 | BRF_SND },
	{ "vh2.12m",      0x400000, 0x6e2430af, 5 | BRF_SND },
};


STD_ROM_PICK(Vhunt2) STD_ROM_FN(Vhunt2)

static struct BurnRomInfo Vhunt2r1RomDesc[] = {
	{ "vh2j.03",      0x080000, 0x1a5feb13, 1 | BRF_ESS | BRF_PRG },
	{ "vh2j.04",      0x080000, 0x434611a5, 1 | BRF_ESS | BRF_PRG },
	{ "vh2j.05",      0x080000, 0xde34f624, 1 | BRF_ESS | BRF_PRG },
	{ "vh2j.06",      0x080000, 0x6a3b9897, 1 | BRF_ESS | BRF_PRG },
	{ "vh2j.07",      0x080000, 0xb021c029, 1 | BRF_ESS | BRF_PRG },
	{ "vh2j.08",      0x080000, 0xac873dff, 1 | BRF_ESS | BRF_PRG },
	{ "vh2j.09",      0x080000, 0xeaefce9c, 1 | BRF_ESS | BRF_PRG },
	{ "vh2j.10",      0x080000, 0x11730952, 1 | BRF_ESS | BRF_PRG },

	{ "vh2.13m",      0x400000, 0x3b02ddaa, 3 | BRF_GRA },
	{ "vh2.15m",      0x400000, 0x4e40de66, 3 | BRF_GRA },
	{ "vh2.17m",      0x400000, 0xb31d00c9, 3 | BRF_GRA },
	{ "vh2.19m",      0x400000, 0x149be3ab, 3 | BRF_GRA },
	{ "vh2.14m",      0x400000, 0xcd09bd63, 3 | BRF_GRA },
	{ "vh2.16m",      0x400000, 0xe0182c15, 3 | BRF_GRA },
	{ "vh2.18m",      0x400000, 0x778dc4f6, 3 | BRF_GRA },
	{ "vh2.20m",      0x400000, 0x605d9d1d, 3 | BRF_GRA },

	{ "vh2.01",       0x020000, 0x67b9f779, 4 | BRF_ESS | BRF_PRG },
	{ "vh2.02",       0x020000, 0xaaf15fcb, 4 | BRF_ESS | BRF_PRG },

	{ "vh2.11m",      0x400000, 0x38922efd, 5 | BRF_SND },
	{ "vh2.12m",      0x400000, 0x6e2430af, 5 | BRF_SND },
};


STD_ROM_PICK(Vhunt2r1) STD_ROM_FN(Vhunt2r1)

struct BurnDriver BurnDrvCpsVhunt2 = {
	"vhunt2", NULL, NULL, "1997",
	"Vampire Hunter 2 - darkstalkers revenge (970929 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS2,
	NULL, Vhunt2RomInfo, Vhunt2RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsVhunt2r1 = {
	"vhunt2r1", "vhunt2", NULL, "1997",
	"Vampire Hunter 2 - darkstalkers revenge (970913 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Vhunt2r1RomInfo, Vhunt2r1RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
