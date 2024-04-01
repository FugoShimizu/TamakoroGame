#pragma once

#include <DxLib.h>

// セル基底クラス
class CellBase {
protected:

	int ModelHandle = -1; // セルのハンドル
	float Direction; // セルの向き
	VECTOR Location; // セルの座標

	CellBase(); // コンストラクタ

public:

	void SetTexture(const int GraphHandle) const; // テクスチャ設定関数 // 未使用
	void Draw(const MATRIX &RotationMat) const; // 描画関数
	void DeleteModel(); // モデルハンドル削除関数
};
