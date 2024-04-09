#include <DxLib.h>
#include "time.h"

// コンストラクタ
Time::Time() {
	// メンバ変数の初期化
	StartTime = GetNowCount() / 1000; // 現在時間
	GoalElapsedTime = 0;
	// 終了
	return;
}

// 経過時間描画関数
void Time::DrawTime() const {
	// 経過時間の描画
	const int ElapsedTime = GetNowCount() / 1000 - StartTime;
	DrawFormatString(1180, 0, GetColor(255, 255, 255), "Time %02d:%02d", ElapsedTime / 60, ElapsedTime % 60);
	// 終了
	return;
}

// ゴール時間描画関数
bool Time::DrawGoalTime() {
	// 既にゴール済でないか判定
	const bool Fast = !GoalElapsedTime;
	// ゴール時経過時間の描画
	if(Fast) GoalElapsedTime = GetNowCount() / 1000 - StartTime;
	DrawFormatString(1180, 0, GetColor(0, 0, 255), "Time %02d:%02d", GoalElapsedTime / 60, GoalElapsedTime % 60);
	// 終了
	return Fast;
}