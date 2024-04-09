#pragma once
#include <utility>

// ステージタイプ列挙型構造体
enum struct StageForm {
	SQR,
	HEX
};

// ステージ設定情報クラス
class Setting {
public:
	static void SetStageInfo(const std::pair<bool, StageForm> &StageType, const std::pair<bool, int> &StageSize, const std::pair<bool, int> &StageSeed); // ステージ情報設定関数
	static StageForm GetStageType(); // ステージタイプ取得関数
	static int GetStageSize(); // ステージサイズ取得関数
	static int GetStageSeed(); // ステージシード取得関数
private:
	static inline StageForm Type = StageForm::SQR; // ステージタイプ
	static inline int Size = 16; // ステージサイズ
	static inline int Seed = 0; // ステージシード
};