#include "model.hpp"
#include "input.hpp"
#include "setting.hpp"
#include <algorithm>
#include <cmath>

/**
 * マーカー描画関数
 * @param ScrCoord マーカーのスクリーン座標
 * @param MarkerGraphHandle マーカーグラフハンドル
 * @param FontColor 距離表示の文字色
 * @param Distance ボールとの距離（≧0）
 */
void Model::DrawMarker(
	const VECTOR &ScrCoord,
	const int MarkerGraphHandle,
	const unsigned int FontColor,
	const int Distance
) const {
	// マーカーと距離の描画
	if(ScrCoord.z < 1.0F && ScrCoord.z > 0.0F) {
		DrawGraph(static_cast<int>(ScrCoord.x) - 40, static_cast<int>(ScrCoord.y) - 90, MarkerGraphHandle, TRUE);
		if(!IsGoaled) {
			DrawFormatString(static_cast<int>(ScrCoord.x) - 30, static_cast<int>(ScrCoord.y) - 106, FontColor, "%3d cm", Distance);
		}
	}
	// 終了
	return;
}

/**
 * マーカー設定関数
 */
void Model::SetMarker() const {
	// スタート位置とゴール位置の表示
	const VECTOR StartScrCoord = ConvWorldPosToScreenPos(VTransformSR(StartLoc, RotationMat)); // スタート位置のスクリーン座標
	const VECTOR GoalScrCoord = ConvWorldPosToScreenPos(VTransformSR(GoalLoc, RotationMat)); // ゴール位置のスクリーン座標
	if(StartScrCoord.z > GoalScrCoord.z) { // ゴール側が手前に在る時
		DrawMarker(StartScrCoord, StartMarkerGraphHandle, GetColor(255, 0, 0), static_cast<int>(StartDist));
		DrawMarker(GoalScrCoord, GoalMarkerGraphHandle, GetColor(0, 0, 255), static_cast<int>(GoalDist));
	} else { // スタート側が手前に在る時
		DrawMarker(GoalScrCoord, GoalMarkerGraphHandle, GetColor(0, 0, 255), static_cast<int>(GoalDist));
		DrawMarker(StartScrCoord, StartMarkerGraphHandle, GetColor(255, 0, 0), static_cast<int>(StartDist));
	}
	// 終了
	return;
}

/**
 * モデル描画関数
 */
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

/**
 * 周辺モデル描画関数
 */
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

/**
 * 遠方モデル描画関数
 */
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

/**
 * ミニマップ描画関数
 * @param CamAngH カメラの方向角
 */
void Model::DrawMiniMap(const float CamAngH) const {
	// ミニマップの表示
	SetDrawArea(1020, 460, 1260, 700); // ミニマップの描画領域
	SetupCamera_Ortho(static_cast<float>(MiniMapScale << 3)); // 正射影カメラをセットアップ
	SetCameraScreenCenter(1140, 580); // ミニマップの中心位置
	SetCameraPositionAndTargetAndUpVec(
		VTransformSR(VAdd(Bal.Pos, VGet(0.0F, 2.0F, 0.0F)), RotationMat),
		VTransformSR(Bal.Pos, RotationMat),
		VGet(std::sin(CamAngH), 0.0F, std::cos(CamAngH))
	); // カメラの位置をボールの上に設定
	DrawBox(1020, 460, 1260, 700, GetColor(0, 0, 0), TRUE); // ミニマップの背景
	DrawModel(); // ミニマップを描画
	SetMarker(); // スタート位置マーカーとゴール位置マーカーを描画
	SetDrawArea(0, 0, 1280, 720); // 描画領域を元に戻す
	// 終了
	return;
}

/**
 * 画像描画関数
 * @param CamAngH カメラの方向角
 */
void Model::DrawInfo(const float CamAngH) const {
	// スタート位置マーカーとゴール位置マーカーの描画
	SetMarker();
	// デバッグ情報の描画
	if(ShowDebug) {
		DrawFormatString(
			0,
			0,
			IsGoaled ? GetColor(0, 0, 0) : GetColor(255, 255, 255),
			"Type: %d, Size: %d, Seed: %d\nStageTilt: (X= %f, Z= %f)\nBallPosition: (X= %f, Z= %f)\nBallVelocity: (X= %f, Z= %f)",
			static_cast<int>(Setting::GetStageType()),
			Setting::GetStageSize(),
			Setting::GetStageSeed(),
			RotationAng.x,
			RotationAng.z,
			Bal.Pos.x,
			Bal.Pos.z,
			Bal.Vel.x,
			Bal.Vel.z
		); // 操作方法説明の描画
	} else if(!IsGoaled) {
		DrawString(
			0,
			0,
			"傾ける：マウス左ドラッグ／WASDキー　視点移動：矢印キー　拡大・縮小：マウスホイール　視点リセット：Rキー　視点変更：F5キー\nボール位置リセット：Uキー　ミニマップ表示切替：Mキー　デバッグ表示切替：F3キー　タイトルに戻る：Tキー",
			GetColor(255, 255, 255)
		);
	}
	// ミニマップの描画
	if(ShowMiniMap) DrawMiniMap(CamAngH);
	// 終了
	return;
}

