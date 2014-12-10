#include <string.h>
#include "doze.h"

#include <stdio.h>

int nDozeVer = 0x1004;								// Version number of the library

static int Interrupt(int nVal)
{
	if ((Doze.iff & 0xFF) == 0) {					// not enabled
		return 0;
	}

//	printf("    IRQ taken\n");

	// Get out of any halt opcodes
	if (DozeAsmRead(Doze.pc) == 0x76) {
		Doze.pc++;
	}

	Doze.iff = 0;

	if (Doze.im == 0) {
		DozeAsmCall((unsigned short)(nVal & 0x38));	// rst nn
		return 13;									// cycles done
	} else {
		if (Doze.im == 2) {
			int nTabAddr = 0, nIntAddr = 0;
			// Get interrupt address from table (I points to the table)
			nTabAddr = (Doze.ir & 0xFF00) + nVal;

			// Read 16-bit table value
			nIntAddr  = DozeAsmRead((unsigned short)(nTabAddr + 1)) << 8;
			nIntAddr |= DozeAsmRead((unsigned short)(nTabAddr));

			DozeAsmCall((unsigned short)(nIntAddr));
			return 19;								// cycles done
		} else {
			DozeAsmCall(0x38);						// rst 38h
			return 13;								// cycles done
		}
	}
}

// Try to take the latched interrupt
static inline void TryInt()
{
	int nDid;

	if (Doze.nInterruptLatch & DOZE_IRQSTATUS_NONE) {
		return;
	}

	nDid = Interrupt(Doze.nInterruptLatch & 0xFF);	// Success! we did some cycles, and took the interrupt
	if (nDid > 0 && (Doze.nInterruptLatch & DOZE_IRQSTATUS_AUTO)) {
		Doze.nInterruptLatch = DOZE_IRQSTATUS_NONE;
	}

	Doze.nCyclesLeft -= nDid;
}

void __cdecl DozeRun()
{
	TryInt();										// Try the interrupt before we begin

	if (Doze.nCyclesLeft < 0) {
		return;
	}

	if (DozeAsmRead(Doze.pc) == 0x76) {
		// cpu is halted (repeatedly doing halt inst.)
		int nDid = (Doze.nCyclesLeft >> 2) + 1;
		Doze.ir = (unsigned short)(((Doze.ir + nDid) & 0x7F) | (Doze.ir & 0xFF80)); // Increase R register
		Doze.nCyclesLeft -= nDid;

		return;
	}

	// Find out about mid-exec EIs
	Doze.nEI = 1;
	DozeAsmRun();

	// Just enabled interrupts
	while (Doze.nEI == 2) {

//		printf("    EI executed\n");

		// (do one more instruction before interrupt)
		int nTodo = Doze.nCyclesLeft;
		Doze.nCyclesLeft = 0;
		Doze.nEI = 0;
		DozeAsmRun();
		Doze.nCyclesLeft += nTodo;

		TryInt();

		// And continue the rest of the exec
		DozeAsmRun();
	}
}

int __cdecl DozeReset()
{
	// Reset z80
	memset(&Doze, 0, 32);

	Doze.af = 0x0040;
	Doze.ix = 0xFFFF;
	Doze.iy = 0xFFFF;

	return 0;
}

int __cdecl DozeNmi()
{
	Doze.iff &= 0xFF00;						// reset iff1
	DozeAsmCall((unsigned short)0x66);		// Do nmi

	return 12;
}
