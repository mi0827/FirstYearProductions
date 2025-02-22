#pragma once
#include "Base.h"
#include "Pos.h"
#include "Enemy.h"
#include "MovePlayer.h"


// -------------------
// �e�v���C�V�[���p�̃x�[�X�N���X
// -------------------
class PlayBase :public Base {
public:
	PlayBase();
	~PlayBase();
	
	// enemy���m���d�Ȃ�Ȃ��悤�ɂ��邽�߂̊֐�
	void OverlapJudgment(Enemy& enemy1, Enemy& enemy2, int i);

	// Box�̓����蔻���Ԃ��֐�
	bool IsHit(Pos& obgect1, Pos& obgect2);

	// �v���C���[��enemy��Box�ł̓����蔻��
	bool OnHitBoxPlayerEnemy(MovePlayer& player, Pos& enemy);

	// enemy���m��Box�ł̓����蔻��
	bool OnHitBoxEnemyEnemy(Pos& enemy1, Pos& enemy2);

private:

protected:
	// �v���C�^�C��
	static constexpr float PLAY_TIME_MAX = 3600.0f;// �v���C���ԁi�U�O�t���[���łP���j

	// �I�̐�
	const int m_target_max = 5;

	// �����蔻�肪�Ȃ��Ƃ���ŃN���b�N�����ꍇ
	bool is_hit_none = false;

	// �I�̐��̕��̍��W
	Pos m_target_pos[5];

	// �e�X�R�A��text�ɏ������ނ��߂̕ϐ�
	// �`��p
	int m_best_score;
	// �������ݗp
	int num;

	
};