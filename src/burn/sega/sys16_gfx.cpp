#include "sys16.h"

int System16SpriteBanks[16];
int System16TileBanks[2];
int System16Page[4];
int System16ScrollX[4] = {0, 0, 0, 0};
int System16ScrollY[4] = {0, 0, 0, 0};
int System16VideoEnable;
int System16ScreenFlip;
int System16SpriteShadow;
int System16ColScroll = 0;
int System16RowScroll = 0;
int System16RoadControl = 0;
int System16RoadColorOffset1 = 0;
int System16RoadColorOffset2 = 0;
int System16RoadColorOffset3 = 0;
int System16RoadXOffset = 0;
int System16RoadPriority = 0;
int System16PaletteEntries = 0;
int System16TilemapColorOffset = 0;

unsigned short *pTempDraw = NULL;

/*====================================================
Decode Functions
====================================================*/

void System16Decode8x8Tiles(unsigned char *pTile, int Num, int offs1, int offs2, int offs3)
{
	int c, y, x, Dat1, Dat2, Dat3, Col;

	for (c = 0; c < Num; c++) {
		for (y = 0; y < 8; y++) {
			Dat1 = System16TempGfx[offs1 + (c * 8) + y];
			Dat2 = System16TempGfx[offs2 + (c * 8) + y];
			Dat3 = System16TempGfx[offs3 + (c * 8) + y];
			for (x = 0; x < 8; x++) {
				Col = 0;
				if (Dat1 & 1) { Col |= 4;}
				if (Dat2 & 1) { Col |= 2;}
				if (Dat3 & 1) { Col |= 1;}
				pTile[(c * 64) + (y * 8) + (7 - x)] = Col;
				Dat1 >>= 1;
				Dat2 >>= 1;
				Dat3 >>= 1;
			}
		}
	}
}

void OutrunDecodeRoad()
{
	for (int y = 0; y < 256 * 2; y++) {
		UINT8 *src = System16TempGfx + ((y & 0xff) * 0x40 + (y >> 8) * 0x8000) % System16RoadRomSize;
		UINT8 *dst = System16Roads + y * 512;

		/* loop over columns */
		for (int x = 0; x < 512; x++)
		{
			dst[x] = (((src[x/8] >> (~x & 7)) & 1) << 0) | (((src[x/8 + 0x4000] >> (~x & 7)) & 1) << 1);

			/* pre-mark road data in the "stripe" area with a high bit */
			if (x >= 256-8 && x < 256 && dst[x] == 3)
				dst[x] |= 4;
		}
	}

	/* set up a dummy road in the last entry */
	memset(System16Roads + 256 * 2 * 512, 3, 512);
}

void HangonDecodeRoad()
{
	int x, y;

	/* loop over rows */
	for (y = 0; y < 256; y++)
	{
		UINT8 *src = System16TempGfx + ((y & 0xff) * 0x40) % System16RoadRomSize;
		UINT8 *dst = System16Roads + y * 512;

		/* loop over columns */
		for (x = 0; x < 512; x++)
			dst[x] = (((src[x/8] >> (~x & 7)) & 1) << 0) | (((src[x/8 + 0x4000] >> (~x & 7)) & 1) << 1);
	}
}

/*====================================================
Tile Layer Rendering
====================================================*/

static void System16ARenderTileLayer(int Page, int PriorityDraw, int Transparent)
{
	int mx, my, Code, Colour, x, y, Priority, TileIndex, ColourOff;
	
	UINT16 EffPage, ActPage = 0, xScroll, yScroll;
	
	xScroll = ((System16TextRam[0xff8 + 1 + (Page * 2)] << 8) | System16TextRam[0xff8 + 0 + (Page * 2)]) & 0x1ff;
	yScroll = ((System16TextRam[0xf24 + 1 + (Page * 2)] << 8) | System16TextRam[0xf24 + 0 + (Page * 2)]) & 0x0ff;
	EffPage = (System16TextRam[0xe9e + 1 - (Page * 2)] << 8) | System16TextRam[0xe9e + 0 - (Page * 2)];
	
	if (System16ScreenFlip) xScroll += 17;
	
	EffPage = ((EffPage >> 4) & 0x0707) | ((EffPage << 4) & 0x7070);
	
	for (my = 0; my < 64; my++) {
		for (mx = 0; mx < 128; mx++) {
			if (my < 32 && mx < 64) ActPage = (EffPage >> 0) & 0x0f;
			if (my < 32 && mx >= 64) ActPage = (EffPage >> 4) & 0x0f;
			if (my >= 32 && mx < 64) ActPage = (EffPage >> 8) & 0x0f;
			if (my >= 32 && mx >= 64) ActPage = (EffPage >> 12) & 0x0f;
			TileIndex = 64 * 32 * 2 * ActPage + ((2 * 64 * my) & 0xfff) + ((2 * mx) & 0x7f);
			int Data = (System16TileRam[TileIndex + 1] << 8) | System16TileRam[TileIndex + 0];
			
			Priority = (Data >> 12) & 1;
			
			if (Priority == PriorityDraw) {
				Code = ((Data >> 1) & 0x1000) | (Data & 0xfff);
				Code &= (System16NumTiles - 1);
				Colour = (Data >> 5) & 0x7f;
			
				x = 8 * mx;
				y = 8 * my;
				
				x -= (200 - xScroll) & 0x3ff;
				y -= yScroll & 0x1ff;
				
				if (x < -200) x += 1024;
				if (y < -288) y += 512;
				
				ColourOff = System16TilemapColorOffset;
				if (Colour >= 0x20) ColourOff = 0x100 | System16TilemapColorOffset;
				if (Colour >= 0x40) ColourOff = 0x200 | System16TilemapColorOffset;
				if (Colour >= 0x60) ColourOff = 0x300 | System16TilemapColorOffset;
			
				if (Transparent) {
					if (x > 7 && x < 312 && y > 7 && y < 216) {
						Render8x8Tile_Mask(Code, x, y, Colour, 3, 0, ColourOff, System16Tiles);
					} else {
						Render8x8Tile_Mask_Clip(Code, x, y, Colour, 3, 0, ColourOff, System16Tiles);
					}
				} else {
					if (x > 7 && x < 312 && y > 7 && y < 216) {
						Render8x8Tile(Code, x, y, Colour, 3, ColourOff, System16Tiles);
					} else {
						Render8x8Tile_Clip(Code, x, y, Colour, 3, ColourOff, System16Tiles);
					}
				}
			}
		}
	}
}

static void System16BRenderTileLayer(int Page, int PriorityDraw, int Transparent)
{
	int mx, my, Code, Colour, x, y, Priority, TileIndex, ColourOff;
	
	UINT16 EffPage, ActPage = 0, xScroll, yScroll;
	
	EffPage = System16Page[Page];
	xScroll = System16ScrollX[Page];
	yScroll = System16ScrollY[Page];
	
	// Need to support this at each row/column
	if (xScroll & 0x8000) xScroll = (System16TextRam[0xf80 + (0x40 * Page) + 1] << 8) | System16TextRam[0xf80 + (0x40 * Page) + 0];
	if (yScroll & 0x8000) yScroll = (System16TextRam[0xf16 + (0x40 * Page) + 1] << 8) | System16TextRam[0xf16 + (0x40 * Page) + 0];
	
	for (my = 0; my < 64; my++) {
		for (mx = 0; mx < 128; mx++) {
			if (my < 32 && mx < 64) ActPage = (EffPage >> 0) & 0x0f;
			if (my < 32 && mx >= 64) ActPage = (EffPage >> 4) & 0x0f;
			if (my >= 32 && mx < 64) ActPage = (EffPage >> 8) & 0x0f;
			if (my >= 32 && mx >= 64) ActPage = (EffPage >> 12) & 0x0f;			
			TileIndex = 64 * 32 * 2 * ActPage + ((2 * 64 * my) & 0xfff) + ((2 * mx) & 0x7f);
			int Data = (System16TileRam[TileIndex + 1] << 8) | System16TileRam[TileIndex + 0];
			
			Priority = (Data >> 15) & 1;
			
			if (Priority == PriorityDraw) {
				Code = Data & 0x1fff;
				Code = System16TileBanks[Code / 0x1000] * 0x1000 + Code % 0x1000;
				Code &= (System16NumTiles - 1);
				Colour = (Data >> 6) & 0x7f;
			
				x = 8 * mx;
				y = 8 * my;
				
				x -= (192 - xScroll) & 0x3ff;
				y -= yScroll & 0x1ff;
				
				if (x < -192) x += 1024;
				if (y < -288) y += 512;
				
				ColourOff = System16TilemapColorOffset;
				if (Colour >= 0x20) ColourOff = 0x100 | System16TilemapColorOffset;
				if (Colour >= 0x40) ColourOff = 0x200 | System16TilemapColorOffset;
				if (Colour >= 0x60) ColourOff = 0x300 | System16TilemapColorOffset;
			
				if (Transparent) {
					if (x > 7 && x < 312 && y > 7 && y < 216) {
						Render8x8Tile_Mask(Code, x, y, Colour, 3, 0, ColourOff, System16Tiles);
					} else {
						Render8x8Tile_Mask_Clip(Code, x, y, Colour, 3, 0, ColourOff, System16Tiles);
					}
				} else {
					if (x > 7 && x < 312 && y > 7 && y < 216) {
						Render8x8Tile(Code, x, y, Colour, 3, ColourOff, System16Tiles);
					} else {
						Render8x8Tile_Clip(Code, x, y, Colour, 3, ColourOff, System16Tiles);
					}
				}
			}
		}
	}
}

static void System16BAltRenderTileLayer(int Page, int PriorityDraw, int Transparent)
{
	int mx, my, Code, Colour, x, y, Priority, TileIndex, ColourOff;
	
	UINT16 EffPage, ActPage = 0, xScroll, yScroll;
	
	EffPage = System16Page[Page];
	xScroll = System16ScrollX[Page];
	yScroll = System16ScrollY[Page];
	
	// Need to support this at each row/column
	if (xScroll & 0x8000) xScroll = (System16TextRam[0xf80 + (0x40 * Page) + 1] << 8) | System16TextRam[0xf80 + (0x40 * Page) + 0];
	if (yScroll & 0x8000) yScroll = (System16TextRam[0xf16 + (0x40 * Page) + 1] << 8) | System16TextRam[0xf16 + (0x40 * Page) + 0];
	
	for (my = 0; my < 64; my++) {
		for (mx = 0; mx < 128; mx++) {
			if (my < 32 && mx < 64) ActPage = (EffPage >> 0) & 0x0f;
			if (my < 32 && mx >= 64) ActPage = (EffPage >> 4) & 0x0f;
			if (my >= 32 && mx < 64) ActPage = (EffPage >> 8) & 0x0f;
			if (my >= 32 && mx >= 64) ActPage = (EffPage >> 12) & 0x0f;
			TileIndex = 64 * 32 * 2 * ActPage + ((2 * 64 * my) & 0xfff) + ((2 * mx) & 0x7f);
			int Data = (System16TileRam[TileIndex + 1] << 8) | System16TileRam[TileIndex + 0];
			
			Priority = (Data >> 15) & 1;
			
			if (Priority == PriorityDraw) {
				Code = Data & 0x1fff;
				Code = System16TileBanks[Code / 0x1000] * 0x1000 + Code % 0x1000;
				Code &= (System16NumTiles - 1);
				Colour = (Data >> 5) & 0x7f;
						
				x = 8 * mx;
				y = 8 * my;
				
				x -= (192 - xScroll) & 0x3ff;
				y -= yScroll & 0x1ff;
				
				if (x < -192) x += 1024;
				if (y < -288) y += 512;
				
				ColourOff = System16TilemapColorOffset;
				if (Colour >= 0x20) ColourOff = 0x100 | System16TilemapColorOffset;
				if (Colour >= 0x40) ColourOff = 0x200 | System16TilemapColorOffset;
				if (Colour >= 0x60) ColourOff = 0x300 | System16TilemapColorOffset;
			
				if (Transparent) {
					if (x > 7 && x < 312 && y > 7 && y < 216) {
						Render8x8Tile_Mask(Code, x, y, Colour, 3, 0, ColourOff, System16Tiles);
					} else {
						Render8x8Tile_Mask_Clip(Code, x, y, Colour, 3, 0, ColourOff, System16Tiles);
					}
				} else {
					if (x > 7 && x < 312 && y > 7 && y < 216) {
						Render8x8Tile(Code, x, y, Colour, 3, ColourOff, System16Tiles);
					} else {
						Render8x8Tile_Clip(Code, x, y, Colour, 3, ColourOff, System16Tiles);
					}
				}
			}
		}
	}
}

