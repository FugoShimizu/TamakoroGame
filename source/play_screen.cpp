#include <DxLib.h>
#include "play_screen.h"
#include "input.h"
#include "Camera.h"
#include "model.h"
#include "button.h"
#include "time.h"

// コンストラクタ
PlayScreen::PlayScreen() {
	// ライトの設定
	SetLightEnable(FALSE);
	SetGlobalAmbientLight(GetColorF(0.2F, 0.2F, 0.2F, 0.0F));
	LightHandle = CreateDirLightHandle(VGet(-0.125F, -1.0F, -0.25F));
	SetLightDifColorHandle(LightHandle, GetColorF(1.0F, 1.0F, 1.0F, 1.0F));
	SetLightSpcColorHandle(LightHandle, GetColorF(0.5F, 0.5F, 0.5F, 0.0F));
	SetLightAmbColorHandle(LightHandle, GetColorF(0.0F, 0.0F, 0.0F, 0.0F));
	// ボール周辺の影の設定
	NearShadowMapHandle = MakeShadowMap(4096, 4096);
	SetShadowMapLightDirection(NearShadowMapHandle, VGet(-0.26F, -1.0F, -0.45F));
	SetShadowMapDrawArea(NearShadowMapHandle, VGet(-16.0F, -8.0F, -16.0F), VGet(16.0F, 8.0F, 16.0F));
	// ボール遠方の影の設定
	FarShadowMapHandle = MakeShadowMap(4096, 4096);
	SetShadowMapLightDirection(FarShadowMapHandle, VGet(-0.26F, -1.0F, -0.45F));
	SetShadowMapDrawArea(FarShadowMapHandle, VGet(-64.0F, -32.0F, -64.0F), VGet(64.0F, 32.0F, 64.0F));
	// 音声の読込
	StartSoundHandle = LoadSoundMem("sounds\\start_sound.mp3", 1);
	GoalSoundHandle = LoadSoundMem("sounds\\goal_sound.mp3", 1);
	BGMSoundHandle = LoadSoundMem("sounds\\bgm_sound.mp3", 1);
	// フォントの生成
	FontHandle = CreateFontToHandle(NULL, 140, 4);
	// 終了
	return;
}

// 画面描画関数
bool PlayScreen::DrawScreen() {
	// オブジェクト
	Camera Cam; // カメラ
	Model Mdl; // 3Dモデル
	const Button Btn; // 選択ボタン
	Time Tm; // 時間
	// 軌跡表示フラグ
	int ShowRoute = 0;
	// スタート音の再生
	ChangeNextPlayVolumeSoundMem(128, StartSoundHandle);
	PlaySoundMem(StartSoundHandle, DX_PLAYTYPE_BACK);
	// BGMの再生
	ChangeNextPlayVolumeSoundMem(128, BGMSoundHandle);
	PlaySoundMem(BGMSoundHandle, DX_PLAYTYPE_LOOP);
	// プレイ画面の描画
	while(!Input::ExitOperation() && !Input::GetKeyPress(KEY_INPUT_T)) {
		// 入力状態の更新
		Input::SetInput();
		// ステージの向きの設定
		const float CamAng = Mdl.Rotate(Cam.GetDirection());
		// ボールの位置の計算
		const bool Goal = Mdl.Simulate();
		// カメラ位置の設定
		Cam.Move(Mdl.GetBallLocation(), CamAng, Mdl.SwitchDisplay());
		// 画面のクリア
		ClearDrawScreen();
		// ボール周辺のシャドウマップへの描画
		SetShadowMapDrawArea(NearShadowMapHandle, VSub(Mdl.GetBallLocation(), VGet(16.0F, 8.0F, 16.0F)), VAdd(Mdl.GetBallLocation(), VGet(16.0F, 8.0F, 16.0F))); // 描画領域をボール周辺に設定
		ShadowMap_DrawSetup(NearShadowMapHandle);
		Mdl.DrawNearModel();
		ShadowMap_DrawEnd();
		// ボール遠方のシャドウマップへの描画
		ShadowMap_DrawSetup(FarShadowMapHandle);
		Mdl.DrawFarModel();
		ShadowMap_DrawEnd();
		// 描画
		Cam.DrawBackground(); // 背景
		SetUseShadowMap(0, NearShadowMapHandle);
		SetUseShadowMap(1, FarShadowMapHandle);
		Mdl.DrawModel(); // 3Dモデル
		SetUseShadowMap(0, -1);
		SetUseShadowMap(1, -1);
		Mdl.DrawInfo(Cam.GetDirection()); // 画像等
		// ゴール画面の描画
		if(Goal) { // ゴール済の時
			// 背景
			SetDrawBlendMode(DX_BLENDMODE_ADD, 192);
			DrawBox(0, 0, 1280, 720, GetColor(255, 255, 255), TRUE); // 背景を白くする
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			// ゴール時の経過時間
			if(Tm.DrawGoalTime()) { // ゴール時
				// ゴール音の再生
				ChangeNextPlayVolumeSoundMem(128, GoalSoundHandle);
				PlaySoundMem(GoalSoundHandle, DX_PLAYTYPE_BACK);
				// BGMの停止
				StopSoundMem(BGMSoundHandle);
			}
			// 選択ボタン
			if(ShowRoute) {
				// 軌跡画面の表示
				Mdl.DrawRoute(ShowRoute);
				if(ShowRoute < INT_MAX) ++ShowRoute;
				ShowRoute *= !Input::GetUnclick();
			} else {
				// 「GOAL!」の表示
				DrawStringToHandle(290, 70, "ＧＯＡＬ！", GetColor(0, 0, 255), FontHandle);
				// 軌跡表示ボタン
				ShowRoute = Btn.DrawButton(96, 300, "軌跡確認"); // ボタンクリック時は軌跡画面を表示
				// 再プレイボタン
				if(Btn.DrawButton(490, 300, "再プレイ") || Input::GetKeyPress(KEY_INPUT_RETURN)) return true; // ボタンクリック時は再プレイ
				// タイトルに戻るボタン
				if(Btn.DrawButton(874, 300, "タイトル")) return false; // ボタンクリック時はタイトル画面に戻る
			}
		} else Tm.DrawTime(); // 経過時間
		// 裏画面の内容を表画面に反映
		ScreenFlip();
	}
	// BGMの停止
	StopSoundMem(BGMSoundHandle);
	// 終了
	return false;
}