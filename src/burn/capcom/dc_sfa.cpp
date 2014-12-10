#include "cps.h"

STDINPUTINFOSPEC(Drv, CpsFsi);

static struct BurnRomInfo SfaRomDesc[] = {
	{ "sfze.03d",      0x80000, 0xebf2054d, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.04b",       0x80000, 0x8b73b0e5, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.05a",       0x80000, 0x0810544d, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.06",        0x80000, 0x806e8f38, 1 | BRF_ESS | BRF_PRG },

	{ "sfz.14m",      0x200000, 0x90fefdb3, 3 | BRF_GRA },
	{ "sfz.16m",      0x200000, 0x5354c948, 3 | BRF_GRA },
	{ "sfz.18m",      0x200000, 0x41a1e790, 3 | BRF_GRA },
	{ "sfz.20m",      0x200000, 0xa549df98, 3 | BRF_GRA },

	{ "sfz.01",       0x020000, 0xffffec7d, 4 | BRF_ESS | BRF_PRG },
	{ "sfz.02",       0x020000, 0x45f46a08, 4 | BRF_ESS | BRF_PRG },

	{ "sfz.11m",      0x200000, 0xc4b093cd, 5 | BRF_SND },
	{ "sfz.12m",      0x200000, 0x8bdbc4b4, 5 | BRF_SND },
};


STD_ROM_PICK(Sfa) STD_ROM_FN(Sfa)

static struct BurnRomInfo Sfar1RomDesc[] = {
	{ "sfze.03c",      0x80000, 0xa1b69dd7, 1 | BRF_ESS | BRF_PRG },
	{ "sfze.04b",      0x80000, 0xbb90acd5, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.05a",       0x80000, 0x0810544d, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.06",        0x80000, 0x806e8f38, 1 | BRF_ESS | BRF_PRG },

	{ "sfz.14m",      0x200000, 0x90fefdb3, 3 | BRF_GRA },
	{ "sfz.16m",      0x200000, 0x5354c948, 3 | BRF_GRA },
	{ "sfz.18m",      0x200000, 0x41a1e790, 3 | BRF_GRA },
	{ "sfz.20m",      0x200000, 0xa549df98, 3 | BRF_GRA },

	{ "sfz.01",       0x020000, 0xffffec7d, 4 | BRF_ESS | BRF_PRG },
	{ "sfz.02",       0x020000, 0x45f46a08, 4 | BRF_ESS | BRF_PRG },

	{ "sfz.11m",      0x200000, 0xc4b093cd, 5 | BRF_SND },
	{ "sfz.12m",      0x200000, 0x8bdbc4b4, 5 | BRF_SND },
};


STD_ROM_PICK(Sfar1) STD_ROM_FN(Sfar1)

static struct BurnRomInfo Sfar2RomDesc[] = {
	{ "sfze.03b",      0x80000, 0x2bf5708e, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.04a",       0x80000, 0x5f99e9a5, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.05a",       0x80000, 0x0810544d, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.06",        0x80000, 0x806e8f38, 1 | BRF_ESS | BRF_PRG },

	{ "sfz.14m",      0x200000, 0x90fefdb3, 3 | BRF_GRA },
	{ "sfz.16m",      0x200000, 0x5354c948, 3 | BRF_GRA },
	{ "sfz.18m",      0x200000, 0x41a1e790, 3 | BRF_GRA },
	{ "sfz.20m",      0x200000, 0xa549df98, 3 | BRF_GRA },

	{ "sfz.01",       0x020000, 0xffffec7d, 4 | BRF_ESS | BRF_PRG },
	{ "sfz.02",       0x020000, 0x45f46a08, 4 | BRF_ESS | BRF_PRG },

	{ "sfz.11m",      0x200000, 0xc4b093cd, 5 | BRF_SND },
	{ "sfz.12m",      0x200000, 0x8bdbc4b4, 5 | BRF_SND },
};


STD_ROM_PICK(Sfar2) STD_ROM_FN(Sfar2)

static struct BurnRomInfo Sfar3RomDesc[] = {
	{ "sfze.03a",      0x80000, 0xfdbcd434, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.04",        0x80000, 0x0c436d30, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.05",        0x80000, 0x1f363612, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.06",        0x80000, 0x806e8f38, 1 | BRF_ESS | BRF_PRG },

