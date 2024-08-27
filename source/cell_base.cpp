#include "cell_base.h"

// コンストラクタ
CellBase::CellBase() {
	// メンバ変数の初期化
	ModelHandle = -1;
	Direction = 0;
	Location = VGet(0.0F, 0.0F, 0.0F);
	// 終了
	return;
}

// テクスチャ設定関数
void CellBase::SetTexture(const int &GraphHandle) const {
	// テクスチャの変更
	MV1SetTextureGraphHandle(ModelHandle, 0, GraphHandle, FALSE);
	// 終了
	return;
}

// 描画関数
void CellBase::Draw(const MATRIX &RotationMat) const {
	// セルを描画する
	MV1SetMatrix(ModelHandle, MMult(MMult(MGetRotY(Direction), RotationMat), MGetTranslate(VTransformSR(Location, RotationMat))));
	MV1DrawModel(ModelHandle);
	// 終了
	return;
}