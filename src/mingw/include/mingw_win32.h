// Additions to the Cygwin/MinGW win32 headers

#undef NM_FIRST
#define NM_FIRST				(0U - 0U)

#if (_WIN32_IE >= 0x0300)
 #define NMLVKEYDOWN			LV_KEYDOWN
#endif

#define MNS_NOCHECK         	(0x80000000)
#define MNS_MODELESS        	(0x40000000)
#define MNS_DRAGDROP        	(0x20000000)
#define MNS_AUTODISMISS     	(0x10000000)
#define MNS_NOTIFYBYPOS     	(0x08000000)
#define MNS_CHECKORBMP      	(0x04000000)

//#define MIM_MAXHEIGHT			(0x00000001)
//#define MIM_BACKGROUND			(0x00000002)
//#define MIM_HELPID				(0x00000004)
//#define MIM_MENUDATA			(0x00000008)
//#define MIM_STYLE				(0x00000010)
//#define MIM_APPLYTOSUBMENUS		(0x80000000)

#define WM_UNINITMENUPOPUP		(0x0125)

#define ENM_SCROLLEVENTS		(8)

// Rich edit
#define ST_DEFAULT				(0)
#define ST_KEEPUNDO				(1)
#define ST_SELECTION			(2)

typedef struct _settextex
{
	DWORD	flags;
	UINT	codepage;
} SETTEXTEX;

// Macro used for handling Window Messages
#define HANDLE_WM_DISPLAYCHANGE(hwnd, wParam, lParam, fn)		\
    ((fn)((hwnd), (UINT)(wParam), (UINT)LOWORD(lParam), (UINT)HIWORD(wParam)), 0L)

#if _WIN32_WINNT < 0x0500
 #define VK_OEM_PLUS	0xBB
 #define VK_OEM_COMMA	0xBC
 #define VK_OEM_MINUS	0xBD
 #define VK_OEM_PERIOD	0xBE
#endif