	{ "sfz.14m",      0x200000, 0x90fefdb3, 3 | BRF_GRA },
	{ "sfz.16m",      0x200000, 0x5354c948, 3 | BRF_GRA },
	{ "sfz.18m",      0x200000, 0x41a1e790, 3 | BRF_GRA },
	{ "sfz.20m",      0x200000, 0xa549df98, 3 | BRF_GRA },

	{ "sfz.01",       0x020000, 0xffffec7d, 4 | BRF_ESS | BRF_PRG },
	{ "sfz.02",       0x020000, 0x45f46a08, 4 | BRF_ESS | BRF_PRG },

	{ "sfz.11m",      0x200000, 0xc4b093cd, 5 | BRF_SND },
	{ "sfz.12m",      0x200000, 0x8bdbc4b4, 5 | BRF_SND },
};


STD_ROM_PICK(Sfar3) STD_ROM_FN(Sfar3)

static struct BurnRomInfo SfauRomDesc[] = {
	{ "sfzu.03a",      0x80000, 0x49fc7db9, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.04a",       0x80000, 0x5f99e9a5, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.05a",       0x80000, 0x0810544d, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.06",        0x80000, 0x806e8f38, 1 | BRF_ESS | BRF_PRG },

	{ "sfz.14m",      0x200000, 0x90fefdb3, 3 | BRF_GRA },
	{ "sfz.16m",      0x200000, 0x5354c948, 3 | BRF_GRA },
	{ "sfz.18m",      0x200000, 0x41a1e790, 3 | BRF_GRA },
	{ "sfz.20m",      0x200000, 0xa549df98, 3 | BRF_GRA },

	{ "sfz.01",       0x020000, 0xffffec7d, 4 | BRF_ESS | BRF_PRG },
	{ "sfz.02",       0x020000, 0x45f46a08, 4 | BRF_ESS | BRF_PRG },

	{ "sfz.11m",      0x200000, 0xc4b093cd, 5 | BRF_SND },
	{ "sfz.12m",      0x200000, 0x8bdbc4b4, 5 | BRF_SND },
};


STD_ROM_PICK(Sfau) STD_ROM_FN(Sfau)

static struct BurnRomInfo SfzaRomDesc[] = {
	{ "sfza.03a",      0x80000, 0xca91bed9, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.04a",       0x80000, 0x5f99e9a5, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.05a",       0x80000, 0x0810544d, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.06",        0x80000, 0x806e8f38, 1 | BRF_ESS | BRF_PRG },

	{ "sfz.14m",      0x200000, 0x90fefdb3, 3 | BRF_GRA },
	{ "sfz.16m",      0x200000, 0x5354c948, 3 | BRF_GRA },
	{ "sfz.18m",      0x200000, 0x41a1e790, 3 | BRF_GRA },
	{ "sfz.20m",      0x200000, 0xa549df98, 3 | BRF_GRA },

	{ "sfz.01",       0x020000, 0xffffec7d, 4 | BRF_ESS | BRF_PRG },
	{ "sfz.02",       0x020000, 0x45f46a08, 4 | BRF_ESS | BRF_PRG },

	{ "sfz.11m",      0x200000, 0xc4b093cd, 5 | BRF_SND },
	{ "sfz.12m",      0x200000, 0x8bdbc4b4, 5 | BRF_SND },
};


STD_ROM_PICK(Sfza) STD_ROM_FN(Sfza)

static struct BurnRomInfo SfzjRomDesc[] = {
	{ "sfzj.03c",      0x80000, 0xf5444120, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.04b",       0x80000, 0x8b73b0e5, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.05a",       0x80000, 0x0810544d, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.06",        0x80000, 0x806e8f38, 1 | BRF_ESS | BRF_PRG },

	{ "sfz.14m",      0x200000, 0x90fefdb3, 3 | BRF_GRA },
	{ "sfz.16m",      0x200000, 0x5354c948, 3 | BRF_GRA },
	{ "sfz.18m",      0x200000, 0x41a1e790, 3 | BRF_GRA },
	{ "sfz.20m",      0x200000, 0xa549df98, 3 | BRF_GRA },

	{ "sfz.01",       0x020000, 0xffffec7d, 4 | BRF_ESS | BRF_PRG },
	{ "sfz.02",       0x020000, 0x45f46a08, 4 | BRF_ESS | BRF_PRG },

