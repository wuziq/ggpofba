// Mad Gear/Led Storm
#include "burnint.h"
#include "msm6295.h"

// ---------------------------------------------------------------------------
// Inputs

static unsigned char drvInput[8] = {0, };
static unsigned char drvInpJoy1[8];
static unsigned char drvInpJoy2[8];
static unsigned char drvInpMisc[8];
static unsigned char drvReset = 0;


// Dip Switch and Input Definitions
static struct BurnInputInfo madgearInputList[] = {
	{"P1 Coin"     , BIT_DIGITAL  , drvInpMisc + 4,	"p1 coin"},
	{"P1 Start"    , BIT_DIGITAL  , drvInpMisc + 2,	"p1 start"},
	{"P1 Up"       , BIT_DIGITAL  , drvInpJoy1 + 7,	"p1 up"},
	{"P1 Down"     , BIT_DIGITAL  , drvInpJoy1 + 6,	"p1 down"},
	{"P1 Left"     , BIT_DIGITAL  , drvInpJoy1 + 5,	"p1 left"},
	{"P1 Right"    , BIT_DIGITAL  , drvInpJoy1 + 4,	"p1 right"},
	{"P1 Button 1" , BIT_DIGITAL  , drvInpJoy1 + 3,	"p1 fire 1"},
//	{"P1 Button 2" , BIT_DIGITAL  , drvInpJoy1 + 2,	"p1 fire 2"},
//	{"P1 Button 3" , BIT_DIGITAL  , drvInpJoy1 + 1,	"p1 fire 3"},

	{"P2 Coin"     , BIT_DIGITAL  , drvInpMisc + 3,	"p2 coin"},
	{"P2 Start"    , BIT_DIGITAL  , drvInpMisc + 1,	"p2 start"},
	{"P2 Up"       , BIT_DIGITAL  , drvInpJoy2 + 7,	"p2 up"},
	{"P2 Down"     , BIT_DIGITAL  , drvInpJoy2 + 6,	"p2 down"},
	{"P2 Left"     , BIT_DIGITAL  , drvInpJoy2 + 5,	"p2 left"},
	{"P2 Right"    , BIT_DIGITAL  , drvInpJoy2 + 4,	"p2 right"},
	{"P2 Button 1" , BIT_DIGITAL  , drvInpJoy2 + 3,	"p2 fire 1"},
//	{"P2 Button 2" , BIT_DIGITAL  , drvInpJoy2 + 2,	"p2 fire 2"},
//	{"P2 Button 3" , BIT_DIGITAL  , drvInpJoy2 + 1,	"p2 fire 3"},

	{"Reset"       , BIT_DIGITAL  , &drvReset     ,	"reset"},
	{"Service"     , BIT_DIGITAL  , drvInpMisc + 7,	"service"},

	{"Dip A"       , BIT_DIPSWITCH, drvInput + 4  ,	"dip"},
	{"Dip B"       , BIT_DIPSWITCH, drvInput + 5  ,	"dip"},
	{"Dip C"       , BIT_DIPSWITCH, drvInput + 6  ,	"dip"},
};

STDINPUTINFO(madgear);

static struct BurnDIPInfo madgearDIPList[] = {
	// Defaults
	{0x10,	0xFF, 0xFF,	0x00, NULL},
	{0x11,	0xFF, 0xFF,	0x00, NULL},
	{0x12,	0xFF, 0xFF,	0x00, NULL},
	
	// DIP A
	{0,		0xFE, 0,	2,	  "Test mode"},
	{0x10,	0x01, 0x80,	0x80, "On"},
	{0x10,	0x01, 0x80,	0x00, "Off"},
	
	// DIP B
	{0,		0xFE, 0,	2,	  "Continue"},
	{0x11,	0x01, 0x01,	0x00, "Yes"},
	{0x11,	0x01, 0x01,	0x01, "No"},
	{0,		0xFE, 0,	2,	  "Screen flip"},
	{0x11,	0x01, 0x02,	0x00, "Off"},
	{0x11,	0x01, 0x02,	0x02, "On"},
	{0,		0xFE, 0,	4,	  "Dificulty level"},
	{0x11,	0x01, 0x0C,	0x00, "Normal"},
	{0x11,	0x01, 0x0C,	0x04, "Easy"},
	{0x11,	0x01, 0x0C,	0x08, "Difficult"},
	{0x11,	0x01, 0x0C,	0x0C, "Very difficult"},
	{0,		0xFE, 0,	3,	  "Play mode, type"},
	{0x11,	0x01, 0x30,	0x00, "1 player only, upright"},
	{0x11,	0x01, 0x30,	0x30, "2 players, upright"},
	{0x11,	0x01, 0x30,	0x20, "2 players, table"},
//	{0x11,	0x01, 0x30,	0x10, "1 player only, upright"},
	{0,		0xFE, 0,	2,	  "Demo sound effector"},
	{0x11,	0x01, 0x40,	0x40, "Off"},
	{0x11,	0x01, 0x40,	0x00, "On"},
	{0,		0xFE, 0,	2,	  "Demo sound B.G.M."},
	{0x11,	0x01, 0x80,	0x80, "Off"},
	{0x11,	0x01, 0x80,	0x00, "On"},

	// DIP C
	{0,		0xFE, 0,	16,	  "Coin 1"},
	{0x12,	0x01, 0xF0,	0x00, "1 coin 1 credit"},
	{0x12,	0x01, 0xF0,	0x10, "1 coin 2 credits"},
	{0x12,	0x01, 0xF0,	0x20, "1 coin 3 credits"},
	{0x12,	0x01, 0xF0,	0x30, "1 coin 4 credits"},
	{0x12,	0x01, 0xF0,	0x40, "1 coin 5 credits"},
	{0x12,	0x01, 0xF0,	0x50, "1 coin 6 credits"},
	{0x12,	0x01, 0xF0,	0x60, "2 coin 1 credit"},
	{0x12,	0x01, 0xF0,	0x70, "2 coin 3 credits"},
	{0x12,	0x01, 0xF0,	0x80, "3 coin 1 credit"},
	{0x12,	0x01, 0xF0,	0x90, "3 coin 2 credits"},
	{0x12,	0x01, 0xF0,	0xA0, "4 coin 1 credit"},
	{0x12,	0x01, 0xF0,	0xB0, "5 coin 1 credit"},
	{0x12,	0x01, 0xF0,	0xC0, "5 coin 3 credits"},
	{0x12,	0x01, 0xF0,	0xD0, "6 coin 1 credit"},
	{0x12,	0x01, 0xF0,	0xE0, "8 coin 3 credits"},
	{0x12,	0x01, 0xFF,	0xF0, "Free play"},
	{0,		0xFE, 0,	15,	  "Coin 2"},
	{0x12,	0x82, 0x0F,	0x00, "1 coin 1 credit"},
	{0x12,	0x00, 0xFF,	0xF0, NULL},
	{0x12,	0x01, 0x0F,	0x01, "1 coin 2 credits"},
	{0x12,	0x01, 0x0F,	0x02, "1 coin 3 credits"},
	{0x12,	0x01, 0x0F,	0x03, "1 coin 4 credits"},
	{0x12,	0x01, 0x0F,	0x04, "1 coin 5 credits"},
	{0x12,	0x01, 0x0F,	0x05, "1 coin 6 credits"},
	{0x12,	0x01, 0x0F,	0x06, "2 coin 1 credit"},
	{0x12,	0x01, 0x0F,	0x07, "2 coin 3 credits"},
	{0x12,	0x01, 0x0F,	0x08, "3 coin 1 credit"},
	{0x12,	0x01, 0x0F,	0x09, "3 coin 2 credits"},
	{0x12,	0x01, 0x0F,	0x0A, "4 coin 1 credit"},
	{0x12,	0x01, 0x0F,	0x0B, "5 coin 1 credit"},
	{0x12,	0x01, 0x0F,	0x0C, "5 coin 3 credits"},
	{0x12,	0x01, 0x0F,	0x0D, "6 coin 1 credit"},
	{0x12,	0x01, 0x0F,	0x0E, "8 coin 3 credits"},
};

