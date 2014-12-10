/*
Operation Wolf driver
=====================
Part of FBAs Taito 68k hardware drivers
Credits: Mame team, Raine team
Coding by KEV, with help from Treble Winner and Jan_Klaassen
*/

#include "taito.h"
#include "msm5205.h"

static unsigned char *Mem=NULL,*MemEnd=NULL;
static unsigned char *RamStart=NULL,*RamEnd=NULL;
static unsigned char *Rom=NULL;
static unsigned char *opwolf_ram=NULL,*opwolf_src_pal=NULL;
static unsigned char drvReset = 0;
static unsigned char *z80_rom=NULL,*z80_ram=NULL,*z802_ram=NULL,*z802_rom=NULL;
static unsigned int *opwolf_pal=NULL;

static int gun_x=134 << 8,gun_y=77 << 8;
// Z80 ROM bank
static int Z80Bank=0;
static int nCurrentBank=0;

static int nCyclesTotal[3];
static int nCyclesSegment=0;

static unsigned short opwolfAxis[2];

static unsigned char opwolfInputPort0[8], opwolfInputPort1[8];
unsigned char opwolfInput[4]= {0,0,0,0};
static unsigned char opwolfDip[2]= {0, 0};

#define A(a, b, c, d) { a, b, (unsigned char*)(c), d }

static struct BurnInputInfo opwolfInputList[]=
{
	{"P1 Coin"     , BIT_DIGITAL,	opwolfInputPort0 + 0, "p1 coin"     },
	{"P1 Start"    , BIT_DIGITAL,	opwolfInputPort1 + 4, "p1 start"    },
	{"P2 Coin"     , BIT_DIGITAL,	opwolfInputPort0 + 1, "p2 coin"     },

   A("P1 X Axis",	BIT_ANALOG_REL,	opwolfAxis + 0,	"mouse x-axis"),
   A("P1 Y Axis",	BIT_ANALOG_REL,	opwolfAxis + 1,	"mouse y-axis"),

	{"P1 Fire"	   , BIT_DIGITAL,	opwolfInputPort1 + 0, "mouse button 1"   },
	{"P1 Grenade"  , BIT_DIGITAL,	opwolfInputPort1 + 1, "mouse button 2"   },

	{"Reset"       , BIT_DIGITAL,	&drvReset           , "reset"       },
	{"Service"     , BIT_DIGITAL,	opwolfInputPort1 + 2, "service"     },
	{"Tilt"        , BIT_DIGITAL,	opwolfInputPort1 + 3, "tilt"        },
	{"Dip 1"       , BIT_DIPSWITCH,	opwolfDip + 0		  , "dip"         },
	{"Dip 2"       , BIT_DIPSWITCH,	opwolfDip + 1		  , "dip"         },
};

#undef A

static struct BurnDIPInfo opwolfDIPList[]=
{
	// Defaults
	{0x0a, 0xff, 0xff, 0x02, NULL                     },
	{0x0b, 0xff, 0xff, 0x00, NULL                     },

	// Dip 1
	{0   , 0xfe, 0xff , 2  , "NY Conversion of Upright"},
	{0x0a, 0x01, 0x01, 0x00, "Off"                    },
	{0x0a, 0x01, 0x01, 0x01, "On"                     },

	{0   , 0xfe, 0xff , 2  , "Allow Continue"         },
	{0x0a, 0x01, 0x02, 0x00, "Off"                    },
	{0x0a, 0x01, 0x02, 0x02, "On"                     },

	{0   , 0xfe, 0   , 2   , "Test Mode"              },
	{0x0a, 0x01, 0x04, 0x00, "Off"                    },
	{0x0a, 0x01, 0x04, 0x04, "On"                     },

	{0   , 0xfe, 0   , 2   , "Demo Sounds"            },
	{0x0a, 0x01, 0x08, 0x08, "Off"                    },
	{0x0a, 0x01, 0x08, 0x00, "On"                     },

	{0   , 0xfe, 0   , 4   , "Coin A"                 },
	{0x0a, 0x01, 0x30, 0x00, "1 Coin  1 Credit"       },
	{0x0a, 0x01, 0x30, 0x10, "2 Coins 1 Credit"       },
	{0x0a, 0x01, 0x30, 0x20, "3 Coins 1 Credit"       },
	{0x0a, 0x01, 0x30, 0x30, "4 Coins 1 Credit"       },

