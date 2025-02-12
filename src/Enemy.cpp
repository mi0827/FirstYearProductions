#include "WinMain.h"
#include "Pos.h"
#include "Base.h"
#include "MovePlayer.h"
#include "PlayBase.h"
#include "Hit.h"
#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

// プレイヤーが動かす玉のクラス
extern MovePlayer player;

// -----------------
// 初期処理
// -----------------
void Enemy::Init(float speed)
{
	// 各難易度シーンでの処理の違いに使う
	m_time = 0;

	// enemyを配列で読み込むための変数
	char image[64];
	int num = 0;
	for (int i = 0; i < ENEMY_MAX; i++) {
		// i が２以下の時だけ num に2代入する
		if (i == 0) {
			num = 0;
		}
		else if (i <= 2) {
			num = 1;
		}
		else {
			num = 2;
		}
		// 画像の読み込み
		sprintfDx(image, "data/Enemy/ghost%d.png", num);
		m_enemy_image[i] = LoadGraph(image);

		// 座標設定
		m_enemy_pos[i].x = GetRand(RAND_X_MAX);
		m_enemy_pos[i].y = GetRand(RAND_Y_MAX) + RAND_Y_PLUS;
		m_enemy_pos[i].w = 100.0f;
		m_enemy_pos[i].h = 100.0f;

		// お化けの画像自体の座標の設定
		// 画像のどこから～
		m_image_pos[i].x = 0; // 画像の切り取るｘ座標
		m_image_pos[i].y = 0; // 画像の切り取るｙ座標
		// 画像のどこまで
		m_image_pos[i].w = 100; // 画像の切り取る横幅
		m_image_pos[i].h = 100; // 画像の切り取る縦幅

		// お化けの当たり判定がちょうどのサイズになるように大きさ調整
		// enemyのあたり判定用変数
		m_hit_pos[i].x = m_enemy_pos[i].x + HIT_BOX_W;
		m_hit_pos[i].y = m_enemy_pos[i].y + HIT_BOX_H;
		m_hit_pos[i].w = 60.0f;
		m_hit_pos[i].h = 90.0f;

		// お化けの移動用スピード用変数
		m_move_speed[i] = speed;

		//  動く方向の設定
		m_left_and_right[i] = GetRand(1);
	}


	// 攻撃エフェクト画像の読み込み
	m_effect_image = LoadGraph("data/effect/effect0.png");

	// エフェクト画像自体の座標変数
	// 人る目の画像うの座標設定 
	m_effect_image_pos.x = 0;
	m_effect_image_pos.w = 120;
	m_effect_image_pos.y = 0;
	m_effect_image_pos.h = 120;
	// エフェクト画像の座標用変数
	m_effect_pos.x = 0;
	m_effect_pos.y = 0;

	// フレームカウントの初期設定
	m_flame_count = 0;

	// front_jugeの初期設定
	for (int i = 0; i < ENEMY_MAX; i++) {
		// 前を向いていない状態にしておく
		m_front_judg[i] = false;
	}

	// m_update_stop最初は処理をしたいのでtrue
	m_update_stop = true;

	// フロントカウントの初期設定
	for (int i = 0; i < ENEMY_MAX; i++) {
		m_front_count[i] = 0;
	}

	// ポイントの初期化　
	m_point = 0;

	// 重なっているかどうかを見るための処理
	for (int i = 0; i < ENEMY_MAX; i++) {
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
				continue;

			// 重なっている
			// enemyが重なっているかは一つの画像サイズでとる
			if (CheckBoxHit(m_enemy_pos[i].x, m_enemy_pos[i].y, m_enemy_pos[i].w, m_enemy_pos[i].h,
				m_enemy_pos[j].x, m_enemy_pos[j].y, m_enemy_pos[j].w, m_enemy_pos[j].h))
			{
				// カウントを０に戻す
				counter = 0;
				// 全部の位置をランダムに配置しなおす
				m_enemy_pos[i].x = GetRand(RAND_X_MAX);
				m_enemy_pos[i].y = GetRand(RAND_Y_MAX) + RAND_Y_PLUS;
				//  動く方向の設定
				m_left_and_right[i] = GetRand(1);

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

	// 効果音の読み込み
	m_hit_sound= LoadSoundMem("data/sound/effect/explosion0.mp3");

	// 効果音の
	// ボリューム設定
	ChangeVolumeSoundMem(255, m_hit_sound);
}

// -----------------
// 更新処理
// -----------------
void Enemy::Update(int time_max)
{// playBaseクラスのオブジェクト
	PlayBase play_base;
	
	// フレームカウントを増やす
	// アニメーションさせるさせるためのもの
	m_flame_count++;

	// プレイヤーとお化けの当たり判定がないとき
	if (m_update_stop == true) {

		// タイマーを増やす
		m_time++;

		// 当たり判定ようの変数に値を入れる
		for (int i = 0; i < ENEMY_MAX; i++) {
			m_hit_pos[i].x = m_enemy_pos[i].x + HIT_BOX_W;
			m_hit_pos[i].y = m_enemy_pos[i].y + HIT_BOX_H;
		}


		// 移動処理
		for (int i = 0; i < ENEMY_MAX; i++) {
			// 前を向いていないお化けだけ移動処理をする
			if (m_front_judg[i] == false) {
				// 右
				if (m_left_and_right[i] == TRUE) {
					m_enemy_pos[i].x += m_move_speed[i];
				}
				// 左
				else if (m_left_and_right[i] == FALSE) {
					m_enemy_pos[i].x -= m_move_speed[i];
				}
			}
		}

		// 移動範囲
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (m_enemy_pos[i].x < -10) {
				// 右を向く
				m_left_and_right[i] = TRUE;
				m_front_judg[i] = true;
			}
			if (m_enemy_pos[i].x > WINDOW_W - 80) {
				// 左を見る
				m_left_and_right[i] = FALSE;
				m_front_judg[i] = true;
			}
		}


		// 画像が見ている方向を設定
		for (int i = 0; i < ENEMY_MAX; i++) {
			// フレームカウントが一定になったら
			if (m_flame_count % 15 == 0) {
				// 画像うの切り取る場所をずらす
				m_image_pos[i].x += 100;
				m_image_pos[i].w = m_image_pos[i].x;
			}// 画像の切り取るをループさせる
			if (m_image_pos[i].x > 200) {
				m_image_pos[i].x = 0;
				m_image_pos[i].w = 100;
			}
			// お化けが前を向いていない
			if (m_front_judg[i] == false) {
				// 右
				if (m_left_and_right[i] == TRUE) {
					// 右を見ている画像を切り取る
					m_image_pos[i].y = 200;
					m_image_pos[i].h = m_image_pos[i].h;
				}
				// 左
				else if (m_left_and_right[i] == FALSE) {
					// 左を見ている画像を切り取る
					m_image_pos[i].y = 100;
					m_image_pos[i].h = m_image_pos[i].h;
				}

				// フロントカウントを０にしておく
				m_front_count[i] = 0;
			}
			// お化けが前を向いている
			else if (m_front_judg[i] == true) {
				// フロントカウントを増やす
				m_front_count[i] ++;


				// 前を向いている画像にする
				m_image_pos[i].y = 0;
				m_image_pos[i].h = 100;


				// フロントカウントが一定の数値を超すと
				if (m_front_count[i] > 20) {
					// 左右を見ているシーンにする
					m_front_judg[i] = false;
				}
			}
		}

		// マウスを左クリックしたら当たり判定をとる
		if (IsMouseOn(MOUSE_INPUT_LEFT)) {
			// クリックしたらタイマーをリセット
			m_time = 0;
			for (int i = 0; i < ENEMY_MAX; i++) {

				//　クリックしたらタイマーをリセット
				m_time = 0;

				// クリックしたのでfalseにしておく
				is_hit_none = false;

				if (play_base.OnHitBoxPlayerEnemy(player, m_hit_pos[i])) {
					// フレームカウントをリセット 
					m_flame_count = 0;
					// 効果音の再生
					PlaySoundMem(m_hit_sound, DX_PLAYTYPE_BACK);

					// 当たり判定があったenemyの座標に描画
					m_effect_pos.x = m_enemy_pos[i].x;
					m_effect_pos.y = m_enemy_pos[i].y;

					// 当たっていたら
				// ポイントを足す
				// 普通の的を押したとき
					if (i == 0) {
						m_point += m_lucky_point;
					}
					// ラッキー的を押したとき
					else if (i <= 2) {
						m_point += m_plus_point;
					}
					// 押したダメな的を押したき
					else {
						m_point += m_minus_point;
					}

					// 当たり判定あったのでtrueにしておく
					is_hit_none = true;

					// 当たり判定があったら爆破処理をいれる
					m_update_stop = false;
				}
			}

			// 当たり判定がなかったらfalseのままなのでこの処理をする
			if (m_update_stop == true)
			{
				// ポイントを引く
				m_point += m_minus_point;
				for (int i = 0; i < ENEMY_MAX; i++) {
					// 全部の位置をランダムに配置しなおす
					m_enemy_pos[i].x = GetRand(RAND_X_MAX);
					m_enemy_pos[i].y = GetRand(RAND_Y_MAX) + RAND_Y_PLUS;
					//  動く方向の設定
					m_left_and_right[i] = GetRand(1);

					// 重なっていないかを見る
					//play_base.OverlapJudgment(m_enemy_pos, enemy, i);
					play_base.OverlapJudgment(*this, *this, i);
				}
			}
		}
	}
	// タイマーが一定の値になると的の位置をランダムに再設定
	if (m_time > time_max) {// いったん２秒にしておく
		for (int i = 0; i < ENEMY_MAX; ++i) {
			// 全部の位置をランダムに配置しなおす
			m_enemy_pos[i].x = GetRand(RAND_X_MAX);
			m_enemy_pos[i].y = GetRand(RAND_Y_MAX) + RAND_Y_PLUS;
			//  動く方向の設定
			m_left_and_right[i] = GetRand(1);
			// 重なっているかを見るための関数
			play_base.OverlapJudgment(*this, *this, i);
		}
		m_point += m_minus_point;
		// タイマーをリセット
		m_time = 0;
	}

	// enemy爆破エフェクトをする処理
	if (m_update_stop == false) {

		// フレームカウントが一定になったら
		if (m_flame_count % 6 == 0) {
			// 画像うの切り取る場所をずらす
			m_effect_image_pos.x += 120;
			m_effect_image_pos.w;
		}// 画像の切り取るをループさせる
		if (m_effect_image_pos.x > 580) {
			m_effect_image_pos.x = 0;
			m_effect_image_pos.w = 120;
		}

		// 爆破画像のアニメーションが一周したらm_effect_posをtrueにする
		if (m_flame_count > 30) {
			// フレームカウントをリセット 
			m_flame_count = 0;
			// アニメーション画像鵜をリセット
			m_effect_image_pos.x = 0;
			m_effect_image_pos.w = 120;
			for (int i = 0; i < ENEMY_MAX; i++) {
				// あたり判定があったお化けの位置を再設定
				m_enemy_pos[i].x = GetRand(RAND_X_MAX);
				m_enemy_pos[i].y = GetRand(RAND_Y_MAX) + RAND_Y_PLUS;
				// 動く方向を設定
				m_left_and_right[i] = GetRand(1);
				// 重なっているかを見るための関数
				play_base.OverlapJudgment(*this, *this, i);
			}
			m_update_stop = true;
		}
	}
}

// -----------------
// 描画処理
// -----------------
void Enemy::Draw()
{
	// お化けの描画
	for (int i = 0; i < ENEMY_MAX; i++) {
		// アニメーションさせる
		DrawRectGraphF(m_enemy_pos[i].x, m_enemy_pos[i].y, m_image_pos[i].x, m_image_pos[i].y, m_image_pos[i].w, m_image_pos[i].h, m_enemy_image[i], TRUE, FALSE);

	}
	if (m_update_stop == false) {
		// ダメージを受けた時のエフェクトの描画
		DrawRectGraphF(m_effect_pos.x, m_effect_pos.y, m_effect_image_pos.x, m_effect_image_pos.y, m_effect_image_pos.w, m_effect_image_pos.h, m_effect_image, TRUE, FALSE);
	}
	
}

void Enemy::PointDraw()
{
	// 仮でポイントの描画
	DrawFormatString(150, 16, GetColor(255, 255, 255), "現在のポイント：%3d", m_point);
}

// -----------------
// 終了処理
// -----------------
void Enemy::Exit()
{
	// サウンドの削除
	DeleteSoundMem(m_hit_sound);

	// お化け画像の終了処理
	for (int i = 0; i < ENEMY_MAX; i++) {
		DeleteGraph(m_enemy_image[i]);
	}
	// 攻撃エフェクト
	DeleteGraph(m_effect_image);
}
