#include "GV.h"

int DrawRotaGraphF(double xd, double yd, double ExRate, double Angle, int GrHandle, int TransFlag, int TurnFlag = FALSE) {
	return DrawRotaGraphF((float)xd, (float)yd, ExRate, Angle, GrHandle, TransFlag, TurnFlag);
}
int DrawModiGraphF(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, int GrHandle, int TransFlag) {
	return DrawModiGraphF((float)x1, (float)y1, (float)x2, (float)y2, (float)x3, (float)y3, (float)x4, (float)y4, GrHandle, TransFlag);
}
//
//int DrawRotaGraphFdF(double xd, double yd, double ExRate, double Angle, int GrHandle, int TransFlag, int TurnFlag = FALSE) {
//	return DrawRotaGraphF((float)xd + FX + dn.x, (float)yd + FY + dn.y, ExRate, Angle, GrHandle, TransFlag, TurnFlag);
//}
//int DrawModiGraphFdF(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, int GrHandle, int TransFlag) {
//	return DrawModiGraphF((float)x1 + FX + dn.x, (float)y1 + FY + dn.y, (float)x2 + FX + dn.x, (float)y2 + FY + dn.y,
//		(float)x3 + FX + dn.x, (float)y3 + FY + dn.y, (float)x4 + FX + dn.x, (float)y4 + FY + dn.y, GrHandle, TransFlag);
//}
//int DrawGraphFd(int xd, int yd, int GrHandle, int TransFlag) {
//	return DrawGraph(xd + FX + dn.x, yd + FY + dn.y, GrHandle, TransFlag);
//}

void draw_stage() {
	//ÉuÉçÉbÉNï`âÊ
	for (int i = 0; i < STAGE_TOTAL; i++) {
		switch (Block[i].d) {
		case FALSE:
			DrawRotaGraphF(
				Block[i].x + camera_x,
				Block[i].y,
				1.0f,
				0.0f,
				Block[i].img[0].img,
				TRUE,
				FALSE);
			break;
			
		case TRUE://ç∂ï˚å¸å¸Ç≠
			DrawRotaGraphF(
				Block[i].x + camera_x,
				Block[i].y,
				1.0f,
				0.0f,
				Block[i].img[0].img,
				TRUE,
				TRUE);
			break;
		}
	}
}

void draw_main() {


	draw_back_main();
	draw_stage();



	//DrawBox(0, 0, WINDOW_SIZE_W, WINDOW_SIZE_H, GetColor(50, 50, 50), TRUE);	//îwåiÇÉOÉåÅ[Ç…ê›íË



	if (bright_set.brt != 255)SetDrawBright(bright_set.brt, bright_set.brt, bright_set.brt);


	if (bright_set.brt != 255)SetDrawBright(255, 255, 255);

	player_hp_bar();
	boss_hp_bar();

	if (bright_set.brt != 255)SetDrawBright(bright_set.brt, bright_set.brt, bright_set.brt);

	draw_boss();		//ìGÇÃï\é¶
	draw_pshot();//é©ã@ÉVÉáÉbÉgÇÃï`âÊ

	if (bright_set.brt != 255)SetDrawBright(255, 255, 255);

	draw_player();

	if (bright_set.brt != 255)SetDrawBright(bright_set.brt, bright_set.brt, bright_set.brt);

	draw_bullet();//íeÇÃï`âÊ
	if (bright_set.brt != 255)SetDrawBright(255, 255, 255);


}