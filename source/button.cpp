#include <algorithm>
#include <DxLib.h>
#include "button.h"
#include "input.h"

// コンストラクタ
Button::Button() {
	// メンバ変数の初期化
	Input::Cycle = 0;
	// 画像の読込
	ButtonOFFGraphHandle = LoadGraph("graphs\\button.png"); // ボタン
	ButtonONGraphHandle = LoadGraph("graphs\\selecting_button.png"); // 選択中ボタン
	RButtonOFFGraphHandle = LoadGraph("graphs\\radio_button.png"); // ラジオラジオ
	RButtonONGraphHandle = LoadGraph("graphs\\selecting_radio_button.png"); // 選択中ラジオボタン
	// 音声の読込
	PushSoundHandle = LoadSoundMem("sounds\\push_sound.mp3", 1);
	// フォントの生成
	FontHandle = CreateFontToHandle(NULL, 72, 2);
	// 終了
	return;
}

// ボタン描画関数
bool Button::DrawButton(const int &x, const int &y, const char *ButtonName) const {
	// ボタンの描画
	DrawGraph(x, y, ButtonOFFGraphHandle, TRUE);
	// ボタン名の描画
	const int Offset = (320 - GetDrawStringWidthToHandle(ButtonName, static_cast<int>(strlen(ButtonName)), FontHandle)) / 2;
	DrawStringToHandle(x + Offset, y + 24, ButtonName, GetColor(0, 0, 0), FontHandle);
	// ボタンクリックの判定
	if(Input::CursorInBox(x, y, x + 320, y + 120)) { // ボタン上にカーソルが有る時
		if(Input::GetClicking()) { // クリック中
			// ボタン明度の上昇
			SetDrawBlendMode(DX_BLENDMODE_ADD, 64);
			DrawGraph(x, y, ButtonONGraphHandle, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		} else if(Input::GetUnclick()) { // クリック解除時
			// 押下音の再生
			ChangeNextPlayVolumeSoundMem(128, PushSoundHandle);
			PlaySoundMem(PushSoundHandle, DX_PLAYTYPE_BACK);
			// 終了
			return true;
		}
	}
	// 終了
	return false;
}

// ラジオボタン描画関数
bool Button::DrawRadioButton(const int &x, const int &y, const char *ButtonName, const bool &Selecting) const {
	// ボタンの描画
	DrawGraph(x, y, Selecting ? RButtonONGraphHandle : RButtonOFFGraphHandle, TRUE);
	// ボタン名の描画
	DrawString(x + 30, y + 5, ButtonName, GetColor(255, 255, 255));
	// ボタンクリックの判定
	if(!Selecting && Input::CursorInCircle(x + 12, y + 12, 12) && Input::GetUnclick()) return true; // ボタン上をクリックした時
	// 終了
	return false;
}

// スライダー描画関数
bool Button::DrawSlider(const int &x, const int &y, const int &MinValue, const int &MaxValue, int &Value) const {
	// スライダーの描画
	int Pos = x + 120 / (MaxValue - MinValue) * (Value - MinValue);
	DrawBox(x + 4, y + 10, x + 124, y + 14, GetColor(128, 128, 128), TRUE);
	DrawBox(x + 4, y + 10, Pos, y + 14, GetColor(255, 255, 255), TRUE);
	DrawBox(Pos, y + 4, Pos + 8, y + 20, GetColor(255, 255, 255), TRUE);
	// 値の描画
	DrawFormatString(x + 134, y + 4, GetColor(255, 255, 255), "%d", Value);
	// スライダーの操作
	if(Input::CursorInBox(x, y + 4, x + 128, y + 20) && Input::GetClicking()) {
		// 操作を反映
		DrawBox(Pos, y + 4, Pos + 8, y + 20, GetColor(255, 128, 0), FALSE);
		Value = std::clamp(Value + (Input::GetCursorPosX() - Pos - 4) / 4, MinValue, MaxValue);
		// 終了
		return true;
	}
	// 終了
	return false;
}

// テキストボックス描画関数
bool Button::DrawTextBox(const int &x, const int &y, std::string &ValueStr, bool &Selecting, int &CursorPos) const {
	// テキストボックスの描画
	DrawBox(x + 4, y + 2, x + 124, y + 22, GetColor(255, 255, 255), TRUE);
	// テキストボックスの選択中判定
	if(Input::GetUnclick()) Selecting = Input::CursorInBox(x + 4, y + 2, x + 124, y + 22); // テキストボックス上をクリックすると選択中にする
	// 値の描画
	if(ValueStr.empty() && !Selecting) DrawString(x + 14, y + 4, "シードを入力", GetColor(128, 128, 128)); // 入力文字列が空の時
	else DrawFormatString(x + 14, y + 4, GetColor(0, 0, 0), "%11s", ValueStr.c_str());
	// 値の書換
	if(Selecting) { // テキストボックス選択中
		// 選択中表示
		DrawBox(x + 4, y + 2, x + 124, y + 22, GetColor(255, 128, 0), FALSE); // 橙色の枠を表示
		// カーソル表示
		if(Input::Cycle < 64) DrawLine(x - CursorPos * 9 + 112, y + 4, x - CursorPos * 9 + 112, y + 19, GetColor(0, 0, 0));
		// テキストボックスの操作
		if(!Input::Cycle) { // キーの押下中に連続で動作される間隔を空ける
			// カーソルの移動
			CursorPos += Input::GetLRMove();
			CursorPos = std::clamp(CursorPos, 0, static_cast<int>(ValueStr.length())); // カーソル移動範囲の制限
			// 文字列の操作
			if(CursorPos == ValueStr.length() && ValueStr[0] != '-' && Input::GetNumKeyPressing('-')) ValueStr.insert(ValueStr.begin(), '-'); // 符号を入力
			if(CursorPos < ValueStr.length() || ValueStr[0] != '-') for(char Num = '0'; Num <= '9'; ++Num) if(Input::GetNumKeyPressing(Num)) ValueStr.insert(ValueStr.end() - CursorPos, Num); // 数字を入力
			if(CursorPos < ValueStr.length() && Input::GetKeyPressing(KEY_INPUT_BACK)) ValueStr.erase(ValueStr.length() - CursorPos - 1, 1); // 一文字削除
			if(ValueStr.length() > 10 && ValueStr[0] == '0') ValueStr.erase(0, 1); // 正の値の桁数を10桁に制限
			else if(ValueStr.length() > 11 && ValueStr[1] == '0') ValueStr.erase(1, 1); // 負の値の桁数を10桁に制限
		}
		// 終了
		return true;
	}
	// 終了
	return false;
}