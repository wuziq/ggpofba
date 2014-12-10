/*
Rainbow Island driver
=====================
Part of FBAs Taito 68k hardware drivers
Credits: Mame team, Raine team
Coding by KEV, with help from Treble Winner and Jan_Klaassen
*/

#include "taito.h"

static unsigned char *Mem=NULL,*MemEnd=NULL;
static unsigned char *RamStart=NULL,*RamEnd=NULL;
static unsigned char *Rom=NULL;
static unsigned char *rainbow_ram=NULL,*rainbow_src_pal=NULL;
static unsigned char drvReset = 0;
static unsigned char *z80_rom=NULL,*z80_ram=NULL;
static unsigned int *rainbow_pal=NULL;

// Z80 ROM bank
static int Z80Bank=0;
static int nCurrentBank=0;


static int nCyclesTotal[2];
static int nCyclesSegment=0;

static unsigned char rainbowInputPort0[8], rainbowInputPort1[8], rainbowInputPort2[8], rainbowInputPort3[8];
unsigned char rainbowInput[4]= {0,0,0,0};
static unsigned char rainbowDip[2]= {0, 0};
static struct BurnInputInfo rainbowInputList[]=
{
	{"P1 Coin"     , BIT_DIGITAL,	rainbowInputPort1 + 0, "p1 coin"     },
	{"P1 Start"    , BIT_DIGITAL,	rainbowInputPort0 + 6, "p1 start"    },
	{"P1 Left"     , BIT_DIGITAL,	rainbowInputPort2 + 4, "p1 left"     },
	{"P1 Right"    , BIT_DIGITAL,	rainbowInputPort2 + 5, "p1 right"    },
	{"P1 Button 1" , BIT_DIGITAL,	rainbowInputPort2 + 6, "p1 fire 1"   },
	{"P1 Button 2" , BIT_DIGITAL,	rainbowInputPort2 + 7, "p1 fire 2"   },

	{"P2 Coin"     , BIT_DIGITAL,	rainbowInputPort1 + 1, "p2 coin"     },
	{"P2 Start"    , BIT_DIGITAL,	rainbowInputPort0 + 5, "p2 start"    },
	{"P2 Left"     , BIT_DIGITAL,	rainbowInputPort3 + 3, "p2 left"     },
	{"P2 Right"    , BIT_DIGITAL,	rainbowInputPort3 + 4, "p2 right"    },
	{"P2 Button 1" , BIT_DIGITAL,	rainbowInputPort3 + 5, "p2 fire 1"   },
	{"P2 Button 2" , BIT_DIGITAL,	rainbowInputPort3 + 6, "p2 fire 2"   },

	{"Reset"       , BIT_DIGITAL,	&drvReset            , "reset"       },
	{"Service"     , BIT_DIGITAL,	rainbowInputPort0 + 7, "service"     },
	{"Tilt"        , BIT_DIGITAL,	rainbowInputPort2 + 0, "tilt"        },
	{"Dip 1"       , BIT_DIPSWITCH,	rainbowDip + 0     , "dip"         },
	{"Dip 2"       , BIT_DIPSWITCH,	rainbowDip + 1     , "dip"         },
};

static struct BurnDIPInfo rainbowDIPList[]=
{
	// Defaults
	{0x0f, 0xff, 0xff, 0xFE, NULL                     },
	{0x10, 0xff, 0xff, 0x3F, NULL                     },

	// Dip 1
	{0   , 0xfe, 0xff, 2   , "Cabinet"                },
	{0x0f, 0x01, 0x01, 0x01, "Cocktail"               },
	{0x0f, 0x01, 0x01, 0x00, "Upright"                },

	{0   , 0xfe, 0xff, 2   , "Flip Screen"            },
	{0x0f, 0x01, 0x02, 0x02, "Off"                    },
	{0x0f, 0x01, 0x02, 0x00, "On"                     },

	{0   , 0xfe, 0   , 2   , "Test Mode"              },
	{0x0f, 0x01, 0x04, 0x04, "Off"                    },
	{0x0f, 0x01, 0x04, 0x00, "On"                     },

