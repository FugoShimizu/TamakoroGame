#include "block_q_path_e.h"

// コンストラクタ
BlockQPathE::BlockQPathE() {
	// モデルの読込
	ModelHandle = MV1LoadModel("models\\block_q_path_e.mv1");
	// 終了
	return;
}

// 衝突判定関数
void BlockQPathE::Collision(const int &Direction, VECTOR &BallPos, VECTOR &BallVel) const {
	// ボールの衝突判定
	LeftBackCorner(BallPos, BallVel);
	LeftFrontCorner(BallPos, BallVel);
	RightBackCorner(BallPos, BallVel);
	RightFrontCorner(BallPos, BallVel);
	// 終了
	return;
}