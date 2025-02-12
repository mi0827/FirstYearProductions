#pragma once

// お化けの移動用スピード
constexpr auto ENEMY_EASY_SPEED = 0.5f;    // イージー用のスピード
constexpr auto ENEMY_NORMAL_SPEED = 0.8f;  // ノーマル用のスピード
constexpr auto ENEMY_HARD_SPEED = 1.5f;    // ハード用のスピード
constexpr auto HIT_BOX_W = 20.0f;          // enemyのBox当たり判定調整ｗ
constexpr auto HIT_BOX_H = 13.0f;          // enemyのBox当たり判定調整Ｈ

// enemyが描画いているものと重ならないように値を設定している
constexpr auto RAND_X_MAX = 700;           // enemyのX座標のランダムの幅
constexpr auto RAND_Y_MAX = 260;           // enemyのY座標のランダムの幅
constexpr auto RAND_Y_PLUS = 40;           // enemyのY座標のランダムの幅にプラスすもの;

// Enemyの数
constexpr auto ENEMY_MAX = 6;

class Enemy :public Base {
public:
	Enemy();
	~Enemy();
	void Init(float speed);	//	初期化処理	
	void Update(int time_max );//	更新処理
	void Draw();//	描画処理
	void PointDraw(); // ポイント描画用
	void Exit();//	終了処理

	int m_point; // 合計ポイント用の変数

	// お化けの画像用変数
	int m_enemy_image[ENEMY_MAX];

	// お化け画像の切り取る場所の座標用変数
	Pos m_image_pos[ENEMY_MAX];

	// お化けの座標用変数
	Pos m_enemy_pos[ENEMY_MAX];

	// あたり判定用の変数
	Pos m_hit_pos[ENEMY_MAX];

	// enemyを左右どちらに移動させるか判断するための変数
	bool m_left_and_right[ENEMY_MAX];

	//enemyの移動スピード変数
	float m_move_speed[ENEMY_MAX];
private:

	// フレームカウント
	int m_flame_count;

	// お化けが前を向いてる時間 
	int m_front_count[ENEMY_MAX];

	// お化けが前を向くかを見るための変数
	bool m_front_judg[ENEMY_MAX];

	// お化けが破壊された時にエフェクト処理をするためにUpdateを止める
	bool m_update_stop;

	// 各ポイント変数
	const int m_plus_point = 50; // 普通のプラスポイント
	const int m_lucky_point = 100; // ラッキーを押したときのプラスポイント
	const int m_minus_point = -80; // 間違った時(何もないところでクリックしたときも)のマイナスポイント
	const int m_perfect_point = 500; // 一回の間違えなかった時のボーナスポイント
	const int m_penalty_poiint = -200; // １０回間違えた時のペナルティーポイント


	// 当たり判定がないところでクリックした場合
	bool is_hit_none = false;

	// 攻撃エフェクト画像用の変数
	int m_effect_image;

	// エフェクト画像自体の座標変数
	Pos m_effect_image_pos;

	// エフェクト画像の座標用変数
	Pos m_effect_pos;
	

	// 各難易度シーンでのお化けの移動処理ようの変数
	int m_time;

	// 当たり判定したときに流す音用の変数
	int m_hit_sound;

};