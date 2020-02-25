#include "all.h"
using namespace GameLib;
using namespace input;
OBJ player;


extern float world_pos;
extern float scroll_pos;
extern float scroll_begin;
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

void player_init()
{
	player.pos={0,1080/2};
	world_pos = -300;
	Pjump::state = 0;
	
}

void Pjump::init(float pos)
{
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
		if (player.pos.x>=Pjump::pos)Pjump::state = 0;
		player.pos.x -= Pjump::speed;
		break;
	}

}
extern int map[MAP_Y][MAP_X];

void player_update()
{			
	player.rect = {player.pos.y-50,player.pos.y+50,player.pos.x-50,player.pos.x+50};
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
						player.pos.x = ((64 * (x)-50)+ scroll_pos);
					if (Pjump::state == 3) 
						{ Pjump::state = 0;}
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
					player.pos.x = ((64 * (x)-50) + scroll_pos);
				if (Pjump::state == 3)
					{ Pjump::state = 0; }
				}
				break;
			}
		}
		}
	}
	if (Pjump::state == 0)player.pos.x += 12;
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
	
	if(LEFT)
	{
	//	if(world_pos<0)world_pos += 5;
		
		player.pos.y += 5;
	}
	if (RIGHT)
	{
		//if (world_pos > -scrollarea)world_pos -= 5;
		player.pos.y -= 5;
	}
#if (Debug)

	
	//if (UP) { player.pos.x -= 5; }
	//if (DOWN) { player.pos.x += 5; }
	if (Pjump::state == 0 &&JUMP&&Pjump::get_flg()) { Pjump::state = 1; }
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
		break;
	case Move:
		break;
	case Jump:
		break;
	}
	//debug::display();
	
	primitive::rect(player.pos, { 100,100 }, { 50,50 });
}
	