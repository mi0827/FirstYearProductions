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

// ��Փx�I��p�̃N���X
ModeSelectScene scene;

// �`���[�g���A���N���X
Tutorial tutorial;

// �e��Փx�Q�[���V�[���̃N���X�̓ǂݍ���
EasyPlay easyplay;
HardPlay hardplay;
NormalPlay normalplay;

// �v���C���[���������ʂ̃N���X
MovePlayer player;

// �e��Փx�N���X��extern MovePlayer player;���̌`�œǂ�ł���
// extern�����Ƃ����œǂ�ł���N���X���ق��̂Ƃ���œǂ�ł���
// Enemy�N���X
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
// �����ݒ�
// ---------------
void PlayScene::Init()
{
	// �e�N���X�̏�����

	// ��Փx�I��p�̃N���X
	scene.Init();

	// �v���C���[���������e�̃N���X
	player.Init();

	// �`���[�g���A���N���X
	tutorial.Init();

	// �ǂ̓�Փx�̃N���X��ǂݍ��ނ����f�p�̕ϐ�
	// �ŏ��͂O�ɂ��Ƃ�
	m_check_count = 0;

	// ��Փx�I���V�[����play�V�[�����𔻒f�Ɏg���ϐ�
	// �ŏ��͂O�ɂ��Ƃ�
	m_change_scene = 0;

	// �n�܂�܂ł̃J�E���g�͍ŏ��O�ɂ��Ă���
	m_start_count = 0;
	// �J�E���g�����邽�߂̕ϐ�
	// 3�b�Ȃ̂ōŏ��͂R�ɂ���
	m_change_count = 3;
	// �J�E���g��`�悷��ϐ�
	m_pos.x = WINDOW_W / 2;
	m_pos.y = WINDOW_H / 2;
	m_pos.r = 0; // ����͌����Ƃ��Ďg��

	// �������Ԃ����摜�ŕ`�悷�邽�߂̍��W�p�ϐ�
	// X���W�͂O�ŉ�ʒ[�ɂ���
	m_flame_pos.x = 0;

	// Y���W�͕`�悵���������ɐݒ�
	m_flame_pos.y = 390;

	// ���摜�����Ԍo�߂ŕ`��ʒu�����������Ă������߂̕ϐ�
	// �����W�𑝂₵�Ă����̂ōŏ��͂O���W�ɂ��Ă���
	m_flame_time_pos.x = 0;

	// �x���W�͌��炵����͂��Ȃ����`�悷�邽�߂�
	// ��ԉ��ɕ`�悵�������ߍŏ��͉�ʂ����ς��̍��W�ɂ��Ă���
	m_flame_time_pos.y = WINDOW_H;

	// ���摜�̓ǂݍ���
	// ����z��œǂݍ��ނ��߂̕ϐ�
	char image[64];
	for (int i = 0; i < FIAME_IMAGE_MAX; i++) {
		sprintfDx(image, "data/fiame/fiame%d.png", i);
		m_flame_image[i] = LoadGraph(image);
	}

	// ���摜���A�j���[�V�������邽�߂̕ϐ�
	// m_fiame_image[i]��i�̕����ɓ���
	m_animation_count = 0;

	// ��b�U�O�t���[���ƍl�������̏ꍇ
	// �ꕪ���͂T�S�O�O�t���[���Ȃ̂ł��ꊄ���ʒ[�̂����W�����ďo�����l������
	m_timelimit = WINDOW_W / 5400.0;

	// �w�i�摜�̓ǂݍ���
	m_bak_image = LoadGraph("data/BG/pipo-bg002.jpg");

	// �Q�[���̐�������
	// �ŏ��͂O�ɂ��Ă���
	// �i�K�𑝂₷
	m_game_count = 0;

	// �J�[�e���摜�̓ǂݍ���
	// �J����
	m_curtain_open_image = LoadGraph("data/curtain/open.png");
	// �����
	m_curtain_close_image = LoadGraph("data/curtain/close.png");

	// �J�[�e�����A�j���[�V���������邽�ߕϐ�
	m_curtain_count = 0;

	// �J�[�e���̕`����W
	m_curtain_pos.x = 100;
	m_curtain_pos.y = 0;

	// �J�[�e���摜���̂̍��W
	m_curtain_image_pos.x = 0;
	m_curtain_image_pos.y = 0;
	m_curtain_image_pos.w = 800;
	m_curtain_image_pos.h = 450;

	// �t���[���摜�̓ǂݍ���
	char frame_image[64];
	for (int i = 0; i < FRAME_IMSGE_MAX; i++) {
		sprintfDx(frame_image, "data/frame/frame%d.png", i);
		m_frame_image[i] = LoadGraph(frame_image);
	}
	// �t���[���摜�̕`����W
	for (int i = 0; i < FRAME_IMSGE_MAX; i++) {
		m_frame_pos[i].y = 12;
	}
	// x���W�͈���ݒ�
	m_frame_pos[0].x = 10;
	m_frame_pos[1].x = 130;
	m_frame_pos[2].x = 490;

	// �Q�[���V�[���ɐi�ޑO�ƒ��𕪂���ϐ�
	m_play = false;

	// �Q�[���V�[���̒��ƌ�𕪂���ϐ�
	m_play_end = false;

	// �Q�[���V�[���̐؂�ւ��p�ϐ�
	change_ = false;


}


