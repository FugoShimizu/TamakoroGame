#pragma once

#include "loading_screen.hpp"
#include <random>
#include <utility>
#include <vector>

// ノード（三角）構造体
struct NodeT {
	bool IsOpen = true; // 未探索判定
	bool HasPath2 = false; // ２時方向通路
	bool HasPath6 = false; // ６時方向通路
	bool HasPath10 = false; // １０時方向通路
};

// 六角形迷路クラス
class MazeHex {
private:

	std::mt19937 Engine; // パラメータ定義済擬似乱数生成器
	std::uniform_int_distribution<int> Dist2; // 一様分布 (0~1)
	std::uniform_int_distribution<int> Dist3; // 一様分布 (0~2)
	int Size; // 迷路の大きさ
	std::vector<std::vector<std::pair<NodeT, NodeT>>> Maze; // 迷路構成ノード（first: 北ノード，second: 南ノード）
	std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>> Path; // 迷路構成ブロック情報（first: 種類，second: 向き）
	LoadingScreen LoadScr; // ロード画面
	void DigN(const int NowLat, const int NowLon); // 再帰的穴掘法関数（北ノード）
	void DigS(const int NowLat, const int NowLon); // 再帰的穴掘法関数（南ノード）
	void Generate(); // 迷路生成関数
	void Transform(); // 迷路変換関数

public:

	std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>> GetPath() const; // 迷路取得関数

	MazeHex(); // コンストラクタ
};
