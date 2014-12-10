#include "cps.h"

STDINPUTINFOSPEC(Drv, CpsFsi);

static struct BurnRomInfo NwarrRomDesc[] = {
	{ "vphu.03f",     0x080000, 0x85d6a359, 1 | BRF_ESS | BRF_PRG },
	{ "vphu.04c",     0x080000, 0xcb7fce77, 1 | BRF_ESS | BRF_PRG },
	{ "vphu.05e",     0x080000, 0xe08f2bba, 1 | BRF_ESS | BRF_PRG },
	{ "vphu.06c",     0x080000, 0x08c04cdb, 1 | BRF_ESS | BRF_PRG },
	{ "vphu.07b",     0x080000, 0xb5a5ab19, 1 | BRF_ESS | BRF_PRG },
	{ "vphu.08b",     0x080000, 0x51bb20fb, 1 | BRF_ESS | BRF_PRG },
	{ "vphu.09b",     0x080000, 0x41a64205, 1 | BRF_ESS | BRF_PRG },
	{ "vphu.10b",     0x080000, 0x2b1d43ae, 1 | BRF_ESS | BRF_PRG },

	{ "vph.13m",      0x400000, 0xc51baf99, 3 | BRF_GRA },
	{ "vph.15m",      0x400000, 0x3ce83c77, 3 | BRF_GRA },
	{ "vph.17m",      0x400000, 0x4f2408e0, 3 | BRF_GRA },
	{ "vph.19m",      0x400000, 0x9ff60250, 3 | BRF_GRA },
	{ "vph.14m",      0x400000, 0x7a0e1add, 3 | BRF_GRA },
	{ "vph.16m",      0x400000, 0x2f41ca75, 3 | BRF_GRA },
	{ "vph.18m",      0x400000, 0x64498eed, 3 | BRF_GRA },
	{ "vph.20m",      0x400000, 0x17f2433f, 3 | BRF_GRA },

	{ "vph.01",       0x020000, 0x5045dcac, 4 | BRF_ESS | BRF_PRG },
	{ "vph.02",       0x020000, 0x86b60e59, 4 | BRF_ESS | BRF_PRG },

	{ "vph.11m",      0x200000, 0xe1837d33, 5 | BRF_SND },
	{ "vph.12m",      0x200000, 0xfbd3cd90, 5 | BRF_SND },
};


STD_ROM_PICK(Nwarr) STD_ROM_FN(Nwarr)

static struct BurnRomInfo NwarrhRomDesc[] = {
	{ "vphh.03d",     0x080000, 0x6029c7be, 1 | BRF_ESS | BRF_PRG },
	{ "vphh.04a",     0x080000, 0xd26625ee, 1 | BRF_ESS | BRF_PRG },
	{ "vphh.05c",     0x080000, 0x73ee0b8a, 1 | BRF_ESS | BRF_PRG },
	{ "vphh.06a",     0x080000, 0xa5b3a50a, 1 | BRF_ESS | BRF_PRG },
	{ "vphh.07",      0x080000, 0x5fc2bdc1, 1 | BRF_ESS | BRF_PRG },
	{ "vphh.08",      0x080000, 0xe65588d9, 1 | BRF_ESS | BRF_PRG },
	{ "vphh.09",      0x080000, 0xa2ce6d63, 1 | BRF_ESS | BRF_PRG },
	{ "vphh.10",      0x080000, 0xe2f4f4b9, 1 | BRF_ESS | BRF_PRG },

	{ "vph.13m",      0x400000, 0xc51baf99, 3 | BRF_GRA },
	{ "vph.15m",      0x400000, 0x3ce83c77, 3 | BRF_GRA },
	{ "vph.17m",      0x400000, 0x4f2408e0, 3 | BRF_GRA },
	{ "vph.19m",      0x400000, 0x9ff60250, 3 | BRF_GRA },
	{ "vph.14m",      0x400000, 0x7a0e1add, 3 | BRF_GRA },
	{ "vph.16m",      0x400000, 0x2f41ca75, 3 | BRF_GRA },
	{ "vph.18m",      0x400000, 0x64498eed, 3 | BRF_GRA },
	{ "vph.20m",      0x400000, 0x17f2433f, 3 | BRF_GRA },

	{ "vph.01",       0x020000, 0x5045dcac, 4 | BRF_ESS | BRF_PRG },
	{ "vph.02",       0x020000, 0x86b60e59, 4 | BRF_ESS | BRF_PRG },

	{ "vph.11m",      0x200000, 0xe1837d33, 5 | BRF_SND },
	{ "vph.12m",      0x200000, 0xfbd3cd90, 5 | BRF_SND },
};


STD_ROM_PICK(Nwarrh) STD_ROM_FN(Nwarrh)

