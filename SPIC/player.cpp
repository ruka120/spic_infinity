#include "all.h"
using namespace GameLib;
using namespace input;
extern Sprite* sprData[Spr_Max];
OBJ player;

extern float world_pos;
extern float scroll_pos;
extern float scroll_begin;
extern ENEMY enemy;

namespace Pjump
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
	Wait=0,
	Move,
	Jump
};

enum
{
    Left,
    Right
};

void player_init()
{
    player.set_state(Wait);
    player.scl = 1;
    player.direction = Right;
	player.pos={0,1080/2};
	world_pos = -300;
	Pjump::state = 0;
}

void Pjump::init(float pos)
{
    player.set_state(Jump);
	Pjump::state = 2;
	Pjump::pos = pos;
	Pjump::speed = 15;
}
bool Pjump::get_flg()
{
	if (isflg[0] || isflg[1] ) { return true; }
	return false;
}
void Pjump::update()
{
	switch (Pjump::state)
	{
	case 1:
     
		Pjump::init(player.pos.x);
		break;
	case 2:
		Pjump::speed -= 0.5;
		if (Pjump::speed <= 0)Pjump::state = 3;
		player.pos.x -= Pjump::speed;
		break;
	case 3:
		Pjump::speed -= 0.5;
        if (player.pos.x >= Pjump::pos)
        {
            Pjump::state = 0;
            player.set_state(Wait);
        }
        player.pos.x -= Pjump::speed;
		break;
	}

}
extern int map[MAP_Y][MAP_X];

void player_update()
{			
    if (player.direction == Right) { player.scl = 1; }
    if (player.direction == Left) { player.scl = -1; }

    //if (LEFT || RIGHT) { player.set_state(Move); }
  //  else if(JUMP) {player.set_state(Jump); }
  //  else { player.set_state(Wait); }

	player.rect = {player.pos.y-32,player.pos.y+32,player.pos.x-32,player.pos.x+32};
    enemy.rect = { enemy.pos.y - 32,enemy.pos.y + 32,enemy.pos.x - 32,enemy.pos.x + 32 };

	Pjump::isflg[0] = false;
	Pjump::isflg[1] = false;
	
	//マップとの当たり判定
	//player.pos.x += 0.5;
	for (int y = 0; y < MAP_Y; y++)
	{
		for (int x = 0,begin=scroll_begin,fin=begin+32; begin < fin; x++,begin++)
		{
		if (Judge.rect(64 * y, 64 * (y + 1), (64 * x)+ scroll_pos, (64 * (x + 1))+ scroll_pos, player.rect.right, player.rect.top))
			{
			debug::setString("%d", map[y][begin]);
				switch (map[y][begin])
				{
				case 0:
					
					break;
				case 1:
					Pjump::isflg[0] = true;
                    if (Pjump::state != 2)
                    {
                        player.pos.x = ((64 * (x)-32) + scroll_pos);
                        if (Pjump::state == 3)
                        {
                            player.set_state(Wait);
                            Pjump::state = 0;
                        }
                    }
					break;
				}
			}
		if (Judge.rect(64 * y, 64 * (y + 1), (64 * x) + scroll_pos, (64 * (x + 1)) + scroll_pos, player.rect.right, player.rect.under))
		{
			debug::setString("%d", map[y][begin]);
			switch (map[y][begin])
			{
			case 0:
				
				break;
			case 1:
				Pjump::isflg[1] = true;
                if (Pjump::state != 2)
                {
                    player.pos.x = ((64 * (x)-32) + scroll_pos);
                    if (Pjump::state == 3)
                    {
                        player.set_state(Wait);
                        Pjump::state = 0;
                    }
                }
				break;
			}
		}
		}
	}
	if (Pjump::state == 0)player.pos.x += 12;

    //エネミーとの当たり判定
    /*if (Judge.rect(enemy.rect.top, enemy.rect.under, enemy.rect.left, enemy.rect.right, player.pos.x, player.pos.y))
    {
        
    }*/



	debug::setString("%f", scroll_pos);
	switch (player.get_state())
	{
	case Wait:
		break;
	case Move:
		break;
	case Jump:
		break;
	}
    if (LEFT || RIGHT)
    {
        if (LEFT)
        {
            //	if(world_pos<0)world_pos += 5;
            player.direction = Left;
            player.pos.y += 5;
            if (player.get_state() != Jump)
                player.set_state(Move);
        }
        if (RIGHT)
        {
            //if (world_pos > -scrollarea)world_pos -= 5;
            player.direction = Right;
            player.pos.y -= 5;
            if (player.get_state() != Jump)
                player.set_state(Move);
        }
    }
    else  if (player.get_state() == Move)player.set_state(Wait);
#if (Debug)

	
	//if (UP) { player.pos.x -= 5; }
	//if (DOWN) { player.pos.x += 5; }
    if (Pjump::state == 0 && JUMP && Pjump::get_flg())
    {
        Pjump::state = 1; 
    }
	Pjump::update();
#endif
	if (player.pos.x < 50) { Pjump::speed = 0; player.pos.x = 50; }
	if (player.pos.x > 1870) { player.pos.x = 1870; }
	if (player.pos.y < 50) { player.pos.y = 50; }
	if (player.pos.y > 1030) { player.pos.y = 1030; }
#if(0)
	if (player.pos.x - 50 < area_left&&world_pos < -300) { player.pos.x = (area_left+50); world_pos += 5;}
	else if (player.pos.x - 50 < 0) { player.pos.x = (0 + 50);}
	if (player.pos.x + 50 > area_right&&world_pos >-(scrollarea-300)) { player.pos.x = (area_right - 50); world_pos -= 5;}
	else if (player.pos.x + 50 > 1920) { player.pos.x = (1920 - 50);}
#endif
	//debug::setString("world_pos:%f", world_pos);
}

void player_draw()
{
	switch (player.get_state())
	{
	case Wait:
        player.anim(sprData[Player], 10, 8, 1, 8, player.pos.x, player.pos.y, 1, player.scl, 0, 0, 64, 64, 32, 32);

		break;
	case Move:
        player.anim(sprData[Player], 10, 4, 1, 4, player.pos.x, player.pos.y, 1, player.scl, 0, 64, 64, 64, 32, 32);
		break;
	case Jump:
        switch (Pjump::state)
        {
        case 2:
            sprite_render(sprData[Player], player.pos.x, player.pos.y, 1, player.scl, 0, 128, 64, 64, 32, 32);
            break;

        case 3:
           sprite_render(sprData[Player], player.pos.x, player.pos.y, 1, player.scl, 64, 128, 64, 64, 32, 32);
            break;
        }
		break;
	}
	//debug::display();

    //Damage
        //player.anim(sprData[Player], 10, 1, 1, 1, player.pos.x, player.pos.y, 1, 1, 0, 192, 64, 64, 32, 32);
}
	