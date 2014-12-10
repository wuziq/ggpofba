/*
Taito 68000 tiles
=====================
Part of FBAs Taito 68k hardware drivers
Credits: Mame team, Raine team
Coding by KEV, with help from Treble Winner and Jan_Klaassen
*/
#include "taito.h"



int p1scrollx=0,p2scrollx=0;
int p1scrolly=0,p2scrolly=0;

typedef void (*RenderTileFunction)(int,int,int,int);
static RenderTileFunction* RenderTile;
static RenderTileFunction* RenderTileMask;



#include "vid_pc080sn.h"

void PC080SN_bg()
{
	int x=0,y=0,xpos=0,ypos=0,addr=0x0000;
	int flip=0;
	unsigned short dat1,dat2;
	if (nBurnBpp!=nLastTileBpp)
	{
		taitoRecalcPal=1;

		nLastTileBpp=nBurnBpp;
		switch(nBurnBpp) {
		case 2:
			RenderTile=RenderTile16;
			break;
		case 3 :
			RenderTile=RenderTile24;
			break;
		case 4:
			RenderTile=RenderTile32;
			break;
		default:
			break;

	  }

	  }

    for (y=0;y<64;y++)
    {
		if ((((y<<3)-p1scrolly)&0x1ff)<255)
        {
			for (x=0;x<64;x++)
            {
				if ((((x<<3)-p1scrollx)&0x1ff)<345)
                {
					dat2=PC080SN_word_0[addr+2]|(PC080SN_word_0[addr+3]<<8);
                    dat1=((PC080SN_word_0[addr]|PC080SN_word_0[addr+1]<<8));
					flip=(dat1& 0xc000) >> 14;
					xpos=(((x<<3)-p1scrollx)&0x1ff);
					ypos=(((unsigned)((y<<3)-p1scrolly))&255);
					if(xpos>=20&&ypos>=20&&ypos<232&&xpos<324)
					{
						switch(flip){
						case 1:
							RenderTile[1](dat2&0x3FFF,xpos-17,ypos-8,(dat1&0x1ff)<<4);
							break;
						case 2:
							RenderTile[2](dat2&0x3FFF,xpos-16,ypos-9,(dat1&0x1ff)<<4);
							break;
						case 3:
							RenderTile[3](dat2&0x3FFF,xpos-17,ypos-9,(dat1&0x1ff)<<4);
							break;
						default:
							RenderTile[0](dat2&0x3FFF,xpos-16,ypos-8,(dat1&0x1ff)<<4);
							break;
						}
					} else if(xpos>=8&&ypos>=0&&ypos<255&&xpos<340)
					{
						switch(flip){
						case 1:
							RenderTile[5](dat2&0x3FFF,xpos-17,ypos-8,(dat1&0x1ff)<<4);
							break;
						case 2:
							RenderTile[6](dat2&0x3FFF,xpos-16,ypos-9,(dat1&0x1ff)<<4);
							break;
						case 3:
							RenderTile[7](dat2&0x3FFF,xpos-17,ypos-9,(dat1&0x1ff)<<4);
							break;
						default:
							RenderTile[4](dat2&0x3FFF,xpos-16,ypos-8,(dat1&0x1ff)<<4);
							break;
						}
					}

                }
                addr+=4;
			}
		}
		else
			addr+=256;
	}
}

void PC080SN_fg()
{
	int x=0,y=0,xpos=0,ypos=0,addr2=0x8000;
	unsigned short dat1,dat2;
	if (nBurnBpp!=nLastTileMaskBpp)
	{
		nLastTileMaskBpp=nBurnBpp;
		taitoRecalcPal=1;
		switch(nBurnBpp) {
		case 2:
			RenderTileMask=RenderTileMask16;
			break;
		case 3:
			RenderTileMask=RenderTileMask24;
			break;
		case 4:
			RenderTileMask=RenderTileMask32;
			break;
		default:
			break;

	  }

	  }
	for (y=0;y<64;y++)
	{
		if ((((y<<3)-p2scrolly)&0x1ff)<255)
		{
			for (x=0;x<64;x++)
            {
				if ((((x<<3)-p2scrollx)&0x1ff)<345)
                {

					dat2=PC080SN_word_0[addr2+2]|(PC080SN_word_0[addr2+3]<<8);
					dat1=((PC080SN_word_0[addr2]|(PC080SN_word_0[addr2+1]<<8)&0x1f)<<4);
					xpos=(((x<<3)-p2scrollx)&0x1ff);
					ypos=(((y<<3)-p2scrolly)&0x1ff);
					if(xpos>=20&&ypos>=20&&ypos<232&&xpos<324)
					{
						RenderTileMask[0](dat2&0x3FFF,xpos-16,ypos-8,dat1);
					}
					else if(xpos>=8&&ypos>=0&&ypos<255&&xpos<340)
					{
						RenderTileMask[1](dat2&0x3FFF,xpos-16,ypos-8,dat1);
					}
                }
                addr2+=4;
            }
        }
        else
			addr2+=256;
	}
}

/// need to handle priorities correctly and add double width mode
/// for PC080SN at some point (once I find a game that uses it)



