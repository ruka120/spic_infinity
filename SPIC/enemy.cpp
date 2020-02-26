#include "all.h"
using namespace GameLib;
using namespace input;

extern Sprite* sprData[Spr_Max];
extern int map[MAP_Y][MAP_X];
extern OBJ player;
extern float world_pos;
extern float scroll_pos;
extern float scroll_begin;
ENEMY enemy;

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
	pos = { 500,540 / 2 };
    world_pos = -300;
}
void ENEMY::update()
{
    enemy.rect = {pos.y,pos.y + 64,pos.x,pos.x + 64 };
	Ejump::isflg[0] = false;
	Ejump::isflg[1] = false;
	if (Ejump::state == 0) { pos.x += 5; }
    for (int y = 0; y < MAP_Y; y++)
    {
        for (int x = 0, begin = scroll_begin, fin = begin + 32; begin < fin; x++, begin++)
        {
            if (Judge.rect(64 * y, 64 * (y + 1), (64 * x) + scroll_pos, (64 * (x + 1)) + scroll_pos, enemy.rect.right, enemy.rect.top))
            {
                switch (map[y][begin])
                {
				case 0:
					Ejump::isflg[0] = false;
					break;
				case 1:
					Ejump::isflg[0] = false;
                    pos.x = ((64 * (x)-32) + scroll_pos);

					switch (map[y + 1][begin])
					{
					case 0:
						Ejump::isflg[0] = true;;
						if (Ejump::state != 2)
						{
                            pos.x = ((64 * (x)-32) + scroll_pos);
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
            if (Judge.rect(64 * y, 64 * (y + 1), (64 * x) + scroll_pos, (64 * (x + 1)) + scroll_pos, enemy.rect.right, enemy.rect.under))
            {
                switch (map[y][begin])
				{
				case 0:
					Ejump::isflg[1] = false;
					break;
				case 1:
					Ejump::isflg[1] = false;
                    pos.x = ((64 * (x)-32) + scroll_pos);

					switch (map[y - 1][begin])
					{
					case 0:
						Ejump::isflg[1] = true;;
						if (Ejump::state != 2)
						{
                            pos.x = ((64 * (x)-32) + scroll_pos);
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
	switch (get_state())
	{
	case eWait:
		break;
	case eMove:
		break;
	case eJump:
		break;
	}

	//プレイヤーにただ近づく場合
	if (pos.y > player.pos.y) { pos.y -= 3; }
	if (pos.y < player.pos.y) { pos.y += 3; }

	//足場があるところだけで左右に動く場合
	if (Ejump::state == 0 && Ejump::get_flg()) { Ejump::state = 1; }
	Ejump::update();

	if (pos.x < 50)   { pos.x = 50; }
	if (pos.x > 1820) { pos.x = 1820; }
	if (pos.y < 50)   { pos.y = 50; }
	if (pos.y > 1030) { pos.y = 1030; }
}


void ENEMY::draw()
{
	switch (get_state())
	{
	case eWait:
		break;
	case eMove:
		break;
	case eJump:
		break;
	}
    OBJ::anim(sprData[Enemy], 10, 8, 1, 8, pos.x, pos.y, 1, 1, 0, 0, 64, 64, 32, 32);
    //sprite_render(sprData[Enemy], enemy.pos.x, enemy.pos.y, 1, 1, 0, 0, 64, 64, 32, 32);
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
