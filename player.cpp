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
	p.phy.v0y = 2.3;
	p.phy.ay = -0.1;
	static double t = 0;
	double Fx = 0;//�͂��`
	double Fy = 0;//�͂��`
	double dash = 1.0;//�͂��`
	double y_add;
	//��C��R
	Fx += p.phy.vx * -0.06;

	if (p.jump_state == e_grounded) {
		//���C��
		if (p.phy.vx > 0) {
			Fx += -0.5;
		}
		else if (p.phy.vx < 0) {
			Fx += 0.5;
		}
	}
	if (GetKey(KEY_INPUT_LSHIFT) != 0)dash = 1.5;//Shift�L�[�Ń_�b�V��
	if (GetKey(KEY_INPUT_D) != 0) {
		p.turn = FALSE;
		if (p.jump_state == e_grounded)//���n���Ă���Ƃ�
			Fx += 1.5 * dash;
		else
			Fx += 1;
	}
	if (GetKey(KEY_INPUT_A) != 0) {
		p.turn = TRUE;
		if (p.jump_state == e_grounded)
			Fx += -1.5 * dash;
		else
			Fx += -1;
	}
	p.phy.ax = Fx;
	p.phy.vx += p.phy.ax;
	if (p.phy.vx > 0) {
		for (int i = 0; i < (int)p.phy.vx; i++) {
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
	if (p.phy.vx < 0) {
		for (int i = 0; i > (int)p.phy.vx; i--) {
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

	if (GetKey(KEY_INPUT_SPACE) == 1 && p.jump_count < 2) {
		p.jump_count++;
		t = 0;
		p.jump_state = e_jumping;
	}
	if (p.jump_state == e_jumping) {
		y_add = p.phy.v0y * t + p.phy.ay * (t * t);

		if (y_add >= 0) {
			for (int i = 0; i < (int)y_add; i++) {
				p.y--;
				if (collision_block_to_player() == TRUE) {
					p.jump_state = e_falling;
					t = 0;
					p.y++;
					break;
				}
			}
		}
		else {
			p.jump_state = e_falling;
		}
	}
	if (p.jump_state == e_falling || p.jump_state == e_grounded) {

		y_add = p.phy.ay / 4 * (t * t);
		for (int i = 0; i > (int)y_add; i--) {
			p.y++;
			if (collision_block_to_player() == TRUE) {
				p.jump_state = e_grounded;
				p.jump_count = 0;
				t = 0;
				p.y--;
				break;
			}
		}
	}
	t++;
}

//���@�̕`��
void draw_player(void) {
	int t;
	if (p.hp == 0) return;

	t = count % 5;
	if (t < 1) {
		p.buff_x[0] = p.x;
		p.buff_y[0] = p.y;
	}
	else if (t < 2) {
		p.buff_x[1] = p.x;
		p.buff_y[1] = p.y;
	}
	else if (t < 3) {
		p.buff_x[2] = p.x;
		p.buff_y[2] = p.y;
	}
	else if (t < 4) {
		p.buff_x[3] = p.x;
		p.buff_y[3] = p.y;
	}
	else if (t < 5) {
		p.buff_x[4] = p.x;
		p.buff_y[4] = p.y;
	}


	if (p.jump_count >= 2) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 44);
		DrawRotaGraphF((float)p.buff_x[4] + camera_x, (float)p.buff_y[4], 1.0f, 0.0f, p.img, TRUE, p.turn == TRUE ? TRUE : FALSE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 44);
		DrawRotaGraphF((float)p.buff_x[3] + camera_x, (float)p.buff_y[3], 1.0f, 0.0f, p.img, TRUE, p.turn == TRUE ? TRUE : FALSE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 44);
		DrawRotaGraphF((float)p.buff_x[2] + camera_x, (float)p.buff_y[2], 1.0f, 0.0f, p.img, TRUE, p.turn == TRUE ? TRUE : FALSE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 44);
		DrawRotaGraphF((float)p.buff_x[1] + camera_x, (float)p.buff_y[1], 1.0f, 0.0f, p.img, TRUE, p.turn == TRUE ? TRUE : FALSE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 44);
		DrawRotaGraphF((float)p.buff_x[0] + camera_x, (float)p.buff_y[0], 1.0f, 0.0f, p.img, TRUE, p.turn == TRUE ? TRUE : FALSE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	DrawRotaGraphF((float)p.x + camera_x, (float)p.y, 1.0f, 0.0f, p.img, TRUE, p.turn == TRUE ? TRUE : FALSE);
	RedBlinkDrawRotaGraphF((float)p.x + camera_x, (float)p.y, p.img, p.muteki_count, 6,p.turn == TRUE ? TRUE : FALSE);	//���@��ԓ_�ł�����
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
