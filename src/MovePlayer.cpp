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
// �����ݒ�
// --------------------
void MovePlayer::Init()
{
	// �~�̍��W�̏����ݒ�
	m_pos.x = WINDOW_W / 2;
	m_pos.y = WINDOW_H / 2;
	//m_pos.r = 10.0f; // ���o
	m_pos.w = 20.0f;
	m_pos.h = 20.0f;
	// �X�e�b�L�摜�̓ǂݍ���
	m_image = LoadGraph("data/Icon/icon006.png");

	
}


// --------------------
// �X�V����
// --------------------
void MovePlayer::Update()
{
	// �}�E�X���W�̎擾
	m_pos.x = GetMouseX();
	m_pos.y = GetMouseY();
	if (IsMouseOn(MOUSE_INPUT_LEFT)) {
		m_pos.x += 5;
		m_pos.y += 5;
	}
	// ������͈͂̐ݒ�
	if (m_pos.x > WINDOW_W - m_pos.w) m_pos.x = WINDOW_W - m_pos.w;
	if (m_pos.x < 0 + m_pos.w) m_pos.x = 0 + m_pos.w;
	if (m_pos.y > WINDOW_H - m_pos.h) m_pos.y = WINDOW_H - m_pos.h;
	if (m_pos.y < 0 + m_pos.h) m_pos.y = 0 + m_pos.h;

}

// --------------------
// �`�揈��
// --------------------
void MovePlayer::Draw()
{

	// �X�e�b�L�摜�̕`�� 
	DrawExtendGraphF(m_pos.x, m_pos.y, m_pos.x + 50, m_pos.y + 50, m_image, TRUE);
	

}

// --------------------
// �I������
// --------------------
void MovePlayer::Exit()
{

}
