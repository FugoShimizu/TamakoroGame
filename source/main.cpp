#include <DxLib.h>
#include "input.h"
#include "title_screen.h"
#include "play_screen.h"

// ���C���֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	// �����ݒ�
	ChangeWindowMode(TRUE); // �E�C���h�E���[�h�ŋN��
	SetMainWindowText("TamakoroGame"); // �E�C���h�E�^�C�g���̐ݒ�
	SetGraphMode(1280, 720, 32); // ��ʃ��[�h��720p�ɐݒ�
	SetFullSceneAntiAliasingMode(4, 4); // �A���`�G�C���A�X�̐ݒ�
	if(DxLib_Init() == -1) return -1; // �c�w���C�u�����̏�����
	SetDrawScreen(DX_SCREEN_BACK); // �`���𗠉�ʂɐݒ�
	// �I�u�W�F�N�g
	TitleScreen TitleScr; // �^�C�g�����
	PlayScreen PlayScr; // �v���C���
	// �^�C�g���X�L�b�v�t���O
	bool SkipTitle = false;
	// ���C�����[�v
	while(!Input::ExitOperation()) {
		// �^�C�g����ʂ̕\��
		if(!TitleScr.DrawScreen(SkipTitle)) break; // EXIT��I���ŏI��
		// �v���C��ʂ̕\��
		SkipTitle = PlayScr.DrawScreen();
	}
	// �c�w���C�u�����g�p�̏I������
	DxLib_End();
	// �\�t�g�̏I��
	return 0;
}