#include "all.h"
#include "volcano.h"
using namespace GameLib;
using namespace input;
VOLCANO volcano;
OBSIDIAN obsidian;
extern OBJ player;
////VOLCANO class////
void VOLCANO::set(float begin_posy, float fin_posx, float speed)
{
	set_state(1);
	this->speed.x = speed;
	pos = { 1920,begin_posy };
	fin_pos = fin_posx;
	timer = 20;
}
void VOLCANO::update()
{
	int next = get_state() + 1;

	switch (get_state())
	{
	case 0:
		pos = { 1920,0 };
		break;
	case 1://è„è∏
		if (fin_pos <= pos.x) { pos.x -= speed.x; }
		else { set_state(next); }
		break;
	case 2:
		if (timer <= 0) { set_state(next); }
		timer--; 	pos.x += 0.5;
		break;
	case 3://â∫ç~

		if (pos.x < 2000) { pos.x += speed.x; }
		else { set_state(0); }
		break;
	}
}

void VOLCANO::draw()
{
	primitive::rect(pos.x, pos.y, 1920, 300, 0, 150, 0, 1, 0, 0, 0.6);
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
	volcano.rect = { volcano.pos.y - 150,volcano.pos.y + 150,volcano.pos.x,1920 };
	switch (get_state())
	{
	case 0:
		exist = false;
		break;
	case 1:
		pos.x ++;
		if (size < 1920)
			size += 10;
		if (pos.x > 1920)
			set_state(0);
		break;
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
#if Debug
	if (TRG(0)&PAD_TRG3&&volcano.get_state() == 0) { volcano.set(player.pos.y, (player.pos.x - 50), 10); }
	debug::setString("%d", Judge.rect(volcano.rect, player.rect));
	if (TRG(0)&PAD_TRG3&&obsidian.get_state() == 0) { obsidian.set(VECTOR2{ player.pos.x + 50,player.pos.y }); }

#endif
	volcano.update();
	obsidian.update();
}
void volcano_draw()
{
	volcano.draw();
	obsidian.draw();
	debug::display();
}