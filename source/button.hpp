#pragma once

#include <string>

// ボタン（ＵＩ）クラス
class Button {
private:

	int ButtonOFFGraphHandle = -1; // ボタングラフハンドル
	int ButtonONGraphHandle = -1; // 選択中ボタングラフハンドル
	int RButtonOFFGraphHandle = -1; // ラジオボタングラフハンドル
	int RButtonONGraphHandle = -1; // 選択中ラジオボタングラフハンドル
	int PushSoundHandle = -1; // 押下サウンドハンドル https://dova-s.jp/se/play478.html
	int FontHandle = -1; // フォントハンドル

public:

	bool DrawButton(const int X, const int Y, const char *ButtonName) const; // ボタン描画関数
	bool DrawRadioButton(const int X, const int Y, const char *ButtonName, const bool Selecting) const; // ラジオボタン描画関数
	bool DrawSlider(const int X, const int Y, const int MinValue, const int MaxValue, int &Value) const; // スライダー描画関数
	bool DrawTextBox(const int X, const int Y, std::string &ValueStr, bool &Selecting, int &CursorPos) const; // テキストボックス描画関数

	Button &operator=(const Button &) = delete; // コピー代入演算子（禁止）
	Button(const Button &) = delete; // コピーコンストラクタ（禁止）

	Button(); // コンストラクタ
	~Button(); // デストラクタ
};
