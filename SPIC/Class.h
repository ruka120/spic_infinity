#pragma once

struct Rect
{
	float top;
	float under;
	float left;
	float right;
};
//OBJクラス
class OBJ
{
private:
	int state;
	//前フレームの状態遷移の保存先
	int Previous_state;
	bool Previous_flg;
	//アニメーション情報関連
	int animetimer;
	int chipcou;
	int chipx;
	int chipy;
	//int switching_time;
	//初期化
	void chip_reset();
	//アニメーションタイマー初期化するためのフラグ返す関数
	bool timer_init(int STATE);
	bool effect_init(bool flg);
public:
	OBJ();
	Rect rect;
	void set_state(int STATE);
	int get_state();
	VECTOR2 pos;
	VECTOR2 speed;
    float scl;  //描画の時に変える
	bool exist;
	int hp;
	bool effect_flg;
    //画像データ
    //切り替え時間(フレーム単位)
    //横、縦のチップの個数(x,y)
    //チップの総数
    //描写位置(x,y)
    //スケール(x,y)
    //画像の開始位置(x,y)
    //1チップの大きさ(x,y)
    //基準点(x,y)
    //角度
    //色(r,g,b,a)
	void anim(GameLib::Sprite* data,
		const int time,
		int NumX, int NumY,
		int max,
		float posx, float posy,
		float sclx, float scly,
		float dataposx, float dataposy,
		float sizex, float sizey,
		float StandardX = 0.0f, float StandardY = 0.0f,
		float rad = 0.0f,
		float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);
	//画像データ
    //モーション終了後の状態
    //切り替え時間(フレーム単位)
    //横、縦のチップの個数(x,y)
    //チップの総数
    //描写位置(x,y)
    //スケール(x,y)
    //画像の開始位置(x,y)
    //1チップの大きさ(x,y)
    //基準点(x,y)
    //角度
    //色(r,g,b,a)
	void motion(GameLib::Sprite* data,
		int after,
		const int time,
		int NumX, int NumY,
		int max,
		float posx, float posy,
		float sclx, float scly,
		float dataposx, float dataposy,
		float sizex, float sizey,
		float StandardX = 0.0f, float StandardY = 0.0f,
		float rad = 0.0f,
		float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);
	
	void effect(GameLib::Sprite* data,
		const int time,
		int NumX, int NumY,
		int max,
		float posx, float posy,
		float sclx, float scly,
		float dataposx, float dataposy,
		float sizex, float sizey,
		float StandardX = 0.0f, float StandardY = 0.0f,
		float rad = 0.0f,
		float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);
};
class ENEMY :public OBJ
{
public:
    int type;
    bool isflg[2];
    bool get_flg();
    bool grounding;
    int jump_state;
    float jump_pos;
    float jump_speed;
    void init();
    void update();
    void draw();
    void jump_init(float pos);
    void jump_update();
};

class VOLCANO :
	public OBJ
{
private:
	int timer;
	float fin_pos;
public:
	VOLCANO() { speed.x = 10; }
	void init()
	{
		set_state(0); 
		rect = {pos.y - 64,pos.y + 64,pos.x,1920 };

	}
	void set(float begin_posy,float fin_posx,float speed);
	void update();
	void draw();

};
class OBSIDIAN :public OBJ
{
private:
	float size;
public:
	OBSIDIAN() { speed.x = 10; }
	void init() { size = 0; set_state(0); }
	void set(VECTOR2 pos);
	void update();
	void draw();
};

#define judge (0)
static class JUDGE
{
public:

#if(judge)
	//当たり判定代入用の変数
	//矩形の当たり判定
	//float px_a,float py_a ->当たり判定を行う2つのオブジェクトの1つ目の左上の座標(X,Y)
	//int sx_a,int sy_a ->当たり判定を行う2つのオブジェクトの1つ目の横と縦の長さ(X,Y)
	//float px_a,float py_a ->当たり判定を行う2つのオブジェクトの2つ目の左上の座標(X,Y)
	//int sx_a,int sy_a ->当たり判定を行う2つのオブジェクトの2つ目の横と縦の長さ(X,Y)
	bool rect(float px_a, float py_a, int sx_a, int sy_a,
		float px_b, float py_b, int sx_b, int sy_b);
#else
	////矩形の当たり判定
	//当たり判定を行う矩形の四点の座標(top,under,left,right)又はRECT構造体
	//当たり判定を行う座標(x,y)又はVECTOR2(pos)
	bool rect(float top, float under, float left, float right, float posx, float posy);
	bool rect(float top, float under, float left, float right, VECTOR2 pos);
	bool rect(Rect rect, VECTOR2 pos);
	bool rect(Rect rect, float posx, float posy);
	bool rect(Rect a, Rect b);
#endif
	//円の当たり判定
	//float px_a,folat py_a->当たり判定を行う2つのオブジェクトの1つ目の中心座標(X,Y)又はVECTOR2(pos)
	//int r_a-> 当たり判定を行う2つのオブジェクトの1つ目の半径
	//float px_b,folat py_b->当たり判定を行う2つのオブジェクトの2つ目の中心座標(X,Y)又はVECTOR2(pos)
	//int r_b-> 当たり判定を行う2つのオブジェクトの2つ目の半径
	bool circle(float px_a, float py_a, int r_a, float px_b, float py_b, int r_b);
	bool circle(VECTOR2 posa, int r_a, VECTOR2 posb, int r_b);
	bool circle(VECTOR2 posa, int r_a, float px_b, float py_b, int r_b);
	bool circle(float px_a, float py_a, int r_a, VECTOR2 posb, int r_b);

	//レーザーとの当たり判定
	//int xory ->ｘ座標の判定かｙ座標の判定の設定　(0->x,1->y)
	//float biginpos, float finfin ->判定の初め(bigin)と終わり(fin)の座標
	//float judgepos, float laserwidth ->判定線(レーザーの中心線)と幅(判定線からレーザーの)
	bool laser(int xory, float biginpos, float finpos,
		        float judgepos, float laserwidth,
		        VECTOR2 pos, float objwidth);
}Judge;