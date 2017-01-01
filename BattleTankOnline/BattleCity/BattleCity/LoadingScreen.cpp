#include "LoadingScreen.h"



LoadingScreen::LoadingScreen() :UI()
{
	
}


LoadingScreen::~LoadingScreen()
{
}
void LoadingScreen::Init()
{
	UI::Init();
	Child.push_back(new UIObject(P(222,26), BObjectName::UI_TITLE_BATTLE_CITY));
	Child.push_back(new UIObject(P(340,420), BObjectName::UI_TEXT_LOADING));
	Child.push_back(new UIObject(P(674,658), BObjectName::UI_TEXT_CREATE_BY_ROTS));
}
void LoadingScreen::RenderFrame()
{
	for (list<UIObject *>::iterator i = Child.begin(); i != Child.end(); i++)
	{
		(*i)->FixedDraw();
	}
}
void LoadingScreen::UpdateWorld()
{
}
