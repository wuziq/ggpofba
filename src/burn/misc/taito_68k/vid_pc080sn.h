/*Taito 68000 tiles
=====================
Part of FBAs Taito 68k hardware drivers
Credits: Mame team, Raine team
Coding by KEV, with help from Treble Winner and Jan_Klaassen
*/
#ifndef __TAITOTILES_H__
#define __TAITOTILES_H__

inline void drawtilemask_16(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<6);
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<8; y++)
	{
		for (x=0; x<8; x++, xpos++,pPix+=nBurnBpp,sPix++){
			if (*((unsigned char *)sPix)) {
				*((unsigned short *)pPix)=newpal[*((unsigned char *)sPix)];
			}
		}
		xpos-=8;
		pPix-=(nBurnBpp<<3);
		ypos++;
		pPix+=nBurnPitch;
	}
}

inline void drawtilemask_clip_16(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<6);
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<8; y++)
	{
		if ((ypos>=0)&&(ypos<240))
		{
			for (x=0; x<8; x++, xpos++,pPix+=nBurnBpp,sPix++){
				if ((xpos>=0)&&(xpos<320)) {
					if (*((unsigned char *)sPix)) {
						*((unsigned short *)pPix)=newpal[*((unsigned char *)sPix)];
					}
				}
			}
			xpos-=8;
			pPix-=(nBurnBpp<<3);
		}
		ypos++;
		pPix+=nBurnPitch;
	}
}



inline void drawtile_16(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<6);
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<8; y++)
	{
		for (x=0; x<8; x++, xpos++,pPix+=nBurnBpp,sPix++){
			*((unsigned short *)pPix)=newpal[*((unsigned char *)sPix)];
		}
		xpos-=8;
		pPix-=(nBurnBpp<<3);
		ypos++;
		pPix+=nBurnPitch;
	}
}

inline void drawtile_x_16(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<6);
	xpos+=8;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<8; y++)
	{
		for (x=0; x<8; x++, xpos--,pPix-=nBurnBpp,sPix++){
		   	*((unsigned short *)pPix)=newpal[*((unsigned char *)sPix)];
			}
		xpos+=8;
		pPix+=(nBurnBpp<<3);
		ypos++;
		pPix+=nBurnPitch;
	}
}

inline void drawtile_y_16(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<6);
	ypos+=8;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<8; y++)
	{
		for (x=0; x<8; x++, xpos++,pPix+=nBurnBpp,sPix++){
			*((unsigned short *)pPix)=newpal[*((unsigned char *)sPix)];
		}
		xpos-=8;
		pPix-=(nBurnBpp<<3);
		ypos--;
		pPix-=nBurnPitch;
	}
}

inline void drawtile_xy_16(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<6);
	xpos+=8;
	ypos+=8;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<8; y++)
	{
		for (x=0; x<8; x++, xpos--,pPix-=nBurnBpp,sPix++){
				*((unsigned short *)pPix)=newpal[*((unsigned char *)sPix)];
			}
		xpos+=8;
		pPix+=(nBurnBpp<<3);
		ypos--;
		pPix-=nBurnPitch;
	}
}


/////
// as above bu twith clipping

inline void drawtile_clip_16(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<6);
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<8; y++)
	{
		if ((ypos>=0)&&(ypos<240))
		{
			for (x=0; x<8; x++, xpos++,pPix+=nBurnBpp,sPix++){
				if ((xpos>=0)&&(xpos<320)) {
					*((unsigned short *)pPix)=newpal[*((unsigned char *)sPix)];
				}
			}
			xpos-=8;
			pPix-=(nBurnBpp<<3);
		}
		ypos++;
		pPix+=nBurnPitch;
	}
}

inline void drawtile_x_clip_16(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<6);
	xpos+=8;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<8; y++)
	{
		if ((ypos>=0)&&(ypos<240)){
			for (x=0; x<8; x++, xpos--,pPix-=nBurnBpp,sPix++){
				if ((xpos>=0)&&(xpos<320)) {
				   	*((unsigned short *)pPix)=newpal[*((unsigned char *)sPix)];
				}
			}
			xpos+=8;
			pPix+=(nBurnBpp<<3);
		}
		ypos++;
		pPix+=nBurnPitch;
	}
}

inline void drawtile_y_clip_16(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<6);
	ypos+=8;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<8; y++)
	{
		if ((ypos>=0)&&(ypos<240))
		{
			for (x=0; x<8; x++, xpos++,pPix+=nBurnBpp,sPix++){
				if ((xpos>=0)&&(xpos<320)) {
						*((unsigned short *)pPix)=newpal[*((unsigned char *)sPix)];
				}
			}
			xpos-=8;
			pPix-=(nBurnBpp<<3);
		}
		ypos--;
		pPix-=nBurnPitch;
	}
}