static void System16ARenderTextLayer(int PriorityDraw)
{
	int mx, my, Code, Colour, x, y, Priority, TileIndex = 0;

	for (my = 0; my < 32; my++) {
		for (mx = 0; mx < 64; mx++) { 
			Code = (System16TextRam[TileIndex + 1] << 8) | System16TextRam[TileIndex + 0];
			
			Priority = (Code >> 11) & 1;
			
			if (Priority == PriorityDraw) {
				Colour = (Code >> 8) & 0x07;
				Code &= 0xff;
			
				x = 8 * mx;
				y = 8 * my;
				
				x -= 192;
			
				if (x > 7 && x < 312 && y > 7 && y < 216) {
					Render8x8Tile_Mask(Code, x, y, Colour, 3, 0, System16TilemapColorOffset, System16Tiles);
				} else {
					Render8x8Tile_Mask_Clip(Code, x, y, Colour, 3, 0, System16TilemapColorOffset, System16Tiles);
				}
			}

			TileIndex +=2 ;
		}
	}
}

static void System16BRenderTextLayer(int PriorityDraw)
{
	int mx, my, Code, Colour, x, y, Priority, TileIndex = 0;

	for (my = 0; my < 32; my++) {
		for (mx = 0; mx < 64; mx++) {
			Code = (System16TextRam[TileIndex + 1] << 8) | System16TextRam[TileIndex + 0];
			Priority = (Code >> 15) & 1;
			
			if (Priority == PriorityDraw) {			
				Colour = (Code >> 9) & 0x07;
				Code &= 0x1ff;
			
				Code += System16TileBanks[0] * 0x1000;
				
				Code &= (System16NumTiles - 1);
			
				x = 8 * mx;
				y = 8 * my;
			
				x -= 192;

				if (x > 7 && x < 312 && y > 7 && y < 216) {
					Render8x8Tile_Mask(Code, x, y, Colour, 3, 0, System16TilemapColorOffset, System16Tiles);
				} else {
					Render8x8Tile_Mask_Clip(Code, x, y, Colour, 3, 0, System16TilemapColorOffset, System16Tiles);
				}
			}

			TileIndex +=2 ;
		}
	}
}

static void System16BAltRenderTextLayer(int PriorityDraw)
{
	int mx, my, Code, Colour, x, y, Priority, TileIndex = 0;

	for (my = 0; my < 32; my++) {
		for (mx = 0; mx < 64; mx++) {
			Code = (System16TextRam[TileIndex + 1] << 8) | System16TextRam[TileIndex + 0];
			Priority = (Code >> 15) & 1;
			
			if (Priority == PriorityDraw) {			
				Colour = (Code >> 8) & 0x07;
				Code &= 0xff;
			
				Code += System16TileBanks[0] * 0x1000;
				
				Code &= (System16NumTiles - 1);
			
				x = 8 * mx;
				y = 8 * my;
			
				x -= 192;

				if (x > 7 && x < 312 && y > 7 && y < 216) {
					Render8x8Tile_Mask(Code, x, y, Colour, 3, 0, System16TilemapColorOffset, System16Tiles);
				} else {
					Render8x8Tile_Mask_Clip(Code, x, y, Colour, 3, 0, System16TilemapColorOffset, System16Tiles);
				}
			}

			TileIndex +=2 ;
		}
	}
}

/*====================================================
Sprite Rendering
====================================================*/

inline static void System16DrawPixel(int x, int pix, int colour, unsigned short* pPixel)
{
	if (x >= 0 && x <= 319 && pix != 0 && pix != 15) {
		if (colour == (0x3f << 4)) {
			pPixel[x] &= (System16PaletteEntries - 1);
			pPixel[x] += ((((System16PaletteRam[pPixel[x] + 1] << 8) | System16PaletteRam[pPixel[x] + 0]) & 0x8000) ? (System16PaletteEntries * 2) : System16PaletteEntries);
		} else {
			pPixel[x] = (pix | colour | 0x400) & (System16PaletteEntries - 1);
		}
	}
}

static void System16ARenderSpriteLayer(int Priority)
{
	UINT8 numbanks = System16SpriteRomSize / 0x10000;

	const UINT16 *spritebase = (const UINT16*)System16Sprites;
	UINT16 *data;
		
	for (data = (UINT16*)System16SpriteRam; data < (UINT16*)System16SpriteRam + System16SpriteRamSize / 2; data += 8) {
		if ((data[0] >> 8) > 0xf0) break;
		int sprpri  = 1 << ((data[4] >> 0) & 0x3);
				
#if 1 && defined FBA_DEBUG
		if (sprpri != 1 && sprpri != 2 && sprpri != 4 && sprpri != 8) bprintf(PRINT_IMPORTANT, _T("Unknown Sprite Priority - %x\n"), sprpri);
#endif
		
		if (sprpri != Priority) continue;
		
		int bottom  = (data[0] >> 8) + 1;
		int top     = (data[0] & 0xff) + 1;
		int xpos    = (data[1] & 0x1ff) - 0xbd;
		int pitch   = (INT16)data[2];
		UINT16 addr = data[3];
		int color   = ((data[4] >> 8) & 0x3f) << 4;
		int bank    = System16SpriteBanks[(data[4] >> 4) & 0x7];
		const UINT16 *spritedata;
		int x, y, pix, xdelta = 1;
		
		/* initialize the end address to the start address */
		data[7] = addr;

		/* if hidden, or top greater than/equal to bottom, or invalid bank, punt */
		if ((top >= bottom) || bank == 255)
			continue;

		/* clamp to within the memory region size */
		if (numbanks)
			bank %= numbanks;
		spritedata = spritebase + 0x8000 * bank;
		
		if (!System16ScreenFlip) {
			for (y = top; y < bottom; y++) {
				addr += pitch;
				if (y >= 0 && y <= 223) {
					unsigned short* pPixel = pTransDraw + (y * 320);
					if (!(addr & 0x8000)) {
						/* start at the word before because we preincrement below */
						data[7] = addr - 1;
						for (x = xpos; ((xpos - x) & 0x1ff) != 1; ) {
							UINT16 pixels = spritedata[++data[7] & 0x7fff];
					
							pix = (pixels >> 12) & 0xf; System16DrawPixel(x, pix, color, pPixel); x += xdelta;
							pix = (pixels >>  8) & 0xf; System16DrawPixel(x, pix, color, pPixel); x += xdelta;
							pix = (pixels >>  4) & 0xf; System16DrawPixel(x, pix, color, pPixel); x += xdelta;
							pix = (pixels >>  0) & 0xf; System16DrawPixel(x, pix, color, pPixel); x += xdelta;
					
							if (pix == 15) break;
						}
					} else {
						data[7] = addr + 1;
						for (x = xpos; ((xpos - x) & 0x1ff) != 1; ) {
							UINT16 pixels = spritedata[--data[7] & 0x7fff];

							/* draw four pixels */
							pix = (pixels >>  0) & 0xf; System16DrawPixel(x, pix, color, pPixel); x += xdelta;
							pix = (pixels >>  4) & 0xf; System16DrawPixel(x, pix, color, pPixel); x += xdelta;
							pix = (pixels >>  8) & 0xf; System16DrawPixel(x, pix, color, pPixel); x += xdelta;
							pix = (pixels >> 12) & 0xf; System16DrawPixel(x, pix, color, pPixel); x += xdelta;

							/* stop if the last pixel in the group was 0xf */
							if (pix == 15) break;
						}
					}
				}
			}
		} else {
			for (y = bottom - 3; y > top - 3; y--) {
				addr += pitch;
				if (y >= 0 && y <= 223) {
					unsigned short* pPixel = pTransDraw + (y * 320);
					if (!(addr & 0x8000)) {
						/* start at the word before because we preincrement below */
						data[7] = addr - 1;
						for (x = xpos; ((xpos - x) & 0x1ff) != 1; ) {
							UINT16 pixels = spritedata[++data[7] & 0x7fff];
					
							pix = (pixels >> 12) & 0xf; System16DrawPixel(x, pix, color, pPixel); x += xdelta;
							pix = (pixels >>  8) & 0xf; System16DrawPixel(x, pix, color, pPixel); x += xdelta;
							pix = (pixels >>  4) & 0xf; System16DrawPixel(x, pix, color, pPixel); x += xdelta;
							pix = (pixels >>  0) & 0xf; System16DrawPixel(x, pix, color, pPixel); x += xdelta;
					
							if (pix == 15) break;
						}
					} else {
						data[7] = addr + 1;
						for (x = xpos; ((xpos - x) & 0x1ff) != 1; ) {
							UINT16 pixels = spritedata[--data[7] & 0x7fff];

							/* draw four pixels */
							pix = (pixels >>  0) & 0xf; System16DrawPixel(x, pix, color, pPixel); x += xdelta;
							pix = (pixels >>  4) & 0xf; System16DrawPixel(x, pix, color, pPixel); x += xdelta;
							pix = (pixels >>  8) & 0xf; System16DrawPixel(x, pix, color, pPixel); x += xdelta;
							pix = (pixels >> 12) & 0xf; System16DrawPixel(x, pix, color, pPixel); x += xdelta;

							/* stop if the last pixel in the group was 0xf */
							if (pix == 15) break;
						}
					}
				}
			}
		}
	}
}

