#include "MultiPlayerHud.h"


MultiPlayerHud::MultiPlayerHud() :UI()
{
}

MultiPlayerHud::~MultiPlayerHud()
{

}
void MultiPlayerHud::Init()
{
	UI::Init();

	for (int i = 0; i  < ConfigsManager::Instance()->GetIntConfig(MAX_CLIENT_IN_GAME); i++)
	{
		TankInfo[i] = new UIMutiplayerTankInfo(P(100 + 295*i,300), -1, i, true);
		if(Helper::GetClientInfo(i) != NULL)
			TankInfo[i]->UpdateInfo(Helper::GetClientInfo(i)->UID, Helper::GetClientInfo(i)->TankID);
		Child.push_back(TankInfo[i]);
	}
	UpdateInfo();
}

void MultiPlayerHud::Init(ClientInf* clientinf[])
{
	UI::Init();

	for (int i = 0; i < ConfigsManager::Instance()->GetIntConfig(MAX_CLIENT_IN_GAME); i++)
	{
		TankInfo[i] = new UIMutiplayerTankInfo(P(950, 100 + 180 * i), -1, i, true);
		TankInfo[i]->UpdateInfo(clientinf[i]->UID, clientinf[i]->TankID);
		Child.push_back(TankInfo[i]);
	}
}
void MultiPlayerHud::Init(ClientInf* clientinf [],RECT* TankRect)
{
	UI::Init();

	for (int i = 0; i < ConfigsManager::Instance()->GetIntConfig(MAX_CLIENT_IN_GAME); i++)
	{
		TankInfo[i] = new UIMutiplayerTankInfo(P(950, 100 + 180 * i), -1, i, true);
		TankInfo[i]->UpdateInfo(clientinf[i]->UID, clientinf[i]->TankID);
		Child.push_back(TankInfo[i]);
		TankInfo[i]->UpdateTankRECT(TankRect[i]);
	}
}
void MultiPlayerHud::UpdateInfo()
{
	for (int i = 0; i < ConfigsManager::Instance()->GetIntConfig(MAX_CLIENT_IN_GAME); i++)
	{
		TankInfo[i]->Kill->UpdateValue(GameScore::Instance()->MulTiplayerInfo[i]->Kill);
		TankInfo[i]->Death->UpdateValue(GameScore::Instance()->MulTiplayerInfo[i]->Death);
	}
}
RECT* MultiPlayerHud::GetTankRECT()
{
	RECT* result = new RECT[4];
	for (int i = 0; i < ConfigsManager::Instance()->GetIntConfig(MAX_CLIENT_IN_GAME); i++)
	{
		result[i] = TankInfo[i]->TankRect;
	}
	return result;
}
void MultiPlayerHud::UpdateTankRECT(RECT * TankRect)
{
	for (int i = 0; i < ConfigsManager::Instance()->GetIntConfig(MAX_CLIENT_IN_GAME); i++)
	{
		TankInfo[i]->UpdateTankRECT(TankRect[i]);
	}
}
void MultiPlayerHud::RenderFrame()
{
	UI::RenderFrame();
}
void MultiPlayerHud::UpdateWorld()
{

}
