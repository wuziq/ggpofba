#include "burner.h"

static bool SkipComma(TCHAR** s)
{
	while (**s && **s != _T(',')) {
		(*s)++;
	}

	if (**s == _T(',')) {
		(*s)++;
	}

	if (**s) {
		return true;
	}

	return false;
}

static void CheatError(TCHAR* pszFilename, int nLineNumber, CheatInfo* pCheat, TCHAR* pszInfo, TCHAR* pszLine)
{
	FBAPopupAddText(PUF_TEXT_NO_TRANSLATE, _T("Cheat file %s is malformed.\nPlease remove or repair the file.\n\n"), pszFilename);
	if (pCheat) {
		FBAPopupAddText(PUF_TEXT_NO_TRANSLATE, _T("Parse error at line %i, in cheat \"%s\".\n"), nLineNumber, pCheat->szCheatName);
	} else {
		FBAPopupAddText(PUF_TEXT_NO_TRANSLATE, _T("Parse error at line %i.\n"), nLineNumber);
	}

	if (pszInfo) {
		FBAPopupAddText(PUF_TEXT_NO_TRANSLATE, _T("Problem:\t%s.\n"), pszInfo);
	}
	if (pszLine) {
		FBAPopupAddText(PUF_TEXT_NO_TRANSLATE, _T("Text:\t%s\n"), pszLine);
	}

	FBAPopupDisplay(PUF_TYPE_ERROR);
}

