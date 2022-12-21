#include "GV.h"
#include "effects.h"

void calc_player() {
	//if (p.state == 1) {//喰らいボム受付中
	//	/bright_set.brt = 80;//暗く
	//	if (p.count > 20) {//0.33秒受け付ける
	//		p.state = 2;    //1:喰らいボム受付中　2:死んで浮き上がり中
	//		p.count = 0;
	//		bright_set.brt = 255;
	//	}
	//}
	if (p.count == 0 && p.state == 1) {
		//enter_char_item();//キャラのアイテム登録(39章)
		//p.x = FMX / 2;//座標セット
		//p.y = FMY + 30;
		p.muteki_count++;//無敵状態へ
	}
	//if (p.state == 2) {//死んで浮上中なら
	//	unsigned int push = CheckStatePad(configpad.left) + CheckStatePad(configpad.right)
	//		+ CheckStatePad(configpad.up) + CheckStatePad(configpad.down);
	//	p.y -= 1.5;//キャラを上に上げる
	//	//１秒以上か、キャラがある程度上にいて、何かおされたら
	//	if (p.count > 60 || (p.y < FMY - 20 && push)) {
	//		p.count = 0;
	//		p.state = 0;//キャラステータスを元に戻す
	//	}
	//}
	if (p.muteki_count > 0) {//無敵カウント中なら
		p.muteki_count++;
		if (p.muteki_count > 60)//60以上たったら
			p.muteki_count = 0;//戻す
	}
	p.count++;//キャラクタカウントアップ
	//p.img = (p.count % 24) / 6;//現在の画像決定
}

void player_move(void) {
	if (GetKey(KEY_INPUT_D) != 0) {
		p.turn = FALSE;

		for (int i = 0; i < p.speed; i++) {
			p.x++;;
			if (p.x > WINDOW_SIZE_W / 2 &&
				p.x < STAGE_WIDTH * 32 - WINDOW_SIZE_W / 2) {
				camera_x--;
			}

			if (p.x > STAGE_WIDTH * 32 - 16 ||
				collision_block_to_player() == TRUE) {
				p.x--;
				if (p.x > WINDOW_SIZE_W / 2 &&
					p.x < STAGE_WIDTH * 32 - WINDOW_SIZE_W / 2) {
					camera_x++;
				}
				break;
			}
		}
	}
	if (GetKey(KEY_INPUT_A) != 0) {
		p.turn = TRUE;

		for (int i = 0; i < p.speed; i++) {
			p.x--;;
			if (p.x > WINDOW_SIZE_W / 2 &&
				p.x < STAGE_WIDTH * 32 - WINDOW_SIZE_W / 2) {
				camera_x++;
			}

			if (p.x < 16 ||
				collision_block_to_player() == TRUE) {
				p.x++;
				if (p.x > WINDOW_SIZE_W / 2 &&
					p.x < STAGE_WIDTH * 32 - WINDOW_SIZE_W / 2) {
					camera_x--;
				}
				break;
			}
		}
	}
	if (GetKey(KEY_INPUT_W) != 0) {
		for (int i = 0; i < p.speed; i++) {
			p.y--;
			if (p.y < 16 ||
				collision_block_to_player() == TRUE) {
				p.y++;
				break;
			}
		}
	}
	if (GetKey(KEY_INPUT_S) != 0) {
		for (int i = 0; i < p.speed; i++) {
			p.y++;
			if (p.y > STAGE_HEIGHT * 32 - 16 ||
				collision_block_to_player() == TRUE) {
				p.y--;
				break;
			}
		}
	}

	double v0y = 2.3;
	double ay = -0.1;
	static double t = 0;
	int y_add;

	if(p.jump_flug != e_grounded)t++;

	if (GetKey(KEY_INPUT_SPACE) == 1) {
		p.phy.prex = p.x;
		p.jump_count++;
		t = 0;
		p.jump_flug = e_jumping;
	}
	if (p.jump_flug == e_jumping) {
		y_add = v0y * t + ay * (t * t);

		if (y_add >= 0) {
			for (int i = 0; i < y_add; i++) {
				p.y--;
				if (collision_block_to_player() == TRUE) {
					p.jump_flug = e_falling;
					t = 0;
					p.y++;
					break;
				}
			}
		}
		else {
			p.jump_flug = e_falling;
		}
	}
	if (p.jump_flug == e_falling) {
		y_add = ay/3 * (t * t);
		for (int i = 0; i > y_add; i--) {
			p.y++;
			if (collision_block_to_player() == TRUE) {
				//p.jump_flug = e_grounded;
				t = 0;
				p.y--;
				break;
			}
		}
	}
}

//自機の描画
void draw_player(void) {
	if (p.hp == 0) return;


	if (p.turn == TRUE) {
		DrawRotaGraphF((float)p.x + camera_x, (float)p.y, 1.0f, 0.0f, p.img, TRUE, TRUE);
	}
	else {
		DrawRotaGraphF((float)p.x + camera_x, (float)p.y, 1.0f, 0.0f, p.img, TRUE, FALSE);
	}


	RedBlinkDrawRotaGraphF((float)p.x + camera_x, (float)p.y, p.img, p.muteki_count, 6);	//自機を赤点滅させる
}

//void collision_shot_to_enemy(void) {
//	if (p.hp == 0 || e.hp == 0) return;
//
//	for (int i = 0; i < SHOT_FANCTIONS; i++) {
//		for (int j = 0; j < SHOT_QUANTITY; j++) {
//			if (shot_p[i].exists[j] == TRUE) {	//その弾が存在するとき
//				//２点間の距離公式　プレイヤーの弾 to 敵
//				if (25 > sqrt((e.x - shot_p[i].x[j]) * (e.x - shot_p[i].x[j]) + (e.y - shot_p[i].y[j]) * (e.y - shot_p[i].y[j]))) {
//					e.hit_time = GetNowCount();		//ヒットした時間を取得
//					e.hp -= shot_p[i].damage;		//敵のHPをダメージ分減らす
//					if (e.hp < 0)	e.hp = 0;	//HPがマイナスのとき、0に修正
//					shot_p[i].exists[j] = 0;	//当たった弾を消す
//					e.hit = TRUE;			//ヒットフラグを立てる
//				}
//			}
//		}
//	}
//}

//void collision_player_to_enemy(void) {
//	if (p.hp == 0 || e.hp == 0) return;
//
//	//２点間の距離公式　プレイヤー to 敵
//	if (40 > sqrt((e.x - p.x) * (e.x - p.x) + (e.y - p.y) * (e.y - p.y))) {
//		p.hit_time = GetNowCount();	//ヒットした時間を取得
//		if (p.hit == FALSE) p.hp -= 300;	//ヒットフラグ立っていなければプレイヤーのHPをダメージ分減らす
//		if (p.hp < 0)		 p.hp = 0;		//HPがマイナスのとき、0に修正
//		p.hit = TRUE;	//ヒットフラグを立てる
//	}
//}
//
