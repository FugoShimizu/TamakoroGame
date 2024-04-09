#pragma once
#include <numbers>
#include "cell_base.h"

// �Z���i�O�p�j�N���X
class CellT : public CellBase {
public:
	static constexpr float Root3 = std::numbers::sqrt3_v<float>; // ��3
	static constexpr float CentroidZ = 4.0f / 3.0f; // ���S�̍������_���_��Z���W
	static constexpr float CentroidX = CentroidZ * Root3; // ���S�̍������_���_��X���W
	void SetCellN(const int &SourceModelHandle, const int &CellDir, const int &StageSize, const int &Latitude, const int &Longitude); // �Z���ݒ�֐��i�k�Z���j
	void SetCellS(const int &SourceModelHandle, const int &CellDir, const int &StageSize, const int &Latitude, const int &Longitude); // �Z���ݒ�֐��i��Z���j
};