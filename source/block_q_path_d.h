#pragma once
#include "block_q_path_base.h"

// Ｄ型通路部ブロック（四角）クラス
class BlockQPathD : public BlockQPathBase {
public:
	BlockQPathD(); // コンストラクタ
	void Collision(const int &Direction, VECTOR &BallPos, VECTOR &BallVel) const; // 衝突判定関数
};