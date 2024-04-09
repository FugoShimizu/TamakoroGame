#include <DxLib.h>
#include "title_screen.h"
#include "input.h"
#include "button.h"

// �R���X�g���N�^
TitleScreen::TitleScreen() {
	// �����o�ϐ��̏�����
	StageTypeTmp = std::make_pair(true, StageForm::SQR);
	StageSizeTmp = std::make_pair(true, 16);
	StageSeedTmp = std::make_pair(true, 0);
	// �摜�̓Ǎ�
	BGGraphHandle = LoadGraph("graphs\\background.png"); // �w�i
	TitleGraphHandle = LoadGraph("graphs\\title.png"); // �w�i
	// �I��
	return;
}

// ��ʕ`��֐�
bool TitleScreen::DrawScreen(const bool &SkipTitle) {
	// ���g���C���̃X�e�[�W�Đ���
	if(SkipTitle) { // �^�C�g���X�L�b�v�t���O
		// �X�e�[�W���̐ݒ�
		Setting::SetStageInfo(StageTypeTmp, StageSizeTmp, StageSeedTmp);
		// �Q�[�����X�^�[�g������
		return true;
	}
	// �{�^���I�u�W�F�N�g
	const Button Btn;
	// �e�L�X�g�{�b�N�X�t���O
	bool SelectingTextBox = false;
	int TextCursorPos = 0;
	// �^�C�g����ʂ�`��
	while(!Input::ExitOperation()) {
		// ���͏�Ԃ̍X�V
		Input::SetInput();
		// ��ʂ̃N���A
		ClearDrawScreen();
		// �w�i
		DrawModiGraph(0, 0, 1280, 0, 1280, 720, 0, 720, DerivationGraph(0, 221, 128, 17, BGGraphHandle), FALSE);
		// �^�C�g��
		DrawGraph(0, 0, TitleGraphHandle, TRUE);
		// �I���{�^��
		if(Btn.DrawButton(240, 320, "�I��")) return false; // �Q�[�����I��
		// �X�e�[�W�����{�^��
		if(Btn.DrawButton(720, 320, "�v���C") || Input::GetKeyPress(KEY_INPUT_RETURN)) { // �{�^���N���b�N��
			// �X�e�[�W���̐ݒ�
			Setting::SetStageInfo(StageTypeTmp, StageSizeTmp, StageSeedTmp);
			// �Q�[�����X�^�[�g
			return true;
		}
		// �X�e�[�W�̌`�̐ݒ�t�h
		DrawString(480, 480, "�X�e�[�W�̌`", GetColor(0, 0, 0));
		if(Btn.DrawRadioButton(500, 500, "�����_��", StageTypeTmp.first)) StageTypeTmp.first = true;
		if(Btn.DrawRadioButton(600, 500, "�l�p�`", !StageTypeTmp.first && StageTypeTmp.second == StageForm::SQR)) StageTypeTmp = std::make_pair(false, StageForm::SQR);
		if(Btn.DrawRadioButton(700, 500, "�Z�p�`", !StageTypeTmp.first && StageTypeTmp.second == StageForm::HEX)) StageTypeTmp = std::make_pair(false, StageForm::HEX);
		// �X�e�[�W�̑傫���̐ݒ�t�h
		DrawString(480, 540, "�X�e�[�W�̑傫��", GetColor(0, 0, 0));
		if(Btn.DrawRadioButton(500, 560, "�����_��", StageSizeTmp.first)) StageSizeTmp.first = true;
		if(Btn.DrawRadioButton(600, 560, "", !StageSizeTmp.first)) StageSizeTmp.first = false;
		if(Btn.DrawSlider(630, 560, 2, 32, StageSizeTmp.second)) StageSizeTmp.first = false;
		// �X�e�[�W�̃V�[�h�̐ݒ�t�h
		DrawString(480, 600, "�X�e�[�W�̃V�[�h", GetColor(0, 0, 0));
		if(Btn.DrawRadioButton(500, 620, "�����_��", StageSeedTmp.first)) StageSeedTmp.first = true;
		if(Btn.DrawRadioButton(600, 620, "", !StageSeedTmp.first)) StageSeedTmp.first = false;
		if(Btn.DrawTextBox(630, 620, SeedStr, SelectingTextBox, TextCursorPos)) StageSeedTmp.first = false;
		// �V�[�h������̐��l��
		if(SeedStr.empty() || SeedStr == "-") StageSeedTmp.second = 0; // �����񂪋�Ȃ�0�ɂ���
		else {
			try {
				StageSeedTmp.second = std::stoi(SeedStr);
			} catch(...) { // �I�[�o�[�t���[��
				StageSeedTmp.second = SeedStr[0] == '-' ? INT_MIN : INT_MAX;
				SeedStr = std::to_string(StageSeedTmp.second);
			}
		}
		// ���ӎ���
		DrawString(1140, 700, "������������܂�", GetColor(255, 255, 255));
		// ����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
	}
	// �I��
	return false;
}