	{0   , 0xfe, 0   , 4   , "Coin B"                 },
	{0x0a, 0x01, 0xc0, 0xc0, "1 Coin 5 Credits"       },
	{0x0a, 0x01, 0xc0, 0x80, "1 Coin 4 Credits"       },
	{0x0a, 0x01, 0xc0, 0x40, "1 Coin 3 Credits"       },
	{0x0a, 0x01, 0xc0, 0x00, "1 Coin 2 Credits"       },

	// Dip 2
	{0   , 0xfe, 0   , 4   , "Difficulty"             },
	{0x0b, 0x01, 0x03, 0x01, "Easy"                   },
	{0x0b, 0x01, 0x03, 0x00, "Medium"                 },
	{0x0b, 0x01, 0x03, 0x02, "Hard"                   },
	{0x0b, 0x01, 0x03, 0x03, "Hardest"                },

	{0   , 0xfe, 0   , 4   , "Ammo Magazines at Start"},
	{0x0b, 0x01, 0x0c, 0x0c, "4"                      },
	{0x0b, 0x01, 0x0c, 0x08, "5"                      },
	{0x0b, 0x01, 0x0c, 0x00, "6"                      },
	{0x0b, 0x01, 0x0c, 0x04, "7"                      },

//	{0   , 0xfe, 0   , 2   , "Language"               }, // Bootleg cchip forces english language
//	{0x0b, 0x01, 0x80, 0x00, "Japanese"               },
//	{0x0b, 0x01, 0x80, 0x80, "English"                },
};

STDDIPINFO(opwolf);
STDINPUTINFO(opwolf);

void opwolfBankSwitch(unsigned int /*a*/, unsigned int data)
{
	Z80Bank=(data-1) & 0x03;
	unsigned char* nStartAddress = z80_rom + 0x4000+(Z80Bank*0x4000);
	nCurrentBank = Z80Bank;
	ZetMapArea(0x4000, 0x7FFF, 0, nStartAddress);
	ZetMapArea(0x4000, 0x7FFF, 2, nStartAddress);
}

void opwolfYM2151IRQHandler(int irq )
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


int opwolfInpMake()
{
	const int min_x =  21 * 0x0100;
	const int min_y = -29 * 0x0100;

	opwolfInput[0] = 0x00;
	opwolfInput[1] = 0xFF;

	for (int i = 0; i < 8; i++) {
		opwolfInput[0] |= (opwolfInputPort0[i] & 1) << i;
		opwolfInput[1] -= (opwolfInputPort1[i] & 1) << i;

	}
// gun - could be considered a hack :)

	gun_x += (short)opwolfAxis[0];
	gun_y += (short)opwolfAxis[1];

	if (gun_x < min_x)
		gun_x = min_x;
	if (gun_x > min_x + 319 * 0x0100)
		gun_x = min_x + 319 * 0x0100;
	if (gun_y < min_y)
		gun_y = min_y;
	if (gun_y > min_y + 239 * 0x0100)
		gun_y = min_y + 239 * 0x0100;

	return 0;
}


inline static unsigned int CalcCol(unsigned short nColour)
{
	int r, g, b;
	b = (nColour & 0x000f) << 4;	// Blue
	g = (nColour & 0x00f0);  	// Green
	r = (nColour & 0x0f00) >> 4;	// Red

	b |= b >> 4;
	g |= g >> 4;
	r |= r >> 4;

	return BurnHighCol(r, g, b, 0);
}