static void System16BRenderSpriteLayer(int Priority)
{
	UINT8 numbanks;
	const UINT16 *spritebase;
  	UINT16 *data;

	spritebase = (const UINT16 *)System16Sprites;
	numbanks = System16SpriteRomSize / 0x20000;

	for (data = (UINT16*)System16SpriteRam; data < (UINT16*)System16SpriteRam + System16SpriteRamSize / 2; data += 8) {
		if (data[2] & 0x8000) break;
		int sprpri  = 1 << ((data[4] >> 6) & 0x3);
				
#if 1 && defined FBA_DEBUG
		if (sprpri != 1 && sprpri != 2 && sprpri != 4 && sprpri != 8) bprintf(PRINT_IMPORTANT, _T("Unknown Sprite Priority - %x\n"), sprpri);
#endif
		
		if (sprpri != Priority) continue;
		
		int bottom  = data[0] >> 8;
		int top     = data[0] & 0xff;
		int xpos    = (data[1] & 0x1ff) - 0xb8;
		int hide    = data[2] & 0x4000;
		int flip    = data[2] & 0x100;
		int pitch   = (INT8)(data[2] & 0xff);
		UINT16 addr = data[3];
		int bank    = System16SpriteBanks[(data[4] >> 8) & 0xf];
		int color   = ((data[4] & 0x3f) << 4);
		int vzoom   = (data[5] >> 5) & 0x1f;
		int hzoom   = data[5] & 0x1f;
		const UINT16 *spritedata;
		int x, y, pix, xdelta = 1;

		/* initialize the end address to the start address */
		data[7] = addr;

		/* if hidden, or top greater than/equal to bottom, or invalid bank, punt */
		if (hide || (top >= bottom) || bank == 255)
			continue;

		/* clamp to within the memory region size */
		if (numbanks)
			bank %= numbanks;
		spritedata = spritebase + 0x10000 * bank;

		/* reset the yzoom counter */
		data[5] &= 0x03ff;
		
		if (!System16ScreenFlip) {
			/* loop from top to bottom */
			for (y = top; y < bottom; y++) {
				/* advance a row */
				addr += pitch;

				/* accumulate zoom factors; if we carry into the high bit, skip an extra row */
				data[5] += vzoom << 10;
				if (data[5] & 0x8000) {
					addr += pitch;
					data[5] &= ~0x8000;
				}

				/* skip drawing if not within the cliprect */
				if (y >= 0 && y <= 223) {
					unsigned short* pPixel = pTransDraw + (y * 320);
					int xacc;

					/* compute the initial X zoom accumulator; this is verified on the real PCB */
					xacc = 4 * hzoom;

					/* non-flipped case */
					if (!flip) {
						/* start at the word before because we preincrement below */
						data[7] = addr - 1;
						for (x = xpos; ((xpos - x) & 0x1ff) != 1; ) {
							UINT16 pixels = spritedata[++data[7]];

							/* draw four pixels */
							pix = (pixels >> 12) & 0xf; xacc = (xacc & 0x3f) + hzoom; if (xacc < 0x40) { System16DrawPixel(x, pix, color, pPixel); x += xdelta; }
							pix = (pixels >>  8) & 0xf; xacc = (xacc & 0x3f) + hzoom; if (xacc < 0x40) { System16DrawPixel(x, pix, color, pPixel); x += xdelta; }
							pix = (pixels >>  4) & 0xf; xacc = (xacc & 0x3f) + hzoom; if (xacc < 0x40) { System16DrawPixel(x, pix, color, pPixel); x += xdelta; }
							pix = (pixels >>  0) & 0xf; xacc = (xacc & 0x3f) + hzoom; if (xacc < 0x40) { System16DrawPixel(x, pix, color, pPixel); x += xdelta; }

							/* stop if the last pixel in the group was 0xf */
							if (pix == 15) break;
						}
					} else {
						/* start at the word after because we predecrement below */
						data[7] = addr + 1;
						for (x = xpos; ((xpos - x) & 0x1ff) != 1; ) {
							UINT16 pixels = spritedata[--data[7]];

							/* draw four pixels */
							pix = (pixels >>  0) & 0xf; xacc = (xacc & 0x3f) + hzoom; if (xacc < 0x40) { System16DrawPixel(x, pix, color, pPixel); x += xdelta; }
							pix = (pixels >>  4) & 0xf; xacc = (xacc & 0x3f) + hzoom; if (xacc < 0x40) { System16DrawPixel(x, pix, color, pPixel); x += xdelta; }
							pix = (pixels >>  8) & 0xf; xacc = (xacc & 0x3f) + hzoom; if (xacc < 0x40) { System16DrawPixel(x, pix, color, pPixel); x += xdelta; }
							pix = (pixels >> 12) & 0xf; xacc = (xacc & 0x3f) + hzoom; if (xacc < 0x40) { System16DrawPixel(x, pix, color, pPixel); x += xdelta; }

							/* stop if the last pixel in the group was 0xf */
							if (pix == 15) break;
						}
					}
				}
			}
		} else {
			/* loop from top to bottom */
			for (y = bottom; y > top; y--) {
				/* advance a row */
				addr += pitch;

				/* accumulate zoom factors; if we carry into the high bit, skip an extra row */
				data[5] += vzoom << 10;
				if (data[5] & 0x8000) {
					addr += pitch;
					data[5] &= ~0x8000;
				}

				/* skip drawing if not within the cliprect */
				if (y >= 0 && y <= 223) {
					unsigned short* pPixel = pTransDraw + (y * 320);
					int xacc;

					/* compute the initial X zoom accumulator; this is verified on the real PCB */
					xacc = 4 * hzoom;

					/* non-flipped case */
					if (!flip) {
						/* start at the word before because we preincrement below */
						data[7] = addr - 1;
						for (x = xpos; ((xpos - x) & 0x1ff) != 1; ) {
							UINT16 pixels = spritedata[++data[7]];

							/* draw four pixels */
							pix = (pixels >> 12) & 0xf; xacc = (xacc & 0x3f) + hzoom; if (xacc < 0x40) { System16DrawPixel(x, pix, color, pPixel); x += xdelta; }
							pix = (pixels >>  8) & 0xf; xacc = (xacc & 0x3f) + hzoom; if (xacc < 0x40) { System16DrawPixel(x, pix, color, pPixel); x += xdelta; }
							pix = (pixels >>  4) & 0xf; xacc = (xacc & 0x3f) + hzoom; if (xacc < 0x40) { System16DrawPixel(x, pix, color, pPixel); x += xdelta; }
							pix = (pixels >>  0) & 0xf; xacc = (xacc & 0x3f) + hzoom; if (xacc < 0x40) { System16DrawPixel(x, pix, color, pPixel); x += xdelta; }

							/* stop if the last pixel in the group was 0xf */
							if (pix == 15) break;
						}
					} else {
						/* start at the word after because we predecrement below */
						data[7] = addr + 1;
						for (x = xpos; ((xpos - x) & 0x1ff) != 1; ) {
							UINT16 pixels = spritedata[--data[7]];

							/* draw four pixels */
							pix = (pixels >>  0) & 0xf; xacc = (xacc & 0x3f) + hzoom; if (xacc < 0x40) { System16DrawPixel(x, pix, color, pPixel); x += xdelta; }
							pix = (pixels >>  4) & 0xf; xacc = (xacc & 0x3f) + hzoom; if (xacc < 0x40) { System16DrawPixel(x, pix, color, pPixel); x += xdelta; }
							pix = (pixels >>  8) & 0xf; xacc = (xacc & 0x3f) + hzoom; if (xacc < 0x40) { System16DrawPixel(x, pix, color, pPixel); x += xdelta; }
							pix = (pixels >> 12) & 0xf; xacc = (xacc & 0x3f) + hzoom; if (xacc < 0x40) { System16DrawPixel(x, pix, color, pPixel); x += xdelta; }

							/* stop if the last pixel in the group was 0xf */
							if (pix == 15) break;
						}
					}
				}
			}

		}
	}
}

inline static void OutrunDrawPixel(int x, int pix, int colour, int shadow, unsigned short* pPixel)
{
	if (x >= 0 && x <= 319 && pix != 0 && pix != 15) {
		if (shadow && pix == 0xa) {
			pPixel[x] &= (System16PaletteEntries - 1);
			pPixel[x] += ((((System16PaletteRam[pPixel[x] + 1] << 8) | System16PaletteRam[pPixel[x] + 0]) & 0x8000) ? System16PaletteEntries * 2 : System16PaletteEntries);
		} else {
			pPixel[x] = (pix | colour | 0x800) & (System16PaletteEntries - 1);
		}
	}
}

static void OutrunRenderSpriteLayer(int Priority)
{
	UINT8 numbanks = System16SpriteRomSize / 0x40000;
	const UINT32 *spritebase = (const UINT32 *)System16Sprites;
	UINT16 *data;

	for (data = (UINT16*)System16SpriteRamBuff; data < (UINT16*)System16SpriteRamBuff + System16SpriteRamSize / 2; data += 8) {
		if (data[0] & 0x8000) break;
		int sprpri  = 1 << ((data[3] >> 12) & 3);
				
#if 1 && defined FBA_DEBUG
		if (sprpri != 1 && sprpri != 2 && sprpri != 4 && sprpri != 8) bprintf(PRINT_IMPORTANT, _T("Unknown Sprite Priority - %x\n"), sprpri);
#endif
		if (sprpri != Priority) continue;
		
		int hide    = (data[0] & 0x5000);
		int bank    = (data[0] >> 9) & 7;
		int top     = (data[0] & 0x1ff) - 0x100;
		UINT16 addr = data[1];
		int pitch   = (INT16)((data[2] >> 1) | ((data[4] & 0x1000) << 3)) >> 8;
		int xpos    = data[2] & 0x1ff;
		int shadow  = (data[3] >> 14) & 1;
		int vzoom   = data[3] & 0x7ff;
		int ydelta  = (data[4] & 0x8000) ? 1 : -1;
		int flip    = (~data[4] >> 14) & 1;
		int xdelta  = (data[4] & 0x2000) ? 1 : -1;
		int hzoom   = data[4] & 0x7ff;
		int height  = (data[5] >> 8) + 1;
		int color   = (data[5] & 0x7f) << 4;
		int x, y, ytarget, yacc = 0, pix;
		const UINT32 *spritedata;

		/* adjust X coordinate */
		/* note: the threshhold below is a guess. If it is too high, rachero will draw garbage */
		/* If it is too low, smgp won't draw the bottom part of the road */
		if (xpos < 0x80 && xdelta < 0)
			xpos += 0x200;
		xpos -= 0xbe;

		/* initialize the end address to the start address */
		data[7] = addr;

		/* if hidden, or top greater than/equal to bottom, or invalid bank, punt */
		if (hide || height == 0)
			continue;

		/* clamp to within the memory region size */
		if (numbanks)
			bank %= numbanks;
		spritedata = spritebase + 0x10000 * bank;

		/* clamp to a maximum of 8x (not 100% confirmed) */
		if (vzoom < 0x40) vzoom = 0x40;
		if (hzoom < 0x40) hzoom = 0x40;

		/* loop from top to bottom */
		ytarget = top + ydelta * height;
		for (y = top; y != ytarget; y += ydelta)
		{
			/* skip drawing if not within the cliprect */
			if (y >= 0 && y <= 223) {
				unsigned short* pPixel = pTransDraw + (y * 320);
				int xacc = 0;

				/* non-flipped case */
				if (!flip)
				{
					/* start at the word before because we preincrement below */
					data[7] = addr - 1;
					for (x = xpos; (xdelta > 0 && x <= 319) || (xdelta < 0 && x >= 0); )
					{
						UINT32 pixels = spritedata[++data[7]];

						/* draw four pixels */
						pix = (pixels >> 28) & 0xf; while (xacc < 0x200) { OutrunDrawPixel(x, pix, color, shadow, pPixel); x += xdelta; xacc += hzoom; } xacc -= 0x200;
						pix = (pixels >> 24) & 0xf; while (xacc < 0x200) { OutrunDrawPixel(x, pix, color, shadow, pPixel); x += xdelta; xacc += hzoom; } xacc -= 0x200;
						pix = (pixels >> 20) & 0xf; while (xacc < 0x200) { OutrunDrawPixel(x, pix, color, shadow, pPixel); x += xdelta; xacc += hzoom; } xacc -= 0x200;
						pix = (pixels >> 16) & 0xf; while (xacc < 0x200) { OutrunDrawPixel(x, pix, color, shadow, pPixel); x += xdelta; xacc += hzoom; } xacc -= 0x200;
						pix = (pixels >> 12) & 0xf; while (xacc < 0x200) { OutrunDrawPixel(x, pix, color, shadow, pPixel); x += xdelta; xacc += hzoom; } xacc -= 0x200;
						pix = (pixels >>  8) & 0xf; while (xacc < 0x200) { OutrunDrawPixel(x, pix, color, shadow, pPixel); x += xdelta; xacc += hzoom; } xacc -= 0x200;
						pix = (pixels >>  4) & 0xf; while (xacc < 0x200) { OutrunDrawPixel(x, pix, color, shadow, pPixel); x += xdelta; xacc += hzoom; } xacc -= 0x200;
						pix = (pixels >>  0) & 0xf; while (xacc < 0x200) { OutrunDrawPixel(x, pix, color, shadow, pPixel); x += xdelta; xacc += hzoom; } xacc -= 0x200;

						/* stop if the second-to-last pixel in the group was 0xf */
						if ((pixels & 0x000000f0) == 0x000000f0)
							break;
					}
				}

				/* flipped case */
				else
				{
					/* start at the word after because we predecrement below */
					data[7] = addr + 1;
					for (x = xpos; (xdelta > 0 && x <= 319) || (xdelta < 0 && x >= 0); )
					{
						UINT32 pixels = spritedata[--data[7]];

						/* draw four pixels */
						pix = (pixels >>  0) & 0xf; while (xacc < 0x200) { OutrunDrawPixel(x, pix, color, shadow, pPixel); x += xdelta; xacc += hzoom; } xacc -= 0x200;
						pix = (pixels >>  4) & 0xf; while (xacc < 0x200) { OutrunDrawPixel(x, pix, color, shadow, pPixel); x += xdelta; xacc += hzoom; } xacc -= 0x200;
						pix = (pixels >>  8) & 0xf; while (xacc < 0x200) { OutrunDrawPixel(x, pix, color, shadow, pPixel); x += xdelta; xacc += hzoom; } xacc -= 0x200;
						pix = (pixels >> 12) & 0xf; while (xacc < 0x200) { OutrunDrawPixel(x, pix, color, shadow, pPixel); x += xdelta; xacc += hzoom; } xacc -= 0x200;
						pix = (pixels >> 16) & 0xf; while (xacc < 0x200) { OutrunDrawPixel(x, pix, color, shadow, pPixel); x += xdelta; xacc += hzoom; } xacc -= 0x200;
						pix = (pixels >> 20) & 0xf; while (xacc < 0x200) { OutrunDrawPixel(x, pix, color, shadow, pPixel); x += xdelta; xacc += hzoom; } xacc -= 0x200;
						pix = (pixels >> 24) & 0xf; while (xacc < 0x200) { OutrunDrawPixel(x, pix, color, shadow, pPixel); x += xdelta; xacc += hzoom; } xacc -= 0x200;
						pix = (pixels >> 28) & 0xf; while (xacc < 0x200) { OutrunDrawPixel(x, pix, color, shadow, pPixel); x += xdelta; xacc += hzoom; } xacc -= 0x200;

						/* stop if the second-to-last pixel in the group was 0xf */
						if ((pixels & 0x0f000000) == 0x0f000000)
							break;
					}
				}
			}

			/* accumulate zoom factors; if we carry into the high bit, skip an extra row */
			yacc += vzoom;
			addr += pitch * (yacc >> 9);
			yacc &= 0x1ff;
		}
	}
}

inline static void HangonDrawPixel(int x, int pix, int colour, int shadow, unsigned short* pPixel)
{
	if (x >= 0 && x <= 319 && pix != 0 && pix != 15) {
		if (shadow && pix == 0xa) {
			pPixel[x] &= (System16PaletteEntries - 1);
			pPixel[x] += ((((System16PaletteRam[pPixel[x] + 1] << 8) | System16PaletteRam[pPixel[x] + 0]) & 0x8000) ? System16PaletteEntries * 2 : System16PaletteEntries);
		} else {
			pPixel[x] = (pix | colour | 0x400) & (System16PaletteEntries - 1);
		}
	}
}

