#include <cmath>
#include "block_t_path_base.h"

// �R���X�g���N�^
BlockTPathBase::BlockTPathBase() {
	// �����̓Ǎ�
	CollisionSoundHandle = LoadSoundMem("sounds\\collision_sound_b.mp3", 8); // �Փˉ�
	// �I��
	return;
}

// �{�[���ʒu��]�ϊ��֐�
void BlockTPathBase::RotateBallPos(const int &Direction, VECTOR &BallPos, VECTOR &BallVel) const {
	// ��]�ϊ�
	const MATRIX RotationMat = MGetRotY(UnitRotAngT * Direction); // ��]�s��
	BallPos = VTransformSR(BallPos, RotationMat);
	BallVel = VTransformSR(BallVel, RotationMat);
	// �I��
	return;
}

// 12�������ǏՓ˔���֐�
void BlockTPathBase::TwlOcWall(const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const {
	// �ǂƂ̋����ƏՓˊp�x�̎Z�o
	if(!AdjacentWall[0].first && BallPos.x < Root3 / -6.0F) CollisionDetection(hypotf(BallPos.x + Root3 / 6.0F, BallPos.z - SlimWallDist), atan2f(BallPos.z - SlimWallDist, BallPos.x + Root3 / 6.0F), BallPos, BallVel);
	else if(!AdjacentWall[0].second && BallPos.x > Root3 / 6.0F) CollisionDetection(hypotf(BallPos.x - Root3 / 6.0F, BallPos.z - SlimWallDist), atan2f(BallPos.z - SlimWallDist, BallPos.x - Root3 / 6.0F), BallPos, BallVel);
	else CollisionDetection(SlimWallDist - BallPos.z, TwlOc, BallPos, BallVel);
	// �I��
	return;
}

// 4�������ǏՓ˔���֐�
void BlockTPathBase::ForOcWall(const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const {
	// �ǂƂ̋����ƏՓˊp�x�̎Z�o
	if(!AdjacentWall[1].first && BallPos.x / Root3 + BallPos.z > 1.0F / 3.0F) CollisionDetection(hypotf(BallPos.x - 3.5F / Root3, BallPos.z + WideWallDist), atan2f(BallPos.z + WideWallDist, BallPos.x - 3.5F / Root3), BallPos, BallVel);
	else if(!AdjacentWall[1].second && BallPos.x / Root3 + BallPos.z < 1.0F / -3.0F) CollisionDetection(hypotf(BallPos.x - Root3, BallPos.z + 4.0F / 3.0F), atan2f(BallPos.z + 4.0F / 3.0F, BallPos.x - Root3), BallPos, BallVel);
	else CollisionDetection(-0.5F * fmaf(BallPos.x, Root3, -BallPos.z - 13.0F / 3.0F), ForOc, BallPos, BallVel);
	// �I��
	return;
}

// 8�������ǏՓ˔���֐�
void BlockTPathBase::EitOcWall(const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const {
	// �ǂƂ̋����ƏՓˊp�x�̎Z�o
	if(!AdjacentWall[2].first && BallPos.x / -Root3 + BallPos.z < 1.0F / -3.0F) CollisionDetection(hypotf(BallPos.x + Root3, BallPos.z + 4.0F / 3.0F), atan2f(BallPos.z + 4.0F / 3.0F, BallPos.x + Root3), BallPos, BallVel);
	else if(!AdjacentWall[2].second && BallPos.x / -Root3 + BallPos.z > 1.0F / 3.0F) CollisionDetection(hypotf(BallPos.x + 3.5F / Root3, BallPos.z + WideWallDist), atan2f(BallPos.z + WideWallDist, BallPos.x + 3.5F / Root3), BallPos, BallVel);
	else CollisionDetection(0.5F * fmaf(BallPos.x, Root3, BallPos.z + 13.0F / 3.0F), EitOc, BallPos, BallVel);
	// �I��
	return;
}

// 2�������ǏՓ˔���֐�
void BlockTPathBase::TwoOcWall(const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const {
	// �ǂƂ̋����ƏՓˊp�x�̎Z�o
	if(AdjacentWall[1].second && BallPos.x / -Root3 + BallPos.z < 5.0F / -3.0F) CollisionDetection(1.0F - hypotf(BallPos.x - Root3 / 3.0F, BallPos.z + 4.0F / 3.0F), atan2f(BallPos.z + 4.0F / 3.0F, BallPos.x - Root3 / 3.0F) + DX_PI_F, BallPos, BallVel);
	else CollisionDetection(-0.5F * fmaf(BallPos.x, Root3, BallPos.z - 5.0F / 3.0F), TwoOc, BallPos, BallVel);
	// �I��
	return;
}

// 6�������ǏՓ˔���֐�
void BlockTPathBase::SixOcWall(const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const {
	// �ǂƂ̋����ƏՓˊp�x�̎Z�o
	if(AdjacentWall[1].first && BallPos.x > 5.0F * Root3 / 6.0F) CollisionDetection(1.0F - hypotf(BallPos.x - 5.0F * Root3 / 6.0F, BallPos.z - 1.0F / 6.0F), atan2f(BallPos.z - 1.0F / 6.0F, BallPos.x - 5.0F * Root3 / 6.0F) + DX_PI_F, BallPos, BallVel);
	else if(AdjacentWall[2].second && BallPos.x < 5.0F * Root3 / -6.0F) CollisionDetection(1.0F - hypotf(BallPos.x + 5.0F * Root3 / 6.0F, BallPos.z - 1.0F / 6.0F), atan2f(BallPos.z - 1.0F / 6.0F, BallPos.x + 5.0F * Root3 / 6.0F) + DX_PI_F, BallPos, BallVel);
	else CollisionDetection(5.0F / 6.0F + BallPos.z, SixOc, BallPos, BallVel);
	// �I��
	return;
}

// 10�������ǏՓ˔���֐�
void BlockTPathBase::TenOcWall(const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const {
	// �ǂƂ̋����ƏՓˊp�x�̎Z�o
	if(AdjacentWall[2].first && BallPos.x / Root3 + BallPos.z < 5.0F / -3.0F) CollisionDetection(1.0F - hypotf(BallPos.x + Root3 / 3.0F, BallPos.z + 4.0F / 3.0F), atan2f(BallPos.z + 4.0F / 3.0F, BallPos.x + Root3 / 3.0F) + DX_PI_F, BallPos, BallVel);
	else CollisionDetection(0.5F * fmaf(BallPos.x, Root3, -BallPos.z + 5.0F / 3.0F), TenOc, BallPos, BallVel);
	// �I��
	return;
}