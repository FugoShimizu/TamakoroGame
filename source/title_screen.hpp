#pragma once

#include "setting.hpp"
#include <array>
#include <string>
#include <utility>

// タイトル画面クラス
class TitleScreen {
private:

	const std::array<int, 2> BGGraphHandles; // 背景グラフハンドル（添字はステージの形）
	std::pair<bool, StageForm> StageTypeTmp; // ステージの形設定（first: ランダムか，second: 非ランダム時の値）
	std::pair<bool, int> StageSizeTmp; // ステージの大きさ設定（first: ランダムか，second: 非ランダム時の値）
	std::pair<bool, int> StageSeedTmp; // ステージのシード設定（first: ランダムか，second: 非ランダム時の値）
	std::string SeedStr; // ステージシードの文字列
	int TitleGraphHandle = -1; // タイトルグラフハンドル

public:

	bool DrawScreen(const bool SkipTitle); // 画面描画関数

	TitleScreen &operator=(const TitleScreen &) = delete; // コピー代入演算子（禁止）
	TitleScreen(const TitleScreen &) = delete; // コピーコンストラクタ（禁止）

	TitleScreen(); // コンストラクタ
	~TitleScreen(); // デストラクタ
};
