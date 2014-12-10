/*
Part of FBAs Taito 68k hardware drivers
Credits: Mame team, Raine team
Coding by KEV, with help from Treble Winner and Jan_Klaassen
*/
#include "taito.h"
static unsigned char *Mem=NULL,*MemEnd=NULL;
static unsigned char *RamStart=NULL,*RamEnd=NULL;
static unsigned char *Rom=NULL;
static unsigned char *twinhawk_ram=NULL,*twinhawk_src_pal=NULL;
unsigned char *sysbvidattr=NULL,*sysbvidram=NULL;
static unsigned char drvReset = 0;
static unsigned char *z80_rom=NULL,*z80_ram=NULL;
static unsigned int *twinhawk_pal=NULL;

// Z80 ROM bank
static int Z80Bank=0;
static int nCurrentBank=0;

static int nCyclesTotal[2];
static int nCyclesSegment=0;

static unsigned char twinhawkInputPort0[8], twinhawkInputPort1[8], twinhawkInputPort2[8];
unsigned char twinhawkInput[4]= {0,0,0,0};
static unsigned char twinhawkDip[2]= {0, 0};

static struct BurnInputInfo twinhawkInputList[]=
{
	{"P1 Coin"     , BIT_DIGITAL,	twinhawkInputPort2 + 0, "p1 coin"     },
	{"P1 Start"    , BIT_DIGITAL,	twinhawkInputPort0 + 7, "p1 start"    },
	{"P1 Up"       , BIT_DIGITAL,	twinhawkInputPort0 + 0, "p1 up"       },
	{"P1 Down"     , BIT_DIGITAL,	twinhawkInputPort0 + 1, "p1 down"     },
	{"P1 Left"     , BIT_DIGITAL,	twinhawkInputPort0 + 2, "p1 left"     },
	{"P1 Right"    , BIT_DIGITAL,	twinhawkInputPort0 + 3, "p1 right"    },
	{"P1 Button 1" , BIT_DIGITAL,	twinhawkInputPort0 + 4, "p1 fire 1"   },
	{"P1 Button 2" , BIT_DIGITAL,	twinhawkInputPort0 + 5, "p1 fire 2"   },
	{"P1 Button 3" , BIT_DIGITAL,	twinhawkInputPort0 + 6, "p1 fire 3"   },

	{"P2 Coin"     , BIT_DIGITAL,	twinhawkInputPort2 + 1, "p2 coin"     },
	{"P2 Start"    , BIT_DIGITAL,	twinhawkInputPort1 + 7, "p2 start"    },
	{"P2 Up"       , BIT_DIGITAL,	twinhawkInputPort1 + 0, "p2 up"       },
	{"P2 Down"     , BIT_DIGITAL,	twinhawkInputPort1 + 1, "p2 down"     },
	{"P2 Left"     , BIT_DIGITAL,	twinhawkInputPort1 + 2, "p2 left"     },
	{"P2 Right"    , BIT_DIGITAL,	twinhawkInputPort1 + 3, "p2 right"    },
	{"P2 Button 1" , BIT_DIGITAL,	twinhawkInputPort1 + 4, "p2 fire 1"   },
	{"P2 Button 2" , BIT_DIGITAL,	twinhawkInputPort1 + 5, "p2 fire 2"   },
	{"P2 Button 3" , BIT_DIGITAL,	twinhawkInputPort1 + 6, "p2 fire 3"   },

	{"Reset"	     , BIT_DIGITAL,	&drvReset			        ,	"reset"       },
	{"Service"     , BIT_DIGITAL,	twinhawkInputPort2 + 2, "service"     },
	{"Tilt"        , BIT_DIGITAL,	twinhawkInputPort2 + 3, "tilt"        },
	{"Dip 1"       , BIT_DIPSWITCH,	twinhawkDip + 0     , "dip"         },
	{"Dip 2"       , BIT_DIPSWITCH,	twinhawkDip + 1     , "dip"         },
};

STDINPUTINFO(twinhawk);


