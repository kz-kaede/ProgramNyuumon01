#define GLOBAL_INSTANCE 
#include "GV.h"
#include "scene.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	int RefreshTime = 0;
	extern void set_color();

	SetGraphMode(WINDOW_SIZE_W, WINDOW_SIZE_H, 32);//ウィンドウサイズの変更
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) return -1;//DXlibの初期化

	SetDrawScreen(DX_SCREEN_BACK);	//描写を裏画面に変更

	SceneMgr_Initialize();
	set_color();

	while (ScreenFlip() == 0 && ClearDrawScreen() == 0 && ProcessMessage() == 0 && UpdateKeyState() == 0) {
		RefreshTime = GetNowCount();

		SceneMgr_Update();  //更新
		SceneMgr_Draw();    //描画

		while (GetNowCount() - RefreshTime < 17);//1周の処理が17ミリ秒になるまで待つ
		count++;
	}
	SceneMgr_Finalize();

	DxLib_End();//DXlib終了
	return 0;
}
