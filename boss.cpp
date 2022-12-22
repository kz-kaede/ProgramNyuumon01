#include "GV.h"
//#include "bossfanc.h"
#include "effects.h"

#define V0 10.0


void hit_boss() {
	if (boss.muteki_count > 0) {
		boss.muteki_count++;
	}
	if (boss.muteki_count > 100) {
		boss.muteki_count = 0;
	}
}

//�n���ꂽ-ang�`ang�܂ł̃����_���Ȋp�x��Ԃ�
double rang(double ang) {
	return (-ang + ang * 2 * GetRand(10000) / 10000.0);
}

//�����I�v�Z��_�Ƌ����w��œo�^������(�w�莞��t�Œ�ʒu�ɖ߂�)
void input_phy_pos(double x, double y, int t) {//t=�ړ��ɂ����鎞��
	double ymax_x, ymax_y;
	if (t == 0)t = 1;
	boss.phy.flag = 1;//�o�^�I��
	boss.phy.count = 0;//�J�E���^������
	boss.phy.set_t = t;//�ړ��ɂ����鎞�Ԃ��Z�b�g
	ymax_x = boss.x - x;//�ړ���������������
	boss.phy.v0x = 2 * ymax_x / t;//���������̏����x
	boss.phy.ax = 2 * ymax_x / (t * t);//���������̉����x
	boss.phy.prex = boss.x;//����x���W
	ymax_y = boss.y - y;//�ړ���������������
	boss.phy.v0y = 2 * ymax_y / t;//���������̏����x
	boss.phy.ay = 2 * ymax_y / (t * t);//���������̉����x
	boss.phy.prey = boss.y;//����y���W
}

//������ʒu����dist���ꂽ�ʒu��t�J�E���g�ňړ�����
int move_boss_pos(double x1, double y1, double x2, double y2, double dist, int t) {
	int i = 0;
	double x, y, angle;
	for (i = 0; i < 1000; i++) {
		x = boss.x, y = boss.y;//���̃{�X�̈ʒu���Z�b�g
		angle = rang(PI);//�K���Ɍ��������������߂�
		x += cos(angle) * dist;//������Ɉړ�������
		y += sin(angle) * dist;
		if (x1 <= x && x <= x2 && y1 <= y && y <= y2) {//���̓_���ړ��\�͈͂Ȃ�
			input_phy_pos(x, y, t);
			return 0;
		}
	}
	return -1;//1000�񎎂��ă_���Ȃ�G���[
}




double bossatan2() {//���@�ƓG�Ƃ̐����p�x
	return atan2(p.y - boss.y, p.x - boss.x);
}
double bossatan3(int k, double x, double y) {//�w����W�ƒe�Ƃ̐����p�x
	return atan2(y - boss_shot.bullet[k].y, x - boss_shot.bullet[k].x);
}
//�����I�v�Z��������o�^������(�w�莞��t�Œ�ʒu�ɖ߂�)
void input_phy(int t) {//t=�ړ��ɂ����鎞��
	double ymax_x, ymax_y;
	if (t == 0)t = 1;
	boss.phy.flag = 1;//�o�^�I��
	boss.phy.count = 0;//�J�E���^������
	boss.phy.set_t = t;//�ړ��ɂ����鎞�Ԃ��Z�b�g
	ymax_x = boss.x - BOSS_POS_X;//�ړ���������������
	boss.phy.v0x = 2 * ymax_x / t;//���������̏����x
	boss.phy.ax = 2 * ymax_x / (t * t);//���������̉����x
	boss.phy.prex = boss.x;//����x���W
	ymax_y = boss.y - BOSS_POS_Y;//�ړ���������������
	boss.phy.v0y = 2 * ymax_y / t;//���������̏����x
	boss.phy.ay = 2 * ymax_y / (t * t);//���������̉����x
	boss.phy.prey = boss.y;//����y���W
}

//�����I�L�����N�^�ړ��v�Z
void calc_phy() {
	double t = boss.phy.count;
	boss.x = boss.phy.prex - ((boss.phy.v0x * t) - 0.5 * boss.phy.ax * t * t);//���݂���ׂ�x���W�v�Z
	boss.y = boss.phy.prey - ((boss.phy.v0y * t) - 0.5 * boss.phy.ay * t * t);//���݂���ׂ�y���W�v�Z
	boss.phy.count++;
	if (boss.phy.count >= boss.phy.set_t)//�ړ��ɂ����鎞�ԕ��ɂȂ�����
		boss.phy.flag = 0;//�I�t
}

//�{�X���Z�b�g
void enter_boss(int num) {
	if (num == 0) {//���{�X�J�n���̎���
		//memset(e, 0, sizeof(enemy_t) * ENEMY_MAX);//�G���G������
		memset(pshot, 0, sizeof(pshot_t) * PSHOT_MAX);//�e��������
		boss.x = FMX - 30;//�{�X�̏������W
		boss.y = FMY/2;
		//boss.x = FMX / 2;//�{�X�̏������W
		//boss.y = -30;
		if (stage_count == boss.appear_count[0])//�ŏ��Ȃ�
			boss.kind = -1;//�e���̎��
	}
	boss.phy.flag = 1;
	boss.exists = 1;
	boss.hagoromo = 0;//����L���邩�ǂ����̃t���O
	boss.endtime = 20 * 60;//�c�莞��
	boss.state = 1;//�ҋ@����Ԃ�
	boss.count = 0;
	boss.graph_flag = 0;//�`��t���O��߂�
	boss.kind++;
	boss.wtime = 0;//�ҋ@���Ԃ�������
	//memset(lazer, 0, sizeof(lazer_t) * LAZER_MAX);//���[�U�[����������
	input_phy(60);//60�J�E���g�����ĕ����I�v�Z�Œ�ʒu�ɖ߂�
}
//�{�X�̑ҋ@����
void wait_and_enter() {
	int t = 150;
	boss.wtime++;
	if (boss.wtime > t)//140�J�E���g�ҋ@������e���Z�b�g
		enter_boss_shot();
}


