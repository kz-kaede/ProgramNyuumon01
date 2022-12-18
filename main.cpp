#define GLOBAL_INSTANCE 
#include "GV.h"
#include "scene.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	int RefreshTime = 0;
	extern void set_color();

	SetGraphMode(WINDOW_SIZE_W, WINDOW_SIZE_H, 32);//�E�B���h�E�T�C�Y�̕ύX
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) return -1;//DXlib�̏�����

	SetDrawScreen(DX_SCREEN_BACK);	//�`�ʂ𗠉�ʂɕύX

	SceneMgr_Initialize();
	set_color();

	while (ScreenFlip() == 0 && ClearDrawScreen() == 0 && ProcessMessage() == 0 && UpdateKeyState() == 0) {
		RefreshTime = GetNowCount();

		SceneMgr_Update();  //�X�V
		SceneMgr_Draw();    //�`��

		while (GetNowCount() - RefreshTime < 17);//1���̏�����17�~���b�ɂȂ�܂ő҂�
		count++;
	}
	SceneMgr_Finalize();

	DxLib_End();//DXlib�I��
	return 0;
}
