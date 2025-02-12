#pragma once
#include"PlayBase.h"
// ノーマルの制限時間
constexpr auto NORMAL_TIME_MAX = 120;
// ------------------------
// ノーマルモード用クラス
// ------------------------
class NormalPlay : public PlayBase {
public:
	NormalPlay();
	~NormalPlay();

	void Init();   // 初期設定
	void Update(); // 更新処理
	void Draw();   // 描画処理
	void PointDraw(Pos pos); // 最終ポイントを描画するための関数
	void Exit();//	終了処理

	// Textファイルの読み込み
	int TextLoadingNormal();
	
	// Textファイルへの書き込み
	int TextWriteInNormal();

private:
	// カウントで球の位置を帰るための変数
	int m_time_count;

	// ノーマル画面でのｂｇｍを入れる変数
	int m_bgm;
	// 流す時間を決める変数
	int m_bgm_count;

	// BGMが流れているかを確認する変数
	bool sound_change;
};