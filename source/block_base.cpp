#include "block_base.h"

// ���f���n���h���擾�֐�
int BlockBase::GetModel() const {
	// �I��
	return ModelHandle; // ���f���n���h����Ԃ�
}

// ���f���n���h���폜�֐�
void BlockBase::DeleteModel() const {
	// ���f���̍폜
	MV1DeleteModel(ModelHandle);
	// �I��
	return;
}

// �Փ˔��蔽�f�֐�
void BlockBase::CollisionDetection(const float &Distance, const float &Angle, VECTOR &BallPos, VECTOR &BallVel) const {
	// �Փ˂ɂ��{�[���̈ʒu�Ƒ��x�̏C��
	if(Distance < 1.0F) { // �{�[�����Փ˂��Ă��鎞
		// �ǂ̖@����X�������ւ̕ϊ�
		MATRIX RotationMat = MGetRotY(Angle); // ��]�s��
		BallPos = VTransformSR(BallPos, RotationMat);
		BallVel = VTransformSR(BallVel, RotationMat);
		// �Փ˂ɂ��ʒu�Ƒ��x�̏C��
		BallPos.x += 1.0F - Distance;
		BallVel.x *= RepulsionCoefficient;
		CollisionSound(BallVel.x); // �Փˉ�
		// �����̍ĕϊ�
		RotationMat = MGetRotY(-Angle); // ��]�s��
		BallPos = VTransformSR(BallPos, RotationMat);
		BallVel = VTransformSR(BallVel, RotationMat);
	}
	// �I��
	return;
}

// �Փˉ��Đ��֐�
void BlockBase::CollisionSound(const float &ImpactVel) const {
	// �Փˉ��̍Đ�
	if(ImpactVel > 0.01F) { // 臒l�ȏ�̑��x�ŏՓ˂�����
		// ���ʂ̐ݒ�
		ChangeNextPlayVolumeSoundMem(static_cast<int>(ImpactVel * 1024.0F), CollisionSoundHandle);
		// �����̍Đ�
		PlaySoundMem(CollisionSoundHandle, DX_PLAYTYPE_BACK);
		// �f�o�b�O�p
	//	clsDx(); printfDx("%f", ImpactVel);
	}
	// �I��
	return;
}