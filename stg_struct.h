#pragma once

//物理的計算を行う為の構造体
typedef struct {
	int flag, count, set_t;
	double ax, v0x, ay, v0y, vx, vy, prex, prey;
}phy_t;

//プレイヤーに関する構造体
typedef struct {
	bool turn,isHit;
	int state, img, count, power, muteki_count, num, hp_max, hp, slow, shot_count, jump_count, jump_state;
	double x, y,buff_x[5],buff_y[5], speed;
	phy_t phy;
}player_t;

//敵に関する構造体
typedef struct {
	int img, hit, hit_time, hp_max, hp;
	double x, y;
}enemy_t;

//弾に関する構造体
typedef struct {
	//フラグ、種類、カウンタ、色、状態、少なくとも消さない時間、エフェクトの種類
	int exists, kind, damage, count, col, state, till, eff, kaiten, eff_detail;
	int count_till, count_stt;
	//座標、角度、速度、ベースの角度、一時記憶スピード
	double x, y, vx, vy, angle, speed, base_angle[1], rem_speed[1];
	int c_flag;
	double cx, cy;
}bullet_t;

//弾の情報
typedef struct {
	int size_x, size_y, col_num, kaiten;
	double range;
}bullet_info_t;

//敵のショットに関する構造体
typedef struct {
	//フラグ、種類、カウンタ、どの敵から発射されたかの番号、色
	int isSet, kind, cnt, num;
	//ベース角度、ベーススピード
	double base_angle[1], base_spd[1];
	bullet_t bullet[ESHOT_BULLET_MAX];
}eshot_t;

//ボスショットに関する構造体
typedef struct {
	//フラグ、種類、カウンタ、どの敵から発射されたかの番号、色
	int isSet, kind, count, num;
	//ベース角度、ベーススピード
	double base_angle[10], base_spd[1];
	bullet_t bullet[BOSS_BULLET_MAX];
	bullet_t assist[6];
}boss_shot_t;

//プレイヤーショット関する構造体
typedef struct {
	int exists, damage, count, kind, img;
	double x, y, angle, speed;
}pshot_t;


//ボスの情報
typedef struct {
	//フラグ、カウンタ、種類、待機時間、状態、弾幕終了までのカウンタ、後ろの羽衣、表示フラグ
	int state,exists, count, kind, wtime, endtime, hagoromo, graph_flag, muteki_count;
	//HP,最大HP
	int hp, hp_max;
	//出現カウンタ数、各弾幕のHP、背景の種類、中ボス-ラスボスの弾幕数(45)
	int appear_count[2], set_hp[DANMAKU_MAX], back_knd[DANMAKU_MAX], danmaku_num[2];
	//座標
	double x, y, dx, dy, angle, speed;
	//物理移動のための変数
	phy_t phy;
}boss_t;

//画面の明るさ情報
typedef struct {
	unsigned char brt;
}bright_set_t;

//ゲームステージタイトル
typedef struct {
	//フラグ、画像ハンドル、カウンタ、輝度、出現カウント
	int flag, img, cnt, brt, appear_cnt;
}stage_title_t;

//BGM情報(area_tで使用
typedef struct {
	//BGMの再生フラグ、再生ハンドル、いつならすか再生種類番号をいれる、ループ位置
	int flag, handle, knd[2], loop_pos[2];
}bgm_t;


typedef enum {
	e_grounded,
	e_jumping,
	e_falling,
}e_jump_t;

////弾のパラメータ
//typedef struct {
//	int handle[SHOT_QUANTITY];
//	int exists[SHOT_QUANTITY];	//存在するかどうか
//	double x[SHOT_QUANTITY];
//	double y[SHOT_QUANTITY];
//	double velocity;
//	double vx[SHOT_QUANTITY];
//	double vy[SHOT_QUANTITY];
//	int damage;
//	int set_time[SHOT_QUANTITY];
//	int count;
//} shot_t;
