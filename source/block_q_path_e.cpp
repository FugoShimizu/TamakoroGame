#include "block_q_path_e.h"

// �R���X�g���N�^
BlockQPathE::BlockQPathE() {
	// ���f���̓Ǎ�
	ModelHandle = MV1LoadModel("models\\block_q_path_e.mv1");
	// �I��
	return;
}

// �Փ˔���֐�
void BlockQPathE::Collision(const int &Direction, VECTOR &BallPos, VECTOR &BallVel) const {
	// �{�[���̏Փ˔���
	LeftBackCorner(BallPos, BallVel);
	LeftFrontCorner(BallPos, BallVel);
	RightBackCorner(BallPos, BallVel);
	RightFrontCorner(BallPos, BallVel);
	// �I��
	return;
}