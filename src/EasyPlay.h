#pragma once
#include "MovePlayer.h"
#include "PlayBase.h"

// �C�[�W�[�p�̎���
constexpr auto EASY_TIME_MAX = 5400;
// ------------------------
// �C�[�W�[���[�h�p�N���X
// ------------------------
class EasyPlay : public PlayBase{
public:
	EasyPlay();
	~EasyPlay();
	// Text�t�@�C���̓ǂݍ���
	int TextLoadingEasy();

	// Text�t�@�C���ւ̏�������
	int TextWriteInEasy();

	void Init();	//	����������	
	void Update();//	�X�V����
	void Draw();//	�`�揈��
	void PointDraw(Pos pos); // �ŏI�|�C���g��`�悷�邽�߂̊֐�
	void Exit();//	�I������

private:
	// easy��ʂł̂�����������ϐ�
	int m_bgm;

	// BGM������Ă��邩���m�F����ϐ�
	bool sound_change;

	// �������Ԃ����߂�ϐ�
	int m_bgm_count;

	//// �X�R�A���X�V�����Ƃ��ɗ������p�̕ϐ�
	//int m_update_sound;

	//// �X�R�A�X�V�̉��𗬂��������߂�ϐ�
	//bool m_sound;
};