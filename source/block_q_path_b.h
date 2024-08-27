#pragma once
#include "block_q_path_base.h"

// Ｂ型通路部ブロック（四角）クラス
class BlockQPathB : public BlockQPathBase {
public:
	BlockQPathB(); // コンストラクタ
	void Collision(const int &direction, VECTOR &BallPos, VECTOR &BallVel) const override; // 衝突判定関数
};