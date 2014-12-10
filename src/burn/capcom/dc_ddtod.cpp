#include "cps.h"

static struct BurnInputInfo DrvInputList[] =
{
  {"P1 Coin"       , BIT_DIGITAL, CpsInp020+4, "p1 coin"  },
  {"P1 Start"      , BIT_DIGITAL, CpsInp020+0, "p1 start" },
  {"P1 Up"         , BIT_DIGITAL, CpsInp001+3, "p1 up"    },
  {"P1 Down"       , BIT_DIGITAL, CpsInp001+2, "p1 down"  },
  {"P1 Left"       , BIT_DIGITAL, CpsInp001+1, "p1 left"  },
  {"P1 Right"      , BIT_DIGITAL, CpsInp001+0, "p1 right" },
  {"P1 Attack"     , BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},
  {"P1 Jump"       , BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},
  {"P1 Use"        , BIT_DIGITAL, CpsInp001+6, "p1 fire 3"},
  {"P1 Select"     , BIT_DIGITAL, CpsInp001+7, "p1 fire 4"},

  {"P2 Coin"       , BIT_DIGITAL, CpsInp020+5, "p2 coin"  },
  {"P2 Start"      , BIT_DIGITAL, CpsInp020+1, "p2 start" },
  {"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"    },
  {"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"  },
  {"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"  },
  {"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right" },
  {"P2 Attack"     , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
  {"P2 Jump"       , BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},
  {"P2 Use"        , BIT_DIGITAL, CpsInp000+6, "p2 fire 3"},
  {"P2 Select"     , BIT_DIGITAL, CpsInp000+7, "p2 fire 4"},

  {"P3 Coin"       , BIT_DIGITAL, CpsInp020+6, "p3 coin"  },
  {"P3 Start"      , BIT_DIGITAL, CpsInp020+2, "p3 start" },
  {"P3 Up"         , BIT_DIGITAL, CpsInp011+3, "p3 up"    },
  {"P3 Down"       , BIT_DIGITAL, CpsInp011+2, "p3 down"  },
  {"P3 Left"       , BIT_DIGITAL, CpsInp011+1, "p3 left"  },
  {"P3 Right"      , BIT_DIGITAL, CpsInp011+0, "p3 right" },
  {"P3 Attack"     , BIT_DIGITAL, CpsInp011+4, "p3 fire 1"},
  {"P3 Jump"       , BIT_DIGITAL, CpsInp011+5, "p3 fire 2"},
  {"P3 Use"        , BIT_DIGITAL, CpsInp011+6, "p3 fire 3"},
  {"P3 Select"     , BIT_DIGITAL, CpsInp011+7, "p3 fire 4"},

  {"P4 Coin"       , BIT_DIGITAL, CpsInp020+7, "p4 coin"  },
  {"P4 Start"      , BIT_DIGITAL, CpsInp020+3, "p4 start" },
  {"P4 Up"         , BIT_DIGITAL, CpsInp010+3, "p4 up"    },
  {"P4 Down"       , BIT_DIGITAL, CpsInp010+2, "p4 down"  },
  {"P4 Left"       , BIT_DIGITAL, CpsInp010+1, "p4 left"  },
  {"P4 Right"      , BIT_DIGITAL, CpsInp010+0, "p4 right" },
  {"P4 Attack"     , BIT_DIGITAL, CpsInp010+4, "p4 fire 1"},
  {"P4 Jump"       , BIT_DIGITAL, CpsInp010+5, "p4 fire 2"},
  {"P4 Use"        , BIT_DIGITAL, CpsInp010+6, "p4 fire 3"},
  {"P4 Select"     , BIT_DIGITAL, CpsInp010+7, "p4 fire 4"},

  {"Reset"         , BIT_DIGITAL, &CpsReset,   "reset"    },
  {"Diagnostic"    , BIT_DIGITAL, CpsInp021+1, "diag"     },
  {"Service"       , BIT_DIGITAL, CpsInp021+2, "service"  },
};

STDINPUTINFO(Drv);

static struct BurnRomInfo DdtodRomDesc[] = {
	{ "dade.03c",      0x80000, 0x8e73533d, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "dade.04c",      0x80000, 0x00c2e82e, 1 | BRF_ESS | BRF_PRG },
	{ "dade.05c",      0x80000, 0xea996008, 1 | BRF_ESS | BRF_PRG },
	{ "dad.06a",      0x80000, 0x6225495a, 1 | BRF_ESS | BRF_PRG },
	{ "dad.07a",      0x80000, 0xb3480ec3, 1 | BRF_ESS | BRF_PRG },

