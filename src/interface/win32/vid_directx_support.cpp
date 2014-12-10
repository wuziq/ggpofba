// Support functions for blitters that use DirectX
#include "burner.h"
#include "vid_directx_support.h"

// ---------------------------------------------------------------------------
// General

static IDirectDraw7* pDD = NULL;

void VidSExit()
{
	pDD = NULL;
}

int VidSInit(IDirectDraw7* pDD7)
{
	pDD = pDD7;

	if (pDD == NULL) {
		return 1;
	}

	return 0;
}

// ---------------------------------------------------------------------------

// Get bit-depth of a surface (15/16/24/32)

int VidSGetSurfaceDepth(IDirectDrawSurface7* pSurf)
{
	DDPIXELFORMAT ddpf;
	if (pSurf == NULL) {
		return 0;
	}

	// Find out the pixelformat of the screen surface
	memset(&ddpf, 0, sizeof(ddpf));
	ddpf.dwSize = sizeof(ddpf);

	if (SUCCEEDED(pSurf->GetPixelFormat(&ddpf))) {
		int nDepth = ddpf.dwRGBBitCount;
		if (nDepth == 16 && ddpf.dwGBitMask == 0x03E0) {
			nDepth = 15;
		}

		return nDepth;
	}

	return 0;
}

// Clear a surface to a specified colour

int VidSClearSurface(IDirectDrawSurface7* pSurf, unsigned int nColour, RECT* pRect)
{
	DDBLTFX BltFx;

	if (pSurf == NULL) {
		return 1;
	}

	memset(&BltFx, 0, sizeof(BltFx));
	BltFx.dwSize = sizeof(BltFx);
	BltFx.dwFillColor = nColour;

	if (FAILED(pSurf->Blt(NULL, NULL, pRect, DDBLT_COLORFILL, &BltFx))) {
		return 1;
	} else {
		return 0;
	}
}

// Clipper

int VidSClipperInit(IDirectDrawSurface7* pSurf)
{
	if (nVidFullscreen && bDrvOkay) {
		return 0;
	}

	IDirectDrawClipper *pClipper = NULL;

	if (SUCCEEDED(DirectDrawCreateClipper(0, &pClipper, NULL))) {
		if (SUCCEEDED(pClipper->SetHWnd(0, hVidWnd))) {
			pSurf->SetClipper(pClipper);
			RELEASE(pClipper);

			return 0;
		}
	}

	return 1;
}

// ---------------------------------------------------------------------------
// Gamma controls

static IDirectDrawGammaControl* pGammaControl;
static DDGAMMARAMP* pFBAGamma = NULL;
static DDGAMMARAMP* pSysGamma = NULL;

void VidSRestoreGamma()
{
	if (pGammaControl) {
		if (pSysGamma) {
			pGammaControl->SetGammaRamp(0, pSysGamma);
		}

		free(pSysGamma);
		pSysGamma = NULL;
		free(pFBAGamma);
		pFBAGamma = NULL;

		RELEASE(pGammaControl);
	}
}

int VidSUpdateGamma()
{
	if (pGammaControl) {
		if (bDoGamma) {
			for (int i = 0; i < 256; i++) {
				int nValue = (int)(65535.0 * pow((i / 255.0), nGamma));
				pFBAGamma->red[i] = nValue;
				pFBAGamma->green[i] = nValue;
				pFBAGamma->blue[i] = nValue;
			}
			pGammaControl->SetGammaRamp(0, pFBAGamma);
		} else {
			pGammaControl->SetGammaRamp(0, pSysGamma);
		}
	}

	return 0;
}

int VidSSetupGamma(IDirectDrawSurface7* pSurf)
{
	pGammaControl = NULL;

	if (!bVidUseHardwareGamma || !nVidFullscreen) {
		return 0;
	}

	if (FAILED(pSurf->QueryInterface(IID_IDirectDrawGammaControl, (void**)&pGammaControl))) {
		pGammaControl = NULL;
#ifdef PRINT_DEBUG_INFO
		dprintf(_T("  * Warning: Couldn't use hardware gamma controls.\n"));
#endif

		return 1;
	}

	pSysGamma = (DDGAMMARAMP*)malloc(sizeof(DDGAMMARAMP));
	if (pSysGamma == NULL) {
		VidSRestoreGamma();
		return 1;
	}
	pGammaControl->GetGammaRamp(0, pSysGamma);

	pFBAGamma = (DDGAMMARAMP*)malloc(sizeof(DDGAMMARAMP));
	if (pFBAGamma == NULL) {
		VidSRestoreGamma();
		return 1;
	}

	VidSUpdateGamma();

	return 0;
}

// ---------------------------------------------------------------------------
// Fullscreen mode support routines

int VidSScoreDisplayMode(VidSDisplayScoreInfo* pScoreInfo)
{
	// Continue if the resolution is too low
	if (pScoreInfo->nModeWidth < pScoreInfo->nRequestedWidth || pScoreInfo->nModeHeight < pScoreInfo->nRequestedHeight) {
		return 0;
	}

	// Only test standard resolutions if below 512 x 384
	if ((pScoreInfo->nModeWidth == 320 && pScoreInfo->nModeHeight == 240) || (pScoreInfo->nModeWidth == 400 && pScoreInfo->nModeHeight == 300) || (pScoreInfo->nModeWidth >= 512 && pScoreInfo->nModeHeight >= 384)) {

		if (pScoreInfo->nRequestedWidth == 0 || pScoreInfo->nRequestedHeight == 0) {
			RECT rect = {0, 0, 0, 0};
			int nGameWidth = nVidImageWidth, nGameHeight = nVidImageHeight;
			unsigned int nScore;

			if (bDrvOkay) {
				if ((BurnDrvGetFlags() & BDF_ORIENTATION_VERTICAL) && (nVidRotationAdjust & 1)) {
					BurnDrvGetVisibleSize(&nGameHeight, &nGameWidth);
				} else {
					BurnDrvGetVisibleSize(&nGameWidth, &nGameHeight);
				}
			}

			nVidScrnWidth = rect.right = pScoreInfo->nModeWidth;
			nVidScrnHeight = rect.bottom = pScoreInfo->nModeHeight;
			VidImageSize(&rect, nGameWidth, nGameHeight);

			// Continue if the resolution is too low
			if (!bDrvOkay) {
				if ((unsigned int)(rect.bottom - rect.top) < pScoreInfo->nRequestedHeight) {
					return 0;
				}
			} else {
				if (BurnDrvGetFlags() & BDF_ORIENTATION_VERTICAL) {
					if ((unsigned int)(rect.right - rect.left) < pScoreInfo->nRequestedWidth) {
						return 0;
					}
				} else {
					if ((unsigned int)(rect.bottom - rect.top) < pScoreInfo->nRequestedHeight) {
						return 0;
					}
				}
			}

			// Score resolutions based on how many pixels are unused and the pixel aspect
			nScore = 65536 * (pScoreInfo->nModeWidth - (unsigned)(rect.right - rect.left)) + (pScoreInfo->nModeHeight - (unsigned)(rect.bottom - rect.top));
			nScore = (int)((double)nScore * ((double)pScoreInfo->nModeWidth * nVidScrnAspectY / pScoreInfo->nModeHeight / nVidScrnAspectX));
			if (nScore < pScoreInfo->nBestScore) {
				pScoreInfo->nBestScore = nScore;
				pScoreInfo->nBestWidth = pScoreInfo->nModeWidth;
				pScoreInfo->nBestHeight = pScoreInfo->nModeHeight;
			}
		} else {
			// Select the lowest resolution that will fit the image
			if (pScoreInfo->nModeWidth < pScoreInfo->nBestWidth && pScoreInfo->nModeHeight < pScoreInfo->nBestHeight) {
				pScoreInfo->nBestWidth = pScoreInfo->nModeWidth;
				pScoreInfo->nBestHeight = pScoreInfo->nModeHeight;
			}
		}
	}

	return 0;
}

