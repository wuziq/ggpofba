/*================================================================================================
Generic Tile Rendering Module - Uses the Colour-Depth Independent Image Transfer Method

Supports 8 x 8 and 16 x 16 with or without masking and with full flipping. The functions fully
support varying colour-depths and palette offsets as well as all the usual variables.

Call GenericTilesInit() in the driver Init function to store the drivers screen size for clipping.
This function also calls BurnTransferInit().

Call GenericTilesExit() in the driver Exit function to clear the screen size variables.
Again, this function also calls BurnTransferExit().

Otherwise, use the Transfer code as usual.
================================================================================================*/

#include "tiles_generic.h"

unsigned char* pTileData;
int nScreenWidth, nScreenHeight;

int GenericTilesInit()
{
	int nRet;

	if (BurnDrvGetFlags() & BDF_ORIENTATION_VERTICAL) {
		BurnDrvGetVisibleSize(&nScreenHeight, &nScreenWidth);
	} else {
		BurnDrvGetVisibleSize(&nScreenWidth, &nScreenHeight);
	}

	nRet = BurnTransferInit();

	return nRet;
}

int GenericTilesExit()
{
	nScreenWidth = nScreenHeight = 0;
	BurnTransferExit();

	return 0;
}

//================================================================================================

#define PLOTPIXEL(x, po) pPixel[x] = nPalette | pTileData[x] | po;
#define PLOTPIXEL_FLIPX(x, a, po) pPixel[x] = nPalette | pTileData[a] | po;
#define PLOTPIXEL_MASK(x, mc, po) if (pTileData[x] != mc) {pPixel[x] = nPalette | pTileData[x] | po;}
#define PLOTPIXEL_MASK_FLIPX(x, a, mc, po) if (pTileData[a] != mc) {pPixel[x] = nPalette | pTileData[a] | po;}
#define CLIPPIXEL(x, sx, mx, a) if ((sx + x) >= 0 && (sx + x) < mx) { a; };

/*================================================================================================
8 x 8 Functions
================================================================================================*/

void Render8x8Tile(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile)
{
	unsigned char nPalette = nTilePalette << nColourDepth;
	pTileData = pTile + (nTileNumber << 6);

	unsigned short* pPixel = pTransDraw + (StartY * nScreenWidth) + StartX;

	for (int y = 0; y < 8; y++, pPixel += nScreenWidth, pTileData += 8) {
		PLOTPIXEL(0, nPaletteOffset);
		PLOTPIXEL(1, nPaletteOffset);
		PLOTPIXEL(2, nPaletteOffset);
		PLOTPIXEL(3, nPaletteOffset);
		PLOTPIXEL(4, nPaletteOffset);
		PLOTPIXEL(5, nPaletteOffset);
		PLOTPIXEL(6, nPaletteOffset);
		PLOTPIXEL(7, nPaletteOffset);
	}
}

void Render8x8Tile_Clip(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile)
{
	unsigned char nPalette = nTilePalette << nColourDepth;
	pTileData = pTile + (nTileNumber << 6);

	unsigned short* pPixel = pTransDraw + (StartY * nScreenWidth) + StartX;

	for (int y = 0; y < 8; y++, pPixel += nScreenWidth, pTileData += 8) {
		if ((StartY + y) < 0 || (StartY + y) >= nScreenHeight) {
			continue;
		}

		CLIPPIXEL(0, StartX, nScreenWidth, PLOTPIXEL(0, nPaletteOffset));
		CLIPPIXEL(1, StartX, nScreenWidth, PLOTPIXEL(1, nPaletteOffset));
		CLIPPIXEL(2, StartX, nScreenWidth, PLOTPIXEL(2, nPaletteOffset));
		CLIPPIXEL(3, StartX, nScreenWidth, PLOTPIXEL(3, nPaletteOffset));
		CLIPPIXEL(4, StartX, nScreenWidth, PLOTPIXEL(4, nPaletteOffset));
		CLIPPIXEL(5, StartX, nScreenWidth, PLOTPIXEL(5, nPaletteOffset));
		CLIPPIXEL(6, StartX, nScreenWidth, PLOTPIXEL(6, nPaletteOffset));
		CLIPPIXEL(7, StartX, nScreenWidth, PLOTPIXEL(7, nPaletteOffset));
	}
}

void Render8x8Tile_FlipX(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile)
{
	unsigned char nPalette = nTilePalette << nColourDepth;
	pTileData = pTile + (nTileNumber << 6);

	unsigned short* pPixel = pTransDraw + (StartY * nScreenWidth) + StartX;

	for (int y = 0; y < 8; y++, pPixel += nScreenWidth, pTileData += 8) {
		PLOTPIXEL_FLIPX(7, 0, nPaletteOffset);
		PLOTPIXEL_FLIPX(6, 1, nPaletteOffset);
		PLOTPIXEL_FLIPX(5, 2, nPaletteOffset);
		PLOTPIXEL_FLIPX(4, 3, nPaletteOffset);
		PLOTPIXEL_FLIPX(3, 4, nPaletteOffset);
		PLOTPIXEL_FLIPX(2, 5, nPaletteOffset);
		PLOTPIXEL_FLIPX(1, 6, nPaletteOffset);
		PLOTPIXEL_FLIPX(0, 7, nPaletteOffset);
	}
}

