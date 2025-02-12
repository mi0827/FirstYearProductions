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

// 四角同士の当たり判定
//===========================================================================
// 四角同士の当たり判定を変えす関数
bool PlayBase::IsHit(Pos& obgect1, Pos& obgect2)
{
	return  CheckBoxHit(obgect1.x, obgect1.y, obgect1.w, obgect1.h, 
		obgect2.x, obgect2.y, obgect2.w, obgect2.h);
}

// 杖とenemyの四角での当たり判定
bool PlayBase::OnHitBoxPlayerEnemy(MovePlayer& player, Pos& enemy)
{
	return CheckBoxHit(player.m_pos.x, player.m_pos.y, player.m_pos.w, player.m_pos.h,
		enemy.x, enemy.y, enemy.w, enemy.h);
}

// enemy同士の当たり判定
bool PlayBase::OnHitBoxEnemyEnemy(Pos& enemy1, Pos& enemy2) {
	
			return  IsHit(enemy1, enemy2);

}

//===========================================================================

// enemy同士が重ならないようにする関数
void PlayBase::OverlapJudgment(Enemy& enemy1, Enemy& enemy2, int i)
{
	// 的位置が重ならないようにしている
	int j = 0;
	int counter = 0;
	// 全部が重なっていないかを見ている
	// counterが４以上にならないと抜けれない
	for (; ; ++j)
	{
		// j　が　ENEMY_MAX;　より大きくなったら０にする
		j %= ENEMY_MAX;
		// Ⅰとｊが同じ値なら当たり判定を取らない
		if (i == j)
		{
			continue;
		}

		// 重なっている
		if (OnHitBoxEnemyEnemy(enemy1.m_enemy_pos[i], enemy2.m_enemy_pos[j]))
		{
			// カウントを０に戻す
			counter = 0;
			// 全部の位置をランダムに配置しなおす
			enemy1.m_enemy_pos[i].x = GetRand(RAND_X_MAX);
			enemy1.m_enemy_pos[i].y = GetRand(RAND_Y_MAX) + RAND_Y_PLUS;

			// ここであたり判定ようのm_hit_enemyを再設定
			enemy1.m_hit_pos[i].x = enemy1.m_enemy_pos[i].x + HIT_BOX_W;
			enemy1.m_hit_pos[i].y = enemy1.m_enemy_pos[i].y + HIT_BOX_H;

			// また見直しをするために最初に戻る
			continue;
		}

		// 重なってない
		// 重なってない数をカウント
		++counter;
		if (counter >= ENEMY_MAX - 1)
		{
			break;
		}
	}

}



