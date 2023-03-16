#include "GV.h"
extern double rang(double ang);

extern int search_boss_shot();
//extern int search_lazer();
//extern int search_child();
extern double bossatan2();
extern double bossatan3(int k, double x, double y);//指定座標と弾との成す角
extern int move_boss_pos(double x1, double y1, double x2, double y2, double dist, int t);
extern void input_phy_pos(double x, double y, int t);
//extern void input_lphy(lazer_t* laz, int time, double angle);

//円形発射
void boss_shot_bulletH000() {
#define TM000 120
    int i, k, t = boss_shot.count % TM000, t2 = boss_shot.count;
    static int cnum;
    double angle;
    if (t2 == 0)//最初なら
        cnum = 0;
    if (t == 0) {//1周期の最初なら
        boss_shot.base_angle[0] = bossatan2();//基準と成る角度をセット
        if (cnum % 4 == 3) {//4回中4回目なら
            //40＜ｘ＜FMX-40、30＜y＜120の範囲を60の距離、60カウントで移動
            move_boss_pos(40, 30, FMX - 40, 120, 60, 60);
        }
    }
    //60カウント以下で10カウントに1回
    if (t < 60 && t % 10 == 0) {
        angle = bossatan2();//自機とボスとの成す角
        for (i = 0; i < 30; i++) {
            if ((k = search_boss_shot()) != -1) {
                boss_shot.bullet[k].col = 0;//弾の色
                boss_shot.bullet[k].x = boss.x;//座標
                boss_shot.bullet[k].y = boss.y;
                boss_shot.bullet[k].kind = 8;//弾の種類
                boss_shot.bullet[k].damage = 20;//弾のダメージ
                boss_shot.bullet[k].angle = angle + PI2 / 30 * i;//角度
                boss_shot.bullet[k].exists = 1;
                boss_shot.bullet[k].count = 0;
                boss_shot.bullet[k].speed = 3;//スピード
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
    if (t2 == 0)//最初なら
        cnum = 0;
    if (t == 0) {//1周期の最初なら
        boss_shot.base_angle[0] = bossatan2();//基準と成る角度をセット
        if (cnum % 4 == 3) {//4回中4回目なら
            //40＜ｘ＜FMX-40、30＜y＜120の範囲を60の距離、60カウントで移動
            move_boss_pos(40, 30, FMX - 40, 120, 60, 60);
        }
    }
    if (t == TM001 / 2 - 1)//周期の半分で角度を変える[k].exists
        boss_shot.base_angle[0] += PI2 / 20 / 2;
    //円形
    if (t % (TM001 / 10) == 0) {//10カウントに1回ずつ
        angle = bossatan2();//ボスと自機との成す角
        for (i = 0; i < 20; i++) {//PI2/20度ずつ1周
            if ((k = search_boss_shot()) != -1) {
                boss_shot.bullet[k].col = 4;
                boss_shot.bullet[k].x = boss.x;
                boss_shot.bullet[k].y = boss.y;
                boss_shot.bullet[k].kind = 8;
                boss_shot.bullet[k].damage = 20;//弾のダメージ
                boss_shot.bullet[k].angle = boss_shot.base_angle[0] + PI2 / 20 * i;
                boss_shot.bullet[k].exists = 1;
                boss_shot.bullet[k].count = 0;
                boss_shot.bullet[k].speed = 2.7;
                //se_flag[0] = 1;
            }
        }
    }
    //ランダム直下落下
    if (t % 4 == 0) {
        if ((k = search_boss_shot()) != -1) {
            boss_shot.bullet[k].col = 0;
            boss_shot.bullet[k].x = GetRand(FMX);
            boss_shot.bullet[k].y = GetRand(200);
            boss_shot.bullet[k].kind = 8;
            boss_shot.bullet[k].damage = 20;//弾のダメージ
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
        //40<x<FMX-40  50<y<150　の範囲で100離れた位置に80カウントで移動する
        move_boss_pos(40, 50, FMX - 40, 150, 100, 80);
    }
    //最初のランダム発射
    if (t < 180) {
        for (i = 0; i < 2; i++) {//1カウントに2回発射
            if ((k = search_boss_shot()) != -1) {
                boss_shot.bullet[k].col = GetRand(6);//7種類の色をランダムに
                boss_shot.bullet[k].x = boss.x;//発射初期座標はボスの位置
                boss_shot.bullet[k].y = boss.y;
                boss_shot.bullet[k].kind = 7;//弾の種類
                boss_shot.bullet[k].damage = 20;//弾のダメージ
                boss_shot.bullet[k].angle = rang(PI2 / 20) + PI2 / 10 * t;
                boss_shot.bullet[k].exists = 1;
                boss_shot.bullet[k].count = 0;
                boss_shot.bullet[k].speed = 3.2 + rang(2.1);
                boss_shot.bullet[k].state = 0;//弾のステータス
                boss_shot.bullet[k].kaiten = 1;//弾を回転するかどうかのフラグ
            }
        }
        //if (t % 10 == 0)
        //    se_flag[0] = 1;
    }
    //自機依存による8方向発射
    if (210 < t && t < 270 && t % 3 == 0) {
        angle = bossatan2();
        for (i = 0; i < 8; i++) {
            if ((k = search_boss_shot()) != -1) {
                boss_shot.bullet[k].col = 0;
                boss_shot.bullet[k].x = boss.x;
                boss_shot.bullet[k].y = boss.y;
                boss_shot.bullet[k].kind = 7;
                boss_shot.bullet[k].damage = 20;//弾のダメージ
                //自機とボスとの成す角を基準に８方向に発射する
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
            //tが190の時に全てストップさせ、白くし、カウントリセット
            if (boss_shot.bullet[i].state == 0) {
                if (t == 190) {
                    boss_shot.bullet[i].kaiten = 0;//弾の回転を止める
                    boss_shot.bullet[i].speed = 0;
                    boss_shot.bullet[i].col = 9;
                    boss_shot.bullet[i].count = 0;
                    boss_shot.bullet[i].state = 1;
                }
            }
            //ランダムな方向に移動し始める
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