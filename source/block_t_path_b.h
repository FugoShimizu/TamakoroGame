#pragma once
#include "block_t_path_base.h"

// �a�^�ʘH���u���b�N�i�O�p�j�N���X
class BlockTPathB : public BlockTPathBase {
public:
	BlockTPathB(); // �R���X�g���N�^
	void Collision(const int &Direction, const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const; // �Փ˔���֐�
};