int opwolfPalUpdate()
{
	int i;
	unsigned short* ps;
	unsigned int* pd;

	for (i = 0, ps = (unsigned short*)opwolf_src_pal, pd = opwolf_pal; i < 0x400; i++, ps++, pd++) {
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
	opwolf_ram=Next;	Next+=0x8004;
	opwolf_src_pal=Next;		Next+=0x1000;
	PC090OJ_spritectrl=Next; Next+=0x04;
	PC080SN_word_0=Next;	Next+=0x10000;
	PC080SN_yscroll_word_0=Next;Next+=0x10;
	PC080SN_xscroll_word_0=Next;Next+=0x10;
	PC080SN_ctrl_word_0=Next;Next+=0x10;
	PC090OJ_word_0=Next;Next+=0x4000;
	opwolf_pal=(unsigned int*)Next; Next += 0x800 * sizeof(unsigned int);
	z80_ram=Next; Next+=0x2000;
	z80_rom=Next; Next+=0x1c000;
	z802_rom=Next; Next+=0x1c000;
	z802_ram=Next; Next+=0x1000;
	MSM5205ROM=Next;		Next+=0x80000;
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
	nRet=BurnLoadRom(Rom+0x20001,2,2); if (nRet!=0) return 1;
	nRet=BurnLoadRom(Rom+0x20000,3,2); if (nRet!=0) return 1;

	// Fix gun coords
  Rom[0x3ffae] = 0x1c;
  Rom[0x3ffb0] = 0xec;

	nRet=BurnLoadRom(z80_rom,4,1); // load z80 code rom

	nRet=BurnLoadRom(MSM5205ROM + 0x00000, 7, 1);

	unsigned char *TempGfx;
	unsigned int c,y = 0;
	TempGfx=(unsigned char *)malloc(0xA0000);
	nRet = BurnLoadRom(TempGfx + 0x00000, 5, 1); if (nRet) return 1;

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
	nRet = BurnLoadRom(TempGfx + 0x00000, 6, 1); if (nRet) return 1;

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
	init_gun();
	return nRet;
}

static int opwolfbLoadRoms()
{
	int nRet=0;
	// Load program roms and byteswap
	nRet=BurnLoadRom(Rom+0x00001,0,2); if (nRet!=0) return 1;
	nRet=BurnLoadRom(Rom+0x00000,1,2); if (nRet!=0) return 1;
	nRet=BurnLoadRom(Rom+0x20001,2,2); if (nRet!=0) return 1;
	nRet=BurnLoadRom(Rom+0x20000,3,2); if (nRet!=0) return 1;

	// Fix gun coords
  Rom[0x3ffae] = 0x1c;
  Rom[0x3ffb0] = 0xec;

	nRet=BurnLoadRom(z80_rom,4,1); // load z80 code rom
	nRet=BurnLoadRom(z802_rom,5,1); // load z80 code rom

	nRet=BurnLoadRom(MSM5205ROM + 0x00000, 22, 2);
	nRet=BurnLoadRom(MSM5205ROM + 0x20000, 23, 2);
	nRet=BurnLoadRom(MSM5205ROM + 0x40000, 24, 2);
	nRet=BurnLoadRom(MSM5205ROM + 0x60000, 25, 2);
	nRet=BurnLoadRom(MSM5205ROM + 0x00001, 26, 2);
	nRet=BurnLoadRom(MSM5205ROM + 0x20001, 27, 2);
	nRet=BurnLoadRom(MSM5205ROM + 0x40001, 28, 2);
	nRet=BurnLoadRom(MSM5205ROM + 0x60001, 29, 2);

	unsigned char *TempGfx;
	unsigned int c,y = 0;
	TempGfx=(unsigned char *)malloc(0xA0000);
	nRet = BurnLoadRom(TempGfx + 0x00000, 6, 1); if (nRet) return 1;
	nRet = BurnLoadRom(TempGfx + 0x10000, 7, 1); if (nRet) return 1;
	nRet = BurnLoadRom(TempGfx + 0x20000, 8, 1); if (nRet) return 1;
	nRet = BurnLoadRom(TempGfx + 0x30000, 9, 1); if (nRet) return 1;
	nRet = BurnLoadRom(TempGfx + 0x40000, 10, 1); if (nRet) return 1;
	nRet = BurnLoadRom(TempGfx + 0x50000, 11, 1); if (nRet) return 1;
	nRet = BurnLoadRom(TempGfx + 0x60000, 12, 1); if (nRet) return 1;
	nRet = BurnLoadRom(TempGfx + 0x70000, 13, 1); if (nRet) return 1;

	ttiles=(unsigned char *)malloc(16384*64);
	memset(ttiles,0,16384*64);
	tsprites=(unsigned char *)malloc(5120*256);
	memset(tsprites,0,5120*256);

	for(c = 0; c < 0x40000; c++, y+=4){
		ttiles[y+0]=TempGfx[c+0x00000] >> 4;
		ttiles[y+1]=TempGfx[c+0x00000] & 0xf;
		ttiles[y+2]=TempGfx[c+0x40000] >> 4;
		ttiles[y+3]=TempGfx[c+0x40000] & 0xf;
	}
	
	memset(TempGfx,0,0xa0000);
	nRet = BurnLoadRom(TempGfx + 0x00000, 14, 1); if (nRet) return 1;
	nRet = BurnLoadRom(TempGfx + 0x10000, 15, 1); if (nRet) return 1;
	nRet = BurnLoadRom(TempGfx + 0x20000, 16, 1); if (nRet) return 1;
	nRet = BurnLoadRom(TempGfx + 0x30000, 17, 1); if (nRet) return 1;
	nRet = BurnLoadRom(TempGfx + 0x40000, 18, 1); if (nRet) return 1;
	nRet = BurnLoadRom(TempGfx + 0x50000, 19, 1); if (nRet) return 1;
	nRet = BurnLoadRom(TempGfx + 0x60000, 20, 1); if (nRet) return 1;
	nRet = BurnLoadRom(TempGfx + 0x70000, 21, 1); if (nRet) return 1;

	y = 0;
	for(c = 0; c < 0x40000; c++, y+=4){
		tsprites[y+0]=TempGfx[c+0x00000] >> 4;
		tsprites[y+1]=TempGfx[c+0x00000] & 0xf;
		tsprites[y+2]=TempGfx[c+0x40000] >> 4;
		tsprites[y+3]=TempGfx[c+0x40000] & 0xf;
	}
	
	free(TempGfx);
	init_gun();
	return nRet;
  }

unsigned char __fastcall opwolfZ80Read(unsigned short a)
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

void __fastcall opwolfZ80Write(unsigned short a,unsigned char d)
{
	unsigned int start=0;
	unsigned int end=0;
	static unsigned char adpcm_b[0x08]={0,0,0,0,0,0,0,0};
	static unsigned char adpcm_c[0x08]={0,0,0,0,0,0,0,0};

	if (a>=0xb000&&a<0xb006)
	{
		adpcm_b[a&0x0f] = d;

		if ((a&0x0f)==0x04) //trigger ?
		{
		start = adpcm_b[0]|(adpcm_b[1]<<8);
		end   = adpcm_b[2]|(adpcm_b[3]<<8);
		start *=16;
		end   *=16;
		MSM5205Play(start,(end-start)*2,0);
		}
		return;
	}
	if (a>=0xc000&&a<0xc006)
	{
		adpcm_c[a&0x0f] = d;

		if ((a&0x0f)==0x04) //trigger ?
		{
		start = adpcm_c[0]|(adpcm_c[1]<<8);
		end   = adpcm_c[2]|(adpcm_c[3]<<8);
		start *=16;
		end   *=16;
		MSM5205Play(start,(end-start)*2,1);
		}
		return;
	}
	if (a==0xd000)
	{
		return;
	}
	if (a==0xe000)
	{
		return;
	}
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
//		printf ("write %x\n",a);
		return;
	}
}