// ---------------
// �X�V����
// ---------------
void PlayScene::Update()
{
	// �e�N���X�̍X�V����
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
		// ��Փx�I���V�[���ŌĂ΂ꂽ��Փx�ɒl��Ԃ�
		// �Ă΂ꂽ�Q�[���V�[���̃N���X�̏�������
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
		// �X�^�[�g�J�E���g�𑝂₷
		m_start_count++;
		if ((m_start_count % 60) == 0) {
			m_change_count--;
		}
		// �J�E���g���P�W�O�𒴂�����J�[�e���̏���������
		// �U�O�t���[���̏ꍇ�R�b
		if (m_start_count > 180) {
			if (m_start_count % 6 == 0) {
				// �J�[�e���̃A�j���[�V����
				m_curtain_image_pos.y += 450;
				m_curtain_image_pos.h = 450 + m_curtain_image_pos.y;
			}
		}
		// �J�E���g���Q�P�O�𒴂�����Q�[���V�[���̏���������
		// �J�[�e���̕`�悪�I���
		if (m_start_count > GAME_STRAT) {
			m_play = true;
		}

		// �Q�[���V�[���ɓ���
		if (m_play == true) {
			// �Q�[���̐������Ԃ𑝂₵�n�߂�
			m_game_count++;

			// ���̉摜�̕`���ʂ�傫�����Ă����i�����W�����j
			m_flame_time_pos.x += m_timelimit;

			// �v���C���[���������e�̃N���X�̍X�V����
			player.Update();

			// ��ŕԂ��ꂽ�l�ɂ���ē�Ղ��N���X���Ă�
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
			// �^�C�}�[���R�b���߂�����
			// 3�b�̏�ʂ̔w�i�摜��K�v�Ȃ��Ȃ����̂ō폜
			DeleteGraph(m_bak_image);

			// 10�t���[���Ɉ��m_animation_count�𑝂₷
			if (m_start_count % 10 == 0) {
				// ���摜���A�j���[�V�������邽�߂ɑ��₷
				m_animation_count++;
				// ���摜�̐���葽���Ȃ�����
				if (m_animation_count > FIAME_IMAGE_MAX - 1) {
					// �ŏ��̉摜�ɖ߂�悤�ɂO�ɂ���
					m_animation_count = 0;
				}
			}

			// �Q�[���̐����ɒB������G���h�V�[���ɍs��
			if (m_game_count > PLAY_TIME_MAX) {


				// �J�[�e���̃A�j���[�V����
				// �Đݒ�i����j�Ŏg������
				if (m_play_end == false) {
					m_curtain_image_pos.y = 0;
					m_curtain_image_pos.h = 450;
				}
				// �Q�[���V�[���̂��Ƃ̃J�[�e���̕`��
				m_play_end = true;
			}

		}
		if (m_play_end == true) {
			// �J�[�e���i����j�̃A�j���[�V�����p�J�E���g�𑝂₷
			m_curtain_count++;

			if (m_curtain_count % 10 == 0) {
				// �J�[�e���̃A�j���[�V����
				m_curtain_image_pos.y += 450;
				m_curtain_image_pos.h = 450 + m_curtain_image_pos.y;

			}
		}
		// �J�[�e���̉摜���~�߂�
		if (m_curtain_image_pos.h > 7200) {
			m_curtain_image_pos.y = 7200;
			m_curtain_image_pos.h = 450 + m_curtain_image_pos.y;

		}
		// �J�[�e���A�j���[�V���������������
		if (m_curtain_count > GAME_END) {
			// �G���h�N���X�ɍs�����߂̂���
			change_ = true;
		}


		//// ���ŃG���h�N���X�ɍs�����߂̂���
		//// ��X����
		//if (IsKeyOn(KEY_INPUT_SPACE)) {

		//	change_ = true;
		//}
	default:
		break;
	}
}

