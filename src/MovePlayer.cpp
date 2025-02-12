#include "WinMain.h"
#include "Base.h"
#include "MovePlayer.h"

MovePlayer::MovePlayer()
{
}

MovePlayer::~MovePlayer()
{
}


// --------------------
// 初期設定
// --------------------
void MovePlayer::Init()
{
	// 円の座標の初期設定
	m_pos.x = WINDOW_W / 2;
	m_pos.y = WINDOW_H / 2;
	//m_pos.r = 10.0f; // 半経
	m_pos.w = 20.0f;
	m_pos.h = 20.0f;
	// ステッキ画像の読み込み
	m_image = LoadGraph("data/Icon/icon006.png");

	
}


// --------------------
// 更新処理
// --------------------
void MovePlayer::Update()
{
	// マウス座標の取得
	m_pos.x = GetMouseX();
	m_pos.y = GetMouseY();
	if (IsMouseOn(MOUSE_INPUT_LEFT)) {
		m_pos.x += 5;
		m_pos.y += 5;
	}
	// 動ける範囲の設定
	if (m_pos.x > WINDOW_W - m_pos.w) m_pos.x = WINDOW_W - m_pos.w;
	if (m_pos.x < 0 + m_pos.w) m_pos.x = 0 + m_pos.w;
	if (m_pos.y > WINDOW_H - m_pos.h) m_pos.y = WINDOW_H - m_pos.h;
	if (m_pos.y < 0 + m_pos.h) m_pos.y = 0 + m_pos.h;

}

// --------------------
// 描画処理
// --------------------
void MovePlayer::Draw()
{

	// ステッキ画像の描画 
	DrawExtendGraphF(m_pos.x, m_pos.y, m_pos.x + 50, m_pos.y + 50, m_image, TRUE);
	

}

// --------------------
// 終了処理
// --------------------
void MovePlayer::Exit()
{

}
