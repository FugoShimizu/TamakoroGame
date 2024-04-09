#include <algorithm>
#include <array>
#include <cmath>
#include "stage_hex.h"
#include "Maze_hex.h"
#include "setting.h"

// �R���X�g���N�^
StageHex::StageHex() {
	// �����o�ϐ��̏�����
	Size = Setting::GetStageSize();
	BallLat = Size - 1;
	BallLon = 0;
	Stage = std::vector<std::vector<std::pair<CellT, CellT>>>(Size + 2, std::vector<std::pair<CellT, CellT>>(Size + 2));
	// �X�e�[�W�̐���
	if(Setting::GetStageType() == StageForm::HEX) BuildStage();
	// �I��
	return;
}

// �X�e�[�W�\�z�֐�
void StageHex::BuildStage() {
	// ���H�̐���
	const MazeHex Maze;
	Paths = Maze.GetPath();
	// �X�e�[�W�̊p�̃��f���̊���
	Stage[Size + 1][(Size + 1) / 2 + 1].first.SetCellN(Corner.GetModel(), 2, Size, Size + 1, (Size + 1) / 2 + 1); // ��
	Stage[0][Size / 2].second.SetCellS(Corner.GetModel(), 2, Size, 0, Size / 2); // �N
	Stage[0][Size + 1].first.SetCellN(Corner.GetModel(), 1, Size, 0, Size + 1); // �K
	Stage[Size + 1][0].second.SetCellS(Corner.GetModel(), 1, Size, Size + 1, 0); // ��
	Stage[Size / 2 + 1][0].first.SetCellN(Corner.GetModel(), 0, Size, Size / 2 + 1, 0); // ��
	Stage[(Size + 1) / 2][Size + 1].second.SetCellS(Corner.GetModel(), 0, Size, (Size + 1) / 2, Size + 1); // ��
	// �X�e�[�W�̉��̃��f���̊���
	for(int j = 1; j <= (Size + 1) / 2; ++j) Stage[Size + 1][j].first.SetCellN(Border.GetModel(), 2, Size, Size + 1, j); // �\
	for(int j = Size / 2 + 1; j <= Size; ++j) Stage[0][j].second.SetCellS(Border.GetModel(), 2, Size, 0, j); // ��
	for(int i = 1; i <= (Size + 1) / 2; ++i) Stage[i][Size + 1].first.SetCellN(Border.GetModel(), 1, Size, i, Size + 1); // �C
	for(int i = Size / 2 + 1; i <= Size; ++i) Stage[i][0].second.SetCellS(Border.GetModel(), 1, Size, i, 0); // ��
	for(int i = Size / 2, j = 1; i > 0; --i, ++j) Stage[i][j].first.SetCellN(Border.GetModel(), 0, Size, i, j); // �q
	for(int i = Size, j = (Size + 1) / 2 + 1; j <= Size; --i, ++j) Stage[i][j].second.SetCellS(Border.GetModel(), 0, Size, i, j); // ��
	// �X�e�[�W�̖��H�����̃��f���̊���
	for(int i = 1; i <= Size; ++i) for(int j = 1; j <= Size; ++j) {
		if(i + j > Size / 2 + 1 && i + j <= (Size + 1) * 3 / 2) switch(Paths[i - 1][j - 1].first.first) {
		case 0:
			Stage[i][j].first.SetCellN(PathA.GetModel(), Paths[i - 1][j - 1].first.second, Size, i, j);
			break;
		case 1:
			Stage[i][j].first.SetCellN(PathB.GetModel(), Paths[i - 1][j - 1].first.second, Size, i, j);
			break;
		case 2:
			Stage[i][j].first.SetCellN(PathC.GetModel(), Paths[i - 1][j - 1].first.second, Size, i, j);
			break;
		default:
			Stage[i][j].first.SetCellN(-1, Paths[i - 1][j - 1].first.second, Size, i, j);
			break;
		}
		if(i + j > Size / 2 && i + j < (Size + 1) * 3 / 2) switch(Paths[i - 1][j - 1].second.first) {
		case 0:
			Stage[i][j].second.SetCellS(PathA.GetModel(), Paths[i - 1][j - 1].second.second, Size, i, j);
			break;
		case 1:
			Stage[i][j].second.SetCellS(PathB.GetModel(), Paths[i - 1][j - 1].second.second, Size, i, j);
			break;
		case 2:
			Stage[i][j].second.SetCellS(PathC.GetModel(), Paths[i - 1][j - 1].second.second, Size, i, j);
			break;
		default:
			Stage[i][j].second.SetCellS(-1, Paths[i - 1][j - 1].second.second, Size, i, j);
			break;
		}
	}
	// �X�e�[�W�̃��f���R�s�[���̍폜
	Corner.DeleteModel();
	Border.DeleteModel();
	PathA.DeleteModel();
	PathB.DeleteModel();
	PathC.DeleteModel();
	// �I��
	return;
}

