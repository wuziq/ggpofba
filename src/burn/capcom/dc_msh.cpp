#include "cps.h"

STDINPUTINFOSPEC(Drv, CpsFsi);

static struct BurnRomInfo MshRomDesc[] = {
	{ "mshe.03e",      0x80000, 0xbd951414, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "mshe.04e",      0x80000, 0x19dd42f2, 1 | BRF_ESS | BRF_PRG },
	{ "msh.05",        0x80000, 0x6a091b9e, 1 | BRF_ESS | BRF_PRG },
	{ "msh.06b",       0x80000, 0x803e3fa4, 1 | BRF_ESS | BRF_PRG },
	{ "msh.07a",       0x80000, 0xc45f8e27, 1 | BRF_ESS | BRF_PRG },
	{ "msh.08a",       0x80000, 0x9ca6f12c, 1 | BRF_ESS | BRF_PRG },
	{ "msh.09a",       0x80000, 0x82ec27af, 1 | BRF_ESS | BRF_PRG },
	{ "msh.10b",       0x80000, 0x8d931196, 1 | BRF_ESS | BRF_PRG },

	{ "msh.13m",      0x400000, 0x09d14566, 3 | BRF_GRA },			 // 10
	{ "msh.15m",      0x400000, 0xee962057, 3 | BRF_GRA },
	{ "msh.17m",      0x400000, 0x604ece14, 3 | BRF_GRA },
	{ "msh.19m",      0x400000, 0x94a731e8, 3 | BRF_GRA },
	{ "msh.14m",      0x400000, 0x4197973e, 3 | BRF_GRA },
	{ "msh.16m",      0x400000, 0x438da4a0, 3 | BRF_GRA },
	{ "msh.18m",      0x400000, 0x4db92d94, 3 | BRF_GRA },
	{ "msh.20m",      0x400000, 0xa2b0c6c0, 3 | BRF_GRA },

	{ "msh.01",       0x020000, 0xc976e6f9, 4 | BRF_ESS | BRF_PRG }, // 18
	{ "msh.02",       0x020000, 0xce67d0d9, 4 | BRF_ESS | BRF_PRG },

	{ "msh.11m",      0x200000, 0x37ac6d30, 5 | BRF_SND },
	{ "msh.12m",      0x200000, 0xde092570, 5 | BRF_SND },
};


STD_ROM_PICK(Msh) STD_ROM_FN(Msh)

static struct BurnRomInfo MshuRomDesc[] = {
	{ "mshu.03",       0x80000, 0xd2805bdd, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "mshu.04",       0x80000, 0x743f96ff, 1 | BRF_ESS | BRF_PRG },
	{ "msh.05",        0x80000, 0x6a091b9e, 1 | BRF_ESS | BRF_PRG },
	{ "msh.06b",       0x80000, 0x803e3fa4, 1 | BRF_ESS | BRF_PRG },
	{ "msh.07a",       0x80000, 0xc45f8e27, 1 | BRF_ESS | BRF_PRG },
	{ "msh.08a",       0x80000, 0x9ca6f12c, 1 | BRF_ESS | BRF_PRG },
	{ "msh.09a",       0x80000, 0x82ec27af, 1 | BRF_ESS | BRF_PRG },
	{ "msh.10b",       0x80000, 0x8d931196, 1 | BRF_ESS | BRF_PRG },

	{ "msh.13m",      0x400000, 0x09d14566, 3 | BRF_GRA },			 // 10
	{ "msh.15m",      0x400000, 0xee962057, 3 | BRF_GRA },
	{ "msh.17m",      0x400000, 0x604ece14, 3 | BRF_GRA },
	{ "msh.19m",      0x400000, 0x94a731e8, 3 | BRF_GRA },
	{ "msh.14m",      0x400000, 0x4197973e, 3 | BRF_GRA },
	{ "msh.16m",      0x400000, 0x438da4a0, 3 | BRF_GRA },
	{ "msh.18m",      0x400000, 0x4db92d94, 3 | BRF_GRA },
	{ "msh.20m",      0x400000, 0xa2b0c6c0, 3 | BRF_GRA },

