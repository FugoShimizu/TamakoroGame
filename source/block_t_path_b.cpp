#include "block_t_path_b.h"

// コンストラクタ
BlockTPathB::BlockTPathB() {
	// モデルの読込
	ModelHandle = MV1LoadModel("models\\block_t_path_b.mv1");
	// 終了
	return;
}

// 衝突判定関数
void BlockTPathB::Collision(const int &Direction, const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const {
	// セル回転分のボール位置の回転変換
	RotateBallPos(-Direction, BallPos, BallVel);
	// ボールの衝突判定
	TwlOcWall(AdjacentWall, BallPos, BallVel);
	SixOcWall(AdjacentWall, BallPos, BallVel);
	// ボール位置の再回転変換
	RotateBallPos(Direction, BallPos, BallVel);
	// 終了
	return;
}