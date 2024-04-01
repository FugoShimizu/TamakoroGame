#include "maze_sqr.hpp"
#include "setting.hpp"
#include <array>

/**
 * 再帰的穴掘法関数
 * @param NowLat 現在のノードの緯度（0≦NowLat＜Size）
 * @param NowLon 現在のノードの経度（0≦NowLon＜Size）
 */
void MazeSqr::Dig(const int NowLat, const int NowLon) {
	// ロード画面の描画
	LoadScr.DrawScreen();
	// 全方向のランダムな探索
	unsigned int OpenDirs = 0XF; // 各方向の未探索判定（bit0: 北，bit1: 南，bit2: 西，bit3: 東）
	while(OpenDirs) switch(Dist(Engine)) {
	case 0: // 北方向
		if(NowLat && Maze[NowLat - 1][NowLon].IsOpen) { // 未探索の時
			Maze[NowLat][NowLon].HasPathN = true;
			Maze[NowLat - 1][NowLon].IsOpen = false;
			Maze[NowLat - 1][NowLon].HasPathS = true;
			Dig(NowLat - 1, NowLon); // 次のノードに進む
		}
		OpenDirs &= ~0X1; // 探索済にする
		break;
	case 1: // 南方向
		if(NowLat < Size - 1 && Maze[NowLat + 1][NowLon].IsOpen) { // 未探索の時
			Maze[NowLat][NowLon].HasPathS = true;
			Maze[NowLat + 1][NowLon].IsOpen = false;
			Maze[NowLat + 1][NowLon].HasPathN = true;
			Dig(NowLat + 1, NowLon); // 次のノードに進む
		}
		OpenDirs &= ~0X2; // 探索済にする
		break;
	case 2: // 西方向
		if(NowLon && Maze[NowLat][NowLon - 1].IsOpen) { // 未探索の時
			Maze[NowLat][NowLon].HasPathW = true;
			Maze[NowLat][NowLon - 1].IsOpen = false;
			Maze[NowLat][NowLon - 1].HasPathE = true;
			Dig(NowLat, NowLon - 1); // 次のノードに進む
		}
		OpenDirs &= ~0X4; // 探索済にする
		break;
	case 3: // 東方向
		if(NowLon < Size - 1 && Maze[NowLat][NowLon + 1].IsOpen) { // 未探索の時
			Maze[NowLat][NowLon].HasPathE = true;
			Maze[NowLat][NowLon + 1].IsOpen = false;
			Maze[NowLat][NowLon + 1].HasPathW = true;
			Dig(NowLat, NowLon + 1); // 次のノードに進む
		}
		OpenDirs &= ~0X8; // 探索済にする
		break;
	}
	// 終了
	return;
}

/**
 * 迷路生成関数
 */
void MazeSqr::Generate() {
	// 迷路の生成
	Maze = std::vector<std::vector<NodeQ>>(Size, std::vector<NodeQ>(Size));
	Maze[0][Size - 1].IsOpen = false;
	Dig(0, Size - 1); // ゴール位置から生成を開始する
	// 終了
	return;
}

/**
 * 迷路変換関数
 */
void MazeSqr::Transform() {
	// 各ノード情報のブロックの情報への変換
	Path = std::vector<std::vector<std::pair<int, int>>>(Size, std::vector<std::pair<int, int>>(Size));
	static constexpr std::array<std::array<std::array<std::array<std::pair<int, int>, 2>, 2>, 2>, 2> Transformer = {
		{
			{
				{
					{ { { std::make_pair(-1, 0), std::make_pair(0, 3) }, { std::make_pair(0, 1), std::make_pair(1, 1) } } },
					{ { { std::make_pair(0, 0), std::make_pair(2, 3) }, { std::make_pair(2, 0), std::make_pair(3, 3) } } }
				}
			},
			{
				{
					{ { { std::make_pair(0, 2), std::make_pair(2, 2) }, { std::make_pair(2, 1), std::make_pair(3, 1) } } },
					{ { { std::make_pair(1, 0), std::make_pair(3, 2) }, { std::make_pair(3, 0), std::make_pair(4, 0) } } }
				}
			}
		}
	};
	for(int i = 0; i < Size; ++i) {
		for(
			int j = 0; j < Size;
			++j
		) Path[i][j] = Transformer[Maze[i][j].HasPathN][Maze[i][j].HasPathS][Maze[i][j].HasPathW][Maze[i][j].HasPathE];
	}
	// 終了
	return;
}

/**
 * 迷路取得関数
 * @return 迷路のデータ
 */
std::vector<std::vector<std::pair<int, int>>> MazeSqr::GetPath() const {
	// 迷路のデータの返戻
	return Path;
}

/**
 * コンストラクタ
 */
MazeSqr::MazeSqr() : Engine(Setting::GetStageSeed()), Dist(0, 3) {
	// 迷路の大きさの取得
	Size = Setting::GetStageSize();
	// 迷路の生成
	Generate();
	// ブロック情報の生成
	Transform();
	// 終了
	return;
}
