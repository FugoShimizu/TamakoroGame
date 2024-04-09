#include <algorithm>
#include <cmath>
#include "stage_sqr.h"
#include "Maze_sqr.h"
#include "setting.h"

// コンストラクタ
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

// ステージ構築関数
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
	for(int i = 1; i <= Size; ++i) for(int j = 1; j <= Size; ++j) switch(Paths[i - 1][j - 1].first) {
	case 0:
		Stage[i][j].SetCell(PathA.GetModel(), Paths[i - 1][j - 1].second, Size, i, j);
		break;
	case 1:
		Stage[i][j].SetCell(PathB.GetModel(), Paths[i - 1][j - 1].second, Size, i, j);
		break;
	case 2:
		Stage[i][j].SetCell(PathC.GetModel(), Paths[i - 1][j - 1].second, Size, i, j);
		break;
	case 3:
		Stage[i][j].SetCell(PathD.GetModel(), Paths[i - 1][j - 1].second, Size, i, j);
		break;
	case 4:
		Stage[i][j].SetCell(PathE.GetModel(), Paths[i - 1][j - 1].second, Size, i, j);
		break;
	default:
		Stage[i][j].SetCell(-1, Paths[i - 1][j - 1].second, Size, i, j);
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

// ボール位置該当ブロック衝突判定関数
void StageSqr::PositionFix(VECTOR &BallPos, VECTOR &BallVel) {
	// ボール位置のステージ内拘束
	BallPos.x = std::clamp(BallPos.x, static_cast<float>(Size * -2 + 1), static_cast<float>(Size * 2 - 1));
	BallPos.z = std::clamp(BallPos.z, static_cast<float>(Size * -2 + 1), static_cast<float>(Size * 2 - 1));
	// ボール位置の該当ブロックの判定
	BallLat = static_cast<int>(Size * 0.5F - BallPos.z * 0.25F);
	BallLon = static_cast<int>(Size * 0.5F + BallPos.x * 0.25F);
	std::pair<int, int> Cie = Paths[BallLat][BallLon];
	// セル内ボール位置の算出
	VECTOR BallLocLocal = VGet(fmodf((BallPos.x + Size * 2), 4.0F) - 2.0F, 0.0F, fmodf((BallPos.z + Size * 2), 4.0F) - 2.0F);
	// 該当ブロックに応じた衝突判定
	switch(Cie.first) {
	case 0:
		PathA.Collision(Cie.second, BallLocLocal, BallVel);
		break;
	case 1:
		PathB.Collision(Cie.second, BallLocLocal, BallVel);
		break;
	case 2:
		PathC.Collision(Cie.second, BallLocLocal, BallVel);
		break;
	case 3:
		PathD.Collision(Cie.second, BallLocLocal, BallVel);
		break;
	case 4:
		PathE.Collision(Cie.second, BallLocLocal, BallVel);
		break;
	}
	// 修正されたセル内ボール位置の反映
	BallPos = VAdd(VGet(static_cast<float>((Size - 1) * -2 + BallLon * 4), 0.0F, static_cast<float>((Size - 1) * 2 - BallLat * 4)), BallLocLocal);
	// 終了
	return;
}

// 描画関数
void StageSqr::Draw(const MATRIX &RotationMat) const {
	// ステージの描画
	for(const std::vector<CellQ> &x : Stage) for(const CellQ &y : x) y.Draw(RotationMat);
	// 終了
	return;
}

// 周辺描画関数
void StageSqr::DrawNear(const MATRIX &RotationMat) const {
	// ステージの描画
	for(int i = 0; i < Size + 2; ++i) for(int j = 0; j < Size + 2; ++j) if(abs(i - BallLat - 1) + abs(j - BallLon - 1) <= 3) Stage[i][j].Draw(RotationMat);
	// 終了
	return;
}

// 遠方描画関数
void StageSqr::DrawFar(const MATRIX &RotationMat) const {
	// ステージの描画
	for(int i = 0; i < Size + 2; ++i) for(int j = 0; j < Size + 2; ++j) if(abs(i - BallLat - 1) + abs(j - BallLon - 1) > 3) Stage[i][j].Draw(RotationMat);
	// 終了
	return;
}