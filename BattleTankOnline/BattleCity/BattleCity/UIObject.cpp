#include "UIObject.h"


UIObject::UIObject(P pos, BObjectName name,bool visible) : StaticObject(pos,name)
{
	Visible = visible;
	InitSprite();
	RECTTime = 0;
}
UIObject::UIObject(P pos, BObjectName name, bool visible, int index) : StaticObject(pos, name)
{
	Visible = visible;
	InitSprite();
	RECTIndex = index;
}
UIObject::UIObject() :StaticObject(P(0,0))
{
	Visible = true;
	RECTTime = 0;
}
void UIObject::InitUIObject(P pos, BObjectName name)
{
	Position = pos;
	ObjectName = name;
	InitSprite();
	RECTTime = 0;
}
void UIObject::ReverseYAxis()
{
	Position.Y = SCREEN_HEIGHT - Position.Y - Size.Y;
}
void UIObject::Draw()
{
	if (Visible)
		StaticObject::Draw();
}
void UIObject::Draw(P position)
{
	StaticObject::Draw(position);
}
void UIObject::FixedDraw()
{
	if(Visible)
		StaticObject::FixedDraw();
}
void UIObject::InitSprite()
{
	Sprite = CSprite::GetUISpriteSheet();
	InitRect();
}
void UIObject::InitRect()
{
	StaticObject::InitRect();
}
void UIObject::UpdateWorld()
{

}
void UIObject::HandlerKey(ControlKey Key)
{

}
