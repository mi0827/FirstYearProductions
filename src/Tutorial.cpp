#include "WinMain.h"
#include "Pos.h"
#include "Base.h"
#include "Enemy.h"
#include "MovePlayer.h"
#include "PlayBase.h"
#include "Tutorial.h"

// �v���C���[���������ʂ̃N���X
extern MovePlayer player;

// Enemy�N���X
extern Enemy enemy;

// ���̃V�[���ɍs�����߂̊֐�
bool Tutorial::IsChange()
{
	return change_;
}

void Tutorial::Init()
{
	// MovePlayer�̏����ݒ�
	player.Init();
	// enemy�̏�������
	// �`���[�g���A���ł͓������Ȃ�
	enemy.Init(0.0f);
	// �w�i�摜�̓ǂݍ���
	m_bak_image = LoadGraph("data/BG/pipo-bg001a.jpg");
	//  �ŏ���false
	change_ = false;

	// BGM�̓ǂݍ���
	m_bgm = LoadSoundMem("data/sound/tutoriarulbgm.mp3");

	// BGM������Ă��邩���m�F����ϐ�
	// �ŏ��͗���Ă��Ȃ�
	sound_change = true;

	// �{�����[���ݒ�
	ChangeVolumeSoundMem(150, m_bgm);
}

void Tutorial::Update()
{
	// bgm�̍Đ�
// ��T�ڂ�������
	if (sound_change == true) {
		PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP, TRUE);
	}
	// ��T�ڂ���J��Ԃ��Ȃ��悤�ɂ���
	sound_change = false;
	

	// MovePlayer�̍X�V����
	player.Update();

	//enemy�̍X�V����
	enemy.Update(3600);
	if (IsKeyOn(KEY_INPUT_SPACE)) {
		// BGM�̍Đ����~�߂�
		StopSoundMem(m_bgm);
		change_ = true;
	}
}

void Tutorial::Draw()
{
	// �w�i�摜�̕`��
	// ��ʃT�C�Y�ɍ��킹�ĕ`��
	DrawExtendGraphF(0, 0, WINDOW_W, WINDOW_H, m_bak_image, TRUE);


	enemy.Draw();

	player.Draw();

	// �����̑傫����ς���
	/*SetFontSize(40);
	DrawString(20, 20, "�`���[�g���A��", GetColor(0, 0, 0), FALSE);*/
	SetFontSize(25);
	// �S�V�b�N�̂ɕύX
	ChangeFont("�l�r �S�V�b�N��");
	DrawString(20, 2, "�}�E�X���g���Ă�������@���ă|�C���g���Q�b�g���悤�I�I", GetColor(0, 0, 0));
	DrawString(250, 425, "���������Ŗ��܂�܂łɂł��邾���|�����I", GetColor(255, 0, 0));

	// �����̂ɕύX
	ChangeFont("�l�r ����");
	DrawString(20, 425, "SKIP >> SPACE", GetColor(0, 0, 0));
	// �����̑傫����ς��� 

	SetFontSize(15);
	for (int i = 0; i < ENEMY_MAX; i++) {
		
		if (i == 0) {
			DrawString(enemy.m_enemy_pos[i].x, enemy.m_enemy_pos[i].y - 15, "�|�C���g������I�I", GetColor(250, 0, 0));
		}
		else if (i <= 2) {
			DrawString(enemy.m_enemy_pos[i].x, enemy.m_enemy_pos[i].y - 15, "�@���Ă�����I", GetColor(255, 0, 0));
		}
		else {
			DrawString(enemy.m_enemy_pos[i].x, enemy.m_enemy_pos[i].y - 15, "������̓_��", GetColor(255, 0, 0));
		}

	}
	// �����̑傫�������ɖ߂�
	SetFontSize(25);
}

void Tutorial::Exit()
{
	// Bgm�̍폜
	DeleteSoundMem(m_bgm);
	// MovePlayer�̏I������
	player.Exit();
	// enemy�̍폜
	enemy.Exit();

	// �w�i�摜�̍폜
	DeleteGraph(m_bak_image);
}


