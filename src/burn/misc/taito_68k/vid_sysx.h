/*
Part of FBAs Taito 68k hardware drivers
Credits: Mame team, Raine team
Coding by KEV, with help from Treble Winner and Jan_Klaassen
*/
#ifndef __VID_SYSX_H__
#define __VID_SYSX_H__
inline void Sysxtile_16(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<8);
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<16; y++)
	{
		for (x=0; x<16; x++, xpos++,pPix+=nBurnBpp,sPix++){
				if (*((unsigned char *)sPix)) {
			   		*((unsigned short *)pPix)=newpal[*((unsigned char *)sPix)];
				}
		}
		xpos-=16;
		pPix-=(nBurnBpp<<4);
		ypos++;
		pPix+=nBurnPitch;
	}

}

inline void Sysxtile_x_16(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<8);
	xpos+=16;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<16; y++)
	{
		for (x=0; x<16; x++, xpos--,pPix-=nBurnBpp,sPix++){
				if (*((unsigned char *)sPix)) {
			   		*((unsigned short *)pPix)=newpal[*((unsigned char *)sPix)];
				}
			}
		xpos+=16;
		pPix+=(nBurnBpp<<4);
		ypos++;
		pPix+=nBurnPitch;
	}
}

inline void Sysxtile_y_16(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<8);
	ypos+=16;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<16; y++)
	{
		for (x=0; x<16; x++, xpos++,pPix+=nBurnBpp,sPix++){
				if (*((unsigned char *)sPix)) {
			   		*((unsigned short *)pPix)=newpal[*((unsigned char *)sPix)];
				}
		}
		xpos-=16;
		pPix-=(nBurnBpp<<4);
		ypos--;
		pPix-=nBurnPitch;
	}
}

inline void Sysxtile_xy_16(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<8);
	xpos+=16;
	ypos+=16;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<16; y++)
	{
		for (x=0; x<16; x++, xpos--,pPix-=nBurnBpp,sPix++){
				if (*((unsigned char *)sPix)) {
			   		*((unsigned short *)pPix)=newpal[*((unsigned char *)sPix)];
				}
			}
		xpos+=16;
		pPix+=(nBurnBpp<<4);
		ypos--;
		pPix-=nBurnPitch;
	}
}


/////
// as above bu twith clipping

inline void Sysxtile_clip_16(int number, int xpos, int ypos, int colour)
{
	int y,x;

	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<8);
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<16; y++)
	{
		for (x=0; x<16; x++, xpos++,pPix+=nBurnBpp,sPix++){
			if ((xpos>=0)&&(xpos<384)&&(ypos>=0)&&(ypos<XSysYMax)) {
				if (*((unsigned char *)sPix)) {
			   		*((unsigned short *)pPix)=newpal[*((unsigned char *)sPix)];
				}
			}
		}
		xpos-=16;
		pPix-=(nBurnBpp<<4);
		ypos++;
		pPix+=nBurnPitch;
	}
}

inline void Sysxtile_x_clip_16(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<8);
	xpos+=16;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<16; y++)
	{
		for (x=0; x<16; x++, xpos--,pPix-=nBurnBpp,sPix++){
			if ((xpos>=0)&&(xpos<384)&&(ypos>=0)&&(ypos<XSysYMax)) {
			if (*((unsigned char *)sPix)) {
		   		*((unsigned short *)pPix)=newpal[*((unsigned char *)sPix)];
				}
			}
		}
		xpos+=16;
		pPix+=(nBurnBpp<<4);
		ypos++;
		pPix+=nBurnPitch;
	}

}

inline void Sysxtile_y_clip_16(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<8);
	ypos+=16;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<16; y++)
	{
		for (x=0; x<16; x++, xpos++,pPix+=nBurnBpp,sPix++){
			if ((xpos>=0)&&(xpos<384)&&(ypos>=0)&&(ypos<XSysYMax)) {
				if (*((unsigned char *)sPix)) {
					*((unsigned short *)pPix)=newpal[*((unsigned char *)sPix)];
				}
			}
		}
		xpos-=16;
		pPix-=(nBurnBpp<<4);
		ypos--;
		pPix-=nBurnPitch;
	}

}

