#include <array>
#include "Maze_sqr.h"
#include "setting.h"

// コンストラクタ
MazeSqr::MazeSqr() : Engine(Setting::GetStageSeed()), Dist(0, 3) {
	// 迷路の大きさを取得
	Size = Setting::GetStageSize();
	// 迷路の生成
	Generate();
	// ブロック情報の生成
	Transform();
	// 終了
	return;
}

// 迷路生成関数
void MazeSqr::Generate() {
	// 迷路の生成
	Maze = std::vector<std::vector<NodeQ>>(Size, std::vector<NodeQ>(Size));
	Maze[0][Size - 1].Open = false;
	Dig(0, Size - 1); // ゴール位置から生成を開始する
	// 終了
	return;
}

// 迷路変換関数
void MazeSqr::Transform() {
	// 各ノード情報のブロックの情報への変換
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
	// 終了
	return;
}

// 再帰的穴掘法関数
void MazeSqr::Dig(const int &NowLat, const int &NowLon) {
	// ロード画面の描画
	LoadScr.DrawScreen();
	// 各方向の未探索判定
	bool North = true, South = true, West = true, East = true;
	// 全方向のランダムな探索
	while(North || South || West || East) switch(Dist(Engine)) {
	case 0: // 北方向
		if(NowLat > 0 && Maze[NowLat - 1][NowLon].Open) { // 未探索の時
			Maze[NowLat][NowLon].PathN = true;
			Maze[NowLat - 1][NowLon].Open = false;
			Maze[NowLat - 1][NowLon].PathS = true;
			Dig(NowLat - 1, NowLon); // 次のノードに進む
		}
		North = false; // 探索済にする
		break;
	case 1: // 南方向
		if(NowLat < Size - 1 && Maze[NowLat + 1][NowLon].Open) { // 未探索の時
			Maze[NowLat][NowLon].PathS = true;
			Maze[NowLat + 1][NowLon].Open = false;
			Maze[NowLat + 1][NowLon].PathN = true;
			Dig(NowLat + 1, NowLon); // 次のノードに進む
		}
		South = false; // 探索済にする
		break;
	case 2: // 西方向
		if(NowLon > 0 && Maze[NowLat][NowLon - 1].Open) { // 未探索の時
			Maze[NowLat][NowLon].PathW = true;
			Maze[NowLat][NowLon - 1].Open = false;
			Maze[NowLat][NowLon - 1].PathE = true;
			Dig(NowLat, NowLon - 1); // 次のノードに進む
		}
		West = false; // 探索済にする
		break;
	case 3: // 東方向
		if(NowLon < Size - 1 && Maze[NowLat][NowLon + 1].Open) { // 未探索の時
			Maze[NowLat][NowLon].PathE = true;
			Maze[NowLat][NowLon + 1].Open = false;
			Maze[NowLat][NowLon + 1].PathW = true;
			Dig(NowLat, NowLon + 1); // 次のノードに進む
		}
		East = false; // 探索済にする
		break;
	}
	// 終了
	return;
}

// 迷路取得関数
std::vector<std::vector<std::pair<int, int>>> MazeSqr::GetPath() const {
	// 終了
	return Path; // 迷路のデータを返す
}