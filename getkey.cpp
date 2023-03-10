#include "DxLib.h"

static int Key[256];

// キーの入力状態を取得・更新する
int UpdateKeyState() {
	char tmpKey[256]; // 現在のキーの入力状態を格納する
	GetHitKeyStateAll(tmpKey); // 全てのキーの入力状態を得る
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) { // i番のキーコードに対応するキーが押されていたら
			Key[i]++;     // 加算
		}
		else {              // 押されていなければ
			Key[i] = 0;   // 0にする
		}
	}
	return 0;
}

// KeyCodeのキーの入力状態を取得する
int GetKey(int KeyCode) {
	return Key[KeyCode]; // KeyCodeの入力状態を返す
}