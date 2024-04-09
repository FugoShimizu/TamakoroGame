#pragma once
#include <queue>
#include <DxLib.h>
#include "stage_sqr.h"
#include "stage_hex.h"
#include "ball.h"
#include "setting.h"

// ���f���N���X
class Model {
public:
	Model(); // �R���X�g���N�^
	VECTOR GetBallLocation() const; // �{�[�����[���h���W�擾�֐�
	float Rotate(const float &CamAngH); // �X�e�[�W�X�Α���֐�
	bool Simulate(); // �V�~�����[�g�֐�
	bool SwitchDisplay(); // �\���ؑ֊֐�
	void DrawModel() const; // ���f���`��֐�
	void DrawNearModel() const; // ���Ӄ��f���`��֐�
	void DrawFarModel() const; // �������f���`��֐�
	void DrawInfo(const float &CamAngH) const; // �摜�`��֐�
	void DrawRoute(int EndNum) const; // �O�Չ�ʕ`��֐�
private:
	static constexpr float SlopeRateDrag = 1.0f / 512.0f; // �h���b�O���쎞�X�Ί���
	static constexpr float SlopeRateWSAD = 1.0f / 64.0f; // WSAD�L�[���쎞�X�Ί���
	static constexpr float SlopeRateRdct = 15.0f / 16.0f; // �����쎞�X�Ώk������
	static constexpr float MaxSlope = DX_PI_F / 6.0f; // �ő�X�Ίp
	StageSqr StageSqr; // �l�p�`�X�e�[�W
	StageHex StageHex; // �Z�p�`�X�e�[�W
	Ball Bal; // �{�[��
	StageForm Type; // �X�e�[�W�̌`
	int Size; // �X�e�[�W�̑傫��
	bool Goal; // �S�[������
	VECTOR RotationAng; // �X�e�[�W�X�Ίp
	VECTOR CamRotAng; // �J�������_����̃X�e�[�W�X�Ίp
	MATRIX RotationMat; // ��]�s��
	VECTOR StartLoc; // �X�^�[�g�ʒu
	VECTOR GoalLoc; // �S�[���ʒu
	float StartDist; // �X�^�[�g�ƃ{�[���̒�������
	float GoalDist; // �S�[���ƃ{�[���̒�������
	bool ShowDebug; // �f�o�b�O��ʕ\���t���O
	bool ShowMiniMap; // �~�j�}�b�v�\���t���O
	int MiniMapScale; // �~�j�}�b�v�k��
	std::queue<VECTOR> BallPosHist; // �{�[���ʒu����
	int SMGraphHandle; // �X�^�[�g�}�[�J�[�O���t�n���h��
	int GMGraphHandle; // �S�[���}�[�J�[�O���t�n���h��
	void SetMarker() const; // �}�[�J�[�ݒ�֐�
	void DrawMarker(const VECTOR &ScrCoord, const int &MarkerGraphHandle, const unsigned int &FontColor, const int &Distance) const; // �}�[�J�[�`��֐�
	void DrawMiniMap(const float &CamAngH) const; // �~�j�}�b�v�`��֐�
};