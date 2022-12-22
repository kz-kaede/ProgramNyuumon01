#include "GV.h"
//#include "bossfanc.h"
#include "effects.h"

#define V0 10.0


void hit_boss() {
	if (boss.muteki_count > 0) {
		boss.muteki_count++;
	}
	if (boss.muteki_count > 100) {
		boss.muteki_count = 0;
	}
}

//渡された-ang～angまでのランダムな角度を返す
double rang(double ang) {
	return (-ang + ang * 2 * GetRand(10000) / 10000.0);
}

//物理的計算を点と距離指定で登録をする(指定時間tで定位置に戻す)
void input_phy_pos(double x, double y, int t) {//t=移動にかける時間
	double ymax_x, ymax_y;
	if (t == 0)t = 1;
	boss.phy.flag = 1;//登録オン
	boss.phy.count = 0;//カウンタ初期化
	boss.phy.set_t = t;//移動にかける時間をセット
	ymax_x = boss.x - x;//移動したい水平距離
	boss.phy.v0x = 2 * ymax_x / t;//水平成分の初速度
	boss.phy.ax = 2 * ymax_x / (t * t);//水平成分の加速度
	boss.phy.prex = boss.x;//初期x座標
	ymax_y = boss.y - y;//移動したい鉛直距離
	boss.phy.v0y = 2 * ymax_y / t;//鉛直成分の初速度
	boss.phy.ay = 2 * ymax_y / (t * t);//鉛直成分の加速度
	boss.phy.prey = boss.y;//初期y座標
}

//今いる位置からdist離れた位置にtカウントで移動する
int move_boss_pos(double x1, double y1, double x2, double y2, double dist, int t) {
	int i = 0;
	double x, y, angle;
	for (i = 0; i < 1000; i++) {
		x = boss.x, y = boss.y;//今のボスの位置をセット
		angle = rang(PI);//適当に向かう方向を決める
		x += cos(angle) * dist;//そちらに移動させる
		y += sin(angle) * dist;
		if (x1 <= x && x <= x2 && y1 <= y && y <= y2) {//その点が移動可能範囲なら
			input_phy_pos(x, y, t);
			return 0;
		}
	}
	return -1;//1000回試してダメならエラー
}




double bossatan2() {//自機と敵との成す角度
	return atan2(p.y - boss.y, p.x - boss.x);
}
double bossatan3(int k, double x, double y) {//指定座標と弾との成す角度
	return atan2(y - boss_shot.bullet[k].y, x - boss_shot.bullet[k].x);
}
//物理的計算をさせる登録をする(指定時間tで定位置に戻す)
void input_phy(int t) {//t=移動にかける時間
	double ymax_x, ymax_y;
	if (t == 0)t = 1;
	boss.phy.flag = 1;//登録オン
	boss.phy.count = 0;//カウンタ初期化
	boss.phy.set_t = t;//移動にかける時間をセット
	ymax_x = boss.x - BOSS_POS_X;//移動したい水平距離
	boss.phy.v0x = 2 * ymax_x / t;//水平成分の初速度
	boss.phy.ax = 2 * ymax_x / (t * t);//水平成分の加速度
	boss.phy.prex = boss.x;//初期x座標
	ymax_y = boss.y - BOSS_POS_Y;//移動したい鉛直距離
	boss.phy.v0y = 2 * ymax_y / t;//鉛直成分の初速度
	boss.phy.ay = 2 * ymax_y / (t * t);//鉛直成分の加速度
	boss.phy.prey = boss.y;//初期y座標
}

//物理的キャラクタ移動計算
void calc_phy() {
	double t = boss.phy.count;
	boss.x = boss.phy.prex - ((boss.phy.v0x * t) - 0.5 * boss.phy.ax * t * t);//現在いるべきx座標計算
	boss.y = boss.phy.prey - ((boss.phy.v0y * t) - 0.5 * boss.phy.ay * t * t);//現在いるべきy座標計算
	boss.phy.count++;
	if (boss.phy.count >= boss.phy.set_t)//移動にかける時間分になったら
		boss.phy.flag = 0;//オフ
}

//ボスをセット
void enter_boss(int num) {
	if (num == 0) {//中ボス開始時の時は
		//memset(e, 0, sizeof(enemy_t) * ENEMY_MAX);//雑魚敵を消す
		memset(pshot, 0, sizeof(pshot_t) * PSHOT_MAX);//弾幕を消す
		boss.x = FMX - 30;//ボスの初期座標
		boss.y = FMY/2;
		//boss.x = FMX / 2;//ボスの初期座標
		//boss.y = -30;
		if (stage_count == boss.appear_count[0])//最初なら
			boss.kind = -1;//弾幕の種類
	}
	boss.phy.flag = 1;
	boss.exists = 1;
	boss.hagoromo = 0;//扇を広げるかどうかのフラグ
	boss.endtime = 20 * 60;//残り時間
	boss.state = 1;//待機中状態に
	boss.count = 0;
	boss.graph_flag = 0;//描画フラグを戻す
	boss.kind++;
	boss.wtime = 0;//待機時間を初期化
	//memset(lazer, 0, sizeof(lazer_t) * LAZER_MAX);//レーザー情報を初期化
	input_phy(60);//60カウントかけて物理的計算で定位置に戻す
}
//ボスの待機処理
void wait_and_enter() {
	int t = 150;
	boss.wtime++;
	if (boss.wtime > t)//140カウント待機したら弾幕セット
		enter_boss_shot();
}