static struct BurnDIPInfo twinhawkCoinageDIPList[] =
{
	// Taito Coinage World
	{0   , 0xfe, 0   , 4   , "Coin A"                 },
	{0x15, 0x01, 0x30, 0x30, "4 Coins 1 Credit"       },
	{0x15, 0x01, 0x30, 0x20, "3 Coins 1 Credit"       },
	{0x15, 0x01, 0x30, 0x10, "2 Coins 1 Credit"       },
	{0x15, 0x01, 0x30, 0x00, "1 Coin 1 Credit"        },

	{0   , 0xfe, 0   , 4   , "Coin B"                 },
	{0x15, 0x01, 0xc0, 0xc0, "1 Coin 6 Credits"       },
	{0x15, 0x01, 0xc0, 0x80, "1 Coin 4 Credits"       },
	{0x15, 0x01, 0xc0, 0x40, "1 Coin 3 Credits"       },
	{0x15, 0x01, 0xc0, 0x00, "1 Coin 2 Credits"       },
};

static struct BurnDIPInfo twinhwkuCoinageDIPList[] =
{
	// Taito Coinage US
	{0   , 0xfe, 0   , 4   , "Coin A"                 },
	{0x15, 0x01, 0x30, 0x30, "4 Coins 1 Credit"       },
	{0x15, 0x01, 0x30, 0x20, "3 Coins 1 Credit"       },
	{0x15, 0x01, 0x30, 0x10, "2 Coins 1 Credit"       },
	{0x15, 0x01, 0x30, 0x00, "1 Coin 1 Credit"        },

	{0   , 0xfe, 0   , 4   , "Coin B"                 },
	{0x15, 0x01, 0xc0, 0xc0, "4 Coins 1 Credit"       },
	{0x15, 0x01, 0xc0, 0x80, "3 Coins 1 Credit"       },
	{0x15, 0x01, 0xc0, 0x40, "2 Coins 1 Credit"       },
	{0x15, 0x01, 0xc0, 0x00, "1 Coin 1 Credit"        },
};

static struct BurnDIPInfo daisenpuCoinageDIPList[] =
{
	// Taito Coinage Japan
	{0   , 0xfe, 0   , 4   , "Coin A"                 },
	{0x15, 0x01, 0x30, 0x30, "2 Coins 3 Credits"      },
	{0x15, 0x01, 0x30, 0x20, "2 Coins 1 Credit"       },
	{0x15, 0x01, 0x30, 0x10, "1 Coin 2 Credits"       },
	{0x15, 0x01, 0x30, 0x00, "1 Coin 1 Credit"        },

	{0   , 0xfe, 0   , 4   , "Coin B"                 },
	{0x15, 0x01, 0xc0, 0xc0, "2 Coins 3 Credits"      },
	{0x15, 0x01, 0xc0, 0x80, "2 Coins 1 Credit"       },
	{0x15, 0x01, 0xc0, 0x40, "1 Coin 2 Credits"       },
	{0x15, 0x01, 0xc0, 0x00, "1 Coin 1 Credit"        },
};


static struct BurnDIPInfo twinhawkDIPList[]=
{
	// Defaults
	{0x15, 0xff, 0xff, 0x00, NULL                     },
	{0x16, 0xff, 0xff, 0x80, NULL                     },

	// Dip 1
	{0   , 0xfe, 0xff , 2  , "Flip Screen"            },
	{0x15, 0x01, 0x02, 0x00, "Off"                    },
	{0x15, 0x01, 0x02, 0x02, "On"                     },

