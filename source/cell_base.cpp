#include "cell_base.hpp"

/**
 * テクスチャ設定関数
 * @param GraphHandle 設定するグラフィックハンドル
 */
void CellBase::SetTexture(const int GraphHandle) const {
	// テクスチャの変更
	MV1SetTextureGraphHandle(ModelHandle, 0, GraphHandle, FALSE);
	// 終了
	return;
}

/**
 * 描画関数
 * @param RotationMat ステージ傾斜の回転行列
 */
void CellBase::Draw(const MATRIX &RotationMat) const {
	// セルの描画
	MV1SetMatrix(ModelHandle, MMult(MMult(MGetRotY(Direction), RotationMat), MGetTranslate(VTransformSR(Location, RotationMat))));
	MV1DrawModel(ModelHandle);
	// 終了
	return;
}

/**
 * モデルハンドル削除関数
 */
void CellBase::DeleteModel() {
	// モデルの削除
	MV1DeleteModel(ModelHandle);
	// ハンドルの無効化
	ModelHandle = -1;
	// 終了
	return;
}

/**
 * コンストラクタ
 */
CellBase::CellBase() {
	// メンバ変数の初期化
	ModelHandle = -1;
	Direction = 0;
	Location = VGet(0.0F, 0.0F, 0.0F);
	// 終了
	return;
}
