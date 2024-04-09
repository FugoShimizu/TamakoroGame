#pragma once
#include <string>
#include <utility>
#include "setting.h"

// �^�C�g����ʃN���X
class TitleScreen {
public:
	TitleScreen(); // �R���X�g���N�^
	bool DrawScreen(const bool &SkipTitle); // ��ʕ`��֐�
private:
	std::pair<bool, StageForm> StageTypeTmp; // �X�e�[�W�̌`�ݒ�ifirst�F�����_�����Csecond�F�񃉃��_�����̒l�j
	std::pair<bool, int> StageSizeTmp; // �X�e�[�W�̑傫���ݒ�ifirst�F�����_�����Csecond�F�񃉃��_�����̒l�j
	std::pair<bool, int> StageSeedTmp; // �X�e�[�W�̃V�[�h�ݒ�ifirst�F�����_�����Csecond�F�񃉃��_�����̒l�j
	std::string SeedStr; // �X�e�[�W�V�[�h�̕�����
	int BGGraphHandle; // �w�i�O���t�n���h��
	int TitleGraphHandle; // �^�C�g���O���t�n���h��
};