#pragma once

// ------------------------
// �^�C�g���V�[���p�N���X
// ------------------------
class Title: public Base {
public:
	Title();
	~Title();

	bool IsChange(); // �摜�̐؂�ւ�

	void Init();   // �����ݒ�
	void Update(); // �X�V����
	void Draw();   // �`�揈��
	void Exit();//	�I������

private:
	Pos m_mouse_pos; // �}�E�X�̍��W

	// �^�C�g����ʂł̂�����������ϐ�
	int m_bgm;
	// ���肵���Ƃ��ɗ������p�̕ϐ�
	int m_button_sound;
	

	// BGM������Ă��邩���m�F����ϐ�
	bool sound_change;


	 // �{�^���������Ă���悤�Ɍ����邽�߂̕ϐ�
	Pos m_push;
	int m_push_count; 

	int m_button_image;  // �{�^���摜������p�p�̕ϐ�

	bool change_;

};