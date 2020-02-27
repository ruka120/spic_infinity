#include "all.h"
using namespace GameLib;
namespace result
{
	int state;
	int Rcase;
}
void result_init(const  int Rcase)
{
	result::Rcase = Rcase;
}
extern int game_state;
void result_update()
{
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
		//クリア、オーバー以外のが来たら何も
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