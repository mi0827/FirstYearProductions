#include "WinMain.h"
#include <ctime>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);
	// 画面を全画面に
	/*ChangeWindowMode(FALSE);
	SetWindowSize(WINDOW_W, WINDOW_H);*/
	// いつもの小さい画面
	/*ChangeWindowMode(TRUE);
	SetWindowSize(WINDOW_W, WINDOW_H);*/
	SetGraphMode(WINDOW_W, WINDOW_H, 32);
	SetBackgroundColor(0, 0, 0);
	SetMainWindowText("作品展");
	if (DxLib_Init() == -1) { return -1; }

	SetDrawScreen(DX_SCREEN_BACK);
	// マウスカーソルを非表示する
	SetMouseDispFlag(FALSE);

	// ---------------
	// 初期化処理
	// ---------------
	SRand((int)time(NULL));
	InputKeyInit();
	InputPadInit();
	InputMouseInit();
	GameInit();


	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// ---------------
		// 更新処理
		// ---------------
		InputKeyUpdate();
		InputPadUpdate();
		InputMouseUpdate();
		GameUpdate();

		// ---------------
		// 描画処理
		// ---------------
		ClearDrawScreen();
		clsDx();
		// ------------------------
		//	Debug用
		// ------------------------
		GameDraw();
		ScreenFlip();
	}

	// ---------------
	// 終了処理
	// ---------------
	InputKeyExit();
	InputPadExit();
	InputMouseExit();
	GameExit();

	DxLib_End();

	return 0;
}
