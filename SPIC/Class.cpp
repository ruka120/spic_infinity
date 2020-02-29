#include "all.h"
using namespace GameLib;
void CHIP::reset()
{
	cou = 1;
	x = 0;
	y = 0;
}


OBJ::OBJ()
{
	OBJ::Previous_state = -1;
	OBJ::Previous_flg = false;
}
void OBJ::set_state(int STATE)
{
	OBJ::state = STATE;
}
int OBJ::get_state()
{
	return OBJ::state;
}
bool OBJ::timer_init(int STATE)
{
	//もし、前フレームと状態が違うのであれば初期化するフラグを立てる
	if (OBJ::Previous_state != STATE) {
		Previous_state = STATE;
		return true;
	}
	else
	{
		Previous_state = STATE;
		return false;
	}
}
bool OBJ::effect_init(bool flg)
{
	if(flg)
	{
	if (OBJ::Previous_flg != flg) {
		Previous_flg = flg;
		return true;
	}
	else
	{
		Previous_flg = flg;
	}
	}
		return false;
}
//ループアニメーション
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
void OBJ::anim(
	Sprite* data,
	const int time,
	int NumX, int NumY,
	int max,
	float posx, float posy,
	float sclx, float scly,
	float dataposx, float dataposy,
	float sizex, float sizey,
	float StandardX, float StandardY,
	float rad,
	float r, float g, float b, float a
)
{
	//OBJ::switching_time = time;
	if (timer_init(OBJ::state))
	{
		OBJ::animetimer = 0;
	}
	if (OBJ::animetimer <= 0)
	{
		OBJ::chip[0].reset();
	}
	if (animetimer != 0 && animetimer%time == 0)
	{
		OBJ::chip[0].x++;
		OBJ::chip[0].cou++;
		if (OBJ::chip[0].x >= NumX)
		{
			OBJ::chip[0].x = 0;
			OBJ::chip[0].y++;
		}
		if (chip[0].y >= NumY)
		{
			chip[0].y = 0;
		}
		if (NumX*NumY != max && OBJ::chip[0].cou > max)
		{
			chip[0].cou = 1;
			chip[0].x = chip[0].y = 0;
		}
	}
	sprite_render
	(
		data,
		posx, posy,
		sclx, scly,
		dataposx + (sizex*chip[0].x), dataposy + (sizey*chip[0].y),
		sizex, sizey,
		StandardX, StandardY,
		rad,
		r, g, b, a
	);
	OBJ::animetimer++;
}
//1通りの動きをしたら終了
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
void OBJ::motion(
	Sprite * data,
	int after,
	const int time,
	int NumX, int NumY,
	int max,
	float posx, float posy,
	float sclx, float scly,
	float dataposx, float dataposy,
	float sizex, float sizey,
	float StandardX, float StandardY,
	float rad,
	float r, float g, float b, float a)
{
	//OBJ::switching_time = time;
	if (timer_init(OBJ::state))
	{
		OBJ::animetimer = 0;
	}
	if (OBJ::animetimer <= 0)
	{
		OBJ::chip[1].reset();
	}
	if (animetimer != 0 && animetimer%time == 0)
	{
		chip[1].x++;
		chip[1].cou++;
		if (chip[1].x >= NumX)
		{
			chip[1].x = 0;
			chip[1].y++;
		}
		if (chip[1].y >= NumY)
		{
			chip[1].y = 0;
		}
		if (chip[1].cou >= max)
		{
			OBJ::state = after;
		}
	}
	sprite_render
	(
		data,
		posx, posy,
		sclx, scly,
		dataposx + (sizex*chip[1].x), dataposy + (sizey*chip[1].y),
		sizex, sizey,
		StandardX, StandardY,
		rad,
		r, g, b, a
	);
	OBJ::animetimer++;
}

void OBJ::effect(GameLib::Sprite * data,const int time, int NumX, int NumY, int max, float posx, float posy, float sclx, float scly, float dataposx, float dataposy, float sizex, float sizey, float StandardX, float StandardY, float rad, float r, float g, float b, float a)
{
	if (!effect_flg)return;
	if (effect_init(effect_flg))
	{
		OBJ::animetimer = 0;
	}
	if (OBJ::animetimer <= 0)
	{
		OBJ::chip[2].reset();
	}
	if (animetimer != 0 && animetimer%time == 0)
	{
		chip[2].x++;
		chip[2].cou++;
		if (chip[2].x >= NumX)
		{
			chip[2].x = 0;
			chip[2].y++;
		}
		if (chip[2].y >= NumY)
		{
			chip[2].y = 0;
		}
		if (chip[2].cou > max)
		{
			Previous_flg = false;
			effect_flg = false;
			return;
		}
	}
	sprite_render
	(
		data,
		posx, posy,
		sclx, scly,
		dataposx + (sizex*chip[2].x), dataposy + (sizey*chip[2].y),
		sizex, sizey,
		StandardX, StandardY,
		rad,
		r, g, b, a
	);
	OBJ::animetimer++;
}

