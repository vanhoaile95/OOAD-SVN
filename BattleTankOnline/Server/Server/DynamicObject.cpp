#include "DynamicObject.h"


DynamicObject::DynamicObject(P pos) : Object(pos)
{
	//InitSize();
}
DynamicObject::DynamicObject(P pos,BObjectName name) : Object(pos,name)
{
	//InitSize();
}

bool DynamicObject::HandlerCollision(Collision collision, int sid){ return true; }

bool DynamicObject::HandlerBulletCollision(Collision collision, int tankid, int tanktype, int sid)
{
	return true;
}

string DynamicObject::Controll(string msg)
{
	return "";
}

void DynamicObject::Update()
{
	FrameVelocity = (ObjectVelocity * ServerTimeManager::Instance()->DeltaTime);
	CollisionTime = P(1, 1);
	//Size = P(SpriteRect[RECTIndex].right - SpriteRect[RECTIndex].left, SpriteRect[RECTIndex].bottom - SpriteRect[RECTIndex].top);
	//printf("\nUpdate: %f,%f : %d", ObjectVelocity.X, ObjectVelocity.Y,ClientTimeManager::Instance()->DeltaTime);
}

void DynamicObject::LateUpdate()
{
	if (Type == BulletBox && FrameVelocity.X != 0)
	{
		int j = 0;
	}
	Position += FrameVelocity * CollisionTime;
	//printf("\nLateUpdate: %f,%f", Position.X, Position.Y);
}