	{ "sfz.11m",      0x200000, 0xc4b093cd, 5 | BRF_SND },
	{ "sfz.12m",      0x200000, 0x8bdbc4b4, 5 | BRF_SND },
};


STD_ROM_PICK(Sfzj) STD_ROM_FN(Sfzj)

static struct BurnRomInfo Sfzjr1RomDesc[] = {
	{ "sfzj.03b",      0x80000, 0x844220c2, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.04a",       0x80000, 0x5f99e9a5, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.05a",       0x80000, 0x0810544d, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.06",        0x80000, 0x806e8f38, 1 | BRF_ESS | BRF_PRG },

	{ "sfz.14m",      0x200000, 0x90fefdb3, 3 | BRF_GRA },
	{ "sfz.16m",      0x200000, 0x5354c948, 3 | BRF_GRA },
	{ "sfz.18m",      0x200000, 0x41a1e790, 3 | BRF_GRA },
	{ "sfz.20m",      0x200000, 0xa549df98, 3 | BRF_GRA },

	{ "sfz.01",       0x020000, 0xffffec7d, 4 | BRF_ESS | BRF_PRG },
	{ "sfz.02",       0x020000, 0x45f46a08, 4 | BRF_ESS | BRF_PRG },

	{ "sfz.11m",      0x200000, 0xc4b093cd, 5 | BRF_SND },
	{ "sfz.12m",      0x200000, 0x8bdbc4b4, 5 | BRF_SND },
};


STD_ROM_PICK(Sfzjr1) STD_ROM_FN(Sfzjr1)

static struct BurnRomInfo Sfzjr2RomDesc[] = {
	{ "sfzj.03a",      0x80000, 0x3cfce93c, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.04",        0x80000, 0x0c436d30, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.05",        0x80000, 0x1f363612, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.06",        0x80000, 0x806e8f38, 1 | BRF_ESS | BRF_PRG },

	{ "sfz.14m",      0x200000, 0x90fefdb3, 3 | BRF_GRA },
	{ "sfz.16m",      0x200000, 0x5354c948, 3 | BRF_GRA },
	{ "sfz.18m",      0x200000, 0x41a1e790, 3 | BRF_GRA },
	{ "sfz.20m",      0x200000, 0xa549df98, 3 | BRF_GRA },

	{ "sfz.01",       0x020000, 0xffffec7d, 4 | BRF_ESS | BRF_PRG },
	{ "sfz.02",       0x020000, 0x45f46a08, 4 | BRF_ESS | BRF_PRG },

	{ "sfz.11m",      0x200000, 0xc4b093cd, 5 | BRF_SND },
	{ "sfz.12m",      0x200000, 0x8bdbc4b4, 5 | BRF_SND },
};


STD_ROM_PICK(Sfzjr2) STD_ROM_FN(Sfzjr2)

static struct BurnRomInfo SfzhRomDesc[] = {
	{ "sfzh.03c",     0x080000, 0xbce635aa, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.04a",      0x080000, 0x5f99e9a5, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.05a",      0x080000, 0x0810544d, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.06",       0x080000, 0x806e8f38, 1 | BRF_ESS | BRF_PRG },

	{ "sfz.14m",      0x200000, 0x90fefdb3, 3 | BRF_GRA },
	{ "sfz.16m",      0x200000, 0x5354c948, 3 | BRF_GRA },
	{ "sfz.18m",      0x200000, 0x41a1e790, 3 | BRF_GRA },
	{ "sfz.20m",      0x200000, 0xa549df98, 3 | BRF_GRA },

	{ "sfz.01",       0x020000, 0xffffec7d, 4 | BRF_ESS | BRF_PRG },
	{ "sfz.02",       0x020000, 0x45f46a08, 4 | BRF_ESS | BRF_PRG },

	{ "sfz.11m",      0x200000, 0xc4b093cd, 5 | BRF_SND },
	{ "sfz.12m",      0x200000, 0x8bdbc4b4, 5 | BRF_SND },
};


STD_ROM_PICK(Sfzh) STD_ROM_FN(Sfzh)

static struct BurnRomInfo SfzbRomDesc[] = {
	{ "sfzb.03g",     0x080000, 0x348862d4, 1 | BRF_ESS | BRF_PRG },
	{ "sfzb.04e",     0x080000, 0x8d9b2480, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.05a",      0x080000, 0x0810544d, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.06",       0x080000, 0x806e8f38, 1 | BRF_ESS | BRF_PRG },

