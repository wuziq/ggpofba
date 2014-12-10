/*
Taito 68000 sprites
=====================
Part of FBAs Taito 68k hardware drivers
Credits: Mame team, Raine team
Coding by KEV, with help from Treble Winner and Jan_Klaassen
*/
////////////
// 16bit Sprite functions

#ifndef __TAITOSPRITES_H__
#define __TAITOSPRITES_H__

void PC090OJ_blit_16(int number,int colour,int xpos,int ypos)
//				 sprite num, colour, rest is obvious
	{
	int y,x;

	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=tsprites+(number<<8);
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


void PC090OJ_blit_x_16(int number,int colour,int xpos,int ypos)
//				 sprite num, colour, rest is obvious
	{
	unsigned int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal;
	newpal=taito_pal+colour;
	sPix=tsprites+(number<<8);
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

void PC090OJ_blit_y_16(int number,int colour,int xpos,int ypos)
//				 sprite num, colour, rest is obvious
	{
	int y,x;

	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal;
	newpal=taito_pal+colour;
	sPix=tsprites+(number<<8);
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

void PC090OJ_blit_xy_16(int number,int colour,int xpos,int ypos)
//				 sprite num, colour, rest is obvious
{

	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal;
	newpal=taito_pal+colour;
	sPix=tsprites+(number<<8);
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


////
// as above but with clipping

void PC090OJ_blit_clip_16(int number,int colour,int xpos,int ypos)
//				 sprite num, colour, rest is obvious
	{
	int y,x;

	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=tsprites+(number<<8);
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<16; y++)
	{
		for (x=0; x<16; x++, xpos++,pPix+=nBurnBpp,sPix++){
			if ((xpos>=0)&&(xpos<320)&&(ypos>=0)&&(ypos<240)) {
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

void PC090OJ_blit_x_clip_16(int number,int colour,int xpos,int ypos)
//				 sprite num, colour, rest is obvious
	{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal;
	newpal=taito_pal+colour;
	sPix=tsprites+(number<<8);
	xpos+=16;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<16; y++)
	{
		for (x=0; x<16; x++, xpos--,pPix-=nBurnBpp,sPix++){
			if ((xpos>=0)&&(xpos<320)&&(ypos>=0)&&(ypos<240)) {
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

void PC090OJ_blit_y_clip_16(int number,int colour,int xpos,int ypos)
//				 sprite num, colour, rest is obvious
	{
	int y,x;

	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal;
	newpal=taito_pal+colour;
	sPix=tsprites+(number<<8);
	ypos+=16;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<16; y++)
	{
		for (x=0; x<16; x++, xpos++,pPix+=nBurnBpp,sPix++){
			if ((xpos>=0)&&(xpos<320)&&(ypos>=0)&&(ypos<240)) {
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

void PC090OJ_blit_xy_clip_16(int number,int colour,int xpos,int ypos)
//				 sprite num, colour, rest is obvious
{

	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal;
	newpal=taito_pal+colour;
	sPix=tsprites+(number<<8);
	xpos+=16;
	ypos+=16;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<16; y++)
	{
		for (x=0; x<16; x++, xpos--,pPix-=nBurnBpp,sPix++){
			if ((xpos>=0)&&(xpos<320)&&(ypos>=0)&&(ypos<240)) {
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

static RenderSpriteFunction RenderSprite16[8] = {
	&PC090OJ_blit_16,
	&PC090OJ_blit_x_16,
	&PC090OJ_blit_y_16,
	&PC090OJ_blit_xy_16,
	&PC090OJ_blit_clip_16,
	&PC090OJ_blit_x_clip_16,
	&PC090OJ_blit_y_clip_16,
	&PC090OJ_blit_xy_clip_16,
};

/////////
// 32bit Sprite functions

void PC090OJ_blit_32(int number,int colour,int xpos,int ypos)
//				 sprite num, colour, rest is obvious
	{
	int y,x;

	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=tsprites+(number<<8);
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


void PC090OJ_blit_x_32(int number,int colour,int xpos,int ypos)
//				 sprite num, colour, rest is obvious
	{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal;
	newpal=taito_pal+colour;
	sPix=tsprites+(number<<8);
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

void PC090OJ_blit_y_32(int number,int colour,int xpos,int ypos)
//				 sprite num, colour, rest is obvious
	{
	int y,x;

	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal;
	newpal=taito_pal+colour;
	sPix=tsprites+(number<<8);
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

void PC090OJ_blit_xy_32(int number,int colour,int xpos,int ypos)
//				 sprite num, colour, rest is obvious
{

	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal;
	newpal=taito_pal+colour;
	sPix=tsprites+(number<<8);
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


////
// as above but with clipping

void PC090OJ_blit_clip_32(int number,int colour,int xpos,int ypos)
//				 sprite num, colour, rest is obvious
	{
	int y,x;

	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=tsprites+(number<<8);
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<16; y++)
	{
		for (x=0; x<16; x++, xpos++,pPix+=nBurnBpp,sPix++){
			if ((xpos>=0)&&(xpos<320)&&(ypos>=0)&&(ypos<240)) {
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


void PC090OJ_blit_x_clip_32(int number,int colour,int xpos,int ypos)
//				 sprite num, colour, rest is obvious
	{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal;
	newpal=taito_pal+colour;
	sPix=tsprites+(number<<8);
	xpos+=16;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<16; y++)
	{
		for (x=0; x<16; x++, xpos--,pPix-=nBurnBpp,sPix++){
			if ((xpos>=0)&&(xpos<320)&&(ypos>=0)&&(ypos<240)) {
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

void PC090OJ_blit_y_clip_32(int number,int colour,int xpos,int ypos)
//				 sprite num, colour, rest is obvious
	{
	int y,x;

	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal;
	newpal=taito_pal+colour;
	sPix=tsprites+(number<<8);
	ypos+=16;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<16; y++)
	{
		for (x=0; x<16; x++, xpos++,pPix+=nBurnBpp,sPix++){
			if ((xpos>=0)&&(xpos<320)&&(ypos>=0)&&(ypos<240))
				{
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

void PC090OJ_blit_xy_clip_32(int number,int colour,int xpos,int ypos)
//				 sprite num, colour, rest is obvious
{

	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal;
	newpal=taito_pal+colour;
	sPix=tsprites+(number<<8);
	xpos+=16;
	ypos+=16;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<16; y++)
	{
		for (x=0; x<16; x++, xpos--,pPix-=nBurnBpp,sPix++){
			if ((xpos>=0)&&(xpos<320)&&(ypos>=0)&&(ypos<240)) {
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

static RenderSpriteFunction RenderSprite32[8] = {
	&PC090OJ_blit_32,
	&PC090OJ_blit_x_32,
	&PC090OJ_blit_y_32,
	&PC090OJ_blit_xy_32,
	&PC090OJ_blit_clip_32,
	&PC090OJ_blit_x_clip_32,
	&PC090OJ_blit_y_clip_32,
	&PC090OJ_blit_xy_clip_32,
};




/////////
// 24bit Sprite functions

void PC090OJ_blit_24(int number,int colour,int xpos,int ypos)
//				 sprite num, colour, rest is obvious
	{
	int y,x;

	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=tsprites+(number<<8);
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


void PC090OJ_blit_x_24(int number,int colour,int xpos,int ypos)
//				 sprite num, colour, rest is obvious
	{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal;
	newpal=taito_pal+colour;
	sPix=tsprites+(number<<8);
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

void PC090OJ_blit_y_24(int number,int colour,int xpos,int ypos)
//				 sprite num, colour, rest is obvious
	{
	int y,x;

	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal;
	newpal=taito_pal+colour;
	sPix=tsprites+(number<<8);
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

void PC090OJ_blit_xy_24(int number,int colour,int xpos,int ypos)
//				 sprite num, colour, rest is obvious
{

	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal;
	newpal=taito_pal+colour;
	sPix=tsprites+(number<<8);
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


////
// as above but with clipping

void PC090OJ_blit_clip_24(int number,int colour,int xpos,int ypos)
//				 sprite num, colour, rest is obvious
	{
	int y,x;

	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal; // pointer to the pallete at correct offset for this sprite
	newpal=taito_pal+colour;
	sPix=tsprites+(number<<8);
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<16; y++)
	{
		if ((ypos>=0)&&(ypos<240)&&(xpos>=0)&&(xpos<320))
		{
			for (x=0; x<16; x++, xpos++,pPix+=nBurnBpp,sPix++){
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


void PC090OJ_blit_x_clip_24(int number,int colour,int xpos,int ypos)
//				 sprite num, colour, rest is obvious
	{
	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal;
	newpal=taito_pal+colour;
	sPix=tsprites+(number<<8);
	xpos+=16;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<16; y++)
	{
		for (x=0; x<16; x++, xpos--,pPix-=nBurnBpp,sPix++){
			if ((xpos>=0)&&(xpos<320)&&(ypos>=0)&&(ypos<240)) {
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

void PC090OJ_blit_y_clip_24(int number,int colour,int xpos,int ypos)
//				 sprite num, colour, rest is obvious
	{
	int y,x;

	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal;
	newpal=taito_pal+colour;
	sPix=tsprites+(number<<8);
	ypos+=16;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<16; y++)
	{
		for (x=0; x<16; x++, xpos++,pPix+=nBurnBpp,sPix++){
			if ((xpos>=0)&&(xpos<320)&&(ypos>=0)&&(ypos<240)) {
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

void PC090OJ_blit_xy_clip_24(int number,int colour,int xpos,int ypos)
//				 sprite num, colour, rest is obvious
{

	int y,x;
	unsigned char *pPix;
	unsigned char *sPix;
	unsigned int *newpal;
	newpal=taito_pal+colour;
	sPix=tsprites+(number<<8);
	xpos+=16;
	ypos+=16;
	pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
	for (y=0;y<16; y++)
	{
		for (x=0; x<16; x++, xpos--,pPix-=nBurnBpp,sPix++){
			if ((xpos>=0)&&(xpos<320)&&(ypos>=0)&&(ypos<240)) {
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

static RenderSpriteFunction RenderSprite24[8] = {
	&PC090OJ_blit_24,
	&PC090OJ_blit_x_24,
	&PC090OJ_blit_y_24,
	&PC090OJ_blit_xy_24,
	&PC090OJ_blit_clip_24,
	&PC090OJ_blit_x_clip_24,
	&PC090OJ_blit_y_clip_24,
	&PC090OJ_blit_xy_clip_24,
};




#endif


