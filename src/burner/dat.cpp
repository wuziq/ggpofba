// Burner data file module (for ROM managers)
// written    2001 LoqiqX
// updated 11/2003 by LvR -- essentially a rewrite

#include "burner.h"

int write_datfile(int nDatType, FILE* fDat)
{
	int nRet=0;
	unsigned int nOldSelect=0;
	unsigned int nGameSelect=0;
	unsigned int nParentSelect,nBoardROMSelect;

	nOldSelect=nBurnDrvSelect;										// preserve the currently selected driver

	// Go over each of the games
	for (nGameSelect=0;nGameSelect<nBurnDrvCount;nGameSelect++)
	{
		char sgName[16];
		char spName[16];
		char sbName[16];
		unsigned int i=0;
		int nPass=0;

		nBurnDrvSelect=nGameSelect;									// Switch to driver nGameSelect

		if (BurnDrvGetFlags() & BDF_BOARDROM) {
			continue;
		}

		strcpy(sgName, BurnDrvGetTextA(DRV_NAME));
		strcpy(spName, "");											// make sure this string is empty before we start
		strcpy(sbName, "");											// make sure this string is empty before we start

		// Check to see if the game has a parent
		if (BurnDrvGetTextA(DRV_PARENT))
		{
			nParentSelect=-1U;
			while (BurnDrvGetTextA(DRV_PARENT))
			{
				strcpy(spName, BurnDrvGetTextA(DRV_PARENT));
				for (i=0;i<nBurnDrvCount;i++)
				{
					nBurnDrvSelect=i;
					if (!strcmp(spName, BurnDrvGetTextA(DRV_NAME)))
					{
						nParentSelect=i;
						break;
					}
				}
			}

			nBurnDrvSelect=nGameSelect;								// restore driver select
		}
		else
			nParentSelect=nGameSelect;

		// Check to see if the game has a BoardROM
		if (BurnDrvGetTextA(DRV_BOARDROM))
		{
			nBoardROMSelect=-1U;
			strcpy(sbName, BurnDrvGetTextA(DRV_BOARDROM));
			for (i=0;i<nBurnDrvCount;i++)
			{
				nBurnDrvSelect=i;
				if (!strcmp(sbName, BurnDrvGetTextA(DRV_NAME)))
				{
					nBoardROMSelect=i;
					break;
				}
			}

			nBurnDrvSelect=nGameSelect;								// restore driver select
		}
		else
			nBoardROMSelect=nGameSelect;

		if (nDatType==0)
		{
			// Report problems
			if (nParentSelect==-1U)
				fprintf(fDat, "# Missing parent %s. It needs to be added to " APP_TITLE "!\n\n", spName);
			if (nBoardROMSelect==-1U)
				fprintf(fDat, "# Missing boardROM %s. It needs to be added to " APP_TITLE "!\n\n", sbName);

			// Write the header
			fprintf(fDat, "game (\n");
			fprintf(fDat, "\tname %s\n", sgName);

			if (nParentSelect!=nGameSelect && nParentSelect!=-1U)
			{
				fprintf(fDat, "\tcloneof %s\n", spName);
				fprintf(fDat, "\tromof %s\n", spName);
			}
			else
			{
				// Add "romof" (but not 'cloneof') line for games that have boardROMs
				if (nBoardROMSelect!=nGameSelect && nBoardROMSelect!=-1U)
				{
					fprintf(fDat, "\tromof %s\n", sbName);
				}
			}

			fprintf(fDat, "\tdescription \"%s\"\n", DecorateGameName(nBurnDrvSelect));
			fprintf(fDat, "\tyear %s\n", BurnDrvGetTextA(DRV_DATE));
			fprintf(fDat, "\tmanufacturer \"%s\"\n", BurnDrvGetTextA(DRV_MANUFACTURER));
		}

		// Write the individual ROM info
		for (nPass=0; nPass<2; nPass++)
		{
			nBurnDrvSelect=nGameSelect;

			// Skip pass 0 if possible
			if (nPass==0 && (nBoardROMSelect==nGameSelect || nBoardROMSelect==-1U || nDatType!=0))
				continue;

			// Go over each of the files needed for this game (upto 0x0100)
			for (i=0, nRet=0; nRet==0 && i<0x100; i++)
			{
				int nRetTmp=0;
				struct BurnRomInfo ri;
				int nLen; unsigned int nCrc;
				char *szPossibleName=NULL;
				int j, nMerged=0;

				memset(&ri,0,sizeof(ri));

				// Get info on this file
				nBurnDrvSelect=nGameSelect;
				nRet=BurnDrvGetRomInfo(&ri,i);
				nRet+=BurnDrvGetRomName(&szPossibleName,i,0);

				if (ri.nLen==0) continue;

				if (nRet==0)
				{
					struct BurnRomInfo riTmp;
					char *szPossibleNameTmp;
					nLen=ri.nLen; nCrc=ri.nCrc;

					// Check for files from boardROMs
					if (nBoardROMSelect!=nGameSelect && nBoardROMSelect!=-1U) {
						nBurnDrvSelect=nBoardROMSelect;
						nRetTmp=0;

						// Go over each of the files needed for this game (upto 0x0100)
						for (j=0; nRetTmp==0 && j<0x100; j++)
						{
							memset(&riTmp,0,sizeof(riTmp));

							nRetTmp+=BurnDrvGetRomInfo(&riTmp,j);
							nRetTmp+=BurnDrvGetRomName(&szPossibleNameTmp,j,0);

							if (nRetTmp==0)
							{
								if (riTmp.nLen && riTmp.nCrc==nCrc && !strcmp(szPossibleName, szPossibleNameTmp))
								{
									// This file is from a boardROM
									nMerged|=2;
									nRetTmp++;
								}
							}
						}
					}

					if (!nMerged && nParentSelect!=nGameSelect && nParentSelect!=-1U) {
						nBurnDrvSelect=nParentSelect;
						nRetTmp=0;

						// Go over each of the files needed for this game (upto 0x0100)
						for (j=0; nRetTmp==0 && j<0x100; j++)
						{
							memset(&riTmp,0,sizeof(riTmp));

							nRetTmp+=BurnDrvGetRomInfo(&riTmp,j);
							nRetTmp+=BurnDrvGetRomName(&szPossibleNameTmp,j,0);

							if (nRetTmp==0)
							{
								if (riTmp.nLen && riTmp.nCrc==nCrc && !strcmp(szPossibleName, szPossibleNameTmp))
								{
									// This file is from a parent set
									nMerged|=1;
									nRetTmp++;
								}
							}
						}
					}

					nBurnDrvSelect=nGameSelect;						// Switch back to game
				}

				if (nDatType==0)
				{
					// Selectable BIOS meta info
					if (nPass==0 && nMerged&2 && ri.nType&BRF_SELECT)
						fprintf(fDat, "\tbiosset ( name %d description \"%s\" %s)\n", i - 128, szPossibleName, ri.nType & BRF_OPT ? "" : "default yes ");
					// File info
					if (nPass==1 && !nMerged) {
						if (ri.nType & BRF_NODUMP) {
							fprintf(fDat, "\trom ( name %s size %d flags nodump )\n", szPossibleName, ri.nLen);
						} else {
							fprintf(fDat, "\trom ( name %s size %d crc %08x )\n", szPossibleName, ri.nLen, ri.nCrc);
						}
					}
					if (nPass==1 && nMerged)
					{
						// Selectable BIOS file info
						if (nMerged&2 && ri.nType&BRF_SELECT)
							fprintf(fDat, "\trom ( name %s merge %s bios %d size %d crc %08x )\n", szPossibleName, szPossibleName, i - 128, ri.nLen, ri.nCrc);
						// Files from parent/boardROMs
						else {
							if (ri.nType & BRF_NODUMP) {
								fprintf(fDat, "\trom ( name %s merge %s size %d flags nodump )\n", szPossibleName, szPossibleName, ri.nLen);
							} else {
								fprintf(fDat, "\trom ( name %s merge %s size %d crc %08x )\n", szPossibleName, szPossibleName, ri.nLen, ri.nCrc);
							}
						}
					}
				}
				else
				{
					if (nPass == 0) continue;						// No meta info needed

					if (nParentSelect!=nGameSelect && nParentSelect!=-1U)
					{
						nBurnDrvSelect=nParentSelect;				// Switch to parent
						fprintf(fDat, "¬%s¬%s", spName, DecorateGameName(nBurnDrvSelect));
						nBurnDrvSelect=nGameSelect;					// Switch back to game
					}
					else
						fprintf(fDat, "¬%s¬%s", BurnDrvGetTextA(DRV_NAME), DecorateGameName(nBurnDrvSelect));

					fprintf(fDat, "¬%s¬%s", BurnDrvGetTextA(DRV_NAME), DecorateGameName(nBurnDrvSelect));

		   			fprintf(fDat, "¬%s¬%08x¬%d", szPossibleName, ri.nCrc, ri.nLen);

					if (nParentSelect!=nGameSelect && nParentSelect!=-1U)
					{
						// Files from parent
						fprintf(fDat, "¬%s", spName);
					}
					else
					{
						// Files from boardROM
						if (nBoardROMSelect!=nGameSelect && nBoardROMSelect!=-1U)
							fprintf(fDat, "¬%s", sbName);
					}

					if (!nMerged)
						fprintf(fDat, "¬¬\n");
					else
						fprintf(fDat, "¬%s¬\n", szPossibleName);
				}
			}
		}

		if (nDatType==0)
			fprintf(fDat, ")\n\n");
	}

	if (nDatType!=0)
		fprintf(fDat, "[RESOURCES]\n");

	// Do another pass over each of the games to find boardROMs
	for (nBurnDrvSelect=0; nBurnDrvSelect<nBurnDrvCount; nBurnDrvSelect++)
	{
		int i, nPass;

		if (!(BurnDrvGetFlags() & BDF_BOARDROM)) {
			continue;
		}

		if (nDatType==0)
		{
			fprintf(fDat, "resource (\n");
			fprintf(fDat, "\tname %s\n", BurnDrvGetTextA(DRV_NAME));
			fprintf(fDat, "\tdescription \"%s\"\n", DecorateGameName(nBurnDrvSelect));
			fprintf(fDat, "\tyear %s\n", BurnDrvGetTextA(DRV_DATE));
			fprintf(fDat, "\tmanufacturer \"%s\"\n", BurnDrvGetTextA(DRV_COMMENT));

		}

		for (nPass=0; nPass<2; nPass++)
		{
			// No meta information needed
			if (nPass==0 && nDatType!=0) continue;

			// Go over each of the individual files (upto 0x0100)
			for (i=0; i<0x100; i++)
			{
				struct BurnRomInfo ri;
				char *szPossibleName=NULL;

				memset(&ri,0,sizeof(ri));

				nRet=BurnDrvGetRomInfo(&ri,i);
				nRet+=BurnDrvGetRomName(&szPossibleName,i,0);

				if (ri.nLen==0) continue;

				if (nRet==0) {
					if (nDatType==0)
					{
						if (nPass==0)
						{
							if (ri.nType&BRF_SELECT)
								fprintf(fDat, "\tbiosset ( name %d description \"%s\" %s)\n", i, szPossibleName, ri.nType & 0x80 ? "" : "default yes ");
						}
						else
						{
							if (ri.nType&BRF_SELECT)
								fprintf(fDat, "\trom ( name %s bios %d size %d crc %08x )\n", szPossibleName, i, ri.nLen, ri.nCrc);
							else
								fprintf(fDat, "\trom ( name %s size %d crc %08x )\n", szPossibleName, ri.nLen, ri.nCrc);
						}
					}
					else
					{
						fprintf(fDat, "¬%s¬%s", BurnDrvGetTextA(DRV_NAME), DecorateGameName(nBurnDrvSelect));
						fprintf(fDat, "¬%s¬%s", BurnDrvGetTextA(DRV_NAME), DecorateGameName(nBurnDrvSelect));
			   			fprintf(fDat, "¬%s¬%08x¬%d", szPossibleName, ri.nCrc, ri.nLen);
						fprintf(fDat, "¬¬¬\n");
					}
				}
			}
		}

		if (nDatType==0)
			fprintf(fDat, ")\n");
	}

	// Restore current driver
	nBurnDrvSelect=nOldSelect;

	return 0;
}