	{ "dad.13m",      0x200000, 0xda3cb7d6, 3 | BRF_GRA },			 // 8
	{ "dad.15m",      0x200000, 0x92b63172, 3 | BRF_GRA },
	{ "dad.17m",      0x200000, 0xb98757f5, 3 | BRF_GRA },
	{ "dad.19m",      0x200000, 0x8121ce46, 3 | BRF_GRA },
	{ "dad.14m",      0x100000, 0x837e6f3f, 3 | BRF_GRA },
	{ "dad.16m",      0x100000, 0xf0916bdb, 3 | BRF_GRA },
	{ "dad.18m",      0x100000, 0xcef393ef, 3 | BRF_GRA },
	{ "dad.20m",      0x100000, 0x8953fe9e, 3 | BRF_GRA },

	{ "dad.01",       0x020000, 0x3f5e2424, 4 | BRF_ESS | BRF_PRG }, // 16

	{ "dad.11m",      0x200000, 0x0c499b67, 5 | BRF_SND },
	{ "dad.12m",      0x200000, 0x2f0b5a4e, 5 | BRF_SND },
};


STD_ROM_PICK(Ddtod) STD_ROM_FN(Ddtod)

static struct BurnRomInfo Ddtodr1RomDesc[] = {
	{ "dade.03a",      0x80000, 0x665a035e, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "dade.04a",      0x80000, 0x02613207, 1 | BRF_ESS | BRF_PRG },
	{ "dade.05a",      0x80000, 0x36845996, 1 | BRF_ESS | BRF_PRG },
	{ "dad.06",        0x80000, 0x13aa3e56, 1 | BRF_ESS | BRF_PRG },
	{ "dad.07",        0x80000, 0x431cb6dd, 1 | BRF_ESS | BRF_PRG },
	
	{ "dad.13m",      0x200000, 0xda3cb7d6, 3 | BRF_GRA },			 // 8
	{ "dad.15m",      0x200000, 0x92b63172, 3 | BRF_GRA },
	{ "dad.17m",      0x200000, 0xb98757f5, 3 | BRF_GRA },
	{ "dad.19m",      0x200000, 0x8121ce46, 3 | BRF_GRA },
	{ "dad.14m",      0x100000, 0x837e6f3f, 3 | BRF_GRA },
	{ "dad.16m",      0x100000, 0xf0916bdb, 3 | BRF_GRA },
	{ "dad.18m",      0x100000, 0xcef393ef, 3 | BRF_GRA },
	{ "dad.20m",      0x100000, 0x8953fe9e, 3 | BRF_GRA },

	{ "dad.01",       0x020000, 0x3f5e2424, 4 | BRF_ESS | BRF_PRG }, // 16

	{ "dad.11m",      0x200000, 0x0c499b67, 5 | BRF_SND },
	{ "dad.12m",      0x200000, 0x2f0b5a4e, 5 | BRF_SND },
};


STD_ROM_PICK(Ddtodr1) STD_ROM_FN(Ddtodr1)

static struct BurnRomInfo DdtoduRomDesc[] = {
	{ "dadu.03b",      0x80000, 0xa519905f, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "dadu.04b",      0x80000, 0x52562d38, 1 | BRF_ESS | BRF_PRG },
	{ "dadu.05b",      0x80000, 0xee1cfbfe, 1 | BRF_ESS | BRF_PRG },
	{ "dad.06",        0x80000, 0x13aa3e56, 1 | BRF_ESS | BRF_PRG },
	{ "dad.07",        0x80000, 0x431cb6dd, 1 | BRF_ESS | BRF_PRG },

