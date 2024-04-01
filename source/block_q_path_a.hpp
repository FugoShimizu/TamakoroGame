#pragma once

#include "block_q_path_base.hpp"

// Ａ型通路部ブロック（四角）クラス
class BlockQPathA : public BlockQPathBase {
public:

	void Collision(const int Direction, VECTOR &BallPos, VECTOR &BallVel) const override; // 衝突判定関数

	BlockQPathA(); // コンストラクタ
};