STDDIPINFO(madgear);

// ---------------------------------------------------------------------------

static unsigned char *Mem, *MemEnd, *RamStart, *RamEnd;

static unsigned char *Rom01, *Rom02;
static unsigned char *MadGearSpriteROM, *MadGearTextROM, *MadGearFGTileROM, *MadGearBGTileROM;

static unsigned char *Ram01, *Ram02;
static unsigned char *MadGearSpriteRAM, *MadGearTextRAM, *MadGearFGTileRAM, *MadGearBGTileRAM;

static unsigned char* MadGearPalSrc;
static unsigned int* MadGearPalette;


static int MemIndex()
{
	unsigned char* Next; Next = Mem;
	Rom01				= Next; Next += 0x080000;		// 68K program
	Rom02				= Next; Next += 0x010000;		// Z80 program	
	MadGearSpriteROM	= Next; Next += 0x100000;
	MadGearTextROM		= Next; Next += 0x020000;
	MadGearFGTileROM	= Next; Next += 0x080000;
	MadGearBGTileROM	= Next; Next += 0x100000;
	MSM6295ROM			= Next; Next += 0x040000;
	RamStart			= Next;
	Ram01				= Next; Next += 0x010000;		// 68K work RAM
	Ram02				= Next; Next += 0x004000;		// Z80 work RAM
	MadGearSpriteRAM	= Next; Next += 0x000800;
	MadGearTextRAM		= Next; Next += 0x002000;
	MadGearFGTileRAM	= Next; Next += 0x004000;
	MadGearBGTileRAM	= Next; Next += 0x004000;
	MadGearPalSrc		= Next; Next += 0x000800;
	RamEnd				= Next;
	MadGearPalette		= (unsigned int*)Next; Next += 0x000400 * sizeof(int);
	MemEnd				= Next;

	return 0;
}

// ---------------------------------------------------------------------------
//	Graphics
//	Tiles
static int nMadGearBGX, nMadGearBGY, nMadGearFGX, nMadGearFGY;

static unsigned char* pTileData;
static unsigned char* pSpriteData;

static int nTileNumber;
static int nTilePalette;
static int nTileXFlip, nTileYFlip;

static unsigned char* pTileRow;
static unsigned char* pTile;

static int nTileXPos, nTileYPos;
//	Sprites
static unsigned char sprite_flipy_mask = 0x80;
static unsigned char sprite_pri_mask = 0x10;

static int nSpriteAttr,nSpriteYPos,nSpriteXPos,nSpriteFlipX,nSpriteFlipY,nSpriteNumber,nSpritePalette;

// ---------------------------------------------------------------------------
//	Palette

static unsigned char drvRecalcPalette = 0;

inline static unsigned int CalcCol(unsigned short a)
{
	int r, g, b, i;

	// Format is IIII RRRR GGGG BBBB
	i = (a & 0x000F);

	r = (a & 0xF000) >> 8;	  // Red
	r |= r >> 4;
	g = (a & 0x0F00) >> 4;	  // Green
	g |= g >> 4;
	b = (a & 0x00F0);		  // Blue
	b |= b >> 4;

	r *= i; r /= 0x0F;
	g *= i; g /= 0x0F;
	b *= i; b /= 0x0F;

	return BurnHighCol(r, g, b, 0);
}

static void MadGearPaletteUpdate()
{
	int i;
	unsigned short* ps;
	unsigned int* pd;

	for (i = 0, ps = (unsigned short*)MadGearPalSrc, pd = MadGearPalette; i < 0x0400; i++, ps++, pd++) {
		*pd = CalcCol(*ps);
	}

	return;
}

// ---------------------------------------------------------------------------
// Text layer

static unsigned char* MadGearTextAttrib = NULL;

static void MadGearTextExit()
{
	free(MadGearTextAttrib);
	MadGearTextAttrib = NULL;
}

static int MadGearTextInit()
{
	if ((MadGearTextAttrib = (unsigned char*)malloc(0x0800)) == NULL) {
		return 1;
	}
	
	for (int nTile = 0x07FF; nTile >= 0; nTile--) {
		unsigned char* pOrg = MadGearTextROM + nTile * 16;
		unsigned char* pDest = MadGearTextROM + nTile * 64;

		unsigned char n[2];

		bool bOpaque = false;

		for (int y = 7; y >= 0; y--) {

			n[0] = pOrg[y * 2 + 0];
			n[1] = pOrg[y * 2 + 1];

			if (n[0] || n[1]) {
				bOpaque = true;
			}

			pDest[y * 8 + 3] = ((n[0] << 1) & 2) | ((n[0] >> 4) & 1);
			pDest[y * 8 + 2] = ((n[0]     ) & 2) | ((n[0] >> 5) & 1);
			pDest[y * 8 + 1] = ((n[0] >> 1) & 2) | ((n[0] >> 6) & 1);
			pDest[y * 8 + 0] = ((n[0] >> 2) & 2) | ((n[0] >> 7) & 1);
		
			pDest[y * 8 + 7] = ((n[1] << 1) & 2) | ((n[1] >> 4) & 1);
			pDest[y * 8 + 6] = ((n[1]     ) & 2) | ((n[1] >> 5) & 1);
			pDest[y * 8 + 5] = ((n[1] >> 1) & 2) | ((n[1] >> 6) & 1);
			pDest[y * 8 + 4] = ((n[1] >> 2) & 2) | ((n[1] >> 7) & 1);
		}

		if (bOpaque) {
			MadGearTextAttrib[nTile] = 1;
		} else {
			MadGearTextAttrib[nTile] = 0;
		}

	}

	return 0;
}

#define PLOTPIXEL(x) if (pTileData[x] < 3) { ((unsigned short*)pPixel)[x] = (unsigned short)pPalette[pTileData[x]]; }

inline static void MadGearRenderTextTile()
{
	unsigned int* pPalette = MadGearPalette + 0x0300 + (nTilePalette << 2);
	pTileData = MadGearTextROM + (nTileNumber << 6);

	unsigned char* pPixel = pTile;

	int nOffset = 8;

	if (nTileYFlip) {
		pTileData += 7 * 8;
		nOffset = -8;
	}

	for (int y = 0; y < 8; y++, pPixel += nBurnPitch, pTileData += nOffset) {
		PLOTPIXEL(0);
		PLOTPIXEL(1);
		PLOTPIXEL(2);
		PLOTPIXEL(3);
		PLOTPIXEL(4);
		PLOTPIXEL(5);
		PLOTPIXEL(6);
		PLOTPIXEL(7);
	}
}

#undef PLOTPIXEL

