#include "WinMain.h"
#include "Pos.h"
#include "Base.h"
#include "MovePlayer.h"
#include "PlayBase.h"
#include "Hit.h"
#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

// �v���C���[���������ʂ̃N���X
extern MovePlayer player;

// -----------------
// ��������
// -----------------
void Enemy::Init(float speed)
{
	// �e��Փx�V�[���ł̏����̈Ⴂ�Ɏg��
	m_time = 0;

	// enemy��z��œǂݍ��ނ��߂̕ϐ�
	char image[64];
	int num = 0;
	for (int i = 0; i < ENEMY_MAX; i++) {
		// i ���Q�ȉ��̎����� num ��2�������
		if (i == 0) {
			num = 0;
		}
		else if (i <= 2) {
			num = 1;
		}
		else {
			num = 2;
		}
		// �摜�̓ǂݍ���
		sprintfDx(image, "data/Enemy/ghost%d.png", num);
		m_enemy_image[i] = LoadGraph(image);

		// ���W�ݒ�
		m_enemy_pos[i].x = GetRand(RAND_X_MAX);
		m_enemy_pos[i].y = GetRand(RAND_Y_MAX) + RAND_Y_PLUS;
		m_enemy_pos[i].w = 100.0f;
		m_enemy_pos[i].h = 100.0f;

		// �������̉摜���̂̍��W�̐ݒ�
		// �摜�̂ǂ�����`
		m_image_pos[i].x = 0; // �摜�̐؂��邘���W
		m_image_pos[i].y = 0; // �摜�̐؂��邙���W
		// �摜�̂ǂ��܂�
		m_image_pos[i].w = 100; // �摜�̐؂��鉡��
		m_image_pos[i].h = 100; // �摜�̐؂���c��

		// �������̓����蔻�肪���傤�ǂ̃T�C�Y�ɂȂ�悤�ɑ傫������
		// enemy�̂����蔻��p�ϐ�
		m_hit_pos[i].x = m_enemy_pos[i].x + HIT_BOX_W;
		m_hit_pos[i].y = m_enemy_pos[i].y + HIT_BOX_H;
		m_hit_pos[i].w = 60.0f;
		m_hit_pos[i].h = 90.0f;

		// �������̈ړ��p�X�s�[�h�p�ϐ�
		m_move_speed[i] = speed;

		//  ���������̐ݒ�
		m_left_and_right[i] = GetRand(1);
	}


	// �U���G�t�F�N�g�摜�̓ǂݍ���
	m_effect_image = LoadGraph("data/effect/effect0.png");

	// �G�t�F�N�g�摜���̂̍��W�ϐ�
	// �l��ڂ̉摜���̍��W�ݒ� 
	m_effect_image_pos.x = 0;
	m_effect_image_pos.w = 120;
	m_effect_image_pos.y = 0;
	m_effect_image_pos.h = 120;
	// �G�t�F�N�g�摜�̍��W�p�ϐ�
	m_effect_pos.x = 0;
	m_effect_pos.y = 0;

	// �t���[���J�E���g�̏����ݒ�
	m_flame_count = 0;

	// front_juge�̏����ݒ�
	for (int i = 0; i < ENEMY_MAX; i++) {
		// �O�������Ă��Ȃ���Ԃɂ��Ă���
		m_front_judg[i] = false;
	}

	// m_update_stop�ŏ��͏������������̂�true
	m_update_stop = true;

	// �t�����g�J�E���g�̏����ݒ�
	for (int i = 0; i < ENEMY_MAX; i++) {
		m_front_count[i] = 0;
	}

	// �|�C���g�̏������@
	m_point = 0;

	// �d�Ȃ��Ă��邩�ǂ��������邽�߂̏���
	for (int i = 0; i < ENEMY_MAX; i++) {
		// �I�ʒu���d�Ȃ�Ȃ��悤�ɂ��Ă���
		int j = 0;
		int counter = 0;
		// �S�����d�Ȃ��Ă��Ȃ��������Ă���
		// counter���S�ȏ�ɂȂ�Ȃ��Ɣ�����Ȃ�
		for (; ; ++j)
		{
			// j�@���@ENEMY_MAX;�@���傫���Ȃ�����O�ɂ���
			j %= ENEMY_MAX;
			// �T�Ƃ��������l�Ȃ瓖���蔻������Ȃ�
			if (i == j)
				continue;

			// �d�Ȃ��Ă���
			// enemy���d�Ȃ��Ă��邩�͈�̉摜�T�C�Y�łƂ�
			if (CheckBoxHit(m_enemy_pos[i].x, m_enemy_pos[i].y, m_enemy_pos[i].w, m_enemy_pos[i].h,
				m_enemy_pos[j].x, m_enemy_pos[j].y, m_enemy_pos[j].w, m_enemy_pos[j].h))
			{
				// �J�E���g���O�ɖ߂�
				counter = 0;
				// �S���̈ʒu�������_���ɔz�u���Ȃ���
				m_enemy_pos[i].x = GetRand(RAND_X_MAX);
				m_enemy_pos[i].y = GetRand(RAND_Y_MAX) + RAND_Y_PLUS;
				//  ���������̐ݒ�
				m_left_and_right[i] = GetRand(1);

				// �܂������������邽�߂ɍŏ��ɖ߂�
				continue;
			}

			// �d�Ȃ��ĂȂ�
			// �d�Ȃ��ĂȂ������J�E���g
			++counter;
			if (counter >= ENEMY_MAX - 1)
			{
				break;
			}
		}
	}

	// ���ʉ��̓ǂݍ���
	m_hit_sound= LoadSoundMem("data/sound/effect/explosion0.mp3");

	// ���ʉ���
	// �{�����[���ݒ�
	ChangeVolumeSoundMem(255, m_hit_sound);
}