	{ "msh.01",       0x020000, 0xc976e6f9, 4 | BRF_ESS | BRF_PRG }, // 18
	{ "msh.02",       0x020000, 0xce67d0d9, 4 | BRF_ESS | BRF_PRG },

	{ "msh.11m",      0x200000, 0x37ac6d30, 5 | BRF_SND },
	{ "msh.12m",      0x200000, 0xde092570, 5 | BRF_SND },
};


STD_ROM_PICK(Mshu) STD_ROM_FN(Mshu)

static struct BurnRomInfo MshjRomDesc[] = {
	{ "mshj.03g",      0x80000, 0x261f4091, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "mshj.04g",      0x80000, 0x61d791c6, 1 | BRF_ESS | BRF_PRG },
	{ "msh.05a",       0x80000, 0xf37539e6, 1 | BRF_ESS | BRF_PRG },
	{ "msh.06b",       0x80000, 0x803e3fa4, 1 | BRF_ESS | BRF_PRG },
	{ "msh.07a",       0x80000, 0xc45f8e27, 1 | BRF_ESS | BRF_PRG },
	{ "msh.08a",       0x80000, 0x9ca6f12c, 1 | BRF_ESS | BRF_PRG },
	{ "msh.09a",       0x80000, 0x82ec27af, 1 | BRF_ESS | BRF_PRG },
	{ "msh.10b",       0x80000, 0x8d931196, 1 | BRF_ESS | BRF_PRG },

	{ "msh.13m",      0x400000, 0x09d14566, 3 | BRF_GRA },			 // 10
	{ "msh.15m",      0x400000, 0xee962057, 3 | BRF_GRA },
	{ "msh.17m",      0x400000, 0x604ece14, 3 | BRF_GRA },
	{ "msh.19m",      0x400000, 0x94a731e8, 3 | BRF_GRA },
	{ "msh.14m",      0x400000, 0x4197973e, 3 | BRF_GRA },
	{ "msh.16m",      0x400000, 0x438da4a0, 3 | BRF_GRA },
	{ "msh.18m",      0x400000, 0x4db92d94, 3 | BRF_GRA },
	{ "msh.20m",      0x400000, 0xa2b0c6c0, 3 | BRF_GRA },

	{ "msh.01",       0x020000, 0xc976e6f9, 4 | BRF_ESS | BRF_PRG }, // 18
	{ "msh.02",       0x020000, 0xce67d0d9, 4 | BRF_ESS | BRF_PRG },

	{ "msh.11m",      0x200000, 0x37ac6d30, 5 | BRF_SND },
	{ "msh.12m",      0x200000, 0xde092570, 5 | BRF_SND },
};


STD_ROM_PICK(Mshj) STD_ROM_FN(Mshj)

static struct BurnRomInfo Mshjr1RomDesc[] = {
	{ "mshj.03f",      0x80000, 0xff172fd2, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "mshj.04f",      0x80000, 0xebbb205a, 1 | BRF_ESS | BRF_PRG },
	{ "msh.05",        0x80000, 0x6a091b9e, 1 | BRF_ESS | BRF_PRG },
	{ "msh.06b",       0x80000, 0x803e3fa4, 1 | BRF_ESS | BRF_PRG },
	{ "msh.07a",       0x80000, 0xc45f8e27, 1 | BRF_ESS | BRF_PRG },
	{ "msh.08a",       0x80000, 0x9ca6f12c, 1 | BRF_ESS | BRF_PRG },
	{ "msh.09a",       0x80000, 0x82ec27af, 1 | BRF_ESS | BRF_PRG },
	{ "msh.10b",       0x80000, 0x8d931196, 1 | BRF_ESS | BRF_PRG },

	{ "msh.13m",      0x400000, 0x09d14566, 3 | BRF_GRA },			 // 10
	{ "msh.15m",      0x400000, 0xee962057, 3 | BRF_GRA },
	{ "msh.17m",      0x400000, 0x604ece14, 3 | BRF_GRA },
	{ "msh.19m",      0x400000, 0x94a731e8, 3 | BRF_GRA },
	{ "msh.14m",      0x400000, 0x4197973e, 3 | BRF_GRA },
	{ "msh.16m",      0x400000, 0x438da4a0, 3 | BRF_GRA },
	{ "msh.18m",      0x400000, 0x4db92d94, 3 | BRF_GRA },
	{ "msh.20m",      0x400000, 0xa2b0c6c0, 3 | BRF_GRA },

