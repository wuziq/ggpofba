// Sotfware effects

#ifdef BUILD_WIN32
 #define SOFTFX_ENABLE_DIRECTX
#endif
#ifdef BUILD_SDL
 #define SOFTFX_ENABLE_SDL
#endif

#ifdef SOFTFX_ENABLE_DIRECTX
 #include "vid_directx_support.h"
#endif
#ifdef SOFTFX_ENABLE_SDL
 #include <SDL.h>
#endif

TCHAR* VidSoftFXGetEffect(int nEffect);
int VidSoftFXGetZoom(int nEffect);
int VidSoftFXCheckDepth(int nEffect, int nDepth);

void VidSoftFXExit();
int VidSoftFXInit(int nBlitter, int nRotate);

int VidSoftFXScale(RECT* pRect, int nGameWidth, int nGameHeight);

#ifdef SOFTFX_ENABLE_DIRECTX
int VidSoftFXApplyEffectDirectX(IDirectDrawSurface7* pSurf, RECT* pRect);
#endif

#ifdef SOFTFX_ENABLE_SDL
int VidSoftFXApplyEffectSDL(SDL_Surface* pSurf);
#endif
