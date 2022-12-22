#include "GV.h"

#define ENEMY_RANGE_MAX 4
#define PSHOT_RANGE_MAX 2
#define BRANGE 40.0//�{�X�̓�����͈�

//�G�̓����蔻��͈�
int enemy_range[ENEMY_RANGE_MAX] = { 16,30,16,50 };
//���@�V���b�g�̓����蔻��͈�
int pshot_range[PSHOT_RANGE_MAX] = { 6, };

void collision_main() {
	collision_pshot_to_enemy();//���@�V���b�g�ƓG�Ƃ̏���
	collision_enemyshot_to_player();//�G�V���b�g�Ǝ��@�Ƃ̏���
	collision_enemy_to_player();
	collision_block_to_player();
	//ch_and_item();//�A�C�e���ڐG����
}

//�����蔻��
//������𔻒肷�镨��:1  ������𔻒肷�镨��:2
int collision_judge(double x1, double y1, double x2, double y2,
	double range1, double range2, double spd1, double angle1) {
	int j;
	double x = x1 - x2;
	double y = y1 - y2;
	//�����蔻��̍��v�͈�
	double r = range1 + range2;
	//���Ԃ��v�Z����K�v�������
	if (spd1 > r) {
		//�P�t���[���O�ɂ����ʒu���i�[����
		double pre_x = x1 + cos(angle1 + PI) * spd1;
		double pre_y = y1 + sin(angle1 + PI) * spd1;
		double px, py;
		for (j = 0; j < spd1 / r; j++) {//�i�񂾕��������蔻�蕪���[�v
			px = pre_x - x2;
			py = pre_y - y2;
			if (px * px + py * py < r * r)
				return 1;
			pre_x += cos(angle1) * r;
			pre_y += sin(angle1) * r;
		}
	}
	if (x * x + y * y < r * r)//�����蔻����Ȃ�
		return 1;//������
	return 0;
}

//���@�V���b�g�ƓG�Ƃ̏���
void collision_pshot_to_enemy() {
	int i, s;
	for (i = 0; i < PSHOT_MAX; i++) {//���@�V���b�g����
		if (pshot[i].exists == TRUE) {
			//for (s = 0; s < ENEMY_MAX; s++) {//�G����
			//	if (enemy[s].flag > 0) {
			//		if (out_judge_pshot(i, s)) {//���@�V���b�g�ƓG���������Ă����
			//			pshot[i].exists = FALSE;//���̎��@�V���b�g������
			//			hit_enemy(s, pshot[i].damage);
			//			break;
			//		}
			//	}
			//}

			//�{�X���o�����Ă��āA�`�悵�Ȃ��t���O���I�t�ŁA�V���b�g���Ȃ�
			if (boss.exists == TRUE && boss.graph_flag == 0 && boss.state == 2) {
				if (collision_pshot_to_boss(i)) {
					pshot[i].exists = FALSE;
					hit_boss(pshot[i].damage);
					boss.muteki_count = 1;
				}
			}
		}
	}
}

//���@�V���b�g���{�X�ɓ����������ǂ����𔻒肷��
int collision_pshot_to_boss(int i) {
	if (pshot[i].count > 0) {//�V���b�g�̋O�����P�x�ł��v�Z����Ă�����
		if (collision_judge(pshot[i].x, pshot[i].y, boss.x, boss.y,
			pshot_range[pshot[i].kind], BRANGE, pshot[i].speed, pshot[i].angle)) {
			return 1;
		}
	}
	return 0;
}

//�G�V���b�g�����@�ɓ����������ǂ����𔻒肷��
int collision_enemyshot_to_player(int s, int n) {
	if (eshot[s].bullet[n].count > 0) {//�V���b�g�̋O�����P�x�ł��v�Z����Ă�����
		if (collision_judge(
			eshot[s].bullet[n].x, eshot[s].bullet[n].y, p.x, p.y,
			bullet_info[eshot[s].bullet[n].kind].range, PRANGE,
			eshot[s].bullet[n].speed, eshot[s].bullet[n].angle
		)) {
			return 1;
		}
	}
	return 0;
}

//�{�X�V���b�g�����@�ɓ����������ǂ����𔻒肷��
int collision_bossshot_to_player(int n) {
	if (boss_shot.bullet[n].count > 0) {//�V���b�g�̋O�����P�x�ł��v�Z����Ă�����
		if (collision_judge(
			boss_shot.bullet[n].x, boss_shot.bullet[n].y, p.x, p.y,
			bullet_info[boss_shot.bullet[n].kind].range, PRANGE,
			boss_shot.bullet[n].speed, boss_shot.bullet[n].angle
		)) {
			return TRUE;
		}
	}
	return 0;
}