	{ "dad.13m",      0x200000, 0xda3cb7d6, 3 | BRF_GRA },			 // 8
	{ "dad.15m",      0x200000, 0x92b63172, 3 | BRF_GRA },
	{ "dad.17m",      0x200000, 0xb98757f5, 3 | BRF_GRA },
	{ "dad.19m",      0x200000, 0x8121ce46, 3 | BRF_GRA },
	{ "dad.14m",      0x100000, 0x837e6f3f, 3 | BRF_GRA },
	{ "dad.16m",      0x100000, 0xf0916bdb, 3 | BRF_GRA },
	{ "dad.18m",      0x100000, 0xcef393ef, 3 | BRF_GRA },
	{ "dad.20m",      0x100000, 0x8953fe9e, 3 | BRF_GRA },

	{ "dad.01",       0x020000, 0x3f5e2424, 4 | BRF_ESS | BRF_PRG }, // 16

	{ "dad.11m",      0x200000, 0x0c499b67, 5 | BRF_SND },
	{ "dad.12m",      0x200000, 0x2f0b5a4e, 5 | BRF_SND },
};


STD_ROM_PICK(Ddtodu) STD_ROM_FN(Ddtodu)

static struct BurnRomInfo Ddtodur1RomDesc[] = {
	{ "dadu.03a",      0x80000, 0x4413f177, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "dadu.04a",      0x80000, 0x168de230, 1 | BRF_ESS | BRF_PRG },
	{ "dadu.05a",      0x80000, 0x03d39e91, 1 | BRF_ESS | BRF_PRG },
	{ "dad.06",        0x80000, 0x13aa3e56, 1 | BRF_ESS | BRF_PRG },
	{ "dad.07",        0x80000, 0x431cb6dd, 1 | BRF_ESS | BRF_PRG },

	{ "dad.13m",      0x200000, 0xda3cb7d6, 3 | BRF_GRA },			 // 8
	{ "dad.15m",      0x200000, 0x92b63172, 3 | BRF_GRA },
	{ "dad.17m",      0x200000, 0xb98757f5, 3 | BRF_GRA },
	{ "dad.19m",      0x200000, 0x8121ce46, 3 | BRF_GRA },
	{ "dad.14m",      0x100000, 0x837e6f3f, 3 | BRF_GRA },
	{ "dad.16m",      0x100000, 0xf0916bdb, 3 | BRF_GRA },
	{ "dad.18m",      0x100000, 0xcef393ef, 3 | BRF_GRA },
	{ "dad.20m",      0x100000, 0x8953fe9e, 3 | BRF_GRA },

	{ "dad.01",       0x020000, 0x3f5e2424, 4 | BRF_ESS | BRF_PRG }, // 16

	{ "dad.11m",      0x200000, 0x0c499b67, 5 | BRF_SND },
	{ "dad.12m",      0x200000, 0x2f0b5a4e, 5 | BRF_SND },
};


STD_ROM_PICK(Ddtodur1) STD_ROM_FN(Ddtodur1)

static struct BurnRomInfo DdtodjRomDesc[] = {
	{ "dadj.03b",      0x80000, 0x87606b85, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "dadj.04b",      0x80000, 0x24d49575, 1 | BRF_ESS | BRF_PRG },
	{ "dadj.05b",      0x80000, 0x56ce51f7, 1 | BRF_ESS | BRF_PRG },
	{ "dad.06",        0x80000, 0x13aa3e56, 1 | BRF_ESS | BRF_PRG },
	{ "dad.07",        0x80000, 0x431cb6dd, 1 | BRF_ESS | BRF_PRG },

	{ "dad.13m",      0x200000, 0xda3cb7d6, 3 | BRF_GRA },			 // 8
	{ "dad.15m",      0x200000, 0x92b63172, 3 | BRF_GRA },
	{ "dad.17m",      0x200000, 0xb98757f5, 3 | BRF_GRA },
	{ "dad.19m",      0x200000, 0x8121ce46, 3 | BRF_GRA },
	{ "dad.14m",      0x100000, 0x837e6f3f, 3 | BRF_GRA },
	{ "dad.16m",      0x100000, 0xf0916bdb, 3 | BRF_GRA },
	{ "dad.18m",      0x100000, 0xcef393ef, 3 | BRF_GRA },
	{ "dad.20m",      0x100000, 0x8953fe9e, 3 | BRF_GRA },

