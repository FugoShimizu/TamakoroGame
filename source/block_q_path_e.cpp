#include "block_q_path_e.hpp"

/**
 * 衝突判定関数
 * @param Direction 回転方向（0≦Direction≦3）
 * @param BallPos ボール位置
 * @param BallVel ボール速度
 */
void BlockQPathE::Collision(const int Direction, VECTOR &BallPos, VECTOR &BallVel) const {
	// ボールの衝突判定
	LeftBackCorner(BallPos, BallVel);
	LeftFrontCorner(BallPos, BallVel);
	RightBackCorner(BallPos, BallVel);
	RightFrontCorner(BallPos, BallVel);
	// 終了
	return;
}

/**
 * コンストラクタ
 */
BlockQPathE::BlockQPathE() {
	// モデルの読込
	ModelHandle = MV1LoadModel("models\\block_q_path_e.mv1");
	// 終了
	return;
}
