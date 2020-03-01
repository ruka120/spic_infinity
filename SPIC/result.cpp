#include "all.h"
using namespace GameLib;
namespace result
{
	int state;
	int Rcase;
}
extern int play;
OBJ resu;
extern OBJ player;
void result_init(const  int Rcase)
{
	play = 2;
	resu.set_state(Rcase);//アニメーション初期化用
	result::Rcase = Rcase;
	music::stop(play02);
	if (result::Rcase == clear) { music::play(clear01); }
	else { music::play(over01); }
}
extern int game_state;
extern OBJ player;
void result_update()
{
	volcano_update();
	if (input::TRG(0))
	{
		resu.set_state(10);
		if (result::Rcase == clear) { music::stop(clear01); }
		else{ music::stop(over01); }
		game_state++;
		sound::play(2);
	}
	switch (resu.get_state())
	{
	case clear:
		player.set_state(4);
		//music::play(clear01,true);
		break;
	case over:
	//	music::play(over02, true);
		break;

	}
	
}
extern Sprite* sprData[Spr_Max];
void result_drow()
{
	switch (resu.get_state())
	{
	case clear:
		resu.motion(sprData[Clear],1, 6, 10, 1, 9, 1920/2, 1080/2, 1, 1, 0, 0,256, 1080,128/2,1080/2);
		break;
	case 1:
		sprite_render(sprData[Clear], 1920 / 2, 1080 / 2, 1, 1, 256 * 9, 0, 256, 1080, 128 / 2, 1080 / 2);
		break;
	case over:
if(player.get_state()==100)
		resu.anim(sprData[Bg], 6, 6, 2, 11, 0, 0, 1, 1, 0, 1080 * 2, 1920, 1080);
		break;
	}
}