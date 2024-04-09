#include "cell_t.h"

// �Z���ݒ�֐��i�k�Z���j
void CellT::SetCellN(const int &SourceModelHandle, const int &CellDir, const int &StageSize, const int &Latitude, const int &Longitude) {
	// ���f���̃R�s�[
	ModelHandle = MV1DuplicateModel(SourceModelHandle);
	// �Z���̌����̐ݒ�
	Direction = CellDir * DX_TWO_PI_F / 3.0F;
	// �Z���̈ʒu�̐ݒ�
	Location = VGet((Longitude - Latitude) * CentroidX, 0.0F, (StageSize - Latitude - Longitude + 1) * 4 + CentroidZ);
	//�I��
	return;
}

// �Z���ݒ�֐��i��Z���j
void CellT::SetCellS(const int &SourceModelHandle, const int &CellDir, const int &StageSize, const int &Latitude, const int &Longitude) {
	// ���f���̃R�s�[
	ModelHandle = MV1DuplicateModel(SourceModelHandle);
	// �Z���̌����̐ݒ�
	Direction = CellDir * DX_TWO_PI_F / 3.0F + DX_PI_F;
	// �Z���̈ʒu�̐ݒ�
	Location = VGet((Longitude - Latitude) * CentroidX, 0.0F, (StageSize - Latitude - Longitude + 1) * 4 - CentroidZ);
	//�I��
	return;
}