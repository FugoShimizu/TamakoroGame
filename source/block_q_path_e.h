#pragma once
#include "block_q_path_base.h"

// �d�^�ʘH���u���b�N�i�l�p�j�N���X
class BlockQPathE : public BlockQPathBase {
public:
	BlockQPathE(); // �R���X�g���N�^
	void Collision(const int &Direction, VECTOR &BallPos, VECTOR &BallVel) const; // �Փ˔���֐�
};