	{ "dad.01",       0x020000, 0x3f5e2424, 4 | BRF_ESS | BRF_PRG }, // 16

	{ "dad.11m",      0x200000, 0x0c499b67, 5 | BRF_SND },
	{ "dad.12m",      0x200000, 0x2f0b5a4e, 5 | BRF_SND },
};


STD_ROM_PICK(Ddtodj) STD_ROM_FN(Ddtodj)

static struct BurnRomInfo Ddtodjr1RomDesc[] = {
	{ "dadj.03a",      0x80000, 0x711638dc, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "dadj.04a",      0x80000, 0x4869639c, 1 | BRF_ESS | BRF_PRG },
	{ "dadj.05a",      0x80000, 0x484c0efa, 1 | BRF_ESS | BRF_PRG },
	{ "dad.06",        0x80000, 0x13aa3e56, 1 | BRF_ESS | BRF_PRG },
	{ "dad.07",        0x80000, 0x431cb6dd, 1 | BRF_ESS | BRF_PRG },

	{ "dad.13m",      0x200000, 0xda3cb7d6, 3 | BRF_GRA },			 // 8
	{ "dad.15m",      0x200000, 0x92b63172, 3 | BRF_GRA },
	{ "dad.17m",      0x200000, 0xb98757f5, 3 | BRF_GRA },
	{ "dad.19m",      0x200000, 0x8121ce46, 3 | BRF_GRA },
	{ "dad.14m",      0x100000, 0x837e6f3f, 3 | BRF_GRA },
	{ "dad.16m",      0x100000, 0xf0916bdb, 3 | BRF_GRA },
	{ "dad.18m",      0x100000, 0xcef393ef, 3 | BRF_GRA },
	{ "dad.20m",      0x100000, 0x8953fe9e, 3 | BRF_GRA },

	{ "dad.01",       0x020000, 0x3f5e2424, 4 | BRF_ESS | BRF_PRG }, // 16

	{ "dad.11m",      0x200000, 0x0c499b67, 5 | BRF_SND },
	{ "dad.12m",      0x200000, 0x2f0b5a4e, 5 | BRF_SND },
};


STD_ROM_PICK(Ddtodjr1) STD_ROM_FN(Ddtodjr1)

static struct BurnRomInfo DdtodaRomDesc[] = {
	{ "dada.03a",      0x80000, 0xfc6f2dd7, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "dada.04a",      0x80000, 0xd4be4009, 1 | BRF_ESS | BRF_PRG },
	{ "dada.05a",      0x80000, 0x6712d1cf, 1 | BRF_ESS | BRF_PRG },
	{ "dad.06",        0x80000, 0x13aa3e56, 1 | BRF_ESS | BRF_PRG },
	{ "dad.07",        0x80000, 0x431cb6dd, 1 | BRF_ESS | BRF_PRG },

	{ "dad.13m",      0x200000, 0xda3cb7d6, 3 | BRF_GRA },			 // 8
	{ "dad.15m",      0x200000, 0x92b63172, 3 | BRF_GRA },
	{ "dad.17m",      0x200000, 0xb98757f5, 3 | BRF_GRA },
	{ "dad.19m",      0x200000, 0x8121ce46, 3 | BRF_GRA },
	{ "dad.14m",      0x100000, 0x837e6f3f, 3 | BRF_GRA },
	{ "dad.16m",      0x100000, 0xf0916bdb, 3 | BRF_GRA },
	{ "dad.18m",      0x100000, 0xcef393ef, 3 | BRF_GRA },
	{ "dad.20m",      0x100000, 0x8953fe9e, 3 | BRF_GRA },

	{ "dad.01",       0x020000, 0x3f5e2424, 4 | BRF_ESS | BRF_PRG }, // 16

