#pragma once
#include "PlayBase.h"

class Tutorial : public PlayBase {
public:

	void Init();	//	初期化処理	
	void Update();//	更新処理
	void Draw();//	描画処理
	void Exit();//	終了処理
	bool IsChange(); // シーンの切り替え用の関数

private:
	// BGMが流れているかを確認する変数
	bool sound_change;

	// チュートリアル画面でのｂｇｍを入れる変数
	int m_bgm;

	// GameMain でのシーンの切り替えに使う変数
	bool change_;
};