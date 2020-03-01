#include "all.h"
using namespace GameLib;
extern int game_timer;
extern int game_state;
extern Sprite* sprData[Spr_Max];
extern OBJ test;

 void dispScore(int sc, float xpos, float ypos, float scale, int keta)
   {
        while (keta--)
        {
            int num = sc % 10;
            float texPosX = num % 5 * (float)NUMBER_WIDTH;
            float texPosY = num / 5 * (float)NUMBER_HEIGHT;
            sprite_render(sprData[Number], xpos, ypos, scale, scale,
                texPosX, texPosY,
                NUMBER_WIDTH, NUMBER_HEIGHT,
                0, 0,
                0, 1, 1, 1);
            xpos -= NUMBER_WIDTH * scale;
            sc /= 10;
        }
    }
