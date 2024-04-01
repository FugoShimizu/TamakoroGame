#pragma once

#include <DxLib.h>

// ブロック基底クラス
class BlockBase {
private:

	static constexpr float RepulsionCoefficient = -0.5F; // 反発係数（負）
	void CollisionSound(const float ImpactVel) const; // 衝突音再生関数

protected:

	int ModelHandle = -1; // モデルハンドル
	int CollisionSoundHandle = -1; // 衝突音サウンドハンドル
	void CollisionDetection(const float Distance, const float Angle, VECTOR &BallPos, VECTOR &BallVel) const; // 衝突判定反映関数

public:

	int GetModel() const; // モデルハンドル取得関数
	void DeleteModel(); // モデルハンドル削除関数

	BlockBase &operator=(const BlockBase &) = delete; // コピー代入演算子（禁止）
	BlockBase(const BlockBase &) = delete; // コピーコンストラクタ（禁止）
	BlockBase() = default; // コンストラクタ

	virtual ~BlockBase(); // デストラクタ
};
