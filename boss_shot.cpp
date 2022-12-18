#include "GV.h"
#include "bossfanc.h"
#include "effects.h"

//�{�X�̒e�����C��
void boss_shot_main() {
	if ((stage_count == boss.appear_count[0] || stage_count == boss.appear_count[1])
		&& boss.exists == FALSE) {//�J�n���ԂȂ�
		enter_boss(0);//�J�n
	}
	if (boss.exists == FALSE)//�{�X���o�^����Ė�����Ζ߂�
		return;
	calc_boss();
	if (boss.phy.flag == 1)//�������Z�ړ��I���Ȃ�
		calc_phy();//�����v�Z��
	if (boss.state == 2 && (boss.hp <= 0/* || boss.endtime <= 0*/)) {//�e�����ő̗͂������Ȃ�����
		//se_flag[1] = 1;//�G�̃s�`������
		//se_flag[11] = 1;
		//input_phy(30);//30�J�E���g�Œ�ʒu�ɖ߂�
		memset(&boss_shot, 0, sizeof(boss_shot_t));//�{�X�̒e������������
		//memset(&lazer, 0, sizeof(lazer_t) * LAZER_MAX);//�{�X�̃��[�U�[����������
		//flash.flag = 0;//�t���b�V��������
		//if (boss.kind == boss.danmaku_num[0] || boss.kind == boss.danmaku_num[1]) {//�o���ׂ��e����������������
		if (boss.kind == boss.danmaku_num[0] || boss.kind == boss.danmaku_num[1]) {//�o���ׂ��e����������������
			boss.exists = 0;//����
			boss.kind++;
		//	enter_dn(10, 40);//(45)
		//  se_flag[9] = 1;//�{�X�����񂾉�
			return;
		}
		else
			//stage_count++;
			enter_boss(1);//���̒e����o�^
	}
	if (boss.state == 1) {//�e���Ԃ̑ҋ@����
		wait_and_enter();
	}
	if (boss.state == 2) {//�e�����Ȃ�
		boss_shot_bullet[boss.kind]();//�e���֐���(�֐��|�C���^)
		boss_shot_calc();//�e���v�Z
	}
	boss.count++;
}


//�e�����Z�b�g
void enter_boss_shot() {
	memset(&boss_shot, 0, sizeof(boss_shot_t));//�e��񏉊���
	boss_shot.isSet = TRUE;
	boss.wtime = 0;//�ҋ@����0
	boss.state = 2;//�e������Ԃ�
	boss.hp = boss.set_hp[boss.kind];//HP�ݒ�
	boss.hp_max = boss.hp;
}

//�󂫔ԍ���Ԃ�
int search_boss_shot() {
	for (int i = 0; i < BOSS_BULLET_MAX; i++) {
		if (boss_shot.bullet[i].exists == FALSE)
			return i;
	}
	return -1;
}

//�{�X�̒e�����v�Z����
void boss_shot_calc() {
	int i;
	boss.endtime--;
	//if (boss.endtime < 0)
	//	boss.hp = 0;
	for (i = 0; i < BOSS_BULLET_MAX; i++) {
		if (boss_shot.bullet[i].exists == TRUE) {
			boss_shot.bullet[i].x += cos(boss_shot.bullet[i].angle) * boss_shot.bullet[i].speed;
			boss_shot.bullet[i].y += sin(boss_shot.bullet[i].angle) * boss_shot.bullet[i].speed;
			boss_shot.bullet[i].count++;
			if (boss_shot.bullet[i].count > boss_shot.bullet[i].till) {
				if (boss_shot.bullet[i].x<-50 - camera_x || boss_shot.bullet[i].x>(double)FMX + 50 - camera_x ||
					boss_shot.bullet[i].y<-50 || boss_shot.bullet[i].y>(double)FMY + 50)
					boss_shot.bullet[i].exists = FALSE;
			}
		}
	}
	boss_shot.count++;
}

//�e�ۂ̕`��
void draw_bullet() {
	int i, j, eff;
	double disp_angle;
	SetDrawMode(DX_DRAWMODE_BILINEAR);//���`�⊮�`��
	//for (i = 0; i < ESHOT_MAX; i++) {//�G�̒e���������[�v
	//	if (eshot[i].flag > 0) {//�e���f�[�^���I���Ȃ�
	//		for (j = 0; j < ESHOT_BULLET_MAX; j++) {//���̒e�������e�̍ő吔�����[�v
	//			if (eshot[i].bullet[j].exists != 0) {//�e�f�[�^���I���Ȃ�
	//				if (eshot[i].bullet[j].eff == 1)
	//					SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	//				if (bullet_info[shot[i].bullet[j].kind].kaiten == 1)
	//					disp_angle = PI2 * (eshot[i].bullet[j].count % 120) / 120;
	//				else
	//					disp_angle = eshot[i].bullet[j].angle + PI / 2;
	//
	//				DrawRotaGraphF(
	//					eshot[i].bullet[j].x, eshot[i].bullet[j].y,
	//					1.0, disp_angle,
	//					img_bullet[eshot[i].bullet[j].kind][eshot[i].bullet[j].col], TRUE);
	//
	//				if (eshot[i].bullet[j].eff == 1)
	//					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//			}
	//		}
	//	}
	//}
	//boss_assist_img();
	//�{�X
	if (boss_shot.isSet == TRUE) {//�e���f�[�^���I���Ȃ�
		for (j = 0; j < BOSS_BULLET_MAX; j++) {//���̒e�������e�̍ő吔�����[�v
			if (boss_shot.bullet[j].exists == TRUE) {//�e�f�[�^���I���Ȃ�
				eff = 0;
				if (boss_shot.bullet[j].kaiten == 1)
					disp_angle = PI2 * (boss_shot.bullet[j].count % 120) / 120;
				else
					disp_angle = boss_shot.bullet[j].angle + PI / 2;
				if (boss_shot.bullet[j].eff_detail == 1) {//���J�ɂ��������p�e�G�t�F�N�g
					SetDrawBlendMode(DX_BLENDMODE_ADD, 100 + GetRand(155)), eff = 1;
					DrawRotaGraphF(
						(float)boss_shot.bullet[j].x, (float)boss_shot.bullet[j].y,
						1.3, disp_angle,
						img_bullet[boss_shot.bullet[j].kind][boss_shot.bullet[j].col], TRUE);
				}
				if (boss_shot.bullet[j].eff == 1)
					SetDrawBlendMode(DX_BLENDMODE_ADD, 255), eff = 1;
				if (boss_shot.bullet[j].eff == 2)
					SetDrawBlendMode(DX_BLENDMODE_ADD, 255 + GetRand(100)), eff = 1;
				DrawRotaGraphF(
					(float)boss_shot.bullet[j].x + (float)camera_x, (float)boss_shot.bullet[j].y,
					1.0, disp_angle,
					img_bullet[boss_shot.bullet[j].kind][boss_shot.bullet[j].col], TRUE);
				if (eff == 1)
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}
	}
	SetDrawMode(DX_DRAWMODE_NEAREST);//�`��`����߂�
}