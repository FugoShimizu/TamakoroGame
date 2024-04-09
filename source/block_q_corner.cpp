#include "block_q_corner.h"

// コンストラクタ
BlockQCorner::BlockQCorner() {
	// モデルの読込
	ModelHandle = MV1LoadModel("models\\block_q_corner.mv1");
	// 終了
	return;
}