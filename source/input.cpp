#include <DxLib.h>
#include "input.h"

// ���͏�Ԑݒ�֐�
void Input::SetInput() {
	// ���O���͏�Ԃ̕ێ�
	ClickStateTmp = ClickState;
	CursorPosTmp = CursorPos;
	KeyStateTmp = KeyState;
	// ���͏�Ԃ̎擾
	ClickState = GetMouseInput();
	GetMousePoint(&CursorPos.first, &CursorPos.second);
	GetHitKeyStateAll(&KeyState[0]);
	// �������p�J�E���g�̐i�s
	++Cycle %= 128;
	Cycle *= KeyStateTmp == KeyState; // �L�[�̉�����Ԃ̕ω���0�ɂ���
	// �I��
	return;
}

// �N���b�N��Ԏ擾�֐�
bool Input::GetClicking() {
	// �I��
	return ClickState; // �N���b�N��Ԃ�Ԃ�
}

// �N���b�N�������m�֐�
bool Input::GetUnclick() {
	// �I��
	return ClickStateTmp && !ClickState; // �N���b�N������Ԃ�
}

// �J�[�\��X�����W�擾�֐�
int Input::GetCursorPosX() {
	// �I��
	return CursorPos.first; // �J�[�\��X�����W��Ԃ�
}

// �J�[�\��X���ړ��ʎ擾�֐�
int Input::GetCursorMoveX() {
	// �I��
	return CursorPos.first - CursorPosTmp.first; // �J�[�\��X���ړ��ʂ�Ԃ�
}

// �J�[�\��Y�����W�擾�֐�
int Input::GetCursorPosY() {
	// �I��
	return CursorPos.second; // �J�[�\��Y�����W��Ԃ�
}

// �J�[�\��Y���ړ��ʎ擾�֐�
int Input::GetCursorMoveY() {
	// �I��
	return CursorPos.second - CursorPosTmp.second; // �J�[�\��Y���ړ��ʂ�Ԃ�
}

// �w��L�[������Ԏ擾�֐�
bool Input::GetKeyPressing(const int &KeyCode) {
	// �I��
	return KeyState[KeyCode]; // �w��L�[������Ԃ�Ԃ�
}

// �w��L�[�������쌟�m�֐�
bool Input::GetKeyPress(const int &KeyCode) {
	// �I��
	return !KeyStateTmp[KeyCode] && KeyState[KeyCode]; // �w��L�[���������Ԃ�
}

// �w�萔���L�[������Ԏ擾�֐�
bool Input::GetNumKeyPressing(const char &Num) {
	// �w�萔���L�[������Ԃ�Ԃ�
	switch(Num) {
	case '0':
		return KeyState[KEY_INPUT_NUMPAD0] || KeyState[KEY_INPUT_0];
	case '1':
		return KeyState[KEY_INPUT_NUMPAD1] || KeyState[KEY_INPUT_1];
	case '2':
		return KeyState[KEY_INPUT_NUMPAD2] || KeyState[KEY_INPUT_2];
	case '3':
		return KeyState[KEY_INPUT_NUMPAD3] || KeyState[KEY_INPUT_3];
	case '4':
		return KeyState[KEY_INPUT_NUMPAD4] || KeyState[KEY_INPUT_4];
	case '5':
		return KeyState[KEY_INPUT_NUMPAD5] || KeyState[KEY_INPUT_5];
	case '6':
		return KeyState[KEY_INPUT_NUMPAD6] || KeyState[KEY_INPUT_6];
	case '7':
		return KeyState[KEY_INPUT_NUMPAD7] || KeyState[KEY_INPUT_7];
	case '8':
		return KeyState[KEY_INPUT_NUMPAD8] || KeyState[KEY_INPUT_8];
	case '9':
		return KeyState[KEY_INPUT_NUMPAD9] || KeyState[KEY_INPUT_9];
	case '-':
		return KeyState[KEY_INPUT_SUBTRACT] || KeyState[KEY_INPUT_MINUS];
	}
	// �I��
	return false; // �Y�����������false��Ԃ�
}

// WSAD�L�[������Ԏ擾�֐�
bool Input::GetWSADPressing() {
	// �I��
	return KeyState[KEY_INPUT_W] || KeyState[KEY_INPUT_S] || KeyState[KEY_INPUT_A] || KeyState[KEY_INPUT_D]; // WSAD�L�[������Ԃ�Ԃ�
}

// WS�L�[������Ԏ擾�֐�
int Input::GetWSMove() {
	// �I��
	return KeyState[KEY_INPUT_W] - KeyState[KEY_INPUT_S]; // WS�L�[������Ԃ�Ԃ�
}

// AD�L�[������Ԏ擾�֐�
int Input::GetADMove() {
	// �I��
	return KeyState[KEY_INPUT_A] - KeyState[KEY_INPUT_D]; // AD�L�[������Ԃ�Ԃ�
}

// �㉺�L�[������Ԏ擾�֐�
int Input::GetUDMove() {
	// �I��
	return KeyState[KEY_INPUT_UP] - KeyState[KEY_INPUT_DOWN]; // �㉺�L�[������Ԃ�Ԃ�
}

// ���E�L�[������Ԏ擾�֐�
int Input::GetLRMove() {
	// �I��
	return KeyState[KEY_INPUT_LEFT] - KeyState[KEY_INPUT_RIGHT]; // ���E�L�[������Ԃ�Ԃ�
}

// �w���`�͈͓��J�[�\���L���֐�
bool Input::CursorInBox(const int &x1, const int &y1, const int &x2, const int &y2) {
	// �I��
	return CursorPos.first >= x1 && CursorPos.second >= y1 && CursorPos.first < x2 &&CursorPos.second < y2; // �w���`�͈͓��̃J�[�\���L����Ԃ�
}

// �w��~�`�͈͓��J�[�\���L���֐�
bool Input::CursorInCircle(const int &x, const int &y, const int &r) {
	// �I��
	return (CursorPos.first - x) * (CursorPos.first - x) + (CursorPos.second - y) * (CursorPos.second - y) < r * r; // �w��~�`�͈͓��̃J�[�\���L����Ԃ�
}

// �I������֐�
bool Input::ExitOperation() {
	// �I��
	return ProcessMessage() || KeyState[KEY_INPUT_ESCAPE]; // �I�������Ԃ�
}