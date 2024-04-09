#include "ball.h"

// コンストラクタ
Ball::Ball() {
	// メンバ変数の初期化
	SetPos(VGet(0.0F, 0.0F, 0.0F));
	// モデルの読込
	ModelHandle = MV1LoadModel("models\\ball.mv1");
	// 終了
	return;
}

// テクスチャ設定関数
void Ball::SetTexture(const int &GraphHandle) const {
	// テクスチャの変更
	MV1SetTextureGraphHandle(ModelHandle, 0, GraphHandle, FALSE);
	// 終了
	return;
}

// 位置設定関数
void Ball::SetPos(const VECTOR &Position) {
	// ボール位置の設定
	Pos = Position;
	Vel = VGet(0.0F, 0.0F, 0.0F);
	// 終了
	return;
}

// 移動関数
void Ball::Position(const float &StgRotX, const float &StgRotZ) {
	// ボール位置の計算
	Vel = VAdd(Vel, VScale(VGet(-StgRotZ, 0.0F, StgRotX), 0.02F)); // 加減速
	Vel = VScale(Vel, 0.984375F); // 摩擦力による減速
	Pos = VAdd(Pos, Vel); // 速度に応じて位置を移動
	// 終了
	return;
}

// 描画関数
void Ball::Draw(const MATRIX &RotationMat) const {
	// ボールの描画
	MV1SetPosition(ModelHandle, VTransformSR(Pos, RotationMat));
	MV1DrawModel(ModelHandle);
	// 終了
	return;
}