	{0   , 0xfe, 0   , 2   , "Test Mode"              },
	{0x15, 0x01, 0x04, 0x00, "Off"                    },
	{0x15, 0x01, 0x04, 0x04, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Demo Sounds"            },	// No Effect?
//	{0x15, 0x01, 0x08, 0x08, "Off"                    },
//	{0x15, 0x01, 0x08, 0x00, "On"                     },

	// Dip 2
	{0   , 0xfe, 0   , 4   , "Difficulty"             },
	{0x16, 0x01, 0x03, 0x01, "Easy"                   },
	{0x16, 0x01, 0x03, 0x00, "Normal"                 },
	{0x16, 0x01, 0x03, 0x02, "Hard"                   },
	{0x16, 0x01, 0x03, 0x03, "Hardest"                },

	{0   , 0xfe, 0   , 4   , "Bonus Life"             },
	{0x16, 0x01, 0x0c, 0x0c, "None"                   },
	{0x16, 0x01, 0x0c, 0x08, "50k only"               },
	{0x16, 0x01, 0x0c, 0x04, "70k and every 200k"     },
	{0x16, 0x01, 0x0c, 0x00, "50k and every 150k"     },

	{0   , 0xfe, 0   , 4   , "Lives"                  },
	{0x16, 0x01, 0x30, 0x30, "2"                      },
	{0x16, 0x01, 0x30, 0x00, "3"                      },
	{0x16, 0x01, 0x30, 0x20, "4"                      },
	{0x16, 0x01, 0x30, 0x10, "5"                      },

//	{0   , 0xfe, 0   , 2   , "Unused"                 },
//	{0x16, 0x01, 0x40, 0x00, "Off"                    },
//	{0x16, 0x01, 0x40, 0x40, "On"                     },

	{0   , 0xfe, 0   , 2   , "Allow Continue"         },
	{0x16, 0x01, 0x80, 0x00, "Off"                    },
	{0x16, 0x01, 0x80, 0x80, "On"                     },
};


static struct BurnDIPInfo daisenpuDIPList[]=
{
	// Defaults
	{0x15, 0xff, 0xff, 0x01, NULL                     },
	{0x16, 0xff, 0xff, 0x80, NULL                     },

	// Dip 1
	{0   , 0xfe, 0xff , 2  , "Cabinet"                },
	{0x15, 0x01, 0x01, 0x00, "Cocktail"               },
	{0x15, 0x01, 0x01, 0x01, "Upright"                },

	{0   , 0xfe, 0xff , 2  , "Flip Screen"            },
	{0x15, 0x01, 0x02, 0x00, "Off"                    },
	{0x15, 0x01, 0x02, 0x02, "On"                     },

	{0   , 0xfe, 0   , 2   , "Test Mode"              },
	{0x15, 0x01, 0x04, 0x00, "Off"                    },
	{0x15, 0x01, 0x04, 0x04, "On"                     },

	{0   , 0xfe, 0   , 2   , "Demo Sounds"            },
	{0x15, 0x01, 0x08, 0x08, "Off"                    },
	{0x15, 0x01, 0x08, 0x00, "On"                     },

	// Dip 2
	{0   , 0xfe, 0   , 4   , "Difficulty"             },
	{0x16, 0x01, 0x03, 0x01, "Easy"                   },
	{0x16, 0x01, 0x03, 0x00, "Normal"                 },
	{0x16, 0x01, 0x03, 0x02, "Hard"                   },
	{0x16, 0x01, 0x03, 0x03, "Hardest"                },

	{0   , 0xfe, 0   , 4   , "Bonus Life"             },
	{0x16, 0x01, 0x0c, 0x0c, "None"                   },
	{0x16, 0x01, 0x0c, 0x08, "100k only"              },
	{0x16, 0x01, 0x0c, 0x00, "70k and every 200k"     },
	{0x16, 0x01, 0x0c, 0x04, "50k and every 150k"     },

	{0   , 0xfe, 0   , 4   , "Lives"                  },
	{0x16, 0x01, 0x30, 0x30, "2"                      },
	{0x16, 0x01, 0x30, 0x00, "3"                      },
	{0x16, 0x01, 0x30, 0x20, "4"                      },
	{0x16, 0x01, 0x30, 0x10, "5"                      },

//	{0   , 0xfe, 0   , 2   , "Unused"                 },
//	{0x16, 0x01, 0x40, 0x00, "Off"                    },
//	{0x16, 0x01, 0x40, 0x40, "On"                     },

