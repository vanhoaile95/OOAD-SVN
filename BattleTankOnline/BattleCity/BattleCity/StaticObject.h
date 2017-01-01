#ifndef STATIC_OBJECT_H
#define STATIC_OBJECT_H
#pragma once

#include "Object.h"

class StaticObject: public Object
{
	int RECTLength;
public:
	StaticObject(P pos);
	StaticObject(P pos,BObjectName name);
	virtual void Update();
	virtual void Draw();

	virtual void InitSprite();
	virtual void InitRect();
	virtual void Draw(P position);
	virtual void FixedDraw();
	virtual int Controll(P pos, string msg, int ping);
	virtual bool HandlerCollision(Collision collision);
	virtual bool HandlerBulletCollision(Collision collision, int tankid, int tanktype);
	virtual Box GetBox(){ return Object::GetBox();}
};
#endif