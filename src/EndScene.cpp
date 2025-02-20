
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
#include "Endscene.h"

EndScene::EndScene()
{

}

EndScene::~EndScene()
{
}

extern PlayScene playscene;     // �v���C�V�[��


// ���̃V�[���ɍs�����߂̊֐�
bool EndScene::IsChange()
{
	return change_;
}


//-----------------------
// �����ݒ�
//-----------------------
void EndScene::Init()
{
	// �����̕`����W
	m_pos.x = 230;
	m_pos.y = 100;

	// �w�i�摜�̓ǂݍ���
	m_bak_image = LoadGraph("data/BG/pipo-bg003a.jpg");

	// �ŏ���false
	change_ = false;

	// �Ō�̉�ʂŕ`�悷�邽�߂̕ϐ�
	m_point_pos.x = 300;
	m_point_pos.y = 500;

	// BGM�̓ǂݍ���
	m_bgm = LoadSoundMem("data/sound/end.mp3");

	//// �X�R�A�X�V�����Ƃ��ɗ������ʉ�
	//m_update_sound = LoadSoundMem("data/sound/effect/update.mp3");

	//// �X�R�A�X�V�̉��𗬂��������߂�ϐ�
	//m_sound = false;

	// BGM������Ă��邩���m�F����ϐ�
	// �ŏ��͗���Ă��Ȃ�
	sound_change = true;

	// �{�����[���ݒ�
	ChangeVolumeSoundMem(255, m_bgm);
}


//-----------------------
// �X�V����
//-----------------------
void EndScene::Update()
{

	// bgm�̍Đ�
	// ��T�ڂ�������
	if (sound_change == true) {
		PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP, TRUE);
	}
	// ��T�ڂ���J��Ԃ��Ȃ��悤�ɂ���
	sound_change = false;
	
	/*ChangeVolumeSoundMem(100, m_update_sound);*/


	if (IsKeyOn(KEY_INPUT_SPACE)) {
		// BGM���~
		StopSoundMem(m_bgm);
		change_ = true;
	}

	// �Ō�̉�ʂŕ`�悷�邽�߂̕ϐ�
	m_point_pos.y--;
	// ��ʂ̐^�񒆂��炢�ɍs������~�߂�
	if (m_point_pos.y <= 270) {
		/*m_sound = true;*/
		m_point_pos.y = 270;
	}
//	if (m_sound == true) {
//		// ���ʉ����Đ�
//		PlaySoundMem(m_update_sound, DX_PLAYTYPE_BACK);
//	}
}

//-----------------------
// �`�揈��
//-----------------------
void EndScene::Draw()
{
	// ��ʃT�C�Y�ɍ��킹�Ĕw�i�摜�̕`��
	DrawExtendGraphF(0, 0, WINDOW_W, WINDOW_H, m_bak_image, TRUE);

	// �����̑傫����ς���
	SetFontSize(35);
	// �G���f�B���O�Ȃ̂��킩��悤��
	DrawStringF(m_pos.x- 20, m_pos.y, "�V��ł���Ă��肪�Ƃ� ", GetColor(255, 0, 0), TRUE);
	// �����̑傫����߂�
	SetFontSize(25);

	playscene.PointDraw(m_point_pos);

}

void EndScene::Exit()
{
	// Bgm�̍폜
	DeleteSoundMem(m_bgm);
	// �T�E���h�̍폜
	DeleteSoundMem(m_update_sound);
	DeleteGraph(m_bak_image);
}
