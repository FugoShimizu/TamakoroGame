#pragma once
#include "block_base.h"

// 通路部ブロック（四角）親クラス
class BlockQPathBase : public BlockBase {
public:
	virtual void Collision(const int &direction, VECTOR &BallPos, VECTOR &BallVel) const = 0; // 衝突判定関数
protected:
	BlockQPathBase(); // コンストラクタ
	void RotateBallPos(const int &Direction, VECTOR &BallPos, VECTOR &BallVel) const; // ボール位置回転変換関数
	void LeftWall(VECTOR &BallPos, VECTOR &BallVel) const; // 左側壁衝突判定関数
	void RightWall(VECTOR &BallPos, VECTOR &BallVel) const; // 右側壁衝突判定関数
	void BackWall(VECTOR &BallPos, VECTOR &BallVel) const; // 後方壁衝突判定関数
	void FrontWall(VECTOR &BallPos, VECTOR &BallVel) const; // 前方壁衝突判定関数
	void LeftBackCorner(VECTOR &BallPos, VECTOR &BallVel) const; // 左後方角衝突判定関数
	void LeftFrontCorner(VECTOR &BallPos, VECTOR &BallVel) const; // 左前方角衝突判定関数
	void RightBackCorner(VECTOR &BallPos, VECTOR &BallVel) const; // 右後方角衝突判定関数
	void RightFrontCorner(VECTOR &BallPos, VECTOR &BallVel) const; // 右前方角衝突判定関数
private:
	static constexpr float UnitRotAngQ = 0.5F * DX_PI_F; // 単位回転角度
};