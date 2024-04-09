#pragma once
#include <string>

// �{�^���i�t�h�j�N���X
class Button {
public:
	Button(); // �R���X�g���N�^
	bool DrawButton(const int &x, const int &y, const char *ButtonName) const; // �{�^���`��֐�
	bool DrawRadioButton(const int &x, const int &y, const char *ButtonName, const bool &Selecting) const; // ���W�I�{�^���`��֐�
	bool DrawSlider(const int &x, const int &y, const int &MinValue, const int &MaxValue, int &Value) const; // �X���C�_�[�`��֐�
	bool DrawTextBox(const int &x, const int &y, std::string &ValueStr, bool &Selecting, int &CursorPos) const; // �e�L�X�g�{�b�N�X�`��֐�
private:
	int ButtonOFFGraphHandle; // �{�^���O���t�n���h��
	int ButtonONGraphHandle; // �I�𒆃{�^���O���t�n���h��
	int RButtonOFFGraphHandle; // ���W�I�{�^���O���t�n���h��
	int RButtonONGraphHandle; // �I�𒆃��W�I�{�^���O���t�n���h��
	int PushSoundHandle; // �����T�E���h�n���h�� https://dova-s.jp/se/play478.html
	int FontHandle; // �t�H���g�n���h��
};