static struct BurnRomInfo NwarrbRomDesc[] = {
	{ "vphb.03d",     0x080000, 0x3a426d3f, 1 | BRF_ESS | BRF_PRG },
	{ "vphb.04a",     0x080000, 0x51c4bb2f, 1 | BRF_ESS | BRF_PRG },
	{ "vphb.05c",     0x080000, 0xac44d997, 1 | BRF_ESS | BRF_PRG },
	{ "vphb.06a",     0x080000, 0x5072a5fe, 1 | BRF_ESS | BRF_PRG },
	{ "vphb.07",      0x080000, 0x9b355192, 1 | BRF_ESS | BRF_PRG },
	{ "vphb.08",      0x080000, 0x42220f84, 1 | BRF_ESS | BRF_PRG },
	{ "vphb.09",      0x080000, 0x029e015d, 1 | BRF_ESS | BRF_PRG },
	{ "vphb.10",      0x080000, 0x37b3ce37, 1 | BRF_ESS | BRF_PRG },

	{ "vph.13m",      0x400000, 0xc51baf99, 3 | BRF_GRA },
	{ "vph.15m",      0x400000, 0x3ce83c77, 3 | BRF_GRA },
	{ "vph.17m",      0x400000, 0x4f2408e0, 3 | BRF_GRA },
	{ "vph.19m",      0x400000, 0x9ff60250, 3 | BRF_GRA },
	{ "vph.14m",      0x400000, 0x7a0e1add, 3 | BRF_GRA },
	{ "vph.16m",      0x400000, 0x2f41ca75, 3 | BRF_GRA },
	{ "vph.18m",      0x400000, 0x64498eed, 3 | BRF_GRA },
	{ "vph.20m",      0x400000, 0x17f2433f, 3 | BRF_GRA },

	{ "vph.01",       0x020000, 0x5045dcac, 4 | BRF_ESS | BRF_PRG },
	{ "vph.02",       0x020000, 0x86b60e59, 4 | BRF_ESS | BRF_PRG },

	{ "vph.11m",      0x200000, 0xe1837d33, 5 | BRF_SND },
	{ "vph.12m",      0x200000, 0xfbd3cd90, 5 | BRF_SND },
};


STD_ROM_PICK(Nwarrb) STD_ROM_FN(Nwarrb)

static struct BurnRomInfo VhuntjRomDesc[] = {
	{ "vphj.03f",     0x080000, 0x3de2e333, 1 | BRF_ESS | BRF_PRG },
	{ "vphj.04c",     0x080000, 0xc95cf304, 1 | BRF_ESS | BRF_PRG },
	{ "vphj.05d",     0x080000, 0x50de5ddd, 1 | BRF_ESS | BRF_PRG },
	{ "vphj.06c",     0x080000, 0xac3bd3d5, 1 | BRF_ESS | BRF_PRG },
	{ "vphj.07b",     0x080000, 0x0761309f, 1 | BRF_ESS | BRF_PRG },
	{ "vphj.08b",     0x080000, 0x5a5c2bf5, 1 | BRF_ESS | BRF_PRG },
	{ "vphj.09b",     0x080000, 0x823d6d99, 1 | BRF_ESS | BRF_PRG },
	{ "vphj.10b",     0x080000, 0x32c7d8f0, 1 | BRF_ESS | BRF_PRG },

	{ "vph.13m",      0x400000, 0xc51baf99, 3 | BRF_GRA },
	{ "vph.15m",      0x400000, 0x3ce83c77, 3 | BRF_GRA },
	{ "vph.17m",      0x400000, 0x4f2408e0, 3 | BRF_GRA },
	{ "vph.19m",      0x400000, 0x9ff60250, 3 | BRF_GRA },
	{ "vph.14m",      0x400000, 0x7a0e1add, 3 | BRF_GRA },
	{ "vph.16m",      0x400000, 0x2f41ca75, 3 | BRF_GRA },
	{ "vph.18m",      0x400000, 0x64498eed, 3 | BRF_GRA },
	{ "vph.20m",      0x400000, 0x17f2433f, 3 | BRF_GRA },

	{ "vph.01",       0x020000, 0x5045dcac, 4 | BRF_ESS | BRF_PRG },
	{ "vph.02",       0x020000, 0x86b60e59, 4 | BRF_ESS | BRF_PRG },

	{ "vph.11m",      0x200000, 0xe1837d33, 5 | BRF_SND },
	{ "vph.12m",      0x200000, 0xfbd3cd90, 5 | BRF_SND },
};


STD_ROM_PICK(Vhuntj) STD_ROM_FN(Vhuntj)

static struct BurnRomInfo Vhuntjr1RomDesc[] = {
	{ "vphj.03c",     0x080000, 0x606b682a, 1 | BRF_ESS | BRF_PRG },
	{ "vphj.04b",     0x080000, 0xa3b40393, 1 | BRF_ESS | BRF_PRG },
	{ "vphj.05b",     0x080000, 0xfccd5558, 1 | BRF_ESS | BRF_PRG },
	{ "vphj.06b",     0x080000, 0x07e10a73, 1 | BRF_ESS | BRF_PRG },
	{ "vphj.07b",     0x080000, 0x0761309f, 1 | BRF_ESS | BRF_PRG },
	{ "vphj.08b",     0x080000, 0x5a5c2bf5, 1 | BRF_ESS | BRF_PRG },
	{ "vphj.09b",     0x080000, 0x823d6d99, 1 | BRF_ESS | BRF_PRG },
	{ "vphj.10b",     0x080000, 0x32c7d8f0, 1 | BRF_ESS | BRF_PRG },

