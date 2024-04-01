#include "input.hpp"
#include "title_screen.hpp"
#include "play_screen.hpp"
#include <DxLib.h>

/**
 * 埋込アーカイブ登録関数
 * @param Instance インスタンスハンドル
 * @param ResourceName リソース名
 * @param EmulatePath 見せかけのアーカイブファイルパス
 */
void RegisterEmbeddedArchive(const HINSTANCE &Instance, const char *ResourceName, const char *EmulatePath) {
	// リソースの検索
	const HRSRC ResourceInfo = FindResource(Instance, ResourceName, RT_RCDATA);
	if(!ResourceInfo) return; // リソースが無ければ終了
	// リソースのサイズと先頭アドレスの取得
	const int Size = static_cast<int>(SizeofResource(Instance, ResourceInfo));
	void *const Source = LockResource(LoadResource(Instance, ResourceInfo));
	// ＤＸライブラリ側へ複製させて登録 (CopyFlag=TRUE)
	DXArchiveSetMemImage(Source, Size, EmulatePath, TRUE, FALSE);
	// 終了
	return;
}

/**
 * メイン関数
 * @param hInstance インスタンスハンドル
 * @param hPrevInstance 前のインスタンスハンドル
 * @param lpCmdLine コマンドライン文字列
 * @param nCmdShow ウインドウの表示状態
 * @return 終了コード
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	// 初期設定
	ChangeWindowMode(TRUE); // ウインドウモードで起動
	SetMainWindowText("TamakoroGame"); // ウインドウタイトルの設定
	SetGraphMode(1280, 720, 32); // 画面モードを 720p に設定
	SetFullSceneAntiAliasingMode(4, 4); // アンチエイリアスの設定
	if(DxLib_Init() == -1) return -1; // ＤＸライブラリの初期化
	// 埋込アセットアーカイブの登録
	SetUseDXArchiveFlag(TRUE); // アーカイブからの読込を有効化
	SetDXArchiveKeyString("TamakoroGameAssetKey2024"); // アーカイブの復号鍵
	RegisterEmbeddedArchive(hInstance, "MODELS_DXA", "models.dxa"); // モデル
	RegisterEmbeddedArchive(hInstance, "GRAPHS_DXA", "graphs.dxa"); // 画像
	RegisterEmbeddedArchive(hInstance, "SOUNDS_DXA", "sounds.dxa"); // 音声
	SetDrawScreen(DX_SCREEN_BACK); // 描画先を裏画面に設定
	// オブジェクト（DxLib_End より前に破棄する為にブロックスコープに入れる）
	{
		TitleScreen TitleScr; // タイトル画面
		PlayScreen PlayScr; // プレイ画面
		// タイトルスキップフラグ
		bool SkipTitle = false;
		// メインループ
		while(!Input::ExitOperation()) {
			// タイトル画面の表示
			if(!TitleScr.DrawScreen(SkipTitle)) break; // 「終了」を選択で終了
			// プレイ画面の表示
			SkipTitle = PlayScr.DrawScreen();
		}
	}
	// ＤＸライブラリ使用の終了処理
	DxLib_End();
	// ソフトの終了
	return 0;
}