unsigned char __fastcall opwolfZ802Read(unsigned short a)
{
	if (a>=0x8800&&a<=0x9800)
	{
		return opwolfInput[0];
	}
//	bprintf(PRINT_NORMAL, PRINT_NORMAL, "Read %x\n",a);
	return 0;
}

void __fastcall opwolfZ802Write(unsigned short /*a*/,unsigned char /*d*/)
{
	// ignore all writes as the memory map should suffice
	return;
}


unsigned short __fastcall opwolfReadWord(unsigned int a)
{
	if (a>=0x3a0000&&a<=0x3a0001)
	{
		return gun_x >> 8;
	}
	if (a>=0x3a0002&&a<=0x3a0003)
	{
		return gun_y >> 8;
	}

	if (a>=0x0ff000&&a<=0x0fffff)
	{
		int offset=a-0x0ff000;
		return z802_ram[offset/2]; // cchip bootleg
	}
	if (a>=0x0f0008&&a<=0x0f0009)
	{
		return opwolfInput[0]; // input a/dip a?
	}
	if (a>=0x0f000a&&a<=0x0f000b)
	{
		return opwolfInput[1]; // input b/dip b?
	}

	if (a==0x380000/*&&a<=0x380001*/)
	{
		return 0xff - opwolfDip[0]; //dip a??
	}
	if (a==0x380002/*&&a<=0x380003*/)
	{
		return 0xff - opwolfDip[1]; //dip b??
	}
	switch (a)
	{
	case 0x3e0003:
		return tc0140_comm_r();
	default:
//		bprintf(PRINT_NORMAL, "read w%x\n",a);
		return 0;
	}
}

