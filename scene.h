#pragma once

typedef enum {
	eScene_Menu,	//メニュー画面
	eScene_Game,	//ゲーム画面
	eScene_Config,	//設定画面

	eScene_None,	//無し
} eScene;

extern void SceneMgr_Initialize();//初期化
extern void SceneMgr_Finalize();//終了処理
extern void SceneMgr_Update();//更新
extern void SceneMgr_Draw();//描画

// 引数 nextScene にシーンを変更する
extern void SceneMgr_ChangeScene(eScene nextScene);


//Config
extern void Config_Initialize();//初期化
extern void Config_Finalize();//終了処理
extern void Config_Update();//更新
extern void Config_Draw();//描画

//Menu
extern void Menu_Initialize();//初期化
extern void Menu_Finalize();//終了処理
extern void Menu_Update();//更新
extern void Menu_Draw();//描画

//Game
extern void Game_Initialize();//初期化
extern void Game_Finalize();//終了処理
extern void Game_Update();//更新
extern void Game_Main();//描画

extern void game_load_stage();
extern void game_load_img();//画像の読み込み
extern void game_load_sound();//音源の読み込み
extern void game_clear_img();//画像の削除
extern void game_clear_sound();//音源の削除