	{0   , 0xfe, 0   , 2   , "Demo Sounds"            },
	{0x0f, 0x01, 0x08, 0x00, "Off"                    },
	{0x0f, 0x01, 0x08, 0x08, "On"                     },

	{0   , 0xfe, 0   , 4   , "Coin A"                 },
	{0x0f, 0x01, 0x30, 0x00, "4 Coins 1 Credit"       },
	{0x0f, 0x01, 0x30, 0x10, "3 Coins 1 Credit"       },
	{0x0f, 0x01, 0x30, 0x20, "2 Coins 1 Credit"       },
	{0x0f, 0x01, 0x30, 0x30, "1 Coin 1 Credit"        },

	{0   , 0xfe, 0   , 4   , "Coin B"                 },
	{0x0f, 0x01, 0xc0, 0xc0, "1 Coin 2 Credits"       },
	{0x0f, 0x01, 0xc0, 0x80, "1 Coin 3 Credits"       },
	{0x0f, 0x01, 0xc0, 0x40, "1 Coin 4 Credits"       },
	{0x0f, 0x01, 0xc0, 0x00, "1 Coin 6 Credits"       },

	// Dip 2
	{0   , 0xfe, 0   , 4   , "Difficulty"             },
	{0x10, 0x01, 0x03, 0x02, "Easy"                   },
	{0x10, 0x01, 0x03, 0x03, "Medium"                 },
	{0x10, 0x01, 0x03, 0x01, "Hard"                   },
	{0x10, 0x01, 0x03, 0x00, "Hardest"                },

	{0   , 0xfe, 0   , 2   , "Bonus Life"             },
	{0x10, 0x01, 0x04, 0x00, "None"                   },
	{0x10, 0x01, 0x04, 0x04, "100k, 1000k"            },

	{0   , 0xfe, 0   , 2   , "Complete Bonus"         },
	{0x10, 0x01, 0x08, 0x00, "100k points"            },
	{0x10, 0x01, 0x08, 0x08, "1 Up"                   },

	{0   , 0xfe, 0   , 4   , "Lives"                  },
	{0x10, 0x01, 0x30, 0x10, "1"                      },
	{0x10, 0x01, 0x30, 0x00, "2"                      },
	{0x10, 0x01, 0x30, 0x30, "3"                      },
	{0x10, 0x01, 0x30, 0x20, "4"                      },

	{0   , 0xfe, 0   , 2   , "Language"               },
	{0x10, 0x01, 0x40, 0x00, "English"                },
	{0x10, 0x01, 0x40, 0x40, "Japanese"               },

	{0   , 0xfe, 0   , 2   , "Coin Type"              },
	{0x10, 0x01, 0x80, 0x00, "Type 1"                 },
	{0x10, 0x01, 0x80, 0x80, "Type 2"                 },
};

STDDIPINFO(rainbow);
STDINPUTINFO(rainbow);


void rainbowBankSwitch(unsigned int /*a*/, unsigned int data)
{
	Z80Bank=(data-1) & 0x03;
	unsigned char* nStartAddress = z80_rom + 0x4000+(Z80Bank*0x4000);
	nCurrentBank = Z80Bank;
	ZetMapArea(0x4000, 0x7FFF, 0, nStartAddress);
	ZetMapArea(0x4000, 0x7FFF, 2, nStartAddress);
}

void rainbowYM2151IRQHandler(int irq )
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


