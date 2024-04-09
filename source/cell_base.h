#pragma once
#include <DxLib.h>

// �Z�����N���X
class CellBase {
public:
	void SetTexture(const int &GraphHandle) const; // �e�N�X�`���ݒ�֐� // ���g�p
	void Draw(const MATRIX &RotationMat) const; // �`��֐�
protected:
	CellBase(); // �R���X�g���N�^
	int ModelHandle; // �Z���̃n���h��
	float Direction;	// �Z���̌���
	VECTOR Location;	// �Z���̍��W
};