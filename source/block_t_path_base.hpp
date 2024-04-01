#pragma once

#include "block_base.hpp"
#include <array>
#include <numbers>
#include <utility>

// 通路部ブロック（三角）親クラス
class BlockTPathBase : public BlockBase {
private:

	static constexpr float UnitRotAngT = DX_TWO_PI_F / 3.0F; // 単位回転角度
	static constexpr float Root3 = std::numbers::sqrt3_v<float>; // √3
	static constexpr float TwlOc = 1.5F * DX_PI_F; // １２時方向からＸ負方向の回転量
	static constexpr float TwoOc = 7.0F * DX_PI_F / 6.0F; // ２時方向からＸ負方向の回転量
	static constexpr float ForOc = 5.0F * DX_PI_F / 6.0F; // ４時方向からＸ負方向の回転量
	static constexpr float SixOc = 0.5F * DX_PI_F; // ６時方向からＸ負方向の回転量
	static constexpr float EitOc = 1.0F * DX_PI_F / 6.0F; // ８時方向からＸ負方向の回転量
	static constexpr float TenOc = 11.0F * DX_PI_F / 6.0F; // １０時方向からＸ負方向の回転量
	static constexpr float SlimWallDist = 13.0F / 6.0F; // 中心から短い壁の距離
	static constexpr float WideWallDist = 5.0F / 6.0F; // 中心から長い壁の距離

protected:

	void RotateBallPos(const int Direction, VECTOR &BallPos, VECTOR &BallVel) const; // ボール位置回転変換関数
	void TwlOcWall(const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const; // １２時方向壁衝突判定関数
	void ForOcWall(const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const; // ４時方向壁衝突判定関数
	void EitOcWall(const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const; // ８時方向壁衝突判定関数
	void TwoOcWall(const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const; // ２時方向壁衝突判定関数
	void SixOcWall(const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const; // ６時方向壁衝突判定関数
	void TenOcWall(const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const; // １０時方向壁衝突判定関数

	BlockTPathBase(); // コンストラクタ

public:

	virtual void Collision(
		const int Direction,
		const std::array<std::pair<bool, bool>, 3> &AdjacentWall,
		VECTOR &BallPos,
		VECTOR &BallVel
	) const = 0; // 衝突判定関数
};