/**
 * 軌跡画面描画関数
 * @param EndNum 描画する軌跡の末端番号
 */
void Model::DrawRoute(unsigned int EndNum) const {
	// マップの表示
	SetupCamera_Ortho(6.0F * Size); // 正射影カメラをセットアップ
	SetCameraScreenCenter(640, 360);
	SetCameraPositionAndTargetAndUpVec(
		VTransformSR(VGet(0.0F, 2.0F, 0.0F), RotationMat),
		VTransformSR(VGet(0.0F, 0.0F, 0.0F), RotationMat),
		VGet(0.0F, 0.0F, 1.0F)
	); // カメラの位置を中央に設定
	DrawModel(); // マップを描画
	SetMarker(); // スタート位置マーカーとゴール位置マーカーを描画
	// 移動距離の表示
	DrawFormatString(588, 620, GetColor(0, 0, 0), "道程：%3d cm", BallPosHist.size());
	DrawString(564, 640, "左クリックで閉じる", GetColor(0, 0, 0));
	// 軌跡の表示
	std::queue<VECTOR> BallPosHistTmp = BallPosHist; // 履歴を複製
	BallPosHistTmp.push(GoalLoc); // 最後をゴール位置にする
	const float Scale = 120.0F / Size; // 描画縮尺
	VECTOR LastPos = VScale(BallPosHistTmp.front(), Scale);
	BallPosHistTmp.pop();
	while(EndNum && !BallPosHistTmp.empty()) {
		const VECTOR NextPos = VScale(BallPosHistTmp.front(), Scale);
		BallPosHistTmp.pop();
		DrawLineAA(LastPos.x + 640.0F, 360.0F - LastPos.z, NextPos.x + 640.0F, 360.0F - NextPos.z, GetColor(255, 0, 0)); // 軌跡の線
		LastPos = NextPos;
		--EndNum;
	}
	DrawCircle(static_cast<int>(LastPos.x) + 640, 360 - static_cast<int>(LastPos.z), 120 / Size, GetColor(255, 0, 0), TRUE); // 先頭部
	// 終了
	return;
}

/**
 * ボールワールド座標取得関数
 * @return ボールのワールド座標
 */
VECTOR Model::GetBallLocation() const {
	// ボールのワールド座標の返戻
	return VTransformSR(Bal.Pos, RotationMat);
}

/**
 * ステージ傾斜操作関数
 * @param CamAngH カメラの方向角
 * @return カメラ方向のステージ傾斜角
 */
float Model::Rotate(const float CamAngH) {
	// ステージ傾斜の計算
	if(Input::GetClicking()) {
		RotationAng = VAdd(
			RotationAng,
			VScale(VGet(static_cast<float>(-Input::GetCursorMoveY()), 0.0F, static_cast<float>(-Input::GetCursorMoveX())), SlopeRateDrag)
		); // 左クリック中はマウスドラッグで傾斜
	} else if(Input::GetWASDPressing()) {
		RotationAng = VAdd(
			RotationAng,
			VScale(VGet(static_cast<float>(Input::GetWSMove()), 0.0F, static_cast<float>(Input::GetADMove())), SlopeRateWASD)
		); // ＷＡＳＤキー押下中はＷＡＳＤキーで傾斜
	} else RotationAng = VScale(RotationAng, SlopeRateRdct); // 無操作時は徐々に自立
	// 最大傾斜角への傾斜の制限
	if(const float Slope = VSize(RotationAng); Slope > MaxSlope) RotationAng = VScale(RotationAng, MaxSlope / Slope);
	// カメラの向きに応じた傾け方向の調整
	CamRotAng = VTransformSR(RotationAng, MGetRotY(CamAngH));
	// 描画用回転行列の生成
	RotationMat = MMult(MGetRotX(CamRotAng.x), MGetRotZ(CamRotAng.z)); // 回転行列
	// カメラ方向のステージ傾斜角の算出
	const VECTOR Direct = VGet(std::sin(CamAngH), 0.0F, std::cos(CamAngH)); // 方向ベクトル
	const VECTOR Normal = VTransformSR(VGet(0.0F, 1.0F, 0.0F), RotationMat); // 法線ベクトル
	// カメラ方向のステージ傾斜角の返戻
	return 0.5F * DX_PI_F - std::acos(VDot(Direct, Normal) / VSize(Direct) / VSize(Normal));
}

