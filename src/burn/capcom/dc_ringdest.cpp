// Saturday Night Slammasters II

#include "cps.h"

static struct BurnInputInfo DrvInputList[] =
{
  {"P1 Coin"        , BIT_DIGITAL, CpsInp020+4, "p1 coin"},
  {"P1 Start"       , BIT_DIGITAL, CpsInp020+0, "p1 start"},
  {"P1 Up"          , BIT_DIGITAL, CpsInp001+3, "p1 up"},
  {"P1 Down"        , BIT_DIGITAL, CpsInp001+2, "p1 down"},
  {"P1 Left"        , BIT_DIGITAL, CpsInp001+1, "p1 left"},
  {"P1 Right"       , BIT_DIGITAL, CpsInp001+0, "p1 right"},
  {"P1 Hold"        , BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},
  {"P1 Weak punch"  , BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},
  {"P1 Strong punch", BIT_DIGITAL, CpsInp001+6, "p1 fire 3"},
  {"P1 Button 4"    , BIT_DIGITAL, CpsInp011+0, "p1 fire 4"},
  {"P1 Weak kick"   , BIT_DIGITAL, CpsInp011+1, "p1 fire 5"},
  {"P1 Strong kick" , BIT_DIGITAL, CpsInp011+2, "p1 fire 6"},

  {"P2 Coin"        , BIT_DIGITAL, CpsInp020+5, "p2 coin"},
  {"P2 Start"       , BIT_DIGITAL, CpsInp020+1, "p2 start"},
  {"P2 Up"          , BIT_DIGITAL, CpsInp000+3, "p2 up"},
  {"P2 Down"        , BIT_DIGITAL, CpsInp000+2, "p2 down"},
  {"P2 Left"        , BIT_DIGITAL, CpsInp000+1, "p2 left"},
  {"P2 Right"       , BIT_DIGITAL, CpsInp000+0, "p2 right"},
  {"P2 Hold"        , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
  {"P2 Weak punch"  , BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},
  {"P2 Strong punch", BIT_DIGITAL, CpsInp000+6, "p2 fire 3"},
  {"P2 Button 4"    , BIT_DIGITAL, CpsInp011+4, "p2 fire 4"},
  {"P2 Weak kick"   , BIT_DIGITAL, CpsInp011+5, "p2 fire 5"},
  {"P2 Strong kick" , BIT_DIGITAL, CpsInp020+6, "p2 fire 6"},

  {"Reset"          , BIT_DIGITAL, &CpsReset   , "reset"},
  {"Diagnostic"     , BIT_DIGITAL, CpsInp021+1, "diag"},
  {"Service"        , BIT_DIGITAL, CpsInp021+2, "service"},
};

STDINPUTINFO(Drv);

static struct BurnRomInfo RingdestRomDesc[] = {
	{ "smbe.03b",      0x80000, 0xb8016278, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "smbe.04b",      0x80000, 0x18c4c447, 1 | BRF_ESS | BRF_PRG },
	{ "smbe.05b",      0x80000, 0x18ebda7f, 1 | BRF_ESS | BRF_PRG },
	{ "smbe.06b",      0x80000, 0x89c80007, 1 | BRF_ESS | BRF_PRG },
	{ "smb.07",        0x80000, 0xb9a11577, 1 | BRF_ESS | BRF_PRG },
	{ "smb.08",        0x80000, 0xf931b76b, 1 | BRF_ESS | BRF_PRG },

	{ "smb.13m",      0x200000, 0xd9b2d1de, 3 | BRF_GRA },			 // 9
	{ "smb.15m",      0x200000, 0x9a766d92, 3 | BRF_GRA },
	{ "smb.17m",      0x200000, 0x51800f0f, 3 | BRF_GRA },
	{ "smb.19m",      0x200000, 0x35757e96, 3 | BRF_GRA },
	{ "smb.14m",      0x200000, 0xe5bfd0e7, 3 | BRF_GRA },
	{ "smb.16m",      0x200000, 0xc56c0866, 3 | BRF_GRA },
	{ "smb.18m",      0x200000, 0x4ded3910, 3 | BRF_GRA },
	{ "smb.20m",      0x200000, 0x26ea1ec5, 3 | BRF_GRA },
	{ "smb.21m",      0x080000, 0x0a08c5fc, 3 | BRF_GRA },
	{ "smb.23m",      0x080000, 0x0911b6c4, 3 | BRF_GRA },
	{ "smb.25m",      0x080000, 0x82d6c4ec, 3 | BRF_GRA },
	{ "smb.27m",      0x080000, 0x9b48678b, 3 | BRF_GRA },

	{ "smb.01",       0x020000, 0x0abc229a, 4 | BRF_ESS | BRF_PRG }, // 21
	{ "smb.02",       0x020000, 0xd051679a, 4 | BRF_ESS | BRF_PRG },

	{ "smb.11m",      0x200000, 0xc56935f9, 5 | BRF_SND },
	{ "smb.12m",      0x200000, 0x955b0782, 5 | BRF_SND },
};


STD_ROM_PICK(Ringdest) STD_ROM_FN(Ringdest)

static struct BurnRomInfo SmbombRomDesc[] = {
	{ "smbj.03a",      0x80000, 0x1c5613de, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "smbj.04a",      0x80000, 0x29071ed7, 1 | BRF_ESS | BRF_PRG },
	{ "smbj.05a",      0x80000, 0xeb20bce4, 1 | BRF_ESS | BRF_PRG },
	{ "smbj.06a",      0x80000, 0x94b420cd, 1 | BRF_ESS | BRF_PRG },
	{ "smb.07",        0x80000, 0xb9a11577, 1 | BRF_ESS | BRF_PRG },
	{ "smb.08",        0x80000, 0xf931b76b, 1 | BRF_ESS | BRF_PRG },

