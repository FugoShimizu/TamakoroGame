#include "input.hpp"
#include <DxLib.h>

/**
 * 入力状態設定関数
 */
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
	++Cycle &= 0X7F; // 128 で循環
	Cycle *= KeyStateTmp == KeyState; // キーの押下状態の変化で 0 にする
	// 終了
	return;
}

/**
 * クリック状態取得関数
 * @return クリック状態
 */
bool Input::GetClicking() {
	// クリック状態の返戻
	return ClickState;
}

/**
 * クリック解除検知関数
 * @return クリック解除
 */
bool Input::GetUnclick() {
	// クリック解除の返戻
	return ClickStateTmp && !ClickState;
}

/**
 * カーソルＸ軸座標取得関数
 * @return カーソルＸ軸座標
 */
int Input::GetCursorPosX() {
	// カーソルＸ軸座標の返戻
	return CursorPos.first;
}

/**
 * カーソルＸ軸移動量取得関数
 * @return カーソルＸ軸移動量
 */
int Input::GetCursorMoveX() {
	// カーソルＸ軸移動量の返戻
	return CursorPos.first - CursorPosTmp.first;
}

/**
 * カーソルＹ軸座標取得関数
 * @return カーソルＹ軸座標
 */
int Input::GetCursorPosY() {
	// カーソルＹ軸座標の返戻
	return CursorPos.second;
}

/**
 * カーソルＹ軸移動量取得関数
 * @return カーソルＹ軸移動量
 */
int Input::GetCursorMoveY() {
	// カーソルＹ軸移動量の返戻
	return CursorPos.second - CursorPosTmp.second;
}

/**
 * 指定キー押下状態取得関数
 * @param KeyCode 判定するキーコード（0≦KeyCode＜256）
 * @return 指定キー押下状態
 */
bool Input::GetKeyPressing(const int KeyCode) {
	// 指定キー押下状態の返戻
	return KeyState[KeyCode];
}

/**
 * 指定キー押下操作検知関数
 * @param KeyCode 判定するキーコード（0≦KeyCode＜256）
 * @return 指定キー押下操作
 */
bool Input::GetKeyPress(const int KeyCode) {
	// 指定キー押下操作の返戻
	return !KeyStateTmp[KeyCode] && KeyState[KeyCode];
}

/**
 * 指定数字キー押下状態取得関数
 * @param Num 判定する数字（'0'〜'9' 又は '-'）
 * @return 指定数字キー押下状態
 */
bool Input::GetNumKeyPressing(const char Num) {
	// 指定数字キー押下状態の返戻
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
	default:
		return false;
	}
}

/**
 * ＷＡＳＤキー押下状態取得関数
 * @return ＷＡＳＤキー押下状態
 */
bool Input::GetWASDPressing() {
	// ＷＡＳＤキー押下状態の返戻
	return KeyState[KEY_INPUT_W] || KeyState[KEY_INPUT_S] || KeyState[KEY_INPUT_A] || KeyState[KEY_INPUT_D];
}

/**
 * ＷＳキー押下状態取得関数
 * @return ＷＳキー押下状態
 */
int Input::GetWSMove() {
	// ＷＳキー押下状態の返戻
	return KeyState[KEY_INPUT_W] - KeyState[KEY_INPUT_S];
}

/**
 * ＡＤキー押下状態取得関数
 * @return ＡＤキー押下状態
 */
int Input::GetADMove() {
	// ＡＤキー押下状態の返戻
	return KeyState[KEY_INPUT_A] - KeyState[KEY_INPUT_D];
}

/**
 * 上下キー押下状態取得関数
 * @return 上下キー押下状態
 */
int Input::GetUDMove() {
	// 上下キー押下状態の返戻
	return KeyState[KEY_INPUT_UP] - KeyState[KEY_INPUT_DOWN];
}

/**
 * 左右キー押下状態取得関数
 * @return 左右キー押下状態
 */
int Input::GetLRMove() {
	// 左右キー押下状態の返戻
	return KeyState[KEY_INPUT_LEFT] - KeyState[KEY_INPUT_RIGHT];
}

/**
 * 指定矩形範囲内カーソル有無関数
 * @param X1 矩形左上のＸ座標（≧0）
 * @param Y1 矩形左上のＹ座標（≧0）
 * @param X2 矩形右下のＸ座標（＞X1）
 * @param Y2 矩形右下のＹ座標（＞Y1）
 * @return 指定矩形範囲内のカーソル有無
 */
bool Input::IsCursorInBox(const int X1, const int Y1, const int X2, const int Y2) {
	// 指定矩形範囲内のカーソル有無の返戻
	return CursorPos.first >= X1 && CursorPos.second >= Y1 && CursorPos.first < X2 && CursorPos.second < Y2;
}

/**
 * 指定円形範囲内カーソル有無関数
 * @param X 円中心のＸ座標（≧0）
 * @param Y 円中心のＹ座標（≧0）
 * @param R 円の半径（≧0）
 * @return 指定円形範囲内のカーソル有無
 */
bool Input::IsCursorInCircle(const int X, const int Y, const int R) {
	// 中心からの変位
	const int OffsetX = CursorPos.first - X, OffsetY = CursorPos.second - Y;
	// 指定円形範囲内のカーソル有無の返戻
	return OffsetX * OffsetX + OffsetY * OffsetY < R * R;
}

/**
 * 終了操作関数
 * @return 終了操作
 */
bool Input::ExitOperation() {
	// 終了操作の返戻
	return ProcessMessage() || KeyState[KEY_INPUT_ESCAPE];
}
