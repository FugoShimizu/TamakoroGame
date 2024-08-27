#include <algorithm>
#include <cmath>
#include "model.h"
#include "input.h"
#include "Setting.h"

// コンストラクタ
Model::Model() {
	// メンバ変数の初期化
	Type = Setting::GetStageType();
	Size = Setting::GetStageSize();
	Goal = false;
	RotationAng = VGet(0.0F, 0.0F, 0.0F);
	CamRotAng = VGet(0.0F, 0.0F, 0.0F);
	RotationMat = MGetIdent(); // 単位行列
	switch(Type) {
	case StageForm::SQR: // 四角形ステージの時
		StartLoc = VGet(static_cast<float>(2 * (1 - Size)), 0.0F, static_cast<float>(2 * (1 - Size))); // スタート位置
		GoalLoc = VGet(static_cast<float>(2 * (Size - 1)), 0.0F, static_cast<float>(2 * (Size - 1))); // ゴール位置
		break;
	case StageForm::HEX: // 六角形ステージの時
		StartLoc = VGet(CellT::CentroidX * (1 - Size), 0.0F, 0.0F); // スタート位置
		GoalLoc = VGet(CellT::CentroidX * (Size - 1), 0.0F, 0.0F); // ゴール位置
		break;
	}
	StartDist = 0;
	GoalDist = VSize(VSub(GoalLoc, StartLoc));
	Bal.SetPos(StartLoc);
	ShowDebug = false;
	ShowMiniMap = true;
	MiniMapScale = 4;
	BallPosHist.push(StartLoc);
	// 画像の読込
	SMGraphHandle = LoadGraph("graphs\\start_marker.png"); // スタート位置マーカー
	GMGraphHandle = LoadGraph("graphs\\goal_marker.png"); // ゴール位置マーカー
	// 終了
	return;
}

// ボールワールド座標取得関数
VECTOR Model::GetBallLocation() const {
	// 終了
	return VTransformSR(Bal.Pos, RotationMat); // ボールのワールド座標を返す
}

// ステージ傾斜操作関数
float Model::Rotate(const float &CamAngH) {
	// ステージ傾斜の計算
	if(Input::GetClicking()) RotationAng = VAdd(RotationAng, VScale(VGet(static_cast<float>(-Input::GetCursorMoveY()), 0.0F, static_cast<float>(-Input::GetCursorMoveX())), SlopeRateDrag)); // 左クリック中はマウスドラッグで傾斜
	else if(Input::GetWSADPressing()) RotationAng = VAdd(RotationAng, VScale(VGet(static_cast<float>(Input::GetWSMove()), 0.0F, static_cast<float>(Input::GetADMove())), SlopeRateWSAD)); // WSADキー押下中はWSADキーで傾斜
	else RotationAng = VScale(RotationAng, SlopeRateRdct); // 無操作時は徐々に自立
	// 傾斜を最大傾斜角に制限
	const float Slope = VSize(RotationAng);
	if(Slope > MaxSlope) RotationAng = VScale(RotationAng, MaxSlope / Slope);
	// カメラの向きに応じた傾け方向の調整
	CamRotAng = VTransformSR(RotationAng, MGetRotY(CamAngH));
	// 描画用回転行列の生成
	RotationMat = MMult(MGetRotX(CamRotAng.x), MGetRotZ(CamRotAng.z)); // 回転行列
	// カメラ方向のステージ傾斜角の算出
	const VECTOR Direct = VGet(sinf(CamAngH), 0.0F, cosf(CamAngH)); // 方向ベクトル
	const VECTOR Normal = VTransformSR(VGet(0.0F, 1.0F, 0.0F), RotationMat); // 法線ベクトル
	// 終了
	return 0.5F * DX_PI_F - acosf(VDot(Direct, Normal) / VSize(Direct) / VSize(Normal)); // カメラ方向のステージ傾斜角を返す
}

// シミュレート関数
bool Model::Simulate() {
	// ボール位置のリセット
	if(Input::GetKeyPress(KEY_INPUT_U)) { // Uキーでスタートに戻る
		// スタートに戻す
		Bal.SetPos(StartLoc);
		// ボールの位置履歴の初期化
		if(!Goal) { // 未ゴール時
			std::queue<VECTOR> NewQueue;
			BallPosHist.swap(NewQueue);
			BallPosHist.push(StartLoc);
		}
	}
	// デバッグ用
//	if(Input::GetKeyPress(KEY_INPUT_G)) Bal.SetPos(GoalLoc); // Gキーでゴール
	// 傾きからボール位置を算出
	Bal.Position(CamRotAng.x, CamRotAng.z);
	// 衝突判定をボール位置に反映
	switch(Type) {
	case StageForm::SQR: // 四角形ステージの時
		StageSqr.PositionFix(Bal.Pos, Bal.Vel);
		break;
	case StageForm::HEX: // 六角形ステージの時
		StageHex.PositionFix(Bal.Pos, Bal.Vel);
		break;
	}
	// スタートとゴールからの距離を算出
	StartDist = VSize(VSub(Bal.Pos, StartLoc));
	GoalDist = VSize(VSub(Bal.Pos, GoalLoc));
	// ゴール前
	if(!Goal) { // 未ゴールの時
		// ボール位置履歴の追加
		if(BallPosHist.size() < INT_MAX && VSize(VSub(Bal.Pos, BallPosHist.back())) >= 1.0F) BallPosHist.push(Bal.Pos);
		// ゴール判定
		Goal = GoalDist < 1.0F;
	}
	// 終了
	return Goal; // ゴール判定を返す
}

