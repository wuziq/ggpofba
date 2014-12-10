/*
Rastan driver
=============
Part of FBAs Taito 68k hardware drivers
Credits: Mame team, Raine team
Coding by KEV, with help from Treble Winner and Jan_Klaassen
*/

#include "taito.h"
#include "msm5205.h"
static unsigned char *Mem=NULL,*MemEnd=NULL;
static unsigned char *RamStart=NULL,*RamEnd=NULL;
static unsigned char *Rom=NULL;
static unsigned char *rastan_ram=NULL,*rastan_src_pal=NULL;
static unsigned char drvReset = 0;

static unsigned char *z80_rom=NULL,*z80_ram=NULL;
static unsigned int *rastan_pal=NULL;

// Z80 ROM bank
static int Z80Bank;
static int nCurrentBank;

static int nCyclesTotal[2];
static int nCyclesSegment;

unsigned char RastanInputPort0[8], RastanInputPort1[8], RastanInputPort2[8];
unsigned char RastanInput[3];
unsigned char RastanDip[2];
static struct BurnInputInfo rastanInputList[]=
{
	{"P1 Coin"     , BIT_DIGITAL,	RastanInputPort2 + 5, "p1 coin"     },
	{"P1 Start"    , BIT_DIGITAL,	RastanInputPort2 + 3, "p1 start"    },
	{"P1 Up"       , BIT_DIGITAL,	RastanInputPort0 + 0, "p1 up"       },
	{"P1 Down"     , BIT_DIGITAL,	RastanInputPort0 + 1, "p1 down"     },
	{"P1 Left"     , BIT_DIGITAL,	RastanInputPort0 + 2, "p1 left"     },
	{"P1 Right"    , BIT_DIGITAL,	RastanInputPort0 + 3, "p1 right"    },
	{"P1 Button 1" , BIT_DIGITAL,	RastanInputPort0 + 4, "p1 fire 1"   },
	{"P1 Button 2" , BIT_DIGITAL,	RastanInputPort0 + 5, "p1 fire 2"   },

	{"P2 Coin"     , BIT_DIGITAL,	RastanInputPort2 + 6, "p2 coin"     },
	{"P2 Start"    , BIT_DIGITAL,	RastanInputPort2 + 4, "p2 start"    },
	{"P2 Up"       , BIT_DIGITAL,	RastanInputPort1 + 0, "p2 up"       },
	{"P2 Down"     , BIT_DIGITAL,	RastanInputPort1 + 1, "p2 down"     },
	{"P2 Left"     , BIT_DIGITAL,	RastanInputPort1 + 2, "p2 left"     },
	{"P2 Right"    , BIT_DIGITAL,	RastanInputPort1 + 3, "p2 right"    },
	{"P2 Button 1" , BIT_DIGITAL,	RastanInputPort1 + 4, "p2 fire 1"   },
	{"P2 Button 2" , BIT_DIGITAL,	RastanInputPort1 + 5, "p2 fire 2"   },

	{"Reset"	     , BIT_DIGITAL,	&drvReset			      , "reset"		    },
	{"Service"     , BIT_DIGITAL,	RastanInputPort2 + 0, "service"     },
	{"Tilt"        , BIT_DIGITAL,	RastanInputPort2 + 2, "tilt"        },
	{"Dip 1"       , BIT_DIPSWITCH,	RastanDip + 0     , "dip"         },
	{"Dip 2"       , BIT_DIPSWITCH,	RastanDip + 1     , "dip"         },
};

STDINPUTINFO(rastan);

static struct BurnDIPInfo rastanCoinageDIPList[] =
{
	// Taito Coinage World
	{0   , 0xfe, 0   , 4   , "Coin A"                 },
	{0x13, 0x01, 0x30, 0x30, "4 Coins 1 Credit"       },
	{0x13, 0x01, 0x30, 0x20, "3 Coins 1 Credit"       },
	{0x13, 0x01, 0x30, 0x10, "2 Coins 1 Credit"       },
	{0x13, 0x01, 0x30, 0x00, "1 Coin 1 Credit"        },

	{0   , 0xfe, 0   , 4   , "Coin B"                 },
	{0x13, 0x01, 0xc0, 0xc0, "1 Coin 6 Credits"       },
	{0x13, 0x01, 0xc0, 0x80, "1 Coin 4 Credits"       },
	{0x13, 0x01, 0xc0, 0x40, "1 Coin 3 Credits"       },
	{0x13, 0x01, 0xc0, 0x00, "1 Coin 2 Credits"       },
};

