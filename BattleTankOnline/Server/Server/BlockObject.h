#ifndef BLOCK_OBJECT_H
#define BLOCK_OBJECT_H
#pragma once

#include "StaticObject.h"

class BlockObject : public StaticObject
{
protected:
public:
	BlockObject(P pos,BObjectName Name);
	virtual bool HandlerCollision(Collision collision){ return true; }
	virtual string Controll(string msg);
};
#endif