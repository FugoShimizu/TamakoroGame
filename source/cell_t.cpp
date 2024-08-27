#include "cell_t.h"

// セル設定関数（北セル）
void CellT::SetCellN(const int &SourceModelHandle, const int &CellDir, const int &StageSize, const int &Latitude, const int &Longitude) {
	// モデルのコピー
	ModelHandle = MV1DuplicateModel(SourceModelHandle);
	// セルの向きの設定
	Direction = DX_TWO_PI_F / 3.0F * CellDir;
	// セルの位置の設定
	Location = VGet(CentroidX * (Longitude - Latitude), 0.0F, 4 * (StageSize - Latitude - Longitude + 1) + CentroidZ);
	//終了
	return;
}

// セル設定関数（南セル）
void CellT::SetCellS(const int &SourceModelHandle, const int &CellDir, const int &StageSize, const int &Latitude, const int &Longitude) {
	// モデルのコピー
	ModelHandle = MV1DuplicateModel(SourceModelHandle);
	// セルの向きの設定
	Direction = DX_TWO_PI_F / 3.0F * CellDir + DX_PI_F;
	// セルの位置の設定
	Location = VGet(CentroidX * (Longitude - Latitude), 0.0F, 4 * (StageSize - Latitude - Longitude + 1) - CentroidZ);
	//終了
	return;
}