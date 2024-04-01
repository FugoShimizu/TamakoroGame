#pragma once

#include "cell_base.hpp"
#include <numbers>

// セル（三角）クラス
class CellT : public CellBase {
public:

	static constexpr float Root3 = std::numbers::sqrt3_v<float>; // √3
	static constexpr float CentroidZ = 4.0F / 3.0F; // 中心の左下頂点原点のＺ座標
	static constexpr float CentroidX = CentroidZ * Root3; // 中心の左下頂点原点のＸ座標
	void SetCellN(const int SourceModelHandle, const int CellDir, const int StageSize, const int Latitude, const int Longitude); // セル設定関数（北セル）
	void SetCellS(const int SourceModelHandle, const int CellDir, const int StageSize, const int Latitude, const int Longitude); // セル設定関数（南セル）
};
