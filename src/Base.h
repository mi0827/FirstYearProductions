#pragma once
#include "Pos.h"

// -------------------
// ベースクラス
// -------------------
class Base {
public:	

	Pos m_pos;  // x座標、y座標、円の半径、横幅、縦幅
	
	int m_bak_image; // 背景画像を入れる用の変数
};
