#include <algorithm>
#include <DxLib.h>
#include "button.h"
#include "input.h"

// �R���X�g���N�^
Button::Button() {
	// �����o�ϐ��̏�����
	Input::Cycle = 0;
	// �摜�̓Ǎ�
	ButtonOFFGraphHandle = LoadGraph("graphs\\button.png"); // �{�^��
	ButtonONGraphHandle = LoadGraph("graphs\\selecting_button.png"); // �I�𒆃{�^��
	RButtonOFFGraphHandle = LoadGraph("graphs\\radio_button.png"); // ���W�I���W�I
	RButtonONGraphHandle = LoadGraph("graphs\\selecting_radio_button.png"); // �I�𒆃��W�I�{�^��
	// �����̓Ǎ�
	PushSoundHandle = LoadSoundMem("sounds\\push_sound.mp3", 1);
	// �t�H���g�̐���
	FontHandle = CreateFontToHandle(NULL, 72, 2);
	// �I��
	return;
}

// �{�^���`��֐�
bool Button::DrawButton(const int &x, const int &y, const char *ButtonName) const {
	// �{�^���̕`��
	DrawGraph(x, y, ButtonOFFGraphHandle, TRUE);
	// �{�^�����̕`��
	const int Offset = (320 - GetDrawStringWidthToHandle(ButtonName, static_cast<int>(strlen(ButtonName)), FontHandle)) / 2;
	DrawStringToHandle(x + Offset, y + 24, ButtonName, GetColor(0, 0, 0), FontHandle);
	// �{�^���N���b�N�̔���
	if(Input::CursorInBox(x, y, x + 320, y + 120)) { // �{�^����ɃJ�[�\�����L�鎞
		if(Input::GetClicking()) { // �N���b�N��
			// �{�^�����x�̏㏸
			SetDrawBlendMode(DX_BLENDMODE_ADD, 64);
			DrawGraph(x, y, ButtonONGraphHandle, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		} else if(Input::GetUnclick()) { // �N���b�N������
			// �������̍Đ�
			ChangeNextPlayVolumeSoundMem(128, PushSoundHandle);
			PlaySoundMem(PushSoundHandle, DX_PLAYTYPE_BACK);
			// �I��
			return true;
		}
	}
	// �I��
	return false;
}

// ���W�I�{�^���`��֐�
bool Button::DrawRadioButton(const int &x, const int &y, const char *ButtonName, const bool &Selecting) const {
	// �{�^���̕`��
	DrawGraph(x, y, Selecting ? RButtonONGraphHandle : RButtonOFFGraphHandle, TRUE);
	// �{�^�����̕`��
	DrawString(x + 30, y + 5, ButtonName, GetColor(255, 255, 255));
	// �{�^���N���b�N�̔���
	if(!Selecting && Input::CursorInCircle(x + 12, y + 12, 12) && Input::GetUnclick()) return true; // �{�^������N���b�N������
	// �I��
	return false;
}

// �X���C�_�[�`��֐�
bool Button::DrawSlider(const int &x, const int &y, const int &MinValue, const int &MaxValue, int &Value) const {
	// �X���C�_�[�̕`��
	int Pos = x + 120 / (MaxValue - MinValue) * (Value - MinValue);
	DrawBox(x + 4, y + 10, x + 124, y + 14, GetColor(128, 128, 128), TRUE);
	DrawBox(x + 4, y + 10, Pos, y + 14, GetColor(255, 255, 255), TRUE);
	DrawBox(Pos, y + 4, Pos + 8, y + 20, GetColor(255, 255, 255), TRUE);
	// �l�̕`��
	DrawFormatString(x + 134, y + 4, GetColor(255, 255, 255), "%d", Value);
	// �X���C�_�[�̑���
	if(Input::CursorInBox(x, y + 4, x + 128, y + 20) && Input::GetClicking()) {
		// ����𔽉f
		DrawBox(Pos, y + 4, Pos + 8, y + 20, GetColor(255, 128, 0), FALSE);
		Value = std::clamp(Value + (Input::GetCursorPosX() - Pos - 4) / 4, MinValue, MaxValue);
		// �I��
		return true;
	}
	// �I��
	return false;
}

// �e�L�X�g�{�b�N�X�`��֐�
bool Button::DrawTextBox(const int &x, const int &y, std::string &ValueStr, bool &Selecting, int &CursorPos) const {
	// �e�L�X�g�{�b�N�X�̕`��
	DrawBox(x + 4, y + 2, x + 124, y + 22, GetColor(255, 255, 255), TRUE);
	// �e�L�X�g�{�b�N�X�̑I�𒆔���
	if(Input::GetUnclick()) Selecting = Input::CursorInBox(x + 4, y + 2, x + 124, y + 22); // �e�L�X�g�{�b�N�X����N���b�N����ƑI�𒆂ɂ���
	// �l�̕`��
	if(ValueStr.empty() && !Selecting) DrawString(x + 14, y + 4, "�V�[�h�����", GetColor(128, 128, 128)); // ���͕����񂪋�̎�
	else DrawFormatString(x + 14, y + 4, GetColor(0, 0, 0), "%11s", ValueStr.c_str());
	// �l�̏���
	if(Selecting) { // �e�L�X�g�{�b�N�X�I��
		// �I�𒆕\��
		DrawBox(x + 4, y + 2, x + 124, y + 22, GetColor(255, 128, 0), FALSE); // ��F�̘g��\��
		// �J�[�\���\��
		if(Input::Cycle < 64) DrawLine(x - CursorPos * 9 + 112, y + 4, x - CursorPos * 9 + 112, y + 19, GetColor(0, 0, 0));
		// �e�L�X�g�{�b�N�X�̑���
		if(!Input::Cycle) { // �L�[�̉������ɘA���œ��삳���Ԋu���󂯂�
			// �J�[�\���̈ړ�
			CursorPos += Input::GetLRMove();
			CursorPos = std::clamp(CursorPos, 0, static_cast<int>(ValueStr.length())); // �J�[�\���ړ��͈͂̐���
			// ������̑���
			if(CursorPos == ValueStr.length() && ValueStr[0] != '-' && Input::GetNumKeyPressing('-')) ValueStr.insert(ValueStr.begin(), '-'); // ���������
			if(CursorPos < ValueStr.length() || ValueStr[0] != '-') for(char Num = '0'; Num <= '9'; ++Num) if(Input::GetNumKeyPressing(Num)) ValueStr.insert(ValueStr.end() - CursorPos, Num); // ���������
			if(CursorPos < ValueStr.length() && Input::GetKeyPressing(KEY_INPUT_BACK)) ValueStr.erase(ValueStr.length() - CursorPos - 1, 1); // �ꕶ���폜
			if(ValueStr.length() > 10 && ValueStr[0] == '0') ValueStr.erase(0, 1); // ���̒l�̌�����10���ɐ���
			else if(ValueStr.length() > 11 && ValueStr[1] == '0') ValueStr.erase(1, 1); // ���̒l�̌�����10���ɐ���
		}
		// �I��
		return true;
	}
	// �I��
	return false;
}