inline void drawtile_xy_clip_16(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<6);
	xpos+=8;
	ypos+=8;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<8; y++)
	{
		if ((ypos>=0)&&(ypos<240))
		{
			for (x=0; x<8; x++, xpos--,pPix-=nBurnBpp,sPix++){
				if ((xpos>=0)&&(xpos<320)) {
					*((unsigned short *)pPix)=newpal[*((unsigned char *)sPix)];
				}
			}
			xpos+=8;
			pPix+=(nBurnBpp<<3);
		}
		ypos--;
		pPix-=nBurnPitch;
	}
}


static RenderTileFunction RenderTile16[8] = {
	&drawtile_16,
	&drawtile_x_16,
	&drawtile_y_16,
	&drawtile_xy_16,
	&drawtile_clip_16,
	&drawtile_x_clip_16,
	&drawtile_y_clip_16,
	&drawtile_xy_clip_16,
};

static RenderTileFunction RenderTileMask16[2] = {
	&drawtilemask_16,
	&drawtilemask_clip_16,
};

inline void drawtilemask_32(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<6);
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<8; y++)
	{
		for (x=0; x<8; x++, xpos++,pPix+=nBurnBpp,sPix++){
			if (*((unsigned char *)sPix)) {
				*((unsigned int *)pPix)=newpal[*((unsigned char *)sPix)];
			}
		}
		xpos-=8;
		pPix-=(nBurnBpp<<3);
		ypos++;
		pPix+=nBurnPitch;
	}
}

inline void drawtilemask_clip_32(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<6);
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<8; y++)
	{
		if ((ypos>=0)&&(ypos<240))
		{
			for (x=0; x<8; x++, xpos++,pPix+=nBurnBpp,sPix++){
				if ((xpos>=0)&&(xpos<320)) {
					if (*((unsigned char *)sPix)) {
						*((unsigned int *)pPix)=newpal[*((unsigned char *)sPix)];
					}
				}
			}
			xpos-=8;
			pPix-=(nBurnBpp<<3);
		}
		ypos++;
		pPix+=nBurnPitch;
	}
}

inline void drawtile_32(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<6);
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<8; y++)
	{
		for (x=0; x<8; x++, xpos++,pPix+=nBurnBpp,sPix++){
			*((unsigned int *)pPix)=newpal[*((unsigned char *)sPix)];
		}
		xpos-=8;
		pPix-=(nBurnBpp<<3);
		ypos++;
		pPix+=nBurnPitch;
	}
}

inline void drawtile_x_32(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<6);
	xpos+=8;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<8; y++)
	{
		for (x=0; x<8; x++, xpos--,pPix-=nBurnBpp,sPix++){
		   	*((unsigned int *)pPix)=newpal[*((unsigned char *)sPix)];
			}
		xpos+=8;
		pPix+=(nBurnBpp<<3);
		ypos++;
		pPix+=nBurnPitch;
	}
}

inline void drawtile_y_32(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<6);
	ypos+=8;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<8; y++)
	{
		for (x=0; x<8; x++, xpos++,pPix+=nBurnBpp,sPix++){
			*((unsigned int *)pPix)=newpal[*((unsigned char *)sPix)];
		}
		xpos-=8;
		pPix-=(nBurnBpp<<3);
		ypos--;
		pPix-=nBurnPitch;
	}
}

inline void drawtile_xy_32(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<6);
	xpos+=8;
	ypos+=8;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<8; y++)
	{
		for (x=0; x<8; x++, xpos--,pPix-=nBurnBpp,sPix++){
				*((unsigned int *)pPix)=newpal[*((unsigned char *)sPix)];
			}
		xpos+=8;
		pPix+=(nBurnBpp<<3);
		ypos--;
		pPix-=nBurnPitch;
	}
}


/////
// as above bu twith clipping

inline void drawtile_clip_32(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<6);
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<8; y++)
	{
		if ((ypos>=0)&&(ypos<240))
		{
			for (x=0; x<8; x++, xpos++,pPix+=nBurnBpp,sPix++){
				if ((xpos>=0)&&(xpos<320)) {
					*((unsigned int *)pPix)=newpal[*((unsigned char *)sPix)];
				}
			}
			xpos-=8;
			pPix-=(nBurnBpp<<3);
		}
		ypos++;
		pPix+=nBurnPitch;
	}
}