inline void Sysxtile_xy_clip_16(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<8);
	xpos+=16;
	ypos+=16;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<16; y++)
	{
		for (x=0; x<16; x++, xpos--,pPix-=nBurnBpp,sPix++){
			if ((xpos>=0)&&(xpos<384)&&(ypos>=0)&&(ypos<XSysYMax)) {
				if (*((unsigned char *)sPix)) {
			   		*((unsigned short *)pPix)=newpal[*((unsigned char *)sPix)];
				}
			}
		}
		xpos+=16;
		pPix+=(nBurnBpp<<4);
		ypos--;
		pPix-=nBurnPitch;
	}
}


static RenderTileFunction RenderTileSysx16[8] = {
	&Sysxtile_16,
	&Sysxtile_x_16,
	&Sysxtile_y_16,
	&Sysxtile_xy_16,
	&Sysxtile_clip_16,
	&Sysxtile_x_clip_16,
	&Sysxtile_y_clip_16,
	&Sysxtile_xy_clip_16,
};
///// 32bit functions



inline void Sysxtile_32(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<8);
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<16; y++)
	{
		for (x=0; x<16; x++, xpos++,pPix+=nBurnBpp,sPix++){
				if (*((unsigned char *)sPix)) {
			   		*((unsigned int *)pPix)=newpal[*((unsigned char *)sPix)];
				}
		}
		xpos-=16;
		pPix-=(nBurnBpp<<4);
		ypos++;
		pPix+=nBurnPitch;
	}

}

inline void Sysxtile_x_32(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<8);
	xpos+=16;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<16; y++)
	{
		for (x=0; x<16; x++, xpos--,pPix-=nBurnBpp,sPix++){
				if (*((unsigned char *)sPix)) {
			   		*((unsigned int *)pPix)=newpal[*((unsigned char *)sPix)];
				}
			}
		xpos+=16;
		pPix+=(nBurnBpp<<4);
		ypos++;
		pPix+=nBurnPitch;
	}
}

inline void Sysxtile_y_32(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<8);
	ypos+=16;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<16; y++)
	{
		for (x=0; x<16; x++, xpos++,pPix+=nBurnBpp,sPix++){
				if (*((unsigned char *)sPix)) {
			   		*((unsigned int *)pPix)=newpal[*((unsigned char *)sPix)];
				}
		}
		xpos-=16;
		pPix-=(nBurnBpp<<4);
		ypos--;
		pPix-=nBurnPitch;
	}
}

inline void Sysxtile_xy_32(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<8);
	xpos+=16;
	ypos+=16;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<16; y++)
	{
		for (x=0; x<16; x++, xpos--,pPix-=nBurnBpp,sPix++){
				if (*((unsigned char *)sPix)) {
			   		*((unsigned int *)pPix)=newpal[*((unsigned char *)sPix)];
				}
			}
		xpos+=16;
		pPix+=(nBurnBpp<<4);
		ypos--;
		pPix-=nBurnPitch;
	}
}


/////
// as above but with clipping

inline void Sysxtile_clip_32(int number, int xpos, int ypos, int colour)
{
	int y,x;

	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<8);
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<16; y++)
	{
		for (x=0; x<16; x++, xpos++,pPix+=nBurnBpp,sPix++){
			if ((xpos>=0)&&(xpos<384)&&(ypos>=0)&&(ypos<XSysYMax)) {
				if (*((unsigned char *)sPix)) {
			   		*((unsigned int *)pPix)=newpal[*((unsigned char *)sPix)];
				}
			}
		}
		xpos-=16;
		pPix-=(nBurnBpp<<4);
		ypos++;
		pPix+=nBurnPitch;
	}
}

