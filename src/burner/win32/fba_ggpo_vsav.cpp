#include "burner.h"
#include "ggpoclient.h"

#define STATE_IDLE         0
#define STATE_STARTING     1
#define STATE_RUNNING      2

static struct {
   int state;
   char *game;
   struct {
      char *id;
      int   rounds;
   } p[2];
} GameInfo = { 0 };

extern bool SpriteInList(const QuarkSpriteInfo *s, QuarkSprite sprites[], int count);
extern int QuarkFindSprite(QuarkSprite sprites[], int count, int x, int y);

static void
QuarkSpriteStartNewGame(GGPOSession *ggpo, char *game)
{
   for (int i = 0; i < 2; i++) {
      GameInfo.p[i].rounds = 0;
      GameInfo.p[i].id = NULL;
   }
   ggpo_client_set_game_event(ggpo, GGPOCLIENT_GAMEEVENT_STARTING, game);
}

static void
QuarkSpriteFinishGame(GGPOSession *ggpo)
{
   ggpo_client_set_game_event(ggpo, GGPOCLIENT_GAMEEVENT_PLAYER_1, (void *)GameInfo.p[0].id);
   ggpo_client_set_game_event(ggpo, GGPOCLIENT_GAMEEVENT_PLAYER_2, (void *)GameInfo.p[1].id);
   ggpo_client_set_game_event(ggpo, GGPOCLIENT_GAMEEVENT_PLAYER_1_SCORE, (void *)GameInfo.p[0].rounds);
   ggpo_client_set_game_event(ggpo, GGPOCLIENT_GAMEEVENT_PLAYER_2_SCORE, (void *)GameInfo.p[1].rounds);
   ggpo_client_set_game_event(ggpo, GGPOCLIENT_GAMEEVENT_WINNER, (void *)(GameInfo.p[0].rounds > GameInfo.p[1].rounds ? 1 : 2));
   ggpo_client_set_game_event(ggpo, GGPOCLIENT_GAMEEVENT_FINISHED, NULL);
}

/*
 * A little state machine with match info should go here...
 */

bool
RedFadeoutVisible(QuarkSprite sprites[], int count)
{
   int i;

   for (i = 0; i < count; i++) {
      if (sprites[i].id == 64494) {
         return true;
      }
   }
   return false;
}

void
QuarkProcessVSAVSprites(GGPOSession *ggpo, QuarkSprite sprites[], int count)
{   
   static const struct {
      char *character;
      int  id;
   } search[] = {
      {"Demitri",      15594 },
      {"Morrigan",     15544 },
      {"Victor",       15550 },
      {"B.B.Hood",     15539 },
      {"Q-Bee",        15610 },
      {"Lilith",       15564 },
      {"L.Rapter",     15501 },
      {"Felicia",      15562 },
      {"Jedah",        15726 },
      {"J.Talbain",    15533 },
      {"Bishamon",     15547 },
      {"Anakaris",     15578 },
      {"Hsien-Ko",     15597 },
      {"Sasquatch",    15768 },
      {"Rikuo",        15694 },
   };

   static const QuarkSpriteInfo finishSprite = { 64928, 104, 88 };
   static const QuarkSpriteInfo startSprite = { 46365, 168, 104 };
   /*
    * See if it's time to start a new game...
    */
   if (GameInfo.state == STATE_IDLE) {
      if (SpriteInList(&startSprite, sprites, count)) {
         GameInfo.state = STATE_STARTING;
      }
   } else if (GameInfo.state == STATE_STARTING) {
      if (!SpriteInList(&startSprite, sprites, count)) {
         QuarkSpriteStartNewGame(ggpo, "vsav");
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
      if (!GameInfo.p[0].id || !GameInfo.p[1].id) {
         for (int j = 0; j < ARRAYSIZE(search); j++) {
            for (int k = 0; k < count; k++) {
               if (sprites[k].id == search[j].id && sprites[k].y == 24) {
                  if (sprites[k].x < 160) {
                     GameInfo.p[0].id = search[j].character;
                  } else {
                     GameInfo.p[1].id = search[j].character;
                  }
               }
            }
         }
      }

      /*
       * See if we're finished...
       */
      if (SpriteInList(&finishSprite, sprites, count)) {
         GameInfo.p[0].rounds = 0;
         GameInfo.p[1].rounds = 0;
         for (int k = 0; k < count; k++) {
            if (sprites[k].y == 23) {
               if (sprites[k].x == 8 || sprites[k].x == 34) {
                  GameInfo.p[0].rounds++;
               } else if (sprites[k].x == 328 || sprites[k].x == 354) {
                  GameInfo.p[1].rounds++;
               }
            }
         }

         QuarkSpriteFinishGame(ggpo);
         GameInfo.state = STATE_IDLE;
      }
   }
}
