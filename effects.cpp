#include "GV.h"
#include "effects.h"

//赤点滅
void RedBlinkDrawRotaGraphF(float x, float y, int GrHandle, int time, int BlinkCycle) {
	if (time == 0) return;
	if (time != 0 && time < 21) {
		if (time % BlinkCycle <= BlinkCycle / 2) {
			SetDrawBright(255, 50, 50);	//画面の色を赤する
		}
		else {
			SetDrawBright(255, 255, 255);	//画面の色を元に戻す
		}
		DrawRotaGraphF(x, y, 1.0f, 0.0f, GrHandle, TRUE);	//画像の描画
		SetDrawBright(255, 255, 255);		//画面の色をリセット
	}
}

//
//void draw_boss_effect() {
//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
//	DrawRotaGraphF(boss.dx, boss.dy,
//		(0.4 + 0.05 * sin(PI2 / 360 * (count % 360))) * 3,
//		2 * PI * (count % 580) / 580,
//		img_etc[5], TRUE);
//	DrawRotaGraphF(boss.dx, boss.dy,
//		(0.5 + 0.1 * sin(PI2 / 360 * (count % 360))) * 2,
//		2 * PI * (count % 340) / 340, img_etc[2], TRUE);
//	DrawRotaGraphF(boss.dx + 60 * sin(PI2 / 153 * (count % 153)),
//		boss.dy + 80 * sin(PI2 / 120 * (count % 120)),
//		0.4 + 0.05 * sin(PI2 / 120 * (count % 120)),
//		2 * PI * (count % 30) / 30, img_etc[6], TRUE);
//	DrawRotaGraphF(boss.dx + 60 * sin(PI2 / 200 * ((count + 20) % 200)),
//		boss.dy + 80 * sin(PI2 / 177 * ((count + 20) % 177)),
//		0.3 + 0.05 * sin(PI2 / 120 * (count % 120)),
//		2 * PI * (count % 35) / 35, img_etc[6], TRUE);
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//	DrawRotaGraphF(boss.dx + 60 * sin(PI2 / 230 * ((count + 40) % 230)),
//		boss.dy + 80 * sin(PI2 / 189 * ((count + 40) % 189)),
//		0.6 + 0.05 * sin(PI2 / 120 * (count % 120)),
//		2 * PI * (count % 40) / 40, img_etc[6], TRUE);
//}