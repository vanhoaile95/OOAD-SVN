#include "Mission.h"
#include <dinput.h>
#include "CollisionManager.h"

Mission::Mission() 
{
	MaxTank = ConfigsManager::Instance()->GetIntConfig(ConfigName::MAX_TANK_IN_GAME);
	MaxClient = ConfigsManager::Instance()->GetIntConfig(ConfigName::MAX_CLIENT_IN_GAME);
}

void Mission::Init(GameState mapid, Map * map)
{
	_listObjects.clear();
	_Map = map;
	_listObjects = *BuildListObject(_Map);

	InitBorderAndTank();

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
		Borders[i]->ID = i + 1000;
		pair<int, Object*> p(i + 1000, Borders[i]);
		_listObjects.insert(p);
	}


	P InitPointA[10] = { P(50,50),P(750, 50),P(100, 100),P(600, 100) };
	P InitPointB[10] = { P(750, 600),P(50, 600), P(100, 550),P(700, 550) };

	for (int i = 0; i < MaxTank; i++)
	{
		int dir = (i % 2 == 0) ? 1 : 0;
		if (dir)
		{
			Tanks[i] = new AITank(InitPointA[i / 2], BObjectName::PLAYER0, i);
		}
		else
		{
			Tanks[i] = new AITank(InitPointB[i / 2], BObjectName::PLAYER2, i);
		}
	}
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
string Mission::Controll(int id,string command)
{
	return Tanks[id]->Controll(command);
}
void Mission::StartGame(int listuid[],int sid)
{
	for (int i = 0; i < MaxTank;i++)
	{
		if(i >= MaxClient)
		{
			Tanks[i]->EnableAIMode();
		}
		else
		{
			if (listuid[i] == -1)
			{
				Tanks[i]->EnableAIMode();
			}
			ListUID[i] = listuid[i];
		}
		Tanks[i]->Start();

		Tanks[i]->SID = sid;
		Tanks[i]->TankID = i;
		_listBullets.push_back(Tanks[i]->Bullet);
	}
	SID = sid;
}

void Mission::UpdateWorld()
{
	DWORD testa = timeGetTime();
	//Update trước khi xử lý va chạm
	for (map<int,Object *>::iterator i = _listObjects.begin(); i != _listObjects.end(); i++)
	{
		i->second->Update();
	}
	for (int i = 0; i < MaxTank;i++)
	{
		Tanks[i]->Update();
	}
	DWORD testb = timeGetTime();
	for (int i = 0; i < MaxTank; i++)
	{
		for (int j = 0; j < MaxTank; j++)
		{
			if (i != j)
			{
				CollisionManager::CollisionCheckObject(Tanks[i], Tanks[j], SID);
			}
		}
		for (map<int, Object *>::iterator j = _listObjects.begin(); j != _listObjects.end(); j++)
		{
			CollisionManager::CollisionCheckObject(Tanks[i], j->second, SID);
		}
	}

	for (list<TankBullet *>::iterator i = _listBullets.begin(); i != _listBullets.end(); i++)
	{
		for (list<TankBullet *>::iterator j = _listBullets.begin(); j != _listBullets.end(); j++)
		{
			if (*i != *j)
			{
				CollisionManager::CollisionCheckObject(*i, *j, SID);
			}
		}
		for (int j = 0; j < MaxTank; j++)
		{
			if(Tanks[j]->TankID != (*i)->TankID)
				CollisionManager::CollisionCheckWithBulletObject(Tanks[j], *i, SID);
		}
		for (map<int, Object *>::iterator j = _listObjects.begin(); j != _listObjects.end(); j++)
		{
			CollisionManager::CollisionCheckWithBulletObject(j->second, *i, SID);
		}
	}
	DWORD testc = timeGetTime();

	for (int i = 0; i < MaxTank; i++)
	{
		Tanks[i]->LateUpdate();
	}
	DWORD testd = timeGetTime();
	DWORD re1 = testb - testa;
	DWORD re2 = testc - testb;
	DWORD re3 = testd - testc;
	if (re2 > 50) {
		int i = 0;
 	}
}

Mission::~Mission()
{

}