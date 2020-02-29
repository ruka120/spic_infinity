#include "all.h"
using namespace GameLib;
using namespace input;

ENEMY enemy[ENEMY_MAX];

int ran_type=0;
extern Sprite* sprData[Spr_Max];
extern int map[MAP_Y][MAP_X];
extern OBJ player;
extern VOLCANO volcano;
extern float world_pos;
extern float scroll_pos;
extern float scroll_begin;

//状態遷移用enumクラス
enum
{
	eMove,
	eJump,
    eDie
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
   set_state(eMove);
   alpha = 1.0f;
   exist = true;
   scl = 1;
   rect = { pos.y - 32,pos.y + 32,pos.x - 32,pos.x + 32 };
   speed = { 12,3 };
    
}

void ENEMY::set_enemy()
{
    float ran_y=0;
    ran_y = (rand() % (1080 - 128) + 64);
    ran_type = rand() % 2;
    type = ran_type;
    pos = { -32, ran_y };

    switch (ran_type)
    {
    case 0:
        type = Stalker;
        set_state(eMove);

        break;

    case 1:
        type = Nokonoko;
        set_state(eMove);

        break;
    }
    exist = true;
}


//ジャンプに関する初期化
void ENEMY::jump_init(float pos)
{
	jump_state = 2;
	jump_pos = pos;
	jump_speed = 10;
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
	switch (jump_state)
	{
	case 1:
        set_state(eJump);
        jump_init(pos.x);
		break;

	case 2:
        jump_speed -= 0.5;
        grounding = false;
		pos.x -= jump_speed;
        if (jump_speed <= 0)
        {
            jump_state = 3;
        }
		break;

	case 3:
        jump_speed -= 0.5;
		pos.x -= jump_speed;
        if (pos.x >= jump_pos)
        {
            jump_state = 0;
        }
		break;
	}

}


