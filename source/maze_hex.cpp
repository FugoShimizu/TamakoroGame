#include <array>
#include "Maze_hex.h"
#include "setting.h"

// �R���X�g���N�^
MazeHex::MazeHex() : Engine(Setting::GetStageSeed()), Dist2(0, 1), Dist3(0, 2) {
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
void MazeHex::Generate() {
	// ���H�̐���
	Maze = std::vector<std::vector<std::pair<NodeT, NodeT>>>(Size, std::vector<std::pair<NodeT, NodeT>>(Size));
	Maze[0][Size - 1].first.Open = false;
	Maze[0][Size - 1].second.Open = false;
	Maze[0][Size - 1].first.Path6 = true;
	Maze[0][Size - 1].second.Path6 = true;
	if(Dist2(Engine)) DigN(0, Size - 1); // �S�[���ʒu���琶�����J�n����
	else DigS(0, Size - 1);
	// �I��
	return;
}

// ���H�ϊ��֐�
void MazeHex::Transform() {
	// �e�m�[�h���̃u���b�N�̏��ւ̕ϊ�
	Path = std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>>(Size, std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>(Size));
	std::array<std::array<std::array<std::pair<int, int>, 2>, 2>, 2> Transformer = {{
		{{{std::make_pair(-1, 0), std::make_pair(0, 1)}, {std::make_pair(0, 0), std::make_pair(1, 2)}}},
		{{{std::make_pair(0, 2), std::make_pair(1, 0)}, {std::make_pair(1, 1), std::make_pair(2, 0)}}}
	}};
	for(int i = 0; i < Size; ++i) for(int j = 0; j < Size; ++j) Path[i][j] = std::make_pair(Transformer[Maze[i][j].first.Path2][Maze[i][j].first.Path6][Maze[i][j].first.Path10], Transformer[Maze[i][j].second.Path2][Maze[i][j].second.Path6][Maze[i][j].second.Path10]);
	// �I��
	return;
}

// �ċA�I���@�@�֐��i�k�m�[�h�j
void MazeHex::DigN(const int &NowLat, const int &NowLon) {
	// ���[�h��ʂ̕`��
	LoadScr.DrawScreen();
	// �e�����̖��T������
	bool Tiger = true, Horse = true, Dog = true;
	// �S�����̃����_���ȒT��
	while(Tiger || Horse || Dog) switch(Dist3(Engine)) {
	case 0: // �Е���
		if(NowLat > 0 && Maze[NowLat - 1][NowLon].second.Open) { // ���T���̎�
			Maze[NowLat][NowLon].first.Path2 = true;
			Maze[NowLat - 1][NowLon].second.Open = false;
			Maze[NowLat - 1][NowLon].second.Path2 = true;
			DigS(NowLat - 1, NowLon); // ���̃m�[�h�ɐi��
		}
		Tiger = false; // �T���ςɂ���
		break;
	case 1: // �ߕ���
		if(NowLat + NowLon <= (Size - 1) * 2 - Size / 2 && Maze[NowLat][NowLon].second.Open) { // ���T���̎�
			Maze[NowLat][NowLon].first.Path6 = true;
			Maze[NowLat][NowLon].second.Open = false;
			Maze[NowLat][NowLon].second.Path6 = true;
			DigS(NowLat, NowLon); // ���̃m�[�h�ɐi��
		}
		Horse = false; // �T���ςɂ���
		break;
	case 2: // ������
		if(NowLon > 0 && Maze[NowLat][NowLon - 1].second.Open) { // ���T���̎�
			Maze[NowLat][NowLon].first.Path10 = true;
			Maze[NowLat][NowLon - 1].second.Open = false;
			Maze[NowLat][NowLon - 1].second.Path10 = true;
			DigS(NowLat, NowLon - 1); // ���̃m�[�h�ɐi��
		}
		Dog = false; // �T���ςɂ���
		break;
	}
	// �I��
	return;
}

// �ċA�I���@�@�֐��i��m�[�h�j
void MazeHex::DigS(const int &NowLat, const int &NowLon) {
	// ���[�h��ʂ̕`��
	LoadScr.DrawScreen();
	// �e�����̖��T������
	bool Monkey = true, Rat = true, Dragon = true;
	// �S�����̃����_���ȒT��
	while(Monkey || Rat || Dragon) switch(Dist3(Engine)) {
	case 0: // �\����
		if(NowLat < Size - 1 && Maze[NowLat + 1][NowLon].first.Open) { // ���T���̎�
			Maze[NowLat][NowLon].second.Path2 = true;
			Maze[NowLat + 1][NowLon].first.Open = false;
			Maze[NowLat + 1][NowLon].first.Path2 = true;
			DigN(NowLat + 1, NowLon);  // ���̃m�[�h�ɐi��
		}
		Monkey = false; // �T���ςɂ���
		break;
	case 1: // �q����
		if(NowLat + NowLon >= Size / 2 && Maze[NowLat][NowLon].first.Open) { // ���T���̎�
			Maze[NowLat][NowLon].second.Path6 = true;
			Maze[NowLat][NowLon].first.Open = false;
			Maze[NowLat][NowLon].first.Path6 = true;
			DigN(NowLat, NowLon); // ���̃m�[�h�ɐi��
		}
		Rat = false; // �T���ςɂ���
		break;
	case 2: // �C����
		if(NowLon < Size - 1 && Maze[NowLat][NowLon + 1].first.Open) { // ���T���̎�
			Maze[NowLat][NowLon].second.Path10 = true;
			Maze[NowLat][NowLon + 1].first.Open = false;
			Maze[NowLat][NowLon + 1].first.Path10 = true;
			DigN(NowLat, NowLon + 1); // ���̃m�[�h�ɐi��
		}
		Dragon = false; // �T���ςɂ���
		break;
	}
	// �I��
	return;
}

// ���H�擾�֐�
std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>> MazeHex::GetPath() const {
	// �I��
	return Path; // ���H�̃f�[�^��Ԃ�
}