/**
 * シミュレート関数
 * @return ゴール判定
 */
bool Model::Simulate() {
	// ボール位置のリセット
	if(Input::GetKeyPress(KEY_INPUT_U)) { // Ｕキーでスタートに戻る
		// スタートに戻す
		Bal.SetPos(StartLoc);
		// ボールの位置履歴の初期化
		if(!IsGoaled) { // 未ゴール時
			std::queue<VECTOR> NewQueue;
			BallPosHist.swap(NewQueue);
			BallPosHist.push(StartLoc);
		}
	}
	// デバッグ用
	// if(Input::GetKeyPress(KEY_INPUT_G)) Bal.SetPos(GoalLoc); // Ｇキーでゴール
	// 傾きからのボール位置の算出
	Bal.Position(CamRotAng.x, CamRotAng.z);
	// ボール位置への衝突判定の反映
	switch(Type) {
	case StageForm::SQR: // 四角形ステージの時
		StageSqr.PositionFix(Bal.Pos, Bal.Vel);
		break;
	case StageForm::HEX: // 六角形ステージの時
		StageHex.PositionFix(Bal.Pos, Bal.Vel);
		break;
	}
	// スタートとゴールからの距離の算出
	StartDist = VSize(VSub(Bal.Pos, StartLoc));
	GoalDist = VSize(VSub(Bal.Pos, GoalLoc));
	// ゴール前
	if(!IsGoaled) { // 未ゴールの時
		// ボール位置履歴の追加
		if(BallPosHist.size() < INT_MAX && VSize(VSub(Bal.Pos, BallPosHist.back())) >= 1.0F) BallPosHist.push(Bal.Pos);
		// ゴール判定
		IsGoaled = GoalDist < 1.0F;
	}
	// ゴール判定の返戻
	return IsGoaled;
}

/**
 * 表示切替関数
 * @return ミニマップ上のカーソル有無
 */
bool Model::SwitchDisplay() {
	// デバック情報の表示有無の切替
	if(Input::GetKeyPress(KEY_INPUT_F3)) ShowDebug ^= true; // Ｆ３キーで切替
	// ミニマップの表示有無の切替
	if(Input::GetKeyPress(KEY_INPUT_M)) ShowMiniMap ^= true; // Ｍキーで切替
	// ミニマップの拡縮
	const bool IsCursorOnMiniMap = ShowMiniMap && Input::IsCursorInBox(1020, 460, 1260, 700); // ミニマップ上のカーソル有無
	if(IsCursorOnMiniMap) { // カーソルがミニマップ上に有る時
		MiniMapScale -= GetMouseWheelRotVol(); // マウスホイールでミニマップを拡縮
		MiniMapScale = std::clamp(MiniMapScale, 2, 8); // 拡縮を範囲内に制限
	}
	// ミニマップ縮尺のリセット
	if(Input::GetKeyPress(KEY_INPUT_R)) MiniMapScale = 4; // Ｒキーでリセット
	// ミニマップ上のカーソル有無の返戻
	return IsCursorOnMiniMap;
}

/**
 * コンストラクタ
 */
Model::Model() {
	// メンバ変数の初期化
	Type = Setting::GetStageType();
	Size = Setting::GetStageSize();
	IsGoaled = false;
	RotationAng = VGet(0.0F, 0.0F, 0.0F);
	CamRotAng = VGet(0.0F, 0.0F, 0.0F);
	RotationMat = MGetIdent(); // 単位行列
	switch(Type) {
	case StageForm::SQR: // 四角形ステージの時
		StartLoc = VGet(static_cast<float>(1 - Size << 1), 0.0F, static_cast<float>(1 - Size << 1)); // スタート位置
		GoalLoc = VGet(static_cast<float>(Size - 1 << 1), 0.0F, static_cast<float>(Size - 1 << 1)); // ゴール位置
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
	StartMarkerGraphHandle = LoadGraph("graphs\\start_marker.png"); // スタート位置マーカー
	GoalMarkerGraphHandle = LoadGraph("graphs\\goal_marker.png"); // ゴール位置マーカー
	// 終了
	return;
}

/**
 * デストラクタ
 */
Model::~Model() {
	// マーカーグラフの解放
	DeleteGraph(StartMarkerGraphHandle);
	DeleteGraph(GoalMarkerGraphHandle);
	// 終了
	return;
}
