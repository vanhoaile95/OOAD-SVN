#include "UIDigit.h"



UIDigit::UIDigit(P pos, int maxLength, bool visible) :UIObject(pos, BObjectName::UI_DIGIT, visible)
{
	InitSprite();
	Length = maxLength;
	Value = new int[Length];
	CurrentColor = Color::White;
}

void UIDigit::UpdateValue(int value)
{
	int temp = value;

	if (value == -20 || value == -21)
	{
		RECTIndex = -value;
		return;
	}

	int i = 0;
	Length = 0;
	do
	{
		Value[Length] = temp % 10;
		Length++;
		temp /= 10;
	} while (temp > 0);
}

void UIDigit::Draw()
{
	if (RECTIndex == 20 || RECTIndex == 21)
	{
		StaticObject::Draw();
		return;
	}
	P pos = Position;
	RECTIndex = 0;
	for (int i = Length - 1; i >= 0; i--)
	{
		RECTIndex = Value[i];
		RECTIndex += CurrentColor * 10;
		Draw(pos);
		pos.X += 30;
	}
}

void UIDigit::Draw(P position)
{
	UIObject::Draw(position);
}