	{ "dad.11m",      0x200000, 0x0c499b67, 5 | BRF_SND },
	{ "dad.12m",      0x200000, 0x2f0b5a4e, 5 | BRF_SND },
};


STD_ROM_PICK(Ddtoda) STD_ROM_FN(Ddtoda)

static struct BurnRomInfo DdtodhRomDesc[] = {
	{ "dadh.03b",      0x80000, 0xae0cb98e, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "dadh.04b",      0x80000, 0xb5774363, 1 | BRF_ESS | BRF_PRG },
	{ "dadh.05b",      0x80000, 0x6ce2a485, 1 | BRF_ESS | BRF_PRG },
	{ "dad.06",        0x80000, 0x13aa3e56, 1 | BRF_ESS | BRF_PRG },
	{ "dad.07",        0x80000, 0x431cb6dd, 1 | BRF_ESS | BRF_PRG },

	{ "dad.13m",      0x200000, 0xda3cb7d6, 3 | BRF_GRA },			 // 8
	{ "dad.15m",      0x200000, 0x92b63172, 3 | BRF_GRA },
	{ "dad.17m",      0x200000, 0xb98757f5, 3 | BRF_GRA },
	{ "dad.19m",      0x200000, 0x8121ce46, 3 | BRF_GRA },
	{ "dad.14m",      0x100000, 0x837e6f3f, 3 | BRF_GRA },
	{ "dad.16m",      0x100000, 0xf0916bdb, 3 | BRF_GRA },
	{ "dad.18m",      0x100000, 0xcef393ef, 3 | BRF_GRA },
	{ "dad.20m",      0x100000, 0x8953fe9e, 3 | BRF_GRA },

	{ "dad.01",       0x020000, 0x3f5e2424, 4 | BRF_ESS | BRF_PRG }, // 16

	{ "dad.11m",      0x200000, 0x0c499b67, 5 | BRF_SND },
	{ "dad.12m",      0x200000, 0x2f0b5a4e, 5 | BRF_SND },
};


STD_ROM_PICK(Ddtodh) STD_ROM_FN(Ddtodh)

struct BurnDriver BurnDrvCpsDdtod = {
	"ddtod", NULL, NULL, "1994",
	"Dungeons & Dragons - tower of doom (940412 Euro)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,4,HARDWARE_CAPCOM_CPS2,
	NULL, DdtodRomInfo, DdtodRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsDdtodr1 = {
	"ddtodr1", "ddtod", NULL, "1994",
	"Dungeons & Dragons - tower of doom (940113 Euro)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,4,HARDWARE_CAPCOM_CPS2,
	NULL, Ddtodr1RomInfo, Ddtodr1RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsDdtodu = {
	"ddtodu", "ddtod", NULL, "1994",
	"Dungeons & Dragons - tower of doom (940125 USA)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,4,HARDWARE_CAPCOM_CPS2,
	NULL, DdtoduRomInfo, DdtoduRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsDdtodur1 = {
	"ddtodur1", "ddtod", NULL, "1994",
	"Dungeons & Dragons - tower of doom (940113 USA)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,4,HARDWARE_CAPCOM_CPS2,
	NULL, Ddtodur1RomInfo, Ddtodur1RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsDdtodj = {
	"ddtodj", "ddtod", NULL, "1994",
	"Dungeons & Dragons - tower of doom (940125 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,4,HARDWARE_CAPCOM_CPS2,
	NULL, DdtodjRomInfo, DdtodjRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsDdtodjr1 = {
	"ddtodjr1", "ddtod", NULL, "1994",
	"Dungeons & Dragons - tower of doom (940113 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,4,HARDWARE_CAPCOM_CPS2,
	NULL, Ddtodjr1RomInfo, Ddtodjr1RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsDdtoda = {
	"ddtoda", "ddtod", NULL, "1994",
	"Dungeons & Dragons - tower of doom (940113 Asia)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,4,HARDWARE_CAPCOM_CPS2,
	NULL, DdtodaRomInfo, DdtodaRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsDdtodh = {
	"ddtodh", "ddtod", NULL, "1994",
	"Dungeons & Dragons - tower of doom (940125 Hispanic)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,4,HARDWARE_CAPCOM_CPS2,
	NULL, DdtodhRomInfo, DdtodhRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
