#ifndef DYNAMIC_OBJECT_H
#define DYNAMIC_OBJECT_H
#pragma once

#include "Object.h"


class DynamicObject : public Object
{
public:
	P CollisionTime;
public:
	DynamicObject(P pos);
	DynamicObject(P pos,BObjectName name);
	virtual bool HandlerCollision(Collision collision);
	virtual bool HandlerBulletCollision(Collision collision, int tankid, int tanktype);
	virtual Box GetBox(){ return Object::GetBox(); }
	virtual int Controll(P pos, string msg, int ping);
	virtual void Update();
	virtual void LateUpdate();

	virtual void InitSprite();
	virtual void InitRect();
	virtual void Draw();
	virtual void FixedDraw();
};
#endif