	{0   , 0xfe, 0   , 2   , "Allow Continue"         },
	{0x16, 0x01, 0x80, 0x00, "Off"                    },
	{0x16, 0x01, 0x80, 0x80, "On"                     },
};

STDDIPINFOEXT(twinhawk, twinhawkCoinage, twinhawk);
STDDIPINFOEXT(twinhwku, twinhwkuCoinage, twinhawk);
STDDIPINFOEXT(daisenpu, daisenpuCoinage, daisenpu);


void twinhawkBankSwitch(unsigned int /*a*/, unsigned int data)
{
	Z80Bank=(data-1) & 0x03;
	unsigned char* nStartAddress = z80_rom + 0x4000+(Z80Bank*0x4000);
	nCurrentBank = Z80Bank;
	ZetMapArea(0x4000, 0x7FFF, 0, nStartAddress);
	ZetMapArea(0x4000, 0x7FFF, 2, nStartAddress);
}

void twinhawkYM2151IRQHandler(int irq )
{
	if (irq)
	{
		ZetRaiseIrq(1);
	}
	else
	{
		ZetLowerIrq();
	}
}

int twinhawkInpMake()
{
	twinhawkInput[0] = twinhawkInput[1] = 0xff;
	twinhawkInput[2] = 0xff;

	for (int i = 0; i < 8; i++) {
		twinhawkInput[0] -= (twinhawkInputPort0[i] & 1) << i;
		twinhawkInput[1] -= (twinhawkInputPort1[i] & 1) << i;
		twinhawkInput[2] -= (twinhawkInputPort2[i] & 1) << i;

	}
	return 0;
}

inline static unsigned int CalcCol(unsigned short nColour)
{
	int r, g, b;

	r = (nColour & 0x001F) << 3;	// Red
	r |= r >> 5;
	g = (nColour & 0x03E0) >> 2;  	// Green
	g |= g >> 5;
	b = (nColour & 0x7C00) >> 7;	// Blue
	b |= b >> 5;

	return BurnHighCol(b, g, r, 0);
}

int twinhawkPalUpdate()
{
	int i;
	unsigned short* ps;
	unsigned int* pd;

	for (i = 0, ps = (unsigned short*)twinhawk_src_pal, pd = twinhawk_pal; i < 0x400; i++, ps++, pd++) {
		*pd = CalcCol(*ps);
	}
	return 0;
}
////
// This routine is called first to determine how much memory is needed (MemEnd-(unsigned char *)0),
// and then to set up all the pointers

static int MemIndex()
{
	unsigned char *Next; Next=Mem;
	Rom  =Next;   Next+=0x40000; // 68000 program
	z80_rom=Next; Next+=0x1c000;
    RamStart =Next;
	twinhawk_ram=Next;	Next+=0xb000;
	sysbvidattr=Next; Next+=0x1000;
	sysbvidram=Next; Next+=0x4000;
	twinhawk_src_pal=Next;		Next+=0x1000;
	twinhawk_pal=(unsigned int*)Next; Next += 0x800 * sizeof(unsigned int);
	z80_ram=Next; Next+=0x2000;
	RamEnd   =Next;
    MemEnd=Next;
    return 0;
}

static int LoadRoms()
{

	int nRet=0;
	// Load program roms and byteswap
	nRet=BurnLoadRom(Rom+0x00001,0,2); if (nRet!=0) return 1;
	nRet=BurnLoadRom(Rom+0x00000,1,2); if (nRet!=0) return 1;
	nRet=BurnLoadRom(z80_rom,2,1); // load z80 code rom
	ttiles=(unsigned char *)malloc(0x400000);
	memset(ttiles,0,16384*256);

	SysxTempGfx=(unsigned char *)malloc(0x200000);

	nRet=BurnLoadRom(SysxTempGfx,3,1);
	nRet=BurnLoadRom(SysxTempGfx+0x80000,4,1);
	nRet=BurnLoadRom(SysxTempGfx+0x100000,5,1);
	nRet=BurnLoadRom(SysxTempGfx+0x180000,6,1);
	return nRet;
  }

unsigned char __fastcall twinhawkZ80Read(unsigned short a)
{
	switch (a)
	{
	case (0xe000):
		return BurnYM2151ReadStatus();
	case (0xe001):
		return BurnYM2151ReadStatus();
	case (0xe201):
		return tc0140_slave_comm_r();
	default:
		return 0;
	}
}

void __fastcall twinhawkZ80Write(unsigned short a,unsigned char d)
{
	switch (a)
	{
	case 0xe000:
		BurnYM2151SelectRegister(d);
		return;
	case 0xe001:
		BurnYM2151WriteRegister(d);
		return;
	case 0xe200:
		tc0140_slave_port_w(d);
		return;
	case 0xe201:
		tc0140_slave_comm_w(d);
		return;
	case 0xf200:
		twinhawkBankSwitch(0,d);
	default:
		return;
	}
}

unsigned short __fastcall twinhawkReadWord(unsigned int a)
{
	switch (a)
	{
		case 0x500000:
		case 0x500002:
		case 0x500004:
		case 0x500006:
		case 0x500008:
		case 0x50000a:
		case 0x50000c:
		case 0x50000e:
			SEK_DEF_READ_WORD(0, a);
	}
	if (a==0x900000)
	{
		return twinhawkInput[0];
	}
	if (a==0x900002)
	{
		return twinhawkInput[1];
	}
	if (a==0x900004)
	{
		return twinhawkInput[2];
	}
	if (a>=0x900000&&a<=0x90000f)
	{
		bprintf(PRINT_NORMAL, _T("input word read %x\n"),a);
		return 0;
	}
	if (a==0x800002)
	{
		bprintf(PRINT_NORMAL, _T("sound word read %x\n"),a);
		return 0xff;
	}
	if (a==0x800003)
	{
		bprintf(PRINT_NORMAL, _T("sound word read %x\n"),a);
		return 0xff;
	}
	bprintf(PRINT_NORMAL, _T("unknown word read %x\n"),a);
	return 0xFF;
}

unsigned char __fastcall twinhawkReadByte(unsigned int a)
{
	switch (a) {
		case 0x500001: return (0xff - twinhawkDip[0]) & 0x0f;
		case 0x500003: return ((0xff - twinhawkDip[0]) & 0xf0) >> 4;
		case 0x500005: return (0xff - twinhawkDip[1]) & 0x0f;
		case 0x500007: return ((0xff - twinhawkDip[1]) & 0xf0) >> 4;
//		printf("DSW byte read %x\n",a);
		return 0xFF;
	}

	if (a==0x900001)
	{
		return twinhawkInput[0];
	}

	if (a==0x900003)
	{
		return twinhawkInput[1];
	}

	if (a==0x900005)
	{
		return twinhawkInput[2];
	}

	if (a>=0x900000&&a<=0x90000f)
	{
		bprintf(PRINT_NORMAL, _T("input byte read %x\n"),a);
		return 0xff;
	}

	if (a==0x800002)
	{
		bprintf(PRINT_NORMAL, _T("sound byte read %x\n"),a);
		return 0xff;
	}

	if (a==0x800003)
	{
		return tc0140_comm_r();
	}
	bprintf(PRINT_NORMAL, _T("unknown byte read %x\n"),a);

	return 0xFF;
}

void __fastcall twinhawkWriteWord(unsigned int a,unsigned short d)
{
	if (a>=0x900000&&a<=0x90000f)
	{
//		bprintf(PRINT_NORMAL, "input word write %x\n",a);
	}
	if (a==0x800000)
	{
		bprintf(PRINT_NORMAL, _T("sound word write %x\n"),a);
	}

	if (a==0x800001)
	{
		bprintf(PRINT_NORMAL, _T("sound word write %x\n"),a);
	}

	if (a==0x800002)
	{
		bprintf(PRINT_NORMAL, _T("sound word write %x\n"),a);
	}

	if (a==0x800003)
	{
		bprintf(PRINT_NORMAL, _T("sound word write %x\n"),a);
	}
	if (a<=0xf03fff)
		bprintf(PRINT_NORMAL, _T("unknown word write %x %x\n"),a,d);

	return;
}

void __fastcall twinhawkWriteByte(unsigned int a,unsigned char d)
{
	if (a>=0x900000&&a<=0x90000f)
	{
//		bprintf(PRINT_NORMAL, "input byte write %x\n",a);
	}

	if (a==0x800000)
	{
		bprintf(PRINT_NORMAL, _T("sound byte write %x\n"),a);
	}

	if (a==0x800001)
	{
		tc0140_port_w(d);
	}

	if (a==0x800002)
	{
		bprintf(PRINT_NORMAL, _T("sound byte write %x\n"),a);
	}

	if (a==0x800003)
	{
		tc0140_comm_w(d);
	}

//	bprintf(PRINT_NORMAL, "unknown word byte %x %x\n",a,d);

	return;
}

static int drvDoReset()
{
	SekOpen(0);
	SekReset();
	SekClose();
	ZetOpen(0);
	ZetReset();
	ZetClose();
	ZetRun(4000000/60);
	BurnYM2151Reset();
	return 0;
}

int twinhawkInit()
{
	int nRet=0; int nLen=0;

	//--------------Allocate Memory-----------------
	Mem=NULL;
	MemIndex();
	nLen=MemEnd-(unsigned char *)0;
	Mem=(unsigned char *)malloc(nLen);
	if (Mem==NULL)
		return 1;
	memset(Mem,0,nLen); // blank all memory
	MemIndex(); // Index the allocated memory

	//--------------- Load Roms -------------------
	nRet=LoadRoms();
	if (nRet!=0)
		return 1; // Load the roms into memory

	// Map in memory:
	// ----------------- Cpu 1 68k ------------------------
	SekInit(0, 0x68000); // Allocate 1 68000
	SekOpen(0);
	SekMapMemory(    Rom  ,0x000000,0x3ffff,SM_ROM); // 68000 Rom
	SekMapMemory(twinhawk_src_pal,0xb00000,0xb00FFF,SM_RAM);
	SekMapMemory(sysbvidattr,0xd00000,0xd00fff,SM_RAM);
	SekMapMemory(sysbvidram,0xe00000,0xe03fff,SM_RAM);
	SekMapMemory(twinhawk_ram,0xf00000,0xf03fff,SM_RAM);

	SekSetReadWordHandler(0, twinhawkReadWord);
	SekSetWriteWordHandler(0, twinhawkWriteWord);
	SekSetReadByteHandler(0, twinhawkReadByte);
	SekSetWriteByteHandler(0, twinhawkWriteByte);
	SekClose();
	// ------------------------------------------------
	// ----------------- Cpu 2 Z80 ------------------------
	ZetInit(1);
	ZetOpen(0);
	ZetSetReadHandler(twinhawkZ80Read);
	ZetSetWriteHandler(twinhawkZ80Write);
	ZetMapArea (0x0000,0x3FFF,0,z80_rom);
	ZetMapArea (0x0000,0x3FFF,2,z80_rom);
//	ZetMapArea (0x4000,0x7FFF,0,z80_rom+0x4000);
//	ZetMapArea (0x4000,0x7FFF,2,z80_rom+0x4000);
	ZetMapArea (0xc000,0xdfff,0,z80_ram);
	ZetMapArea (0xc000,0xdfff,2,z80_ram);
	ZetMapArea (0xc000,0xdfff,1,z80_ram);
	ZetMemEnd();
	ZetMemCallback(0xe000, 0xFFFF, 0);			// Read
	ZetMemCallback(0xe000, 0xFFFF, 1);			// Write
	ZetReset();
	ZetClose();
	//-------------------------------------------------

	//-------- sound stuff ----------------------------
	//---------- YM2151 Setup ----------------------
	BurnYM2151Init(4000000, 50.0);
	BurnYM2151SetIrqHandler(&twinhawkYM2151IRQHandler);
	nCurrentBank=-1;

	//--------------------------------------------------
	// ------- GFX Init -------------------
	taito_pal=twinhawk_pal;
	SysXInit(0);
	drvDoReset();
	return 0;
	}

int twinhawkExit()
{

	free(ttiles);
	BurnYM2151Exit();
	SekExit(); // Deallocate 68000
	ZetExit();
	if (Mem!=NULL)
		free(Mem);
	Mem=NULL;
	return 0;
}

static int twinhawkDraw()
{
	twinhawkPalUpdate();
	SysXBG();
	SysXSprites();
	return 0;
}

int twinhawkFrame()
{
	if (drvReset) {	// Reset machine
		drvDoReset();
	}

	twinhawkInpMake();

	int nInterleave =10;

	SekNewFrame();

	SekOpen(0);
	ZetOpen(0);
	nCyclesTotal[0] = 8000000/60;
	nCyclesTotal[1] = 4000000/60;
	rCyclesDone[0] = rCyclesDone[1] = 0;

	int nSoundBufferPos = 0;

	for (int i = 0; i < nInterleave; i++) {
    	int nCurrentCPU;
		int nNext;
		// Run 68000
		nCurrentCPU = 0;
		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;

		nCyclesSegment = nNext - rCyclesDone[nCurrentCPU];
		rCyclesDone[nCurrentCPU] += SekRun(nCyclesSegment);
		// Run Z80
		nCurrentCPU = 1;

		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;
		nCyclesSegment = nNext - rCyclesDone[nCurrentCPU];

		nCyclesSegment = ZetRun(nCyclesSegment);
		rCyclesDone[nCurrentCPU] += nCyclesSegment;
		{
			// Render sound segment
			if (pBurnSoundOut) {
				int nSegmentLength = nBurnSoundLen / nInterleave;
				short* pSoundBuf = pBurnSoundOut + (nSoundBufferPos << 1);
				BurnYM2151Render(pSoundBuf, nSegmentLength);
				nSoundBufferPos += nSegmentLength;
			}
		}
	}

	{
		// Make sure the buffer is entirely filled.
		if (pBurnSoundOut) {
			int nSegmentLength = nBurnSoundLen - nSoundBufferPos;
			short* pSoundBuf = pBurnSoundOut + (nSoundBufferPos << 1);
			if (nSegmentLength) {
				BurnYM2151Render(pSoundBuf, nSegmentLength);
			}
		}
	}
	SekSetIRQLine(2, SEK_IRQSTATUS_AUTO);
	ZetClose();
	SekClose();

	if (pBurnDraw) {
		twinhawkDraw();														// Draw screen if needed
	}

	return 0;
}

static int twinhawkScan(int nAction,int *pnMin)
{
	struct BurnArea ba;

	if (pnMin) {						// Return minimum compatible version
		*pnMin = 0x029521;
	}

	if (nAction & ACB_VOLATILE) {		// Scan volatile ram

		memset(&ba, 0, sizeof(ba));
    ba.Data	  = RamStart;
		ba.nLen	  = RamEnd-RamStart;
		ba.szName = "All Ram";
		BurnAcb(&ba);
	}

	if (nAction & ACB_DRIVER_DATA) {
		SekScan(nAction);										// Scan 68000 state

		ZetOpen(0);
		ZetScan(nAction);										// Scan Z80 state
		ZetClose();

		SCAN_VAR(nCyclesTotal);
		SCAN_VAR(nCyclesSegment);

		// Scan critical driver variables
		SCAN_VAR(twinhawkInputPort0);
		SCAN_VAR(twinhawkInputPort1);
		SCAN_VAR(twinhawkInputPort2);

		SCAN_VAR(twinhawkInput);
		SCAN_VAR(twinhawkDip);
		SCAN_VAR(Z80Bank);
		SCAN_VAR(nCurrentBank);
		
		BurnYM2151Scan(nAction);
	}

	return 0;
}


// Twin Hawk (World)
static struct BurnRomInfo twinhawkRomDesc[] = {
	{ "b87-11.bin",    0x20000, 0xfc84a399, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "b87-10.bin",    0x20000, 0x17181706, BRF_ESS | BRF_PRG }, //  1            (odd)

