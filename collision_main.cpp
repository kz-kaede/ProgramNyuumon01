#include "GV.h"

#define ENEMY_RANGE_MAX 4
#define PSHOT_RANGE_MAX 2
#define BRANGE 40.0//ボスの当たり範囲

//敵の当たり判定範囲
int enemy_range[ENEMY_RANGE_MAX] = { 16,30,16,50 };
//自機ショットの当たり判定範囲
int pshot_range[PSHOT_RANGE_MAX] = { 6, };

void collision_main() {
	collision_pshot_to_enemy();//自機ショットと敵との処理
	collision_enemyshot_to_player();//敵ショットと自機との処理
	collision_enemy_to_player();
	collision_block_to_player();
	//ch_and_item();//アイテム接触処理
}

//当たり判定
//当たりを判定する物体:1  当たりを判定する物体:2
int collision_judge(double x1, double y1, double x2, double y2,
	double range1, double range2, double spd1, double angle1) {
	int j;
	double x = x1 - x2;
	double y = y1 - y2;
	//当たり判定の合計範囲
	double r = range1 + range2;
	//中間を計算する必要があれば
	if (spd1 > r) {
		//１フレーム前にいた位置を格納する
		double pre_x = x1 + cos(angle1 + PI) * spd1;
		double pre_y = y1 + sin(angle1 + PI) * spd1;
		double px, py;
		for (j = 0; j < spd1 / r; j++) {//進んだ分÷当たり判定分ループ
			px = pre_x - x2;
			py = pre_y - y2;
			if (px * px + py * py < r * r)
				return 1;
			pre_x += cos(angle1) * r;
			pre_y += sin(angle1) * r;
		}
	}
	if (x * x + y * y < r * r)//当たり判定内なら
		return 1;//当たり
	return 0;
}

//自機ショットと敵との処理
void collision_pshot_to_enemy() {
	int i, s;
	for (i = 0; i < PSHOT_MAX; i++) {//自機ショット総数
		if (pshot[i].exists == TRUE) {
			//for (s = 0; s < ENEMY_MAX; s++) {//敵総数
			//	if (enemy[s].flag > 0) {
			//		if (out_judge_pshot(i, s)) {//自機ショットと敵が当たっていれば
			//			pshot[i].exists = FALSE;//その自機ショットを消す
			//			hit_enemy(s, pshot[i].damage);
			//			break;
			//		}
			//	}
			//}

			//ボスが出現していて、描画しないフラグがオフで、ショット中なら
			if (boss.exists == TRUE && boss.graph_flag == 0 && boss.state == 2) {
				if (collision_pshot_to_boss(i)) {
					pshot[i].exists = FALSE;
					hit_boss(pshot[i].damage);
					boss.muteki_count = 1;
				}
			}
		}
	}
}

//自機ショットがボスに当たったかどうかを判定する
int collision_pshot_to_boss(int i) {
	if (pshot[i].count > 0) {//ショットの軌道が１度でも計算されていたら
		if (collision_judge(pshot[i].x, pshot[i].y, boss.x, boss.y,
			pshot_range[pshot[i].kind], BRANGE, pshot[i].speed, pshot[i].angle)) {
			return 1;
		}
	}
	return 0;
}

//敵ショットが自機に当たったかどうかを判定する
int collision_enemyshot_to_player(int s, int n) {
	if (eshot[s].bullet[n].count > 0) {//ショットの軌道が１度でも計算されていたら
		if (collision_judge(
			eshot[s].bullet[n].x, eshot[s].bullet[n].y, p.x, p.y,
			bullet_info[eshot[s].bullet[n].kind].range, PRANGE,
			eshot[s].bullet[n].speed, eshot[s].bullet[n].angle
		)) {
			return 1;
		}
	}
	return 0;
}

//ボスショットが自機に当たったかどうかを判定する
int collision_bossshot_to_player(int n) {
	if (boss_shot.bullet[n].count > 0) {//ショットの軌道が１度でも計算されていたら
		if (collision_judge(
			boss_shot.bullet[n].x, boss_shot.bullet[n].y, p.x, p.y,
			bullet_info[boss_shot.bullet[n].kind].range, PRANGE,
			boss_shot.bullet[n].speed, boss_shot.bullet[n].angle
		)) {
			return TRUE;
		}
	}
	return 0;
}

