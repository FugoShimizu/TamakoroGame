#pragma once
#include "block_q_path_base.h"

// �`�^�ʘH���u���b�N�i�l�p�j�N���X
class BlockQPathA : public BlockQPathBase {
public:
	BlockQPathA(); // �R���X�g���N�^
	void Collision(const int &Direction, VECTOR &BallPos, VECTOR &BallVel) const; // �Փ˔���֐�
};