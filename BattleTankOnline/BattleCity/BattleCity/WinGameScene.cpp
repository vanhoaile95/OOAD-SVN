#include "WinGameScene.h"
#include "GameScore.h"

WinGameScene::WinGameScene() :UI()
{
}


WinGameScene::~WinGameScene()
{
}

void WinGameScene::OnKeyUp(int KeyCode)
{

}
void WinGameScene::OnKeyDown(int KeyCode)
{
	if (KeyCode == DIK_UP || KeyCode == DIK_DOWN) {
		//ActiveChild->HandlerKey(ControlKey::UpKey);
	}
}
void WinGameScene::Init()
{
	UI::Init();

	GreenTeamWin = new UIObject(P(340, 150), BObjectName::UI_TEXT_GREEN_TEAM_WIN, false);
	Child.push_back(GreenTeamWin);
	WhiteTeamWin = new UIObject(P(340, 150), BObjectName::UI_TEXT_WHITE_TEAM_WIN, false);
	Child.push_back(WhiteTeamWin);

	MultiplayerHud = new MultiPlayerHud();
	MultiplayerHud->Init();

	/*if (ActiveChild == NULL)
		ActiveChild = new UISelectButton(P(462, 636), BObjectName::UI_BACK_MAIN_MENU_BTN, SelectedValue::MainMenuMode, true);
	Child.push_back(ActiveChild);*/
	ReverseYAxis();
}
void WinGameScene::UpdateData()
{
	if (GameScore::Instance()->WinState == 1)
	{
		WhiteTeamWin->Visible = true;
		GreenTeamWin->Visible = false;
	}
	else
	{
		WhiteTeamWin->Visible = false;
		GreenTeamWin->Visible = true;
	}
}
void WinGameScene::RenderFrame()
{
	UI::RenderFrame();
	MultiplayerHud->RenderFrame();
}
void WinGameScene::UpdateWorld()
{
	//ActiveChild->UpdateWorld();
	MultiplayerHud->UpdateWorld();
}