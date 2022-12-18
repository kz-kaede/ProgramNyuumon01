#include "DxLib.h"

static int Key[256];

// �L�[�̓��͏�Ԃ��擾�E�X�V����
int UpdateKeyState() {
	char tmpKey[256]; // ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll(tmpKey); // �S�ẴL�[�̓��͏�Ԃ𓾂�
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) { // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			Key[i]++;     // ���Z
		}
		else {              // ������Ă��Ȃ����
			Key[i] = 0;   // 0�ɂ���
		}
	}
	return 0;
}

// KeyCode�̃L�[�̓��͏�Ԃ��擾����
int GetKey(int KeyCode) {
	return Key[KeyCode]; // KeyCode�̓��͏�Ԃ�Ԃ�
}