unsigned char __fastcall opwolfReadByte(unsigned int a)
{
	if (a>=0x0ff000&&a<=0x0fffff)
	{
		int offset=a-0x0ff000;
	//	bprintf(PRINT_NORMAL, "cchip returns %x at %x\n",z802_ram[offset],offset);
		return z802_ram[offset/2]; // cchip bootleg
	}

	if (a>=0x0f0008&&a<=0x0f0009)
	{
		return opwolfInput[0]; // input a/dip a?
	}
	if (a>=0x0f000a&&a<=0x0f000b)
	{
		return opwolfInput[1]; // input b/dip b?
	}
	switch (a)
	{
	case 0x3e0002:
		return tc0140_comm_r();
	case 0x3e0003:
		return tc0140_comm_r();
	default:
//		bprintf(PRINT_NORMAL, "read b%x\n",a);
		return 0;
	}

}

void __fastcall opwolfWriteWord(unsigned int a,unsigned short d)
{

	if (a>=0x0ff000&&a<=0x0fffff)
	{
		int offset=a-0x0ff000;
	//	bprintf(PRINT_NORMAL, "cchip returns %x at %x\n",z802_ram[offset],offset);
		z802_ram[offset/2]=d; // cchip bootleg
		return;
	}
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


void __fastcall opwolfWriteByte(unsigned int a,unsigned char d)
{
	if (a>=0x0ff000&&a<=0x0fffff)
	{
		int offset=a-0x0ff000;
	//	bprintf(PRINT_NORMAL, "cchip returns %x at %x\n",z802_ram[offset],offset);
		z802_ram[offset/2]=d; // cchip bootleg
		return;
	}
	switch (a)
	{
	case 0x3e0000:
		tc0140_port_w(d);
		return;
	case 0x3e0001:
		tc0140_port_w(d);
		return;
	case 0x3e0002:
		tc0140_comm_w(d);
		return;
	case 0x3e0003:
		tc0140_comm_w(d);
		return;
	default:
//		bprintf(PRINT_NORMAL, "write b%x at %x\n",d,a);
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
	ZetRun(4000000/60);
	ZetClose();
	ZetOpen(1);
	ZetReset();
	ZetClose();
	BurnYM2151Reset();
	MSM5205Reset(0);
	MSM5205Reset(1);
	return 0;
}

int opwolfInit()
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
	if(!strcmp(BurnDrvGetTextA(DRV_NAME), "opwolfb")) {
		nRet=opwolfbLoadRoms();
	} else {
		nRet=LoadRoms();
	}
	if (nRet!=0)
		return 1; // Load the roms into memory
	// ----------------- Cpu 1 68k ------------------------
	SekInit(0, 0x68000); // Allocate 1 68000
	SekOpen(0);

	SekMapMemory(    Rom  ,0x000000,0x03ffff,SM_ROM); // 68000 Rom
	SekMapMemory(opwolf_ram,0x100000,0x107fff,SM_RAM);
	SekMapMemory(opwolf_src_pal,0x200000,0x200fff,SM_RAM);
	SekMapMemory(PC090OJ_spritectrl,0x380000,0x380003,SM_WRITE);
	SekMapMemory(opwolf_ram+0x8000,0x3c0000,0x3c0001,SM_RAM); //0x3010
	SekMapMemory(PC080SN_word_0,0xc00000,0xc0ffff,SM_RAM);
	SekMapMemory(PC080SN_ctrl_word_0,0xc50000,0xc50003,SM_WRITE);
	SekMapMemory(PC090OJ_word_0,0xd00000,0xd03fff,SM_RAM);
	SekSetWriteWordHandler(0, opwolfWriteWord);
	SekSetReadWordHandler(0, opwolfReadWord);
	SekSetReadByteHandler(0, opwolfReadByte);
	SekSetWriteByteHandler(0, opwolfWriteByte);
	SekClose();
	// ----------------- Cpu 2 Z80 ------------------------
	ZetInit(2);
	ZetOpen(0);
	ZetSetReadHandler(opwolfZ80Read);
	ZetSetWriteHandler(opwolfZ80Write);
	ZetMapArea (0x0000,0x3FFF,0,z80_rom);
	ZetMapArea (0x0000,0x3FFF,2,z80_rom);
	ZetMapArea (0x4000,0x7FFF,0,z80_rom+0x4000);
	ZetMapArea (0x4000,0x7FFF,2,z80_rom+0x4000);
	ZetMapArea (0x8000,0x8FFF,0,z80_ram);
	ZetMapArea (0x8000,0x8FFF,2,z80_ram);
	ZetMapArea (0x8000,0x8FFF,1,z80_ram);
	// Callbacks
	ZetMemCallback(0x9000, 0xd002, 0);			// Read
	ZetMemCallback(0x9000, 0xd002, 1);			// Write
	ZetMemEnd();
	ZetReset();
	ZetClose();

	ZetOpen(1);
	ZetSetReadHandler(opwolfZ802Read);
	ZetSetWriteHandler(opwolfZ802Write);
	ZetMapArea (0x0000,0x7fff,0,z802_rom);
	ZetMapArea (0x0000,0x7fff,2,z802_rom);
//	ZetMapArea (0x8800,0xbFFF,0,z802_ram);
//	ZetMapArea (0x8800,0xbFFF,1,z802_ram);
//	ZetMapArea (0x8800,0xbFFF,2,z802_ram);
	ZetMapArea (0xc000,0xcfff,0,z802_ram);
	ZetMapArea (0xc000,0xcfff,1,z802_ram);
	ZetMapArea (0xc000,0xcfff,2,z802_ram);
	ZetMemCallback(0xc000, 0x9800, 0);			// Read
	ZetMemCallback(0xc000, 0x9800, 1);			// Write
	ZetMemEnd();
	ZetReset();
	ZetClose();
	//-------------------------------------------------

	//-------- sound stuff ----------------------------
	//---------- YM2151 Setup ----------------------

	BurnYM2151Init(4000000, 50.0);
	BurnYM2151SetIrqHandler(&opwolfYM2151IRQHandler);
	BurnYM2151SetPortHandler(&opwolfBankSwitch);
	nCurrentBank=-1;

	MSM5205Init(0,8000, 100,1);
	MSM5205Init(1,8000, 100,1);
	//--------------------------------------------------
	// ------- GFX Init -------------------
	taito_pal=opwolf_pal;
	init_taito_gfx();
	//-------------------------------------
	drvDoReset();
	return 0;
	}

int opwolfExit()
{
	if(tsprites)
		free(tsprites);
	if(ttiles)
		free(ttiles);
	BurnYM2151Exit();
	MSM5205Exit(0);
	MSM5205Exit(1);
	SekExit(); // Deallocate 68000
	ZetExit();
	if (Mem!=NULL)
		free(Mem);
	Mem=NULL;
	return 0;
}


static int opwolfGFX()
{
	PC080SN_bg();
	PC090OJ_draw_sprites();
	PC080SN_fg();
	draw_gun(gun_x >> 8,gun_y >> 8);
	return 0;
}


static int opwolfDraw()
{
	opwolfPalUpdate();
	opwolfGFX();
	return 0;
}



int opwolfFrame()
{
	if (drvReset) {	// Reset machine
		drvDoReset();
	}

	opwolfInpMake();

	int nInterleave = 10;

	SekNewFrame();

	SekOpen(0);
	ZetOpen(0);
	nCyclesTotal[0] = 12000000/60;
	nCyclesTotal[1] = 4000000/60;
	nCyclesTotal[2] = 4000000/60;
	rCyclesDone[0] =rCyclesDone[1] = rCyclesDone[2] = 0;

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

		ZetClose();
		ZetOpen(1);
		nCurrentCPU = 2;
		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;
		nCyclesSegment = nNext - rCyclesDone[nCurrentCPU];
		nCyclesSegment = ZetRun(nCyclesSegment);
		ZetClose();
		ZetOpen(0);
		rCyclesDone[nCurrentCPU] += nCyclesSegment;

		{
			// Render sound segment
			if (pBurnSoundOut) {
				int nSegmentLength = nBurnSoundLen / nInterleave;
				short* pSoundBuf = pBurnSoundOut + (nSoundBufferPos << 1);
				BurnYM2151Render(pSoundBuf, nSegmentLength);
				MSM5205Render(0,pSoundBuf, nSegmentLength); //this wrong??
				MSM5205Render(1,pSoundBuf, nSegmentLength); //this wrong??
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
				MSM5205Render(1,pSoundBuf, nSegmentLength); //this wrong??
			}
		}
	}

	SekSetIRQLine(5, SEK_IRQSTATUS_AUTO);
	SekClose();
	ZetClose();
	ZetOpen(1);
	ZetRaiseIrq(1);
	ZetClose();
	if (pBurnDraw) {
		opwolfDraw();														// Draw screen if needed
	}

	return 0;
}

