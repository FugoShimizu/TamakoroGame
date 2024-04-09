#include "block_q_path_b.h"

// �R���X�g���N�^
BlockQPathB::BlockQPathB() {
	// ���f���̓Ǎ�
	ModelHandle = MV1LoadModel("models\\block_q_path_b.mv1");
	// �I��
	return;
}

// �Փ˔���֐�
void BlockQPathB::Collision(const int &Direction, VECTOR &BallPos, VECTOR &BallVel) const {
	// �Z����]���̃{�[���ʒu�̉�]�ϊ�
	RotateBallPos(-Direction, BallPos, BallVel);
	// �{�[���̏Փ˔���
	LeftWall(BallPos, BallVel);
	RightWall(BallPos, BallVel);
	// �{�[���ʒu�̍ĉ�]�ϊ�
	RotateBallPos(Direction, BallPos, BallVel);
	// �I��
	return;
}