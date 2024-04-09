#include <DxLib.h>
#include "loading_screen.h"
#include "setting.h"

// �R���X�g���N�^
LoadingScreen::LoadingScreen() {
	// �����o�ϐ��̏�����
	switch(Setting::GetStageType()) {
	case StageForm::SQR:
		TotalNodes = Setting::GetStageSize() * Setting::GetStageSize();
		break;
	case StageForm::HEX:
		TotalNodes = Setting::GetStageSize() * Setting::GetStageSize() * 3 / 2 + Setting::GetStageSize() % 2 * Setting::GetStageSize() - 1;
		break;
	default:
		TotalNodes = 0;
		break;
	}
	LoadedNodes = 0;
	// �摜�̓Ǎ�
	BGGraphHandle = LoadGraph("graphs\\background.png"); // �w�i
	// �I��
	return;
}

// ��ʕ`��֐�
void LoadingScreen::DrawScreen() {
	// �T���σm�[�h���̉��Z
	++LoadedNodes;
	// ��ʂ̃N���A
	ClearDrawScreen();
	// �w�i�̕`��
	DrawModiGraph(0, 0, 1280, 0, 1280, 720, 0, 720, DerivationGraph(0, 221, 128, 17, BGGraphHandle), FALSE);
	// �Q�[�W�̕`��
	DrawString(390, 332, "Now Loading...", GetColor(255, 255, 255));
	DrawBox(390, 350, 890, 370, GetColor(128, 128, 128), TRUE);
	DrawBox(390, 350, 390 + LoadedNodes * 500 / TotalNodes, 370, GetColor(255, 255, 255), TRUE);
	DrawFormatString(900, 352, GetColor(255, 255, 255), "%3d%%", LoadedNodes * 100 / TotalNodes);
	// ����ʂ̓��e��\��ʂɔ��f
	ScreenFlip();
	// �I��
	return;
}