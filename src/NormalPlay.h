#pragma once
#include"PlayBase.h"
// �m�[�}���̐�������
constexpr auto NORMAL_TIME_MAX = 120;
// ------------------------
// �m�[�}�����[�h�p�N���X
// ------------------------
class NormalPlay : public PlayBase {
public:
	NormalPlay();
	~NormalPlay();

	void Init();   // �����ݒ�
	void Update(); // �X�V����
	void Draw();   // �`�揈��
	void PointDraw(Pos pos); // �ŏI�|�C���g��`�悷�邽�߂̊֐�
	void Exit();//	�I������

	// Text�t�@�C���̓ǂݍ���
	int TextLoadingNormal();
	
	// Text�t�@�C���ւ̏�������
	int TextWriteInNormal();

private:
	// �J�E���g�ŋ��̈ʒu���A�邽�߂̕ϐ�
	int m_time_count;

	// �m�[�}����ʂł̂�����������ϐ�
	int m_bgm;
	// �������Ԃ����߂�ϐ�
	int m_bgm_count;

	// BGM������Ă��邩���m�F����ϐ�
	bool sound_change;
};