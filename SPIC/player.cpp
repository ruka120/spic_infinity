#include "all.h"
using namespace GameLib;
using namespace input;
extern Sprite* sprData[Spr_Max];
OBJ player;

extern float world_pos;
extern float scroll_pos;
extern float scroll_begin;
extern ENEMY enemy;

OBJ ui[5];
int dame_timer;
int dame_state;
extern int play;
extern VOLCANO volcano;
extern float scroll_pos;
extern float scroll_begin;
extern Sprite* sprData[Spr_Max];
extern int game_state;
bool over_flg();
namespace Pjump
{
 bool isflg[3];
 int state;
 float pos;
 float speed;
 void init(float pos);
 bool get_flg();
 void update();
}

//��ԑJ�ڗpenum�N���X
enum
{
	Wait=0,
	Move,
	Jump,
	Die
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
	player.pos={0,1080/2};
	world_pos = -300;
	player.rect = { player.pos.y - 50,player.pos.y + 50,player.pos.x - 50,player.pos.x + 50 };
	Pjump::state = 0;
	dame_state = 0;
	for (int i = 0; i < 5; i++)
		ui[i].set_state(0);
	player.hp = 5;
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
	if (isflg[0] || isflg[1] || isflg[2]) { return true; }
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

    if (RIGHT) { player.scl = 1; }
    if (LEFT)  { player.scl = -1; }

	player.rect = {player.pos.y-16,player.pos.y+16,player.pos.x-32,player.pos.x+32};
    enemy.rect = { enemy.pos.y - 32,enemy.pos.y + 32,enemy.pos.x - 32,enemy.pos.x + 32 };
		
	//debug::setString("%d", dame_timer);
	//player.rect = {player.pos.y-50,player.pos.y+50,player.pos.x-50,player.pos.x+50};
	Pjump::isflg[0] = false;
	Pjump::isflg[1] = false;
	switch (dame_state)
	{
	case 1:
		dame_timer = 120;
		dame_state++;
		for (int i = 4; i >= 0; i--)
		{
			if (ui[i].get_state() == 2|| ui[i].get_state() == 1)continue;
			ui[i].set_state(1);
			break;
		}
		//player.hp--;
		break;
	case 2:
		dame_timer--;
		if (dame_timer <= 0)
		{
			dame_state = 0;
		}
		break;
	}
		//debug::setString("%d", player.hp);
	//�}�b�v�Ƃ̓����蔻��
	//player.pos.x += 0.5;
	if (TRG(0)&PAD_TRG3&&volcano.get_state() == 0) { volcano.set(player.pos.y, (player.pos.x - 50), 50); }
	for (int y = 0; y < MAP_Y; y++)
	{
		for (int x = 0,begin=scroll_begin,fin=begin+32; begin < fin; x++,begin++)
		{
		if (Judge.rect(64 * y, 64 * (y + 1), (64 * x)+ scroll_pos, (64 * (x + 1))+ scroll_pos, player.rect.right, player.rect.top))
			{
		//	debug::setString("%d", map[y][begin]);
				switch (map[y][begin])
				{
				case 0:
					
					break;
				case 5:
					result_init(clear);
				case 3: 
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
				case 7:
					player.pos.y = (64 * y);
					break;
				}
				switch (map[y][begin - 1])
				{
				case 10:
					Pjump::speed = 0;
					break;
				}
			}
		if (Judge.rect(64 * y, 64 * (y + 1), (64 * x) + scroll_pos, (64 * (x + 1)) + scroll_pos, player.rect.right, player.rect.under))
		{
		//	debug::setString("%d", map[y][begin]);
			switch (map[y][begin])
			{
			case 0:
				break;
			case 5:
				result_init(clear);
			case 3:
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
			case 8:
				player.pos.y = (64 * y);
				break;
			}
			switch (map[y][begin - 1])
			{
			case 10:
				Pjump::speed = 0;
				break;
			}
		}
	
		}
	}

	if (Pjump::state == 0)player.pos.x += 12;

    //�G�l�~�[�Ƃ̓����蔻��
    /*if (Judge.rect(enemy.rect.top, enemy.rect.under, enemy.rect.left, enemy.rect.right, player.pos.x, player.pos.y))
    {
        
    }*/



//	debug::setString("%f", scroll_pos);
//	debug::setString("%f", scroll_pos);
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
            player.pos.y += 5;
            if (player.get_state() != Jump)
                player.set_state(Move);
        }
        if (RIGHT)
        {
            //if (world_pos > -scrollarea)world_pos -= 5;
            player.pos.y -= 5;
            if (player.get_state() != Jump)
                player.set_state(Move);
        }
    }
    else  if (player.get_state() == Move)player.set_state(Wait);
#if (Debug)
    if (Pjump::state == 0 && JUMP && Pjump::get_flg())
    {
        Pjump::state = 1; 
    }

	
	if (UP) {
		for (int i = 0; i < 5; i++)
		{
		//	ui[i].set_state(1);
		}
	}
	//if (DOWN) { player.pos.x += 5; }
#endif
	if (Pjump::state == 0 &&JUMP&&Pjump::get_flg()) { Pjump::state = 1; }
	Pjump::update();
	if (player.pos.x < 32) { Pjump::speed = 0; player.pos.x = 50; }
	if (player.pos.x > 1920-200)
	{
		for (int i = 4; i >= 0; i--)
		{
			if (ui[i].get_state() == 2 || ui[i].get_state() == 1)continue;
			ui[i].set_state(1);
		}
		player.set_state(Die);
		result_init(over); 
	}
	if (player.pos.y < 50) { player.pos.y = 50; }
	if (player.pos.y > 1030) { player.pos.y = 1030; }

	//debug::setString("world_pos:%f", world_pos);
	if (over_flg())
	{
		player.set_state(Die);
		result_init(over);
	}
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
	case Die:
		player.motion(sprData[Player], 100, 8, 9, 1, 9,player.pos.x, player.pos.y, 1, player.scl, 0, 64 * 5, 64, 64, 32, 32);
		break;
	}
	//debug::display();
	player.effect(sprData[Effect], 5, 4, 1, 4, player.pos.x, player.pos.y, 1, 1, 0, 0, 64, 64, 32, 32);
    //Damage
        //sprite_render(sprData[Player], 10, 1, 1, 1, player.pos.x, player.pos.y, 1, player.scl, 0, 192, 64, 64, 32, 32);
}
void ui_draw()
{
	for (int i = 0; i < 5; i++)
	{
		switch ( ui[i].get_state())
		{
		case 0://�̗͂���
			ui[i].anim(sprData[Ui], 15, 3, 1, 3, 64 * i, 1080-64, 0.5, 0.5, 0, 0, 128, 128, 0, 0);
			break;
		case 1://�R���郂�[�V����
			ui[i].motion(sprData[Ui], 2,15, 5, 1, 5, 64 * i, 1080 - 64, 0.5, 0.5, 0, 128, 128, 128, 0, 0);
			break;
		case 2://�̗͂Ȃ�
			break;
		}
	}
}
bool over_flg()
{
	for (int i = 0; i < 5; i++)
	{
		if (ui[i].get_state() > 1)continue;
		return false;
	}
	return true;
}