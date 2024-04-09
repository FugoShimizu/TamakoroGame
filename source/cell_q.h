#pragma once
#include "cell_base.h"

// セル（四角）クラス
class CellQ : public CellBase {
public:
	void SetCell(const int &SourceModelHandle, const int &CellDir, const int &StageSize, const int &Latitude, const int &Longitude); // セル設定関数
};