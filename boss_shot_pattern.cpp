#include "GV.h"
extern double rang(double ang);

extern int search_boss_shot();
//extern int search_lazer();
//extern int search_child();
extern double bossatan2();
extern double bossatan3(int k, double x, double y);//�w����W�ƒe�Ƃ̐����p
extern int move_boss_pos(double x1, double y1, double x2, double y2, double dist, int t);
extern void input_phy_pos(double x, double y, int t);
//extern void input_lphy(lazer_t* laz, int time, double angle);

//�~�`����
void boss_shot_bulletH000() {
#define TM000 120
    int i, k, t = boss_shot.count % TM000, t2 = boss_shot.count;
    static int cnum;
    double angle;
    if (t2 == 0)//�ŏ��Ȃ�
        cnum = 0;
    if (t == 0) {//1�����̍ŏ��Ȃ�
        boss_shot.base_angle[0] = bossatan2();//��Ɛ���p�x���Z�b�g
        if (cnum % 4 == 3) {//4��4��ڂȂ�
            //40������FMX-40�A30��y��120�͈̔͂�60�̋����A60�J�E���g�ňړ�
            move_boss_pos(40, 30, FMX - 40, 120, 60, 60);
        }
    }
    //60�J�E���g�ȉ���10�J�E���g��1��
    if (t < 60 && t % 10 == 0) {
        angle = bossatan2();//���@�ƃ{�X�Ƃ̐����p
        for (i = 0; i < 30; i++) {
            if ((k = search_boss_shot()) != -1) {
                boss_shot.bullet[k].col = 0;//�e�̐F
                boss_shot.bullet[k].x = boss.x;//���W
                boss_shot.bullet[k].y = boss.y;
                boss_shot.bullet[k].kind = 8;//�e�̎��
                boss_shot.bullet[k].damage = 20;//�e�̃_���[�W
                boss_shot.bullet[k].angle = angle + PI2 / 30 * i;//�p�x
                boss_shot.bullet[k].exists = 1;
                boss_shot.bullet[k].count = 0;
                boss_shot.bullet[k].speed = 3;//�X�s�[�h
                //se_flag[0] = 1;
            }
        }
    }
        //for(i=0;i<BOSS_BULLET_MAX;i++){
        //    if(boss_shot.bullet[i].flag>0){
        //
        //    }
        //}
    if (t == TM000 - 1)
        cnum++;
}


void boss_shot_bulletH001() {
#define TM001 60
    int i, k, t = boss_shot.count % TM001, t2 = boss_shot.count;
    static int cnum;
    double angle;
    if (t2 == 0)//�ŏ��Ȃ�
        cnum = 0;
    if (t == 0) {//1�����̍ŏ��Ȃ�
        boss_shot.base_angle[0] = bossatan2();//��Ɛ���p�x���Z�b�g
        if (cnum % 4 == 3) {//4��4��ڂȂ�
            //40������FMX-40�A30��y��120�͈̔͂�60�̋����A60�J�E���g�ňړ�
            move_boss_pos(40, 30, FMX - 40, 120, 60, 60);
        }
    }
    if (t == TM001 / 2 - 1)//�����̔����Ŋp�x��ς���[k].exists
        boss_shot.base_angle[0] += PI2 / 20 / 2;
    //�~�`
    if (t % (TM001 / 10) == 0) {//10�J�E���g��1�񂸂�
        angle = bossatan2();//�{�X�Ǝ��@�Ƃ̐����p
        for (i = 0; i < 20; i++) {//PI2/20�x����1��
            if ((k = search_boss_shot()) != -1) {
                boss_shot.bullet[k].col = 4;
                boss_shot.bullet[k].x = boss.x;
                boss_shot.bullet[k].y = boss.y;
                boss_shot.bullet[k].kind = 8;
                boss_shot.bullet[k].damage = 20;//�e�̃_���[�W
                boss_shot.bullet[k].angle = boss_shot.base_angle[0] + PI2 / 20 * i;
                boss_shot.bullet[k].exists = 1;
                boss_shot.bullet[k].count = 0;
                boss_shot.bullet[k].speed = 2.7;
                //se_flag[0] = 1;
            }
        }
    }
    //�����_����������
    if (t % 4 == 0) {
        if ((k = search_boss_shot()) != -1) {
            boss_shot.bullet[k].col = 0;
            boss_shot.bullet[k].x = GetRand(FMX);
            boss_shot.bullet[k].y = GetRand(200);
            boss_shot.bullet[k].kind = 8;
            boss_shot.bullet[k].damage = 20;//�e�̃_���[�W
            boss_shot.bullet[k].angle = PI / 2;
            boss_shot.bullet[k].exists = 1;
            boss_shot.bullet[k].count = 0;
            boss_shot.bullet[k].speed = 1 + rang(0.5);
            //se_flag[0] = 1;
        }
    }
    //    for(i=0;i<BOSS_BULLET_MAX;i++){
    //        if(boss_shot.bullet[i].flag>0){
    //
    //        }
    //    }
    if (t == TM001 - 1)
        cnum++;
}


