// Cheat module

#include "burnint.h"

bool bCheatsAllowed;
CheatInfo* pCheatInfo = NULL;

static bool bCheatsEnabled = false;

int CheatUpdate()
{
	bCheatsEnabled = false;

	if (bCheatsAllowed) {
		CheatInfo* pCurrentCheat = pCheatInfo;
		CheatAddressInfo* pAddressInfo;

		while (pCurrentCheat) {
			if (pCurrentCheat->nStatus > 1) {
				pAddressInfo = pCurrentCheat->pOption[pCurrentCheat->nCurrent]->AddressInfo;
				if (pAddressInfo->nAddress) {
					bCheatsEnabled = true;
				}
			}
			pCurrentCheat = pCurrentCheat->pNext;
		}
	}

	return 0;
}

int CheatEnable(int nCheat, int nOption)
{
	int nCurrentCheat = 0;
	CheatInfo* pCurrentCheat = pCheatInfo;
	CheatAddressInfo* pAddressInfo;
	int nOpenCPU = -1;

	if (!bCheatsAllowed) {
		return 1;
	}

	if (nOption >= CHEAT_MAX_OPTIONS) {
		return 1;
	}

	while (pCurrentCheat && nCurrentCheat <= nCheat) {
		if (nCurrentCheat == nCheat) {

			if (nOption == -1) {
				nOption = pCurrentCheat->nDefault;
			}

			if (pCurrentCheat->nType != 1) {

				// Return OK if the cheat is already active with the same option
				if (pCurrentCheat->nCurrent == nOption) {
					return 0;
				}

				// Deactivate old option (if any)
				pAddressInfo = pCurrentCheat->pOption[nOption]->AddressInfo;
				while (pAddressInfo->nAddress) {

					if (pAddressInfo->nCPU != nOpenCPU) {
						if (nOpenCPU != -1) {
							SekClose();
						}

						nOpenCPU = pAddressInfo->nCPU;
						SekOpen(nOpenCPU);
					}

					// Write back original values to memory
					SekWriteByteROM(pAddressInfo->nAddress, pAddressInfo->nOriginalValue);
					pAddressInfo++;
				}
			}

			// Activate new option
			pAddressInfo = pCurrentCheat->pOption[nOption]->AddressInfo;
			while (pAddressInfo->nAddress) {

				if (pAddressInfo->nCPU != nOpenCPU) {
					if (nOpenCPU != -1) {
						SekClose();
					}

					nOpenCPU = pAddressInfo->nCPU;
					SekOpen(nOpenCPU);
				}

				// Copy the original values
				pAddressInfo->nOriginalValue = SekReadByte(pAddressInfo->nAddress);

				if (pCurrentCheat->nType != 0) {
					if (pAddressInfo->nCPU != nOpenCPU) {
						if (nOpenCPU != -1) {
							SekClose();
						}

						nOpenCPU = pAddressInfo->nCPU;
						SekOpen(nOpenCPU);
					}

					// Activate the cheat
					SekWriteByteROM(pAddressInfo->nAddress, pAddressInfo->nValue);
				}

				pAddressInfo++;
			}

			// Set cheat status and active option
			if (pCurrentCheat->nType != 1) {
				pCurrentCheat->nCurrent = nOption;
			}
			if (pCurrentCheat->nType == 0) {
				pCurrentCheat->nStatus = 2;
			}
			if (pCurrentCheat->nType == 2) {
				pCurrentCheat->nStatus = 1;
			}

			break;
		}
		pCurrentCheat = pCurrentCheat->pNext;
		nCurrentCheat++;
	}

	if (nOpenCPU != -1) {
		SekClose();
	}

	CheatUpdate();

	if (nCurrentCheat == nCheat && pCurrentCheat) {
		return 0;
	}

	return 1;
}

int CheatApply()
{
	if (!bCheatsEnabled) {
		return 0;
	}

	int nOpenCPU = -1;

	CheatInfo* pCurrentCheat = pCheatInfo;
	CheatAddressInfo* pAddressInfo;
	while (pCurrentCheat) {
		if (pCurrentCheat->nStatus > 1) {
			pAddressInfo = pCurrentCheat->pOption[pCurrentCheat->nCurrent]->AddressInfo;
			while (pAddressInfo->nAddress) {

				if (pAddressInfo->nCPU != nOpenCPU) {
					if (nOpenCPU != -1) {
						SekClose();
					}

					nOpenCPU = pAddressInfo->nCPU;
					SekOpen(nOpenCPU);
				}

				SekWriteByteROM(pAddressInfo->nAddress, pAddressInfo->nValue);
				pAddressInfo++;
			}
		}
		pCurrentCheat = pCurrentCheat->pNext;
	}

	if (nOpenCPU != -1) {
		SekClose();
	}

	return 0;
}

int CheatInit()
{
	CheatExit();

	bCheatsEnabled = false;

	return 0;
}

void CheatExit()
{
	if (pCheatInfo) {
		CheatInfo* pCurrentCheat = pCheatInfo;
		CheatInfo* pNextCheat;

		do {
			pNextCheat = pCurrentCheat->pNext;
			for (int i = 0; i < CHEAT_MAX_OPTIONS; i++) {
				free(pCurrentCheat->pOption[i]);
			}
			free(pCurrentCheat);
		} while ((pCurrentCheat = pNextCheat) != 0);
	}

	pCheatInfo = NULL;
}

