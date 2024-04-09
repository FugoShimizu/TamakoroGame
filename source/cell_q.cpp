#include "cell_q.h"

// �Z���ݒ�֐�
void CellQ::SetCell(const int &SourceModelHandle, const int &CellDir, const int &StageSize, const int &Latitude, const int &Longitude) {
	// ���f���̃R�s�[
	ModelHandle = MV1DuplicateModel(SourceModelHandle);
	// �Z���̌����̐ݒ�
	Direction = CellDir * DX_PI_F * 0.5F;
	// �Z���̈ʒu�̐ݒ�
	Location = VGet(static_cast<float>((StageSize + 1) * -2 + Longitude * 4), 0.0F, static_cast<float>((StageSize + 1) * 2 - Latitude * 4));
	//�I��
	return;
}