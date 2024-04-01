#include "cell_t.hpp"

/**
 * セル設定関数（北セル）
 * @param SourceModelHandle コピー元モデルハンドル
 * @param CellDir セルの向き（0≦CellDir≦2）
 * @param StageSize ステージの大きさ（≧1）
 * @param Latitude 緯度（0≦Latitude≦StageSize+1）
 * @param Longitude 経度（0≦Longitude≦StageSize+1）
 */
void CellT::SetCellN(
	const int SourceModelHandle,
	const int CellDir,
	const int StageSize,
	const int Latitude,
	const int Longitude
) {
	// モデルのコピー
	ModelHandle = MV1DuplicateModel(SourceModelHandle);
	// セルの向きの設定
	Direction = DX_TWO_PI_F / 3.0F * CellDir;
	// セルの位置の設定
	Location = VGet(CentroidX * (Longitude - Latitude), 0.0F, (StageSize - Latitude - Longitude + 1 << 2) + CentroidZ);
	// 終了
	return;
}

/**
 * セル設定関数（南セル）
 * @param SourceModelHandle コピー元モデルハンドル
 * @param CellDir セルの向き（0≦CellDir≦2）
 * @param StageSize ステージの大きさ（≧1）
 * @param Latitude 緯度（0≦Latitude≦StageSize+1）
 * @param Longitude 経度（0≦Longitude≦StageSize+1）
 */
void CellT::SetCellS(
	const int SourceModelHandle,
	const int CellDir,
	const int StageSize,
	const int Latitude,
	const int Longitude
) {
	// モデルのコピー
	ModelHandle = MV1DuplicateModel(SourceModelHandle);
	// セルの向きの設定
	Direction = DX_TWO_PI_F / 3.0F * CellDir + DX_PI_F;
	// セルの位置の設定
	Location = VGet(CentroidX * (Longitude - Latitude), 0.0F, (StageSize - Latitude - Longitude + 1 << 2) - CentroidZ);
	// 終了
	return;
}
