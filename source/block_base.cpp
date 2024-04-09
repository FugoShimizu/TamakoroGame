#include "block_base.h"

// モデルハンドル取得関数
int BlockBase::GetModel() const {
	// 終了
	return ModelHandle; // モデルハンドルを返す
}

// モデルハンドル削除関数
void BlockBase::DeleteModel() const {
	// モデルの削除
	MV1DeleteModel(ModelHandle);
	// 終了
	return;
}

// 衝突判定反映関数
void BlockBase::CollisionDetection(const float &Distance, const float &Angle, VECTOR &BallPos, VECTOR &BallVel) const {
	// 衝突によるボールの位置と速度の修正
	if(Distance < 1.0F) { // ボールが衝突している時
		// 壁の法線のX軸方向への変換
		MATRIX RotationMat = MGetRotY(Angle); // 回転行列
		BallPos = VTransformSR(BallPos, RotationMat);
		BallVel = VTransformSR(BallVel, RotationMat);
		// 衝突による位置と速度の修正
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

// 衝突音再生関数
void BlockBase::CollisionSound(const float &ImpactVel) const {
	// 衝突音の再生
	if(ImpactVel > 0.01F) { // 閾値以上の速度で衝突した時
		// 音量の設定
		ChangeNextPlayVolumeSoundMem(static_cast<int>(ImpactVel * 1024.0F), CollisionSoundHandle);
		// 音声の再生
		PlaySoundMem(CollisionSoundHandle, DX_PLAYTYPE_BACK);
		// デバッグ用
	//	clsDx(); printfDx("%f", ImpactVel);
	}
	// 終了
	return;
}