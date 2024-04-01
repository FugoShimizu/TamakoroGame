#include "block_q_path_a.hpp"

/**
 * 衝突判定関数
 * @param Direction 回転方向（0≦Direction≦3）
 * @param BallPos ボール位置
 * @param BallVel ボール速度
 */
void BlockQPathA::Collision(const int Direction, VECTOR &BallPos, VECTOR &BallVel) const {
	// セル回転分のボール位置の回転変換
	RotateBallPos(-Direction, BallPos, BallVel);
	// ボールの衝突判定
	LeftWall(BallPos, BallVel);
	RightWall(BallPos, BallVel);
	FrontWall(BallPos, BallVel);
	// ボール位置の再回転変換
	RotateBallPos(Direction, BallPos, BallVel);
	// 終了
	return;
}

/**
 * コンストラクタ
 */
BlockQPathA::BlockQPathA() {
	// モデルの読込
	ModelHandle = MV1LoadModel("models\\block_q_path_a.mv1");
	// 終了
	return;
}
