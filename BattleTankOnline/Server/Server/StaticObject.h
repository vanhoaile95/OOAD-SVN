#ifndef STATIC_OBJECT_H
#define STATIC_OBJECT_H
#pragma once

#include "Object.h"

class StaticObject: public Object
{

public:
	StaticObject(P pos);
	StaticObject(P pos,BObjectName name);
	virtual void Update();
	virtual string Controll(string msg);
	virtual bool HandlerCollision(Collision collision, int sid);
	virtual bool HandlerBulletCollision(Collision collision, int tankid, int tanktype, int sid);
	virtual Box GetBox(){ return Object::GetBox();}
};
#endif