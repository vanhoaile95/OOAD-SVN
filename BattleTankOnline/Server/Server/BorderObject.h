#ifndef BORDER_OBJECT_H
#define BORDER_OBJECT_H
#pragma once

#include "StaticObject.h"

class BorderObject : public StaticObject
{
public:
	BorderObject(BObjectName name);
	virtual void InitRect();

	virtual Box GetBox(){ return Object::GetBox(); }
};
#endif