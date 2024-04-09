#include "block_q_path_d.h"

// コンストラクタ
BlockQPathD::BlockQPathD() {
	// モデルの読込
	ModelHandle = MV1LoadModel("models\\block_q_path_d.mv1");
	// 終了
	return;
}

// 衝突判定関数
void BlockQPathD::Collision(const int &Direction, VECTOR &BallPos, VECTOR &BallVel) const {
	// セル回転分のボール位置の回転変換
	RotateBallPos(-Direction, BallPos, BallVel);
	// ボールの衝突判定
	RightWall(BallPos, BallVel);
	LeftBackCorner(BallPos, BallVel);
	LeftFrontCorner(BallPos, BallVel);
	// ボール位置の再回転変換
	RotateBallPos(Direction, BallPos, BallVel);
	// 終了
	return;
}