	{ "b87-07",         0x8000, 0xe2e0efa0, BRF_ESS | BRF_PRG }, //  2 z80 code

	{ "b87-02",        0x80000, 0x89ad43a0, BRF_GRA },			 //  3 8x8 tile bitmaps
	{ "b87-04",        0x80000, 0x958434b6, BRF_GRA },			 //  4 8x8 tile bitmaps
	{ "b87-01",        0x80000, 0x81e82ae1, BRF_GRA },			 //  5 8x8 tile bitmaps
	{ "b87-03",        0x80000, 0xce155ae0, BRF_GRA },			 //  6 8x8 tile bitmaps

};

STD_ROM_PICK(twinhawk);
STD_ROM_FN(twinhawk);

struct BurnDriver BurnDrvtwinhawk = {
	"twinhawk", NULL, NULL, "1989",
	"Twin Hawk (World)\0", NULL, "Taito", "Taito X System",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_ORIENTATION_VERTICAL,2,HARDWARE_MISC_MISC,
	NULL,twinhawkRomInfo,twinhawkRomName,twinhawkInputInfo, twinhawkDIPInfo,
	twinhawkInit,twinhawkExit,twinhawkFrame,NULL,twinhawkScan,
	&taitoRecalcPal,224,384,3,4
};

//Twin Hawk (US)
static struct BurnRomInfo twinhwkuRomDesc[] = {
	{ "b87-09.u6",     0x20000, 0x7e6267c7, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "b87-08.u4",     0x20000, 0x31d9916f, BRF_ESS | BRF_PRG }, //  1            (odd)

