#pragma once
#include <random>
#include <utility>
#include <vector>
#include "loading_screen.h"

// ノード（三角）構造体
struct NodeT {
	bool Open; // 未探索判定
	bool Path2; // 2時方向通路
	bool Path6; // 6時方向通路
	bool Path10; // 10時方向通路
	NodeT() { // コンストラクタ
		Open = true;
		Path2 = false;
		Path6 = false;
		Path10 = false;
		return;
	}
};

// 六角形迷路クラス
class MazeHex {
public:
	MazeHex(); // コンストラクタ
	std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>> GetPath() const; // 迷路取得関数
private:
	std::mt19937 Engine; // パラメータ定義済擬似乱数生成器
	std::uniform_int_distribution<int> Dist2; // 一様分布（0～1）
	std::uniform_int_distribution<int> Dist3; // 一様分布（0～2）
	int Size; // 迷路の大きさ
	std::vector<std::vector<std::pair<NodeT, NodeT>>> Maze; // 迷路構成ノード（first：北ノード，second：南ノード）
	std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>> Path; // 迷路構成ブロック情報（first：種類，second：向き）
	LoadingScreen LoadScr; // ロード画面
	void Generate(); // 迷路生成関数
	void Transform(); // 迷路変換関数
	void DigN(const int &NowLat, const int &NowLon); // 再帰的穴掘法関数（北ノード）
	void DigS(const int &NowLat, const int &NowLon); // 再帰的穴掘法関数（南ノード）
};