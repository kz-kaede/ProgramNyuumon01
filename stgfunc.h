#pragma once

//stg_main.cpp
GLOBAL void PrintDebug();

//draw_main.cpp
GLOBAL void draw_main();

//player.cpp
GLOBAL void calc_player();
GLOBAL void player_move();
GLOBAL void draw_player();
//GLOBAL void collision_player_to_enemy();

//player_shot.cpp
GLOBAL void pshot_main();
GLOBAL void enter_shot();
GLOBAL int search_pshot();
GLOBAL void ch0_shot_pattern();
GLOBAL void ch1_shot_pattern();
GLOBAL void calc_pshot();
GLOBAL void draw_pshot();


//boss.cpp
GLOBAL void hit_boss();
GLOBAL void input_phy_pos(double x, double y, int t);
GLOBAL int move_boss_pos(double x1, double y1, double x2, double y2, double dist, int t);
GLOBAL double bossatan2();
GLOBAL double bossatan3(int k, double x,double y);
GLOBAL void input_phy(int t);
GLOBAL void calc_phy();
GLOBAL void enter_boss(int num);
GLOBAL void wait_and_enter();
GLOBAL void calc_boss();
GLOBAL void draw_boss();

//boss_shot.cpp
GLOBAL void boss_shot_main();
GLOBAL void enter_boss_shot();
GLOBAL int search_boss_shot();
GLOBAL void boss_shot_calc();
GLOBAL void draw_bullet();


//boss.cpp
//GLOBAL void boss_move();
//GLOBAL void draw_boss();

//collision_main.cpp
GLOBAL void collision_main();
GLOBAL int collision_judge(double x1, double y1, double x2, double y2,
	double range1,double range2,double spd1, double angle1);
GLOBAL void collision_pshot_to_enemy();
GLOBAL int collision_pshot_to_boss(int i);
GLOBAL int collision_enemyshot_to_player(int s, int n);
GLOBAL int collision_bossshot_to_player(int n);
GLOBAL void collision_enemyshot_to_player();
GLOBAL void collision_enemy_to_player();
GLOBAL int collision_block_to_player();
//GLOBAL void hit_enemy(int s, int damage)
GLOBAL void hit_boss(int damage);
GLOBAL void hit_player(int damage);


//draw_back_main.cpp
GLOBAL void draw_back_main();


//status.cpp
GLOBAL void player_hp_bar();
GLOBAL void boss_hp_bar();

//gameset.cpp
GLOBAL void judge_gameset();

//fps.cpp
GLOBAL void FpsTimeFanction();
