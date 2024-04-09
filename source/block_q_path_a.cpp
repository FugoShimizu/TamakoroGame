#include "block_q_path_a.h"

// �R���X�g���N�^
BlockQPathA::BlockQPathA() {
	// ���f���̓Ǎ�
	ModelHandle = MV1LoadModel("models\\block_q_path_a.mv1");
	// �I��
	return;
}

// �Փ˔���֐�
void BlockQPathA::Collision(const int &Direction, VECTOR &BallPos, VECTOR &BallVel) const {
	// �Z����]���̃{�[���ʒu�̉�]�ϊ�
	RotateBallPos(-Direction, BallPos, BallVel);
	// �{�[���̏Փ˔���
	LeftWall(BallPos, BallVel);
	RightWall(BallPos, BallVel);
	FrontWall(BallPos, BallVel);
	// �{�[���ʒu�̍ĉ�]�ϊ�
	RotateBallPos(Direction, BallPos, BallVel);
	// �I��
	return;
}