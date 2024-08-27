#include <algorithm>
#include <cmath>
#include "model.h"
#include "input.h"
#include "Setting.h"

// �R���X�g���N�^
Model::Model() {
	// �����o�ϐ��̏�����
	Type = Setting::GetStageType();
	Size = Setting::GetStageSize();
	Goal = false;
	RotationAng = VGet(0.0F, 0.0F, 0.0F);
	CamRotAng = VGet(0.0F, 0.0F, 0.0F);
	RotationMat = MGetIdent(); // �P�ʍs��
	switch(Type) {
	case StageForm::SQR: // �l�p�`�X�e�[�W�̎�
		StartLoc = VGet(static_cast<float>(2 * (1 - Size)), 0.0F, static_cast<float>(2 * (1 - Size))); // �X�^�[�g�ʒu
		GoalLoc = VGet(static_cast<float>(2 * (Size - 1)), 0.0F, static_cast<float>(2 * (Size - 1))); // �S�[���ʒu
		break;
	case StageForm::HEX: // �Z�p�`�X�e�[�W�̎�
		StartLoc = VGet(CellT::CentroidX * (1 - Size), 0.0F, 0.0F); // �X�^�[�g�ʒu
		GoalLoc = VGet(CellT::CentroidX * (Size - 1), 0.0F, 0.0F); // �S�[���ʒu
		break;
	}
	StartDist = 0;
	GoalDist = VSize(VSub(GoalLoc, StartLoc));
	Bal.SetPos(StartLoc);
	ShowDebug = false;
	ShowMiniMap = true;
	MiniMapScale = 4;
	BallPosHist.push(StartLoc);
	// �摜�̓Ǎ�
	SMGraphHandle = LoadGraph("graphs\\start_marker.png"); // �X�^�[�g�ʒu�}�[�J�[
	GMGraphHandle = LoadGraph("graphs\\goal_marker.png"); // �S�[���ʒu�}�[�J�[
	// �I��
	return;
}

// �{�[�����[���h���W�擾�֐�
VECTOR Model::GetBallLocation() const {
	// �I��
	return VTransformSR(Bal.Pos, RotationMat); // �{�[���̃��[���h���W��Ԃ�
}

// �X�e�[�W�X�Α���֐�
float Model::Rotate(const float &CamAngH) {
	// �X�e�[�W�X�΂̌v�Z
	if(Input::GetClicking()) RotationAng = VAdd(RotationAng, VScale(VGet(static_cast<float>(-Input::GetCursorMoveY()), 0.0F, static_cast<float>(-Input::GetCursorMoveX())), SlopeRateDrag)); // ���N���b�N���̓}�E�X�h���b�O�ŌX��
	else if(Input::GetWSADPressing()) RotationAng = VAdd(RotationAng, VScale(VGet(static_cast<float>(Input::GetWSMove()), 0.0F, static_cast<float>(Input::GetADMove())), SlopeRateWSAD)); // WSAD�L�[��������WSAD�L�[�ŌX��
	else RotationAng = VScale(RotationAng, SlopeRateRdct); // �����쎞�͏��X�Ɏ���
	// �X�΂��ő�X�Ίp�ɐ���
	const float Slope = VSize(RotationAng);
	if(Slope > MaxSlope) RotationAng = VScale(RotationAng, MaxSlope / Slope);
	// �J�����̌����ɉ������X�������̒���
	CamRotAng = VTransformSR(RotationAng, MGetRotY(CamAngH));
	// �`��p��]�s��̐���
	RotationMat = MMult(MGetRotX(CamRotAng.x), MGetRotZ(CamRotAng.z)); // ��]�s��
	// �J���������̃X�e�[�W�X�Ίp�̎Z�o
	const VECTOR Direct = VGet(sinf(CamAngH), 0.0F, cosf(CamAngH)); // �����x�N�g��
	const VECTOR Normal = VTransformSR(VGet(0.0F, 1.0F, 0.0F), RotationMat); // �@���x�N�g��
	// �I��
	return 0.5F * DX_PI_F - acosf(VDot(Direct, Normal) / VSize(Direct) / VSize(Normal)); // �J���������̃X�e�[�W�X�Ίp��Ԃ�
}

