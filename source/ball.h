#pragma once
#include <DxLib.h>

// ボールクラス
class Ball {
public:
	VECTOR Pos; // 位置
	VECTOR Vel; // 速度
	Ball(); // コンストラクタ
	void SetTexture(const int &GraphHandle) const; // テクスチャ設定関数 // 未使用
	void SetPos(const VECTOR &Position); // 位置設定関数
	void Position(const float &StgRotX, const float &StgRotZ); // 移動関数
	void Draw(const MATRIX &RotationMat) const; // 描画関数
private:
	int ModelHandle; // モデルハンドル
};