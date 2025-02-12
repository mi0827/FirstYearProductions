#pragma once
constexpr auto FIAME_IMAGE_MAX = 5; // 炎画像の数
constexpr auto OPEN_CURTAIN_MAX = 10; // カーテンの開く画像の数
constexpr auto CLOSE_CURTAIN_MAX = 18; // カーテンの閉じる画像の数
constexpr auto GAME_STRAT = 240; // ゲームシーンに行く前の処理を終わらせる値
constexpr auto GAME_END = 150; // ゲームシーンを終わてる魏の処理を始める値
constexpr auto FRAME_IMSGE_MAX = 3; // フレーム画像の数

enum {
	TUTORIAL, // チュートリアルシーン

	SELECT, // 難易度選択シーン

	PLAY,   // プレイシーン

	END
};

// ------------------------
// プレイシーン用クラス
// ------------------------
// モード選択シーンからゲームシーンまでを行うクラス
class PlayScene : public Base {
public:
	PlayScene();
	~PlayScene();


	bool IsChange(); // シーンの切り替え用の関数

	void Init();   // 初期設定
	void Update(); // 更新処理
	void Draw();   // 描画処理
	void PointDraw(Pos pos); // 最終ポイントを描画するための関数
	void Exit();//	終了処理

private:
	// どの難易度のクラスを読み込むか判断用の変数
	int m_check_count;

	// 難易度選択シーンかplayシーン化を判断に使う変数
	int m_change_scene;

	// GameMain でのシーンの切り替えに使う変数
	bool change_;

	// 難易度選択画面が終わってから、ゲームシーンが始まるまでのカウント
	int m_start_count;

	// カウントを見えるようにするため
	int m_change_count;

	//-------------------------------------
	// 画像を入れる用の変数
	//------------------------------------
	
	// 制限時間をラインで描画用変数
	// 炎の画像ようの変数
	// アニメーションさせるため複数個作る
	int m_fiame_image[FIAME_IMAGE_MAX];
	// 開くカーテン画像用変数
	int m_curtain_open_image;

	// 閉じるカーテン画像変数
	int m_curtain_close_image;

	int m_frame_image[FRAME_IMSGE_MAX];

	// -----------------------------------------
	// 各画像の描画座標用変数
	//------------------------------------------
	// 
	// 炎画像の描画座標用の変数
	Pos m_fiame_pos;

	// カーテン画像の描画座標用変数
	Pos m_curtain_pos;

	// フレーム画像の描画座標
	Pos m_frame_pos[FRAME_IMSGE_MAX];

	// --------------------------------------
	// アニメーションさせるための変数たち
	// ---------------------------------------
	
	// 時間経過で描画位置を小さくしていくための変数
	Pos m_fiame_time_pos;

	// 炎画像をアニメーションするための変数
	int m_animation_count;

	// 描画している画像を徐々に減らしていくための数値を入れる用の変数
	float m_timelimt;

	// ゲームの制限時間
	float m_game_count;

	// カーテン画像をアニメーションさせるためのカウント変数
	int m_curtain_count;

	// カーテン画像自体の座標用の変数
	Pos m_curtain_image_pos;

	// --------------------------
	// boolがたの変数
	// -------------------------
	
	// ゲームシーンに進む前と中を分ける変数
	bool m_play;

	// ゲームシーン野中と後を分ける変数
	bool m_play_end;

	
};