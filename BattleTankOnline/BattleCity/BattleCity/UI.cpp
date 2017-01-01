#include "UI.h"


UI::UI()
{
	
}
UI::~UI()
{

}
void UI::Init()
{
	Child.clear();
	ActiveChild = NULL;
}

void UI::RenderFrame()
{
	for (list<UIObject *>::iterator i = Child.begin(); i != Child.end(); i++)
	{
		(*i)->Draw();
	}
}
void UI::UpdateWorld()
{
	for (list<UIObject *>::iterator i = Child.begin(); i != Child.end(); i++)
	{
		(*i)->UpdateWorld();
	}
}

void UI::ReverseYAxis()
{
	for (list<UIObject *>::iterator i = Child.begin(); i != Child.end(); i++)
	{
		(*i)->ReverseYAxis();
	}
}

SelectedValue UI::GetValue()
{
	return ActiveChild->Value;
}