static void HangonRenderSpriteLayer(int Priority)
{
	UINT8 numbanks = System16SpriteRomSize / 0x20000;
	const UINT32 *spritebase = (UINT32*)System16Sprites;
	const UINT8 *zoom = System16Prom;
	UINT16 *data;

	for (data = (UINT16*)System16SpriteRam; data < (UINT16*)System16SpriteRam + System16SpriteRamSize / 2; data += 8) {
		if ((data[0] >> 8) > 0xf0) break;	
		int sprpri  = ((data[2] >> 14) & 1) ? (1<<3) : (1<<1);
		
#if 1 && defined FBA_DEBUG
		if (sprpri != 1 && sprpri != 2 && sprpri != 4 && sprpri != 8) bprintf(PRINT_IMPORTANT, _T("Unknown Sprite Priority - %x\n"), sprpri);
#endif
		
		if (sprpri != Priority) continue;
		
		int bottom  = (data[0] >> 8) + 1;
		int top     = (data[0] & 0xff) + 1;
		int bank    = System16SpriteBanks[(data[1] >> 12) & 0x7];
		int xpos    = (data[1] & 0x1ff) - 0xbd;
		int shadow  = (~data[2] >> 15) & 1;
		int color   = (((data[2] >> 8) & 0x3f) << 4);
		int pitch   = (INT16)(data[2] << 9) >> 9;
		UINT16 addr = data[3];
		int hzoom   = ((data[4] >> 8) & 0x3f) << 1;
		int vzoom   = (data[4] >> 0) & 0x3f;
		int x, y, pix, zaddr, zmask;
		const UINT32 *spritedata;
		
		/* initialize the end address to the start address */
		data[7] = addr;

		/* if hidden, or top greater than/equal to bottom, or invalid bank, punt */
		if ((top >= bottom) || bank == 255)
			continue;

		/* clamp to within the memory region size */
		if (numbanks)
			bank %= numbanks;
		spritedata = spritebase + 0x8000 * bank;
		
		/* determine the starting zoom address and mask */
		zaddr = (vzoom & 0x38) << 5;
		zmask = 1 << (vzoom & 7);
		
		for (y = top; y < bottom; y++) {
			addr += pitch;
			
			/* if the zoom bit says so, add pitch a second time */
			if (zoom[zaddr++] & zmask)
				addr += pitch;
				
			if (y >= 0 && y <= 223) {
				unsigned short* pPixel = pTransDraw + (y * 320);
				int xacc = 0x00;
				
				if (!(addr & 0x8000)) {
					/* start at the word before because we preincrement below */
					data[7] = addr - 1;
					for (x = xpos; x <= 319; ) {
						UINT32 pixels = spritedata[++data[7] & 0x7fff];
					
						pix = (pixels >> 28) & 0xf; xacc = (xacc & 0xff) + hzoom; if (xacc < 0x100) { if (x >= 0) HangonDrawPixel(x, pix, color, shadow, pPixel); x++; }
						pix = (pixels >> 24) & 0xf; xacc = (xacc & 0xff) + hzoom; if (xacc < 0x100) { if (x >= 0) HangonDrawPixel(x, pix, color, shadow, pPixel); x++; }
						pix = (pixels >> 20) & 0xf; xacc = (xacc & 0xff) + hzoom; if (xacc < 0x100) { if (x >= 0) HangonDrawPixel(x, pix, color, shadow, pPixel); x++; }
						pix = (pixels >> 16) & 0xf; xacc = (xacc & 0xff) + hzoom; if (xacc < 0x100) { if (x >= 0) HangonDrawPixel(x, pix, color, shadow, pPixel); x++; }
						pix = (pixels >> 12) & 0xf; xacc = (xacc & 0xff) + hzoom; if (xacc < 0x100) { if (x >= 0) HangonDrawPixel(x, pix, color, shadow, pPixel); x++; }
						pix = (pixels >>  8) & 0xf; xacc = (xacc & 0xff) + hzoom; if (xacc < 0x100) { if (x >= 0) HangonDrawPixel(x, pix, color, shadow, pPixel); x++; }
						pix = (pixels >>  4) & 0xf; xacc = (xacc & 0xff) + hzoom; if (xacc < 0x100) { if (x >= 0) HangonDrawPixel(x, pix, color, shadow, pPixel); x++; }
						pix = (pixels >>  0) & 0xf; xacc = (xacc & 0xff) + hzoom; if (xacc < 0x100) { if (x >= 0) HangonDrawPixel(x, pix, color, shadow, pPixel); x++; }
					
						if (pix == 15) break;
					}
				} else {
					data[7] = addr + 1;
					for (x = xpos; x <= 319; ) {
						UINT32 pixels = spritedata[--data[7] & 0x7fff];

						pix = (pixels >>  0) & 0xf; xacc = (xacc & 0xff) + hzoom; if (xacc < 0x100) { if (x >= 0) HangonDrawPixel(x, pix, color, shadow, pPixel); x++; }
						pix = (pixels >>  4) & 0xf; xacc = (xacc & 0xff) + hzoom; if (xacc < 0x100) { if (x >= 0) HangonDrawPixel(x, pix, color, shadow, pPixel); x++; }
						pix = (pixels >>  8) & 0xf; xacc = (xacc & 0xff) + hzoom; if (xacc < 0x100) { if (x >= 0) HangonDrawPixel(x, pix, color, shadow, pPixel); x++; }
						pix = (pixels >> 12) & 0xf; xacc = (xacc & 0xff) + hzoom; if (xacc < 0x100) { if (x >= 0) HangonDrawPixel(x, pix, color, shadow, pPixel); x++; }
						pix = (pixels >> 16) & 0xf; xacc = (xacc & 0xff) + hzoom; if (xacc < 0x100) { if (x >= 0) HangonDrawPixel(x, pix, color, shadow, pPixel); x++; }
						pix = (pixels >> 20) & 0xf; xacc = (xacc & 0xff) + hzoom; if (xacc < 0x100) { if (x >= 0) HangonDrawPixel(x, pix, color, shadow, pPixel); x++; }
						pix = (pixels >> 24) & 0xf; xacc = (xacc & 0xff) + hzoom; if (xacc < 0x100) { if (x >= 0) HangonDrawPixel(x, pix, color, shadow, pPixel); x++; }
						pix = (pixels >> 28) & 0xf; xacc = (xacc & 0xff) + hzoom; if (xacc < 0x100) { if (x >= 0) HangonDrawPixel(x, pix, color, shadow, pPixel); x++; }

						/* stop if the last pixel in the group was 0xf */
						if (pix == 15) break;
					}
				}
			}
		}
	}
}

inline static void HangonAltDrawPixel(int x, int pix, int colour, unsigned short* pPixel)
{
	if (x >= 0 && x <= 319 && pix != 0 && pix != 15) {
		if (colour == (0x3f << 4)) {
			pPixel[x] &= (System16PaletteEntries - 1);
			pPixel[x] += ((System16SpriteShadow) ? System16PaletteEntries * 2 : System16PaletteEntries);
		} else {
			pPixel[x] = (pix | colour | 0x400) & (System16PaletteEntries - 1);
		}
	}
}

static void HangonAltRenderSpriteLayer(int Priority)
{
	UINT8 numbanks = System16SpriteRomSize / 0x10000;
	const UINT16 *spritebase = (UINT16*)System16Sprites;
	const UINT8 *zoom = System16Prom;
	UINT16 *data;
	
	for (data = (UINT16*)System16SpriteRam; data < (UINT16*)System16SpriteRam + System16SpriteRamSize / 2; data += 8) {
		if ((data[0] >> 8) > 0xf0) break;
		int sprpri  = 1 << ((data[4] >> 0) & 0x3);
		
#if 1 && defined FBA_DEBUG
		if (sprpri != 1 && sprpri != 2 && sprpri != 4 && sprpri != 8) bprintf(PRINT_IMPORTANT, _T("Unknown Sprite Priority - %x\n"), sprpri);
#endif
		
		if (sprpri != Priority) continue;
		
		int bottom  = (data[0] >> 8) + 1;
		int top     = (data[0] & 0xff) + 1;
		int bank    = System16SpriteBanks[(data[1] >> 12) & 0xf];
		int xpos    = (data[1] & 0x1ff) - 0xbd;
		int pitch   = (INT16)data[2];
		UINT16 addr = data[3];
		int color   = (((data[4] >> 8) & 0x3f) << 4);
		int vzoom   = (data[4] >> 2) & 0x3f;
		int hzoom   = vzoom << 1;
		
		int x, y, pix, zaddr, zmask;
		const UINT16 *spritedata;

		/* initialize the end address to the start address */
		data[7] = addr;

		/* if hidden, or top greater than/equal to bottom, or invalid bank, punt */
		if ((top >= bottom) || bank == 255)
			continue;

		/* clamp to within the memory region size */
		if (numbanks)
			bank %= numbanks;
		spritedata = spritebase + 0x8000 * bank;

		/* determine the starting zoom address and mask */
		zaddr = (vzoom & 0x38) << 5;
		zmask = 1 << (vzoom & 7);

		/* loop from top to bottom */
		for (y = top; y < bottom; y++)
		{
			/* advance a row */
			addr += pitch;

			/* if the zoom bit says so, add pitch a second time */
			if (zoom[zaddr++] & zmask)
				addr += pitch;

			/* skip drawing if not within the cliprect */
			if (y >= 0 && y <= 223)
			{
				unsigned short* pPixel = pTransDraw + (y * 320);
				int xacc = 0x00;

				/* note that the System 16A sprites have a design flaw that allows the address */
				/* to carry into the flip flag, which is the topmost bit -- it is very important */
				/* to emulate this as the games compensate for it */

				/* non-flipped case */
				if (!(addr & 0x8000))
				{
					/* start at the word before because we preincrement below */
					data[7] = addr - 1;
					for (x = xpos; x <= 319; )
					{
						UINT16 pixels = spritedata[++data[7] & 0x7fff];

						/* draw four pixels */
						pix = (pixels >> 12) & 0xf; xacc = (xacc & 0xff) + hzoom; if (xacc < 0x100) { if (x >= 0) HangonAltDrawPixel(x, pix, color, pPixel); x++; }
						pix = (pixels >>  8) & 0xf; xacc = (xacc & 0xff) + hzoom; if (xacc < 0x100) { if (x >= 0) HangonAltDrawPixel(x, pix, color, pPixel); x++; }
						pix = (pixels >>  4) & 0xf; xacc = (xacc & 0xff) + hzoom; if (xacc < 0x100) { if (x >= 0) HangonAltDrawPixel(x, pix, color, pPixel); x++; }
						pix = (pixels >>  0) & 0xf; xacc = (xacc & 0xff) + hzoom; if (xacc < 0x100) { if (x >= 0) HangonAltDrawPixel(x, pix, color, pPixel); x++; }

						/* stop if the last pixel in the group was 0xf */
						if (pix == 15)
							break;
					}
				}

				/* flipped case */
				else
				{
					/* start at the word after because we predecrement below */
					data[7] = addr + 1;
					for (x = xpos; x <= 319; )
					{
						UINT16 pixels = spritedata[--data[7] & 0x7fff];

						/* draw four pixels */
						pix = (pixels >>  0) & 0xf; xacc = (xacc & 0xff) + hzoom; if (xacc < 0x100) { if (x >= 0) HangonAltDrawPixel(x, pix, color, pPixel); x++; }
						pix = (pixels >>  4) & 0xf; xacc = (xacc & 0xff) + hzoom; if (xacc < 0x100) { if (x >= 0) HangonAltDrawPixel(x, pix, color, pPixel); x++; }
						pix = (pixels >>  8) & 0xf; xacc = (xacc & 0xff) + hzoom; if (xacc < 0x100) { if (x >= 0) HangonAltDrawPixel(x, pix, color, pPixel); x++; }
						pix = (pixels >> 12) & 0xf; xacc = (xacc & 0xff) + hzoom; if (xacc < 0x100) { if (x >= 0) HangonAltDrawPixel(x, pix, color, pPixel); x++; }

						/* stop if the last pixel in the group was 0xf */
						if (pix == 15)
							break;
					}
				}
			}
		}
	}
}

inline static void BoardXDrawPixel(int x, int pix, int colour, int shadow, unsigned short* pPixel)
{
	if (x >= 0 && x <= 319 && pix != 0 && pix != 15) {
		if (shadow && pix == 0xa) {
			pPixel[x] &= (System16PaletteEntries - 1);
			pPixel[x] += ((((System16PaletteRam[pPixel[x] + 1] << 8) | System16PaletteRam[pPixel[x] + 0]) & 0x8000) ? System16PaletteEntries * 2 : System16PaletteEntries);
		} else {
			pPixel[x] = (pix | colour) & (System16PaletteEntries - 1);
		}
	}
}

