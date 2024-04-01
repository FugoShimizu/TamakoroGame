#include "block_q_path_base.hpp"
#include <cmath>

/**
 * ボール位置回転変換関数
 * @param Direction 回転方向（-3≦Direction≦3）
 * @param BallPos ボール位置
 * @param BallVel ボール速度
 */
void BlockQPathBase::RotateBallPos(const int Direction, VECTOR &BallPos, VECTOR &BallVel) const {
	// 回転変換
	const MATRIX RotationMat = MGetRotY(UnitRotAngQ * Direction); // 回転行列
	BallPos = VTransformSR(BallPos, RotationMat);
	BallVel = VTransformSR(BallVel, RotationMat);
	// 終了
	return;
}

/**
 * 左側壁衝突判定関数
 * @param BallPos ボール位置
 * @param BallVel ボール速度
 */
void BlockQPathBase::LeftWall(VECTOR &BallPos, VECTOR &BallVel) const {
	// 壁との距離と衝突角度の算出
	CollisionDetection(BallPos.x + 1.5F, 0.0F, BallPos, BallVel);
	// 終了
	return;
}

/**
 * 右側壁衝突判定関数
 * @param BallPos ボール位置
 * @param BallVel ボール速度
 */
void BlockQPathBase::RightWall(VECTOR &BallPos, VECTOR &BallVel) const {
	// 壁との距離と衝突角度の算出
	CollisionDetection(1.5F - BallPos.x, DX_PI_F, BallPos, BallVel);
	// 終了
	return;
}

/**
 * 後方壁衝突判定関数
 * @param BallPos ボール位置
 * @param BallVel ボール速度
 */
void BlockQPathBase::BackWall(VECTOR &BallPos, VECTOR &BallVel) const {
	// 壁との距離と衝突角度の算出
	CollisionDetection(BallPos.z + 1.5F, 0.5F * DX_PI_F, BallPos, BallVel);
	// 終了
	return;
}

/**
 * 前方壁衝突判定関数
 * @param BallPos ボール位置
 * @param BallVel ボール速度
 */
void BlockQPathBase::FrontWall(VECTOR &BallPos, VECTOR &BallVel) const {
	// 壁との距離と衝突角度の算出
	CollisionDetection(1.5F - BallPos.z, 1.5F * DX_PI_F, BallPos, BallVel);
	// 終了
	return;
}

/**
 * 左後方角衝突判定関数
 * @param BallPos ボール位置
 * @param BallVel ボール速度
 */
void BlockQPathBase::LeftBackCorner(VECTOR &BallPos, VECTOR &BallVel) const {
	// 角との距離と衝突角度の算出
	if(BallPos.z < -1.5F) LeftWall(BallPos, BallVel);
	else if(BallPos.x < -1.5F) BackWall(BallPos, BallVel);
	else {
		const float OffsetX = BallPos.x + 1.5F, OffsetZ = BallPos.z + 1.5F;
		CollisionDetection(std::hypot(OffsetX, OffsetZ), std::atan2(OffsetZ, OffsetX), BallPos, BallVel);
	}
	// 終了
	return;
}

/**
 * 左前方角衝突判定関数
 * @param BallPos ボール位置
 * @param BallVel ボール速度
 */
void BlockQPathBase::LeftFrontCorner(VECTOR &BallPos, VECTOR &BallVel) const {
	// 角との距離と衝突角度の算出
	if(BallPos.z > 1.5F) LeftWall(BallPos, BallVel);
	else if(BallPos.x < -1.5F) FrontWall(BallPos, BallVel);
	else {
		const float OffsetX = BallPos.x + 1.5F, OffsetZ = BallPos.z - 1.5F;
		CollisionDetection(std::hypot(OffsetX, OffsetZ), std::atan2(OffsetZ, OffsetX), BallPos, BallVel);
	}
	// 終了
	return;
}

/**
 * 右後方角衝突判定関数
 * @param BallPos ボール位置
 * @param BallVel ボール速度
 */
void BlockQPathBase::RightBackCorner(VECTOR &BallPos, VECTOR &BallVel) const {
	// 角との距離と衝突角度の算出
	if(BallPos.z < -1.5F) RightWall(BallPos, BallVel);
	else if(BallPos.x > 1.5F) BackWall(BallPos, BallVel);
	else {
		const float OffsetX = BallPos.x - 1.5F, OffsetZ = BallPos.z + 1.5F;
		CollisionDetection(std::hypot(OffsetX, OffsetZ), std::atan2(OffsetZ, OffsetX), BallPos, BallVel);
	}
	// 終了
	return;
}

/**
 * 右前方角衝突判定関数
 * @param BallPos ボール位置
 * @param BallVel ボール速度
 */
void BlockQPathBase::RightFrontCorner(VECTOR &BallPos, VECTOR &BallVel) const {
	// 角との距離と衝突角度の算出
	if(BallPos.z > 1.5F) RightWall(BallPos, BallVel);
	else if(BallPos.x > 1.5F) FrontWall(BallPos, BallVel);
	else {
		const float OffsetX = BallPos.x - 1.5F, OffsetZ = BallPos.z - 1.5F;
		CollisionDetection(std::hypot(OffsetX, OffsetZ), std::atan2(OffsetZ, OffsetX), BallPos, BallVel);
	}
	// 終了
	return;
}

/**
 * コンストラクタ
 */
BlockQPathBase::BlockQPathBase() {
	// 音声の読込
	CollisionSoundHandle = LoadSoundMem("sounds\\collision_sound_a.mp3", 8); // 衝突音
	// 終了
	return;
}