inline void Sysxtile_x_clip_32(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<8);
	xpos+=16;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<16; y++)
	{
		for (x=0; x<16; x++, xpos--,pPix-=nBurnBpp,sPix++){
			if ((xpos>=0)&&(xpos<384)&&(ypos>=0)&&(ypos<XSysYMax)) {
			if (*((unsigned char *)sPix)) {
		   		*((unsigned int *)pPix)=newpal[*((unsigned char *)sPix)];
				}
			}
		}
		xpos+=16;
		pPix+=(nBurnBpp<<4);
		ypos++;
		pPix+=nBurnPitch;
	}

}

inline void Sysxtile_y_clip_32(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<8);
	ypos+=16;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<16; y++)
	{
		for (x=0; x<16; x++, xpos++,pPix+=nBurnBpp,sPix++){
			if ((xpos>=0)&&(xpos<384)&&(ypos>=0)&&(ypos<XSysYMax)) {
				if (*((unsigned char *)sPix)) {
					*((unsigned int *)pPix)=newpal[*((unsigned char *)sPix)];
				}
			}
		}
		xpos-=16;
		pPix-=(nBurnBpp<<4);
		ypos--;
		pPix-=nBurnPitch;
	}

}

inline void Sysxtile_xy_clip_32(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<8);
	xpos+=16;
	ypos+=16;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<16; y++)
	{
		for (x=0; x<16; x++, xpos--,pPix-=nBurnBpp,sPix++){
			if ((xpos>=0)&&(xpos<384)&&(ypos>=0)&&(ypos<XSysYMax)) {
				if (*((unsigned char *)sPix)) {
			   		*((unsigned int *)pPix)=newpal[*((unsigned char *)sPix)];
				}
			}
		}
		xpos+=16;
		pPix+=(nBurnBpp<<4);
		ypos--;
		pPix-=nBurnPitch;
	}
}


static RenderTileFunction RenderTileSysx32[8] = {
	&Sysxtile_32,
	&Sysxtile_x_32,
	&Sysxtile_y_32,
	&Sysxtile_xy_32,
	&Sysxtile_clip_32,
	&Sysxtile_x_clip_32,
	&Sysxtile_y_clip_32,
	&Sysxtile_xy_clip_32,
};

// 24 bit funcs (untested)

inline void Sysxtile_24(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<8);
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<16; y++)
	{
		for (x=0; x<16; x++, xpos++,pPix+=nBurnBpp,sPix++){
				if (*((unsigned char *)sPix)) {
			    pPix[0]=(unsigned char) *((unsigned char *)sPix);
				pPix[1]=(unsigned char)(*((unsigned char *)sPix)>>8);
				pPix[2]=(unsigned char)(*((unsigned char *)sPix)>>16);
				}
		}
		xpos-=16;
		pPix-=(nBurnBpp<<4);
		ypos++;
		pPix+=nBurnPitch;
	}

}

inline void Sysxtile_x_24(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<8);
	xpos+=16;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<16; y++)
	{
		for (x=0; x<16; x++, xpos--,pPix-=nBurnBpp,sPix++){
				if (*((unsigned char *)sPix)) {
			    pPix[0]=(unsigned char) *((unsigned char *)sPix);
				pPix[1]=(unsigned char)(*((unsigned char *)sPix)>>8);
				pPix[2]=(unsigned char)(*((unsigned char *)sPix)>>16);
				}
			}
		xpos+=16;
		pPix+=(nBurnBpp<<4);
		ypos++;
		pPix+=nBurnPitch;
	}
}

inline void Sysxtile_y_24(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<8);
	ypos+=16;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<16; y++)
	{
		for (x=0; x<16; x++, xpos++,pPix+=nBurnBpp,sPix++){
				if (*((unsigned char *)sPix)) {
			    pPix[0]=(unsigned char) *((unsigned char *)sPix);
				pPix[1]=(unsigned char)(*((unsigned char *)sPix)>>8);
				pPix[2]=(unsigned char)(*((unsigned char *)sPix)>>16);
				}
		}
		xpos-=16;
		pPix-=(nBurnBpp<<4);
		ypos--;
		pPix-=nBurnPitch;
	}
}

