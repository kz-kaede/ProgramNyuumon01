#include "GV.h"

void player_hp_bar() {
	int BarWidthMax = 260;
	int hp_bar;
	int hp_bar_print;
	int lines = 1;		//HP�o�[�̖{�����w��
	int y1 = 50;
	int	y2 = 60;

	hp_bar = (double)p.hp / (double)p.hp_max * ((double)BarWidthMax * (double)lines);	//HP���o�[�̒����ɕϊ�

	for (int i = lines; 0 < i; i--) {		//HP�o�[�̖{������f�N�������g
		if (hp_bar >= BarWidthMax * i) {		//������i�Ԗڂ�HP�o�[���A���̃o�[�̍ő�l�ȏ�Ȃ�
			hp_bar_print = BarWidthMax;
		}
		else if (hp_bar >= BarWidthMax * (i - 1)) {	//������i�Ԗڂ�HP�o�[���A���̃o�[�̍ŏ��l�ȏ�A�ő�l�����Ȃ�
			hp_bar_print = hp_bar % BarWidthMax;
		}
		else {								//������i�Ԗڂ�HP�o�[���A���̃o�[�̍ŏ��l�����Ȃ�
			hp_bar_print = 0;
		}
		DrawBox(10, y1, 10 + BarWidthMax, y2, GetColor(0, 0, 0), TRUE);	//HP�o�[�w�i
		DrawBox(10, y1, 10 + hp_bar_print, y2, GetColor(50, 230, 50), TRUE);	//HP�o�[���C��
		DrawBox(10, y1, 10 + BarWidthMax, y2, GetColor(255, 255, 255), FALSE);	//HP�o�[��

		//�o�[�̍��W�X�V
		y1 += 15; y2 += 15;
	}
	SetFontSize(20);
	DrawString(10, 22, "Player\n", GetColor(255, 255, 255));	//�v���C���[�̕�����`��
}

void boss_hp_bar() {
	int BarWidthMax = 260;
	int hp_bar;
	int hp_bar_print;
	int lines = 3;		//HP�o�[�̖{�����w��
	int y1 = 50;
	int	y2 = 60;

	hp_bar = (double)boss.hp / (double)boss.hp_max * ((double)BarWidthMax * (double)lines);	//HP���o�[�̒����ɕϊ�

	for (int i = lines; 0 < i; i--) {		//HP�o�[�̖{������f�N�������g
		if (hp_bar >= BarWidthMax * i) {		//������i�Ԗڂ�HP�o�[���A���̃o�[�̍ő�l�ȏ�Ȃ�
			hp_bar_print = BarWidthMax;
		}
		else if (hp_bar >= BarWidthMax * (i - 1)) {	//������i�Ԗڂ�HP�o�[���A���̃o�[�̍ŏ��l�ȏ�A�ő�l�����Ȃ�
			hp_bar_print = hp_bar % BarWidthMax;
		}
		else {								//������i�Ԗڂ�HP�o�[���A���̃o�[�̍ŏ��l�����Ȃ�
			hp_bar_print = 0;
		}
		DrawBox(1270 - BarWidthMax, y1, 1270, y2, GetColor(0, 0, 0), TRUE);	//HP�o�[�w�i
		DrawBox(1270 - BarWidthMax, y1, 1270 - BarWidthMax + hp_bar_print, y2, GetColor(255, 100, 100), TRUE);	//HP�o�[���C��
		DrawBox(1270 - BarWidthMax, y1, 1270, y2, GetColor(255, 255, 255), FALSE);	//HP�o�[��
		//�o�[�̍��W�X�V
		y1 += 15; y2 += 15;
	}
	SetFontSize(20);
	DrawString(970, 22, "BOSS \"The Pumpkin\"\n", GetColor(255, 50, 50));	//BOSS�̕�����`��
}
