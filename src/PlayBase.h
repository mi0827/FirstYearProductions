#pragma once
#include "Base.h"
#include "Pos.h"
#include "Enemy.h"
#include "MovePlayer.h"


// -------------------
// 各プレイシーン用のベースクラス
// -------------------
class PlayBase :public Base {
public:
	PlayBase();
	~PlayBase();
	
	// enemy同士が重ならないようにするための関数
	void OverlapJudgment(Enemy& enemy1, Enemy& enemy2, int i);

	// Boxの当たり判定を返す関数
	bool IsHit(Pos& obgect1, Pos& obgect2);

	// プレイヤーとenemyのBoxでの当たり判定
	bool OnHitBoxPlayerEnemy(MovePlayer& player, Pos& enemy);

	// enemy同士のBoxでの当たり判定
	bool OnHitBoxEnemyEnemy(Pos& enemy1, Pos& enemy2);

private:

protected:
	// プレイタイム
	static constexpr float PLAY_TIME_MAX = 3600.0f;// プレイ時間（６０フレームで１分）

	// 的の数
	const int m_target_max = 5;

	// 当たり判定がないところでクリックした場合
	bool is_hit_none = false;

	// 的の数の分の座標
	Pos m_target_pos[5];

	// 各スコアをtextに書き込むための変数
	// 描画用
	int m_best_score;
	// 書き込み用
	int num;

	
};