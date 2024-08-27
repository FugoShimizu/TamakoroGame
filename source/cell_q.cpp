#include "cell_q.h"

// セル設定関数
void CellQ::SetCell(const int &SourceModelHandle, const int &CellDir, const int &StageSize, const int &Latitude, const int &Longitude) {
	// モデルのコピー
	ModelHandle = MV1DuplicateModel(SourceModelHandle);
	// セルの向きの設定
	Direction = 0.5F * DX_PI_F * CellDir;
	// セルの位置の設定
	Location = VGet(static_cast<float>(-2 * (StageSize + 1) + 4 * Longitude), 0.0F, static_cast<float>(2 * (StageSize + 1) - 4 * Latitude));
	//終了
	return;
}