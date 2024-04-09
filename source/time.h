#pragma once

// 時間クラス
class Time {
public:
	Time(); // コンストラクタ
	void DrawTime() const; // 経過時間描画関数
	bool DrawGoalTime(); // ゴール時間描画関数
private:
	int StartTime; // スタート時時間（秒）
	int GoalElapsedTime; // ゴール時経過時間（秒）
};