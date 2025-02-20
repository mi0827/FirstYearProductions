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

// 難易度選択用のクラス
ModeSelectScene scene;

// チュートリアルクラス
Tutorial tutorial;

// 各難易度ゲームシーンのクラスの読み込み
EasyPlay easyplay;
HardPlay hardplay;
NormalPlay normalplay;

// プレイヤーが動かす玉のクラス
MovePlayer player;

// 各難易度クラスでextern MovePlayer player;この形で読んでいる
// externがつくとここで読んでいるクラスをほかのところで読んでいる
// Enemyクラス
Enemy enemy;

PlayScene::PlayScene()
{

}

PlayScene::~PlayScene()
{

}

bool PlayScene::IsChange()
{
	return change_;
}



// ---------------
// 初期設定
// ---------------
void PlayScene::Init()
{
	// 各クラスの初期化

	// 難易度選択用のクラス
	scene.Init();

	// プレイヤーが動かす弾のクラス
	player.Init();

	// チュートリアルクラス
	tutorial.Init();

	// どの難易度のクラスを読み込むか判断用の変数
	// 最初は０にしとく
	m_check_count = 0;

	// 難易度選択シーンかplayシーン化を判断に使う変数
	// 最初は０にしとく
	m_change_scene = 0;

	// 始まるまでのカウントは最初０にしておく
	m_start_count = 0;
	// カウントが見るための変数
	// 3秒なので最初は３にする
	m_change_count = 3;
	// カウントを描画する変数
	m_pos.x = WINDOW_W / 2;
	m_pos.y = WINDOW_H / 2;
	m_pos.r = 0; // 今回は向きとして使う

	// 制限時間を炎画像で描画するための座標用変数
	// X座標は０で画面端にする
	m_flame_pos.x = 0;

	// Y座標は描画したい高さに設定
	m_flame_pos.y = 390;

	// 炎画像を時間経過で描画位置を小さくしていくための変数
	// ｘ座標を増やしていくので最初は０座標にしておく
	m_flame_time_pos.x = 0;

	// Ｙ座標は減らしたりはしないが描画するために
	// 一番下に描画したいため最初は画面いっぱいの座標にしておく
	m_flame_time_pos.y = WINDOW_H;

	// 炎画像の読み込み
	// 炎を配列で読み込むための変数
	char image[64];
	for (int i = 0; i < FIAME_IMAGE_MAX; i++) {
		sprintfDx(image, "data/fiame/fiame%d.png", i);
		m_flame_image[i] = LoadGraph(image);
	}

	// 炎画像をアニメーションするための変数
	// m_fiame_image[i]のiの部分に入る
	m_animation_count = 0;

	// 一秒６０フレームと考えた時の場合
	// 一分半は５４００フレームなのでそれ割る画面端のｘ座標をして出た数値を入れる
	m_timelimit = WINDOW_W / 5400.0;

	// 背景画像の読み込み
	m_bak_image = LoadGraph("data/BG/pipo-bg002.jpg");

	// ゲームの制限時間
	// 最初は０にしておく
	// 段階を増やす
	m_game_count = 0;

	// カーテン画像の読み込み
	// 開く方
	m_curtain_open_image = LoadGraph("data/curtain/open.png");
	// 閉じる方
	m_curtain_close_image = LoadGraph("data/curtain/close.png");

	// カーテンをアニメーションさせるため変数
	m_curtain_count = 0;

	// カーテンの描画座標
	m_curtain_pos.x = 100;
	m_curtain_pos.y = 0;

	// カーテン画像自体の座標
	m_curtain_image_pos.x = 0;
	m_curtain_image_pos.y = 0;
	m_curtain_image_pos.w = 800;
	m_curtain_image_pos.h = 450;

	// フレーム画像の読み込み
	char frame_image[64];
	for (int i = 0; i < FRAME_IMSGE_MAX; i++) {
		sprintfDx(frame_image, "data/frame/frame%d.png", i);
		m_frame_image[i] = LoadGraph(frame_image);
	}
	// フレーム画像の描画座標
	for (int i = 0; i < FRAME_IMSGE_MAX; i++) {
		m_frame_pos[i].y = 12;
	}
	// x座標は一つずつ設定
	m_frame_pos[0].x = 10;
	m_frame_pos[1].x = 130;
	m_frame_pos[2].x = 490;

	// ゲームシーンに進む前と中を分ける変数
	m_play = false;

	// ゲームシーンの中と後を分ける変数
	m_play_end = false;

	// ゲームシーンの切り替え用変数
	change_ = false;


}