// 表示切替関数
bool Model::SwitchDisplay() {
	// デバック情報の表示有無の切替
	if(Input::GetKeyPress(KEY_INPUT_F3)) ShowDebug ^= true; // F3キーで切替
	// ミニマップの表示有無の切替
	if(Input::GetKeyPress(KEY_INPUT_M)) ShowMiniMap ^= true; // Mキーで切替
	// ミニマップの拡縮
	const bool CursorOnMiniMap = ShowMiniMap && Input::CursorInBox(1020, 460, 1260, 700); // ミニマップ上のカーソル有無
	if(CursorOnMiniMap) { // カーソルがミニマップ上に有る時
		MiniMapScale -= GetMouseWheelRotVol(); // マウスホイールでミニマップを拡縮
		MiniMapScale = std::clamp(MiniMapScale, 2, 8); // 拡縮を範囲内に制限
	}
	// ミニマップ縮尺のリセット
	if(Input::GetKeyPress(KEY_INPUT_R)) MiniMapScale = 4; // Rキーでリセット
	// 終了
	return CursorOnMiniMap; // ミニマップ上のカーソル有無を返す
}

// モデル描画関数
void Model::DrawModel() const {
	// ステージの描画
	switch(Type) {
	case StageForm::SQR: // 四角形ステージの時
		StageSqr.Draw(RotationMat);
		break;
	case StageForm::HEX: // 六角形ステージの時
		StageHex.Draw(RotationMat);
		break;
	}
	// ボールの描画
	Bal.Draw(RotationMat);
	// 終了
	return;
}

// 周辺モデル描画関数
void Model::DrawNearModel() const {
	// ステージの描画
	switch(Type) {
	case StageForm::SQR: // 四角形ステージの時
		StageSqr.DrawNear(RotationMat);
		break;
	case StageForm::HEX: // 六角形ステージの時
		StageHex.DrawNear(RotationMat);
		break;
	}
	// ボールの描画
	Bal.Draw(RotationMat);
	// 終了
	return;
}

// 遠方モデル描画関数
void Model::DrawFarModel() const {
	// ステージの描画
	switch(Type) {
	case StageForm::SQR: // 四角形ステージの時
		StageSqr.DrawFar(RotationMat);
		break;
	case StageForm::HEX: // 六角形ステージの時
		StageHex.DrawFar(RotationMat);
		break;
	}
	// 終了
	return;
}

// 画像描画関数
void Model::DrawInfo(const float &CamAngH) const {
	// スタート位置マーカーとゴール位置マーカーの描画
	SetMarker();
	// デバッグ情報の描画
	if(ShowDebug) DrawFormatString(0, 0, Goal ? GetColor(0, 0, 0) : GetColor(255, 255, 255), "Type: %d, Size: %d, Seed: %d\nStageTilt: (X= %f, Z= %f)\nBallPosition: (X= %f, Z= %f)\nBallVelocity: (X= %f, Z= %f)", static_cast<int>(Setting::GetStageType()), Setting::GetStageSize(), Setting::GetStageSeed(), RotationAng.x, RotationAng.z, Bal.Pos.x, Bal.Pos.z, Bal.Vel.x, Bal.Vel.z);
	// 操作方法説明の描画
	else if(!Goal) DrawString(0, 0, "傾ける：マウス左ドラッグ／WSADキー　視点移動：矢印キー　拡大・縮小：マウスホイール　視点リセット：Rキー　視点変更：F5キー\nボール位置リセット：Uキー　ミニマップ表示切替：Mキー　デバッグ表示切替：F3キー　タイトルに戻る：Tキー", GetColor(255, 255, 255));
	// ミニマップの描画
	if(ShowMiniMap) DrawMiniMap(CamAngH);
	// 終了
	return;
}

