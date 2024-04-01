#include "setting.hpp"
#include <algorithm>
#include <random>

/**
 * ステージ情報設定関数
 * @param StageType ステージの形の設定（first: ランダム化，second: 非ランダム時の値）
 * @param StageSize ステージの大きさの設定（first: ランダム化，second: 非ランダム時の値）
 * @param StageSeed ステージのシードの設定（first: ランダム化，second: 非ランダム時の値）
 */
void Setting::SetStageInfo(
	const std::pair<bool, StageForm> &StageType,
	const std::pair<bool, int> &StageSize,
	const std::pair<bool, int> &StageSeed
) {
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

/**
 * ステージタイプ取得関数
 * @return ステージの形
 */
StageForm Setting::GetStageType() {
	// ステージの形の返戻
	return Type;
}

/**
 * ステージサイズ取得関数
 * @return ステージの大きさ
 */
int Setting::GetStageSize() {
	// ステージの大きさの返戻
	return Size;
}

/**
 * ステージシード取得関数
 * @return シード値
 */
int Setting::GetStageSeed() {
	// シード値の返戻
	return Seed;
}
