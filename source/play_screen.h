#pragma once

// �v���C��ʃN���X
class PlayScreen {
public:
	PlayScreen(); // �R���X�g���N�^
	bool DrawScreen(); // ��ʕ`��֐�
private:
	int LightHandle; // ���C�g�n���h��
	int NearShadowMapHandle; // �{�[�����ӃV���h�E�}�b�v�n���h��
	int FarShadowMapHandle; // �{�[�������V���h�E�}�b�v�n���h��
	int StartSoundHandle; // �X�^�[�g�T�E���h�n���h�� https://dova-s.jp/se/play1047.html
	int GoalSoundHandle; // �S�[���T�E���h�n���h�� https://dova-s.jp/se/play1343.html
	int BGMSoundHandle; // BGM�T�E���h�n���h�� https://dova-s.jp/bgm/play15951.html
	int FontHandle; // �t�H���g�n���h��
};