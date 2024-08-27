#include <algorithm>
#include <random>
#include "setting.h"

// コンストラクタ
void Setting::SetStageInfo(const std::pair<bool, StageForm> &StageType, const std::pair<bool, int> &StageSize, const std::pair<bool, int> &StageSeed) {
	// 乱数の生成
	std::random_device SeedGen; // 非決定論的乱数生成器
	std::mt19937 Engine(SeedGen()); // パラメータ定義済擬似乱数生成器
	std::uniform_int_distribution<int> DistType(0, 1); // 一様分布
	std::normal_distribution<float> DistSize(16.0F, 2.5F); // 正規分布
	// 各設定値の設定
	Type = StageType.first ? static_cast<StageForm>(DistType(Engine)) : StageType.second; // ステージの形
	Size = StageSize.first ? std::clamp(static_cast<int>(DistSize(Engine)), 8, 24) : std::clamp(StageSize.second, 2, 32); // ステージの大きさ
	Seed = StageSeed.first ? SeedGen() : StageSeed.second; // シード値
	// 終了
	return;
}

// ステージタイプ取得関数
StageForm Setting::GetStageType() {
	// 終了
	return Type; // ステージの形を返す
}

// ステージサイズ取得関数
int Setting::GetStageSize() {
	// 終了
	return Size; // ステージの大きさを返す
}

// ステージシード取得関数
int Setting::GetStageSeed() {
	// 終了
	return Seed; // シード値を返す
}
