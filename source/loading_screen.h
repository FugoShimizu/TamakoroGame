#pragma once

// ���[�h��ʃN���X
class LoadingScreen {
public:
	LoadingScreen(); // �R���X�g���N�^
	void DrawScreen(); // ��ʕ`��֐�
private:
	int TotalNodes; // ���m�[�h��
	int LoadedNodes; // �T���σm�[�h��
	int BGGraphHandle; // �w�i�O���t�n���h��
};