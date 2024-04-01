#include "block_base.hpp"

/**
 * モデルハンドル取得関数
 * @return モデルハンドル
 */
int BlockBase::GetModel() const {
	// モデルハンドルの返戻
	return ModelHandle;
}

/**
 * モデルハンドル削除関数
 */
void BlockBase::DeleteModel() {
	// モデルの削除
	MV1DeleteModel(ModelHandle);
	// ハンドルの無効化
	ModelHandle = -1;
	// 終了
	return;
}

/**
 * 衝突音再生関数
 * @param ImpactVel 衝突時の速度
 */
void BlockBase::CollisionSound(const float ImpactVel) const {
	// 衝突音の再生
	if(ImpactVel > 0.01F) { // 閾値以上の速度で衝突した時
		// 音量の設定
		ChangeNextPlayVolumeSoundMem(static_cast<int>(1024.0F * ImpactVel), CollisionSoundHandle);
		// 音声の再生
		PlaySoundMem(CollisionSoundHandle, DX_PLAYTYPE_BACK);
	}
	// 終了
	return;
}

/**
 * 衝突判定反映関数
 * @param Distance 壁との距離
 * @param Angle 壁の法線方向の角度
 * @param BallPos ボール位置
 * @param BallVel ボール速度
 */
void BlockBase::CollisionDetection(const float Distance, const float Angle, VECTOR &BallPos, VECTOR &BallVel) const {
	// 衝突に因るボールの位置と速度の修正
	if(Distance < 1.0F) { // ボールが衝突している時
		// 壁の法線のＸ軸方向への変換
		MATRIX RotationMat = MGetRotY(Angle); // 回転行列
		BallPos = VTransformSR(BallPos, RotationMat);
		BallVel = VTransformSR(BallVel, RotationMat);
		// 衝突に因る位置と速度の修正
		BallPos.x += 1.0F - Distance;
		BallVel.x *= RepulsionCoefficient;
		CollisionSound(BallVel.x); // 衝突音
		// 方向の再変換
		RotationMat = MGetRotY(-Angle); // 回転行列
		BallPos = VTransformSR(BallPos, RotationMat);
		BallVel = VTransformSR(BallVel, RotationMat);
	}
	// 終了
	return;
}

/**
 * デストラクタ
 */
BlockBase::~BlockBase() {
	// モデルと衝突音の解放
	MV1DeleteModel(ModelHandle);
	DeleteSoundMem(CollisionSoundHandle);
	// 終了
	return;
}
