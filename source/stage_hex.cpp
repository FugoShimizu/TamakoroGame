#include "stage_hex.hpp"
#include "maze_hex.hpp"
#include "setting.hpp"
#include <algorithm>
#include <array>
#include <cmath>

/**
 * ステージ構築関数
 */
void StageHex::BuildStage() {
	// 迷路の生成
	const MazeHex Maze;
	Paths = Maze.GetPath();
	// ステージの角のモデルの割当
	Stage[Size + 1][(Size + 1 >> 1) + 1].first.SetCellN(Corner.GetModel(), 2, Size, Size + 1, (Size + 1 >> 1) + 1); // 未
	Stage[0][Size >> 1].second.SetCellS(Corner.GetModel(), 2, Size, 0, Size >> 1); // 丑
	Stage[0][Size + 1].first.SetCellN(Corner.GetModel(), 1, Size, 0, Size + 1); // 卯
	Stage[Size + 1][0].second.SetCellS(Corner.GetModel(), 1, Size, Size + 1, 0); // 酉
	Stage[(Size >> 1) + 1][0].first.SetCellN(Corner.GetModel(), 0, Size, (Size >> 1) + 1, 0); // 亥
	Stage[Size + 1 >> 1][Size + 1].second.SetCellS(Corner.GetModel(), 0, Size, Size + 1 >> 1, Size + 1); // 巳
	// ステージの縁のモデルの割当
	for(int j = 1; j <= Size + 1 >> 1; ++j) Stage[Size + 1][j].first.SetCellN(Border.GetModel(), 2, Size, Size + 1, j); // 申
	for(int j = (Size >> 1) + 1; j <= Size; ++j) Stage[0][j].second.SetCellS(Border.GetModel(), 2, Size, 0, j); // 寅
	for(int i = 1; i <= Size + 1 >> 1; ++i) Stage[i][Size + 1].first.SetCellN(Border.GetModel(), 1, Size, i, Size + 1); // 辰
	for(int i = (Size >> 1) + 1; i <= Size; ++i) Stage[i][0].second.SetCellS(Border.GetModel(), 1, Size, i, 0); // 戌
	for(int i = Size >> 1, j = 1; i; --i, ++j) Stage[i][j].first.SetCellN(Border.GetModel(), 0, Size, i, j); // 子
	for(int i = Size, j = (Size + 1 >> 1) + 1; j <= Size; --i, ++j) Stage[i][j].second.SetCellS(Border.GetModel(), 0, Size, i, j); // 午
	// ステージの迷路部分のモデルの割当
	const int UpperLimit = 3 * (Size + 1) >> 1; // 迷路部分の緯度経度和の上限
	for(int i = 1; i <= Size; ++i) for(int j = 1; j <= Size; ++j) {
		const std::pair<std::pair<int, int>, std::pair<int, int>> Path = Paths[i - 1][j - 1];
		if(i + j > (Size >> 1) + 1 && i + j <= UpperLimit) switch(Path.first.first) {
		case 0:
			Stage[i][j].first.SetCellN(PathA.GetModel(), Path.first.second, Size, i, j);
			break;
		case 1:
			Stage[i][j].first.SetCellN(PathB.GetModel(), Path.first.second, Size, i, j);
			break;
		case 2:
			Stage[i][j].first.SetCellN(PathC.GetModel(), Path.first.second, Size, i, j);
			break;
		default:
			Stage[i][j].first.SetCellN(-1, Path.first.second, Size, i, j);
			break;
		}
		if(i + j > Size >> 1 && i + j < UpperLimit) switch(Path.second.first) {
		case 0:
			Stage[i][j].second.SetCellS(PathA.GetModel(), Path.second.second, Size, i, j);
			break;
		case 1:
			Stage[i][j].second.SetCellS(PathB.GetModel(), Path.second.second, Size, i, j);
			break;
		case 2:
			Stage[i][j].second.SetCellS(PathC.GetModel(), Path.second.second, Size, i, j);
			break;
		default:
			Stage[i][j].second.SetCellS(-1, Path.second.second, Size, i, j);
			break;
		}
	}
	// ステージのモデルコピー元の削除
	Corner.DeleteModel();
	Border.DeleteModel();
	PathA.DeleteModel();
	PathB.DeleteModel();
	PathC.DeleteModel();
	// 終了
	return;
}