void Render8x8Tile_FlipX_Clip(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile)
{
	unsigned char nPalette = nTilePalette << nColourDepth;
	pTileData = pTile + (nTileNumber << 6);

	unsigned short* pPixel = pTransDraw + (StartY * nScreenWidth) + StartX;

	for (int y = 0; y < 8; y++, pPixel += nScreenWidth, pTileData += 8) {
		if ((StartY + y) < 0 || (StartY + y) >= nScreenHeight) {
			continue;
		}

		CLIPPIXEL(7, StartX, nScreenWidth, PLOTPIXEL_FLIPX(7, 0, nPaletteOffset));
		CLIPPIXEL(6, StartX, nScreenWidth, PLOTPIXEL_FLIPX(6, 1, nPaletteOffset));
		CLIPPIXEL(5, StartX, nScreenWidth, PLOTPIXEL_FLIPX(5, 2, nPaletteOffset));
		CLIPPIXEL(4, StartX, nScreenWidth, PLOTPIXEL_FLIPX(4, 3, nPaletteOffset));
		CLIPPIXEL(3, StartX, nScreenWidth, PLOTPIXEL_FLIPX(3, 4, nPaletteOffset));
		CLIPPIXEL(2, StartX, nScreenWidth, PLOTPIXEL_FLIPX(2, 5, nPaletteOffset));
		CLIPPIXEL(1, StartX, nScreenWidth, PLOTPIXEL_FLIPX(1, 6, nPaletteOffset));
		CLIPPIXEL(0, StartX, nScreenWidth, PLOTPIXEL_FLIPX(0, 7, nPaletteOffset));
	}
}

void Render8x8Tile_FlipY(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile)
{
	unsigned char nPalette = nTilePalette << nColourDepth;
	pTileData = pTile + (nTileNumber << 6);

	unsigned short* pPixel = pTransDraw + ((StartY + 7) * nScreenWidth) + StartX;

	for (int y = 7; y >= 0; y--, pPixel -= nScreenWidth, pTileData += 8) {
		PLOTPIXEL(0, nPaletteOffset);
		PLOTPIXEL(1, nPaletteOffset);
		PLOTPIXEL(2, nPaletteOffset);
		PLOTPIXEL(3, nPaletteOffset);
		PLOTPIXEL(4, nPaletteOffset);
		PLOTPIXEL(5, nPaletteOffset);
		PLOTPIXEL(6, nPaletteOffset);
		PLOTPIXEL(7, nPaletteOffset);
	}
}

void Render8x8Tile_FlipY_Clip(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile)
{
	unsigned char nPalette = nTilePalette << nColourDepth;
	pTileData = pTile + (nTileNumber << 6);

	unsigned short* pPixel = pTransDraw + ((StartY + 7) * nScreenWidth) + StartX;

	for (int y = 7; y >= 0; y--, pPixel -= nScreenWidth, pTileData += 8) {
		if ((StartY + y) < 0 || (StartY + y) >= nScreenHeight) {
			continue;
		}

		CLIPPIXEL(0, StartX, nScreenWidth, PLOTPIXEL(0, nPaletteOffset));
		CLIPPIXEL(1, StartX, nScreenWidth, PLOTPIXEL(1, nPaletteOffset));
		CLIPPIXEL(2, StartX, nScreenWidth, PLOTPIXEL(2, nPaletteOffset));
		CLIPPIXEL(3, StartX, nScreenWidth, PLOTPIXEL(3, nPaletteOffset));
		CLIPPIXEL(4, StartX, nScreenWidth, PLOTPIXEL(4, nPaletteOffset));
		CLIPPIXEL(5, StartX, nScreenWidth, PLOTPIXEL(5, nPaletteOffset));
		CLIPPIXEL(6, StartX, nScreenWidth, PLOTPIXEL(6, nPaletteOffset));
		CLIPPIXEL(7, StartX, nScreenWidth, PLOTPIXEL(7, nPaletteOffset));
	}
}

void Render8x8Tile_FlipXY(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile)
{
	unsigned char nPalette = nTilePalette << nColourDepth;
	pTileData = pTile + (nTileNumber << 6);

	unsigned short* pPixel = pTransDraw + ((StartY + 7) * nScreenWidth) + StartX;

	for (int y = 7; y >= 0; y--, pPixel -= nScreenWidth, pTileData += 8) {
		PLOTPIXEL_FLIPX(7, 0, nPaletteOffset);
		PLOTPIXEL_FLIPX(6, 1, nPaletteOffset);
		PLOTPIXEL_FLIPX(5, 2, nPaletteOffset);
		PLOTPIXEL_FLIPX(4, 3, nPaletteOffset);
		PLOTPIXEL_FLIPX(3, 4, nPaletteOffset);
		PLOTPIXEL_FLIPX(2, 5, nPaletteOffset);
		PLOTPIXEL_FLIPX(1, 6, nPaletteOffset);
		PLOTPIXEL_FLIPX(0, 7, nPaletteOffset);
	}
}

void Render8x8Tile_FlipXY_Clip(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile)
{
	unsigned char nPalette = nTilePalette << nColourDepth;
	pTileData = pTile + (nTileNumber << 6);

	unsigned short* pPixel = pTransDraw + ((StartY + 7) * nScreenWidth) + StartX;

	for (int y = 7; y >= 0; y--, pPixel -= nScreenWidth, pTileData += 8) {
		if ((StartY + y) < 0 || (StartY + y) >= nScreenHeight) {
			continue;
		}

		CLIPPIXEL(7, StartX, nScreenWidth, PLOTPIXEL_FLIPX(7, 0, nPaletteOffset));
		CLIPPIXEL(6, StartX, nScreenWidth, PLOTPIXEL_FLIPX(6, 1, nPaletteOffset));
		CLIPPIXEL(5, StartX, nScreenWidth, PLOTPIXEL_FLIPX(5, 2, nPaletteOffset));
		CLIPPIXEL(4, StartX, nScreenWidth, PLOTPIXEL_FLIPX(4, 3, nPaletteOffset));
		CLIPPIXEL(3, StartX, nScreenWidth, PLOTPIXEL_FLIPX(3, 4, nPaletteOffset));
		CLIPPIXEL(2, StartX, nScreenWidth, PLOTPIXEL_FLIPX(2, 5, nPaletteOffset));
		CLIPPIXEL(1, StartX, nScreenWidth, PLOTPIXEL_FLIPX(1, 6, nPaletteOffset));
		CLIPPIXEL(0, StartX, nScreenWidth, PLOTPIXEL_FLIPX(0, 7, nPaletteOffset));
	}
}

/*================================================================================================
8 x 8 Functions with Masking
================================================================================================*/

