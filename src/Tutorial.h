#pragma once
#include "PlayBase.h"

class Tutorial : public PlayBase {
public:

	void Init();	//	����������	
	void Update();//	�X�V����
	void Draw();//	�`�揈��
	void Exit();//	�I������
	bool IsChange(); // �V�[���̐؂�ւ��p�̊֐�

private:
	// BGM������Ă��邩���m�F����ϐ�
	bool sound_change;

	// �`���[�g���A����ʂł̂�����������ϐ�
	int m_bgm;

	// GameMain �ł̃V�[���̐؂�ւ��Ɏg���ϐ�
	bool change_;
};