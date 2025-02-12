#pragma once

// ���[�h����ʂ������
enum {

	EASY = 0,  // �ȒP
	NORMAL,   // ����
	HARD, // ���

	end,
};

// ------------------------
// ��Փx�I���V�[���p�N���X
// ------------------------
class ModeSelectScene: public Base {
public:
	ModeSelectScene();
	~ModeSelectScene();

	bool IsChange(); // �V�[���̐؂�ւ�
	bool EasyChange(); // Easy���[�h���ĂԂ��߂̊֐�
	bool NormalChange(); // Normal���[�h���ĂԂ��߂̊֐�
	bool HardChange(); // Hard���[�h���ĂԂ��߂̊֐�
	void Init();   // �����ݒ�
	void Update(); // �X�V����
	void Draw();   // �`�揈��
	void Exit();//	�I������

private:
	
	// �e�`�悷����̂̍��W�p�ϐ�
	Pos m_pos[end];  // �I���̕����Ȃǂ�`�悷�邽�߂̍��W 
	Pos m_mouse_pos; // �}�E�X�̍��W
	Pos m_select;  // �I���̂��߂̍��W
	Pos m_target;   // �΂̋ʂ̕`��p�̕ϐ�


	int m_check_count; // �\���L�[�Ń��[�h�I��p�ϐ�
	bool change_;
	bool m_easy_chande;   // Easy�̂�I���������m�F���邽�߂̕ϐ�
	bool m_normal_chande; // Normal��I�����������m�F���邽�߂̕ϐ�
	bool m_hard_chande;   // Haed��I�����������m�F���邽�߂̕ϐ�

	int m_r[end], m_g[end], m_b[end]; // �����̐F�p�̕ϐ�


	// �v���C���[�̕���摜�p�̕ϐ�
	
	int m_image;
	// �e��Փx�̉��ɗ���΂̋ʂ̉摜�p�ϐ�
	int m_target_image[3];
	
	// ��Փx�V�[����ʂł̂�����������ϐ�
	int m_bgm;

	// ���肵���Ƃ��ɗ������p�̕ϐ�
	int m_button_sound;

	// BGM������Ă��邩���m�F����ϐ�
	bool sound_change;
};