static struct BurnDIPInfo rastsagaCoinageDIPList[] =
{
	// Taito Coinage Japan and US
	{0   , 0xfe, 0   , 4   , "Coin A"                 },
	{0x13, 0x01, 0x30, 0x20, "2 Coins 1 Credit"       },
	{0x13, 0x01, 0x30, 0x00, "1 Coin 1 Credit"        },
	{0x13, 0x01, 0x30, 0x30, "2 Coins 3 Credits"      },
	{0x13, 0x01, 0x30, 0x10, "1 Coin 2 Credits"       },

	{0   , 0xfe, 0   , 4   , "Coin B"                 },
	{0x13, 0x01, 0xc0, 0x80, "2 Coins 1 Credit"       },
	{0x13, 0x01, 0xc0, 0x00, "1 Coin 1 Credit"        },
	{0x13, 0x01, 0xc0, 0xc0, "2 Coins 3 Credits"      },
	{0x13, 0x01, 0xc0, 0x40, "1 Coin 2 Credits"       },
};

static struct BurnDIPInfo rastanDIPList[]=
{
	// Defaults
	{0x13, 0xff, 0xff, 0x00, NULL                     },
	{0x14, 0xff, 0xff, 0x00, NULL                     },

	// Dip 1
	{0   , 0xfe, 0   , 2   , "Cabinet"                },
	{0x13, 0x01, 0x01, 0x00, "Cocktail"               },
	{0x13, 0x01, 0x01, 0x01, "Upright"                },

	{0   , 0xfe, 0   , 2   , "Flip Screen"            },
	{0x13, 0x01, 0x02, 0x00, "Off"                    },
	{0x13, 0x01, 0x02, 0x02, "On"                     },

	{0   , 0xfe, 0   , 2   , "Test Mode"              },
	{0x13, 0x01, 0x04, 0x00, "Off"                    },
	{0x13, 0x01, 0x04, 0x04, "On"                     },

	// Dip 2
	{0   , 0xfe, 0   , 4   , "Difficulty"             },
	{0x14, 0x01, 0x03, 0x01, "Easy"                   },
	{0x14, 0x01, 0x03, 0x00, "Medium"                 },
	{0x14, 0x01, 0x03, 0x02, "Hard"                   },
	{0x14, 0x01, 0x03, 0x03, "Hardest"                },

	{0   , 0xfe, 0   , 4   , "Bonus Life"             },
	{0x14, 0x01, 0x0c, 0x00, "100000"                 },
	{0x14, 0x01, 0x0c, 0x04, "150000"                 },
	{0x14, 0x01, 0x0c, 0x08, "200000"                 },
	{0x14, 0x01, 0x0c, 0x0c, "250000"                 },

	{0   , 0xfe, 0   , 4   , "Lives"                  },
	{0x14, 0x01, 0x30, 0x00, "3"                      },
	{0x14, 0x01, 0x30, 0x10, "4"                      },
	{0x14, 0x01, 0x30, 0x20, "5"                      },
	{0x14, 0x01, 0x30, 0x30, "6"                      },

	{0   , 0xfe, 0   , 2   , "Allow Continue"         },
	{0x14, 0x01, 0x40, 0x40, "No"                     },
	{0x14, 0x01, 0x40, 0x00, "Yes"                    },
};

STDDIPINFOEXT(rastan, rastanCoinage, rastan);
STDDIPINFOEXT(rastsaga, rastsagaCoinage, rastan);


void rastanBankSwitch(unsigned int /*a*/, unsigned int data)
{
	Z80Bank=(data^1) & 0x01;
  	if (Z80Bank != nCurrentBank) {
  			unsigned char* nStartAddress = z80_rom + 0x4000+(Z80Bank*0x4000);
  			nCurrentBank = Z80Bank;
  			ZetMapArea(0x4000, 0x7FFF, 0, nStartAddress);
  			ZetMapArea(0x4000, 0x7FFF, 2, nStartAddress);
		}
}

int rastanInpMake()
{
	RastanInput[0] = RastanInput[1] = 0xff;
	RastanInput[2] = 0x1f;

	for (int i = 0; i < 8; i++) {
		RastanInput[0] -= (RastanInputPort0[i] & 1) << i;
		RastanInput[1] -= (RastanInputPort1[i] & 1) << i;
		if (i < 5) {
			RastanInput[2] -= (RastanInputPort2[i] & 1) << i;
		} else {
			RastanInput[2] |= (RastanInputPort2[i] & 1) << i;
		}
	}

	return 0;
}

