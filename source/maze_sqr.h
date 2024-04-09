#pragma once
#include <random>
#include <utility>
#include <vector>
#include "loading_screen.h"

// ノード（四角）構造体
struct NodeQ {
	bool Open; // 未探索判定
	bool PathN; // 北方向通路
	bool PathS; // 南方向通路
	bool PathE; // 東方向通路
	bool PathW; // 西方向通路
	NodeQ() { // コンストラクタ
		Open = true;
		PathN = false;
		PathS = false;
		PathW = false;
		PathE = false;
		return;
	}
};

// 四角形迷路クラス
class MazeSqr {
public:
	MazeSqr(); // コンストラクタ
	std::vector<std::vector<std::pair<int, int>>> GetPath() const; // 迷路取得関数
private:
	std::mt19937 Engine; // パラメータ定義済擬似乱数生成器
	std::uniform_int_distribution<int> Dist;// 一様分布（0～3）
	int Size; // 迷路の大きさ
	std::vector<std::vector<NodeQ>> Maze; // 迷路構成ノード
	std::vector<std::vector<std::pair<int, int>>> Path; // 迷路構成ブロック情報
	LoadingScreen LoadScr; // ロード画面
	void Generate(); // 迷路生成関数
	void Transform(); // 迷路変換関数
	void Dig(const int &now_lat, const int &now_lon); // 再帰的穴掘法関数
};