static void MadGearTextRender()
{
	unsigned short* pTextRAM = ((unsigned short*)MadGearTextRAM) + 64;

	pTileRow = pBurnDraw;
	
	for (int y = 1; y < 31; y++, pTextRAM += 64, pTileRow += (nBurnPitch << 3)) {
		pTile = pTileRow;
		for (int x = 8; x < 56; x++, pTile += (nBurnBpp << 3)) {
			nTileNumber = pTextRAM[x];
			nTilePalette = nTileNumber >> 12;
			nTileYFlip = nTileNumber & 0x0800;
			nTileNumber &= 0x07FF;
			
			if (MadGearTextAttrib[nTileNumber]) {
				MadGearRenderTextTile();
			}
		}
	}

	return;
}
// ---------------------------------------------------------------------------
// Sprite Layer
/*

void DecodeSprites(unsigned char* pData, int nLen)
{
	unsigned char* pOrg = pData + nLen - 1;
	unsigned char* pDest = pData + ((nLen - 1) << 1);
	
	for (int i = 0; i < nLen; i++, pOrg--, pDest -= 2) {
		pDest[0] = *pOrg & 15;
		pDest[1] = *pOrg >> 4;
	}
	
	return;
}

static int MadGearSpriteInit()

//TODO: Not as clean as the other loaders.

{
		int nRet = 0, nBaseROM = 4;
		
		int nSize;
		
		{
			struct BurnRomInfo ri;

			ri.nType = 0;
			ri.nLen = 0;
			
			BurnDrvGetRomInfo(&ri, nBaseROM);
			
			nSize = ri.nLen;
		}
  
		unsigned char* pTemp = (unsigned char*)malloc(nSize * 8);
		
		for (int i = 0; i < 8; i++) {
			nRet |= BurnLoadRom(pTemp + nSize * i, nBaseROM + 4, 1);
		}

		nSize*=2;
		for (int i = 0; i < nSize; i++) {
			for (int j = 0; j < 8; j++) {
				MadGearSpriteROM[(i << 3) + j]  = ((pTemp[i + nSize * 0] >> (7 - j)) & 1) << 3;
				MadGearSpriteROM[(i << 3) + j] |= ((pTemp[i + nSize * 1] >> (7 - j)) & 1) << 2;
				MadGearSpriteROM[(i << 3) + j] |= ((pTemp[i + nSize * 2] >> (7 - j)) & 1) << 1;
				MadGearSpriteROM[(i << 3) + j] |= ((pTemp[i + nSize * 3] >> (7 - j)) & 1) << 0;
			}
		}

		free(pTemp);
	return 0;
}*/
// ---------------------------------------------------------------------------
// Tile layers

static unsigned char* MadGearFGTileAttrib = NULL;

static void ConvertTileData(unsigned char* pData, int nLen)
{
	unsigned char* pOrg = pData + nLen - 1;
	unsigned char* pDest = pData + ((nLen - 1) << 1);
	
	for (int i = 0; i < nLen; i++, pOrg--, pDest -= 2) {
		pDest[0] = *pOrg & 15;
		pDest[1] = *pOrg >> 4;
	}
	
	return;
}

static void MadGearBGTileExit()
{
	return;
}
static int MadGearBGTileInit()
{
	ConvertTileData(MadGearBGTileROM, 0x040000);
	
	unsigned char n[256];
	unsigned char* pOrg = MadGearBGTileROM;

	for (int nTile = 0; nTile < 0x1000; nTile++, pOrg += 256) {
	
		for (int i = 0; i < 256; i++) {
			n[i] = 0;
		}
		
		// decode colour information
		for (int i = 0; i < 256; i += 4) {			
			for (int j = 0; j < 4; j++) {
				n[i + 0] |= ((pOrg[i + j] >> 0) & 1) << (j ^ 3);
				n[i + 1] |= ((pOrg[i + j] >> 1) & 1) << (j ^ 3);
				n[i + 2] |= ((pOrg[i + j] >> 2) & 1) << (j ^ 3);
				n[i + 3] |= ((pOrg[i + j] >> 3) & 1) << (j ^ 3);
			}
		}

		// Re-arrange the data from 4 8x8 tiles to 1 16x16 tile
		for (int i = 0; i < 64; i++) {
			int j = (i & 0x07) + ((i & 0x38) << 1);
			pOrg[j + 0x00] = n[i + 0x00];
			pOrg[j + 0x80] = n[i + 0x80];
			pOrg[j + 0x08] = n[i + 0x40];
			pOrg[j + 0x88] = n[i + 0xC0];
		}
	}
	return 0;
}

static void MadGearFGTileExit()
{
	free(MadGearFGTileAttrib);
	MadGearFGTileAttrib = NULL;
	
	return;
}

static int MadGearFGTileInit()
{
	ConvertTileData(MadGearFGTileROM, 0x080000);

	unsigned char n[256];
	unsigned char* pOrg = MadGearFGTileROM;

	for (int nTile = 0; nTile < 0x0800; nTile++, pOrg += 256) {
	
		for (int i = 0; i < 256; i++) {
			n[i] = 0;
		}
		
		// decode colour information
		for (int i = 0; i < 256; i += 4) {			
			for (int j = 0; j < 4; j++) {
				n[i + 0] |= ((pOrg[i + j] >> 3) & 1) << (j ^ 3);
				n[i + 1] |= ((pOrg[i + j] >> 2) & 1) << (j ^ 3);
				n[i + 2] |= ((pOrg[i + j] >> 1) & 1) << (j ^ 3);
				n[i + 3] |= ((pOrg[i + j] >> 0) & 1) << (j ^ 3);
			}
		}

		// Re-arrange the data from 4 8x8 tiles to 1 16x16 tile
		for (int i = 0; i < 64; i++) {
			int j = (i & 0x07) + ((i & 0x38) << 1);
			pOrg[j + 0x00] = n[i + 0x00];
			pOrg[j + 0x80] = n[i + 0x40];
			pOrg[j + 0x08] = n[i + 0x80];
			pOrg[j + 0x88] = n[i + 0xC0];
		}
	}
	
	return 0;
}

#define PLOTPIXEL(a, b) if (TESTPIXEL(b)) { ((unsigned short*)pPixel)[a] = (unsigned short)pPalette[pTileData[b]]; }
#define CLIPPIXEL(a, b) if ((nTileXPos + a) >= 0 && (nTileXPos + a) < 384) { PLOTPIXEL(a, b); }

 #define TESTPIXEL(b) 1

inline static void MadGearRenderTileOpaqueNoClip()
{
	unsigned int* pPalette = MadGearPalette + (nTilePalette << 4);

	unsigned char* pPixel = pTile;

	int nOffset = 16;

	if (nTileYFlip) {
		pTileData += 15 * 16;
		nOffset = -16;
	}

	if (nTileXFlip) {
		for (int y = 0; y < 16; y++, pPixel += nBurnPitch, pTileData += nOffset) {
			PLOTPIXEL( 0, 15);
			PLOTPIXEL( 1, 14);
			PLOTPIXEL( 2, 13);
			PLOTPIXEL( 3, 12);
			PLOTPIXEL( 4, 11);
			PLOTPIXEL( 5, 10);
			PLOTPIXEL( 6,  9);
			PLOTPIXEL( 7,  8);
			PLOTPIXEL( 8,  7);
			PLOTPIXEL( 9,  6);
			PLOTPIXEL(10,  5);
			PLOTPIXEL(11,  4);
			PLOTPIXEL(12,  3);
			PLOTPIXEL(13,  2);
			PLOTPIXEL(14,  1);
			PLOTPIXEL(15,  0);
		}
	} else {
		for (int y = 0; y < 16; y++, pPixel += nBurnPitch, pTileData += nOffset) {
			PLOTPIXEL( 0,  0);
			PLOTPIXEL( 1,  1);
			PLOTPIXEL( 2,  2);
			PLOTPIXEL( 3,  3);
			PLOTPIXEL( 4,  4);
			PLOTPIXEL( 5,  5);
			PLOTPIXEL( 6,  6);
			PLOTPIXEL( 7,  7);
			PLOTPIXEL( 8,  8);
			PLOTPIXEL( 9,  9);
			PLOTPIXEL(10, 10);
			PLOTPIXEL(11, 11);
			PLOTPIXEL(12, 12);
			PLOTPIXEL(13, 13);
			PLOTPIXEL(14, 14);
			PLOTPIXEL(15, 15);
		}
	}
}

