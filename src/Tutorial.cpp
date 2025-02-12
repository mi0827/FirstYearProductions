#include "WinMain.h"
#include "Pos.h"
#include "Base.h"
#include "Enemy.h"
#include "MovePlayer.h"
#include "PlayBase.h"
#include "Tutorial.h"

// プレイヤーが動かす玉のクラス
extern MovePlayer player;

// Enemyクラス
extern Enemy enemy;

// 次のシーンに行くための関数
bool Tutorial::IsChange()
{
	return change_;
}

void Tutorial::Init()
{
	// MovePlayerの初期設定
	player.Init();
	// enemyの初期処理
	// チュートリアルでは動かさない
	enemy.Init(0.0f);
	// 背景画像の読み込み
	m_bak_image = LoadGraph("data/BG/pipo-bg001a.jpg");
	//  最初はfalse
	change_ = false;

	// BGMの読み込み
	m_bgm = LoadSoundMem("data/sound/tutoriarulbgm.mp3");

	// BGMが流れているかを確認する変数
	// 最初は流れていない
	sound_change = true;

	// ボリューム設定
	ChangeVolumeSoundMem(150, m_bgm);
}

void Tutorial::Update()
{
	// bgmの再生
// 一週目だけ流す
	if (sound_change == true) {
		PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP, TRUE);
	}
	// 二週目から繰り返さないようにする
	sound_change = false;
	

	// MovePlayerの更新処理
	player.Update();

	//enemyの更新処理
	enemy.Update(3600);
	if (IsKeyOn(KEY_INPUT_SPACE)) {
		// BGMの再生を止める
		StopSoundMem(m_bgm);
		change_ = true;
	}
}

void Tutorial::Draw()
{
	// 背景画像の描画
	// 画面サイズに合わせて描画
	DrawExtendGraphF(0, 0, WINDOW_W, WINDOW_H, m_bak_image, TRUE);


	enemy.Draw();

	player.Draw();

	// 文字の大きさを変える
	/*SetFontSize(40);
	DrawString(20, 20, "チュートリアル", GetColor(0, 0, 0), FALSE);*/
	SetFontSize(25);
	// ゴシック体に変更
	ChangeFont("ＭＳ ゴシック体");
	DrawString(20, 2, "マウスを使ってお化けを叩いてポイントをゲットしよう！！", GetColor(0, 0, 0));
	DrawString(250, 425, "※床が炎で埋まるまでにできるだけ倒そう！", GetColor(255, 0, 0));

	// 明朝体に変更
	ChangeFont("ＭＳ 明朝");
	DrawString(20, 425, "SKIP >> SPACE", GetColor(0, 0, 0));
	// 文字の大きさを変える 

	SetFontSize(15);
	for (int i = 0; i < ENEMY_MAX; i++) {
		
		if (i == 0) {
			DrawString(enemy.m_enemy_pos[i].x, enemy.m_enemy_pos[i].y - 15, "ポイント高いよ！！", GetColor(250, 0, 0));
		}
		else if (i <= 2) {
			DrawString(enemy.m_enemy_pos[i].x, enemy.m_enemy_pos[i].y - 15, "叩いていいよ！", GetColor(255, 0, 0));
		}
		else {
			DrawString(enemy.m_enemy_pos[i].x, enemy.m_enemy_pos[i].y - 15, "こいつらはダメ", GetColor(255, 0, 0));
		}

	}
	// 文字の大きさを元に戻す
	SetFontSize(25);
}

void Tutorial::Exit()
{
	// Bgmの削除
	DeleteSoundMem(m_bgm);
	// MovePlayerの終了処理
	player.Exit();
	// enemyの削除
	enemy.Exit();

	// 背景画像の削除
	DeleteGraph(m_bak_image);
}