/**
 * 描画関数
 * @param RotationMat ステージ傾斜の回転行列
 */
void StageHex::Draw(const MATRIX &RotationMat) const {
	// ステージの描画
	for(const std::vector<std::pair<CellT, CellT>> &Row : Stage) for(const std::pair<CellT, CellT> &Col : Row) {
		Col.first.Draw(RotationMat);
		Col.second.Draw(RotationMat);
	}
	// 終了
	return;
}

/**
 * 周辺描画関数
 * @param RotationMat ステージ傾斜の回転行列
 */
void StageHex::DrawNear(const MATRIX &RotationMat) const {
	// ステージの描画
	for(
		int i = 0; i < Size + 2;
		++i
	) for(int j = 0; j < Size + 2; ++j) if(std::abs(i - BallLat - 1) + std::abs(j - BallLon - 1) < 4) {
		Stage[i][j].first.Draw(RotationMat);
		Stage[i][j].second.Draw(RotationMat);
	}
	// 終了
	return;
}

/**
 * 遠方描画関数
 * @param RotationMat ステージ傾斜の回転行列
 */
void StageHex::DrawFar(const MATRIX &RotationMat) const {
	// ステージの描画
	for(
		int i = 0; i < Size + 2;
		++i
	) for(int j = 0; j < Size + 2; ++j) if(std::abs(i - BallLat - 1) + std::abs(j - BallLon - 1) > 3) {
		Stage[i][j].first.Draw(RotationMat);
		Stage[i][j].second.Draw(RotationMat);
	}
	// 終了
	return;
}

/**
 * ボール位置該当ブロック衝突判定関数
 * @param BallPos ボール位置
 * @param BallVel ボール速度
 */