//当たり判定クラス//
#if(judge)
bool JUDGE::rect(float px_a, float py_a, int sx_a, int sy_a, float px_b, float py_b, int sx_b, int sy_b)
{
	bool jflg[2];
	float px_c, py_c, px_d, py_d;
	px_c = (px_a + sx_a), py_c = (py_a + sy_a), px_d = (px_b + sx_b), py_d = (py_b + sy_b);
	if (px_a <= px_b || px_a <= px_d) { if (px_c >= px_b || px_c >= px_d) { jflg[0] = true; } }
	else if (px_b <= px_a || px_b <= px_c) { if (px_d >= px_a || px_d >= px_c) { jflg[0] = true; } }
	else { jflg[0] = false; }
	if (py_a <= py_b || py_a <= py_d) { if (py_c >= py_b || py_c >= py_d) { jflg[1] = true; } }
	else if (py_b <= py_a || py_b <= py_c) { if (py_d >= py_a || py_d >= py_c) { jflg[1] = true; } }
	else { jflg[1] = false; }
	if (jflg[0] == true && jflg[1] == true) { return true; }
	else { return false; }
}



#else 
bool JUDGE::rect(float top, float under, float left, float right, float posx, float posy)
{
	if (top > posy)    return false;
	if (under < posy)  return false;
	if (left > posx)   return false;
	if (right < posx)  return false;
	return true;
}

bool JUDGE::rect(float top, float under, float left, float right, VECTOR2 pos)
{
	if (top > pos.y)    return false;
	if (under < pos.y)  return false;
	if (left > pos.x)   return false;
	if (right < pos.x)  return false;
	return true;
}

bool JUDGE::rect(Rect rect, VECTOR2 pos)
{
	if (rect.top > pos.y)    return false;
	if (rect.under < pos.y)  return false;
	if (rect.left > pos.x)   return false;
	if (rect.right < pos.x)  return false;
	return true;
}
bool JUDGE::rect(float top, float under, float left, float right, Rect a)
{
	if (top    > a.under)    return false;
	if (under < a.top)  return false;
	if (left   > a.right)   return false;
	if (right < a.left)  return false;
	return true;
}
bool JUDGE::rect(Rect rect, float posx, float posy)
{
	if (rect.top > posy)	      return false;
	if (rect.under < posy)  return false;
	if (rect.left > posx)     return false;
	if (rect.right < posx)    return false;
	return true;
}

#endif
bool JUDGE::circle(float px_a, float py_a, int r_a, float px_b, float py_b, int r_b)
{
	float xa_b = ((px_a - px_b)*(px_a - px_b));
	float ya_b = ((py_a - py_b)*(py_a - py_b));
	float ra_b = ((r_a + r_b)*(r_a + r_b));
	if (ra_b >= (xa_b + ya_b)) { return true; }
	else { return false; }
}
bool JUDGE::rect(Rect a, Rect b)
{
	
	if (a.right  <  b.left)   return false;
	if (a.left   >  b.right)  return false;
	if (a.under  <  b.top)    return false;
	if (a.top    >  b.under)  return false;
	return true;
}
bool JUDGE::circle(VECTOR2 posa, int r_a, VECTOR2 posb, int r_b)
{
	float xa_b = ((posa.x - posb.x)*(posa.x - posb.x));
	float ya_b = ((posa.y - posb.y)*(posa.y - posb.y));
	float ra_b = ((r_a + r_b)*(r_a + r_b));
	if (ra_b >= (xa_b + ya_b)) { return true; }
	else { return false; }
}

bool JUDGE::circle(VECTOR2 posa, int r_a, float px_b, float py_b, int r_b)
{
	float xa_b = ((posa.x - px_b)*(posa.x - px_b));
	float ya_b = ((posa.y - py_b)*(posa.y - py_b));
	float ra_b = ((r_a + r_b)*(r_a + r_b));
	if (ra_b >= (xa_b + ya_b)) { return true; }
	else { return false; }
}

bool JUDGE::circle(float px_a, float py_a, int r_a, VECTOR2 posb, int r_b)
{
	float xa_b = ((px_a - posb.x)*(px_a - posb.x));
	float ya_b = ((py_a - posb.y)*(py_a - posb.y));
	float ra_b = ((r_a + r_b)*(r_a + r_b));
	if (ra_b >= (xa_b + ya_b)) { return true; }
	else { return false; }
}

bool JUDGE::laser(int xory, float biginpos, float finpos, float judgepos, float laserwidth, VECTOR2 pos, float objwidth)
{
	switch (xory)
	{
	case 0://Xの判定
		if (biginpos > (pos.y + objwidth))return false;
		if (finpos < (pos.y - objwidth))return false;
		if (((pos.x - judgepos)*(pos.x - judgepos)) < ((laserwidth + objwidth)*(laserwidth + objwidth)))return true;
		else return false;
		break;
	case 1://Yの判定
		if (biginpos > (pos.x + objwidth))return false;
		if (finpos < (pos.x - objwidth))return false;
		if (((pos.y - judgepos)*(pos.y - judgepos)) < ((laserwidth + objwidth)*(laserwidth + objwidth)))return true;
		else return false;
		break;
	}

}

