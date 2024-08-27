#include <algorithm>
#include <cmath>
#include "stage_sqr.h"
#include "Maze_sqr.h"
#include "setting.h"

// �R���X�g���N�^
StageSqr::StageSqr() {
	// �����o�ϐ��̏�����
	Size = Setting::GetStageSize();
	BallLat = Size - 1;
	BallLon = 0;
	Stage = std::vector<std::vector<CellQ>>(Size + 2, std::vector<CellQ>(Size + 2));
	// �X�e�[�W�̐���
	if(Setting::GetStageType() == StageForm::SQR) BuildStage();
	// �I��
	return;
}

// �X�e�[�W�\�z�֐�
void StageSqr::BuildStage() {
	// ���H�̐���
	const MazeSqr Maze;
	Paths = Maze.GetPath();
	// �X�e�[�W�̊p�̃��f���̊���
	Stage[0][0].SetCell(Corner.GetModel(), 0, Size, 0, 0); // �k��
	Stage[0][Size + 1].SetCell(Corner.GetModel(), 1, Size, 0, Size + 1); // �k��
	Stage[Size + 1][Size + 1].SetCell(Corner.GetModel(), 2, Size, Size + 1, Size + 1); // �쓌
	Stage[Size + 1][0].SetCell(Corner.GetModel(), 3, Size, Size + 1, 0); // �쐼
	// �X�e�[�W�̉��̃��f���̊���
	for(int j = 1; j <= Size; ++j) {
		Stage[0][j].SetCell(Border.GetModel(), 0, Size, 0, j); // �k
		Stage[Size + 1][j].SetCell(Border.GetModel(), 2, Size, Size + 1, j); // ��
	}
	for(int i = 1; i <= Size; ++i) {
		Stage[i][0].SetCell(Border.GetModel(), 3, Size, i, 0); // ��
		Stage[i][Size + 1].SetCell(Border.GetModel(), 1, Size, i, Size + 1); // ��
	}
	// �X�e�[�W�̖��H�����̃��f���̊���
	for(int i = 1; i <= Size; ++i) for(int j = 1; j <= Size; ++j) switch(Paths[i - 1][j - 1].first) {
	case 0:
		Stage[i][j].SetCell(PathA.GetModel(), Paths[i - 1][j - 1].second, Size, i, j);
		break;
	case 1:
		Stage[i][j].SetCell(PathB.GetModel(), Paths[i - 1][j - 1].second, Size, i, j);
		break;
	case 2:
		Stage[i][j].SetCell(PathC.GetModel(), Paths[i - 1][j - 1].second, Size, i, j);
		break;
	case 3:
		Stage[i][j].SetCell(PathD.GetModel(), Paths[i - 1][j - 1].second, Size, i, j);
		break;
	case 4:
		Stage[i][j].SetCell(PathE.GetModel(), Paths[i - 1][j - 1].second, Size, i, j);
		break;
	default:
		Stage[i][j].SetCell(-1, Paths[i - 1][j - 1].second, Size, i, j);
		break;
	}
	// �X�e�[�W�̃��f���R�s�[���̍폜
	Corner.DeleteModel();
	Border.DeleteModel();
	PathA.DeleteModel();
	PathB.DeleteModel();
	PathC.DeleteModel();
	PathD.DeleteModel();
	PathE.DeleteModel();
	// �I��
	return;
}

// �{�[���ʒu�Y���u���b�N�Փ˔���֐�
void StageSqr::PositionFix(VECTOR &BallPos, VECTOR &BallVel) {
	// �{�[���ʒu�̃X�e�[�W���S��
	BallPos.x = std::clamp(BallPos.x, static_cast<float>(-2 * Size + 1), static_cast<float>(2 * Size - 1));
	BallPos.z = std::clamp(BallPos.z, static_cast<float>(-2 * Size + 1), static_cast<float>(2 * Size - 1));
	// �{�[���ʒu�̊Y���u���b�N�̔���
	BallLat = static_cast<int>(0.5F * Size - 0.25F * BallPos.z);
	BallLon = static_cast<int>(0.5F * Size + 0.25F * BallPos.x);
	std::pair<int, int> Cie = Paths[BallLat][BallLon];
	// �Z�����{�[���ʒu�̎Z�o
	VECTOR BallLocLocal = VGet(fmodf((BallPos.x + 2 * Size), 4.0F) - 2.0F, 0.0F, fmodf((BallPos.z + 2 * Size), 4.0F) - 2.0F);
	// �Y���u���b�N�ɉ������Փ˔���
	switch(Cie.first) {
	case 0:
		PathA.Collision(Cie.second, BallLocLocal, BallVel);
		break;
	case 1:
		PathB.Collision(Cie.second, BallLocLocal, BallVel);
		break;
	case 2:
		PathC.Collision(Cie.second, BallLocLocal, BallVel);
		break;
	case 3:
		PathD.Collision(Cie.second, BallLocLocal, BallVel);
		break;
	case 4:
		PathE.Collision(Cie.second, BallLocLocal, BallVel);
		break;
	}
	// �C�����ꂽ�Z�����{�[���ʒu�̔��f
	BallPos = VAdd(VGet(static_cast<float>(2 * (1 - Size) + 4 * BallLon), 0.0F, static_cast<float>(2 * (Size - 1) - 4 * BallLat)), BallLocLocal);
	// �I��
	return;
}

// �`��֐�
void StageSqr::Draw(const MATRIX &RotationMat) const {
	// �X�e�[�W�̕`��
	for(const std::vector<CellQ> &x : Stage) for(const CellQ &y : x) y.Draw(RotationMat);
	// �I��
	return;
}

// ���ӕ`��֐�
void StageSqr::DrawNear(const MATRIX &RotationMat) const {
	// �X�e�[�W�̕`��
	for(int i = 0; i < Size + 2; ++i) for(int j = 0; j < Size + 2; ++j) if(abs(i - BallLat - 1) + abs(j - BallLon - 1) <= 3) Stage[i][j].Draw(RotationMat);
	// �I��
	return;
}

// �����`��֐�
void StageSqr::DrawFar(const MATRIX &RotationMat) const {
	// �X�e�[�W�̕`��
	for(int i = 0; i < Size + 2; ++i) for(int j = 0; j < Size + 2; ++j) if(abs(i - BallLat - 1) + abs(j - BallLon - 1) > 3) Stage[i][j].Draw(RotationMat);
	// �I��
	return;
}