static int opwolfScan(int nAction,int *pnMin)
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
		SCAN_VAR(opwolfInputPort0);
		SCAN_VAR(opwolfInputPort1);
		SCAN_VAR(opwolfInput);
		SCAN_VAR(opwolfDip);
	}

	return 0;
}


/// Rom information
static struct BurnRomInfo opwolfRomDesc[] = {
	{ "b20-05-02.40",  0x10000, 0x3ffbfe3a, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "b20-03-02.30",  0x10000, 0xfdabd8a5, BRF_ESS | BRF_PRG }, //  1            (odd)
	{ "b20-04.39",     0x10000, 0x216b4838, BRF_ESS | BRF_PRG }, //  2 68000 code (even)
	{ "b20-20.29",     0x10000, 0xd244431a, BRF_ESS | BRF_PRG }, //  3            (odd)

	{ "b20-07.10",     0x10000, 0x45c7ace3, BRF_ESS | BRF_PRG }, //  4 z80 code

	{ "b20-13.13",     0x80000, 0xf6acdab1, BRF_GRA },			 //  5 8x8 tile bitmaps
	
	{ "b20-14.72",     0x80000, 0x89f889e5, BRF_GRA },			 //  6 Sprite

	{ "b20-08.21",     0x80000, 0xf3e19c64, BRF_SND },			 //  7 adpcm
};


