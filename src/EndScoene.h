#pragma once

// ------------------------
// �G���h�V�[���p�N���X
// ------------------------
// �Q�[�����I�������ɍs��
class EndScoene:  public Base {
public:

	EndScoene();
	~EndScoene();

	bool IsChange();

	void Init();   // �����ݒ�
	void Update(); // �X�V����
	void Draw();   // �`�揈��
	void Exit();//	�I������

private:
	bool change_;
	// �^�C�g����ʂł̂�����������ϐ�
	int m_bgm;

	// BGM������Ă��邩���m�F����ϐ�
	bool sound_change;

	// �X�R�A���X�V�����Ƃ��ɗ������p�̕ϐ�
	int m_update_sound;

	// �X�R�A�X�V�̉��𗬂��������߂�ϐ�
	bool m_sound;

	// �Ō�Ƀ|�C���g��`�悷����W
	Pos m_point_pos;
};