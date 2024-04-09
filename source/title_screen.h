#pragma once
#include <string>
#include <utility>
#include "setting.h"

// タイトル画面クラス
class TitleScreen {
public:
	TitleScreen(); // コンストラクタ
	bool DrawScreen(const bool &SkipTitle); // 画面描画関数
private:
	std::pair<bool, StageForm> StageTypeTmp; // ステージの形設定（first：ランダムか，second：非ランダム時の値）
	std::pair<bool, int> StageSizeTmp; // ステージの大きさ設定（first：ランダムか，second：非ランダム時の値）
	std::pair<bool, int> StageSeedTmp; // ステージのシード設定（first：ランダムか，second：非ランダム時の値）
	std::string SeedStr; // ステージシードの文字列
	int BGGraphHandle; // 背景グラフハンドル
	int TitleGraphHandle; // タイトルグラフハンドル
};