inline void Sysxtile_xy_24(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<8);
	xpos+=16;
	ypos+=16;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<16; y++)
	{
		for (x=0; x<16; x++, xpos--,pPix-=nBurnBpp,sPix++){
				if (*((unsigned char *)sPix)) {
			    pPix[0]=(unsigned char) *((unsigned char *)sPix);
				pPix[1]=(unsigned char)(*((unsigned char *)sPix)>>8);
				pPix[2]=(unsigned char)(*((unsigned char *)sPix)>>16);
				}
			}
		xpos+=16;
		pPix+=(nBurnBpp<<4);
		ypos--;
		pPix-=nBurnPitch;
	}
}


/////
// as above but with clipping

inline void Sysxtile_clip_24(int number, int xpos, int ypos, int colour)
{
	int y,x;

	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<8);
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<16; y++)
	{
		for (x=0; x<16; x++, xpos++,pPix+=nBurnBpp,sPix++){
			if ((xpos>=0)&&(xpos<384)&&(ypos>=0)&&(ypos<XSysYMax)) {
				if (*((unsigned char *)sPix)) {
			    pPix[0]=(unsigned char) *((unsigned char *)sPix);
				pPix[1]=(unsigned char)(*((unsigned char *)sPix)>>8);
				pPix[2]=(unsigned char)(*((unsigned char *)sPix)>>16);
				}
			}
		}
		xpos-=16;
		pPix-=(nBurnBpp<<4);
		ypos++;
		pPix+=nBurnPitch;
	}
}

inline void Sysxtile_x_clip_24(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<8);
	xpos+=16;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<16; y++)
	{
		for (x=0; x<16; x++, xpos--,pPix-=nBurnBpp,sPix++){
			if ((xpos>=0)&&(xpos<384)&&(ypos>=0)&&(ypos<XSysYMax)) {
			if (*((unsigned char *)sPix)) {
			    pPix[0]=(unsigned char) *((unsigned char *)sPix);
				pPix[1]=(unsigned char)(*((unsigned char *)sPix)>>8);
				pPix[2]=(unsigned char)(*((unsigned char *)sPix)>>16);
				}
			}
		}
		xpos+=16;
		pPix+=(nBurnBpp<<4);
		ypos++;
		pPix+=nBurnPitch;
	}

}

inline void Sysxtile_y_clip_24(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<8);
	ypos+=16;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<16; y++)
	{
		for (x=0; x<16; x++, xpos++,pPix+=nBurnBpp,sPix++){
			if ((xpos>=0)&&(xpos<384)&&(ypos>=0)&&(ypos<XSysYMax)) {
				if (*((unsigned char *)sPix)) {
			    pPix[0]=(unsigned char) *((unsigned char *)sPix);
				pPix[1]=(unsigned char)(*((unsigned char *)sPix)>>8);
				pPix[2]=(unsigned char)(*((unsigned char *)sPix)>>16);
				}
			}
		}
		xpos-=16;
		pPix-=(nBurnBpp<<4);
		ypos--;
		pPix-=nBurnPitch;
	}

}

inline void Sysxtile_xy_clip_24(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<8);
	xpos+=16;
	ypos+=16;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<16; y++)
	{
		for (x=0; x<16; x++, xpos--,pPix-=nBurnBpp,sPix++){
			if ((xpos>=0)&&(xpos<384)&&(ypos>=0)&&(ypos<XSysYMax)) {
				if (*((unsigned char *)sPix)) {
			    pPix[0]=(unsigned char) *((unsigned char *)sPix);
				pPix[1]=(unsigned char)(*((unsigned char *)sPix)>>8);
				pPix[2]=(unsigned char)(*((unsigned char *)sPix)>>16);
				}
			}
		}
		xpos+=16;
		pPix+=(nBurnBpp<<4);
		ypos--;
		pPix-=nBurnPitch;
	}
}


static RenderTileFunction RenderTileSysx24[8] = {
	&Sysxtile_24,
	&Sysxtile_x_24,
	&Sysxtile_y_24,
	&Sysxtile_xy_24,
	&Sysxtile_clip_24,
	&Sysxtile_x_clip_24,
	&Sysxtile_y_clip_24,
	&Sysxtile_xy_clip_24,
};

#endif



