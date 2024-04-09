#include "block_q_path_b.h"

// コンストラクタ
BlockQPathB::BlockQPathB() {
	// モデルの読込
	ModelHandle = MV1LoadModel("models\\block_q_path_b.mv1");
	// 終了
	return;
}

// 衝突判定関数
void BlockQPathB::Collision(const int &Direction, VECTOR &BallPos, VECTOR &BallVel) const {
	// セル回転分のボール位置の回転変換
	RotateBallPos(-Direction, BallPos, BallVel);
	// ボールの衝突判定
	LeftWall(BallPos, BallVel);
	RightWall(BallPos, BallVel);
	// ボール位置の再回転変換
	RotateBallPos(Direction, BallPos, BallVel);
	// 終了
	return;
}