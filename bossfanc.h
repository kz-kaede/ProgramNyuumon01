#pragma once
extern void boss_shot_bulletH000();
extern void boss_shot_bulletH001();
extern void boss_shot_bulletH002();

//関数ポインタの配列にboss_shot_bullet関数のアドレスを代入
void (*boss_shot_bullet[DANMAKU_MAX])() =
{
    //中ボス
            boss_shot_bulletH000,//ノーマル
            boss_shot_bulletH002,//スペル～パーフェクトフリーズ～
    //ラスボス
            boss_shot_bulletH001,//ノーマル～サイレントセレナ～
    //終り

            boss_shot_bulletH000,//ぬるぽ回避用(この弾幕は出てこない)
};