// �V�~�����[�g�֐�
bool Model::Simulate() {
	// �{�[���ʒu�̃��Z�b�g
	if(Input::GetKeyPress(KEY_INPUT_U)) { // U�L�[�ŃX�^�[�g�ɖ߂�
		// �X�^�[�g�ɖ߂�
		Bal.SetPos(StartLoc);
		// �{�[���̈ʒu�����̏�����
		if(!Goal) { // ���S�[����
			std::queue<VECTOR> NewQueue;
			BallPosHist.swap(NewQueue);
			BallPosHist.push(StartLoc);
		}
	}
	// �f�o�b�O�p
//	if(Input::GetKeyPress(KEY_INPUT_G)) Bal.SetPos(GoalLoc); // G�L�[�ŃS�[��
	// �X������{�[���ʒu���Z�o
	Bal.Position(CamRotAng.x, CamRotAng.z);
	// �Փ˔�����{�[���ʒu�ɔ��f
	switch(Type) {
	case StageForm::SQR: // �l�p�`�X�e�[�W�̎�
		StageSqr.PositionFix(Bal.Pos, Bal.Vel);
		break;
	case StageForm::HEX: // �Z�p�`�X�e�[�W�̎�
		StageHex.PositionFix(Bal.Pos, Bal.Vel);
		break;
	}
	// �X�^�[�g�ƃS�[������̋������Z�o
	StartDist = VSize(VSub(Bal.Pos, StartLoc));
	GoalDist = VSize(VSub(Bal.Pos, GoalLoc));
	// �S�[���O
	if(!Goal) { // ���S�[���̎�
		// �{�[���ʒu�����̒ǉ�
		if(BallPosHist.size() < INT_MAX && VSize(VSub(Bal.Pos, BallPosHist.back())) >= 1.0F) BallPosHist.push(Bal.Pos);
		// �S�[������
		Goal = GoalDist < 1.0F;
	}
	// �I��
	return Goal; // �S�[�������Ԃ�
}

// �\���ؑ֊֐�
bool Model::SwitchDisplay() {
	// �f�o�b�N���̕\���L���̐ؑ�
	if(Input::GetKeyPress(KEY_INPUT_F3)) ShowDebug ^= true; // F3�L�[�Őؑ�
	// �~�j�}�b�v�̕\���L���̐ؑ�
	if(Input::GetKeyPress(KEY_INPUT_M)) ShowMiniMap ^= true; // M�L�[�Őؑ�
	// �~�j�}�b�v�̊g�k
	const bool CursorOnMiniMap = ShowMiniMap && Input::CursorInBox(1020, 460, 1260, 700); // �~�j�}�b�v��̃J�[�\���L��
	if(CursorOnMiniMap) { // �J�[�\�����~�j�}�b�v��ɗL�鎞
		MiniMapScale -= GetMouseWheelRotVol(); // �}�E�X�z�C�[���Ń~�j�}�b�v���g�k
		MiniMapScale = std::clamp(MiniMapScale, 2, 8); // �g�k��͈͓��ɐ���
	}
	// �~�j�}�b�v�k�ڂ̃��Z�b�g
	if(Input::GetKeyPress(KEY_INPUT_R)) MiniMapScale = 4; // R�L�[�Ń��Z�b�g
	// �I��
	return CursorOnMiniMap; // �~�j�}�b�v��̃J�[�\���L����Ԃ�
}

// ���f���`��֐�
void Model::DrawModel() const {
	// �X�e�[�W�̕`��
	switch(Type) {
	case StageForm::SQR: // �l�p�`�X�e�[�W�̎�
		StageSqr.Draw(RotationMat);
		break;
	case StageForm::HEX: // �Z�p�`�X�e�[�W�̎�
		StageHex.Draw(RotationMat);
		break;
	}
	// �{�[���̕`��
	Bal.Draw(RotationMat);
	// �I��
	return;
}

