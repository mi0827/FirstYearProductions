#include "WinMain.h"
#include "Pos.h"
#include "Base.h"
#include "Enemy.h"
#include "MovePlayer.h"
#include "PlayBase.h"
#include <fstream>
#include <string>
#include "HardPlay.h"
using namespace std;
HardPlay::HardPlay()
{

}

HardPlay::~HardPlay()
{

}

// �v���C���[���������ʂ̃N���X

extern MovePlayer player;

// enemy�N���X
extern Enemy enemy;

// text��HardScore�t�@�C���̓ǂݍ���
int HardPlay::TextLoadingHrad()
{
	fstream file;
	// �t�@�C�����J��
	file.open("text/HardScore.txt", ios::in);
	// �t�@�C�����J�������ǂ����̂̃`�F�b�N
	if (!file.is_open()) {
		return EXIT_FAILURE;
	}
	// �t�@�C���̑���A�i�ǂݍ��݁j
	string str;
	file >> m_best_score;
	// �t�@�C�������
	file.close();

}


// text��HardScore�t�@�C���̏�������
int HardPlay::TextWriteInHrad()
{
	fstream file;

	// �t�@�C�����J��
	file.open("text/HardScore.txt", ios::out);
	// �t�@�C�����J�������ǂ����̂̃`�F�b�N
	if (!file.is_open()) {
		return EXIT_FAILURE;
	}
	// �t�@�C���̑���A�i�������݁j

	num = enemy.m_point;
	file << num << endl;
	// �t�@�C�������
	file.close();
}


// -----------------
// ��������
// -----------------
void HardPlay::Init()
{
	// Hrad�̕����̕`����W
	m_pos.x = 16;
	m_pos.y = 16;
	
	// �ŏ��͂O
	m_time_count = 0;
	// MovePlayer�̏����ݒ�
	player.Init();
	// enemy�N���X�̏�����
	// enemy��Hard�p�̃X�s�[�h������
	enemy.Init(ENEMY_HARD_SPEED);
	// �w�i�摜�̓ǂݍ���
	m_bak_image = LoadGraph("data/BG/pipo-bg004.jpg");


	// �ō��X�R�A�̓ǂݍ���
	TextLoadingHrad();

	// Hard��ʂł̂�����������ϐ�
	m_bgm = LoadSoundMem("data/sound/hard.mp3");
	// �������Ԃ����߂�ϐ�
	m_bgm_count = 0;

	// BGM������Ă��邩���m�F����ϐ�
	// �ŏ��͗���Ă��Ȃ�
	sound_change = true;

	// �{�����[���ݒ�
	ChangeVolumeSoundMem(255, m_bgm);
}

// -----------------
// �X�V����
// -----------------
void HardPlay::Update()
{
	// �������Ԃ����߂�J�E���g�𑝂₷
	m_bgm_count++;
	// bgm�̍Đ�
	// ��T�ڂ�������
	if (sound_change == true) {
		PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP, TRUE);
	}
	// ��T�ڂ���J��Ԃ��Ȃ��悤�ɂ���
	sound_change = false;
	

	if (m_bgm_count > PLAY_TIME_MAX) {
		// BGM���~
		StopSoundMem(m_bgm);
	}

	// MovePlayer�̍X�V����
	player.Update();
	// enemy�̍X�V����
	enemy.Update(HARD_TIME_MAX);
}



// -----------------
// �`�揈��
// -----------------
void HardPlay::Draw()
{
	// �w�i�摜�̕`��
	// ��ʃT�C�Y�ɍ��킹�ĕ`��
	DrawExtendGraphF(0, 0, WINDOW_W, WINDOW_H, m_bak_image, TRUE);

	// �n�[�h���Ă΂�Ă��邩�킩��悤��
	DrawString(m_pos.x, m_pos.y, "Hard", GetColor(255, 0, 0), TRUE);

	// �ō��̃|�C���g�̕`��
	DrawFormatString(500, 16, GetColor(255, 255, 255), "�ō��|�C���g�F%3d", m_best_score);

	// enemy�̕`�揈��
	enemy.Draw();
	enemy.PointDraw();

	// MovePlayer�̕`�揈��
	player.Draw();

}

// �ŏI�|�C���g��`�悷�邽�߂̊֐�
void HardPlay::PointDraw(Pos pos)
{
	// �����̑傫����ς���
	SetFontSize(30);

	// ���Ń|�C���g�̕`��
	DrawFormatString(pos.x, pos.y, GetColor(255, 255, 255), "�|�C���g�́F%3d", enemy.m_point);
	
	// m_best_score �����X�R�A���������
	// �ō��X�R�A�̏�������
	if (m_best_score < enemy.m_point) {
		// �X�R�A�̋L�^���X�V������`��
		DrawString(pos.x, pos.y - 70, "�X�R�A�X�V�I�I", GetColor(255, 255, 255));
		DrawString(pos.x, pos.y - 40, "��������", GetColor(255, 255, 255));
		// �X�R�A�̏�������
		TextWriteInHrad();
	}

	// �����̑傫����߂�
	SetFontSize(25);
}

// -----------------
// �I������
// -----------------
void HardPlay::Exit()
{
	// Bgm�̍폜
	DeleteSoundMem(m_bgm);
	// MovePlayer�̏I������
	player.Exit();
	// enemy�̏I������
	enemy.Exit();
	// �w�i�摜�̍폜
	DeleteGraph(m_bak_image);
}


