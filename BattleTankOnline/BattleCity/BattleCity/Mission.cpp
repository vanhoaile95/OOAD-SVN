#include "ClientManager.h"
#include "Mission.h"
#include <dinput.h>
#include "CollisionManager.h"
#include "BorderObject.h"

Mission::Mission() //: CollisionManager(this)
{
	//_Mario = Mario;
	VPX = NULL;
	VPY = NULL;
	UpdateTime = 0;
	UpdateInteval = ConfigsManager::Instance()->GetIntConfig(ConfigName::SLEEP_PERSTEP_TIME);
}
void Mission::Init()
{
	if (Helper::Offline())
	{
		_Map = new Map("m1");
	}
	else
	{
		_Map = new Map("map1");
	}
	_listObjects.clear();
	//_IsReset = false;
	_Map->LoadMap();
	_listObjects = *BuildListObject(_Map);

	for (map<int, Object *>::iterator j = _listObjects.begin(); j != _listObjects.end(); j++)
	{
		if (j->second->ObjectName == BObjectName::BASE1)
		{
			Base1 = j->second;
		}
		else if (j->second->ObjectName == BObjectName::BASE2)
		{
			Base2 = j->second;
		}
	}

	MultiplayerHud = new MultiPlayerHud();
	if (!Helper::Offline())
	{
		MultiplayerHud->Init(ClientManager::Instance()->ClientInfo);
	}
	else
	{
		MultiplayerHud->InitOffline();
	}
	InitBorderAndTank();
	//EffectManager::GetInstance()->GetDeltaTime(&_GameTime->_DeltaTime);
	Camera::GetInstance()->VPX = 0;
	Camera::GetInstance()->VPY = SCREEN_HEIGHT;
	//mario_level = GameInfor::GetInstance()->MarioLevelPointer();
	//mario_speedup = GameInfor::GetInstance()->MarioSpeedPointer();
}
void Mission::InitBorderAndTank()
{
	BorderObject * Borders[4];
	Borders[0] = new BorderObject(BObjectName::BORDER_BELOW);
	Borders[1] = new BorderObject(BObjectName::BORDER_ABOVE);
	Borders[2] = new BorderObject(BObjectName::BORDER_LEFT);
	Borders[3] = new BorderObject(BObjectName::BORDER_RIGHT);
	for (int i = 0; i < 4; i++)
	{
		Borders[i]->InitSprite();
		Borders[i]->ID = i+1000;
		pair<int, Object*> p(i + 1000, Borders[i]);
		_listObjects.insert(p);
	}

	P InitPointA[10] = { P(50,50),P(750, 50),P(100, 100),P(600, 100)};
	P InitPointB[10] = { P(750, 600),P(50, 600), P(100, 550),P(700, 550)};

	for (int i = 0; i < ClientManager::Instance()->MaxTank; i++)
	{
		int dir = (i % 2 == 0) ? 1 : 0;
		if (dir)
		{
			Tanks[i] = new AITank(InitPointA[i / 2], BObjectName::PLAYER0,i);
		}
		else
		{
			Tanks[i] = new AITank(InitPointB[i / 2], BObjectName::PLAYER2,i);
		}
		if (Helper::Offline() && Tanks[i]->TankID != Helper::GetTankID())
		{
			Tanks[i]->EnableAIMode();
		}
		Tanks[i]->InitSprite();
	}
	TankControl = Tanks[Helper::GetTankID()];
}
void Mission::Reset()
{
	/*for (list<Object *>::iterator i = _listFreeObjects.begin(); i != _listFreeObjects.end(); i++)
	{
		delete (*i);
	}
	_IsReset = false;
	_listObjects.clear();
	_listFreeObjects.clear();*/
	//_Map->LoadMap();
	//_listObjects = *BuildListObject(_Map, _Mario, &_listFreeObjects);
	//_quadTree = BuildQuadTree(_Map, &_listObjects, MQuadTreeType::DRAW, _listNodes);
	//_updateQuadTree = BuildQuadTree(_Map, &_listObjects, MQuadTreeType::UPDATE, _listUpdateNodes);

}
void Mission::ProcessInput()
{

}
void Mission::OnKeyDown(int KeyCode)
{
	string command = "";
	switch (KeyCode)
	{
	case DIK_UP:
		command = "1|0";
		break;
	case DIK_LEFT:
		command = "1|1";
		break;
	case DIK_DOWN:
		command = "1|2";
		break;
	case DIK_RIGHT:
		command = "1|3";
		break;
	case DIK_SPACE:
		command = "3|0";
		break;
	}
	if (command != "")
	{
		if (TankControl->Controll(command) != 0 && !Helper::Offline())
		{
			if(command != "3|0")
				Helper::SEND_Controll(command);
		}
	}
	
}
void Mission::OnKeyUp(int KeyCode)
{
	string command = "";
	switch (KeyCode)
	{
	case DIK_UP:
		command = "0|0";
		break;
	case DIK_LEFT:
		command = "0|1";
		break;
	case DIK_DOWN:
		command = "0|2";
		break;
	case DIK_RIGHT:
		command = "0|3";
		break;
	}
	if (command != "")
	{
		if (TankControl->Controll(command) != 0 && !Helper::Offline())
		{
			Helper::SEND_Controll(command);
		}
	}
}
void Mission::ServerGameLogicUpdate()
{
	if(Helper::Offline()) return;
	//SEND
	UpdateTime += ClientTimeManager::Instance()->DeltaTime;
	if (UpdateTime > UpdateInteval 
		&& UpdateTime > ClientManager::Instance()->Ping*4
		&& CanCheckUpdate 
		&& !ClientManager::Instance()->CanSend() 
		&& !ClientManager::Instance()->Received())
	{
		UpdateTime = 0;
		Helper::SEND_PING_UpdateGameLogic();
	}
	else if (UpdateTime > 2000)
	{
		UpdateTime = 0;
		Helper::SEND_PING_UpdateGameLogic();
	}
	//RECV

	string updateinf;
	if (!Helper::Equals(Helper::RECV_PING_UpdateGameLogic(&updateinf), "Wait"))
	{
		if (updateinf != "")
		{
			//test1 = ClientTimeManager::Instance()->GetClientCurrentTime();
			vector<string> listcommand = StringHelper::split(updateinf, "|");
			for (int i = 0; i < (int)listcommand.size(); i++)
			{
				vector<string> decode = StringHelper::split(listcommand[i], "+");
				//string updateData = "#tank+#x+#y+#command+#dir+#time";
				int id = Helper::GetIntFromString(decode[0]);
				float x = Helper::GetFloatFromString(decode[1]);
				float y = Helper::GetFloatFromString(decode[2]);
				string command = decode[3].append("|").append(decode[4]);
				DWORD currentTime = ClientTimeManager::Instance()->GetClientCurrentTime();
				int delay = (int) (Helper::GetDWORD(decode, 5) - currentTime);
				//if (delay >= 500)
				//	int askda = 0;
				if (id > 0)
				{
					Tanks[id-1]->Controll(P(x, y), command, delay);
				}
				else
				{
					_listObjects.find(-id)->second->Controll(P(x, y), command,delay);
					if (Base1->ID == -id)
					{
						GameScore::Instance()->WinState = 1;
						Value = WinGameMode;
					}
					else if (Base2->ID == -id)
					{
						GameScore::Instance()->WinState = 2;
						Value = WinGameMode;
					}
				}
				
			}
			//test2 = ClientTimeManager::Instance()->GetClientCurrentTime();
		}
		CanCheckUpdate = true;
	}

}
void Mission::CheckWinGame(int id)
{
	if (Base1->ID == id)
	{
		GameScore::Instance()->WinState = 1;
		Value = WinGameMode;
	}
	else if (Base2->ID == id)
	{
		GameScore::Instance()->WinState = 2;
		Value = WinGameMode;
	}
}
void Mission::UpdateWorld()
{
	ServerGameLogicUpdate();

	//Update trước khi xử lý va chạm
	for (int i = 0; i < ClientManager::Instance()->MaxTank; i++)
	{
		Tanks[i]->Update();
	}
	for (map<int, Object *>::iterator i = _listObjects.begin(); i != _listObjects.end(); i++)
	{
		i->second->Update();
	}


	//if (Helper::Offline())
	{
		for (int i = 0; i < ClientManager::Instance()->MaxTank; i++)
		{
			for (int j = 0; j < ClientManager::Instance()->MaxTank; j++)
			{
				if (i != j)
				{
					CollisionManager::CollisionCheckObject(Tanks[i], Tanks[j]);
				}
			}
			for (map<int, Object *>::iterator j = _listObjects.begin(); j != _listObjects.end(); j++)
			{
				CollisionManager::CollisionCheckObject(Tanks[i], j->second);
			}
		}

		for (list<TankBullet *>::iterator i = _listBullets.begin(); i != _listBullets.end(); i++)
		{
			for (list<TankBullet *>::iterator j = _listBullets.begin(); j != _listBullets.end(); j++)
			{
				if (*i != *j)
				{
					CollisionManager::CollisionCheckObject(*i,*j);
				}
			}
			for (int j = 0; j < ClientManager::Instance()->MaxTank; j++)
			{
				if (Tanks[j]->TankID != (*i)->TankID)
					CollisionManager::CollisionCheckWithBulletObject(Tanks[j], *i);
			}
			for (map<int, Object *>::iterator j = _listObjects.begin(); j != _listObjects.end(); j++)
			{
				CollisionManager::CollisionCheckWithBulletObject(j->second, *i);
			}
		}
	}




	for (int i = 0; i < ClientManager::Instance()->MaxTank; i++)
	{
		Tanks[i]->LateUpdate();
	}
}

void Mission::RenderFrame()
{
	for (map<int, Object *>::iterator i = _listObjects.begin(); i != _listObjects.end(); i++)
	{
		if(i->second->Type != TypeBoxCollision::TreeBox)
			i->second->Draw();
	}
	for (int i = 0; i < ClientManager::Instance()->MaxTank; i++)
	{
		Tanks[i]->Draw();
	}
	for (map<int, Object *>::iterator i = _listObjects.begin(); i != _listObjects.end(); i++)
	{
		if (i->second->Type == TypeBoxCollision::TreeBox)
			i->second->Draw();
	}
	//EffectManager::GetInstance()->Draw();
	MultiplayerHud->RenderFrame();

}
RECT* Mission::GetTankRECT()
{
	RECT* tankrect = new RECT[4];
	for (int i = 0; i < ClientManager::Instance()->MaxClient; i++)
	{
		tankrect[i] = Tanks[i]->TankRECT();
	}
	return tankrect;
}
Mission::~Mission()
{

}