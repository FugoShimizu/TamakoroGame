#pragma once

#include "block_t_path_base.hpp"

// Ｂ型通路部ブロック（三角）クラス
class BlockTPathB : public BlockTPathBase {
public:

	void Collision(
		const int Direction,
		const std::array<std::pair<bool, bool>, 3> &AdjacentWall,
		VECTOR &BallPos,
		VECTOR &BallVel
	) const override; // 衝突判定関数

	BlockTPathB(); // コンストラクタ
};