static int ConfigParseFile(TCHAR* pszFilename)
{
#define INSIDE_NOTHING (0xFFFF & (1 << (sizeof(TCHAR) * 8) - 1))

	TCHAR szLine[1024];
	TCHAR* s;
	TCHAR* t;
	int nLen;

	int nLine = 0;
	TCHAR nInside = INSIDE_NOTHING;

	CheatInfo* pCurrentCheat = NULL;

	FILE* h = _tfopen(pszFilename, _T("rt"));
	if (h == NULL) {
		return 1;
	}

	while (1) {
		if (_fgetts(szLine, sizeof(szLine), h) == NULL) {
			break;
		}

		nLine++;

		nLen = _tcslen(szLine);
		// Get rid of the linefeed at the end
		while (szLine[nLen - 1] == 0x0A || szLine[nLen - 1] == 0x0D) {
			szLine[nLen - 1] = 0;
			nLen--;
		}

		s = szLine;													// Start parsing

		if (s[0] == _T('/') && s[1] == _T('/')) {					// Comment
			continue;
		}

		if ((t = LabelCheck(s, _T("include"))) != 0) {				// Include a file
			s = t;

			TCHAR szFilename[MAX_PATH] = _T("");

			// Read name of the cheat file
			TCHAR* szQuote = NULL;
			QuoteRead(&szQuote, NULL, s);

			_stprintf(szFilename, _T("cheats\\%s.dat"), szQuote);

			if (ConfigParseFile(szFilename)) {
				_stprintf(szFilename, _T("cheats\\%s.ini"), szQuote);
				if (ConfigParseFile(szFilename)) {
					CheatError(pszFilename, nLine, NULL, _T("included file doesn't exist"), szLine);
				}
			}

			continue;
		}

		if ((t = LabelCheck(s, _T("cheat"))) != 0) {				// Add new cheat
			s = t;

			// Read cheat name
			TCHAR* szQuote = NULL;
			TCHAR* szEnd = NULL;

			QuoteRead(&szQuote, &szEnd, s);

			s = szEnd;

			if ((t = LabelCheck(s, _T("advanced"))) != 0) {			// Advanced cheat
				s = t;
			}

			SKIP_WS(s);

			if (nInside == _T('{')) {
				CheatError(pszFilename, nLine, pCurrentCheat, _T("missing closing bracket"), NULL);
				break;
			}
#if 0
			if (*s != _T('\0') && *s != _T('{')) {
				CheatError(pszFilename, nLine, NULL, _T("malformed cheat declaration"), szLine);
				break;
			}
#endif
			nInside = *s;

			// Link new node into the list
			CheatInfo* pPreviousCheat = pCurrentCheat;
			pCurrentCheat = (CheatInfo*)malloc(sizeof(CheatInfo));
			if (pCheatInfo == NULL) {
				pCheatInfo = pCurrentCheat;
			}

			memset(pCurrentCheat, 0, sizeof(CheatInfo));
			pCurrentCheat->pPrevious = pPreviousCheat;
			if (pPreviousCheat) {
				pPreviousCheat->pNext = pCurrentCheat;
			}

			// Fill in defaults
			pCurrentCheat->nType = 0;								// Default to cheat type 0 (apply each frame)
			pCurrentCheat->nStatus = -1;							// Disable cheat

			memcpy(pCurrentCheat->szCheatName, szQuote, QUOTE_MAX);

			continue;
		}

		if ((t = LabelCheck(s, _T("type"))) != 0) {					// Cheat type
			if (nInside == INSIDE_NOTHING || pCurrentCheat == NULL) {
				CheatError(pszFilename, nLine, pCurrentCheat, _T("rogue cheat type"), szLine);
				break;
			}
			s = t;

			// Set type
			pCurrentCheat->nType = _tcstol(s, NULL, 0);

			continue;
		}

		if ((t = LabelCheck(s, _T("default"))) != 0) {				// Default option
			if (nInside == INSIDE_NOTHING || pCurrentCheat == NULL) {
				CheatError(pszFilename, nLine, pCurrentCheat, _T("rogue default"), szLine);
				break;
			}
			s = t;

			// Set default option
			pCurrentCheat->nDefault = _tcstol(s, NULL, 0);

			continue;
		}

		int n = _tcstol(s, &t, 0);
		if (t != s) {				   								// New option

			if (nInside == INSIDE_NOTHING || pCurrentCheat == NULL) {
				CheatError(pszFilename, nLine, pCurrentCheat, _T("rogue option"), szLine);
				break;
			}

			// Link a new Option structure to the cheat
			if (n < CHEAT_MAX_OPTIONS) {
				s = t;

				// Read option name
				TCHAR* szQuote = NULL;
				TCHAR* szEnd = NULL;
				if (QuoteRead(&szQuote, &szEnd, s)) {
					CheatError(pszFilename, nLine, pCurrentCheat, _T("option name omitted"), szLine);
					break;
				}
				s = szEnd;

				if (pCurrentCheat->pOption[n] == NULL) {
					pCurrentCheat->pOption[n] = (CheatOption*)malloc(sizeof(CheatOption));
				}
				memset(pCurrentCheat->pOption[n], 0, sizeof(CheatOption));

				memcpy(pCurrentCheat->pOption[n]->szOptionName, szQuote, QUOTE_MAX * sizeof(TCHAR));

				int nCurrentAddress = 0;
				bool bOK = true;
				while (nCurrentAddress < CHEAT_MAX_ADDRESS) {
					int nCPU = 0, nAddress = 0, nValue = 0;

					if (SkipComma(&s)) {
						nCPU = _tcstol(s, &t, 0);		// CPU number
						if (t == s) {
							CheatError(pszFilename, nLine, pCurrentCheat, _T("CPU number omitted"), szLine);
							bOK = false;
							break;
						}
						s = t;

						SkipComma(&s);
						nAddress = _tcstol(s, &t, 0);	// Address
						if (t == s) {
							bOK = false;
							CheatError(pszFilename, nLine, pCurrentCheat, _T("address omitted"), szLine);
							break;
						}
						s = t;

						SkipComma(&s);
						nValue = _tcstol(s, &t, 0);		// Value
						if (t == s) {
							bOK = false;
							CheatError(pszFilename, nLine, pCurrentCheat, _T("value omitted"), szLine);
							break;
						}
					} else {
						if (nCurrentAddress) {			// Only the first option is allowed no address
							break;
						}
						if (n) {
							bOK = false;
							CheatError(pszFilename, nLine, pCurrentCheat, _T("CPU / address / value omitted"), szLine);
							break;
						}
					}

					pCurrentCheat->pOption[n]->AddressInfo[nCurrentAddress].nCPU = nCPU;
					pCurrentCheat->pOption[n]->AddressInfo[nCurrentAddress].nAddress = nAddress;
					pCurrentCheat->pOption[n]->AddressInfo[nCurrentAddress].nValue = nValue;
					nCurrentAddress++;
				}

				if (!bOK) {
					break;
				}

			}

			continue;
		}

		SKIP_WS(s);
		if (*s == _T('}')) {
			if (nInside != _T('{')) {
				CheatError(pszFilename, nLine, pCurrentCheat, _T("missing opening bracket"), NULL);
				break;
			}

			nInside = INSIDE_NOTHING;
		}

		// Line isn't (part of) a valid cheat
#if 0
		if (*s) {
			CheatError(pszFilename, nLine, NULL, _T("rogue line"), szLine);
			break;
		}
#endif

	}

	if (h) {
		fclose(h);
	}

	return 0;
}

int ConfigCheatLoad()
{
	TCHAR szFilename[MAX_PATH] = _T("");

	_stprintf(szFilename, _T("cheats\\%s.dat"), BurnDrvGetText(DRV_NAME));
	if (ConfigParseFile(szFilename)) {
		_stprintf(szFilename, _T("cheats\\%s.ini"), BurnDrvGetText(DRV_NAME));
		if (ConfigParseFile(szFilename)) {
			return 1;
		}
	}

	if (pCheatInfo) {
		int nCurrentCheat = 0;
		while (CheatEnable(nCurrentCheat, -1) == 0) {
			nCurrentCheat++;
		}

		CheatUpdate();
	}

	return 0;
}


