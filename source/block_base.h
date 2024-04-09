#pragma once
#include <DxLib.h>

// �u���b�N���N���X
class BlockBase {
public:
	int GetModel() const; // ���f���n���h���擾�֐�
	void DeleteModel() const; // ���f���n���h���폜�֐�
protected:
	int ModelHandle; // ���f���n���h��
	int CollisionSoundHandle; // �Փˉ��T�E���h�n���h��
	void CollisionDetection(const float &Distance, const float &Angle, VECTOR &BallPos, VECTOR &BallVel) const; // �Փ˔��蔽�f�֐�
private:
	static constexpr float RepulsionCoefficient = -0.5F; // �����W���i���j
	void CollisionSound(const float &ImpactVel) const; // �Փˉ��Đ��֐�
};