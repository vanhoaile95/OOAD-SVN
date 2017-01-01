#include "ServerGameLogic.h"
#include "ServerTimeManager.h"
#include "Global.h"

ServerGameLogic* ServerGameLogic::_instance = 0;

ServerGameLogic* ServerGameLogic::Instance()
{
	if (0 == _instance)
	{
		_instance = new ServerGameLogic();
	}
	return _instance;
}

ServerGameLogic::ServerGameLogic()
{
	GameMaps = new map<int, Map*>();
	GameLogic = new map<int, MissionManager*>();
	Global::Instance()->GameLogic = GameLogic;
}
ServerGameLogic::~ServerGameLogic()
{

}
void ServerGameLogic::Init()
{
	ServerTimeManager::Instance()->Init();
	InitMap();
}
void ServerGameLogic::InitMap()
{
	Map* m0 = new Map("map1");
	m0->LoadMap();
	pair<int, Map*> pm1(0, m0);
	GameMaps->insert(pm1);
}
void ServerGameLogic::InitGameLogic(int sid, int mapid)
{
	MissionManager* m1 = new MissionManager();
	pair<int, MissionManager*> pm1(sid, m1);
	GameLogic->insert(pm1);
	m1->Init(sid,GameMaps->find(mapid)->second);
}
string ServerGameLogic::Controll(int sid,int id, string command)
{
	return GetServer(sid)->Controll(id, command);
}
Mission* ServerGameLogic::GetServer(int sid)
{
	auto search = GameLogic->find(sid);
	if (search != GameLogic->end()) {
		return search->second->CurrentScene;
	}
	return NULL;
}
void ServerGameLogic::OffServer(int sid)
{
	auto search = GameLogic->find(sid);
	if (search != GameLogic->end()) {
		GameLogic->erase(search);
	}
}
void ServerGameLogic::Run()
{
	//MSG msg;
	int done = 0;

	while (!done)
	{
		
		if (ServerTimeManager::Instance()->CanCreateNewFrame())
		{
			UpdateWorld();
		}
		else
		{
			ServerTimeManager::Instance()->SleepToNewFrame();
		}
	}
}
void ServerGameLogic::UpdateWorld()
{
	for (map<int, MissionManager*>::iterator i = GameLogic->begin(); i != GameLogic->end(); i++)
	{
		MissionManager * servergamelogic = i->second;
		if (servergamelogic->CurrentState == GameState::Running)
		{
			servergamelogic->UpdateWorld();
		}
	}
}

void ServerGameLogic::End()
{

}
