#include "cell_q.h"

// �Z���ݒ�֐�
void CellQ::SetCell(const int &SourceModelHandle, const int &CellDir, const int &StageSize, const int &Latitude, const int &Longitude) {
	// ���f���̃R�s�[
	ModelHandle = MV1DuplicateModel(SourceModelHandle);
	// �Z���̌����̐ݒ�
	Direction = 0.5F * DX_PI_F * CellDir;
	// �Z���̈ʒu�̐ݒ�
	Location = VGet(static_cast<float>(-2 * (StageSize + 1) + 4 * Longitude), 0.0F, static_cast<float>(2 * (StageSize + 1) - 4 * Latitude));
	//�I��
	return;
}