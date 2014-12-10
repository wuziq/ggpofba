// FB Alpha - Emulator for MC68000/Z80 based arcade games
//            Refer to the "license.txt" file for more info

// Burner emulation library

#ifdef __cplusplus
 extern "C" {
#endif

#if !defined (_WIN32)
 #define __cdecl
#endif

#include <time.h>
#include "cheat.h"
#include "state.h"

// Enable the MAME logerror() function in debug builds
// #define MAME_USE_LOGERROR

// Give access to the CPUID function for various compilers
#if defined (__GNUC__)
 #define CPUID(f,ra,rb,rc,rd) __asm__ __volatile__ ("cpuid"											\
 													: "=a" (ra), "=b" (rb), "=c" (rc), "=d" (rd)	\
 													: "a"  (f)										\
 												   );
#elif defined (_MSC_VER)
 #define CPUID(f,ra,rb,rc,rd) __asm { __asm mov		eax, f		\
									  __asm cpuid				\
									  __asm mov		ra, eax		\
									  __asm mov		rb, ebx		\
									  __asm mov		rc, ecx		\
									  __asm mov		rd, edx }
#else
 #define CPUID(f,ra,rb,rc,rd)
#endif

#ifdef _UNICODE
 #define SEPERATOR_1 " \u2022 "
 #define SEPERATOR_2 " \u25E6 "
#else
 #define SEPERATOR_1 " ~ "
 #define SEPERATOR_2 " ~ "
#endif

#ifdef _UNICODE
 #define WRITE_UNICODE_BOM(file) { UINT16 BOM[] = { 0xFEFF }; fwrite(BOM, 2, 1, file); }
#else
 #define WRITE_UNICODE_BOM(file)
#endif

typedef signed char INT8;
typedef unsigned char UINT8;
typedef signed short INT16;
typedef unsigned short UINT16;
typedef signed int INT32;
typedef unsigned int UINT32;

extern int nBurnVer;						// Version number of the library

// ---------------------------------------------------------------------------
// Callbacks

// Application-defined rom loading function
extern int (__cdecl *BurnExtLoadRom)(unsigned char* Dest, int* pnWrote, int i);

// Application-defined progress indicator functions
extern int (__cdecl *BurnExtProgressRangeCallback)(double dProgressRange);
extern int (__cdecl *BurnExtProgressUpdateCallback)(double dProgress, const TCHAR* pszText, bool bAbs);

// Application-defined colour conversion function
extern unsigned int (__cdecl *BurnHighCol) (int r, int g, int b, int i);

// ---------------------------------------------------------------------------

extern unsigned int nCurrentFrame;

inline static int GetCurrentFrame() {
	return nCurrentFrame;
}

inline static void SetCurrentFrame(const unsigned int n) {
	nCurrentFrame = n;
}

// ---------------------------------------------------------------------------
// Driver info structures

// ROMs

#define BRF_PRG				(1 << 20)
#define BRF_GRA				(1 << 21)
#define BRF_SND				(1 << 22)

#define BRF_ESS				(1 << 24)
#define BRF_BIOS			(1 << 25)
#define BRF_SELECT			(1 << 26)
#define BRF_OPT				(1 << 27)
#define BRF_NODUMP			(1 << 28)

struct BurnRomInfo {
	char szName[32];
	unsigned int nLen;
	unsigned int nCrc;
	unsigned int nType;
};

// Inputs

#define BIT_DIGITAL			(1)

#define BIT_GROUP_ANALOG	(4)
#define BIT_ANALOG_REL		(4)
#define BIT_ANALOG_ABS		(5)

#define BIT_GROUP_CONSTANT	(8)
#define BIT_CONSTANT		(8)
#define BIT_DIPSWITCH		(9)

struct BurnInputInfo {
	char* szName;
	unsigned char nType;
	union {
		unsigned char* pVal;					// Most inputs use a char*
		unsigned short* pShortVal;				// All analog inputs use a short*
	};
	char* szInfo;
};

// DIPs

struct BurnDIPInfo {
	int nInput;
	unsigned char nFlags;
	unsigned char nMask;
	unsigned char nSetting;
	char* szText;
};

// ---------------------------------------------------------------------------

extern bool bBurnUseMMX;
extern bool bBurnUseASMCPUEmulation;

extern unsigned int nFramesEmulated;
extern unsigned int nFramesRendered;
extern clock_t starttime;					// system time when emulation started and after roms loaded

extern bool bForce60Hz;

extern int nBurnFPS;
extern int nBurnCPUSpeedAdjust;

extern unsigned int nBurnDrvCount;			// Count of game drivers
extern unsigned int nBurnDrvSelect;			// Which game driver is selected

extern int nMaxPlayers;

