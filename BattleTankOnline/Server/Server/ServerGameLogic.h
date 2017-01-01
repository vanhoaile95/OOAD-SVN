#define GAME_LOGIC_H
#ifdef GAME_LOGIC_H
#pragma once
#include "MissionManager.h"

class ServerGameLogic
{
private:
	static ServerGameLogic *_instance;
	ServerGameLogic();
	~ServerGameLogic();
public:
	static ServerGameLogic* Instance();

	map<int, MissionManager*> *GameLogic;
	map<int, Map*> *GameMaps;

	void Init();
	void InitMap();
	void InitGameLogic(int sid, int mapid);
	string Controll(int sid,int id, string command);
	Mission* GetServer(int sid);
	void OffServer(int sid);
	void Run();
	void End();



	void UpdateWorld();
};

#endif // GAME_LOGIC