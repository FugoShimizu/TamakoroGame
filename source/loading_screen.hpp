#pragma once

// ロード画面クラス
class LoadingScreen {
private:

	unsigned int TotalNodes; // 総ノード数
	unsigned int LoadedNodes; // 探索済ノード数
	int BGGraphHandle = -1; // 背景グラフハンドル

public:

	void DrawScreen(); // 画面描画関数

	LoadingScreen &operator=(const LoadingScreen &) = delete; // コピー代入演算子（禁止）
	LoadingScreen(const LoadingScreen &) = delete; // コピーコンストラクタ（禁止）

	LoadingScreen(); // コンストラクタ
	~LoadingScreen(); // デストラクタ
};