extern unsigned char *pBurnDraw;			// Pointer to correctly sized bitmap
extern int nBurnPitch;						// Pitch between each line
extern int nBurnBpp;						// Bytes per pixel (2, 3, or 4)

extern unsigned char nBurnLayer;			// Can be used externally to select which layers to show
extern unsigned char nSpriteEnable;			// Can be used externally to select which Sprites to show

extern int nBurnSoundRate;					// Samplerate of sound
extern int nBurnSoundLen;					// Length in samples per frame
extern short* pBurnSoundOut;				// Pointer to output buffer

extern int nInterpolation;					// Desired interpolation level for ADPCM/PCM sound
extern int nFMInterpolation;				// Desired interpolation level for FM sound

#define PRINT_NORMAL	(0)
#define PRINT_UI		(1)
#define PRINT_IMPORTANT (2)
#define PRINT_ERROR		(3)

extern int (__cdecl *bprintf) (int nStatus, TCHAR* szFormat, ...);

int BurnLibInit();
int BurnLibExit();

int BurnDrvInit();
int BurnDrvExit();
int BurnDrvFrame();
int BurnDrvRedraw();
int BurnRecalcPal();

int BurnSetProgressRange(double dProgressRange);
int BurnUpdateProgress(double dProgressStep, const TCHAR* pszText, bool bAbs);

// ---------------------------------------------------------------------------
// Retrieve driver information

#define DRV_NAME		 (0)
#define DRV_DATE		 (1)
#define DRV_FULLNAME	 (2)
#define DRV_ALTNAME		 (3)
#define DRV_COMMENT		 (4)
#define DRV_MANUFACTURER (5)
#define DRV_SYSTEM		 (6)
#define DRV_PARENT		 (7)
#define DRV_BOARDROM	 (8)

#define DRV_NEXTNAME	 (1 << 8)
#define DRV_ASCIIONLY	 (1 << 12)
#define DRV_UNICODEONLY	 (1 << 13)

TCHAR* BurnDrvGetText(unsigned int i);
char* BurnDrvGetTextA(unsigned int i);

int BurnDrvGetZipName(char** pszName, unsigned int i);
int BurnDrvGetRomInfo(struct BurnRomInfo *pri, unsigned int i);
int BurnDrvGetRomName(char** pszName, unsigned int i, int nAka);
int BurnDrvGetInputInfo(struct BurnInputInfo* pii, unsigned int i);
int BurnDrvGetDIPInfo(struct BurnDIPInfo* pdi, unsigned int i);
int BurnDrvGetVisibleSize(int* pnWidth, int* pnHeight);
int BurnDrvGetVisibleOffs(int* pnLeft, int* pnTop);
int BurnDrvGetFullSize(int* pnWidth, int* pnHeight);
int BurnDrvGetAspect(int* pnXAspect, int* pnYAspect);
int BurnDrvGetHardwareCode();
int BurnDrvGetFlags();
bool BurnDrvIsWorking();
int BurnDrvGetMaxPlayers();

// ---------------------------------------------------------------------------
// Flags used with the Burndriver structure

// Flags for the flags member
#define BDF_GAME_WORKING			(1 << 0)
#define BDF_ORIENTATION_FLIPPED		(1 << 1)
#define BDF_ORIENTATION_VERTICAL	(1 << 2)
#define BDF_BOARDROM				(1 << 3)
#define BDF_CLONE					(1 << 4)
#define BDF_BOOTLEG					(1 << 5)
#define BDF_PROTOTYPE				(1 << 6)
#define BDF_16BIT_ONLY				(1 << 7)

// Flags for the hardware member
// Format: 0xDDEEFFFF, where EE: Manufacturer, DD: Hardware platform, FFFF: Flags (used by driver)

#define HARDWARE_PUBLIC_MASK		(0xFFFF0000)
#define HARDWARE_PREFIX_MISC		(0x00000000)
#define HARDWARE_PREFIX_CAPCOM		(0x01000000)
#define HARDWARE_PREFIX_SEGA		(0x02000000)
#define HARDWARE_PREFIX_KONAMI		(0x03000000)
#define HARDWARE_PREFIX_TOAPLAN		(0x04000000)
#define HARDWARE_PREFIX_SNK			(0x05000000)
#define HARDWARE_PREFIX_CAVE		(0x06000000)
#define HARDWARE_PREFIX_CPS2		(0x07000000)

#define HARDWARE_MISC_MISC			(HARDWARE_PREFIX_MISC)

#define HARDWARE_CAPCOM_CPS1		(HARDWARE_PREFIX_CAPCOM | 0x00010000)
#define HARDWARE_CAPCOM_CPS1_QSOUND (HARDWARE_PREFIX_CAPCOM | 0x00020000)
#define HARDWARE_CAPCOM_CPS1_GENERIC (HARDWARE_PREFIX_CAPCOM | 0x00030000)
#define HARDWARE_CAPCOM_CPSCHANGER	(HARDWARE_PREFIX_CAPCOM | 0x00040000)
#define HARDWARE_CAPCOM_CPS2		(HARDWARE_PREFIX_CPS2 | 0x00010000)
#define HARDWARE_CAPCOM_CPS2_SIMM	(0x0002)

