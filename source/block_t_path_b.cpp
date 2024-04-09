#include "block_t_path_b.h"

// �R���X�g���N�^
BlockTPathB::BlockTPathB() {
	// ���f���̓Ǎ�
	ModelHandle = MV1LoadModel("models\\block_t_path_b.mv1");
	// �I��
	return;
}

// �Փ˔���֐�
void BlockTPathB::Collision(const int &Direction, const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const {
	// �Z����]���̃{�[���ʒu�̉�]�ϊ�
	RotateBallPos(-Direction, BallPos, BallVel);
	// �{�[���̏Փ˔���
	TwlOcWall(AdjacentWall, BallPos, BallVel);
	SixOcWall(AdjacentWall, BallPos, BallVel);
	// �{�[���ʒu�̍ĉ�]�ϊ�
	RotateBallPos(Direction, BallPos, BallVel);
	// �I��
	return;
}