#include "burner.h"
#include "ggpoclient.h"

#define STATE_IDLE         0
#define STATE_STARTING     1
#define STATE_RUNNING      2

static struct {
   int state;
   char *game;
   struct {
      char *c[2];
      int   rounds;
   } p[2];
} GameInfo = { 0 };

static bool
SpriteInList(const QuarkSpriteInfo *s, QuarkSprite sprites[], int count)
{
   int i;
   for (i = 0; i < count; i++) {
      if (sprites[i].id == s->id &&
          sprites[i].x == s->x &&
          sprites[i].y == s->y) {
         return true;
      }
   }
   return false;
}

static int
QuarkFindSprite(QuarkSprite sprites[], int count, int x, int y)
{
   int i;
   for (i = 0; i < count; i++) {
      if (sprites[i].x == x &&
          sprites[i].y == y) {
         return sprites[i].id;
      }
   }
   return false;
}


static void
QuarkSpriteStartNewGame(GGPOSession *ggpo, char *game)
{
   for (int i = 0; i < 2; i++) {
      GameInfo.p[i].rounds = 0;
      for (int j = 0; j < 2; j++) {
         GameInfo.p[i].c[j] = NULL;
      }
   }
   ggpo_client_set_game_event(ggpo, GGPOCLIENT_GAMEEVENT_STARTING, game);
}

static void
QuarkSpriteFinishGame(GGPOSession *ggpo)
{
   static char p1name[256];
   static char p2name[256];
   sprintf(p1name, "%s | %s", GameInfo.p[0].c[0] ? GameInfo.p[0].c[0] : "* Unknown *",
                              GameInfo.p[0].c[1] ? GameInfo.p[0].c[1] : "* Unknown *");
   sprintf(p2name, "%s | %s", GameInfo.p[1].c[0] ? GameInfo.p[1].c[0] : "* Unknown *",
                              GameInfo.p[1].c[1] ? GameInfo.p[1].c[1] : "* Unknown *");

   ggpo_client_set_game_event(ggpo, GGPOCLIENT_GAMEEVENT_PLAYER_1, (void *)p1name);
   ggpo_client_set_game_event(ggpo, GGPOCLIENT_GAMEEVENT_PLAYER_2, (void *)p2name);
   ggpo_client_set_game_event(ggpo, GGPOCLIENT_GAMEEVENT_PLAYER_1_SCORE, (void *)GameInfo.p[0].rounds);
   ggpo_client_set_game_event(ggpo, GGPOCLIENT_GAMEEVENT_PLAYER_2_SCORE, (void *)GameInfo.p[1].rounds);
   ggpo_client_set_game_event(ggpo, GGPOCLIENT_GAMEEVENT_WINNER, (void *)(GameInfo.p[0].rounds > GameInfo.p[1].rounds ? 1 : 2));
   ggpo_client_set_game_event(ggpo, GGPOCLIENT_GAMEEVENT_FINISHED, NULL);
}

/*
 * A little state machine with match info should go here...
 */

void
QuarkProcessMVSCSprites(GGPOSession *ggpo, QuarkSprite sprites[], int count)
{   
  /*
   * P1, Round 1:  17x 28 (blank: 42016)
   * P1, Round 2:  32x 28 
   * P2, Round 2: 336x 28
   * P2, Round 1: 352x 28
   *
   *       {"Ryu: 109x29 (3x1) 
   */

   /*
    * These are the nameplates for all the characters you can select.
    */
   static const struct {
      char *character;
      int id;
   } search[] = {
      {"Roll",             28092 },
      {"Roll",             28245 },
      {"Ryu",              28094 },
      {"Ryu",              28247 },
      {"Chun Li",          28120 },
      {"Chun Li",          28264 },
      {"Zangief",          28320 },
      {"Zangief",          28268 },
      {"Morrigan",         28280 },
      {"Morrigan",         28336 },
      {"Captain Commando", 28112 },
      {"Captain Commando", 28256 },
      {"Megaman",          28124 },
      {"Megaman",          28344 },
      {"Strider-Hiryu",    28104 },
      {"Strider-Hiryu",    28249 }, 
      {"Spiderman",        28240 },
      {"Spiderman",        28099 },
      {"Jin",              28278 },
      {"Jin",              28332 },
      {"Captain America",  28144 },
      {"Captain America",  28080 },
      {"Hulk",             28138 },
      {"Hulk",             28077 },
      {"Venom",            28074 },
      {"Venom",            28156 },
      {"War Machine",      28069 },
      {"War Machine",      28133 },
      {"Gambit",           28096 },
      {"Gambit",           28140 },
      {"Wolverine",        28087 },
      {"Wolverine",        28151 },
   };

   static const QuarkSpriteInfo startSprite =  { 46614, 136, 0 };
   static const QuarkSpriteInfo finishSprite = { 59888, 128, 128 }; 

   /*
    * See if it's time to start a new game...
    */
   if (GameInfo.state == STATE_IDLE) {
      if (SpriteInList(&startSprite, sprites, count)) {
         GameInfo.state = STATE_STARTING;
      }
   } else if (GameInfo.state == STATE_STARTING) {
      if (!SpriteInList(&startSprite, sprites, count)) {
         QuarkSpriteStartNewGame(ggpo, "mvsc");
         GameInfo.state = STATE_RUNNING;
      }
   } else if (GameInfo.state == STATE_RUNNING) {
      /*
       * We can go from running back to starting if someone
       * does something weird like resetting the game.  So keep
       * looking for the start sprite.
       */
      if (SpriteInList(&startSprite, sprites, count)) {
         GameInfo.state = STATE_STARTING;
      }

      /*
       * Identify the players...
       */
      for (int i = 0; i < 2; i++) {
         for (int j = 0; j < 2; j++) {
            if (!GameInfo.p[i].c[j]) {
               for (int k = 0; k < ARRAYSIZE(search); k++) {
                  for (int l = 0; l < count; l++) {
                     if (sprites[l].id == search[k].id) {
                        if (i == 0 && j == 0 && sprites[l].x == 40 && sprites[l].y == 14) {
                           GameInfo.p[i].c[j] = search[k].character;
                        } else if (i == 0 && j == 1 && sprites[l].x == 40 && sprites[l].y == 37) {
                           GameInfo.p[i].c[j] = search[k].character;
                        } else if (i == 1 && j == 0 && (sprites[l].x + sprites[l].w == 344) && sprites[l].y == 14) {
                           GameInfo.p[i].c[j] = search[k].character;
                        } else if (i == 1 && j == 1 && (sprites[l].x + sprites[l].w == 344) && sprites[l].y == 37) {
                           GameInfo.p[i].c[j] = search[k].character;
                        }
                     }
                  }
               }
            }
         }
      }
      /*
       * See if we're finished...
       */
      if (SpriteInList(&finishSprite, sprites, count)) {
         static const QuarkSpriteInfo p1win =  { 27712, 48, 2};
         if (SpriteInList(&p1win, sprites, count)) {
            GameInfo.p[0].rounds = 1;
         } else {
            GameInfo.p[1].rounds = 1;
         }
         QuarkSpriteFinishGame(ggpo);
         GameInfo.state = STATE_IDLE;
      }
   }
}
