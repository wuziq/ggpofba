// Burner Config file module
#include "burner.h"
int nIniVersion = 0;

struct VidPresetData VidPreset[4] = {
	{ 400, 300},
	{ 640, 480},
	{ 1024, 768},
	{ 1280, 960},
};

static void CreateConfigName(TCHAR* szConfig)
{
	_stprintf(szConfig, _T("config\\%s.ini"), szAppExeName);
	return;
}

// Read in the config file for the whole application
int ConfigAppLoad()
{
	TCHAR szConfig[MAX_PATH];
	TCHAR szLine[1024];
	FILE* h;

	CreateConfigName(szConfig);

	if ((h = _tfopen(szConfig, _T("rt"))) == NULL) {
		return 1;
	}

	// Go through each line of the config file
	while (_fgetts(szLine, sizeof(szLine), h)) {
		int nLen = _tcslen(szLine);

		// Get rid of the linefeed at the end
		if (szLine[nLen - 1] == 10) {
			szLine[nLen - 1] = 0;
			nLen--;
		}

#define VAR(x) { TCHAR* szValue = LabelCheck(szLine,_T(#x));			\
  if (szValue) x = _tcstol(szValue, NULL, 0); }
#define FLT(x) { TCHAR* szValue = LabelCheck(szLine,_T(#x));			\
  if (szValue) x = _tcstod(szValue, NULL); }
#define STR(x) { TCHAR* szValue = LabelCheck(szLine,_T(#x) _T(" "));	\
  if (szValue) _tcscpy(x,szValue); }

		VAR(nIniVersion);

		// Emulation
		VAR(bBurnUseASMCPUEmulation);

		// Video
		VAR(nVidWidth); VAR(nVidHeight); VAR(nVidDepth); VAR(nVidRefresh);
		VAR(bVidArcaderes);
		VAR(nVidRotationAdjust);
		VAR(VidPreset[0].nWidth); VAR(VidPreset[0].nHeight);
		VAR(VidPreset[1].nWidth); VAR(VidPreset[1].nHeight);
		VAR(VidPreset[2].nWidth); VAR(VidPreset[2].nHeight);
		VAR(VidPreset[3].nWidth); VAR(VidPreset[3].nHeight);
		VAR(nScreenSize);
		VAR(nWindowSize);
		VAR(nWindowPosX); VAR(nWindowPosY);
		VAR(bDoGamma);
		VAR(bVidUseHardwareGamma);
		VAR(bHardwareGammaOnly);
		FLT(nGamma);
		VAR(bVidFullStretch);
		VAR(bVidCorrectAspect);

		VAR(bVidTripleBuffer);
		VAR(bVidVSync);

		VAR(bVidScanlines);
		VAR(nVidScanIntensity);
		VAR(nVidScrnAspectX);
		VAR(nVidScrnAspectY);
		VAR(bForce60Hz);
		VAR(bAlwaysDrawFrames);

		VAR(bVidUsePlaceholder);
		STR(szPlaceHolder);

		VAR(nVidSelect);
		VAR(nVidBlitterOpt[0]);
		VAR(nVidBlitterOpt[1]);
		VAR(nVidBlitterOpt[2]);
		VAR(nVidBlitterOpt[3]);

		// DirectDraw blitter
		VAR(bVidScanHalf);

		// Direct3D blitter
		VAR(bVidBilinear);
		VAR(bVidScanDelay);
		VAR(bVidScanRotate);
		VAR(bVidScanBilinear);
		VAR(nVidFeedbackIntensity);
		VAR(nVidFeedbackOverSaturation);
		FLT(fVidScreenAngle);
		FLT(fVidScreenCurvature);
		VAR(bVidForce16bit);
		VAR(nVidTransferMethod);

		// DirectX Graphics blitter
		FLT(dVidCubicB);
		FLT(dVidCubicC);

		// Sound
		VAR(nAudSampleRate);
		VAR(nAudSegCount);
		VAR(nAudDSPModule);
		VAR(nInterpolation);
		VAR(nFMInterpolation);

		// Other
		STR(szLocalisationTemplate);

		VAR(nVidSDisplayStatus);
		VAR(nMinChatFontSize);
		VAR(nMaxChatFontSize);

		VAR(bModelessMenu);

		VAR(nSplashTime);

		VAR(bDrvSaveAll);
		VAR(nAppThreadPriority);
		VAR(bAlwaysProcessKeyboardInput);
		VAR(bAutoPause);
		VAR(bSaveInputs);

		VAR(nLoadMenuShowX);

		STR(szAppRomPaths[0]);
		STR(szAppRomPaths[1]);
		STR(szAppRomPaths[2]);
		STR(szAppRomPaths[3]);
		STR(szAppRomPaths[4]);
		STR(szAppRomPaths[5]);
		STR(szAppRomPaths[6]);
		STR(szAppRomPaths[7]);

		// Default Controls
		VAR(nPlayerDefaultControls[0]);
		STR(szPlayerDefaultIni[0]);
		VAR(nPlayerDefaultControls[1]);
		STR(szPlayerDefaultIni[1]);
		VAR(nPlayerDefaultControls[2]);
		STR(szPlayerDefaultIni[2]);
		VAR(nPlayerDefaultControls[3]);
		STR(szPlayerDefaultIni[3]);

