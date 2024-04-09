#include "cell_t.h"

// セル設定関数（北セル）
void CellT::SetCellN(const int &SourceModelHandle, const int &CellDir, const int &StageSize, const int &Latitude, const int &Longitude) {
	// モデルのコピー
	ModelHandle = MV1DuplicateModel(SourceModelHandle);
	// セルの向きの設定
	Direction = CellDir * DX_TWO_PI_F / 3.0F;
	// セルの位置の設定
	Location = VGet((Longitude - Latitude) * CentroidX, 0.0F, (StageSize - Latitude - Longitude + 1) * 4 + CentroidZ);
	//終了
	return;
}

// セル設定関数（南セル）
void CellT::SetCellS(const int &SourceModelHandle, const int &CellDir, const int &StageSize, const int &Latitude, const int &Longitude) {
	// モデルのコピー
	ModelHandle = MV1DuplicateModel(SourceModelHandle);
	// セルの向きの設定
	Direction = CellDir * DX_TWO_PI_F / 3.0F + DX_PI_F;
	// セルの位置の設定
	Location = VGet((Longitude - Latitude) * CentroidX, 0.0F, (StageSize - Latitude - Longitude + 1) * 4 - CentroidZ);
	//終了
	return;
}