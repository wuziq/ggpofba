#include "burner.h"
#include "ggponet.h"
#include "ggpoclient.h"
#include "ggpo_perfmon.h"
#include "version.h"

GGPOSession *ggpo = NULL;
void QuarkInitPerfMon();
void QuarkPerfMonUpdate(GGPONetworkStats *stats);
bool bSkipPerfmonUpdates = false;
char gDumpSpriteDir[MAX_PATH] = { 0 };

#define MAX_SPRITES 10000

extern int nAcbVersion;
int gSpriteCount = 0;
QuarkSprite gSprites[MAX_SPRITES];

bool bNetGame = false;
char gGameName[128] = { 0 };
extern void QuarkProcessSFA2Sprites(GGPOSession *ggpo, QuarkSprite sprites[], int count);
extern void QuarkProcessVSAVSprites(GGPOSession *ggpo, QuarkSprite sprites[], int count);
extern void QuarkProcessMVSCSprites(GGPOSession *ggpo, QuarkSprite sprites[], int count);
extern void QuarkProcessKOF98Sprites(GGPOSession *ggpo, QuarkSprite sprites[], int count);

bool bReplaySupport = false;
bool bReplayStarted = false;

void
QuarkFinishReplay()
{
   if (!bReplaySupport && bReplayStarted) {
      ggpo_client_set_game_event(ggpo, GGPOCLIENT_GAMEEVENT_FINISHED, NULL);
      bReplayStarted = false;
   }
}

bool
ggpo_on_client_event_callback(GGPOClientEvent *info)
{
   switch (info->code) {
   case GGPOCLIENT_EVENTCODE_CONNECTING:
      VidSSetQuarkConnectStatus("Connecting to Server...");
      break;

   case GGPOCLIENT_EVENTCODE_CONNECTED:
      VidSSetQuarkConnectStatus("Connected");
      break;

   case GGPOCLIENT_EVENTCODE_RETREIVING_MATCHINFO:
      VidSSetQuarkConnectStatus("Retrieving Match Info...");
      break;

   case GGPOCLIENT_EVENTCODE_DISCONNECTED:
      VidSSetQuarkConnectStatus("Disconnected.");
      QuarkFinishReplay();
      break;

   case GGPOCLIENT_EVENTCODE_MATCHINFO:
      VidSSetMatchInfo(info->u.matchinfo.p1,
                       info->u.matchinfo.p2,
                       info->u.matchinfo.blurb);
      break;

   case GGPOCLIENT_EVENTCODE_SPECTATOR_COUNT_CHANGED:
      VidSUpdateSpectatorCount(info->u.spectator_count_changed.count);
      break;

   case GGPOCLIENT_EVENTCODE_CHAT:
   	TCHAR szTemp[128];
	   _sntprintf(szTemp, 128, _T("«%.32hs» "), info->u.chat.username);
	   VidSAddChatMsg(szTemp, 0XFFA000, ANSIToTCHAR(info->u.chat.text, NULL, 0), 0xEEEEEE);
      break;
   }
   return true;
}

bool __cdecl
ggpo_on_event_callback(GGPOEvent *info)
{
   TCHAR status[256];

   if (ggpo_is_client_eventcode(info->code)) {
      return ggpo_on_client_event_callback((GGPOClientEvent *)info);
   }

   switch (info->code) {
   case GGPO_EVENTCODE_CONNECTED_TO_PEER:
      strcpy(status, _T("Connected to peer."));
      VidSSetQuarkConnectStatus(status);
      break;

   case GGPO_EVENTCODE_SYNCHRONIZING_WITH_PEER:
      VidSSetQuarkShowLogo(false);
      sprintf(status, "Synchronizing with peer (%d/%d)...",
              info->u.synchronizing.count, info->u.synchronizing.total);
      VidSSetQuarkConnectStatus(status);
      break;

   case GGPO_EVENTCODE_RUNNING:
      sprintf(status, "");
      VidSSetQuarkConnectStatus(status);
      break;

   case GGPO_EVENTCODE_DISCONNECTED_FROM_PEER:
      sprintf(status, "Disconnected from peer.");
      VidSSetQuarkConnectStatus(status);
      break;

   case GGPO_EVENTCODE_TIMESYNC:
      Sleep(1000 * info->u.timesync.frames_ahead / 60);
      break;
   }
   return true;
}

