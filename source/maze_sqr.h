#pragma once
#include <random>
#include <utility>
#include <vector>
#include "loading_screen.h"

// �m�[�h�i�l�p�j�\����
struct NodeQ {
	bool Open; // ���T������
	bool PathN; // �k�����ʘH
	bool PathS; // ������ʘH
	bool PathE; // �������ʘH
	bool PathW; // �������ʘH
	NodeQ() { // �R���X�g���N�^
		Open = true;
		PathN = false;
		PathS = false;
		PathW = false;
		PathE = false;
		return;
	}
};

// �l�p�`���H�N���X
class MazeSqr {
public:
	MazeSqr(); // �R���X�g���N�^
	std::vector<std::vector<std::pair<int, int>>> GetPath() const; // ���H�擾�֐�
private:
	std::mt19937 Engine; // �p�����[�^��`�ϋ[������������
	std::uniform_int_distribution<int> Dist;// ��l���z�i0�`3�j
	int Size; // ���H�̑傫��
	std::vector<std::vector<NodeQ>> Maze; // ���H�\���m�[�h
	std::vector<std::vector<std::pair<int, int>>> Path; // ���H�\���u���b�N���
	LoadingScreen LoadScr; // ���[�h���
	void Generate(); // ���H�����֐�
	void Transform(); // ���H�ϊ��֐�
	void Dig(const int &now_lat, const int &now_lon); // �ċA�I���@�@�֐�
};