#pragma once
#include "block_q_path_base.h"

// �c�^�ʘH���u���b�N�i�l�p�j�N���X
class BlockQPathD : public BlockQPathBase {
public:
	BlockQPathD(); // �R���X�g���N�^
	void Collision(const int &Direction, VECTOR &BallPos, VECTOR &BallVel) const; // �Փ˔���֐�
};