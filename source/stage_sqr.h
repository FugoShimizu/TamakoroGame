#pragma once
#include <utility>
#include <vector>
#include <DxLib.h>
#include "block_q_Corner.h"
#include "block_q_border.h"
#include "block_q_path_a.h"
#include "block_q_path_b.h"
#include "block_q_path_c.h"
#include "block_q_path_d.h"
#include "block_q_path_e.h"
#include "cell_q.h"

// �l�p�`�X�e�[�W�N���X
class StageSqr {
public:
	StageSqr(); // �R���X�g���N�^
	void PositionFix(VECTOR &BallPos, VECTOR &BallVel); // �{�[���ʒu�Y���u���b�N�Փ˔���֐�
	void Draw(const MATRIX &RotationMat) const; // �`��֐�
	void DrawNear(const MATRIX &RotationMat) const; // ���ӕ`��֐�
	void DrawFar(const MATRIX &RotationMat) const; // �����`��֐�
private:
	int Size; // �X�e�[�W�̑傫��
	int BallLat; // �{�[���ʒu�̊Y���u���b�N�ܓx
	int BallLon; // �{�[���ʒu�̊Y���u���b�N�o�x
	std::vector<std::vector<CellQ>> Stage; // �X�e�[�W�\���Z��
	std::vector<std::vector<std::pair<int, int>>> Paths; // ���H�\���u���b�N���ifirst�F��ށCsecond�F�����j
	BlockQCorner Corner; // �p���u���b�N
	BlockQBorder Border; // �����u���b�N
	BlockQPathA PathA; // �`�^�ʘH�ʘH���u���b�N
	BlockQPathB PathB; // �a�^�ʘH�ʘH���u���b�N
	BlockQPathC PathC; // �b�^�ʘH�ʘH���u���b�N
	BlockQPathD PathD; // �c�^�ʘH�ʘH���u���b�N
	BlockQPathE PathE; // �d�^�ʘH�ʘH���u���b�N
	void BuildStage(); // �X�e�[�W�\�z�֐�
};