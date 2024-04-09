#pragma once
#include <array>
#include <utility>

// ���̓N���X
class Input {
public:
	static inline int Cycle = 0; // �������p�J�E���g
	static void SetInput(); // ���͏�Ԑݒ�֐�
	static bool GetClicking(); // �N���b�N��Ԏ擾�֐�
	static bool GetUnclick(); // �N���b�N�������m�֐�
	static int GetCursorPosX(); // �J�[�\��X�����W�擾�֐�
	static int GetCursorMoveX(); // �J�[�\��X���ړ��ʎ擾�֐�
	static int GetCursorPosY(); // �J�[�\��Y�����W�擾�֐�
	static int GetCursorMoveY(); // �J�[�\��Y���ړ��ʎ擾�֐�
	static bool GetKeyPressing(const int &KeyCode); // �w��L�[������Ԏ擾�֐�
	static bool GetKeyPress(const int &KeyCode); // �w��L�[�������쌟�m�֐�
	static bool GetNumKeyPressing(const char &Num); // �w�萔���L�[������Ԏ擾�֐�
	static bool GetWSADPressing(); // WSAD�L�[������Ԏ擾�֐�
	static int GetWSMove(); // WS�L�[������Ԏ擾�֐�
	static int GetADMove(); // AD�L�[������Ԏ擾�֐�
	static int GetUDMove(); // �㉺�L�[������Ԏ擾�֐�
	static int GetLRMove(); // ���E�L�[������Ԏ擾�֐�
	static bool CursorInBox(const int &x1, const int &y1, const int &x2, const int &y2); // �w���`�͈͓��J�[�\���L���֐�
	static bool CursorInCircle(const int &x, const int &y, const int &r); // �w��~�`�͈͓��J�[�\���L���֐�
	static bool ExitOperation(); // �I������֐�
private:
	static inline bool ClickState = false; // ���N���b�N���
	static inline bool ClickStateTmp = false; // ���O�̍��N���b�N���
	static inline std::pair<int, int> CursorPos; // �J�[�\���ʒu�ifirst�FX���W�Csecond�FY���W�j
	static inline std::pair<int, int> CursorPosTmp; // ���O�̃J�[�\���ʒu�ifirst�FX���W�Csecond�FY���W�j
	static inline std::array<char, 256> KeyState; // �e�L�[�������
	static inline std::array<char, 256> KeyStateTmp; // ���O�̊e�L�[�������
};