// ---------------
// 更新処理
// ---------------
void PlayScene::Update()
{
	// 各クラスの更新処理
	switch (m_change_scene)
	{
	case TUTORIAL:
		tutorial.Update();
		if (tutorial.IsChange()) {
			m_change_scene = 1;
		}
		break;
	case SELECT:

		tutorial.Exit();
		// 難易度選択シーンで呼ばれた難易度に値を返す
		// 呼ばれたゲームシーンのクラスの初期処理
		scene.Update();
		if (scene.EasyChange()) {
			easyplay.Init();
			m_check_count = 0;
		}
		if (scene.NormalChange()) {
			normalplay.Init();
			m_check_count = 1;
		}
		if (scene.HardChange()) {
			hardplay.Init();
			m_check_count = 2;
		}
		if (scene.IsChange()) {
			m_change_scene = 2;
		}
		break;

	case PLAY:
		// スタートカウントを増やす
		m_start_count++;
		if ((m_start_count % 60) == 0) {
			m_change_count--;
		}
		// カウントが１８０を超えたらカーテンの処理をする
		// ６０フレームの場合３秒
		if (m_start_count > 180) {
			if (m_start_count % 6 == 0) {
				// カーテンのアニメーション
				m_curtain_image_pos.y += 450;
				m_curtain_image_pos.h = 450 + m_curtain_image_pos.y;
			}
		}
		// カウントが２１０を超えたらゲームシーンの処理をする
		// カーテンの描画が終わる
		if (m_start_count > GAME_STRAT) {
			m_play = true;
		}

		// ゲームシーンに入る
		if (m_play == true) {
			// ゲームの制限時間を増やし始める
			m_game_count++;

			// 炎の画像の描画画面を大きくしていく（ｘ座標だけ）
			m_flame_time_pos.x += m_timelimit;

			// プレイヤーが動かす弾のクラスの更新処理
			player.Update();

			// 上で返された値によって難易をクラスを呼ぶ
			switch (m_check_count)
			{
			case EASY:
				easyplay.Update();
				break;
			case NORMAL:
				normalplay.Update();
				break;
			case HARD:
				hardplay.Update();
				break;
			}
			// タイマーが３秒を過ぎたら
			// 3秒の場面の背景画像を必要なくなったので削除
			DeleteGraph(m_bak_image);

			// 10フレームに一回m_animation_countを増やす
			if (m_start_count % 10 == 0) {
				// 炎画像をアニメーションするために増やす
				m_animation_count++;
				// 炎画像の数より多くなったら
				if (m_animation_count > FIAME_IMAGE_MAX - 1) {
					// 最初の画像に戻るように０にする
					m_animation_count = 0;
				}
			}

			// ゲームの制限に達したらエンドシーンに行く
			if (m_game_count > PLAY_TIME_MAX) {


				// カーテンのアニメーション
				// 再設定（閉じる）で使うため
				if (m_play_end == false) {
					m_curtain_image_pos.y = 0;
					m_curtain_image_pos.h = 450;
				}
				// ゲームシーンのあとのカーテンの描画
				m_play_end = true;
			}

		}
		if (m_play_end == true) {
			// カーテン（閉じる）のアニメーション用カウントを増やす
			m_curtain_count++;

			if (m_curtain_count % 10 == 0) {
				// カーテンのアニメーション
				m_curtain_image_pos.y += 450;
				m_curtain_image_pos.h = 450 + m_curtain_image_pos.y;

			}
		}
		// カーテンの画像を止める
		if (m_curtain_image_pos.h > 7200) {
			m_curtain_image_pos.y = 7200;
			m_curtain_image_pos.h = 450 + m_curtain_image_pos.y;

		}
		// カーテンアニメーションが一周したら
		if (m_curtain_count > GAME_END) {
			// エンドクラスに行くためのもの
			change_ = true;
		}


		//// 仮でエンドクラスに行くためのもの
		//// 後々消す
		//if (IsKeyOn(KEY_INPUT_SPACE)) {

		//	change_ = true;
		//}
	default:
		break;
	}
}

