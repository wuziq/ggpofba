#include "cps.h"
// CPS - Read/Write

// Input bits
#define INP(nnn) unsigned char CpsInp##nnn[8];
CPSINPSET
#undef  INP

// Bytes to return from ports
#define INP(nnn) static unsigned char Inp##nnn;
CPSINPSET
#undef  INP

unsigned short CpsInp055 = 0;
unsigned short CpsInp05d = 0;
unsigned short CpsInpPaddle1 = 0;
unsigned short CpsInpPaddle2 = 0;
static int ReadPaddle = 0;
int CpsPaddle1Value = 0;
int CpsPaddle2Value = 0;
int CpsPaddle1 = 0;
int CpsPaddle2 = 0;
static int nDial055, nDial05d;

int PangEEP = 0;
int Forgottn = 0;
int Cps1QsHack = 0;
int Cawingb = 0;
int Wofh = 0;
int Pzloop2 = 0;
int Ssf2tb = 0;

static int nCalc[2] = {0, 0};

static const bool nCPSExtraNVRAM = false;
static int n664001;

#define INP(nnnn) unsigned char CpsInp##nnnn[8];
CPSINPEX
#undef  INP

#define INP(nnnn) static unsigned char Inp##nnnn;
CPSINPEX
#undef  INP


// Read input port 0x000-0x1ff
static unsigned char CpsReadPort(const unsigned int ia)
{
	unsigned char d = 0xFF;
	
	if (ia == 0x000) {
		d = (unsigned char)~Inp000;
		if (Pzloop2) {
			if (ReadPaddle) {
				d -= CpsPaddle2Value;
			} else {
				d = CpsPaddle2;
			}
		}
		return d;
	}
	if (ia == 0x001) {
		d = (unsigned char)~Inp001;
		if (Pzloop2) {
			if (ReadPaddle) {
				d -= CpsPaddle1Value;
			} else {
				d = CpsPaddle1;
			}
		}
		return d;
	}
	if (ia == 0x010) {
		d = (unsigned char)~Inp010;
		return d;
	}
	if (ia == 0x011) {
		d = (unsigned char)~Inp011;
		return d;
	}

	if (ia == 0x018) {
		d = (unsigned char)~Inp018;
		return d;
	}

	if (ia == 0x019) {
		d = (unsigned char)~Inp019;
		return d;
	}

	if (ia == 0x01A) {
		d = (unsigned char)~Cpi01A;
		return d;
	}
	if (ia == 0x01C) {
		d = (unsigned char)~Cpi01C;
		return d;
	}
	if (ia == 0x01E) {
		d = (unsigned char)~Cpi01E;
		return d;
	}


	if (Cps == 2) {
		// Used on CPS2 only I think
		if (ia == 0x020) {
			d = (unsigned char)~Inp020;
			return d;
		}
		if (ia == 0x021) {
			d = (unsigned char)~Inp021;
			d &= 0xFE;
			d |= EEPROMRead();
			return d;
		}

		// CPS2 Volume control
		if (ia == 0x030) {
			if (Ssf2tb) {
				d = 0x20;
			} else {
				d = 0xe0;
			}
			return d;
		}
		if (ia == 0x031) {
			d = 0x21;
			return d;
		}

		if (ia >= 0x0100 && ia < 0x0200) {
			static int nRasterLine;

//			bprintf(PRINT_NORMAL, _T("  - port 0x%02X (%3i)\n"), ia & 255, SekCurrentScanline());

			// The linecounters seem to return the line at which the last IRQ triggered by this counter is scheduled minus the current line
			if ((ia & 0x0FE) == 0x50) {
				if ((ia & 1) == 0) {
					nRasterLine = nIrqLine50 - SekCurrentScanline();
					return nRasterLine >> 8;
				} else {
					return nRasterLine & 0xFF;
				}
			}
			if ((ia & 0x0FE) == 0x52) {
				if ((ia & 1) == 0) {
					nRasterLine = nIrqLine52 - SekCurrentScanline();
					return nRasterLine >> 8;
				} else {
					return nRasterLine & 0xFF;
				}
			}

		}

	} else {
		// Board ID
		if (ia == 0x100 + CpsBID[0]) {
			d = (unsigned char)CpsBID[1];
			return d;
		}
		if (ia == 0x100 + (CpsBID[0] + 1)) {
			d = (unsigned char)CpsBID[2];
			return d;
		}

		// used mainly by non-Q-Sound games - but also by dinoh
		if (ia == 0x177) {
			d = (unsigned char)~Inp177;
			return d;
		}

		if (Cps1Qs == 1) {
			// CPS1 EEPROM read
			if (ia == 0xC007) {
				return EEPROMRead();
			}
			// CPS1 Player 3
			if (ia == 0xC000) {
				d = (unsigned char)~Inpc000;
				return d;
			}
			if (ia == 0xC001) {
				d = (unsigned char)~Inpc001;
				return d;
			}
			// CPS1 Player 4
			if (ia == 0xC002) {
				d = (unsigned char)~Inpc002;
				return d;
			}
			if (ia == 0xC003) {
				d = (unsigned char)~Inpc003;
				return d;
			}

			// used by wofh
			if (ia == 0x006) {
				d = (unsigned char)~Inp006;
				return d;
			}
			if (ia == 0x007) {
				d = (unsigned char)~Inp007;
				return d;
			}
		} else {
			if (Forgottn) {
				if (ia == 0x053) {
					return (nDial055 >>  8) & 0xFF;
				}
				if (ia == 0x055) {
					return (nDial055 >> 16) & 0xFF;
				}
				if (ia == 0x05B) {
					return (nDial05d >>  8) & 0xFF;
				}
				if (ia == 0x05D) {
					return (nDial05d >> 16) & 0xFF;
				}
			}

			// used by cawingb
			if (ia == 0x008) {
				d = (unsigned char)~Inp008;
				return d;
			}

			if (ia == 0x176) {
				d = (unsigned char)~Inp176;
				return d;
			}
			if (ia == 0x179) {
				d = (unsigned char)~Inp179;
				return d;
			}
			if (ia == 0x1FD) {
				d=(unsigned char)~Inp1fd;
				return d;
			}
		}
		if (PangEEP == 1) {
			// Pang3 EEPROM
			if (ia == 0x17B) {
				return EEPROMRead();
			}
		}
	}

	return d;
}

