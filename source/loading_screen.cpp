#include <DxLib.h>
#include "loading_screen.h"
#include "setting.h"

// ƒRƒ“ƒXƒgƒ‰ƒNƒ^
LoadingScreen::LoadingScreen() {
	// ƒƒ“ƒo•Ï”‚Ì‰Šú‰»
	switch(Setting::GetStageType()) {
	case StageForm::SQR:
		TotalNodes = Setting::GetStageSize() * Setting::GetStageSize();
		break;
	case StageForm::HEX:
		TotalNodes = Setting::GetStageSize() * Setting::GetStageSize() * 3 / 2 + Setting::GetStageSize() % 2 * Setting::GetStageSize() - 1;
		break;
	default:
		TotalNodes = 0;
		break;
	}
	LoadedNodes = 0;
	// ‰æ‘œ‚Ì“Ç
	BGGraphHandle = LoadGraph("graphs\\background.png"); // ”wŒi
	// I—¹
	return;
}

// ‰æ–Ê•`‰æŠÖ”
void LoadingScreen::DrawScreen() {
	// ’TõÏƒm[ƒh”‚Ì‰ÁZ
	++LoadedNodes;
	// ‰æ–Ê‚ÌƒNƒŠƒA
	ClearDrawScreen();
	// ”wŒi‚Ì•`‰æ
	DrawModiGraph(0, 0, 1280, 0, 1280, 720, 0, 720, DerivationGraph(0, 221, 128, 17, BGGraphHandle), FALSE);
	// ƒQ[ƒW‚Ì•`‰æ
	DrawString(390, 332, "Now Loading...", GetColor(255, 255, 255));
	DrawBox(390, 350, 890, 370, GetColor(128, 128, 128), TRUE);
	DrawBox(390, 350, 390 + LoadedNodes * 500 / TotalNodes, 370, GetColor(255, 255, 255), TRUE);
	DrawFormatString(900, 352, GetColor(255, 255, 255), "%3d%%", LoadedNodes * 100 / TotalNodes);
	// — ‰æ–Ê‚Ì“à—e‚ğ•\‰æ–Ê‚É”½‰f
	ScreenFlip();
	// I—¹
	return;
}