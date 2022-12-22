#pragma once
#include "DxLib.h"
#include "getkey.h"
#include "define.h"
#include <math.h>

//main.cppのみGLOBALを外し定義する
#ifdef GLOBAL_INSTANCE
#define GLOBAL
#else
#define GLOBAL extern 
#endif

#include "StgFunc.h"

GLOBAL int color_white;
GLOBAL int color_red;
GLOBAL int img_bullet[20][10];
GLOBAL int img_pshot[3];//自機ショット用画像(49)
GLOBAL int img_boss[8];//ボス画像
GLOBAL int img_back[20];//背景用画像



//フラグ・ステータス変数
GLOBAL int func_state, stage_count, count, stage;	//関数制御用変数
GLOBAL int se_flag[SE_MAX];			//サウンドフラグ


GLOBAL player_t p;
GLOBAL enemy_t e;
GLOBAL boss_t boss;//ボス情報
GLOBAL e_jump_t e_jump;

GLOBAL pshot_t pshot[PSHOT_MAX];//プレイヤーの弾を宣言
GLOBAL eshot_t eshot[ESHOT_MAX];//敵の弾を宣言
GLOBAL boss_shot_t boss_shot;//ボスショット情報
//GLOBAL effect_t effect[EFFECT_MAX];//エフェクト
GLOBAL bullet_info_t bullet_info[20];//弾情報
GLOBAL bright_set_t bright_set; //描画の輝度
//GLOBAL stage_title_t stage_title;//ステージタイトル


//ステージ変数
GLOBAL int camera_x;
GLOBAL color_t col;
GLOBAL block_type_t b_type;
//GLOBAL text_t Text;
GLOBAL ract_t Ract;
GLOBAL ract_t* Block;
GLOBAL e_Ani_t e_Ani;
GLOBAL text_t Text;
GLOBAL text_t** Stage;
GLOBAL char Ver[10];
GLOBAL int STAGE_TOTAL;
GLOBAL int STAGE_WIDTH;
GLOBAL int STAGE_HEIGHT;


//デバック
GLOBAL char str[3];
GLOBAL kind_t b_kind[200][23];


