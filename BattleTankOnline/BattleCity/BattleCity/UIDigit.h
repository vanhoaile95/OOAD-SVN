#ifndef UI_DIGIT_H
#define UI_DIGIT_H
#pragma once
#include "UIObject.h"

class UIDigit :public UIObject
{
public:
	int * Value;
	int Length;
	Color CurrentColor;
	UIDigit(P pos,int maxLength = 5,bool visible = true);

	void UpdateValue(int value);
	virtual void Draw();
	virtual void Draw(P position);
};
#endif