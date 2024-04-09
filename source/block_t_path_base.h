#pragma once
#include <array>
#include <numbers>
#include <utility>
#include "block_base.h"

// �ʘH���u���b�N�i�O�p�j�e�N���X
class BlockTPathBase : public BlockBase {
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
	static constexpr float TwlOc = DX_PI_F * 1.5F; // 12����������X�������̉�]��
	static constexpr float TwoOc = DX_PI_F * 7.0F / 6.0F; // 2����������X�������̉�]��
	static constexpr float ForOc = DX_PI_F * 5.0F / 6.0F; // 4����������X�������̉�]��
	static constexpr float SixOc = DX_PI_F * 0.5F; // 6����������X�������̉�]��
	static constexpr float EitOc = DX_PI_F * 1.0F / 6.0F; // 8����������X�������̉�]��
	static constexpr float TenOc = DX_PI_F * 11.0F / 6.0F; // 10����������X�������̉�]��
	static constexpr float SlimWallDist = 13.0F / 6.0F; // ���S����Z���ǂ̋���
	static constexpr float WideWallDist = 5.0F / 6.0F; // ���S���璷���ǂ̋���
};