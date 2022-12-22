#include "GV.h"
#include "effects.h"

int pshot0num[2] = { 2,4 };
int pshot0pos_x[4] = { 30,30,10,10 };
int pshot0pos_y[4] = { -10, 10, -30, 30 };

#define OPTION_X 25
#define OPTION_Y 35
int option0num[2] = { 2,4 };
double option0ang[4] = { -PI / 2,-PI / 2,-PI / 2 - PI / 4,-PI / 2 + PI / 4 };//オプションの発射角度(49)


//プレイヤーショットに関する関数
void pshot_main() {
	calc_pshot();//ショットの起動計算
	enter_shot();//ショット登録
}

//ショット登録部
void enter_shot() {
	//ショットボタンが押されていたら
	if (p.hp == 0)return;
	if (GetKey(KEY_INPUT_J) > 0) {
		p.shot_count++;
		if (p.shot_count % 3 == 0) {//3カウントに1回
			//if (GetKey(KEY_INPUT_LSHIFT) > 0)//低速移動中なら
			//	ch1_shot_pattern();
			//else
				ch0_shot_pattern();
		}
	}
	else
		p.shot_count = 0;
}

//自機ショットの登録可能番号を返す
int search_pshot() {
	for (int i = 0; i < PSHOT_MAX; i++) {
		if (pshot[i].exists == 0)
			return i;
	}
	return -1;
}

//通常ショット登録
void ch0_shot_pattern() {
	int n,k;
	//n = pshot0num[p.power < 200 ? 0 : 1];
	n = 4;
	for (int i = 0; i < n; i++) {
		if ((k = search_pshot()) != -1) {
			pshot[k].exists = TRUE;
			pshot[k].count = 0;
			pshot[k].speed = 20;
			if (p.turn == TRUE) {
				pshot[k].angle = PI;
				pshot[k].x = p.x - pshot0pos_x[i];
			}
			else {
				pshot[k].angle = 0;
				pshot[k].x = p.x + pshot0pos_x[i];
			}
			pshot[k].y = p.y + pshot0pos_y[i];
			pshot[k].damage = (n < 2 ? 20 : 12) + p.power / 100;//2筋なら20,4筋なら12(50)
			pshot[k].kind = 0;
			pshot[k].img = img_pshot[0];//画像番号代入(49)
		}
	}
}

//低速通常ショット登録
void ch1_shot_pattern() {
	int k;
	int n = pshot0num[p.power < 200 ? 0 : 1];
	for (int i = 0; i < n; i++) {
		if ((k = search_pshot()) != -1) {
			pshot[k].exists = TRUE;
			pshot[k].count = 0;
			pshot[k].angle = 0;
			pshot[k].speed = 20;
			pshot[k].x = p.x + pshot0pos_x[i] / 3;//低速中なら位置を中心側へ
			pshot[k].y = p.y + pshot0pos_y[i] / 2;
			pshot[k].damage = (n < 2 ? 20 : 12) + p.power / 100;//2筋なら20,4筋なら12(50)
			pshot[k].kind = 0;
			pshot[k].img = img_pshot[0];//画像番号代入(49)
		}
	}
}


//ショットの移動計算
void calc_pshot() {
	for (int i = 0; i < PSHOT_MAX; i++) {
		if (pshot[i].exists == TRUE) {
			int dranx = (int)(pshot[i].speed + 11 / 2), drany = (int)(pshot[i].speed + 55 / 2);
			//if (pshot[i].kind == 1)
			//	calc_homing(i);
			pshot[i].x += cos(pshot[i].angle) * pshot[i].speed;
			pshot[i].y += sin(pshot[i].angle) * pshot[i].speed;
			pshot[i].count++;
			if (pshot[i].x<-dranx - camera_x || pshot[i].x>(double)FMX + dranx - camera_x ||
				pshot[i].y<-drany || pshot[i].y>(double)FMY + drany)//画面から外れたら
				pshot[i].exists = FALSE;
		}
	}
}



//自機ショット描画
void draw_pshot() {
	for (int i = 0; i < PSHOT_MAX; i++) {
		if (pshot[i].exists == TRUE) {
			DrawRotaGraphF((float)pshot[i].x + (float)camera_x, (float)pshot[i].y, 1, pshot[i].angle + PI / 2, pshot[i].img, TRUE);
		}
	}
}



