#pragma once

// �������̈ړ��p�X�s�[�h
constexpr auto ENEMY_EASY_SPEED = 0.5f;    // �C�[�W�[�p�̃X�s�[�h
constexpr auto ENEMY_NORMAL_SPEED = 0.8f;  // �m�[�}���p�̃X�s�[�h
constexpr auto ENEMY_HARD_SPEED = 1.5f;    // �n�[�h�p�̃X�s�[�h
constexpr auto HIT_BOX_W = 20.0f;          // enemy��Box�����蔻�蒲����
constexpr auto HIT_BOX_H = 13.0f;          // enemy��Box�����蔻�蒲���g

// enemy���`�悢�Ă�����̂Əd�Ȃ�Ȃ��悤�ɒl��ݒ肵�Ă���
constexpr auto RAND_X_MAX = 700;           // enemy��X���W�̃����_���̕�
constexpr auto RAND_Y_MAX = 260;           // enemy��Y���W�̃����_���̕�
constexpr auto RAND_Y_PLUS = 40;           // enemy��Y���W�̃����_���̕��Ƀv���X������;

// Enemy�̐�
constexpr auto ENEMY_MAX = 6;

class Enemy :public Base {
public:
	Enemy();
	~Enemy();
	void Init(float speed);	//	����������	
	void Update(int time_max );//	�X�V����
	void Draw();//	�`�揈��
	void PointDraw(); // �|�C���g�`��p
	void Exit();//	�I������

	int m_point; // ���v�|�C���g�p�̕ϐ�

	// �������̉摜�p�ϐ�
	int m_enemy_image[ENEMY_MAX];

	// �������摜�̐؂���ꏊ�̍��W�p�ϐ�
	Pos m_image_pos[ENEMY_MAX];

	// �������̍��W�p�ϐ�
	Pos m_enemy_pos[ENEMY_MAX];

	// �����蔻��p�̕ϐ�
	Pos m_hit_pos[ENEMY_MAX];

	// enemy�����E�ǂ���Ɉړ������邩���f���邽�߂̕ϐ�
	bool m_left_and_right[ENEMY_MAX];

	//enemy�̈ړ��X�s�[�h�ϐ�
	float m_move_speed[ENEMY_MAX];
private:

	// �t���[���J�E���g
	int m_flame_count;

	// ���������O�������Ă鎞�� 
	int m_front_count[ENEMY_MAX];

	// ���������O�������������邽�߂̕ϐ�
	bool m_front_judg[ENEMY_MAX];

	// ���������j�󂳂ꂽ���ɃG�t�F�N�g���������邽�߂�Update���~�߂�
	bool m_update_stop;

	// �e�|�C���g�ϐ�
	const int m_plus_point = 50; // ���ʂ̃v���X�|�C���g
	const int m_lucky_point = 100; // ���b�L�[���������Ƃ��̃v���X�|�C���g
	const int m_minus_point = -80; // �Ԉ������(�����Ȃ��Ƃ���ŃN���b�N�����Ƃ���)�̃}�C�i�X�|�C���g
	const int m_perfect_point = 500; // ���̊ԈႦ�Ȃ��������̃{�[�i�X�|�C���g
	const int m_penalty_poiint = -200; // �P�O��ԈႦ�����̃y�i���e�B�[�|�C���g


	// �����蔻�肪�Ȃ��Ƃ���ŃN���b�N�����ꍇ
	bool is_hit_none = false;

	// �U���G�t�F�N�g�摜�p�̕ϐ�
	int m_effect_image;

	// �G�t�F�N�g�摜���̂̍��W�ϐ�
	Pos m_effect_image_pos;

	// �G�t�F�N�g�摜�̍��W�p�ϐ�
	Pos m_effect_pos;
	

	// �e��Փx�V�[���ł̂������̈ړ������悤�̕ϐ�
	int m_time;

	// �����蔻�肵���Ƃ��ɗ������p�̕ϐ�
	int m_hit_sound;

};