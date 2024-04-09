#include "block_t_path_c.h"

// �R���X�g���N�^
BlockTPathC::BlockTPathC() {
	// ���f���̓Ǎ�
	ModelHandle = MV1LoadModel("models\\block_t_path_c.mv1");
	// �I��
	return;
}

// �Փ˔���֐�
void BlockTPathC::Collision(const int &Direction, const std::array<std::pair<bool, bool>, 3> &AdjacentWall, VECTOR &BallPos, VECTOR &BallVel) const {
	// �Z����]���̃{�[���ʒu�̉�]�ϊ�
	RotateBallPos(-Direction, BallPos, BallVel);
	// �{�[���̏Փ˔���
	TwlOcWall(AdjacentWall, BallPos, BallVel);
	ForOcWall(AdjacentWall, BallPos, BallVel);
	EitOcWall(AdjacentWall, BallPos, BallVel);
	// �{�[���ʒu�̍ĉ�]�ϊ�
	RotateBallPos(Direction, BallPos, BallVel);
	// �I��
	return;
}