#define HARDWARE_SEGA_SYSTEMX		(HARDWARE_PREFIX_SEGA | 0x00010000)
#define HARDWARE_SEGA_SYSTEMY		(HARDWARE_PREFIX_SEGA | 0x00020000)
#define HARDWARE_SEGA_SYSTEM16A		(HARDWARE_PREFIX_SEGA | 0x00030000)
#define HARDWARE_SEGA_SYSTEM16B 	(HARDWARE_PREFIX_SEGA | 0x00040000)
#define HARDWARE_SEGA_SYSTEM16M		(HARDWARE_PREFIX_SEGA | 0x00050000)
#define HARDWARE_SEGA_SYSTEM18		(HARDWARE_PREFIX_SEGA | 0x00060000)
#define HARDWARE_SEGA_HANGON		(HARDWARE_PREFIX_SEGA | 0x00070000)
#define HARDWARE_SEGA_OUTRUN		(HARDWARE_PREFIX_SEGA | 0x00080000)

#define HARDWARE_SEGA_FD1089A_ENC	(0x0002)
#define HARDWARE_SEGA_FD1089B_ENC	(0x0004)
#define HARDWARE_SEGA_5358		(0x0008)
#define HARDWARE_SEGA_MC8123_ENC	(0x0010)
#define HARDWARE_SEGA_BAYROUTE_MEMMAP	(0x0020)
#define HARDWARE_SEGA_ALT_MEMMAP	(0x0040)
#define HARDWARE_SEGA_FD1094_ENC	(0x0080)
#define HARDWARE_SEGA_SPRITE_LOAD32	(0x0100)
#define HARDWARE_SEGA_YM2203		(0x0200)

#define HARDWARE_TOAPLAN_RAIZING	(HARDWARE_PREFIX_TOAPLAN | 0x00010000)
#define HARDWARE_TOAPLAN_68K_Zx80	(HARDWARE_PREFIX_TOAPLAN | 0x00020000)
#define HARDWARE_TOAPLAN_68K_ONLY	(HARDWARE_PREFIX_TOAPLAN | 0x00030000)

#define HARDWARE_SNK_NEOGEO			(HARDWARE_PREFIX_SNK | 0x00010000)
#define HARDWARE_SNK_SRAM			(0x0002)	// SRAM protection
#define HARDWARE_SNK_SWAPP			(0x0004)	// Swap code roms
#define HARDWARE_SNK_SWAPV			(0x0008)	// Swap sound roms
#define HARDWARE_SNK_SWAPC			(0x0010)	// Swap sprite roms
#define HARDWARE_SNK_ENCRYPTED_A	(0x0020)	// KOF99 encryption scheme
#define HARDWARE_SNK_ENCRYPTED_B	(0x0040)	// KOF2000 encryption scheme
#define HARDWARE_SNK_ALTERNATE_TEXT	(0x0080)	// KOF2000 text layer banks
#define HARDWARE_SNK_SMA_PROTECTION	(0x0100)	// SMA protection
#define HARDWARE_SNK_CUSTOM_BANKING (0x0200)	// Uses custom banking
#define HARDWARE_SNK_P32		(0x0400)	// Uses 32Bit 68000 roms
#define HARDWARE_SNK_PVC_PROT		(0x0800)

#define HARDWARE_SNK_CONTROLMASK	(0xF000)
#define HARDWARE_SNK_JOYSTICK		(0x0000)	// Uses joysticks
#define HARDWARE_SNK_PADDLE			(0x1000)	// Uses joysticks or paddles
#define HARDWARE_SNK_TRACKBALL		(0x2000)	// Uses a trackball
#define HARDWARE_SNK_4_JOYSTICKS	(0x3000)	// Uses 4 joysticks
#define HARDWARE_SNK_MAHJONG		(0x4000)	// Uses a special mahjong controller
#define HARDWARE_SNK_GAMBLING		(0x5000)	// Uses gambling controls
#define HARDWARE_SNK_PCB		(0x6000)

#define HARDWARE_SNK_NEOCD			(HARDWARE_PREFIX_SNK | 0x00020000)

#define HARDWARE_CAVE_68K_ONLY		(HARDWARE_PREFIX_CAVE)
#define HARDWARE_CAVE_68K_Z80		(HARDWARE_PREFIX_CAVE | 0x0001)
#define HARDWARE_CAVE_M6295			(0x0002)
#define HARDWARE_CAVE_YM2151		(0x0004)

#ifdef __cplusplus
 } // End of extern "C"
#endif

