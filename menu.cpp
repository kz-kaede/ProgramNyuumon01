#include "GV.h"
#include "scene.h"

const static int GAME_Y = 240;    //「ゲーム」文字のy位置
const static int CONFIG_Y = 270;    //「設定」文字のy位置
static int mImageHandle;    //画像ハンドル格納用変数

typedef enum {
    eMenu_Game,        //ゲーム
    eMenu_Config,    //設定

    eMenu_Num,        //本項目の数
} eMenu;

static int NowSelect = eMenu_Game;    //現在の選択状態(初期はゲーム選択中)

//初期化
void Menu_Initialize() {
    SetFontSize(22);
    SetDrawBright(255, 255, 255);
    //mImageHandle = LoadGraph("images/Scene_Menu.png");    //画像のロード
}

//終了処理
void Menu_Finalize() {
    clsDx();
    //DeleteGraph(mImageHandle);    //画像の解放
}

//更新
void Menu_Update() {
    if (GetKey(KEY_INPUT_DOWN) == 1) {//下キーが押されていたら
        NowSelect = (NowSelect + 1) % eMenu_Num;//選択状態を一つ下げる
    }
    if (GetKey(KEY_INPUT_UP) == 1) {//上キーが押されていたら
        NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;//選択状態を一つ上げる
    }
    if (GetKey(KEY_INPUT_RETURN) == 1) {//エンターキーが押されたら
        switch (NowSelect) {//現在選択中の状態によって処理を分岐
        case eMenu_Game://ゲーム選択中なら
            SceneMgr_ChangeScene(eScene_Game);//シーンをゲーム画面に変更
            break;
        case eMenu_Config://設定選択中なら
            SceneMgr_ChangeScene(eScene_Config);//シーンを設定画面に変更
            break;
        }
    }
    if (GetKey(KEY_INPUT_ESCAPE) == 1)exit(0);//エスケープが押されていたら終了
}

//描画
void Menu_Draw() {
    DrawBox(0, 0, WINDOW_SIZE_W, WINDOW_SIZE_H, GetColor(50, 50, 100), TRUE);	//背景を設定
    SetFontSize(22);
    DrawString(200, 150, "メニュー画面です。", GetColor(255, 255, 255));
    DrawString(200, 170, "上下キーを押し、エンターを押して下さい。", GetColor(255, 255, 255));
    DrawString(280, GAME_Y, "ゲームスタート", GetColor(255, 255, 255));
    DrawString(280, CONFIG_Y, "設定", GetColor(255, 255, 255));
    int y = 0;
    switch (NowSelect) {//現在の選択状態に従って処理を分岐
    case eMenu_Game://ゲーム選択中なら
        y = GAME_Y;    //ゲームの座標を格納
        break;
    case eMenu_Config://設定選択中なら
        y = CONFIG_Y;    //設定の座標を格納
        break;
    }
    DrawString(250, y, "■", GetColor(255, 255, 255));
}