STD_ROM_PICK(opwolf);
STD_ROM_FN(opwolf);

static struct BurnRomInfo opwolfuRomDesc[] = {
	{ "b20-05-02.40",  0x10000, 0x3ffbfe3a, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "b20-03-02.30",  0x10000, 0xfdabd8a5, BRF_ESS | BRF_PRG }, //  1            (odd)
	{ "b20-04.39",     0x10000, 0x216b4838, BRF_ESS | BRF_PRG }, //  2 68000 code (even)
	{ "opwlf.29",      0x10000, 0xb71bc44c, BRF_ESS | BRF_PRG }, //  3            (odd)

	{ "b20-07.10",     0x10000, 0x45c7ace3, BRF_ESS | BRF_PRG }, //  4 z80 code

	{ "b20-13.13",     0x80000, 0xf6acdab1, BRF_GRA },			 //  5 8x8 tile bitmaps
	
	{ "b20-14.72",     0x80000, 0x89f889e5, BRF_GRA },			 //  6 Sprite

	{ "b20-08.21",     0x80000, 0xf3e19c64, BRF_SND },			 //  7 adpcm
};


STD_ROM_PICK(opwolfu);
STD_ROM_FN(opwolfu);

static struct BurnRomInfo opwolfbRomDesc[] = {
	{ "opwlfb.12",  0x10000, 0xd87e4405, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "opwlfb.10",  0x10000, 0x9ab6f75c, BRF_ESS | BRF_PRG }, //  1            (odd)
	{ "opwlfb.13",  0x10000, 0x61230c6e, BRF_ESS | BRF_PRG }, //  2 68000 code (even)
	{ "opwlfb.11",  0x10000, 0x342e318d, BRF_ESS | BRF_PRG }, //  3            (odd)

	{ "opwlfb.30",  0x08000, 0x0669b94c, BRF_ESS | BRF_PRG },	//  4 z80 code

	{ "opwlfb.09",  0x08000, 0xab27a3dd, BRF_ESS | BRF_PRG },	//  5 z80 code bootleg cchip