//敵の更新処理
void ENEMY::update()
{
    rect = { pos.y - 32,pos.y + 32,pos.x - 32,pos.x + 32 };

	isflg[0] = false;
	isflg[1] = false;
    grounding = true;

    if (Judge.rect(volcano.rect, rect)&&volcano.get_state()!=0)
    {
        speed.x = 0;
        speed.y = 0;
        exist = false;
    }

    //マップの当たり判定
    for (int y = 0; y < MAP_Y; y++)
    {
        for (int x = 0, begin = scroll_begin, fin = begin + 32; begin < fin; x++, begin++)
        {
            if (Judge.rect(64 * y, 64 * (y + 1), (64 * x) + scroll_pos, (64 * (x + 1)) + scroll_pos, rect.right, rect.top))
            {
                switch (type)
                {
                case Stalker://ストーカー型
                    switch (map[y][begin])
                    {
                    case 0:
                        grounding = false;
                        isflg[0] = false;
                        break;

                    case 1:
                        set_state(eMove);
                        isflg[0] = false;
                        pos.x = ((64 * (x)-32) + scroll_pos);

                        switch (map[y + 1][begin])
                        {
                        case 0:
                            grounding = false;
                            set_state(eJump);
                            isflg[0] = true;
                            if (jump_state != 2)
                            {
                                pos.x = ((64 * (x)-32) + scroll_pos);
                                if (jump_state == 3)
                                {
                                    jump_state = 0;
                                }
                            }
                            break;

                        case 1:
                            grounding = true;
                            set_state(eMove);
                            break;

                        case 7:
                            speed *= -1;
                            break;
                        }
                        break;
                    }
                    break;

                case Nokonoko://ノコノコ型
                    switch (map[y][begin])
                    {
                    case 1:
                        grounding = true;
                        set_state(eMove);
                        pos.x = ((64 * (x)-32) + scroll_pos);

                        switch (map[y + 1][begin])
                        {
                        case 0:
                        case 7:
                            speed *= -1;
                            break;
                        }
                        break;
                    }
                    break;
                }
            
#if 0

                //足元のチップ番号
                switch (map[y][begin])
                {
				case 0:
                    grounding = false;
					isflg[0] = false;
					break;

				case 1:
                    set_state(eMove);
                    isflg[0] = false;
                    pos.x = ((64 * (x)-32) + scroll_pos);

                    //足元の一個先
					switch (map[y + 1][begin])
					{
					case 0:
                        grounding = false;
                        switch (type)
                        {
                        case Stalker:  //ストーカー型
                            set_state(eJump);
                            isflg[0] = true;

                            if (jump_state != 2)
                            {
                                pos.x = ((64 * (x)-32) + scroll_pos);
                                if (jump_state == 3)
                                {
                                    jump_state = 0;
                                }
                            }
                            break;

                        case Nokonoko:  //ノコノコ型
                            speed *= -1; //反転
                            break;
                        }
                        break;

                    case 1:
                    case 7:
                        grounding = true;
                        speed *= -1;
                        set_state(eMove);
                        break;
					}
                    break;
				}
#endif
			}

            if (Judge.rect(64 * y, 64 * (y + 1), (64 * x) + scroll_pos, (64 * (x + 1)) + scroll_pos, rect.right, rect.under))
            {
                switch (type)
                {
                case Stalker://ストーカー型
                    switch (map[y][begin])
                    {
                    case 0:
                        grounding = false;
                        isflg[1] = false;
                        break;

                    case 1:
                        set_state(eMove);
                        isflg[1] = false;
                        pos.x = ((64 * (x)-32) + scroll_pos);

                        switch (map[y + 1][begin])
                        {
                        case 0:
                            grounding = false;
                            set_state(eJump);
                            isflg[1] = true;
                            if (jump_state != 2)
                            {
                                pos.x = ((64 * (x)-32) + scroll_pos);
                                if (jump_state == 3)
                                {
                                    jump_state = 0;
                                }
                            }
                            break;

                        case 1:
                            grounding = true;
                            set_state(eMove);
                            break;

                        case 7:
                            speed *= -1;
                            break;
                        }
                        break;
                    }
                    break;

                case Nokonoko://ノコノコ型
                    switch (map[y][begin])
                    {
                    case 1:
                        grounding = true;
                        set_state(eMove);
                        pos.x = ((64 * (x)-32) + scroll_pos);

                        switch (map[y + 1][begin])
                        {
                        case 0:
                        case 7:
                            speed *= -1;
                            break;
                        }
                        break;
                    }
                    break;
                }
#if 0
                switch (map[y][begin])
				{
				case 0:
                    grounding=false;
                    isflg[1] = false;
					break;

				case 1:
                    isflg[1] = false;
                    pos.x = ((64 * (x)-32) + scroll_pos);

                    switch (map[y - 1][begin])
                    {
                    case 0:
                        grounding = false;
                        switch (type)
                        {
                        case Stalker:
                            isflg[1] = true;
                            if (jump_state != 2)
                            {
                                pos.x = ((64 * (x)-32) + scroll_pos);

                                if (jump_state == 3)
                                {
                                    jump_state = 0;
                                }
                            }
                            break;

                        case Nokonoko:
                            speed *= -1;
                            break;
                        }
                        break;

                    case 1:
                    case 7:
                        grounding = true;
                        speed *= -1;
                        set_state(eMove);
                        break;
                    }
					break;
				}
#endif
			}
		}
	}

	if (jump_state == 0) 
    { 
        pos.x += 12; 
    }

	switch (get_state())
	{
	case eMove:
		break;
	case eJump:
		break;
    case eDie:
        break;
	}

	//プレイヤーにただ近づく場合
    switch (type)
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

    //ジャンプステート
	if (jump_state == 0 && get_flg())
    {
        jump_state = 1;
    }
    jump_update();

    //画面内だけ
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
            anim(sprData[Enemy], 10, 8, 1, 8, pos.x, pos.y, 1, scl, 0, 0, 64, 64, 32, 32);
        break;

    case eJump:
            if (grounding == false)
            {
                sprite_render(sprData[Enemy], pos.x, pos.y, 1, scl, 256, 0, 64, 64, 32, 32);
            }
        break;

    case eDie:
            sprite_render(sprData[Effect], pos.x, pos.y, 1, scl, 0, 64, 64, 64, 32, 32);
        break;
    }
}

void enemy_init()
{
    for (int i = 0; i < ENEMY_MAX; i++)
    {
	enemy[i].init();
    }
}

void enemy_update()
{
    for (int i = 0; i < ENEMY_MAX; i++)
    {
        if (enemy[i].exist)
        {
            enemy[i].update();
        }
        else
        {
            enemy[i].set_enemy();
        }
    }
}

void enemy_draw()
{
    for (int i = 0; i < ENEMY_MAX; i++)
    {
	enemy[i].draw();
    }
}
