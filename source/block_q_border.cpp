#include "block_q_border.h"

// コンストラクタ
BlockQBorder::BlockQBorder() {
	// モデルの読込
	ModelHandle = MV1LoadModel("models\\block_q_border.mv1");
	// 終了
	return;
}