// ���Ӄ��f���`��֐�
void Model::DrawNearModel() const {
	// �X�e�[�W�̕`��
	switch(Type) {
	case StageForm::SQR: // �l�p�`�X�e�[�W�̎�
		StageSqr.DrawNear(RotationMat);
		break;
	case StageForm::HEX: // �Z�p�`�X�e�[�W�̎�
		StageHex.DrawNear(RotationMat);
		break;
	}
	// �{�[���̕`��
	Bal.Draw(RotationMat);
	// �I��
	return;
}

// �������f���`��֐�
void Model::DrawFarModel() const {
	// �X�e�[�W�̕`��
	switch(Type) {
	case StageForm::SQR: // �l�p�`�X�e�[�W�̎�
		StageSqr.DrawFar(RotationMat);
		break;
	case StageForm::HEX: // �Z�p�`�X�e�[�W�̎�
		StageHex.DrawFar(RotationMat);
		break;
	}
	// �I��
	return;
}

// �摜�`��֐�
void Model::DrawInfo(const float &CamAngH) const {
	// �X�^�[�g�ʒu�}�[�J�[�ƃS�[���ʒu�}�[�J�[�̕`��
	SetMarker();
	// �f�o�b�O���̕`��
	if(ShowDebug) DrawFormatString(0, 0, Goal ? GetColor(0, 0, 0) : GetColor(255, 255, 255), "Type: %d, Size: %d, Seed: %d\nStageTilt: (X= %f, Z= %f)\nBallPosition: (X= %f, Z= %f)\nBallVelocity: (X= %f, Z= %f)", static_cast<int>(Setting::GetStageType()), Setting::GetStageSize(), Setting::GetStageSeed(), RotationAng.x, RotationAng.z, Bal.Pos.x, Bal.Pos.z, Bal.Vel.x, Bal.Vel.z);
	// ������@�����̕`��
	else if(!Goal) DrawString(0, 0, "�X����F�}�E�X���h���b�O�^WSAD�L�[�@���_�ړ��F���L�[�@�g��E�k���F�}�E�X�z�C�[���@���_���Z�b�g�FR�L�[�@���_�ύX�FF5�L�[\n�{�[���ʒu���Z�b�g�FU�L�[�@�~�j�}�b�v�\���ؑցFM�L�[�@�f�o�b�O�\���ؑցFF3�L�[�@�^�C�g���ɖ߂�FT�L�[", GetColor(255, 255, 255));
	// �~�j�}�b�v�̕`��
	if(ShowMiniMap) DrawMiniMap(CamAngH);
	// �I��
	return;
}

// �}�[�J�[�ݒ�֐�
void Model::SetMarker() const {
	// �X�^�[�g�ʒu�ƃS�[���ʒu��\��
	const VECTOR s_ScrCoord = ConvWorldPosToScreenPos(VTransformSR(StartLoc, RotationMat)); // �X�^�[�g�ʒu�̃X�N���[�����W
	const VECTOR g_ScrCoord = ConvWorldPosToScreenPos(VTransformSR(GoalLoc, RotationMat)); // �S�[���ʒu�̃X�N���[�����W
	if(s_ScrCoord.z > g_ScrCoord.z) { // �S�[��������O�ɂ��鎞
		DrawMarker(s_ScrCoord, SMGraphHandle, GetColor(255, 0, 0), static_cast<int>(StartDist));
		DrawMarker(g_ScrCoord, GMGraphHandle, GetColor(0, 0, 255), static_cast<int>(GoalDist));
	} else { // �X�^�[�g������O�ɂ��鎞
		DrawMarker(g_ScrCoord, GMGraphHandle, GetColor(0, 0, 255), static_cast<int>(GoalDist));
		DrawMarker(s_ScrCoord, SMGraphHandle, GetColor(255, 0, 0), static_cast<int>(StartDist));
	}
	// �I��
	return;
}

