#pragma once

// ���ԃN���X
class Time {
public:
	Time(); // �R���X�g���N�^
	void DrawTime() const; // �o�ߎ��ԕ`��֐�
	bool DrawGoalTime(); // �S�[�����ԕ`��֐�
private:
	int StartTime; // �X�^�[�g�����ԁi�b�j
	int GoalElapsedTime; // �S�[�����o�ߎ��ԁi�b�j
};