#pragma once
#include "cell_base.h"

// �Z���i�l�p�j�N���X
class CellQ : public CellBase {
public:
	void SetCell(const int &SourceModelHandle, const int &CellDir, const int &StageSize, const int &Latitude, const int &Longitude); // �Z���ݒ�֐�
};