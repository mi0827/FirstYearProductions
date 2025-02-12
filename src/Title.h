#pragma once

// ------------------------
// タイトルシーン用クラス
// ------------------------
class Title: public Base {
public:
	Title();
	~Title();

	bool IsChange(); // 画像の切り替え

	void Init();   // 初期設定
	void Update(); // 更新処理
	void Draw();   // 描画処理
	void Exit();//	終了処理

private:
	Pos m_mouse_pos; // マウスの座標

	// タイトル画面でのｂｇｍを入れる変数
	int m_bgm;
	// 決定したときに流す音用の変数
	int m_button_sound;
	

	// BGMが流れているかを確認する変数
	bool sound_change;


	 // ボタンをいしているように見せるための変数
	Pos m_push;
	int m_push_count; 

	int m_button_image;  // ボタン画像を入れる用用の変数

	bool change_;

};