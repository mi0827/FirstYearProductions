#include "WinMain.h"
#include "Base.h"
#include "Hit.h"
#include "Enemy.h"
#include "MovePlayer.h"
#include "PlayBase.h"

PlayBase::PlayBase()
{
}

PlayBase::~PlayBase()
{
}

// �l�p���m�̓����蔻��
//===========================================================================
// �l�p���m�̓����蔻���ς����֐�
bool PlayBase::IsHit(Pos& obgect1, Pos& obgect2)
{
	return  CheckBoxHit(obgect1.x, obgect1.y, obgect1.w, obgect1.h, 
		obgect2.x, obgect2.y, obgect2.w, obgect2.h);
}

// ���enemy�̎l�p�ł̓����蔻��
bool PlayBase::OnHitBoxPlayerEnemy(MovePlayer& player, Pos& enemy)
{
	return CheckBoxHit(player.m_pos.x, player.m_pos.y, player.m_pos.w, player.m_pos.h,
		enemy.x, enemy.y, enemy.w, enemy.h);
}

// enemy���m�̓����蔻��
bool PlayBase::OnHitBoxEnemyEnemy(Pos& enemy1, Pos& enemy2) {
	
			return  IsHit(enemy1, enemy2);

}

//===========================================================================

// enemy���m���d�Ȃ�Ȃ��悤�ɂ���֐�
void PlayBase::OverlapJudgment(Enemy& enemy1, Enemy& enemy2, int i)
{
	// �I�ʒu���d�Ȃ�Ȃ��悤�ɂ��Ă���
	int j = 0;
	int counter = 0;
	// �S�����d�Ȃ��Ă��Ȃ��������Ă���
	// counter���S�ȏ�ɂȂ�Ȃ��Ɣ�����Ȃ�
	for (; ; ++j)
	{
		// j�@���@ENEMY_MAX;�@���傫���Ȃ�����O�ɂ���
		j %= ENEMY_MAX;
		// �T�Ƃ��������l�Ȃ瓖���蔻������Ȃ�
		if (i == j)
		{
			continue;
		}

		// �d�Ȃ��Ă���
		if (OnHitBoxEnemyEnemy(enemy1.m_enemy_pos[i], enemy2.m_enemy_pos[j]))
		{
			// �J�E���g���O�ɖ߂�
			counter = 0;
			// �S���̈ʒu�������_���ɔz�u���Ȃ���
			enemy1.m_enemy_pos[i].x = GetRand(RAND_X_MAX);
			enemy1.m_enemy_pos[i].y = GetRand(RAND_Y_MAX) + RAND_Y_PLUS;

			// �����ł����蔻��悤��m_hit_enemy���Đݒ�
			enemy1.m_hit_pos[i].x = enemy1.m_enemy_pos[i].x + HIT_BOX_W;
			enemy1.m_hit_pos[i].y = enemy1.m_enemy_pos[i].y + HIT_BOX_H;

			// �܂������������邽�߂ɍŏ��ɖ߂�
			continue;
		}

		// �d�Ȃ��ĂȂ�
		// �d�Ȃ��ĂȂ������J�E���g
		++counter;
		if (counter >= ENEMY_MAX - 1)
		{
			break;
		}
	}

}