int VidSInitScoreInfo(VidSDisplayScoreInfo* pScoreInfo)
{
	int nGameWidth = nVidImageWidth, nGameHeight = nVidImageHeight;
	int nGameAspectX = 4, nGameAspectY = 3;

	pScoreInfo->nBestWidth = -1U;
	pScoreInfo->nBestHeight = -1U;
	pScoreInfo->nBestScore = -1U;

	if (pScoreInfo->nRequestedZoom == 0) {
		return 0;
	}

	pScoreInfo->nRequestedWidth = 0;
	pScoreInfo->nRequestedHeight = 0;

	if (bDrvOkay) {
		if ((BurnDrvGetFlags() & BDF_ORIENTATION_VERTICAL) && (nVidRotationAdjust & 1)) {
			BurnDrvGetVisibleSize(&nGameHeight, &nGameWidth);
			BurnDrvGetAspect(&nGameAspectY, &nGameAspectX);
		} else {
			BurnDrvGetVisibleSize(&nGameWidth, &nGameHeight);
			BurnDrvGetAspect(&nGameAspectX, &nGameAspectY);
		}
	}

	if (!bVidCorrectAspect || bVidFullStretch || (nVidSelect == 1 && (nVidBlitterOpt[1] & 0x07000000) == 0x07000000) || (nVidSelect == 2 && nVidBlitterOpt[2] & 0x00000100)) {
		pScoreInfo->nRequestedWidth = nGameWidth * pScoreInfo->nRequestedZoom;
		pScoreInfo->nRequestedHeight = nGameHeight * pScoreInfo->nRequestedZoom;
	} else {
		if (bDrvOkay) {
			if (BurnDrvGetFlags() & BDF_ORIENTATION_VERTICAL) {
				pScoreInfo->nRequestedWidth = nGameWidth * pScoreInfo->nRequestedZoom;
			} else {
				pScoreInfo->nRequestedHeight = nGameHeight * pScoreInfo->nRequestedZoom;
			}
		}
	}

	return 0;
}

static HRESULT WINAPI myEnumModesCallback(LPDDSURFACEDESC2 pSurfaceDesc, void* lpContext)
{
	((VidSDisplayScoreInfo*)lpContext)->nModeWidth = pSurfaceDesc->dwWidth;
	((VidSDisplayScoreInfo*)lpContext)->nModeHeight = pSurfaceDesc->dwHeight;

	VidSScoreDisplayMode((VidSDisplayScoreInfo*)lpContext);

	return DDENUMRET_OK;
}

void VidSRestoreScreenMode()
{
	if (pDD == NULL) {
		return;
	}

	// Undo the changes we made to the display
	pDD->SetCooperativeLevel(NULL, DDSCL_NORMAL);

	nVidScrnWidth = 0;
	nVidScrnHeight = 0;

	return;
}

// Enter fullscreen mode, select optimal full-screen resolution
int VidSEnterFullscreenMode(int nZoom, int nDepth)
{
	int nWidth, nHeight;

	if (pDD == NULL) {
		return 1;
	}

	if (nDepth == 0) {
		nDepth = nVidDepth;
	}
	if (nDepth == 15) {
		nDepth = 16;
	}

	if (FAILED(pDD->SetCooperativeLevel(hVidWnd, DDSCL_ALLOWREBOOT | DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN))) {
		return 1;
	}

	if (bVidArcaderes) {
		if (!VidSGetArcaderes(&nWidth, &nHeight)) {
			return 1;
		}
	} else {
		if (nZoom) {
			DDSURFACEDESC2 ddsd;
			VidSDisplayScoreInfo ScoreInfo;

			memset(&ScoreInfo, 0, sizeof(VidSDisplayScoreInfo));
			ScoreInfo.nRequestedZoom = nZoom;
			VidSInitScoreInfo(&ScoreInfo);

			memset(&ddsd, 0, sizeof(ddsd));
			ddsd.dwSize = sizeof(ddsd);
			ddsd.dwFlags = DDSD_PIXELFORMAT;

			ddsd.ddpfPixelFormat.dwFlags = DDPF_RGB;
			ddsd.ddpfPixelFormat.dwRGBBitCount = nDepth;

			pDD->EnumDisplayModes(0, &ddsd, (void*)&ScoreInfo, myEnumModesCallback);

			if (ScoreInfo.nBestWidth == -1U) {

				VidSRestoreScreenMode();

				FBAPopupAddText(PUF_TEXT_DEFAULT, MAKEINTRESOURCE(IDS_ERR_UI_FULL_NOMODE));
				FBAPopupDisplay(PUF_TYPE_ERROR);

				return 1;
			}

			nWidth = ScoreInfo.nBestWidth;
			nHeight = ScoreInfo.nBestHeight;
		} else {
			nWidth = nVidWidth;
			nHeight = nVidHeight;
		}
	}

	if (!bDrvOkay && (nWidth < 640 || nHeight < 480)) {
		return 1;
	}

	if (FAILED(pDD->SetDisplayMode(nWidth, nHeight, nDepth, nVidRefresh, 0))) {
		VidSRestoreScreenMode();

		FBAPopupAddText(PUF_TEXT_DEFAULT, MAKEINTRESOURCE(IDS_ERR_UI_FULL_PROBLEM));
		if (bVidArcaderes && (nWidth != 320 && nHeight != 240)) {
			FBAPopupAddText(PUF_TEXT_DEFAULT, MAKEINTRESOURCE(IDS_ERR_UI_FULL_CUSTRES));
		}
		FBAPopupDisplay(PUF_TYPE_ERROR);

		nVidScrnWidth = 0;
		nVidScrnHeight = 0;

		return 1;
	}

	nVidScrnWidth = nWidth;
	nVidScrnHeight = nHeight;

	return 0;
}

// ---------------------------------------------------------------------------

// Compute the resolution needed to run a game without scaling and filling the screen
// (taking into account the aspect ratios of the game and monitor)
bool VidSGetArcaderes(int* pWidth, int* pHeight)
{
	int nGameWidth, nGameHeight;
	int nGameAspectX, nGameAspectY;

	if (bDrvOkay) {
		if ((BurnDrvGetFlags() & BDF_ORIENTATION_VERTICAL) && (nVidRotationAdjust & 1)) {
			BurnDrvGetVisibleSize(&nGameHeight, &nGameWidth);
			BurnDrvGetAspect(&nGameAspectY, &nGameAspectX);
		} else {
			BurnDrvGetVisibleSize(&nGameWidth, &nGameHeight);
			BurnDrvGetAspect(&nGameAspectX, &nGameAspectY);
		}

		double dMonAspect = (double)nVidScrnAspectX / nVidScrnAspectY;
		double dGameAspect = (double)nGameAspectX / nGameAspectY;

		if (dMonAspect > dGameAspect) {
			*pWidth = nGameHeight * nGameAspectY * nGameWidth * nVidScrnAspectX / (nGameHeight * nGameAspectX * nVidScrnAspectY);
			*pHeight = nGameHeight;
		} else {
			*pWidth = nGameWidth;
			*pHeight = nGameWidth * nGameAspectX * nGameHeight * nVidScrnAspectY / (nGameWidth * nGameAspectY * nVidScrnAspectX);
		}

		// Horizontal resolution must be a multiple of 8
		if (*pWidth - nGameWidth < 8) {
			*pWidth = (*pWidth + 7) & ~7;
		} else {
			*pWidth = (*pWidth + 4) & ~7;
		}
	} else {
		return false;
	}

	return true;
}

