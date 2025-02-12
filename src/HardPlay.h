#pragma once
//#include "MovePlayer.h"
//#include "PlayBase.h"

// �n�[�h�p�̎���
constexpr auto HARD_TIME_MAX = 60;
// -------#-----------------
// �n�[�h���[�h�p�N���X
// ------------------------
class HardPlay : public PlayBase {
public:
	HardPlay();
	~HardPlay();


	void Init();   // �����ݒ�
	void Update(); // �X�V����
	void Draw();   // �`�揈��
	void PointDraw(Pos pos); // �ŏI�|�C���g��`�悷�邽�߂̊֐�
	void Exit();//	�I������

	// Text�t�@�C���̓ǂݍ���
	int TextLoadingHrad();
	
	// Text�t�@�C���ւ̏�������
	int TextWriteInHrad();

private:
	// �J�E���g�ŋ��̈ʒu���A�邽�߂̕ϐ�
	int m_time_count;
	// Hrad��ʂł̂�����������ϐ�
	int m_bgm;
	// �������Ԃ����߂�ϐ�
	int m_bgm_count;

	// BGM������Ă��邩���m�F����ϐ�
	bool sound_change;
};