int rainbowInpMake()
{
	rainbowInput[0] = 0xe0;
	rainbowInput[1] = 0x00;
	rainbowInput[2] = 0xfd;
	rainbowInput[3] = 0x7e;

	for (int i = 0; i < 8; i++) {
		rainbowInput[0] -= (rainbowInputPort0[i] & 1) << i;
		rainbowInput[1] += (rainbowInputPort1[i] & 1) << i;
		rainbowInput[2] -= (rainbowInputPort2[i] & 1) << i;
		rainbowInput[3] -= (rainbowInputPort3[i] & 1) << i;

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

	return BurnHighCol(r, g, b, 0);
}

int rainbowPalUpdate()
{
	int i;
	unsigned short* ps;
	unsigned int* pd;

	for (i = 0, ps = (unsigned short*)rainbow_src_pal, pd = rainbow_pal; i < 0x400; i++, ps++, pd++) {
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
	Rom  =Next;   Next+=0x80000; // 68000 program
  RamStart =Next;
	rainbow_ram=Next;	Next+=0x7010;
	rainbow_src_pal=Next;		Next+=0x1000;
	PC090OJ_spritectrl=Next; Next+=0x04;
	PC080SN_word_0=Next;	Next+=0x10000;
	PC080SN_yscroll_word_0=Next;Next+=0x10;
	PC080SN_xscroll_word_0=Next;Next+=0x10;
	PC080SN_ctrl_word_0=Next;Next+=0x10;
	PC090OJ_word_0=Next;Next+=0x4000;
	rainbow_pal=(unsigned int*)Next; Next += 0x800 * sizeof(unsigned int);
	z80_ram=Next; Next+=0x2000;
	RamEnd   =Next;
	z80_rom=Next; Next+=0x1c000;
    MemEnd=Next;
    return 0;
}


static int LoadRoms()
{
	int nRet=0;
	// Load program roms and byteswap
	nRet=BurnLoadRom(Rom+0x00001,0,2); if (nRet!=0) return 1;
	nRet=BurnLoadRom(Rom+0x00000,1,2); if (nRet!=0) return 1;
	nRet=BurnLoadRom(Rom+0x20001,2,2); if (nRet!=0) return 1;
	nRet=BurnLoadRom(Rom+0x20000,3,2); if (nRet!=0) return 1;
	nRet=BurnLoadRom(Rom+0x40001,4,2); if (nRet!=0) return 1;
	nRet=BurnLoadRom(Rom+0x40000,5,2); if (nRet!=0) return 1;

	nRet=BurnLoadRom(z80_rom,6,1); // load z80 code rom

	unsigned char *TempGfx;
	unsigned int c,y;
	TempGfx=(unsigned char *)malloc(0xA0000);
	nRet = BurnLoadRom(TempGfx + 0x00000, 7, 1);
		if (nRet) return 1;

	ttiles=(unsigned char *)malloc(16384*64);
	memset(ttiles,0,16384*64);
	tsprites=(unsigned char *)malloc(5120*256);
	memset(tsprites,0,5120*256);

	for (c=0;c<16384;c++)
	{
		for (y=0;y<8;y++)
		{//8 12 0 4 24 28 16 2040, 44, 32, 36, 56, 60, 48, 52
			ttiles[(c*64)+0+(y*8)]=TempGfx[0x00001 + (y*4) + (c*32)] >>4;
			ttiles[(c*64)+1+(y*8)]=TempGfx[0x00001 + (y*4) + (c*32)]&0xF;
			ttiles[(c*64)+2+(y*8)]=TempGfx[0x00000 + (y*4) + (c*32)]>>4;
			ttiles[(c*64)+3+(y*8)]=TempGfx[0x00000 + (y*4) + (c*32)]&0xF;
			ttiles[(c*64)+4+(y*8)]=TempGfx[0x00003 + (y*4) + (c*32)] >>4;;
			ttiles[(c*64)+5+(y*8)]=TempGfx[0x00003 + (y*4) + (c*32)]&0xF;
			ttiles[(c*64)+6+(y*8)]=TempGfx[0x00002 + (y*4) + (c*32)]>>4;
			ttiles[(c*64)+7+(y*8)]=TempGfx[0x00002 + (y*4) + (c*32)]&0xF;
		}
	}
	memset(TempGfx,0,0xa0000);
	nRet = BurnLoadRom(TempGfx + 0x00000, 8, 1);
		if (nRet) return 1;
	nRet = BurnLoadRom(TempGfx + 0x80000, 9, 2);
		if (nRet) return 1;
	nRet = BurnLoadRom(TempGfx + 0x80001, 10, 2);
		if (nRet) return 1;

	for (c = 0; c < 5120; c ++) {
		for (y = 0; y < 16; y ++) { //8 12 0 4 24 28 16 20 40, 44, 32, 36, 56, 60, 48, 52
			tsprites[(c*256)+0+(y*16)] = TempGfx[0x00001 + (y * 8) + (c * 128)] >> 4;
			tsprites[(c*256)+1+(y*16)] = TempGfx[0x00001 + (y * 8) + (c * 128)] & 0x0f;
			tsprites[(c*256)+2+(y*16)] = TempGfx[0x00000 + (y * 8) + (c * 128)] >> 4;
			tsprites[(c*256)+3+(y*16)] = TempGfx[0x00000 + (y * 8) + (c * 128)] & 0x0f;
			tsprites[(c*256)+4+(y*16)] = TempGfx[0x00003 + (y * 8) + (c * 128)] >> 4;
			tsprites[(c*256)+5+(y*16)] = TempGfx[0x00003 + (y * 8) + (c * 128)] & 0x0f;
			tsprites[(c*256)+6+(y*16)] = TempGfx[0x00002 + (y * 8) + (c * 128)] >> 4;
			tsprites[(c*256)+7+(y*16)] = TempGfx[0x00002 + (y * 8) + (c * 128)] & 0x0f;
			tsprites[(c*256)+8+(y*16)] = TempGfx[0x00005 + (y * 8) + (c * 128)] >> 4;
			tsprites[(c*256)+9+(y*16)] = TempGfx[0x00005 + (y * 8) + (c * 128)] & 0x0f;
			tsprites[(c*256)+10+(y*16)] = TempGfx[0x00004 + (y * 8) + (c * 128)] >> 4;
			tsprites[(c*256)+11+(y*16)] = TempGfx[0x00004 + (y * 8) + (c * 128)] & 0x0f;
			tsprites[(c*256)+12+(y*16)] = TempGfx[0x00007 + (y * 8) + (c * 128)] >> 4;
			tsprites[(c*256)+13+(y*16)] = TempGfx[0x00007 + (y * 8) + (c * 128)] & 0x0f;
			tsprites[(c*256)+14+(y*16)] = TempGfx[0x00006 + (y * 8) + (c * 128)] >> 4;
			tsprites[(c*256)+15+(y*16)] = TempGfx[0x00006 + (y * 8) + (c * 128)] & 0x0f;
		}
	}
	free(TempGfx);
	return nRet;
  }

unsigned char __fastcall rainbowZ80Read(unsigned short a)
{
	switch (a)
	{
	case (0x9001):
		return BurnYM2151ReadStatus();
	case (0xa001):
		return tc0140_slave_comm_r();
	default:
		return 0;
	}
}

void __fastcall rainbowZ80Write(unsigned short a,unsigned char d)
{
	switch (a)
	{
	case 0x9000:
		BurnYM2151SelectRegister(d);
		return;
	case 0x9001:
		BurnYM2151WriteRegister(d);
		return;
	case 0xa000:
		tc0140_slave_port_w(d);
		return;
	case 0xa001:
		tc0140_slave_comm_w(d);
		return;
	default:
		return;
	}


}


unsigned short __fastcall rainbowReadWord(unsigned int a)
{
	if (a>=0x800000&&a<=0x8007ff)
	{
		return rainbow_cchip_ram_r((a-0x800000)/2);
	}

	if (a>=0x800802&&a<=0x800803)
	{
		return rainbow_cchip_ctrl_r();
	}

	if (a>=0x390000&&a<=0x390003)
	{
		return rainbowDip[0]; //dip a
	}
	if (a>=0x3b0000&&a<=0x3b0003)
	{
		return rainbowDip[1]; //dip b
	}
	switch (a)
	{
	case 0x3e0003:
		return tc0140_comm_r();
	default:
		return 0;
	}
}

unsigned char __fastcall rainbowReadByte(unsigned int a)
{
	if (a>=0x800000&&a<=0x8007ff)
	{
		return rainbow_cchip_ram_r((a-0x800000)/2);
	}

	if (a>=0x800802&&a<=0x800803)
	{
		return rainbow_cchip_ctrl_r();
	}

	switch (a)
	{
	case 0x3e0003:
		return tc0140_comm_r();
	default:
		return 0;
	}

}

void __fastcall rainbowWriteWord(unsigned int a,unsigned short d)
{
	switch (a){

	case 0xc20000:
		if (PC080SN_ctrl_word_0[0]&0x01) {
			d= -d;
		}
		p1scrolly=-d;
		return;

	case 0xc20002:
		if (PC080SN_ctrl_word_0[0]&0x01) {
			d= -d;
		}
		p2scrolly=-d;
		return;

	case 0xc40000:
		if (PC080SN_ctrl_word_0[0]&0x01) {
			d= -d;
		}
		p1scrollx=-d;
		return;

	case 0xc40002:
		if (PC080SN_ctrl_word_0[0]&0x01) {
			d= -d;
		}
		p2scrollx=-d;
		return;

	default:

		return;

	}
}

void __fastcall rainbowWriteByte(unsigned int a,unsigned char d)
{
	if (a>=0x800000&&a<=0x8007ff)
	{
		rainbow_cchip_ram_w((a-0x800001)/2,d);
		return;
	}

	if (a>=0x800802&&a<=0x800803)
	{
		return;
	}

	if (a>=0x800c00&&a<=0x800c01)
	{
		rainbow_cchip_bank_w(d);
		return;
	}

	switch (a)
	{
	case 0x3e0001:
		tc0140_port_w(d);
		return;
	case 0x3e0003:
		tc0140_comm_w(d);
		return;
	}
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

int rainbowInit()
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
	SekMapMemory(    Rom  ,0x000000,0x07ffff,SM_ROM); // 68000 Rom
	SekMapMemory(rainbow_ram,0x10c000,0x10ffff,SM_RAM); //0x4000
	SekMapMemory(rainbow_src_pal,0x200000,0x200fff,SM_RAM);
	SekMapMemory(rainbow_ram+0x4000,0x201000,0x203fff,SM_RAM); //0x3000
	SekMapMemory(PC090OJ_spritectrl,0x3a0000,0x3a0001,SM_WRITE);
	SekMapMemory(rainbow_ram+0x7000,0x3c0000,0x3c0003,SM_RAM);
	SekMapMemory(PC080SN_word_0,0xc00000,0xc0ffff,SM_RAM);
	SekMapMemory(PC080SN_ctrl_word_0,0xc50000,0xc50003,SM_WRITE);
	SekMapMemory(PC090OJ_word_0,0xd00000,0xd03fff,SM_RAM);
	SekSetWriteWordHandler(0, rainbowWriteWord);
	SekSetReadWordHandler(0, rainbowReadWord);
	SekSetReadByteHandler(0, rainbowReadByte);
	SekSetWriteByteHandler(0, rainbowWriteByte);
	SekClose();
	// ------------------------------------------------
	// ----------------- Cpu 2 Z80 ------------------------
	ZetInit(1);
	ZetOpen(0);
	ZetSetReadHandler(rainbowZ80Read);
	ZetSetWriteHandler(rainbowZ80Write);
	ZetMapArea (0x0000,0x3FFF,0,z80_rom);
	ZetMapArea (0x0000,0x3FFF,2,z80_rom);
//	ZetMapArea (0x4000,0x7FFF,0,z80_rom+0x4000);
//	ZetMapArea (0x4000,0x7FFF,2,z80_rom+0x4000);
	ZetMapArea (0x8000,0x8FFF,0,z80_ram);
	ZetMapArea (0x8000,0x8FFF,2,z80_ram);
	ZetMapArea (0x8000,0x8FFF,1,z80_ram);
	ZetMemEnd();
	ZetMemCallback(0x9000, 0xa001, 0);			// Read
	ZetMemCallback(0x9000, 0xa001, 1);			// Write
	ZetReset();
	ZetClose();
	//-------------------------------------------------

	//-------- sound stuff ----------------------------
	//---------- YM2151 Setup ----------------------
	BurnYM2151Init(4000000, 50.0);
	BurnYM2151SetIrqHandler(&rainbowYM2151IRQHandler);
	BurnYM2151SetPortHandler(&rainbowBankSwitch);
	nCurrentBank=-1;

	//--------------------------------------------------
	// ------- GFX Init -------------------
	taito_pal=rainbow_pal;
	init_taito_gfx();
	//-------------------------------------
	if (!strcmp(BurnDrvGetTextA(DRV_NAME), "rainbowe"))
	{
		rainbow_cchip_init(1); // protection chip
	} else
	{
		rainbow_cchip_init(0); // protection chip
	}
	drvDoReset();
	return 0;
	}

int rainbowExit()
{
	rainbow_cchip_exit();
	free(tsprites);
	free(ttiles);
	BurnYM2151Exit();
	SekExit(); // Deallocate 68000
	ZetExit();
	if (Mem!=NULL)
		free(Mem);
	Mem=NULL;
	return 0;
}


static int rainbowGFX()
{
	PC080SN_bg();
	PC090OJ_draw_sprites();
	PC080SN_fg();
	return 0;
}


static int rainbowDraw()
{
	rainbowPalUpdate();
	rainbowGFX();
	return 0;
}



int rainbowFrame()
{
	if (drvReset) {	// Reset machine
		drvDoReset();
	}

	rainbowInpMake();
	cchip_timer();


	int nInterleave = 10;

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

	SekSetIRQLine(4, SEK_IRQSTATUS_AUTO);
	ZetClose();
	SekClose();

	if (pBurnDraw) {
		rainbowDraw();														// Draw screen if needed
	}

	return 0;
}

static int rainbowScan(int nAction,int *pnMin)
{
	struct BurnArea ba;

	if (pnMin) {						// Return minimum compatible version
		*pnMin = 0x029521;
	}

	if (nAction & ACB_VOLATILE) {		// Scan volatile ram

		memset(&ba, 0, sizeof(ba));
    ba.Data		= RamStart;
		ba.nLen		= RamEnd-RamStart;
		ba.szName	= "All Ram";
		BurnAcb(&ba);

		SekScan(nAction);										// Scan 68000 state

		ZetOpen(0);
		ZetScan(nAction);										// Scan Z80 state
		ZetClose();

		SCAN_VAR(Z80Bank);
		SCAN_VAR(nCurrentBank);

		SCAN_VAR(nCyclesTotal);
		SCAN_VAR(nCyclesSegment);

		SCAN_VAR(rainbowInputPort0);
		SCAN_VAR(rainbowInputPort1);
		SCAN_VAR(rainbowInputPort2);
		SCAN_VAR(rainbowInputPort3);

		SCAN_VAR(rainbowDip);

		BurnYM2151Scan(nAction);
	}

	return 0;
}


/// Rom information
static struct BurnRomInfo rainbowRomDesc[] = {
	{ "b22-10-1.19",   0x10000, 0xe34a50ca, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "b22-11-1.20",   0x10000, 0x6a31a093, BRF_ESS | BRF_PRG }, //  1            (odd)
	{ "b22-08-1.21",   0x10000, 0x15d6e17a, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "b22-09-1.22",   0x10000, 0x454e66bc, BRF_ESS | BRF_PRG }, //  1            (odd)
	{ "b22-03.23",     0x20000, 0x3ebb0fb8, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "b22-04.24",     0x20000, 0x91625e7f, BRF_ESS | BRF_PRG }, //  1            (odd)

	{ "b22-14.43",     0x10000, 0x113c1a5b, BRF_ESS | BRF_PRG }, //  2 z80 code

	{ "b22-01.2",      0x80000, 0xb76c9168, BRF_GRA },			 //  2 8x8 tile bitmaps

	{ "b22-01.5",      0x80000, 0x1b87ecf0, BRF_GRA },			 //  6 Sprite
	{ "b22-12.7",      0x10000, 0x67a76dc6, BRF_GRA },			 //  7
	{ "b22-13.6",      0x10000, 0x2fda099f, BRF_GRA },			 //  8
};


STD_ROM_PICK(rainbow);
STD_ROM_FN(rainbow);

// Rom info
static struct BurnRomInfo rainbowoRomDesc[] = {
	{ "b22-10.19",     0x10000, 0x3b013495, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "b22-11.20",     0x10000, 0x80041a3d, BRF_ESS | BRF_PRG }, //  1            (odd)
	{ "b22-08.21",     0x10000, 0x962fb845, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "b22-09.22",     0x10000, 0xf43efa27, BRF_ESS | BRF_PRG }, //  1            (odd)
	{ "b22-03.23",     0x20000, 0x3ebb0fb8, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "b22-04.24",     0x20000, 0x91625e7f, BRF_ESS | BRF_PRG }, //  1            (odd)

	{ "b22-14.43",     0x10000, 0x113c1a5b, BRF_ESS | BRF_PRG }, //  2 z80 code

	{ "b22-01.2",      0x80000, 0xb76c9168, BRF_GRA },			 //  2 8x8 tile bitmaps

	{ "b22-01.5",      0x80000, 0x1b87ecf0, BRF_GRA },			 //  6 Sprite
	{ "b22-12.7",      0x10000, 0x67a76dc6, BRF_GRA },			 //  7
	{ "b22-13.6",      0x10000, 0x2fda099f, BRF_GRA },			 //  8
};


STD_ROM_PICK(rainbowo);
STD_ROM_FN(rainbowo);

// Rom info
static struct BurnRomInfo rainboweRomDesc[] = {
	{ "b39-01.19",     0x10000, 0x50690880, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "b39-02.20",     0x10000, 0x4dead71f, BRF_ESS | BRF_PRG }, //  1            (odd)
	{ "b39-03.21",     0x10000, 0x4a4cb785, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "b39-04.22",     0x10000, 0x4caa53bd, BRF_ESS | BRF_PRG }, //  1            (odd)
	{ "b22-03.23",     0x20000, 0x3ebb0fb8, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "b22-04.24",     0x20000, 0x91625e7f, BRF_ESS | BRF_PRG }, //  1            (odd)

	{ "b22-14.43",     0x10000, 0x113c1a5b, BRF_ESS | BRF_PRG }, //  2 z80 code

	{ "b22-01.2",      0x80000, 0xb76c9168, BRF_GRA },			 //  2 8x8 tile bitmaps

	{ "b22-01.5",      0x80000, 0x1b87ecf0, BRF_GRA },			 //  6 Sprite
	{ "b22-12.7",      0x10000, 0x67a76dc6, BRF_GRA },			 //  7
	{ "b22-13.6",      0x10000, 0x2fda099f, BRF_GRA },			 //  8
};


STD_ROM_PICK(rainbowe);
STD_ROM_FN(rainbowe);

struct BurnDriver BurnDrvrainbow = {
	"rainbow", NULL, NULL, "1987",
	"Rainbow Islands (new version)\0", NULL, "Taito", "Custom Taito",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_MISC_MISC,
	NULL,rainbowRomInfo,rainbowRomName,rainbowInputInfo, rainbowDIPInfo,
	rainbowInit,rainbowExit,rainbowFrame,NULL,rainbowScan,
	&taitoRecalcPal,320,240,4,3
};

struct BurnDriver BurnDrvrainbowo = {
	"rainbowo", "rainbow", NULL, "1987",
	"Rainbow Islands (old version)\0", NULL, "Taito", "Custom Taito",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_MISC_MISC,
	NULL,rainbowoRomInfo,rainbowoRomName,rainbowInputInfo, rainbowDIPInfo,
	rainbowInit,rainbowExit,rainbowFrame,NULL,rainbowScan,
	&taitoRecalcPal,320,240,4,3
};

struct BurnDriver BurnDrvrainbowe = {
	"rainbowe", "rainbow", NULL, "1988",
	"Rainbow Islands (Extra)\0", NULL, "Taito", "Custom Taito",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_MISC_MISC,
	NULL,rainboweRomInfo,rainboweRomName,rainbowInputInfo, rainbowDIPInfo,
	rainbowInit,rainbowExit,rainbowFrame,NULL,rainbowScan,
	&taitoRecalcPal,320,240,4,3
};
