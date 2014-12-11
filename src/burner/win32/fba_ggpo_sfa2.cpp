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

bool
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

int
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


void
QuarkSpriteStartNewGame(GGPOSession *ggpo, char *game)
{
   for (int i = 0; i < 2; i++) {
      GameInfo.p[i].rounds = 0;
      GameInfo.p[i].id = NULL;
   }
   ggpo_client_set_game_event(ggpo, GGPOCLIENT_GAMEEVENT_STARTING, game);
}

void
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

void
QuarkProcessSFA2Sprites(GGPOSession *ggpo, QuarkSprite sprites[], int count)
{   
  /*
   * P1, Round 1:  17x 28 (blank: 42016)
   * P1, Round 2:  32x 28 
   * P2, Round 2: 336x 28
   * P2, Round 1: 352x 28
   *
   * P1 Ryu: 109x29 (3x1) 
   */

   /*
    * These are the nameplates for all the characters you can select.
    */
   static const struct {
      char *character;
      int p[2];
   } search[] = {
      {"Ryu",      { 42593,   42897} },
      {"Ken",      { 42596,   42900} },
      {"ChunLi",   { 42605,   42909} },
      {"Adon",     { 42625,   42929} },
      {"Sodom",    { 42628,   42932} },
      {"Guy",      { 42631,   42935} },
      {"Birdie",   { 42634,   42938} },
      {"Rose" ,    { 42637,   42941} },
      {"Sagat",    { 42660,   42964} },
      {"Dan",      { 42663,   42967} },
      {"Sakura",   { 42666,   42970} },
      {"Rolento",  { 42669,   42973} },
      {"Dhalsim",  { 42689,   42993} },
      {"Zangief",  { 42692,   42996} },
      {"Gen",      { 42695,   42999} },
      {"Akuma",    { 42698,   43002} },
      {"Charlie",  { 42701,   43005} },
      {"Bison",    { 42721,   43025} },
   };

   /*
    * These are the nameplate positions for the above
    * sprites.
    */
   static struct {
      int x, y;
   } nameplatePositions[] = { { 108, 29 }, { 228,  29 } };

   /*
    * These are the locations of the victory icons.
    */
   static struct {
      int x, y;
   } victoryIconPositions[][2] = {
      /* Round 1      Round 2 */
      { {  16, 28 }, {  32, 28 } }, /* Player 1 */
      { { 352, 28 }, { 336, 28 } }  /* Player 2 */
   };

   /*
    * This is the id of the transparent sprite that gets drawn
    * if there's nothing in the victory position.
    */
   static const int NO_ROUND = 42016;

   static const int p1_x = 108;
   static const int p1_y =  29;
   static const int p2_x = 228;
   static const int p2_y =  29;
   static const QuarkSpriteInfo startSprite =  { 25936, 130, 12 };
   static const QuarkSpriteInfo finishSprite = { 28624, 112, 144  };
   static const QuarkSpriteInfo challengeSprite = { 46483, 57, 92  };

   /*
    * See if it's time to start a new game...
    */
   if (GameInfo.state == STATE_IDLE) {
      if (SpriteInList(&startSprite, sprites, count)) {
         GameInfo.state = STATE_STARTING;
      }
   } else if (GameInfo.state == STATE_STARTING) {
      if (!SpriteInList(&startSprite, sprites, count)) {
         QuarkSpriteStartNewGame(ggpo, "sfa2");
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
         if (!GameInfo.p[i].id) {
            for (int j = 0; j < _ARRAYSIZE(search); j++) {
               QuarkSpriteInfo s = { search[j].p[i], nameplatePositions[i].x, nameplatePositions[i].y };
               if (SpriteInList(&s, sprites, count)) {
                  GameInfo.p[i].id = search[j].character;
                  break;
               }
            }
         }
      }

      // See if we're finished
      if (SpriteInList(&finishSprite, sprites, count) ||
          SpriteInList(&challengeSprite, sprites, count)) {
          // Count the rounds
         for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
               int found = QuarkFindSprite(sprites, count, victoryIconPositions[i][j].x, victoryIconPositions[i][j].y);
               if (found > 0 && found != NO_ROUND) {
                  GameInfo.p[i].rounds++;
               }
            }
         }
         QuarkSpriteFinishGame(ggpo);
         GameInfo.state = STATE_IDLE;
      }
   }
}
