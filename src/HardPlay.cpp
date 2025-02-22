#include "WinMain.h"
#include "Pos.h"
#include "Base.h"
#include "Enemy.h"
#include "MovePlayer.h"
#include "PlayBase.h"
#include <fstream>
#include <string>
#include "HardPlay.h"
using namespace std;
HardPlay::HardPlay()
{

}

HardPlay::~HardPlay()
{

}

// プレイヤーが動かす玉のクラス

extern MovePlayer player;

// enemyクラス
extern Enemy enemy;

// textのHardScoreファイルの読み込み
int HardPlay::TextLoadingHrad()
{
	fstream file;
	// ファイルを開く
	file.open("text/HardScore.txt", ios::in);
	// ファイルが開けたかどうかののチェック
	if (!file.is_open()) {
		return EXIT_FAILURE;
	}
	// ファイルの操作、（読み込み）
	string str;
	file >> m_best_score;
	// ファイルを閉じる
	file.close();

}


// textのHardScoreファイルの書き込み
int HardPlay::TextWriteInHrad()
{
	fstream file;

	// ファイルを開く
	file.open("text/HardScore.txt", ios::out);
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
void HardPlay::Init()
{
	// Hradの文字の描画座標
	m_pos.x = 16;
	m_pos.y = 16;
	
	// 最初は０
	m_time_count = 0;
	// MovePlayerの初期設定
	player.Init();
	// enemyクラスの初期化
	// enemyにHard用のスピードを入れる
	enemy.Init(ENEMY_HARD_SPEED);
	// 背景画像の読み込み
	m_bak_image = LoadGraph("data/BG/pipo-bg004.jpg");


	// 最高スコアの読み込み
	TextLoadingHrad();

	// Hard画面でのｂｇｍを入れる変数
	m_bgm = LoadSoundMem("data/sound/hard.mp3");
	// 流す時間を決める変数
	m_bgm_count = 0;

	// BGMが流れているかを確認する変数
	// 最初は流れていない
	sound_change = true;

	// ボリューム設定
	ChangeVolumeSoundMem(255, m_bgm);
}

// -----------------
// 更新処理
// -----------------
void HardPlay::Update()
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
	

	if (m_bgm_count > PLAY_TIME_MAX) {
		// BGMを停止
		StopSoundMem(m_bgm);
	}

	// MovePlayerの更新処理
	player.Update();
	// enemyの更新処理
	enemy.Update(HARD_TIME_MAX);
}



// -----------------
// 描画処理
// -----------------
void HardPlay::Draw()
{
	// 背景画像の描画
	// 画面サイズに合わせて描画
	DrawExtendGraphF(0, 0, WINDOW_W, WINDOW_H, m_bak_image, TRUE);

	// ハードが呼ばれているかわかるように
	DrawString(m_pos.x, m_pos.y, "Hard", GetColor(255, 0, 0), TRUE);

	// 最高のポイントの描画
	DrawFormatString(500, 16, GetColor(255, 255, 255), "最高ポイント：%3d", m_best_score);

	// enemyの描画処理
	enemy.Draw();
	enemy.PointDraw();

	// MovePlayerの描画処理
	player.Draw();

}

// 最終ポイントを描画するための関数
void HardPlay::PointDraw(Pos pos)
{
	// 文字の大きさを変える
	SetFontSize(30);

	// 仮でポイントの描画
	DrawFormatString(pos.x, pos.y, GetColor(255, 255, 255), "ポイントは：%3d", enemy.m_point);
	
	// m_best_score よりもスコアが高ければ
	// 最高スコアの書きこみ
	if (m_best_score < enemy.m_point) {
		// スコアの記録を更新したら描画
		DrawString(pos.x, pos.y - 70, "スコア更新！！", GetColor(255, 255, 255));
		DrawString(pos.x, pos.y - 40, "凄すぎる", GetColor(255, 255, 255));
		// スコアの書き込み
		TextWriteInHrad();
	}

	// 文字の大きさを戻す
	SetFontSize(25);
}

// -----------------
// 終了処理
// -----------------
void HardPlay::Exit()
{
	// Bgmの削除
	DeleteSoundMem(m_bgm);
	// MovePlayerの終了処理
	player.Exit();
	// enemyの終了処理
	enemy.Exit();
	// 背景画像の削除
	DeleteGraph(m_bak_image);
}


