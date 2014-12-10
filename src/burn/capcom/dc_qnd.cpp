#include "cps.h"

static struct BurnInputInfo DrvInputList[] =
{
  {"P1 Coin"       , BIT_DIGITAL, CpsInp020+4, "p1 coin"},
  {"P1 Start"      , BIT_DIGITAL, CpsInp020+0, "p1 start"},
  {"P1 Answer 1"   , BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},
  {"P1 Answer 2"   , BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},
  {"P1 Answer 3"   , BIT_DIGITAL, CpsInp001+6, "p1 fire 3"},
  {"P1 Answer 4"   , BIT_DIGITAL, CpsInp001+7, "p1 fire 4"},

  {"P2 Coin"       , BIT_DIGITAL, CpsInp020+5, "p2 coin"},
  {"P2 Start"      , BIT_DIGITAL, CpsInp020+1, "p2 start"},
  {"P2 Answer 1"   , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
  {"P2 Answer 2"   , BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},
  {"P2 Answer 3"   , BIT_DIGITAL, CpsInp000+6, "p2 fire 3"},
  {"P2 Answer 4"   , BIT_DIGITAL, CpsInp000+7, "p2 fire 4"},

  {"Reset"         , BIT_DIGITAL, &CpsReset,   "reset"},
  {"Diagnostic"    , BIT_DIGITAL, CpsInp021+1, "diag"},
  {"Service"       , BIT_DIGITAL, CpsInp021+2, "service"},
};

STDINPUTINFO(Drv);

static struct BurnRomInfo DrvRomDesc[] = {
	{ "tqzj.03a",      0x80000, 0x7acf3e30, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "tqzj.04",       0x80000, 0xf1044a87, 1 | BRF_ESS | BRF_PRG },
	{ "tqzj.05",       0x80000, 0x4105ba0e, 1 | BRF_ESS | BRF_PRG },
	{ "tqzj.06",       0x80000, 0xc371e8a5, 1 | BRF_ESS | BRF_PRG },

	{ "tqz.14m",      0x200000, 0x98af88a2, 3 | BRF_GRA },			 //  5
	{ "tqz.16m",      0x200000, 0xdf82d491, 3 | BRF_GRA },
	{ "tqz.18m",      0x200000, 0x42f132ff, 3 | BRF_GRA },
	{ "tqz.20m",      0x200000, 0xb2e128a3, 3 | BRF_GRA },

	{ "tqz.01",       0x020000, 0xe9ce9d0a, 4 | BRF_ESS | BRF_PRG }, //  9

	{ "tqz.11m",      0x200000, 0x78e7884f, 5 | BRF_SND },			 // 10
	{ "tqz.12m",      0x200000, 0x2e049b13, 5 | BRF_SND },
};


STD_ROM_PICK(Drv) STD_ROM_FN(Drv)

struct BurnDriver BurnDrvCpsQndream = {
	"qndream", NULL, NULL, "1996",
	"Quiz Nanairo Dreams - nijiirochou no kiseki (nanairo dreams 960826 Japan)\0", NULL, "Capcom", "CPS2",
	L"Quiz \u306A\u306A\u3044\u308D Dreams - \u8679\u8272\u753A\u306E\u5947\u8DE1 (Nanairo Dreams 960826 Japan)\0Quiz Nanairo Dreams - nijiirochou no kiseki\0", NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS2,
	NULL, DrvRomInfo, DrvRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
