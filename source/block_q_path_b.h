#pragma once
#include "block_q_path_base.h"

// �a�^�ʘH���u���b�N�i�l�p�j�N���X
class BlockQPathB : public BlockQPathBase {
public:
	BlockQPathB(); // �R���X�g���N�^
	void Collision(const int &direction, VECTOR &BallPos, VECTOR &BallVel) const override; // �Փ˔���֐�
};