#pragma once

class MovePlayer : public Base {
public:
	MovePlayer();
	~MovePlayer();

	void Init();   // 初期設定
	void Update(); // 更新処理
	void Draw();   // 描画処理
	void Exit();//	終了処理
	
private:

	// プレイヤーの武器画像用の変数
	int m_image;

};