void boss_shot_bulletH002() {
#define TM002 650
    int i, k, t = boss_shot.count % TM002;
    double angle;
    if (t == 0 || t == 210) {
        //40<x<FMX-40  50<y<150�@�͈̔͂�100���ꂽ�ʒu��80�J�E���g�ňړ�����
        move_boss_pos(40, 50, FMX - 40, 150, 100, 80);
    }
    //�ŏ��̃����_������
    if (t < 180) {
        for (i = 0; i < 2; i++) {//1�J�E���g��2�񔭎�
            if ((k = search_boss_shot()) != -1) {
                boss_shot.bullet[k].col = GetRand(6);//7��ނ̐F�������_����
                boss_shot.bullet[k].x = boss.x;//���ˏ������W�̓{�X�̈ʒu
                boss_shot.bullet[k].y = boss.y;
                boss_shot.bullet[k].kind = 7;//�e�̎��
                boss_shot.bullet[k].damage = 20;//�e�̃_���[�W
                boss_shot.bullet[k].angle = rang(PI2 / 20) + PI2 / 10 * t;
                boss_shot.bullet[k].exists = 1;
                boss_shot.bullet[k].count = 0;
                boss_shot.bullet[k].speed = 3.2 + rang(2.1);
                boss_shot.bullet[k].state = 0;//�e�̃X�e�[�^�X
                boss_shot.bullet[k].kaiten = 1;//�e����]���邩�ǂ����̃t���O
            }
        }
        //if (t % 10 == 0)
        //    se_flag[0] = 1;
    }
    //���@�ˑ��ɂ��8��������
    if (210 < t && t < 270 && t % 3 == 0) {
        angle = bossatan2();
        for (i = 0; i < 8; i++) {
            if ((k = search_boss_shot()) != -1) {
                boss_shot.bullet[k].col = 0;
                boss_shot.bullet[k].x = boss.x;
                boss_shot.bullet[k].y = boss.y;
                boss_shot.bullet[k].kind = 7;
                boss_shot.bullet[k].damage = 20;//�e�̃_���[�W
                //���@�ƃ{�X�Ƃ̐����p����ɂW�����ɔ��˂���
                boss_shot.bullet[k].angle = angle - PI / 2 * 0.8 + PI * 0.8 / 7 * i + rang(PI / 180);
                boss_shot.bullet[k].exists = 1;
                boss_shot.bullet[k].count = 0;
                boss_shot.bullet[k].speed = 3.0 + rang(0.3);
                boss_shot.bullet[k].state = 2;
                boss_shot.bullet[k].kaiten = 1;
            }
        }
        //if (t % 10 == 0)
        //    se_flag[0] = 1;
    }
    for (i = 0; i < BOSS_BULLET_MAX; i++) {
        if (boss_shot.bullet[i].exists == TRUE) {
            //t��190�̎��ɑS�ăX�g�b�v�����A�������A�J�E���g���Z�b�g
            if (boss_shot.bullet[i].state == 0) {
                if (t == 190) {
                    boss_shot.bullet[i].kaiten = 0;//�e�̉�]���~�߂�
                    boss_shot.bullet[i].speed = 0;
                    boss_shot.bullet[i].col = 9;
                    boss_shot.bullet[i].count = 0;
                    boss_shot.bullet[i].state = 1;
                }
            }
            //�����_���ȕ����Ɉړ����n�߂�
            if (boss_shot.bullet[i].state == 1) {
                if (boss_shot.bullet[i].count == 200) {
                    boss_shot.bullet[i].angle = rang(PI);
                    boss_shot.bullet[i].kaiten = 1;
                }
                if (boss_shot.bullet[i].count > 200)
                    boss_shot.bullet[i].speed += 0.01;
            }
        }
    }
}