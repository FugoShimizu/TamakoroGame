#pragma once
#include "block_q_path_base.h"

// Ｃ型通路部ブロック（四角）クラス
class BlockQPathC : public BlockQPathBase {
public:
	BlockQPathC(); // コンストラクタ
	void Collision(const int &Direction, VECTOR &BallPos, VECTOR &BallVel) const; // 衝突判定関数
};