	{ "smb.13m",      0x200000, 0xd9b2d1de, 3 | BRF_GRA },			 // 9
	{ "smb.15m",      0x200000, 0x9a766d92, 3 | BRF_GRA },
	{ "smb.17m",      0x200000, 0x51800f0f, 3 | BRF_GRA },
	{ "smb.19m",      0x200000, 0x35757e96, 3 | BRF_GRA },
	{ "smb.14m",      0x200000, 0xe5bfd0e7, 3 | BRF_GRA },
	{ "smb.16m",      0x200000, 0xc56c0866, 3 | BRF_GRA },
	{ "smb.18m",      0x200000, 0x4ded3910, 3 | BRF_GRA },
	{ "smb.20m",      0x200000, 0x26ea1ec5, 3 | BRF_GRA },
	{ "smb.21m",      0x080000, 0x0a08c5fc, 3 | BRF_GRA },
	{ "smb.23m",      0x080000, 0x0911b6c4, 3 | BRF_GRA },
	{ "smb.25m",      0x080000, 0x82d6c4ec, 3 | BRF_GRA },
	{ "smb.27m",      0x080000, 0x9b48678b, 3 | BRF_GRA },

	{ "smb.01",       0x020000, 0x0abc229a, 4 | BRF_ESS | BRF_PRG }, // 21
	{ "smb.02",       0x020000, 0xd051679a, 4 | BRF_ESS | BRF_PRG },

	{ "smb.11m",      0x200000, 0xc56935f9, 5 | BRF_SND },
	{ "smb.12m",      0x200000, 0x955b0782, 5 | BRF_SND },
};


STD_ROM_PICK(Smbomb) STD_ROM_FN(Smbomb)

static struct BurnRomInfo Smbombr1RomDesc[] = {
	{ "smbj.03",       0x80000, 0x52eafb10, 1 | BRF_ESS | BRF_PRG },
	{ "smbj.04",       0x80000, 0xaa6e8078, 1 | BRF_ESS | BRF_PRG },
	{ "smbj.05",       0x80000, 0xb69e7d5f, 1 | BRF_ESS | BRF_PRG },
	{ "smbj.06",       0x80000, 0x8d857b56, 1 | BRF_ESS | BRF_PRG },
	{ "smb.07",        0x80000, 0xb9a11577, 1 | BRF_ESS | BRF_PRG },
	{ "smb.08",        0x80000, 0xf931b76b, 1 | BRF_ESS | BRF_PRG },

	{ "smb.13m",      0x200000, 0xd9b2d1de, 3 | BRF_GRA },			 // 9
	{ "smb.15m",      0x200000, 0x9a766d92, 3 | BRF_GRA },
	{ "smb.17m",      0x200000, 0x51800f0f, 3 | BRF_GRA },
	{ "smb.19m",      0x200000, 0x35757e96, 3 | BRF_GRA },
	{ "smb.14m",      0x200000, 0xe5bfd0e7, 3 | BRF_GRA },
	{ "smb.16m",      0x200000, 0xc56c0866, 3 | BRF_GRA },
	{ "smb.18m",      0x200000, 0x4ded3910, 3 | BRF_GRA },
	{ "smb.20m",      0x200000, 0x26ea1ec5, 3 | BRF_GRA },
	{ "smb.21m",      0x080000, 0x0a08c5fc, 3 | BRF_GRA },
	{ "smb.23m",      0x080000, 0x0911b6c4, 3 | BRF_GRA },
	{ "smb.25m",      0x080000, 0x82d6c4ec, 3 | BRF_GRA },
	{ "smb.27m",      0x080000, 0x9b48678b, 3 | BRF_GRA },

	{ "smb.01",       0x020000, 0x0abc229a, 4 | BRF_ESS | BRF_PRG }, // 21
	{ "smb.02",       0x020000, 0xd051679a, 4 | BRF_ESS | BRF_PRG },

	{ "smb.11m",      0x200000, 0xc56935f9, 5 | BRF_SND },
	{ "smb.12m",      0x200000, 0x955b0782, 5 | BRF_SND },
};


STD_ROM_PICK(Smbombr1) STD_ROM_FN(Smbombr1)

struct BurnDriver BurnDrvCpsRingdest = {
	"ringdest", NULL, NULL, "1994",
	"Ring of Destruction - slammasters II (940902 Euro)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS2,
	NULL, RingdestRomInfo, RingdestRomName, DrvInputInfo, NULL,
	Cps2Init,CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSmbomb = {
	"smbomb", "ringdest", NULL, "1994",
	"Super Muscle Bomber - the international blowout (940831 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, SmbombRomInfo, SmbombRomName, DrvInputInfo, NULL,
	Cps2Init,CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSmbombr1 = {
	"smbombr1", "ringdest", NULL, "1994",
	"Super Muscle Bomber - the international blowout (940808 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Smbombr1RomInfo, Smbombr1RomName, DrvInputInfo, NULL,
	Cps2Init,CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
