#pragma once

#define PI 3.1415926535897932384626433832795
#define PI2 (PI*2)
#define WINDOW_SIZE_W 1280
#define WINDOW_SIZE_H 720
//フィールドの広さ
#define FMX WINDOW_SIZE_W
#define FMY WINDOW_SIZE_H
//フィールドの左上の座標
#define FX 32
#define FY 16
//ボスの定位置
#define BOSS_POS_X (WINDOW_SIZE_W*3/4)
#define BOSS_POS_Y (WINDOW_SIZE_H/2)

//効果音の種類の最大数
#define SE_MAX 100

//敵の同時表示最大数
#define ENEMY_MAX 30
//敵の出現情報最大数
#define ENEMY_ORDER_MAX 500

//自機の当たり判定範囲
#define PRANGE 10.0
#define PRANGE11 5.0

//#define SHOT_FANCTIONS 2
//#define SHOT_QUANTITY 512

//敵１匹が持つ弾の最大数
#define ESHOT_BULLET_MAX 1000
//ボスが持つ弾の最大数
#define BOSS_BULLET_MAX 3000
//一度に画面に表示できる敵の弾幕の最大数
#define ESHOT_MAX 30
//ショットの種類の最大数
#define SHOT_KND_MAX 18
//自機ショットの登録最大数
#define PSHOT_MAX 200
//エフェクト登録最大数
#define EFFECT_MAX 100
//消滅エフェクト登録最大数
#define DEL_EFFECT_MAX 30
//弾幕最大数
#define DANMAKU_MAX 50


//ステージ数
#define STAGE_NUM 5


#include "stg_struct.h"
#include "stage_struct.h"