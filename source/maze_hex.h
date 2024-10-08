#pragma once
#include <random>
#include <utility>
#include <vector>
#include "loading_screen.h"

// m[hiOpj\’Μ
struct NodeT {
	bool Open; // ’Tυ»θ
	bool Path2; // 2ϋόΚH
	bool Path6; // 6ϋόΚH
	bool Path10; // 10ϋόΚH
	NodeT() { // RXgN^
		Open = true;
		Path2 = false;
		Path6 = false;
		Path10 = false;
		return;
	}
};

// Zp`ΐHNX
class MazeHex {
public:
	MazeHex(); // RXgN^
	std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>> GetPath() const; // ΐHζΎΦ
private:
	std::mt19937 Engine; // p[^θ`Ο[Ά¬ν
	std::uniform_int_distribution<int> Dist2; // κlͺzi0`1j
	std::uniform_int_distribution<int> Dist3; // κlͺzi0`2j
	int Size; // ΐHΜε«³
	std::vector<std::vector<std::pair<NodeT, NodeT>>> Maze; // ΐH\¬m[hifirstFkm[hCsecondFμm[hj
	std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>> Path; // ΐH\¬ubNξρifirstFνήCsecondFό«j
	LoadingScreen LoadScr; // [hζΚ
	void Generate(); // ΐHΆ¬Φ
	void Transform(); // ΐHΟ·Φ
	void DigN(const int &NowLat, const int &NowLon); // ΔAI@@Φikm[hj
	void DigS(const int &NowLat, const int &NowLon); // ΔAI@@Φiμm[hj
};