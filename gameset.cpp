#include "GV.h"


void judge_gameset() {
	//���s�̔���
	if (boss.kind == boss.danmaku_num[0] + 1) {
		SetFontSize(64);
		DrawString(520, 330, "You Win!\n", color_white);
		SetFontSize(32);
		DrawFormatString(530, 400, color_white, "Score: %d", p.hp * 100);	//�X�R�A�̕\��
	}
	if (p.hp == 0) {
		SetDrawBright(255, 100, 100);
		SetFontSize(64);
		DrawString(480, 330, "Game Over...\n", color_red);
	}
}