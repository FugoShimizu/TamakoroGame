#include "block_q_path_c.hpp"

/**
 * 衝突判定関数
 * @param Direction 回転方向（0≦Direction≦3）
 * @param BallPos ボール位置
 * @param BallVel ボール速度
 */
void BlockQPathC::Collision(const int Direction, VECTOR &BallPos, VECTOR &BallVel) const {
	// セル回転分のボール位置の回転変換
	RotateBallPos(-Direction, BallPos, BallVel);
	// ボールの衝突判定
	RightWall(BallPos, BallVel);
	FrontWall(BallPos, BallVel);
	LeftBackCorner(BallPos, BallVel);
	// ボール位置の再回転変換
	RotateBallPos(Direction, BallPos, BallVel);
	// 終了
	return;
}

/**
 * コンストラクタ
 */
BlockQPathC::BlockQPathC() {
	// モデルの読込
	ModelHandle = MV1LoadModel("models\\block_q_path_c.mv1");
	// 終了
	return;
}
