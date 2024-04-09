#include "block_t_path_c.h"

// コンストラクタ
BlockTPathC::BlockTPathC() {
	// モデルの読込
	ModelHandle = MV1LoadModel("models\\block_t_path_c.mv1");
	// 終了
	return;
}

// 衝突判定関数
void BlockTPathC::Collision(const int &Direction, const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const {
	// セル回転分のボール位置の回転変換
	RotateBallPos(-Direction, BallPos, BallVel);
	// ボールの衝突判定
	TwlOcWall(AdjacentWall, BallPos, BallVel);
	ForOcWall(AdjacentWall, BallPos, BallVel);
	EitOcWall(AdjacentWall, BallPos, BallVel);
	// ボール位置の再回転変換
	RotateBallPos(Direction, BallPos, BallVel);
	// 終了
	return;
}