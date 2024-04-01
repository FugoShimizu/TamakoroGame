#include "block_t_path_a.hpp"

/**
 * 衝突判定関数
 * @param Direction 回転方向（0≦Direction≦2）
 * @param AdjacentWall 隣接壁の有無
 * @param BallPos ボール位置
 * @param BallVel ボール速度
 */
void BlockTPathA::Collision(
	const int Direction,
	const std::array<std::pair<bool, bool>, 3> &AdjacentWall,
	VECTOR &BallPos,
	VECTOR &BallVel
) const {
	// セル回転分のボール位置の回転変換
	RotateBallPos(-Direction, BallPos, BallVel);
	// ボールの衝突判定
	TwoOcWall(AdjacentWall, BallPos, BallVel);
	TenOcWall(AdjacentWall, BallPos, BallVel);
	// ボール位置の再回転変換
	RotateBallPos(Direction, BallPos, BallVel);
	// 終了
	return;
}

/**
 * コンストラクタ
 */
BlockTPathA::BlockTPathA() {
	// モデルの読込
	ModelHandle = MV1LoadModel("models\\block_t_path_a.mv1");
	// 終了
	return;
}