bool __cdecl
ggpo_begin_game_callback(char *name)
{
   WIN32_FIND_DATA fd;
   char filename[MAX_PATH];
  
   /*
    * Force to 60hz to fix the framerate for network play.
    */
   bForce60Hz = TRUE;
   
   sprintf(filename, "savestates\\%s_ggpo.fs", name);
   if (FindFirstFile(filename, &fd) != INVALID_HANDLE_VALUE) {
      /*
       * Load our save-state file (freeplay, event mode, etc.)
       */
      BurnStateLoad(filename, 1, &DrvInitCallback);
   } else {
      int i;
	   for (i = 0; i < nBurnDrvCount; i++) {
		   nBurnDrvSelect = i;
		   if (_tcscmp(BurnDrvGetText(DRV_NAME), name) == 0) {
			   MediaInit();
			   DrvInit(i, true);
            return true;
		   }
	   }
   }
   sprintf(gGameName, name);
   return false;
}

bool __cdecl
ggpo_advance_frame_callback(int flags)
{
   bSkipPerfmonUpdates = true;
   RunFrame(0, 0);
   bSkipPerfmonUpdates = false;
   return true;
}


void
QuarkProcessEndOfFrame()
{
   ggpo_client_set_game_event(ggpo, GGPOCLIENT_GAMEEVENT_STARTING, game);
}

bool __cdecl
QuarkAlert(char *text)
{
   AudSoundStop();
   MessageBox(hScrnWnd, ANSIToTCHAR(text, NULL, 0), _T(APP_TITLE), MB_OK | MB_SETFOREGROUND);
   return true;
}

static char gAcbBuffer[16 * 1024 * 1024];
static char *gAcbScanPointer;
static int gAcbChecksum;
FILE *gAcbLogFp;

void ComputeIncrementalChecksum(struct BurnArea *pba)
{
   /*
    * Ignore checksums in release builds for now.  It takes a while.
    */
#if defined(FBA_DEBUG)
   int i;

#if 0
   static char *soundAreas[] = {
      "Z80",
      "YM21",
      "nTicksDone",
      "nCyclesExtra",
   };
   /*
    * This is a really crappy checksum routine, but it will do for
    * our purposes
    */
   for (i = 0; i < ARRAYSIZE(soundAreas); i++) {
      if (!strncmp(soundAreas[i], pba->szName, strlen(soundAreas[i]))) {
         return;
      }
   }
#endif

   for (i = 0; i < pba->nLen; i++) {
      int b = ((unsigned char *)pba->Data)[i];
      if (b) {
         if (i % 2) {
            gAcbChecksum *= b;
         } else {
            gAcbChecksum += b * 317;
         }
      } else {
         gAcbChecksum++;
      }
   }
#endif
}

static int __cdecl
QuarkLogAcb(struct BurnArea* pba)
{
   int i, offset;
   fprintf(gAcbLogFp, "%s:", pba->szName);
  
   int col = 10, row = 30;
   for (int i = 0; i < pba->nLen; i++) {
      if ((i % row) == 0) {
         fprintf(gAcbLogFp, "\noffset %9d :", i);
      } else if ((i % col) == 0) {
         fprintf(gAcbLogFp, " - ");
      }
      fprintf(gAcbLogFp, " %02x", ((unsigned char*)pba->Data)[i]);
   }
   fprintf(gAcbLogFp, "\n");
   ComputeIncrementalChecksum(pba);
   return 0;
}

static int __cdecl
QuarkReadAcb(struct BurnArea* pba)
{
   ComputeIncrementalChecksum(pba);
   memcpy(gAcbScanPointer, pba->Data, pba->nLen);
   gAcbScanPointer += pba->nLen;
   return 0;
}
static int __cdecl
QuarkWriteAcb(struct BurnArea* pba)
{
   memcpy(pba->Data, gAcbScanPointer, pba->nLen);
   gAcbScanPointer += pba->nLen;
   return 0;
}

