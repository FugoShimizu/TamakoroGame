#include "cell_base.h"

// �R���X�g���N�^
CellBase::CellBase() {
	// �����o�ϐ��̏�����
	ModelHandle = -1;
	Direction = 0;
	Location = VGet(0.0F, 0.0F, 0.0F);
	// �I��
	return;
}

// �e�N�X�`���ݒ�֐�
void CellBase::SetTexture(const int &GraphHandle) const {
	// �e�N�X�`���̕ύX
	MV1SetTextureGraphHandle(ModelHandle, 0, GraphHandle, FALSE);
	// �I��
	return;
}

// �`��֐�
void CellBase::Draw(const MATRIX &RotationMat) const {
	// �Z����`�悷��
	MV1SetMatrix(ModelHandle, MMult(MMult(MGetRotY(Direction), RotationMat), MGetTranslate(VTransformSR(Location, RotationMat))));
	MV1DrawModel(ModelHandle);
	// �I��
	return;
}