void RastanYM2151IRQHandler(int irq )
{
	if (irq)
	{
		ZetRaiseIrq(0);
	}
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

int rastanPalUpdate()
{
	int i;
	unsigned short* ps;
	unsigned int* pd;

	for (i = 0, ps = (unsigned short*)rastan_src_pal, pd = rastan_pal; i < 0x800; i++, ps++, pd++) {
		*pd = CalcCol(*ps);
	}
	return 0;
}

////
// This routine is called first to determine how much memory is needed (MemEnd-(unsigned char *)0),

static int MemIndex()
{
	unsigned char *Next; Next=Mem;
	Rom  =Next;						Next+=0x60000; // 68000 program
  RamStart =Next;
	rastan_ram=Next;				Next+=0x4020;
	rastan_src_pal=Next;			Next+=0x1000;
	PC090OJ_spritectrl=Next;		Next+=0x10;
	PC080SN_word_0=Next;			Next+=0x10000;
	PC080SN_yscroll_word_0=Next;	Next+=0x10;
	PC080SN_xscroll_word_0=	Next;	Next+=0x10;
	PC080SN_ctrl_word_0=Next;		Next+=0x10;
	PC090OJ_word_0=Next;			Next+=0x4000;
	rastan_pal=(unsigned int*)Next; Next += 0x800 * sizeof(unsigned int);
	MSM5205ROM=Next;				Next+=0x10000;
	z80_ram=Next;					Next+=0x2000;
	RamEnd   =Next;
	z80_rom=Next;					Next+=0x10000;
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
	nRet=BurnLoadRom(MSM5205ROM,15,1); // adcpm

	ttiles=(unsigned char *)malloc(16384*64);
	memset(ttiles,0,16384*64);
	tsprites=(unsigned char *)malloc(5120*256);
	memset(tsprites,0,5120*256);

	unsigned char *TempGfx;
	unsigned int c,y;
	TempGfx=(unsigned char *)malloc(0x40000);
	nRet = BurnLoadRom(TempGfx + 0x00000, 11, 1); if (nRet) return 1;
	nRet = BurnLoadRom(TempGfx + 0x20000, 13, 1); if (nRet) return 1;
	for (c = 0; c < 2048; c ++) {
		for (y = 0; y < 16; y ++) { //8 12 0 4 24 28 16 20 40, 44, 32, 36, 56, 60, 48, 52
			tsprites[(c*256)+0+(y*16)] = TempGfx[0x00000 + (y * 4) + (c * 64)] >> 4;
			tsprites[(c*256)+1+(y*16)] = TempGfx[0x00000 + (y * 4) + (c * 64)] & 0x0f;
			tsprites[(c*256)+2+(y*16)] = TempGfx[0x20000 + (y * 4) + (c * 64)] >> 4;
			tsprites[(c*256)+3+(y*16)] = TempGfx[0x20000 + (y * 4) + (c * 64)] & 0x0f;
			tsprites[(c*256)+4+(y*16)] = TempGfx[0x00001 + (y * 4) + (c * 64)] >> 4;
			tsprites[(c*256)+5+(y*16)] = TempGfx[0x00001 + (y * 4) + (c * 64)] & 0x0f;
			tsprites[(c*256)+6+(y*16)] = TempGfx[0x20001 + (y * 4) + (c * 64)] >> 4;
			tsprites[(c*256)+7+(y*16)] = TempGfx[0x20001 + (y * 4) + (c * 64)] & 0x0f;
			tsprites[(c*256)+8+(y*16)] = TempGfx[0x00002 + (y * 4) + (c * 64)] >> 4;
			tsprites[(c*256)+9+(y*16)] = TempGfx[0x00002 + (y * 4) + (c * 64)] & 0x0f;
			tsprites[(c*256)+10+(y*16)] = TempGfx[0x20002 + (y * 4) + (c * 64)] >> 4;
			tsprites[(c*256)+11+(y*16)] = TempGfx[0x20002 + (y * 4) + (c * 64)] & 0x0f;
			tsprites[(c*256)+12+(y*16)] = TempGfx[0x00003 + (y * 4) + (c * 64)] >> 4;
			tsprites[(c*256)+13+(y*16)] = TempGfx[0x00003 + (y * 4) + (c * 64)] & 0x0f;
			tsprites[(c*256)+14+(y*16)] = TempGfx[0x20003 + (y * 4) + (c * 64)] >> 4;
			tsprites[(c*256)+15+(y*16)] = TempGfx[0x20003 + (y * 4) + (c * 64)] & 0x0f;
		}
	}
	nRet = BurnLoadRom(TempGfx + 0x00000, 12, 1); if (nRet) return 1;
	nRet = BurnLoadRom(TempGfx + 0x20000, 14, 1); if (nRet) return 1;
	for (c = 0; c < 2048; c ++) {
		for (y = 0; y < 16; y ++) { //8 12 0 4 24 28 16 20 40, 44, 32, 36, 56, 60, 48, 52
			tsprites[((c+2048)*256)+0+(y*16)] = TempGfx[0x00000 + (y * 4) + (c * 64)] >> 4;
			tsprites[((c+2048)*256)+1+(y*16)] = TempGfx[0x00000 + (y * 4) + (c * 64)] & 0x0f;
			tsprites[((c+2048)*256)+2+(y*16)] = TempGfx[0x20000 + (y * 4) + (c * 64)] >> 4;
			tsprites[((c+2048)*256)+3+(y*16)] = TempGfx[0x20000 + (y * 4) + (c * 64)] & 0x0f;
			tsprites[((c+2048)*256)+4+(y*16)] = TempGfx[0x00001 + (y * 4) + (c * 64)] >> 4;
			tsprites[((c+2048)*256)+5+(y*16)] = TempGfx[0x00001 + (y * 4) + (c * 64)] & 0x0f;
			tsprites[((c+2048)*256)+6+(y*16)] = TempGfx[0x20001 + (y * 4) + (c * 64)] >> 4;
			tsprites[((c+2048)*256)+7+(y*16)] = TempGfx[0x20001 + (y * 4) + (c * 64)] & 0x0f;
			tsprites[((c+2048)*256)+8+(y*16)] = TempGfx[0x00002 + (y * 4) + (c * 64)] >> 4;
			tsprites[((c+2048)*256)+9+(y*16)] = TempGfx[0x00002 + (y * 4) + (c * 64)] & 0x0f;
			tsprites[((c+2048)*256)+10+(y*16)] = TempGfx[0x20002 + (y * 4) + (c * 64)] >> 4;
			tsprites[((c+2048)*256)+11+(y*16)] = TempGfx[0x20002 + (y * 4) + (c * 64)] & 0x0f;
			tsprites[((c+2048)*256)+12+(y*16)] = TempGfx[0x00003 + (y * 4) + (c * 64)] >> 4;
			tsprites[((c+2048)*256)+13+(y*16)] = TempGfx[0x00003 + (y * 4) + (c * 64)] & 0x0f;
			tsprites[((c+2048)*256)+14+(y*16)] = TempGfx[0x20003 + (y * 4) + (c * 64)] >> 4;
			tsprites[((c+2048)*256)+15+(y*16)] = TempGfx[0x20003 + (y * 4) + (c * 64)] & 0x0f;
		}
	}
	nRet = BurnLoadRom(TempGfx + 0x00000, 7, 1); if (nRet) return 1;
	nRet = BurnLoadRom(TempGfx + 0x20000, 9, 1); if (nRet) return 1;
	for (c=0;c<8192;c++)
	{
		for (y=0;y<8;y++)
		{//8 12 0 4 24 28 16 2040, 44, 32, 36, 56, 60, 48, 52
			ttiles[(c*64)+0+(y*8)]=TempGfx[0x00000 + (y*2) + (c*16)] >>4;
			ttiles[(c*64)+1+(y*8)]=TempGfx[0x00000 + (y*2) + (c*16)]&0xF;
			ttiles[(c*64)+2+(y*8)]=TempGfx[0x20000 + (y*2) + (c*16)]>>4;
			ttiles[(c*64)+3+(y*8)]=TempGfx[0x20000 + (y*2) + (c*16)]&0xF;
			ttiles[(c*64)+4+(y*8)]=TempGfx[0x00001 + (y*2) + (c*16)] >>4;;
			ttiles[(c*64)+5+(y*8)]=TempGfx[0x00001 + (y*2) + (c*16)]&0xF;
			ttiles[(c*64)+6+(y*8)]=TempGfx[0x20001 + (y*2) + (c*16)]>>4;
			ttiles[(c*64)+7+(y*8)]=TempGfx[0x20001 + (y*2) + (c*16)]&0xF;
		}
	}
	nRet = BurnLoadRom(TempGfx + 0x00000, 8, 1); if (nRet) return 1;
	nRet = BurnLoadRom(TempGfx + 0x20000, 10, 1); if (nRet) return 1;
	for (c=0;c<8192;c++)
	{
		for (y=0;y<8;y++)
		{//8 12 0 4 24 28 16 2040, 44, 32, 36, 56, 60, 48, 52
			ttiles[((c+8192)*64)+0+(y*8)]=TempGfx[0x00000 + (y*2) + (c*16)] >>4;
			ttiles[((c+8192)*64)+1+(y*8)]=TempGfx[0x00000 + (y*2) + (c*16)]&0xF;
			ttiles[((c+8192)*64)+2+(y*8)]=TempGfx[0x20000 + (y*2) + (c*16)]>>4;
			ttiles[((c+8192)*64)+3+(y*8)]=TempGfx[0x20000 + (y*2) + (c*16)]&0xF;
			ttiles[((c+8192)*64)+4+(y*8)]=TempGfx[0x00001 + (y*2) + (c*16)] >>4;;
			ttiles[((c+8192)*64)+5+(y*8)]=TempGfx[0x00001 + (y*2) + (c*16)]&0xF;
			ttiles[((c+8192)*64)+6+(y*8)]=TempGfx[0x20001 + (y*2) + (c*16)]>>4;
			ttiles[((c+8192)*64)+7+(y*8)]=TempGfx[0x20001 + (y*2) + (c*16)]&0xF;
		}
	}
	free(TempGfx);
	return nRet;
  }

unsigned char __fastcall RastanZ80Read(unsigned short a)
{
	switch (a)
	{
	case (0x9001):
		return BurnYM2151ReadStatus();
	case (0xa001):
		return tc0140_slave_comm_r();
	default:
		bprintf(PRINT_NORMAL, _T("z80 read %x\n"),a);
		return 0xff;
	}
}

void __fastcall RastanZ80Write(unsigned short a,unsigned char d)
{
	switch (a)
	{
	case 0xb000:
		{
		UINT8 *rom = MSM5205ROM;
		int len = 0x10000;
		int start = d << 8;
		int end;

		/* look for end of sample */
		end = (start + 3) & ~3;
		while (end < len && *((unsigned int *)(&rom[end])) != 0x08080808)
			end += 4;

		MSM5205Play(start,(end-start)*2,0);
		}
		return;
	case 0xc000:
		return;
	case 0xd000:
		return;
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
		bprintf(PRINT_NORMAL, _T("z80write %x\n"),a);
	}


}


unsigned short __fastcall rastanReadWord(unsigned int a)
{
	switch (a)
	{
	case 0x390000:
		return RastanInput[0];
	case 0x390002:
		return RastanInput[1];
	case 0x390004:
		return RastanInput[2];
	default:
		bprintf(PRINT_NORMAL, _T("readword %x\n"), a);
		return 0;
	}
}

unsigned char __fastcall rastanReadByte(unsigned int a)
{
	switch (a)
	{
	case 0x390001:
		return RastanInput[0];
	case 0x390003:
		return RastanInput[1];
	case 0x390005:
		return RastanInput[2];
	case 0x390007:
		return RastanInput[2];
	case 0x390009:
		return 0xff-  RastanDip[0];  //dipa
	case 0x39000b:
		return 0xff -  RastanDip[1]; //dipb
	case 0x3e0003:
		return tc0140_comm_r();
	default:
		bprintf(PRINT_NORMAL, _T("readbyte %x\n"),a);
		return 0;
	}

}



 void __fastcall rastanWriteWord(unsigned int a,unsigned short d)
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
		bprintf(PRINT_NORMAL, _T("Word%x,%x\n"),a,d);
		return;

	}

}


