#include <DxLib.h>
#include "input.h"

// 入力状態設定関数
void Input::SetInput() {
	// 直前入力状態の保持
	ClickStateTmp = ClickState;
	CursorPosTmp = CursorPos;
	KeyStateTmp = KeyState;
	// 入力状態の取得
	ClickState = GetMouseInput();
	GetMousePoint(&CursorPos.first, &CursorPos.second);
	GetHitKeyStateAll(&KeyState[0]);
	// 定期動作用カウントの進行
	++Cycle %= 128;
	Cycle *= KeyStateTmp == KeyState; // キーの押下状態の変化で0にする
	// 終了
	return;
}

// クリック状態取得関数
bool Input::GetClicking() {
	// 終了
	return ClickState; // クリック状態を返す
}

// クリック解除検知関数
bool Input::GetUnclick() {
	// 終了
	return ClickStateTmp && !ClickState; // クリック解除を返す
}

// カーソルX軸座標取得関数
int Input::GetCursorPosX() {
	// 終了
	return CursorPos.first; // カーソルX軸座標を返す
}

// カーソルX軸移動量取得関数
int Input::GetCursorMoveX() {
	// 終了
	return CursorPos.first - CursorPosTmp.first; // カーソルX軸移動量を返す
}

// カーソルY軸座標取得関数
int Input::GetCursorPosY() {
	// 終了
	return CursorPos.second; // カーソルY軸座標を返す
}

// カーソルY軸移動量取得関数
int Input::GetCursorMoveY() {
	// 終了
	return CursorPos.second - CursorPosTmp.second; // カーソルY軸移動量を返す
}

// 指定キー押下状態取得関数
bool Input::GetKeyPressing(const int &KeyCode) {
	// 終了
	return KeyState[KeyCode]; // 指定キー押下状態を返す
}

// 指定キー押下操作検知関数
bool Input::GetKeyPress(const int &KeyCode) {
	// 終了
	return !KeyStateTmp[KeyCode] && KeyState[KeyCode]; // 指定キー押下操作を返す
}

// 指定数字キー押下状態取得関数
bool Input::GetNumKeyPressing(const char &Num) {
	// 指定数字キー押下状態を返す
	switch(Num) {
	case '0':
		return KeyState[KEY_INPUT_NUMPAD0] || KeyState[KEY_INPUT_0];
	case '1':
		return KeyState[KEY_INPUT_NUMPAD1] || KeyState[KEY_INPUT_1];
	case '2':
		return KeyState[KEY_INPUT_NUMPAD2] || KeyState[KEY_INPUT_2];
	case '3':
		return KeyState[KEY_INPUT_NUMPAD3] || KeyState[KEY_INPUT_3];
	case '4':
		return KeyState[KEY_INPUT_NUMPAD4] || KeyState[KEY_INPUT_4];
	case '5':
		return KeyState[KEY_INPUT_NUMPAD5] || KeyState[KEY_INPUT_5];
	case '6':
		return KeyState[KEY_INPUT_NUMPAD6] || KeyState[KEY_INPUT_6];
	case '7':
		return KeyState[KEY_INPUT_NUMPAD7] || KeyState[KEY_INPUT_7];
	case '8':
		return KeyState[KEY_INPUT_NUMPAD8] || KeyState[KEY_INPUT_8];
	case '9':
		return KeyState[KEY_INPUT_NUMPAD9] || KeyState[KEY_INPUT_9];
	case '-':
		return KeyState[KEY_INPUT_SUBTRACT] || KeyState[KEY_INPUT_MINUS];
	}
	// 終了
	return false; // 該当が無ければfalseを返す
}

// WSADキー押下状態取得関数
bool Input::GetWSADPressing() {
	// 終了
	return KeyState[KEY_INPUT_W] || KeyState[KEY_INPUT_S] || KeyState[KEY_INPUT_A] || KeyState[KEY_INPUT_D]; // WSADキー押下状態を返す
}

// WSキー押下状態取得関数
int Input::GetWSMove() {
	// 終了
	return KeyState[KEY_INPUT_W] - KeyState[KEY_INPUT_S]; // WSキー押下状態を返す
}

// ADキー押下状態取得関数
int Input::GetADMove() {
	// 終了
	return KeyState[KEY_INPUT_A] - KeyState[KEY_INPUT_D]; // ADキー押下状態を返す
}

// 上下キー押下状態取得関数
int Input::GetUDMove() {
	// 終了
	return KeyState[KEY_INPUT_UP] - KeyState[KEY_INPUT_DOWN]; // 上下キー押下状態を返す
}

// 左右キー押下状態取得関数
int Input::GetLRMove() {
	// 終了
	return KeyState[KEY_INPUT_LEFT] - KeyState[KEY_INPUT_RIGHT]; // 左右キー押下状態を返す
}

// 指定矩形範囲内カーソル有無関数
bool Input::CursorInBox(const int &x1, const int &y1, const int &x2, const int &y2) {
	// 終了
	return CursorPos.first >= x1 && CursorPos.second >= y1 && CursorPos.first < x2 &&CursorPos.second < y2; // 指定矩形範囲内のカーソル有無を返す
}

// 指定円形範囲内カーソル有無関数
bool Input::CursorInCircle(const int &x, const int &y, const int &r) {
	// 終了
	return (CursorPos.first - x) * (CursorPos.first - x) + (CursorPos.second - y) * (CursorPos.second - y) < r * r; // 指定円形範囲内のカーソル有無を返す
}

// 終了操作関数
bool Input::ExitOperation() {
	// 終了
	return ProcessMessage() || KeyState[KEY_INPUT_ESCAPE]; // 終了操作を返す
}