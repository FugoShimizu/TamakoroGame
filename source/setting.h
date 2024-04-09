#pragma once
#include <utility>

// �X�e�[�W�^�C�v�񋓌^�\����
enum struct StageForm {
	SQR,
	HEX
};

// �X�e�[�W�ݒ���N���X
class Setting {
public:
	static void SetStageInfo(const std::pair<bool, StageForm> &StageType, const std::pair<bool, int> &StageSize, const std::pair<bool, int> &StageSeed); // �X�e�[�W���ݒ�֐�
	static StageForm GetStageType(); // �X�e�[�W�^�C�v�擾�֐�
	static int GetStageSize(); // �X�e�[�W�T�C�Y�擾�֐�
	static int GetStageSeed(); // �X�e�[�W�V�[�h�擾�֐�
private:
	static inline StageForm Type = StageForm::SQR; // �X�e�[�W�^�C�v
	static inline int Size = 16; // �X�e�[�W�T�C�Y
	static inline int Seed = 0; // �X�e�[�W�V�[�h
};