void __fastcall rastanWriteByte(unsigned int a,unsigned char d)
{
	switch (a)
	{
	case 0x3e0001:
		tc0140_port_w(d);
		return;
	case 0x3e0003:
		tc0140_comm_w(d);
		return;
	default:
		bprintf(PRINT_NORMAL, _T("writebyte %x to %x\n"),a,d);
	}

}

static int drvDoReset()
{
	SekOpen(0);
	SekReset();
	SekClose();
	ZetOpen(0);
	ZetReset();
	ZetRun(40000000/60);
	ZetClose();
	BurnYM2151Reset();
	MSM5205Reset(0);
	return 0;
}

int rastanInit()
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
	taito_pal=rastan_pal;
	init_taito_gfx();

	// Map in memory:
	// ----------------- Cpu 1 ------------------------
	SekInit(0, 0x68000); // Allocate 1 68000
	SekOpen(0);
	SekMapMemory(    Rom  ,0x000000,0x05ffff,SM_ROM); // 68000 Rom
	SekMapMemory(rastan_ram,0x10c000,0x10ffff,SM_RAM); //0x4000
	SekMapMemory(rastan_src_pal,0x200000,0x200fff,SM_RAM);
	SekMapMemory(rastan_ram+0x4000,0x350008,0x350010,SM_RAM);
	SekMapMemory(PC090OJ_spritectrl,0x380000,0x380003,SM_RAM);
	SekMapMemory(rastan_ram+0x4012,0x3c0000,0x3c0003,SM_WRITE);
	SekMapMemory(PC080SN_word_0,0xc00000,0xc0ffff,SM_RAM);
	SekMapMemory(PC080SN_ctrl_word_0,0xc50000,0xc50003,SM_WRITE);
	SekMapMemory(PC090OJ_word_0,0xd00000,0xd03fff,SM_RAM);
	SekSetReadWordHandler(0, rastanReadWord);
	SekSetWriteWordHandler(0, rastanWriteWord);
	SekSetReadByteHandler(0, rastanReadByte);
	SekSetWriteByteHandler(0, rastanWriteByte);
	// ------------------------------------------------
	SekClose();

	ZetInit(1);
	ZetOpen(0);
	ZetSetReadHandler(RastanZ80Read);
	ZetSetWriteHandler(RastanZ80Write);
	ZetMapArea (0x0000,0x3FFF,0,z80_rom);
	ZetMapArea (0x0000,0x3FFF,2,z80_rom);
	ZetMapArea (0x4000,0x7FFF,0,z80_rom+0x4000);
	ZetMapArea (0x4000,0x7FFF,2,z80_rom+0x4000);
	ZetMapArea (0x8000,0x8FFF,0,z80_ram);
	ZetMapArea (0x8000,0x8FFF,1,z80_ram);
	ZetMemEnd();
	ZetMemCallback(0x9000, 0xa001, 0);			// Read
	ZetMemCallback(0x9000, 0xa001, 1);			// Write
	ZetReset();
	ZetClose();
	//-------------------------------------------------


	BurnYM2151Init(4000000, 50.0);
	BurnYM2151SetIrqHandler(&RastanYM2151IRQHandler);
	BurnYM2151SetPortHandler(&rastanBankSwitch);
	nCurrentBank=0; // bank number 0 or 1

	MSM5205Init(0,8000, 60,1);
	drvDoReset();
	return 0;
	}

