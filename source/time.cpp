#include <DxLib.h>
#include "time.h"

// �R���X�g���N�^
Time::Time() {
	// �����o�ϐ��̏�����
	StartTime = GetNowCount() / 1000; // ���ݎ���
	GoalElapsedTime = 0;
	// �I��
	return;
}

// �o�ߎ��ԕ`��֐�
void Time::DrawTime() const {
	// �o�ߎ��Ԃ̕`��
	const int ElapsedTime = GetNowCount() / 1000 - StartTime;
	DrawFormatString(1180, 0, GetColor(255, 255, 255), "Time %02d:%02d", ElapsedTime / 60, ElapsedTime % 60);
	// �I��
	return;
}

// �S�[�����ԕ`��֐�
bool Time::DrawGoalTime() {
	// ���ɃS�[���ςłȂ�������
	const bool Fast = !GoalElapsedTime;
	// �S�[�����o�ߎ��Ԃ̕`��
	if(Fast) GoalElapsedTime = GetNowCount() / 1000 - StartTime;
	DrawFormatString(1180, 0, GetColor(0, 0, 255), "Time %02d:%02d", GoalElapsedTime / 60, GoalElapsedTime % 60);
	// �I��
	return Fast;
}