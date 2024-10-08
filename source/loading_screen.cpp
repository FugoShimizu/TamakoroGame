#include <DxLib.h>
#include "loading_screen.h"
#include "setting.h"

// コンストラクタ
LoadingScreen::LoadingScreen() {
	// メンバ変数の初期化
	switch(Setting::GetStageType()) {
	case StageForm::SQR:
		TotalNodes = Setting::GetStageSize() * Setting::GetStageSize();
		break;
	case StageForm::HEX:
		TotalNodes = 3 * Setting::GetStageSize() * Setting::GetStageSize() / 2 + Setting::GetStageSize() % 2 * Setting::GetStageSize() - 1;
		break;
	default:
		TotalNodes = 0;
		break;
	}
	LoadedNodes = 0;
	// 画像の読込
	BGGraphHandle = LoadGraph("graphs\\background.png"); // 背景
	// 終了
	return;
}

// 画面描画関数
void LoadingScreen::DrawScreen() {
	// 探索済ノード数の加算
	++LoadedNodes;
	// 画面のクリア
	ClearDrawScreen();
	// 背景の描画
	DrawModiGraph(0, 0, 1280, 0, 1280, 720, 0, 720, DerivationGraph(0, 221, 128, 17, BGGraphHandle), FALSE);
	// ゲージの描画
	DrawString(390, 332, "Now Loading...", GetColor(255, 255, 255));
	DrawBox(390, 350, 890, 370, GetColor(128, 128, 128), TRUE);
	DrawBox(390, 350, 390 + 500 * LoadedNodes / TotalNodes, 370, GetColor(255, 255, 255), TRUE);
	DrawFormatString(900, 352, GetColor(255, 255, 255), "%3d%%", 100 * LoadedNodes / TotalNodes);
	// 裏画面の内容を表画面に反映
	ScreenFlip();
	// 終了
	return;
}