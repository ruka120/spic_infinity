#include "all.h"
using namespace GameLib;
using namespace input;
OBJ tuto;
extern Sprite* sprData[Spr_Max];

void tutorial_init()
{

	tuto.set_state(0);
}

void tutorial_update()
{
	switch (tuto.get_state())
	{
	case 0:
		if (TRG(0)&PAD_RIGHT)
		{
			tuto.set_state(1);
		}
		if (TRG(0)&PAD_LEFT)
		{
			tuto.set_state(3);
		}
		break;
	case 1:
		if (TRG(0)&PAD_RIGHT)
		{
			tuto.set_state(2);
		}
		if (TRG(0)&PAD_LEFT)
		{
			tuto.set_state(0);
		}
		break;
	case 2:
		if (TRG(0)&PAD_RIGHT)
		{
			tuto.set_state(3);
		}
		if (TRG(0)&PAD_LEFT)
		{
			tuto.set_state(1);
		}
		break;
	case 3:
		if (TRG(0)&PAD_RIGHT)
		{
			tuto.set_state(0);
		}
		if (TRG(0)&PAD_LEFT)
		{
			tuto.set_state(2);
		}
		break;
	}

}

void tutorial_draw()
{
	primitive::rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 0, 0, 0, 0, 1);
	sprite_render(sprData[Waku], 1920/2, 1080/2, 1, 1, 0, 0, 1300, 960, 1300 / 2, 960 / 2);
	switch (tuto.get_state())
	{
	case 0:
		tuto.anim(sprData[Tutorial], 10, 8, 1, 8, (1920 / 2) + 110, 1080 / 2, 1, 1, 0, 0, 1080, 960, 1080 / 2, 960 / 2);
		sprite_render(sprData[Waku], 435, 890,1 , 1, 0, 960, 240, 240, 120, 120,0,1,1,1,1);
		sprite_render(sprData[Waku], 435, 650, 0.8, 0.8, 240, 960, 240, 240, 120, 120,0, 1, 1, 1, 0.5);
		sprite_render(sprData[Waku], 435, 415, 0.8, 0.8, 240*2, 960, 240, 240, 120, 120,0, 1, 1, 1, 0.5);
		sprite_render(sprData[Waku], 435, 180, 0.8, 0.8, 240*3, 960, 240, 240, 120, 120, 0, 1, 1, 1, 0.5);
		break;
	case 1:
		tuto.anim(sprData[Tutorial], 10, 7, 1, 7, (1920 / 2) + 110, 1080 / 2, 1, 1, 0, 960, 1080, 960, 1080 / 2, 960 / 2);
		sprite_render(sprData[Waku], 435, 890, 0.8, 0.8, 0, 960, 240, 240, 120, 120,0, 1, 1, 1, 0.5);
		sprite_render(sprData[Waku], 435, 650, 1, 1, 240, 960, 240, 240, 120, 120);
		sprite_render(sprData[Waku], 435, 415, 0.8, 0.8, 240 * 2, 960, 240, 240, 120, 120,0, 1, 1, 1, 0.5);
		sprite_render(sprData[Waku], 435, 180, 0.8, 0.8, 240 * 3, 960, 240, 240, 120, 120, 0, 1, 1, 1, 0.5);
		break;
	case 2:
		tuto.anim(sprData[Tutorial], 10, 7, 1, 7, (1920 / 2) + 110, 1080 / 2, 1, 1, 0, 960*2, 1080, 960, 1080 / 2, 960 / 2);
		sprite_render(sprData[Waku], 435, 890, 0.8, 0.8, 0, 960, 240, 240, 120, 120, 0, 1, 1, 1, 0.5);
		sprite_render(sprData[Waku], 435, 650, 0.8, 0.8, 240, 960, 240, 240, 120, 120, 0, 1, 1, 1, 0.5);
		sprite_render(sprData[Waku], 435, 415, 1, 1, 240 * 2, 960, 240, 240, 120, 120);
		sprite_render(sprData[Waku], 435, 180, 0.8, 0.8, 240 * 3, 960, 240, 240, 120, 120, 0, 1, 1, 1, 0.5);
		break;
	case 3:
		tuto.anim(sprData[Tutorial], 10, 8, 1, 8, (1920 / 2) + 110, 1080 / 2, 1, 1, 0, 960*3, 1080, 960, 1080 / 2, 960 / 2);
		sprite_render(sprData[Waku], 435, 890, 0.8, 0.8, 0, 960, 240, 240, 120, 120, 0, 1, 1, 1, 0.5);
		sprite_render(sprData[Waku], 435, 650, 0.8, 0.8, 240, 960, 240, 240, 120, 120, 0, 1, 1, 1, 0.5);
		sprite_render(sprData[Waku], 435, 415, 0.8, 0.8, 240 * 2, 960, 240, 240, 120, 120, 0, 1, 1, 1, 0.5);
		sprite_render(sprData[Waku], 435, 180, 1, 1, 240 * 3, 960, 240, 240, 120, 120);
		break;
	}
	
	sprite_render(sprData[Ui], 1700, 200, 1, 1, 0, 256, 64, 192);
	sprite_render(sprData[Ui], 1764, 200, 1, 1, 128, 256, 70, 192);
}