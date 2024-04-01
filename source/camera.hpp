#pragma once

#include <DxLib.h>
#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>

// カメラ（視点）クラス
class Camera {
private:

	static constexpr float UnitMoveAng = DX_PI_F / 64.0F; // 単位移動角度
	// 背景球の形状
	static constexpr uint32_t BGDivLat = 32; // 緯度方向の分割数
	static constexpr uint32_t BGDivLon = BGDivLat << 1; // 経度方向の分割数
	static constexpr size_t BGIndexCount = 6 * BGDivLat * BGDivLon; // 頂点インデックス数（各升を２つの三角形に分割）
	static constexpr float BGUnitAng = 1.0F / BGDivLat * DX_PI_F; // 分割単位角度
	static constexpr float BGRadius = 128.0F; // 半径（描画距離の範囲内）

	static constexpr std::array<uint16_t, BGIndexCount> BGIndices = []() -> std::array<uint16_t, BGIndexCount> { // 頂点インデックス
		// 頂点インデックスの生成
		std::array<uint16_t, BGIndexCount> Indices {};
		size_t Count = 0;
		for(uint32_t i = 0; i < BGDivLat; ++i) for(uint32_t j = 0; j < BGDivLon; ++j) {
			const uint16_t UpperLeft = static_cast<uint16_t>((BGDivLon + 1) * i + j), UpperRight = static_cast<uint16_t>(UpperLeft + 1);
			const uint16_t LowerLeft = static_cast<uint16_t>(UpperLeft + BGDivLon + 1);
			for(const uint16_t Index : { UpperLeft, LowerLeft, UpperRight, UpperRight, LowerLeft, static_cast<uint16_t>(LowerLeft + 1) }) {
				Indices[Count++] = Index;
			}
		}
		// 頂点インデックスの返戻
		return Indices;
	}();

	static const std::vector<VERTEX3D> BGVertices; // 背景球の頂点（カメラ中心の相対座標）
	const int BGGraphHandle; // 背景グラフハンドル
	unsigned int Viewpoint; // 視点
	int DirectionV; // 仰角（水平方向から上向き，64=180°）
	int DirectionH; // 方向角（Ｚ負方向から右回り，64=180°）
	float PositionY; // 仰角から算出したＹ座標
	float PositionR; // 仰角から算出した中心からの距離
	float PositionX; // 方向角から算出したＸ座標
	float PositionZ; // 方向角から算出したＺ座標
	VECTOR Position;
	VECTOR Overhead;
	int Distance; // 対象距離
	static std::vector<VERTEX3D> MakeBGVertices(); // 背景球頂点生成関数
	void Reset(); // 位置初期化関数
	void Control(const float CamAngLowLim, const bool IsCursorOnMiniMap); // 操作関数

public:

	float GetDirection() const; // 方向角取得関数
	void DrawBackground() const; // 背景描画関数
	void Move(const VECTOR &BallLocation, const float CamAngLowLim, const bool IsCursorOnMiniMap); // 移動関数

	Camera &operator=(const Camera &) = delete; // コピー代入演算子（禁止）
	Camera(const Camera &) = delete; // コピーコンストラクタ（禁止）

	Camera(); // コンストラクタ
	~Camera(); // デストラクタ
};
