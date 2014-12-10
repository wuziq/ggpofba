/*
Taito 68000 sprites
=====================
Part of FBAs Taito 68k hardware drivers
Credits: Mame team, Raine team
Coding by KEV, with help from Treble Winner and Jan_Klaassen
*/
#include "taito.h"
unsigned char *PC080SN_word_0,*PC080SN_yscroll_word_0,*PC080SN_xscroll_word_0,*PC080SN_ctrl_word_0;
unsigned char *PC090OJ_word_0;
unsigned char *PC090OJ_spritectrl;
unsigned int *taito_pal;
typedef void (*RenderSpriteFunction)(int,int,int,int);
static RenderSpriteFunction* RenderSprite;
static char gunRecalcPal;

int rCyclesDone[3];

#include "vid_pc090oj.h"

void PC090OJ_draw_sprites()
{

	unsigned char spritecolbank=0;
	unsigned int  x=0, y=0;
	int code=0,color=0;
	int flip=0;
	if (nBurnBpp!=nLastSpriteBpp)
	{
		nLastSpriteBpp=nBurnBpp;
		taitoRecalcPal=1;
		gunRecalcPal=1;
		switch(nBurnBpp) {
		case 2:
			RenderSprite=RenderSprite16;
			break;
		case 3:
			RenderSprite=RenderSprite24;
			break;
		case 4:
			RenderSprite=RenderSprite32;
			break;
		default:
			break;
		}
	}
	spritecolbank=(((PC090OJ_spritectrl[0]&0xe0) >> 5)& 0xf);
	for (int c=0,addr = 0x7F8; c<256; c++, addr-=8)
	{
		code=(PC090OJ_word_0[addr+4]|(PC090OJ_word_0[addr+5]<<8))&0x1fff;
		if (code<5120)
		{
			x=(PC090OJ_word_0[addr+6]|(PC090OJ_word_0[addr+7]<<8))&0x1ff;
			y=(PC090OJ_word_0[addr+2]|(PC090OJ_word_0[addr+3]<<8))&0x1ff;
			if (x>0x140){
				x -= 0x200;
			}
			if (y>0x140)
				y -= 0x200;

			color=(PC090OJ_word_0[addr]&0x0F|spritecolbank<<4)<<4;
			flip=PC090OJ_word_0[addr+1]&0xC0;

			if (x>=16&&y>=16&&x<304&&y<230) {
				switch (flip&0xC0){
				case 0xC0:
					//PC090OJ_blit_xy(code,color,x,y-8);
					RenderSprite[3](code,color,x,y-8);
					break;
				case 0x40:
				//	PC090OJ_blit_x(code,color,x-1,y-8);
					RenderSprite[1](code,color,x-1,y-8);
					break;
				case 0x80:
				//	PC090OJ_blit_y(code,color,x,y-8);
					RenderSprite[2](code,color,x,y-8);
					break;
				default:
				//	PC090OJ_blit(code,color,x,y-8);
					RenderSprite[0](code,color,x,y-8);
					break;
				}
			}
			else
				{
				switch (flip&0xC0){
				case 0xC0:
				//	PC090OJ_blit_xy_clip(code,color,x,y-8);
					RenderSprite[7](code,color,x,y-8);
					break;
				case 0x40:
				//	PC090OJ_blit_x_clip(code,color,x-1,y-8);
					RenderSprite[5](code,color,x-1,y-8);
					break;
				case 0x80:
				//	PC090OJ_blit_y_clip(code,color,x,y-8);
					RenderSprite[6](code,color,x,y-8);
					break;
				default:
					RenderSprite[4](code,color,x,y-8);
				//	PC090OJ_blit_clip(code,color,x,y-8);
					break;
				}

			}
		}
	}
}

void init_gun()
{
	gunRecalcPal = 1;
}

void draw_gun(int x, int y)
{
	static unsigned char gun_data[18][18] = {

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

	static unsigned int gun_palette[] = {
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0x00404040, 0x00808080, 0x00C0C0C0, 0x00FFFFFF, 0, 0
	};

	if (gunRecalcPal) {
		gunRecalcPal = 0;
		for (int c = 2; c < 6; c++) {
			gun_palette[c] = BurnHighCol((gun_palette[8 + c] >> 16) & 255,(gun_palette[8 + c] >> 8) & 255,(gun_palette[8 + c] >> 0) & 255, 0);
		}
	}

	x -= 29;
	y += 21;

	unsigned char* pTile = pBurnDraw + 320 * nBurnBpp * (y - 1) + nBurnBpp * x;

	for (int y2 = 0; y2 < 17; y2++) {

		pTile += 320 * nBurnBpp;

		if ((y + y2) < 0 || (y + y2) > 239) {
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
