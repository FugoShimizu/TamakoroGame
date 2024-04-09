#pragma once
#include <DxLib.h>

// �J�����i���_�j�N���X
class Camera {
public:
	Camera(); // �R���X�g���N�^
	void Move(const VECTOR &BallPosition, const float &CamAngLowLim, const bool &CursorOnMiniMap); // �ړ��֐�
	float GetDirection() const; // �����p�擾�֐�
	void DrawBackground() const; // �w�i�`��֐�
private:
	constexpr static float UnitMoveAng = DX_PI_F / 64.0f; // �P�ʈړ��p�x
	int Viewpoint; // ���_
	int DirectionV; // �p�i�����������������C64=180���j
	int DirectionH; // �����p�iZ����������E���C64=180���j
	float PositionY; // �p����Z�o����Y���W
	float PositionR; // �p����Z�o�������S����̋���
	float PositionX; // �����p����Z�o����X���W
	float PositionZ; // �����p����Z�o����Z���W
	VECTOR Position;
	VECTOR Overhead;
	int Distance; // �Ώۋ���
	int BGGraphHandle; // �w�i�O���t�n���h��
	void Reset(); // �ʒu�������֐�
	void Control(const float &CamAngLowLim, const bool &CursorOnMiniMap); // ����֐�
};