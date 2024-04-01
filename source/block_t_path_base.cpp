#include "block_t_path_base.hpp"
#include <cmath>

/**
 * ボール位置回転変換関数
 * @param Direction 回転方向（-2≦Direction≦2）
 * @param BallPos ボール位置
 * @param BallVel ボール速度
 */
void BlockTPathBase::RotateBallPos(const int Direction, VECTOR &BallPos, VECTOR &BallVel) const {
	// 回転変換
	const MATRIX RotationMat = MGetRotY(UnitRotAngT * Direction); // 回転行列
	BallPos = VTransformSR(BallPos, RotationMat);
	BallVel = VTransformSR(BallVel, RotationMat);
	// 終了
	return;
}

/**
 * １２時方向壁衝突判定関数
 * @param AdjacentWall 隣接壁の有無
 * @param BallPos ボール位置
 * @param BallVel ボール速度
 */
void BlockTPathBase::TwlOcWall(
	const std::array<std::pair<bool, bool>, 3> &AdjacentWall,
	VECTOR &BallPos,
	VECTOR &BallVel
) const {
	// 壁との距離と衝突角度の算出
	if(!AdjacentWall[0].first && BallPos.x < Root3 / -6.0F) {
		const float OffsetX = BallPos.x + Root3 / 6.0F, OffsetZ = BallPos.z - SlimWallDist;
		CollisionDetection(std::hypot(OffsetX, OffsetZ), std::atan2(OffsetZ, OffsetX), BallPos, BallVel);
	} else if(!AdjacentWall[0].second && BallPos.x > Root3 / 6.0F) {
		const float OffsetX = BallPos.x - Root3 / 6.0F, OffsetZ = BallPos.z - SlimWallDist;
		CollisionDetection(std::hypot(OffsetX, OffsetZ), std::atan2(OffsetZ, OffsetX), BallPos, BallVel);
	} else CollisionDetection(SlimWallDist - BallPos.z, TwlOc, BallPos, BallVel);
	// 終了
	return;
}

/**
 * ４時方向壁衝突判定関数
 * @param AdjacentWall 隣接壁の有無
 * @param BallPos ボール位置
 * @param BallVel ボール速度
 */
void BlockTPathBase::ForOcWall(
	const std::array<std::pair<bool, bool>, 3> &AdjacentWall,
	VECTOR &BallPos,
	VECTOR &BallVel
) const {
	// 壁との距離と衝突角度の算出
	if(!AdjacentWall[1].first && BallPos.x / Root3 + BallPos.z > 1.0F / 3.0F) {
		const float OffsetX = BallPos.x - 3.5F / Root3, OffsetZ = BallPos.z + WideWallDist;
		CollisionDetection(std::hypot(OffsetX, OffsetZ), std::atan2(OffsetZ, OffsetX), BallPos, BallVel);
	} else if(!AdjacentWall[1].second && BallPos.x / Root3 + BallPos.z < 1.0F / -3.0F) {
		const float OffsetX = BallPos.x - Root3, OffsetZ = BallPos.z + 4.0F / 3.0F;
		CollisionDetection(std::hypot(OffsetX, OffsetZ), std::atan2(OffsetZ, OffsetX), BallPos, BallVel);
	} else CollisionDetection(-0.5F * std::fma(BallPos.x, Root3, -13.0F / 3.0F - BallPos.z), ForOc, BallPos, BallVel);
	// 終了
	return;
}

/**
 * ８時方向壁衝突判定関数
 * @param AdjacentWall 隣接壁の有無
 * @param BallPos ボール位置
 * @param BallVel ボール速度
 */
void BlockTPathBase::EitOcWall(
	const std::array<std::pair<bool, bool>, 3> &AdjacentWall,
	VECTOR &BallPos,
	VECTOR &BallVel
) const {
	// 壁との距離と衝突角度の算出
	if(!AdjacentWall[2].first && BallPos.x / -Root3 + BallPos.z < 1.0F / -3.0F) {
		const float OffsetX = BallPos.x + Root3, OffsetZ = BallPos.z + 4.0F / 3.0F;
		CollisionDetection(std::hypot(OffsetX, OffsetZ), std::atan2(OffsetZ, OffsetX), BallPos, BallVel);
	} else if(!AdjacentWall[2].second && BallPos.x / -Root3 + BallPos.z > 1.0F / 3.0F) {
		const float OffsetX = BallPos.x + 3.5F / Root3, OffsetZ = BallPos.z + WideWallDist;
		CollisionDetection(std::hypot(OffsetX, OffsetZ), std::atan2(OffsetZ, OffsetX), BallPos, BallVel);
	} else CollisionDetection(0.5F * std::fma(BallPos.x, Root3, BallPos.z + 13.0F / 3.0F), EitOc, BallPos, BallVel);
	// 終了
	return;
}

