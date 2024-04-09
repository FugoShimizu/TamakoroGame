#pragma once
#include <DxLib.h>

// セル基底クラス
class CellBase {
public:
	void SetTexture(const int &GraphHandle) const; // テクスチャ設定関数 // 未使用
	void Draw(const MATRIX &RotationMat) const; // 描画関数
protected:
	CellBase(); // コンストラクタ
	int ModelHandle; // セルのハンドル
	float Direction;	// セルの向き
	VECTOR Location;	// セルの座標
};