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
	DynamicObject(P pos, BObjectName name);
	virtual bool HandlerCollision(Collision collision, int sid);
	virtual bool HandlerBulletCollision(Collision collision, int tankid, int tanktype, int sid);
	virtual string Controll(string msg);
	virtual Box GetBox(){ return Object::GetBox(); }
	virtual void Update();
	virtual void LateUpdate();
};
#endif