#pragma once

#include <DxLib.h>

// カメラ（視点）クラス
class Camera {
private:

	static constexpr float UnitMoveAng = DX_PI_F / 64.0F; // 単位移動角度
	unsigned int Viewpoint; // 視点
	int DirectionV; // 仰角（水平方向から上向き，64=180°）
	int DirectionH; // 方向角（Ｚ負方向から右回り，64=180°）
	float PositionY; // 仰角から算出したＹ座標
	float PositionR; // 仰角から算出した中心からの距離
	float PositionX; // 方向角から算出したＸ座標
	float PositionZ; // 方向角から算出したＺ座標
	VECTOR Position;
	VECTOR Overhead;
	int Distance; // 対象距離
	int BGGraphHandle = -1; // 背景グラフハンドル
	void Reset(); // 位置初期化関数
	void Control(const float CamAngLowLim, const bool IsCursorOnMiniMap); // 操作関数

public:

	float GetDirection() const; // 方向角取得関数
	void DrawBackground() const; // 背景描画関数
	void Move(const VECTOR &BallLocation, const float CamAngLowLim, const bool IsCursorOnMiniMap); // 移動関数

	Camera &operator=(const Camera &) = delete; // コピー代入演算子（禁止）
	Camera(const Camera &) = delete; // コピーコンストラクタ（禁止）

	Camera(); // コンストラクタ
	~Camera(); // デストラクタ
};