void calc_boss() {
	static int updown = 1;	//1�Ȃ火�@-1�Ȃ灪
	static int updown_y = 0;
	static int r = 150;
	static double angle = 0.0;
	int boss_kaiten_chuushin_x = 1000;
	int boss_kaiten_chuushin_y = updown_y;


	//�G���㉺�ɓ�����
	if (updown == 1) {
		updown_y += 1;
		if (updown_y > 680) {
			updown = -1;
		}
	}
	if (updown == -1) {
		updown_y -= 1;
		if (updown_y < 50) {
			updown = 1;
		}
	}

	//�G���~�`�ɓ�����
	angle = angle - 0.01;
	if (angle > 2 * PI) {
		angle = angle - 2 * PI;
	}
	boss.x = boss_kaiten_chuushin_x + r * cos(angle);
	boss.y = boss_kaiten_chuushin_y + r * sin(angle);

	boss.dx = boss.x;
	boss.dy = boss.y + sin(PI2 / 130 * (count % 130)) * 10;//�㉺�^��
}


//�{�X��`��
void draw_boss() {
	//int i;
	if (boss.exists == FALSE)return;
	//draw_boss_effect();
	DrawRotaGraphF((float)boss.dx + (float)camera_x, (float)boss.dy,1.0f, 0.0f, img_boss[boss.kind], TRUE);
	RedBlinkDrawRotaGraphF((float)boss.dx + (float)camera_x, (float)boss.dy, img_boss[boss.kind], boss.muteki_count, 6,FALSE);	//���@��ԓ_�ł�����

	if (boss.hp_max == 0) { printfDx("draw_boss��0����\n"); return; }

	/* ���ǉ��� */
	/*
	double subx = 0.98 * boss.hp / boss.hp_max;
	if (boss.back_knd[boss.kind] == 1)
		DrawModiGraphF(
			3, 2,
			3 + FMX * subx, 2,
			3 + FMX * subx, 8,
			3, 8,
			img_etc[7], FALSE);
	else
		DrawModiGraphF(
			3, 2,
			3 + FMX * subx, 2,
			3 + FMX * subx, 8,
			3, 8,
			img_etc[1], FALSE);

	for(i=0;i<FMX*0.98*boss.hp/boss.hp_max;i++){
		if(boss.back_knd[boss.kind]==1)
			DrawGraphFd(3+i,2,img_etc[7],FALSE);
		else
			DrawGraphFd(3+i,2,img_etc[1],FALSE);
	}
	*/
}




//void boss_move() {
//	static int updown = 1;	//1�Ȃ火�@-1�Ȃ灪
//	static int updown_y = 0;
//	static int r = 150;
//	static double angle = 0.0;
//	int enemy_kaiten_chuushin_x = 1000;
//	int enemy_kaiten_chuushin_y = updown_y;
//
//
//	//�G���㉺�ɓ�����
//	if (updown == 1) {
//		updown_y += 6;
//		if (updown_y > 680) {
//			updown = -1;
//		}
//	}
//	if (updown == -1) {
//		updown_y -= 6;
//		if (updown_y < 50) {
//			updown = 1;
//		}
//	}
//
//	//�G���~�`�ɓ�����
//	angle = angle - 0.04;
//	if (angle > 2 * PI) {
//		angle = angle - 2 * PI;
//	}
//	e.x = enemy_kaiten_chuushin_x + r * cos(angle);
//	e.y = enemy_kaiten_chuushin_y + r * sin(angle);
//}

//void draw_boss() {
//	if (e.hp == 0) return;
//
//	DrawGra((int)e.x, (int)e.y, e.img, TRUE);	//�G�̕`��
//	RedBlinkDrawGra((int)e.x, (int)e.y, e.img, &e.hit, e.hit_time, 110);	//�G��ԓ_�ł�����
//}

//void collision_shot_to_player(void) {
//	if (p.hp == 0 || e.hp == 0) return;
//
//	for (int i = 0; i < SHOT_FANCTIONS; i++) {
//		for (int j = 0; j < SHOT_QUANTITY; j++) {
//			if (shot_e[i].exists[j] == TRUE) {	//���̒e�����݂���Ƃ�
//				//�Q�_�Ԃ̋��������@�G�̒e to �v���C���[
//				if (15 > sqrt((p.x - shot_e[i].x[j]) * (p.x - shot_e[i].x[j]) + (p.y - shot_e[i].y[j]) * (p.y - shot_e[i].y[j]))) {
//					p.hit_time = GetNowCount();	//�q�b�g�������Ԃ��擾
//					if (p.hit == FALSE)	p.hp -= shot_e[i].damage;	//�q�b�g�t���O�����Ă��Ȃ���΃v���C���[��HP���_���[�W�����炷
//					if (p.hp < 0)			p.hp = 0;	//HP���}�C�i�X�̂Ƃ��A0�ɏC��
//					shot_e[i].exists[j] = FALSE;	//���������e������
//					p.hit = TRUE;	//�q�b�g�t���O�𗧂Ă�
//				}
//			}
//		}
//	}
//}