#define POINT_STRUCT
#ifdef POINT_STRUCT
#pragma once
#include "Collision.h"
#include "PointStruct.h"

class Box
{
public:
	TypeBoxCollision Type; // Box đó thuộc loại box nào.
	P Position;
	P Size;
	P FrameVelocity; // Độ dời của box theo 2 trục X,Y trong khoảng thời gian 1 khung hình
	bool enableCollision; // cho biết box này có đang nhận và xử lý va chạm đó không
	Box(P pos, P size, P v);
	Box(P pos);
	Box();
};
#endif //POINT_STRUCT
