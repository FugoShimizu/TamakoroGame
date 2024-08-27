#include <algorithm>
#include <random>
#include "setting.h"

// �R���X�g���N�^
void Setting::SetStageInfo(const std::pair<bool, StageForm> &StageType, const std::pair<bool, int> &StageSize, const std::pair<bool, int> &StageSeed) {
	// �����̐���
	std::random_device SeedGen; // �񌈒�_�I����������
	std::mt19937 Engine(SeedGen()); // �p�����[�^��`�ϋ[������������
	std::uniform_int_distribution<int> DistType(0, 1); // ��l���z
	std::normal_distribution<float> DistSize(16.0F, 2.5F); // ���K���z
	// �e�ݒ�l�̐ݒ�
	Type = StageType.first ? static_cast<StageForm>(DistType(Engine)) : StageType.second; // �X�e�[�W�̌`
	Size = StageSize.first ? std::clamp(static_cast<int>(DistSize(Engine)), 8, 24) : std::clamp(StageSize.second, 2, 32); // �X�e�[�W�̑傫��
	Seed = StageSeed.first ? SeedGen() : StageSeed.second; // �V�[�h�l
	// �I��
	return;
}

// �X�e�[�W�^�C�v�擾�֐�
StageForm Setting::GetStageType() {
	// �I��
	return Type; // �X�e�[�W�̌`��Ԃ�
}

// �X�e�[�W�T�C�Y�擾�֐�
int Setting::GetStageSize() {
	// �I��
	return Size; // �X�e�[�W�̑傫����Ԃ�
}

// �X�e�[�W�V�[�h�擾�֐�
int Setting::GetStageSeed() {
	// �I��
	return Seed; // �V�[�h�l��Ԃ�
}