inline static void MadGearRenderTileOpaqueClip()
{
	unsigned int* pPalette = MadGearPalette + (nTilePalette << 4);

	unsigned char* pPixel = pTile;

	int nOffset = 16;

	if (nTileYFlip) {
		pTileData += 15 * 16;
		nOffset = -16;
	}

	if (nTileXFlip) {
		for (int y = 0; y < 16; y++, pPixel += nBurnPitch, pTileData += nOffset) {

			if ((nTileYPos + y) < 0 || (nTileYPos + y) >= 240) {
				continue;
			}

			CLIPPIXEL( 0, 15);
			CLIPPIXEL( 1, 14);
			CLIPPIXEL( 2, 13);
			CLIPPIXEL( 3, 12);
			CLIPPIXEL( 4, 11);
			CLIPPIXEL( 5, 10);
			CLIPPIXEL( 6,  9);
			CLIPPIXEL( 7,  8);
			CLIPPIXEL( 8,  7);
			CLIPPIXEL( 9,  6);
			CLIPPIXEL(10,  5);
			CLIPPIXEL(11,  4);
			CLIPPIXEL(12,  3);
			CLIPPIXEL(13,  2);
			CLIPPIXEL(14,  1);
			CLIPPIXEL(15,  0);
		}
	} else {
		for (int y = 0; y < 16; y++, pPixel += nBurnPitch, pTileData += nOffset) {

			if ((nTileYPos + y) < 0 || (nTileYPos + y) >= 240) {
				continue;
			}

			CLIPPIXEL( 0,  0);
			CLIPPIXEL( 1,  1);
			CLIPPIXEL( 2,  2);
			CLIPPIXEL( 3,  3);
			CLIPPIXEL( 4,  4);
			CLIPPIXEL( 5,  5);
			CLIPPIXEL( 6,  6);
			CLIPPIXEL( 7,  7);
			CLIPPIXEL( 8,  8);
			CLIPPIXEL( 9,  9);
			CLIPPIXEL(10, 10);
			CLIPPIXEL(11, 11);
			CLIPPIXEL(12, 12);
			CLIPPIXEL(13, 13);
			CLIPPIXEL(14, 14);
			CLIPPIXEL(15, 15);
		}
	}
}

#undef TESTPIXEL

#define TESTPIXEL(b) (pTileData[b] < 15)

inline static void MadGearRenderTileTransNoClip()
{
	unsigned int* pPalette = MadGearPalette + (nTilePalette << 4);

	unsigned char* pPixel = pTile;

	int nOffset = 16;

	if (nTileYFlip) {
		pTileData += 15 * 16;
		nOffset = -16;
	}

	if (nTileXFlip) {
		for (int y = 0; y < 16; y++, pPixel += nBurnPitch, pTileData += nOffset) {
			PLOTPIXEL( 0, 15);
			PLOTPIXEL( 1, 14);
			PLOTPIXEL( 2, 13);
			PLOTPIXEL( 3, 12);
			PLOTPIXEL( 4, 11);
			PLOTPIXEL( 5, 10);
			PLOTPIXEL( 6,  9);
			PLOTPIXEL( 7,  8);
			PLOTPIXEL( 8,  7);
			PLOTPIXEL( 9,  6);
			PLOTPIXEL(10,  5);
			PLOTPIXEL(11,  4);
			PLOTPIXEL(12,  3);
			PLOTPIXEL(13,  2);
			PLOTPIXEL(14,  1);
			PLOTPIXEL(15,  0);
		}
	} else {
		for (int y = 0; y < 16; y++, pPixel += nBurnPitch, pTileData += nOffset) {
			PLOTPIXEL( 0,  0);
			PLOTPIXEL( 1,  1);
			PLOTPIXEL( 2,  2);
			PLOTPIXEL( 3,  3);
			PLOTPIXEL( 4,  4);
			PLOTPIXEL( 5,  5);
			PLOTPIXEL( 6,  6);
			PLOTPIXEL( 7,  7);
			PLOTPIXEL( 8,  8);
			PLOTPIXEL( 9,  9);
			PLOTPIXEL(10, 10);
			PLOTPIXEL(11, 11);
			PLOTPIXEL(12, 12);
			PLOTPIXEL(13, 13);
			PLOTPIXEL(14, 14);
			PLOTPIXEL(15, 15);
		}
	}
}

inline static void MadGearRenderTileTransClip()
{
	unsigned int* pPalette = MadGearPalette + (nTilePalette << 4);

	unsigned char* pPixel = pTile;

	int nOffset = 16;

	if (nTileYFlip) {
		pTileData += 15 * 16;
		nOffset = -16;
	}

	if (nTileXFlip) {
		for (int y = 0; y < 16; y++, pPixel += nBurnPitch, pTileData += nOffset) {

			if ((nTileYPos + y) < 0 || (nTileYPos + y) >= 240) {
				continue;
			}

			CLIPPIXEL( 0, 15);
			CLIPPIXEL( 1, 14);
			CLIPPIXEL( 2, 13);
			CLIPPIXEL( 3, 12);
			CLIPPIXEL( 4, 11);
			CLIPPIXEL( 5, 10);
			CLIPPIXEL( 6,  9);
			CLIPPIXEL( 7,  8);
			CLIPPIXEL( 8,  7);
			CLIPPIXEL( 9,  6);
			CLIPPIXEL(10,  5);
			CLIPPIXEL(11,  4);
			CLIPPIXEL(12,  3);
			CLIPPIXEL(13,  2);
			CLIPPIXEL(14,  1);
			CLIPPIXEL(15,  0);
		}
	} else {
		for (int y = 0; y < 16; y++, pPixel += nBurnPitch, pTileData += nOffset) {

			if ((nTileYPos + y) < 0 || (nTileYPos + y) >= 240) {
				continue;
			}

			CLIPPIXEL( 0,  0);
			CLIPPIXEL( 1,  1);
			CLIPPIXEL( 2,  2);
			CLIPPIXEL( 3,  3);
			CLIPPIXEL( 4,  4);
			CLIPPIXEL( 5,  5);
			CLIPPIXEL( 6,  6);
			CLIPPIXEL( 7,  7);
			CLIPPIXEL( 8,  8);
			CLIPPIXEL( 9,  9);
			CLIPPIXEL(10, 10);
			CLIPPIXEL(11, 11);
			CLIPPIXEL(12, 12);
			CLIPPIXEL(13, 13);
			CLIPPIXEL(14, 14);
			CLIPPIXEL(15, 15);
		}
	}
}

 #undef TESTPIXEL

#undef CLIPPIXEL
#undef PLOTPIXEL


static void MadGearBGTileRender()
{
	int bx = (nMadGearBGX >> 4) + 0;
	int by = (nMadGearBGY >> 4) + 0;
	
	unsigned short* pTileRAM;
	bool bYClip;

	int nTileRowXPos =  -(nMadGearBGX & 15);
	nTileYPos = -(nMadGearBGY & 15);
	
	pTileRow = pBurnDraw + nTileYPos * nBurnPitch + nTileRowXPos * nBurnBpp;

	for (int y = 0; y < 16; y++, nTileYPos += 16, pTileRow += (nBurnPitch << 4)) {
	
		pTileRAM = ((unsigned short*)MadGearBGTileRAM) + ((by + y) & 63);

		nTileXPos = nTileRowXPos;

		pTile = pTileRow;		
		bYClip = (nTileYPos < 0 || nTileYPos > 224);

		for (int x = 0; x < 25; x++, nTileXPos += 16, pTile += (nBurnBpp << 4)) {
			nTileNumber = pTileRAM[((x + bx) & 63) << 5] & 0x01FFF;
			pTileData = MadGearBGTileROM + (nTileNumber << 8);

			nTilePalette = pTileRAM[(((x + bx) & 63) << 5) + 0x0800];
			nTileXFlip = nTilePalette & 0x0020;
			nTileYFlip = nTilePalette & 0x0040;
			nTilePalette &= 0x000F;
//			nTilePalette += 0x0010;
			
			if (bYClip || nTileXPos < 0 || nTileXPos > 368) {
				MadGearRenderTileOpaqueClip();
			} else {
				MadGearRenderTileOpaqueNoClip();
			}
		}
	}

	return;
}