	{ "msh.01",       0x020000, 0xc976e6f9, 4 | BRF_ESS | BRF_PRG }, // 18
	{ "msh.02",       0x020000, 0xce67d0d9, 4 | BRF_ESS | BRF_PRG },

	{ "msh.11m",      0x200000, 0x37ac6d30, 5 | BRF_SND },
	{ "msh.12m",      0x200000, 0xde092570, 5 | BRF_SND },
};


STD_ROM_PICK(Mshjr1) STD_ROM_FN(Mshjr1)

static struct BurnRomInfo MshaRomDesc[] = {
	{ "msha.03e",      0x80000, 0xec84ec44, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "msha.04e",      0x80000, 0x098b8503, 1 | BRF_ESS | BRF_PRG },
	{ "msh.05",        0x80000, 0x6a091b9e, 1 | BRF_ESS | BRF_PRG },
	{ "msh.06b",       0x80000, 0x803e3fa4, 1 | BRF_ESS | BRF_PRG },
	{ "msh.07a",       0x80000, 0xc45f8e27, 1 | BRF_ESS | BRF_PRG },
	{ "msh.08a",       0x80000, 0x9ca6f12c, 1 | BRF_ESS | BRF_PRG },
	{ "msh.09a",       0x80000, 0x82ec27af, 1 | BRF_ESS | BRF_PRG },
	{ "msh.10b",       0x80000, 0x8d931196, 1 | BRF_ESS | BRF_PRG },

	{ "msh.13m",      0x400000, 0x09d14566, 3 | BRF_GRA },			 // 10
	{ "msh.15m",      0x400000, 0xee962057, 3 | BRF_GRA },
	{ "msh.17m",      0x400000, 0x604ece14, 3 | BRF_GRA },
	{ "msh.19m",      0x400000, 0x94a731e8, 3 | BRF_GRA },
	{ "msh.14m",      0x400000, 0x4197973e, 3 | BRF_GRA },
	{ "msh.16m",      0x400000, 0x438da4a0, 3 | BRF_GRA },
	{ "msh.18m",      0x400000, 0x4db92d94, 3 | BRF_GRA },
	{ "msh.20m",      0x400000, 0xa2b0c6c0, 3 | BRF_GRA },

	{ "msh.01",       0x020000, 0xc976e6f9, 4 | BRF_ESS | BRF_PRG }, // 18
	{ "msh.02",       0x020000, 0xce67d0d9, 4 | BRF_ESS | BRF_PRG },

	{ "msh.11m",      0x200000, 0x37ac6d30, 5 | BRF_SND },
	{ "msh.12m",      0x200000, 0xde092570, 5 | BRF_SND },
};


STD_ROM_PICK(Msha) STD_ROM_FN(Msha)

static struct BurnRomInfo MshhRomDesc[] = {
	{ "mshh.03c",      0x80000, 0x8d84b0fa, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "mshh.04c",      0x80000, 0xd638f601, 1 | BRF_ESS | BRF_PRG },
	{ "msh.05a",       0x80000, 0xf37539e6, 1 | BRF_ESS | BRF_PRG },
	{ "msh.06b",       0x80000, 0x803e3fa4, 1 | BRF_ESS | BRF_PRG },
	{ "msh.07a",       0x80000, 0xc45f8e27, 1 | BRF_ESS | BRF_PRG },
	{ "msh.08a",       0x80000, 0x9ca6f12c, 1 | BRF_ESS | BRF_PRG },
	{ "msh.09a",       0x80000, 0x82ec27af, 1 | BRF_ESS | BRF_PRG },
	{ "msh.10b",       0x80000, 0x8d931196, 1 | BRF_ESS | BRF_PRG },

	{ "msh.13m",      0x400000, 0x09d14566, 3 | BRF_GRA },			 // 10
	{ "msh.15m",      0x400000, 0xee962057, 3 | BRF_GRA },
	{ "msh.17m",      0x400000, 0x604ece14, 3 | BRF_GRA },
	{ "msh.19m",      0x400000, 0x94a731e8, 3 | BRF_GRA },
	{ "msh.14m",      0x400000, 0x4197973e, 3 | BRF_GRA },
	{ "msh.16m",      0x400000, 0x438da4a0, 3 | BRF_GRA },
	{ "msh.18m",      0x400000, 0x4db92d94, 3 | BRF_GRA },
	{ "msh.20m",      0x400000, 0xa2b0c6c0, 3 | BRF_GRA },