	{ "opwlfb.08",     0x10000, 0x134d294e, BRF_GRA },			// 6 8x8 tile bitmaps
	{ "opwlfb.06",     0x10000, 0x317d0e66, BRF_GRA },			// 7
	{ "opwlfb.07",     0x10000, 0xe1c4095e, BRF_GRA },			// 8
	{ "opwlfb.05",     0x10000, 0xfd9e72c8, BRF_GRA },			// 9
	{ "opwlfb.04",     0x10000, 0xde0ca98d, BRF_GRA },			// 10
	{ "opwlfb.02",     0x10000, 0x6231fdd0, BRF_GRA },			// 11
	{ "opwlfb.03",     0x10000, 0xccf8ba80, BRF_GRA },			// 12
	{ "opwlfb.01",     0x10000, 0x0a65f256, BRF_GRA },			// 13

	{ "opwlfb.14",     0x10000, 0x663786eb, BRF_GRA },			// 14  Sprite
	{ "opwlfb.15",     0x10000, 0x315b8aa9, BRF_GRA },			// 15
	{ "opwlfb.16",     0x10000, 0xe01099e3, BRF_GRA },			// 16
	{ "opwlfb.17",     0x10000, 0x56fbe61d, BRF_GRA },			// 17
	{ "opwlfb.18",     0x10000, 0xde9ab08e, BRF_GRA },			// 18
	{ "opwlfb.19",     0x10000, 0x645cf85e, BRF_GRA },			// 19
	{ "opwlfb.20",     0x10000, 0xd80b9cc6, BRF_GRA },			// 20
	{ "opwlfb.21",     0x10000, 0x97d25157, BRF_GRA },			// 21

	{ "opwlfb.29",     0x10000, 0x05a9eac0, BRF_SND },			// 22 adpcm
	{ "opwlfb.28",     0x10000, 0x281b2175, BRF_SND },			// 23
	{ "opwlfb.27",     0x10000, 0x441211a6, BRF_SND },			// 24
	{ "opwlfb.26",     0x10000, 0x86d1d42d, BRF_SND },			// 25
	{ "opwlfb.25",     0x10000, 0x85b87f58, BRF_SND },			// 26
	{ "opwlfb.24",     0x10000, 0x8efc5d4d, BRF_SND },			// 27
	{ "opwlfb.23",     0x10000, 0xa874c703, BRF_SND },			// 28
	{ "opwlfb.22",     0x10000, 0x9228481f, BRF_SND },			// 29

};


STD_ROM_PICK(opwolfb);
STD_ROM_FN(opwolfb);

struct BurnDriver BurnDrvopwolf = {
	"opwolf",NULL, NULL, "1987",
	"Operation Wolf (World)\0", "Protection C-Chip not emulated", "Taito", "Custom Taito",
	NULL, NULL, NULL, NULL,
	0,1,HARDWARE_MISC_MISC,
	NULL,opwolfRomInfo,opwolfRomName,opwolfInputInfo, opwolfDIPInfo,
	opwolfInit,opwolfExit,opwolfFrame,NULL,opwolfScan,
	&taitoRecalcPal,320,240,4,3
};

struct BurnDriverD BurnDrvOpwolfu = {
	"opwolfu", "opwolf", NULL, "1987",
	"Operation Wolf (US)\0", "Protection C-Chip not emulated", "Taito", "Custom Taito",
	NULL, NULL, NULL, NULL,
	BDF_CLONE,2,HARDWARE_MISC_MISC,
	NULL,opwolfuRomInfo,opwolfuRomName,opwolfInputInfo, opwolfDIPInfo,
	opwolfInit,opwolfExit,opwolfFrame,NULL,opwolfScan,
	&taitoRecalcPal,320,240,4,3
};

struct BurnDriver BurnDrvopwolfb = {
	"opwolfb", "opwolf", NULL, "1987",
	"Operation Bear (bootleg)\0", NULL, "Bear", "Custom Taito",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG,2,HARDWARE_MISC_MISC,
	NULL,opwolfbRomInfo,opwolfbRomName,opwolfInputInfo, opwolfDIPInfo,
	opwolfInit,opwolfExit,opwolfFrame,NULL,opwolfScan,
	&taitoRecalcPal,320,240,4,3
};

