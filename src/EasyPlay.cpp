#include "WinMain.h"
#include "Pos.h"
#include "Base.h"
#include "Enemy.h"
#include "MovePlayer.h"
#include "PlayBase.h"
#include <fstream>
#include <string>
#include "EasyPlay.h"
using namespace std;


// プレイヤーが動かす玉のクラス
extern MovePlayer player;

// Enemyクラス
extern Enemy enemy;


EasyPlay::EasyPlay()
{

}


EasyPlay::~EasyPlay()
{

}
// TextのEasyScoreファイルの読み込み
int EasyPlay::TextLoadingEasy()
{

	fstream file;
	// ファイルを開く
	file.open("text/EasyScore.txt", ios::in);
	// ファイルが開けたかどうかののチェック
	if (!file.is_open()) {
		return EXIT_FAILURE;
	}
	// ファイルの操作、（読み込み）
	file >> m_best_score;
	// ファイルを閉じる
	file.close();
}

// TextのtEasyScoreファイルへの書き込み
int  EasyPlay::TextWriteInEasy()
{
	fstream file;

	// ファイルを開く
	file.open("text/EasyScore.txt", ios::out);
	// ファイルが開けたかどうかののチェック
	if (!file.is_open()) {
		return EXIT_FAILURE;
	}
	// ファイルの操作、（書き込み）
	num = enemy.m_point;
	file << num << endl;
	// ファイルを閉じる
	file.close();
}

// -----------------
// 初期処理
// -----------------
void EasyPlay::Init()
{
	// Easyの文字の描画座標
	m_pos.x = 16;
	m_pos.y = 16;

	// MovePlayerの初期設定
	player.Init();
	// enemyの初期処理
	// enemyにEasyようのスピードを入れる
	enemy.Init(ENEMY_EASY_SPEED);
	// 背景画像の読み込み
	m_bak_image = LoadGraph("data/BG/pipo-bg005.jpg");

	// 最高スコアの読み込み
	TextLoadingEasy();

	// Easy画面でのｂｇｍを入れる変数
	m_bgm = LoadSoundMem("data/sound/easy.mp3");

	// 流す時間を決める変数
	m_bgm_count = 0;

	//// スコア更新したときに流す効果音
	//m_update_sound = LoadSoundMem("data/sound/effect/update.mp3");

	//// スコア更新の音を流すかを決める変数
	//m_sound = false;

	// BGMが流れているかを確認する変数
	// 最初は流れていない
	sound_change = true;

	// ボリューム設定
	ChangeVolumeSoundMem(150, m_bgm);
}

// -----------------
// 更新処理
// -----------------
void EasyPlay::Update()
{

	// 流す時間を決めるカウントを増やす
	m_bgm_count++;
	// bgmの再生
	// 一週目だけ流す
	if (sound_change == true) {
		PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP, TRUE);
	}
	// 二週目から繰り返さないようにする
	sound_change = false;
	

	if (m_bgm_count > 5400) {
		// BGMを停止
		StopSoundMem(m_bgm);
	}
	// MovePlayerの更新処理
	player.Update();

	//enemyの更新処理
	enemy.Update(EASY_TIME_MAX);
	
}


// -----------------
// 描画処理
// -----------------
void EasyPlay::Draw()
{
	// 背景画像の描画
	// 画面サイズに合わせて描画
	DrawExtendGraphF(0, 0, WINDOW_W, WINDOW_H, m_bak_image, TRUE);

	// Easyが呼ばれているかわかるように
	DrawString(m_pos.x, m_pos.y, "Easy", GetColor(255, 0, 0), TRUE);

	// 仮でポイントの描画
	DrawFormatString(500, 16, GetColor(255, 255, 255), "最高スコア：%3d", m_best_score);

	// enemyの描画
	enemy.PointDraw();
	enemy.Draw();

	// MovePlayerの描画処理
	player.Draw();

}

//======================================================================

// 最終ポイントを描画するための関数
void EasyPlay::PointDraw(Pos pos)
{
	// 文字の大きさを変える
	SetFontSize(30);

	// 最後でスコアの描画
	DrawFormatString(pos.x, pos.y, GetColor(255, 255, 255), "スコア：%3d", enemy.m_point);
		
	// m_best_score よりもスコアが高ければ
	// 最高スコアの書きこみ
	if (m_best_score < enemy.m_point) {
		// スコアの記録を更新したら描画
		DrawString(pos.x , pos.y - 80, "スコア更新！！", GetColor(255, 255, 255));
		DrawString(pos.x , pos.y - 40, "凄すぎる", GetColor(255, 255, 255));
		// スコアの書き込み
		TextWriteInEasy();
		/*m_sound = true;*/
	}

	//// スコア更新したときに流す効果音
	//if (m_sound == true) {
	//	// 効果音を再生
	//	PlaySoundMem(m_update_sound, DX_PLAYTYPE_BACK);
	//}

	// 文字の大きさを戻す
	SetFontSize(25);
}


// -----------------
// 終了処理
// -----------------
void EasyPlay::Exit()
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
