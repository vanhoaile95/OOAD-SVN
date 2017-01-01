#ifndef BORDER_OBJECT_H
#define BORDER_OBJECT_H
#pragma once

#include "StaticObject.h"

class BorderObject : public StaticObject
{
	int RECTLength;
public:
	BorderObject(BObjectName name);
	virtual void InitSprite();
	virtual void InitRect();

	virtual void Draw();
	virtual void Draw(P position);
	virtual void FixedDraw();

	virtual int Controll(P pos, string msg);
	virtual bool HandlerCollision(Collision collision);
	virtual Box GetBox(){ return Object::GetBox(); }
};
#endif