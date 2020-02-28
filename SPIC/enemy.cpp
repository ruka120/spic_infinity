#include "all.h"
using namespace GameLib;
using namespace input;

ENEMY enemy;

extern Sprite* sprData[Spr_Max];
extern int map[MAP_Y][MAP_X];
extern OBJ player;
extern float world_pos;
extern float scroll_pos;
extern float scroll_begin;

//状態遷移用enumクラス
enum
{
	eMove,
	eJump,
    eDamage
};

//敵タイプ
enum
{
    Stalker,  //ストーカー型
    Nokonoko  //赤ノコノコ型
};

//敵の初期化
void ENEMY::init()
{
    type = Nokonoko;
    scl = 1;
	pos = { 0, 0 };
    if (type == Nokonoko)
    {
        speed = { 0,3 };
    }
    else if (type == Stalker)
    {
        speed = { 12,3 };
    }
    world_pos = -300;
}

//ジャンプに関する初期化
void ENEMY::jump_init(float pos)
{
	enemy.jump_state = 2;
	enemy.jump_pos = pos;
	enemy.jump_speed = 10;
}

//ジャンプできるかできないか
bool ENEMY::get_flg()
{
	if (isflg[0] || isflg[1]) { return true; }
	return false;
}

//ジャンプに関する更新処理
void ENEMY::jump_update()
{
	switch (enemy.jump_state)
	{
	case 1:
        enemy.set_state(eJump);
        enemy.jump_init(enemy.pos.x);
		break;

	case 2:
        enemy.jump_speed -= 0.5;
        grounding = false;
		enemy.pos.x -= enemy.jump_speed;
        if (enemy.jump_speed <= 0)
        {
            enemy.jump_state = 3;
        }
		break;

	case 3:
        enemy.jump_speed -= 0.5;
		enemy.pos.x -= enemy.jump_speed;
        if (enemy.pos.x >= enemy.jump_pos)
        {
            enemy.jump_state = 0;
        }
		break;
	}

}


//敵の更新処理
void ENEMY::update()
{
    enemy.rect = { pos.y - 32,pos.y + 32,pos.x - 32,pos.x + 32 };
    player.rect = { player.pos.y - 32,player.pos.y + 32,player.pos.x - 32,player.pos.x + 32 };

	enemy.isflg[0] = false;
	enemy.isflg[1] = false;
    grounding = true;

    for (int y = 0; y < MAP_Y; y++)
    {
        for (int x = 0, begin = scroll_begin, fin = begin + 32; begin < fin; x++, begin++)
        {

            if (Judge.rect(64 * y, 64 * (y + 1), (64 * x) + scroll_pos, (64 * (x + 1)) + scroll_pos, enemy.rect.right, enemy.rect.top))
            {
                switch (map[y][begin])
                {
				case 0:
                    grounding = false;
					enemy.isflg[0] = false;
					break;

				case 1:
                    set_state(eMove);
                    enemy.isflg[0] = false;
                    pos.x = ((64 * (x)-32) + scroll_pos);

					switch (map[y + 1][begin])
					{
					case 0:
                        grounding = false;
                        switch (enemy.type)
                        {
                        case Stalker:  //ストーカー型
                            set_state(eJump);
                            enemy.isflg[0] = true;

                            if (enemy.jump_state != 2)
                            {
                                pos.x = ((64 * (x)-32) + scroll_pos);
                                if (enemy.jump_state == 3)
                                {
                                    enemy.jump_state = 0;
                                }
                            }
                            break;

                        case Nokonoko:  //ノコノコ型
                            enemy.speed *= -1; //反転
                            break;
                        }
                        break;

                    case 1:
                        grounding = true;
                        set_state(eMove);
                        break;
					}
				}
			}
            if (Judge.rect(64 * y, 64 * (y + 1), (64 * x) + scroll_pos, (64 * (x + 1)) + scroll_pos, enemy.rect.right, enemy.rect.under))
            {
                switch (map[y][begin])
				{
				case 0:
                    grounding=false;
                    enemy.isflg[1] = false;
					break;

				case 1:
                    enemy.isflg[1] = false;
                    pos.x = ((64 * (x)-32) + scroll_pos);

                    switch (map[y - 1][begin])
                    {
                    case 0:
                        grounding = false;
                        switch (enemy.type)
                        {
                        case Stalker:
                            enemy.isflg[1] = true;
                            if (enemy.jump_state != 2)
                            {
                                pos.x = ((64 * (x)-32) + scroll_pos);

                                if (enemy.jump_state == 3)
                                {
                                    enemy.jump_state = 0;
                                }
                            }
                            break;

                        case Nokonoko:
                            enemy.speed *= -1;
                            break;
                        }
                        break;

                    case 1:
                        grounding = true;
                        set_state(eMove);
                        break;
                    }
					break;
				}
			}
		}
	}

	if (enemy.jump_state == 0) 
    { 
        pos.x += 12; 
    }

	switch (get_state())
	{
	case eMove:
		break;
	case eJump:
		break;
	}

	//プレイヤーにただ近づく場合
    switch (enemy.type)
    {
    case Stalker:
        if (pos.y < player.pos.y)
        {
            if (get_state() != eJump)
            {
                set_state(eMove);
            }
            scl = -1;
            pos.y += speed.y;
        }
        if (pos.y > player.pos.y)
        {
            if (get_state() != eJump)
            {
                set_state(eMove);
            }
            scl = 1;
            pos.y -= speed.y;
        }
        break;

	//足場があるところだけで左右に動く場合
    case Nokonoko:
        pos.y += speed.y;
        if (speed.y < 0) { scl =  1; }
        if (speed.y > 0) { scl = -1; }
        break;
    }


    //今はプレイヤーとの判定やけど後からマグマとの判定に変更する
    if (Judge.rect(player.rect.top, player.rect.under, player.rect.left, player.rect.right, pos.x, pos.y))
    {
        set_state(eDamage);
        pos.x = 0;
    }


	if (enemy.jump_state == 0 && enemy.get_flg())
    {
        enemy.jump_state = 1;
    }
    enemy.jump_update();

	if (pos.x < 50)   { pos.x = 50; }
	if (pos.x > 1820) { pos.x = 1820; }
	if (pos.y < 50)   { pos.y = 50; }
	if (pos.y > 1030) { pos.y = 1030; }
}


void ENEMY::draw()
{
	switch (get_state())
	{
	case eMove:
        enemy.anim(sprData[Enemy], 10, 8, 1, 8, pos.x, pos.y, 1, scl, 0, 0, 64, 64, 32, 32);
        break;

	case eJump:
        if (grounding == false)
        {
        sprite_render(sprData[Enemy], pos.x, pos.y, 1, scl, 256, 0, 64, 64, 32, 32);
        }
		break;
	}
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
