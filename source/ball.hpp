#pragma once

#include <DxLib.h>

// ボールクラス
class Ball {
private:

	int ModelHandle = -1; // モデルハンドル

public:

	VECTOR Pos; // 位置
	VECTOR Vel; // 速度
	void SetTexture(const int GraphHandle) const; // テクスチャ設定関数 // 未使用
	void Draw(const MATRIX &RotationMat) const; // 描画関数
	void SetPos(const VECTOR &Position); // 位置設定関数
	void Position(const float StgRotX, const float StgRotZ); // 移動関数

	Ball &operator=(const Ball &) = delete; // コピー代入演算子（禁止）
	Ball(const Ball &) = delete; // コピーコンストラクタ（禁止）

	Ball(); // コンストラクタ
	~Ball(); // デストラクタ
};
