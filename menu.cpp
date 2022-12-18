#include "GV.h"
#include "scene.h"

const static int GAME_Y = 240;    //�u�Q�[���v������y�ʒu
const static int CONFIG_Y = 270;    //�u�ݒ�v������y�ʒu
static int mImageHandle;    //�摜�n���h���i�[�p�ϐ�

typedef enum {
    eMenu_Game,        //�Q�[��
    eMenu_Config,    //�ݒ�

    eMenu_Num,        //�{���ڂ̐�
} eMenu;

static int NowSelect = eMenu_Game;    //���݂̑I�����(�����̓Q�[���I��)

//������
void Menu_Initialize() {
    SetFontSize(22);
    SetDrawBright(255, 255, 255);
    //mImageHandle = LoadGraph("images/Scene_Menu.png");    //�摜�̃��[�h
}

//�I������
void Menu_Finalize() {
    clsDx();
    //DeleteGraph(mImageHandle);    //�摜�̉��
}

//�X�V
void Menu_Update() {
    if (GetKey(KEY_INPUT_DOWN) == 1) {//���L�[��������Ă�����
        NowSelect = (NowSelect + 1) % eMenu_Num;//�I����Ԃ��������
    }
    if (GetKey(KEY_INPUT_UP) == 1) {//��L�[��������Ă�����
        NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;//�I����Ԃ���グ��
    }
    if (GetKey(KEY_INPUT_RETURN) == 1) {//�G���^�[�L�[�������ꂽ��
        switch (NowSelect) {//���ݑI�𒆂̏�Ԃɂ���ď����𕪊�
        case eMenu_Game://�Q�[���I�𒆂Ȃ�
            SceneMgr_ChangeScene(eScene_Game);//�V�[�����Q�[����ʂɕύX
            break;
        case eMenu_Config://�ݒ�I�𒆂Ȃ�
            SceneMgr_ChangeScene(eScene_Config);//�V�[����ݒ��ʂɕύX
            break;
        }
    }
    if (GetKey(KEY_INPUT_ESCAPE) == 1)exit(0);//�G�X�P�[�v��������Ă�����I��
}

//�`��
void Menu_Draw() {
    DrawBox(0, 0, WINDOW_SIZE_W, WINDOW_SIZE_H, GetColor(50, 50, 100), TRUE);	//�w�i��ݒ�
    SetFontSize(22);
    DrawString(200, 150, "���j���[��ʂł��B", GetColor(255, 255, 255));
    DrawString(200, 170, "�㉺�L�[�������A�G���^�[�������ĉ������B", GetColor(255, 255, 255));
    DrawString(280, GAME_Y, "�Q�[���X�^�[�g", GetColor(255, 255, 255));
    DrawString(280, CONFIG_Y, "�ݒ�", GetColor(255, 255, 255));
    int y = 0;
    switch (NowSelect) {//���݂̑I����Ԃɏ]���ď����𕪊�
    case eMenu_Game://�Q�[���I�𒆂Ȃ�
        y = GAME_Y;    //�Q�[���̍��W���i�[
        break;
    case eMenu_Config://�ݒ�I�𒆂Ȃ�
        y = CONFIG_Y;    //�ݒ�̍��W���i�[
        break;
    }
    DrawString(250, y, "��", GetColor(255, 255, 255));
}
