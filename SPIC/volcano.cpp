#include "all.h"
#include "volcano.h"
using namespace GameLib;
using namespace input;
VOLCANO volcano;
OBSIDIAN obsidian;
extern OBJ player;
OBJ mgmg;
extern float scroll_pos;
extern float scroll_begin;
extern Sprite* sprData[Spr_Max];
extern int map[MAP_Y][MAP_X];
extern int dame_state;

////VOLCANO class////
void VOLCANO::set(float begin_posy, float fin_posx, float speed)
{
	set_state(1);
	this->speed.x = speed;
	pos = { 1920 - 225,begin_posy };
	fin_pos = fin_posx;
	timer = 60;
}
void VOLCANO::update()
{
	int next = get_state() + 1;
	volcano.rect = { volcano.pos.y - 150,volcano.pos.y + 150,volcano.pos.x,1920 };

	switch (get_state())
	{
	case 0:
		pos = { 1920-256,0 };
		break;
	case 1:
		timer--;
		if (timer <= 0)
		{
			timer = 20;
			set_state(next);
		}
		break;
	case 2://ã¸
		if (fin_pos <= pos.x) { pos.x -= speed.x; }
		else { set_state(next); }
		break;
	case 3:
		if (timer <= 0) { set_state(next); }
		timer--; 	pos.x += 0.5;
		break;
	case 4://‰º~

		if (pos.x < 2000) { pos.x += speed.x; }
		else { set_state(0); }
		break;
	}
	for (int y = 0; y < MAP_Y; y++)
	{
		for (int x = 0, begin = scroll_begin, fin = begin + 32; begin < fin; x++, begin++)
		{
			if (Judge.rect(64 * y, 64 * (y + 1), 64 * x, 64 * (x + 1), pos.x, pos.y - 150))
			{
				switch (map[y][begin])
				{
				case 5://…‚Ì‚Ó‚ê‚½‚Æ‚«‚Ìˆ—
					if (obsidian.get_state() == 0)
					{
					
					}
					break;
				}
		    }
			if (Judge.rect(64 * y, 64 * (y + 1), 64 * x, 64 * (x + 1), pos.x, pos.y + 150))
			{
				switch (map[y][begin])
				{
				case 5://…‚Ì‚Ó‚ê‚½‚Æ‚«‚Ìˆ—
					if (obsidian.get_state() == 0)
					{

					}
					break;
				}
			}
		}
	}
	if (Judge.rect(volcano.rect, player.rect))
	{
		dame_state = 1;
	}
		debug::setString("%d", Judge.rect(volcano.rect, player.rect));
}

void VOLCANO::draw()
{
	switch (get_state())
	{
	case 1:
		anim(sprData[Volcano], 12, 3, 1, 3, pos.x, pos.y, 1.5, 1, 0, 1080, 128, 128, 128, 64);
		break;
	case 2:
	case 3:
	case 4:
		anim(sprData[Volcano], 12, 3, 1, 3, pos.x, pos.y, 1, 1, 0, 1080+128, 2000, 128, 0, 64);
		break;
	}
}


////OBSIDIAN class////
void OBSIDIAN::set(VECTOR2 pos)
{
	set_state(1);
	this->pos = pos;
	exist = true;
}

void OBSIDIAN::update()
{
	rect = {pos.y-150,pos.y+150,pos.x,pos.x+size};
	Rect Top   = { rect.top,rect.under,rect.left,pos.x+50   };
	Rect Left  = { rect.under-50,rect.under,rect.left+50,rect.right };
	Rect Right = { rect.top,pos.y,rect.left+50,rect.right };

	switch (get_state())
	{
	case 0:
		exist = false;
		break;
	case 1:
		
		//pos.x ++;
		if (size < 1920)
			size += 10;
		if (pos.x > 1920)
			set_state(0);
		break;
	}
	debug::setString("top%d", Judge.rect(Top, player.rect));
	debug::setString("left%d", Judge.rect(Left, player.rect));
	debug::setString("right%d", Judge.rect(Right, player.rect));
	if (Judge.rect(Top,player.rect))
	{
		
		player.pos.x = rect.left - (32+12);
	}
	if (Judge.rect(Left, player.rect))
	{
		player.pos.y = rect.under+55;
	}
	if (Judge.rect(Right, player.rect))
	{
		player.pos.y = rect.top-55;
	}
}

void OBSIDIAN::draw()
{
	if (exist)
		primitive::rect(pos.x, pos.y, size, 300, 0, 150, 0, 0, 0, 1, 1);
}
void volcano_init()
{
	volcano.init();
	obsidian.init();
}
void volcano_update()
{
	
	if (TRG(0)&PAD_TRG3&&volcano.get_state() == 0) { volcano.set(player.pos.y, (player.pos.x - 50), 15); }
#if Debug

	if (TRG(0)&PAD_TRG3&&obsidian.get_state() == 0) { obsidian.set(VECTOR2{ player.pos.x + 100,player.pos.y }); }

#endif
	volcano.update();
	obsidian.update();
}
void volcano_draw()
{
	volcano.draw();
	obsidian.draw();
	mgmg.anim(sprData[Volcano], 12, 3, 1, 3, 1920 - 256, 0, 1, 1, 0, 0, 256, 1080);
	debug::display();
}