	{ "sfz.14m",      0x200000, 0x90fefdb3, 3 | BRF_GRA },
	{ "sfz.16m",      0x200000, 0x5354c948, 3 | BRF_GRA },
	{ "sfz.18m",      0x200000, 0x41a1e790, 3 | BRF_GRA },
	{ "sfz.20m",      0x200000, 0xa549df98, 3 | BRF_GRA },

	{ "sfz.01",       0x020000, 0xffffec7d, 4 | BRF_ESS | BRF_PRG },
	{ "sfz.02",       0x020000, 0x45f46a08, 4 | BRF_ESS | BRF_PRG },

	{ "sfz.11m",      0x200000, 0xc4b093cd, 5 | BRF_SND },
	{ "sfz.12m",      0x200000, 0x8bdbc4b4, 5 | BRF_SND },
};


STD_ROM_PICK(Sfzb) STD_ROM_FN(Sfzb)

static struct BurnRomInfo Sfzbr1RomDesc[] = {
	{ "sfzb.03e",     0x080000, 0xecba89a3, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.04b",       0x80000, 0x8b73b0e5, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.05a",       0x80000, 0x0810544d, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.06",        0x80000, 0x806e8f38, 1 | BRF_ESS | BRF_PRG },

	{ "sfz.14m",      0x200000, 0x90fefdb3, 3 | BRF_GRA },
	{ "sfz.16m",      0x200000, 0x5354c948, 3 | BRF_GRA },
	{ "sfz.18m",      0x200000, 0x41a1e790, 3 | BRF_GRA },
	{ "sfz.20m",      0x200000, 0xa549df98, 3 | BRF_GRA },

	{ "sfz.01",       0x020000, 0xffffec7d, 4 | BRF_ESS | BRF_PRG },
	{ "sfz.02",       0x020000, 0x45f46a08, 4 | BRF_ESS | BRF_PRG },

	{ "sfz.11m",      0x200000, 0xc4b093cd, 5 | BRF_SND },
	{ "sfz.12m",      0x200000, 0x8bdbc4b4, 5 | BRF_SND },
};


STD_ROM_PICK(Sfzbr1) STD_ROM_FN(Sfzbr1)

struct BurnDriver BurnDrvCpsSfa = {
	"sfa", NULL, NULL, "1995",
	"Street Fighter Alpha - warriors' dreams (950727 Euro)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS2,
	NULL, SfaRomInfo, SfaRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSfar1 = {
	"sfar1", "sfa", NULL, "1995",
	"Street Fighter Alpha - warriors' dreams (950718 Euro)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Sfar1RomInfo, Sfar1RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSfar2 = {
	"sfar2", "sfa", NULL, "1995",
	"Street Fighter Alpha - warriors' dreams (950627 Euro)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Sfar2RomInfo, Sfar2RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSfar3 = {
	"sfar3", "sfa", NULL, "1995",
	"Street Fighter Alpha - warriors' dreams (950605 Euro)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Sfar3RomInfo, Sfar3RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSfau = {
	"sfau", "sfa", NULL, "1995",
	"Street Fighter Alpha - warriors' dreams (950627 USA)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, SfauRomInfo, SfauRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSfza = {
	"sfza", "sfa", NULL, "1995",
	"Street Fighter Zero (950627 Asia)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, SfzaRomInfo, SfzaRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSfzj = {
	"sfzj", "sfa", NULL, "1995",
	"Street Fighter Zero (950727 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, SfzjRomInfo, SfzjRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSfzjr1 = {
	"sfzjr1", "sfa", NULL, "1995",
	"Street Fighter Zero (950627 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Sfzjr1RomInfo, Sfzjr1RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSfzjr2 = {
	"sfzjr2", "sfa", NULL, "1995",
	"Street Fighter Zero (950605 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Sfzjr2RomInfo, Sfzjr2RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSfzh = {
	"sfzh", "sfa", NULL, "1995",
	"Street Fighter Zero (950627 Hispanic)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, SfzhRomInfo, SfzhRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSfzb = {
	"sfzb", "sfa", NULL, "1995",
	"Street Fighter Zero (951109 Brazil)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, SfzbRomInfo, SfzbRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSfzbr1 = {
	"sfzbr1", "sfa", NULL, "1995",
	"Street Fighter Zero (950727 Brazil)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Sfzbr1RomInfo, Sfzbr1RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
