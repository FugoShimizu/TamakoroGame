#pragma once
#include "block_base.h"

// �ʘH���u���b�N�i�l�p�j�e�N���X
class BlockQPathBase : public BlockBase {
public:
	virtual void Collision(const int &direction, VECTOR &BallPos, VECTOR &BallVel) const = 0; // �Փ˔���֐�
protected:
	BlockQPathBase(); // �R���X�g���N�^
	void RotateBallPos(const int &Direction, VECTOR &BallPos, VECTOR &BallVel) const; // �{�[���ʒu��]�ϊ��֐�
	void LeftWall(VECTOR &BallPos, VECTOR &BallVel) const; // �����ǏՓ˔���֐�
	void RightWall(VECTOR &BallPos, VECTOR &BallVel) const; // �E���ǏՓ˔���֐�
	void BackWall(VECTOR &BallPos, VECTOR &BallVel) const; // ����ǏՓ˔���֐�
	void FrontWall(VECTOR &BallPos, VECTOR &BallVel) const; // �O���ǏՓ˔���֐�
	void LeftBackCorner(VECTOR &BallPos, VECTOR &BallVel) const; // ������p�Փ˔���֐�
	void LeftFrontCorner(VECTOR &BallPos, VECTOR &BallVel) const; // ���O���p�Փ˔���֐�
	void RightBackCorner(VECTOR &BallPos, VECTOR &BallVel) const; // �E����p�Փ˔���֐�
	void RightFrontCorner(VECTOR &BallPos, VECTOR &BallVel) const; // �E�O���p�Փ˔���֐�
private:
	static constexpr float UnitRotAngQ = 0.5F * DX_PI_F; // �P�ʉ�]�p�x
};