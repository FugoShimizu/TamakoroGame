#pragma once

#include "block_t_border.hpp"
#include "block_t_corner.hpp"
#include "block_t_path_a.hpp"
#include "block_t_path_b.hpp"
#include "block_t_path_c.hpp"
#include "cell_t.hpp"
#include <DxLib.h>
#include <utility>
#include <vector>

// 六角形ステージクラス
class StageHex {
private:

	int Size; // ステージの大きさ
	int BallLat; // ボール位置の該当ブロック緯度
	int BallLon; // ボール位置の該当ブロック経度
	std::vector<std::vector<std::pair<CellT, CellT>>> Stage; // ステージ構成セル
	std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>> Paths; // 迷路構成ブロック情報
	BlockTCorner Corner; // 角部ブロック
	BlockTBorder Border; // 縁部ブロック
	BlockTPathA PathA; // Ａ型通路通路部ブロック
	BlockTPathB PathB; // Ｂ型通路通路部ブロック
	BlockTPathC PathC; // Ｃ型通路通路部ブロック
	void BuildStage(); // ステージ構築関数

public:

	void Draw(const MATRIX &RotationMat) const; // 描画関数
	void DrawNear(const MATRIX &RotationMat) const; // 周辺描画関数
	void DrawFar(const MATRIX &RotationMat) const; // 遠方描画関数
	void PositionFix(VECTOR &BallPos, VECTOR &BallVel); // ボール位置該当ブロック衝突判定関数

	StageHex &operator=(const StageHex &) = delete; // コピー代入演算子（禁止）
	StageHex(const StageHex &) = delete; // コピーコンストラクタ（禁止）

	StageHex(); // コンストラクタ
	~StageHex(); // デストラクタ
};
