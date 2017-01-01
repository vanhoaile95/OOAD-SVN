#include "ClientManager.h"
#include "MultiplayerMain.h"
#include "UIServerInfo.h"
#include "ServerInfo.h"
#include "ClientInfo.h"
#include "Global.h"


MultiplayerMain::MultiplayerMain() :UI()
{

}


MultiplayerMain::~MultiplayerMain()
{

}
void MultiplayerMain::Init()
{
	UI::Init();
	if (UID == NULL) UID = new UIDigit(P(771, 67));
	UID->UpdateValue(0);
	Child.push_back(UID);
	if (SID == NULL) SID = new UIDigit(P(1022, 67));
	SID->UpdateValue(0);
	Child.push_back(SID);

	Child.push_back(new UIObject(P(142, 64), BObjectName::UI_TITLE_SMALL_BATTLE_CITY));
	Child.push_back(new UIObject(P(654, 67), BObjectName::UI_TEXT_ID,true,0));
	Child.push_back(new UIObject(P(904, 67), BObjectName::UI_TEXT_ID,true,1));
	Child.push_back(new UIObject(P(428, 305), BObjectName::UI_DOT_ROW));
	Child.push_back(new UIObject(P(428, 132), BObjectName::UI_DOT_ROW));
	Child.push_back(new UIObject(P(428, 305), BObjectName::UI_DOT_ROW));
	Child.push_back(new UIObject(P(420, 454), BObjectName::UI_DOT_ROW));
	Child.push_back(new UIObject(P(457, 181), BObjectName::UI_TEXT_CREATE_GAME));
	Child.push_back(new UIObject(P(488, 244), BObjectName::UI_TEXT_JOIN_GAME));
	Child.push_back(new UIObject(P(537, 648), BObjectName::UI_TEXT_START));

	if(btnStart == NULL)
		btnStart = new UISelectButton(P(462, 636), BObjectName::UI_MULTIPLAYER_START_BTN,SelectedValue::WaitingForClient, false);
	Child.push_back(btnStart);
	if (btnMain == NULL)
		btnMain = new UISelectButton(P(391, 168), BObjectName::UI_MULTIPLAYER_BTN, SelectedValue::CreateGame,true);
	Child.push_back(btnMain);
	ActiveChild = btnMain;

	//int row = 2, col = 2, max = 4;
	ServerInfo[0] = new UIServerInfo(P(436, 320), 0, false);
	ServerInfo[1] = new UIServerInfo(P(689, 320), 0, false);
	ServerInfo[2] = new UIServerInfo(P(436, 388), 0, false);
	ServerInfo[3] = new UIServerInfo(P(689, 388), 0, false);
	Child.push_back(ServerInfo[0]);
	Child.push_back(ServerInfo[1]);
	Child.push_back(ServerInfo[2]);
	Child.push_back(ServerInfo[3]);

	
	for (int i = 0; i < ClientManager::Instance()->MaxClient; i++)
	{
		ClientInfo[i] = new UIClientInfo(P(150+230*i, 493), -1, i, false);
		Child.push_back(ClientInfo[i]);
	}

	ReverseYAxis();

	CurrentServerInfoData = NULL;
	ClientManager::Instance()->Offline = false;
}

void MultiplayerMain::RenderFrame()
{
	UI::RenderFrame();
}
void MultiplayerMain::OnKeyUp(int KeyCode)
{

}
void MultiplayerMain::OnKeyDown(int KeyCode)
{
	if (WaitingForResponse) return;
	if (KeyCode == DIK_UP || KeyCode == DIK_RIGHT) {
		if (ActiveChild->Value == SelectedValue::SelectServer)
		{
			SelectServer();
		}
		else
		{
			ActiveChild->HandlerKey(ControlKey::UpKey);
		}
	}
	else if (KeyCode == DIK_LEFT || KeyCode == DIK_DOWN)
	{
		if (ActiveChild->Value == SelectedValue::SelectServer)
		{
			SelectServer(false);
		}
		else
		{
			ActiveChild->HandlerKey(ControlKey::UpKey);
		}
	}
}
void MultiplayerMain::HandlerAction(SelectedValue value)
{
	if (ActiveChild->ObjectName == BObjectName::UI_MULTIPLAYER_BTN && !WaitingForResponse)
	{
		if (ActiveChild->Value == SelectedValue::JoinGameMode)
		{
			Helper::SEND_Command("JoinGameMode");
			WaitingForResponse = true;
		}
		else if (ActiveChild->Value == SelectedValue::CreateGame)
		{
			Helper::SEND_Command("CreateGame");
			WaitingForResponse = true;
		}
		/*btnStart->Visible = true;
		ActiveChild = btnStart;
		btnStart->Value = btnMain->Value;*/

	}
	else if (ActiveChild->ObjectName == BObjectName::UI_SERVER_AVA && !WaitingForResponse)
	{
		if (ActiveChild->Value == SelectedValue::SelectServer)
		{
			int svindex = ServerInfo[CurrentIndex]->SID;
			Helper::SEND_JoinServer(svindex);
			WaitingForResponse = true;
		}
	}
	else if (ActiveChild->ObjectName == BObjectName::UI_MULTIPLAYER_START_BTN
		&& ActiveChild->Value == SelectedValue::WaitingForClient)
	{
		Helper::SEND_StartGame(ClientManager::Instance()->SID);
		WaitingForResponse = true;
		ActiveChild->Value = SelectedValue::WaitingForStartGame;
	}
}