	{ "b87-07",         0x8000, 0xe2e0efa0, BRF_ESS | BRF_PRG }, //  2 z80 code

	{ "b87-02",        0x80000, 0x89ad43a0, BRF_GRA },			 //  3 8x8 tile bitmaps
	{ "b87-04",        0x80000, 0x958434b6, BRF_GRA },			 //  4 8x8 tile bitmaps
	{ "b87-01",        0x80000, 0x81e82ae1, BRF_GRA },			 //  5 8x8 tile bitmaps
	{ "b87-03",        0x80000, 0xce155ae0, BRF_GRA },			 //  6 8x8 tile bitmaps

};

STD_ROM_PICK(twinhwku);
STD_ROM_FN(twinhwku);

struct BurnDriver BurnDrvtwinhwku = {
	"twinhwku", "twinhawk", NULL, "1989",
	"Twin Hawk (US)\0", NULL, "Taito", "Taito X System",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_ORIENTATION_VERTICAL,2,HARDWARE_MISC_MISC,
	NULL,twinhwkuRomInfo,twinhwkuRomName,twinhawkInputInfo, twinhwkuDIPInfo,
	twinhawkInit,twinhawkExit,twinhawkFrame,NULL,twinhawkScan,
	&taitoRecalcPal,224,384,3,4
};

// Daisenpu (Japan)
static struct BurnRomInfo daisenpuRomDesc[] = {
	{ "b87-06",        0x20000, 0xcf236100, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "b87-05",        0x20000, 0x7f15edc7, BRF_ESS | BRF_PRG }, //  1            (odd)

