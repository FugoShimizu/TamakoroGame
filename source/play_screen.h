#pragma once

// プレイ画面クラス
class PlayScreen {
public:
	PlayScreen(); // コンストラクタ
	bool DrawScreen(); // 画面描画関数
private:
	int LightHandle; // ライトハンドル
	int NearShadowMapHandle; // ボール周辺シャドウマップハンドル
	int FarShadowMapHandle; // ボール遠方シャドウマップハンドル
	int StartSoundHandle; // スタートサウンドハンドル https://dova-s.jp/se/play1047.html
	int GoalSoundHandle; // ゴールサウンドハンドル https://dova-s.jp/se/play1343.html
	int BGMSoundHandle; // BGMサウンドハンドル https://dova-s.jp/bgm/play15951.html
	int FontHandle; // フォントハンドル
};