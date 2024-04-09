#pragma once
#include <DxLib.h>

// �{�[���N���X
class Ball {
public:
	VECTOR Pos; // �ʒu
	VECTOR Vel; // ���x
	Ball(); // �R���X�g���N�^
	void SetTexture(const int &GraphHandle) const; // �e�N�X�`���ݒ�֐� // ���g�p
	void SetPos(const VECTOR &Position); // �ʒu�ݒ�֐�
	void Position(const float &StgRotX, const float &StgRotZ); // �ړ��֐�
	void Draw(const MATRIX &RotationMat) const; // �`��֐�
private:
	int ModelHandle; // ���f���n���h��
};