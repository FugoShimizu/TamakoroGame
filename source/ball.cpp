#include "ball.h"

// �R���X�g���N�^
Ball::Ball() {
	// �����o�ϐ��̏�����
	SetPos(VGet(0.0F, 0.0F, 0.0F));
	// ���f���̓Ǎ�
	ModelHandle = MV1LoadModel("models\\ball.mv1");
	// �I��
	return;
}

// �e�N�X�`���ݒ�֐�
void Ball::SetTexture(const int &GraphHandle) const {
	// �e�N�X�`���̕ύX
	MV1SetTextureGraphHandle(ModelHandle, 0, GraphHandle, FALSE);
	// �I��
	return;
}

// �ʒu�ݒ�֐�
void Ball::SetPos(const VECTOR &Position) {
	// �{�[���ʒu�̐ݒ�
	Pos = Position;
	Vel = VGet(0.0F, 0.0F, 0.0F);
	// �I��
	return;
}

// �ړ��֐�
void Ball::Position(const float &StgRotX, const float &StgRotZ) {
	// �{�[���ʒu�̌v�Z
	Vel = VAdd(Vel, VScale(VGet(-StgRotZ, 0.0F, StgRotX), 0.02F)); // ������
	Vel = VScale(Vel, 0.984375F); // ���C�͂ɂ�錸��
	Pos = VAdd(Pos, Vel); // ���x�ɉ����Ĉʒu���ړ�
	// �I��
	return;
}

// �`��֐�
void Ball::Draw(const MATRIX &RotationMat) const {
	// �{�[���̕`��
	MV1SetPosition(ModelHandle, VTransformSR(Pos, RotationMat));
	MV1DrawModel(ModelHandle);
	// �I��
	return;
}