// �{�[���ʒu�Y���u���b�N�Փ˔���֐�
void StageHex::PositionFix(VECTOR &BallPos, VECTOR &BallVel) {
	// �{�[���ʒu�̃X�e�[�W���S��
	BallPos.x = std::clamp(BallPos.x, abs(BallPos.z) / CellT::Root3 - Size * CellT::CentroidX + 1.0F, abs(BallPos.z) / -CellT::Root3 + Size * CellT::CentroidX - 1.0F);
	BallPos.z = std::clamp(BallPos.z, static_cast<float>((Size + 1) / -2 * 4 + 1), static_cast<float>((Size + 1) / 2 * 4 - 1));
	// �{�[���ʒu�̊Y���u���b�N�̔���
	BallLat = static_cast<int>(fmaf(BallPos.x, CellT::Root3, BallPos.z - Size * 4)) / -8;
	BallLon = static_cast<int>(fmaf(BallPos.x, CellT::Root3, Size * 4 - BallPos.z)) / 8;
	const bool Pole = (static_cast<int>(BallPos.z + Size * 4) / 4 - BallLat - BallLon) % 2;
	std::pair<int, int> Cie;
	std::array<std::pair<int, int>, 3> AdjacentCell; // �אڃZ��
	// �Z�����{�[���ʒu�̎Z�o
	VECTOR BallLocLocal;
	// ��k�Z���ɉ������Z�o
	if(Pole) { // �k�Z��
		Cie = Paths[BallLat][BallLon].first;
		if(BallLat > 0) AdjacentCell[(3 - Cie.second) % 3] = Paths[BallLat - 1][BallLon].second; // �Q������
		if(BallLat + BallLon <= (Size - 1) * 2 - Size / 2) AdjacentCell[(4 - Cie.second) % 3] = Paths[BallLat][BallLon].second; // �U������
		if(BallLon > 0) AdjacentCell[(5 - Cie.second) % 3] = Paths[BallLat][BallLon - 1].second; // �P�O������
		BallLocLocal = VGet(fmodf(BallPos.x + (Size + (Size - BallLat + BallLon - 1) % 2) * CellT::CentroidX, CellT::CentroidX * 2.0F) - CellT::CentroidX, 0.0F, fmodf(BallPos.z + Size * 4, 4.0F) - CellT::CentroidZ);
	} else { // ��Z��
		Cie = Paths[BallLat][BallLon].second;
		if(BallLat < Size - 1) AdjacentCell[(3 - Cie.second) % 3] = Paths[BallLat + 1][BallLon].first; // �W������
		if(BallLat + BallLon >= Size / 2) AdjacentCell[(4 - Cie.second) % 3] = Paths[BallLat][BallLon].first; // �P�Q������
		if(BallLon < Size - 1) AdjacentCell[(5 - Cie.second) % 3] = Paths[BallLat][BallLon + 1].first; // �S������
		BallLocLocal = VGet(CellT::CentroidX - fmodf(BallPos.x + (Size + (Size - BallLat + BallLon - 1) % 2) * CellT::CentroidX, CellT::CentroidX * 2.0F), 0.0F, CellT::CentroidZ * 2.0F - fmodf(BallPos.z + Size * 4, 4.0F));
	}
	// �אڕǂ̔���
	std::array<std::pair<bool, bool>, 3> AdjacentWall; // ���S���猩�āCfirst�F�����̕ǁCsecond�F�E���̕� // true�F�����ǁCfalse�F�Z����
	for(int i = 0; i < 3; ++i) AdjacentWall[i] = std::make_pair(!AdjacentCell[(i + 2) % 3].first || AdjacentCell[(i + 2) % 3] == std::make_pair(1, (Cie.second + i) % 3), !AdjacentCell[i].first || AdjacentCell[i] == std::make_pair(1, (Cie.second + i) % 3)); // �P�Q�������C�S�������C�W������
	// �Y���u���b�N�ɉ������Փ˔���
	switch(Cie.first) {
	case 0:
		PathA.Collision(Cie.second, AdjacentWall, BallLocLocal, BallVel);
		break;
	case 1:
		PathB.Collision(Cie.second, AdjacentWall, BallLocLocal, BallVel);
		break;
	case 2:
		PathC.Collision(Cie.second, AdjacentWall, BallLocLocal, BallVel);
		break;
	}
	// �C�����ꂽ�Z�����{�[���ʒu�̔��f
	if(Pole) BallPos = VAdd(VGet((BallLon - BallLat) * CellT::CentroidX, 0.0F, (Size - BallLat - BallLon - 1) * 4 + CellT::CentroidZ), BallLocLocal);
	else BallPos = VAdd(VGet((BallLon - BallLat) * CellT::CentroidX, 0.0F, (Size - BallLat - BallLon - 1) * 4 - CellT::CentroidZ), VScale(BallLocLocal, -1.0F));
	// �I��
	return;
}

// �`��֐�
void StageHex::Draw(const MATRIX &RotationMat) const {
	// �X�e�[�W�̕`��
	for(const std::vector<std::pair<CellT, CellT>> &x : Stage) for(const std::pair<CellT, CellT> &y : x) {
		y.first.Draw(RotationMat);
		y.second.Draw(RotationMat);
	}
	// �I��
	return;
}

// ���ӕ`��֐�
void StageHex::DrawNear(const MATRIX &RotationMat) const {
	// �X�e�[�W�̕`��
	for(int i = 0; i < Size + 2; ++i) for(int j = 0; j < Size + 2; ++j) if(abs(i - BallLat - 1) + abs(j - BallLon - 1) <= 3) {
		Stage[i][j].first.Draw(RotationMat);
		Stage[i][j].second.Draw(RotationMat);
	}
	// �I��
	return;
}

// �����`��֐�
void StageHex::DrawFar(const MATRIX &RotationMat) const {
	// �X�e�[�W�̕`��
	for(int i = 0; i < Size + 2; ++i) for(int j = 0; j < Size + 2; ++j) if(abs(i - BallLat - 1) + abs(j - BallLon - 1) > 3) {
		Stage[i][j].first.Draw(RotationMat);
		Stage[i][j].second.Draw(RotationMat);
	}
	// �I��
	return;
}