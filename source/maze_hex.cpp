#include "maze_hex.hpp"
#include "setting.hpp"
#include <array>

/**
 * 再帰的穴掘法関数（北ノード）
 * @param NowLat 現在のノードの緯度（0≦NowLat＜Size）
 * @param NowLon 現在のノードの経度（0≦NowLon＜Size）
 */
void MazeHex::DigN(const int NowLat, const int NowLon) {
	// ロード画面の描画
	LoadScr.DrawScreen();
	// 全方向のランダムな探索
	unsigned int OpenDirs = 0X7; // 各方向の未探索判定（bit0: 寅，bit1: 午，bit2: 戌）
	while(OpenDirs) switch(Dist3(Engine)) {
	case 0: // 寅方向
		if(NowLat && Maze[NowLat - 1][NowLon].second.IsOpen) { // 未探索の時
			Maze[NowLat][NowLon].first.HasPath2 = true;
			Maze[NowLat - 1][NowLon].second.IsOpen = false;
			Maze[NowLat - 1][NowLon].second.HasPath2 = true;
			DigS(NowLat - 1, NowLon); // 次のノードに進む
		}
		OpenDirs &= ~0X1; // 探索済にする
		break;
	case 1: // 午方向
		if(NowLat + NowLon <= (Size - 1 << 1) - (Size >> 1) && Maze[NowLat][NowLon].second.IsOpen) { // 未探索の時
			Maze[NowLat][NowLon].first.HasPath6 = true;
			Maze[NowLat][NowLon].second.IsOpen = false;
			Maze[NowLat][NowLon].second.HasPath6 = true;
			DigS(NowLat, NowLon); // 次のノードに進む
		}
		OpenDirs &= ~0X2; // 探索済にする
		break;
	case 2: // 戌方向
		if(NowLon && Maze[NowLat][NowLon - 1].second.IsOpen) { // 未探索の時
			Maze[NowLat][NowLon].first.HasPath10 = true;
			Maze[NowLat][NowLon - 1].second.IsOpen = false;
			Maze[NowLat][NowLon - 1].second.HasPath10 = true;
			DigS(NowLat, NowLon - 1); // 次のノードに進む
		}
		OpenDirs &= ~0X4; // 探索済にする
		break;
	}
	// 終了
	return;
}

/**
 * 再帰的穴掘法関数（南ノード）
 * @param NowLat 現在のノードの緯度（0≦NowLat＜Size）
 * @param NowLon 現在のノードの経度（0≦NowLon＜Size）
 */
void MazeHex::DigS(const int NowLat, const int NowLon) {
	// ロード画面の描画
	LoadScr.DrawScreen();
	// 全方向のランダムな探索
	unsigned int OpenDirs = 0X7; // 各方向の未探索判定（bit0: 申，bit1: 子，bit2: 辰）
	while(OpenDirs) switch(Dist3(Engine)) {
	case 0: // 申方向
		if(NowLat < Size - 1 && Maze[NowLat + 1][NowLon].first.IsOpen) { // 未探索の時
			Maze[NowLat][NowLon].second.HasPath2 = true;
			Maze[NowLat + 1][NowLon].first.IsOpen = false;
			Maze[NowLat + 1][NowLon].first.HasPath2 = true;
			DigN(NowLat + 1, NowLon); // 次のノードに進む
		}
		OpenDirs &= ~0X1; // 探索済にする
		break;
	case 1: // 子方向
		if(NowLat + NowLon >= Size >> 1 && Maze[NowLat][NowLon].first.IsOpen) { // 未探索の時
			Maze[NowLat][NowLon].second.HasPath6 = true;
			Maze[NowLat][NowLon].first.IsOpen = false;
			Maze[NowLat][NowLon].first.HasPath6 = true;
			DigN(NowLat, NowLon); // 次のノードに進む
		}
		OpenDirs &= ~0X2; // 探索済にする
		break;
	case 2: // 辰方向
		if(NowLon < Size - 1 && Maze[NowLat][NowLon + 1].first.IsOpen) { // 未探索の時
			Maze[NowLat][NowLon].second.HasPath10 = true;
			Maze[NowLat][NowLon + 1].first.IsOpen = false;
			Maze[NowLat][NowLon + 1].first.HasPath10 = true;
			DigN(NowLat, NowLon + 1); // 次のノードに進む
		}
		OpenDirs &= ~0X4; // 探索済にする
		break;
	}
	// 終了
	return;
}

/**
 * 迷路生成関数
 */
void MazeHex::Generate() {
	// 迷路の生成
	using NodeRow = std::vector<std::pair<NodeT, NodeT>>;
	Maze = std::vector<NodeRow>(Size, NodeRow(Size));
	Maze[0][Size - 1].first.IsOpen = false;
	Maze[0][Size - 1].second.IsOpen = false;
	Maze[0][Size - 1].first.HasPath6 = true;
	Maze[0][Size - 1].second.HasPath6 = true;
	if(Dist2(Engine)) DigN(0, Size - 1); // ゴール位置から生成を開始する
	else DigS(0, Size - 1);
	// 終了
	return;
}

/**
 * 迷路変換関数
 */
void MazeHex::Transform() {
	// 各ノード情報のブロックの情報への変換
	using PathRow = std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>;
	Path = std::vector<PathRow>(Size, PathRow(Size));
	static constexpr std::array<std::array<std::array<std::pair<int, int>, 2>, 2>, 2> Transformer = {
		{
			{ { { std::make_pair(-1, 0), std::make_pair(0, 1) }, { std::make_pair(0, 0), std::make_pair(1, 2) } } },
			{ { { std::make_pair(0, 2), std::make_pair(1, 0) }, { std::make_pair(1, 1), std::make_pair(2, 0) } } }
		}
	};
	for(int i = 0; i < Size; ++i) for(int j = 0; j < Size; ++j) {
		Path[i][j] = std::make_pair(
			Transformer[Maze[i][j].first.HasPath2][Maze[i][j].first.HasPath6][Maze[i][j].first.HasPath10],
			Transformer[Maze[i][j].second.HasPath2][Maze[i][j].second.HasPath6][Maze[i][j].second.HasPath10]
		);
	}
	// 終了
	return;
}

/**
 * 迷路取得関数
 * @return 迷路のデータ
 */
std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>> MazeHex::GetPath() const {
	// 迷路のデータの返戻
	return Path;
}

/**
 * コンストラクタ
 */
MazeHex::MazeHex() : Engine(Setting::GetStageSeed()), Dist2(0, 1), Dist3(0, 2) {
	// 迷路の大きさの取得
	Size = Setting::GetStageSize();
	// 迷路の生成
	Generate();
	// ブロック情報の生成
	Transform();
	// 終了
	return;
}
