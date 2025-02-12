
#include "WinMain.h"
#include "Base.h"
#include "Hit.h"
#include "ModeSelectScene.h"

ModeSelectScene::ModeSelectScene()
{

}

ModeSelectScene::~ModeSelectScene()
{

}

//-----------------------------
// 次のシーンに行くための関数たち
//-----------------------------
bool ModeSelectScene::IsChange()
{
	return change_;
}

bool ModeSelectScene::EasyChange()
{
	return m_easy_chande;
}

bool ModeSelectScene::NormalChange()
{
	return m_normal_chande;
}

bool ModeSelectScene::HardChange()
{
	return m_hard_chande;
}

//-----------------------
// 初期設定
//-----------------------
void ModeSelectScene::Init()
{
	// 各文字の変数
	m_pos[0].x = 325, m_pos[0].y = 100;
	m_pos[1].x = 325, m_pos[1].y = 200;
	m_pos[2].x = 325, m_pos[2].y = 300;

	// 各カラー用の変数
	for (int i = 0; i < end; ++i) {
		m_r[i] = 0;
		m_g[i] = 0;
		m_b[i] = 0;
	}

	// 十字キーでの三角の描画用変数
	m_check_count = 0;


	// 火の玉の描画用変数
	m_target.x = m_pos[m_check_count].x - 25;
	m_target.y = m_pos[m_check_count].y;

	// 背景画像の読み込み
	m_bak_image = LoadGraph("data/BG/pipo-bg002.jpg");

	// 槍画像の描画
	m_image = LoadGraph("data/Icon/icon004.png");

	// 火の玉画像の読み込み
	// enemyを配列で読み込むための変数
	char image[64];
	for (int i = 0; i < 3; i++) {
		sprintfDx(image, "data/Enemy/pipo-enemy0%d.png", i);
		m_target_image[i] = LoadGraph(image);
	}

	// 各難易度シーン、次のシーンに行く変数たち
	// 最初はfalse
	m_easy_chande = false;
	m_normal_chande = false;
	m_hard_chande = false;
	change_ = false;

	// BGMの読み込み
	m_bgm = LoadSoundMem("data/sound/modeselect.mp3");

	// ボタンを押したときに流す効果音
	m_button_sound = LoadSoundMem("data/sound/effect/decision1.mp3");

	// BGMが流れているかを確認する変数
	// 最初は流れていない
	sound_change = true;

	// ボリューム設定
	ChangeVolumeSoundMem(255, m_bgm);
	ChangeVolumeSoundMem(255, m_button_sound);
}

//-----------------------
// 更新処理
//-----------------------
void ModeSelectScene::Update()
{

	// bgmの再生
	// 一週目だけ流す
	if (sound_change == true) {
		PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP, TRUE);
	}
	// 二週目から繰り返さないようにする
	sound_change = false;


	// 変更した色をもとに戻す
	for (int i = 0; i < end; ++i) {
		m_r[i] = 0;
		m_g[i] = 0;
		m_b[i] = 0;
	}

	// マウス座標を取ってくる
	m_mouse_pos.x = GetMouseX();
	m_mouse_pos.y = GetMouseY();

	// 十字キーでも選択する
	if (IsKeyOn(KEY_INPUT_UP)) {
		m_check_count -= 1;
		if (m_check_count < 0) {
			m_check_count = 0;
		}
	}
	if (IsKeyOn(KEY_INPUT_DOWN)) {
		m_check_count += 1;
		if (m_check_count > 2) {
			m_check_count = 2;
		}
	}

	// マウス座標での当たり判定
	for (int i = 0; i < end; ++i) {          
		if (CheckPointBoxHit(m_mouse_pos.x, m_mouse_pos.y, m_pos[i].x, m_pos[i].y, 150, 40)) { // 文字の大きさに合わせてる
			m_check_count = i;
		}
	}

	// スペースキーで次に進む
	if (IsKeyOn(KEY_INPUT_SPACE)) {
		// 各難易度を選択したらそのクラスを呼ぶ
		if (m_check_count == 0) {
			m_easy_chande = true;
		}
		if (m_check_count == 1) {
			m_normal_chande = true;
		}
		if (m_check_count == 2) {
			m_hard_chande = true;
		}
		PlaySoundMem(m_button_sound, DX_PLAYTYPE_NORMAL);
		// BGMを停止
		StopSoundMem(m_bgm);
		change_ = true;
	}

	// マウスの左クリックでも次に進む
	if (IsMouseOn(MOUSE_INPUT_LEFT)) {

		// 各難易度を選択したらそのクラスを呼ぶ
		if (m_check_count == 0) {
			m_easy_chande = true;
		}
		if (m_check_count == 1) {
			m_normal_chande = true;
		}
		if (m_check_count == 2) {
			m_hard_chande = true;
		}
		PlaySoundMem(m_button_sound, DX_PLAYTYPE_NORMAL);
		// BGMを停止
		StopSoundMem(m_bgm);
		change_ = true;
	}
	// 火の玉の描画位置を変更
	m_target.x = m_pos[m_check_count].x - 70;
	m_target.y = m_pos[m_check_count].y - 10;

	// 色を変更
	m_r[m_check_count] = 0;
	m_g[m_check_count] = 255;
	m_b[m_check_count] = 255;
}

//-----------------------
// 描画処理
//-----------------------
void ModeSelectScene::Draw()
{
	// 背景画像の描画
	// 画面サイズに大きさを合わせて描画
	DrawExtendGraph(0, 0, WINDOW_W, WINDOW_H, m_bak_image, TRUE);

	DrawExtendGraphF(m_target.x, m_target.y, m_target.x + 70, m_target.y + 70, m_target_image[m_check_count], TRUE);
	// 各文字の描画
	// 文字の大きさを変える
	SetFontSize(50);
	for (int i = 0; i < end; ++i) {
		switch (i)
		{
		case EASY:
			DrawStringF(m_pos[i].x, m_pos[i].y, "EASY", GetColor(m_r[EASY], m_g[EASY], m_b[EASY]), true);
			break;
		case NORMAL:
			DrawStringF(m_pos[i].x, m_pos[i].y, "NORMAL", GetColor(m_r[NORMAL], m_g[NORMAL], m_b[NORMAL]), true);
			break;
		case HARD:
			DrawStringF(m_pos[i].x, m_pos[i].y, "HARD", GetColor(m_r[HARD], m_g[HARD], m_b[HARD]), true);
			break;
		}
	}
	// 文字の大きさを元に戻す
	SetFontSize(25);
	// 槍の描画
	// マウス座標に合わせて描画 
	DrawGraphF(m_mouse_pos.x, m_mouse_pos.y, m_image, TRUE);


}

void ModeSelectScene::Exit()
{

	// Bgmの削除
	DeleteSoundMem(m_bgm);
	// サウンドの削除
	DeleteSoundMem(m_button_sound);

	DeleteGraph(m_bak_image);
	DeleteGraph(m_image);
	for (int i = 0; i < end; i++) {
		DeleteGraph(m_target_image[i]);
	}
}