// -----------------
// �X�V����
// -----------------
void Enemy::Update(int time_max)
{// playBase�N���X�̃I�u�W�F�N�g
	PlayBase play_base;
	
	// �t���[���J�E���g�𑝂₷
	// �A�j���[�V���������邳���邽�߂̂���
	m_flame_count++;

	// �v���C���[�Ƃ������̓����蔻�肪�Ȃ��Ƃ�
	if (m_update_stop == true) {

		// �^�C�}�[�𑝂₷
		m_time++;

		// �����蔻��悤�̕ϐ��ɒl������
		for (int i = 0; i < ENEMY_MAX; i++) {
			m_hit_pos[i].x = m_enemy_pos[i].x + HIT_BOX_W;
			m_hit_pos[i].y = m_enemy_pos[i].y + HIT_BOX_H;
		}


		// �ړ�����
		for (int i = 0; i < ENEMY_MAX; i++) {
			// �O�������Ă��Ȃ������������ړ�����������
			if (m_front_judg[i] == false) {
				// �E
				if (m_left_and_right[i] == TRUE) {
					m_enemy_pos[i].x += m_move_speed[i];
				}
				// ��
				else if (m_left_and_right[i] == FALSE) {
					m_enemy_pos[i].x -= m_move_speed[i];
				}
			}
		}

		// �ړ��͈�
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (m_enemy_pos[i].x < -10) {
				// �E������
				m_left_and_right[i] = TRUE;
				m_front_judg[i] = true;
			}
			if (m_enemy_pos[i].x > WINDOW_W - 80) {
				// ��������
				m_left_and_right[i] = FALSE;
				m_front_judg[i] = true;
			}
		}


		// �摜�����Ă��������ݒ�
		for (int i = 0; i < ENEMY_MAX; i++) {
			// �t���[���J�E���g�����ɂȂ�����
			if (m_flame_count % 15 == 0) {
				// �摜���̐؂���ꏊ�����炷
				m_image_pos[i].x += 100;
				m_image_pos[i].w = m_image_pos[i].x;
			}// �摜�̐؂�������[�v������
			if (m_image_pos[i].x > 200) {
				m_image_pos[i].x = 0;
				m_image_pos[i].w = 100;
			}
			// ���������O�������Ă��Ȃ�
			if (m_front_judg[i] == false) {
				// �E
				if (m_left_and_right[i] == TRUE) {
					// �E�����Ă���摜��؂���
					m_image_pos[i].y = 200;
					m_image_pos[i].h = m_image_pos[i].h;
				}
				// ��
				else if (m_left_and_right[i] == FALSE) {
					// �������Ă���摜��؂���
					m_image_pos[i].y = 100;
					m_image_pos[i].h = m_image_pos[i].h;
				}

				// �t�����g�J�E���g���O�ɂ��Ă���
				m_front_count[i] = 0;
			}
			// ���������O�������Ă���
			else if (m_front_judg[i] == true) {
				// �t�����g�J�E���g�𑝂₷
				m_front_count[i] ++;


				// �O�������Ă���摜�ɂ���
				m_image_pos[i].y = 0;
				m_image_pos[i].h = 100;


				// �t�����g�J�E���g�����̐��l�𒴂���
				if (m_front_count[i] > 20) {
					// ���E�����Ă���V�[���ɂ���
					m_front_judg[i] = false;
				}
			}
		}

		// �}�E�X�����N���b�N�����瓖���蔻����Ƃ�
		if (IsMouseOn(MOUSE_INPUT_LEFT)) {
			// �N���b�N������^�C�}�[�����Z�b�g
			m_time = 0;
			for (int i = 0; i < ENEMY_MAX; i++) {

				//�@�N���b�N������^�C�}�[�����Z�b�g
				m_time = 0;

				// �N���b�N�����̂�false�ɂ��Ă���
				is_hit_none = false;

				if (play_base.OnHitBoxPlayerEnemy(player, m_hit_pos[i])) {
					// �t���[���J�E���g�����Z�b�g 
					m_flame_count = 0;
					// ���ʉ��̍Đ�
					PlaySoundMem(m_hit_sound, DX_PLAYTYPE_BACK);

					// �����蔻�肪������enemy�̍��W�ɕ`��
					m_effect_pos.x = m_enemy_pos[i].x;
					m_effect_pos.y = m_enemy_pos[i].y;

					// �������Ă�����
				// �|�C���g�𑫂�
				// ���ʂ̓I���������Ƃ�
					if (i == 0) {
						m_point += m_lucky_point;
					}
					// ���b�L�[�I���������Ƃ�
					else if (i <= 2) {
						m_point += m_plus_point;
					}
					// �������_���ȓI����������
					else {
						m_point += m_minus_point;
					}

					// �����蔻�肠�����̂�true�ɂ��Ă���
					is_hit_none = true;

					// �����蔻�肪�������甚�j�����������
					m_update_stop = false;
				}
			}

			// �����蔻�肪�Ȃ�������false�̂܂܂Ȃ̂ł��̏���������
			if (m_update_stop == true)
			{
				// �|�C���g������
				m_point += m_minus_point;
				for (int i = 0; i < ENEMY_MAX; i++) {
					// �S���̈ʒu�������_���ɔz�u���Ȃ���
					m_enemy_pos[i].x = GetRand(RAND_X_MAX);
					m_enemy_pos[i].y = GetRand(RAND_Y_MAX) + RAND_Y_PLUS;
					//  ���������̐ݒ�
					m_left_and_right[i] = GetRand(1);

					// �d�Ȃ��Ă��Ȃ���������
					//play_base.OverlapJudgment(m_enemy_pos, enemy, i);
					play_base.OverlapJudgment(*this, *this, i);
				}
			}
		}
	}
	// �^�C�}�[�����̒l�ɂȂ�ƓI�̈ʒu�������_���ɍĐݒ�
	if (m_time > time_max) {// ��������Q�b�ɂ��Ă���
		for (int i = 0; i < ENEMY_MAX; ++i) {
			// �S���̈ʒu�������_���ɔz�u���Ȃ���
			m_enemy_pos[i].x = GetRand(RAND_X_MAX);
			m_enemy_pos[i].y = GetRand(RAND_Y_MAX) + RAND_Y_PLUS;
			//  ���������̐ݒ�
			m_left_and_right[i] = GetRand(1);
			// �d�Ȃ��Ă��邩�����邽�߂̊֐�
			play_base.OverlapJudgment(*this, *this, i);
		}
		m_point += m_minus_point;
		// �^�C�}�[�����Z�b�g
		m_time = 0;
	}

	// enemy���j�G�t�F�N�g�����鏈��
	if (m_update_stop == false) {

		// �t���[���J�E���g�����ɂȂ�����
		if (m_flame_count % 6 == 0) {
			// �摜���̐؂���ꏊ�����炷
			m_effect_image_pos.x += 120;
			m_effect_image_pos.w;
		}// �摜�̐؂�������[�v������
		if (m_effect_image_pos.x > 580) {
			m_effect_image_pos.x = 0;
			m_effect_image_pos.w = 120;
		}

		// ���j�摜�̃A�j���[�V���������������m_effect_pos��true�ɂ���
		if (m_flame_count > 30) {
			// �t���[���J�E���g�����Z�b�g 
			m_flame_count = 0;
			// �A�j���[�V�����摜�L�����Z�b�g
			m_effect_image_pos.x = 0;
			m_effect_image_pos.w = 120;
			for (int i = 0; i < ENEMY_MAX; i++) {
				// �����蔻�肪�������������̈ʒu���Đݒ�
				m_enemy_pos[i].x = GetRand(RAND_X_MAX);
				m_enemy_pos[i].y = GetRand(RAND_Y_MAX) + RAND_Y_PLUS;
				// ����������ݒ�
				m_left_and_right[i] = GetRand(1);
				// �d�Ȃ��Ă��邩�����邽�߂̊֐�
				play_base.OverlapJudgment(*this, *this, i);
			}
			m_update_stop = true;
		}
	}
}