	{ "vph.13m",      0x400000, 0xc51baf99, 3 | BRF_GRA },
	{ "vph.15m",      0x400000, 0x3ce83c77, 3 | BRF_GRA },
	{ "vph.17m",      0x400000, 0x4f2408e0, 3 | BRF_GRA },
	{ "vph.19m",      0x400000, 0x9ff60250, 3 | BRF_GRA },
	{ "vph.14m",      0x400000, 0x7a0e1add, 3 | BRF_GRA },
	{ "vph.16m",      0x400000, 0x2f41ca75, 3 | BRF_GRA },
	{ "vph.18m",      0x400000, 0x64498eed, 3 | BRF_GRA },
	{ "vph.20m",      0x400000, 0x17f2433f, 3 | BRF_GRA },

	{ "vph.01",       0x020000, 0x5045dcac, 4 | BRF_ESS | BRF_PRG },
	{ "vph.02",       0x020000, 0x86b60e59, 4 | BRF_ESS | BRF_PRG },

	{ "vph.11m",      0x200000, 0xe1837d33, 5 | BRF_SND },
	{ "vph.12m",      0x200000, 0xfbd3cd90, 5 | BRF_SND },
};


STD_ROM_PICK(Vhuntjr1) STD_ROM_FN(Vhuntjr1)

static struct BurnRomInfo Vhuntjr2RomDesc[] = {
	{ "vphj.03b",     0x080000, 0x679c3fa9, 1 | BRF_ESS | BRF_PRG },
	{ "vphj.04a",     0x080000, 0xeb6e71e4, 1 | BRF_ESS | BRF_PRG },
	{ "vphj.05a",     0x080000, 0xeaf634ea, 1 | BRF_ESS | BRF_PRG },
	{ "vphj.06a",     0x080000, 0xb70cc6be, 1 | BRF_ESS | BRF_PRG },
	{ "vphj.07a",     0x080000, 0x46ab907d, 1 | BRF_ESS | BRF_PRG },
	{ "vphj.08a",     0x080000, 0x1c00355e, 1 | BRF_ESS | BRF_PRG },
	{ "vphj.09a",     0x080000, 0x026e6f82, 1 | BRF_ESS | BRF_PRG },
	{ "vphj.10a",     0x080000, 0xaadfb3ea, 1 | BRF_ESS | BRF_PRG },

	{ "vph.13m",      0x400000, 0xc51baf99, 3 | BRF_GRA },
	{ "vph.15m",      0x400000, 0x3ce83c77, 3 | BRF_GRA },
	{ "vph.17m",      0x400000, 0x4f2408e0, 3 | BRF_GRA },
	{ "vph.19m",      0x400000, 0x9ff60250, 3 | BRF_GRA },
	{ "vph.14m",      0x400000, 0x7a0e1add, 3 | BRF_GRA },
	{ "vph.16m",      0x400000, 0x2f41ca75, 3 | BRF_GRA },
	{ "vph.18m",      0x400000, 0x64498eed, 3 | BRF_GRA },
	{ "vph.20m",      0x400000, 0x17f2433f, 3 | BRF_GRA },

	{ "vph.01",       0x020000, 0x5045dcac, 4 | BRF_ESS | BRF_PRG },
	{ "vph.02",       0x020000, 0x86b60e59, 4 | BRF_ESS | BRF_PRG },

	{ "vph.11m",      0x200000, 0xe1837d33, 5 | BRF_SND },
	{ "vph.12m",      0x200000, 0xfbd3cd90, 5 | BRF_SND },
};


STD_ROM_PICK(Vhuntjr2) STD_ROM_FN(Vhuntjr2)

struct BurnDriver BurnDrvCpsNwarr = {
	"nwarr", NULL, NULL, "1995",
	"Night Warriors - darkstalkers' revenge (950406 USA)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS2,
	NULL, NwarrRomInfo, NwarrRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsNwarrh = {
	"nwarrh", "nwarr", NULL, "1995",
	"Night Warriors - darkstalkers' revenge (950403 Hispanic)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, NwarrhRomInfo, NwarrhRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsNwarrb = {
	"nwarrb", "nwarr", NULL, "1995",
	"Night Warriors - darkstalkers' revenge (950403 Brazil)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, NwarrbRomInfo, NwarrbRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsVhuntj = {
	"vhuntj", "nwarr", NULL, "1995",
	"Vampire Hunter - darkstalkers' revenge (950316 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, VhuntjRomInfo, VhuntjRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsVhuntjr1 = {
	"vhuntjr1", "nwarr", NULL, "1995",
	"Vampire Hunter - darkstalkers' revenge (950307 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Vhuntjr1RomInfo, Vhuntjr1RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsVhuntjr2 = {
	"vhuntjr2", "nwarr", NULL, "1995",
	"Vampire Hunter - darkstalkers' revenge (950302 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Vhuntjr2RomInfo, Vhuntjr2RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