static void XBoardRenderSpriteLayer(int Priority)
{
	UINT8 numbanks = System16SpriteRomSize / 0x40000;
	const UINT32 *spritebase = (const UINT32 *)System16Sprites;
	UINT16 *data;

	for (data = (UINT16*)System16SpriteRamBuff; data < (UINT16*)System16SpriteRamBuff + System16SpriteRamSize / 2; data += 8) {
		if (data[0] & 0x8000) break;
		int sprpri  = 1 << ((data[3] >> 12) & 3);
		
#if 1 && defined FBA_DEBUG
		if (sprpri != 1 && sprpri != 2 && sprpri != 4 && sprpri != 8) bprintf(PRINT_IMPORTANT, _T("Unknown Sprite Priority - %x\n"), sprpri);
#endif
		if (sprpri != Priority) continue;
		
		int hide    = (data[0] & 0x5000);
		int bank    = (data[0] >> 9) & 7;
		int top     = (data[0] & 0x1ff) - 0x100;
		UINT16 addr = data[1];
		int pitch   = (INT16)((data[2] >> 1) | ((data[4] & 0x1000) << 3)) >> 8;
		int xpos    = data[2] & 0x1ff;
		int shadow  = (data[3] >> 14) & 1;
		int vzoom   = data[3] & 0x7ff;
		int ydelta  = (data[4] & 0x8000) ? 1 : -1;
		int flip    = (~data[4] >> 14) & 1;
		int xdelta  = (data[4] & 0x2000) ? 1 : -1;
		int hzoom   = data[4] & 0x7ff;
		int height  = (data[5] & 0xfff) + 1;
		int color   = (data[6] & 0xff) << 4;
		int x, y, ytarget, yacc = 0, pix;
		const UINT32 *spritedata;

		/* adjust X coordinate */
		/* note: the threshhold below is a guess. If it is too high, rachero will draw garbage */
		/* If it is too low, smgp won't draw the bottom part of the road */
		if (xpos < 0x80 && xdelta < 0)
			xpos += 0x200;
		xpos -= 0xbe;

		/* initialize the end address to the start address */
		data[7] = addr;

		/* if hidden, or top greater than/equal to bottom, or invalid bank, punt */
		if (hide || height == 0)
			continue;

		/* clamp to within the memory region size */
		if (numbanks)
			bank %= numbanks;
		spritedata = spritebase + 0x10000 * bank;

		/* clamp to a maximum of 8x (not 100% confirmed) */
		if (vzoom < 0x40) vzoom = 0x40;
		if (hzoom < 0x40) hzoom = 0x40;

		/* loop from top to bottom */
		ytarget = top + ydelta * height;
		for (y = top; y != ytarget; y += ydelta)
		{
			/* skip drawing if not within the cliprect */
			if (y >= 0 && y <= 223) {
				unsigned short* pPixel = pTransDraw + (y * 320);
				int xacc = 0;

				/* non-flipped case */
				if (!flip)
				{
					/* start at the word before because we preincrement below */
					data[7] = addr - 1;
					for (x = xpos; (xdelta > 0 && x <= 319) || (xdelta < 0 && x >= 0); )
					{
						UINT32 pixels = spritedata[++data[7]];
						
						/* draw four pixels */
						pix = (pixels >> 28) & 0xf; while (xacc < 0x200) { BoardXDrawPixel(x, pix, color, shadow, pPixel); x += xdelta; xacc += hzoom; } xacc -= 0x200;
						pix = (pixels >> 24) & 0xf; while (xacc < 0x200) { BoardXDrawPixel(x, pix, color, shadow, pPixel); x += xdelta; xacc += hzoom; } xacc -= 0x200;
						pix = (pixels >> 20) & 0xf; while (xacc < 0x200) { BoardXDrawPixel(x, pix, color, shadow, pPixel); x += xdelta; xacc += hzoom; } xacc -= 0x200;
						pix = (pixels >> 16) & 0xf; while (xacc < 0x200) { BoardXDrawPixel(x, pix, color, shadow, pPixel); x += xdelta; xacc += hzoom; } xacc -= 0x200;
						pix = (pixels >> 12) & 0xf; while (xacc < 0x200) { BoardXDrawPixel(x, pix, color, shadow, pPixel); x += xdelta; xacc += hzoom; } xacc -= 0x200;
						pix = (pixels >>  8) & 0xf; while (xacc < 0x200) { BoardXDrawPixel(x, pix, color, shadow, pPixel); x += xdelta; xacc += hzoom; } xacc -= 0x200;
						pix = (pixels >>  4) & 0xf; while (xacc < 0x200) { BoardXDrawPixel(x, pix, color, shadow, pPixel); x += xdelta; xacc += hzoom; } xacc -= 0x200;
						pix = (pixels >>  0) & 0xf; while (xacc < 0x200) { BoardXDrawPixel(x, pix, color, shadow, pPixel); x += xdelta; xacc += hzoom; } xacc -= 0x200;

						/* stop if the second-to-last pixel in the group was 0xf */
						if ((pixels & 0x000000f0) == 0x000000f0)
							break;
					}
				}

				/* flipped case */
				else
				{
					/* start at the word after because we predecrement below */
					data[7] = addr + 1;
					for (x = xpos; (xdelta > 0 && x <= 319) || (xdelta < 0 && x >= 0); )
					{
						UINT32 pixels = spritedata[--data[7]];
						
						/* draw four pixels */
						pix = (pixels >>  0) & 0xf; while (xacc < 0x200) { BoardXDrawPixel(x, pix, color, shadow, pPixel); x += xdelta; xacc += hzoom; } xacc -= 0x200;
						pix = (pixels >>  4) & 0xf; while (xacc < 0x200) { BoardXDrawPixel(x, pix, color, shadow, pPixel); x += xdelta; xacc += hzoom; } xacc -= 0x200;
						pix = (pixels >>  8) & 0xf; while (xacc < 0x200) { BoardXDrawPixel(x, pix, color, shadow, pPixel); x += xdelta; xacc += hzoom; } xacc -= 0x200;
						pix = (pixels >> 12) & 0xf; while (xacc < 0x200) { BoardXDrawPixel(x, pix, color, shadow, pPixel); x += xdelta; xacc += hzoom; } xacc -= 0x200;
						pix = (pixels >> 16) & 0xf; while (xacc < 0x200) { BoardXDrawPixel(x, pix, color, shadow, pPixel); x += xdelta; xacc += hzoom; } xacc -= 0x200;
						pix = (pixels >> 20) & 0xf; while (xacc < 0x200) { BoardXDrawPixel(x, pix, color, shadow, pPixel); x += xdelta; xacc += hzoom; } xacc -= 0x200;
						pix = (pixels >> 24) & 0xf; while (xacc < 0x200) { BoardXDrawPixel(x, pix, color, shadow, pPixel); x += xdelta; xacc += hzoom; } xacc -= 0x200;
						pix = (pixels >> 28) & 0xf; while (xacc < 0x200) { BoardXDrawPixel(x, pix, color, shadow, pPixel); x += xdelta; xacc += hzoom; } xacc -= 0x200;

						/* stop if the second-to-last pixel in the group was 0xf */
						if ((pixels & 0x0f000000) == 0x0f000000)
							break;
					}
				}
			}

			/* accumulate zoom factors; if we carry into the high bit, skip an extra row */
			yacc += vzoom;
			addr += pitch * (yacc >> 9);
			yacc &= 0x1ff;
		}
	}
}

inline static void YBoardSystem16BDrawPixel(int x, int pix, int colour, unsigned short* pPixel)
{
	if (x >= 0 && x <= 319 && pix != 0 && pix != 15) {
		if (pix == 14) {
			pPixel[x] &= (System16PaletteEntries - 1);
			pPixel[x] += ((((System16PaletteRam[pPixel[x] + 1] << 8) | System16PaletteRam[pPixel[x] + 0]) & 0x8000) ? (System16PaletteEntries * 2) : System16PaletteEntries);
		} else {
			pPixel[x] = (pix | colour | 0x800) & (System16PaletteEntries - 1);
		}
	}
}

static void YBoardSystem16BRenderSpriteLayer()
{
	UINT8 numbanks;
	const UINT16 *spritebase;
  	UINT16 *data;

	spritebase = (const UINT16 *)System16Sprites;
	numbanks = System16SpriteRomSize / 0x20000;

	for (data = (UINT16*)System16SpriteRam; data < (UINT16*)System16SpriteRam + System16SpriteRamSize / 2; data += 8) {
		if (data[2] & 0x8000) break;
		//int sprpri  = (data[1] >> 8) & 0x1e;
				
		int bottom  = data[0] >> 8;
		int top     = data[0] & 0xff;
		int xpos    = (data[1] & 0x1ff) - 0xb8;
		int hide    = data[2] & 0x4000;
		int flip    = data[2] & 0x100;
		int pitch   = (INT8)(data[2] & 0xff);
		UINT16 addr = data[3];
		int bank    = System16SpriteBanks[(data[4] >> 8) & 0xf];
		int color   = ((data[4] & 0x7f) << 4);
		int vzoom   = (data[5] >> 5) & 0x1f;
		int hzoom   = data[5] & 0x1f;
		const UINT16 *spritedata;
		int x, y, pix, xdelta = 1;
		
		/* initialize the end address to the start address */
		data[7] = addr;

		/* if hidden, or top greater than/equal to bottom, or invalid bank, punt */
		if (hide || (top >= bottom) || bank == 255)
			continue;

		/* clamp to within the memory region size */
		if (numbanks)
			bank %= numbanks;
		spritedata = spritebase + 0x10000 * bank;

		/* reset the yzoom counter */
		data[5] &= 0x03ff;

		/* loop from top to bottom */
		for (y = top; y < bottom; y++) {
			/* advance a row */
			addr += pitch;

			/* accumulate zoom factors; if we carry into the high bit, skip an extra row */
			data[5] += vzoom << 10;
			if (data[5] & 0x8000) {
				addr += pitch;
				data[5] &= ~0x8000;
			}

			/* skip drawing if not within the cliprect */
			if (y >= 0 && y <= 223) {
				unsigned short* pPixel = pTransDraw + (y * 320);
				int xacc;

				/* compute the initial X zoom accumulator; this is verified on the real PCB */
				xacc = 4 * hzoom;

				/* non-flipped case */
				if (!flip) {
					/* start at the word before because we preincrement below */
					data[7] = addr - 1;
					for (x = xpos; ((xpos - x) & 0x1ff) != 1; ) {
						UINT16 pixels = spritedata[++data[7]];

						/* draw four pixels */
						pix = (pixels >> 12) & 0xf; xacc = (xacc & 0x3f) + hzoom; if (xacc < 0x40) { YBoardSystem16BDrawPixel(x, pix, color, pPixel); x += xdelta; }
						pix = (pixels >>  8) & 0xf; xacc = (xacc & 0x3f) + hzoom; if (xacc < 0x40) { YBoardSystem16BDrawPixel(x, pix, color, pPixel); x += xdelta; }
						pix = (pixels >>  4) & 0xf; xacc = (xacc & 0x3f) + hzoom; if (xacc < 0x40) { YBoardSystem16BDrawPixel(x, pix, color, pPixel); x += xdelta; }
						pix = (pixels >>  0) & 0xf; xacc = (xacc & 0x3f) + hzoom; if (xacc < 0x40) { YBoardSystem16BDrawPixel(x, pix, color, pPixel); x += xdelta; }

						/* stop if the last pixel in the group was 0xf */
						if (pix == 15) break;
					}
				} else {
					/* start at the word after because we predecrement below */
					data[7] = addr + 1;
					for (x = xpos; ((xpos - x) & 0x1ff) != 1; ) {
						UINT16 pixels = spritedata[--data[7]];

						/* draw four pixels */
						pix = (pixels >>  0) & 0xf; xacc = (xacc & 0x3f) + hzoom; if (xacc < 0x40) { YBoardSystem16BDrawPixel(x, pix, color, pPixel); x += xdelta; }
						pix = (pixels >>  4) & 0xf; xacc = (xacc & 0x3f) + hzoom; if (xacc < 0x40) { YBoardSystem16BDrawPixel(x, pix, color, pPixel); x += xdelta; }
						pix = (pixels >>  8) & 0xf; xacc = (xacc & 0x3f) + hzoom; if (xacc < 0x40) { YBoardSystem16BDrawPixel(x, pix, color, pPixel); x += xdelta; }
						pix = (pixels >> 12) & 0xf; xacc = (xacc & 0x3f) + hzoom; if (xacc < 0x40) { YBoardSystem16BDrawPixel(x, pix, color, pPixel); x += xdelta; }

						/* stop if the last pixel in the group was 0xf */
						if (pix == 15) break;
					}
				}
			}
		}
	}
}

