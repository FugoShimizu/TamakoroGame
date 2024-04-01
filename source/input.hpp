#pragma once

#include <array>
#include <utility>

// 入力クラス
class Input {
private:

	static inline bool ClickState = false; // 左クリック状態
	static inline bool ClickStateTmp = false; // 直前の左クリック状態
	static inline std::pair<int, int> CursorPos; // カーソル位置（first: Ｘ座標，second: Ｙ座標）
	static inline std::pair<int, int> CursorPosTmp; // 直前のカーソル位置（first: Ｘ座標，second: Ｙ座標）
	static inline std::array<char, 256> KeyState; // 各キー押下状態
	static inline std::array<char, 256> KeyStateTmp; // 直前の各キー押下状態

public:

	static inline unsigned int Cycle = 0; // 定期動作用カウント
	static void SetInput(); // 入力状態設定関数
	static bool GetClicking(); // クリック状態取得関数
	static bool GetUnclick(); // クリック解除検知関数
	static int GetCursorPosX(); // カーソルＸ軸座標取得関数
	static int GetCursorMoveX(); // カーソルＸ軸移動量取得関数
	static int GetCursorPosY(); // カーソルＹ軸座標取得関数
	static int GetCursorMoveY(); // カーソルＹ軸移動量取得関数
	static bool GetKeyPressing(const int KeyCode); // 指定キー押下状態取得関数
	static bool GetKeyPress(const int KeyCode); // 指定キー押下操作検知関数
	static bool GetNumKeyPressing(const char Num); // 指定数字キー押下状態取得関数
	static bool GetWASDPressing(); // ＷＡＳＤキー押下状態取得関数
	static int GetWSMove(); // ＷＳキー押下状態取得関数
	static int GetADMove(); // ＡＤキー押下状態取得関数
	static int GetUDMove(); // 上下キー押下状態取得関数
	static int GetLRMove(); // 左右キー押下状態取得関数
	static bool IsCursorInBox(const int X1, const int Y1, const int X2, const int Y2); // 指定矩形範囲内カーソル有無関数
	static bool IsCursorInCircle(const int X, const int Y, const int R); // 指定円形範囲内カーソル有無関数
	static bool ExitOperation(); // 終了操作関数
};
