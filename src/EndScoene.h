#pragma once

// ------------------------
// エンドシーン用クラス
// ------------------------
// ゲームが終わった後に行う
class EndScoene:  public Base {
public:

	EndScoene();
	~EndScoene();

	bool IsChange();

	void Init();   // 初期設定
	void Update(); // 更新処理
	void Draw();   // 描画処理
	void Exit();//	終了処理

private:
	bool change_;
	// タイトル画面でのｂｇｍを入れる変数
	int m_bgm;

	// BGMが流れているかを確認する変数
	bool sound_change;

	// スコアを更新したときに流す音用の変数
	int m_update_sound;

	// スコア更新の音を流すかを決める変数
	bool m_sound;

	// 最後にポイントを描画する座標
	Pos m_point_pos;
};