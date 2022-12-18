#include "GV.h"

void player_hp_bar() {
	int BarWidthMax = 260;
	int hp_bar;
	int hp_bar_print;
	int lines = 1;		//HPバーの本数を指定
	int y1 = 50;
	int	y2 = 60;

	hp_bar = (double)p.hp / (double)p.hp_max * ((double)BarWidthMax * (double)lines);	//HPをバーの長さに変換

	for (int i = lines; 0 < i; i--) {		//HPバーの本数からデクリメント
		if (hp_bar >= BarWidthMax * i) {		//下からi番目のHPバーが、そのバーの最大値以上なら
			hp_bar_print = BarWidthMax;
		}
		else if (hp_bar >= BarWidthMax * (i - 1)) {	//下からi番目のHPバーが、そのバーの最小値以上、最大値未満なら
			hp_bar_print = hp_bar % BarWidthMax;
		}
		else {								//下からi番目のHPバーが、そのバーの最小値未満なら
			hp_bar_print = 0;
		}
		DrawBox(10, y1, 10 + BarWidthMax, y2, GetColor(0, 0, 0), TRUE);	//HPバー背景
		DrawBox(10, y1, 10 + hp_bar_print, y2, GetColor(50, 230, 50), TRUE);	//HPバーメイン
		DrawBox(10, y1, 10 + BarWidthMax, y2, GetColor(255, 255, 255), FALSE);	//HPバー縁

		//バーの座標更新
		y1 += 15; y2 += 15;
	}
	SetFontSize(20);
	DrawString(10, 22, "Player\n", GetColor(255, 255, 255));	//プレイヤーの文字を描画
}

void boss_hp_bar() {
	int BarWidthMax = 260;
	int hp_bar;
	int hp_bar_print;
	int lines = 3;		//HPバーの本数を指定
	int y1 = 50;
	int	y2 = 60;

	hp_bar = (double)boss.hp / (double)boss.hp_max * ((double)BarWidthMax * (double)lines);	//HPをバーの長さに変換

	for (int i = lines; 0 < i; i--) {		//HPバーの本数からデクリメント
		if (hp_bar >= BarWidthMax * i) {		//下からi番目のHPバーが、そのバーの最大値以上なら
			hp_bar_print = BarWidthMax;
		}
		else if (hp_bar >= BarWidthMax * (i - 1)) {	//下からi番目のHPバーが、そのバーの最小値以上、最大値未満なら
			hp_bar_print = hp_bar % BarWidthMax;
		}
		else {								//下からi番目のHPバーが、そのバーの最小値未満なら
			hp_bar_print = 0;
		}
		DrawBox(1270 - BarWidthMax, y1, 1270, y2, GetColor(0, 0, 0), TRUE);	//HPバー背景
		DrawBox(1270 - BarWidthMax, y1, 1270 - BarWidthMax + hp_bar_print, y2, GetColor(255, 100, 100), TRUE);	//HPバーメイン
		DrawBox(1270 - BarWidthMax, y1, 1270, y2, GetColor(255, 255, 255), FALSE);	//HPバー縁
		//バーの座標更新
		y1 += 15; y2 += 15;
	}
	SetFontSize(20);
	DrawString(970, 22, "BOSS \"The Pumpkin\"\n", GetColor(255, 50, 50));	//BOSSの文字を描画
}
