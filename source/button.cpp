#include "button.hpp"
#include "input.hpp"
#include <DxLib.h>
#include <algorithm>

/**
 * ボタン描画関数
 * @param X ボタンのＸ座標（≧0）
 * @param Y ボタンのＹ座標（≧0）
 * @param ButtonName ボタン名
 * @return ボタンがクリックされたか
 */
bool Button::DrawButton(const int X, const int Y, const char *ButtonName) const {
	// ボタンの描画
	DrawGraph(X, Y, ButtonOFFGraphHandle, TRUE);
	// ボタン名の描画
	const int Offset = (320 - GetDrawStringWidthToHandle(ButtonName, static_cast<int>(strlen(ButtonName)), FontHandle)) / 2;
	DrawStringToHandle(X + Offset, Y + 24, ButtonName, GetColor(0, 0, 0), FontHandle);
	// ボタンクリックの判定
	if(Input::IsCursorInBox(X, Y, X + 320, Y + 120)) { // ボタン上にカーソルが有る時
		if(Input::GetClicking()) { // クリック中
			// ボタン明度の上昇
			SetDrawBlendMode(DX_BLENDMODE_ADD, 64);
			DrawGraph(X, Y, ButtonONGraphHandle, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		} else if(Input::GetUnclick()) { // クリック解除時
			// 押下音の再生
			ChangeNextPlayVolumeSoundMem(128, PushSoundHandle);
			PlaySoundMem(PushSoundHandle, DX_PLAYTYPE_BACK);
			// クリックの返戻
			return true;
		}
	}
	// 未クリックの返戻
	return false;
}

/**
 * ラジオボタン描画関数
 * @param X ボタンのＸ座標（≧0）
 * @param Y ボタンのＹ座標（≧0）
 * @param ButtonName ボタン名
 * @param Selecting 選択中か
 * @return ボタンがクリックされたか
 */
bool Button::DrawRadioButton(const int X, const int Y, const char *ButtonName, const bool Selecting) const {
	// ボタンの描画
	DrawGraph(X, Y, Selecting ? RButtonONGraphHandle : RButtonOFFGraphHandle, TRUE);
	// ボタン名の描画
	DrawString(X + 30, Y + 5, ButtonName, GetColor(255, 255, 255));
	// ボタンクリックの判定
	if(!Selecting && Input::IsCursorInCircle(X + 12, Y + 12, 12) && Input::GetUnclick()) return true; // ボタン上をクリックした時
	// 未クリックの返戻
	return false;
}

/**
 * スライダー描画関数
 * @param X スライダーのＸ座標（≧0）
 * @param Y スライダーのＹ座標（≧0）
 * @param MinValue 最小値（＜MaxValue）
 * @param MaxValue 最大値（＞MinValue）
 * @param Value 値（MinValue≦Value≦MaxValue）
 * @return スライダーが操作されたか
 */
bool Button::DrawSlider(const int X, const int Y, const int MinValue, const int MaxValue, int &Value) const {
	// スライダーの描画
	const int Pos = X + 120 / (MaxValue - MinValue) * (Value - MinValue);
	DrawBox(X + 4, Y + 10, X + 124, Y + 14, GetColor(128, 128, 128), TRUE);
	DrawBox(X + 4, Y + 10, Pos, Y + 14, GetColor(255, 255, 255), TRUE);
	DrawBox(Pos, Y + 4, Pos + 8, Y + 20, GetColor(255, 255, 255), TRUE);
	// 値の描画
	DrawFormatString(X + 134, Y + 4, GetColor(255, 255, 255), "%d", Value);
	// スライダーの操作
	if(Input::IsCursorInBox(X, Y + 4, X + 128, Y + 20) && Input::GetClicking()) {
		// 操作の反映
		DrawBox(Pos, Y + 4, Pos + 8, Y + 20, GetColor(255, 128, 0), FALSE);
		Value = std::clamp(Value + (Input::GetCursorPosX() - Pos - 4) / 4, MinValue, MaxValue);
		// 操作の返戻
		return true;
	}
	// 未操作の返戻
	return false;
}

/**
 * テキストボックス描画関数
 * @param X テキストボックスのＸ座標（≧0）
 * @param Y テキストボックスのＹ座標（≧0）
 * @param ValueStr 入力文字列
 * @param Selecting 選択中か
 * @param CursorPos カーソル位置（0≦CursorPos≦入力文字列の長さ）
 * @return テキストボックスが選択中か
 */
bool Button::DrawTextBox(const int X, const int Y, std::string &ValueStr, bool &Selecting, int &CursorPos) const {
	// テキストボックスの描画
	DrawBox(X + 4, Y + 2, X + 124, Y + 22, GetColor(255, 255, 255), TRUE);
	// テキストボックスの選択中判定
	if(Input::GetUnclick()) Selecting = Input::IsCursorInBox(X + 4, Y + 2, X + 124, Y + 22); // テキストボックス上をクリックすると選択中にする
	// 値の描画
	if(ValueStr.empty() && !Selecting) DrawString(X + 14, Y + 4, "シードを入力", GetColor(128, 128, 128)); // 入力文字列が空の時
	else DrawFormatString(X + 14, Y + 4, GetColor(0, 0, 0), "%11s", ValueStr.c_str());
	// 値の書換
	if(Selecting) { // テキストボックス選択中
		// 選択中表示
		DrawBox(X + 4, Y + 2, X + 124, Y + 22, GetColor(255, 128, 0), FALSE); // 橙色の枠を表示
		// カーソル表示
		if(Input::Cycle < 64U) {
			const int LineX = X - 9 * CursorPos + 112; // カーソル線のＸ座標
			DrawLine(LineX, Y + 4, LineX, Y + 19, GetColor(0, 0, 0));
		}
		// テキストボックスの操作
		if(!Input::Cycle) { // キーの押下中に連続で動作される間隔を空ける
			// カーソルの移動
			CursorPos += Input::GetLRMove();
			CursorPos = std::clamp(CursorPos, 0, static_cast<int>(ValueStr.length())); // カーソル移動範囲の制限
			// 文字列の操作
			if(CursorPos == ValueStr.length() && ValueStr[0] != '-' && Input::GetNumKeyPressing('-')) {
				ValueStr.insert(ValueStr.begin(), '-'); // 符号を入力
			}
			if(static_cast<int>(ValueStr.length()) > CursorPos || ValueStr[0] != '-') {
				for(char Num = '0'; Num <= '9'; ++Num) if(Input::GetNumKeyPressing(Num)) ValueStr.insert(ValueStr.end() - CursorPos, Num); // 数字を入力
			}
			if(static_cast<int>(ValueStr.length()) > CursorPos && Input::GetKeyPressing(KEY_INPUT_BACK)) {
				ValueStr.erase(ValueStr.length() - CursorPos - 1, 1); // 一文字削除
			}
			if(ValueStr.length() > 10 && ValueStr[0] == '0') ValueStr.erase(0, 1); // 正の値の桁数を１０桁に制限
			else if(ValueStr.length() > 11 && ValueStr[1] == '0') ValueStr.erase(1, 1); // 負の値の桁数を１０桁に制限
		}
		// 選択中の返戻
		return true;
	}
	// 未選択の返戻
	return false;
}

/**
 * コンストラクタ
 */
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
	FontHandle = CreateFontToHandle(nullptr, 72, 2);
	// 終了
	return;
}

/**
 * デストラクタ
 */
Button::~Button() {
	// グラフ・サウンド・フォントの解放
	DeleteGraph(ButtonOFFGraphHandle);
	DeleteGraph(ButtonONGraphHandle);
	DeleteGraph(RButtonOFFGraphHandle);
	DeleteGraph(RButtonONGraphHandle);
	DeleteSoundMem(PushSoundHandle);
	DeleteFontToHandle(FontHandle);
	// 終了
	return;
}