bool __cdecl
ggpo_save_game_state_callback(unsigned char **buffer, int *len, int *checksum, int frame)
{
   int headersize = 3 * sizeof(int);
   int payloadsize;

   gAcbChecksum = 0;
   gAcbScanPointer = gAcbBuffer;
   BurnAcb = QuarkReadAcb;
   BurnAreaScan(ACB_FULLSCAN | ACB_READ, NULL);
   payloadsize = gAcbScanPointer - gAcbBuffer;

   *checksum = gAcbChecksum;
   *len = payloadsize + headersize;
   *buffer = (unsigned char *)malloc(*len);

   ((int *)(*buffer))[0] = 'GGPO';
   ((int *)(*buffer))[1] = headersize;
   ((int *)(*buffer))[2] = nBurnVer;
   memcpy((*buffer) + headersize, gAcbBuffer, payloadsize);
   return true;
}

bool __cdecl
ggpo_load_game_state_callback(unsigned char *buffer, int len)
{
   if (((int *)buffer)[0] == 'GGPO') {
      nAcbVersion = ((int *)buffer)[2];
      buffer += ((int *)buffer)[1];
   } else {
      nAcbVersion = GGPOFBA_VERSION_0_25;
   }
   gAcbScanPointer = (char *)buffer;
   BurnAcb = QuarkWriteAcb;
   BurnAreaScan(ACB_FULLSCAN | ACB_WRITE, NULL);
   nAcbVersion = nBurnVer;
   return true;
}

bool __cdecl
ggpo_log_game_state_callback(char *filename, unsigned char *buffer, int len)
{
   /*
    * Note: this is destructive since it relies on loading game
    * state before scanning!  Luckily, we only call the logging
    * routine for fatal errors (we should still fix this, though).
    */
   ggpo_load_game_state_callback(buffer, len);

   gAcbLogFp = fopen(filename, "w");

   gAcbChecksum = 0;
   BurnAcb = QuarkLogAcb;
   BurnAreaScan(ACB_FULLSCAN | ACB_READ, NULL);
   fprintf(gAcbLogFp, "\n");
   fprintf(gAcbLogFp, "Checksum:       %d\n", gAcbChecksum);
   fprintf(gAcbLogFp, "Buffer Pointer: %p\n", buffer);
   fprintf(gAcbLogFp, "Buffer Len:     %d\n", len);

   fclose(gAcbLogFp);
   return true;
}

void __cdecl 
ggpo_free_buffer_callback(void *buffer)
{
   free(buffer);
}

void
QuarkTogglePerfMon()
{
   static bool initialized = false;
   if (!initialized) {
      ggpoutil_perfmon_init(hScrnWnd);
   }
   ggpoutil_perfmon_toggle();
}

void
QuarkInit(TCHAR *connect)
{
   GGPOSessionCallbacks cb = { 0 };

   bNetGame = TRUE;

   cb.begin_game = ggpo_begin_game_callback;
   cb.load_game_state = ggpo_load_game_state_callback;
   cb.save_game_state = ggpo_save_game_state_callback;
   cb.log_game_state = ggpo_log_game_state_callback;
   cb.free_buffer = ggpo_free_buffer_callback;
   cb.advance_frame = ggpo_advance_frame_callback;
   cb.on_event = ggpo_on_event_callback;

   //cb.Alert = QuarkAlert;

   if (strncmp(connect, "quark:served", strlen("quark:served")) == 0) {
      int port;
      char game[256], match[256];

      sscanf(connect, "quark:served,%[^,],%[^,],%d", game, match, &port);
      ggpo = ggpo_client_connect(&cb, game, match, port);
   } else if (strncmp(connect, "quark:direct", strlen("quark:direct")) == 0) {
      int localPort, remotePort, p1 = 0;
      char ip[128], game[128];

      sscanf(connect, "quark:direct,%[^,],%d,%[^,],%d,%d", game, &localPort, ip, &remotePort, &p1);
      ggpo = ggpo_start_session(&cb, game, localPort, ip, remotePort, p1);
   } else if (strncmp(connect, "quark:synctest", strlen("quark:synctest")) == 0) {
      int frames;
      char game[128];
      sscanf(connect, "quark:synctest,%[^,],%d", game, &frames);
      ggpo = ggpo_start_synctest(&cb, game, frames);
   } else if (strncmp(connect, "quark:stream", strlen("quark:stream")) == 0) {
      char game[256], matchid[256];
      int port;

      sscanf(connect, "quark:stream,%[^,],%[^,],%d", game, matchid, &port);
      ggpo = ggpo_start_streaming(&cb, game, matchid, port);
   } else if (strncmp(connect, "quark:replay", strlen("quark:replay")) == 0) {
      ggpo = ggpo_start_replay(&cb, connect + strlen("quark:replay,"));
   }

   VidSSetQuarkShowLogo(true);
}

