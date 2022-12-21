#include "GV.h"
#include "effects.h"

void calc_player() {
	//if (p.state == 1) {//��炢�{����t��
	//	/bright_set.brt = 80;//�Â�
	//	if (p.count > 20) {//0.33�b�󂯕t����
	//		p.state = 2;    //1:��炢�{����t���@2:����ŕ����オ�蒆
	//		p.count = 0;
	//		bright_set.brt = 255;
	//	}
	//}
	if (p.count == 0 && p.state == 1) {
		//enter_char_item();//�L�����̃A�C�e���o�^(39��)
		//p.x = FMX / 2;//���W�Z�b�g
		//p.y = FMY + 30;
		p.muteki_count++;//���G��Ԃ�
	}
	//if (p.state == 2) {//����ŕ��㒆�Ȃ�
	//	unsigned int push = CheckStatePad(configpad.left) + CheckStatePad(configpad.right)
	//		+ CheckStatePad(configpad.up) + CheckStatePad(configpad.down);
	//	p.y -= 1.5;//�L��������ɏグ��
	//	//�P�b�ȏォ�A�L������������x��ɂ��āA���������ꂽ��
	//	if (p.count > 60 || (p.y < FMY - 20 && push)) {
	//		p.count = 0;
	//		p.state = 0;//�L�����X�e�[�^�X�����ɖ߂�
	//	}
	//}
	if (p.muteki_count > 0) {//���G�J�E���g���Ȃ�
		p.muteki_count++;
		if (p.muteki_count > 60)//60�ȏソ������
			p.muteki_count = 0;//�߂�
	}
	p.count++;//�L�����N�^�J�E���g�A�b�v
	//p.img = (p.count % 24) / 6;//���݂̉摜����
}

void player_move(void) {
	if (GetKey(KEY_INPUT_D) != 0) {
		p.turn = FALSE;

		for (int i = 0; i < p.speed; i++) {
			p.x++;;
			if (p.x > WINDOW_SIZE_W / 2 &&
				p.x < STAGE_WIDTH * 32 - WINDOW_SIZE_W / 2) {
				camera_x--;
			}

			if (p.x > STAGE_WIDTH * 32 - 16 ||
				collision_block_to_player() == TRUE) {
				p.x--;
				if (p.x > WINDOW_SIZE_W / 2 &&
					p.x < STAGE_WIDTH * 32 - WINDOW_SIZE_W / 2) {
					camera_x++;
				}
				break;
			}
		}
	}
	if (GetKey(KEY_INPUT_A) != 0) {
		p.turn = TRUE;

		for (int i = 0; i < p.speed; i++) {
			p.x--;;
			if (p.x > WINDOW_SIZE_W / 2 &&
				p.x < STAGE_WIDTH * 32 - WINDOW_SIZE_W / 2) {
				camera_x++;
			}

			if (p.x < 16 ||
				collision_block_to_player() == TRUE) {
				p.x++;
				if (p.x > WINDOW_SIZE_W / 2 &&
					p.x < STAGE_WIDTH * 32 - WINDOW_SIZE_W / 2) {
					camera_x--;
				}
				break;
			}
		}
	}
	if (GetKey(KEY_INPUT_W) != 0) {
		for (int i = 0; i < p.speed; i++) {
			p.y--;
			if (p.y < 16 ||
				collision_block_to_player() == TRUE) {
				p.y++;
				break;
			}
		}
	}
	if (GetKey(KEY_INPUT_S) != 0) {
		for (int i = 0; i < p.speed; i++) {
			p.y++;
			if (p.y > STAGE_HEIGHT * 32 - 16 ||
				collision_block_to_player() == TRUE) {
				p.y--;
				break;
			}
		}
	}

	double v0y = 2.3;
	double ay = -0.1;
	static double t = 0;
	int y_add;

	if(p.jump_flug != e_grounded)t++;

	if (GetKey(KEY_INPUT_SPACE) == 1) {
		p.phy.prex = p.x;
		p.jump_count++;
		t = 0;
		p.jump_flug = e_jumping;
	}
	if (p.jump_flug == e_jumping) {
		y_add = v0y * t + ay * (t * t);

		if (y_add >= 0) {
			for (int i = 0; i < y_add; i++) {
				p.y--;
				if (collision_block_to_player() == TRUE) {
					p.jump_flug = e_falling;
					t = 0;
					p.y++;
					break;
				}
			}
		}
		else {
			p.jump_flug = e_falling;
		}
	}
	if (p.jump_flug == e_falling) {
		y_add = ay/3 * (t * t);
		for (int i = 0; i > y_add; i--) {
			p.y++;
			if (collision_block_to_player() == TRUE) {
				//p.jump_flug = e_grounded;
				t = 0;
				p.y--;
				break;
			}
		}
	}
}

//���@�̕`��
void draw_player(void) {
	if (p.hp == 0) return;


	if (p.turn == TRUE) {
		DrawRotaGraphF((float)p.x + camera_x, (float)p.y, 1.0f, 0.0f, p.img, TRUE, TRUE);
	}
	else {
		DrawRotaGraphF((float)p.x + camera_x, (float)p.y, 1.0f, 0.0f, p.img, TRUE, FALSE);
	}


	RedBlinkDrawRotaGraphF((float)p.x + camera_x, (float)p.y, p.img, p.muteki_count, 6);	//���@��ԓ_�ł�����
}

//void collision_shot_to_enemy(void) {
//	if (p.hp == 0 || e.hp == 0) return;
//
//	for (int i = 0; i < SHOT_FANCTIONS; i++) {
//		for (int j = 0; j < SHOT_QUANTITY; j++) {
//			if (shot_p[i].exists[j] == TRUE) {	//���̒e�����݂���Ƃ�
//				//�Q�_�Ԃ̋��������@�v���C���[�̒e to �G
//				if (25 > sqrt((e.x - shot_p[i].x[j]) * (e.x - shot_p[i].x[j]) + (e.y - shot_p[i].y[j]) * (e.y - shot_p[i].y[j]))) {
//					e.hit_time = GetNowCount();		//�q�b�g�������Ԃ��擾
//					e.hp -= shot_p[i].damage;		//�G��HP���_���[�W�����炷
//					if (e.hp < 0)	e.hp = 0;	//HP���}�C�i�X�̂Ƃ��A0�ɏC��
//					shot_p[i].exists[j] = 0;	//���������e������
//					e.hit = TRUE;			//�q�b�g�t���O�𗧂Ă�
//				}
//			}
//		}
//	}
//}

//void collision_player_to_enemy(void) {
//	if (p.hp == 0 || e.hp == 0) return;
//
//	//�Q�_�Ԃ̋��������@�v���C���[ to �G
//	if (40 > sqrt((e.x - p.x) * (e.x - p.x) + (e.y - p.y) * (e.y - p.y))) {
//		p.hit_time = GetNowCount();	//�q�b�g�������Ԃ��擾
//		if (p.hit == FALSE) p.hp -= 300;	//�q�b�g�t���O�����Ă��Ȃ���΃v���C���[��HP���_���[�W�����炷
//		if (p.hp < 0)		 p.hp = 0;		//HP���}�C�i�X�̂Ƃ��A0�ɏC��
//		p.hit = TRUE;	//�q�b�g�t���O�𗧂Ă�
//	}
//}
//
