// Pang! 3

#include "cps.h"

static struct BurnInputInfo DrvInputList[] =
{
  {"P1 Coin"       , BIT_DIGITAL, CpsInp018+0, "p1 coin"},
  {"P1 Start"      , BIT_DIGITAL, CpsInp018+4, "p1 start"},
  {"P1 Up"         , BIT_DIGITAL, CpsInp001+3, "p1 up"},
  {"P1 Down"       , BIT_DIGITAL, CpsInp001+2, "p1 down"},
  {"P1 Left"       , BIT_DIGITAL, CpsInp001+1, "p1 left"},
  {"P1 Right"      , BIT_DIGITAL, CpsInp001+0, "p1 right"},
  {"P1 Shot 1"     , BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},
  {"P1 Shot 2"     , BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},

  {"P2 Coin"       , BIT_DIGITAL, CpsInp018+1, "p2 coin"},
  {"P2 Start"      , BIT_DIGITAL, CpsInp018+5, "p2 start"},
  {"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"},
  {"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"},
  {"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"},
  {"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right"},
  {"P2 Shot 1"     , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
  {"P2 Shot 2"     , BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},

  {"Reset"         , BIT_DIGITAL, &CpsReset,   "reset"},
  {"Diagnostic"    , BIT_DIGITAL, CpsInp018+6, "diag"},
  {"Service"       , BIT_DIGITAL, CpsInp018+2, "service"},
  {"Dip C"         , BIT_DIPSWITCH, &Cpi01E    , "dip"},
};

STDINPUTINFO(Drv);

static struct BurnDIPInfo pang3DIPList[]=
{
	// Defaults
	{0x13, 0xff, 0xff, 0x00, NULL                },

	// Dip C
	{0   , 0xfe, 0   , 2   , "Freeze"                 },
	{0x13, 0x01, 0x08, 0x00, "Off"                    },
	{0x13, 0x01, 0x08, 0x08, "On"                     },
};

STDDIPINFO(pang3);

static int DrvInit()
{
  int nRet=0;
  Cps=1; PangEEP=1;
  nCpsRomLen=   0x100000;
  nCpsCodeLen=0; // not encrypted
  nCpsGfxLen= 4*0x200000;
  nCpsZRomLen=  0x010000;
  nCpsAdLen  =2*0x020000;
  nRet=CpsInit(); if (nRet!=0) return 1;

  // Load program roms
  nRet=BurnLoadRom(CpsRom+0x000000,0,1); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x080000,1,1); if (nRet!=0) return 1; // Already byteswapped

  // Load graphics roms
  CpsLoadTilesPang(CpsGfx,2);

  // Load Z80 Rom
  nRet=BurnLoadRom(CpsZRom,4,1);
  nCpsLcReg=0x66; // Layer control register is at 0x6e
  CpsLayEn[1]=0x02; //layer enable 1 is different
  CpsLayEn[2]=0x04;
  CpsLayEn[3]=0x08; // Layer enable is different

  MaskAddr[0]=0x68;
  MaskAddr[1]=0x6a;
  MaskAddr[2]=0x6c;
  MaskAddr[3]=0x6e;

  // Load ADPCM data
  nRet=BurnLoadRom(CpsAd        ,5,1);
  nRet=BurnLoadRom(CpsAd+0x20000,6,1);

  nRet=CpsRunInit(); if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

static int Pang3jInit()
{
  int nRet=0;
  int i,src,dst;
  Cps=1; PangEEP=1;
  nCpsRomLen=   0x100000;
  nCpsCodeLen=0; // not encrypted
  nCpsGfxLen= 4*0x200000;
  nCpsZRomLen=  0x010000;
  nCpsAdLen  =2*0x020000;
  nRet=CpsInit(); if (nRet!=0) return 1;

  // Load program roms
  nRet=BurnLoadRom(CpsRom+0x000000,0,1); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x080000,1,1); if (nRet!=0) return 1; // Already byteswapped