#undef STR
#undef FLT
#undef VAR
	}

	fclose(h);
	return 0;
}

// Write out the config file for the whole application
int ConfigAppSave()
{
	TCHAR szConfig[MAX_PATH];
	FILE *h;

	if (bCmdOptUsed) {
		return 1;
	}

	CreateConfigName(szConfig);

	if ((h = _tfopen(szConfig, _T("wt"))) == NULL) {
		return 1;
	}

	// Write title
	_ftprintf(h, _T("// ") _T(APP_TITLE) _T(" v%s --- Main Config File\n\n"), szAppBurnVer);
	_ftprintf(h, _T("// Don't edit this file manually unless you know what you're doing\n"));
	_ftprintf(h, _T("// ") _T(APP_TITLE) _T(" will restore default settings when this file is deleted\n"));

#define VAR(x) _ftprintf(h, _T(#x) _T(" %d\n"),  x)
#define FLT(x) _ftprintf(h, _T(#x) _T(" %lf\n"), x)
#define STR(x) _ftprintf(h, _T(#x) _T(" %s\n"),  x)

	_ftprintf(h, _T("\n// The application version this file was saved from\n"));
	// We can't use the macros for this!
	_ftprintf(h, _T("nIniVersion 0x%06X"), nBurnVer);

	_ftprintf(h, _T("\n\n\n"));
	_ftprintf(h, _T("// --- emulation --------------------------------------------------------------\n"));

	_ftprintf(h, _T("\n// If non-zero, use A68K for MC68000 emulation\n"));
	VAR(bBurnUseASMCPUEmulation);

	_ftprintf(h, _T("\n\n\n"));
	_ftprintf(h, _T("// --- Video ------------------------------------------------------------------\n"));

	_ftprintf(h, _T("\n// The display mode to use for fullscreen\n"));
	VAR(nVidWidth); VAR(nVidHeight); VAR(nVidDepth);
	_ftprintf(h, _T("\n// Specify the refresh rate, 0 = default (changing this will not work with many video cards)\n"));
	VAR(nVidRefresh);
	_ftprintf(h, _T("\n// If non-zero, use the same fullscreen resolution as the original arcade game\n"));
	VAR(bVidArcaderes);
	_ftprintf(h, _T("\n// If non-zero, do not rotate the graphics for vertical games\n"));
	VAR(nVidRotationAdjust);
	_ftprintf(h, _T("\n// The preset resolutions appearing in the menu\n"));
	VAR(VidPreset[0].nWidth); VAR(VidPreset[0].nHeight);
	VAR(VidPreset[1].nWidth); VAR(VidPreset[1].nHeight);
	VAR(VidPreset[2].nWidth); VAR(VidPreset[2].nHeight);
	VAR(VidPreset[3].nWidth); VAR(VidPreset[3].nHeight);
	_ftprintf(h, _T("\n// Full-screen size (0 = use display mode variables)\n"));
	VAR(nScreenSize);
	_ftprintf(h, _T("\n// Initial window size (0 = autosize)\n"));
	VAR(nWindowSize);
	_ftprintf(h, _T("\n// Window position\n"));
	VAR(nWindowPosX); VAR(nWindowPosY);
	_ftprintf(h, _T("\n// If non-zero, perform gamma correction\n"));
	VAR(bDoGamma);
	_ftprintf(h, _T("\n// If non-zero, use the video hardware to correct gamma\n"));
	VAR(bVidUseHardwareGamma);
	_ftprintf(h, _T("\n// If non-zero, don't fall back on software gamma correction\n"));
	VAR(bHardwareGammaOnly);
	_ftprintf(h, _T("\n// Gamma to correct with\n"));
	FLT(nGamma);
	_ftprintf(h, _T("\n// If non-zero, allow stretching of the image to any size\n"));
	VAR(bVidFullStretch);
	_ftprintf(h, _T("\n// If non-zero, stretch the image to the largest size preserving aspect ratio\n"));
	VAR(bVidCorrectAspect);
	_ftprintf(h, _T("\n// If non-zero, try to use a triple buffer in fullscreen\n"));
	VAR(bVidTripleBuffer);
	_ftprintf(h, _T("\n// If non-zero, try to synchronise blits with the display\n"));
	VAR(bVidVSync);
	_ftprintf(h, _T("\n// Transfer method:  0 = blit from system memory / use driver/DirectX texture management;\n"));
	_ftprintf(h, _T("//                   1 = copy to a video memory surface, then use bltfast();\n"));
	_ftprintf(h, _T("//                  -1 = autodetect for DirectDraw, equals 1 for Direct3D\n"));
	VAR(nVidTransferMethod);
	_ftprintf(h, _T("\n// If non-zero, draw scanlines to simulate a low-res monitor\n"));
	VAR(bVidScanlines);
	_ftprintf(h, _T("\n// Maximum scanline intensity\n"));
	VAR(nVidScanIntensity);
	_ftprintf(h, _T("\n// If non-zero, rotate scanlines and RGB effects for rotated games\n"));
	VAR(bVidScanRotate);
	_ftprintf(h, _T("\n// The selected blitter module\n"));
	VAR(nVidSelect);
	_ftprintf(h, _T("\n// Options for the blitter modules\n"));
	VAR(nVidBlitterOpt[0]);
	VAR(nVidBlitterOpt[1]);
	VAR(nVidBlitterOpt[2]);
	VAR(nVidBlitterOpt[3]);
	_ftprintf(h, _T("\n// The aspect ratio of the monitor\n"));
	VAR(nVidScrnAspectX);
	VAR(nVidScrnAspectY);
	_ftprintf(h, _T("\n// If non-zero, force all games to use a 60Hz refresh rate\n"));
	VAR(bForce60Hz);
	_ftprintf(h, _T("\n// If non-zero, skip frames when needed to keep the emulation running at full speed\n"));
	VAR(bAlwaysDrawFrames);

	_ftprintf(h, _T("\n// If non-zero, use a placeholder image when no game is loaded\n"));
	VAR(bVidUsePlaceholder);
	_ftprintf(h, _T("\n// The filename of the placeholder image to use (empty filename = use built-in)\n"));
	STR(szPlaceHolder);

	_ftprintf(h, _T("\n"));
	_ftprintf(h, _T("// --- DirectDraw blitter module settings -------------------------------------\n"));
	_ftprintf(h, _T("\n// If non-zero, draw scanlines at 50%% intensity\n"));
	VAR(bVidScanHalf);
	_ftprintf(h, _T("\n"));
	_ftprintf(h, _T("// --- Direct3D 7 blitter module settings -------------------------------------\n"));
	_ftprintf(h, _T("\n// If non-zero, use bi-linear filtering to display the image\n"));
	VAR(bVidBilinear);
	_ftprintf(h, _T("\n// If non-zero, simulate slow phosphors (feedback)\n"));
	VAR(bVidScanDelay);
	_ftprintf(h, _T("\n// If non-zero, use bi-linear filtering for the scanlines\n"));
	VAR(bVidScanBilinear);
	_ftprintf(h, _T("\n// Feedback amount for slow phosphor simulation\n"));
	VAR(nVidFeedbackIntensity);
	_ftprintf(h, _T("\n// Oversaturation amount for slow phosphor simulation\n"));
	VAR(nVidFeedbackOverSaturation);
	_ftprintf(h, _T("\n// Angle at wich the emulated screen is tilted (in radians)\n"));
	FLT(fVidScreenAngle);
	_ftprintf(h, _T("\n// Angle of the sphere segment used for the 3D screen (in radians)\n"));
	FLT(fVidScreenCurvature);
	_ftprintf(h, _T("\n// If non-zero, force 16 bit emulation even in 32-bit screenmodes\n"));
	VAR(bVidForce16bit);
	_ftprintf(h, _T("\n"));
	_ftprintf(h, _T("// --- DirectX Graphics 9 blitter module settings -----------------------------\n"));
	_ftprintf(h, _T("\n// The filter parameters for the cubic filter\n"));
	FLT(dVidCubicB);
	FLT(dVidCubicC);

	_ftprintf(h, _T("\n\n\n"));
	_ftprintf(h, _T("// --- Sound ------------------------------------------------------------------\n"));

	_ftprintf(h, _T("\n// Sample rate\n"));
	VAR(nAudSampleRate);
	_ftprintf(h, _T("\n// Number of frames in sound buffer (= sound lag)\n"));
	VAR(nAudSegCount);
	_ftprintf(h, _T("\n// DSP module to use for sound enhancement: 0 = none, 1 = low-pass filter\n"));
	VAR(nAudDSPModule);
	_ftprintf(h, _T("\n// The order of PCM/ADPCM interpolation\n"));
	VAR(nInterpolation);
	_ftprintf(h, _T("\n// The order of FM interpolation\n"));
	VAR(nFMInterpolation);

	_ftprintf(h, _T("\n\n\n"));
	_ftprintf(h, _T("// --- UI ---------------------------------------------------------------------\n"));

	_ftprintf(h, _T("\n// Filename of the active UI translation template\n"));
	STR(szLocalisationTemplate);

	_ftprintf(h, _T("\n// 1 = display pause/record/replay/kaillera icons in the upper right corner of the display\n"));
	VAR(nVidSDisplayStatus);
	_ftprintf(h, _T("\n// Minimum height (in pixels) of the font used for the Kaillera chat function (used for arcade resolution)\n"));
	VAR(nMinChatFontSize);
	_ftprintf(h, _T("\n// Maximum height (in pixels) of the font used for the Kaillera chat function (used for 1280x960 or higher).\n"));
	VAR(nMaxChatFontSize);

	_ftprintf(h, _T("\n// Make the menu modeless\n"));
	VAR(bModelessMenu);

	_ftprintf(h, _T("\n// Minimum length of time to display the splash screen (in milliseconds)\n"));
	VAR(nSplashTime);

	_ftprintf(h, _T("\n// If non-zero, load and save all ram (the state)\n"));
	VAR(bDrvSaveAll);
	_ftprintf(h, _T("\n// The thread priority for the application. Do *NOT* edit this manually\n"));
	VAR(nAppThreadPriority);
	_ftprintf(h, _T("\n// If non-zero, process keyboard input even when the application loses focus\n"));
	VAR(bAlwaysProcessKeyboardInput);
	_ftprintf(h, _T("\n// If non-zero, pause when the application loses focus\n"));
	VAR(bAutoPause);
	_ftprintf(h, _T("\n// If non-zero, save the inputs for each game\n"));
	VAR(bSaveInputs);
	_ftprintf(h, _T("\n"));
	_ftprintf(h, _T("// --- Load Game Dialog -------------------------------------------------------\n"));
	_ftprintf(h, _T("\n// Load game dialog options\n"));
	VAR(nLoadMenuShowX);

	_ftprintf(h, _T("\n// The paths to search for rom zips (include trailing backslash)\n"));
	STR(szAppRomPaths[0]);
	STR(szAppRomPaths[1]);
	STR(szAppRomPaths[2]);
	STR(szAppRomPaths[3]);
	STR(szAppRomPaths[4]);
	STR(szAppRomPaths[5]);
	STR(szAppRomPaths[6]);
	STR(szAppRomPaths[7]);

	_ftprintf(h, _T("\n\n\n"));
	_ftprintf(h, _T("// --- miscellaneous ---------------------------------------------------------\n"));

	_ftprintf(h, _T("\n// Player default controls, number is the index of the configuration in the input dialog\n"));
	VAR(nPlayerDefaultControls[0]);
	STR(szPlayerDefaultIni[0]);
	VAR(nPlayerDefaultControls[1]);
	STR(szPlayerDefaultIni[1]);
	VAR(nPlayerDefaultControls[2]);
	STR(szPlayerDefaultIni[2]);
	VAR(nPlayerDefaultControls[3]);
	STR(szPlayerDefaultIni[3]);

	_ftprintf(h, _T("\n\n\n"));

#undef STR
#undef FLT
#undef VAR

	fclose(h);
	return 0;
}

