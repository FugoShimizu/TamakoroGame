#pragma once
#include <DxLib.h>

// カメラ（視点）クラス
class Camera {
public:
	Camera(); // コンストラクタ
	void Move(const VECTOR &BallPosition, const float &CamAngLowLim, const bool &CursorOnMiniMap); // 移動関数
	float GetDirection() const; // 方向角取得関数
	void DrawBackground() const; // 背景描画関数
private:
	constexpr static float UnitMoveAng = DX_PI_F / 64.0f; // 単位移動角度
	int Viewpoint; // 視点
	int DirectionV; // 仰角（水平方向から上向き，64=180°）
	int DirectionH; // 方向角（Z負方向から右回り，64=180°）
	float PositionY; // 仰角から算出したY座標
	float PositionR; // 仰角から算出した中心からの距離
	float PositionX; // 方向角から算出したX座標
	float PositionZ; // 方向角から算出したZ座標
	VECTOR Position;
	VECTOR Overhead;
	int Distance; // 対象距離
	int BGGraphHandle; // 背景グラフハンドル
	void Reset(); // 位置初期化関数
	void Control(const float &CamAngLowLim, const bool &CursorOnMiniMap); // 操作関数
};