#ifndef ALGORITHM_H
#define ALGORITHM_H
#pragma once
#include <d3dx9.h>
#include <algorithm>
#include <list>
#include <math.h>
#include "Box.h"


// Hàm trả về vận tốc *startVx, *startVy
// khi đối tượng di chuyển từ (startX,StartY) Đến (DesX,DesY)
// Với vận tốc V
void GetVelocityMove(float desX, float desY, float startX, float startY, float *startVx, float *startVy, float V);

static bool Intersect(const RECT *rect1, const RECT *rect2);

//RECT GetSweptBroadphaseBox(Box b);

#endif