//void shot_p_single(void) {
//	if (p.hp == 0) return;
//
//	shot_p[0].velocity = 10;
//	shot_p[0].damage = 60;
//
//	if (shot_p[0].count >= SHOT_QUANTITY - 2) shot_p[0].count = 0;	//カウントが最大になったらカウントリセット
//
//	//特定のキーが押された時、弾を表示する
//	if (GetKey(KEY_INPUT_J) != 0) {	//キーボードの”J"キー
//		if (shot_p[0].exists[shot_p[0].count] == FALSE) {	//カウントが進み、次の弾が存在してない時、プレイヤー位置から新しい弾を発射
//			shot_p[0].x[shot_p[0].count] = p.x + 10; //プレイヤーの座標を弾の座標に
//			shot_p[0].y[shot_p[0].count] = p.y;
//			shot_p[0].exists[shot_p[0].count] = TRUE;	//存在
//			shot_p[0].set_time[shot_p[0].count] = GetNowCount();	//弾の生成時間を取得
//		}
//	}
//	if (GetNowCount() - shot_p[0].set_time[shot_p[0].count] > 300) {	//弾の連射間隔を調整
//		shot_p[0].count++;
//	}
//
//	//すべての弾に対して、弾が存在していたら座標更新
//	for (int j = 0; j < SHOT_QUANTITY; j++) {
//		if (shot_p[0].exists[j] == TRUE) {		//その弾存在するなら
//			shot_p[0].x[j] += shot_p[0].velocity;	//右方向に動かす
//			//弾が画面外に出たら非存在にする
//			if (shot_p[0].x[j] < 0 || shot_p[0].x[j] > WINDOW_SIZE_W || shot_p[0].y[j] < 0 || shot_p[0].y[j] > WINDOW_SIZE_H) {
//				shot_p[0].exists[j] = FALSE;
//			}
//			DrawGra((int)shot_p[0].x[j], (int)shot_p[0].y[j], shot_p[0].handle[j], TRUE); //弾の描画
//		}
//	}
//}
//
////ショットの移動計算
//void calc_pshot() {
//	for (int i = 0; i < CSHOT_MAX; i++) {
//		if (pshot[i].exists == 1) {
//			int dranx = (int)(pshot[i].speed + 11 / 2), drany = (int)(pshot[i].speed + 55 / 2);
//			if (pshot[i].kind == 1)
//				calc_homing(i);
//			pshot[i].x += cos(pshot[i].angle) * pshot[i].speed;
//			pshot[i].y += sin(pshot[i].angle) * pshot[i].speed;
//			pshot[i].count++;
//			if (pshot[i].x<-dranx || pshot[i].x>FMX + dranx ||
//				pshot[i].y<-drany || pshot[i].y>FMY + drany)//画面から外れたら
//				pshot[i].exists = 0;
//		}
//	}
//}
//
//void shot_p_triple(void) {
//	if (p.hp == 0) return;
//
//	shot_p[1].velocity = 10;
//	shot_p[1].damage = 40;
//
//	if (shot_p[1].count >= SHOT_QUANTITY - 2) shot_p[1].count = 0;	//カウントが最大になったらカウントリセット
//
//	//特定のキーが押された時、散弾を表示する
//	if (GetKey(KEY_INPUT_K) != 0) {	//キーボードの”K"キー
//		if (shot_p[1].exists[shot_p[1].count] == FALSE) {	//カウントが進み、次の弾が存在してない時、プレイヤー位置から新しい弾を発射
//			shot_p[1].x[shot_p[1].count] = p.x + 10;
//			shot_p[1].y[shot_p[1].count] = p.y;
//			shot_p[1].exists[shot_p[1].count] = 1;	//存在
//			shot_p[1].count++;
//
//			shot_p[1].x[shot_p[1].count] = p.x + 10;
//			shot_p[1].y[shot_p[1].count] = p.y;
//			shot_p[1].exists[shot_p[1].count] = 1;	//存在
//			shot_p[1].count++;
//
//			shot_p[1].x[shot_p[1].count] = p.x + 10;
//			shot_p[1].y[shot_p[1].count] = p.y;
//			shot_p[1].exists[shot_p[1].count] = TRUE;	//存在
//			shot_p[1].set_time[shot_p[1].count] = GetNowCount();	//弾の生成時間を取得
//		}
//	}
//	if (GetNowCount() - shot_p[1].set_time[shot_p[1].count] > 600) {	//弾の連射間隔を調整
//		shot_p[1].count++;
//	}
//
//	printfDx("shot_p[1].count = %d\n", shot_p[1].count);
//
//
//	//すべての弾に対して、弾が存在していたら座標更新
//	for (int j = 0; j < SHOT_QUANTITY; j++) {
//		if (shot_p[1].exists[j] == TRUE) {	//その弾が存在するなら
//			switch (j % 3) {
//			case 0:		//中央
//				shot_p[1].x[j] += shot_p[1].velocity;	//右方向に動かす
//				break;
//			case 1:		//上
//				shot_p[1].x[j] += shot_p[1].velocity;	//右上方向に動かす
//				shot_p[1].y[j] -= shot_p[1].velocity / 3;
//				break;
//			case 2:		//下
//				shot_p[1].x[j] += shot_p[1].velocity;	//右下方向に動かす
//				shot_p[1].y[j] += shot_p[1].velocity / 3;
//				break;
//			default:
//				printfDx("エラー\n");
//			}
//			//弾が画面外に出たら非存在にする
//			if (shot_p[1].x[j] < 0 || shot_p[1].x[j] > WINDOW_SIZE_W || shot_p[1].y[j] < 0 || shot_p[1].y[j] > WINDOW_SIZE_H) {
//				shot_p[1].exists[j] = FALSE;
//			}
//			DrawGra((int)shot_p[1].x[j], (int)shot_p[1].y[j], shot_p[1].handle[j], TRUE); //弾の描画
//		}
//	}
//}