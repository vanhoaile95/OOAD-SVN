#ifndef UI_OBJECT_H
#define UI_OBJECT_H
#pragma once
#include "StaticObject.h"
#include "ControlKey.h"
#include "SelectedValue.h"

class UIObject :public StaticObject
{
public:
	bool Visible;
	SelectedValue Value;

	UIObject(P pos, BObjectName name,bool visible = true);
	UIObject(P pos, BObjectName name, bool visible ,int index);
	UIObject();
	void InitUIObject(P pos, BObjectName Name);
	virtual void ReverseYAxis();

	virtual void InitSprite();
	virtual void InitRect();
	virtual void FixedDraw();
	virtual void Draw();
	virtual void Draw(P position);
	virtual void UpdateWorld();
	virtual void HandlerKey(ControlKey Key);
	
};

#endif