//敵ショットと自機との処理
void collision_enemyshot_to_player() {
	if (boss.kind == boss.danmaku_num[0] + 1)return;

	int s, n;
	//if (p.state == 0 && p.muteki_count == 0 && out_lazer() == 1) {
	//	p.count = 0;
	//	p.state = 1;
	//	se_flag[3] = 1;
	//}
	////雑魚敵のショット
	//for (s = 0; s < ESHOT_MAX; s++) {//敵ショット総数
	//	if (eshot[s].isSet == TRUE) {//そのショットが登録されていたら
	//		for (n = 0; n < ESHOT_BULLET_MAX; n++) {//弾総数
	//			if (eshot[s].bullet[n].exists == TRUE) {//弾が登録されていたら
	//				if (bom.flag != 0) {
	//					eshot[s].bullet[n].flag = 0;
	//					continue;
	//				}
	//				if (collision_enemyshot_to_player(s, n) == 1) {//自機にその弾が接触していたら
	//					eshot[s].bullet[n].flag = 0;//弾をオフ
	//					if (p.state == 0 && p.muteki_count == 0) {
	//						p.count = 0;
	//						p.state = 1;
	//						se_flag[3] = 1;
	//					}
	//				}
	//			}
	//		}
	//	}
	//}
	//ボスのショット
	if (boss_shot.isSet == TRUE) {//そのショットが登録されていたら
		for (n = 0; n < BOSS_BULLET_MAX; n++) {//弾総数
			if (boss_shot.bullet[n].exists == TRUE) {//弾が登録されていたら
				//if (bom.flag != 0) {
				//	boss_shot.bullet[n].flag = 0;
				//	continue;
				//}
				if (collision_bossshot_to_player(n) == TRUE) {//自機にその弾が接触していたら
					boss_shot.bullet[n].exists = FALSE;//弾を消す
					if (/*p.state == 0 && */p.muteki_count == 0) {
						hit_player(boss_shot.bullet[n].damage);
						p.count = 0;
						p.state = 1;
						se_flag[3] = 1;
					}
				}
			}
		}
	}
}


void collision_enemy_to_player() {
	if (boss.kind == boss.danmaku_num[0] + 1)return;

	//ボスとプレイヤーが接触していたら
	if (collision_judge(boss.x, boss.y, p.x, p.y, BRANGE, PRANGE, NULL, NULL)) {
		if (p.muteki_count == 0)hit_player(10);//無敵状態でなければダメージ分減らす
		p.count = 0;
		p.state = 1;
		se_flag[3] = 1;
	}
}

//sの敵に弾のダメージ食らわす
//void hit_enemy(int s, int damage) {
//	enemy[s].hp -= damage;//弾の持つパワー分HPを減らす
//	enemy_death_judge(s);//敵が死ぬかどうかを決める
//}

//ボスにダメージを食らわす
void hit_boss(int damage) {
	boss.hp -= damage;//弾の持つパワー分HPを減らす
	if (boss.hp < 0)boss.hp = 0;
}

//プレイヤーにダメージを食らわす
void hit_player(int damage) {
	p.hp -= damage;//弾の持つパワー分HPを減らす
	if (p.hp < 0)p.hp = 0;
}

//プレイヤーとブロックの接触判定
int collision_block_to_player() {
	for (int i = 0; i < STAGE_TOTAL; i++) {
		if (strcmp(Block[i].kind, b_type.steps_01) != 0) {//足場ブロック以外のとき
			if (Block[i].x - Block[i].w < p.x && p.x < Block[i].x + Block[i].w &&
				Block[i].y - Block[i].h < p.y && p.y < Block[i].y + Block[i].h) {
				return TRUE;
			}
		}
		else if ((p.jump_state == e_falling || p.jump_state == e_grounded) &&
			GetKey(KEY_INPUT_S) == 0) {//足場ブロックのとき
			if (Block[i].x - Block[i].w < p.x && p.x < Block[i].x + Block[i].w &&
				Block[i].y - Block[i].h < p.y && p.y < Block[i].y - Block[i].h + 5) {
				p.y = Block[i].y - Block[i].h + 1;//範囲内ならプレイヤーのy座標を足場ブロック上面のy座標に強制変更
				return TRUE;
			}
		}
	}
	return FALSE;
}