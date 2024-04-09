#pragma once

// ロード画面クラス
class LoadingScreen {
public:
	LoadingScreen(); // コンストラクタ
	void DrawScreen(); // 画面描画関数
private:
	int TotalNodes; // 総ノード数
	int LoadedNodes; // 探索済ノード数
	int BGGraphHandle; // 背景グラフハンドル
};