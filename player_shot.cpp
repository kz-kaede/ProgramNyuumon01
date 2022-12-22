#include "GV.h"
#include "effects.h"

int pshot0num[2] = { 2,4 };
int pshot0pos_x[4] = { 30,30,10,10 };
int pshot0pos_y[4] = { -10, 10, -30, 30 };

#define OPTION_X 25
#define OPTION_Y 35
int option0num[2] = { 2,4 };
double option0ang[4] = { -PI / 2,-PI / 2,-PI / 2 - PI / 4,-PI / 2 + PI / 4 };//�I�v�V�����̔��ˊp�x(49)


//�v���C���[�V���b�g�Ɋւ���֐�
void pshot_main() {
	calc_pshot();//�V���b�g�̋N���v�Z
	enter_shot();//�V���b�g�o�^
}

//�V���b�g�o�^��
void enter_shot() {
	//�V���b�g�{�^����������Ă�����
	if (p.hp == 0)return;
	if (GetKey(KEY_INPUT_J) > 0) {
		p.shot_count++;
		if (p.shot_count % 3 == 0) {//3�J�E���g��1��
			//if (GetKey(KEY_INPUT_LSHIFT) > 0)//�ᑬ�ړ����Ȃ�
			//	ch1_shot_pattern();
			//else
				ch0_shot_pattern();
		}
	}
	else
		p.shot_count = 0;
}

//���@�V���b�g�̓o�^�\�ԍ���Ԃ�
int search_pshot() {
	for (int i = 0; i < PSHOT_MAX; i++) {
		if (pshot[i].exists == 0)
			return i;
	}
	return -1;
}

//�ʏ�V���b�g�o�^
void ch0_shot_pattern() {
	int n,k;
	//n = pshot0num[p.power < 200 ? 0 : 1];
	n = 4;
	for (int i = 0; i < n; i++) {
		if ((k = search_pshot()) != -1) {
			pshot[k].exists = TRUE;
			pshot[k].count = 0;
			pshot[k].speed = 20;
			if (p.turn == TRUE) {
				pshot[k].angle = PI;
				pshot[k].x = p.x - pshot0pos_x[i];
			}
			else {
				pshot[k].angle = 0;
				pshot[k].x = p.x + pshot0pos_x[i];
			}
			pshot[k].y = p.y + pshot0pos_y[i];
			pshot[k].damage = (n < 2 ? 20 : 12) + p.power / 100;//2�؂Ȃ�20,4�؂Ȃ�12(50)
			pshot[k].kind = 0;
			pshot[k].img = img_pshot[0];//�摜�ԍ����(49)
		}
	}
}

//�ᑬ�ʏ�V���b�g�o�^
void ch1_shot_pattern() {
	int k;
	int n = pshot0num[p.power < 200 ? 0 : 1];
	for (int i = 0; i < n; i++) {
		if ((k = search_pshot()) != -1) {
			pshot[k].exists = TRUE;
			pshot[k].count = 0;
			pshot[k].angle = 0;
			pshot[k].speed = 20;
			pshot[k].x = p.x + pshot0pos_x[i] / 3;//�ᑬ���Ȃ�ʒu�𒆐S����
			pshot[k].y = p.y + pshot0pos_y[i] / 2;
			pshot[k].damage = (n < 2 ? 20 : 12) + p.power / 100;//2�؂Ȃ�20,4�؂Ȃ�12(50)
			pshot[k].kind = 0;
			pshot[k].img = img_pshot[0];//�摜�ԍ����(49)
		}
	}
}


//�V���b�g�̈ړ��v�Z
void calc_pshot() {
	for (int i = 0; i < PSHOT_MAX; i++) {
		if (pshot[i].exists == TRUE) {
			int dranx = (int)(pshot[i].speed + 11 / 2), drany = (int)(pshot[i].speed + 55 / 2);
			//if (pshot[i].kind == 1)
			//	calc_homing(i);
			pshot[i].x += cos(pshot[i].angle) * pshot[i].speed;
			pshot[i].y += sin(pshot[i].angle) * pshot[i].speed;
			pshot[i].count++;
			if (pshot[i].x<-dranx - camera_x || pshot[i].x>(double)FMX + dranx - camera_x ||
				pshot[i].y<-drany || pshot[i].y>(double)FMY + drany)//��ʂ���O�ꂽ��
				pshot[i].exists = FALSE;
		}
	}
}



//���@�V���b�g�`��
void draw_pshot() {
	for (int i = 0; i < PSHOT_MAX; i++) {
		if (pshot[i].exists == TRUE) {
			DrawRotaGraphF((float)pshot[i].x + (float)camera_x, (float)pshot[i].y, 1, pshot[i].angle + PI / 2, pshot[i].img, TRUE);
		}
	}
}



