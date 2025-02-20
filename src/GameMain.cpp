#include "WinMain.h"
#include "Base.h"
#include "Hit.h"
#include "Title.h"
#include "ModeSelectScene.h"
#include "EasyPlay.h"
#include "NormalPlay.h"
#include "HardPlay.h"
#include "PlayScene.h"
#include "Enemy.h"
#include "Endscene.h"
// =====================================================
//	グローバル変数
//	複数の関数で共通して使いたい変数はここに書く
// =====================================================

int scene_change = 0;

enum  Scene // 各シーン
{
	TITLE_SCENE = 0, // タイトルシーン
	GAMEMAIN_SCENE,  // ゲームメインシーン
	END_SCENE,       // エンドシーン

	CLEAN,           // クリーン
};

// オブジェクトの宣言
// -------------------------
Base base;             //Base タイトルシーンの切り替えをするため
PlayScene playscene;     // プレイシーン
Title title;           // タイトル
EndScene endscene;     // エンディングシーン

// -------------------------
 

// スタート画面に戻るための変数
int start_count ;
int count = 10;

// =====================================================
//		初期化
//	ゲーム開始直後に最初に1回だけ実行される関数
//	最初の値を変数に入れたいときに使う
// =====================================================
void GameInit()
{
	title.Init();
	playscene.Init();
	endscene.Init();

}

// =====================================================
//		更新
//	ゲームが終了されるまで実行される関数
//	1秒間に約60回呼ばれる
//	1フレームで行う処理をここに書く
// =====================================================
void GameUpdate()
{

	switch (scene_change)
	{
	case TITLE_SCENE:
		start_count = 600;
		count = 10;
		title.Update();
		if (title.IsChange()) {
			scene_change = 1;
		}
		break;
	case GAMEMAIN_SCENE:
		playscene.Update();
		if (playscene.IsChange()) {
			scene_change = 2;
		}
		break;
	case END_SCENE:
		endscene.Update();
		if (IsKeyOn(KEY_INPUT_SPACE)) {
			scene_change = 3;
		}
		break;
	case CLEAN:
		start_count--;
		if (start_count % 60 == 0) {
			count--;
		}
		
		if (start_count < 0) {
			GameExit();
			GameInit();
			
			scene_change = 0;
			
		}
		break;
	}
	// 

}
// =====================================================
//		描画
//	ゲームが終了されるまで実行される関数
//	1秒間に約60回呼ばれる
//	GameUpdate関数が実行された後に実行される関数
// =====================================================
void GameDraw()
{
	switch (scene_change)
	{
	case TITLE_SCENE:
		title.Draw();
		break;

	case GAMEMAIN_SCENE:
		playscene.Draw();
		break;

	case END_SCENE:
		endscene.Draw();
		DrawString(20, 425, "SKIP >> SPACE", GetColor(255, 255, 255));
		break;
	case CLEAN:
		DrawFormatString(310, 230,  GetColor(255, 255, 255), "START << %d", count);
	default:
		break;
	}


}
// =====================================================
//		終了
//	ゲームが終了する前に1回だけ実行される関数
//	何か最後に後片付けを行うときに使う
// =====================================================
void GameExit()
{
	// 各クラスの終了処理
	title.Exit();
	playscene.Exit();
	endscene.Exit();
}
