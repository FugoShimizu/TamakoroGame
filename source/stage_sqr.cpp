#include "stage_sqr.hpp"
#include "maze_sqr.hpp"
#include "setting.hpp"
#include <algorithm>
#include <cmath>

/**
 * ステージ構築関数
 */
void StageSqr::BuildStage() {
	// 迷路の生成
	const MazeSqr Maze;
	Paths = Maze.GetPath();
	// ステージの角のモデルの割当
	Stage[0][0].SetCell(Corner.GetModel(), 0, Size, 0, 0); // 北西
	Stage[0][Size + 1].SetCell(Corner.GetModel(), 1, Size, 0, Size + 1); // 北東
	Stage[Size + 1][Size + 1].SetCell(Corner.GetModel(), 2, Size, Size + 1, Size + 1); // 南東
	Stage[Size + 1][0].SetCell(Corner.GetModel(), 3, Size, Size + 1, 0); // 南西
	// ステージの縁のモデルの割当
	for(int j = 1; j <= Size; ++j) {
		Stage[0][j].SetCell(Border.GetModel(), 0, Size, 0, j); // 北
		Stage[Size + 1][j].SetCell(Border.GetModel(), 2, Size, Size + 1, j); // 南
	}
	for(int i = 1; i <= Size; ++i) {
		Stage[i][0].SetCell(Border.GetModel(), 3, Size, i, 0); // 西
		Stage[i][Size + 1].SetCell(Border.GetModel(), 1, Size, i, Size + 1); // 東
	}
	// ステージの迷路部分のモデルの割当
	for(
		int i = 1; i <= Size;
		++i
	) for(int j = 1; j <= Size; ++j) switch(const std::pair<int, int> Path = Paths[i - 1][j - 1]; Path.first) {
	case 0:
		Stage[i][j].SetCell(PathA.GetModel(), Path.second, Size, i, j);
		break;
	case 1:
		Stage[i][j].SetCell(PathB.GetModel(), Path.second, Size, i, j);
		break;
	case 2:
		Stage[i][j].SetCell(PathC.GetModel(), Path.second, Size, i, j);
		break;
	case 3:
		Stage[i][j].SetCell(PathD.GetModel(), Path.second, Size, i, j);
		break;
	case 4:
		Stage[i][j].SetCell(PathE.GetModel(), Path.second, Size, i, j);
		break;
	default:
		Stage[i][j].SetCell(-1, Path.second, Size, i, j);
		break;
	}
	// ステージのモデルコピー元の削除
	Corner.DeleteModel();
	Border.DeleteModel();
	PathA.DeleteModel();
	PathB.DeleteModel();
	PathC.DeleteModel();
	PathD.DeleteModel();
	PathE.DeleteModel();
	// 終了
	return;
}

/**
 * 描画関数
 * @param RotationMat ステージ傾斜の回転行列
 */
void StageSqr::Draw(const MATRIX &RotationMat) const {
	// ステージの描画
	for(const std::vector<CellQ> &Row : Stage) for(const CellQ &Col : Row) Col.Draw(RotationMat);
	// 終了
	return;
}

/**
 * 周辺描画関数
 * @param RotationMat ステージ傾斜の回転行列
 */
void StageSqr::DrawNear(const MATRIX &RotationMat) const {
	// ステージの描画
	for(
		int i = 0; i < Size + 2;
		++i
	) for(int j = 0; j < Size + 2; ++j) if(std::abs(i - BallLat - 1) + std::abs(j - BallLon - 1) < 4) Stage[i][j].Draw(RotationMat);
	// 終了
	return;
}

/**
 * 遠方描画関数
 * @param RotationMat ステージ傾斜の回転行列
 */
void StageSqr::DrawFar(const MATRIX &RotationMat) const {
	// ステージの描画
	for(
		int i = 0; i < Size + 2;
		++i
	) for(int j = 0; j < Size + 2; ++j) if(std::abs(i - BallLat - 1) + std::abs(j - BallLon - 1) > 3) Stage[i][j].Draw(RotationMat);
	// 終了
	return;
}

/**
 * ボール位置該当ブロック衝突判定関数
 * @param BallPos ボール位置
 * @param BallVel ボール速度
 */
void StageSqr::PositionFix(VECTOR &BallPos, VECTOR &BallVel) {
	// ボール位置のステージ内拘束
	const float Lower = static_cast<float>(-(Size << 1) + 1), Upper = static_cast<float>((Size << 1) - 1);
	BallPos.x = std::clamp(BallPos.x, Lower, Upper);
	BallPos.z = std::clamp(BallPos.z, Lower, Upper);
	// ボール位置の該当ブロックの判定
	BallLat = static_cast<int>(0.5F * Size - 0.25F * BallPos.z);
	BallLon = static_cast<int>(0.5F * Size + 0.25F * BallPos.x);
	// セル内ボール位置の算出
	VECTOR BallLocLocal
	= VGet(std::fmod(BallPos.x + (Size << 1), 4.0F) - 2.0F, 0.0F, std::fmod(BallPos.z + (Size << 1), 4.0F) - 2.0F);
	// 該当ブロックに応じた衝突判定
	switch(const std::pair<int, int> CellInfo = Paths[BallLat][BallLon]; CellInfo.first) {
	case 0:
		PathA.Collision(CellInfo.second, BallLocLocal, BallVel);
		break;
	case 1:
		PathB.Collision(CellInfo.second, BallLocLocal, BallVel);
		break;
	case 2:
		PathC.Collision(CellInfo.second, BallLocLocal, BallVel);
		break;
	case 3:
		PathD.Collision(CellInfo.second, BallLocLocal, BallVel);
		break;
	case 4:
		PathE.Collision(CellInfo.second, BallLocLocal, BallVel);
		break;
	}
	// 修正されたセル内ボール位置の反映
	BallPos = VAdd(
		VGet(static_cast<float>((1 - Size << 1) + (BallLon << 2)), 0.0F, static_cast<float>((Size - 1 << 1) - (BallLat << 2))),
		BallLocLocal
	);
	// 終了
	return;
}

/**
 * コンストラクタ
 */
StageSqr::StageSqr() {
	// メンバ変数の初期化
	Size = Setting::GetStageSize();
	BallLat = Size - 1;
	BallLon = 0;
	Stage = std::vector<std::vector<CellQ>>(Size + 2, std::vector<CellQ>(Size + 2));
	// ステージの生成
	if(Setting::GetStageType() == StageForm::SQR) BuildStage();
	// 終了
	return;
}

/**
 * デストラクタ
 */
StageSqr::~StageSqr() {
	// 全セルのモデルの解放
	for(std::vector<CellQ> &Row : Stage) for(CellQ &Col : Row) Col.DeleteModel();
	// 終了
	return;
}