// Write output port 0x000-0x1ff
static void CpsWritePort(const unsigned int ia, unsigned char d)
{
	if ((Cps & 1) && Cps1Qs == 0) {
		if (Cawingb && ia == 0x006) {
			PsndSyncZ80((long long)SekTotalCycles() * nCpsZ80Cycles / nCpsCycles);

			PsndCode = d;
			return;
		}

		// CPS1 sound code
		if (ia == 0x181) {
			PsndSyncZ80((long long)SekTotalCycles() * nCpsZ80Cycles / nCpsCycles);
//			bprintf(PRINT_NORMAL, (T" -- Sound latch -> %i\n"), d);

			PsndCode = d;
			return;
		}

		// CPS1 sound fade
		if (ia == 0x189) {
			PsndSyncZ80((long long)SekTotalCycles() * nCpsZ80Cycles / nCpsCycles);

			PsndFade = d;
			return;
		}

		if (ia == 0x041) {
			nDial055 = 0;
		}
		if (ia == 0x049) {
			nDial05d = 0;
		}
	}

	if (Cps == 1 && Cps1QsHack == 1) {
		if (ia == 0x181) {
			// Pass the Sound Code to the Q-Sound Shared Ram
			CpsZRamC0[0x001] = d;
		}
	}

	// CPS registers
	if (ia >= 0x100 && ia < 0x200) {
		//Pang3 EEPROM
		if (PangEEP == 1 && ia == 0x17B) {
			EEPROMWrite(d & 0x40, d & 0x80, d & 0x01);
			return;
		}
		CpsReg[(ia ^ 1) & 0xFF] = d;
//		int aa = ia & 0xfe;
//		if (aa == 0x0e || aa == 0x12 || aa == 0x16) {
//			bprintf(PRINT_NORMAL, _T("  - sc (%3i)\n"), SekCurrentScanline());
//		}
		return;
	}

	if (Cps == 2) {
		if (ia == 0x40) {
			EEPROMWrite(d & 0x20, d & 0x40, d & 0x10);

			return;
		}

		// CPS2 object bank select
		if ((ia & 0x1FF) == 0x0E1) {
//			bprintf(PRINT_NORMAL, _T("  - %2i (%3i)\n"), d & 1, SekCurrentScanline());
//			CpsObjGet();
			CpsMapObjectBanks(d & 1);
			return;
			EEPROMWrite(d & 0x40, d & 0x80, d & 0x01);
			return;
		}
		
		if (ia == 0x41 && Pzloop2) {
			ReadPaddle = d & 0x02;
		}
	}

	if (Cps1Qs == 1) {
		//CPS1 EEPROM write
		if (ia == 0xc007) {
			EEPROMWrite(d & 0x40, d & 0x80, d & 0x01);
			return;
		}
	}
}

