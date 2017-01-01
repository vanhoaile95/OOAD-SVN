#define SERVER_H
#ifdef SERVER_H
#pragma once
#include "Helper.h"
#include "ClientManager.h"


enum ServerState
{
	INIT_FAILED = -40,
	ON_ERROR = -1,

	INIT = 0,
	RUNNING = 1,
	STOP = 10,

	WAITING = 2,
	FULL = 3,
	GAME_RUN = 4,
	GAME_END = 5,
};
class Server
{
public:
	int MaxClient;
	int ClientCount;
	int SID;
	int listUID[4];
	int MapIndex;
	ServerState State;

	Client* Clients[4];
public:
	Server();   
	~Server();

	int Init(int SID);
	int Execute();
	int End();
	int Join(int UID);
	int Exit(int UID);

	int StartGame();
};
#endif // SERVER_H