#include "all.h"
using namespace GameLib;
using namespace input;
int title_state;      // ���
int title_timer;      // �^�C�}�[
float fadeOut;        // �t�F�C�h�A�E�g
OBJ title;
extern int nextScene; //�V�[���ڍs�p
//CAT:�摜�ǂݍ���
Sprite* sprData[Spr_Max];
wchar_t* sprName[] =
{
	L"./Data/Images/bg.png",
	L"./Data/Images/number.png",
	L"./Data/Images/chip.png",
    L"./Data/Images/player.png",
    L"./Data/Images/enemy.png",
	L"./Data/Images/stage.png",
	L"./Data/Images/volcano.png",
	L"./Data/Images/pose.png",
	L"./Data/Images/ui.png",
	L"./Data/Images/effect.png",
	L"./Data/Images/tutorial.png",
	L"./Data/Images/waku.png",
	L"./Data/Images/clear.png",
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
bool keyflg;
void title_init()
{
	fadeOut = 0;
	keyflg = false;
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
void Tfade(const int next)
{
	if (keyflg)
	{
    fadeOut += 0.0167f;
	if (fadeOut >= 1.0f)
	{
		fadeOut = 0.0f;
		title_state=next;
		keyflg = false;
	}
	}
	
}
void title_update()
{
	static const int title_max=5;//�^�C�g����ʂ̍ő吔
    switch (title_state)
    {
    case 0:
		music::play(0, true);
        title_state++;
        break;
	case 1:
		if (TRG(0))
		{
			keyflg = true;
		}
		Tfade(2);
		break;
    case 2:
		if (TRG(0) & PAD_TRG1) 
		{
			keyflg = true;
		}
		Tfade(0);
        if (TRG(0) & PAD_TRG3&&stage::state==0)
        {
            fadeOut=0.0f;
            title_state++;
			
        }

		if (LEFT&&stage::state == 0) { stage::next  = 1; stage::state++; }
		if (RIGHT&&stage::state == 0) { stage::next = 3; stage::state++; }
	
		{
			stage::update();
		}
        break;
    case 3:
        fadeOut += 0.0167f;
        if (fadeOut >= 1.0f)
        {
			if (stagesetter() != 2)
			{
				nextScene = SCENE_GAME;
			}
			else
			{
            fadeOut = 0;
			tutorial_init();
			title_state++; 
			}
			
		}
        break;
	case 4:
		if (TRG(0) & PAD_TRG1)
		{
			keyflg = true;
		}
		Tfade(2);
		tutorial_update();
		break;
    }
    if (title_state == title_max) 
    { 
		nextScene = SCENE_GAME; 
	}
    title_timer++;
   }

void title_draw()
{
	switch (title_state)
	{
	case 0:
	case 1:
		title.anim(sprData[Bg], 10, 6, 1, 6, 0, 0, 1, 1, 0, 0, 1920, 1080);
		break;
	case 2:
		primitive::rect(0, 0, 1920, 1080, 0, 0, 0, 0, 0, 0);
		stage::draw();
        sprite_render(sprData[Ui], 1700, 200, 1, 1, 0, 256, 200, 192);
		break;
	case 3:
		stage::draw();
		break;
	case 4:
		tutorial_draw();
		break;
	}
		if (fadeOut > 0.0f)
		{
			primitive::rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 0, 1- fadeOut, 1 - fadeOut, 1 - fadeOut, fadeOut);
		}
}

void title_end()
{
	music::unload(0);
	for (int i = 0; i < Spr_Max; i++)
	{
		SAFE_DELETE(sprData[i]);
	}
}



