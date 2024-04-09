#pragma once
#include <utility>
#include <vector>
#include <DxLib.h>
#include "block_t_Corner.h"
#include "block_t_border.h"
#include "block_t_path_a.h"
#include "block_t_path_b.h"
#include "block_t_path_c.h"
#include "cell_t.h"

// �Z�p�`�X�e�[�W�N���X
class StageHex {
public:
	StageHex(); // �R���X�g���N�^
	void PositionFix(VECTOR &BallPos, VECTOR &BallVel); // �{�[���ʒu�Y���u���b�N�Փ˔���֐�
	void Draw(const MATRIX &RotationMat) const; // �`��֐�
	void DrawNear(const MATRIX &RotationMat) const; // ���ӕ`��֐�
	void DrawFar(const MATRIX &RotationMat) const; // �����`��֐�
private:
	int Size; // �X�e�[�W�̑傫��
	int BallLat; // �{�[���ʒu�̊Y���u���b�N�ܓx
	int BallLon; // �{�[���ʒu�̊Y���u���b�N�o�x
	std::vector<std::vector<std::pair<CellT, CellT>>> Stage; // �X�e�[�W�\���Z��
	std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>> Paths; // ���H�\���u���b�N���
	BlockTCorner Corner; // �p���u���b�N
	BlockTBorder Border; // �����u���b�N
	BlockTPathA PathA; // �`�^�ʘH�ʘH���u���b�N
	BlockTPathB PathB; // �a�^�ʘH�ʘH���u���b�N
	BlockTPathC PathC; // �b�^�ʘH�ʘH���u���b�N
	void BuildStage(); // �X�e�[�W�\�z�֐�
};