// �}�[�J�[�`��֐�
void Model::DrawMarker(const VECTOR &ScrCoord, const int &MarkerGraphHandle, const unsigned int &FontColor, const int &Distance) const {
	// �}�[�J�[�Ƌ����̕`��
	if(ScrCoord.z < 1.0F && ScrCoord.z > 0.0F) {
		DrawGraph(static_cast<int>(ScrCoord.x) - 40, static_cast<int>(ScrCoord.y) - 90, MarkerGraphHandle, TRUE);
		if(!Goal) DrawFormatString(static_cast<int>(ScrCoord.x) - 30, static_cast<int>(ScrCoord.y) - 106, FontColor, "%3d cm", Distance);
	}
	// �I��
	return;
}

// �~�j�}�b�v�`��֐�
void Model::DrawMiniMap(const float &CamAngH) const {
	// �~�j�}�b�v�̕\��
	SetDrawArea(1020, 460, 1260, 700); // �~�j�}�b�v�̕`��̈�
	SetupCamera_Ortho(static_cast<float>(8 * MiniMapScale)); // ���ˉe�J�������Z�b�g�A�b�v
	SetCameraScreenCenter(1140, 580); // �~�j�}�b�v�̒��S�ʒu
	SetCameraPositionAndTargetAndUpVec(VTransformSR(VAdd(Bal.Pos, VGet(0.0F, 2.0F, 0.0F)), RotationMat), VTransformSR(Bal.Pos, RotationMat), VGet(sinf(CamAngH), 0.0F, cosf(CamAngH))); // �J�����̈ʒu���{�[���̏�ɐݒ�
	DrawBox(1020, 460, 1260, 700, GetColor(0, 0, 0), TRUE); // �~�j�}�b�v�̔w�i
	DrawModel(); // �~�j�}�b�v��`��
	SetMarker(); // �X�^�[�g�ʒu�}�[�J�[�ƃS�[���ʒu�}�[�J�[��`��
	SetDrawArea(0, 0, 1280, 720); // �`��̈�����ɖ߂�
	// �I��
	return;
}

// �O�Չ�ʕ`��֐�
void Model::DrawRoute(int EndNum) const {
	// �}�b�v�̕\��
	SetupCamera_Ortho(6.0F * Size); // ���ˉe�J�������Z�b�g�A�b�v
	SetCameraScreenCenter(640, 360);
	SetCameraPositionAndTargetAndUpVec(VTransformSR(VGet(0.0F, 2.0F, 0.0F), RotationMat), VTransformSR(VGet(0.0F, 0.0F, 0.0F), RotationMat), VGet(0.0F, 0.0F, 1.0F)); // �J�����̈ʒu�𒆉��ɐݒ�
	DrawModel(); // �}�b�v��`��
	SetMarker(); // �X�^�[�g�ʒu�}�[�J�[�ƃS�[���ʒu�}�[�J�[��`��
	// �ړ������̕\��
	DrawFormatString(588, 620, GetColor(0, 0, 0), "�����F%3d cm", BallPosHist.size());
	DrawString(564, 640, "���N���b�N�ŕ���", GetColor(0, 0, 0));
	// �O�Ղ̕\��
	std::queue<VECTOR> BallPosHist_tmp = BallPosHist; // �����𕡐�
	BallPosHist_tmp.push(GoalLoc); // �Ō���S�[���ʒu�ɂ���
	VECTOR LastPos = VScale(BallPosHist_tmp.front(), 120.0F / Size);
	BallPosHist_tmp.pop();
	while(EndNum && !BallPosHist_tmp.empty()) {
		const VECTOR NextPos = VScale(BallPosHist_tmp.front(), 120.0F / Size);
		BallPosHist_tmp.pop();
		DrawLineAA(640.0F + LastPos.x, 360.0F - LastPos.z, 640.0F + NextPos.x, 360.0F - NextPos.z, GetColor(255, 0, 0)); // �O�Ղ̐�
		LastPos = NextPos;
		--EndNum;
	}
	DrawCircle(640 + static_cast<int>(LastPos.x), 360 - static_cast<int>(LastPos.z), 120 / Size, GetColor(255, 0, 0), TRUE); // �擪��
	// �I��
	return;
}