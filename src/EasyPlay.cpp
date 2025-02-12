#include "WinMain.h"
#include "Pos.h"
#include "Base.h"
#include "Enemy.h"
#include "MovePlayer.h"
#include "PlayBase.h"
#include <fstream>
#include <string>
#include "EasyPlay.h"
using namespace std;


// �v���C���[���������ʂ̃N���X
extern MovePlayer player;

// Enemy�N���X
extern Enemy enemy;


EasyPlay::EasyPlay()
{

}


EasyPlay::~EasyPlay()
{

}
// Text��EasyScore�t�@�C���̓ǂݍ���
int EasyPlay::TextLoadingEasy()
{

	fstream file;
	// �t�@�C�����J��
	file.open("text/EasyScore.txt", ios::in);
	// �t�@�C�����J�������ǂ����̂̃`�F�b�N
	if (!file.is_open()) {
		return EXIT_FAILURE;
	}
	// �t�@�C���̑���A�i�ǂݍ��݁j
	file >> m_best_score;
	// �t�@�C�������
	file.close();
}

// Text��tEasyScore�t�@�C���ւ̏�������
int  EasyPlay::TextWriteInEasy()
{
	fstream file;

	// �t�@�C�����J��
	file.open("text/EasyScore.txt", ios::out);
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
void EasyPlay::Init()
{
	// Easy�̕����̕`����W
	m_pos.x = 16;
	m_pos.y = 16;

	// MovePlayer�̏����ݒ�
	player.Init();
	// enemy�̏�������
	// enemy��Easy�悤�̃X�s�[�h������
	enemy.Init(ENEMY_EASY_SPEED);
	// �w�i�摜�̓ǂݍ���
	m_bak_image = LoadGraph("data/BG/pipo-bg005.jpg");

	// �ō��X�R�A�̓ǂݍ���
	TextLoadingEasy();

	// Easy��ʂł̂�����������ϐ�
	m_bgm = LoadSoundMem("data/sound/easy.mp3");

	// �������Ԃ����߂�ϐ�
	m_bgm_count = 0;

	//// �X�R�A�X�V�����Ƃ��ɗ������ʉ�
	//m_update_sound = LoadSoundMem("data/sound/effect/update.mp3");

	//// �X�R�A�X�V�̉��𗬂��������߂�ϐ�
	//m_sound = false;

	// BGM������Ă��邩���m�F����ϐ�
	// �ŏ��͗���Ă��Ȃ�
	sound_change = true;

	// �{�����[���ݒ�
	ChangeVolumeSoundMem(150, m_bgm);
}

// -----------------
// �X�V����
// -----------------
void EasyPlay::Update()
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
	

	if (m_bgm_count > 5400) {
		// BGM���~
		StopSoundMem(m_bgm);
	}
	// MovePlayer�̍X�V����
	player.Update();

	//enemy�̍X�V����
	enemy.Update(EASY_TIME_MAX);
	
}


// -----------------
// �`�揈��
// -----------------
void EasyPlay::Draw()
{
	// �w�i�摜�̕`��
	// ��ʃT�C�Y�ɍ��킹�ĕ`��
	DrawExtendGraphF(0, 0, WINDOW_W, WINDOW_H, m_bak_image, TRUE);

	// Easy���Ă΂�Ă��邩�킩��悤��
	DrawString(m_pos.x, m_pos.y, "Easy", GetColor(255, 0, 0), TRUE);

	// ���Ń|�C���g�̕`��
	DrawFormatString(500, 16, GetColor(255, 255, 255), "�ō��X�R�A�F%3d", m_best_score);

	// enemy�̕`��
	enemy.PointDraw();
	enemy.Draw();

	// MovePlayer�̕`�揈��
	player.Draw();

}

//======================================================================

// �ŏI�|�C���g��`�悷�邽�߂̊֐�
void EasyPlay::PointDraw(Pos pos)
{
	// �����̑傫����ς���
	SetFontSize(30);

	// �Ō�ŃX�R�A�̕`��
	DrawFormatString(pos.x, pos.y, GetColor(255, 255, 255), "�X�R�A�F%3d", enemy.m_point);
		
	// m_best_score �����X�R�A���������
	// �ō��X�R�A�̏�������
	if (m_best_score < enemy.m_point) {
		// �X�R�A�̋L�^���X�V������`��
		DrawString(pos.x , pos.y - 80, "�X�R�A�X�V�I�I", GetColor(255, 255, 255));
		DrawString(pos.x , pos.y - 40, "��������", GetColor(255, 255, 255));
		// �X�R�A�̏�������
		TextWriteInEasy();
		/*m_sound = true;*/
	}

	//// �X�R�A�X�V�����Ƃ��ɗ������ʉ�
	//if (m_sound == true) {
	//	// ���ʉ����Đ�
	//	PlaySoundMem(m_update_sound, DX_PLAYTYPE_BACK);
	//}

	// �����̑傫����߂�
	SetFontSize(25);
}


// -----------------
// �I������
// -----------------
void EasyPlay::Exit()
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