void Render8x8Tile_Mask(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile)
{
	unsigned char nPalette = nTilePalette << nColourDepth;
	pTileData = pTile + (nTileNumber << 6);

	unsigned short* pPixel = pTransDraw + (StartY * nScreenWidth) + StartX;

	for (int y = 0; y < 8; y++, pPixel += nScreenWidth, pTileData += 8) {
		PLOTPIXEL_MASK(0, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK(1, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK(2, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK(3, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK(4, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK(5, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK(6, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK(7, nMaskColour, nPaletteOffset);
	}
}

void Render8x8Tile_Mask_Clip(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile)
{
	unsigned char nPalette = nTilePalette << nColourDepth;
	pTileData = pTile + (nTileNumber << 6);

	unsigned short* pPixel = pTransDraw + (StartY * nScreenWidth) + StartX;

	for (int y = 0; y < 8; y++, pPixel += nScreenWidth, pTileData += 8) {
		if ((StartY + y) < 0 || (StartY + y) >= nScreenHeight) {
			continue;
		}

		CLIPPIXEL(0, StartX, nScreenWidth, PLOTPIXEL_MASK(0, nMaskColour, nPaletteOffset));
		CLIPPIXEL(1, StartX, nScreenWidth, PLOTPIXEL_MASK(1, nMaskColour, nPaletteOffset));
		CLIPPIXEL(2, StartX, nScreenWidth, PLOTPIXEL_MASK(2, nMaskColour, nPaletteOffset));
		CLIPPIXEL(3, StartX, nScreenWidth, PLOTPIXEL_MASK(3, nMaskColour, nPaletteOffset));
		CLIPPIXEL(4, StartX, nScreenWidth, PLOTPIXEL_MASK(4, nMaskColour, nPaletteOffset));
		CLIPPIXEL(5, StartX, nScreenWidth, PLOTPIXEL_MASK(5, nMaskColour, nPaletteOffset));
		CLIPPIXEL(6, StartX, nScreenWidth, PLOTPIXEL_MASK(6, nMaskColour, nPaletteOffset));
		CLIPPIXEL(7, StartX, nScreenWidth, PLOTPIXEL_MASK(7, nMaskColour, nPaletteOffset));
	}
}

void Render8x8Tile_Mask_FlipX(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile)
{
	unsigned char nPalette = nTilePalette << nColourDepth;
	pTileData = pTile + (nTileNumber << 6);

	unsigned short* pPixel = pTransDraw + (StartY * nScreenWidth) + StartX;

	for (int y = 0; y < 8; y++, pPixel += nScreenWidth, pTileData += 8) {
		PLOTPIXEL_MASK_FLIPX(7, 0, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX(6, 1, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX(5, 2, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX(4, 3, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX(3, 4, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX(2, 5, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX(1, 6, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX(0, 7, nMaskColour, nPaletteOffset);
	}
}

void Render8x8Tile_Mask_FlipX_Clip(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile)
{
	unsigned char nPalette = nTilePalette << nColourDepth;
	pTileData = pTile + (nTileNumber << 6);

	unsigned short* pPixel = pTransDraw + (StartY * nScreenWidth) + StartX;

	for (int y = 0; y < 8; y++, pPixel += nScreenWidth, pTileData += 8) {
		if ((StartY + y) < 0 || (StartY + y) >= nScreenHeight) {
			continue;
		}

		CLIPPIXEL(7, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX(7, 0, nMaskColour, nPaletteOffset));
		CLIPPIXEL(6, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX(6, 1, nMaskColour, nPaletteOffset));
		CLIPPIXEL(5, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX(5, 2, nMaskColour, nPaletteOffset));
		CLIPPIXEL(4, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX(4, 3, nMaskColour, nPaletteOffset));
		CLIPPIXEL(3, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX(3, 4, nMaskColour, nPaletteOffset));
		CLIPPIXEL(2, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX(2, 5, nMaskColour, nPaletteOffset));
		CLIPPIXEL(1, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX(1, 6, nMaskColour, nPaletteOffset));
		CLIPPIXEL(0, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX(0, 7, nMaskColour, nPaletteOffset));
	}
}

void Render8x8Tile_Mask_FlipY(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile)
{
	unsigned char nPalette = nTilePalette << nColourDepth;
	pTileData = pTile + (nTileNumber << 6);

	unsigned short* pPixel = pTransDraw + ((StartY + 7) * nScreenWidth) + StartX;

	for (int y = 7; y >= 0; y--, pPixel -= nScreenWidth, pTileData += 8) {
		PLOTPIXEL_MASK(0, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK(1, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK(2, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK(3, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK(4, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK(5, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK(6, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK(7, nMaskColour, nPaletteOffset);
	}
}

void Render8x8Tile_Mask_FlipY_Clip(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile)
{
	unsigned char nPalette = nTilePalette << nColourDepth;
	pTileData = pTile + (nTileNumber << 6);

	unsigned short* pPixel = pTransDraw + ((StartY + 7) * nScreenWidth) + StartX;

	for (int y = 7; y >= 0; y--, pPixel -= nScreenWidth, pTileData += 8) {
		if ((StartY + y) < 0 || (StartY + y) >= nScreenHeight) {
			continue;
		}

		CLIPPIXEL(0, StartX, nScreenWidth, PLOTPIXEL_MASK(0, nMaskColour, nPaletteOffset));
		CLIPPIXEL(1, StartX, nScreenWidth, PLOTPIXEL_MASK(1, nMaskColour, nPaletteOffset));
		CLIPPIXEL(2, StartX, nScreenWidth, PLOTPIXEL_MASK(2, nMaskColour, nPaletteOffset));
		CLIPPIXEL(3, StartX, nScreenWidth, PLOTPIXEL_MASK(3, nMaskColour, nPaletteOffset));
		CLIPPIXEL(4, StartX, nScreenWidth, PLOTPIXEL_MASK(4, nMaskColour, nPaletteOffset));
		CLIPPIXEL(5, StartX, nScreenWidth, PLOTPIXEL_MASK(5, nMaskColour, nPaletteOffset));
		CLIPPIXEL(6, StartX, nScreenWidth, PLOTPIXEL_MASK(6, nMaskColour, nPaletteOffset));
		CLIPPIXEL(7, StartX, nScreenWidth, PLOTPIXEL_MASK(7, nMaskColour, nPaletteOffset));
	}
}

void Render8x8Tile_Mask_FlipXY(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile)
{
	unsigned char nPalette = nTilePalette << nColourDepth;
	pTileData = pTile + (nTileNumber << 6);

	unsigned short* pPixel = pTransDraw + ((StartY + 7) * nScreenWidth) + StartX;

	for (int y = 7; y >= 0; y--, pPixel -= nScreenWidth, pTileData += 8) {
		PLOTPIXEL_MASK_FLIPX(7, 0, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX(6, 1, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX(5, 2, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX(4, 3, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX(3, 4, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX(2, 5, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX(1, 6, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX(0, 7, nMaskColour, nPaletteOffset);
	}
}

void Render8x8Tile_Mask_FlipXY_Clip(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile)
{
	unsigned char nPalette = nTilePalette << nColourDepth;
	pTileData = pTile + (nTileNumber << 6);

	unsigned short* pPixel = pTransDraw + ((StartY + 7) * nScreenWidth) + StartX;

	for (int y = 7; y >= 0; y--, pPixel -= nScreenWidth, pTileData += 8) {
		if ((StartY + y) < 0 || (StartY + y) >= nScreenHeight) {
			continue;
		}

		CLIPPIXEL(7, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX(7, 0, nMaskColour, nPaletteOffset));
		CLIPPIXEL(6, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX(6, 1, nMaskColour, nPaletteOffset));
		CLIPPIXEL(5, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX(5, 2, nMaskColour, nPaletteOffset));
		CLIPPIXEL(4, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX(4, 3, nMaskColour, nPaletteOffset));
		CLIPPIXEL(3, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX(3, 4, nMaskColour, nPaletteOffset));
		CLIPPIXEL(2, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX(2, 5, nMaskColour, nPaletteOffset));
		CLIPPIXEL(1, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX(1, 6, nMaskColour, nPaletteOffset));
		CLIPPIXEL(0, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX(0, 7, nMaskColour, nPaletteOffset));
	}
}

/*================================================================================================
16 x 16 Functions
================================================================================================*/

void Render16x16Tile(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile)
{
	unsigned char nPalette = nTilePalette << nColourDepth;
	pTileData = pTile + (nTileNumber << 8);

	unsigned short* pPixel = pTransDraw + (StartY * nScreenWidth) + StartX;

	for (int y = 0; y < 16; y++, pPixel += nScreenWidth, pTileData += 16) {
		PLOTPIXEL( 0, nPaletteOffset);
		PLOTPIXEL( 1, nPaletteOffset);
		PLOTPIXEL( 2, nPaletteOffset);
		PLOTPIXEL( 3, nPaletteOffset);
		PLOTPIXEL( 4, nPaletteOffset);
		PLOTPIXEL( 5, nPaletteOffset);
		PLOTPIXEL( 6, nPaletteOffset);
		PLOTPIXEL( 7, nPaletteOffset);
		PLOTPIXEL( 8, nPaletteOffset);
		PLOTPIXEL( 9, nPaletteOffset);
		PLOTPIXEL(10, nPaletteOffset);
		PLOTPIXEL(11, nPaletteOffset);
		PLOTPIXEL(12, nPaletteOffset);
		PLOTPIXEL(13, nPaletteOffset);
		PLOTPIXEL(14, nPaletteOffset);
		PLOTPIXEL(15, nPaletteOffset);
	}
}

void Render16x16Tile_Clip(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile)
{
	unsigned char nPalette = nTilePalette << nColourDepth;
	pTileData = pTile + (nTileNumber << 8);

	unsigned short* pPixel = pTransDraw + (StartY * nScreenWidth) + StartX;

	for (int y = 0; y < 16; y++, pPixel += nScreenWidth, pTileData += 16) {
		if ((StartY + y) < 0 || (StartY + y) >= nScreenHeight) {
			continue;
		}

		CLIPPIXEL( 0, StartX, nScreenWidth, PLOTPIXEL( 0, nPaletteOffset));
		CLIPPIXEL( 1, StartX, nScreenWidth, PLOTPIXEL( 1, nPaletteOffset));
		CLIPPIXEL( 2, StartX, nScreenWidth, PLOTPIXEL( 2, nPaletteOffset));
		CLIPPIXEL( 3, StartX, nScreenWidth, PLOTPIXEL( 3, nPaletteOffset));
		CLIPPIXEL( 4, StartX, nScreenWidth, PLOTPIXEL( 4, nPaletteOffset));
		CLIPPIXEL( 5, StartX, nScreenWidth, PLOTPIXEL( 5, nPaletteOffset));
		CLIPPIXEL( 6, StartX, nScreenWidth, PLOTPIXEL( 6, nPaletteOffset));
		CLIPPIXEL( 7, StartX, nScreenWidth, PLOTPIXEL( 7, nPaletteOffset));
		CLIPPIXEL( 8, StartX, nScreenWidth, PLOTPIXEL( 8, nPaletteOffset));
		CLIPPIXEL( 9, StartX, nScreenWidth, PLOTPIXEL( 9, nPaletteOffset));
		CLIPPIXEL(10, StartX, nScreenWidth, PLOTPIXEL(10, nPaletteOffset));
		CLIPPIXEL(11, StartX, nScreenWidth, PLOTPIXEL(11, nPaletteOffset));
		CLIPPIXEL(12, StartX, nScreenWidth, PLOTPIXEL(12, nPaletteOffset));
		CLIPPIXEL(13, StartX, nScreenWidth, PLOTPIXEL(13, nPaletteOffset));
		CLIPPIXEL(14, StartX, nScreenWidth, PLOTPIXEL(14, nPaletteOffset));
		CLIPPIXEL(15, StartX, nScreenWidth, PLOTPIXEL(15, nPaletteOffset));
	}
}

void Render16x16Tile_FlipX(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile)
{
	unsigned char nPalette = nTilePalette << nColourDepth;
	pTileData = pTile + (nTileNumber << 8);

	unsigned short* pPixel = pTransDraw + (StartY * nScreenWidth) + StartX;

	for (int y = 0; y < 16; y++, pPixel += nScreenWidth, pTileData += 16) {
		PLOTPIXEL_FLIPX(15,  0, nPaletteOffset);
		PLOTPIXEL_FLIPX(14,  1, nPaletteOffset);
		PLOTPIXEL_FLIPX(13,  2, nPaletteOffset);
		PLOTPIXEL_FLIPX(12,  3, nPaletteOffset);
		PLOTPIXEL_FLIPX(11,  4, nPaletteOffset);
		PLOTPIXEL_FLIPX(10,  5, nPaletteOffset);
		PLOTPIXEL_FLIPX( 9,  6, nPaletteOffset);
		PLOTPIXEL_FLIPX( 8,  7, nPaletteOffset);
		PLOTPIXEL_FLIPX( 7,  8, nPaletteOffset);
		PLOTPIXEL_FLIPX( 6,  9, nPaletteOffset);
		PLOTPIXEL_FLIPX( 5, 10, nPaletteOffset);
		PLOTPIXEL_FLIPX( 4, 11, nPaletteOffset);
		PLOTPIXEL_FLIPX( 3, 12, nPaletteOffset);
		PLOTPIXEL_FLIPX( 2, 13, nPaletteOffset);
		PLOTPIXEL_FLIPX( 1, 14, nPaletteOffset);
		PLOTPIXEL_FLIPX( 0, 15, nPaletteOffset);
	}
}

void Render16x16Tile_FlipX_Clip(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile)
{
	unsigned char nPalette = nTilePalette << nColourDepth;
	pTileData = pTile + (nTileNumber << 8);

	unsigned short* pPixel = pTransDraw + (StartY * nScreenWidth) + StartX;

	for (int y = 0; y < 16; y++, pPixel += nScreenWidth, pTileData += 16) {
		if ((StartY + y) < 0 || (StartY + y) >= nScreenHeight) {
			continue;
		}

		CLIPPIXEL(15, StartX, nScreenWidth, PLOTPIXEL_FLIPX(15,  0, nPaletteOffset));
		CLIPPIXEL(14, StartX, nScreenWidth, PLOTPIXEL_FLIPX(14,  1, nPaletteOffset));
		CLIPPIXEL(13, StartX, nScreenWidth, PLOTPIXEL_FLIPX(13,  2, nPaletteOffset));
		CLIPPIXEL(12, StartX, nScreenWidth, PLOTPIXEL_FLIPX(12,  3, nPaletteOffset));
		CLIPPIXEL(11, StartX, nScreenWidth, PLOTPIXEL_FLIPX(11,  4, nPaletteOffset));
		CLIPPIXEL(10, StartX, nScreenWidth, PLOTPIXEL_FLIPX(10,  5, nPaletteOffset));
		CLIPPIXEL( 9, StartX, nScreenWidth, PLOTPIXEL_FLIPX( 9,  6, nPaletteOffset));
		CLIPPIXEL( 8, StartX, nScreenWidth, PLOTPIXEL_FLIPX( 8,  7, nPaletteOffset));
		CLIPPIXEL( 7, StartX, nScreenWidth, PLOTPIXEL_FLIPX( 7,  8, nPaletteOffset));
		CLIPPIXEL( 6, StartX, nScreenWidth, PLOTPIXEL_FLIPX( 6,  9, nPaletteOffset));
		CLIPPIXEL( 5, StartX, nScreenWidth, PLOTPIXEL_FLIPX( 5, 10, nPaletteOffset));
		CLIPPIXEL( 4, StartX, nScreenWidth, PLOTPIXEL_FLIPX( 4, 11, nPaletteOffset));
		CLIPPIXEL( 3, StartX, nScreenWidth, PLOTPIXEL_FLIPX( 3, 12, nPaletteOffset));
		CLIPPIXEL( 2, StartX, nScreenWidth, PLOTPIXEL_FLIPX( 2, 13, nPaletteOffset));
		CLIPPIXEL( 1, StartX, nScreenWidth, PLOTPIXEL_FLIPX( 1, 14, nPaletteOffset));
		CLIPPIXEL( 0, StartX, nScreenWidth, PLOTPIXEL_FLIPX( 0, 15, nPaletteOffset));
	}
}

void Render16x16Tile_FlipY(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile)
{
	unsigned char nPalette = nTilePalette << nColourDepth;
	pTileData = pTile + (nTileNumber << 8);

	unsigned short* pPixel = pTransDraw + ((StartY + 15) * nScreenWidth) + StartX;

	for (int y = 15; y >= 0; y--, pPixel -= nScreenWidth, pTileData += 16) {
		PLOTPIXEL( 0, nPaletteOffset);
		PLOTPIXEL( 1, nPaletteOffset);
		PLOTPIXEL( 2, nPaletteOffset);
		PLOTPIXEL( 3, nPaletteOffset);
		PLOTPIXEL( 4, nPaletteOffset);
		PLOTPIXEL( 5, nPaletteOffset);
		PLOTPIXEL( 6, nPaletteOffset);
		PLOTPIXEL( 7, nPaletteOffset);
		PLOTPIXEL( 8, nPaletteOffset);
		PLOTPIXEL( 9, nPaletteOffset);
		PLOTPIXEL(10, nPaletteOffset);
		PLOTPIXEL(11, nPaletteOffset);
		PLOTPIXEL(12, nPaletteOffset);
		PLOTPIXEL(13, nPaletteOffset);
		PLOTPIXEL(14, nPaletteOffset);
		PLOTPIXEL(15, nPaletteOffset);
	}
}

void Render16x16Tile_FlipY_Clip(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile)
{
	unsigned char nPalette = nTilePalette << nColourDepth;
	pTileData = pTile + (nTileNumber << 8);

	unsigned short* pPixel = pTransDraw + ((StartY + 15) * nScreenWidth) + StartX;

	for (int y = 15; y >= 0; y--, pPixel -= nScreenWidth, pTileData += 16) {
		if ((StartY + y) < 0 || (StartY + y) >= nScreenHeight) {
			continue;
		}

		CLIPPIXEL( 0, StartX, nScreenWidth, PLOTPIXEL( 0, nPaletteOffset));
		CLIPPIXEL( 1, StartX, nScreenWidth, PLOTPIXEL( 1, nPaletteOffset));
		CLIPPIXEL( 2, StartX, nScreenWidth, PLOTPIXEL( 2, nPaletteOffset));
		CLIPPIXEL( 3, StartX, nScreenWidth, PLOTPIXEL( 3, nPaletteOffset));
		CLIPPIXEL( 4, StartX, nScreenWidth, PLOTPIXEL( 4, nPaletteOffset));
		CLIPPIXEL( 5, StartX, nScreenWidth, PLOTPIXEL( 5, nPaletteOffset));
		CLIPPIXEL( 6, StartX, nScreenWidth, PLOTPIXEL( 6, nPaletteOffset));
		CLIPPIXEL( 7, StartX, nScreenWidth, PLOTPIXEL( 7, nPaletteOffset));
		CLIPPIXEL( 8, StartX, nScreenWidth, PLOTPIXEL( 8, nPaletteOffset));
		CLIPPIXEL( 9, StartX, nScreenWidth, PLOTPIXEL( 9, nPaletteOffset));
		CLIPPIXEL(10, StartX, nScreenWidth, PLOTPIXEL(10, nPaletteOffset));
		CLIPPIXEL(11, StartX, nScreenWidth, PLOTPIXEL(11, nPaletteOffset));
		CLIPPIXEL(12, StartX, nScreenWidth, PLOTPIXEL(12, nPaletteOffset));
		CLIPPIXEL(13, StartX, nScreenWidth, PLOTPIXEL(13, nPaletteOffset));
		CLIPPIXEL(14, StartX, nScreenWidth, PLOTPIXEL(14, nPaletteOffset));
		CLIPPIXEL(15, StartX, nScreenWidth, PLOTPIXEL(15, nPaletteOffset));
	}
}

void Render16x16Tile_FlipXY(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile)
{
	unsigned char nPalette = nTilePalette << nColourDepth;
	pTileData = pTile + (nTileNumber << 8);

	unsigned short* pPixel = pTransDraw + ((StartY + 15) * nScreenWidth) + StartX;

	for (int y = 15; y >= 0; y--, pPixel -= nScreenWidth, pTileData += 16) {
		PLOTPIXEL_FLIPX(15,  0, nPaletteOffset);
		PLOTPIXEL_FLIPX(14,  1, nPaletteOffset);
		PLOTPIXEL_FLIPX(13,  2, nPaletteOffset);
		PLOTPIXEL_FLIPX(12,  3, nPaletteOffset);
		PLOTPIXEL_FLIPX(11,  4, nPaletteOffset);
		PLOTPIXEL_FLIPX(10,  5, nPaletteOffset);
		PLOTPIXEL_FLIPX( 9,  6, nPaletteOffset);
		PLOTPIXEL_FLIPX( 8,  7, nPaletteOffset);
		PLOTPIXEL_FLIPX( 7,  8, nPaletteOffset);
		PLOTPIXEL_FLIPX( 6,  9, nPaletteOffset);
		PLOTPIXEL_FLIPX( 5, 10, nPaletteOffset);
		PLOTPIXEL_FLIPX( 4, 11, nPaletteOffset);
		PLOTPIXEL_FLIPX( 3, 12, nPaletteOffset);
		PLOTPIXEL_FLIPX( 2, 13, nPaletteOffset);
		PLOTPIXEL_FLIPX( 1, 14, nPaletteOffset);
		PLOTPIXEL_FLIPX( 0, 15, nPaletteOffset);
	}
}

void Render16x16Tile_FlipXY_Clip(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile)
{
	unsigned char nPalette = nTilePalette << nColourDepth;
	pTileData = pTile + (nTileNumber << 8);

	unsigned short* pPixel = pTransDraw + ((StartY + 15) * nScreenWidth) + StartX;

	for (int y = 15; y >= 0; y--, pPixel -= nScreenWidth, pTileData += 16) {
		if ((StartY + y) < 0 || (StartY + y) >= nScreenHeight) {
			continue;
		}

		CLIPPIXEL(15, StartX, nScreenWidth, PLOTPIXEL_FLIPX(15,  0, nPaletteOffset));
		CLIPPIXEL(14, StartX, nScreenWidth, PLOTPIXEL_FLIPX(14,  1, nPaletteOffset));
		CLIPPIXEL(13, StartX, nScreenWidth, PLOTPIXEL_FLIPX(13,  2, nPaletteOffset));
		CLIPPIXEL(12, StartX, nScreenWidth, PLOTPIXEL_FLIPX(12,  3, nPaletteOffset));
		CLIPPIXEL(11, StartX, nScreenWidth, PLOTPIXEL_FLIPX(11,  4, nPaletteOffset));
		CLIPPIXEL(10, StartX, nScreenWidth, PLOTPIXEL_FLIPX(10,  5, nPaletteOffset));
		CLIPPIXEL( 9, StartX, nScreenWidth, PLOTPIXEL_FLIPX( 9,  6, nPaletteOffset));
		CLIPPIXEL( 8, StartX, nScreenWidth, PLOTPIXEL_FLIPX( 8,  7, nPaletteOffset));
		CLIPPIXEL( 7, StartX, nScreenWidth, PLOTPIXEL_FLIPX( 7,  8, nPaletteOffset));
		CLIPPIXEL( 6, StartX, nScreenWidth, PLOTPIXEL_FLIPX( 6,  9, nPaletteOffset));
		CLIPPIXEL( 5, StartX, nScreenWidth, PLOTPIXEL_FLIPX( 5, 10, nPaletteOffset));
		CLIPPIXEL( 4, StartX, nScreenWidth, PLOTPIXEL_FLIPX( 4, 11, nPaletteOffset));
		CLIPPIXEL( 3, StartX, nScreenWidth, PLOTPIXEL_FLIPX( 3, 12, nPaletteOffset));
		CLIPPIXEL( 2, StartX, nScreenWidth, PLOTPIXEL_FLIPX( 2, 13, nPaletteOffset));
		CLIPPIXEL( 1, StartX, nScreenWidth, PLOTPIXEL_FLIPX( 1, 14, nPaletteOffset));
		CLIPPIXEL( 0, StartX, nScreenWidth, PLOTPIXEL_FLIPX( 0, 15, nPaletteOffset));
	}
}

/*================================================================================================
16 x 16 Functions with Masking
================================================================================================*/

void Render16x16Tile_Mask(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile)
{
	unsigned char nPalette = nTilePalette << nColourDepth;
	pTileData = pTile + (nTileNumber << 8);

	unsigned short* pPixel = pTransDraw + (StartY * nScreenWidth) + StartX;

	for (int y = 0; y < 16; y++, pPixel += nScreenWidth, pTileData += 16) {
		PLOTPIXEL_MASK( 0, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK( 1, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK( 2, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK( 3, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK( 4, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK( 5, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK( 6, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK( 7, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK( 8, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK( 9, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK(10, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK(11, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK(12, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK(13, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK(14, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK(15, nMaskColour, nPaletteOffset);
	}
}

void Render16x16Tile_Mask_Clip(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile)
{
	unsigned char nPalette = nTilePalette << nColourDepth;
	pTileData = pTile + (nTileNumber << 8);

	unsigned short* pPixel = pTransDraw + (StartY * nScreenWidth) + StartX;

	for (int y = 0; y < 16; y++, pPixel += nScreenWidth, pTileData += 16) {
		if ((StartY + y) < 0 || (StartY + y) >= nScreenHeight) {
			continue;
		}

		CLIPPIXEL( 0, StartX, nScreenWidth, PLOTPIXEL_MASK( 0, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 1, StartX, nScreenWidth, PLOTPIXEL_MASK( 1, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 2, StartX, nScreenWidth, PLOTPIXEL_MASK( 2, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 3, StartX, nScreenWidth, PLOTPIXEL_MASK( 3, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 4, StartX, nScreenWidth, PLOTPIXEL_MASK( 4, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 5, StartX, nScreenWidth, PLOTPIXEL_MASK( 5, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 6, StartX, nScreenWidth, PLOTPIXEL_MASK( 6, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 7, StartX, nScreenWidth, PLOTPIXEL_MASK( 7, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 8, StartX, nScreenWidth, PLOTPIXEL_MASK( 8, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 9, StartX, nScreenWidth, PLOTPIXEL_MASK( 9, nMaskColour, nPaletteOffset));
		CLIPPIXEL(10, StartX, nScreenWidth, PLOTPIXEL_MASK(10, nMaskColour, nPaletteOffset));
		CLIPPIXEL(11, StartX, nScreenWidth, PLOTPIXEL_MASK(11, nMaskColour, nPaletteOffset));
		CLIPPIXEL(12, StartX, nScreenWidth, PLOTPIXEL_MASK(12, nMaskColour, nPaletteOffset));
		CLIPPIXEL(13, StartX, nScreenWidth, PLOTPIXEL_MASK(13, nMaskColour, nPaletteOffset));
		CLIPPIXEL(14, StartX, nScreenWidth, PLOTPIXEL_MASK(14, nMaskColour, nPaletteOffset));
		CLIPPIXEL(15, StartX, nScreenWidth, PLOTPIXEL_MASK(15, nMaskColour, nPaletteOffset));
	}
}

void Render16x16Tile_Mask_FlipX(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile)
{
	unsigned char nPalette = nTilePalette << nColourDepth;
	pTileData = pTile + (nTileNumber << 8);

	unsigned short* pPixel = pTransDraw + (StartY * nScreenWidth) + StartX;

	for (int y = 0; y < 16; y++, pPixel += nScreenWidth, pTileData += 16) {
		PLOTPIXEL_MASK_FLIPX(15,  0, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX(14,  1, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX(13,  2, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX(12,  3, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX(11,  4, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX(10,  5, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX( 9,  6, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX( 8,  7, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX( 7,  8, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX( 6,  9, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX( 5, 10, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX( 4, 11, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX( 3, 12, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX( 2, 13, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX( 1, 14, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX( 0, 15, nMaskColour, nPaletteOffset);
	}
}

void Render16x16Tile_Mask_FlipX_Clip(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile)
{
	unsigned char nPalette = nTilePalette << nColourDepth;
	pTileData = pTile + (nTileNumber << 8);

	unsigned short* pPixel = pTransDraw + (StartY * nScreenWidth) + StartX;

	for (int y = 0; y < 16; y++, pPixel += nScreenWidth, pTileData += 16) {
		if ((StartY + y) < 0 || (StartY + y) >= nScreenHeight) {
			continue;
		}

		CLIPPIXEL(15, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX(15,  0, nMaskColour, nPaletteOffset));
		CLIPPIXEL(14, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX(14,  1, nMaskColour, nPaletteOffset));
		CLIPPIXEL(13, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX(13,  2, nMaskColour, nPaletteOffset));
		CLIPPIXEL(12, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX(12,  3, nMaskColour, nPaletteOffset));
		CLIPPIXEL(11, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX(11,  4, nMaskColour, nPaletteOffset));
		CLIPPIXEL(10, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX(10,  5, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 9, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX( 9,  6, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 8, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX( 8,  7, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 7, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX( 7,  8, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 6, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX( 6,  9, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 5, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX( 5, 10, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 4, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX( 4, 11, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 3, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX( 3, 12, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 2, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX( 2, 13, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 1, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX( 1, 14, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 0, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX( 0, 15, nMaskColour, nPaletteOffset));
	}
}

void Render16x16Tile_Mask_FlipY(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile)
{
	unsigned char nPalette = nTilePalette << nColourDepth;
	pTileData = pTile + (nTileNumber << 8);

	unsigned short* pPixel = pTransDraw + ((StartY + 15) * nScreenWidth) + StartX;

	for (int y = 15; y >= 0; y--, pPixel -= nScreenWidth, pTileData += 16) {
		PLOTPIXEL_MASK( 0, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK( 1, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK( 2, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK( 3, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK( 4, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK( 5, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK( 6, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK( 7, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK( 8, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK( 9, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK(10, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK(11, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK(12, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK(13, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK(14, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK(15, nMaskColour, nPaletteOffset);
	}
}

void Render16x16Tile_Mask_FlipY_Clip(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile)
{
	unsigned char nPalette = nTilePalette << nColourDepth;
	pTileData = pTile + (nTileNumber << 8);

	unsigned short* pPixel = pTransDraw + ((StartY + 15) * nScreenWidth) + StartX;

	for (int y = 15; y >= 0; y--, pPixel -= nScreenWidth, pTileData += 16) {
		if ((StartY + y) < 0 || (StartY + y) >= nScreenHeight) {
			continue;
		}

		CLIPPIXEL( 0, StartX, nScreenWidth, PLOTPIXEL_MASK( 0, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 1, StartX, nScreenWidth, PLOTPIXEL_MASK( 1, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 2, StartX, nScreenWidth, PLOTPIXEL_MASK( 2, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 3, StartX, nScreenWidth, PLOTPIXEL_MASK( 3, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 4, StartX, nScreenWidth, PLOTPIXEL_MASK( 4, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 5, StartX, nScreenWidth, PLOTPIXEL_MASK( 5, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 6, StartX, nScreenWidth, PLOTPIXEL_MASK( 6, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 7, StartX, nScreenWidth, PLOTPIXEL_MASK( 7, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 8, StartX, nScreenWidth, PLOTPIXEL_MASK( 8, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 9, StartX, nScreenWidth, PLOTPIXEL_MASK( 9, nMaskColour, nPaletteOffset));
		CLIPPIXEL(10, StartX, nScreenWidth, PLOTPIXEL_MASK(10, nMaskColour, nPaletteOffset));
		CLIPPIXEL(11, StartX, nScreenWidth, PLOTPIXEL_MASK(11, nMaskColour, nPaletteOffset));
		CLIPPIXEL(12, StartX, nScreenWidth, PLOTPIXEL_MASK(12, nMaskColour, nPaletteOffset));
		CLIPPIXEL(13, StartX, nScreenWidth, PLOTPIXEL_MASK(13, nMaskColour, nPaletteOffset));
		CLIPPIXEL(14, StartX, nScreenWidth, PLOTPIXEL_MASK(14, nMaskColour, nPaletteOffset));
		CLIPPIXEL(15, StartX, nScreenWidth, PLOTPIXEL_MASK(15, nMaskColour, nPaletteOffset));
	}
}

void Render16x16Tile_Mask_FlipXY(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile)
{
	unsigned char nPalette = nTilePalette << nColourDepth;
	pTileData = pTile + (nTileNumber << 8);

	unsigned short* pPixel = pTransDraw + ((StartY + 15) * nScreenWidth) + StartX;

	for (int y = 15; y >= 0; y--, pPixel -= nScreenWidth, pTileData += 16) {
		PLOTPIXEL_MASK_FLIPX(15,  0, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX(14,  1, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX(13,  2, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX(12,  3, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX(11,  4, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX(10,  5, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX( 9,  6, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX( 8,  7, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX( 7,  8, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX( 6,  9, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX( 5, 10, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX( 4, 11, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX( 3, 12, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX( 2, 13, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX( 1, 14, nMaskColour, nPaletteOffset);
		PLOTPIXEL_MASK_FLIPX( 0, 15, nMaskColour, nPaletteOffset);
	}
}

void Render16x16Tile_Mask_FlipXY_Clip(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile)
{
	unsigned char nPalette = nTilePalette << nColourDepth;
	pTileData = pTile + (nTileNumber << 8);

	unsigned short* pPixel = pTransDraw + ((StartY + 15) * nScreenWidth) + StartX;

	for (int y = 15; y >= 0; y--, pPixel -= nScreenWidth, pTileData += 16) {
		if ((StartY + y) < 0 || (StartY + y) >= nScreenHeight) {
			continue;
		}

		CLIPPIXEL(15, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX(15,  0, nMaskColour, nPaletteOffset));
		CLIPPIXEL(14, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX(14,  1, nMaskColour, nPaletteOffset));
		CLIPPIXEL(13, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX(13,  2, nMaskColour, nPaletteOffset));
		CLIPPIXEL(12, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX(12,  3, nMaskColour, nPaletteOffset));
		CLIPPIXEL(11, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX(11,  4, nMaskColour, nPaletteOffset));
		CLIPPIXEL(10, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX(10,  5, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 9, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX( 9,  6, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 8, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX( 8,  7, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 7, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX( 7,  8, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 6, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX( 6,  9, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 5, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX( 5, 10, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 4, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX( 4, 11, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 3, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX( 3, 12, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 2, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX( 2, 13, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 1, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX( 1, 14, nMaskColour, nPaletteOffset));
		CLIPPIXEL( 0, StartX, nScreenWidth, PLOTPIXEL_MASK_FLIPX( 0, 15, nMaskColour, nPaletteOffset));
	}
}

#undef PLOTPIXEL
#undef PLOTPIXEL_FLIPX
#undef PLOTPIXEL_MASK
#undef CLIPPIXEL