//void shot_p_single(void) {
//	if (p.hp == 0) return;
//
//	shot_p[0].velocity = 10;
//	shot_p[0].damage = 60;
//
//	if (shot_p[0].count >= SHOT_QUANTITY - 2) shot_p[0].count = 0;	//�J�E���g���ő�ɂȂ�����J�E���g���Z�b�g
//
//	//����̃L�[�������ꂽ���A�e��\������
//	if (GetKey(KEY_INPUT_J) != 0) {	//�L�[�{�[�h�́hJ"�L�[
//		if (shot_p[0].exists[shot_p[0].count] == FALSE) {	//�J�E���g���i�݁A���̒e�����݂��ĂȂ����A�v���C���[�ʒu����V�����e�𔭎�
//			shot_p[0].x[shot_p[0].count] = p.x + 10; //�v���C���[�̍��W��e�̍��W��
//			shot_p[0].y[shot_p[0].count] = p.y;
//			shot_p[0].exists[shot_p[0].count] = TRUE;	//����
//			shot_p[0].set_time[shot_p[0].count] = GetNowCount();	//�e�̐������Ԃ��擾
//		}
//	}
//	if (GetNowCount() - shot_p[0].set_time[shot_p[0].count] > 300) {	//�e�̘A�ˊԊu�𒲐�
//		shot_p[0].count++;
//	}
//
//	//���ׂĂ̒e�ɑ΂��āA�e�����݂��Ă�������W�X�V
//	for (int j = 0; j < SHOT_QUANTITY; j++) {
//		if (shot_p[0].exists[j] == TRUE) {		//���̒e���݂���Ȃ�
//			shot_p[0].x[j] += shot_p[0].velocity;	//�E�����ɓ�����
//			//�e����ʊO�ɏo����񑶍݂ɂ���
//			if (shot_p[0].x[j] < 0 || shot_p[0].x[j] > WINDOW_SIZE_W || shot_p[0].y[j] < 0 || shot_p[0].y[j] > WINDOW_SIZE_H) {
//				shot_p[0].exists[j] = FALSE;
//			}
//			DrawGra((int)shot_p[0].x[j], (int)shot_p[0].y[j], shot_p[0].handle[j], TRUE); //�e�̕`��
//		}
//	}
//}
//
////�V���b�g�̈ړ��v�Z
//void calc_pshot() {
//	for (int i = 0; i < CSHOT_MAX; i++) {
//		if (pshot[i].exists == 1) {
//			int dranx = (int)(pshot[i].speed + 11 / 2), drany = (int)(pshot[i].speed + 55 / 2);
//			if (pshot[i].kind == 1)
//				calc_homing(i);
//			pshot[i].x += cos(pshot[i].angle) * pshot[i].speed;
//			pshot[i].y += sin(pshot[i].angle) * pshot[i].speed;
//			pshot[i].count++;
//			if (pshot[i].x<-dranx || pshot[i].x>FMX + dranx ||
//				pshot[i].y<-drany || pshot[i].y>FMY + drany)//��ʂ���O�ꂽ��
//				pshot[i].exists = 0;
//		}
//	}
//}
//
//void shot_p_triple(void) {
//	if (p.hp == 0) return;
//
//	shot_p[1].velocity = 10;
//	shot_p[1].damage = 40;
//
//	if (shot_p[1].count >= SHOT_QUANTITY - 2) shot_p[1].count = 0;	//�J�E���g���ő�ɂȂ�����J�E���g���Z�b�g
//
//	//����̃L�[�������ꂽ���A�U�e��\������
//	if (GetKey(KEY_INPUT_K) != 0) {	//�L�[�{�[�h�́hK"�L�[
//		if (shot_p[1].exists[shot_p[1].count] == FALSE) {	//�J�E���g���i�݁A���̒e�����݂��ĂȂ����A�v���C���[�ʒu����V�����e�𔭎�
//			shot_p[1].x[shot_p[1].count] = p.x + 10;
//			shot_p[1].y[shot_p[1].count] = p.y;
//			shot_p[1].exists[shot_p[1].count] = 1;	//����
//			shot_p[1].count++;
//
//			shot_p[1].x[shot_p[1].count] = p.x + 10;
//			shot_p[1].y[shot_p[1].count] = p.y;
//			shot_p[1].exists[shot_p[1].count] = 1;	//����
//			shot_p[1].count++;
//
//			shot_p[1].x[shot_p[1].count] = p.x + 10;
//			shot_p[1].y[shot_p[1].count] = p.y;
//			shot_p[1].exists[shot_p[1].count] = TRUE;	//����
//			shot_p[1].set_time[shot_p[1].count] = GetNowCount();	//�e�̐������Ԃ��擾
//		}
//	}
//	if (GetNowCount() - shot_p[1].set_time[shot_p[1].count] > 600) {	//�e�̘A�ˊԊu�𒲐�
//		shot_p[1].count++;
//	}
//
//	printfDx("shot_p[1].count = %d\n", shot_p[1].count);
//
//
//	//���ׂĂ̒e�ɑ΂��āA�e�����݂��Ă�������W�X�V
//	for (int j = 0; j < SHOT_QUANTITY; j++) {
//		if (shot_p[1].exists[j] == TRUE) {	//���̒e�����݂���Ȃ�
//			switch (j % 3) {
//			case 0:		//����
//				shot_p[1].x[j] += shot_p[1].velocity;	//�E�����ɓ�����
//				break;
//			case 1:		//��
//				shot_p[1].x[j] += shot_p[1].velocity;	//�E������ɓ�����
//				shot_p[1].y[j] -= shot_p[1].velocity / 3;
//				break;
//			case 2:		//��
//				shot_p[1].x[j] += shot_p[1].velocity;	//�E�������ɓ�����
//				shot_p[1].y[j] += shot_p[1].velocity / 3;
//				break;
//			default:
//				printfDx("�G���[\n");
//			}
//			//�e����ʊO�ɏo����񑶍݂ɂ���
//			if (shot_p[1].x[j] < 0 || shot_p[1].x[j] > WINDOW_SIZE_W || shot_p[1].y[j] < 0 || shot_p[1].y[j] > WINDOW_SIZE_H) {
//				shot_p[1].exists[j] = FALSE;
//			}
//			DrawGra((int)shot_p[1].x[j], (int)shot_p[1].y[j], shot_p[1].handle[j], TRUE); //�e�̕`��
//		}
//	}
//}