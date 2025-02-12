#pragma once
#include "MovePlayer.h"
#include "PlayBase.h"

// イージー用の時間
constexpr auto EASY_TIME_MAX = 5400;
// ------------------------
// イージーモード用クラス
// ------------------------
class EasyPlay : public PlayBase{
public:
	EasyPlay();
	~EasyPlay();
	// Textファイルの読み込み
	int TextLoadingEasy();

	// Textファイルへの書き込み
	int TextWriteInEasy();

	void Init();	//	初期化処理	
	void Update();//	更新処理
	void Draw();//	描画処理
	void PointDraw(Pos pos); // 最終ポイントを描画するための関数
	void Exit();//	終了処理

private:
	// easy画面でのｂｇｍを入れる変数
	int m_bgm;

	// BGMが流れているかを確認する変数
	bool sound_change;

	// 流す時間を決める変数
	int m_bgm_count;

	//// スコアを更新したときに流す音用の変数
	//int m_update_sound;

	//// スコア更新の音を流すかを決める変数
	//bool m_sound;
};