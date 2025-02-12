#pragma once
constexpr auto FIAME_IMAGE_MAX = 5; // ���摜�̐�
constexpr auto OPEN_CURTAIN_MAX = 10; // �J�[�e���̊J���摜�̐�
constexpr auto CLOSE_CURTAIN_MAX = 18; // �J�[�e���̕���摜�̐�
constexpr auto GAME_STRAT = 240; // �Q�[���V�[���ɍs���O�̏������I��点��l
constexpr auto GAME_END = 150; // �Q�[���V�[�����I��Ă�鰂̏������n�߂�l
constexpr auto FRAME_IMSGE_MAX = 3; // �t���[���摜�̐�

enum {
	TUTORIAL, // �`���[�g���A���V�[��

	SELECT, // ��Փx�I���V�[��

	PLAY,   // �v���C�V�[��

	END
};

// ------------------------
// �v���C�V�[���p�N���X
// ------------------------
// ���[�h�I���V�[������Q�[���V�[���܂ł��s���N���X
class PlayScene : public Base {
public:
	PlayScene();
	~PlayScene();


	bool IsChange(); // �V�[���̐؂�ւ��p�̊֐�

	void Init();   // �����ݒ�
	void Update(); // �X�V����
	void Draw();   // �`�揈��
	void PointDraw(Pos pos); // �ŏI�|�C���g��`�悷�邽�߂̊֐�
	void Exit();//	�I������

private:
	// �ǂ̓�Փx�̃N���X��ǂݍ��ނ����f�p�̕ϐ�
	int m_check_count;

	// ��Փx�I���V�[����play�V�[�����𔻒f�Ɏg���ϐ�
	int m_change_scene;

	// GameMain �ł̃V�[���̐؂�ւ��Ɏg���ϐ�
	bool change_;

	// ��Փx�I����ʂ��I����Ă���A�Q�[���V�[�����n�܂�܂ł̃J�E���g
	int m_start_count;

	// �J�E���g��������悤�ɂ��邽��
	int m_change_count;

	//-------------------------------------
	// �摜������p�̕ϐ�
	//------------------------------------
	
	// �������Ԃ����C���ŕ`��p�ϐ�
	// ���̉摜�悤�̕ϐ�
	// �A�j���[�V���������邽�ߕ������
	int m_fiame_image[FIAME_IMAGE_MAX];
	// �J���J�[�e���摜�p�ϐ�
	int m_curtain_open_image;

	// ����J�[�e���摜�ϐ�
	int m_curtain_close_image;

	int m_frame_image[FRAME_IMSGE_MAX];

	// -----------------------------------------
	// �e�摜�̕`����W�p�ϐ�
	//------------------------------------------
	// 
	// ���摜�̕`����W�p�̕ϐ�
	Pos m_fiame_pos;

	// �J�[�e���摜�̕`����W�p�ϐ�
	Pos m_curtain_pos;

	// �t���[���摜�̕`����W
	Pos m_frame_pos[FRAME_IMSGE_MAX];

	// --------------------------------------
	// �A�j���[�V���������邽�߂̕ϐ�����
	// ---------------------------------------
	
	// ���Ԍo�߂ŕ`��ʒu�����������Ă������߂̕ϐ�
	Pos m_fiame_time_pos;

	// ���摜���A�j���[�V�������邽�߂̕ϐ�
	int m_animation_count;

	// �`�悵�Ă���摜�����X�Ɍ��炵�Ă������߂̐��l������p�̕ϐ�
	float m_timelimt;

	// �Q�[���̐�������
	float m_game_count;

	// �J�[�e���摜���A�j���[�V���������邽�߂̃J�E���g�ϐ�
	int m_curtain_count;

	// �J�[�e���摜���̂̍��W�p�̕ϐ�
	Pos m_curtain_image_pos;

	// --------------------------
	// bool�����̕ϐ�
	// -------------------------
	
	// �Q�[���V�[���ɐi�ޑO�ƒ��𕪂���ϐ�
	bool m_play;

	// �Q�[���V�[���쒆�ƌ�𕪂���ϐ�
	bool m_play_end;

	
};