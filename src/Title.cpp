
#include "WinMain.h"
#include "Base.h"
#include "Hit.h"
#include "Title.h"

Title::Title()
{
}

Title::~Title()
{
}
//-----------------------------
// 次のシーンに行くための関数
//-----------------------------
bool Title::IsChange()
{
	return change_;
}

int m_image;
//-----------------------
// 初期設定
//-----------------------
void Title::Init()
{
	// ボタン画像の位置に合わせて座標の設定
	m_pos.x = 250;
	m_pos.y = 250;

	// ボタンを押している用に見せるための変数
	m_push.x = 0;
	m_push.y = 0;
	// カウントは０スタート
	m_push_count = 0;

	// 背景が画像の設定
	m_bak_image = LoadGraph("data/BG/pipo-battlebg010a.jpg");
	// ボタン画像の読み込み
	m_button_image = LoadGraph("data/icon142.png");

	// 剣画像の読み込み
	m_image = LoadGraph("data/Icon/icon002.png");

	// 最初はfalse
	change_ = false;

	// BGMの読み込み
	m_bgm = LoadSoundMem("data/sound/titlebgm.mp3");

	// ボタンを押したときに流す効果音
	m_button_sound = LoadSoundMem("data/sound/effect/decision0.mp3");

	// ボリューム設定
	ChangeVolumeSoundMem(255, m_bgm);
	ChangeVolumeSoundMem(255, m_button_sound);

	PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP);
	// BGMが流れているかを確認する変数
	// 最初は流れていない
	sound_change = true;

}


//-----------------------
// 更新処理
//-----------------------
void Title::Update()
{
	// カウントを足す
	m_push_count++;

	// bgmの再生
	// 一週目だけ流す
	if (sound_change == true) {
		PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP);
	}
	// 二週目から繰り返さないようにする
	sound_change = false;	


	// マウス座標を取ってくる
	m_mouse_pos.x = GetMouseX();
	m_mouse_pos.y = GetMouseY();

	// ボタンを押してるように見える処理
	if (m_push_count > 0) {
		// ボタンの座標をずらす
		m_push.x = 5;
		m_push.y = 5;
	}
	if (m_push_count > 20) {
		//ボタンの座標を直す
		m_push.x = 0;
		m_push.y = 0;
	}
	if (m_push_count > 40) {
		// カウントをリセット
		m_push_count = 0;
	}

	// スペースキーを押したら
	if (IsKeyOn(KEY_INPUT_SPACE)) {
		// 効果音を再生
		PlaySoundMem(m_button_sound, DX_PLAYTYPE_NORMAL);
		// BGMを停止
		StopSoundMem(m_bgm);
		change_ = true;

	}

	// マウスのクリックでもできるように
	// マウスを左クリックしたとき
	if (IsMouseOn(MOUSE_INPUT_LEFT)) {

		// 当たり判定があれば
		// マウス座標の点とボタンの四角の当たり判定
		if (CheckPointBoxHit(m_mouse_pos.x, m_mouse_pos.y, m_pos.x, m_pos.y, 300, 100)) {
			// カウントを増やす
			// 効果音を再生
			PlaySoundMem(m_button_sound, DX_PLAYTYPE_NORMAL);
			// BGMを停止
			StopSoundMem(m_bgm);
			change_ = true;

		}
	}

}


//-----------------------
// 描画処理
//-----------------------
void Title::Draw()
{
	// 背景画像の描画
	// 画面サイズに合わせて描画
	DrawExtendGraph(0, 0, WINDOW_W, WINDOW_H, m_bak_image, TRUE);


	// タイトルの描画

	SetFontSize(50);
	// 明朝体に変更
	ChangeFont("ＭＳ 明朝");
	DrawString(m_pos.x - 80, m_pos.y - 150, "ゴースト・ハンター", GetColor(50, 100, 100), TRUE);
	DrawString(m_pos.x - 83, m_pos.y - 153, "ゴースト・ハンター", GetColor(255, 255, 0), TRUE);
	// これで元に戻す
	/*ChangeFont("ＭＳ ゴシック体");*/
	// 文字の大きさを変える
	SetFontSize(25);
	// 押したらいいキーの描画(サイズを変更する)
	DrawExtendGraph(m_pos.x + m_push.x, m_pos.y + m_push.y, m_pos.x + 300 + m_push.x, m_pos.y + 100 + m_push.y, m_button_image, TRUE);

	// ステッキの描画
	// マウス座標に合わせる
	DrawExtendGraphF(m_mouse_pos.x, m_mouse_pos.y, m_mouse_pos.x + 50, m_mouse_pos.y + 50, m_image, TRUE);

	if (CheckSoundMem(m_button_sound)==true) {
		DrawString(16, 16, "a", GetColor(255, 255, 255), TRUE);
	}
}

void Title::Exit()
{
	// Bgmの削除
	DeleteSoundMem(m_bgm);
	// サウンドの削除
	DeleteSoundMem(m_button_sound);
	// 背景画像
	DeleteGraph(m_bak_image);
	// ボタン画像
	DeleteGraph(m_button_image);
	// 剣画像
	DeleteGraph(m_image);
}
