#pragma once
extern void boss_shot_bulletH000();
extern void boss_shot_bulletH001();
extern void boss_shot_bulletH002();

//�֐��|�C���^�̔z���boss_shot_bullet�֐��̃A�h���X����
void (*boss_shot_bullet[DANMAKU_MAX])() =
{
    //���{�X
            boss_shot_bulletH000,//�m�[�}��
            boss_shot_bulletH002,//�X�y���`�p�[�t�F�N�g�t���[�Y�`
    //���X�{�X
            boss_shot_bulletH001,//�m�[�}���`�T�C�����g�Z���i�`
    //�I��

            boss_shot_bulletH000,//�ʂ�ۉ��p(���̒e���͏o�Ă��Ȃ�)
};
