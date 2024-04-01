#include "cell_q.hpp"

/**
 * セル設定関数
 * @param SourceModelHandle コピー元モデルハンドル
 * @param CellDir セルの向き（0≦CellDir≦3）
 * @param StageSize ステージの大きさ（≧1）
 * @param Latitude 緯度（0≦Latitude≦StageSize+1）
 * @param Longitude 経度（0≦Longitude≦StageSize+1）
 */
void CellQ::SetCell(
	const int SourceModelHandle,
	const int CellDir,
	const int StageSize,
	const int Latitude,
	const int Longitude
) {
	// モデルのコピー
	ModelHandle = MV1DuplicateModel(SourceModelHandle);
	// セルの向きの設定
	Direction = 0.5F * DX_PI_F * CellDir;
	// セルの位置の設定
	const int Edge = StageSize + 1 << 1; // ステージ縁の座標
	Location = VGet(static_cast<float>((Longitude << 2) - Edge), 0.0F, static_cast<float>(Edge - (Latitude << 2)));
	// 終了
	return;
}
