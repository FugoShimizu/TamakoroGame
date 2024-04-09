#pragma once
#include <utility>
#include <vector>
#include <DxLib.h>
#include "block_t_Corner.h"
#include "block_t_border.h"
#include "block_t_path_a.h"
#include "block_t_path_b.h"
#include "block_t_path_c.h"
#include "cell_t.h"

// 六角形ステージクラス
class StageHex {
public:
	StageHex(); // コンストラクタ
	void PositionFix(VECTOR &BallPos, VECTOR &BallVel); // ボール位置該当ブロック衝突判定関数
	void Draw(const MATRIX &RotationMat) const; // 描画関数
	void DrawNear(const MATRIX &RotationMat) const; // 周辺描画関数
	void DrawFar(const MATRIX &RotationMat) const; // 遠方描画関数
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
};