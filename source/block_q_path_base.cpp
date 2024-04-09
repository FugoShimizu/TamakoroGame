#include <cmath>
#include "block_q_path_base.h"

// �R���X�g���N�^
BlockQPathBase::BlockQPathBase() {
	// �����̓Ǎ�
	CollisionSoundHandle = LoadSoundMem("sounds\\collision_sound_a.mp3", 8); // �Փˉ�
	// �I��
	return;
}

// �{�[���ʒu��]�ϊ��֐�
void BlockQPathBase::RotateBallPos(const int &Direction, VECTOR &BallPos, VECTOR &BallVel) const {
	// ��]�ϊ�
	const MATRIX RotationMat = MGetRotY(Direction * UnitRotAngQ); // ��]�s��
	BallPos = VTransformSR(BallPos, RotationMat);
	BallVel = VTransformSR(BallVel, RotationMat);
	// �I��
	return;
}

// �����ǏՓ˔���֐�
void BlockQPathBase::LeftWall(VECTOR &BallPos, VECTOR &BallVel) const {
	// �ǂƂ̋����ƏՓˊp�x�̎Z�o
	CollisionDetection(1.5F + BallPos.x, 0.0F, BallPos, BallVel);
	// �I��
	return;
}

// �E���ǏՓ˔���֐�
void BlockQPathBase::RightWall(VECTOR &BallPos, VECTOR &BallVel) const {
	// �ǂƂ̋����ƏՓˊp�x�̎Z�o
	CollisionDetection(1.5F - BallPos.x, DX_PI_F, BallPos, BallVel);
	// �I��
	return;
}

// ����ǏՓ˔���֐�
void BlockQPathBase::BackWall(VECTOR &BallPos, VECTOR &BallVel) const {
	// �ǂƂ̋����ƏՓˊp�x�̎Z�o
	CollisionDetection(1.5F + BallPos.z, DX_PI_F * 0.5F, BallPos, BallVel);
	// �I��
	return;
}

// �O���ǏՓ˔���֐�
void BlockQPathBase::FrontWall(VECTOR &BallPos, VECTOR &BallVel) const {
	// �ǂƂ̋����ƏՓˊp�x�̎Z�o
	CollisionDetection(1.5F - BallPos.z, DX_PI_F * 1.5F, BallPos, BallVel);
	// �I��
	return;
}

// ������p�Փ˔���֐�
void BlockQPathBase::LeftBackCorner(VECTOR &BallPos, VECTOR &BallVel) const {
	// �p�Ƃ̋����ƏՓˊp�x�̎Z�o
	if(BallPos.z < -1.5F) LeftWall(BallPos, BallVel);
	else if(BallPos.x < -1.5F) BackWall(BallPos, BallVel);
	else CollisionDetection(hypotf(BallPos.x + 1.5F, BallPos.z + 1.5F), atan2f(BallPos.z + 1.5F, BallPos.x + 1.5F), BallPos, BallVel);
	// �I��
	return;
}

// ���O���p�Փ˔���֐�
void BlockQPathBase::LeftFrontCorner(VECTOR &BallPos, VECTOR &BallVel) const {
	// �p�Ƃ̋����ƏՓˊp�x�̎Z�o
	if(BallPos.z > 1.5F) LeftWall(BallPos, BallVel);
	else if(BallPos.x < -1.5F) FrontWall(BallPos, BallVel);
	else CollisionDetection(hypotf(BallPos.x + 1.5F, BallPos.z - 1.5F), atan2f(BallPos.z - 1.5F, BallPos.x + 1.5F), BallPos, BallVel);
	// �I��
	return;
}

// �E����p�Փ˔���֐�
void BlockQPathBase::RightBackCorner(VECTOR &BallPos, VECTOR &BallVel) const {
	// �p�Ƃ̋����ƏՓˊp�x�̎Z�o
	if(BallPos.z < -1.5F) RightWall(BallPos, BallVel);
	else if(BallPos.x > 1.5F) BackWall(BallPos, BallVel);
	else CollisionDetection(hypotf(BallPos.x - 1.5F, BallPos.z + 1.5F), atan2f(BallPos.z + 1.5F, BallPos.x - 1.5F), BallPos, BallVel);
	// �I��
	return;
}

// �E�O���p�Փ˔���֐�
void BlockQPathBase::RightFrontCorner(VECTOR &BallPos, VECTOR &BallVel) const {
	// �p�Ƃ̋����ƏՓˊp�x�̎Z�o
	if(BallPos.z > 1.5F) RightWall(BallPos, BallVel);
	else if(BallPos.x > 1.5F) FrontWall(BallPos, BallVel);
	else CollisionDetection(hypotf(BallPos.x - 1.5F, BallPos.z - 1.5F), atan2f(BallPos.z - 1.5F, BallPos.x - 1.5F), BallPos, BallVel);
	// �I��
	return;
}