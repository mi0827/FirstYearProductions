
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
// ���̃V�[���ɍs�����߂̊֐�
//-----------------------------
bool Title::IsChange()
{
	return change_;
}

int m_image;
//-----------------------
// �����ݒ�
//-----------------------
void Title::Init()
{
	// �{�^���摜�̈ʒu�ɍ��킹�č��W�̐ݒ�
	m_pos.x = 250;
	m_pos.y = 250;

	// �{�^���������Ă���p�Ɍ����邽�߂̕ϐ�
	m_push.x = 0;
	m_push.y = 0;
	// �J�E���g�͂O�X�^�[�g
	m_push_count = 0;

	// �w�i���摜�̐ݒ�
	m_bak_image = LoadGraph("data/BG/pipo-battlebg010a.jpg");
	// �{�^���摜�̓ǂݍ���
	m_button_image = LoadGraph("data/icon142.png");

	// ���摜�̓ǂݍ���
	m_image = LoadGraph("data/Icon/icon002.png");

	// �ŏ���false
	change_ = false;

	// BGM�̓ǂݍ���
	m_bgm = LoadSoundMem("data/sound/titlebgm.mp3");

	// �{�^�����������Ƃ��ɗ������ʉ�
	m_button_sound = LoadSoundMem("data/sound/effect/decision0.mp3");

	// �{�����[���ݒ�
	ChangeVolumeSoundMem(255, m_bgm);
	ChangeVolumeSoundMem(255, m_button_sound);

	PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP);
	// BGM������Ă��邩���m�F����ϐ�
	// �ŏ��͗���Ă��Ȃ�
	sound_change = true;

}


//-----------------------
// �X�V����
//-----------------------
void Title::Update()
{
	// �J�E���g�𑫂�
	m_push_count++;

	// bgm�̍Đ�
	// ��T�ڂ�������
	if (sound_change == true) {
		PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP);
	}
	// ��T�ڂ���J��Ԃ��Ȃ��悤�ɂ���
	sound_change = false;	


	// �}�E�X���W������Ă���
	m_mouse_pos.x = GetMouseX();
	m_mouse_pos.y = GetMouseY();

	// �{�^���������Ă�悤�Ɍ����鏈��
	if (m_push_count > 0) {
		// �{�^���̍��W�����炷
		m_push.x = 5;
		m_push.y = 5;
	}
	if (m_push_count > 20) {
		//�{�^���̍��W�𒼂�
		m_push.x = 0;
		m_push.y = 0;
	}
	if (m_push_count > 40) {
		// �J�E���g�����Z�b�g
		m_push_count = 0;
	}

	// �X�y�[�X�L�[����������
	if (IsKeyOn(KEY_INPUT_SPACE)) {
		// ���ʉ����Đ�
		PlaySoundMem(m_button_sound, DX_PLAYTYPE_NORMAL);
		// BGM���~
		StopSoundMem(m_bgm);
		change_ = true;

	}

	// �}�E�X�̃N���b�N�ł��ł���悤��
	// �}�E�X�����N���b�N�����Ƃ�
	if (IsMouseOn(MOUSE_INPUT_LEFT)) {

		// �����蔻�肪�����
		// �}�E�X���W�̓_�ƃ{�^���̎l�p�̓����蔻��
		if (CheckPointBoxHit(m_mouse_pos.x, m_mouse_pos.y, m_pos.x, m_pos.y, 300, 100)) {
			// �J�E���g�𑝂₷
			// ���ʉ����Đ�
			PlaySoundMem(m_button_sound, DX_PLAYTYPE_NORMAL);
			// BGM���~
			StopSoundMem(m_bgm);
			change_ = true;

		}
	}

}


//-----------------------
// �`�揈��
//-----------------------
void Title::Draw()
{
	// �w�i�摜�̕`��
	// ��ʃT�C�Y�ɍ��킹�ĕ`��
	DrawExtendGraph(0, 0, WINDOW_W, WINDOW_H, m_bak_image, TRUE);


	// �^�C�g���̕`��

	SetFontSize(50);
	// �����̂ɕύX
	ChangeFont("�l�r ����");
	DrawString(m_pos.x - 80, m_pos.y - 150, "�S�[�X�g�E�n���^�[", GetColor(50, 100, 100), TRUE);
	DrawString(m_pos.x - 83, m_pos.y - 153, "�S�[�X�g�E�n���^�[", GetColor(255, 255, 0), TRUE);
	// ����Ō��ɖ߂�
	/*ChangeFont("�l�r �S�V�b�N��");*/
	// �����̑傫����ς���
	SetFontSize(25);
	// �������炢���L�[�̕`��(�T�C�Y��ύX����)
	DrawExtendGraph(m_pos.x + m_push.x, m_pos.y + m_push.y, m_pos.x + 300 + m_push.x, m_pos.y + 100 + m_push.y, m_button_image, TRUE);

	// �X�e�b�L�̕`��
	// �}�E�X���W�ɍ��킹��
	DrawExtendGraphF(m_mouse_pos.x, m_mouse_pos.y, m_mouse_pos.x + 50, m_mouse_pos.y + 50, m_image, TRUE);

	if (CheckSoundMem(m_button_sound)==true) {
		DrawString(16, 16, "a", GetColor(255, 255, 255), TRUE);
	}
}

void Title::Exit()
{
	// Bgm�̍폜
	DeleteSoundMem(m_bgm);
	// �T�E���h�̍폜
	DeleteSoundMem(m_button_sound);
	// �w�i�摜
	DeleteGraph(m_bak_image);
	// �{�^���摜
	DeleteGraph(m_button_image);
	// ���摜
	DeleteGraph(m_image);
}
