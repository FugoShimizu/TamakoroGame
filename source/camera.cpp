#include <algorithm>
#include <cmath>
#include "camera.h"
#include "input.h"
#include "setting.h"

// コンストラクタ
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

// 位置初期化関数
void Camera::Reset() {
	// カメラ位置の初期化
	DirectionV = 24;
	DirectionH = 0;
	Distance = std::clamp(Setting::GetStageSize() * 5, 10, 160);
	// 終了
	return;
}

// 移動関数
void Camera::Move(const VECTOR &BallLocation, const float &CamAngLowLim, const bool &CursorOnMiniMap) {
	// 視野の指定
	SetupCamera_Perspective(DX_PI_F / 3.0F);
	SetCameraScreenCenter(640, 360);
	// カメラの操作
	Control(CamAngLowLim, CursorOnMiniMap);
	// カメラ視点の切替
	if(Input::GetKeyPress(KEY_INPUT_F5)) ++Viewpoint %= 3; // F5キーで切替
	switch(Viewpoint) {
	case 0: // 定点カメラ
		SetCameraPositionAndTargetAndUpVec(Position, VGet(0.0F, 0.0F, 0.0F), Overhead);
		break;
	case 1: // 追跡カメラ
		SetCameraPositionAndTargetAndUpVec(VAdd(Position, BallLocation), BallLocation, Overhead);
		break;
	case 2: // ボール視点カメラ
		SetCameraPositionAndAngle(BallLocation, (DirectionV - 24) * UnitMoveAng, DirectionH * UnitMoveAng, 0.0F);
		break;
	}
	// 終了
	return;
}

// 操作関数
void Camera::Control(const float &CamAngLowLim, const bool &CursorOnMiniMap) {
	// カメラの上下・左右移動
	DirectionV -= Input::GetUDMove(); // 上下操作
	DirectionH -= Input::GetLRMove(); // 左右操作
	DirectionV = std::clamp(DirectionV, 0, 32); // 仰角を範囲内に制限
	DirectionH = DirectionH < -64 ? 63 : DirectionH > 63 ? -64 : DirectionH; // 方向角を範囲内に制限
	// カメラのズーム
	if(!CursorOnMiniMap) { // カーソルがミニマップ上に無い時
		Distance -= GetMouseWheelRotVol(); // マウスホイールで拡縮
		Distance = std::clamp(Distance, 10, 160); // 拡縮を範囲内に制限
	}
	// カメラ位置
	if(Input::GetKeyPress(KEY_INPUT_R)) Reset(); // Rキーでリセット
	const float AngleV = (std::max)(DirectionV * UnitMoveAng, CamAngLowLim); // カメラがステージの下に行かない様にする
	const float AngleH = DirectionH * UnitMoveAng;
	PositionY = sinf(AngleV);
	PositionR = cosf(AngleV);
	PositionX = -sinf(AngleH);
	PositionZ = -cosf(AngleH);
	Position = VAdd(VScale(VGet(PositionX * PositionR, PositionY, PositionZ * PositionR), static_cast<float>(Distance)), VGet(0.0F, 3.0F, 0.0F));
	Overhead = VGet(-PositionX, static_cast<float>(Distance), -PositionZ);
	// デバッグ用
//	clsDx(); printfDx("Cam: (V= %d, H= %d, D= %d)", DirectionV, DirectionH, Distance);
	// 終了
	return;
}

// 方向角取得関数
float Camera::GetDirection() const {
	// 終了
	return DirectionH * UnitMoveAng; // 方向角を返す
}

// 背景描画関数
void Camera::DrawBackground() const {
	// 背景の描画
	DrawModiGraph(0, 0, 1280, 0, 1280, 720, 0, 720, DerivationGraph(0, (std::min)(static_cast<int>(PositionY * 256.0F), 255), 128, (std::max)(static_cast<int>((1.0F - PositionY) * 128.0F), 1), BGGraphHandle), FALSE);
	// 終了
	return;
}