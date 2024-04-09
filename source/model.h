#pragma once
#include <queue>
#include <DxLib.h>
#include "stage_sqr.h"
#include "stage_hex.h"
#include "ball.h"
#include "setting.h"

// モデルクラス
class Model {
public:
	Model(); // コンストラクタ
	VECTOR GetBallLocation() const; // ボールワールド座標取得関数
	float Rotate(const float &CamAngH); // ステージ傾斜操作関数
	bool Simulate(); // シミュレート関数
	bool SwitchDisplay(); // 表示切替関数
	void DrawModel() const; // モデル描画関数
	void DrawNearModel() const; // 周辺モデル描画関数
	void DrawFarModel() const; // 遠方モデル描画関数
	void DrawInfo(const float &CamAngH) const; // 画像描画関数
	void DrawRoute(int EndNum) const; // 軌跡画面描画関数
private:
	static constexpr float SlopeRateDrag = 1.0f / 512.0f; // ドラッグ操作時傾斜割合
	static constexpr float SlopeRateWSAD = 1.0f / 64.0f; // WSADキー操作時傾斜割合
	static constexpr float SlopeRateRdct = 15.0f / 16.0f; // 無操作時傾斜縮小割合
	static constexpr float MaxSlope = DX_PI_F / 6.0f; // 最大傾斜角
	StageSqr StageSqr; // 四角形ステージ
	StageHex StageHex; // 六角形ステージ
	Ball Bal; // ボール
	StageForm Type; // ステージの形
	int Size; // ステージの大きさ
	bool Goal; // ゴール判定
	VECTOR RotationAng; // ステージ傾斜角
	VECTOR CamRotAng; // カメラ視点からのステージ傾斜角
	MATRIX RotationMat; // 回転行列
	VECTOR StartLoc; // スタート位置
	VECTOR GoalLoc; // ゴール位置
	float StartDist; // スタートとボールの直線距離
	float GoalDist; // ゴールとボールの直線距離
	bool ShowDebug; // デバッグ画面表示フラグ
	bool ShowMiniMap; // ミニマップ表示フラグ
	int MiniMapScale; // ミニマップ縮尺
	std::queue<VECTOR> BallPosHist; // ボール位置履歴
	int SMGraphHandle; // スタートマーカーグラフハンドル
	int GMGraphHandle; // ゴールマーカーグラフハンドル
	void SetMarker() const; // マーカー設定関数
	void DrawMarker(const VECTOR &ScrCoord, const int &MarkerGraphHandle, const unsigned int &FontColor, const int &Distance) const; // マーカー描画関数
	void DrawMiniMap(const float &CamAngH) const; // ミニマップ描画関数
};