#include <array>
#include "Maze_hex.h"
#include "setting.h"

// コンストラクタ
MazeHex::MazeHex() : Engine(Setting::GetStageSeed()), Dist2(0, 1), Dist3(0, 2) {
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
void MazeHex::Generate() {
	// 迷路の生成
	Maze = std::vector<std::vector<std::pair<NodeT, NodeT>>>(Size, std::vector<std::pair<NodeT, NodeT>>(Size));
	Maze[0][Size - 1].first.Open = false;
	Maze[0][Size - 1].second.Open = false;
	Maze[0][Size - 1].first.Path6 = true;
	Maze[0][Size - 1].second.Path6 = true;
	if(Dist2(Engine)) DigN(0, Size - 1); // ゴール位置から生成を開始する
	else DigS(0, Size - 1);
	// 終了
	return;
}

// 迷路変換関数
void MazeHex::Transform() {
	// 各ノード情報のブロックの情報への変換
	Path = std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>>(Size, std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>(Size));
	std::array<std::array<std::array<std::pair<int, int>, 2>, 2>, 2> Transformer = {{
		{{{std::make_pair(-1, 0), std::make_pair(0, 1)}, {std::make_pair(0, 0), std::make_pair(1, 2)}}},
		{{{std::make_pair(0, 2), std::make_pair(1, 0)}, {std::make_pair(1, 1), std::make_pair(2, 0)}}}
	}};
	for(int i = 0; i < Size; ++i) for(int j = 0; j < Size; ++j) Path[i][j] = std::make_pair(Transformer[Maze[i][j].first.Path2][Maze[i][j].first.Path6][Maze[i][j].first.Path10], Transformer[Maze[i][j].second.Path2][Maze[i][j].second.Path6][Maze[i][j].second.Path10]);
	// 終了
	return;
}

// 再帰的穴掘法関数（北ノード）
void MazeHex::DigN(const int &NowLat, const int &NowLon) {
	// ロード画面の描画
	LoadScr.DrawScreen();
	// 各方向の未探索判定
	bool Tiger = true, Horse = true, Dog = true;
	// 全方向のランダムな探索
	while(Tiger || Horse || Dog) switch(Dist3(Engine)) {
	case 0: // 寅方向
		if(NowLat > 0 && Maze[NowLat - 1][NowLon].second.Open) { // 未探索の時
			Maze[NowLat][NowLon].first.Path2 = true;
			Maze[NowLat - 1][NowLon].second.Open = false;
			Maze[NowLat - 1][NowLon].second.Path2 = true;
			DigS(NowLat - 1, NowLon); // 次のノードに進む
		}
		Tiger = false; // 探索済にする
		break;
	case 1: // 午方向
		if(NowLat + NowLon <= (Size - 1) * 2 - Size / 2 && Maze[NowLat][NowLon].second.Open) { // 未探索の時
			Maze[NowLat][NowLon].first.Path6 = true;
			Maze[NowLat][NowLon].second.Open = false;
			Maze[NowLat][NowLon].second.Path6 = true;
			DigS(NowLat, NowLon); // 次のノードに進む
		}
		Horse = false; // 探索済にする
		break;
	case 2: // 戌方向
		if(NowLon > 0 && Maze[NowLat][NowLon - 1].second.Open) { // 未探索の時
			Maze[NowLat][NowLon].first.Path10 = true;
			Maze[NowLat][NowLon - 1].second.Open = false;
			Maze[NowLat][NowLon - 1].second.Path10 = true;
			DigS(NowLat, NowLon - 1); // 次のノードに進む
		}
		Dog = false; // 探索済にする
		break;
	}
	// 終了
	return;
}

// 再帰的穴掘法関数（南ノード）
void MazeHex::DigS(const int &NowLat, const int &NowLon) {
	// ロード画面の描画
	LoadScr.DrawScreen();
	// 各方向の未探索判定
	bool Monkey = true, Rat = true, Dragon = true;
	// 全方向のランダムな探索
	while(Monkey || Rat || Dragon) switch(Dist3(Engine)) {
	case 0: // 申方向
		if(NowLat < Size - 1 && Maze[NowLat + 1][NowLon].first.Open) { // 未探索の時
			Maze[NowLat][NowLon].second.Path2 = true;
			Maze[NowLat + 1][NowLon].first.Open = false;
			Maze[NowLat + 1][NowLon].first.Path2 = true;
			DigN(NowLat + 1, NowLon);  // 次のノードに進む
		}
		Monkey = false; // 探索済にする
		break;
	case 1: // 子方向
		if(NowLat + NowLon >= Size / 2 && Maze[NowLat][NowLon].first.Open) { // 未探索の時
			Maze[NowLat][NowLon].second.Path6 = true;
			Maze[NowLat][NowLon].first.Open = false;
			Maze[NowLat][NowLon].first.Path6 = true;
			DigN(NowLat, NowLon); // 次のノードに進む
		}
		Rat = false; // 探索済にする
		break;
	case 2: // 辰方向
		if(NowLon < Size - 1 && Maze[NowLat][NowLon + 1].first.Open) { // 未探索の時
			Maze[NowLat][NowLon].second.Path10 = true;
			Maze[NowLat][NowLon + 1].first.Open = false;
			Maze[NowLat][NowLon + 1].first.Path10 = true;
			DigN(NowLat, NowLon + 1); // 次のノードに進む
		}
		Dragon = false; // 探索済にする
		break;
	}
	// 終了
	return;
}

// 迷路取得関数
std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>> MazeHex::GetPath() const {
	// 終了
	return Path; // 迷路のデータを返す
}