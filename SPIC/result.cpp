#include "all.h"
using namespace GameLib;
namespace result
{
	int state;
	int Rcase;
}
extern int play;
OBJ resu;
void result_init(const  int Rcase)
{
	play = 2;
	resu.set_state(0);//�A�j���[�V�����������p
	result::Rcase = Rcase;
}
extern int game_state;
extern OBJ player;
void result_update()
{
	volcano_update();
	if (input::TRG(0)&input::PAD_START)
	{
		resu.set_state(1);
		game_state++;
	}
	switch (result::Rcase)
	{
	case clear:

		break;
	case over:

		break;
	default:
		//�N���A�A�I�[�o�[�ȊO�̂������牽��
		return;
	}
	
}
extern Sprite* sprData[Spr_Max];
void result_drow()
{
	switch (result::Rcase)
	{
	case clear:

		break;
	case over:
if(player.get_state()==100)
		resu.anim(sprData[Bg], 6, 6, 2, 11, 0, 0, 1, 1, 0, 1080 * 2, 1920, 1080);
		break;
	}
}