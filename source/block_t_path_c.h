#pragma once
#include "block_t_path_base.h"

// �b�^�ʘH���u���b�N�i�O�p�j�N���X
class BlockTPathC : public BlockTPathBase {
public:
	BlockTPathC(); // �R���X�g���N�^
	void Collision(const int &Direction, const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const; // �Փ˔���֐�
};