	{ "b87-07",         0x8000, 0xe2e0efa0, BRF_ESS | BRF_PRG }, //  2 z80 code

	{ "b87-02",        0x80000, 0x89ad43a0, BRF_GRA },			 //  3 8x8 tile bitmaps
	{ "b87-04",        0x80000, 0x958434b6, BRF_GRA },			 //  4 8x8 tile bitmaps
	{ "b87-01",        0x80000, 0x81e82ae1, BRF_GRA },			 //  5 8x8 tile bitmaps
	{ "b87-03",        0x80000, 0xce155ae0, BRF_GRA },			 //  6 8x8 tile bitmaps

};

STD_ROM_PICK(daisenpu);
STD_ROM_FN(daisenpu);

struct BurnDriver BurnDrvDaisenpu = {
	"daisenpu", "twinhawk", NULL, "1989",
	"Daisenpu (Japan)\0", NULL, "Taito", "Taito X System",
	L"Daisenpu (Japan)\0\u5927\u65CB\u98A8\0", NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_ORIENTATION_VERTICAL,2,HARDWARE_MISC_MISC,
	NULL,daisenpuRomInfo,daisenpuRomName,twinhawkInputInfo, daisenpuDIPInfo,
	twinhawkInit,twinhawkExit,twinhawkFrame,NULL,twinhawkScan,
	&taitoRecalcPal,224,384,3,4
};