int rastanExit()
{
	free(tsprites);
	free(ttiles);
	BurnYM2151Exit();
	MSM5205Exit(0);
	SekExit(); // Deallocate 68000
	ZetExit();
	if (Mem!=NULL)
		free(Mem);
	Mem=NULL;
	return 0;
}


static int rastanGFX()
{
	PC080SN_bg();
	PC080SN_fg();
	PC090OJ_draw_sprites();
	return 0;
}


static int rastanDraw()
{
	BurnClearScreen();
	rastanPalUpdate();
	rastanGFX();
	return 0;
}



int rastanFrame()
{
	int nInterleave = 100;
	rastanInpMake();

	if (drvReset) {	// Reset machine
		drvDoReset();
	}

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
				MSM5205Render(0,pSoundBuf, nSegmentLength); //this wrong??
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
				MSM5205Render(0,pSoundBuf, nSegmentLength); //this wrong??
			}
		}
	}
	SekSetIRQLine(5, SEK_IRQSTATUS_AUTO);
	SekClose();
	ZetClose();
	if (pBurnDraw) {
		rastanDraw();														// Draw screen if needed
	}

	return 0;
}


static int rastanScan(int nAction,int *pnMin)
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

		MSM5205Scan(0, nAction);
		BurnYM2151Scan(nAction);

		// Scan critical driver variables
		SCAN_VAR(Z80Bank);
		SCAN_VAR(nCurrentBank);
		SCAN_VAR(nCyclesTotal);
		SCAN_VAR(nCyclesSegment);		
		SCAN_VAR(RastanInputPort0);
		SCAN_VAR(RastanInputPort1);
		SCAN_VAR(RastanInputPort2);
		SCAN_VAR(RastanInput);
		SCAN_VAR(RastanDip);
	}

	return 0;
}