//�G�V���b�g�Ǝ��@�Ƃ̏���
void collision_enemyshot_to_player() {
	if (boss.kind == boss.danmaku_num[0] + 1)return;

	int s, n;
	//if (p.state == 0 && p.muteki_count == 0 && out_lazer() == 1) {
	//	p.count = 0;
	//	p.state = 1;
	//	se_flag[3] = 1;
	//}
	////�G���G�̃V���b�g
	//for (s = 0; s < ESHOT_MAX; s++) {//�G�V���b�g����
	//	if (eshot[s].isSet == TRUE) {//���̃V���b�g���o�^����Ă�����
	//		for (n = 0; n < ESHOT_BULLET_MAX; n++) {//�e����
	//			if (eshot[s].bullet[n].exists == TRUE) {//�e���o�^����Ă�����
	//				if (bom.flag != 0) {
	//					eshot[s].bullet[n].flag = 0;
	//					continue;
	//				}
	//				if (collision_enemyshot_to_player(s, n) == 1) {//���@�ɂ��̒e���ڐG���Ă�����
	//					eshot[s].bullet[n].flag = 0;//�e���I�t
	//					if (p.state == 0 && p.muteki_count == 0) {
	//						p.count = 0;
	//						p.state = 1;
	//						se_flag[3] = 1;
	//					}
	//				}
	//			}
	//		}
	//	}
	//}
	//�{�X�̃V���b�g
	if (boss_shot.isSet == TRUE) {//���̃V���b�g���o�^����Ă�����
		for (n = 0; n < BOSS_BULLET_MAX; n++) {//�e����
			if (boss_shot.bullet[n].exists == TRUE) {//�e���o�^����Ă�����
				//if (bom.flag != 0) {
				//	boss_shot.bullet[n].flag = 0;
				//	continue;
				//}
				if (collision_bossshot_to_player(n) == TRUE) {//���@�ɂ��̒e���ڐG���Ă�����
					boss_shot.bullet[n].exists = FALSE;//�e������
					if (/*p.state == 0 && */p.muteki_count == 0) {
						hit_player(boss_shot.bullet[n].damage);
						p.count = 0;
						p.state = 1;
						se_flag[3] = 1;
					}
				}
			}
		}
	}
}


void collision_enemy_to_player() {
	if (boss.kind == boss.danmaku_num[0] + 1)return;

	//�{�X�ƃv���C���[���ڐG���Ă�����
	if (collision_judge(boss.x, boss.y, p.x, p.y, BRANGE, PRANGE, NULL, NULL)) {
		if (p.muteki_count == 0)hit_player(10);//���G��ԂłȂ���΃_���[�W�����炷
		p.count = 0;
		p.state = 1;
		se_flag[3] = 1;
	}
}

//s�̓G�ɒe�̃_���[�W�H��킷
//void hit_enemy(int s, int damage) {
//	enemy[s].hp -= damage;//�e�̎��p���[��HP�����炷
//	enemy_death_judge(s);//�G�����ʂ��ǂ��������߂�
//}

//�{�X�Ƀ_���[�W��H��킷
void hit_boss(int damage) {
	boss.hp -= damage;//�e�̎��p���[��HP�����炷
	if (boss.hp < 0)boss.hp = 0;
}

//�v���C���[�Ƀ_���[�W��H��킷
void hit_player(int damage) {
	p.hp -= damage;//�e�̎��p���[��HP�����炷
	if (p.hp < 0)p.hp = 0;
}

//�v���C���[�ƃu���b�N�̐ڐG����
int collision_block_to_player() {
	for (int i = 0; i < STAGE_TOTAL; i++) {
		if (strcmp(Block[i].kind, b_type.steps_01) != 0) {//����u���b�N�ȊO�̂Ƃ�
			if (Block[i].x - Block[i].w < p.x && p.x < Block[i].x + Block[i].w &&
				Block[i].y - Block[i].h < p.y && p.y < Block[i].y + Block[i].h) {
				return TRUE;
			}
		}
		else if ((p.jump_state == e_falling || p.jump_state == e_grounded) &&
			GetKey(KEY_INPUT_S) == 0) {//����u���b�N�̂Ƃ�
			if (Block[i].x - Block[i].w < p.x && p.x < Block[i].x + Block[i].w &&
				Block[i].y - Block[i].h < p.y && p.y < Block[i].y - Block[i].h + 5) {
				p.y = Block[i].y - Block[i].h + 1;//�͈͓��Ȃ�v���C���[��y���W�𑫏�u���b�N��ʂ�y���W�ɋ����ύX
				return TRUE;
			}
		}
	}
	return FALSE;
}