inline void drawtile_x_clip_32(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<6);
	xpos+=8;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<8; y++)
	{
		if ((ypos>=0)&&(ypos<240)){
			for (x=0; x<8; x++, xpos--,pPix-=nBurnBpp,sPix++){
				if ((xpos>=0)&&(xpos<320)) {
				   	*((unsigned int *)pPix)=newpal[*((unsigned char *)sPix)];
				}
			}
			xpos+=8;
			pPix+=(nBurnBpp<<3);
		}
		ypos++;
		pPix+=nBurnPitch;
	}
}

inline void drawtile_y_clip_32(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<6);
	ypos+=8;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<8; y++)
	{
		if ((ypos>=0)&&(ypos<240))
		{
			for (x=0; x<8; x++, xpos++,pPix+=nBurnBpp,sPix++){
				if ((xpos>=0)&&(xpos<320)) {
						*((unsigned int *)pPix)=newpal[*((unsigned char *)sPix)];
				}
			}
			xpos-=8;
			pPix-=(nBurnBpp<<3);
		}
		ypos--;
		pPix-=nBurnPitch;
	}
}

inline void drawtile_xy_clip_32(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<6);
	xpos+=8;
	ypos+=8;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<8; y++)
	{
		if ((ypos>=0)&&(ypos<240))
		{
			for (x=0; x<8; x++, xpos--,pPix-=nBurnBpp,sPix++){
				if ((xpos>=0)&&(xpos<320)) {
					*((unsigned int *)pPix)=newpal[*((unsigned char *)sPix)];
				}
			}
			xpos+=8;
			pPix+=(nBurnBpp<<3);
		}
		ypos--;
		pPix-=nBurnPitch;
	}
}


static RenderTileFunction RenderTile32[8] = {
	&drawtile_32,
	&drawtile_x_32,
	&drawtile_y_32,
	&drawtile_xy_32,
	&drawtile_clip_32,
	&drawtile_x_clip_32,
	&drawtile_y_clip_32,
	&drawtile_xy_clip_32,
};

static RenderTileFunction RenderTileMask32[2] = {
	&drawtilemask_32,
	&drawtilemask_clip_32,
};



inline void drawtilemask_24(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<6);
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<8; y++)
	{
		for (x=0; x<8; x++, xpos++,pPix+=nBurnBpp,sPix++){
			if (*((unsigned char *)sPix)) {
			    pPix[0]=(unsigned char) *((unsigned char *)sPix);
				pPix[1]=(unsigned char)(*((unsigned char *)sPix)>>8);
				pPix[2]=(unsigned char)(*((unsigned char *)sPix)>>16);
			}
		}
		xpos-=8;
		pPix-=(nBurnBpp<<3);
		ypos++;
		pPix+=nBurnPitch;
	}
}

inline void drawtilemask_clip_24(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<6);
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<8; y++)
	{
		if ((ypos>=0)&&(ypos<240))
		{
			for (x=0; x<8; x++, xpos++,pPix+=nBurnBpp,sPix++){
				if ((xpos>=0)&&(xpos<320)) {
					if (*((unsigned char *)sPix)) {
			    pPix[0]=(unsigned char) *((unsigned char *)sPix);
				pPix[1]=(unsigned char)(*((unsigned char *)sPix)>>8);
				pPix[2]=(unsigned char)(*((unsigned char *)sPix)>>16);
					}
				}
			}
			xpos-=8;
			pPix-=(nBurnBpp<<3);
		}
		ypos++;
		pPix+=nBurnPitch;
	}
}

inline void drawtile_24(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<6);
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<8; y++)
	{
		for (x=0; x<8; x++, xpos++,pPix+=nBurnBpp,sPix++){
			    pPix[0]=(unsigned char) *((unsigned char *)sPix);
				pPix[1]=(unsigned char)(*((unsigned char *)sPix)>>8);
				pPix[2]=(unsigned char)(*((unsigned char *)sPix)>>16);
		}
		xpos-=8;
		pPix-=(nBurnBpp<<3);
		ypos++;
		pPix+=nBurnPitch;
	}
}

inline void drawtile_x_24(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<6);
	xpos+=8;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<8; y++)
	{
		for (x=0; x<8; x++, xpos--,pPix-=nBurnBpp,sPix++){
			    pPix[0]=(unsigned char) *((unsigned char *)sPix);
				pPix[1]=(unsigned char)(*((unsigned char *)sPix)>>8);
				pPix[2]=(unsigned char)(*((unsigned char *)sPix)>>16);
			}
		xpos+=8;
		pPix+=(nBurnBpp<<3);
		ypos++;
		pPix+=nBurnPitch;
	}
}

