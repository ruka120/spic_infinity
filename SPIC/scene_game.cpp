#include "all.h"
using namespace GameLib;
using namespace input;
int game_state;    // 状態
int game_timer;    // タイマー
int game_score;
extern int nextScene;
extern float fadeOut;
extern Sprite* sprData[Spr_Max];
extern wchar_t* sprName[];
int play;
int type;
void game_init()
{
	spr_load();
	bg_init();
	player_init();
    enemy_init();
	volcano_init();
	game_state = 0;
    game_timer = 0;
	fadeOut = 0;
	play = 0;
	type = 0;
}
void common()
{
	bg_update();
	volcano_update();
	player_update();
    enemy_update();

}
void game_update()
{
	static const int game_max = 3;//ゲーム画面の最大数
    switch (game_state)
    {
     case 0:
		 game_init();
		 music::play(play02, true);
         game_state++;
         break;
     
     case 1:
		 switch (play)
		 {
		 case 0:
			 if(TRG(0)&PAD_START)
			 {
				 sound::play(3);
				 play = 1;
			 }
			 common();
			 break;
		 case 1:
			 if (TRG(0)&PAD_START)
			 {
				 sound::play(0);
				 type = 0;
				 play = 0;
			 }
			 if (TRG(0)&PAD_UP)
			 {
				 sound::play(1);
				 type--;
				 if (type < 0)
				 {
					 type = 2;
				 }
			 }
			 if (TRG(0)&PAD_DOWN)
			 {
				 sound::play(1);
				 type++;
				 if (type > 2)
					 type = 0;
			 }
			 if (TRG(0)&PAD_TRG3)
			 {
				 sound::play(2);
				 switch (type)
				 {
				 case 1:
					 type = 0;
					 game_state = 2;
					 music::stop(play02);
					 break;
				 case 2:
					 type = 0;
					 play = 0;
					 break;
				 }
			 }
		/*	 if (TRG(0)&PAD_L1)
			 {
				 game_init();
			 }*/
			 break;
		 case 2:
			 result_update();
			 break;
		 }
		 
    break;
     case 2:
         fadeOut += 0.0167f;
         if (fadeOut >= 1.0f)
         {
             game_state++;
         }
         break;
    }
    if (game_state == game_max) 
    {
        nextScene = SCENE_TITLE;
    }
    game_timer++;
}

void game_draw()
{
		bg_draw();
		player_draw();
		enemy_draw();
		volcano_draw();
		sprite_render(sprData[Pose], 0, 0, 0.5, 0.5, 0, 1080, 192, 192);
		switch (play)
		{
		case 1:
			primitive::rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 0, 0, 0, 0, 0.5);
			sprite_render(sprData[Pose], 420, 0, 1, 1, 1080*type, 0, 1080, 1080);
			break;
		case 2:
			result_drow();
			break;
		}

		ui_draw();

	if (fadeOut > 0.0f)
	{
		primitive::rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 0, 1-fadeOut, 1 - fadeOut, 1-fadeOut, fadeOut);
	}
}

void game_end()//画像の破棄
{
	for (int i = 0; i < Spr_Max; i++)
	{
		SAFE_DELETE(sprData[i]);
	}
}



