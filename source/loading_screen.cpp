#include "loading_screen.hpp"
#include "setting.hpp"
#include <DxLib.h>

/**
 * 画面描画関数
 */
void LoadingScreen::DrawScreen() {
	// 探索済ノード数の加算
	++LoadedNodes;
	// 画面のクリア
	ClearDrawScreen();
	// 背景の派生グラフの生成と描画
	const int DerivedGraphHandle = DerivationGraph(0, 221, 128, 17, BGGraphHandle);
	DrawModiGraph(0, 0, 1280, 0, 1280, 720, 0, 720, DerivedGraphHandle, FALSE);
	DeleteGraph(DerivedGraphHandle);
	// ゲージの描画
	DrawString(390, 332, "Now Loading...", GetColor(255, 255, 255));
	DrawBox(390, 350, 890, 370, GetColor(128, 128, 128), TRUE);
	DrawBox(390, 350, static_cast<int>(500 * LoadedNodes / TotalNodes) + 390, 370, GetColor(255, 255, 255), TRUE);
	DrawFormatString(900, 352, GetColor(255, 255, 255), "%3d%%", static_cast<int>(100 * LoadedNodes / TotalNodes));
	// 裏画面の内容の表画面への反映
	ScreenFlip();
	// 終了
	return;
}

/**
 * コンストラクタ
 */
LoadingScreen::LoadingScreen() {
	// メンバ変数の初期化
	TotalNodes = [Size = Setting::GetStageSize()]() {
		switch(Setting::GetStageType()) {
		case StageForm::SQR:
			return Size * Size;
		case StageForm::HEX:
			return (3 * Size * Size >> 1) + Size % 2 * Size - 1;
		default:
			return 0;
		}
	}();
	LoadedNodes = 0;
	// 画像の読込
	BGGraphHandle = LoadGraph("graphs\\background.png"); // 背景
	// 終了
	return;
}

/**
 * デストラクタ
 */
LoadingScreen::~LoadingScreen() {
	// 背景グラフの解放
	DeleteGraph(BGGraphHandle);
	// 終了
	return;
}
