/*
Part of FBAs Taito 68k hardware drivers
Credits: Mame team, Raine team
Coding by KEV, with help from Treble Winner and Jan_Klaassen

*/
#include "taito.h"

typedef void (*RenderTileFunction)(int,int,int,int);
static RenderTileFunction* RenderTileMask;
static int bankbase=0;
static int tilemask=0;
static int attribfix=0;
static int XSysYMax=224;
static int yOff=8;
unsigned char *SysxTempGfx=NULL;
#include "vid_sysx.h"


void SysXDecode(int tb, int tc, int n)
// Taken from Raine :)
{
    ttiles[tb+0] |= (((tc&0x80)>>7)<<n);
    ttiles[tb+1] |= (((tc&0x40)>>6)<<n);
    ttiles[tb+2] |= (((tc&0x20)>>5)<<n);
    ttiles[tb+3] |= (((tc&0x10)>>4)<<n);
    ttiles[tb+4] |= (((tc&0x08)>>3)<<n);
    ttiles[tb+5] |= (((tc&0x04)>>2)<<n);
    ttiles[tb+6] |= (((tc&0x02)>>1)<<n);
	ttiles[tb+7] |= (((tc&0x01)>>0)<<n);
}



void SysXInit(int game)
{
	init_taito_gfx(); // call to generic taito graphics function reset.
	switch (game)
	{
	case 0:
		XSysYMax=224; //twinhawk
		yOff=8;
		break;
	case 1:
		XSysYMax=240; //gigandes,ballbros??,superman
		yOff=0;
		break;
	default:
		break;
	}

	int ta=0,tb=0,tc=0;
	for(ta=0;ta<0x80000;ta+=2)
	{
		tc=SysxTempGfx[ta+0];
		SysXDecode(tb,tc,0);
		tc=SysxTempGfx[ta+1];
		SysXDecode(tb,tc,1);
		tc=SysxTempGfx[ta+0+0x80000];
		SysXDecode(tb,tc,2);
		tc=SysxTempGfx[ta+1+0x80000];
		SysXDecode(tb,tc,3);
		tb+=16;
		if((tb&0x7F)==0)
			{tb-=0x78;}
		else{if((tb&0x7F)==8)
			{tb-=8;}}

	}
	for(ta=0x100000;ta<0x180000;ta+=2)
	{
		tc=SysxTempGfx[ta+0];
		SysXDecode(tb,tc,0);
		tc=SysxTempGfx[ta+1];
		SysXDecode(tb,tc,1);
		tc=SysxTempGfx[ta+0+0x80000];
		SysXDecode(tb,tc,2);
		tc=SysxTempGfx[ta+1+0x80000];
		SysXDecode(tb,tc,3);
		tb+=16;
		if((tb&0x7F)==0)
			{tb-=0x78;}
		else{if((tb&0x7F)==8)
			{tb-=8;}}

	}
	free(SysxTempGfx);
}
void SysXClearScreen()
{
	unsigned int nColour = taito_pal[0x1f0];

	if (nColour) {
		switch (nBurnBpp) {
			case 4: {
				unsigned int* pClear = (unsigned int*)pBurnDraw;
				for (int i = 0; i < 384 * XSysYMax / 8; i++) {
					*pClear++ = nColour;
					*pClear++ = nColour;
					*pClear++ = nColour;
					*pClear++ = nColour;
					*pClear++ = nColour;
					*pClear++ = nColour;
					*pClear++ = nColour;
					*pClear++ = nColour;
				}
				break;
			}

			case 3: {
				unsigned char* pClear = pBurnDraw;
				unsigned char r = nColour;
				unsigned char g = (r >> 8) & 0xFF;
				unsigned char b = (r >> 16) & 0xFF;
				r &= 0xFF;
				for (int i = 0; i < 384 * XSysYMax; i++) {
					*pClear++ = r;
					*pClear++ = g;
					*pClear++ = b;
				}
				break;
			}

			case 2: {
				unsigned int* pClear = (unsigned int*)pBurnDraw;
				nColour = nColour | (nColour << 16);
				for (int i = 0; i < 384 * XSysYMax / 16; i++) {
					*pClear++ = nColour;
					*pClear++ = nColour;
					*pClear++ = nColour;
					*pClear++ = nColour;
					*pClear++ = nColour;
					*pClear++ = nColour;
					*pClear++ = nColour;
					*pClear++ = nColour;
				}
				break;
			}
		}
	} else {
		memset(pBurnDraw, 0, 384 * XSysYMax * nBurnBpp);
	}
}