unsigned char __fastcall CpsReadByte(unsigned int a)
{
//	a &= 0xFFFFFF;

	// Input ports mirrored between 0x800000 and 0x807fff
	if ((a & 0xFF8000) == 0x800000) {
		return CpsReadPort(a & 0x1FF);
	}

	if (Cps == 2) {
		if ((a & 0xFF8000) == 0x660000) {
			if (a == 0x664001) {
				return n664001;
			}
		}

		return 0x00;
	}

	if (Cps1Qs == 1) {
		// CPS1 EEPROM & Player 3/4
		if (a >= 0xF1C000 && a <= 0xF1C007) {
			return CpsReadPort(a & 0xC00F);
		}

		return 0x00;
	}

	if (Cawingb || Wofh) {
		if ((a & 0xFF8000) == 0x880000) {
			return CpsReadPort(a & 0x1FF);
		}
	}
	
	return 0x00;
}

void __fastcall CpsWriteByte(unsigned int a,unsigned char d)
{
	// Output ports mirrored between 0x800000 and 0x807fff
	if ((a & 0xFF8000) == 0x800000) {
		CpsWritePort(a & 0x1FF, d);
		return;
	}

	if (Cps == 2) {
		// 0x400000 registers
		if ((a & 0xFFFFF0) == 0x400000)	{
			CpsFrg[a & 0x0F] = d;
			return;
		}
		if ((a & 0xFF8000) == 0x660000) {
			if (a == 0x664001) {
				// bit 1 toggled on/off each frame
				n664001 = d;
			}
			
			return;
		}

		return;
	}

	if (Cps1Qs == 1) {
		// CPS1 EEPROM
		if (a == 0xf1c007) {
			CpsWritePort(a & 0xC00F, d);
			return;
		}

		return;
	}

	if (Cawingb || Wofh) {
		if ((a & 0xFF8000) == 0x880000) {
			CpsWritePort(a & 0x1FF, d);
			return;
		}
	}
}

unsigned short __fastcall CpsReadWord(unsigned int a)
{
//	a &= 0xFFFFFF;

	if ((a & 0xFF8FFF) == 0x800100 + CpsMProt[3]) {
		return (unsigned short)((nCalc[0] * nCalc[1]) >> 16);
	}
	// ports mirrored between 0x800000 and 0x807fff
	if ((a & 0xFF8FFF) == 0x800100 + CpsMProt[2]) {
		return (unsigned short)((nCalc[0] * nCalc[1]));
	}
	
	SEK_DEF_READ_WORD(0, a);
}

