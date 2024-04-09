#pragma once
#include <string>

// ボタン（ＵＩ）クラス
class Button {
public:
	Button(); // コンストラクタ
	bool DrawButton(const int &x, const int &y, const char *ButtonName) const; // ボタン描画関数
	bool DrawRadioButton(const int &x, const int &y, const char *ButtonName, const bool &Selecting) const; // ラジオボタン描画関数
	bool DrawSlider(const int &x, const int &y, const int &MinValue, const int &MaxValue, int &Value) const; // スライダー描画関数
	bool DrawTextBox(const int &x, const int &y, std::string &ValueStr, bool &Selecting, int &CursorPos) const; // テキストボックス描画関数
private:
	int ButtonOFFGraphHandle; // ボタングラフハンドル
	int ButtonONGraphHandle; // 選択中ボタングラフハンドル
	int RButtonOFFGraphHandle; // ラジオボタングラフハンドル
	int RButtonONGraphHandle; // 選択中ラジオボタングラフハンドル
	int PushSoundHandle; // 押下サウンドハンドル https://dova-s.jp/se/play478.html
	int FontHandle; // フォントハンドル
};