#pragma once
//#include "MovePlayer.h"
//#include "PlayBase.h"

// ハード用の時間
constexpr auto HARD_TIME_MAX = 60;
// -------#-----------------
// ハードモード用クラス
// ------------------------
class HardPlay : public PlayBase {
public:
	HardPlay();
	~HardPlay();


	void Init();   // 初期設定
	void Update(); // 更新処理
	void Draw();   // 描画処理
	void PointDraw(Pos pos); // 最終ポイントを描画するための関数
	void Exit();//	終了処理

	// Textファイルの読み込み
	int TextLoadingHrad();
	
	// Textファイルへの書き込み
	int TextWriteInHrad();

private:
	// カウントで球の位置を帰るための変数
	int m_time_count;
	// Hrad画面でのｂｇｍを入れる変数
	int m_bgm;
	// 流す時間を決める変数
	int m_bgm_count;

	// BGMが流れているかを確認する変数
	bool sound_change;
};