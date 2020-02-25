#ifndef INCLUDED_COMMON
#define INCLUDED_COMMON

#define SAFE_DELETE(x)  if(x){delete x;x=NULL;}    
#define ToRadian(x)     DirectX::XMConvertToRadians(x) 
#define SCREEN_WIDTH    (1920)   // 画面の幅
#define SCREEN_HEIGHT   (1080)   // 画面の高さ
#define SCENE_TITLE     (0)
#define SCENE_GAME      (1)
#define Debug           (true)
//キー関連
#define UP    (STATE(0)&PAD_UP)
#define DOWN  (STATE(0)&PAD_DOWN)
#define LEFT  (STATE(0)&PAD_LEFT)
#define RIGHT (STATE(0)&PAD_RIGHT)
#define JUMP  (TRG(0)&PAD_TRG1)
void spr_load();//画像読み込み関数

//// スプライト用 ////
////命名規則頭文字のみ大文字後は小文字////
enum 
{
	Bg = 0,
	Number,
	Map,
    Enemy,
	Stage,
	Spr_Max,

};


#endif// ! INCLUDED_COMMON
