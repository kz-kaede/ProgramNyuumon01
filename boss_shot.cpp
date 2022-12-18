#include "GV.h"
#include "bossfanc.h"
#include "effects.h"

//ボスの弾幕メイン
void boss_shot_main() {
	if ((stage_count == boss.appear_count[0] || stage_count == boss.appear_count[1])
		&& boss.exists == FALSE) {//開始時間なら
		enter_boss(0);//開始
	}
	if (boss.exists == FALSE)//ボスが登録されて無ければ戻る
		return;
	calc_boss();
	if (boss.phy.flag == 1)//物理演算移動オンなら
		calc_phy();//物理計算を
	if (boss.state == 2 && (boss.hp <= 0/* || boss.endtime <= 0*/)) {//弾幕中で体力が無くなったら
		//se_flag[1] = 1;//敵のピチュリ音
		//se_flag[11] = 1;
		//input_phy(30);//30カウントで定位置に戻す
		memset(&boss_shot, 0, sizeof(boss_shot_t));//ボスの弾幕情報を初期化
		//memset(&lazer, 0, sizeof(lazer_t) * LAZER_MAX);//ボスのレーザー情報を初期化
		//flash.flag = 0;//フラッシュを消す
		//if (boss.kind == boss.danmaku_num[0] || boss.kind == boss.danmaku_num[1]) {//出すべき弾幕をだしきったら
		if (boss.kind == boss.danmaku_num[0] || boss.kind == boss.danmaku_num[1]) {//出すべき弾幕をだしきったら
			boss.exists = 0;//消す
			boss.kind++;
		//	enter_dn(10, 40);//(45)
		//  se_flag[9] = 1;//ボスが死んだ音
			return;
		}
		else
			//stage_count++;
			enter_boss(1);//次の弾幕を登録
	}
	if (boss.state == 1) {//弾幕間の待機時間
		wait_and_enter();
	}
	if (boss.state == 2) {//弾幕中なら
		boss_shot_bullet[boss.kind]();//弾幕関数へ(関数ポインタ)
		boss_shot_calc();//弾幕計算
	}
	boss.count++;
}


//弾幕をセット
void enter_boss_shot() {
	memset(&boss_shot, 0, sizeof(boss_shot_t));//弾情報初期化
	boss_shot.isSet = TRUE;
	boss.wtime = 0;//待機時間0
	boss.state = 2;//弾幕中状態に
	boss.hp = boss.set_hp[boss.kind];//HP設定
	boss.hp_max = boss.hp;
}

//空き番号を返す
int search_boss_shot() {
	for (int i = 0; i < BOSS_BULLET_MAX; i++) {
		if (boss_shot.bullet[i].exists == FALSE)
			return i;
	}
	return -1;
}

//ボスの弾幕を計算する
void boss_shot_calc() {
	int i;
	boss.endtime--;
	//if (boss.endtime < 0)
	//	boss.hp = 0;
	for (i = 0; i < BOSS_BULLET_MAX; i++) {
		if (boss_shot.bullet[i].exists == TRUE) {
			boss_shot.bullet[i].x += cos(boss_shot.bullet[i].angle) * boss_shot.bullet[i].speed;
			boss_shot.bullet[i].y += sin(boss_shot.bullet[i].angle) * boss_shot.bullet[i].speed;
			boss_shot.bullet[i].count++;
			if (boss_shot.bullet[i].count > boss_shot.bullet[i].till) {
				if (boss_shot.bullet[i].x<-50 - camera_x || boss_shot.bullet[i].x>(double)FMX + 50 - camera_x ||
					boss_shot.bullet[i].y<-50 || boss_shot.bullet[i].y>(double)FMY + 50)
					boss_shot.bullet[i].exists = FALSE;
			}
		}
	}
	boss_shot.count++;
}

//弾丸の描画
void draw_bullet() {
	int i, j, eff;
	double disp_angle;
	SetDrawMode(DX_DRAWMODE_BILINEAR);//線形補完描画
	//for (i = 0; i < ESHOT_MAX; i++) {//敵の弾幕数分ループ
	//	if (eshot[i].flag > 0) {//弾幕データがオンなら
	//		for (j = 0; j < ESHOT_BULLET_MAX; j++) {//その弾幕が持つ弾の最大数分ループ
	//			if (eshot[i].bullet[j].exists != 0) {//弾データがオンなら
	//				if (eshot[i].bullet[j].eff == 1)
	//					SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	//				if (bullet_info[shot[i].bullet[j].kind].kaiten == 1)
	//					disp_angle = PI2 * (eshot[i].bullet[j].count % 120) / 120;
	//				else
	//					disp_angle = eshot[i].bullet[j].angle + PI / 2;
	//
	//				DrawRotaGraphF(
	//					eshot[i].bullet[j].x, eshot[i].bullet[j].y,
	//					1.0, disp_angle,
	//					img_bullet[eshot[i].bullet[j].kind][eshot[i].bullet[j].col], TRUE);
	//
	//				if (eshot[i].bullet[j].eff == 1)
	//					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//			}
	//		}
	//	}
	//}
	//boss_assist_img();
	//ボス
	if (boss_shot.isSet == TRUE) {//弾幕データがオンなら
		for (j = 0; j < BOSS_BULLET_MAX; j++) {//その弾幕が持つ弾の最大数分ループ
			if (boss_shot.bullet[j].exists == TRUE) {//弾データがオンなら
				eff = 0;
				if (boss_shot.bullet[j].kaiten == 1)
					disp_angle = PI2 * (boss_shot.bullet[j].count % 120) / 120;
				else
					disp_angle = boss_shot.bullet[j].angle + PI / 2;
				if (boss_shot.bullet[j].eff_detail == 1) {//風雨にも負けず用弾エフェクト
					SetDrawBlendMode(DX_BLENDMODE_ADD, 100 + GetRand(155)), eff = 1;
					DrawRotaGraphF(
						(float)boss_shot.bullet[j].x, (float)boss_shot.bullet[j].y,
						1.3, disp_angle,
						img_bullet[boss_shot.bullet[j].kind][boss_shot.bullet[j].col], TRUE);
				}
				if (boss_shot.bullet[j].eff == 1)
					SetDrawBlendMode(DX_BLENDMODE_ADD, 255), eff = 1;
				if (boss_shot.bullet[j].eff == 2)
					SetDrawBlendMode(DX_BLENDMODE_ADD, 255 + GetRand(100)), eff = 1;
				DrawRotaGraphF(
					(float)boss_shot.bullet[j].x + (float)camera_x, (float)boss_shot.bullet[j].y,
					1.0, disp_angle,
					img_bullet[boss_shot.bullet[j].kind][boss_shot.bullet[j].col], TRUE);
				if (eff == 1)
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}
	}
	SetDrawMode(DX_DRAWMODE_NEAREST);//描画形式を戻す
}