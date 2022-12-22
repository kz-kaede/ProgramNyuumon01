#include "GV.h"
#include "scene.h"

int back_knd[DANMAKU_MAX] = {
	0,1,0,1,1,
};
int boss_hp[DANMAKU_MAX] = {
	4000,6000,10000,5000,3000,
};

//������
void Game_Initialize() {
	stage_count = 1;
	memset(&p, 0, sizeof(player_t));
	memset(&e, 0, sizeof(enemy_t));
	memset(&pshot, 0, sizeof(pshot_t));
	memset(&eshot, 0, sizeof(eshot_t));
	memset(&boss, 0, sizeof(boss_t));
	memset(&boss_shot, 0, sizeof(boss_shot_t));

	game_load_stage();
	game_load_img();
	game_load_sound();

	p.hp_max = 300;
	p.hp = p.hp_max;
	p.x = 200;
	p.y = 350;
	p.phy.ax = 0.1;
	p.speed = 8;
	p.jump_state = e_falling;

	e.hp_max = 1000;
	e.hp = e.hp_max;
	e.x = 200;
	e.y = 360;

	boss.appear_count[0] = 160;//���{�X���o�����鎞��(42)(47)
	boss.danmaku_num[0] = 2;//���{�X�����ڂ܂ł̒e�����o����
	boss.danmaku_num[1] = 4;//�Ō�ɏo��{�X�����ڂ܂ł̒e�����o����(47)

	for (int i = 0; i < DANMAKU_MAX; i++) {//�e�����ꂼ���HP(47)
		boss.set_hp[i] = boss_hp[i];
	}
	boss.hp_max = boss.set_hp[0];


	bright_set.brt = 255;//�����P�x�͍ő�

}

//�I������
void Game_Finalize() {
	//clsDx();
	game_clear_img();
	game_clear_sound();
}

//�X�V
void Game_Update() {
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) { //Esc�L�[��������Ă�����
		SceneMgr_ChangeScene(eScene_Menu);//�V�[�������j���[�ɕύX
	}
}

//�Q�[�����C��
void Game_Main() {
	clsDx();			//�ȈՕ����o�͂̃��Z�b�g
	//DrawString(0, 0, "�Q�[����ʂł��B", GetColor(255, 255, 255));


	player_move();//�v���C���[�̈ړ�
	boss_shot_main();//�{�X�V���b�g���C��
	pshot_main();//���@�V���b�g���C��

	collision_main();//�����蔻��

	calc_player();
	hit_boss();

	draw_main();//�`�惁�C��
	judge_gameset();//���s


	if (boss.exists == 0)
		stage_count++;
	FpsTimeFanction();

	SetFontSize(18);
	DrawString(0, 0, "Esc�L�[�������ƃ��j���[��ʂɖ߂�܂��B", GetColor(255, 255, 255));
	PrintDebug();
}


//----------------------------------
// �f�o�b�O���
//----------------------------------
void PrintDebug(void) {
	printfDx("\n\n\n\n");
	printfDx("player = %d\tp.state = %d\tp.phy.vx = %d\np.muteki_count = %d\tjump_state = %d\n",
		p.hp, p.state,(int)p.phy.vx, p.muteki_count,p.jump_state);
	printfDx("boss.x %d\tboss.y %d\tboss_hp %d\n", (int)e.x, (int)e.y, boss.hp);
	printfDx("boss.phy.flag %d\tboss.phy.count %d\tboss.phy.set_t %d\n", boss.phy.flag, boss.phy.count, boss.phy.set_t);
	printfDx("p.x %d\tp.y %d\tp_hp %d\n", (int)p.x, (int)p.y, p.hp);
	printfDx("boss.kind %d\n", boss.kind);
	//printfDx("boss_state %d\n", boss.state);
	//printfDx("boss_knd %d\n", boss.kind);
	//printfDx("boss_shot.count %d\n", boss_shot.count);
	printfDx("boss_endtime %d\n", boss.endtime);
	//printfDx("boss_shot.isSet %d\n", boss_shot.isSet);
	printfDx("%s\n", Ver);
	printfDx("r:%d g:%d b:%d\n", col.r, col.g, col.b);
	printfDx("sWidth:%d sHeight:%d\n", STAGE_WIDTH,STAGE_HEIGHT);
	printfDx("---%s\n", b_kind[1][0].type);
	printfDx("x:%d y:%d\n", (int)Block[4].x, (int)Block[4].y);
}