// This function takes a rectangle and scales it to either:
// - The largest possible multiple of both X and Y;
// - The largest possible multiple of Y, modifying X to ensure the correct aspect ratio;
// - The window size
int VidSScaleImage(RECT* pRect, int nGameWidth, int nGameHeight, bool bVertScanlines)
{
	int xm, ym;											// The multiple of nScrnWidth and nScrnHeight we can fit in
	int nScrnWidth, nScrnHeight;

	int nGameAspectX = 4, nGameAspectY = 3;
	int nWidth = pRect->right - pRect->left;
	int nHeight = pRect->bottom - pRect->top;

	if (bVidFullStretch) {								// Arbitrary stretch
		return 0;
	}

	if (bDrvOkay) {
		if ((BurnDrvGetFlags() & (BDF_ORIENTATION_VERTICAL | BDF_ORIENTATION_FLIPPED)) && (nVidRotationAdjust & 1)) {
			BurnDrvGetAspect(&nGameAspectY, &nGameAspectX);
		} else {
			BurnDrvGetAspect(&nGameAspectX, &nGameAspectY);
		}
	}

	xm = nWidth / nGameWidth;
	ym = nHeight / nGameHeight;

	if (nVidFullscreen) {
		nScrnWidth = nVidScrnWidth;
		nScrnHeight = nVidScrnHeight;
   } else if (nVidEmbeddedWindow) {
      /* Assume square pixels */
      nScrnWidth = nGameAspectX;
      nScrnHeight = nGameAspectY;
   } else {
		nScrnWidth = SystemWorkArea.right - SystemWorkArea.left;
		nScrnHeight = SystemWorkArea.bottom - SystemWorkArea.top;
	}

	if (bVidCorrectAspect && bVidScanlines && ((ym >= 2 && xm) || (ym && xm >= 2 && bVertScanlines))) {	// Correct aspect ratio with scanlines
		int nWidthScratch, nHeightScratch;
		if (nGameWidth < nGameHeight && bVertScanlines) {
			int xmScratch = xm;
			do {
				nWidthScratch = nGameWidth * xmScratch;
				nHeightScratch = nWidthScratch * nVidScrnAspectX * nGameAspectY * nScrnHeight / (nScrnWidth * nVidScrnAspectY * nGameAspectX);
				xmScratch--;
			} while (nHeightScratch > nHeight && xmScratch >= 2);
			if (nHeightScratch > nHeight) {				// The image is too high
				if (nGameWidth < nGameHeight) {			// Vertical games
					nWidth = nHeight * nVidScrnAspectX * nGameAspectX * nScrnHeight / (nScrnWidth * nVidScrnAspectY * nGameAspectY);
				} else {								// Horizontal games
					nWidth = nHeight * nVidScrnAspectY * nGameAspectX * nScrnWidth / (nScrnHeight * nVidScrnAspectX * nGameAspectY);
				}
			} else {
				nWidth = nWidthScratch;
				nHeight = nHeightScratch;
			}
		} else {
			int ymScratch = ym;
			do {
				nHeightScratch = nGameHeight * ymScratch;
				nWidthScratch = nHeightScratch * nVidScrnAspectY * nGameAspectX * nScrnWidth / (nScrnHeight * nVidScrnAspectX * nGameAspectY);
				ymScratch--;
			} while (nWidthScratch > nWidth && ymScratch >= 2);
			if (nWidthScratch > nWidth) {				// The image is too wide
				if (nGameWidth < nGameHeight) {			// Vertical games
					nHeight = nWidth * nVidScrnAspectY * nGameAspectY * nScrnWidth / (nScrnHeight * nVidScrnAspectX * nGameAspectX);
				} else {								// Horizontal games
					nHeight = nWidth * nVidScrnAspectX * nGameAspectY * nScrnHeight / (nScrnWidth * nVidScrnAspectY * nGameAspectX);
				}
			} else {
				nWidth = nWidthScratch;
				nHeight = nHeightScratch;
			}
		}
	} else {
		if (bVidCorrectAspect) {					// Correct aspect ratio
			int nWidthScratch;
			nWidthScratch = nHeight * nVidScrnAspectY * nGameAspectX * nScrnWidth / (nScrnHeight * nVidScrnAspectX * nGameAspectY);
			if (nWidthScratch > nWidth) {			// The image is too wide
				if (nGameWidth < nGameHeight) {		// Vertical games
					nHeight = nWidth * nVidScrnAspectY * nGameAspectY * nScrnWidth / (nScrnHeight * nVidScrnAspectX * nGameAspectX);
				} else {							// Horizontal games
					nHeight = nWidth * nVidScrnAspectX * nGameAspectY * nScrnHeight / (nScrnWidth * nVidScrnAspectY * nGameAspectX);
				}
			} else {
				nWidth = nWidthScratch;
			}
		} else {
			if (xm && ym) {							// Don't correct aspect ratio
				if (xm > ym) {
					xm = ym;
				} else {
					ym = xm;
				}
				nWidth = nGameWidth * xm;
				nHeight = nGameHeight * ym;
			} else {
				if (xm) {
					nWidth = nGameWidth * xm * nHeight / nGameHeight;
				} else {
					if (ym) {
						nHeight = nGameHeight * ym * nWidth / nGameWidth;
					}
				}
			}
		}
	}

	pRect->left = (pRect->right + pRect->left) / 2;
	pRect->left -= nWidth / 2;
	pRect->right = pRect->left + nWidth;

	pRect->top = (pRect->top + pRect->bottom) / 2;
	pRect->top -= nHeight / 2;
	pRect->bottom = pRect->top + nHeight;

	return 0;
}

// ---------------------------------------------------------------------------
// Text display routines

static struct { TCHAR pMsgText[32]; COLORREF nColour; int nPriority; unsigned int nTimer; } VidSShortMsg = { _T(""), 0, 0, 0,};
static HFONT ShortMsgFont = NULL;

static unsigned char nStatusSymbols[4] = {0x3B, 0xC2, 0x3D, 0x34};
static HFONT StatusFont = NULL;

#define CHAT_SIZE 4

static struct { TCHAR* pIDText; COLORREF nIDColour; TCHAR* pMainText; COLORREF nMainColour; } VidSChatMessage[CHAT_SIZE * 2];
static bool bChatInitialised = false;

static HFONT ChatIDFont = NULL;
static HFONT ChatMainFont = NULL;
static unsigned int nChatTimer;
static int nChatFontSize;
static int nChatShadowOffset;
static int nChatOverFlow;

static bool	bDrawChat;
static bool bDrawTV = false;
static TCHAR szSpectatorCount[256] = { 0 };
static TCHAR szMatchInfo[256] = { 0 };
static TCHAR szConnectStatus[256] = { 0 };
static HBITMAP hGGPOLogo = NULL;
static HDC hGGPODC = NULL;
static bool bShowGGPOLogo = false;
static TCHAR connectStatus[256] = { 0 };

static HFONT EditTextFont = NULL;
static HFONT EditCursorFont = NULL;
static DWORD nPrevStart, nPrevEnd;
static int nCursorTime;
static int nCursorState = 0;
static int nEditSize;
static int nEditShadowOffset;

static IDirectDrawSurface7* pShortMsgSurf = NULL;
static IDirectDrawSurface7* pStatusSurf = NULL;
static IDirectDrawSurface7* pChatSurf = NULL;
static IDirectDrawSurface7* pTVSurf = NULL;
static IDirectDrawSurface7* pEditSurf = NULL;
static unsigned int nKeyColour = 0x00FF00;