/**
 * ２時方向壁衝突判定関数
 * @param AdjacentWall 隣接壁の有無
 * @param BallPos ボール位置
 * @param BallVel ボール速度
 */
void BlockTPathBase::TwoOcWall(
	const std::array<std::pair<bool, bool>, 3> &AdjacentWall,
	VECTOR &BallPos,
	VECTOR &BallVel
) const {
	// 壁との距離と衝突角度の算出
	if(AdjacentWall[1].second && BallPos.x / -Root3 + BallPos.z < 5.0F / -3.0F) {
		const float OffsetX = BallPos.x - Root3 / 3.0F, OffsetZ = BallPos.z + 4.0F / 3.0F;
		CollisionDetection(1.0F - std::hypot(OffsetX, OffsetZ), std::atan2(OffsetZ, OffsetX) + DX_PI_F, BallPos, BallVel);
	} else CollisionDetection(-0.5F * std::fma(BallPos.x, Root3, BallPos.z - 5.0F / 3.0F), TwoOc, BallPos, BallVel);
	// 終了
	return;
}

/**
 * ６時方向壁衝突判定関数
 * @param AdjacentWall 隣接壁の有無
 * @param BallPos ボール位置
 * @param BallVel ボール速度
 */
void BlockTPathBase::SixOcWall(
	const std::array<std::pair<bool, bool>, 3> &AdjacentWall,
	VECTOR &BallPos,
	VECTOR &BallVel
) const {
	// 壁との距離と衝突角度の算出
	if(AdjacentWall[1].first && BallPos.x > 5.0F * Root3 / 6.0F) {
		const float OffsetX = BallPos.x - 5.0F * Root3 / 6.0F, OffsetZ = BallPos.z - 1.0F / 6.0F;
		CollisionDetection(1.0F - std::hypot(OffsetX, OffsetZ), std::atan2(OffsetZ, OffsetX) + DX_PI_F, BallPos, BallVel);
	} else if(AdjacentWall[2].second && BallPos.x < 5.0F * Root3 / -6.0F) {
		const float OffsetX = BallPos.x + 5.0F * Root3 / 6.0F, OffsetZ = BallPos.z - 1.0F / 6.0F;
		CollisionDetection(1.0F - std::hypot(OffsetX, OffsetZ), std::atan2(OffsetZ, OffsetX) + DX_PI_F, BallPos, BallVel);
	} else CollisionDetection(BallPos.z + 5.0F / 6.0F, SixOc, BallPos, BallVel);
	// 終了
	return;
}

/**
 * １０時方向壁衝突判定関数
 * @param AdjacentWall 隣接壁の有無
 * @param BallPos ボール位置
 * @param BallVel ボール速度
 */
void BlockTPathBase::TenOcWall(
	const std::array<std::pair<bool, bool>, 3> &AdjacentWall,
	VECTOR &BallPos,
	VECTOR &BallVel
) const {
	// 壁との距離と衝突角度の算出
	if(AdjacentWall[2].first && BallPos.x / Root3 + BallPos.z < 5.0F / -3.0F) {
		const float OffsetX = BallPos.x + Root3 / 3.0F, OffsetZ = BallPos.z + 4.0F / 3.0F;
		CollisionDetection(1.0F - std::hypot(OffsetX, OffsetZ), std::atan2(OffsetZ, OffsetX) + DX_PI_F, BallPos, BallVel);
	} else CollisionDetection(0.5F * std::fma(BallPos.x, Root3, 5.0F / 3.0F - BallPos.z), TenOc, BallPos, BallVel);
	// 終了
	return;
}

/**
 * コンストラクタ
 */
BlockTPathBase::BlockTPathBase() {
	// 音声の読込
	CollisionSoundHandle = LoadSoundMem("sounds\\collision_sound_b.mp3", 8); // 衝突音
	// 終了
	return;
}