void MultiplayerMain::UpdateWorld()
{
	ActiveChild->UpdateWorld();
	if (ActiveChild->ObjectName == BObjectName::UI_MULTIPLAYER_BTN && WaitingForResponse)
	{
		int uid, sid;
		if (ActiveChild->Value == SelectedValue::JoinGameMode)
		{
			CurrentServerInfoData = new list<ServerInf>();
			if (!Helper::Equals(Helper::RECV_JoinGameMode(CurrentServerInfoData,&sid, &uid), "Wait"))
			{
				UID->UpdateValue(uid);
				if (sid == -1)
				{
					TotalServer = CurrentServerInfoData->size();
					list<ServerInf>::iterator dataindex = CurrentServerInfoData->begin();
					for (int i = 0; i < ClientManager::Instance()->MaxClient; i++)
					{
						if (i < TotalServer)
						{
							ServerInf inf = *dataindex;
							ServerInfo[i]->Visible = true;
							ServerInfo[i]->UpdateInfo(inf.SID, inf.HostID, inf.MapID);
							dataindex++;
						}
						else
						{
							ServerInfo[i]->Visible = false;
						}
					}
					SelectServer();
				}
				else
				{
					UID->UpdateValue(uid);
					SID->UpdateValue(sid);
					ActiveChild = btnStart;
					ActiveChild->Value = SelectedValue::WaitingForClient;
				}
				
				WaitingForResponse = false;
			}
		}
		else if (ActiveChild->Value == SelectedValue::CreateGame)
		{
			if (!Helper::Equals(Helper::RECV_CreateGame(&uid, &sid), "Wait"))
			{
				UID->UpdateValue(uid);
				SID->UpdateValue(sid);
				WaitingForResponse = false;
				ActiveChild = btnStart;
			}
		}
	}
	else if (ActiveChild->Value == SelectedValue::SelectServer  && WaitingForResponse)
	{
		ClientInf * clientInf[4];
		if (!Helper::Equals(Helper::RECV_JoinServer(clientInf), "Wait"))
		{
			UpdateClientInfo(clientInf);
			WaitingForResponse = false;
			ActiveChild = btnStart;
		}
	}
	else if (ActiveChild->Value == SelectedValue::WaitingForClient)
	{
		updateTime += ClientTimeManager::Instance()->DeltaTime;
		if (!WaitingForResponse)
		{
			if (updateTime > ConfigsManager::Instance()->GetIntConfig(ConfigName::UI_SYNC_INTERVAL))
			{
				updateTime = 0;
				Helper::SEND_PING_WaitingForClient(ClientManager::Instance()->SID);
				WaitingForResponse = true;
			}
		}
		else
		{
			ClientInf * clientInf[4];
			bool start = false;
			if (!Helper::Equals(Helper::RECV_PING_WaitingForClient(clientInf,&start), "Wait"))
			{
				UpdateClientInfo(clientInf);
				WaitingForResponse = false;
				if (start)
				{
					//ActiveChild->Value = SelectedValue::StartGame;
					Global::Instance()->MissionManager->Control(GameState::Map1);
				}
			}
			
		}
	}
	else if (ActiveChild->Value == SelectedValue::WaitingForStartGame)
	{
		ClientInf * clientInf[4];
		if (!Helper::Equals(Helper::RECV_StartGame(clientInf), "Wait"))
		{
			//UpdateClientInfo(clientInf);
			WaitingForResponse = false;
			Global::Instance()->MissionManager->Control(GameState::Map1);
		}
	}
}



void MultiplayerMain::SelectServer(bool up)
{
	int max = (TotalServer > ClientManager::Instance()->MaxClient) ? ClientManager::Instance()->MaxClient : TotalServer;
	if (up)
	{
		CurrentIndex += 1;
		if (CurrentIndex > max - 1) CurrentIndex = 0;
	}
	else
	{
		CurrentIndex -= 1;
		if (CurrentIndex < 0) CurrentIndex = max - 1;
	}


	for (int i = 0; i < max; i++)
	{
		ServerInfo[i]->Selected = false;
	}
	ServerInfo[CurrentIndex]->Selected = true;
	ActiveChild = ServerInfo[CurrentIndex];
}
void MultiplayerMain::UpdateClientInfo(ClientInf * clientInf[])
{
	for (int i = 0; i < ClientManager::Instance()->MaxClient; i++)
	{
		ClientInfo[i]->Visible = true;
		ClientInfo[i]->UpdateInfo(clientInf[i]->UID, clientInf[i]->TankID);
	}
}