static void MadGearFGTileRender(int nPriority)
{
	int bx = (nMadGearFGX >> 4) + 0;
	int by = (nMadGearFGY >> 4) + 0;
	
	unsigned short* pTileRAM;
	bool bYClip;
	int split=0;
	int nTileRowXPos =  -(nMadGearFGX & 15);
	nTileYPos = -(nMadGearFGY & 15);
	
	pTileRow = pBurnDraw + nTileYPos * nBurnPitch + nTileRowXPos * nBurnBpp;

	for (int y = 0; y < 16; y++, nTileYPos += 16, pTileRow += (nBurnPitch << 4)) {
	
		pTileRAM = ((unsigned short*)MadGearFGTileRAM) + ((by + y) & 63);

		nTileXPos = nTileRowXPos;

		pTile = pTileRow;		
		bYClip = (nTileYPos < 0 || nTileYPos > 224);

		for (int x = 0; x < 25; x++, nTileXPos += 16, pTile += (nBurnBpp << 4)) {
			nTileNumber = pTileRAM[((x + bx) & 63) << 5] & 0x1fff;
			pTileData = MadGearFGTileROM + (nTileNumber << 8);

			nTilePalette = pTileRAM[(((x + bx) & 63) << 5) + 0x0800];
			split = ((nTilePalette & 0x10) >> 4);
			if (split!=nPriority)
				continue;

			nTileXFlip = nTilePalette & 0x0020;
			nTileYFlip = nTilePalette & 0x0040;
			nTilePalette &= 0x000F;
			nTilePalette += 0x0010;
			

			if (bYClip || nTileXPos < 0 || nTileXPos > 368) {
				MadGearRenderTileTransClip();
			} else {
				MadGearRenderTileTransNoClip();
			}
		}
	}

	return;
}



#define TESTPIXEL(b) (pSpriteData[b] < 15)
#define PLOTPIXEL(a, b) if (TESTPIXEL(b)) { ((unsigned short*)pPixel)[a] = (unsigned short)pPalette[pSpriteData[b]]; }
#define CLIPPIXEL(a, b) if ((nSpriteXPos + a) >= 0 && (nSpriteXPos + a) < 384) { PLOTPIXEL(a, b); }

inline static void MadGearRenderSpriteTransClip()
{
	unsigned int* pPalette = MadGearPalette + 0x200 + (nSpritePalette << 4);

	unsigned char* pPixel = pTile;

	int nOffset = 16;

	if (nSpriteFlipY) {
		pTileData += 15 * 16;
		nOffset = -16;
	}

	if (nSpriteFlipX) {
		for (int y = 0; y < 16; y++, pPixel += nBurnPitch, pSpriteData += nOffset) {

			if ((nSpriteYPos + y) < 0 || (nSpriteYPos + y) >= 240) {
				continue;
			}

			CLIPPIXEL( 0, 15);
			CLIPPIXEL( 1, 14);
			CLIPPIXEL( 2, 13);
			CLIPPIXEL( 3, 12);
			CLIPPIXEL( 4, 11);
			CLIPPIXEL( 5, 10);
			CLIPPIXEL( 6,  9);
			CLIPPIXEL( 7,  8);
			CLIPPIXEL( 8,  7);
			CLIPPIXEL( 9,  6);
			CLIPPIXEL(10,  5);
			CLIPPIXEL(11,  4);
			CLIPPIXEL(12,  3);
			CLIPPIXEL(13,  2);
			CLIPPIXEL(14,  1);
			CLIPPIXEL(15,  0);
		}
	} else {
		for (int y = 0; y < 16; y++, pPixel += nBurnPitch, pSpriteData += nOffset) {

			if ((nSpriteYPos + y) < 0 || (nSpriteYPos + y) >= 240) {
				continue;
			}

			CLIPPIXEL( 0,  0);
			CLIPPIXEL( 1,  1);
			CLIPPIXEL( 2,  2);
			CLIPPIXEL( 3,  3);
			CLIPPIXEL( 4,  4);
			CLIPPIXEL( 5,  5);
			CLIPPIXEL( 6,  6);
			CLIPPIXEL( 7,  7);
			CLIPPIXEL( 8,  8);
			CLIPPIXEL( 9,  9);
			CLIPPIXEL(10, 10);
			CLIPPIXEL(11, 11);
			CLIPPIXEL(12, 12);
			CLIPPIXEL(13, 13);
			CLIPPIXEL(14, 14);
			CLIPPIXEL(15, 15);
		}
	}
}


 #undef TESTPIXEL

#undef CLIPPIXEL
#undef PLOTPIXEL

static void MadGearSpriteRender(int nPriority)
{
	unsigned short* pMadgearSpriteRam = ((unsigned short*)MadGearSpriteRAM);

	int offs;
	for(offs=0x400-4;offs>=0;offs-=4)
	{

		nSpriteAttr = pMadgearSpriteRam[offs+1];
		if (sprite_pri_mask)	/* only madgear seems to have this */
		{
			if (nPriority==1 && (nSpriteAttr & sprite_pri_mask)) continue;
			if (nPriority==0 && !(nSpriteAttr & sprite_pri_mask)) continue;
		}
		nSpriteNumber = pMadgearSpriteRam[offs];
		pSpriteData = MadGearSpriteROM + (nSpriteNumber<<8);
		nSpriteXPos = pMadgearSpriteRam[offs+3] & 0x1ff;
		nSpriteYPos = pMadgearSpriteRam[offs+2] & 0x1ff;
		if (nSpriteYPos > 0x100)
			nSpriteYPos -= 0x200;
		nSpriteXPos-=64;
		nSpriteFlipX = nSpriteAttr & 0x20;
		nSpriteFlipY = nSpriteAttr & sprite_flipy_mask;	/* 0x40 for lastduel, 0x80 for madgear */
		nSpritePalette = nSpriteAttr & 0x0f;
		pTile = pBurnDraw + nSpriteYPos * nBurnPitch + nSpriteXPos * nBurnBpp;

		MadGearRenderSpriteTransClip();
/*
		if (flip_screen)
		{
			sx = 496 - sx;
			sy = 240 - sy;
			flipx = !flipx;
			flipy = !flipy;
		}
*/
/*		drawgfx(bitmap,Machine->gfx[0],
				code,
				color,
				flipx,flipy,
				sx,sy,
				cliprect,
				TRANSPARENCY_PEN,15);
*/	}


	return;
}

void mg_decodesprite(int dwGraphic, unsigned char * rBitmap, unsigned char *pbBits)
{
	unsigned long  xbits[16]= 	{ 0, 1, 2, 3, 4, 5, 6, 7,
			16*8+0, 16*8+1, 16*8+2, 16*8+3, 16*8+4, 16*8+5, 16*8+6, 16*8+7 }; // x offset layout
	unsigned long  ybits[16]= { 0,   8,  16,  24,  32,  40,  48,  56, 64,  72,  80,  88,  96, 104, 112, 120 }; // y offset layout
	unsigned long  bpoffsets[4] = { 0x0, 0x100000, 0x200000, 0x300000 }; // start bit of bit planes
	unsigned long  xsize=16; // x size in pixels
	unsigned long  ysize=16; // y size in pixels
	unsigned long  bytespertile=32*8;

	//  The current bit plane.
	unsigned long bCurPlane;

	//  The current pixel row and column in the destination buffer.
	unsigned long dwCurRow;
	unsigned long dwCurCol;

	//  The source bit of interest.
	unsigned long dwSourceBit;

	//  The value of the current pixel in the bitmap.
	unsigned long dwValue;

	//  The offset.
	unsigned long dwOffset = dwGraphic * bytespertile;

	//  Loop through each row and column of the graphic.
	for( dwCurRow = 0 ; dwCurRow < ysize ; ++dwCurRow )
	{
		for( dwCurCol = 0 ; dwCurCol < xsize ; ++dwCurCol )
		{
			//  Initialize the value.
			dwValue = 0;

			//  Loop through each bit plane for the character.
			for( bCurPlane = 0 ; bCurPlane < 4 ; ++bCurPlane )
			{
				//  Shift the value to make room for the new plane.
				dwValue <<= 1;

				//  Calculate the source bit.
				dwSourceBit = dwOffset + bpoffsets[ bCurPlane ] + ybits[ dwCurRow ] +  xbits[ dwCurCol ];

				//  Add the bit from the current bit plane to the 
				//  destination byte.
				dwValue |= ( pbBits[ dwSourceBit >> 3 ] >> (7 - ( dwSourceBit & 7 ))) & 0x01;
				//  Set the pixel value in the bitmap.
				rBitmap[(bytespertile*dwGraphic)+dwCurCol+(dwCurRow*ysize)]= dwValue ;
			}
		}
	}
}