	{ "msh.01",       0x020000, 0xc976e6f9, 4 | BRF_ESS | BRF_PRG }, // 18
	{ "msh.02",       0x020000, 0xce67d0d9, 4 | BRF_ESS | BRF_PRG },

	{ "msh.11m",      0x200000, 0x37ac6d30, 5 | BRF_SND },
	{ "msh.12m",      0x200000, 0xde092570, 5 | BRF_SND },
};


STD_ROM_PICK(Mshh) STD_ROM_FN(Mshh)

static struct BurnRomInfo MshbRomDesc[] = {
	{ "mshb.03c",      0x80000, 0x19697f74, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "mshb.04c",      0x80000, 0x95317a6f, 1 | BRF_ESS | BRF_PRG },
	{ "msh.05a",       0x80000, 0xf37539e6, 1 | BRF_ESS | BRF_PRG },
	{ "msh.06b",       0x80000, 0x803e3fa4, 1 | BRF_ESS | BRF_PRG },
	{ "msh.07a",       0x80000, 0xc45f8e27, 1 | BRF_ESS | BRF_PRG },
	{ "msh.08a",       0x80000, 0x9ca6f12c, 1 | BRF_ESS | BRF_PRG },
	{ "msh.09a",       0x80000, 0x82ec27af, 1 | BRF_ESS | BRF_PRG },
	{ "msh.10b",       0x80000, 0x8d931196, 1 | BRF_ESS | BRF_PRG },

	{ "msh.13m",      0x400000, 0x09d14566, 3 | BRF_GRA },			 // 10
	{ "msh.15m",      0x400000, 0xee962057, 3 | BRF_GRA },
	{ "msh.17m",      0x400000, 0x604ece14, 3 | BRF_GRA },
	{ "msh.19m",      0x400000, 0x94a731e8, 3 | BRF_GRA },
	{ "msh.14m",      0x400000, 0x4197973e, 3 | BRF_GRA },
	{ "msh.16m",      0x400000, 0x438da4a0, 3 | BRF_GRA },
	{ "msh.18m",      0x400000, 0x4db92d94, 3 | BRF_GRA },
	{ "msh.20m",      0x400000, 0xa2b0c6c0, 3 | BRF_GRA },


	{ "msh.01",       0x020000, 0xc976e6f9, 4 | BRF_ESS | BRF_PRG }, // 18
	{ "msh.02",       0x020000, 0xce67d0d9, 4 | BRF_ESS | BRF_PRG },

	{ "msh.11m",      0x200000, 0x37ac6d30, 5 | BRF_SND },
	{ "msh.12m",      0x200000, 0xde092570, 5 | BRF_SND },
};


STD_ROM_PICK(Mshb) STD_ROM_FN(Mshb)

struct BurnDriver BurnDrvCpsMsh = {
	"msh", NULL, NULL, "1995",
	"Marvel Super Heroes (951024 Euro)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS2,
	NULL, MshRomInfo, MshRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsMshu = {
	"mshu", "msh", NULL, "1995",
	"Marvel Super Heroes (951024 USA)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, MshuRomInfo, MshuRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsMshj = {
	"mshj", "msh", NULL, "1995",
	"Marvel Super Heroes (951117 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, MshjRomInfo, MshjRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsMshjr1 = {
	"mshjr1", "msh", NULL, "1995",
	"Marvel Super Heroes (951024 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Mshjr1RomInfo, Mshjr1RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsMsha = {
	"msha", "msh", NULL, "1995",
	"Marvel Super Heroes (951024 Asia)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, MshaRomInfo, MshaRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsMshh = {
	"mshh", "msh", NULL, "1995",
	"Marvel Super Heroes (951117 Hispanic)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, MshhRomInfo, MshhRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsMshb = {
	"mshb", "msh", NULL, "1995",
	"Marvel Super Heroes (951117 Brazil)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, MshbRomInfo, MshbRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