/// Rom information
static struct BurnRomInfo rastanRomDesc[] = {
	{ "b04-35.19",   0x10000, 0x1c91dbb1, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "b04-37.07",   0x10000, 0xecf20bdd, BRF_ESS | BRF_PRG }, //  1            (odd)
	{ "b04-40.20",   0x10000, 0x0930d4b3, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "b04-39.08",   0x10000, 0xd95ade5e, BRF_ESS | BRF_PRG }, //  1            (odd)
	{ "b04-42.21",   0x10000, 0x1857a7cb, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "b04-43.09",   0x10000, 0xc34b9152, BRF_ESS | BRF_PRG }, //  1            (odd)

	{ "b04-19.49",   0x10000, 0xee81fdd8, BRF_ESS | BRF_PRG }, //  2 z80 code

	{ "b04-01.40",   0x20000, 0xcd30de19, BRF_GRA },			 //  2 8x8 tile bitmaps
	{ "b04-03.39",   0x20000, 0xab67e064, BRF_GRA },			 //  3
	{ "b04-02.67",   0x20000, 0x54040fec, BRF_GRA },			 //  4
	{ "b04-04.66",   0x20000, 0x94737e93, BRF_GRA },			 //  5

	{ "b04-05.15",   0x20000, 0xc22d94ac, BRF_GRA },			 //  6 Sprite
	{ "b04-07.14",   0x20000, 0xb5632a51, BRF_GRA },			 //  7
	{ "b04-06.28",   0x20000, 0x002ccf39, BRF_GRA },			 //  8
	{ "b04-08.27",   0x20000, 0xfeafca05, BRF_GRA },			 //  9

	{ "b04-20.76",   0x10000, 0xfd1a34cc, BRF_SND },			 //  samples
};


STD_ROM_PICK(rastan);
STD_ROM_FN(rastan);