void mg_decodebg(int dwGraphic, unsigned char * rBitmap, unsigned char *pbBits)
{
	unsigned long  xbits[16]= 		{ 0, 1, 2, 3, 16+0, 16+1, 16+2, 16+3,
			32*16+0, 32*16+1, 32*16+2, 32*16+3, 32*16+16+0, 32*16+16+1, 32*16+16+2, 32*16+16+3 };
	unsigned long  ybits[16]= 	{ 0*32, 1*32, 2*32, 3*32, 4*32, 5*32, 6*32, 7*32,
			8*32, 9*32, 10*32, 11*32, 12*32, 13*32, 14*32, 15*32 };
	unsigned long  bpoffsets[4] = { 1*4, 3*4, 0*4, 2*4 }; // start bit of bit planes
	unsigned long  xsize=16; // x size in pixels
	unsigned long  ysize=16; // y size in pixels
	unsigned long  bytespertile=64*16;

	//  The current bit plane.
	unsigned long bCurPlane;

	//  The current pixel row and column in the destination buffer.
	unsigned long dwCurRow;
	unsigned long dwCurCol;

	//  The source bit of interest.
	unsigned long dwSourceBit;

	//  The value of the current pixel in the bitmap.
	unsigned long dwValue;

	//  The offset.
	unsigned long dwOffset = dwGraphic * bytespertile;

	//  Loop through each row and column of the graphic.
	for( dwCurRow = 0 ; dwCurRow < ysize ; ++dwCurRow )
	{
		for( dwCurCol = 0 ; dwCurCol < xsize ; ++dwCurCol )
		{
			//  Initialize the value.
			dwValue = 0;

			//  Loop through each bit plane for the character.
			for( bCurPlane = 0 ; bCurPlane < 4 ; ++bCurPlane )
			{
				//  Shift the value to make room for the new plane.
				dwValue <<= 1;

				//  Calculate the source bit.
				dwSourceBit = dwOffset + bpoffsets[ bCurPlane ] + ybits[ dwCurRow ] +  xbits[ dwCurCol ];

				//  Add the bit from the current bit plane to the 
				//  destination byte.
				dwValue |= ( pbBits[ dwSourceBit >> 3 ] >> (7 - ( dwSourceBit & 7 ))) & 0x01;
				//  Set the pixel value in the bitmap.
				rBitmap[(bytespertile*dwGraphic)+dwCurCol+(dwCurRow*ysize)]= dwValue ;
			}
		}
	}
}


// ---------------------------------------------------------------------------

static int drvLoadROMs()
{
	// 68K program
	if (BurnLoadRom(Rom01 + 0x00001, 0, 2)) {
		return 1;
	}
	if (BurnLoadRom(Rom01 + 0x00000, 1, 2)) {
		return 1;
	}
	if (BurnLoadRom(Rom01 + 0x40001, 2, 2)) {
		return 1;
	}
	if (BurnLoadRom(Rom01 + 0x40000, 3, 2)) {
		return 1;
	}

	
	// Text layer
	if (BurnLoadRom(MadGearTextROM, 12, 1)) {
		return 1;
	}


	// load and decode char roms	
	unsigned char* robocopTemp = (unsigned char*) malloc(0xF00000);
	memset(robocopTemp, 0 , sizeof(robocopTemp));
	int nRet = BurnLoadRom(robocopTemp,12,1);
	if (nRet != 0) return 1;


	//Sprite Layer
	if (BurnLoadRom(robocopTemp, 4, 1)) {
		return 1;
	}

	if (BurnLoadRom(robocopTemp+0x10000, 5, 1)) {
		return 1;
	}
	if (BurnLoadRom(robocopTemp+0x20000, 6, 1)) {
		return 1;
	}
	if (BurnLoadRom(robocopTemp+0x30000, 7, 1)) {
		return 1;
	}
	if (BurnLoadRom(robocopTemp+0x40000, 8, 1)) {
		return 1;
	}
	if (BurnLoadRom(robocopTemp+0x50000, 9, 1)) {
		return 1;
	}
	if (BurnLoadRom(robocopTemp+0x60000, 10, 1)) {
		return 1;
	}
	if (BurnLoadRom(robocopTemp+0x70000, 11, 1)) {
		return 1;
	}
	for (int i =0; i<= 4096; i++) // 3072
	{
		mg_decodesprite(i,MadGearSpriteROM,robocopTemp );
	}

//	if ((MadGearTextAttrib = (unsigned char*)malloc(0x0800)) == NULL) {
//		return 1;
//	}


	memset (robocopTemp,0x00, sizeof (robocopTemp));

	// Foreground layer
	if (BurnLoadRom(MadGearFGTileROM, 13, 1)) {
		return 1;
	}

	memset (robocopTemp,0x00, sizeof (robocopTemp));

	// Background layer
	if (BurnLoadRom(robocopTemp, 14, 1)) 
	
	{
		return 1;
	}

	for (int i =0; i<= 64; i++) // 3072
	{
		mg_decodebg(i,MadGearBGTileROM,robocopTemp );
	}



	free(robocopTemp);

	// Z80 program
	if (BurnLoadRom(Rom02, 15, 1)) {
		return 1;
	}

	// MSM6295 ADPCM data
	if (BurnLoadRom(MSM6295ROM + 0x00000, 16, 1)) {
		return 1;
	}
	if (BurnLoadRom(MSM6295ROM + 0x20000, 17, 1)) {
		return 1;
	}

	return 0;
}

unsigned char __fastcall drvReadByte(unsigned int sekAddress)
{
	switch (sekAddress) {
		case 0xFC4000:
			return ~drvInput[4];
		case 0xFC4001:
			return ~drvInput[5];
		case 0xFC4002:
			return ~drvInput[6];
		case 0xFC4003:
			return ~drvInput[7];
		case 0xFC4004:
			return ~drvInput[0];
		case 0xFC4005:
			return ~drvInput[1];
		case 0xFC4006:
			return ~drvInput[2];
		case 0xFC4007:
			return ~drvInput[3];
		
		default: {
//			printf("Attempt to read byte value of location %x\n", sekAddress);
		}
	}
	
	return 0;
}

unsigned short __fastcall drvReadWord(unsigned int sekAddress)
{
	switch (sekAddress) {
		case 0xFC4000:
			return ~((drvInput[4] << 8) | drvInput[5]);
		case 0xFC4002:
			return ~((drvInput[6] << 8) | drvInput[7]);
		case 0xFC4004:
			return ~((drvInput[0] << 8) | drvInput[1]);
		case 0xFC4006:
			return ~((drvInput[2] << 8) | drvInput[3]);

		default: {
// 			printf("Attempt to read word value of location %x\n", sekAddress);
		}
	}

	return 0;
}

void __fastcall drvWriteByte(unsigned int sekAddress, unsigned char byteValue)
{
//	switch (sekAddress) {
//		default: {
//			printf("Attempt to write byte value %x to location %x\n", byteValue, sekAddress);
//		}
//	}
}

