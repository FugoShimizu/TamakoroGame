#include <DxLib.h>
#include "play_screen.h"
#include "input.h"
#include "Camera.h"
#include "model.h"
#include "button.h"
#include "time.h"

// �R���X�g���N�^
PlayScreen::PlayScreen() {
	// ���C�g�̐ݒ�
	SetLightEnable(FALSE);
	SetGlobalAmbientLight(GetColorF(0.2F, 0.2F, 0.2F, 0.0F));
	LightHandle = CreateDirLightHandle(VGet(-0.125F, -1.0F, -0.25F));
	SetLightDifColorHandle(LightHandle, GetColorF(1.0F, 1.0F, 1.0F, 1.0F));
	SetLightSpcColorHandle(LightHandle, GetColorF(0.5F, 0.5F, 0.5F, 0.0F));
	SetLightAmbColorHandle(LightHandle, GetColorF(0.0F, 0.0F, 0.0F, 0.0F));
	// �{�[�����ӂ̉e�̐ݒ�
	NearShadowMapHandle = MakeShadowMap(4096, 4096);
	SetShadowMapLightDirection(NearShadowMapHandle, VGet(-0.26F, -1.0F, -0.45F));
	SetShadowMapDrawArea(NearShadowMapHandle, VGet(-16.0F, -8.0F, -16.0F), VGet(16.0F, 8.0F, 16.0F));
	// �{�[�������̉e�̐ݒ�
	FarShadowMapHandle = MakeShadowMap(4096, 4096);
	SetShadowMapLightDirection(FarShadowMapHandle, VGet(-0.26F, -1.0F, -0.45F));
	SetShadowMapDrawArea(FarShadowMapHandle, VGet(-64.0F, -32.0F, -64.0F), VGet(64.0F, 32.0F, 64.0F));
	// �����̓Ǎ�
	StartSoundHandle = LoadSoundMem("sounds\\start_sound.mp3", 1);
	GoalSoundHandle = LoadSoundMem("sounds\\goal_sound.mp3", 1);
	BGMSoundHandle = LoadSoundMem("sounds\\bgm_sound.mp3", 1);
	// �t�H���g�̐���
	FontHandle = CreateFontToHandle(NULL, 140, 4);
	// �I��
	return;
}

// ��ʕ`��֐�
bool PlayScreen::DrawScreen() {
	// �I�u�W�F�N�g
	Camera Cam; // �J����
	Model Mdl; // 3D���f��
	const Button Btn; // �I���{�^��
	Time Tm; // ����
	// �O�Օ\���t���O
	int ShowRoute = 0;
	// �X�^�[�g���̍Đ�
	ChangeNextPlayVolumeSoundMem(128, StartSoundHandle);
	PlaySoundMem(StartSoundHandle, DX_PLAYTYPE_BACK);
	// BGM�̍Đ�
	ChangeNextPlayVolumeSoundMem(128, BGMSoundHandle);
	PlaySoundMem(BGMSoundHandle, DX_PLAYTYPE_LOOP);
	// �v���C��ʂ̕`��
	while(!Input::ExitOperation() && !Input::GetKeyPress(KEY_INPUT_T)) {
		// ���͏�Ԃ̍X�V
		Input::SetInput();
		// �X�e�[�W�̌����̐ݒ�
		const float CamAng = Mdl.Rotate(Cam.GetDirection());
		// �{�[���̈ʒu�̌v�Z
		const bool Goal = Mdl.Simulate();
		// �J�����ʒu�̐ݒ�
		Cam.Move(Mdl.GetBallLocation(), CamAng, Mdl.SwitchDisplay());
		// ��ʂ̃N���A
		ClearDrawScreen();
		// �{�[�����ӂ̃V���h�E�}�b�v�ւ̕`��
		SetShadowMapDrawArea(NearShadowMapHandle, VSub(Mdl.GetBallLocation(), VGet(16.0F, 8.0F, 16.0F)), VAdd(Mdl.GetBallLocation(), VGet(16.0F, 8.0F, 16.0F))); // �`��̈���{�[�����ӂɐݒ�
		ShadowMap_DrawSetup(NearShadowMapHandle);
		Mdl.DrawNearModel();
		ShadowMap_DrawEnd();
		// �{�[�������̃V���h�E�}�b�v�ւ̕`��
		ShadowMap_DrawSetup(FarShadowMapHandle);
		Mdl.DrawFarModel();
		ShadowMap_DrawEnd();
		// �`��
		Cam.DrawBackground(); // �w�i
		SetUseShadowMap(0, NearShadowMapHandle);
		SetUseShadowMap(1, FarShadowMapHandle);
		Mdl.DrawModel(); // 3D���f��
		SetUseShadowMap(0, -1);
		SetUseShadowMap(1, -1);
		Mdl.DrawInfo(Cam.GetDirection()); // �摜��
		// �S�[����ʂ̕`��
		if(Goal) { // �S�[���ς̎�
			// �w�i
			SetDrawBlendMode(DX_BLENDMODE_ADD, 192);
			DrawBox(0, 0, 1280, 720, GetColor(255, 255, 255), TRUE); // �w�i�𔒂�����
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			// �S�[�����̌o�ߎ���
			if(Tm.DrawGoalTime()) { // �S�[����
				// �S�[�����̍Đ�
				ChangeNextPlayVolumeSoundMem(128, GoalSoundHandle);
				PlaySoundMem(GoalSoundHandle, DX_PLAYTYPE_BACK);
				// BGM�̒�~
				StopSoundMem(BGMSoundHandle);
			}
			// �I���{�^��
			if(ShowRoute) {
				// �O�Չ�ʂ̕\��
				Mdl.DrawRoute(ShowRoute);
				if(ShowRoute < INT_MAX) ++ShowRoute;
				ShowRoute *= !Input::GetUnclick();
			} else {
				// �uGOAL!�v�̕\��
				DrawStringToHandle(290, 70, "�f�n�`�k�I", GetColor(0, 0, 255), FontHandle);
				// �O�Օ\���{�^��
				ShowRoute = Btn.DrawButton(96, 300, "�O�Պm�F"); // �{�^���N���b�N���͋O�Չ�ʂ�\��
				// �ăv���C�{�^��
				if(Btn.DrawButton(490, 300, "�ăv���C") || Input::GetKeyPress(KEY_INPUT_RETURN)) return true; // �{�^���N���b�N���͍ăv���C
				// �^�C�g���ɖ߂�{�^��
				if(Btn.DrawButton(874, 300, "�^�C�g��")) return false; // �{�^���N���b�N���̓^�C�g����ʂɖ߂�
			}
		} else Tm.DrawTime(); // �o�ߎ���
		// ����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
	}
	// BGM�̒�~
	StopSoundMem(BGMSoundHandle);
	// �I��
	return false;
}