int create_datfile(TCHAR* szFilename, int nDatType)
{
	FILE *fDat=0;
	int nRet=0;

	if ((fDat = _tfopen(szFilename, _T("w")))==0)
		return -1;

	if (nDatType==0)
	{
		fprintf(fDat, "clrmamepro (\n");
		fprintf(fDat, "\tname \"" APP_TITLE "\"\n");
		fprintf(fDat, "\tdescription \"" APP_TITLE " v%.20s\"\n", szAppBurnVer);
		fprintf(fDat, "\tcategory \"" APP_DESCRIPTION "\"\n");
		fprintf(fDat, "\tversion %s\n", szAppBurnVer);
		fprintf(fDat, "\tauthor \"" APP_TITLE " v%.20s\"\n", szAppBurnVer);
		fprintf(fDat, "\tforcezipping zip\n");
		fprintf(fDat, ")\n\n");
	}
	else
	{
		fprintf(fDat, "[CREDITS]\n");
		fprintf(fDat, "Author=" APP_TITLE "\n");
		fprintf(fDat, "Version=%.20s\n", szAppBurnVer);
		fprintf(fDat, "Comment=" APP_DESCRIPTION "\n");
		fprintf(fDat, "[DAT]\n");
		fprintf(fDat, "version=2.00\n");
		fprintf(fDat, "[EMULATOR]\n");
		fprintf(fDat, "refname=" APP_TITLE "\n");
		fprintf(fDat, "version=" APP_TITLE " v%.20s\n", szAppBurnVer);
		fprintf(fDat, "[GAMES]\n");
	}

	nRet =  write_datfile(nDatType, fDat);

	fclose(fDat);

	return nRet;
}
