#include <DxLib.h>
#include "input.h"
#include "title_screen.h"
#include "play_screen.h"

// メイン関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	// 初期設定
	ChangeWindowMode(TRUE); // ウインドウモードで起動
	SetMainWindowText("TamakoroGame"); // ウインドウタイトルの設定
	SetGraphMode(1280, 720, 32); // 画面モードを720pに設定
	SetFullSceneAntiAliasingMode(4, 4); // アンチエイリアスの設定
	if(DxLib_Init() == -1) return -1; // ＤＸライブラリの初期化
	SetDrawScreen(DX_SCREEN_BACK); // 描画先を裏画面に設定
	// オブジェクト
	TitleScreen TitleScr; // タイトル画面
	PlayScreen PlayScr; // プレイ画面
	// タイトルスキップフラグ
	bool SkipTitle = false;
	// メインループ
	while(!Input::ExitOperation()) {
		// タイトル画面の表示
		if(!TitleScr.DrawScreen(SkipTitle)) break; // EXITを選択で終了
		// プレイ画面の表示
		SkipTitle = PlayScr.DrawScreen();
	}
	// ＤＸライブラリ使用の終了処理
	DxLib_End();
	// ソフトの終了
	return 0;
}