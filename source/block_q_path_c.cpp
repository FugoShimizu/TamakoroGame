#include "block_q_path_c.h"

// �R���X�g���N�^
BlockQPathC::BlockQPathC() {
	// ���f���̓Ǎ�
	ModelHandle = MV1LoadModel("models\\block_q_path_c.mv1");
	// �I��
	return;
}

// �Փ˔���֐�
void BlockQPathC::Collision(const int &Direction, VECTOR &BallPos, VECTOR &BallVel) const {
	// �Z����]���̃{�[���ʒu�̉�]�ϊ�
	RotateBallPos(-Direction, BallPos, BallVel);
	// �{�[���̏Փ˔���
	RightWall(BallPos, BallVel);
	FrontWall(BallPos, BallVel);
	LeftBackCorner(BallPos, BallVel);
	// �{�[���ʒu�̍ĉ�]�ϊ�
	RotateBallPos(Direction, BallPos, BallVel);
	// �I��
	return;
}