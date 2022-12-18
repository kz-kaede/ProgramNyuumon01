#pragma once

typedef enum {
	eScene_Menu,	//���j���[���
	eScene_Game,	//�Q�[�����
	eScene_Config,	//�ݒ���

	eScene_None,	//����
} eScene;

extern void SceneMgr_Initialize();//������
extern void SceneMgr_Finalize();//�I������
extern void SceneMgr_Update();//�X�V
extern void SceneMgr_Draw();//�`��

// ���� nextScene �ɃV�[����ύX����
extern void SceneMgr_ChangeScene(eScene nextScene);


//Config
extern void Config_Initialize();//������
extern void Config_Finalize();//�I������
extern void Config_Update();//�X�V
extern void Config_Draw();//�`��

//Menu
extern void Menu_Initialize();//������
extern void Menu_Finalize();//�I������
extern void Menu_Update();//�X�V
extern void Menu_Draw();//�`��

//Game
extern void Game_Initialize();//������
extern void Game_Finalize();//�I������
extern void Game_Update();//�X�V
extern void Game_Main();//�`��

extern void game_load_stage();
extern void game_load_img();//�摜�̓ǂݍ���
extern void game_load_sound();//�����̓ǂݍ���
extern void game_clear_img();//�摜�̍폜
extern void game_clear_sound();//�����̍폜