bool
QuarkNetworkGame()
{
   return bNetGame;
}

extern "C" void QuarkLog(char *fmt, ...);

void
QuarkLog(char *fmt, ...)
{
   char buf[1024];
   va_list args;

   va_start(args, fmt);
   vsprintf(buf, fmt, args);
   ggpo_logv(ggpo, fmt, args);
   va_end(args);
}

void
QuarkRunIdle()
{
   ggpo_idle(ggpo, 2);
}

bool
QuarkGetInput(void *values, int size, int players)
{
   return ggpo_synchronize_input(ggpo, values, size, players);
}

bool
QuarkIncrementFrame()
{
   ggpo_advance_frame(ggpo);

   if (!bSkipPerfmonUpdates) {
      ggpoutil_perfmon_update(ggpo);
   }

   /*
    * TODO: Don't do any of this for replays or spectating.
    */
   if (gSpriteCount) {
      bReplaySupport = true;
      if (!strcmp(gGameName, "sfa2")) {
         QuarkProcessSFA2Sprites(ggpo, gSprites, gSpriteCount);
      } else if (!strcmp(gGameName, "mvsc")) {
         QuarkProcessMVSCSprites(ggpo, gSprites, gSpriteCount);
      } else if (!strcmp(gGameName, "vsav")) {
         QuarkProcessVSAVSprites(ggpo, gSprites, gSpriteCount);
      } else if (!strcmp(gGameName, "kof98")) {
         QuarkProcessKOF98Sprites(ggpo, gSprites, gSpriteCount);
      }
      gSpriteCount = 0;
   }

   if (!bReplaySupport && !bReplayStarted) {
      bReplayStarted = true;
      ggpo_client_set_game_event(ggpo, GGPOCLIENT_GAMEEVENT_STARTING, game);
   }

#if 0
   *gDumpSpriteDir = '\0';
#endif
   return true;
}

void
QuarkSendChatText(char *text)
{
   ggpo_client_chat(ggpo, text);
}

void
QuarkNotifySpriteDraw(int id, int x, int y, int width, int height)
{
   if (gSpriteCount >= MAX_SPRITES) {
      return;
   }
   gSprites[gSpriteCount].id = id;
   gSprites[gSpriteCount].x = x;
   gSprites[gSpriteCount].y = y;
   gSprites[gSpriteCount].w = width;
   gSprites[gSpriteCount].h = height;
   gSpriteCount++;
   if (*gDumpSpriteDir) {
      static int offset = 0;
      char file[MAX_PATH];
      sprintf(file, "%s\\sprite-%d--%d - %d, %d (%dx%d).bmp", gDumpSpriteDir, offset++, id, x, y, width, height);

      FILE *fp;
      int i, dx, dy;
      BITMAPFILEHEADER bfh = { 0 };
      BITMAPINFOHEADER bih = { 0 };
      FILE *html = NULL;

      bfh.bfType = 'MB';
      bfh.bfSize = sizeof(bfh) + sizeof(bih) + (4 * width * height);
      bfh.bfOffBits = sizeof(bfh) + sizeof(bih);
      bih.biSize = sizeof(bih);
      bih.biWidth = width;
      bih.biHeight = -height;
      bih.biPlanes = 1;
      bih.biBitCount = 32;
      bih.biCompression = BI_RGB;

      fp = fopen(file, "wb");
      fwrite(&bfh, sizeof(bfh), 1, fp);
      fwrite(&bih, sizeof(bih), 1, fp);
      for (i = 0; i < height; i++) {
         if (y + i >= 0 && y + i < 223) {
            fwrite(pBurnDraw + (x * nBurnBpp) + (y + i) * nBurnPitch, 1, nBurnBpp * width, fp);
         } else {
            fwrite(pBurnDraw, 1, nBurnBpp * width, fp);
         }
      }
      fclose(fp);
   }
}

bool
QuarkDumpSprites()
{
   static int offset = 0;
   CreateDirectory("sprite-dump", NULL);
   sprintf(gDumpSpriteDir, "sprite-dump\\frame-%d", offset++);
   CreateDirectory(gDumpSpriteDir, NULL);
   return true;
}
