// 93Cxx EEPROM module
#include "burnint.h"
#include "eeprom_93cxx.h"

static unsigned char* Memory = NULL;
static int nMemorySize;
static int nDataWidth, nDataMask;
static int nAddressMask, nAddressWidth;

static struct {
	char SK; char DO; bool bWritable; int nDIAcc; int nDOAcc; int nReadBit; int nWriteBit;
} EEPROM;

void EEPROMWrite(char SK, char CS, char DI)
{
//	printf("   EEPROM written SK: %02X, CS: %02X, DI: %02X\n", SK, CS, DI);

	if (CS == 0) {												// CS low, end command/stand-by mode
		EEPROM.nReadBit = 0;
		EEPROM.nWriteBit = 0;
		EEPROM.nDIAcc = 0;
		EEPROM.DO = 1;

		// Write/erase commands *should* be executed here

		EEPROM.SK = SK;
		return;
	}

	if (SK && EEPROM.SK == 0) {									// Rising edge of SK, execute one cycle
		if (EEPROM.nReadBit == 0) {								// Read command

			if (DI && EEPROM.nDIAcc == 0) {						// Start of a new command
				EEPROM.nWriteBit = 0;
			}

			// Read DI line
			EEPROM.nWriteBit++;
			EEPROM.nDIAcc <<= 1;
			if (DI) {
				EEPROM.nDIAcc |= 1;
			}

			if (EEPROM.nWriteBit == nAddressWidth + nDataWidth + 3) {	// Command + address + value read
				if ((EEPROM.nDIAcc >> (nAddressWidth + nDataWidth)) == 5 && EEPROM.bWritable) {
//					printf("   EEPROM address %04X->%04X\n", (EEPROM.nDIAcc >> nDataWidth) & nAddressMask, EEPROM.nDIAcc & nDataMask);
					if (nDataWidth > 8) {
						((unsigned short*)Memory)[(EEPROM.nDIAcc >> nDataWidth) & nAddressMask] = EEPROM.nDIAcc & nDataMask;
					} else {
						Memory[(EEPROM.nDIAcc >> nDataWidth) & nAddressMask] = EEPROM.nDIAcc & nDataMask;
					}
				}
			} else {
				if (EEPROM.nWriteBit == nAddressWidth + 3) {	// Command + address read
					switch (EEPROM.nDIAcc >> nAddressWidth) {
						case 0x04: {
							switch ((EEPROM.nDIAcc >> (nAddressWidth - 2)) & 3) {
								case 0x00:						// EWDS Erase/Write disable
//									printf("   EEPROM -> EWDS\n");
									EEPROM.bWritable = false;
									break;
								case 0x01:						// WRAL Write all
//									printf("   EEPROM -> WRAL\n");
									break;
								case 0x02:						// ERAL Erase all
//									printf("   EEPROM -> ERAL\n");
									break;
								case 0x03:						// EWEN Erase/Write enable
//									printf("   EEPROM -> EWEN\n");
									EEPROM.bWritable = true;
									break;
							}
							break;
						}
						case 0x05:								// Write
							break;
						case 0x06:								// Read
							if (nDataWidth > 8) {
//								printf("   EEPROM address %04X read (%04X)\n", EEPROM.nDIAcc & nAddressMask, ((unsigned short*)Memory)[EEPROM.nDIAcc & nAddressMask]);
								EEPROM.nDOAcc = ((unsigned short*)Memory)[EEPROM.nDIAcc & nAddressMask];
							} else {
//								printf("   EEPROM address %04X read (%04X)\n", EEPROM.nDIAcc & nAddressMask, Memory[EEPROM.nDIAcc & nAddressMask]);
								EEPROM.nDOAcc = Memory[EEPROM.nDIAcc & nAddressMask];
							}
							EEPROM.nReadBit = nDataWidth + 1;
							break;
						case 0x07:								// Erase
							if (EEPROM.bWritable) {
//								printf("  EEPROM address %04X->Erase\n", EEPROM.nDIAcc & nAddressMask);
								if (nDataWidth > 8) {
									((unsigned short*)Memory)[EEPROM.nDIAcc & nAddressMask] = nDataMask;
								} else {
									Memory[EEPROM.nDIAcc & nAddressMask] = nDataMask;
								}
							}
							break;
					}
				}
			}
		}

		if (EEPROM.nReadBit) {									// Place next bit on DO
			EEPROM.nReadBit--;
			EEPROM.DO = (EEPROM.nDOAcc >> nDataWidth) & 1;
			EEPROM.nDOAcc <<= 1;
		} else {
			EEPROM.DO = 1;										// Indicate EEPROM ready
		}
	}

	EEPROM.SK = SK;
}

int EEPROMRead()
{
//	printf("   EEPROM DO Read (%i)\n", EEPROM.DO);
	return EEPROM.DO;
}

void EEPROMFill(unsigned char* pData, int nOffset, int nSize)
{
	memcpy(Memory + nOffset, pData, nSize);
}

void EEPROMReset()
{
	EEPROM.bWritable = false;

	EEPROM.nReadBit = 0;
	EEPROM.nWriteBit = 0;
	EEPROM.nDIAcc = 0;
	EEPROM.DO = 1;

	return;
}

void EEPROMScan(int nAction, int* pnMin)
{
	struct BurnArea ba;

	if (nAction & ACB_DRIVER_DATA) {								// Scan variables

		if (pnMin && *pnMin < 0x020902) {						// Return minimum compatible version
			*pnMin = 0x020902;
		}

		SCAN_VAR(EEPROM);
	}

	if (nAction & ACB_NVRAM) {									// Scan memory

		if (pnMin && (nAction & ACB_TYPEMASK) == ACB_NVRAM) {	// Return minimum compatible version
			*pnMin = 0x020902;
		}

		memset(&ba, 0, sizeof(ba));
    	ba.Data		= Memory;
		ba.nLen		= nMemorySize;
		ba.szName	= "EEPROM memory";
		BurnAcb(&ba);
	}
}

void EEPROMExit()
{

#if 0
	FILE* fp = fopen("eeprom", "wb");
	if (fp) {
		fwrite(Memory, nMemorySize, 1, fp);
		fclose(fp);
	}
#endif

	free(Memory);
	Memory = NULL;
}

// nSize:  size of memory in bits (must be a power of 2)
// nWidth: wordsize in bits (8 or 16)
int EEPROMInit(int nSize, int nWidth)
{
	free(Memory);

	memset(&EEPROM, 0, sizeof(EEPROM));

	for (nAddressWidth = 4; (1 << nAddressWidth) < nSize / nWidth; nAddressWidth++) { }
	nAddressMask = (nSize / nWidth) - 1;
	nDataWidth = nWidth;
	nDataMask = (1 << nWidth) - 1;

	nMemorySize = nSize >> 3;
	Memory = (unsigned char*)malloc(nMemorySize);

	if (Memory == NULL) {
		return 1;
	}

	memset(Memory, 0, nMemorySize);

	EEPROMReset();

	return 0;
}

