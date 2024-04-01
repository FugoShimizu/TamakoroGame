#pragma once

// プレイ画面クラス
class PlayScreen {
private:

	int LightHandle = -1; // ライトハンドル
	int NearShadowMapHandle = -1; // ボール周辺シャドウマップハンドル
	int FarShadowMapHandle = -1; // ボール遠方シャドウマップハンドル
	int StartSoundHandle = -1; // スタートサウンドハンドル https://dova-s.jp/se/play1047.html
	int GoalSoundHandle = -1; // ゴールサウンドハンドル https://dova-s.jp/se/play1343.html
	int BGMSoundHandle = -1; // ＢＧＭサウンドハンドル https://dova-s.jp/bgm/play15951.html
	int FontHandle = -1; // フォントハンドル

public:

	bool DrawScreen(); // 画面描画関数

	PlayScreen &operator=(const PlayScreen &) = delete; // コピー代入演算子（禁止）
	PlayScreen(const PlayScreen &) = delete; // コピーコンストラクタ（禁止）

	PlayScreen(); // コンストラクタ
	~PlayScreen(); // デストラクタ
};
