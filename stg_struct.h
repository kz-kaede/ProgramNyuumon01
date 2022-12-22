#pragma once

//�����I�v�Z���s���ׂ̍\����
typedef struct {
	int flag, count, set_t;
	double ax, v0x, ay, v0y, vx, vy, prex, prey;
}phy_t;

//�v���C���[�Ɋւ���\����
typedef struct {
	bool turn,isHit;
	int state, img, count, power, muteki_count, num, hp_max, hp, slow, shot_count, jump_count, jump_state;
	double x, y,buff_x[5],buff_y[5], speed;
	phy_t phy;
}player_t;

//�G�Ɋւ���\����
typedef struct {
	int img, hit, hit_time, hp_max, hp;
	double x, y;
}enemy_t;

//�e�Ɋւ���\����
typedef struct {
	//�t���O�A��ށA�J�E���^�A�F�A��ԁA���Ȃ��Ƃ������Ȃ����ԁA�G�t�F�N�g�̎��
	int exists, kind, damage, count, col, state, till, eff, kaiten, eff_detail;
	int count_till, count_stt;
	//���W�A�p�x�A���x�A�x�[�X�̊p�x�A�ꎞ�L���X�s�[�h
	double x, y, vx, vy, angle, speed, base_angle[1], rem_speed[1];
	int c_flag;
	double cx, cy;
}bullet_t;

//�e�̏��
typedef struct {
	int size_x, size_y, col_num, kaiten;
	double range;
}bullet_info_t;

//�G�̃V���b�g�Ɋւ���\����
typedef struct {
	//�t���O�A��ށA�J�E���^�A�ǂ̓G���甭�˂��ꂽ���̔ԍ��A�F
	int isSet, kind, cnt, num;
	//�x�[�X�p�x�A�x�[�X�X�s�[�h
	double base_angle[1], base_spd[1];
	bullet_t bullet[ESHOT_BULLET_MAX];
}eshot_t;

//�{�X�V���b�g�Ɋւ���\����
typedef struct {
	//�t���O�A��ށA�J�E���^�A�ǂ̓G���甭�˂��ꂽ���̔ԍ��A�F
	int isSet, kind, count, num;
	//�x�[�X�p�x�A�x�[�X�X�s�[�h
	double base_angle[10], base_spd[1];
	bullet_t bullet[BOSS_BULLET_MAX];
	bullet_t assist[6];
}boss_shot_t;

//�v���C���[�V���b�g�ւ���\����
typedef struct {
	int exists, damage, count, kind, img;
	double x, y, angle, speed;
}pshot_t;


//�{�X�̏��
typedef struct {
	//�t���O�A�J�E���^�A��ށA�ҋ@���ԁA��ԁA�e���I���܂ł̃J�E���^�A���̉H�߁A�\���t���O
	int state,exists, count, kind, wtime, endtime, hagoromo, graph_flag, muteki_count;
	//HP,�ő�HP
	int hp, hp_max;
	//�o���J�E���^���A�e�e����HP�A�w�i�̎�ށA���{�X-���X�{�X�̒e����(45)
	int appear_count[2], set_hp[DANMAKU_MAX], back_knd[DANMAKU_MAX], danmaku_num[2];
	//���W
	double x, y, dx, dy, angle, speed;
	//�����ړ��̂��߂̕ϐ�
	phy_t phy;
}boss_t;

//��ʂ̖��邳���
typedef struct {
	unsigned char brt;
}bright_set_t;

//�Q�[���X�e�[�W�^�C�g��
typedef struct {
	//�t���O�A�摜�n���h���A�J�E���^�A�P�x�A�o���J�E���g
	int flag, img, cnt, brt, appear_cnt;
}stage_title_t;

//BGM���(area_t�Ŏg�p
typedef struct {
	//BGM�̍Đ��t���O�A�Đ��n���h���A���Ȃ炷���Đ���ޔԍ��������A���[�v�ʒu
	int flag, handle, knd[2], loop_pos[2];
}bgm_t;


typedef enum {
	e_grounded,
	e_jumping,
	e_falling,
}e_jump_t;

////�e�̃p�����[�^
//typedef struct {
//	int handle[SHOT_QUANTITY];
//	int exists[SHOT_QUANTITY];	//���݂��邩�ǂ���
//	double x[SHOT_QUANTITY];
//	double y[SHOT_QUANTITY];
//	double velocity;
//	double vx[SHOT_QUANTITY];
//	double vy[SHOT_QUANTITY];
//	int damage;
//	int set_time[SHOT_QUANTITY];
//	int count;
//} shot_t;