void SysXSprites()
// Taken from Mame :)
{
	unsigned short* pSysXVidAtt = ((unsigned short*)sysbvidattr);
	unsigned short* pSysXVidRam = ((unsigned short*)sysbvidram);
	int x=0,y=0,color=0,flip=0;
	if (nBurnBpp!=nLastSpriteMaskBpp)
	{
		nLastSpriteMaskBpp=nBurnBpp;
		taitoRecalcPal=1;
		switch(nBurnBpp) {
		case 2:
			RenderTileMask=RenderTileSysx16;
			break;
		case 3:
			RenderTileMask=RenderTileSysx24;
			break;
		case 4:
			RenderTileMask=RenderTileSysx32;
			break;
		default:
			break;

		}
	}
	for (int i=0x200; i>0; i--)
	{
		unsigned int sprite = pSysXVidRam[i + bankbase]& 0x3fff;
		if (sprite)
		{
			x = ((pSysXVidRam [0x200 + bankbase + i] + 16) &0x1ff)-16;
			y = ((250 - pSysXVidAtt[i]) &0xff)-16-yOff;
			flip = pSysXVidRam[bankbase + i] &0xC000;
			color = (pSysXVidRam[bankbase + i + 0x200] >> 11)<<4;
			if(x>16&&y>8&&y<(XSysYMax-24)&&x<366)
			{
				switch (flip&0xC000){
				case 0xC000:
					RenderTileMask[3](sprite,x,y,color);
					break;
				case 0x4000:
					RenderTileMask[2](sprite,x,y,color);
					break;
				case 0x8000:
					RenderTileMask[1](sprite,x,y,color);
					break;
				default:
					RenderTileMask[0](sprite,x,y,color);
					break;
				}
			}
			else //if (x>=-14&&y>=0&&y<(XSysYMax-8)&&x<384)
			{
			switch (flip&0xC000){
				case 0xC000:
					RenderTileMask[7](sprite,x,y,color);
					break;
				case 0x4000:
					RenderTileMask[6](sprite,x,y,color);
					break;
				case 0x8000:
					RenderTileMask[5](sprite,x,y,color);
					break;
				default:
					RenderTileMask[4](sprite,x,y,color);
					break;
				}
			}
		}
	}

}


void SysXBG()
// Taken from Mame :)
{
	unsigned short* pSysXVidAtt = ((unsigned short*)sysbvidattr);
	unsigned short* pSysXVidRam = ((unsigned short*)sysbvidram);
	int x=0,y=0,x1=0,y1=0,color=0,flip=0;
	if (nBurnBpp!=nLastTileMaskBpp)
	{
		nLastTileMaskBpp=nBurnBpp;
		taitoRecalcPal=1;
		switch(nBurnBpp) {
		case 2:
			RenderTileMask=RenderTileSysx16;
			break;
		case 3:
	//		RenderTileMask=RenderTileMask24;
			break;
		case 4:
	//		RenderTileMask=RenderTileMask32;
			break;
		default:
			break;

		}
	}
	SysXClearScreen();

	bankbase =0;
	tilemask = 0x3fff;
	if (pSysXVidAtt[0x301] &0x40)
		bankbase = 0x1000;
	else
		bankbase = 0x0;
	attribfix = ((pSysXVidAtt[ 0x302 ] &0xff) << 8) |
				((pSysXVidAtt[ 0x303 ] &0xff) << 16);
	for (int i=0; i<(0x200); i+=(0x20))
	{
		x1 = pSysXVidAtt[0x204 + (i>>1)] | (attribfix &0x100);
		y1 = pSysXVidAtt[0x200 + (i>>1)];

		attribfix >>= 1;

		for (int j=i; j<(i + 0x20); j++)
		{
			int tile;

			tile = pSysXVidRam[0x400 + bankbase + j] & tilemask;
			if (tile)
			{
				x = (((x1 + ((j &0x1) << 4)) + 16) &0x1ff)-16;
				y = ((265 - (y1 - ((j &0x1e) << 3))) &0xff)-16-yOff;
				flip = pSysXVidRam[0x400 + bankbase + j] &0xC000;
				color = (pSysXVidRam[0x600 + bankbase + j] >> 11)<<4;
				if(x>16&&y>8&&y<(XSysYMax-24)&&x<366)
				{
					switch (flip&0xC000){
					case 0xC000:
						RenderTileMask[3](tile,x,y,color);
						break;
					case 0x4000:
						RenderTileMask[2](tile,x,y,color);
						break;
					case 0x8000:
						RenderTileMask[1](tile,x,y,color);
						break;
					default:
						RenderTileMask[0](tile,x,y,color);
						break;
					}
				}
				else if (x>=-14&&y>=-14&&y<(XSysYMax-8)&&x<384)
				{
				switch (flip&0xC000){
					case 0xC000:
						RenderTileMask[7](tile,x,y,color);
						break;
					case 0x4000:
						RenderTileMask[6](tile,x,y,color);
						break;
					case 0x8000:
						RenderTileMask[5](tile,x,y,color);
						break;
					default:
						RenderTileMask[4](tile,x,y,color);
						break;
					}//switch
				}//else
			}
		}
	}
}



