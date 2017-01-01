#ifndef MISSION_H
#define MISSION_H

#include "Build.h"
#include "GameState.h"
#include "ServerTimeManager.h"
#include "ConfigsManager.h"
#include "Scene.h"
#include "AITank.h"
#include "BorderObject.h"
#include "Client.h"
#include "ClientInfo.h"
#include "ServerInfo.h"

class Mission : public Scene
{
public:
	int SID;
public:
	int MaxTank;
	int MaxClient;
	map<int,Object *> _listObjects;


	map<int, AITank *> Tanks;
	list<TankBullet*> _listBullets;
	Map *_Map;
	
	int ListUID[4];

	Mission();
	virtual void Init(GameState mapid,Map *map);
	virtual void InitBorderAndTank();
	virtual void UpdateWorld();
	virtual void Reset();

	virtual string Controll(int id, string command);
	void StartGame(int listuid[], int sid);
	~Mission();
};

#endif