void StageHex::PositionFix(VECTOR &BallPos, VECTOR &BallVel) {
	// ボール位置のステージ内拘束
	const float HalfWidth = CellT::CentroidX * Size, SlantX = std::abs(BallPos.z) / CellT::Root3;
	BallPos.x = std::clamp(BallPos.x, SlantX - HalfWidth + 1.0F, HalfWidth - SlantX - 1.0F);
	const int HalfDepth = Size + 1 >> 1 << 2; // Ｚ方向の半幅
	BallPos.z = std::clamp(BallPos.z, static_cast<float>(1 - HalfDepth), static_cast<float>(HalfDepth - 1));
	// ボール位置の該当ブロックの判定
	BallLat = static_cast<int>(std::fma(BallPos.x, CellT::Root3, BallPos.z - (Size << 2))) / -8;
	BallLon = static_cast<int>(std::fma(BallPos.x, CellT::Root3, (Size << 2) - BallPos.z)) / 8;
	const bool IsNorthCell = ((static_cast<int>(BallPos.z + (Size << 2)) >> 2) - BallLat - BallLon) % 2;
	const std::pair<int, int> CellInfo = IsNorthCell ? Paths[BallLat][BallLon].first : Paths[BallLat][BallLon].second;
	std::array<std::pair<int, int>, 3> AdjacentCell; // 隣接セル
	// セル内ボール位置の算出
	VECTOR BallLocLocal;
	// 南北セルに応じた算出
	if(IsNorthCell) { // 北セル
		if(BallLat) AdjacentCell[(3 - CellInfo.second) % 3] = Paths[BallLat - 1][BallLon].second; // ２時方向
		if(BallLat + BallLon <= (Size - 1 << 1) - (Size >> 1)) AdjacentCell[(4 - CellInfo.second) % 3] = Paths[BallLat][BallLon].second; // ６時方向
		if(BallLon) AdjacentCell[(5 - CellInfo.second) % 3] = Paths[BallLat][BallLon - 1].second; // １０時方向
		BallLocLocal = VGet(
			std::fmod(BallPos.x + CellT::CentroidX * (Size + (Size + BallLon - BallLat - 1) % 2), 2.0F * CellT::CentroidX)
			- CellT::CentroidX,
			0.0F,
			std::fmod(BallPos.z + (Size << 2), 4.0F) - CellT::CentroidZ
		);
	} else { // 南セル
		if(BallLat < Size - 1) AdjacentCell[(3 - CellInfo.second) % 3] = Paths[BallLat + 1][BallLon].first; // ８時方向
		if(BallLat + BallLon >= Size >> 1) AdjacentCell[(4 - CellInfo.second) % 3] = Paths[BallLat][BallLon].first; // １２時方向
		if(BallLon < Size - 1) AdjacentCell[(5 - CellInfo.second) % 3] = Paths[BallLat][BallLon + 1].first; // ４時方向
		BallLocLocal = VGet(
			CellT::CentroidX
			- std::fmod(BallPos.x + CellT::CentroidX * (Size + (Size + BallLon - BallLat - 1) % 2), 2.0F * CellT::CentroidX),
			0.0F,
			2.0F * CellT::CentroidZ - std::fmod(BallPos.z + (Size << 2), 4.0F)
		);
	}
	// 隣接壁の判定
	std::array<std::pair<bool, bool>, 3> AdjacentWall; // 中心から見て，first: 左側の壁，second: 右側の壁 // true：長い壁，false：短い壁
	for(int i = 0; i < 3; ++i) {
		AdjacentWall[i] = std::make_pair(
			!AdjacentCell[(i + 2) % 3].first || AdjacentCell[(i + 2) % 3] == std::make_pair(1, (CellInfo.second + i) % 3),
			!AdjacentCell[i].first || AdjacentCell[i] == std::make_pair(1, (CellInfo.second + i) % 3)
		); // １２時方向，４時方向，８時方向
	}
	// 該当ブロックに応じた衝突判定
	switch(CellInfo.first) {
	case 0:
		PathA.Collision(CellInfo.second, AdjacentWall, BallLocLocal, BallVel);
		break;
	case 1:
		PathB.Collision(CellInfo.second, AdjacentWall, BallLocLocal, BallVel);
		break;
	case 2:
		PathC.Collision(CellInfo.second, AdjacentWall, BallLocLocal, BallVel);
		break;
	}
	// 修正されたセル内ボール位置の反映
	if(IsNorthCell) {
		BallPos = VAdd(
			VGet(CellT::CentroidX * (BallLon - BallLat), 0.0F, (Size - BallLat - BallLon - 1 << 2) + CellT::CentroidZ),
			BallLocLocal
		);
	} else {
		BallPos = VAdd(
			VGet(CellT::CentroidX * (BallLon - BallLat), 0.0F, (Size - BallLat - BallLon - 1 << 2) - CellT::CentroidZ),
			VScale(BallLocLocal, -1.0F)
		);
	}
	// 終了
	return;
}

/**
 * コンストラクタ
 */
StageHex::StageHex() {
	// メンバ変数の初期化
	using CellRow = std::vector<std::pair<CellT, CellT>>;
	Size = Setting::GetStageSize();
	BallLat = Size - 1;
	BallLon = 0;
	Stage = std::vector<CellRow>(Size + 2, CellRow(Size + 2));
	// ステージの生成
	if(Setting::GetStageType() == StageForm::HEX) BuildStage();
	// 終了
	return;
}

/**
 * デストラクタ
 */
StageHex::~StageHex() {
	// 全セルのモデルの解放
	for(std::vector<std::pair<CellT, CellT>> &Row : Stage) for(std::pair<CellT, CellT> &Col : Row) {
		Col.first.DeleteModel();
		Col.second.DeleteModel();
	}
	// 終了
	return;
}
