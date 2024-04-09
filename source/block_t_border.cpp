#include "block_t_border.h"

// コンストラクタ
BlockTBorder::BlockTBorder() {
	// モデルの読込
	ModelHandle = MV1LoadModel("models\\block_t_border.mv1");
	// 終了
	return;
}