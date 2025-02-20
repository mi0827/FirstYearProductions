
#include "Pos.h"
#include "Base.h"
#include "WinMain.h"
#include "Hit.h"
#include "ModeSelectScene.h"
#include "MovePlayer.h"
#include "Enemy.h"
#include "Tutorial.h"
#include "EasyPlay.h"
#include "NormalPlay.h"
#include "HardPlay.h"
#include "PlayScene.h"
#include "Endscene.h"

EndScene::EndScene()
{

}

EndScene::~EndScene()
{
}

extern PlayScene playscene;     // プレイシーン


// 次のシーンに行くための関数
bool EndScene::IsChange()
{
	return change_;
}


//-----------------------
// 初期設定
//-----------------------
void EndScene::Init()
{
	// 文字の描画座標
	m_pos.x = 230;
	m_pos.y = 100;

	// 背景画像の読み込み
	m_bak_image = LoadGraph("data/BG/pipo-bg003a.jpg");

	// 最初はfalse
	change_ = false;

	// 最後の画面で描画するための変数
	m_point_pos.x = 300;
	m_point_pos.y = 500;

	// BGMの読み込み
	m_bgm = LoadSoundMem("data/sound/end.mp3");

	//// スコア更新したときに流す効果音
	//m_update_sound = LoadSoundMem("data/sound/effect/update.mp3");

	//// スコア更新の音を流すかを決める変数
	//m_sound = false;

	// BGMが流れているかを確認する変数
	// 最初は流れていない
	sound_change = true;

	// ボリューム設定
	ChangeVolumeSoundMem(255, m_bgm);
}


//-----------------------
// 更新処理
//-----------------------
void EndScene::Update()
{

	// bgmの再生
	// 一週目だけ流す
	if (sound_change == true) {
		PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP, TRUE);
	}
	// 二週目から繰り返さないようにする
	sound_change = false;
	
	/*ChangeVolumeSoundMem(100, m_update_sound);*/


	if (IsKeyOn(KEY_INPUT_SPACE)) {
		// BGMを停止
		StopSoundMem(m_bgm);
		change_ = true;
	}

	// 最後の画面で描画するための変数
	m_point_pos.y--;
	// 画面の真ん中くらいに行ったら止める
	if (m_point_pos.y <= 270) {
		/*m_sound = true;*/
		m_point_pos.y = 270;
	}
//	if (m_sound == true) {
//		// 効果音を再生
//		PlaySoundMem(m_update_sound, DX_PLAYTYPE_BACK);
//	}
}

//-----------------------
// 描画処理
//-----------------------
void EndScene::Draw()
{
	// 画面サイズに合わせて背景画像の描画
	DrawExtendGraphF(0, 0, WINDOW_W, WINDOW_H, m_bak_image, TRUE);

	// 文字の大きさを変える
	SetFontSize(35);
	// エンディングなのがわかるように
	DrawStringF(m_pos.x- 20, m_pos.y, "遊んでくれてありがとう ", GetColor(255, 0, 0), TRUE);
	// 文字の大きさを戻す
	SetFontSize(25);

	playscene.PointDraw(m_point_pos);

}

void EndScene::Exit()
{
	// Bgmの削除
	DeleteSoundMem(m_bgm);
	// サウンドの削除
	DeleteSoundMem(m_update_sound);
	DeleteGraph(m_bak_image);
}
