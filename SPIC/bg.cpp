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
#if Debug
	case 0:
		fp = fopen("DATA\\Map\\first.txt", "rt");
		for (int y = 0; y < MAP_Y; y++)
		{
			for (int x = 0; x < MAP_X; x++)
			{
				fscanf(fp,"%d,",&map[y][x]);
			}
			fprintf(fp, "\n");
		}
		fclose(fp);
		break;
#endif // Debug


	}
}

void bg_init()
{
	load_mapdata(stagesetter());
	scroll_pos = -64;
	scroll_begin = 32;
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
	switch (game_state)
	{
	case 0:
	case 1:
		sprite_render(sprData[Bg], 0, 0, 1, 1, 0, SCREEN_HEIGHT,1920,1080);
		for (int y = 0; y < MAP_Y; y++)
		{
			for (int x = 0,begin= scroll_begin,fin=begin+32; begin < fin; x++,begin++)
			{
				if (map[y][begin]==0)continue;
				sprite_render(sprData[Map],
					(64 * x)+ scroll_pos, 64 * y,
					1, 1,
					(map[y][begin]%5)*64, 64 * (map[y][begin] / 5),
					64, 64);
			}
			
		}
		break;
	case 2:
		
		break;
	}
}


