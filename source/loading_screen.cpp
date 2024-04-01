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
	// 背景の描画
	int GraphWidth = 0, GraphHeight = 0;
	GetGraphSize(BGGraphHandle, &GraphWidth, &GraphHeight);
	const int CropHeight = 9 * GraphWidth >> 5, PrevDrawMode = GetDrawMode(); // 切出す高さ（水平方向 180° 分の幅を画面の縦横比で換算）と変更前の描画モード
	SetDrawMode(DX_DRAWMODE_BILINEAR); // 画像を滑らかに拡大
	DrawRectExtendGraph(
		0,
		0,
		1280,
		720,
		GraphWidth >> 2,
		(GraphHeight >> 1) - (CropHeight >> 1),
		GraphWidth >> 1,
		CropHeight,
		BGGraphHandle,
		FALSE
	); // 正距円筒図法の画像の中央を切出す
	SetDrawMode(PrevDrawMode);
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
LoadingScreen::LoadingScreen() : TotalNodes(
	[Size = Setting::GetStageSize()]() -> unsigned int {
		switch(Setting::GetStageType()) {
		case StageForm::SQR:
			return Size * Size;
		case StageForm::HEX:
			return (3 * Size * Size >> 1) + Size % 2 * Size - 1;
		default:
			return 0;
		}
	}()
),
BGGraphHandle(LoadGraph(Setting::GetStageType() == StageForm::HEX ? "graphs\\background_b.png" : "graphs\\background_a.png")) { // 読込中のステージの形の背景
	// メンバ変数の初期化
	LoadedNodes = 0;
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
