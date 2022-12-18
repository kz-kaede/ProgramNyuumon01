#pragma once

// 各キャラの中心を基準に描画するための補正関数。
void DrawGra(int x, int y, int GrHandle, int TransFlag);

//画像を赤点滅させる
void RedBlinkDrawRotaGraphF(float x, float y, int GrHandle, int time, int BlinkCycle);

//ボスの表示エフェクト
void draw_boss_effect();