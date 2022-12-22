#pragma once
#include "DxLib.h"
#include "getkey.h"
#include "define.h"
#include <math.h>

//main.cpp�̂�GLOBAL���O����`����
#ifdef GLOBAL_INSTANCE
#define GLOBAL
#else
#define GLOBAL extern 
#endif

#include "StgFunc.h"

GLOBAL int color_white;
GLOBAL int color_red;
GLOBAL int img_bullet[20][10];
GLOBAL int img_pshot[3];//���@�V���b�g�p�摜(49)
GLOBAL int img_boss[8];//�{�X�摜
GLOBAL int img_back[20];//�w�i�p�摜



//�t���O�E�X�e�[�^�X�ϐ�
GLOBAL int func_state, stage_count, count, stage;	//�֐�����p�ϐ�
GLOBAL int se_flag[SE_MAX];			//�T�E���h�t���O


GLOBAL player_t p;
GLOBAL enemy_t e;
GLOBAL boss_t boss;//�{�X���
GLOBAL e_jump_t e_jump;

GLOBAL pshot_t pshot[PSHOT_MAX];//�v���C���[�̒e��錾
GLOBAL eshot_t eshot[ESHOT_MAX];//�G�̒e��錾
GLOBAL boss_shot_t boss_shot;//�{�X�V���b�g���
//GLOBAL effect_t effect[EFFECT_MAX];//�G�t�F�N�g
GLOBAL bullet_info_t bullet_info[20];//�e���
GLOBAL bright_set_t bright_set; //�`��̋P�x
//GLOBAL stage_title_t stage_title;//�X�e�[�W�^�C�g��


//�X�e�[�W�ϐ�
GLOBAL int camera_x;
GLOBAL color_t col;
GLOBAL block_type_t b_type;
//GLOBAL text_t Text;
GLOBAL ract_t Ract;
GLOBAL ract_t* Block;
GLOBAL e_Ani_t e_Ani;
GLOBAL text_t Text;
GLOBAL text_t** Stage;
GLOBAL char Ver[10];
GLOBAL int STAGE_TOTAL;
GLOBAL int STAGE_WIDTH;
GLOBAL int STAGE_HEIGHT;


//�f�o�b�N
GLOBAL char str[3];
GLOBAL kind_t b_kind[200][23];


