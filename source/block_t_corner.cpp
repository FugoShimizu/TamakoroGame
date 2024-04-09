#include "block_t_corner.h"

// コンストラクタ
BlockTCorner::BlockTCorner() {
	// モデルの読込
	ModelHandle = MV1LoadModel("models\\block_t_corner.mv1");
	// 終了
	return;
}