// ---------------
// 描画処理
// ---------------
void PlayScene::Draw()
{
	switch (m_change_scene)
	{
	case TUTORIAL:
		tutorial.Draw();
		break;

	case SELECT:
		scene.Draw();
		break;
	case PLAY:

		// playシーンの前の描画
		// カウント(タイマー)の描画
		if (m_play == false) {
			// フォントのサイズを変更
			SetFontSize(100);

			// カーテン(開く)の描画
			DrawRectGraphF(m_curtain_pos.x, m_curtain_pos.y, m_curtain_image_pos.x, m_curtain_image_pos.y, m_curtain_image_pos.w, m_curtain_image_pos.h, m_curtain_open_image, TRUE, TRUE);

			// タイマーの描画
			DrawFormatStringF(m_pos.x - 80, m_pos.y - 80, GetColor(255, 255, 255), " %d", m_change_count);
		}

		// フォントサイズを戻す
		SetFontSize(24);

		// カウントが１８０を超えたら処理をする
		// ６０フレームの場合３秒
		// ゲームシーンに入る
		if (m_play == true) {
			// 各クラスの描画処理
			switch (m_check_count)
			{
				// 描画スタイサイズに合わせる
					// フレーム画像の描画
			case EASY:
				easyplay.Draw();
				DrawExtendGraph(m_frame_pos[0].x, m_frame_pos[0].y, m_frame_pos[0].x + 70, m_frame_pos[0].y + 30, m_frame_image[0], TRUE);
				DrawExtendGraph(m_frame_pos[1].x, m_frame_pos[1].y, m_frame_pos[1].x + 310, m_frame_pos[1].y + 30, m_frame_image[1], TRUE);
				DrawExtendGraph(m_frame_pos[2].x, m_frame_pos[2].y, m_frame_pos[2].x + 250, m_frame_pos[2].y + 30, m_frame_image[2], TRUE);
				break;
			case NORMAL:
				normalplay.Draw();
				DrawExtendGraph(m_frame_pos[0].x, m_frame_pos[0].y, m_frame_pos[0].x + 100, m_frame_pos[0].y + 30, m_frame_image[0], TRUE);
				DrawExtendGraph(m_frame_pos[1].x, m_frame_pos[1].y, m_frame_pos[1].x + 320, m_frame_pos[1].y + 30, m_frame_image[1], TRUE);
				DrawExtendGraph(m_frame_pos[2].x, m_frame_pos[2].y, m_frame_pos[2].x + 270, m_frame_pos[2].y + 30, m_frame_image[2], TRUE);
				break;
			case HARD:
				hardplay.Draw();
				DrawExtendGraph(m_frame_pos[0].x, m_frame_pos[0].y, m_frame_pos[0].x + 70, m_frame_pos[0].y + 30, m_frame_image[0], TRUE);
				DrawExtendGraph(m_frame_pos[1].x, m_frame_pos[1].y, m_frame_pos[1].x + 320, m_frame_pos[1].y + 30, m_frame_image[1], TRUE);
				DrawExtendGraph(m_frame_pos[2].x, m_frame_pos[2].y, m_frame_pos[2].x + 270, m_frame_pos[2].y + 30, m_frame_image[2], TRUE);
				break;
			}

			// 炎の描画
			// アニメーションする
			DrawExtendGraphF(m_flame_pos.x, m_flame_pos.y, m_flame_time_pos.x, m_flame_time_pos.y, m_flame_image[m_animation_count], TRUE);

			// プレイヤーの動かす弾の描画
			player.Draw();

		}

		if (m_play_end == true) {
			// カーテン(閉じる)の描画
			DrawRectGraphF(m_curtain_pos.x, m_curtain_pos.y, m_curtain_image_pos.x, m_curtain_image_pos.y, m_curtain_image_pos.w, m_curtain_image_pos.h, m_curtain_close_image, TRUE, TRUE);
			// カーテン画像の間を埋めるための
			// 左側
			DrawBox(0, 0, 100, 450, GetColor(0, 0, 0), TRUE);
			// 右側
			DrawBox(700, 0, 800, 450, GetColor(0, 0, 0), TRUE);
			// 下側
			DrawBox(0, 430, 800, 450, GetColor(0, 0, 0), TRUE);
		}
		break;

	}
}

// 最終ポイントを描画するための関数
void PlayScene::PointDraw(Pos pos)
{
	// 各クラスの描画処理
	switch (m_check_count)
	{
	case EASY:
		easyplay.PointDraw(pos);
		break;
	case NORMAL:
		normalplay.PointDraw(pos);
		break;
	case HARD:
		hardplay.PointDraw(pos);
		break;
	}
}

// ---------------
// 終了処理
// ---------------
void PlayScene::Exit()
{
	// 各ゲームシーンの終了処理
	switch (m_check_count)
	{
	case EASY:
		easyplay.Exit();
		break;
	case NORMAL:
		normalplay.Exit();
		break;
	case HARD:
		hardplay.Exit();
		break;
	}
	scene.Exit();
	player.Exit();
	tutorial.Exit();
	// 背景画像
	DeleteGraph(m_bak_image);
	// カーテン画像
	// 開く
	DeleteGraph(m_curtain_open_image);
	// 閉じる
	DeleteGraph(m_curtain_close_image);
	// 制限時間の炎画像
	for (int i = 0; i < FIAME_IMAGE_MAX; i++) {
		DeleteGraph(m_flame_image[i]);
	}
}