/// Rom information
static struct BurnRomInfo rastanuRomDesc[] = {
	{ "b04-35.19",   0x10000, 0x1c91dbb1, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "b04-37.07",   0x10000, 0xecf20bdd, BRF_ESS | BRF_PRG }, //  1            (odd)
	{ "b04-45.20",   0x10000, 0x362812dd, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "b04-44.08",   0x10000, 0x51cc5508, BRF_ESS | BRF_PRG }, //  1            (odd)
	{ "b04-42.21",   0x10000, 0x1857a7cb, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "b04-41-1.09", 0x10000, 0xbd403269, BRF_ESS | BRF_PRG }, //  1            (odd)

	{ "b04-19.49",   0x10000, 0xee81fdd8, BRF_ESS | BRF_PRG }, //  2 z80 code

	{ "b04-01.40",   0x20000, 0xcd30de19, BRF_GRA },			 //  2 8x8 tile bitmaps
	{ "b04-03.39",   0x20000, 0xab67e064, BRF_GRA },			 //  3
	{ "b04-02.67",   0x20000, 0x54040fec, BRF_GRA },			 //  4
	{ "b04-04.66",   0x20000, 0x94737e93, BRF_GRA },			 //  5

	{ "b04-05.15",   0x20000, 0xc22d94ac, BRF_GRA },			 //  6 Sprite
	{ "b04-07.14",   0x20000, 0xb5632a51, BRF_GRA },			 //  7
	{ "b04-06.28",   0x20000, 0x002ccf39, BRF_GRA },			 //  8
	{ "b04-08.27",   0x20000, 0xfeafca05, BRF_GRA },			 //  9

	{ "b04-20.76",   0x10000, 0xfd1a34cc, BRF_SND },			 //  samples
};


STD_ROM_PICK(rastanu);
STD_ROM_FN(rastanu);

/// Rom information
static struct BurnRomInfo rastanu2RomDesc[] = {
	{ "rs19_38.bin", 0x10000, 0xa38ac909, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "b04-21.7",    0x10000, 0x7c8dde9a, BRF_ESS | BRF_PRG }, //  1            (odd)
	{ "b04-23.20",   0x10000, 0x254b3dce, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "b04-22.8",    0x10000, 0x98e8edcf, BRF_ESS | BRF_PRG }, //  1            (odd)
	{ "b04-25.21",   0x10000, 0xd1e5adee, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "b04-24.9",    0x10000, 0xa3dcc106, BRF_ESS | BRF_PRG }, //  1            (odd)

	{ "b04-19.49",   0x10000, 0xee81fdd8, BRF_ESS | BRF_PRG }, //  2 z80 code

	{ "b04-01.40",   0x20000, 0xcd30de19, BRF_GRA },			 //  2 8x8 tile bitmaps
	{ "b04-03.39",   0x20000, 0xab67e064, BRF_GRA },			 //  3
	{ "b04-02.67",   0x20000, 0x54040fec, BRF_GRA },			 //  4
	{ "b04-04.66",   0x20000, 0x94737e93, BRF_GRA },			 //  5

	{ "b04-05.15",   0x20000, 0xc22d94ac, BRF_GRA },			 //  6 Sprite
	{ "b04-07.14",   0x20000, 0xb5632a51, BRF_GRA },			 //  7
	{ "b04-06.28",   0x20000, 0x002ccf39, BRF_GRA },			 //  8
	{ "b04-08.27",   0x20000, 0xfeafca05, BRF_GRA },			 //  9

	{ "b04-20.76",   0x10000, 0xfd1a34cc, BRF_SND },			 //  samples
};


STD_ROM_PICK(rastanu2);
STD_ROM_FN(rastanu2);

/// Rom information
static struct BurnRomInfo rastsagaRomDesc[] = {
	{ "rs19_38.bin", 0x10000, 0xa38ac909, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "rs07_37.bin", 0x10000, 0xbad60872, BRF_ESS | BRF_PRG }, //  1            (odd)
	{ "rs20_40.bin", 0x10000, 0x6bcf70dc, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "rs08_39.bin", 0x10000, 0x8838ecc5, BRF_ESS | BRF_PRG }, //  1            (odd)
	{ "rs21_42.bin", 0x10000, 0xb626c439, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "rs09_43.bin", 0x10000, 0xc928a516, BRF_ESS | BRF_PRG }, //  1            (odd)

	{ "b04-19.49",   0x10000, 0xee81fdd8, BRF_ESS | BRF_PRG }, //  2 z80 code

	{ "b04-01.40",   0x20000, 0xcd30de19, BRF_GRA },			 //  2 8x8 tile bitmaps
	{ "b04-03.39",   0x20000, 0xab67e064, BRF_GRA },			 //  3
	{ "b04-02.67",   0x20000, 0x54040fec, BRF_GRA },			 //  4
	{ "b04-04.66",   0x20000, 0x94737e93, BRF_GRA },			 //  5

