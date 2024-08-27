#pragma once
#include <array>
#include <numbers>
#include <utility>
#include "block_base.h"

// �ʘH���u���b�N�i�O�p�j�e�N���X
class BlockTPathBase : public BlockBase {
public:
	virtual void Collision(const int &Direction, const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const = 0; // �Փ˔���֐�
protected:
	BlockTPathBase(); // �R���X�g���N�^
	void RotateBallPos(const int &Direction, VECTOR &BallPos, VECTOR &BallVel) const; // �{�[���ʒu��]�ϊ��֐�
	void TwlOcWall(const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const; // 12�������ǏՓ˔���֐�
	void ForOcWall(const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const; // 4�������ǏՓ˔���֐�
	void EitOcWall(const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const; // 8�������ǏՓ˔���֐�
	void TwoOcWall(const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const; // 2�������ǏՓ˔���֐�
	void SixOcWall(const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const; // 6�������ǏՓ˔���֐�
	void TenOcWall(const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const; // 10�������ǏՓ˔���֐�
private:
	static constexpr float UnitRotAngT = DX_TWO_PI_F / 3.0F; // �P�ʉ�]�p�x
	static constexpr float Root3 = std::numbers::sqrt3_v<float>; // ��3
	static constexpr float TwlOc = 1.5F * DX_PI_F; // 12����������X�������̉�]��
	static constexpr float TwoOc = 7.0F * DX_PI_F / 6.0F; // 2����������X�������̉�]��
	static constexpr float ForOc = 5.0F * DX_PI_F / 6.0F; // 4����������X�������̉�]��
	static constexpr float SixOc = 0.5F * DX_PI_F; // 6����������X�������̉�]��
	static constexpr float EitOc = 1.0F * DX_PI_F / 6.0F; // 8����������X�������̉�]��
	static constexpr float TenOc = 11.0F * DX_PI_F / 6.0F; // 10����������X�������̉�]��
	static constexpr float SlimWallDist = 13.0F / 6.0F; // ���S����Z���ǂ̋���
	static constexpr float WideWallDist = 5.0F / 6.0F; // ���S���璷���ǂ̋���
};