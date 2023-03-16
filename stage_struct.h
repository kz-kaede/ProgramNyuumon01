#pragma once

typedef struct {
	int r, g, b;
}color_t;

typedef enum {
	e_Normal,
	e_Walk1,
	e_End,
	e_Ani_Total,
}e_Ani_t;

typedef struct block{
	char air[3] = "--";
	char ground[3] = "b0";
	char stone[3] = "b2";
	char dirt[3] = "b1";
	char grass[3] = "b3";
	char gold[3] = "b4";
	char steps_01[3] = "s1";
	char bricks[3] = "b5";
	char hatena[3] = "q1";
	char player[3] = "p0";
	char e1[3] = "e1";
}block_type_t;

typedef struct {
	char type[3];
}kind_t;

typedef struct {
	int img,w,h;
}pic_t;

typedef struct {
	char kind[3];
	double x,y;
}text_t;

typedef struct{
	int w, h, ani, d, if_player,jump;
	char kind[3];
	double x, y, angle;
	pic_t img[e_Ani_Total];
}ract_t;