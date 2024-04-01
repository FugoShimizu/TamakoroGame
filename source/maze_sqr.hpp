#pragma once

#include "loading_screen.hpp"
#include <random>
#include <utility>
#include <vector>

// ノード（四角）構造体
struct NodeQ {
	bool IsOpen = true; // 未探索判定
	bool HasPathN = false; // 北方向通路
	bool HasPathS = false; // 南方向通路
	bool HasPathE = false; // 東方向通路
	bool HasPathW = false; // 西方向通路
};

// 四角形迷路クラス
class MazeSqr {
private:

	std::mt19937 Engine; // パラメータ定義済擬似乱数生成器
	std::uniform_int_distribution<int> Dist; // 一様分布 (0~3)
	int Size; // 迷路の大きさ
	std::vector<std::vector<NodeQ>> Maze; // 迷路構成ノード
	std::vector<std::vector<std::pair<int, int>>> Path; // 迷路構成ブロック情報
	LoadingScreen LoadScr; // ロード画面
	void Dig(const int NowLat, const int NowLon); // 再帰的穴掘法関数
	void Generate(); // 迷路生成関数
	void Transform(); // 迷路変換関数

public:

	std::vector<std::vector<std::pair<int, int>>> GetPath() const; // 迷路取得関数

	MazeSqr(); // コンストラクタ
};
