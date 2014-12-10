#include "burnint.h"

extern unsigned char* pTileData;
extern int nScreenWidth, nScreenHeight;

int GenericTilesInit();
int GenericTilesExit();

void Render8x8Tile(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile);
void Render8x8Tile_Clip(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile);
void Render8x8Tile_FlipX(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile);
void Render8x8Tile_FlipX_Clip(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile);
void Render8x8Tile_FlipY(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile);
void Render8x8Tile_FlipY_Clip(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile);
void Render8x8Tile_FlipXY(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile);
void Render8x8Tile_FlipXY_Clip(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile);

void Render8x8Tile_Mask(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile);
void Render8x8Tile_Mask_Clip(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile);
void Render8x8Tile_Mask_FlipX(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile);
void Render8x8Tile_Mask_FlipX_Clip(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile);
void Render8x8Tile_Mask_FlipY(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile);
void Render8x8Tile_Mask_FlipY_Clip(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile);
void Render8x8Tile_Mask_FlipXY(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile);
void Render8x8Tile_Mask_FlipXY_Clip(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile);

void Render16x16Tile(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile);
void Render16x16Tile_Clip(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile);
void Render16x16Tile_FlipX(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile);
void Render16x16Tile_FlipX_Clip(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile);
void Render16x16Tile_FlipY(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile);
void Render16x16Tile_FlipY_Clip(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile);
void Render16x16Tile_FlipXY(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile);
void Render16x16Tile_FlipXY_Clip(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile);

void Render16x16Tile_Mask(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile);
void Render16x16Tile_Mask_Clip(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile);
void Render16x16Tile_Mask_FlipX(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile);
void Render16x16Tile_Mask_FlipX_Clip(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile);
void Render16x16Tile_Mask_FlipY(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile);
void Render16x16Tile_Mask_FlipY_Clip(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile);
void Render16x16Tile_Mask_FlipXY(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile);
void Render16x16Tile_Mask_FlipXY_Clip(int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile);
