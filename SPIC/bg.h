#ifndef INCLUDED_BG
#define INCLUDED_BG

#define area_top   (0)
#define area_under (1080)
#define area_left  (300)
#define area_right (1620)
#define scrollarea (3500)
#define MAP_Y (17)//ここはいじらない
#define MAP_X (300)//ここは配列の上限
#define STAGE1 (100)
#define STAGE2 (64)
#define STAGE3 (64)
void bg_init();
void bg_update();
void bg_draw();


#endif// ! INCLUDED_BG