static int nStatus = 0;
static int nPrevStatus = -1;

int nVidSDisplayStatus = 1;								// 1 = display pause/record/replay/kaillera icons in the upper right corner of the display

int nMaxChatFontSize = 36;								// Maximum size of the font used for the Kaillera chat function (1280x960 or higher)
int nMinChatFontSize = 12;								// Minimum size of the font used for the Kaillera chat function (arcade resolution)

static int nZoom;										// & 1: zoom X, & 2: zoom Y

static int nShortMsgFlags;
static int nStatusFlags;

bool bEditActive = false;
bool bEditTextChanged = false;
TCHAR EditText[MAX_CHAT_SIZE + 1] = _T("");

static BOOL MyTextOut(HDC hdc, int nXStart, int nYStart, LPCTSTR lpString, int cbString, int nShadowOffset, int nColour)
{
	// Print a black shadow
	SetTextColor(hdc, RGB(10, 10, 10));
	if (nShadowOffset >= 2) {
		TextOut(hdc, nXStart + nShadowOffset, nYStart + nShadowOffset, lpString, cbString);
	}
	// Print a black outline
	TextOut(hdc, nXStart - 1, nYStart - 1, lpString, cbString);
	TextOut(hdc, nXStart + 0, nYStart - 1, lpString, cbString);
	TextOut(hdc, nXStart + 1, nYStart - 1, lpString, cbString);
	TextOut(hdc, nXStart + 1, nYStart + 0, lpString, cbString);
	TextOut(hdc, nXStart + 1, nYStart + 1, lpString, cbString);
	TextOut(hdc, nXStart + 0, nYStart + 1, lpString, cbString);
	TextOut(hdc, nXStart - 1, nYStart + 1, lpString, cbString);
	TextOut(hdc, nXStart - 1, nYStart + 0, lpString, cbString);
	// Print the text on top
	SetTextColor(hdc, nColour);

	return TextOut(hdc, nXStart, nYStart, lpString, cbString);
}

static BOOL MyExtTextOut(HDC hdc, int X, int Y, UINT fuOptions, CONST RECT* lprc, LPCTSTR lpString, UINT cbCount, CONST INT* lpDx, int nShadowOffset, int nColour)
{
	// Print a black shadow
	SetTextColor(hdc, RGB(10, 10, 10));
	if (nShadowOffset >= 2) {
		ExtTextOut(hdc, X + nShadowOffset, Y + nShadowOffset, fuOptions, lprc, lpString, cbCount, lpDx);
	}
	// Print a black outline
	ExtTextOut(hdc, X - 1, Y - 1, fuOptions, lprc, lpString, cbCount, lpDx);
	ExtTextOut(hdc, X + 0, Y - 1, fuOptions, lprc, lpString, cbCount, lpDx);
	ExtTextOut(hdc, X + 1, Y - 1, fuOptions, lprc, lpString, cbCount, lpDx);
	ExtTextOut(hdc, X + 1, Y + 0, fuOptions, lprc, lpString, cbCount, lpDx);
	ExtTextOut(hdc, X + 1, Y + 1, fuOptions, lprc, lpString, cbCount, lpDx);
	ExtTextOut(hdc, X + 0, Y + 1, fuOptions, lprc, lpString, cbCount, lpDx);
	ExtTextOut(hdc, X - 1, Y + 1, fuOptions, lprc, lpString, cbCount, lpDx);
	ExtTextOut(hdc, X - 1, Y + 0, fuOptions, lprc, lpString, cbCount, lpDx);
	// Print the text on top
	SetTextColor(hdc, nColour);

	return ExtTextOut(hdc, X, Y, fuOptions, lprc, lpString, cbCount, lpDx);
}

static void VidSExitShortMsg()
{
	VidSShortMsg.nTimer = 0;

	if (ShortMsgFont) {
		DeleteObject(ShortMsgFont);
		ShortMsgFont = NULL;
	}

	RELEASE(pShortMsgSurf);
}

static void VidSExitStatus()
{
	if (StatusFont) {
		DeleteObject(StatusFont);
		StatusFont = NULL;
	}

	RELEASE(pStatusSurf);
}

void VidSExitChat()
{
	nChatTimer = 0;

	if (ChatIDFont) {
		DeleteObject(ChatIDFont);
		ChatIDFont = NULL;
	}
	if (ChatMainFont) {
		DeleteObject(ChatMainFont);
		ChatMainFont = NULL;
	}

	for (int i = 0; i < CHAT_SIZE; i++) {
		free(VidSChatMessage[i].pIDText);
		VidSChatMessage[i].pIDText = NULL;
		free(VidSChatMessage[i].pMainText);
		VidSChatMessage[i].pMainText = NULL;
	}

	RELEASE(pChatSurf);
}

void VidSExitTV()
{
   RELEASE(pTVSurf);
}


static void VidSExitEdit()
{
	bEditActive = false;

	if (EditTextFont) {
		DeleteObject(EditTextFont);
		EditTextFont = NULL;
	}
	if (EditCursorFont) {
		DeleteObject(EditCursorFont);
		EditCursorFont = NULL;
	}

	RELEASE(pEditSurf);
}

void VidSExitOSD()
{
	if (NetworkGame()) {
		VidSExitEdit();
		VidSExitChat();
		VidSExitTV();
	}
	VidSExitShortMsg();
	VidSExitStatus();
}