inline static void YBoardDrawPixel(int x, unsigned int ind, unsigned int colourpri, unsigned short* pPixel)
{
	if (x >= 0 && x <= 511 && ind < 0x1fe) {
		pPixel[x] = (ind | colourpri | 0x1000)/* & (System16PaletteEntries - 1)*/;
	}
}

static void YBoardRenderSpriteLayer()
{
	UINT8 numbanks = System16Sprite2RomSize / 0x80000;
	const UINT64 *spritebase = (const UINT64 *)System16Sprites2;
	const UINT16 *rotatebase = (UINT16*)System16RotateRamBuff;
	UINT8 visited[0x1000];
	UINT16 *data;
	int next = 0;

	/* reset the visited list */
	memset(visited, 0, sizeof(visited));

	for (int y = 0; y <= 511; y++)
		if (!(rotatebase[y & ~1] & 0xc000))
			memset(pTempDraw + (y * 512), 0xff, 512 * sizeof(UINT16));

	for (data = (UINT16*)System16SpriteRam2; !(data[0] & 0x8000) && !visited[next]; data = (UINT16*)System16SpriteRam2 + next * 8)
	{
		int hide    = (data[0] & 0x5000);
		UINT16 *indirect = (UINT16*)System16SpriteRam2 + ((data[0] & 0x7ff) << 4);
		int bank    = ((data[1] >> 8) & 0x10) | ((data[2] >> 12) & 0x0f);
		int xpos    = (data[1] & 0xfff) - 0x600;
		int top     = (data[2] & 0xfff) - 0x600;
		UINT16 addr = data[3];
		int height  = data[4];
		int ydelta  = (data[5] & 0x4000) ? 1 : -1;
		int flip    = (~data[5] >> 13) & 1;
		int xdelta  = (data[5] & 0x1000) ? 1 : -1;
		int zoom    = data[5] & 0x7ff;
		int colorpri= (data[6] << 1) & 0xfe00;
		int pitch   = (INT8)data[6];
		int x, y, ytarget, yacc = 0, pix, ind;
		const UINT64 *spritedata;
		UINT16 offs;

		/* note that we've visited this entry and get the offset of the next one */
		visited[next] = 1;
		next = data[7] & 0xfff;
		
		/* if hidden, or top greater than/equal to bottom, or invalid bank, punt */
		if (hide || height == 0)
			continue;

		/* clamp to within the memory region size */
		if (numbanks)
			bank %= numbanks;
		spritedata = spritebase + 0x10000 * bank;

		/* clamp to a maximum of 8x (not 100% confirmed) */
		if (zoom == 0) zoom = 1;
		
		/* loop from top to bottom */
		ytarget = top + ydelta * height;
		for (y = top; y != ytarget; y += ydelta)
		{
			/* skip drawing if not within the cliprect */
			if (y >= 0 && y <= 511)
			{
				//unsigned short* pPixel = pTransDraw + (y * 320);
				unsigned short* pPixel = pTempDraw + (y * 512);
				int minx = rotatebase[y & ~1];
				int maxx = rotatebase[y |  1];
				int xacc = 0;

				/* bit 0x8000 from rotate RAM means that Y is above the top of the screen */
				if ((minx & 0x8000) && ydelta < 0)
					break;

				/* bit 0x4000 from rotate RAM means that Y is below the bottom of the screen */
				if ((minx & 0x4000) && ydelta > 0)
					break;

				/* if either bit is set, skip the rest for this scanline */
				if (!(minx & 0xc000))
				{
					/* clamp min/max to the cliprect */
					minx -= 0x600;
					maxx -= 0x600;
					if (minx < 0)
						minx = 0;
					if (maxx > 511)
						maxx = 511;

					/* non-flipped case */
					if (!flip)
					{
						/* start at the word before because we preincrement below */
						offs = addr - 1;
						for (x = xpos; (xdelta > 0 && x <= maxx) || (xdelta < 0 && x >= minx); )
						{
							UINT64 pixels = spritedata[++offs];

							/* draw four pixels */
							pix = (pixels >> 60) & 0xf; ind = indirect[pix]; while (xacc < 0x200) { YBoardDrawPixel(x, ind, colorpri, pPixel); x += xdelta; xacc += zoom; } xacc -= 0x200;
							pix = (pixels >> 56) & 0xf; ind = indirect[pix]; while (xacc < 0x200) { YBoardDrawPixel(x, ind, colorpri, pPixel); x += xdelta; xacc += zoom; } xacc -= 0x200;
							pix = (pixels >> 52) & 0xf; ind = indirect[pix]; while (xacc < 0x200) { YBoardDrawPixel(x, ind, colorpri, pPixel); x += xdelta; xacc += zoom; } xacc -= 0x200;
							pix = (pixels >> 48) & 0xf; ind = indirect[pix]; while (xacc < 0x200) { YBoardDrawPixel(x, ind, colorpri, pPixel); x += xdelta; xacc += zoom; } xacc -= 0x200;
							pix = (pixels >> 44) & 0xf; ind = indirect[pix]; while (xacc < 0x200) { YBoardDrawPixel(x, ind, colorpri, pPixel); x += xdelta; xacc += zoom; } xacc -= 0x200;
							pix = (pixels >> 40) & 0xf; ind = indirect[pix]; while (xacc < 0x200) { YBoardDrawPixel(x, ind, colorpri, pPixel); x += xdelta; xacc += zoom; } xacc -= 0x200;
							pix = (pixels >> 36) & 0xf; ind = indirect[pix]; while (xacc < 0x200) { YBoardDrawPixel(x, ind, colorpri, pPixel); x += xdelta; xacc += zoom; } xacc -= 0x200;
							pix = (pixels >> 32) & 0xf; ind = indirect[pix]; while (xacc < 0x200) { YBoardDrawPixel(x, ind, colorpri, pPixel); x += xdelta; xacc += zoom; } xacc -= 0x200;
							pix = (pixels >> 28) & 0xf; ind = indirect[pix]; while (xacc < 0x200) { YBoardDrawPixel(x, ind, colorpri, pPixel); x += xdelta; xacc += zoom; } xacc -= 0x200;
							pix = (pixels >> 24) & 0xf; ind = indirect[pix]; while (xacc < 0x200) { YBoardDrawPixel(x, ind, colorpri, pPixel); x += xdelta; xacc += zoom; } xacc -= 0x200;
							pix = (pixels >> 20) & 0xf; ind = indirect[pix]; while (xacc < 0x200) { YBoardDrawPixel(x, ind, colorpri, pPixel); x += xdelta; xacc += zoom; } xacc -= 0x200;
							pix = (pixels >> 16) & 0xf; ind = indirect[pix]; while (xacc < 0x200) { YBoardDrawPixel(x, ind, colorpri, pPixel); x += xdelta; xacc += zoom; } xacc -= 0x200;
							pix = (pixels >> 12) & 0xf; ind = indirect[pix]; while (xacc < 0x200) { YBoardDrawPixel(x, ind, colorpri, pPixel); x += xdelta; xacc += zoom; } xacc -= 0x200;
							pix = (pixels >>  8) & 0xf; ind = indirect[pix]; while (xacc < 0x200) { YBoardDrawPixel(x, ind, colorpri, pPixel); x += xdelta; xacc += zoom; } xacc -= 0x200;
							pix = (pixels >>  4) & 0xf; ind = indirect[pix]; while (xacc < 0x200) { YBoardDrawPixel(x, ind, colorpri, pPixel); x += xdelta; xacc += zoom; } xacc -= 0x200;
							pix = (pixels >>  0) & 0xf; ind = indirect[pix]; while (xacc < 0x200) { YBoardDrawPixel(x, ind, colorpri, pPixel); x += xdelta; xacc += zoom; } xacc -= 0x200;
							
							/* stop if the second-to-last pixel in the group was 0xf */
							if (pix == 0x0f)
								break;
						}
					}

					/* flipped case */
					else
					{
						/* start at the word after because we predecrement below */
						offs = addr + 1;
						for (x = xpos; (xdelta > 0 && x <= maxx) || (xdelta < 0 && x >= minx); )
						{
							UINT64 pixels = spritedata[--offs];

							/* draw four pixels */
							pix = (pixels >>  0) & 0xf; ind = indirect[pix]; while (xacc < 0x200) { YBoardDrawPixel(x, ind, colorpri, pPixel); x += xdelta; xacc += zoom; } xacc -= 0x200;
							pix = (pixels >>  4) & 0xf; ind = indirect[pix]; while (xacc < 0x200) { YBoardDrawPixel(x, ind, colorpri, pPixel); x += xdelta; xacc += zoom; } xacc -= 0x200;
							pix = (pixels >>  8) & 0xf; ind = indirect[pix]; while (xacc < 0x200) { YBoardDrawPixel(x, ind, colorpri, pPixel); x += xdelta; xacc += zoom; } xacc -= 0x200;
							pix = (pixels >> 12) & 0xf; ind = indirect[pix]; while (xacc < 0x200) { YBoardDrawPixel(x, ind, colorpri, pPixel); x += xdelta; xacc += zoom; } xacc -= 0x200;
							pix = (pixels >> 16) & 0xf; ind = indirect[pix]; while (xacc < 0x200) { YBoardDrawPixel(x, ind, colorpri, pPixel); x += xdelta; xacc += zoom; } xacc -= 0x200;
							pix = (pixels >> 20) & 0xf; ind = indirect[pix]; while (xacc < 0x200) { YBoardDrawPixel(x, ind, colorpri, pPixel); x += xdelta; xacc += zoom; } xacc -= 0x200;
							pix = (pixels >> 24) & 0xf; ind = indirect[pix]; while (xacc < 0x200) { YBoardDrawPixel(x, ind, colorpri, pPixel); x += xdelta; xacc += zoom; } xacc -= 0x200;
							pix = (pixels >> 28) & 0xf; ind = indirect[pix]; while (xacc < 0x200) { YBoardDrawPixel(x, ind, colorpri, pPixel); x += xdelta; xacc += zoom; } xacc -= 0x200;
							pix = (pixels >> 32) & 0xf; ind = indirect[pix]; while (xacc < 0x200) { YBoardDrawPixel(x, ind, colorpri, pPixel); x += xdelta; xacc += zoom; } xacc -= 0x200;
							pix = (pixels >> 36) & 0xf; ind = indirect[pix]; while (xacc < 0x200) { YBoardDrawPixel(x, ind, colorpri, pPixel); x += xdelta; xacc += zoom; } xacc -= 0x200;
							pix = (pixels >> 40) & 0xf; ind = indirect[pix]; while (xacc < 0x200) { YBoardDrawPixel(x, ind, colorpri, pPixel); x += xdelta; xacc += zoom; } xacc -= 0x200;
							pix = (pixels >> 44) & 0xf; ind = indirect[pix]; while (xacc < 0x200) { YBoardDrawPixel(x, ind, colorpri, pPixel); x += xdelta; xacc += zoom; } xacc -= 0x200;
							pix = (pixels >> 48) & 0xf; ind = indirect[pix]; while (xacc < 0x200) { YBoardDrawPixel(x, ind, colorpri, pPixel); x += xdelta; xacc += zoom; } xacc -= 0x200;
							pix = (pixels >> 52) & 0xf; ind = indirect[pix]; while (xacc < 0x200) { YBoardDrawPixel(x, ind, colorpri, pPixel); x += xdelta; xacc += zoom; } xacc -= 0x200;
							pix = (pixels >> 56) & 0xf; ind = indirect[pix]; while (xacc < 0x200) { YBoardDrawPixel(x, ind, colorpri, pPixel); x += xdelta; xacc += zoom; } xacc -= 0x200;
							pix = (pixels >> 60) & 0xf; ind = indirect[pix]; while (xacc < 0x200) { YBoardDrawPixel(x, ind, colorpri, pPixel); x += xdelta; xacc += zoom; } xacc -= 0x200;
							
							/* stop if the second-to-last pixel in the group was 0xf */
							if (pix == 0x0f)
								break;
						}
					}
				}
			}

			/* accumulate zoom factors; if we carry into the high bit, skip an extra row */
			yacc += zoom;
			addr += pitch * (yacc >> 9);
			yacc &= 0x1ff;
		}
	}
}

/*====================================================
Road Rendering
====================================================*/