// マーカー設定関数
void Model::SetMarker() const {
	// スタート位置とゴール位置を表示
	const VECTOR s_ScrCoord = ConvWorldPosToScreenPos(VTransformSR(StartLoc, RotationMat)); // スタート位置のスクリーン座標
	const VECTOR g_ScrCoord = ConvWorldPosToScreenPos(VTransformSR(GoalLoc, RotationMat)); // ゴール位置のスクリーン座標
	if(s_ScrCoord.z > g_ScrCoord.z) { // ゴール側が手前にある時
		DrawMarker(s_ScrCoord, SMGraphHandle, GetColor(255, 0, 0), static_cast<int>(StartDist));
		DrawMarker(g_ScrCoord, GMGraphHandle, GetColor(0, 0, 255), static_cast<int>(GoalDist));
	} else { // スタート側が手前にある時
		DrawMarker(g_ScrCoord, GMGraphHandle, GetColor(0, 0, 255), static_cast<int>(GoalDist));
		DrawMarker(s_ScrCoord, SMGraphHandle, GetColor(255, 0, 0), static_cast<int>(StartDist));
	}
	// 終了
	return;
}

// マーカー描画関数
void Model::DrawMarker(const VECTOR &ScrCoord, const int &MarkerGraphHandle, const unsigned int &FontColor, const int &Distance) const {
	// マーカーと距離の描画
	if(ScrCoord.z < 1.0F && ScrCoord.z > 0.0F) {
		DrawGraph(static_cast<int>(ScrCoord.x) - 40, static_cast<int>(ScrCoord.y) - 90, MarkerGraphHandle, TRUE);
		if(!Goal) DrawFormatString(static_cast<int>(ScrCoord.x) - 30, static_cast<int>(ScrCoord.y) - 106, FontColor, "%3d cm", Distance);
	}
	// 終了
	return;
}

// ミニマップ描画関数
void Model::DrawMiniMap(const float &CamAngH) const {
	// ミニマップの表示
	SetDrawArea(1020, 460, 1260, 700); // ミニマップの描画領域
	SetupCamera_Ortho(static_cast<float>(8 * MiniMapScale)); // 正射影カメラをセットアップ
	SetCameraScreenCenter(1140, 580); // ミニマップの中心位置
	SetCameraPositionAndTargetAndUpVec(VTransformSR(VAdd(Bal.Pos, VGet(0.0F, 2.0F, 0.0F)), RotationMat), VTransformSR(Bal.Pos, RotationMat), VGet(sinf(CamAngH), 0.0F, cosf(CamAngH))); // カメラの位置をボールの上に設定
	DrawBox(1020, 460, 1260, 700, GetColor(0, 0, 0), TRUE); // ミニマップの背景
	DrawModel(); // ミニマップを描画
	SetMarker(); // スタート位置マーカーとゴール位置マーカーを描画
	SetDrawArea(0, 0, 1280, 720); // 描画領域を元に戻す
	// 終了
	return;
}

// 軌跡画面描画関数
void Model::DrawRoute(int EndNum) const {
	// マップの表示
	SetupCamera_Ortho(6.0F * Size); // 正射影カメラをセットアップ
	SetCameraScreenCenter(640, 360);
	SetCameraPositionAndTargetAndUpVec(VTransformSR(VGet(0.0F, 2.0F, 0.0F), RotationMat), VTransformSR(VGet(0.0F, 0.0F, 0.0F), RotationMat), VGet(0.0F, 0.0F, 1.0F)); // カメラの位置を中央に設定
	DrawModel(); // マップを描画
	SetMarker(); // スタート位置マーカーとゴール位置マーカーを描画
	// 移動距離の表示
	DrawFormatString(588, 620, GetColor(0, 0, 0), "道程：%3d cm", BallPosHist.size());
	DrawString(564, 640, "左クリックで閉じる", GetColor(0, 0, 0));
	// 軌跡の表示
	std::queue<VECTOR> BallPosHist_tmp = BallPosHist; // 履歴を複製
	BallPosHist_tmp.push(GoalLoc); // 最後をゴール位置にする
	VECTOR LastPos = VScale(BallPosHist_tmp.front(), 120.0F / Size);
	BallPosHist_tmp.pop();
	while(EndNum && !BallPosHist_tmp.empty()) {
		const VECTOR NextPos = VScale(BallPosHist_tmp.front(), 120.0F / Size);
		BallPosHist_tmp.pop();
		DrawLineAA(640.0F + LastPos.x, 360.0F - LastPos.z, 640.0F + NextPos.x, 360.0F - NextPos.z, GetColor(255, 0, 0)); // 軌跡の線
		LastPos = NextPos;
		--EndNum;
	}
	DrawCircle(640 + static_cast<int>(LastPos.x), 360 - static_cast<int>(LastPos.z), 120 / Size, GetColor(255, 0, 0), TRUE); // 先頭部
	// 終了
	return;
}