#include "GV.h"

//エラー処理
void LoadGraErrCheck(int GrHandle, const char* FileName) {
	if (GrHandle == -1) {
		printfDx("%sが正しく読み込まれていません！\n", FileName);
		printfDx("なにかキーを押すと終了します。\n");
		WaitKey();
		exit(0);
	}
}

//空気ブロックのとき
void Block_Ini(ract_t* b) {
	
	strcpy_s(b->kind, sizeof(b->kind), b_type.air);
	b->x = 0;
	b->y = 0;
	b->w = 0;
	b->h = 0;
	b->angle = 0;

	for (int i = 0; i < e_Ani_Total; i++) {
		b->img[i].img = 0;//写真のハンドル
		b->img[i].w = 0;//写真の幅
		b->img[i].h = 0;//写真の高さ
	}

	b->ani = e_Normal;
	b->d = FALSE;
	b->jump = 0;
	b->if_player = FALSE;
}

void game_load_stage() {


	char name[] = { "dat/stage/1-1.txt" };
	FILE* fp = NULL;
	errno_t error = fopen_s(&fp, name, "r");//ファイルを読み込む

	if (error == NULL && fp != NULL) {
		fscanf_s(fp, "%s", Ver, 10);

		//背景色取得
		fscanf_s(fp, "%d", &col.r);
		fscanf_s(fp, "%d", &col.g);
		fscanf_s(fp, "%d", &col.b);
		//SetBackgroundColor(col.r, col.g, col.b);

		//ステージの幅x高さ、幅、高さ取得
		fscanf_s(fp, "%d", &STAGE_TOTAL);
		fscanf_s(fp, "%d", &STAGE_WIDTH);
		fscanf_s(fp, "%d", &STAGE_HEIGHT);

		Stage = new text_t * [STAGE_WIDTH];
		for (int i = 0; i < STAGE_WIDTH; i++) {
			Stage[i] = new text_t[STAGE_HEIGHT];
		}

		char tmp[3];
		for (int y = 0; y < STAGE_HEIGHT; y++) {
			for (int x = 0; x < STAGE_WIDTH; x++) {
				fscanf_s(fp, "%s", tmp, 3);
				strcpy_s(b_kind[x][y].type, 3, tmp);
				Stage[x][y].x = x;
				Stage[x][y].y = y;
			}
		}
		fclose(fp);//ファイル閉じる
	}
	else {
		printfDx("%sの読み込み失敗しました\n", name);
		return;
	}
	Block = new ract_t[STAGE_TOTAL];//メモリ確保

	//Text型からRact型に変換
	int i = 0;
	for (int y = 0; y < STAGE_HEIGHT; y++) {
		for (int x = 0; x < STAGE_WIDTH; x++) {
			if (strcmp(b_kind[x][y].type, b_type.air) == 0) {
				Block_Ini(&Block[i]);//ブロック初期化
				Stage[x][y].x = 0;
				Stage[x][y].y = 0;
			}
			if (strcmp(b_kind[x][y].type, b_type.ground) == 0) {
				Block[i].img[0].img = LoadGraph("dat/img/block/ground.png");//ブロックの画像代入
				Block[i].d = FALSE;//向き
				Block[i].if_player = FALSE;//プレイヤーか否か
			}
			if (strcmp(b_kind[x][y].type, b_type.stone) == 0) {
				Block[i].img[0].img = LoadGraph("dat/img/block/stone_01.png");//ブロックの画像代入
				Block[i].d = FALSE;//向き
				Block[i].if_player = FALSE;//プレイヤーか否か
			}
			if (strcmp(b_kind[x][y].type, b_type.dirt) == 0) {
				Block[i].img[0].img = LoadGraph("dat/img/block/dirt.png");//ブロックの画像代入
				Block[i].d = FALSE;//向き
				Block[i].if_player = FALSE;//プレイヤーか否か
			}
			if (strcmp(b_kind[x][y].type, b_type.grass) == 0) {
				Block[i].img[0].img = LoadGraph("dat/img/block/grass.png");//ブロックの画像代入
				Block[i].d = FALSE;//向き
				Block[i].if_player = FALSE;//プレイヤーか否か
			}
			if (strcmp(b_kind[x][y].type, b_type.bricks) == 0) {
				Block[i].img[0].img = LoadGraph("dat/img/block/bricks.png");//ブロックの画像代入
				Block[i].d = FALSE;//向き
				Block[i].if_player = FALSE;//プレイヤーか否か
			}
			if (strcmp(b_kind[x][y].type, b_type.gold) == 0) {
				Block[i].img[0].img = LoadGraph("dat/img/block/gold.png");//ブロックの画像代入
				Block[i].d = FALSE;//向き
				Block[i].if_player = FALSE;//プレイヤーか否か
			}
			if (strcmp(b_kind[x][y].type, b_type.steps_01) == 0) {
				Block[i].img[0].img = LoadGraph("dat/img/block/step_01.png");//ブロックの画像代入
				Block[i].d = FALSE;//向き
				Block[i].if_player = FALSE;//プレイヤーか否か
			}
			if (strcmp(b_kind[x][y].type, b_type.e1) == 0) {
				Block[i].img[0].img = LoadGraph("dat/img/block/.png");//ブロックの画像代入
				Block[i].d = FALSE;//向き
				Block[i].if_player = FALSE;//プレイヤーか否か
			}
			if (strcmp(b_kind[x][y].type, b_type.player) == 0) {
				Block[i].img[e_Normal].img = LoadGraph("dat/img/block/puni_01.png");//ブロックの画像代入
				Block[i].img[e_Walk1].img = LoadGraph("dat/img/block/puni_02.png");//ブロックの画像代入
				Block[i].img[e_End].img = LoadGraph("dat/img/block/puni_04.png");//ブロックの画像代入
				Block[i].d = FALSE;//向き
				Block[i].if_player = TRUE;//プレイヤーか否か
			}
			//if (b_kind[x][y].type == b_type.) {
			//	Block[i].img[0].img = LoadGraph("dat/img/block/.png");//ブロックの画像代入
			//	Block[i].d = FALSE;//向き
			//	Block[i].if_player = FALSE;//プレイヤーか否か
			//}
			//if (b_kind[x][y].type == b_type.) {
			//	Block[i].img[0].img = LoadGraph("dat/img/block/.png");//ブロックの画像代入
			//	Block[i].d = FALSE;//向き
			//	Block[i].if_player = FALSE;//プレイヤーか否か
			//}

			//ブロック写真から高さと幅を取得
			GetGraphSize(
				Block[i].img[0].img,
				&Block[i].img[0].w,
				&Block[i].img[0].h);

			//ブロックの高さと幅を代入
			Block[i].w = Block[i].img[0].w;
			Block[i].h = Block[i].img[0].h;

			//ブロックの種類・座標・種類・回転角度・ジャンプカウンタを代入
			strcpy_s(Block[i].kind, sizeof(Block[i].kind), b_kind[x][y].type);
			Block[i].x = Stage[x][y].x * 32 + 16;
			Block[i].y = Stage[x][y].y * 32 + 16;
			Block[i].angle = 0;
			Block[i].jump = 0;
			Block[i].ani = e_Normal;

			i++;
		}
	}

	//メモリ解放(Text型 Stage)
	for (int i = 0; i < STAGE_WIDTH; i++) {
		delete[] Stage[i];
	}
	delete[] Stage;

	//初期化
	camera_x = 0;
}