static void OutrunRenderRoadBackgroundLayer()
{
	UINT16 *roadram = (UINT16*)System16RoadRam;
	int x, y;
	
	for (y = 0; y < 224; y++) {
		unsigned short* pPixel = pTransDraw + (y * 320);
		int data0 = roadram[0x000 + y];
		int data1 = roadram[0x100 + y];
		
		int color = -1;
		
		switch (System16RoadControl & 3) {
			case 0: {
				if (data0 & 0x800) color = data0 & 0x7f;
				break;
			}

			case 1: {
				if (data0 & 0x800) color = data0 & 0x7f;
				else if (data1 & 0x800) color = data1 & 0x7f;
				break;
			}

			case 2: {
				if (data1 & 0x800) color = data1 & 0x7f;
				else if (data0 & 0x800)	color = data0 & 0x7f;
				break;
			}

			case 3: {
				if (data1 & 0x800) color = data1 & 0x7f;
				break;
			}
		}

		if (color != -1) {
			for (x = 0; x < 320; x++) {
				pPixel[x] = color | System16RoadColorOffset3;
			}
		}
	}
}

static void OutrunRenderRoadForegroundLayer()
{
	UINT16 *roadram = (UINT16*)System16RoadRam;
	int x, y;
	
	for (y = 0; y < 224; y++) {
		static const UINT8 priority_map[2][8] =	{
			{ 0x80,0x81,0x81,0x87,0,0,0,0x00 },
			{ 0x81,0x81,0x81,0x8f,0,0,0,0x80 }
		};
	
		unsigned short* pPixel = pTransDraw + (y * 320);
		int data0 = roadram[0x000 + y];
		int data1 = roadram[0x100 + y];
		
		/* if both roads are low priority, skip */
		if ((data0 & 0x800) && (data1 & 0x800))	continue;
		
		int hpos0, hpos1, color0, color1;
		int control = System16RoadControl & 3;
		UINT16 color_table[32];
		UINT8 *src0, *src1;
		UINT8 bgcolor;

		/* get road 0 data */
		src0 = (data0 & 0x800) ? System16Roads + 256 * 2 * 512 : (System16Roads + (0x000 + ((data0 >> 1) & 0xff)) * 512);
		hpos0 = (roadram[0x200 + ((System16RoadControl & 4) ? y : (data0 & 0x1ff))]) & 0xfff;
		color0 = roadram[0x600 + ((System16RoadControl & 4) ? y : (data0 & 0x1ff))];

		/* get road 1 data */
		src1 = (data1 & 0x800) ? System16Roads + 256 * 2 * 512 : (System16Roads + (0x100 + ((data1 >> 1) & 0xff)) * 512);
		hpos1 = (roadram[0x400 + ((System16RoadControl & 4) ? (0x100 + y) : (data1 & 0x1ff))]) & 0xfff;
		color1 = roadram[0x600 + ((System16RoadControl & 4) ? (0x100 + y) : (data1 & 0x1ff))];

		/* determine the 5 colors for road 0 */
		color_table[0x00] = System16RoadColorOffset1 ^ 0x00 ^ ((color0 >> 0) & 1);
		color_table[0x01] = System16RoadColorOffset1 ^ 0x02 ^ ((color0 >> 1) & 1);
		color_table[0x02] = System16RoadColorOffset1 ^ 0x04 ^ ((color0 >> 2) & 1);
		bgcolor = (color0 >> 8) & 0xf;
		color_table[0x03] = (data0 & 0x200) ? color_table[0x00] : (System16RoadColorOffset2 ^ 0x00 ^ bgcolor);
		color_table[0x07] = System16RoadColorOffset1 ^ 0x06 ^ ((color0 >> 3) & 1);

		/* determine the 5 colors for road 1 */
		color_table[0x10] = System16RoadColorOffset1 ^ 0x08 ^ ((color1 >> 4) & 1);
		color_table[0x11] = System16RoadColorOffset1 ^ 0x0a ^ ((color1 >> 5) & 1);
		color_table[0x12] = System16RoadColorOffset1 ^ 0x0c ^ ((color1 >> 6) & 1);
		bgcolor = (color1 >> 8) & 0xf;
		color_table[0x13] = (data1 & 0x200) ? color_table[0x10] : (System16RoadColorOffset2 ^ 0x10 ^ bgcolor);
		color_table[0x17] = System16RoadColorOffset1 ^ 0x0e ^ ((color1 >> 7) & 1);

		/* draw the road */
		switch (control) {
			case 0: {
				if (data0 & 0x800) continue;
				hpos0 = (hpos0 - (0x5f8 + System16RoadXOffset)) & 0xfff;
				for (x = 0; x < 320; x++) {
					int pix0 = (hpos0 < 0x200) ? src0[hpos0] : 3;
					pPixel[x] = color_table[0x00 + pix0];
					hpos0 = (hpos0 + 1) & 0xfff;
				}
				break;
			}

			case 1: {
				hpos0 = (hpos0 - (0x5f8 + System16RoadXOffset)) & 0xfff;
				hpos1 = (hpos1 - (0x5f8 + System16RoadXOffset)) & 0xfff;
				for (x = 0; x < 320; x++) {
					int pix0 = (hpos0 < 0x200) ? src0[hpos0] : 3;
					int pix1 = (hpos1 < 0x200) ? src1[hpos1] : 3;
					if ((priority_map[0][pix0] >> pix1) & 1) {
						pPixel[x] = color_table[0x10 + pix1];
					} else {
						pPixel[x] = color_table[0x00 + pix0];
					}
					hpos0 = (hpos0 + 1) & 0xfff;
					hpos1 = (hpos1 + 1) & 0xfff;
				}
				break;
			}

			case 2: {
				hpos0 = (hpos0 - (0x5f8 + System16RoadXOffset)) & 0xfff;
				hpos1 = (hpos1 - (0x5f8 + System16RoadXOffset)) & 0xfff;
				for (x = 0; x < 320; x++) {
					int pix0 = (hpos0 < 0x200) ? src0[hpos0] : 3;
					int pix1 = (hpos1 < 0x200) ? src1[hpos1] : 3;
					if ((priority_map[1][pix0] >> pix1) & 1) {
						pPixel[x] = color_table[0x10 + pix1];
					} else {
						pPixel[x] = color_table[0x00 + pix0];
					}
					hpos0 = (hpos0 + 1) & 0xfff;
					hpos1 = (hpos1 + 1) & 0xfff;
				}
				break;
			}

			case 3: {
				if (data1 & 0x800) continue;
				hpos1 = (hpos1 - (0x5f8 + System16RoadXOffset)) & 0xfff;
				for (x = 0; x < 320; x++) {
					int pix1 = (hpos1 < 0x200) ? src1[hpos1] : 3;
					pPixel[x] = color_table[0x10 + pix1];
					hpos1 = (hpos1 + 1) & 0xfff;
				}
				break;
			}
		}
	}	
}

static void HangonRenderRoadLayer(int priority)
{
	UINT16 *roadram = (UINT16*)System16RoadRam;
	int x, y;
	
	for (y = 0; y <= 223; y++)
	{
		unsigned short* pPixel = pTransDraw + (y * 320);
		int control = roadram[0x000 + y];
		int ff9j1 = 0, ff9j2 = 0, ctr9m = 0, ctr9n9p = 0, ctr9n9p_ena = 0, ss8j = 0, plycont = 0;
		
		/* the PLYCONT signal controls the road layering */
		plycont = (control >> 10) & 3;
		
		if (plycont != priority) continue;
		
		int hpos = roadram[0x100 + (control & 0xff)];
		int color0 = roadram[0x200 + (control & 0xff)];
		int color1 = roadram[0x300 + (control & 0xff)];
		UINT8 *src;

		/* compute the offset of the road graphics for this line */
		src = System16Roads + (0x000 + (control & 0xff)) * 512;

		/* initialize the 4-bit counter at 9M, which counts bits within each road byte */
		ctr9m = hpos & 7;

		/* initialize the two 4-bit counters at 9P (low) and 9N (high), which count road data bytes */
		ctr9n9p = (hpos >> 3) & 0xff;

		/* initialize the flip-flop at 9J (lower half), which controls the counting direction */
		ff9j1 = (hpos >> 11) & 1;

		/* initialize the flip-flop at 9J (upper half), which controls the background color */
		ff9j2 = 1;

		/* initialize the serial shifter at 8S, which delays several signals after we flip */
		ss8j = 0;

		/* draw this scanline from the beginning */
		for (x = -24; x <= 319; x++)
		{
			int md, color, select;

			/* ---- the following logic all happens constantly ---- */

			/* the enable is controlled by the value in the counter at 9M */
			ctr9n9p_ena = (ctr9m == 7);

			/* if we carried out of the 9P/9N counters, we will forcibly clear the flip-flop at 9J (lower half) */
			if ((ctr9n9p & 0xff) == 0xff)
				ff9j1 = 0;

			/* if the control word bit 8 is clear, we will forcibly set the flip-flop at 9J (lower half) */
			if (!(control & 0x100))
				ff9j1 = 1;

			/* for the Hang On/Super Hang On case only: if the control word bit 9 is clear, we will forcibly */
			/* set the flip-flip at 9J (upper half) */
			if (Hangon && !(control & 0x200))
				ff9j2 = 1;

			/* ---- now process the pixel ---- */
			md = 3;

			/* the Space Harrier/Enduro Racer hardware has a tweak that maps the control word bit 9 to the */
			/* /CE line on the road ROM; use this to effectively disable the road data */
			if (Hangon || !(control & 0x200))

				/* the /OE line on the road ROM is linked to the AND of bits 2 & 3 of the counter at 9N */
				if ((ctr9n9p & 0xc0) == 0xc0)
				{
					/* note that the pixel logic is hidden in a custom at 9S; this is just a guess */
					if (ss8j & 1)
						md = src[((ctr9n9p & 0x3f) << 3) | ctr9m];
					else
						md = src[((ctr9n9p & 0x3f) << 3) | (ctr9m ^ 7)];
				}

			/* "select" is a made-up signal that comes from bit 3 of the serial shifter and is */
			/* used in several places for color selection */
			select = (ss8j >> 3) & 1;

			/* check the flip-flop at 9J (upper half) to determine if we should use the background color; */
			/* the output of this is ANDed with M0 and M1 so it only affects pixels with a value of 3; */
			/* this is done by the AND gates at 9L and 7K */
			if (ff9j2 && md == 3)
			{
				/* in this case, the "select" signal is used to select which background color to use */
				/* since the color0 control word contains two selections */
				color = (color0 >> (select ? 0 : 8)) & 0x3f;
				color |= 0x7c0;
			}

			/* if we're not using the background color, we select pixel data from an alternate path */
			else
			{
				/* the AND gates at 7L, 9K, and 7K clamp the pixel value to 0 if bit 7 of the color 1 */
				/* signal is 1 and if the pixel value is 3 (both M0 and M1 == 1) */
				if ((color1 & 0x80) && md == 3)
					md = 0;

				/* the pixel value plus the "select" line combine to form a mux into the low 8 bits of color1 */
				color = (color1 >> ((md << 1) | select)) & 1;

				/* this value becomes the low bit of the final color; the "select" line itself and the pixel */
				/* value form the other bits */
				color |= select << 3;
				color |= md << 1;
				color |= 0x038;
			}

			/* write the pixel if we're past the minimum clip */
			if (x >= 0)
				pPixel[x] = color;

			/* ---- the following logic all happens on the 6M clock ---- */

			/* clock the counter at 9M */
			ctr9m = (ctr9m + 1) & 7;

			/* if enabled, clock on the two cascaded 4-bit counters at 9P and 9N */
			if (ctr9n9p_ena)
			{
				if (ff9j1)
					ctr9n9p++;
				else
					ctr9n9p--;
			}

			/* clock the flip-flop at 9J (upper half) */
			ff9j2 = !(!ff9j1 && (ss8j & 0x80));

			/* clock the serial shift register at 8J */
			ss8j = (ss8j << 1) | ff9j1;
		}
	}
}