void __fastcall CpsWriteWord(unsigned int a, unsigned short d)
{
	// ports mirrored between 0x800000 and 0x807fff
	if ((a & 0xFF8FFF) == 0x800100 + CpsMProt[0])
		nCalc[0] = d;
	if ((a & 0xFF8FFF) == 0x800100 + CpsMProt[1])
		nCalc[1] = d;

	if (a == 0x804040) {
		if ((d & 0x0008) == 0) {
			ZetReset();
		}
	}
	
	SEK_DEF_WRITE_WORD(0, a, d);
}

// Reset all inputs to zero
static int InpBlank()
{
#define INP(nnn) Inp##nnn = 0; memset(CpsInp##nnn, 0, sizeof(CpsInp##nnn));
	CPSINPSET
#undef INP

#define INP(nnnn) Inp##nnnn = 0; memset(CpsInp##nnnn, 0, sizeof(CpsInp##nnnn));
	CPSINPEX
#undef INP

	CpsInp055 = CpsInp05d = 0;

	return 0;
}

int CpsRwInit()
{
	InpBlank();
	return 0;
}

int CpsRwExit()
{
	InpBlank();
	return 0;
}

inline static void StopOpposite(unsigned char* pInput)
{
	if ((*pInput & 0x03) == 0x03) {
		*pInput &= ~0x03;
	}
	if ((*pInput & 0x0C) == 0x0C) {
		*pInput &= ~0x0C;
	}
}

int CpsRwGetInp()
{
	// Compile separate buttons into Inpxxx
#define INP(nnn) \
  { int i = 0; Inp##nnn = 0; \
    for (i = 0; i < 8; i++) { Inp##nnn |= (CpsInp##nnn[i] & 1) << i; }  }
	CPSINPSET
#undef INP


#define INP(nnnn) \
  { int i = 0; Inp##nnnn = 0; \
    for (i = 0; i < 8; i++) { Inp##nnnn |= (CpsInp##nnnn[i] & 1) << i; }  }
	CPSINPEX
#undef INP

	if (Forgottn) {
		// Handle analog controls
		nDial055 += (int)((short)CpsInp055);
		nDial05d += (int)((short)CpsInp05d);
	}
	
	if (Pzloop2) {
		if (ReadPaddle) {
			CpsPaddle1Value = 0;
			CpsPaddle2Value = 0;
			if (CpsInpPaddle1) {
				if (CpsInpPaddle1 > 0x8000) {
					CpsPaddle1Value = 2;
				}
	
				if (CpsInpPaddle1 < 0x7fff) {
					CpsPaddle1Value = 1;
				}
			}
			
			if (CpsInpPaddle2) {
				if (CpsInpPaddle2 > 0x8000) {
					CpsPaddle2Value = 2;
				}
	
				if (CpsInpPaddle2 < 0x7fff) {
					CpsPaddle2Value = 1;
				}
			}
		}
		
		CpsPaddle1 += (CpsInpPaddle1 >> 8) & 0xff;
		CpsPaddle2 += (CpsInpPaddle2 >> 8) & 0xff;
	}
	
	StopOpposite(&Inp000);
	StopOpposite(&Inp001);

	// Ghouls uses a 4-way stick
	if (Ghouls) {
		static unsigned char nPrevInp000, nPrevInp001;

		if ((Inp000 & 0x03) && (Inp000 & 0x0C)) {
			Inp000 ^= (nPrevInp000 & 0x0F);
		} else {
			nPrevInp000 = Inp000;
		}

		if ((Inp001 & 0x03) && (Inp001 & 0x0C)) {
			Inp001 ^= (nPrevInp001 & 0x0F);
		} else {
			nPrevInp001 = Inp001;
		}
	}

	if (nMaxPlayers > 2) {
		if (Cps == 2) {
			StopOpposite(&Inp011);
			if (nMaxPlayers == 4) {
				StopOpposite(&Inp010);
			}
		} else {
			StopOpposite(&Inp177);
			if (nMaxPlayers == 4) {
				StopOpposite(&Inp179);
			}
			if (Cps1Qs) {
				StopOpposite(&Inpc001);
				if (nMaxPlayers == 4) {
					StopOpposite(&Inpc003);
				}
			}
		}
	}

	return 0;
}
