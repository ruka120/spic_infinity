#include "all.h"
using namespace GameLib;
namespace result
{
	int state;
	int Rcase;
}
extern int play;
void result_init(const  int Rcase)
{
	play = 2;
	result::Rcase = Rcase;
}
extern int game_state;
void result_update()
{
	volcano_update();
	if (input::TRG(0)&input::PAD_START)
	{
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
void result_drow()
{
	switch (result::Rcase)
	{
	case clear:

		break;
	case over:

		break;
	}
}