void System16RotateDraw()
{
	UINT16 *pRotateBuff = (UINT16*)System16RotateRamBuff;

	INT32 currx = (pRotateBuff[0x3f0] << 16) | pRotateBuff[0x3f1];
	INT32 curry = (pRotateBuff[0x3f2] << 16) | pRotateBuff[0x3f3];
	INT32 dyy = (pRotateBuff[0x3f4] << 16) | pRotateBuff[0x3f5];
	INT32 dxx = (pRotateBuff[0x3f6] << 16) | pRotateBuff[0x3f7];
	INT32 dxy = (pRotateBuff[0x3f8] << 16) | pRotateBuff[0x3f9];
	INT32 dyx = (pRotateBuff[0x3fa] << 16) | pRotateBuff[0x3fb];
	int x, y;

	/* advance forward based on the clip rect */
	currx += dxx * (0 + 27) + dxy * 0;
	curry += dyx * (0 + 27) + dyy * 0;

	/* loop over screen Y coordinates */
	for (y = 0; y <= 223; y++)
	{
		unsigned short* pPixel = pTransDraw + (y * 320);
		unsigned short* pSrc = pTempDraw;
		INT32 tx = currx;
		INT32 ty = curry;

		/* loop over screen X coordinates */
		for (x = 0; x <= 319; x++)
		{
			/* fetch the pixel from the source bitmap */
			int sx = (tx >> 14) & 0x1ff;
			int sy = (ty >> 14) & 0x1ff;
			int pix = pSrc[sy * 512 + (sx & 0x1ff)];

			/* non-zero pixels get written; everything else is the scanline color */
			if (pix != 0xffff)
			{
				*pPixel++ = ((pix & 0x1ff) | ((pix >> 6) & 0x200) | ((pix >> 3) & 0xc00) | 0x1000) & (System16PaletteEntries - 1);
			}
			else
			{
				*pPixel++ = /*info->colorbase +*/ sy;
			}

			/* advance the source X/Y pointers */
			tx += dxx;
			ty += dyx;
		}

		/* advance the source X/Y pointers */
		currx += dxy;
		curry += dyy;
	}
}


/*====================================================
Palette Generation
====================================================*/

inline static int System16CalcPalette()
{
	int i;

	for (i = 0; i < System16PaletteEntries * 2; i +=2) {
		int r, g, b;
		int nColour = (System16PaletteRam[i + 1] << 8) | System16PaletteRam[i + 0];
	
		r = (nColour & 0x00f) << 1;
		g = (nColour & 0x0f0) >> 2;
		b = (nColour & 0xf00) >> 7;

		if (nColour & 0x1000) r |= 1;
		if (nColour & 0x2000) g |= 2;
		if (nColour & 0x8000) g |= 1;
		if (nColour & 0x4000) b |= 1;
	
		r = (r << 3) | (r >> 2);
		g = (g << 2) | (g >> 4);
		b = (b << 3) | (b >> 2);
		
		System16Palette[i / 2] = BurnHighCol(r, g, b, 0);
		
		r = r * 160 / 256;
		g = g * 160 / 256;
		b = b * 160 / 256;
	
		System16Palette[(i / 2) + System16PaletteEntries] = BurnHighCol(r, g, b, 0);
		System16Palette[(i / 2) + (System16PaletteEntries * 2)] = BurnHighCol(r, g, b, 0);
	}
	
	return 0;
}

/*====================================================
Frame Rendering
====================================================*/

void System16ARender()
{
	if (!System16VideoEnable) {
		BurnTransferClear();
		return;
	}
	
	System16CalcPalette();
	System16ARenderTileLayer(1, 0, 0);
	System16ARenderTileLayer(1, 1, 0);
	System16ARenderSpriteLayer(1);
	System16ARenderTileLayer(1, 0, 1);
	System16ARenderSpriteLayer(2);
	System16ARenderTileLayer(1, 1, 1);
	System16ARenderTileLayer(0, 0, 1);
	System16ARenderSpriteLayer(4);
	System16ARenderTileLayer(0, 1, 1);
	System16ARenderTextLayer(0);
	System16ARenderSpriteLayer(8);
	System16ARenderTextLayer(1);
	BurnTransferCopy(System16Palette);
}

inline static void System16BUpdateTileValues()
{
	for (int i = 0; i < 4; i++) {
		System16Page[i] = ((System16TextRam[0xe80 + (i * 2) + 1] << 8) | System16TextRam[0xe80 + (i * 2) + 0]);
		System16ScrollX[i] = ((System16TextRam[0xe98 + (i * 2) + 1] << 8) | System16TextRam[0xe98 + (i * 2) + 0]);
		System16ScrollY[i] = ((System16TextRam[0xe90 + (i * 2) + 1] << 8) | System16TextRam[0xe90 + (i * 2) + 0]);
	}
}

void System16BRender()
{
	if (!System16VideoEnable) {
		BurnTransferClear();
		return;
	}

	System16BUpdateTileValues();
	
	System16CalcPalette();
	System16BRenderTileLayer(1, 0, 0);
	System16BRenderTileLayer(1, 1, 0);
	System16BRenderSpriteLayer(1);
	System16BRenderTileLayer(1, 0, 1);
	System16BRenderSpriteLayer(2);
	System16BRenderTileLayer(1, 1, 1);
	System16BRenderTileLayer(0, 0, 1);
	System16BRenderSpriteLayer(4);
	System16BRenderTileLayer(0, 1, 1);
	System16BRenderTextLayer(0);
	System16BRenderSpriteLayer(8);
	System16BRenderTextLayer(1);
	BurnTransferCopy(System16Palette);
}

void System16BAltRender()
{
	if (!System16VideoEnable) {
		BurnTransferClear();
		return;
	}

	System16BUpdateTileValues();
	
	System16CalcPalette();
	System16BAltRenderTileLayer(1, 0, 0);
	System16BAltRenderTileLayer(1, 1, 0);
	System16BRenderSpriteLayer(1);
	System16BAltRenderTileLayer(1, 0, 1);
	System16BRenderSpriteLayer(2);
	System16BAltRenderTileLayer(1, 1, 1);
	System16BAltRenderTileLayer(0, 0, 1);
	System16BRenderSpriteLayer(4);
	System16BAltRenderTileLayer(0, 1, 1);
	System16BAltRenderTextLayer(0);
	System16BRenderSpriteLayer(8);
	System16BAltRenderTextLayer(1);
	BurnTransferCopy(System16Palette);
}

void HangonRender()
{
	if (!System16VideoEnable) {
		BurnTransferClear();
		return;
	}
	
	System16CalcPalette();
	
	HangonRenderRoadLayer(0);
	HangonRenderSpriteLayer(1);
	System16ARenderTileLayer(1, 0, 1);
	HangonRenderSpriteLayer(2);
	System16ARenderTileLayer(1, 1, 1);
	System16ARenderTileLayer(0, 0, 1);
	HangonRenderSpriteLayer(4);
	System16ARenderTileLayer(0, 1, 1);
	HangonRenderRoadLayer(1);
	HangonRenderSpriteLayer(8);
	System16ARenderTextLayer(0);
	System16ARenderTextLayer(1);
	BurnTransferCopy(System16Palette);
}

void HangonAltRender()
{
	if (!System16VideoEnable) {
		BurnTransferClear();
		return;
	}
	
	System16CalcPalette();
	
	HangonRenderRoadLayer(0);
	HangonAltRenderSpriteLayer(1);
	System16ARenderTileLayer(1, 0, 1);
	HangonAltRenderSpriteLayer(2);
	System16ARenderTileLayer(1, 1, 1);
	System16ARenderTileLayer(0, 0, 1);
	HangonAltRenderSpriteLayer(4);
	System16ARenderTileLayer(0, 1, 1);
	HangonRenderRoadLayer(1);
	HangonAltRenderSpriteLayer(8);
	System16ARenderTextLayer(0);
	System16ARenderTextLayer(1);
	BurnTransferCopy(System16Palette);
}

void OutrunRender()
{
	if (!System16VideoEnable) {
		BurnTransferClear();
		return;
	}

	System16BUpdateTileValues();
	
	System16CalcPalette();
	OutrunRenderRoadBackgroundLayer();
	OutrunRenderSpriteLayer(1);
	System16BRenderTileLayer(1, 0, 1);
	OutrunRenderSpriteLayer(2);
	System16BRenderTileLayer(1, 1, 1);
	System16BRenderTileLayer(0, 0, 1);
	OutrunRenderSpriteLayer(4);
	System16BRenderTileLayer(0, 1, 1);
	OutrunRenderRoadForegroundLayer();
	System16BRenderTextLayer(0);
	OutrunRenderSpriteLayer(8);
	System16BRenderTextLayer(1);
	BurnTransferCopy(System16Palette);
}

void ShangonRender()
{
	if (!System16VideoEnable) {
		BurnTransferClear();
		return;
	}

	System16BUpdateTileValues();
	
	System16CalcPalette();
	OutrunRenderRoadBackgroundLayer();
	System16BRenderSpriteLayer(1);
	System16BAltRenderTileLayer(1, 0, 1);
	System16BRenderSpriteLayer(2);
	System16BAltRenderTileLayer(1, 1, 1);
	System16BAltRenderTileLayer(0, 0, 1);
	System16BRenderSpriteLayer(4);
	System16BAltRenderTileLayer(0, 1, 1);
	OutrunRenderRoadForegroundLayer();
	System16BRenderSpriteLayer(8);
	System16BAltRenderTextLayer(0);
	System16BAltRenderTextLayer(1);
	BurnTransferCopy(System16Palette);
}

static void draw_gun(int x, int y)
{
	unsigned char gun_data[18][18] = {

#define a 0,
#define b 1,
#define c 2,
#define d 3,
#define e 4,
#define f 5,

		{ a a a a  a a a a  d a a a  a a a a  a a },
		{ a a a a  a a e e  e e e a  a a a a  a a },
		{ a a a a  e e a a  e a a e  e a a a  a a },
		{ a a a e  a a a a  d a a a  a e a a  a a },
		{ a a e a  a a a a  c a a a  a a e a  a a },
		{ a a e a  a a a f  f f a a  a a e a  a a },
		{ a e a a  a a f b  c b f a  a a a e  a a },
		{ a e a a  a f b a  a a a f  a a a e  a a },
		{ d e e d  c f c a  a a c f  c d e e  d a },
		{ a e a a  a f b a  a a a f  b a a e  a a },
		{ a e a a  a a f a  c a f b  a a a e  a a },
		{ a a e a  a a a f  f f b a  a a e a  a a },
		{ a a e a  a a a a  c b a a  a a e a  a a },
		{ a a a e  a a a a  d a a a  a e a a  a a },
		{ a a a a  e e a a  e a a e  e a a a  a a },
		{ a a a a  a a e e  e e e a  a a a a  a a },
		{ a a a a  a a a a  d a a a  a a a a  a a },
		{ a a a a  a a a a  a a a a  a a a a  a a },

#undef f
#undef e
#undef d
#undef c
#undef b
#undef a

	};

	unsigned int gun_palette[] = {
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0x00404040, 0x00808080, 0x00C0C0C0, 0x00FFFFFF, 0, 0
	};

	for (int c = 2; c < 6; c++) {
		gun_palette[c] = BurnHighCol((gun_palette[8 + c] >> 16) & 255,(gun_palette[8 + c] >> 8) & 255,(gun_palette[8 + c] >> 0) & 255, 0);
	}

//	x -= 29;
//	y += 21;

	unsigned char* pTile = pBurnDraw + 320 * nBurnBpp * (y - 1) + nBurnBpp * x;

	for (int y2 = 0; y2 < 17; y2++) {

		pTile += 320 * nBurnBpp;

		if ((y + y2) < 0 || (y + y2) > 223) {
			continue;
		}

		for (int x2 = 0; x2 < 17; x2++) {

			if ((x + x2) < 0 || (x + x2) > 319) {
				continue;
			}

			if (gun_data[y2][x2]) {
				if (nBurnBpp == 2) {
					((unsigned short*)pTile)[x2] = (unsigned short)gun_palette[gun_data[y2][x2]];
				} else {
					((unsigned int*)pTile)[x2] = gun_palette[gun_data[y2][x2]];
				}
			}
		}
	}
}


void XBoardRender()
{
	if (!System16VideoEnable) {
		BurnTransferClear();
		return;
	}

	System16BUpdateTileValues();
	
	System16CalcPalette();
	OutrunRenderRoadBackgroundLayer();
	if (!System16RoadPriority) OutrunRenderRoadForegroundLayer();
	XBoardRenderSpriteLayer(1);
	System16BRenderTileLayer(1, 0, 1);
	XBoardRenderSpriteLayer(2);
	System16BRenderTileLayer(1, 1, 1);
	System16BRenderTileLayer(0, 0, 1);
	XBoardRenderSpriteLayer(4);
	System16BRenderTileLayer(0, 1, 1);
	if (System16RoadPriority) OutrunRenderRoadForegroundLayer();
	System16BRenderTextLayer(0);
	XBoardRenderSpriteLayer(8);
	System16BRenderTextLayer(1);
	BurnTransferCopy(System16Palette);
	if (System16Gun) {
		draw_gun(System16Gun1X >> 8, System16Gun1Y >> 8);
		draw_gun(System16Gun2X >> 8, System16Gun2Y >> 8);
	}
}

void YBoardRender()
{
	if (!System16VideoEnable) {
		BurnTransferClear();
		return;
	}
	
	System16CalcPalette();
	YBoardRenderSpriteLayer();
	System16RotateDraw();
	YBoardSystem16BRenderSpriteLayer();
	BurnTransferCopy(System16Palette);
}
