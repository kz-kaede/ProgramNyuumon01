#include "GV.h"
#include "scene.h"

static int mImageHandle;    //�摜�n���h���i�[�p�ϐ�

//������
void Config_Initialize() {
	//mImageHandle = LoadGraph("images/Scene_Config.png");//�摜�̃��[�h
}

//�I������
void Config_Finalize() {
	clsDx();
	//DeleteGraph(mImageHandle);//�摜�̉��
}

//�X�V
void Config_Update() {
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {//Esc�L�[��������Ă�����
		SceneMgr_ChangeScene(eScene_Menu);//�V�[�������j���[�ɕύX
	}
}

//�`��
void Config_Draw() {
	//DrawGraph(0, 0, mImageHandle, FALSE);
	DrawBox(0, 0, WINDOW_SIZE_W, WINDOW_SIZE_H, GetColor(50, 100, 50), TRUE);	//�w�i��ݒ�
	DrawString(0, 0, "�ݒ��ʂł��B", GetColor(255, 255, 255));
	DrawString(0, 20, "Esc�L�[�������ƃ��j���[��ʂɖ߂�܂��B", GetColor(255, 255, 255));
	DrawString(570, 350, "�������ł�", GetColor(255, 255, 255));
}