static int VidSInitShortMsg(int nFlags)
{
	DDSURFACEDESC2 ddsd;

	VidSExitShortMsg();

	nShortMsgFlags = nFlags;

	ShortMsgFont = CreateFont(30, 0, 0, 0, FW_DEMIBOLD, 0, 0, 0, 0, 0, 0, ANTIALIASED_QUALITY, FF_SWISS, _T("Lucida"));
	VidSShortMsg.nTimer = 0;

	// create surface to display the text
	memset(&ddsd, 0, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_CKSRCBLT;

	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY;

	ddsd.dwWidth = 192;
	ddsd.dwHeight = 32;

	ddsd.ddckCKSrcBlt.dwColorSpaceLowValue = nKeyColour;
	ddsd.ddckCKSrcBlt.dwColorSpaceHighValue = nKeyColour;

	if (FAILED(pDD->CreateSurface(&ddsd, &pShortMsgSurf, NULL))) {
#ifdef PRINT_DEBUG_INFO
		dprintf(_T("  * Error: Couldn't create OSD texture.\n"));
#endif
		return 1;
	}

	VidSClearSurface(pShortMsgSurf, nKeyColour, NULL);

	return 0;
}

static int VidSInitStatus(int nFlags)
{
	DDSURFACEDESC2 ddsd;

	VidSExitStatus();

	nStatusFlags = nFlags;

	StatusFont = CreateFont(48, 0, 0, 0, FW_DEMIBOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, ANTIALIASED_QUALITY, FF_SWISS, _T("Webdings"));
	nPrevStatus = -1;

	// create surface to display the text
	memset(&ddsd, 0, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_CKSRCBLT;

	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY;

	ddsd.dwWidth = 192;
	ddsd.dwHeight = 50;

	ddsd.ddckCKSrcBlt.dwColorSpaceLowValue = nKeyColour;
	ddsd.ddckCKSrcBlt.dwColorSpaceHighValue = nKeyColour;

	if (FAILED(pDD->CreateSurface(&ddsd, &pStatusSurf, NULL))) {
#ifdef PRINT_DEBUG_INFO
		dprintf(_T("  * Error: Couldn't create OSD texture.\n"));
#endif
		return 1;
	}

	VidSClearSurface(pStatusSurf, nKeyColour, NULL);

	return 0;
}

static int VidSInitChat(int nFlags)
{
	DDSURFACEDESC2 ddsd;

	if (bChatInitialised) {
		VidSExitChat();
	} else {
		for (int i = 0; i < CHAT_SIZE + (CHAT_SIZE >> 1); i++) {
			VidSChatMessage[i].pIDText = NULL;
			VidSChatMessage[i].pMainText = NULL;
		}
		bChatInitialised = true;
	}

	nChatFontSize = nMaxChatFontSize - ((nMaxChatFontSize - nMinChatFontSize) * nFlags) / 4;

	ChatIDFont = CreateFont(nChatFontSize, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, ANTIALIASED_QUALITY, FF_SWISS, _T("Lucida"));
	if (nChatFontSize > 20) {
		ChatMainFont = CreateFont(nChatFontSize, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, ANTIALIASED_QUALITY, FF_SWISS, _T("Lucida"));
	} else {
		ChatMainFont = CreateFont(nChatFontSize, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, ANTIALIASED_QUALITY, FF_SWISS, _T("Lucida"));
	}

	nChatShadowOffset = (nChatFontSize / 16) + 1;
	nChatOverFlow = 0;
	bDrawChat = false;

	// create surface to display the text
	memset(&ddsd, 0, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_CKSRCBLT;

	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY;

	if (nVidFullscreen) {
		RECT rect;
		GetClientScreenRect(hScrnWnd, &rect);
		ddsd.dwWidth = rect.right - rect.left;
	} else {
		extern RECT SystemWorkArea;
		ddsd.dwWidth = SystemWorkArea.right - SystemWorkArea.left;
	}
	ddsd.dwHeight = nChatFontSize * (CHAT_SIZE + (CHAT_SIZE >> 1));

	ddsd.ddckCKSrcBlt.dwColorSpaceLowValue = nKeyColour;
	ddsd.ddckCKSrcBlt.dwColorSpaceHighValue = nKeyColour;

	if (FAILED(pDD->CreateSurface(&ddsd, &pChatSurf, NULL))) {
#ifdef PRINT_DEBUG_INFO
		dprintf(_T("  * Error: Couldn't create Chat texture.\n"));
#endif
		return 1;
	}

	VidSClearSurface(pChatSurf, nKeyColour, NULL);

	bDrawChat = true;

	return 0;
}

static int VidSInitTV(int nFlags)
{
	DDSURFACEDESC2 ddsd;

   VidSExitTV();

	// create surface to display the text
	memset(&ddsd, 0, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_CKSRCBLT;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY;
	if (nVidFullscreen) {
		RECT rect;
		GetClientScreenRect(hScrnWnd, &rect);
		ddsd.dwWidth = rect.right - rect.left;
   	ddsd.dwHeight = rect.bottom - rect.top;
	} else {
		extern RECT SystemWorkArea;
		ddsd.dwWidth = SystemWorkArea.right - SystemWorkArea.left;
   	ddsd.dwHeight = SystemWorkArea.bottom - SystemWorkArea.top;
	}

	ddsd.ddckCKSrcBlt.dwColorSpaceLowValue = nKeyColour;
	ddsd.ddckCKSrcBlt.dwColorSpaceHighValue = nKeyColour;

	if (FAILED(pDD->CreateSurface(&ddsd, &pTVSurf, NULL))) {
#ifdef PRINT_DEBUG_INFO
		dprintf(_T("  * Error: Couldn't create TV texture.\n"));
#endif
		return 1;
	}
   DDCOLORKEY		ck = { 0 };
   ck.dwColorSpaceLowValue = nKeyColour;
   ck.dwColorSpaceHighValue = nKeyColour;
   pTVSurf->SetColorKey(DDCKEY_SRCBLT, &ck);
	VidSClearSurface(pTVSurf, nKeyColour, NULL);

   if (!hGGPOLogo) {
   	hGGPOLogo = (HBITMAP)LoadImage(hAppInst, _T("BMP_GGPO"), IMAGE_BITMAP, 0, 0, 0);
   }
   if (!hGGPODC) {
      HDC hdc = GetDC(NULL);
      hGGPODC = CreateCompatibleDC(NULL);
      SelectObject(hGGPODC, hGGPOLogo);
      ReleaseDC(NULL, hdc);
   }

   bDrawTV = true;
	return 0;
}

static int VidSInitEdit(int nFlags)
{
	DDSURFACEDESC2 ddsd;

	VidSExitEdit();

	nEditSize = nMaxChatFontSize + 8 - ((nMaxChatFontSize - nMinChatFontSize) * nFlags) / 4;

	EditTextFont = CreateFont(nEditSize - 8, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, ANTIALIASED_QUALITY, FF_SWISS, _T("Lucida"));
	EditCursorFont = CreateFont(nEditSize - 8, 0, 0, 0, FW_BOLD, 0, TRUE, 0, 0, 0, 0, ANTIALIASED_QUALITY, FF_SWISS, _T("Lucida"));

	nEditShadowOffset = ((nEditSize - 8) / 16) + 1;

	// create surface to display the text
	memset(&ddsd, 0, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_CKSRCBLT;

	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY;

	if (nVidFullscreen) {
		RECT rect;
		GetClientScreenRect(hScrnWnd, &rect);
		ddsd.dwWidth = rect.right - rect.left;
	} else {
		extern RECT SystemWorkArea;
		ddsd.dwWidth = SystemWorkArea.right - SystemWorkArea.left;
	}
	ddsd.dwHeight = nEditSize;

	ddsd.ddckCKSrcBlt.dwColorSpaceLowValue = nKeyColour;
	ddsd.ddckCKSrcBlt.dwColorSpaceHighValue = nKeyColour;

	if (FAILED(pDD->CreateSurface(&ddsd, &pEditSurf, NULL))) {
#ifdef PRINT_DEBUG_INFO
		dprintf(_T("  * Error: Couldn't create OSD texture.\n"));
#endif
		return 1;
	}

	VidSClearSurface(pEditSurf, nKeyColour, NULL);

	return 0;
}

int VidSInitOSD(int nFlags)
{
#ifdef PRINT_DEBUG_INFO
//	dprintf(_T(" ** OSD initialised.\n"));
#endif

	if (pDD == NULL) {
		return 1;
	}

	if (VidSInitStatus(nFlags)) {
		return 1;
	}
	if (VidSInitShortMsg(nFlags)) {
		return 1;
	}
	if (NetworkGame()) {
		if (VidSInitChat(nFlags)) {
			return 1;
		}
		if (VidSInitEdit(nFlags)) {
			return 1;
		}
      if (VidSInitTV(nFlags)) {
         return 1;
      }
	}

	return 0;
}

int VidSRestoreOSD()
{
	if (pShortMsgSurf) {
		if (FAILED(pShortMsgSurf->IsLost())) {
			if (FAILED(pShortMsgSurf->Restore())) {
				return 1;
			}
			VidSClearSurface(pShortMsgSurf, nKeyColour, NULL);

			VidSShortMsg.nTimer = 0;
		}
	}

	if (pStatusSurf) {
		if (FAILED(pStatusSurf->IsLost())) {
			if (FAILED(pStatusSurf->Restore())) {
				return 1;
			}
			VidSClearSurface(pStatusSurf, nKeyColour, NULL);

			nPrevStatus = -1;
		}
	}

	if (NetworkGame()) {
		if (pChatSurf) {
			if (FAILED(pChatSurf->IsLost())) {
				if (FAILED(pChatSurf->Restore())) {
					return 1;
				}
				VidSClearSurface(pChatSurf, nKeyColour, NULL);
			}
		}

      if (pTVSurf) {
			if (FAILED(pTVSurf->IsLost())) {
				if (FAILED(pTVSurf->Restore())) {
					return 1;
				}
				VidSClearSurface(pTVSurf, nKeyColour, NULL);
			}
		}

		if (pEditSurf) {
			if (FAILED(pEditSurf->IsLost())) {
				if (FAILED(pEditSurf->Restore())) {
					return 1;
				}
				VidSClearSurface(pEditSurf, nKeyColour, NULL);
			}
		}
	}

	return 0;
}

static void VidSDisplayShortMsg(IDirectDrawSurface7* pSurf, RECT* pRect)
{
	if (VidSShortMsg.nTimer) {
		RECT src = { 0, 0, 192, 32 };
		RECT dest = { 0, pRect->top + 4, pRect->right - 8, pRect->top + 36 };

		// Switch off message display when the message has been displayed long enough
		if (nFramesEmulated > VidSShortMsg.nTimer) {
			VidSShortMsg.nTimer = 0;
		}

		if (nStatus) {
			for (int x = 0; x < 4; x++) {
				if (nStatus & (1 << x)) {
					dest.right -= 48;
				}
			}

			dest.top += 10;
			dest.bottom += 10;
		}

        dest.left = dest.right - 192;
		if (dest.left < pRect->left) {
			src.left = pRect->left - dest.left;
			dest.left = pRect->left;
		}

		if (nZoom & 2) {
			dest.top <<= 1;
			dest.bottom <<= 1;
		}

		if (nZoom & 1) {
			dest.left <<= 1;
			dest.right <<= 1;
		}

		// Blit the message to the surface using a colourkey
		pSurf->Blt(&dest, pShortMsgSurf, &src, DDBLT_ASYNC | DDBLT_KEYSRC, NULL);
	}
}

static void VidSDisplayStatus(IDirectDrawSurface7* pSurf, RECT* pRect)
{
	nStatus = 0;

	if (nVidSDisplayStatus == 0) {
		return;
	}

	if (bRunPause) {
		nStatus |= 1;
	}
	if (kNetGame) {
		nStatus |= 2;
	}
	if (nReplayStatus == 1) {
		nStatus |= 4;
	}
	if (nReplayStatus == 2) {
		nStatus |= 8;
	}

	if (nStatus != nPrevStatus) {
		nPrevStatus = nStatus;
		if (nStatus) {
			// Print the message
			HDC hDC;
			HFONT hFont;
			TCHAR szStatus[8];

			// Clear the surface first
			VidSClearSurface(pStatusSurf, nKeyColour, NULL);

			// Make the status string
			memset(szStatus, 0, sizeof(szStatus));
			for (int i = 0, j = 0; i < 4; i++) {
				if (nStatus & (1 << i)) {
					szStatus[j] = nStatusSymbols[i];
					j++;
				}
			}

			pStatusSurf->GetDC(&hDC);
			SetBkMode(hDC, TRANSPARENT);
			hFont = (HFONT)SelectObject(hDC, StatusFont);
			SetTextAlign(hDC, TA_TOP | TA_RIGHT);

			MyTextOut(hDC, 192 - 2, 0, szStatus, _tcslen(szStatus), 2, RGB(0xFF, 0x3F, 0x3F));

			// Clean up
			SelectObject(hDC, hFont);
			pStatusSurf->ReleaseDC(hDC);
		}
	}

	if (nStatus) {
		RECT src = { 192, 0, 192, 48 };
		RECT dest = { 0, pRect->top + 4, pRect->right - 4, pRect->top + 52 };
		for (int x = 0; x < 4; x++) {
			if (nStatus & (1 << x)) {
				src.left -= 48;
			}
		}
		dest.left = dest.right - (src.right - src.left);

		if (nZoom & 2) {
			dest.top <<= 1;
			dest.bottom <<= 1;
		}

		if (nZoom & 1) {
			dest.left <<= 1;
			dest.right <<= 1;
		}

		// Blit the message to the surface using a colourkey
		pSurf->Blt(&dest, pStatusSurf, &src, DDBLT_ASYNC  | DDBLT_KEYSRC, NULL);
	}
}

static int VidSDrawChat(RECT* dest)
{
	bool bContent = false;

	if (pChatSurf == NULL) {
		return 1;
	}

	VidSClearSurface(pChatSurf, nKeyColour, NULL);

	for (int i = 0; i < CHAT_SIZE; i++) {
		if (VidSChatMessage[i].pIDText || VidSChatMessage[i].pMainText) {
			bContent = true;
			break;
		}
	}

	if (bContent) {

		nChatTimer = nFramesEmulated + 300;

		// Print the message
		HDC hDC;
		HFONT hFont;
		int nStringLength;
		int nFit = 0;
		SIZE sizeID, sizeMain;

		// Clear the surface first
		VidSClearSurface(pChatSurf, nKeyColour, NULL);

		pChatSurf->GetDC(&hDC);
		SetBkMode(hDC, TRANSPARENT);

		hFont = (HFONT)SelectObject(hDC, ChatIDFont);
		SetTextAlign(hDC, TA_TOP | TA_LEFT);

		nChatOverFlow = 0;

		for (int i = 0; i < CHAT_SIZE; i++) {

			// Exit when too many lines are displayed
			if (nChatOverFlow > (CHAT_SIZE >> 1)) {
				break;
			}

			if (VidSChatMessage[i].pIDText) {
				SelectObject(hDC, ChatIDFont);
				nStringLength =  _tcslen(VidSChatMessage[i].pIDText);
				MyExtTextOut(hDC, 0, (i + nChatOverFlow) * nChatFontSize, ETO_CLIPPED, dest, VidSChatMessage[i].pIDText, nStringLength, NULL, nChatShadowOffset, VidSChatMessage[i].nIDColour);
				GetTextExtentPoint32(hDC, VidSChatMessage[i].pIDText, nStringLength, &sizeID);
			} else {
				sizeID.cx = 0;
			}

			if (VidSChatMessage[i].pMainText) {
				SelectObject(hDC, ChatMainFont);
				nStringLength =  _tcslen(VidSChatMessage[i].pMainText);
				GetTextExtentExPoint(hDC, VidSChatMessage[i].pMainText, nStringLength, dest->right - sizeID.cx, &nFit, NULL, &sizeMain);

				if (nFit < nStringLength) {
					// The string doesn't fit on the screen in one line, break the line on the last space that fits
					while (nFit > 0 && (VidSChatMessage[i].pMainText[nFit] != ' ')) {
						nFit--;
					}

					nStringLength = nFit;
					MyExtTextOut(hDC, sizeID.cx, (i + nChatOverFlow) * nChatFontSize, ETO_CLIPPED, dest, VidSChatMessage[i].pMainText, nStringLength, NULL, nChatShadowOffset, VidSChatMessage[i].nMainColour);

					nChatOverFlow++;

					nStringLength =  _tcslen(&(VidSChatMessage[i].pMainText[nFit + 1]));
					MyExtTextOut(hDC, sizeID.cx, (i + nChatOverFlow) * nChatFontSize, ETO_CLIPPED, dest, &(VidSChatMessage[i].pMainText[nFit + 1]), nStringLength, NULL, nChatShadowOffset, VidSChatMessage[i].nMainColour);
				} else {
					SelectObject(hDC, ChatMainFont);
					MyTextOut(hDC, sizeID.cx, (i + nChatOverFlow) * nChatFontSize, VidSChatMessage[i].pMainText, nStringLength, nChatShadowOffset, VidSChatMessage[i].nMainColour);
				}
			}
		}

		// Clean up
		SelectObject(hDC, hFont);
		pChatSurf->ReleaseDC(hDC);
	} else {
		nChatTimer = 0;
	}

	return 0;
}

int VidSSetMatchInfo(char *p1, char *p2, char *blurb)
{
   _sntprintf(szMatchInfo, 256, _T("%s (p1) vs %s (p2)."), p1, p2);
   bDrawTV = true;
   return 0;
}

int VidSUpdateSpectatorCount(int spectatorCount)
{
   if (spectatorCount) {
      _sntprintf(szSpectatorCount, 256, _T("%d spectator%s"), spectatorCount, spectatorCount > 1 ? "s" : "");
   } else {
      _sntprintf(szSpectatorCount, 256, _T(""));
   }
   bDrawTV = true;
   return 0;
}

int VidSSetQuarkShowLogo(bool show)
{
   bShowGGPOLogo = show;
   bDrawTV = true;
   return 0;
}

int VidSDrawTV(RECT *rcDest)
{
	if (pTVSurf == NULL || !bDrawTV) {
		return 1;
	}

	VidSClearSurface(pTVSurf, nKeyColour, NULL);

	HDC hDC;
	HFONT hFont;
	int offset = 2;
   int pTVSurfRight = rcDest->right - rcDest->left;
	if (nZoom & 1) {
		pTVSurfRight <<= 1;
	}

	pTVSurf->GetDC(&hDC);
	SetBkMode(hDC, TRANSPARENT);
	hFont = (HFONT)SelectObject(hDC, ChatIDFont);

   if (*szConnectStatus) {
      int x = (rcDest->right - rcDest->left - 320) / 2;
      int y = (rcDest->bottom - rcDest->top - 240) / 2;

      if (bShowGGPOLogo) {
         BitBlt(hDC, x, y, 320, 240, hGGPODC, 0, 0, SRCCOPY);
      }

      SetTextAlign(hDC, TA_BOTTOM | TA_CENTER);
      MyTextOut(hDC, (rcDest->right - rcDest->left) / 2, rcDest->bottom - 4, 
                szConnectStatus, strlen(szConnectStatus), nChatShadowOffset, RGB(0xee, 0xee, 0xee));
   } else {
      SetTextAlign(hDC, TA_TOP | TA_LEFT);
	   MyTextOut(hDC, 4, 4, szMatchInfo, strlen(szMatchInfo), nChatShadowOffset, RGB(0xee, 0xee, 0xee));
      offset += nChatFontSize;

      SetTextAlign(hDC, TA_TOP | TA_RIGHT);
      MyTextOut(hDC, pTVSurfRight - 4, 4, szSpectatorCount, strlen(szSpectatorCount), nChatShadowOffset, RGB(0xcc, 0xcc, 0xcc));
   }
   SelectObject(hDC, hFont);
	pTVSurf->ReleaseDC(hDC);

   return 0;
}

static void VidSDisplayChat(IDirectDrawSurface7* pSurf, RECT* pRect)
{
	if (nChatTimer || bDrawChat) {
		// Blit the message to the surface using a colourkey
		RECT src = { 0, 0, pRect->right - pRect->left, nChatFontSize * (CHAT_SIZE + (CHAT_SIZE >> 1)) };

		// Update the message if needed
		if (bDrawChat) {
			VidSDrawChat(&src);
			bDrawChat = false;
		}

		if (nChatTimer) {
			RECT dest = { pRect->left, pRect->bottom - nChatFontSize * (CHAT_SIZE + nChatOverFlow), pRect->right, pRect->bottom };
			src.bottom = nChatFontSize * (CHAT_SIZE + nChatOverFlow);

			if (bEditActive) {
				dest.top -= nEditSize;
				dest.bottom -= nEditSize;
			} else {
				dest.top -= 4;
				dest.bottom -= 4;
			}

			if (nZoom & 2) {
				dest.top <<= 1;
				dest.bottom <<= 1;
			}

			if (nZoom & 1) {
				dest.left <<= 1;
				dest.right <<= 1;
			}

			pSurf->Blt(&dest, pChatSurf, &src, DDBLT_ASYNC | DDBLT_KEYSRC, NULL);
		}

		// Scroll message if needed
		if (nFramesEmulated > nChatTimer) {
			nChatTimer = 0;
			VidSAddChatMsg(NULL, 0, NULL, 0);
			bDrawChat = true;
		}
	}
}

int
VidSSetQuarkConnectStatus(TCHAR *status)
{
   _tcscpy(szConnectStatus, status);
   bDrawTV = true;
   return 1;
}



static void VidSDisplayTV(IDirectDrawSurface7* pSurf, RECT* pRect)
{
	// Blit the message to the surface using a colourkey
	RECT src = { 0, 0, pRect->right - pRect->left, pRect->bottom - pRect->top };
	RECT dest = *pRect;

	if (nZoom & 2) {
		dest.top <<= 1;
		dest.bottom <<= 1;
	}

	if (nZoom & 1) {
		dest.left <<= 1;
		dest.right <<= 1;
	}
   if (bDrawTV) {
      VidSDrawTV(&dest);
      bDrawTV = false;
   }

	pSurf->Blt(&dest, pTVSurf, &src, DDBLT_ASYNC | DDBLT_KEYSRC, NULL);
}

static void VidSDisplayEdit(IDirectDrawSurface7* pSurf, RECT* pRect)
{
	if (bEditActive) {
		RECT src = { 0, 0, pRect->right - pRect->left, nEditSize };
		RECT dest = { pRect->left, pRect->bottom - nEditSize, pRect->right, pRect->bottom };

		if (nZoom & 2) {
			dest.top <<= 1;
			dest.bottom <<= 1;
		}

		if (nZoom & 1) {
			dest.left <<= 1;
			dest.right <<= 1;
		}

		DWORD nStart, nEnd;
		SendMessage(hwndChat, EM_GETSEL, (WPARAM)&nStart, (WPARAM)&nEnd);

		if (nStart != nPrevStart || nEnd != nPrevEnd) {
			nPrevStart = nStart;
			nPrevEnd = nEnd;
			bEditTextChanged = true;
			nCursorTime = nFramesEmulated + 30;
			nCursorState = 1;
		} else {
			if (GetCurrentFrame() > nCursorTime) {
				nCursorTime = nFramesEmulated + 30;
				nCursorState = !nCursorState;
				bEditTextChanged = true;
			}
		}

		if (bEditTextChanged) {
			if (pEditSurf == NULL) {
				return;
			}

			// Print the message
			HDC hDC;
			HFONT hFont;
			SIZE size;
			int pos;

			TCHAR Space[] = _T(" ");
			unsigned int nFit = 0;
			TCHAR* pText = EditText;

//			bool bDisplayCursor = false;
//			if (GetFocus()) {
//				bDisplayCursor = true;
//			}

			// Clear the surface first
			VidSClearSurface(pEditSurf, nKeyColour, NULL);

			pEditSurf->GetDC(&hDC);
			SetBkMode(hDC, TRANSPARENT);
			hFont = (HFONT)SelectObject(hDC, EditTextFont);
			SetTextAlign(hDC, TA_TOP | TA_LEFT);

			// If the string is wider than the screen, shift the display to the right.
			pos = 0;
			do {
				GetTextExtentExPoint(hDC, pText, _tcslen(pText), src.right - pos - nEditSize, (int*)&nFit, NULL, &size);
				if (nFit < nStart) {
					pos -= src.right * 3 / 5;
				}
			} while (nFit < nStart);

			if (nStart == _tcslen(pText)) {
				if (nStart) {
					MyExtTextOut(hDC, pos + 3, 3, ETO_CLIPPED, &src, pText, nStart, NULL, nEditShadowOffset, RGB(0xDF, 0xDF, 0xFF));
				}

				GetTextExtentPoint32(hDC, pText, nStart, &size);
				pos += size.cx;

				if (nCursorState) {
					SelectObject(hDC, EditCursorFont);
				}
				MyExtTextOut(hDC, pos + 3, 3, ETO_CLIPPED, &src, Space, 1, NULL, nEditShadowOffset, RGB(0xFF, 0xFF, 0xFF));
			} else {
				if (nStart) {
					MyExtTextOut(hDC, pos + 3, 3, ETO_CLIPPED, &src, pText, nStart, NULL, nEditShadowOffset, RGB(0xDF, 0xDF, 0xFF));
				}

				GetTextExtentPoint32(hDC, pText, nStart, &size);
				pos += size.cx;

				if (nEnd == nStart) {
					if (nCursorState) {
						SelectObject(hDC, EditCursorFont);
					}
					MyExtTextOut(hDC, pos + 3, 3, ETO_CLIPPED, &src, pText + nStart, 1, NULL, nEditShadowOffset, RGB(0xFF, 0xFF, 0xFF));

					GetTextExtentPoint32(hDC, pText + nStart, 1, &size);
					pos += size.cx;

					// We really printed one character past the end of the selection
					nEnd++;
				} else {
					// Highlight selected characters
					SelectObject(hDC, EditTextFont);
					// SetTextColor(hDC, RGB(0x7F, 0x1F, 0x1F));
					MyExtTextOut(hDC, pos + 3, 3, ETO_CLIPPED, &src, pText + nStart, nEnd - nStart, NULL, nEditShadowOffset, RGB(0xFF, 0xFF, 0xDF));

					GetTextExtentPoint32(hDC, pText + nStart, nEnd - nStart, &size);
					pos += size.cx;
				}

				if (nEnd < _tcslen(EditText)) {
					SelectObject(hDC, EditTextFont);
					MyExtTextOut(hDC, pos + 3, 3, ETO_CLIPPED, &src, pText + nEnd, _tcslen(pText) - nEnd, NULL, nEditShadowOffset, RGB(0xDF, 0xDF, 0xFF));
				}
			}

			// Clean up
			SelectObject(hDC, hFont);
			pEditSurf->ReleaseDC(hDC);

			bEditTextChanged = false;
		}

		// Blit the message to the surface using a colourkey
		pSurf->Blt(&dest, pEditSurf, &src, DDBLT_ASYNC | DDBLT_KEYSRC, NULL);
	}
}

void VidSDisplayOSD(IDirectDrawSurface7* pSurf, RECT* pRect, int nFlags)
{
	nZoom = nFlags & 3;

	VidSDisplayStatus(pSurf, pRect);
	VidSDisplayShortMsg(pSurf, pRect);
	if (NetworkGame()) {
		VidSDisplayChat(pSurf, pRect);
		VidSDisplayEdit(pSurf, pRect);
		VidSDisplayTV(pSurf, pRect);
	}
}

int VidSNewShortMsg(const TCHAR* pText, int nRGB, int nDuration, int nPriority)	// int nRGB = 0, int nDuration = 0, int nPriority = 5
{
	// If a message with a higher priority is being displayed, exit.
	if (VidSShortMsg.nTimer && VidSShortMsg.nPriority > nPriority) {
		return 1;
	}

	int nSize =  _tcslen(pText);
	if (nSize > 31) {
		nSize = 31;
	}
	_tcsncpy(VidSShortMsg.pMsgText, pText, nSize);
	VidSShortMsg.pMsgText[nSize] = 0;
	if (nRGB) {
		// Convert RGB value to COLORREF
		VidSShortMsg.nColour = RGB((nRGB >> 16), ((nRGB >> 8) & 0xFF), (nRGB & 0xFF));
	} else {
		// Default message colour (yellow)
		VidSShortMsg.nColour = RGB(0xFF, 0xFF, 0x7F);
	}
	if (nDuration) {
		VidSShortMsg.nTimer = nFramesEmulated + nDuration;
	} else {
		VidSShortMsg.nTimer = nFramesEmulated + 120;
	}
	VidSShortMsg.nPriority = nPriority;

	{
		if (pShortMsgSurf == NULL) {
			return 1;
		}

		// Print the message
		HDC hDC;
		HFONT hFont;

		// Clear the surface first
		VidSClearSurface(pShortMsgSurf, nKeyColour, NULL);

		pShortMsgSurf->GetDC(&hDC);
		SetBkMode(hDC, TRANSPARENT);
		hFont = (HFONT)SelectObject(hDC, ShortMsgFont);
		SetTextAlign(hDC, TA_TOP | TA_RIGHT);

		MyTextOut(hDC, 192 - 2, 0, VidSShortMsg.pMsgText, _tcslen(VidSShortMsg.pMsgText), 2, VidSShortMsg.nColour);

		// Clean up
		SelectObject(hDC, hFont);
		pShortMsgSurf->ReleaseDC(hDC);
	}

	return 0;
}

void VidSKillShortMsg()
{
	VidSShortMsg.nTimer = 0;
}

int VidSAddChatMsg(const TCHAR* pID, int nIDRGB, const TCHAR* pMain, int nMainRGB)
{
	if (pID || pMain) {
		// Scroll the text buffers up one entry
		free(VidSChatMessage[0].pIDText);
		VidSChatMessage[0].pIDText = NULL;
		free(VidSChatMessage[0].pMainText);
		VidSChatMessage[0].pMainText = NULL;

		for (int i = 1; i < CHAT_SIZE; i++) {
			VidSChatMessage[i - 1].pIDText = VidSChatMessage[i].pIDText;
			VidSChatMessage[i - 1].nIDColour = VidSChatMessage[i].nIDColour;
			VidSChatMessage[i - 1].pMainText = VidSChatMessage[i].pMainText;
			VidSChatMessage[i - 1].nMainColour = VidSChatMessage[i].nMainColour;
		}

		// Put the new entry in the last position
		if (pID) {
			int nSize = _tcslen(pID);
			VidSChatMessage[CHAT_SIZE - 1].pIDText = (TCHAR*)malloc((nSize + 1) * sizeof(TCHAR));
			 _tcscpy(VidSChatMessage[CHAT_SIZE - 1].pIDText, pID);
			VidSChatMessage[CHAT_SIZE - 1].pIDText[nSize] = 0;
			VidSChatMessage[CHAT_SIZE - 1].nIDColour = RGB((nIDRGB >> 16), ((nIDRGB >> 8) & 0xFF), (nIDRGB & 0xFF));
		} else {
			VidSChatMessage[CHAT_SIZE - 1].pIDText = NULL;
		}
		if (pMain) {
			int nSize = _tcslen(pMain);
			VidSChatMessage[CHAT_SIZE - 1].pMainText = (TCHAR*)malloc((nSize + 1) * sizeof(TCHAR));
			 _tcscpy(VidSChatMessage[CHAT_SIZE - 1].pMainText, pMain);
			VidSChatMessage[CHAT_SIZE - 1].pMainText[nSize] = 0;
			VidSChatMessage[CHAT_SIZE - 1].nMainColour = RGB((nMainRGB >> 16), ((nMainRGB >> 8) & 0xFF), (nMainRGB & 0xFF));
		} else {
			VidSChatMessage[CHAT_SIZE - 1].pMainText = NULL;
		}
	} else {
		for (int i = 0; i < CHAT_SIZE; i++) {
			if (VidSChatMessage[i].pIDText || VidSChatMessage[i].pMainText) {
				free(VidSChatMessage[i].pIDText);
				VidSChatMessage[i].pIDText = NULL;
				free(VidSChatMessage[i].pMainText);
				VidSChatMessage[i].pMainText = NULL;

				break;
			}
		}
	}

	bDrawChat = true;

	return 0;
}

