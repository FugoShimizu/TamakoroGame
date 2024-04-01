#include "camera.hpp"
#include "input.hpp"
#include "setting.hpp"
#include <algorithm>
#include <cmath>

/**
 * 位置初期化関数
 */
void Camera::Reset() {
	// カメラ位置の初期化
	DirectionV = 24;
	DirectionH = 0;
	Distance = std::clamp(5 * Setting::GetStageSize(), 10, 160);
	// 終了
	return;
}

/**
 * 操作関数
 * @param CamAngLowLim カメラ仰角の下限（-π/2≦CamAngLowLim≦π/2）
 * @param IsCursorOnMiniMap カーソルがミニマップ上に有るか
 */
void Camera::Control(const float CamAngLowLim, const bool IsCursorOnMiniMap) {
	// カメラの上下・左右移動
	DirectionV -= Input::GetUDMove(); // 上下操作
	DirectionH -= Input::GetLRMove(); // 左右操作
	DirectionV = std::clamp(DirectionV, 0, 32); // 仰角を範囲内に制限
	DirectionH = DirectionH < -64 ? 63 : DirectionH > 63 ? -64 : DirectionH; // 方向角を範囲内に制限
	// カメラのズーム
	if(!IsCursorOnMiniMap) { // カーソルがミニマップ上に無い時
		Distance -= GetMouseWheelRotVol(); // マウスホイールで拡縮
		Distance = std::clamp(Distance, 10, 160); // 拡縮を範囲内に制限
	}
	// カメラ位置
	if(Input::GetKeyPress(KEY_INPUT_R)) Reset(); // Ｒキーでリセット
	const float AngleV = (std::max)(UnitMoveAng * DirectionV, CamAngLowLim), AngleH = UnitMoveAng * DirectionH; // カメラがステージの下に行かない様にする
	PositionY = std::sin(AngleV);
	PositionR = std::cos(AngleV);
	PositionX = -std::sin(AngleH);
	PositionZ = -std::cos(AngleH);
	Position = VAdd(
		VScale(VGet(PositionX * PositionR, PositionY, PositionZ * PositionR), static_cast<float>(Distance)),
		VGet(0.0F, 3.0F, 0.0F)
	);
	Overhead = VGet(-PositionX, static_cast<float>(Distance), -PositionZ);
	// デバッグ用
	// clsDx(); printfDx("Cam: (V= %d, H= %d, D= %d)", DirectionV, DirectionH, Distance);
	// 終了
	return;
}

/**
 * 移動関数
 * @param BallLocation ボールのワールド座標
 * @param CamAngLowLim カメラ仰角の下限（-π/2≦CamAngLowLim≦π/2）
 * @param IsCursorOnMiniMap カーソルがミニマップ上に有るか
 */
void Camera::Move(const VECTOR &BallLocation, const float CamAngLowLim, const bool IsCursorOnMiniMap) {
	// 視野の指定
	SetupCamera_Perspective(DX_PI_F / 3.0F);
	SetCameraScreenCenter(640, 360);
	// カメラの操作
	Control(CamAngLowLim, IsCursorOnMiniMap);
	// カメラ視点の切替
	if(Input::GetKeyPress(KEY_INPUT_F5)) ++Viewpoint %= 3; // Ｆ５キーで切替
	switch(Viewpoint) {
	case 0: // 定点カメラ
		SetCameraPositionAndTargetAndUpVec(Position, VGet(0.0F, 0.0F, 0.0F), Overhead);
		return;
	case 1: // 追跡カメラ
		SetCameraPositionAndTargetAndUpVec(VAdd(Position, BallLocation), BallLocation, Overhead);
		return;
	case 2: // ボール視点カメラ
		SetCameraPositionAndAngle(BallLocation, UnitMoveAng * (DirectionV - 24), UnitMoveAng * DirectionH, 0.0F);
		return;
	}
}

/**
 * 方向角取得関数
 * @return カメラの方向角
 */
float Camera::GetDirection() const {
	// 方向角の返戻
	return UnitMoveAng * DirectionH;
}

/**
 * 背景描画関数
 */
void Camera::DrawBackground() const {
	// 背景の派生グラフの生成
	const int DerivedGraphHandle = DerivationGraph(
		0,
		(std::min)(static_cast<int>(256.0F * PositionY), 255),
		128,
		(std::max)(static_cast<int>(128.0F * (1.0F - PositionY)), 1),
		BGGraphHandle
	);
	// 背景の描画
	DrawModiGraph(0, 0, 1280, 0, 1280, 720, 0, 720, DerivedGraphHandle, FALSE);
	// 派生グラフの解放
	DeleteGraph(DerivedGraphHandle);
	// 終了
	return;
}

/**
 * コンストラクタ
 */
Camera::Camera() {
	// メンバ変数の初期化
	Viewpoint = 0;
	Reset(); // カメラ位置
	// 画像の読込
	BGGraphHandle = LoadGraph("graphs\\background.png"); // 背景
	// カメラの設定
	SetCameraNearFar(0.5F, 256.0F); // 描画距離
	// 終了
	return;
}

/**
 * デストラクタ
 */
Camera::~Camera() {
	// 背景グラフの解放
	DeleteGraph(BGGraphHandle);
	// 終了
	return;
}
