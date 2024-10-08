#pragma once
#include <array>
#include <numbers>
#include <utility>
#include "block_base.h"

// 通路部ブロック（三角）親クラス
class BlockTPathBase : public BlockBase {
public:
	virtual void Collision(const int &Direction, const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const = 0; // 衝突判定関数
protected:
	BlockTPathBase(); // コンストラクタ
	void RotateBallPos(const int &Direction, VECTOR &BallPos, VECTOR &BallVel) const; // ボール位置回転変換関数
	void TwlOcWall(const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const; // 12時方向壁衝突判定関数
	void ForOcWall(const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const; // 4時方向壁衝突判定関数
	void EitOcWall(const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const; // 8時方向壁衝突判定関数
	void TwoOcWall(const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const; // 2時方向壁衝突判定関数
	void SixOcWall(const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const; // 6時方向壁衝突判定関数
	void TenOcWall(const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const; // 10時方向壁衝突判定関数
private:
	static constexpr float UnitRotAngT = DX_TWO_PI_F / 3.0F; // 単位回転角度
	static constexpr float Root3 = std::numbers::sqrt3_v<float>; // √3
	static constexpr float TwlOc = 1.5F * DX_PI_F; // 12時方向からX負方向の回転量
	static constexpr float TwoOc = 7.0F * DX_PI_F / 6.0F; // 2時方向からX負方向の回転量
	static constexpr float ForOc = 5.0F * DX_PI_F / 6.0F; // 4時方向からX負方向の回転量
	static constexpr float SixOc = 0.5F * DX_PI_F; // 6時方向からX負方向の回転量
	static constexpr float EitOc = 1.0F * DX_PI_F / 6.0F; // 8時方向からX負方向の回転量
	static constexpr float TenOc = 11.0F * DX_PI_F / 6.0F; // 10時方向からX負方向の回転量
	static constexpr float SlimWallDist = 13.0F / 6.0F; // 中心から短い壁の距離
	static constexpr float WideWallDist = 5.0F / 6.0F; // 中心から長い壁の距離
};