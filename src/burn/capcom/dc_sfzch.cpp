// Street Fighter Alpha (CPS Changer)

#include "cps.h"

static struct BurnInputInfo DrvInputList[] =
{
  {"P1 Pause",			BIT_DIGITAL, CpsInp018+2, ""},
  {"P1 Start",			BIT_DIGITAL, CpsInp018+4, "p1 start"},
  {"P1 Up",				BIT_DIGITAL, CpsInp001+3, "p1 up"},
  {"P1 Down",			BIT_DIGITAL, CpsInp001+2, "p1 down"},
  {"P1 Left",			BIT_DIGITAL, CpsInp001+1, "p1 left"},
  {"P1 Right",			BIT_DIGITAL, CpsInp001+0, "p1 right"},
  {"P1 Weak punch",		BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},
  {"P1 Medium punch",	BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},
  {"P1 Strong punch",	BIT_DIGITAL, CpsInp001+6, "p1 fire 3"},
  {"P1 Weak kick",		BIT_DIGITAL, CpsInp001+7, "p1 fire 4"},
  {"P1 Medium kick",	BIT_DIGITAL, CpsInp018+0, "p1 fire 5"},
  {"P1 Strong kick",	BIT_DIGITAL, CpsInp018+6, "p1 fire 6"},

  {"P2 Pause",			BIT_DIGITAL, CpsInp018+3, ""},
  {"P2 Start",			BIT_DIGITAL, CpsInp018+5, "p2 start"},
  {"P2 Up",				BIT_DIGITAL, CpsInp000+3, "p2 up"},
  {"P2 Down",			BIT_DIGITAL, CpsInp000+2, "p2 down"},
  {"P2 Left",			BIT_DIGITAL, CpsInp000+1, "p2 left"},
  {"P2 Right",			BIT_DIGITAL, CpsInp000+0, "p2 right"},
  {"P2 Weak punch",		BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
  {"P2 Medium punch",	BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},
  {"P2 Strong punch",	BIT_DIGITAL, CpsInp000+6, "p2 fire 3"},
  {"P2 Weak kick",		BIT_DIGITAL, CpsInp000+7, "p2 fire 4"},
  {"P2 Medium kick",	BIT_DIGITAL, CpsInp018+1, "p2 fire 5"},
  {"P2 Strong kick",	BIT_DIGITAL, CpsInp018+7, "p2 fire 6"},

  {"Reset",				BIT_DIGITAL, &CpsReset,   "reset"},
};

STDINPUTINFO(Drv);

static int DrvInit()
{
  int nRet=0; int i=0;
  Cps=3;
  nCpsRomLen= 4*0x080000;
  nCpsCodeLen=0; // not encrypted
  nCpsGfxLen=16*0x080000;
  nCpsZRomLen=  0x010000;
  nCpsAdLen  =2*0x020000;
  nRet=CpsInit(); if (nRet!=0) return 1;

  // Load program roms (they are already byteswapped)
  for (i=0;i<4;i++)
  { nRet=BurnLoadRom(CpsRom+0x080000*i,0+i,1); if (nRet!=0) return 1; }

  // Load graphics roms
  for (i=0;i<4;i++)
  {
    // Load up and interleve each set of 4 roms to make the 16x16 tiles
    CpsLoadTiles(CpsGfx+0x200000*i,4+i*4);
  }

  MaskAddr[0]=0x68;
  MaskAddr[1]=0x6a;
  MaskAddr[2]=0x6c;
  MaskAddr[3]=0x6e;

  // Load Z80 Rom
  nRet=BurnLoadRom(CpsZRom,20,1);

  // Load ADPCM data
  nRet=BurnLoadRom(CpsAd        ,21,1);
  nRet=BurnLoadRom(CpsAd+0x20000,22,1);

  nRet=CpsRunInit(); if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

static int DrvExit()
{
  CpsRunExit();
  CpsExit();
  nCpsAdLen=0; nCpsZRomLen=0; nCpsGfxLen=0; nCpsRomLen=0;
  Cps=0;
  return 0;
}

//===========================
//Street Fighter Zero (Japan)
//===========================

static struct BurnRomInfo DrvRomDesc[] = {
	{ "sfzch23",       0x80000, 0x1140743f, BRF_ESS | BRF_PRG }, //  0 68000 code
	{ "sfza22",        0x80000, 0x8d9b2480, BRF_ESS | BRF_PRG }, //  1
	{ "sfzch21",       0x80000, 0x5435225d, BRF_ESS | BRF_PRG }, //  2
	{ "sfza20",        0x80000, 0x806e8f38, BRF_ESS | BRF_PRG }, //  3

	{ "sfz01",         0x80000, 0x0dd53e62, BRF_GRA },
	{ "sfz02",         0x80000, 0x94c31e3f, BRF_GRA },
	{ "sfz03",         0x80000, 0x9584ac85, BRF_GRA },
	{ "sfz04",         0x80000, 0xb983624c, BRF_GRA },

	{ "sfz05",         0x80000, 0x2b47b645, BRF_GRA },
	{ "sfz06",         0x80000, 0x74fd9fb1, BRF_GRA },
	{ "sfz07",         0x80000, 0xbb2c734d, BRF_GRA },
	{ "sfz08",         0x80000, 0x454f7868, BRF_GRA },

	{ "sfz10",         0x80000, 0x2a7d675e, BRF_GRA },
	{ "sfz11",         0x80000, 0xe35546c8, BRF_GRA },
	{ "sfz12",         0x80000, 0xf122693a, BRF_GRA },
	{ "sfz13",         0x80000, 0x7cf942c8, BRF_GRA },

	{ "sfz14",         0x80000, 0x09038c81, BRF_GRA },
	{ "sfz15",         0x80000, 0x1aa17391, BRF_GRA },
	{ "sfz16",         0x80000, 0x19a5abd6, BRF_GRA },
	{ "sfz17",         0x80000, 0x248b3b73, BRF_GRA },

	{ "sfz09",         0x10000, 0xc772628b, BRF_SND },
	{ "sfz18",         0x20000, 0x61022b2d, BRF_SND },
	{ "sfz19",         0x20000, 0x3b5886d5, BRF_SND },
};


STD_ROM_PICK(Drv) STD_ROM_FN(Drv)

struct BurnDriver BurnDrvCpsSfzch = {
	"sfzch", NULL, NULL, "1995",
	"Street Fighter Zero (951020 CPS Changer)\0", NULL, "Capcom", "CPS Changer",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPSCHANGER,
	NULL,DrvRomInfo,DrvRomName,DrvInputInfo, NULL,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

static struct BurnRomInfo SfachRomDesc[] = {
	{ "sfach23",       0x80000, 0x02a1a853, BRF_ESS | BRF_PRG }, //  0 68000 code
	{ "sfza22",        0x80000, 0x8d9b2480, BRF_ESS | BRF_PRG }, //  1
	{ "sfzch21",       0x80000, 0x5435225d, BRF_ESS | BRF_PRG }, //  2
	{ "sfza20",        0x80000, 0x806e8f38, BRF_ESS | BRF_PRG }, //  3

	{ "sfz01",         0x80000, 0x0dd53e62, BRF_GRA },
	{ "sfz02",         0x80000, 0x94c31e3f, BRF_GRA },
	{ "sfz03",         0x80000, 0x9584ac85, BRF_GRA },
	{ "sfz04",         0x80000, 0xb983624c, BRF_GRA },

	{ "sfz05",         0x80000, 0x2b47b645, BRF_GRA },
	{ "sfz06",         0x80000, 0x74fd9fb1, BRF_GRA },
	{ "sfz07",         0x80000, 0xbb2c734d, BRF_GRA },
	{ "sfz08",         0x80000, 0x454f7868, BRF_GRA },

	{ "sfz10",         0x80000, 0x2a7d675e, BRF_GRA },
	{ "sfz11",         0x80000, 0xe35546c8, BRF_GRA },
	{ "sfz12",         0x80000, 0xf122693a, BRF_GRA },
	{ "sfz13",         0x80000, 0x7cf942c8, BRF_GRA },

	{ "sfz14",         0x80000, 0x09038c81, BRF_GRA },
	{ "sfz15",         0x80000, 0x1aa17391, BRF_GRA },
	{ "sfz16",         0x80000, 0x19a5abd6, BRF_GRA },
	{ "sfz17",         0x80000, 0x248b3b73, BRF_GRA },

	{ "sfz09",         0x10000, 0xc772628b, BRF_SND },
	{ "sfz18",         0x20000, 0x61022b2d, BRF_SND },
	{ "sfz19",         0x20000, 0x3b5886d5, BRF_SND },
};


STD_ROM_PICK(Sfach) STD_ROM_FN(Sfach)

struct BurnDriver BurnDrvCpsSfach = {
	"sfach", "sfzch", NULL, "1995",
	"Street Fighter Alpha (950727 CPS Changer)\0", NULL, "Capcom", "CPS Changer",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPSCHANGER,
	NULL,SfachRomInfo,SfachRomName,DrvInputInfo, NULL,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