void __fastcall drvWriteWord(unsigned int sekAddress, unsigned short wordValue)
{
	switch (sekAddress) {
		case 0xFD0000:
			nMadGearFGY = wordValue;
			break;
		case 0xFD0002:
			nMadGearFGX = wordValue;
			break;
		case 0xFD0004:
			nMadGearBGY = wordValue;
			break;
		case 0xFD0006:
			nMadGearBGX = wordValue;
			break;		
		
		default: {
//			printf("Attempt to write word value %x to location %x\n", wordValue, sekAddress);
		}
	}
}

static int drvExit()
{
	MadGearTextExit();
//	MadGearSpriteExit();
	MadGearFGTileExit();
	MadGearBGTileExit();
	
	SekExit();

	// Deallocate all used memory
	free(Mem);
	Mem = NULL;
	
	return 0;
}

static void drvDoReset()
{
	SekOpen(0);
	SekReset();
	SekClose();

	return;
}

static int drvInit()
{
	int nLen;

	// Find out how much memory is needed
	Mem = NULL;
	MemIndex();
	nLen = MemEnd - (unsigned char*)0;
	if ((Mem = (unsigned char*)malloc(nLen)) == NULL) {
		return 1;
	}

	memset(Mem, 0, nLen);										   	// blank all memory
	MemIndex();													   	// Index the allocated memory

	// Load the roms into memory
	if (drvLoadROMs()) {
		return 1;
	}

	{
		SekInit(0, 0x68000); // Allocate 1 68000	

		// Map 68000 memory:
	    SekOpen(0);
		SekMapMemory(Rom01,			0x000000, 0x07FFFF, SM_ROM);	// 68K program
		SekMapMemory(MadGearSpriteRAM,	0xFC1800, 0xFC1FFF, SM_RAM);
		SekMapMemory(MadGearTextRAM,	0xFC8000, 0xFC9FFF, SM_RAM);
		SekMapMemory(MadGearFGTileRAM,	0xFD4000, 0xFD7FFF, SM_RAM);
		SekMapMemory(MadGearBGTileRAM,	0xFD8000, 0xFDCFFF, SM_RAM);
		SekMapMemory(MadGearPalSrc,	0xFCC000, 0xFCC7FF, SM_RAM);	// Palette RAM
		SekMapMemory(Ram01,			0xFF0000, 0xFFFFFF, SM_RAM);
		
		SekSetReadWordHandler(0,drvReadWord);
		SekSetWriteWordHandler(0,drvWriteWord);
		SekSetReadByteHandler(0,drvReadByte);
		SekSetWriteByteHandler(0,drvWriteByte);

		SekClose();
	}
	//MadGearSpriteInit();
	MadGearBGTileInit();
	MadGearFGTileInit();
	MadGearTextInit();

	drvDoReset();

	return 0;
}

static int drvScan(int nAction,int *pnMin)
{
	struct BurnArea ba;

	if (pnMin) {						// Return minimum compatible version
		*pnMin = 0x029521;
	}

	if (nAction & ACB_VOLATILE) {		// Scan volatile ram		
		memset(&ba, 0, sizeof(ba));
		ba.Data	  = RamStart;
		ba.nLen	  = RamEnd-RamStart;
		ba.szName = "All Ram";
		BurnAcb(&ba);

		SekScan(nAction);			// Scan 68000
		ZetScan(nAction);			// Scan Z80

//		MSM6295Scan(0, nAction);			// Scan OKIM6295

		// Scan critical driver variables
		SCAN_VAR(drvInput);
		SCAN_VAR(drvInpJoy1);
		SCAN_VAR(drvInpJoy2);
		SCAN_VAR(drvInpMisc);
	}

	return 0;
}

static void drvDraw()
{
	MadGearPaletteUpdate();

	BurnClearScreen();
	MadGearBGTileRender();
	MadGearFGTileRender(0);
	MadGearSpriteRender(0);
	MadGearFGTileRender(1);// we don't know when to draw this one yet.
	MadGearSpriteRender(1);
	MadGearTextRender();
	
	return;
}

inline static int CheckSleep(int)
{
	return 0;
}

static int drvFrame()
{
	int nCyclesTotal[2], nCyclesDone[2];
	
	if (drvReset) {												// Reset machine
		drvDoReset();
	}

	// Compile digital inputs
	drvInput[0] = 0x00;											// Buttons
	drvInput[1] = 0x00;											// Player 1
	drvInput[2] = 0x00;											// Player 2
	for (int i = 0; i < 8; i++) {
		drvInput[0] |= (drvInpJoy1[i] & 1) << i;
		drvInput[1] |= (drvInpJoy2[i] & 1) << i;
		drvInput[2] |= (drvInpMisc[i] & 1) << i;
	}

	if ((drvInput[0] & 0x30) == 0x30) {
		drvInput[0] &= ~0x30;
	}
	if ((drvInput[0] & 0xC0) == 0xC0) {
		drvInput[0] &= ~0xC0;
	}
	if ((drvInput[1] & 0x30) == 0x30) {
		drvInput[1] &= ~0x30;
	}
	if ((drvInput[1] & 0xC0) == 0xC0) {
		drvInput[1] &= ~0xC0;
	}

	nCyclesTotal[0] = 10000000 / 60;
	nCyclesDone[0] = 0;

//	int nSoundBufferPos = 0;
	bool bVBlank = false;
	SekNewFrame();
	SekOpen(0);
	
	for (int i = 0; i < 4; i++) {
    	int nCurrentCPU;
		int nNext, nCyclesSegment;

		// Run 68000

		nCurrentCPU = 0;
		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / 4;

		switch (i) {
			case 0:	
				SekSetIRQLine(6, SEK_IRQSTATUS_AUTO);
				 
				break;
			case 1:
				break;
			case 2:
				SekSetIRQLine(6, SEK_IRQSTATUS_AUTO);
				break;
			case 3: {
				bVBlank = true;
				
				if (pBurnDraw != NULL) {
					drvDraw();												// Draw screen if needed
				}
				
				SekSetIRQLine(5, SEK_IRQSTATUS_AUTO);
				
				break;				
			}
		}

		nCyclesSegment = nNext - nCyclesDone[nCurrentCPU];
		if (bVBlank || (!CheckSleep(nCurrentCPU))) {					// See if this CPU is busywaiting
			nCyclesDone[nCurrentCPU] += SekRun(nCyclesSegment);
		} else {
			nCyclesDone[nCurrentCPU] += nCyclesSegment;
		}

		// Run Z80

/*
		{
			// Render sound segment
			if (pBurnSoundOut) {
				int nSegmentLength = nBurnSoundLen / nInterleave;
				short* pSoundBuf = pBurnSoundOut + (nSoundBufferPos << 1);
				nSoundBufferPos += nSegmentLength;
			}
		}
*/
	
	}

/*
	{
		// Make sure the buffer is entirely filled.
		if (pBurnSoundOut) {
			int nSegmentLength = nBurnSoundLen - nSoundBufferPos;
			short* pSoundBuf = pBurnSoundOut + (nSoundBufferPos << 1);
			if (nSegmentLength) {
			}
		}
	}
*/
	SekClose();

	return 0;
}

// ---------------------------------------------------------------------------
// Rom information
// Mad Gear (US)
static struct BurnRomInfo madgearRomDesc[] = {
	{ "mg_04.rom",	0x020000, 0xB112257D, BRF_ESS | BRF_PRG }, //  0 CPU #0 code
	{ "mg_03.rom",	0x020000, 0xB2672465, BRF_ESS | BRF_PRG }, //  1
	{ "mg_02.rom",	0x020000, 0x9F5EBE16, BRF_ESS | BRF_PRG }, //  2
	{ "mg_01.rom",	0x020000, 0x1CEA2AF0, BRF_ESS | BRF_PRG }, //  3

