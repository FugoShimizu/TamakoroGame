#include "block_q_path_d.h"

// �R���X�g���N�^
BlockQPathD::BlockQPathD() {
	// ���f���̓Ǎ�
	ModelHandle = MV1LoadModel("models\\block_q_path_d.mv1");
	// �I��
	return;
}

// �Փ˔���֐�
void BlockQPathD::Collision(const int &Direction, VECTOR &BallPos, VECTOR &BallVel) const {
	// �Z����]���̃{�[���ʒu�̉�]�ϊ�
	RotateBallPos(-Direction, BallPos, BallVel);
	// �{�[���̏Փ˔���
	RightWall(BallPos, BallVel);
	LeftBackCorner(BallPos, BallVel);
	LeftFrontCorner(BallPos, BallVel);
	// �{�[���ʒu�̍ĉ�]�ϊ�
	RotateBallPos(Direction, BallPos, BallVel);
	// �I��
	return;
}