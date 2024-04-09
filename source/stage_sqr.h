#pragma once
#include <utility>
#include <vector>
#include <DxLib.h>
#include "block_q_Corner.h"
#include "block_q_border.h"
#include "block_q_path_a.h"
#include "block_q_path_b.h"
#include "block_q_path_c.h"
#include "block_q_path_d.h"
#include "block_q_path_e.h"
#include "cell_q.h"

// 四角形ステージクラス
class StageSqr {
public:
	StageSqr(); // コンストラクタ
	void PositionFix(VECTOR &BallPos, VECTOR &BallVel); // ボール位置該当ブロック衝突判定関数
	void Draw(const MATRIX &RotationMat) const; // 描画関数
	void DrawNear(const MATRIX &RotationMat) const; // 周辺描画関数
	void DrawFar(const MATRIX &RotationMat) const; // 遠方描画関数
private:
	int Size; // ステージの大きさ
	int BallLat; // ボール位置の該当ブロック緯度
	int BallLon; // ボール位置の該当ブロック経度
	std::vector<std::vector<CellQ>> Stage; // ステージ構成セル
	std::vector<std::vector<std::pair<int, int>>> Paths; // 迷路構成ブロック情報（first：種類，second：向き）
	BlockQCorner Corner; // 角部ブロック
	BlockQBorder Border; // 縁部ブロック
	BlockQPathA PathA; // Ａ型通路通路部ブロック
	BlockQPathB PathB; // Ｂ型通路通路部ブロック
	BlockQPathC PathC; // Ｃ型通路通路部ブロック
	BlockQPathD PathD; // Ｄ型通路通路部ブロック
	BlockQPathE PathE; // Ｅ型通路通路部ブロック
	void BuildStage(); // ステージ構築関数
};