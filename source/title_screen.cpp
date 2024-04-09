#include <DxLib.h>
#include "title_screen.h"
#include "input.h"
#include "button.h"

// コンストラクタ
TitleScreen::TitleScreen() {
	// メンバ変数の初期化
	StageTypeTmp = std::make_pair(true, StageForm::SQR);
	StageSizeTmp = std::make_pair(true, 16);
	StageSeedTmp = std::make_pair(true, 0);
	// 画像の読込
	BGGraphHandle = LoadGraph("graphs\\background.png"); // 背景
	TitleGraphHandle = LoadGraph("graphs\\title.png"); // 背景
	// 終了
	return;
}

// 画面描画関数
bool TitleScreen::DrawScreen(const bool &SkipTitle) {
	// リトライ時のステージ再生成
	if(SkipTitle) { // タイトルスキップフラグ
		// ステージ情報の設定
		Setting::SetStageInfo(StageTypeTmp, StageSizeTmp, StageSeedTmp);
		// ゲームをスタートさせる
		return true;
	}
	// ボタンオブジェクト
	const Button Btn;
	// テキストボックスフラグ
	bool SelectingTextBox = false;
	int TextCursorPos = 0;
	// タイトル画面を描画
	while(!Input::ExitOperation()) {
		// 入力状態の更新
		Input::SetInput();
		// 画面のクリア
		ClearDrawScreen();
		// 背景
		DrawModiGraph(0, 0, 1280, 0, 1280, 720, 0, 720, DerivationGraph(0, 221, 128, 17, BGGraphHandle), FALSE);
		// タイトル
		DrawGraph(0, 0, TitleGraphHandle, TRUE);
		// 終了ボタン
		if(Btn.DrawButton(240, 320, "終了")) return false; // ゲームを終了
		// ステージ生成ボタン
		if(Btn.DrawButton(720, 320, "プレイ") || Input::GetKeyPress(KEY_INPUT_RETURN)) { // ボタンクリック時
			// ステージ情報の設定
			Setting::SetStageInfo(StageTypeTmp, StageSizeTmp, StageSeedTmp);
			// ゲームをスタート
			return true;
		}
		// ステージの形の設定ＵＩ
		DrawString(480, 480, "ステージの形", GetColor(0, 0, 0));
		if(Btn.DrawRadioButton(500, 500, "ランダム", StageTypeTmp.first)) StageTypeTmp.first = true;
		if(Btn.DrawRadioButton(600, 500, "四角形", !StageTypeTmp.first && StageTypeTmp.second == StageForm::SQR)) StageTypeTmp = std::make_pair(false, StageForm::SQR);
		if(Btn.DrawRadioButton(700, 500, "六角形", !StageTypeTmp.first && StageTypeTmp.second == StageForm::HEX)) StageTypeTmp = std::make_pair(false, StageForm::HEX);
		// ステージの大きさの設定ＵＩ
		DrawString(480, 540, "ステージの大きさ", GetColor(0, 0, 0));
		if(Btn.DrawRadioButton(500, 560, "ランダム", StageSizeTmp.first)) StageSizeTmp.first = true;
		if(Btn.DrawRadioButton(600, 560, "", !StageSizeTmp.first)) StageSizeTmp.first = false;
		if(Btn.DrawSlider(630, 560, 2, 32, StageSizeTmp.second)) StageSizeTmp.first = false;
		// ステージのシードの設定ＵＩ
		DrawString(480, 600, "ステージのシード", GetColor(0, 0, 0));
		if(Btn.DrawRadioButton(500, 620, "ランダム", StageSeedTmp.first)) StageSeedTmp.first = true;
		if(Btn.DrawRadioButton(600, 620, "", !StageSeedTmp.first)) StageSeedTmp.first = false;
		if(Btn.DrawTextBox(630, 620, SeedStr, SelectingTextBox, TextCursorPos)) StageSeedTmp.first = false;
		// シード文字列の数値化
		if(SeedStr.empty() || SeedStr == "-") StageSeedTmp.second = 0; // 文字列が空なら0にする
		else {
			try {
				StageSeedTmp.second = std::stoi(SeedStr);
			} catch(...) { // オーバーフロー時
				StageSeedTmp.second = SeedStr[0] == '-' ? INT_MIN : INT_MAX;
				SeedStr = std::to_string(StageSeedTmp.second);
			}
		}
		// 注意事項
		DrawString(1140, 700, "※音声が流れます", GetColor(255, 255, 255));
		// 裏画面の内容を表画面に反映
		ScreenFlip();
	}
	// 終了
	return false;
}