	{ "mg_m11.rom",	0x010000, 0xEE319A64, BRF_GRA }, //  4 Sprite data
	{ "mg_m07.rom",	0x010000, 0xE5C0B211, BRF_GRA }, //  5
	{ "mg_m12.rom",	0x010000, 0x887EF120, BRF_GRA }, //  6
	{ "mg_m08.rom",	0x010000, 0x59709AA3, BRF_GRA }, //  7
	{ "mg_m13.rom",	0x010000, 0xEAE07DB4, BRF_GRA }, //  8
	{ "mg_m09.rom",	0x010000, 0x40EE83EB, BRF_GRA }, //  9
	{ "mg_m14.rom",	0x010000, 0x21E5424C, BRF_GRA }, // 10
	{ "mg_m10.rom",	0x010000, 0xB64AFB54, BRF_GRA }, // 11

	{ "mg_06.rom",	0x008000, 0x382EE59B, BRF_GRA }, // 12 Text layer
	{ "ls-11",		  0x080000, 0x6BF81C64, BRF_GRA }, // 13 Foreground layer
	{ "ls-12",		  0x040000, 0x6C1B2C6C, BRF_GRA }, // 14 Background layer

	{ "mg_05.rom",	0x010000, 0x2FBFC945, BRF_ESS | BRF_PRG }, // 15 Audio CPU

	{ "ls-06",		  0x020000, 0x88D39A5B, BRF_SND }, // 16 MSM6295 ADPCM data
	{ "ls-05",		  0x020000, 0xB06E03B5, BRF_SND }, // 17

	{ "63s141.14k",	0x000100, 0x7f862e1e, BRF_GRA }, // 18 priority PROM
};

STD_ROM_PICK(madgear);
STD_ROM_FN(madgear);

struct BurnDriverD BurnDrvMadGear = {
	"madgear", NULL, NULL, "1989",
	"Mad Gear (US)\0", "Preliminary driver", "Capcom", "Custom Capcom",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_ORIENTATION_VERTICAL,2,HARDWARE_MISC_MISC,
	NULL, madgearRomInfo, madgearRomName, madgearInputInfo, madgearDIPInfo,
	drvInit, drvExit, drvFrame, NULL, drvScan, &drvRecalcPalette,
	240, 384, 3, 4
};

// Mad Gear (Japan)
static struct BurnRomInfo madgearjRomDesc[] = {
	{ "mdj_04.rom",	0x020000, 0x9EBBEBB1, BRF_ESS | BRF_PRG }, //  0 CPU #0 code
	{ "mdj_03.rom",	0x020000, 0xA5579C2D, BRF_ESS | BRF_PRG }, //  1
	{ "mg_02.rom",	0x020000, 0x9F5EBE16, BRF_ESS | BRF_PRG }, //  2
	{ "mg_01.rom",	0x020000, 0x1CEA2AF0, BRF_ESS | BRF_PRG }, //  3

	{ "mg_m11.rom",	0x010000, 0xEE319A64, BRF_GRA }, //  4 Sprite data
	{ "mg_m07.rom",	0x010000, 0xE5C0B211, BRF_GRA }, //  5
	{ "mg_m12.rom",	0x010000, 0x887EF120, BRF_GRA }, //  6
	{ "mg_m08.rom",	0x010000, 0x59709AA3, BRF_GRA }, //  7
	{ "mg_m13.rom",	0x010000, 0xEAE07DB4, BRF_GRA }, //  8
	{ "mg_m09.rom",	0x010000, 0x40EE83EB, BRF_GRA }, //  9
	{ "mg_m14.rom",	0x010000, 0x21E5424C, BRF_GRA }, // 10
	{ "mg_m10.rom",	0x010000, 0xB64AFB54, BRF_GRA }, // 11

	{ "mg_06.rom",	0x008000, 0x382EE59B, BRF_GRA }, // 12 Text layer
	{ "ls-11",		  0x080000, 0x6BF81C64, BRF_GRA }, // 13 Foreground layer
	{ "ls-12",		  0x040000, 0x6C1B2C6C, BRF_GRA }, // 14 Background layer

	{ "mg_05.rom",	0x010000, 0x2FBFC945, BRF_ESS | BRF_PRG }, // 15 Audio CPU

	{ "ls-06",		  0x020000, 0x88D39A5B, BRF_SND }, // 16 MSM6295 ADPCM data
	{ "ls-05",		  0x020000, 0xB06E03B5, BRF_SND }, // 17

	{ "63s141.14k",	0x000100, 0x7f862e1e, BRF_GRA }, // 18 priority PROM
};

STD_ROM_PICK(madgearj);
STD_ROM_FN(madgearj);

struct BurnDriverD BurnDrvMadGearj = {
	"madgearj", "madgear", NULL, "1989",
	"Mad Gear (Japan)\0", "Preliminary driver", "Capcom", "Custom Capcom",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_ORIENTATION_VERTICAL,2,HARDWARE_MISC_MISC,
	NULL, madgearjRomInfo, madgearjRomName, madgearInputInfo, madgearDIPInfo,
	drvInit, drvExit, drvFrame, NULL, drvScan, &drvRecalcPalette,
	240, 384, 3, 4
};

// Led Storm (US)
static struct BurnRomInfo ledstormRomDesc[] = {
	{ "mdu.04",	    0x020000, 0x7F7F8329, BRF_ESS | BRF_PRG }, //  0 CPU #0 code
	{ "mdu.03",	    0x020000, 0x11FA542F, BRF_ESS | BRF_PRG }, //  1
	{ "mg_02.rom",	0x020000, 0x9F5EBE16, BRF_ESS | BRF_PRG }, //  2
	{ "mg_01.rom",	0x020000, 0x1CEA2AF0, BRF_ESS | BRF_PRG }, //  3

	{ "mg_m11.rom",	0x010000, 0xEE319A64, BRF_GRA }, //  4 Sprite data
	{ "07",	        0x010000, 0x7152B212, BRF_GRA }, //  5
	{ "mg_m12.rom",	0x010000, 0x887EF120, BRF_GRA }, //  6
	{ "08",	        0x010000, 0x72E5D525, BRF_GRA }, //  7
	{ "mg_m13.rom",	0x010000, 0xEAE07DB4, BRF_GRA }, //  8
	{ "09",	        0x010000, 0x7B5175CB, BRF_GRA }, //  9
	{ "mg_m14.rom",	0x010000, 0x21E5424C, BRF_GRA }, // 10
	{ "10",	        0x010000, 0x6DB7CA64, BRF_GRA }, // 11

	{ "06",	        0x008000, 0x54BFDC02, BRF_GRA }, // 12 Text layer
	{ "ls-11",		  0x080000, 0x6BF81C64, BRF_GRA }, // 13 Foreground layer
	{ "ls-12",		  0x040000, 0x6C1B2C6C, BRF_GRA }, // 14 Background layer

	{ "mg_05.rom",	0x010000, 0x2FBFC945, BRF_ESS | BRF_PRG }, // 15 Audio CPU

	{ "ls-06",		  0x020000, 0x88D39A5B, BRF_SND }, // 16 MSM6295 ADPCM data
	{ "ls-05",		  0x020000, 0xB06E03B5, BRF_SND }, // 17

	{ "63s141.14k",	0x000100, 0x7f862e1e, BRF_GRA }, // 18 priority PROM
};

STD_ROM_PICK(ledstorm);
STD_ROM_FN(ledstorm);

struct BurnDriverD BurnDrvLedStorm = {
	"ledstorm", "madgear", NULL, "1988",
	"Led Storm (US)\0", "Preliminary driver", "Capcom", "Custom Capcom",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_ORIENTATION_VERTICAL,2,HARDWARE_MISC_MISC,
	NULL, ledstormRomInfo, ledstormRomName, madgearInputInfo, madgearDIPInfo,
	drvInit, drvExit, drvFrame, NULL, drvScan, &drvRecalcPalette,
	240, 384, 3, 4
};
