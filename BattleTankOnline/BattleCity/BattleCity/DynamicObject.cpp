#include "DynamicObject.h"


DynamicObject::DynamicObject(P pos) : Object(pos)
{
	
}

DynamicObject::DynamicObject(P pos, BObjectName name) : Object(pos,name)
{

}

void DynamicObject::InitSprite()
{
	Sprite = CSprite::GetGlobalSpriteSheet();
	InitRect();
}

void DynamicObject::InitRect()
{
	SpriteRect = TextureRectManager::GetInstance()->GetRECTWithName(ObjectName);
	//Size = P(SpriteRect[0].right - SpriteRect[0].left, SpriteRect[0].bottom - SpriteRect[0].top);
}
void DynamicObject::Draw()
{
	if (Sprite != NULL && !IsDisappear)
	{
		Sprite->Draw(SpriteRect[RECTIndex],Position);
	}
}
void DynamicObject::FixedDraw()
{
	if (Sprite != NULL && !IsDisappear)
	{
		Sprite->FixedDraw(SpriteRect[RECTIndex],Position);
	}
}
bool DynamicObject::HandlerCollision(Collision collision)
{
	CollisionTime = collision.CollisionTime;
	return true; 
}

bool DynamicObject::HandlerBulletCollision(Collision collision, int tankid, int tanktype)
{
	CollisionTime = collision.CollisionTime;
	return true;
}

int DynamicObject::Controll(P pos, string msg, int ping)
{
	return 1;
}

void DynamicObject::Update()
{
	FrameVelocity = (ObjectVelocity * ClientTimeManager::Instance()->DeltaTime);
	CollisionTime = P(1,1);
	//Size = P(SpriteRect[RECTIndex].right - SpriteRect[RECTIndex].left, SpriteRect[RECTIndex].bottom - SpriteRect[RECTIndex].top);
	//printf("\nUpdate: %f,%f : %d", ObjectVelocity.X, ObjectVelocity.Y,ClientTimeManager::Instance()->DeltaTime);
}

void DynamicObject::LateUpdate()
{
	Position += FrameVelocity * CollisionTime;
	//printf("\nLateUpdate: %f,%f", Position.X, Position.Y);
}