// -----------------
// �`�揈��
// -----------------
void Enemy::Draw()
{
	// �������̕`��
	for (int i = 0; i < ENEMY_MAX; i++) {
		// �A�j���[�V����������
		DrawRectGraphF(m_enemy_pos[i].x, m_enemy_pos[i].y, m_image_pos[i].x, m_image_pos[i].y, m_image_pos[i].w, m_image_pos[i].h, m_enemy_image[i], TRUE, FALSE);

	}
	if (m_update_stop == false) {
		// �_���[�W���󂯂����̃G�t�F�N�g�̕`��
		DrawRectGraphF(m_effect_pos.x, m_effect_pos.y, m_effect_image_pos.x, m_effect_image_pos.y, m_effect_image_pos.w, m_effect_image_pos.h, m_effect_image, TRUE, FALSE);
	}
	
}

void Enemy::PointDraw()
{
	// ���Ń|�C���g�̕`��
	DrawFormatString(150, 16, GetColor(255, 255, 255), "���݂̃|�C���g�F%3d", m_point);
}

// -----------------
// �I������
// -----------------
void Enemy::Exit()
{
	// �T�E���h�̍폜
	DeleteSoundMem(m_hit_sound);

	// �������摜�̏I������
	for (int i = 0; i < ENEMY_MAX; i++) {
		DeleteGraph(m_enemy_image[i]);
	}
	// �U���G�t�F�N�g
	DeleteGraph(m_effect_image);
}