// ---------------
// �`�揈��
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

		// play�V�[���̑O�̕`��
		// �J�E���g(�^�C�}�[)�̕`��
		if (m_play == false) {
			// �t�H���g�̃T�C�Y��ύX
			SetFontSize(100);

			// �J�[�e��(�J��)�̕`��
			DrawRectGraphF(m_curtain_pos.x, m_curtain_pos.y, m_curtain_image_pos.x, m_curtain_image_pos.y, m_curtain_image_pos.w, m_curtain_image_pos.h, m_curtain_open_image, TRUE, TRUE);

			// �^�C�}�[�̕`��
			DrawFormatStringF(m_pos.x - 80, m_pos.y - 80, GetColor(255, 255, 255), " %d", m_change_count);
		}

		// �t�H���g�T�C�Y��߂�
		SetFontSize(24);

		// �J�E���g���P�W�O�𒴂����珈��������
		// �U�O�t���[���̏ꍇ�R�b
		// �Q�[���V�[���ɓ���
		if (m_play == true) {
			// �e�N���X�̕`�揈��
			switch (m_check_count)
			{
				// �`��X�^�C�T�C�Y�ɍ��킹��
					// �t���[���摜�̕`��
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

			// ���̕`��
			// �A�j���[�V��������
			DrawExtendGraphF(m_flame_pos.x, m_flame_pos.y, m_flame_time_pos.x, m_flame_time_pos.y, m_flame_image[m_animation_count], TRUE);

			// �v���C���[�̓������e�̕`��
			player.Draw();

		}

		if (m_play_end == true) {
			// �J�[�e��(����)�̕`��
			DrawRectGraphF(m_curtain_pos.x, m_curtain_pos.y, m_curtain_image_pos.x, m_curtain_image_pos.y, m_curtain_image_pos.w, m_curtain_image_pos.h, m_curtain_close_image, TRUE, TRUE);
			// �J�[�e���摜�̊Ԃ𖄂߂邽�߂�
			// ����
			DrawBox(0, 0, 100, 450, GetColor(0, 0, 0), TRUE);
			// �E��
			DrawBox(700, 0, 800, 450, GetColor(0, 0, 0), TRUE);
			// ����
			DrawBox(0, 430, 800, 450, GetColor(0, 0, 0), TRUE);
		}
		break;

	}
}

// �ŏI�|�C���g��`�悷�邽�߂̊֐�
void PlayScene::PointDraw(Pos pos)
{
	// �e�N���X�̕`�揈��
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
// �I������
// ---------------
void PlayScene::Exit()
{
	// �e�Q�[���V�[���̏I������
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
	// �w�i�摜
	DeleteGraph(m_bak_image);
	// �J�[�e���摜
	// �J��
	DeleteGraph(m_curtain_open_image);
	// ����
	DeleteGraph(m_curtain_close_image);
	// �������Ԃ̉��摜
	for (int i = 0; i < FIAME_IMAGE_MAX; i++) {
		DeleteGraph(m_flame_image[i]);
	}
}

