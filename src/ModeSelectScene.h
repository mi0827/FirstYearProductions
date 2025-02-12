#pragma once

// モードを区別するもの
enum {

	EASY = 0,  // 簡単
	NORMAL,   // 普通
	HARD, // 難しい

	end,
};

// ------------------------
// 難易度選択シーン用クラス
// ------------------------
class ModeSelectScene: public Base {
public:
	ModeSelectScene();
	~ModeSelectScene();

	bool IsChange(); // シーンの切り替え
	bool EasyChange(); // Easyモードを呼ぶための関数
	bool NormalChange(); // Normalモードを呼ぶための関数
	bool HardChange(); // Hardモードを呼ぶための関数
	void Init();   // 初期設定
	void Update(); // 更新処理
	void Draw();   // 描画処理
	void Exit();//	終了処理

private:
	
	// 各描画するものの座標用変数
	Pos m_pos[end];  // 選択の文字などを描画するための座標 
	Pos m_mouse_pos; // マウスの座標
	Pos m_select;  // 選択のための座標
	Pos m_target;   // 火の玉の描画用の変数


	int m_check_count; // 十字キーでモード選択用変数
	bool change_;
	bool m_easy_chande;   // Easyのを選択したか確認するための変数
	bool m_normal_chande; // Normalを選択したかを確認するための変数
	bool m_hard_chande;   // Haedを選択したかを確認するための変数

	int m_r[end], m_g[end], m_b[end]; // 文字の色用の変数


	// プレイヤーの武器画像用の変数
	
	int m_image;
	// 各難易度の横に来る火の玉の画像用変数
	int m_target_image[3];
	
	// 難易度シーン画面でのｂｇｍを入れる変数
	int m_bgm;

	// 決定したときに流す音用の変数
	int m_button_sound;

	// BGMが流れているかを確認する変数
	bool sound_change;
};