void calc_boss() {
	static int updown = 1;	//1なら↓　-1なら↑
	static int updown_y = 0;
	static int r = 150;
	static double angle = 0.0;
	int boss_kaiten_chuushin_x = 1000;
	int boss_kaiten_chuushin_y = updown_y;


	//敵を上下に動かす
	if (updown == 1) {
		updown_y += 1;
		if (updown_y > 680) {
			updown = -1;
		}
	}
	if (updown == -1) {
		updown_y -= 1;
		if (updown_y < 50) {
			updown = 1;
		}
	}

	//敵を円形に動かす
	angle = angle - 0.01;
	if (angle > 2 * PI) {
		angle = angle - 2 * PI;
	}
	boss.x = boss_kaiten_chuushin_x + r * cos(angle);
	boss.y = boss_kaiten_chuushin_y + r * sin(angle);

	boss.dx = boss.x;
	boss.dy = boss.y + sin(PI2 / 130 * (count % 130)) * 10;//上下運動
}


//ボスを描画
void draw_boss() {
	//int i;
	if (boss.exists == FALSE)return;
	//draw_boss_effect();
	DrawRotaGraphF((float)boss.dx + (float)camera_x, (float)boss.dy,1.0f, 0.0f, img_boss[boss.kind], TRUE);
	RedBlinkDrawRotaGraphF((float)boss.dx + (float)camera_x, (float)boss.dy, img_boss[boss.kind], boss.muteki_count, 6,FALSE);	//自機を赤点滅させる

	if (boss.hp_max == 0) { printfDx("draw_boss内0割り\n"); return; }

	/* 改追加分 */
	/*
	double subx = 0.98 * boss.hp / boss.hp_max;
	if (boss.back_knd[boss.kind] == 1)
		DrawModiGraphF(
			3, 2,
			3 + FMX * subx, 2,
			3 + FMX * subx, 8,
			3, 8,
			img_etc[7], FALSE);
	else
		DrawModiGraphF(
			3, 2,
			3 + FMX * subx, 2,
			3 + FMX * subx, 8,
			3, 8,
			img_etc[1], FALSE);

	for(i=0;i<FMX*0.98*boss.hp/boss.hp_max;i++){
		if(boss.back_knd[boss.kind]==1)
			DrawGraphFd(3+i,2,img_etc[7],FALSE);
		else
			DrawGraphFd(3+i,2,img_etc[1],FALSE);
	}
	*/
}




//void boss_move() {
//	static int updown = 1;	//1なら↓　-1なら↑
//	static int updown_y = 0;
//	static int r = 150;
//	static double angle = 0.0;
//	int enemy_kaiten_chuushin_x = 1000;
//	int enemy_kaiten_chuushin_y = updown_y;
//
//
//	//敵を上下に動かす
//	if (updown == 1) {
//		updown_y += 6;
//		if (updown_y > 680) {
//			updown = -1;
//		}
//	}
//	if (updown == -1) {
//		updown_y -= 6;
//		if (updown_y < 50) {
//			updown = 1;
//		}
//	}
//
//	//敵を円形に動かす
//	angle = angle - 0.04;
//	if (angle > 2 * PI) {
//		angle = angle - 2 * PI;
//	}
//	e.x = enemy_kaiten_chuushin_x + r * cos(angle);
//	e.y = enemy_kaiten_chuushin_y + r * sin(angle);
//}

//void draw_boss() {
//	if (e.hp == 0) return;
//
//	DrawGra((int)e.x, (int)e.y, e.img, TRUE);	//敵の描画
//	RedBlinkDrawGra((int)e.x, (int)e.y, e.img, &e.hit, e.hit_time, 110);	//敵を赤点滅させる
//}

//void collision_shot_to_player(void) {
//	if (p.hp == 0 || e.hp == 0) return;
//
//	for (int i = 0; i < SHOT_FANCTIONS; i++) {
//		for (int j = 0; j < SHOT_QUANTITY; j++) {
//			if (shot_e[i].exists[j] == TRUE) {	//その弾が存在するとき
//				//２点間の距離公式　敵の弾 to プレイヤー
//				if (15 > sqrt((p.x - shot_e[i].x[j]) * (p.x - shot_e[i].x[j]) + (p.y - shot_e[i].y[j]) * (p.y - shot_e[i].y[j]))) {
//					p.hit_time = GetNowCount();	//ヒットした時間を取得
//					if (p.hit == FALSE)	p.hp -= shot_e[i].damage;	//ヒットフラグ立っていなければプレイヤーのHPをダメージ分減らす
//					if (p.hp < 0)			p.hp = 0;	//HPがマイナスのとき、0に修正
//					shot_e[i].exists[j] = FALSE;	//当たった弾を消す
//					p.hit = TRUE;	//ヒットフラグを立てる
//				}
//			}
//		}
//	}
//}