#include "camera.hpp"
#include "input.hpp"
#include "setting.hpp"
#include <algorithm>
#include <cmath>

/**
 * 背景球頂点生成関数
 * @return 背景球の頂点（カメラ中心の相対座標）
 */
std::vector<VERTEX3D> Camera::MakeBGVertices() {
	// 頂点の生成
	std::vector<VERTEX3D> Vertices;
	for(uint32_t i = 0; i <= BGDivLat; ++i) for(uint32_t j = 0; j <= BGDivLon; ++j) {
		// 頂点の方向の算出（画像の中心を +Z 方向とし，右へ進むと +X 方向を経て一周する向き）
		const float Polar = BGUnitAng * i, Azimuth = BGUnitAng * j, SinPolar = std::sin(Polar);
		const VECTOR Direction = VGet(-SinPolar * std::sin(Azimuth), std::cos(Polar), -SinPolar * std::cos(Azimuth));
		// 頂点の追加
		Vertices.push_back(
			{
				VScale(Direction, BGRadius),
				VScale(Direction, -1.0F), // 内向きの法線
				GetColorU8(255, 255, 255, 255), // テクスチャの色の儘
				GetColorU8(0, 0, 0, 0), // 鏡面反射無
				1.0F / BGDivLon * j,
				1.0F / BGDivLat * i,
				0.0F,
				0.0F
			}
		);
	}
	// 頂点の返戻
	return Vertices;
}

const std::vector<VERTEX3D> Camera::BGVertices = MakeBGVertices();

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
 * @param CamAngLowLim カメラ仰角の下限（-π/2 ≦ CamAngLowLim ≦ π/2）
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
 * @param CamAngLowLim カメラ仰角の下限（-π/2 ≦ CamAngLowLim ≦ π/2）
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
	// 背景球のカメラ位置への移動（何の視点でも背景が視点の向きにだけ追従する様にする）
	const VECTOR CameraPos = GetCameraPosition(); // ループ内で不変な値を１回だけ取得
	std::vector<VERTEX3D> Vertices = BGVertices;
	for(VERTEX3D &Vertex : Vertices) Vertex.pos = VAdd(Vertex.pos, CameraPos);
	// 背景球の描画（Z バッファを使わずに描画し，後の 3D モデルで上書きする）
	const int PrevDrawMode = GetDrawMode();
	SetUseLighting(FALSE); // 陰影を付けない
	SetDrawMode(DX_DRAWMODE_BILINEAR); // 画像を滑らかに拡大
	DrawPolygonIndexed3D(
		Vertices.data(),
		static_cast<int>(Vertices.size()),
		BGIndices.data(),
		static_cast<int>(BGIndices.size() / 3), // 三角形の数
		BGGraphHandle,
		FALSE
	);
	// 描画設定の復元
	SetDrawMode(PrevDrawMode);
	SetUseLighting(TRUE);
	// 終了
	return;
}

/**
 * コンストラクタ
 */
Camera::Camera() : BGGraphHandle(
	LoadGraph(Setting::GetStageType() == StageForm::HEX ? "graphs\\background_b.png" : "graphs\\background_a.png")
) {
	// メンバ変数の初期化
	Viewpoint = 0;
	Reset(); // カメラ位置
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
