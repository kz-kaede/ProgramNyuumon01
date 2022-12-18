#include "GV.h"
#include "scene.h"

static int mImageHandle;    //画像ハンドル格納用変数

//初期化
void Config_Initialize() {
	//mImageHandle = LoadGraph("images/Scene_Config.png");//画像のロード
}

//終了処理
void Config_Finalize() {
	clsDx();
	//DeleteGraph(mImageHandle);//画像の解放
}

//更新
void Config_Update() {
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {//Escキーが押されていたら
		SceneMgr_ChangeScene(eScene_Menu);//シーンをメニューに変更
	}
}

//描画
void Config_Draw() {
	//DrawGraph(0, 0, mImageHandle, FALSE);
	DrawBox(0, 0, WINDOW_SIZE_W, WINDOW_SIZE_H, GetColor(50, 100, 50), TRUE);	//背景を設定
	DrawString(0, 0, "設定画面です。", GetColor(255, 255, 255));
	DrawString(0, 20, "Escキーを押すとメニュー画面に戻ります。", GetColor(255, 255, 255));
	DrawString(570, 350, "未完成です", GetColor(255, 255, 255));
}