  for (i = 0x80000;i < 0x100000;i += 2)
  {
	/* only the low 8 bits of each word are encrypted */
	src = CpsRom[i];
	dst = src & 0xff00;
	if ( src & 0x01) dst ^= 0x04;
	if ( src & 0x02) dst ^= 0x21;
	if ( src & 0x04) dst ^= 0x01;
	if (~src & 0x08) dst ^= 0x50;
	if ( src & 0x10) dst ^= 0x40;
	if ( src & 0x20) dst ^= 0x06;
	if ( src & 0x40) dst ^= 0x08;
	if (~src & 0x80) dst ^= 0x88;
	CpsRom[i] = (unsigned char)dst;
  }

  // Load graphics roms
  CpsLoadTilesPang(CpsGfx,2);

  // Load Z80 Rom
  nRet=BurnLoadRom(CpsZRom,4,1);
  nCpsLcReg=0x66; // Layer control register is at 0x6e
  CpsLayEn[1]=0x02; //layer enable 1 is different
  CpsLayEn[2]=0x04;
  CpsLayEn[3]=0x08; // Layer enable is different

  MaskAddr[0]=0x68;
  MaskAddr[1]=0x6a;
  MaskAddr[2]=0x6c;
  MaskAddr[3]=0x6e;

  // Load ADPCM data
  nRet=BurnLoadRom(CpsAd        ,5,1);
  nRet=BurnLoadRom(CpsAd+0x20000,6,1);


  nRet=CpsRunInit(); if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

static int DrvExit()
{

  CpsRunExit();

  CpsExit();
  nCpsAdLen=0; nCpsZRomLen=0; nCpsGfxLen=0; nCpsRomLen=0;
  Cps=0; PangEEP=0;
  return 0;
}

//==============
//Pang! 3 (Euro)
//==============

// Rom information
static struct BurnRomInfo Pang3RomDesc[] = {
	{ "pa3w-17.11l",   0x80000, 0x12138234, BRF_ESS | BRF_PRG },
	{ "pa3w-16.10l",   0x80000, 0xd1ba585c, BRF_ESS | BRF_PRG },

	{ "pa3-01m.2c",   0x200000, 0x068a152c, BRF_GRA },
	{ "pa3-07m.2f",   0x200000, 0x3a4a619d, BRF_GRA },

	{ "pa3-11.11f",    0x08000, 0x90a08c46, BRF_SND },

	{ "pa3-05.10d",    0x20000, 0x73a10d5d, BRF_SND },
	{ "pa3-06.11d",    0x20000, 0xaffa4f82, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Pang3) STD_ROM_FN(Pang3)

struct BurnDriver BurnDrvCpsPang3 = {
	"pang3", NULL, NULL, "1995",
	"Pang! 3 (950511 Euro)\0", NULL, "Mitchell", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS1_GENERIC,
	NULL,Pang3RomInfo,Pang3RomName,DrvInputInfo, pang3DIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//===============
//Pang! 3 (Japan)
//===============

// Rom information
static struct BurnRomInfo Pang3jRomDesc[] = {
	{ "pa3j-17.11l",   0x80000, 0x21f6e51f, BRF_ESS | BRF_PRG },
	{ "pa3j-16.10l",   0x80000, 0xca1d7897, BRF_ESS | BRF_PRG },

	{ "pa3-01m.2c",   0x200000, 0x068a152c, BRF_GRA },
	{ "pa3-07m.2f",   0x200000, 0x3a4a619d, BRF_GRA },

	{ "pa3-11.11f",    0x08000, 0x90a08c46, BRF_SND },

	{ "pa3-05.10d",    0x20000, 0x73a10d5d, BRF_SND },
	{ "pa3-06.11d",    0x20000, 0xaffa4f82, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Pang3j) STD_ROM_FN(Pang3j)

struct BurnDriver BurnDrvCpsPang3j = {
	"pang3j", "pang3", NULL, "1995",
	"Pang! 3 (950511 Japan)\0", NULL, "Mitchell", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1_GENERIC,
	NULL,Pang3jRomInfo,Pang3jRomName,DrvInputInfo, pang3DIPInfo,
	Pang3jInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
