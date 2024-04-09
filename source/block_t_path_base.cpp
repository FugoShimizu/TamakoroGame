#include <cmath>
#include "block_t_path_base.h"

// コンストラクタ
BlockTPathBase::BlockTPathBase() {
	// 音声の読込
	CollisionSoundHandle = LoadSoundMem("sounds\\collision_sound_b.mp3", 8); // 衝突音
	// 終了
	return;
}

// ボール位置回転変換関数
void BlockTPathBase::RotateBallPos(const int &Direction, VECTOR &BallPos, VECTOR &BallVel) const {
	// 回転変換
	const MATRIX RotationMat = MGetRotY(Direction * UnitRotAngT); // 回転行列
	BallPos = VTransformSR(BallPos, RotationMat);
	BallVel = VTransformSR(BallVel, RotationMat);
	// 終了
	return;
}

// 12時方向壁衝突判定関数
void BlockTPathBase::TwlOcWall(const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const {
	// 壁との距離と衝突角度の算出
	if(!AdjacentWall[0].first && BallPos.x < Root3 / -6.0F) CollisionDetection(hypotf(BallPos.x + Root3 / 6.0F, BallPos.z - SlimWallDist), atan2f(BallPos.z - SlimWallDist, BallPos.x + Root3 / 6.0F), BallPos, BallVel);
	else if(!AdjacentWall[0].second && BallPos.x > Root3 / 6.0F) CollisionDetection(hypotf(BallPos.x - Root3 / 6.0F, BallPos.z - SlimWallDist), atan2f(BallPos.z - SlimWallDist, BallPos.x - Root3 / 6.0F), BallPos, BallVel);
	else CollisionDetection(SlimWallDist - BallPos.z, TwlOc, BallPos, BallVel);
	// 終了
	return;
}

// 4時方向壁衝突判定関数
void BlockTPathBase::ForOcWall(const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const {
	// 壁との距離と衝突角度の算出
	if(!AdjacentWall[1].first && BallPos.x / Root3 + BallPos.z > 1.0F / 3.0F) CollisionDetection(hypotf(BallPos.x - 7.0F / Root3 / 2.0F, BallPos.z + WideWallDist), atan2f(BallPos.z + WideWallDist, BallPos.x - 7.0F / Root3 / 2.0F), BallPos, BallVel);
	else if(!AdjacentWall[1].second && BallPos.x / Root3 + BallPos.z < 1.0F / -3.0F) CollisionDetection(hypotf(BallPos.x - Root3, BallPos.z + 4.0F / 3.0F), atan2f(BallPos.z + 4.0F / 3.0F, BallPos.x - Root3), BallPos, BallVel);
	else CollisionDetection(fmaf(BallPos.x, Root3, -BallPos.z - 13.0F / 3.0F) * -0.5F, ForOc, BallPos, BallVel);
	// 終了
	return;
}

// 8時方向壁衝突判定関数
void BlockTPathBase::EitOcWall(const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const {
	// 壁との距離と衝突角度の算出
	if(!AdjacentWall[2].first && BallPos.x / -Root3 + BallPos.z < 1.0F / -3.0F) CollisionDetection(hypotf(BallPos.x + Root3, BallPos.z + 4.0F / 3.0F), atan2f(BallPos.z + 4.0F / 3.0F, BallPos.x + Root3), BallPos, BallVel);
	else if(!AdjacentWall[2].second && BallPos.x / -Root3 + BallPos.z > 1.0F / 3.0F) CollisionDetection(hypotf(BallPos.x + 7.0F / Root3 / 2.0F, BallPos.z + WideWallDist), atan2f(BallPos.z + WideWallDist, BallPos.x + 7.0F / Root3 / 2.0F), BallPos, BallVel);
	else CollisionDetection(fmaf(BallPos.x, Root3, BallPos.z + 13.0F / 3.0F) * 0.5F, EitOc, BallPos, BallVel);
	// 終了
	return;
}

// 2時方向壁衝突判定関数
void BlockTPathBase::TwoOcWall(const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const {
	// 壁との距離と衝突角度の算出
	if(AdjacentWall[1].second && BallPos.x / -Root3 + BallPos.z < 5.0F / -3.0F) CollisionDetection(1.0F - hypotf(BallPos.x - Root3 / 3.0F, BallPos.z + 4.0F / 3.0F), atan2f(BallPos.z + 4.0F / 3.0F, BallPos.x - Root3 / 3.0F) + DX_PI_F, BallPos, BallVel);
	else CollisionDetection(fmaf(BallPos.x, Root3, BallPos.z - 5.0F / 3.0F) * -0.5F, TwoOc, BallPos, BallVel);
	// 終了
	return;
}

// 6時方向壁衝突判定関数
void BlockTPathBase::SixOcWall(const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const {
	// 壁との距離と衝突角度の算出
	if(AdjacentWall[1].first && BallPos.x > Root3 * 5.0F / 6.0F) CollisionDetection(1.0F - hypotf(BallPos.x - Root3 * 5.0F / 6.0F, BallPos.z - 1.0F / 6.0F), atan2f(BallPos.z - 1.0F / 6.0F, BallPos.x - Root3 * 5.0F / 6.0F) + DX_PI_F, BallPos, BallVel);
	else if(AdjacentWall[2].second && BallPos.x < Root3 * 5.0F / -6.0F) CollisionDetection(1.0F - hypotf(BallPos.x + Root3 * 5.0F / 6.0F, BallPos.z - 1.0F / 6.0F), atan2f(BallPos.z - 1.0F / 6.0F, BallPos.x + Root3 * 5.0F / 6.0F) + DX_PI_F, BallPos, BallVel);
	else CollisionDetection(5.0F / 6.0F + BallPos.z, SixOc, BallPos, BallVel);
	// 終了
	return;
}

// 10時方向壁衝突判定関数
void BlockTPathBase::TenOcWall(const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const {
	// 壁との距離と衝突角度の算出
	if(AdjacentWall[2].first && BallPos.x / Root3 + BallPos.z < 5.0F / -3.0F) CollisionDetection(1.0F - hypotf(BallPos.x + Root3 / 3.0F, BallPos.z + 4.0F / 3.0F), atan2f(BallPos.z + 4.0F / 3.0F, BallPos.x + Root3 / 3.0F) + DX_PI_F, BallPos, BallVel);
	else CollisionDetection(fmaf(BallPos.x, Root3, -BallPos.z + 5.0F / 3.0F) * 0.5F, TenOc, BallPos, BallVel);
	// 終了
	return;
}