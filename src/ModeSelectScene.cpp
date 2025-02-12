
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
// ���̃V�[���ɍs�����߂̊֐�����
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
// �����ݒ�
//-----------------------
void ModeSelectScene::Init()
{
	// �e�����̕ϐ�
	m_pos[0].x = 325, m_pos[0].y = 100;
	m_pos[1].x = 325, m_pos[1].y = 200;
	m_pos[2].x = 325, m_pos[2].y = 300;

	// �e�J���[�p�̕ϐ�
	for (int i = 0; i < end; ++i) {
		m_r[i] = 0;
		m_g[i] = 0;
		m_b[i] = 0;
	}

	// �\���L�[�ł̎O�p�̕`��p�ϐ�
	m_check_count = 0;


	// �΂̋ʂ̕`��p�ϐ�
	m_target.x = m_pos[m_check_count].x - 25;
	m_target.y = m_pos[m_check_count].y;

	// �w�i�摜�̓ǂݍ���
	m_bak_image = LoadGraph("data/BG/pipo-bg002.jpg");

	// ���摜�̕`��
	m_image = LoadGraph("data/Icon/icon004.png");

	// �΂̋ʉ摜�̓ǂݍ���
	// enemy��z��œǂݍ��ނ��߂̕ϐ�
	char image[64];
	for (int i = 0; i < 3; i++) {
		sprintfDx(image, "data/Enemy/pipo-enemy0%d.png", i);
		m_target_image[i] = LoadGraph(image);
	}

	// �e��Փx�V�[���A���̃V�[���ɍs���ϐ�����
	// �ŏ���false
	m_easy_chande = false;
	m_normal_chande = false;
	m_hard_chande = false;
	change_ = false;

	// BGM�̓ǂݍ���
	m_bgm = LoadSoundMem("data/sound/modeselect.mp3");

	// �{�^�����������Ƃ��ɗ������ʉ�
	m_button_sound = LoadSoundMem("data/sound/effect/decision1.mp3");

	// BGM������Ă��邩���m�F����ϐ�
	// �ŏ��͗���Ă��Ȃ�
	sound_change = true;

	// �{�����[���ݒ�
	ChangeVolumeSoundMem(255, m_bgm);
	ChangeVolumeSoundMem(255, m_button_sound);
}

//-----------------------
// �X�V����
//-----------------------
void ModeSelectScene::Update()
{

	// bgm�̍Đ�
	// ��T�ڂ�������
	if (sound_change == true) {
		PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP, TRUE);
	}
	// ��T�ڂ���J��Ԃ��Ȃ��悤�ɂ���
	sound_change = false;


	// �ύX�����F�����Ƃɖ߂�
	for (int i = 0; i < end; ++i) {
		m_r[i] = 0;
		m_g[i] = 0;
		m_b[i] = 0;
	}

	// �}�E�X���W������Ă���
	m_mouse_pos.x = GetMouseX();
	m_mouse_pos.y = GetMouseY();

	// �\���L�[�ł��I������
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

	// �}�E�X���W�ł̓����蔻��
	for (int i = 0; i < end; ++i) {          
		if (CheckPointBoxHit(m_mouse_pos.x, m_mouse_pos.y, m_pos[i].x, m_pos[i].y, 150, 40)) { // �����̑傫���ɍ��킹�Ă�
			m_check_count = i;
		}
	}

	// �X�y�[�X�L�[�Ŏ��ɐi��
	if (IsKeyOn(KEY_INPUT_SPACE)) {
		// �e��Փx��I�������炻�̃N���X���Ă�
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
		// BGM���~
		StopSoundMem(m_bgm);
		change_ = true;
	}

	// �}�E�X�̍��N���b�N�ł����ɐi��
	if (IsMouseOn(MOUSE_INPUT_LEFT)) {

		// �e��Փx��I�������炻�̃N���X���Ă�
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
		// BGM���~
		StopSoundMem(m_bgm);
		change_ = true;
	}
	// �΂̋ʂ̕`��ʒu��ύX
	m_target.x = m_pos[m_check_count].x - 70;
	m_target.y = m_pos[m_check_count].y - 10;

	// �F��ύX
	m_r[m_check_count] = 0;
	m_g[m_check_count] = 255;
	m_b[m_check_count] = 255;
}

//-----------------------
// �`�揈��
//-----------------------
void ModeSelectScene::Draw()
{
	// �w�i�摜�̕`��
	// ��ʃT�C�Y�ɑ傫�������킹�ĕ`��
	DrawExtendGraph(0, 0, WINDOW_W, WINDOW_H, m_bak_image, TRUE);

	DrawExtendGraphF(m_target.x, m_target.y, m_target.x + 70, m_target.y + 70, m_target_image[m_check_count], TRUE);
	// �e�����̕`��
	// �����̑傫����ς���
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
	// �����̑傫�������ɖ߂�
	SetFontSize(25);
	// ���̕`��
	// �}�E�X���W�ɍ��킹�ĕ`�� 
	DrawGraphF(m_mouse_pos.x, m_mouse_pos.y, m_image, TRUE);


}

void ModeSelectScene::Exit()
{

	// Bgm�̍폜
	DeleteSoundMem(m_bgm);
	// �T�E���h�̍폜
	DeleteSoundMem(m_button_sound);

	DeleteGraph(m_bak_image);
	DeleteGraph(m_image);
	for (int i = 0; i < end; i++) {
		DeleteGraph(m_target_image[i]);
	}
}
