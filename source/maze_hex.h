#pragma once
#include <random>
#include <utility>
#include <vector>
#include "loading_screen.h"

// �m�[�h�i�O�p�j�\����
struct NodeT {
	bool Open; // ���T������
	bool Path2; // 2�������ʘH
	bool Path6; // 6�������ʘH
	bool Path10; // 10�������ʘH
	NodeT() { // �R���X�g���N�^
		Open = true;
		Path2 = false;
		Path6 = false;
		Path10 = false;
		return;
	}
};

// �Z�p�`���H�N���X
class MazeHex {
public:
	MazeHex(); // �R���X�g���N�^
	std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>> GetPath() const; // ���H�擾�֐�
private:
	std::mt19937 Engine; // �p�����[�^��`�ϋ[������������
	std::uniform_int_distribution<int> Dist2; // ��l���z�i0�`1�j
	std::uniform_int_distribution<int> Dist3; // ��l���z�i0�`2�j
	int Size; // ���H�̑傫��
	std::vector<std::vector<std::pair<NodeT, NodeT>>> Maze; // ���H�\���m�[�h�ifirst�F�k�m�[�h�Csecond�F��m�[�h�j
	std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>> Path; // ���H�\���u���b�N���ifirst�F��ށCsecond�F�����j
	LoadingScreen LoadScr; // ���[�h���
	void Generate(); // ���H�����֐�
	void Transform(); // ���H�ϊ��֐�
	void DigN(const int &NowLat, const int &NowLon); // �ċA�I���@�@�֐��i�k�m�[�h�j
	void DigS(const int &NowLat, const int &NowLon); // �ċA�I���@�@�֐��i��m�[�h�j
};