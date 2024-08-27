#include "cell_t.h"

// �Z���ݒ�֐��i�k�Z���j
void CellT::SetCellN(const int &SourceModelHandle, const int &CellDir, const int &StageSize, const int &Latitude, const int &Longitude) {
	// ���f���̃R�s�[
	ModelHandle = MV1DuplicateModel(SourceModelHandle);
	// �Z���̌����̐ݒ�
	Direction = DX_TWO_PI_F / 3.0F * CellDir;
	// �Z���̈ʒu�̐ݒ�
	Location = VGet(CentroidX * (Longitude - Latitude), 0.0F, 4 * (StageSize - Latitude - Longitude + 1) + CentroidZ);
	//�I��
	return;
}

// �Z���ݒ�֐��i��Z���j
void CellT::SetCellS(const int &SourceModelHandle, const int &CellDir, const int &StageSize, const int &Latitude, const int &Longitude) {
	// ���f���̃R�s�[
	ModelHandle = MV1DuplicateModel(SourceModelHandle);
	// �Z���̌����̐ݒ�
	Direction = DX_TWO_PI_F / 3.0F * CellDir + DX_PI_F;
	// �Z���̈ʒu�̐ݒ�
	Location = VGet(CentroidX * (Longitude - Latitude), 0.0F, 4 * (StageSize - Latitude - Longitude + 1) - CentroidZ);
	//�I��
	return;
}