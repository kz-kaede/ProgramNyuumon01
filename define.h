#pragma once

#define PI 3.1415926535897932384626433832795
#define PI2 (PI*2)
#define WINDOW_SIZE_W 1280
#define WINDOW_SIZE_H 720
//�t�B�[���h�̍L��
#define FMX WINDOW_SIZE_W
#define FMY WINDOW_SIZE_H
//�t�B�[���h�̍���̍��W
#define FX 32
#define FY 16
//�{�X�̒�ʒu
#define BOSS_POS_X (WINDOW_SIZE_W*3/4)
#define BOSS_POS_Y (WINDOW_SIZE_H/2)

//���ʉ��̎�ނ̍ő吔
#define SE_MAX 100

//�G�̓����\���ő吔
#define ENEMY_MAX 30
//�G�̏o�����ő吔
#define ENEMY_ORDER_MAX 500

//���@�̓����蔻��͈�
#define PRANGE 10.0
#define PRANGE11 5.0

//#define SHOT_FANCTIONS 2
//#define SHOT_QUANTITY 512

//�G�P�C�����e�̍ő吔
#define ESHOT_BULLET_MAX 1000
//�{�X�����e�̍ő吔
#define BOSS_BULLET_MAX 3000
//��x�ɉ�ʂɕ\���ł���G�̒e���̍ő吔
#define ESHOT_MAX 30
//�V���b�g�̎�ނ̍ő吔
#define SHOT_KND_MAX 18
//���@�V���b�g�̓o�^�ő吔
#define PSHOT_MAX 200
//�G�t�F�N�g�o�^�ő吔
#define EFFECT_MAX 100
//���ŃG�t�F�N�g�o�^�ő吔
#define DEL_EFFECT_MAX 30
//�e���ő吔
#define DANMAKU_MAX 50


//�X�e�[�W��
#define STAGE_NUM 5


#include "stg_struct.h"
#include "stage_struct.h"