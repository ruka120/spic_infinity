#include "all.h"

using namespace GameLib;
using namespace input;
extern int game_timer;
extern int game_state; 
extern Sprite* sprData[Spr_Max];

OBJ bg[2];
float world_pos;
int map[MAP_Y][MAP_X];

float scroll_pos;
float scroll_begin;

void load_mapdata(int num)
{
		FILE *fp;
	switch (num)
	{

	case 0:
		fp = fopen("DATA\\Map\\stage1.csv", "rt");
		for (int y = 0; y < MAP_Y; y++)
		{
			for (int x = 0; x < STAGE1; x++)
			{
				fscanf(fp,"%d,",&map[y][x]);
			}
			fprintf(fp, "\n");
		}
		fclose(fp);
		scroll_begin = 100-32;
		break;
	case 1:
		fp = fopen("DATA\\Map\\stage2.csv", "rt");
		for (int y = 0; y < MAP_Y; y++)
		{
			for (int x = 0; x < STAGE1; x++)
			{
				fscanf(fp, "%d,", &map[y][x]);
			}
			fprintf(fp, "\n");
		}
		fclose(fp);
		scroll_begin = 100 - 32;
		break;


	}
}

void bg_init()
{
	load_mapdata(stagesetter());
	scroll_pos = -64;
	
}

void bg_update()
{
	if(scroll_begin!=0&&scroll_pos<0)scroll_pos++;
	if (scroll_pos >= 0)
	{
		scroll_pos = -64;
		scroll_begin--;
	}
	if (scroll_pos<=-124)
	{
		scroll_pos = -64;
		scroll_begin++;
	}

}

void bg_draw()
{
	//primitive::rect(0, 0, 1920, 1080,0,0,0,0,0,0);
	switch (game_state)
	{
	case 0:
	case 1:
sprite_render(sprData[Bg], 0, 0, 1, 1, 0, SCREEN_HEIGHT,1920,1080,0,0,0,1,1,1,0.8);
		for (int y = 0; y < MAP_Y; y++)
		{
			for (int x = 0,begin= scroll_begin,fin=begin+32; begin < fin; x++,begin++)
			{
				if (map[y][begin]<=0)continue;
				sprite_render(sprData[Map],
					(64 * x)+ scroll_pos, 64 * y,
					1, 1,
					(map[y][begin]%11)*64, 64 * (map[y][begin] / 11),
					64, 64);
			}
			
		}
		break;
	case 2:
		
		break;
	}
}


