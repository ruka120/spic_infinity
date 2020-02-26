#include "all.h"
using namespace GameLib;
using namespace input;
int title_state;      // 状態
int title_timer;      // タイマー
float fadeOut;        // フェイドアウト
extern int nextScene; //シーン移行用
//CAT:画像読み込み
Sprite* sprData[Spr_Max];
wchar_t* sprName[] =
{
	L"./Data/Images/bg.png",
	L"./Data/Images/number.png",
	L"./Data/Images/mapchip.png",
    L"./Data/Images/player.png",
    L"./Data/Images/enemy.png",
	L"./Data/Images/stage.png",

};
void spr_load()
{
	for (int i = 0; i < Spr_Max; i++)
	{
		sprite_load(&sprData[i], sprName[i]);
	}
}
enum 
{
	stage1=0,
	stage2,
	stage3,
	max,
};
namespace stage
{
	int state;
	int num[5];
	float scl;
	float pos[5];
	int vect;
	int next;
	int timer;
	void set();
	void init();
	void reset();
	void update();
	void draw();
}
int stagesetter()
{
	return stage::num[2];
}
void stage::set()
{
	num[1] = num[2] - 1;
	if (num[1] < 0)num[1] = max-1;
	num[3] = num[2] + 1;
	if (num[3] >= max)num[3] = 0;
	num[4] = num[3] + 1;
	if (num[4] >= max)num[4] = 0;
	num[0] = num[1] - 1;
	if (num[0] < 0)num[0] = max - 1;
	
}
void stage::init()
{
	if (next > 2)vect = -1;
	else vect = 1;
}
void stage::reset()
{
	pos[4] = -820;
	pos[3] = -140;
	pos[2] = 540;
	pos[1] = 1200;
	pos[0] = 1220+640;
}

void stage::update()
{
	switch (state)
	{
	case 1:
		init();
		state++;
		break;
	case 2:
		if (scl <= 0.5)
		{
			state++;
		}
		else
		{
		scl -= 0.05;
		pos[0] -= 80;
		pos[1] -= 40;
		pos[3] += 40;
		pos[4] += 80;
		}
		break;
	case 3:
		for (int i = 0; i < 5; i++)
		{
			pos[i] -= (vect * 10);
		}
		if (pos[1] <= 540 || pos[3] >= 540)
		{
		    num[2] = num[next];
			set();
			reset();
			timer = 0;
		    state++;
		}
		break;
	case 4: 
		if (TRG(0)&PAD_SELECT)
		{
			state++;
		}
		if(LEFT||RIGHT)
		{
			if (LEFT) { stage::next = 1; stage::state = 1; }
		    if (RIGHT){ stage::next = 3; stage::state = 1; }
		}
		else if(timer>60)
		state++;
		timer++;
		break;
	case 5:
		if (scl >= 1)
		{
			state++;
		}
		else
		{
		scl += 0.05;
		pos[0] += 80;
		pos[1] += 40;
		pos[3] -= 40;
		pos[4] -= 80;
		}
		break;
	case 6:
		state = 0;
		break;
	}
}
void stage::draw()
{
	for (int i = 0; i < 5; i++)
	{
		sprite_render(sprData[Stage], 1920 / 2, pos[i], scl, scl, 1920 * num[i], 0, 1920, 1080, 1920 / 2, 1080 / 2);
	}
}
void title_init()
{
	spr_load();
	stage::num[2] = stage1;
	stage::set();
	stage::scl = 1;
	stage::pos[0] = 2700;
	stage::pos[1] = 1620;
	stage::pos[2] = 540;
	stage::pos[3] = -540;
	stage::pos[4] = -1620;
    title_state = 0;
    title_timer = 0;
}

void title_update()
{
	static const int title_max=3;//タイトル場面の最大数
    switch (title_state)
    {
    case 0:
		music::play(0, true);
        title_state++;
        break;
    case 1:
        if (TRG(0) & PAD_START&&stage::state==0)
        {
            fadeOut=0.0f;
            title_state++;
        }
		if (TRG(0)&PAD_TRG1)sound::play(0);
		if (LEFT&&stage::state == 0) { stage::next  = 1; stage::state++; }
		if (RIGHT&&stage::state == 0) { stage::next = 3; stage::state++; }
		//if (stage::state != 0)
		{
			stage::update();
		}
        break;
    case 2:
        fadeOut += 0.0167f;
        if (fadeOut >= 1.0f)
        {  title_state++; }
        break;
    }
    if (title_state == title_max) 
    { nextScene = SCENE_GAME; }
    title_timer++;
   }

void title_draw()
{
	switch (title_state)
	{
	case 0:
	case 1:
		sprite_render(sprData[Bg],
			0, 0,
			1, 1,
			0, 0,
			SCREEN_WIDTH, SCREEN_HEIGHT);
		stage::draw();
		break;
	case 2:
		if (fadeOut > 0.0f)
		{
			primitive::rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 0, 1- fadeOut, 1 - fadeOut, 1 - fadeOut, fadeOut);
		}
		break;
	}
#if(Debug)
	for (int i = 0; i < 5; i++)
	{
		debug::setString("pos[%d]:%f", i, stage::pos[i]);
	}
	debug::setString("num[0]:%d", stage::num[0]);
	debug::setString("num[1]:%d", stage::num[1]);
	debug::setString("num[2]:%d", stage::num[2]);
	debug::setString("num[3]:%d", stage::num[3]);
	debug::setString("num[4]:%d", stage::num[4]);
	debug::setString("vect:%d", stage::vect);
	debug::display();
#endif
}

void title_end()
{
	music::unload(0);
	for (int i = 0; i < Spr_Max; i++)
	{
		SAFE_DELETE(sprData[i]);
	}
}



