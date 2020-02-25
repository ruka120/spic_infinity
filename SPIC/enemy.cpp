#include "all.h"
using namespace GameLib;
using namespace input;
extern Sprite* sprData[Spr_Max];
ENEMY enemy;
extern OBJ player;
extern int map[MAP_Y][MAP_X];
namespace Ejump
{
	bool isflg[2];
	int state;
	float pos;
	float speed;
	void init(float pos);
	bool get_flg();
	void update();
}

//状態遷移用enumクラス
enum
{
	eWait = 0,
	eMove,
	eJump
};

void Ejump::init(float pos)
{
	Ejump::state = 2;
	Ejump::pos = pos;
	Ejump::speed = 10;
}
bool Ejump::get_flg()
{
	if (isflg[0] || isflg[1]) { return true; }
	return false;
}
void Ejump::update()
{
	switch (Ejump::state)
	{
	case 1:
		Ejump::init(enemy.pos.x);
		break;
	case 2:
		Ejump::speed -= 0.5;
		enemy.pos.x -= Ejump::speed;
		if (Ejump::speed <= 0)Ejump::state = 3;
		break;
	case 3:
		Ejump::speed -= 0.5;
		enemy.pos.x -= Ejump::speed;
		if (enemy.pos.x >= Ejump::pos)Ejump::state = 0;
		break;
	}

}
void ENEMY::init()
{
	enemy.pos = { 500,540 / 2 };
}
void ENEMY::update()
{
	Ejump::isflg[0] = false;
	Ejump::isflg[1] = false;
	if (Ejump::state == 0) { enemy.pos.x += 5; }
	for (int y = 0; y < MAP_Y; y++)
	{
		for (int x = 0; x < MAP_X; x++)
		{
			if (Judge.rect(64 * y, 64 * (y + 1), 64 * x, 64 * (x + 1), enemy.pos.x + 32, enemy.pos.y + 32))
			{
				switch (map[y][x])
				{
				case 0:
					Ejump::isflg[0] = false;
					break;
				case 1:
					Ejump::isflg[0] = false;
					enemy.pos.x = 64 * (x)-32;

					switch (map[y + 1][x])
					{
					case 0:
						Ejump::isflg[0] = true;;
						if (Ejump::state != 2)
						{
							enemy.pos.x = 64 * (x)-32;
							if (Ejump::state == 3)
							{
								Ejump::state = 0;
							}
						}
						break;
					}
					break;
				}
			}
			if (Judge.rect(64 * y, 64 * (y + 1), 64 * x, 64 * (x + 1), enemy.pos.x + 32, enemy.pos.y - 32))
			{
				switch (map[y][x])
				{
				case 0:
					Ejump::isflg[1] = false;
					break;
				case 1:
					Ejump::isflg[1] = false;
					enemy.pos.x = 64 * (x)-32;

					switch (map[y - 1][x])
					{
					case 0:
						Ejump::isflg[1] = true;;
						if (Ejump::state != 2)
						{
							enemy.pos.x = 64 * (x)-32;
							if (Ejump::state == 3)
							{
								Ejump::state = 0;
							}
						}
						break;
					}

					break;
				}
			}
		}
	}
	switch (enemy.get_state())
	{
	case eWait:
		break;
	case eMove:
		break;
	case eJump:
		break;
	}

	//プレイヤーにただ近づく場合
	if (enemy.pos.y > player.pos.y) { enemy.pos.y -= 5; }
	if (enemy.pos.y < player.pos.y) { enemy.pos.y += 5; }

	//足場があるところだけで左右に動く場合

	if (Ejump::state == 0 && Ejump::get_flg()) { Ejump::state = 1; }
	Ejump::update();

	if (enemy.pos.x < 50) { enemy.pos.x = 50; }
	if (enemy.pos.x > 1820) { enemy.pos.x = 1820; }
	if (enemy.pos.y < 50) { enemy.pos.y = 50; }
	if (enemy.pos.y > 1030) { enemy.pos.y = 1030; }
}


void ENEMY::draw()
{
	switch (enemy.get_state())
	{
	case eWait:
		break;
	case eMove:
		break;
	case eJump:
		break;
	}
	sprite_render(sprData[Enemy], enemy.pos.x, enemy.pos.y, 1, 1, 0, 0, 64, 64, 32, 32);
}

void enemy_init()
{
	enemy.init();
}

void enemy_update()
{
	enemy.update();
}
void enemy_draw()
{
	enemy.draw();
}
