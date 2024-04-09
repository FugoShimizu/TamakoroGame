#include <array>
#include "Maze_sqr.h"
#include "setting.h"

// �R���X�g���N�^
MazeSqr::MazeSqr() : Engine(Setting::GetStageSeed()), Dist(0, 3) {
	// ���H�̑傫�����擾
	Size = Setting::GetStageSize();
	// ���H�̐���
	Generate();
	// �u���b�N���̐���
	Transform();
	// �I��
	return;
}

// ���H�����֐�
void MazeSqr::Generate() {
	// ���H�̐���
	Maze = std::vector<std::vector<NodeQ>>(Size, std::vector<NodeQ>(Size));
	Maze[0][Size - 1].Open = false;
	Dig(0, Size - 1); // �S�[���ʒu���琶�����J�n����
	// �I��
	return;
}

// ���H�ϊ��֐�
void MazeSqr::Transform() {
	// �e�m�[�h���̃u���b�N�̏��ւ̕ϊ�
	Path = std::vector<std::vector<std::pair<int, int>>>(Size, std::vector<std::pair<int, int>>(Size));
	std::array<std::array<std::array<std::array<std::pair<int, int>, 2>, 2>, 2>, 2> transformer = {{
		{{
			{{{std::make_pair(-1, 0), std::make_pair(0, 3)}, {std::make_pair(0, 1), std::make_pair(1, 1)}}},
			{{{std::make_pair(0, 0), std::make_pair(2, 3)}, {std::make_pair(2, 0), std::make_pair(3, 3)}}}
		}}, {{
			{{{std::make_pair(0, 2), std::make_pair(2, 2)}, {std::make_pair(2, 1), std::make_pair(3, 1)}}},
			{{{std::make_pair(1, 0), std::make_pair(3, 2)}, {std::make_pair(3, 0), std::make_pair(4, 0)}}}
		}}
	}};
	for(int i = 0; i < Size; ++i) for(int j = 0; j < Size; ++j) Path[i][j] = transformer[Maze[i][j].PathN][Maze[i][j].PathS][Maze[i][j].PathW][Maze[i][j].PathE];
	// �I��
	return;
}

// �ċA�I���@�@�֐�
void MazeSqr::Dig(const int &NowLat, const int &NowLon) {
	// ���[�h��ʂ̕`��
	LoadScr.DrawScreen();
	// �e�����̖��T������
	bool North = true, South = true, West = true, East = true;
	// �S�����̃����_���ȒT��
	while(North || South || West || East) switch(Dist(Engine)) {
	case 0: // �k����
		if(NowLat > 0 && Maze[NowLat - 1][NowLon].Open) { // ���T���̎�
			Maze[NowLat][NowLon].PathN = true;
			Maze[NowLat - 1][NowLon].Open = false;
			Maze[NowLat - 1][NowLon].PathS = true;
			Dig(NowLat - 1, NowLon); // ���̃m�[�h�ɐi��
		}
		North = false; // �T���ςɂ���
		break;
	case 1: // �����
		if(NowLat < Size - 1 && Maze[NowLat + 1][NowLon].Open) { // ���T���̎�
			Maze[NowLat][NowLon].PathS = true;
			Maze[NowLat + 1][NowLon].Open = false;
			Maze[NowLat + 1][NowLon].PathN = true;
			Dig(NowLat + 1, NowLon); // ���̃m�[�h�ɐi��
		}
		South = false; // �T���ςɂ���
		break;
	case 2: // ������
		if(NowLon > 0 && Maze[NowLat][NowLon - 1].Open) { // ���T���̎�
			Maze[NowLat][NowLon].PathW = true;
			Maze[NowLat][NowLon - 1].Open = false;
			Maze[NowLat][NowLon - 1].PathE = true;
			Dig(NowLat, NowLon - 1); // ���̃m�[�h�ɐi��
		}
		West = false; // �T���ςɂ���
		break;
	case 3: // ������
		if(NowLon < Size - 1 && Maze[NowLat][NowLon + 1].Open) { // ���T���̎�
			Maze[NowLat][NowLon].PathE = true;
			Maze[NowLat][NowLon + 1].Open = false;
			Maze[NowLat][NowLon + 1].PathW = true;
			Dig(NowLat, NowLon + 1); // ���̃m�[�h�ɐi��
		}
		East = false; // �T���ςɂ���
		break;
	}
	// �I��
	return;
}

// ���H�擾�֐�
std::vector<std::vector<std::pair<int, int>>> MazeSqr::GetPath() const {
	// �I��
	return Path; // ���H�̃f�[�^��Ԃ�
}