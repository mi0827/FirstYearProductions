#include "WinMain.h"
#include "GameMain.h"
#include "Hit.h"

//---------------------------------------------------------------------------------
//	‚Q“_‚Ì’·‚³‚ğæ“¾‚·‚éŠÖ”
//---------------------------------------------------------------------------------
float GetLength(float x1, float y1, float x2, float y2)
{
	float x = x1 - x2;
	float y = y1 - y2;
	float length = sqrtf(x * x + y * y);
	return length;
}

//---------------------------------------------------------------------------------
//	‰~“¯m‚Ì“–‚½‚è”»’è
//---------------------------------------------------------------------------------
bool CheckCircleHit(float x1, float y1, float r1, float x2, float y2, float r2)
{
	float length = GetLength(x1, y1, x2, y2);
	float radius = r1 + r2;
	if (length <= radius) {
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------
//	“_‚Æ‰~‚Ì“–‚½‚è”»’è
//---------------------------------------------------------------------------------
bool CheckPointCircleHit(float point_x, float point_y, float circle_x, float circle_y, float circle_r)
{
	float length = GetLength(point_x, point_y, circle_x, circle_y);
	if (length <= circle_r) {
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------
//	lŠp“¯m‚Ì“–‚½‚è”»’è
//---------------------------------------------------------------------------------
bool CheckBoxHit(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{
	if (x1 + w1 >= x2 && x1 <= x2 + w2) {
		if (y1 + h1 >= y2 && y1 <= y2 + h2) {
			return true;
		}
	}
	return false;
}
//---------------------------------------------------------------------------------
//	“_‚ÆlŠp‚Ì“–‚½‚è”»’è
//---------------------------------------------------------------------------------
bool CheckPointBoxHit(float point_x, float point_y, float box_x, float box_y, float box_w, float box_h)
{
	if (point_x >= box_x && point_x <= box_x + box_w) {
		if (point_y >= box_y && point_y <= box_y + box_h) {
			return true;
		}
	}
	return false;
}
