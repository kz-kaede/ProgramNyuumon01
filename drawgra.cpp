#include "DxLib.h"

// �e�L�����̒��S����ɕ`�悷�邽�߂̕␳�֐��B
void DrawGra(int x, int y, int GrHandle, int TransFlag)
{
	int w, h;
	GetGraphSize(GrHandle, &w, &h);
	DrawGraph(x-w/2, y-h/2, GrHandle, TransFlag);
}