inline void drawtile_y_24(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<6);
	ypos+=8;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<8; y++)
	{
		for (x=0; x<8; x++, xpos++,pPix+=nBurnBpp,sPix++){
			    pPix[0]=(unsigned char) *((unsigned char *)sPix);
				pPix[1]=(unsigned char)(*((unsigned char *)sPix)>>8);
				pPix[2]=(unsigned char)(*((unsigned char *)sPix)>>16);
		}
		xpos-=8;
		pPix-=(nBurnBpp<<3);
		ypos--;
		pPix-=nBurnPitch;
	}
}

inline void drawtile_xy_24(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<6);
	xpos+=8;
	ypos+=8;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<8; y++)
	{
		for (x=0; x<8; x++, xpos--,pPix-=nBurnBpp,sPix++){
				    pPix[0]=(unsigned char) *((unsigned char *)sPix);
				pPix[1]=(unsigned char)(*((unsigned char *)sPix)>>8);
				pPix[2]=(unsigned char)(*((unsigned char *)sPix)>>16);
			}
		xpos+=8;
		pPix+=(nBurnBpp<<3);
		ypos--;
		pPix-=nBurnPitch;
	}
}


/////
// as above bu twith clipping

inline void drawtile_clip_24(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<6);
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<8; y++)
	{
		if ((ypos>=0)&&(ypos<240))
		{
			for (x=0; x<8; x++, xpos++,pPix+=nBurnBpp,sPix++){
				if ((xpos>=0)&&(xpos<320)) {
			    pPix[0]=(unsigned char) *((unsigned char *)sPix);
				pPix[1]=(unsigned char)(*((unsigned char *)sPix)>>8);
				pPix[2]=(unsigned char)(*((unsigned char *)sPix)>>16);
				}
			}
			xpos-=8;
			pPix-=(nBurnBpp<<3);
		}
		ypos++;
		pPix+=nBurnPitch;
	}
}

inline void drawtile_x_clip_24(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<6);
	xpos+=8;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<8; y++)
	{
		if ((ypos>=0)&&(ypos<240)){
			for (x=0; x<8; x++, xpos--,pPix-=nBurnBpp,sPix++){
				if ((xpos>=0)&&(xpos<320)) {
				    pPix[0]=(unsigned char) *((unsigned char *)sPix);
				pPix[1]=(unsigned char)(*((unsigned char *)sPix)>>8);
				pPix[2]=(unsigned char)(*((unsigned char *)sPix)>>16);
				}
			}
			xpos+=8;
			pPix+=(nBurnBpp<<3);
		}
		ypos++;
		pPix+=nBurnPitch;
	}
}

inline void drawtile_y_clip_24(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<6);
	ypos+=8;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<8; y++)
	{
		if ((ypos>=0)&&(ypos<240))
		{
			for (x=0; x<8; x++, xpos++,pPix+=nBurnBpp,sPix++){
				if ((xpos>=0)&&(xpos<320)) {
			    pPix[0]=(unsigned char) *((unsigned char *)sPix);
				pPix[1]=(unsigned char)(*((unsigned char *)sPix)>>8);
				pPix[2]=(unsigned char)(*((unsigned char *)sPix)>>16);
				}
			}
			xpos-=8;
			pPix-=(nBurnBpp<<3);
		}
		ypos--;
		pPix-=nBurnPitch;
	}
}

inline void drawtile_xy_clip_24(int number, int xpos, int ypos, int colour)
{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=ttiles+(number<<6);
	xpos+=8;
	ypos+=8;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<8; y++)
	{
		if ((ypos>=0)&&(ypos<240))
		{
			for (x=0; x<8; x++, xpos--,pPix-=nBurnBpp,sPix++){
				if ((xpos>=0)&&(xpos<320)) {
			    pPix[0]=(unsigned char) *((unsigned char *)sPix);
				pPix[1]=(unsigned char)(*((unsigned char *)sPix)>>8);
				pPix[2]=(unsigned char)(*((unsigned char *)sPix)>>16);
				}
			}
			xpos+=8;
			pPix+=(nBurnBpp<<3);
		}
		ypos--;
		pPix-=nBurnPitch;
	}
}


static RenderTileFunction RenderTile24[8] = {
	&drawtile_24,
	&drawtile_x_24,
	&drawtile_y_24,
	&drawtile_xy_24,
	&drawtile_clip_24,
	&drawtile_x_clip_24,
	&drawtile_y_clip_24,
	&drawtile_xy_clip_24,
};

static RenderTileFunction RenderTileMask24[2] = {
	&drawtilemask_24,
	&drawtilemask_clip_24,
};

#endif


