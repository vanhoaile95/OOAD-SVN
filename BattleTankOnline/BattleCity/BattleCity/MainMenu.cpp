#include "MainMenu.h"


MainMenu::MainMenu() :UI()
{
}


MainMenu::~MainMenu()
{
}

void MainMenu::OnKeyUp(int KeyCode)
{
	
}
void MainMenu::OnKeyDown(int KeyCode)
{
	if (KeyCode == DIK_UP || KeyCode == DIK_DOWN) {
		ActiveChild->HandlerKey(ControlKey::UpKey);
	}
}
void MainMenu::Init()
{
	UI::Init();

	Child.push_back(new UIObject(P(222, 26), BObjectName::UI_TITLE_BATTLE_CITY));
	Child.push_back(new UIObject(P(462, 447), BObjectName::UI_TEXT_SINGLEPLAYER));
	Child.push_back(new UIObject(P(462, 528), BObjectName::UI_TEXT_MULTIPLAYER));
	Child.push_back(new UIObject(P(674, 658), BObjectName::UI_TEXT_CREATE_BY_ROTS));

	if(ActiveChild == NULL)
		ActiveChild = new UISelectButton(P(368, 443), BObjectName::UI_MAIN_MENU_BTN,SelectedValue::SinglePlayerMode,true);
	Child.push_back(ActiveChild);
	ReverseYAxis();
}
void MainMenu::RenderFrame()
{
	UI::RenderFrame();
}
void MainMenu::UpdateWorld()
{
	ActiveChild->UpdateWorld();
}