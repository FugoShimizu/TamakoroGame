#include "block_t_path_a.h"

// �R���X�g���N�^
BlockTPathA::BlockTPathA() {
	// ���f���̓Ǎ�
	ModelHandle = MV1LoadModel("models\\block_t_path_a.mv1");
	// �I��
	return;
}

// �Փ˔���֐�
void BlockTPathA::Collision(const int &Direction, const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const {
	// �Z����]���̃{�[���ʒu�̉�]�ϊ�
	RotateBallPos(-Direction, BallPos, BallVel);
	// �{�[���̏Փ˔���
	TwoOcWall(AdjacentWall, BallPos, BallVel);
	TenOcWall(AdjacentWall, BallPos, BallVel);
	// �{�[���ʒu�̍ĉ�]�ϊ�
	RotateBallPos(Direction, BallPos, BallVel);
	// �I��
	return;
}