//画像の読み込み
void game_load_img() {
	p.img = LoadGraph("puni.bmp");
	e.img = LoadGraph("kabocha.bmp");
	LoadDivGraph("dat/img/bullet/b0.png", 5, 5, 1, 76, 76, img_bullet[0]);
	LoadDivGraph("dat/img/bullet/b1.png", 6, 6, 1, 22, 22, img_bullet[1]);
	LoadDivGraph("dat/img/bullet/b2.png", 10, 10, 1, 5, 120, img_bullet[2]);
	LoadDivGraph("dat/img/bullet/b3.png", 5, 5, 1, 19, 34, img_bullet[3]);
	LoadDivGraph("dat/img/bullet/b4.png", 10, 10, 1, 38, 38, img_bullet[4]);
	LoadDivGraph("dat/img/bullet/b5.png", 3, 3, 1, 14, 16, img_bullet[5]);
	LoadDivGraph("dat/img/bullet/b6.png", 3, 3, 1, 14, 18, img_bullet[6]);
	LoadDivGraph("dat/img/bullet/b7.png", 10, 10, 1, 16, 16, img_bullet[7]);
	LoadDivGraph("dat/img/bullet/b8.png", 10, 10, 1, 12, 18, img_bullet[8]);
	LoadDivGraph("dat/img/bullet/b9.png", 3, 3, 1, 13, 19, img_bullet[9]);
	LoadDivGraph("dat/img/bullet/b10.png", 8, 8, 1, 8, 8, img_bullet[10]);
	LoadDivGraph("dat/img/bullet/b11.png", 8, 8, 1, 35, 32, img_bullet[11]);

	img_pshot[0] = LoadGraph("tama.png");
	img_pshot[1] = LoadGraph("tama.png");
	img_pshot[2] = LoadGraph("tama.png");
	img_boss[0] = LoadGraph("kabocha.bmp");
	img_boss[1] = LoadGraph("kabocha_angry.png");
	img_boss[2] = LoadGraph("kabocha_angry.png");
	img_boss[3] = LoadGraph("kabocha_angry.png");



	//エラーチェック
	LoadGraErrCheck(p.img, "puni.bmp");
	LoadGraErrCheck(e.img, "kabocha.bmp");
	//LoadGraErrCheck(shot_p[0].handle[0], "tama.bmp");
	//LoadGraErrCheck(shot_p[1].handle[0], "tama.bmp");
	//LoadGraErrCheck(shot_e[0].handle[0], "tekitama.bmp");
	//LoadGraErrCheck(shot_e[1].handle[0], "tekitama.bmp");
}


void game_load_sound() {


}


void game_clear_img() {
	DeleteGraph(p.img);
	DeleteGraph(e.img);

}


void game_clear_sound() {


}