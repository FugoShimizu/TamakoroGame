#pragma once
#include "block_q_path_base.h"

// �b�^�ʘH���u���b�N�i�l�p�j�N���X
class BlockQPathC : public BlockQPathBase {
public:
	BlockQPathC(); // �R���X�g���N�^
	void Collision(const int &Direction, VECTOR &BallPos, VECTOR &BallVel) const; // �Փ˔���֐�
};