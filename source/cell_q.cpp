#include "cell_q.h"

// セル設定関数
void CellQ::SetCell(const int &SourceModelHandle, const int &CellDir, const int &StageSize, const int &Latitude, const int &Longitude) {
	// モデルのコピー
	ModelHandle = MV1DuplicateModel(SourceModelHandle);
	// セルの向きの設定
	Direction = CellDir * DX_PI_F * 0.5F;
	// セルの位置の設定
	Location = VGet(static_cast<float>((StageSize + 1) * -2 + Longitude * 4), 0.0F, static_cast<float>((StageSize + 1) * 2 - Latitude * 4));
	//終了
	return;
}