	{ "b04-05.15",   0x20000, 0xc22d94ac, BRF_GRA },			 //  6 Sprite
	{ "b04-07.14",   0x20000, 0xb5632a51, BRF_GRA },			 //  7
	{ "b04-06.28",   0x20000, 0x002ccf39, BRF_GRA },			 //  8
	{ "b04-08.27",   0x20000, 0xfeafca05, BRF_GRA },			 //  9

	{ "b04-20.76",   0x10000, 0xfd1a34cc, BRF_SND },			 //  samples
};


STD_ROM_PICK(rastsaga);
STD_ROM_FN(rastsaga);

static struct BurnRomInfo rastsag1RomDesc[] = {
	{ "b04-14.19",   0x10000, 0xa38ac909, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "b04-13.7",    0x10000, 0xbad60872, BRF_ESS | BRF_PRG }, //  1            (odd)
	{ "b04-16-1.20", 0x10000, 0x00b59e60, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "b04-15-1.8",  0x10000, 0xff9e018a, BRF_ESS | BRF_PRG }, //  1            (odd)
	{ "b04-18-1.21", 0x10000, 0xb626c439, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "b04-17-1.9",  0x10000, 0xc928a516, BRF_ESS | BRF_PRG }, //  1            (odd)
	
	{ "b04-19.49",   0x10000, 0xee81fdd8, BRF_ESS | BRF_PRG }, //  2 z80 code

	{ "b04-01.40",   0x20000, 0xcd30de19, BRF_GRA },			 //  2 8x8 tile bitmaps
	{ "b04-03.39",   0x20000, 0xab67e064, BRF_GRA },			 //  3
	{ "b04-02.67",   0x20000, 0x54040fec, BRF_GRA },			 //  4
	{ "b04-04.66",   0x20000, 0x94737e93, BRF_GRA },			 //  5

	{ "b04-05.15",   0x20000, 0xc22d94ac, BRF_GRA },			 //  6 Sprite
	{ "b04-07.14",   0x20000, 0xb5632a51, BRF_GRA },			 //  7
	{ "b04-06.28",   0x20000, 0x002ccf39, BRF_GRA },			 //  8
	{ "b04-08.27",   0x20000, 0xfeafca05, BRF_GRA },			 //  9

	{ "b04-20.76",   0x10000, 0xfd1a34cc, BRF_SND },			 //  samples
};


STD_ROM_PICK(rastsag1);
STD_ROM_FN(rastsag1);

struct BurnDriver BurnDrvrastan = {
	"rastan", NULL, NULL, "1987",
	"Rastan (World)\0", NULL, "Taito", "Custom Taito",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_MISC_MISC,
	NULL,rastanRomInfo,rastanRomName,rastanInputInfo, rastanDIPInfo,
	rastanInit,rastanExit,rastanFrame,NULL,rastanScan,
	NULL,320,240,4,3
};

struct BurnDriver BurnDrvrastanu = {
	"rastanu", "rastan", NULL, "1987",
	"Rastan (US set 1)\0", NULL, "Taito", "Custom Taito",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_MISC_MISC,
	NULL,rastanuRomInfo,rastanuRomName,rastanInputInfo, rastsagaDIPInfo,
	rastanInit,rastanExit,rastanFrame,NULL,rastanScan,
	NULL,320,240,4,3
};

struct BurnDriver BurnDrvrastanu2 = {
	"rastanu2", "rastan", NULL, "1987",
	"Rastan (US set 2)\0", NULL, "Taito", "Custom Taito",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_MISC_MISC,
	NULL,rastanu2RomInfo,rastanu2RomName,rastanInputInfo, rastsagaDIPInfo,
	rastanInit,rastanExit,rastanFrame,NULL,rastanScan,
	NULL,320,240,4,3
};

struct BurnDriver BurnDrvrastsaga = {
	"rastsaga", "rastan", NULL, "1987",
	"Rastan Saga (Japan)\0", NULL, "Taito", "Custom Taito",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_MISC_MISC,
	NULL,rastsagaRomInfo,rastsagaRomName,rastanInputInfo, rastsagaDIPInfo,
	rastanInit,rastanExit,rastanFrame,NULL,rastanScan,
	NULL,320,240,4,3
};

struct BurnDriver BurnDrvrastsag1 = {
	"rastsag1", "rastan", NULL, "1987",
	"Rastan Saga (Japan rev 1)\0", NULL, "Taito", "Custom Taito",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_MISC_MISC,
	NULL,rastsag1RomInfo,rastsag1RomName,rastanInputInfo, rastsagaDIPInfo,
	rastanInit,rastanExit,rastanFrame,NULL,rastanScan,
	NULL,320,240,4,3
};
