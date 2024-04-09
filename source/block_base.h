#pragma once
#include <DxLib.h>

// ブロック基底クラス
class BlockBase {
public:
	int GetModel() const; // モデルハンドル取得関数
	void DeleteModel() const; // モデルハンドル削除関数
protected:
	int ModelHandle; // モデルハンドル
	int CollisionSoundHandle; // 衝突音サウンドハンドル
	void CollisionDetection(const float &Distance, const float &Angle, VECTOR &BallPos, VECTOR &BallVel) const; // 衝突判定反映関数
private:
	static constexpr float RepulsionCoefficient = -0.5F; // 反発係数（負）
	void CollisionSound(const float &ImpactVel) const; // 衝突音再生関数
};