#include "Algorithm.h"

void GetVelocityMove(float desX, float desY, float startX, float startY, float *startVx, float *startVy, float V)
{
	if (startX == desX)
	{
		*startVx = V; *startVy = 0;
		return;
	}
	float vxtemp = desX - startX;
	float vytemp = desY - startY;
	float slope =  vytemp / vxtemp;
	float anpha = atan(slope);
	float absVx = std::abs( V*cos(anpha));
	*startVx = (vxtemp > 0)? absVx : -absVx;
	*startVy = *startVx*slope;
}

bool Intersect(const RECT *rect1, const RECT *rect2)
{
	if (rect1 == NULL || rect2 == NULL)
		return false;
	if (rect1->right < rect2->left) // _rect bên trái so với obj->_rect
		return false;
	if (rect1->left > rect2->right) // _rect bên phải so với obj->_rect
		return false;
	if (rect1->bottom > rect2->top) // _rect bên trên so với obj->_rect
		return false;
	if (rect1->top < rect2->bottom) // _rect bên dưới so với obj->_rect
		return false;
	return true;
}

//RECT GetSweptBroadphaseBox(Box b)
//{
//	RECT broadphaserect;
//	//broadphaserect.left = b.Vx > 0 ? b.X : b.X + b.Vx;
//	//broadphaserect.top = b.Vy > 0 ? b.Y +b.Width : b.Y +b.Width + b.Vy;
//	//broadphaserect.right = broadphaserect.left - b.Width;
//	//broadphaserect.bottom = broadphaserect.right + b.Height;
//	return broadphaserect;
//}
//
//Point::Point(float x, float y)
//{
//	X = x; Y = y;
//}
