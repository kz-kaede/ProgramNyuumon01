#include "GV.h"

void FpsTimeFanction() {
	static int FpsTime[2] = { 0, }, FpsTime_i = 0;
	static double Fps = 0.0;

	if (FpsTime_i == 0)
		FpsTime[0] = GetNowCount();                           //1���ڂ̎��Ԏ擾
	if (FpsTime_i == 49) {
		FpsTime[1] = GetNowCount();                           //50���ڂ̎��Ԏ擾
		Fps = 1000.0f / ((FpsTime[1] - FpsTime[0]) / 50.0f);//���肵���l����fps���v�Z
		FpsTime_i = 0;
	}
	else
		FpsTime_i++;                                          //���݉����ڂ��J�E���g
	if (Fps != 0)
		SetFontSize(20);
		DrawFormatString(1180, 700, color_white, "FPS %.1f", Fps); //fps��\��
	return;
}