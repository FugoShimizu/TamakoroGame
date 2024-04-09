#include <algorithm>
#include <cmath>
#include "camera.h"
#include "input.h"
#include "setting.h"

// �R���X�g���N�^
Camera::Camera() {
	// �����o�ϐ��̏�����
	Viewpoint = 0;
	Reset(); // �J�����ʒu
	// �摜�̓Ǎ�
	BGGraphHandle = LoadGraph("graphs\\background.png"); // �w�i
	// �J�����̐ݒ�
	SetCameraNearFar(0.5F, 256.0F); // �`�拗��
	// �I��
	return;
}

// �ʒu�������֐�
void Camera::Reset() {
	// �J�����ʒu�̏�����
	DirectionV = 24;
	DirectionH = 0;
	Distance = std::clamp(Setting::GetStageSize() * 5, 10, 160);
	// �I��
	return;
}

// �ړ��֐�
void Camera::Move(const VECTOR &BallLocation, const float &CamAngLowLim, const bool &CursorOnMiniMap) {
	// ����̎w��
	SetupCamera_Perspective(DX_PI_F / 3.0F);
	SetCameraScreenCenter(640, 360);
	// �J�����̑���
	Control(CamAngLowLim, CursorOnMiniMap);
	// �J�������_�̐ؑ�
	if(Input::GetKeyPress(KEY_INPUT_F5)) ++Viewpoint %= 3; // F5�L�[�Őؑ�
	switch(Viewpoint) {
	case 0: // ��_�J����
		SetCameraPositionAndTargetAndUpVec(Position, VGet(0.0F, 0.0F, 0.0F), Overhead);
		break;
	case 1: // �ǐՃJ����
		SetCameraPositionAndTargetAndUpVec(VAdd(Position, BallLocation), BallLocation, Overhead);
		break;
	case 2: // �{�[�����_�J����
		SetCameraPositionAndAngle(BallLocation, (DirectionV - 24) * UnitMoveAng, DirectionH * UnitMoveAng, 0.0F);
		break;
	}
	// �I��
	return;
}

// ����֐�
void Camera::Control(const float &CamAngLowLim, const bool &CursorOnMiniMap) {
	// �J�����̏㉺�E���E�ړ�
	DirectionV -= Input::GetUDMove(); // �㉺����
	DirectionH -= Input::GetLRMove(); // ���E����
	DirectionV = std::clamp(DirectionV, 0, 32); // �p��͈͓��ɐ���
	DirectionH = DirectionH < -64 ? 63 : DirectionH > 63 ? -64 : DirectionH; // �����p��͈͓��ɐ���
	// �J�����̃Y�[��
	if(!CursorOnMiniMap) { // �J�[�\�����~�j�}�b�v��ɖ�����
		Distance -= GetMouseWheelRotVol(); // �}�E�X�z�C�[���Ŋg�k
		Distance = std::clamp(Distance, 10, 160); // �g�k��͈͓��ɐ���
	}
	// �J�����ʒu
	if(Input::GetKeyPress(KEY_INPUT_R)) Reset(); // R�L�[�Ń��Z�b�g
	const float AngleV = (std::max)(DirectionV * UnitMoveAng, CamAngLowLim); // �J�������X�e�[�W�̉��ɍs���Ȃ��l�ɂ���
	const float AngleH = DirectionH * UnitMoveAng;
	PositionY = sinf(AngleV);
	PositionR = cosf(AngleV);
	PositionX = -sinf(AngleH);
	PositionZ = -cosf(AngleH);
	Position = VAdd(VScale(VGet(PositionX * PositionR, PositionY, PositionZ * PositionR), static_cast<float>(Distance)), VGet(0.0F, 3.0F, 0.0F));
	Overhead = VGet(-PositionX, static_cast<float>(Distance), -PositionZ);
	// �f�o�b�O�p
//	clsDx(); printfDx("Cam: (V= %d, H= %d, D= %d)", DirectionV, DirectionH, Distance);
	// �I��
	return;
}

// �����p�擾�֐�
float Camera::GetDirection() const {
	// �I��
	return DirectionH * UnitMoveAng; // �����p��Ԃ�
}

// �w�i�`��֐�
void Camera::DrawBackground() const {
	// �w�i�̕`��
	DrawModiGraph(0, 0, 1280, 0, 1280, 720, 0, 720, DerivationGraph(0, (std::min)(static_cast<int>(PositionY * 256.0F), 255), 128, (std::max)(static_cast<int>((1.0F - PositionY) * 128.0F), 1), BGGraphHandle), FALSE);
	// �I��
	return;
}