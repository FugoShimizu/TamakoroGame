#pragma once
#include "block_t_path_base.h"

// Ｃ型通路部ブロック（三角）クラス
class BlockTPathC : public BlockTPathBase {
public:
	BlockTPathC(); // コンストラクタ
	void Collision(const int &Direction, const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const; // 衝突判定関数
};